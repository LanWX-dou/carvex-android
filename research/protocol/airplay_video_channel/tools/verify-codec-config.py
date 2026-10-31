#!/usr/bin/env python3
"""C11: original-cache codec configuration/attachment dataflow, static only.

Evidence reads are deliberately bounded. Cache v5 pointer helpers and Sender
image hashes are fixed; pointer names are checked against original CFStrings.
No encoder, CoreMedia service, crypto or network is executed.
"""
from pathlib import Path
import hashlib
import itertools
import json
import re
import sys
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / 'firmware/tools/ipsw-research/firmware_cache.py').is_file()
)
SHA = '304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f'


class Evidence:
    def __init__(self):
        helpers = REPO / 'firmware/tools/ipsw-research'
        for name, digest in [
            ('firmware_cache.py', '2a4083dc30efce1c9df02ca64330e5279a142f4c08af22e14738bfa9bd1d0300'),
            ('firmware_image.py', '642cb879df32e8974c6e59cce9339dc8deb1aa3c9867e38dfadd03967f01157b'),
        ]:
            assert hashlib.sha256((helpers / name).read_bytes()).hexdigest() == digest, name
        sys.path.insert(0, str(helpers))
        from firmware_cache import Cache
        self.cache = Cache(REPO / 'firmware/extracted/24A446/dyld')
        self.blob = (ROOT / 'source/firmware/AirPlaySender').read_bytes()
        assert hashlib.sha256(self.blob).hexdigest() == SHA
        self.segments = json.loads((ROOT / 'source/metadata/segments.json').read_text())
        self.cs = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
        self.stub_text = (REPO / 'firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt').read_text(encoding='utf-8')

    def sender(self, a, z):
        matches = [s for s in self.segments if s['vmaddr'] <= a and z <= s['vmaddr']+s['filesize']]
        assert len(matches) == 1
        s = matches[0]
        off = s['fileoff'] + a-s['vmaddr']
        raw = self.blob[off:off+z-a]
        assert raw == self.cache.read(a, z-a), f'cache/extracted mismatch {a:x}'
        return self.decode(raw, a)

    def decode(self, raw, a):
        ins = list(self.cs.disasm(raw, a))
        assert sum(i.size for i in ins) == len(raw)
        return {i.address: (i.mnemonic, i.op_str) for i in ins}

    def fragment(self, a, z, digest):
        raw = self.cache.read(a, z-a)
        assert hashlib.sha256(raw).hexdigest() == digest, hex(a)
        return self.decode(raw, a)

    def imports(self, expected):
        for va, name in expected.items():
            assert re.search(rf'(?m)^0x{va:x}: {re.escape(name)}$', self.stub_text), name

    def cf(self, slot, target, value, indirect=None):
        ptr = self.cache.ptr(slot)
        if indirect is not None:
            assert ptr == indirect, hex(slot)
            ptr = self.cache.ptr(ptr)
        assert ptr == target, (hex(slot), hex(ptr), hex(target))
        assert self.cache.cfstr(ptr) == value, hex(slot)

    def true_pointer(self):
        # Independent nlist name for the exported CFBoolean constant slot.
        from firmware_image import Image
        p = REPO / 'firmware/extracted/24A446/binaries/CoreFoundation/CoreFoundation'
        assert hashlib.sha256(p.read_bytes()).hexdigest() == '28be8a1510b9c7b8211d196584d3cd502a2d8fd1c40ffd00e3db84466279d478'
        cf = Image(p)
        slot = self.cache.ptr(0x2680d3198)
        assert slot == 0x1e053a5a0
        assert '_kCFBooleanTrue' in cf.symbols[slot]
        assert self.cache.ptr(slot) == 0x1e8e94158


def verify_not_sync_getter(ev):
    """Original getter/outlined ABI plus local caller model, not CF execution."""
    from firmware_image import Image
    cm_path = REPO / 'firmware/extracted/24A446/binaries/CoreMedia/CoreMedia'
    assert hashlib.sha256(cm_path.read_bytes()).hexdigest() == (
        '65775c5795c2696444037aaaa36ccda29f93fa59c25a05f19a0c53ed4db6724f')
    cm = Image(cm_path)
    a, z = 0x18efac1c8, 0x18efac28c
    assert '_FigCFDictionaryGetBooleanIfPresent' in cm.symbols[a]
    assert cm.starts[cm.starts.index(a) + 1] == z
    code = ev.fragment(a, z, '58fa47a1ccc51b974aef90ef483b26b3be35f00ab7961554fdc2fe289023adb7')
    code.update(ev.fragment(0x18ee830b4, 0x18ee830d0,
                           'f19cfdc71519c19e2afeaae33420d4c015cb34ec3aed3ee392d64eade3610c9c'))
    code.update(ev.fragment(0x18ee4eb40, 0x18ee4eb4c,
                           'dcd8c7801760be580fec8bcd91803eb5b684a24d4d76df4e0acaa34f8b548eac'))
    expected = {
        0x18ee830b4: ('mov', 'x19, x2'),
        0x18ee830b8: ('mov', 'x21, x1'),
        0x18ee830bc: ('mov', 'x22, x0'),
        0x18ee830cc: ('b', '#0x1900caaa0'),
        0x18ee4eb40: ('mov', 'x0, x22'),
        0x18ee4eb44: ('mov', 'x1, x21'),
        0x18efac1e4: ('cbz', 'x0, #0x18efac278'),
        0x18efac1fc: ('b.ne', '#0x18efac244'),
        0x18efac200: ('cbz', 'x21, #0x18efac254'),
        0x18efac204: ('cbz', 'x19, #0x18efac264'),
        0x18efac208: ('add', 'x2, sp, #8'),
        0x18efac210: ('bl', '#0x1900cdf40'),
        0x18efac214: ('cbz', 'w0, #0x18efac278'),
        0x18efac228: ('cmp', 'x20, x0'),
        0x18efac22c: ('b.ne', '#0x18efac274'),
        0x18efac234: ('bl', '#0x1900cdba0'),
        0x18efac238: ('strb', 'w0, [x19]'),
        0x18efac23c: ('mov', 'w0, #1'),
        0x18efac274: ('mov', 'w0, #0'),
    }
    for addr, want in expected.items():
        assert code[addr] == want, (hex(addr), code[addr], want)
    # Unlike import-index checks, verify each actual direct stub and destination export.
    cf = Image(REPO / 'firmware/extracted/24A446/binaries/CoreFoundation/CoreFoundation')
    for stub, target, name, im in [
        (0x25810b040, a, '_FigCFDictionaryGetBooleanIfPresent', cm),
        (0x1900cdf30, 0x18063c298, '_CFDictionaryGetTypeID', cf),
        (0x1900cdf40, 0x1806343b0, '_CFDictionaryGetValueIfPresent', cf),
        (0x1900cdb90, 0x18064d5e0, '_CFBooleanGetTypeID', cf),
        (0x1900caaa0, 0x18062493c, '_CFGetTypeID', cf),
        (0x1900cdba0, 0x1806184e0, '_CFBooleanGetValue', cf),
    ]:
        assert name in im.symbols[target]
        assert ev.decode(ev.cache.read(stub, 12), stub) == {
            stub: ('adrp', f'x16, #0x{target & ~0xfff:x}'),
            stub+4: ('add', f'x16, x16, #0x{target & 0xfff:x}'),
            stub+8: ('br', 'x16'),
        }
    def local_bit4(values):
        output = False  # caller initializes the one-byte output once
        for value in values:
            if type(value) is bool:  # CFBoolean only; integer 0/1 is not CFBoolean
                output = value
                break  # getter returns 1 even when output is false
        return int(not output)
    cases = 0
    for n in range(5):
        for values in itertools.product((None, 'wrong-type', False, True), repeat=n):
            first = next((v for v in values if type(v) is bool), False)
            assert local_bit4(values) == int(not first)
            cases += 1
    assert local_bit4([False, True]) == 1
    assert local_bit4([True, False]) == 0
    assert local_bit4([0, 1]) == 1
    print(f'C11 NotSync: full hashed getter + 2 ABI helpers; {len(expected)} anchors; '
          f'6 direct stubs/export names; {cases} local attachment sequences (not native execution)')


def main():
    ev = Evidence()
    try:
        code = ev.sender(0x2519b0014, 0x2519b15a4)
        code.update(ev.sender(0x251b43fcc, 0x251b44300))
        code.update(ev.sender(0x251b44f90, 0x251b44fa8))
        anchors = {
            0x2519b0070: ('add', 'x8, x20, #0x208'),
            0x2519b0074: ('str', 'x8, [sp, #0x70]'),
            0x2519b04d0: ('bl', '#0x25810c480'),
            0x2519b04d8: ('bl', '#0x25810ace0'),
            0x2519b04e8: ('mov', 'w8, #0x6331'),
            0x2519b04ec: ('movk', 'w8, #0x6176, lsl #16'),
            0x2519b04f0: ('cmp', 'w0, w8'),
            0x2519b04f8: ('ldrb', 'w8, [x20, #0x3c8]'),
            0x2519b04fc: ('cbz', 'w8, #0x2519b061c'),
            0x2519b0620: ('ldr', 'x8, [x8, #0x4d0]'),
            0x2519b0624: ('ldr', 'x1, [x8]'),
            0x2519b062c: ('bl', '#0x25810acd0'),
            0x2519b0650: ('adrp', 'x1, #0x27613f000'),
            0x2519b0654: ('add', 'x1, x1, #0xe10'),
            0x2519b065c: ('bl', '#0x258102680'),
            0x2519b08c4: ('bl', '#0x2581064c0'),
            0x2519b08dc: ('bl', '#0x25810b1a0'),
            0x2519b08e0: ('cbz', 'w0, #0x2519b0940'),
            0x2519b097c: ('str', 'x21, [x8]'),
            0x2519b0994: ('mov', 'w19, #0'),
            0x2519b131c: ('cbz', 'w19, #0x2519b0a08'),
            0x2519b0a08: ('mov', 'w28, #1'),
            0x2519b0e5c: ('cbz', 'w28, #0x2519b0e70'),
            0x2519b0e68: ('bl', '#0x251b43fcc'),
            0x251b43ff8: ('ldr', 'x0, [x0]'),
            0x251b44008: ('bl', '#0x2580f6a40'),
            0x251b44014: ('ldr', 'x1, [x20]'),
            0x251b44024: ('bl', '#0x25810f290'),
            0x251b44060: ('mov', 'w23, #1'),
            0x251b44080: ('strb', 'w23, [x0, #4]'),
            0x251b44278: ('bl', '#0x25810eab0'),
            0x2519b0a18: ('bl', '#0x25810ad50'),
            0x2519b0a40: ('ldr', 'x8, [x8, #0x600]'),
            0x2519b0a5c: ('bl', '#0x25810b040'),
            0x2519b0a60: ('cbnz', 'w0, #0x2519b0a70'),
            0x2519b0a78: ('cset', 'w8, eq'),
            0x2519b0a88: ('mov', 'w8, #1'),
            0x2519b0a8c: ('strb', 'w8, [x20, #0x45d]'),
            0x2519b0b34: ('ldr', 'x1, [x8, #0x898]'),
            0x2519b0b38: ('bl', '#0x251b44f90'),
            0x2519b0b40: ('cset', 'w8, eq'),
            0x2519b0b44: ('strb', 'w8, [x20, #0x45c]'),
            0x251b44f90: ('mov', 'x0, x25'),
            0x251b44f94: ('mov', 'x2, #0'),
            0x251b44fa4: ('b', '#0x25810acf0'),
            0x2519b1048: ('strb', 'w9, [x25, #5]'),
            0x2519b1054: ('orr', 'w9, w9, #0x10'),
        }
        for a, expected in anchors.items():
            assert code[a] == expected, (hex(a), code[a], expected)
        ev.cf(0x2680d44d0, 0x1e9fe5188, 'SampleDescriptionExtensionAtoms', 0x1e09fd170)
        ev.cf(0x2680d4600, 0x1e9fe6608, 'NotSync', 0x1e09fd800)
        ev.cf(0x2693e7898, 0x276136590, 'APInterestingFrame')
        assert ev.cache.cfstr(0x27613fe10) == 'avcC'
        ev.true_pointer()
        verify_not_sync_getter(ev)
        ev.imports({
            0x25810c480: '_CMSampleBufferGetFormatDescription',
            0x25810ace0: '_CMFormatDescriptionGetMediaSubType',
            0x25810acd0: '_CMFormatDescriptionGetExtension',
            0x258102680: '_CFDictionaryGetValue',
            0x2581064c0: '_CFDataGetTypeID',
            0x25810b1a0: '_FigCFEqual',
            0x2580f6a40: '_CFDataGetLength',
            0x25810f290: '_FigCreateBlockBufferWithCFDataNoCopy',
            0x25810eab0: '_CMBlockBufferAppendBufferReference',
            0x25810ad50: '_CMSampleBufferGetSampleAttachmentsArray',
            0x25810b040: '_FigCFDictionaryGetBooleanIfPresent',
            0x25810acf0: '_CMGetAttachment',
        })
        print(f'C11 PASS: fixed Sender/cache code; {len(anchors)} anchors; '
              '4 cache CFStrings; CFBoolean export; 12 import labels (static only)')
    finally:
        ev.cache.close()


if __name__ == '__main__':
    main()
