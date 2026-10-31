#!/usr/bin/env python3
"""C10: fixed-image ABI/header audit; no crypto, full CPU or network execution.

Requires Capstone 5.0.7. Re-disassembles five existing slices, checks exact
anchors/imports/labels, then interprets MOV argument windows and the local
post-UpTicksToMilliseconds clamp. Mock pointer names are not firmware addresses.
"""
import hashlib
import json
from pathlib import Path
import re
import sys

from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").is_file()
)
SHA = "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f"
STARTS = (0x2519b508c, 0x2519bfecc, 0x2519bffc8, 0x2519b0014, 0x251b43fcc)


def require(condition, message):
    if not condition:
        raise ValueError(message)


def main():
    blob = (ROOT / "source/firmware/AirPlaySender").read_bytes()
    require(hashlib.sha256(blob).hexdigest() == SHA, "fixed Sender SHA mismatch")
    segments = json.loads((ROOT / "source/metadata/segments.json").read_text())

    def at(va, size):
        matches = [s for s in segments if s["vmaddr"] <= va and
                   va + size <= s["vmaddr"] + s["filesize"]]
        require(len(matches) == 1, f"ambiguous/missing mapping {va:x}")
        s = matches[0]
        off = s["fileoff"] + va - s["vmaddr"]
        return blob[off:off + size]

    cs = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    code = {}
    for start in STARTS:
        stem = ROOT / f"source/asm/airplaysender/f_{start:x}"
        raw = stem.with_suffix(".bin").read_bytes()
        require(raw == at(start, len(raw)), f"slice mismatch {start:x}")
        decoded = {i.address: (i.mnemonic, i.op_str) for i in cs.disasm(raw, start)}
        require(len(decoded) * 4 == len(raw), f"incomplete disassembly {start:x}")
        saved = {}
        for line in stem.with_suffix(".s").read_text(encoding="utf-8").splitlines():
            m = re.fullmatch(r"0x([0-9a-f]+):\s+(\S+)\s*(.*)", line)
            if m:
                saved[int(m[1], 16)] = (m[2], m[3].strip())
        require(saved == decoded, f"saved assembly != raw re-disassembly {start:x}")
        code.update(decoded)

    anchors = {
        0x2519b50c0: ("cbz", "x8, #0x2519b5280"),
        0x2519b5104: ("ldp", "x8, x22, [sp, #0x18]"),
        0x2519b5108: ("cmp", "x22, x8"),
        0x2519b510c: ("b.ne", "#0x2519b52b0"),
        0x2519b5110: ("ldr", "x1, [x20, #0x1a0]"),
        0x2519b5144: ("ldp", "x26, x25, [sp, #0x30]"),
        0x2519b5148: ("ldr", "x23, [sp, #0x28]"),
        0x2519b519c: ("str", "x27, [sp]"),
        0x2519b51c0: ("blraa", "x9, x8"),
        0x2519b51fc: ("bl", "#0x25810ac90"),
        0x2519b5204: ("ldr", "x1, [sp, #0x10]"),
        0x2519b5208: ("mov", "x0, x19"),
        0x2519b5214: ("bl", "#0x25810eab0"),
        0x2519b52c4: ("mov", "w22, #-0x4178"),
        0x2519bff18: ("bl", "#0x25810a1a0"),
        0x2519bff34: ("mov", "w4, #0x1f"),
        0x2519bff38: ("mov", "x5, x24"),
        0x2519bff3c: ("mov", "x6, x20"),
        0x2519bff5c: ("mov", "w4, #0x20"),
        0x2519bff60: ("mov", "x5, x22"),
        0x2519bff64: ("mov", "x6, x21"),
        0x2519c0018: ("mov", "x1, x21"),
        0x2519c001c: ("bl", "#0x25810e760"),
        0x2519c0028: ("mov", "x1, x21"),
        0x2519c002c: ("bl", "#0x25810e790"),
        0x2519c0038: ("bl", "#0x25810e780"),
        0x2519c00ac: ("blraa", "x9, x8"),
        0x2519b00b4: ("ldr", "x8, [x20, #0x3a8]"),
        0x2519b00b8: ("str", "x8, [sp, #0x38]"),
        0x2519b0424: ("str", "x21, [sp, #0x40]"),
        0x2519b0cc0: ("ldp", "x9, x8, [sp, #0x38]"),
        0x2519b0cc4: ("add", "x23, x9, x8"),
        0x2519b0e44: ("ldr", "x8, [x20, #0x3a8]"),
        0x2519b0e48: ("add", "x27, x8, x0"),
        0x2519b0e4c: ("add", "x23, x27, x23"),
        0x2519b0e88: ("str", "w23, [x0]"),
        0x2519b0f9c: ("stp", "wzr, w27, [x25, #0x18]"),
        0x2519b10b0: ("bl", "#0x25810bd90"),
        0x2519b10b8: ("cmp", "x0, #0x10, lsl #12"),
        0x2519b10bc: ("b.lo", "#0x2519b1114"),
        0x2519b1110: ("mov", "w28, #0xffff"),
        0x2519b1118: ("strh", "w28, [x22]"),
        0x2519b1124: ("cmp", "x19, #0x11"),
        0x2519b1164: ("bl", "#0x2519cf9e4"),
        0x2519b1168: ("cbnz", "w0, #0x2519b1490"),
        0x2519b12f0: ("bl", "#0x2519b508c"),
        0x2519b1308: ("bl", "#0x25810eab0"),
        0x2519b11cc: ("add", "w8, w8, #1"),
        0x2519b11d0: ("str", "w8, [x20, #0x470]"),
        0x2519b0844: ("str", "wzr, [x20, #0x470]"),
        0x2519b07a8: ("ldrb", "w8, [x20, #0x3c5]"),
        0x2519b07ac: ("cmp", "w8, #0"),
        0x2519b07b0: ("mov", "w8, #5"),
        0x2519b07b4: ("mov", "w9, #2"),
        0x2519b07b8: ("csel", "w8, w9, w8, eq"),
        0x2519b07bc: ("strb", "w8, [x0, #4]"),
        0x2519b07c4: ("strb", "w8, [x0, #5]"),
        0x2519b07d4: ("ucvtf", "s0, x0"),
        0x2519b07e0: ("str", "s0, [x21, #0x7c]"),
        0x2519b0e00: ("add", "x4, sp, #0x88"),
        0x2519b0e38: ("ldr", "x0, [sp, #0x88]"),
        0x2519b0e40: ("bl", "#0x25810aca0"),
        0x2519b0e8c: ("strb", "wzr, [x0, #4]"),
        0x2519b116c: ("ldr", "x2, [sp, #0x88]"),
        0x2519b1174: ("cbnz", "x2, #0x2519b12e8"),
    }
    for va, expected in anchors.items():
        require(code.get(va) == expected, f"anchor {va:x}: {code.get(va)} != {expected}")

    for va, label in ((0x251bdf641, b"%s%llu"), (0x251bdf648, b"DataStream-Salt"),
                      (0x251bdf658, b"DataStream-Input-Encryption-Key"),
                      (0x251bdf6a9, b"DataStream-Output-Encryption-Key")):
        require(at(va, len(label) + 1) == label + b"\0", f"label bytes {va:x}")
    imports = {0x25810eae0: "_CMBlockBufferGetDataPointer", 0x25810ac90: "_CMBlockBufferCreateWithMemoryBlock",
               0x25810eab0: "_CMBlockBufferAppendBufferReference", 0x25810a1a0: "_ASPrintF",
               0x25810e760: "_CFDataCreateMutable", 0x25810e790: "_CFDataSetLength",
               0x25810e780: "_CFDataGetMutableBytePtr", 0x25810bd90: "_UpTicksToMilliseconds",
               0x25810aca0: "_CMBlockBufferGetDataLength"}
    stub_text = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for va, name in imports.items():
        require(re.search(rf"(?m)^0x{va:x}: {re.escape(name)}$", stub_text), f"import {name}")

    def moves(start, end, regs):
        regs = dict(regs)
        for va in range(start, end, 4):
            op, args = code[va]
            require(op == "mov", f"unsupported argument opcode {va:x}")
            dst, src = args.split(", ")
            regs[dst] = int(src[1:], 0) if src.startswith("#") else regs[src]
        return regs

    args = moves(0x2519b51a0, 0x2519b51c0,
                 {"x24": "cryptor", "x25": "header", "x26": "headerLen", "x23": "payload",
                  "x22": "payloadLen", "x21": "extra"})
    require([args[f"x{i}"] for i in range(8)] ==
            ["cryptor", "header", "headerLen", "payload", "payloadLen", "payload", "payloadLen", "extra"],
            "wrapper alias ABI")
    derived = moves(0x2519c0090, 0x2519c00ac,
                    {"x27": "provider", "x25": "salt", "x24": "saltLen", "x23": "info",
                     "x22": "infoLen", "x21": "outLen", "x26": "outBytes"})
    require([derived[f"x{i}"] for i in range(7)] ==
            ["provider", "salt", "saltLen", "info", "infoLen", "outLen", "outBytes"], "provider ABI")

    # Local branch after time conversion, not an implementation of UpTicksToMilliseconds.
    imm = re.fullmatch(r"x0, #(0x[0-9a-f]+), lsl #(\d+)", code[0x2519b10b8][1])
    threshold = int(imm[1], 16) << int(imm[2])
    for converted_ms, expected in ((0, 0), (4095, 4095), (4096, 4096), (65534, 65534),
                                   (65535, 65535), (65536, 65535), (2**64 - 1, 65535)):
        w28 = converted_ms if converted_ms < threshold else int(code[0x2519b1110][1].split("#")[1], 16)
        require(w28 & 0xffff == expected, f"interval clamp {converted_ms}")

    targets = []
    for va in range(0x251b4417c, 0x251b441f4, 12):
        require(code[va + 4] == ("fcvt", "s0, d0"), f"float conversion {va:x}")
        op, operands = code[va + 8]
        require(op == "str", f"float store {va:x}")
        m = re.fullmatch(r"s0, \[x22, #(0x[0-9a-f]+)\]", operands)
        require(m is not None, f"float target {va:x}")
        targets.append(int(m[1], 16))
    require(targets == [0x10, 0x14, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c], "sparse float offsets")
    # Interpret just the CMP/MOV/CSEL/STRB window; no allocation or sender run.
    for flag in range(256):
        zero = flag == 0
        w8 = int(code[0x2519b07b0][1].split('#')[1], 0)
        w9 = int(code[0x2519b07b4][1].split('#')[1], 0)
        record_type = (w9 if zero else w8) & 0xff
        require(record_type == (2 if flag == 0 else 5), f"stats type {flag}")
    print(f"C10 PASS: fixed SHA; 5 full slices; {len(anchors)} anchors; 4 labels; {len(imports)} imports; "
          "2 MOV ABI windows; 7 converted-ms boundaries; 10 sparse float stores; 256 stats flag cases")
    print("Scope: static/local evidence only; crypto, time conversion and network interoperability NOT executed.")


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, KeyError) as exc:
        print(f"C10 FAIL: {exc}")
        sys.exit(1)
