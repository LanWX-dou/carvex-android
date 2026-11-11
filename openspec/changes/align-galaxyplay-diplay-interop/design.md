## Context

GalaxyPlay 0.1.212/240 APK remains the target. The user has Android 17 and has not
enabled DiPlay on the vehicle. DiPlay commit 615b32c is a receiver reference,
not evidence of Apple sender behavior or GalaxyPlay runtime results.

## Goals / Non-Goals

**Goals:** Execute real receiver parsers in optional host JVM tests; correct
call Hook Switch routing; honor navigation storage capacity; preserve normal
music behavior and field/source evidence. Keep separate, traceable commits.

**Non-Goals:** Modify/install the external receiver, add a vehicle-name branch,
invent phone call metadata or cellular PCM, claim field acceptance from JVM
tests, or extend the current transport to independent USB/Wi-Fi modes.

## Decisions

- Stage explicitly selected pure Kotlin receiver files into ignored Android
  build output. Extract only the pure call-state model from its Android-facing
  file; keep its class body byte-for-byte and record source and slice hashes.
  Use a temporary Gradle init script to add these test sources. Default builds
  and production APKs have no receiver-source dependency.
- Test source-generated subscriptions, sender bytes through receiver CSM and
  state parsers, actual HID descriptors, and source-derived audio-format rows.
  Hash-bound APK checks independently confirm GalaxyPlay call-key selectors.
- Use the minimum positive maneuver capacity among subscribed components to
  reuse bounded U16 indices. Definitions still precede references. A single-slot
  receiver must be cleared before redefining the active slot to avoid combining
  a new arrow with the old distance.
- Hook Switch (Telephony usage 0x20) routes to the verified host answer key;
  Drop (0x26) routes to end/reject. Flash (0x21) has no verified host contract,
  so remains unsupported. Opening the phone app stays a requestUI operation.

## Risks / Trade-offs

- Receiver code changes → stage only a clean source checkout, record hashes and
  fail on missing expected source boundaries; never silently emulate a parser.
- Storage-slot reuse can briefly update an already referenced definition →
  single-slot reset before definition; complete definition/reference batches and
  existing stale-generation guards remain mandatory.
- Android ordinary phone-state observation cannot supply precise call phases or
  cellular PCM → report these as unavailable; do not label OFFHOOK as ACTIVE.
- DiPlay has changed since GalaxyPlay → corroborate target-specific facts using
  the original APK; preserve the existing GalaxyPlay numeric core.
