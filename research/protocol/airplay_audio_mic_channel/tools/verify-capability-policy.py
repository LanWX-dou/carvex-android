#!/usr/bin/env python3
"""C13: fixed original selection branches/getters and bounded mask execution.

Normalized-row examples are a policy model, not execution of CF plist parsing.
Mask blocks execute original ARM64; external comparison/preference results are
explicit inputs, never accepting hooks for a full negotiation transaction.
"""
from pathlib import Path
import itertools
import runpy
import sys

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / 'firmware/tools/ipsw-research/firmware_cache.py').is_file()
)
DEPS = REPO / 'firmware/tools/ipsw-research/.audit-deps'
# The vendored copy may ship only another platform's core library; importing it
# without a matching core binds an older system libunicorn (UC_ERR_VERSION).
_CORE = ('unicorn.dll' if sys.platform.startswith('win')
         else 'libunicorn.2.dylib' if sys.platform == 'darwin' else 'libunicorn.so.2')
if (DEPS / 'unicorn/lib' / _CORE).is_file():
    sys.path.insert(0, str(DEPS))
from unicorn import Uc, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE
from unicorn.arm64_const import (UC_ARM64_REG_X0, UC_ARM64_REG_X22, UC_ARM64_REG_X24,
                                UC_ARM64_REG_X25, UC_ARM64_REG_X27, UC_ARM64_REG_PC)

MASK_1C_NONZERO = 0xf7fe0f8ffffc0000
MASK_BASE = 0x1f0400003fffc
MASK_EXTENDED = 0x41f04000c3fffc
MASK_TELEPHONY = 0x80014000114


def key(raw, kind):
    return 'input' if raw == 107 or raw == 100 and kind in (
        'default', 'telephony', 'speechRecognition') else 'output'


def select_normalized(rows, raw, kind, manufacturer):
    """Only successfully normalized rows, no malformed plist/extended-array model."""
    fallback, selected, used_default, match = 0, 0, False, None
    for index, row in enumerate(rows):
        if row['type'] != raw:
            continue
        audio_type = row['audioType']  # None = typed getter returned NULL
        if audio_type is None or audio_type == kind:
            selected = row.get(key(raw, kind), 0)
            used_default, match = audio_type is None, index
            break
        if audio_type == 'default':
            fallback = row.get(key(raw, 'default'), 0)
    if not selected and fallback and manufacturer.startswith('Apple'):
        selected, used_default = fallback, True
    return selected, used_default, match


def main():
    ev = runpy.run_path(str(ROOT.parent / 'airplay_video_channel/tools/verify-codec-config.py'))['Evidence']()
    try:
        code = ev.sender(0x251adc3c0, 0x251adc910)
        code.update(ev.sender(0x251adcb7c, 0x251add5ac))
        typed = ev.fragment(0x18be38df0, 0x18be38e58,
                            '2493b7d02cd6319ad9969516e4c2da03e013434e425d689b8d576f6a0f10e799')
        integer = ev.fragment(0x18be373d8, 0x18be37434,
                              '8f3287832be63857f22d82e58278f8c8724f1593418aefadd7fa5a2466be4097')
        code.update(typed)
        code.update(integer)
        anchors = {
            0x251adc424: ('bl', '#0x25810a710'),
            0x251adc484: ('bl', '#0x25810a5c0'),
            0x251adc4a0: ('bl', '#0x25810a6f0'),
            0x251adc4ac: ('cmp', 'w19, w0'),
            0x251adc4c8: ('mov', 'x3, #0'),
            0x251adc4d4: ('cbz', 'x0, #0x251adc558'),
            0x251adc4e0: ('mov', 'x2, #0'),
            0x251adc4e4: ('bl', '#0x258102330'),
            0x251adc4e8: ('cbz', 'x0, #0x251adc558'),
            0x251adc4f4: ('bl', '#0x25810b1a0'),
            0x251adc518: ('mov', 'x25, x0'),
            0x251adc560: ('bl', '#0x251adc910'),
            0x251adc56c: ('mov', 'x2, #0'),
            0x251adc574: ('mov', 'x27, x0'),
            0x251adc5c4: ('mov', 'w21, #1'),
            0x251adc5f4: ('bl', '#0x25810a710'),
            0x251adc600: ('cbnz', 'w0, #0x251adc908'),
            0x251adc628: ('cbz', 'x25, #0x251adc698'),
            0x251adc654: ('bl', '#0x25810ab10'),
            0x251adc658: ('cbz', 'w0, #0x251adc6a0'),
            0x251adc690: ('mov', 'w21, #1'),
            0x251adc6c0: ('cbz', 'x22, #0x251adc838'),
            0x251adc6f0: ('csel', 'x22, x22, x8, eq'),
            0x251adc704: ('mov', 'w1, #0'),
            0x251adc708: ('bl', '#0x258109e20'),
            0x251adc71c: ('csel', 'x22, x22, x8, eq'),
            0x251adc79c: ('str', 'x22, [x27]'),
            0x251adc7b4: ('strb', 'w21, [x8]'),
            0x251adc8f8: ('mov', 'w8, #-0x1a31'),
            0x251adcc30: ('strb', 'w8, [x21, #0x1c]'),
            0x251adcc38: ('strb', 'w20, [x21, #0x1f]'),
            0x18be38e24: ('csel', 'x0, x21, xzr, eq'),
            0x18be38e2c: ('csel', 'w8, wzr, w8, eq'),
            0x18be38e30: ('cbz', 'x19, #0x18be38e38'),
            0x18be37424: ('mov', 'x0, #0'),
        }
        for a, wanted in anchors.items():
            assert code[a] == wanted, (hex(a), code[a], wanted)
        for a, value in [(0x2761398b0, 'audioFormats'), (0x2761398d0, 'audioOutputFormatsExtended'),
                         (0x2761398f0, 'carplayForce44kForBuffered'), (0x276130030, 'manufacturer'),
                         (0x27612e030, 'Apple'), (0x27612fb30, 'type'), (0x276136f30, 'audioType')]:
            assert ev.cache.cfstr(a) == value
        ev.imports({0x25810a710: '_CFDictionaryGetTypedValue', 0x25810a6f0: '_CFDictionaryGetInt64',
                    0x25810a660: '_CFDictionaryContainsKey', 0x258102330: '_CFStringCompare',
                    0x25810ab10: '_CFStringHasPrefix', 0x258109e20: '_APSSettingsGetIntWithDefault',
                    0x25810aff0: '_FigCFArrayRemoveLastElementOfValue',
                    0x25810b1d0: '_FigCFNumberCreateUInt64'})
        for stub, target in [(0x25810a710, 0x18be38df0), (0x25810a6f0, 0x18be373d8)]:
            assert ev.decode(ev.cache.read(stub, 12), stub) == {
                stub: ('adrp', f'x16, #0x{target & ~4095:x}'),
                stub+4: ('add', f'x16, x16, #0x{target & 4095:x}'),
                stub+8: ('br', 'x16'),
            }
        u = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        u.mem_map(0x251adc000, 4096)
        u.mem_write(0x251adc3c0, ev.cache.read(0x251adc3c0, 0x550))
        obj = 0x100000
        u.mem_map(obj, 4096)
        stops = {0x251adc6c4, 0x251adc838}
        # Stop at a branch boundary before any outside call; no register mutation.
        def stop_boundary(cpu, address, size, data):
            if address in stops:
                cpu.emu_stop()
        handle = u.hook_add(UC_HOOK_CODE, stop_boundary)
        values = [0, (1<<64)-1] + [1<<i for i in range(64)]
        count = 0
        for byte1c, byte1f, value in itertools.product((0, 1, 255), (0, 1, 255), values):
            u.mem_write(obj+0x1c, bytes([byte1c, 0, 0, byte1f]))
            u.reg_write(UC_ARM64_REG_X24, obj)
            u.reg_write(UC_ARM64_REG_X25, value)
            u.emu_start(0x251adc6a8, 0, count=100)
            expected = value & (MASK_1C_NONZERO if byte1c else MASK_EXTENDED if byte1f else MASK_BASE)
            assert u.reg_read(UC_ARM64_REG_X22) == expected
            assert u.reg_read(UC_ARM64_REG_PC) == (0x251adc6c4 if expected else 0x251adc838)
            count += 1
        u.hook_del(handle)
        for same, value in itertools.product((0, 1, 255), values):
            u.reg_write(UC_ARM64_REG_X0, same)
            u.reg_write(UC_ARM64_REG_X22, value)
            u.emu_start(0x251adc6dc, 0x251adc6f4, count=100)
            assert u.reg_read(UC_ARM64_REG_X22) == (value & MASK_TELEPHONY if same else value)
            count += 1
        for out_ptr, value in itertools.product((0, obj), values):
            u.reg_write(UC_ARM64_REG_X27, out_ptr)
            u.reg_write(UC_ARM64_REG_X22, value)
            u.emu_start(0x251adc710, 0x251adc720, count=100)
            assert u.reg_read(UC_ARM64_REG_X22) == (value & ~(1<<23) if out_ptr else value)
            count += 1
        def row(kind, mask):
            return dict(type=100, audioType=kind, input=mask, output=mask)
        examples = [
            ([row(None, 4), row('telephony', 16)], 'Apple', (4, True, 0)),
            ([row('telephony', 16), row(None, 4)], 'Apple', (16, False, 0)),
            ([row('default', 4), row('default', 16)], 'Apple Inc.', (16, True, None)),
            ([row('default', 16), row('default', 0)], 'Apple', (0, False, None)),
            ([row('default', 16)], 'apple', (0, False, None)),
            ([row('default', 16), row('telephony', 0), row('telephony', 64)], 'Apple', (16, True, 1)),
            ([row('telephony', 0), row('default', 16)], 'Apple', (0, False, 0)),
            ([row(None, 0), row('telephony', 16)], 'Other', (0, True, 0)),
        ]
        for rows, maker, wanted in examples:
            assert select_normalized(rows, 100, 'telephony', maker) == wanted
        print(f'C13 PASS: fixed Sender/cache and 2 hashed getters; {len(anchors)} anchors; '
              f'7 CFStrings/2 direct stubs/8 import labels; {count} original mask blocks; '
              f'{len(examples)} normalized-order model examples. No full CF parser or negotiation execution.')
    finally:
        ev.cache.close()


if __name__ == '__main__':
    main()
