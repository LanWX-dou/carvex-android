#!/usr/bin/env python3
"""C12: original APAudioFormatToASBD execution and Sender call binding.

No API hooks, instruction replacements, network, codecs or peer negotiation.
Only the original leaf, its constant page and isolated output memory are mapped.
"""
from pathlib import Path
import hashlib
import json
import runpy
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / 'firmware/tools/ipsw-research/firmware_cache.py').is_file()
)
DEPS = REPO / 'firmware/tools/ipsw-research/.audit-deps'
# Only prefer the vendored package when it carries a core library for this platform.
_CORE = ('unicorn.dll' if sys.platform.startswith('win')
         else 'libunicorn.2.dylib' if sys.platform == 'darwin' else 'libunicorn.so.2')
if (DEPS / 'unicorn/lib' / _CORE).is_file():
    sys.path.insert(0, str(DEPS))
from unicorn import Uc, UC_ARCH_ARM64, UC_MODE_ARM, UC_PROT_READ, UC_PROT_WRITE, UC_PROT_EXEC
from unicorn import __version__ as unicorn_version
from unicorn.arm64_const import (UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2,
                                UC_ARM64_REG_X19, UC_ARM64_REG_X22, UC_ARM64_REG_X23,
                                UC_ARM64_REG_X24, UC_ARM64_REG_X29, UC_ARM64_REG_X30,
                                UC_ARM64_REG_PC)

START, END = 0x226ee09d8, 0x226ee144c
DATA, STOP = 0x100000, 0x200000


def main():
    assert unicorn_version == '2.1.4', ('tested Unicorn version', unicorn_version)
    ev = runpy.run_path(str(ROOT.parent / 'airplay_video_channel/tools/verify-codec-config.py'))['Evidence']()
    try:
        from firmware_image import Image
        p = REPO / 'firmware/extracted/24A446/binaries/AirPlaySupport/AirPlaySupport'
        assert hashlib.sha256(p.read_bytes()).hexdigest() == 'd90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15'
        support = Image(p)
        assert '_APAudioFormatToASBD' in support.symbols[START]
        assert support.starts[support.starts.index(START)+1] == END
        leaf = ev.fragment(START, END, '50b1f8a4a243419597d4d3420e501841bd54268781a6ecb40ca5d28be19d990f')
        assert all(m not in ('bl', 'blr', 'blraa', 'blrab') for m, op in leaf.values())
        constants = ev.cache.read(0x226f30000, 4096)
        assert hashlib.sha256(constants).hexdigest() == '56afbab3d862199ebe55cb900aba7aff896e7eafb2d95d9a0480f5d7e0d3c840'
        assert support.read(START, END-START) == ev.cache.read(START, END-START)
        assert support.read(0x226f30000, 4096) == constants
        assert ev.decode(ev.cache.read(0x25810c7c0, 12), 0x25810c7c0) == {
            0x25810c7c0: ('adrp', 'x16, #0x226ee0000'),
            0x25810c7c4: ('add', 'x16, x16, #0x9d8'),
            0x25810c7c8: ('br', 'x16'),
        }
        code = ev.sender(0x251addd00, 0x251adebd4)
        code.update(ev.sender(0x251adc910, 0x251adc9ac))
        anchors = {
            0x251ade020: ('mov', 'w20, #1'),
            0x251ade034: ('tst', 'x20, x8'),
            0x251ade038: ('b.eq', '#0x251ade758'),
            0x251ade04c: ('sub', 'x1, x29, #0xb0'),
            0x251ade050: ('sub', 'x2, x29, #0xb4'),
            0x251ade054: ('mov', 'x0, x20'),
            0x251ade058: ('bl', '#0x25810c7c0'),
            0x251ade05c: ('cbz', 'w0, #0x251ade09c'),
            0x251ade704: ('ldp', 'q1, q0, [x29, #-0xb0]'),
            0x251ade708: ('stp', 'q1, q0, [x19, #0x10]'),
            0x251ade70c: ('str', 'x8, [x19, #0x30]'),
            0x251ade720: ('stp', 'x8, x20, [x19, #0x58]'),
            0x251ade75c: ('lsl', 'x20, x20, #1'),
            0x251ade760: ('cmp', 'x27, #0x40'),
            0x251ade764: ('b.ne', '#0x251ade030'),
            0x251adc920: ('cmp', 'w0, #0x6b'),
            0x251adc924: ('b.eq', '#0x251adc948'),
            0x251adc928: ('cmp', 'w0, #0x64'),
            0x251adc92c: ('b.ne', '#0x251adc954'),
            0x251adc944: ('cbz', 'w0, #0x251adc96c'),
            0x251adc984: ('cbnz', 'w0, #0x251adc95c'),
            0x251adc9a4: ('csel', 'x20, x8, x20, eq'),
        }
        for a, want in anchors.items():
            assert code[a] == want, (hex(a), code[a], want)
        for a, text in [(0x2761319f0, 'default'), (0x27612e7b0, 'telephony'),
                        (0x27612e830, 'speechRecognition'), (0x276139970, 'audioInputFormats'),
                        (0x276139990, 'audioOutputFormats')]:
            assert ev.cache.cfstr(a) == text
        ev.imports({0x258101830: '_CFEqual'})  # index label, not native CF execution

        # Existing frozen observations are expectations, not the execution oracle.
        table_path = REPO / 'firmware/analysis/24A446/carplay-audio-transaction/supported-format-descriptions.json'
        assert hashlib.sha256(table_path.read_bytes()).hexdigest() == 'efb4980919fb90eb83736e95d2a691dae595e1370e448d79ffdf8ef1806bd6eb'
        rows = json.loads(table_path.read_text())['supported']
        expected = {r['value']: r for r in rows}
        assert len(expected) == 59
        u = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        u.mem_map(START & ~4095, 8192, UC_PROT_READ | UC_PROT_EXEC)
        u.mem_write(START, ev.cache.read(START, END-START))
        u.mem_map(0x226f30000, 4096, UC_PROT_READ)
        u.mem_write(0x226f30000, constants)
        u.mem_map(DATA, 4096, UC_PROT_READ | UC_PROT_WRITE)
        u.mem_map(0x251ade000, 4096, UC_PROT_READ | UC_PROT_EXEC)
        u.mem_write(0x251ade09c, ev.cache.read(0x251ade09c, 0x174-0x9c))
        clean = u.context_save()
        values = sorted({0, (1<<64)-1} | {1<<i for i in range(64)} |
                        {(1<<i)|(1<<j) for i in range(64) for j in range(i+1, 64)} |
                        {(1<<i)-1 for i in range(2, 64)})
        cases = 0
        for optional_bits in (True, False):
            for value in values:
                u.context_restore(clean)
                u.mem_write(DATA, b'\xa5'*4096)
                for reg, val in [(UC_ARM64_REG_X0, value), (UC_ARM64_REG_X1, DATA+0x100),
                                 (UC_ARM64_REG_X2, DATA+0x200 if optional_bits else 0),
                                 (UC_ARM64_REG_X30, STOP)]:
                    u.reg_write(reg, val)
                u.emu_start(START, STOP, count=4096)
                assert u.reg_read(UC_ARM64_REG_PC) == STOP, ('instruction budget', value)
                result = u.reg_read(UC_ARM64_REG_X0) & 0xffffffff
                page = bytes(u.mem_read(DATA, 4096))
                want = bytearray(b'\xa5'*4096)
                if value in expected:
                    row = expected[value]
                    assert result == 0, (hex(value), result)
                    packed = struct.pack('<d8I', row['sample_rate'], *[row[k] for k in (
                        'format_id', 'format_flags', 'bytes_per_packet', 'frames_per_packet',
                        'bytes_per_frame', 'channels', 'bits_per_channel', 'reserved')])
                    assert packed.hex() == row['raw_asbd']
                    want[0x100:0x128] = packed
                    if optional_bits:
                        want[0x200:0x204] = struct.pack('<I', row['reported_bits'])
                else:
                    assert result == 0xffffe5b1, (hex(value), result)
                assert page == want, ('output or canary differs', hex(value), optional_bits)
                cases += 1
        # Execute the actual caller's bounded, call-free descriptor transform.
        # w19=0 is the initial-format path; codec consistency/error/logging is not run.
        for row in rows:
            u.context_restore(clean)
            want = bytearray(b'\xa5'*4096)
            wire = bytearray.fromhex(row['raw_asbd'])
            want[0x750:0x778] = wire  # fp-b0
            want[0x74c:0x750] = struct.pack('<I', row['reported_bits'])
            u.mem_write(DATA, bytes(want))
            for reg, val in [(UC_ARM64_REG_X19, 0), (UC_ARM64_REG_X22, 0x6c70636d),
                             (UC_ARM64_REG_X23, DATA+0x400), (UC_ARM64_REG_X24, 0),
                             (UC_ARM64_REG_X29, DATA+0x800)]:
                u.reg_write(reg, val)
            u.emu_start(0x251ade09c, 0x251ade174, count=256)
            assert u.reg_read(UC_ARM64_REG_PC) == 0x251ade174
            if row['format_fourcc'] == 'lpcm':
                struct.pack_into('<I', wire, 12, row['format_flags'] | 2)
                hal = bytearray(wire)
                struct.pack_into('<I', hal, 12, row['format_flags'] & ~2)
            else:
                bits, ch = row['reported_bits'], row['channels']
                bpf = ((bits+7)//8)*ch
                flags = 12 if bits % 8 == 0 else 20
                hal = bytearray(struct.pack('<d8I', row['sample_rate'], 0x6c70636d,
                                           flags, bpf, 1, bpf, ch, bits, 0))
            want[0x750:0x778] = wire
            want[0x400:0x438] = hal + struct.pack('<2d', row['sample_rate'], row['sample_rate'])
            assert bytes(u.mem_read(DATA, 4096)) == want, ('caller transform', row['hex_value'])
        doc = (ROOT / 'spec/11-format-id-map.md').read_text(encoding='utf-8')
        actual_rows = [line for line in doc.splitlines() if line.startswith('| ') and
                       line.split('|')[1].strip().isdigit()]
        expected_rows = []
        for row in rows:
            fields = [row['value'].bit_length()-1, row['format_fourcc'].replace(' ', '␠'),
                      int(row['sample_rate']), row['format_flags'], row['bytes_per_packet'],
                      row['frames_per_packet'], row['bytes_per_frame'], row['channels'],
                      row['bits_per_channel'], row['reported_bits']]
            expected_rows.append('| ' + ' | '.join(map(str, fields)) + ' |')
        assert actual_rows == expected_rows, 'descriptor table differs (including extra/duplicate rows)'
        print(f'C12 PASS: original leaf and constant page; {cases} no-hook ARM64 executions; '
              f'59 complete ASBD rows/optional bits/canaries; 59 original caller transforms; {len(anchors)} Sender anchors; '
              'direct import target and 5 CFStrings. No codec/peer negotiation executed.')
    finally:
        ev.cache.close()


if __name__ == '__main__':
    main()
