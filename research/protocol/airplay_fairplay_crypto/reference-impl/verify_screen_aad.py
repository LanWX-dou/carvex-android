"""固定镜像/原切片/指令锚点与局部分段解释；不证明线上密码互操作。"""
from pathlib import Path
import hashlib
import json
import re

import capstone
import fairplay_crypto as fc
from screen_record_layout import split_chacha_record

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").is_file()
)
CORE_SHA = "3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083"
RECEIVER_SHA = "ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a"


def load(image, directory, source, metadata, expected, selected=None):
    binary = (source / "source/firmware" / image).read_bytes()
    assert hashlib.sha256(binary).hexdigest() == expected
    segments = json.loads((source / "source/metadata" / metadata / "segments.json").read_text(encoding="utf-8"))
    base = ROOT / "source" / directory / image
    index = json.loads((base / "index.json").read_text(encoding="utf-8"))
    assert index["source_sha256"] == expected
    instructions = {}
    count = 0
    for entry in index["functions"]:
        start, end = int(entry["address"], 16), int(entry["end"], 16)
        if selected is not None and start not in selected:
            continue
        seg = next(s for s in segments if s["vmaddr"] <= start < end <= s["vmaddr"] + s["filesize"])
        offset = seg["fileoff"] + start - seg["vmaddr"]
        raw = binary[offset:offset + end - start]
        assert raw == (base / entry["bin"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == entry["raw_sha256"]
        decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
                   for i in capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM).disasm(raw, start)}
        recorded = {}
        for line in (base / entry["asm"]).read_text(encoding="utf-8").splitlines():
            m = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
            if m:
                recorded[int(m[1], 16)] = " ".join(m[2].split())
        assert decoded == recorded
        instructions.update(decoded)
        count += 1
    assert count == (len(selected) if selected is not None else index["count"])
    return instructions, count


def split_slice(insns, n, e, flag4):
    """有限解释ab30..ab74，内存load和外部状态用显式输入；返回第一段长度/尾偏移。"""
    pc, regs, lengths, greater = 0x25185AB30, {}, {}, False
    for _ in range(40):
        op = insns[pc]
        target = pc + 4
        if op == "ldr w8, [x21]": regs["w8"] = n
        elif op == "ldr w9, [x21, #0x1c]": regs["w9"] = e
        elif op == "stp w9, w8, [sp, #0xc8]": lengths = {"first": regs["w8"], "tail": regs["w9"]}
        elif op == "ldrb w10, [x21, #5]": regs["w10"] = 16 if flag4 else 0
        elif op == "tbnz w10, #4, #0x25185ab68":
            if regs["w10"] & 16: target = 0x25185AB68
        elif op in ("ldr x10, [x21, #0x150]", "cmp x10, #0", "cset w23, eq", "mov w23, #1"):
            pass  # w23 does not affect this slice's segment boundaries
        elif op == "cbz w9, #0x25185ab70":
            if not regs["w9"]: target = 0x25185AB70
        elif op == "cbnz w9, #0x25185ab54":
            if regs["w9"]: target = 0x25185AB54
        elif op == "subs w8, w8, w9":
            greater = regs["w8"] > regs["w9"]
            regs["w8"] = (regs["w8"] - regs["w9"]) & 0xffffffff
        elif op == "b.ls #0x25185af74":
            if not greater: return None
        elif op == "str w8, [sp, #0xcc]": lengths["first"] = regs["w8"]
        elif op == "add x25, x19, x8": regs["tail_offset"] = regs["w8"]
        elif op == "b #0x25185ab74": target = 0x25185AB74
        elif op == "mov x25, #0": regs["tail_offset"] = None
        elif op == "add x2, sp, #0xcc": return lengths["first"], regs["tail_offset"]
        else: raise AssertionError((hex(pc), op))
        pc = target
    raise AssertionError("slice did not terminate")


def check():
    receiver, n1 = load("AirPlayReceiver", "asm-audit", ROOT, "receiver", RECEIVER_SHA)
    core, n2 = load("CoreUtils", "asm-audit", ROOT.parent / "airplay_control_plane", "CoreUtils", CORE_SHA)
    old, n3 = load("AirPlayReceiver", "asm", ROOT, "receiver", RECEIVER_SHA,
                   {0x25185BA2C, 0x251859A60, 0x251859B8C})
    insns = receiver | core | old
    anchors = {
        0x251859E2C: "add x0, x22, #0xe8", 0x251859E34: "bl #0x25810b910",
        0x18BF1CFD8: "bl #0x18bf1c660", 0x18BF1CFE4: "str w20, [x8, #4]",
        0x18BF1C708: "adrp x16, #0x18bf1c000", 0x18BF1C70C: "add x16, x16, #0x798",
        0x18BF1C714: "str x16, [x20, #0x18]",
        0x18BF1C7EC: "mov x26, x3", 0x18BF1C7F0: "mov x24, x2", 0x18BF1C7F4: "mov x23, x1",
        0x18BF1C848: "mov x1, x26", 0x18BF1C84C: "mov x2, x24",
        0x18BF1C8B0: "sub x24, x24, x0", 0x18BF1C8B4: "add x20, x0, x20",
        0x18BF1C8CC: "cmp x20, x23", 0x18BF1C8D4: "csel w0, w8, wzr, lo",
        0x25185A108: "ldr x0, [x24, #0xe8]", 0x25185A10C: "ldr x8, [x0, #0x18]",
        0x25185A114: "mov w1, #0x80", 0x25185A118: "mov w2, #0x80", 0x25185A11C: "mov x3, x24",
        0x25185A128: "blraaz x8", 0x25185A150: "ldr w22, [x24]",
        0x25185A434: "b #0x25185ab30",
        0x25185AB80: "bl #0x25185ba2c", 0x25185AB88: "cbnz w0, #0x25185af24",
        0x25185ABB8: "cbnz w0, #0x25185af34", 0x25185ABBC: "cbz x25, #0x25185ac04",
        0x25185ABCC: "bl #0x25185ba2c", 0x25185ABD4: "cbnz w0, #0x25185afa0",
        0x25185BA64: "ldrb w8, [x23, #4]", 0x25185BA68: "cbnz w8, #0x25185bb44",
        0x25185BA70: "ldrb w8, [x23, #0x160]", 0x25185BA74: "cbz w8, #0x25185bb18",
        0x25185BA78: "subs w20, w20, #0x10", 0x25185BA7C: "b.lo #0x25185bb5c",
        0x25185BA98: "mov x1, x23", 0x25185BA9C: "mov w2, #0x80", 0x25185BAA0: "bl #0x25810be70",
        0x25185BAD8: "cbnz w0, #0x25185bb64", 0x25185BAE4: "b.ne #0x25185bb84",
        0x25185BAF8: "strb w10, [x21, x8]", 0x25185BB18: "ldrb w8, [x23, #0x2c0]",
        0x251859AA0: "ldrb w8, [x19, #0xb9]", 0x251859AA8: "ldrb w8, [x19, #0xb8]",
        0x251859B18: "add x8, x19, #0x160", 0x251859B1C: "mov x9, #-0x130",
        0x251859B40: "strb w8, [x19, #0x160]",
        0x251859BC0: "ldrb w8, [x19, #0xb9]", 0x251859BC8: "ldrb w8, [x19, #0xb8]",
        0x251859C48: "strb wzr, [x19, #0x2c0]", 0x251859C64: "cset w8, eq",
        0x251859C68: "strb w8, [x19, #0x2c0]",
    }
    for addr, expected in anchors.items():
        assert insns[addr] == expected, (hex(addr), insns[addr])
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for addr, symbol in {"0x25810b910": "_NetSocket_CreateWithNative",
                         "0x25810ac50": "_CMBaseObjectGetDerivedStorage",
                         "0x25810be70": "_chacha20_poly1305_add_aad"}.items():
        assert f"{addr}: {symbol}\n" in stubs
    cases = 0
    for n in (0, 15, 16, 17, 32, 65, 0xffffffff):
        for e in (0, 1, 15, 16, 17, n, 0xffffffff):
            for flag in (False, True):
                want = None if e and e >= n else (n-e, n-e if e else None)
                assert split_slice(insns, n, e, flag) == want
                cases += 1
    # 独立合成记录：非零头，同AAD两段、纯tag、篡改头/第二段及本地严格拒绝。
    header = bytearray(range(128))
    header[:4] = (33).to_bytes(4, "little")
    header[4] = 0
    header[28:32] = (16).to_bytes(4, "little")
    aad, key, nonce = bytes(header), bytes(range(32)), bytes(8)
    body = fc.chacha20_poly1305_seal(key, nonce, b"x", aad=aad)
    body += fc.chacha20_poly1305_seal(key, fc.next_nonce(nonce), b"", aad=aad)
    record = split_chacha_record(aad, body, max_body=33)
    assert record.aad == aad and tuple(map(len, record.segments)) == (17, 16)
    assert fc.chacha20_poly1305_open(key, nonce, record.segments[0], aad=aad) == b"x"
    nonce = fc.next_nonce(nonce)  # 第一段成功已提交，不因第二段失败而回滚
    assert fc.chacha20_poly1305_open(key, nonce, record.segments[1], aad=aad) == b""
    bad = record.segments[1][:-1] + bytes([record.segments[1][-1] ^ 1])
    assert fc.chacha20_poly1305_open(key, nonce, bad, aad=aad) is None
    assert nonce == (1).to_bytes(8, "little")
    changed = bytearray(aad)
    changed[100] ^= 1
    assert fc.chacha20_poly1305_open(key, bytes(8), record.segments[0], aad=bytes(changed)) is None
    bad_cases = [(aad[:-1], body, 33), (aad, body[:-1], 33), (aad, body+b"x", 34), (aad, body, 32)]
    for off, value in ((4, b"\x01"), (28, (33).to_bytes(4, "little")), (28, (34).to_bytes(4, "little")),
                       (28, (15).to_bytes(4, "little")), (28, (18).to_bytes(4, "little"))):
        h = bytearray(aad)
        h[off:off+len(value)] = value
        bad_cases.append((bytes(h), body, 33))
    for h, b, limit in bad_cases:
        try: split_chacha_record(h, b, max_body=limit)
        except ValueError: pass
        else: raise AssertionError("invalid record accepted")
    single = bytearray(aad)
    single[28:32] = bytes(4)
    assert len(split_chacha_record(bytes(single), body, max_body=33).segments) == 1
    print(f"       screen audit: slices={n1+n2+n3}, anchors={len(anchors)}, split_cases={cases}, rejected={len(bad_cases)}")


if __name__ == "__main__":
    check()
