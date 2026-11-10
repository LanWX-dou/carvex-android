# G08: fast forward/rewind mapping and media-button edges

The host mixing code table has no verified seek codes. The bridge now translates
standard Consumer usages B3/B4 to Android KEYCODE_MEDIA_FAST_FORWARD/REWIND
(90/89), using the platform media-button endpoint already used for play/pause.
No vendor code, seek distance, repeat interval or track-skipping fallback is
invented. This is a local platform adapter change, not a new CarPlay wire format
or a claim about Apple's seeking implementation.

Previously directHidUsage discarded every release, and the queue synthesized
an immediate DOWN/UP for each press. Fast forward/rewind now queue their real
edges. HeldSystemMediaKeys preserves DOWN time until UP, counts independent
device holds and releases accepted holds when the session closes. A failed
release stays eligible for cleanup; it does not leave a phantom physical user
when another press follows. Ordinary one-shot actions keep their previous route.

Protocol evidence boundary: 24A446 accessoryd HID input is descriptor-defined
report transport, as recorded in iap2_input_business_lifecycle R-1.7 and its
original input handlers. The unchanged HidKeyState dispatches only transitions;
the new integration regression proves repeated unchanged reports generate no
repeated media-button events. Mapping values follow the standard Consumer usage
and Android KeyEvent constants, not a guessed Apple/vendor mapping.

The platform call submits an event; it does not report application acceptance.
Receiving apps may handle fast forward as a one-shot command or ignore UP.
Therefore G08 remains PARTIAL until the target player's sustained seeking and
stop/cancel behavior is verified or an explicit begin/end seek consumer is
obtained. No timer or synthesized seekTo position was added to hide this boundary.
Attempts to retrieve current Android online source failed (connection timeout);
the implementation uses the installed SDK constants and existing platform
endpoint, and does not claim fresh online source verification.

Validation: 10 new bridge regressions, including repeated HID reports, concurrent
devices, failed edges, cancellation and late delivery; bridge 37 tests pass.
Protocol 1107 tests remain passing (Gradle task up to date); Xiaomi Debug Kotlin
compilation passed. No phone or vehicle validation.
