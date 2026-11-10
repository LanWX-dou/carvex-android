# Preserve resource declarations during an announcement

This fixes local concurrency and rollback, without adding Apple arbitration rules.
The wire representation continues to follow 24A446 AirPlaySender
`0x251afa97c..0x251afa9fc` (separate main-audio entity/permanent entity).
The multi-resource parse branch is recorded in `2026-11-10-resource-batch.md`.

Previously an announcement failure applied the opposite Boolean owner, losing
the original permanent owner and borrow flag. It could also overwrite a newer
changeModes declaration. Rollback now restores the exact audio snapshot only
if no newer audio declaration exists; unrelated screen changes survive.

MainAudioOwnership likewise checks the receiver revision after the suspended
round trip. A receiver takeover during that wait suppresses SETUP and sending.
A rejected announcement cannot reset a newer declaration to UNKNOWN. A same-owner
receiver declaration now settles the hold even if the previous owner was seeded
from capabilities. Temporary call borrowing and constraints remain OPEN.

Validation: core and protocol unit tests, Xiaomi Kotlin compilation. Regression
tests inject receiver changes inside the announcement callback, verify both
accepted/rejected outcomes and same-value declarations, and restore a borrowed
audio snapshot while preserving a concurrent screen change. No vehicle test.
