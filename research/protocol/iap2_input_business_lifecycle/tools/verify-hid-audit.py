#!/usr/bin/env python3
"""C17: fixed-image HID dataflow anchors; not native execution or interoperability."""
from pathlib import Path
import hashlib
import re
import struct
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = Path(__file__).resolve().parents[1]


def main():
    blob = (ROOT / 'source/firmware/accessoryd').read_bytes()
    assert hashlib.sha256(blob).hexdigest() == '2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe'
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)

    def dis(a, z):
        raw = blob[a - 0x100000000:z - 0x100000000]
        ins = list(md.disasm(raw, a))
        assert sum(i.size for i in ins) == len(raw)
        return {i.address: (i.mnemonic, i.op_str) for i in ins}

    all_ins = {}
    funcs = [0x100130444, 0x100130cf0, 0x10013101c, 0x1001313dc, 0x1000b2dbc]
    for a in funcs:
        txt = (ROOT / f'source/asm/accessoryd/f_{a:x}.s').read_text(encoding='utf-8')
        rows = re.findall(r'^(0x[0-9a-f]+):[ \t]*(\S+)[ \t]*([^\n]*)', txt, re.M)
        expected = {int(p, 16): (m, o.strip()) for p, m, o in rows}
        actual = dis(a, max(expected) + 4)
        assert actual == expected
        all_ins.update(actual)
    for a, z in [(0x1000165c0, 0x1000165d8), (0x100043c64, 0x100043cc8),
                 (0x1000438d0, 0x100043a98), (0x1001a6ba0, 0x1001a6bb8)]:
        all_ins.update(dis(a, z))
    anchors = {
        0x1001305d0: ('sturh', 'w0, [x29, #-0x6a]'),
        0x1001305ac: ('sturh', 'w0, [x29, #-0x6c]'),
        0x10013075c: ('sub', 'x2, x29, #0x6a'),
        0x100130764: ('mov', 'w1, #8'),
        0x100130768: ('bl', '#0x1001a17a0'),
        0x10013076c: ('str', 'x0, [sp, #0x30]'),
        0x100130770: ('sub', 'x2, x29, #0x6c'),
        0x100130778: ('mov', 'w1, #8'),
        0x10013077c: ('bl', '#0x1001a17a0'),
        0x100130780: ('str', 'x0, [sp, #0x28]'),
        0x1001308d4: ('ldr', 'x2, [sp, #0x30]'),
        0x1001308d8: ('bl', '#0x1001a15e0'),
        0x1001308e4: ('ldr', 'x2, [sp, #0x28]'),
        0x1001308e8: ('bl', '#0x1001a15e0'),
        0x1000165c4: ('mov', 'w1, #9'),
        0x1000165d4: ('b', '#0x1001a17a0'),
        0x100131180: ('mov', 'x22, x0'),
        0x10013111c: ('mov', 'x21, x0'),
        0x100131290: ('strh', 'w23, [sp, #0x58]'),
        0x100131294: ('strb', 'w22, [sp, #0x5a]'),
        0x100131298: ('strb', 'w21, [sp, #0x5b]'),
        0x10013129c: ('stp', 'x20, x19, [sp, #0x48]'),
        0x1001312a0: ('add', 'x0, sp, #0x28'),
        0x100043c78: ('ldrh', 'w1, [x0, #0x30]'),
        0x100043c7c: ('ldrb', 'w2, [x0, #0x32]'),
        0x100043c80: ('ldrb', 'w3, [x0, #0x33]'),
        0x100043c88: ('ldr', 'x4, [x19, #0x28]'),
        0x100043c8c: ('bl', '#0x1000b2dbc'),
        0x1000b2ddc: ('mov', 'x21, x2'),
        0x1000b2dd8: ('mov', 'x20, x3'),
        0x1000b2e04: ('mov', 'x4, x21'),
        0x1000b2e08: ('mov', 'x5, x20'),
        0x1000b2e10: ('bl', '#0x1001a6ba0'),
        0x1001a6ba0: ('adrp', 'x1, #0x100238000'),
        0x1001a6ba4: ('ldr', 'x1, [x1, #0x108]'),
        0x1001315dc: ('strb', 'wzr, [x21, #0x18]'),
        0x1001315e0: ('strb', 'wzr, [x21, #0x1a]'),
        0x10013162c: ('mov', 'w0, #0'),
        0x1000439a4: ('ldr', 'w9, [x8]'),
        0x1000439ac: ('ldr', 'w9, [x8, #0x10]'),
        0x1000439b0: ('cmp', 'w9, #0xa'),
        0x1000439b8: ('ldrh', 'w8, [x8, #4]'),
    }
    for a, expected in anchors.items():
        assert all_ins[a] == expected, (hex(a), all_ins[a], expected)
    for table, base, targets in [
        (0x18774, 0x10013052c, [0x100130538, 0x1001305c8, 0x1001305a4, 0x1001305b8, 0x100130560]),
        (0x18788, 0x1001310d8, [0x1001310e4, 0x100131170, 0x10013110c, 0x10013112c]),
    ]:
        for n, target in enumerate(targets):
            assert base + struct.unpack_from('<i', blob, table + 4*n)[0] == target
    # Fixed build's chained selector reference; not a general pointer decoder.
    assert struct.unpack_from('<Q', blob, 0x238108)[0] == 0x80000001c1cb9
    selector = b'getReportResponse:componentID:reportType:reportID:report:\0'
    assert blob[0x1c1cb9:0x1c1cb9 + len(selector)] == selector
    print(f'C17: SHA; {len(funcs)} full slices; {len(anchors)} anchors; 9 jump entries; selector OK (static only)')


if __name__ == '__main__':
    main()
