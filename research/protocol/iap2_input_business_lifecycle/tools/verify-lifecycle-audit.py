#!/usr/bin/env python3
"""C16: original-image/disassembly and bounded operand regression, not emulation."""
from pathlib import Path
import hashlib
import re
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = Path(__file__).resolve().parents[1]
SHA = "2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe"


def main():
    blob = (ROOT / "source/firmware/accessoryd").read_bytes()
    assert hashlib.sha256(blob).hexdigest() == SHA
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)

    def dis(start, end):
        code = blob[start - 0x100000000:end - 0x100000000]
        ins = list(md.disasm(code, start))
        assert sum(i.size for i in ins) == len(code)
        return {i.address: (i.mnemonic, i.op_str) for i in ins}

    all_ins = {}
    funcs = [0x10003021c, 0x1000302a0, 0x100103210, 0x100006f8c,
             0x100006e24, 0x100034db4, 0x100034e68, 0x100050c2c,
             0x10017527c, 0x1001499f0, 0x100051054, 0x100005138]
    for start in funcs:
        txt = (ROOT / f"source/asm/accessoryd/f_{start:x}.s").read_text(encoding="utf-8")
        rows = re.findall(r"^(0x[0-9a-f]+):[ \t]*(\S+)[ \t]*([^\n]*)", txt, re.M)
        expected = {int(a, 16): (m, o.strip()) for a, m, o in rows}
        actual = dis(start, max(expected) + 4)
        assert actual == expected, f"full slice mismatch: {start:x}"
        all_ins.update(actual)

    # This helper was cited previously without a local slice; verify original bytes directly.
    raw = bytes.fromhex("080040790805c05a1f150071e0279f1ac0035fd6")
    assert blob[0x67f3c:0x67f50] == raw
    all_ins.update(dis(0x100067df0, 0x100067e74))
    all_ins.update(dis(0x100067f30, 0x100067f50))
    anchors = {
        0x1000302d4: ("ldrb", "w1, [x19, #0xbe]"),
        0x1000302d8: ("ldrb", "w2, [x19, #0xbc]"),
        0x1000302e0: ("mov", "x3, #0"),
        0x1000302e4: ("mov", "w4, #0"),
        0x1000302e8: ("mov", "w5, #0"),
        0x1000302ec: ("bl", "#0x100006f8c"),
        0x100006f98: ("mov", "x3, x2"),
        0x100006f9c: ("mov", "x2, x1"),
        0x100006fa0: ("mov", "w1, #0x40"),
        0x100006ed0: ("strb", "w26, [x8, #4]"),
        0x100006ed4: ("strb", "w25, [x8, #5]"),
        0x100006ed8: ("strb", "w24, [x8, #6]"),
        0x100006edc: ("strb", "w22, [x8, #7]"),
        0x100034e3c: ("mov", "w1, #0x1b"),
        0x100034ef0: ("mov", "w1, #0x1c"),
        0x100067f44: ("cmp", "w8, #5"),
        0x100067f48: ("cset", "w0, lo"),
        0x100067f34: ("add", "x0, x0, #4"),
        0x100067df8: ("cmp", "w8, #8"),
        0x100067e24: ("cmp", "w8, #6"),
        0x100067e54: ("cmp", "w8, #5"),
        0x100149bf4: ("tbz", "w0, #0, #0x100149ec0"),
        0x100149d08: ("bl", "#0x100067df0"),
        0x100149d28: ("tbz", "w0, #0, #0x10014a278"),
        0x100149dd4: ("tbz", "w0, #0, #0x100149ea8"),
        0x100050ce0: ("strb", "w8, [x19]"),
        0x100050ce4: ("and", "w0, w23, #1"),
        0x1001755bc: ("bl", "#0x100050c2c"),
        0x1001755c0: ("cbz", "w0, #0x100175908"),
        0x1001755e0: ("mov", "w1, #0x5204"),
        0x100175908: ("mov", "w22, #0"),
    }
    for addr, expected in anchors.items():
        assert all_ins[addr] == expected, f"anchor {addr:x}: {all_ins[addr]}"
    # Jump table confirms parameter1..5 branch mapping, independent of prose.
    targets = [0x1001753c0, 0x100175450, 0x100175420,
               0x100175438, 0x100175408, 0x100175468]
    for i, target in enumerate(targets):
        off = 0x18e40 + i * 4
        assert 0x1001753b4 + int.from_bytes(blob[off:off+4], "little", signed=True) == target

    # Bounded arithmetic consequences, NOT whole-handler execution.
    for plen in range(0, 65536):
        helper_true = plen < 5
        generic_valid = plen >= 4
        assert (generic_valid and helper_true) == (plen == 4)
    print(f"C16: SHA; {len(funcs)} full slices; {len(anchors)} anchors; 6 jump entries; empty-TLV boundary OK")


if __name__ == "__main__":
    main()
