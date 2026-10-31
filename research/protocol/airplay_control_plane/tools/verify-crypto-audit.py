"""核查 analysis/13 的新切片、关键原始指令与结构模型；不执行完整固件。"""
from pathlib import Path
import hashlib
import importlib.util
import json
import re

import capstone

ROOT = Path(__file__).resolve().parents[1]
META = ROOT / "source/metadata/CoreUtils"
AUDIT = ROOT / "source/asm-audit/CoreUtils"
BINARY = (ROOT / "source/firmware/CoreUtils").read_bytes()
SEGMENTS = json.loads((META / "segments.json").read_text(encoding="utf-8"))


def raw_at(address, size):
    for segment in SEGMENTS:
        offset = address - segment["vmaddr"]
        if 0 <= offset and offset + size <= segment["filesize"]:
            start = segment["fileoff"] + offset
            return BINARY[start:start + size]
    raise AssertionError("address outside mapped file")


def instructions(path):
    result = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        match = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
        if match:
            result[int(match[1], 16)] = " ".join(match[2].split())
    return result


def check():
    index = json.loads((AUDIT / "index.json").read_text(encoding="utf-8"))
    assert hashlib.sha256(BINARY).hexdigest() == index["source_sha256"]
    symbols = {entry["name"]: entry["addr"] for entry in json.loads((META / "symbols.json").read_text(encoding="utf-8"))}
    disassembler = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    all_insns = {}
    assert index["count"] == len(index["functions"]) == 9
    for entry in index["functions"]:
        start = int(entry["address"], 16)
        assert symbols[entry["symbol"]] == start
        raw = raw_at(start, entry["size"])
        assert raw == (AUDIT / entry["bin"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == entry["raw_sha256"]
        decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
                   for i in disassembler.disasm(raw, start)}
        assert decoded == instructions(AUDIT / entry["asm"])
        all_insns.update(decoded)
    for name in ("f_18be49968.s", "f_18be4d5fc.s", "f_18bf1adbc.s"):
        all_insns.update(instructions(ROOT / "source/asm/CoreUtils" / name))
    anchors = {
        # AAD: 2 bytes to Poly1305, followed by AAD length increment.
        0x18be49aa4: "mov w2, #2", 0x18be49aa8: "bl #0x18be48df8",
        0x18be49ab4: "str x8, [x22, #0x4138]",
        0x18be4d750: "mov w2, #2", 0x18be4d754: "bl #0x18be48df8",
        0x18be4d760: "str x8, [x21, #0x4688]",
        # Independent read/write nonce slots, each passed directly to init64.
        0x18be499ac: "mov w8, #0x4170", 0x18be49a94: "bl #0x18be4a104",
        0x18be4d664: "mov w8, #0x46c0", 0x18be4d738: "bl #0x18be4a104",
        0x18be49b08: "strb w9, [x26, x8]", 0x18be49b10: "cmp x8, #7",
        0x18be4d828: "strb w10, [x23, x9]", 0x18be4d830: "cmp x9, #7",
        # Nonce words and separate block counter; wrapper nonce length dispatch.
        0x18be4a174: "str xzr, [x0, #0x30]",
        0x18be4a184: "str w8, [x19, #0x38]",
        0x18be4a198: "str w8, [x19, #0x3c]",
        0x18be55f64: "cmp x2, #8", 0x18be55f74: "bl #0x18be4a104",
        0x18be5791c: "cmp x2, #8", 0x18be5792c: "bl #0x18be4a104",
        # Tag mismatch is distinct from length mismatch.
        0x18be4b488: "mov w8, #-0x1a62",
        0x18be49c84: "mov w27, #-0x1a6a",
        0x18be49a3c: "b.hi #0x18be49c10",
        # Configure pointer slots: x23=input x2, x21=input x4.
        0x18bf1ade4: "mov x23, x2", 0x18bf1addc: "mov x21, x4",
        0x18bf1ae34: "ldp q0, q1, [x23]", 0x18bf1ae3c: "str q0, [x0, #0x4150]",
        0x18bf1ae4c: "ldp q0, q1, [x21]", 0x18bf1ae54: "str q0, [x0, #0x46a0]",
    }
    for addr, expected in anchors.items():
        assert all_insns.get(addr) == expected, (hex(addr), all_insns.get(addr), expected)
    assert raw_at(0x18bf711b4, 64) == bytes(64)
    assert raw_at(0x18bf72090, 16) == b"expand 32-byte k"
    spec = importlib.util.spec_from_file_location("record_layout", ROOT / "reference-impl/record_layout.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    module.self_test()
    print("crypto audit: 9 raw slices + disassembly, %d anchors, constants and layout tests OK" % len(anchors))


if __name__ == "__main__":
    check()
