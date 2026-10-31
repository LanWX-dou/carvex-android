"""从原Receiver镜像和dyld v5 slide元数据重算CFString，核对引用与分支。

不使用cfstr.py的旧inline猜测；不改写缓存。需要原始24A446 .54.dylddata。
"""
from pathlib import Path
import hashlib
import json
import struct

from verify_screen_aad import load, ROOT, REPO, RECEIVER_SHA

ROWS = (
    (0x276118010, 0x00200000D1935B2B, 0x251935B2B, "X-Apple-ET"),
    (0x276118030, 0x00200000D1935B36, 0x251935B36, "CSeq"),
    (0x276118E70, 0x00200000D1938051, 0x251938051, "et"),
    (0x2761199F0, 0x00200000D1940452, 0x251940452, "ekey"),
    (0x276119A10, 0x00200000D1940457, 0x251940457, "eiv"),
    (0x276114350, 0x00200000D192642B, 0x25192642B, "IsPINRequiredForPairing"),
)


def check():
    binary = (ROOT / "source/firmware/AirPlayReceiver").read_bytes()
    assert hashlib.sha256(binary).hexdigest() == RECEIVER_SHA
    segments = json.loads((ROOT / "source/metadata/receiver/segments.json").read_text(encoding="utf-8"))

    def read(va, size):
        s = next(s for s in segments if s["vmaddr"] <= va and va+size <= s["vmaddr"]+s["filesize"])
        off = s["fileoff"] + va - s["vmaddr"]
        return binary[off:off+size]

    cache_path = REPO / "firmware/extracted/24A446/dyld/dyld_shared_cache_arm64e.54.dylddata"
    with cache_path.open("rb") as f:
        header = f.read(512)
        assert header.startswith(b"dyld_v")
        off, count = struct.unpack_from("<II", header, 0x138)
        assert off and 0 < count < 100
        f.seek(off)
        mappings = [struct.unpack("<QQQQQQII", f.read(56)) for _ in range(count)]
        for addr, raw_ptr, target, text in ROWS:
            a, size, fileoff, slideoff, slidesize, *_ = next(m for m in mappings if m[0] <= addr and addr+32 <= m[0]+m[1])
            assert slidesize >= 24
            f.seek(slideoff)
            slide = f.read(24)
            assert struct.unpack_from("<I", slide)[0] == 5
            base = struct.unpack_from("<Q", slide, 16)[0]
            assert base == 0x180000000
            raw = read(addr, 32)
            f.seek(fileoff+addr-a)
            assert f.read(32) == raw  # 原cache与导出镜像的对象字节交叉检查
            _, flags, ptr, length = struct.unpack("<QQQQ", raw)
            assert flags == 0x7c8 and ptr == raw_ptr and length == len(text)
            assert ptr >> 63 == 0
            resolved = (base + (ptr & ((1 << 34)-1))) | (((ptr >> 34) & 255) << 56)
            assert resolved == target
            assert read(resolved, length+1) == text.encode("ascii")+b"\x00"
    insns, count = load("AirPlayReceiver", "asm", ROOT, "receiver", RECEIVER_SHA,
                        {0x2518A50B4, 0x2518D3704})
    anchors = {
        0x2518A53CC: "adrp x1, #0x276118000", 0x2518A53D0: "add x1, x1, #0x10",
        0x2518A53E4: "bl #0x25810a700", 0x2518A53EC: "cbz w8, #0x2518a5410",
        0x2518A53F0: "adrp x1, #0x276118000", 0x2518A53F4: "add x1, x1, #0x30",
        0x2518A5400: "bl #0x25810a680", 0x2518A5404: "cbz x0, #0x2518a5424",
        0x2518A540C: "b #0x2518a5434", 0x2518A5414: "cmp w24, #8",
        0x2518A5418: "b.eq #0x2518a5430", 0x2518A541C: "cmp w24, #0x20",
        0x2518A5420: "b.ne #0x2518a558c", 0x2518A5428: "mov w8, #3",
        0x2518A5434: "mov w8, #2", 0x2518A5438: "str w8, [x21, #0x100]",
        0x2518D3810: "adrp x1, #0x276118000", 0x2518D3814: "add x1, x1, #0xe70",
        0x2518D3820: "bl #0x25810a6f0", 0x2518D3828: "cbnz w8, #0x2518d3ab0",
        0x2518D3830: "cmp w23, #1", 0x2518D3834: "b.eq #0x2518d3ab0",
        0x2518D3840: "adrp x1, #0x276119000", 0x2518D3844: "add x1, x1, #0x9f0",
        0x2518D385C: "bl #0x25810a6b0", 0x2518D386C: "cmp w23, #0x20",
        0x2518D3874: "cmp w23, #8", 0x2518D3878: "b.ne #0x2518d38e4",
        0x2518D39FC: "adrp x1, #0x276119000", 0x2518D3A00: "add x1, x1, #0xa10",
        0x2518D3A18: "bl #0x25810a6b0", 0x2518D3AB0: "str wzr, [sp, #0x10]",
        0x2518D3AC0: "bl #0x25810a750", 0x2518D3AD0: "bl #0x25810a750",
    }
    for addr, expected in anchors.items():
        assert insns[addr] == expected, (hex(addr), insns[addr])
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for addr, name in {"0x25810a700": "_CFDictionaryGetInt64Ranged", "0x25810a680": "_CFDictionaryCopyCString",
                       "0x25810a6f0": "_CFDictionaryGetInt64", "0x25810a6b0": "_CFDictionaryGetData",
                       "0x25810a750": "_CFDictionaryRemoveValue"}.items():
        assert f"{addr}: {name}\n" in stubs
    print(f"       dictionary audit: strings={len(ROWS)}, slices={count}, anchors={len(anchors)}, slide=v5")


if __name__ == "__main__":
    check()
