#!/usr/bin/env python3
"""C18: fixed-image NowPlaying dataflow, not native execution or interoperability."""
from pathlib import Path
import hashlib
import re
import struct
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x100000000
SHA = '2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe'


class Image:
    def __init__(self):
        self.data = (ROOT / 'source/firmware/accessoryd').read_bytes()
        assert hashlib.sha256(self.data).hexdigest() == SHA
        self.md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
        self.segments, self.stubs = [], []
        off = 32
        for _ in range(struct.unpack_from('<I', self.data, 16)[0]):
            cmd, size = struct.unpack_from('<II', self.data, off)
            if cmd == 2:
                self.symtab = struct.unpack_from('<IIII', self.data, off + 8)
            if cmd == 11:
                self.indirect = struct.unpack_from('<II', self.data, off + 56)
            if cmd == 25:
                va, vs, fo, fs = struct.unpack_from('<QQQQ', self.data, off + 24)
                self.segments.append((va, vs, fo, fs))
                for n in range(struct.unpack_from('<I', self.data, off + 64)[0]):
                    at = off + 72 + n * 80
                    name = self.data[at:at+16].split(b'\0')[0]
                    if name == b'__auth_stubs':
                        va, sz = struct.unpack_from('<QQ', self.data, at + 32)
                        idx, stride = struct.unpack_from('<II', self.data, at + 68)
                        self.stubs.append((va, sz, idx, stride))
            off += size

    def offset(self, va, size=1):
        for a, _, fo, fs in self.segments:
            if a <= va and va + size <= a + fs:
                return fo + va - a
        raise AssertionError(f'not file-backed: {va:x}+{size:x}')

    def read(self, va, size):
        p = self.offset(va, size)
        return self.data[p:p+size]

    def dis(self, a, z):
        ins = list(self.md.disasm(self.read(a, z-a), a))
        assert sum(i.size for i in ins) == z-a
        return {i.address: (i.mnemonic, i.op_str) for i in ins}

    def string(self, va):
        p = self.offset(va)
        return self.data[p:self.data.index(0, p)].decode('utf-8')

    def imported(self, va):
        for start, size, index, stride in self.stubs:
            if start <= va < start + size:
                assert (va-start) % stride == 0
                k = index + (va-start)//stride
                symbol = struct.unpack_from('<I', self.data, self.indirect[0]+4*k)[0]
                assert symbol < self.symtab[1]
                si = struct.unpack_from('<I', self.data, self.symtab[0]+16*symbol)[0]
                p = self.symtab[2]+si
                return self.data[p:self.data.index(0, p)].decode()
        raise AssertionError(f'not an import stub: {va:x}')


def main():
    im = Image()
    ins = {}
    funcs = [0x1001499f0, 0x10014a93c, 0x10014aa20]
    for a in funcs:
        txt = (ROOT / f'source/asm/accessoryd/f_{a:x}.s').read_text(encoding='utf-8')
        rows = re.findall(r'^(0x[0-9a-f]+):[ \t]*(\S+)[ \t]*([^\n]*)', txt, re.M)
        expected = {int(p, 16): (m, o.strip()) for p, m, o in rows}
        actual = im.dis(a, max(expected)+4)
        assert actual == expected
        ins.update(actual)
    ins.update(im.dis(0x10014995c, 0x1001499f0))
    for a, z in [(0x100081c08, 0x100081d50), (0x100081e20, 0x100081e3c),
                 (0x10008f35c, 0x10008f3b8), (0x10008f3fc, 0x10008f458),
                 (0x100031a20, 0x100031ad4), (0x1000815ac, 0x100081608),
                 (0x10008fbd0, 0x10008fc70), (0x10008fcf0, 0x10008fd64)]:
        ins.update(im.dis(a, z))
    anchors = {
        0x100149b68: ('cmp', 'w27, #2'),
        0x100149b70: ('cmp', 'w27, #1'),
        0x100149b74: ('b.eq', '#0x100149c28'),
        0x100149b78: ('cbnz', 'w27, #0x100149e08'),
        0x100149bf8: ('mov', 'w1, w27'),
        0x100149bfc: ('mov', 'x0, x22'),
        0x100149c00: ('bl', '#0x1001a13f0'),
        0x100149d2c: ('mov', 'w1, w28'),
        0x100149d30: ('mov', 'x0, x21'),
        0x100149d34: ('bl', '#0x1001a13f0'),
        0x100149f60: ('mov', 'x0, x27'),
        0x100149f64: ('bl', '#0x10014995c'),
        0x100149f74: ('str', 'x22, [x27, #8]'),
        0x100149f8c: ('str', 'x21, [x27, #0x10]'),
        0x10014a00c: ('ldr', 'x0, [x27, #8]'),
        0x10014a010: ('bl', '#0x1001a1460'),
        0x10014a01c: ('stur', 'x0, [sp, #0x54]'),
        0x10014a024: ('adrp', 'x3, #0x1001f0000'),
        0x10014a028: ('add', 'x3, x3, #0x7af'),
        0x10014a064: ('ldr', 'x0, [x27, #0x10]'),
        0x10014a068: ('bl', '#0x1001a1460'),
        0x10014a074: ('stur', 'x0, [sp, #0x54]'),
        0x10014a07c: ('adrp', 'x3, #0x1001f0000'),
        0x10014a080: ('add', 'x3, x3, #0x7c3'),
        0x100149974: ('ldr', 'x0, [x0, #8]'),
        0x100149990: ('bl', '#0x100031a20'),
        0x100149998: ('bl', '#0x1000815ac'),
        0x1001499ac: ('ldr', 'x0, [x19, #0x10]'),
        0x1001499e0: ('b', '#0x100031a20'),
        0x10014a9c8: ('bl', '#0x10014995c'),
        0x10014a9e8: ('str', 'xzr, [x19, #8]'),
        0x10014a9f8: ('str', 'xzr, [x19, #0x10]'),
        0x100031aa0: ('bl', '#0x1001a2120'),
        0x1000815b0: ('ldr', 'x8, [x0, #0x10]'),
        0x1000815c8: ('ldr', 'x19, [x0, #8]'),
        0x1000815e0: ('mov', 'w3, #0x1a'),
        0x1000815e4: ('bl', '#0x1001a1410'),
        0x10014a41c: ('mov', 'w1, #0xf'),
        0x10014a42c: ('mov', 'w1, #0x11'),
        0x10014a480: ('add', 'x0, x0, #0xc8'),
        0x10014a484: ('bl', '#0x100031a20'),
        0x100081c0c: ('add', 'x8, x8, #0x9b0'),
        0x100081c14: ('b', '#0x10008fc20'),
        0x100081c1c: ('add', 'x8, x8, #0x9b8'),
        0x100081c24: ('b', '#0x10008fc20'),
        0x100081c2c: ('add', 'x8, x8, #0x9c0'),
        0x100081c34: ('b', '#0x10008fc20'),
        0x100081ccc: ('add', 'x8, x8, #0x9c8'),
        0x100081cd4: ('b', '#0x10008fbd0'),
        0x10008fbf8: ('bl', '#0x1001a4800'),
        0x10008fc48: ('bl', '#0x1001a9520'),
        0x10008fd1c: ('adrp', 'x0, #0x100225000'),
        0x10008fd20: ('add', 'x0, x0, #0xd18'),
        0x10008fd24: ('bl', '#0x1001a1d90'),
        0x10014ab20: ('mov', 'x24, x0'),
        0x10014ab38: ('mov', 'x23, x0'),
        0x10014ab50: ('mov', 'x21, x0'),
        0x10014aba4: ('add', 'x16, x16, #0xd40'),
        0x10014abb8: ('str', 'w24, [sp, #0x58]'),
        0x10014abf8: ('add', 'x16, x16, #0xd48'),
        0x10014ac0c: ('str', 'w23, [sp, #0x30]'),
        0x100081d40: ('ldr', 'w0, [x0, #0x20]'),
        0x100081d44: ('b', '#0x10008f35c'),
        0x100081d48: ('ldr', 'w0, [x0, #0x20]'),
        0x100081d4c: ('b', '#0x10008f3fc'),
        0x10008f39c: ('bl', '#0x1001aa720'),
        0x10008f43c: ('bl', '#0x1001aa740'),
        0x100081e38: ('b', '#0x100067df0'),
        0x10014ac2c: ('cmn', 'w21, #1'),
        0x10014ac30: ('cset', 'w8, eq'),
        0x10014ac34: ('strb', 'w8, [x20, #0x53]'),
        0x10014ac9c: ('ldrb', 'w8, [x20, #0x51]'),
        0x10014aca0: ('cmp', 'w8, #1'),
        0x10014aca4: ('b.ne', '#0x10014ada8'),
        0x10014acfc: ('mov', 'x1, x21'),
        0x10014ad08: ('bl', '#0x1000817c0'),
    }
    for a, value in anchors.items():
        assert ins[a] == value, (hex(a), ins[a], value)
    for a, name in [(0x1001a13f0, '_CFArrayAppendValue'),
                    (0x1001a1440, '_CFArrayCreateMutable'),
                    (0x1001a1460, '_CFArrayGetCount'),
                    (0x1001a1410, '_CFArrayContainsValue'),
                    (0x1001a2120, '_dispatch_async'),
                    (0x1001a1d90, '_NSClassFromString')]:
        assert im.imported(a) == name, (hex(a), im.imported(a))
    assert im.string(0x1001f07af) == 'mediaAttrCount: %ld'
    assert im.string(0x1001f07c3) == 'playbackAttrCount: %ld'
    # These are assertions about this SHA-fixed arm64e image, NOT a general
    # chained-fixup/PAC decoder. Compare the stored words before following them.
    for block, target in [(0x10021bf98, 0x100081c08), (0x10021bfd8, 0x100081c18),
                          (0x10021c018, 0x100081c28), (0x10021c088, 0x100081c38),
                          (0x10021c0c8, 0x100081cc8), (0x10021c108, 0x100081cd8),
                          (0x10021c148, 0x100081d0c)]:
        raw = struct.unpack('<Q', im.read(block+16, 8))[0]
        assert raw == 0x8009000000000000 + target-BASE
    for slot, cfstr, value in [
        (0x1002199b0, 0x1002230f8, 'MediaItemAttributes'),
        (0x1002199b8, 0x100223118, 'MediaItemArtwork'),
        (0x1002199c0, 0x100223138, 'PlaybackAttributes'),
        (0x1002199c8, 0x100223158, 'PlaybackQueueList'),
    ]:
        # Low target bits are checked against the already observed CFString;
        # string storage is read from that object's own file-backed field.
        raw = struct.unpack('<Q', im.read(slot, 8))[0]
        assert raw & 0xffffffff == cfstr-BASE
        string_raw = struct.unpack('<Q', im.read(cfstr+16, 8))[0]
        assert im.string(BASE+(string_raw & 0xffffffff)) == value
    assert struct.unpack('<Q', im.read(0x100225d28, 8))[0] == 0x100000001d2110
    assert im.string(0x1001d2110) == 'AccessoryNowPlayingClient'
    for stub, slot, target, value in [
        (0x1001aa720, 0x100238fe8, 0x1001c648c, 'setPlaybackElapsedTime:'),
        (0x1001aa740, 0x100238ff0, 0x1001c64a4, 'setPlaybackQueueIndex:'),
        (0x1001a8560, 0x100238778, 0x1001ba383, 'numberWithLong:'),
        (0x1001ab580, 0x100239380, 0x1001c7524, 'subFeatureSubscribers'),
        (0x1001a4740, 0x1002377e8, 0x1001bf47e, 'addObject:'),
        (0x1001a9440, 0x100238b30, 0x1001c4a32, 'removeObject:'),
        (0x1001a5c40, 0x100237d30, 0x1001b9f38, 'countForObject:'),
        (0x1001a9ba0, 0x100238d08, 0x1001c545f, 'sendUpdatedSubscriberList'),
    ]:
        first = im.dis(stub, stub+8)
        assert first[stub] == ('adrp', f'x1, #{slot & ~0xfff:#x}')
        assert first[stub+4] == ('ldr', f'x1, [x1, #{slot & 0xfff:#x}]')
        assert struct.unpack('<Q', im.read(slot, 8))[0] == 0x8000000000000 + target-BASE
        assert im.string(target) == value
    print(f'C18: SHA; {len(funcs)} full slices; {len(anchors)} anchors; 6 Mach-O imports; '
          '7 block pointers; 8 selectors; subscriber/class/log strings OK (static only)')


if __name__ == '__main__':
    main()
