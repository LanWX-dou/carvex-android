# Preserve active navigation PCM during SETUP

This corrects Android startup buffering, not Apple latency or wire fields.
Navigation remains the independently managed alternate stream described by
WWDC 2016/722 (480–522 seconds) and 723 (739–789 seconds). Existing type101
selection and the 24A446 audio lifecycle evidence remain unchanged; see
`research/protocol/airplay_audio_mic_channel/spec/01-audio-streams.md`
in the research workspace and the earlier navigation drain fix.

Before this change only the first host block survived into the SETUP coroutine,
and it was discarded after 100 ms. Subsequent blocks arrived before a bridge
binding existed and were dropped. Now each navigation activation owns a bounded
startup buffer. Adjacent blocks with the same format are coalesced; after attach,
the active prefix is enqueued before subsequent live PCM can enter. The format
of each segment is preserved, including when a prime uses another format.

The bound is local: at most 32768 bytes (one maximum accepted host PCM block),
and eight format segments. It is not an Apple latency value. Overflow preserves
the prefix, drops subsequent pending blocks and logs the boundary once. Failed
SETUP, source stop, disconnect and superseded activations discard pending data.
No fixed SETUP expiry or sleep was introduced. Media and speech startup policy
are unchanged. A navigation source that ends before SETUP still gets discarded;
this change does not replay an already-ended instruction.

Validation: core, bridge and protocol unit tests plus Xiaomi Kotlin compilation.
New tests cover >100 ms setup, more than eight callbacks coalesced into one bridge
block, callback-buffer reuse, prefix-before-live ordering, overflow, format changes,
failed activation, source stop and disconnect. Existing navigation drain/lifecycle
tests remain required. No device/vehicle test; receiver playback latency remains OPEN.
