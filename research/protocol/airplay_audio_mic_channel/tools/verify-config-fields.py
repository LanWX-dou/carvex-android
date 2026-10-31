#!/usr/bin/env python3
"""C11: original Sender/cache field types, flags and preference fallback.

Uses the adjacent video audit's fixed-image reader. This is static evidence,
not plist exchange, audio encoding, transport or peer-default execution.
"""
from pathlib import Path
import runpy

ROOT = Path(__file__).resolve().parents[1]


def main():
    support = runpy.run_path(str(ROOT.parent / 'airplay_video_channel/tools/verify-codec-config.py'))
    ev = support['Evidence']()
    try:
        code = ev.sender(0x2519bd928, 0x2519bfa8c)
        code.update(ev.sender(0x251bbb188, 0x251bbd808))
        code.update(ev.sender(0x2519c454c, 0x2519c4564))
        code.update(ev.sender(0x2519ae150, 0x2519ae15c))
        code.update(ev.fragment(0x18ee815a0, 0x18ee815e4,
                               'b5bf049d5f6c3fab0f610c479d6a8989210aecf9a41e89c183bb3bc2029ece87'))
        code.update(ev.fragment(0x18ee81258, 0x18ee813c0,
                               'fbb574926a8c08250fb2d31ed4328d878baec61bfddab9e4bb92ed5bb8ee5255'))
        anchors = {
            0x2519be814: ('bl', '#0x2519c4558'),
            0x2519be818: ('mov', 'x22, x0'),
            0x2519c455c: ('ldr', 'x0, [x0, #0x60]'),
            0x2519be840: ('add', 'x8, x8, #0xc18'),
            0x2519be848: ('mov', 'x2, x22'),
            0x2519be84c: ('bl', '#0x25810a790'),
            0x2519ae150: ('ldr', 'x1, [x8]'),
            0x2519ae154: ('mov', 'x0, x28'),
            0x251bbb830: ('ldr', 'x8, [x8, #0x198]'),
            0x251bbb834: ('ldr', 'x19, [x8]'),
            0x251bbb90c: ('ldr', 'w2, [x23, #0x74]'),
            0x251bbb910: ('cmp', 'w2, #1'),
            0x251bbb914: ('b.lt', '#0x251bbb928'),
            0x251bbb924: ('bl', '#0x25810a790'),
            0x251bbb928: ('ldr', 'x0, [x23, #0x28]'),
            0x251bbb930: ('ldr', 'x8, [x8, #0x7f0]'),
            0x251bbb934: ('ldr', 'x1, [x8]'),
            0x251bbb938: ('bl', '#0x25810b1a0'),
            0x251bbb93c: ('cbz', 'w0, #0x251bbb954'),
            0x251bbb944: ('add', 'x8, x8, #0xcd8'),
            0x251bbb94c: ('mov', 'x2, x19'),
            0x251bbb950: ('bl', '#0x2580f7000'),
            0x2519be7a8: ('adrp', 'x0, #0x27612e000'),
            0x2519be7ac: ('add', 'x0, x0, #0x850'),
            0x2519be7b0: ('adrp', 'x1, #0x27612d000'),
            0x2519be7b4: ('add', 'x1, x1, #0xcf0'),
            0x2519be7b8: ('mov', 'w2, #0xc8'),
            0x2519be7bc: ('bl', '#0x25810b2f0'),
            0x2519be7c0: ('sxtw', 'x8, w0'),
            0x2519be7c4: ('str', 'x8, [sp, #0x28]'),
            0x2519be95c: ('cmp', 'w20, #0x6b'),
            0x2519be960: ('b.ne', '#0x2519be990'),
            0x2519be980: ('add', 'x8, x8, #0xd48'),
            0x2519be988: ('ldr', 'x2, [sp, #0x28]'),
            0x2519be98c: ('bl', '#0x25810a790'),
            0x18ee815b0: ('mov', 'x20, x2'),
            0x18ee815b4: ('bl', '#0x1900ce070'),
            0x18ee815bc: ('mov', 'x1, x20'),
            0x18ee815c0: ('bl', '#0x18ee81258'),
            0x18ee81270: ('mov', 'x19, x1'),
            0x18ee81274: ('cbz', 'x0, #0x18ee8132c'),
            0x18ee8132c: ('mov', 'x21, x19'),
            0x18ee813a8: ('mov', 'x0, x21'),
            0x2519bdf58: ('ldr', 's1, [x25, #0x14]'),
            0x2519bdf5c: ('ucvtf', 'd1, d1'),
            0x2519bdf60: ('fdiv', 'd0, d0, d1'),
            0x2519bdf64: ('fcvtzu', 'w8, d0'),
            0x2519bdf68: ('udiv', 'w21, w26, w8'),
            0x2519be8d0: ('ldr', 'w2, [x27, #0x14]'),
        }
        for a, expected in anchors.items():
            assert code[a] == expected, (hex(a), code[a], expected)
        for slot, target, value in [
            (0x2693e7c18, 0x276136ef0, 'audioFormat'),
            (0x2693e7c28, 0x276136f30, 'audioType'),
            (0x2693e7cd0, 0x2761371b0, 'redundantAudio'),
            (0x2693e7cd8, 0x2761371d0, 'disableRetransmits'),
            (0x2693e7d48, 0x276137330, 'burstPeriodMs'),
        ]:
            ev.cf(slot, target, value)
        ev.cf(0x2680d57f0, 0x1e9ffaa48, 'LowLatencyAudio', 0x1e0a05408)
        assert ev.cache.cfstr(0x27612e850) == 'jarvisDefaultBurstPeriod'
        assert ev.cache.cfstr(0x27612dcf0) == 'com.apple.airplay'
        ev.true_pointer()
        ev.imports({0x25810a790: '_CFDictionarySetInt64', 0x2580f7000: '_CFDictionarySetValue',
                    0x25810b1a0: '_FigCFEqual', 0x25810b2f0: '_FigGetCFPreferenceNumberWithDefault',
                    0x1900ce070: '_CFPreferencesCopyAppValue'})
        assert ev.decode(ev.cache.read(0x25810b2f0, 12), 0x25810b2f0) == {
            0x25810b2f0: ('adrp', 'x16, #0x18ee81000'),
            0x25810b2f4: ('add', 'x16, x16, #0x5a0'),
            0x25810b2f8: ('br', 'x16'),
        }
        # Positive finite local arithmetic example, not executing the encoder.
        pps = int(48000 / 512)
        assert pps == 93 and 96000 // pps == 1032
        assert round(48000 / 512) != pps  # reject former rounding-to-nearest claim
        print(f'C11 PASS: 4 Sender ranges vs original cache; 2 hashed CoreMedia fragments; '
              f'{len(anchors)} anchors; 8 CFStrings; CFBoolean export; preference stub; '
              '5 import labels; truncation counterexample (static only)')
    finally:
        ev.cache.close()


if __name__ == '__main__':
    main()
