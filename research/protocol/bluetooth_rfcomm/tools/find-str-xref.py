#!/usr/bin/env python3
"""在 bluetoothd 的 __TEXT 里找引用某个 VM 地址（字符串/常量）的 adrp+add 指令对。

只用于定位"哪段代码引用了这条字符串"，属于阅读辅助：
命中地址若落在已抽样函数内，用 `readable/` 的 C 复核；不落在任何已抽样函数内则按非抽样处理。

用法：python3 tools/find-str-xref.py 0x100b46435
"""
import json
import os
import struct
import sys

BASE = 0x100000000
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BIN = os.path.join(ROOT, "source", "firmware", "bluetoothd")


def text_range():
    data = open(BIN, "rb").read()
    magic, _, _, _, _ = struct.unpack_from("<Iiiii", data, 0)
    assert magic == 0xFEEDFACF
    ncmds = struct.unpack_from("<I", data, 16)[0]
    off = 32
    for _ in range(ncmds):
        cmd, size = struct.unpack_from("<II", data, off)
        if cmd == 0x19:                              # LC_SEGMENT_64
            segname = data[off + 8:off + 24].rstrip(b"\x00").decode()
            vmaddr, vmsize, fileoff, filesize = struct.unpack_from("<QQQQ", data, off + 24)
            if segname == "__TEXT":
                return vmaddr, fileoff, filesize
        off += size
    raise SystemExit("__TEXT not found")


def main(addr):
    vm, foff, fsize = text_range()
    data = open(BIN, "rb").read()[foff:foff + fsize]
    hits = []
    for i in range(0, len(data) - 12, 4):
        w = struct.unpack_from("<I", data, i)[0]
        if (w & 0x9F000000) != 0x90000000:            # adrp
            continue
        immhi = (w >> 5) & 0x7FFFF
        immlo = (w >> 29) & 0x3
        imm = (immhi << 2) | immlo
        if imm & (1 << 20):
            imm -= 1 << 21
        pc = vm + i
        page = (pc & ~0xFFF) + (imm << 12)
        for j in range(4, 32, 4):                     # 后续窗口内找 add
            w2 = struct.unpack_from("<I", data, i + j)[0]
            if (w2 & 0x7F800000) == 0x11000000 and ((w2 >> 22) & 3) == 0:  # ADD imm, 64-bit
                tgt = page + ((w2 >> 10) & 0xFFF)
                if tgt == addr:
                    hits.append(pc)
                break
    print("引用 %#x 的候选指令地址：%s" % (addr, ", ".join("%#x" % h for h in hits) or "（未找到）"))
    idx = os.path.join(ROOT, "function-index.json")
    if os.path.exists(idx) and hits:
        funcs = json.load(open(idx, encoding="utf-8"))
        entries = funcs["functions"] if isinstance(funcs, dict) and "functions" in funcs else funcs
        for h in hits:
            owner = [f for f in entries if int(str(f.get("address")), 16) <= h <= int(str(f.get("slice_end") or f.get("end")), 16)]
            print("  %#x -> %s" % (h, ("函数 %s" % owner[0]["address"]) if owner else "非抽样函数"))


if __name__ == "__main__":
    main(int(sys.argv[1], 16))
