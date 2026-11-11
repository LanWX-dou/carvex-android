## Why

GalaxyPlay 0.1.212 is the user's actual head-unit receiver; DiPlay source at
615b32ce0b40cd0b99ce94ba23a512001553684f provides an additional receiver-side
reference. Current tests do not execute that receiver's parsers, and the
Telephony Hook Switch is incorrectly translated to opening the phone UI.

## What Changes

- Add opt-in JVM interoperability tests executing the supplied receiver source
  against CarVeX wire encoders, subscriptions, audio declarations and HID reports.
- Correct verified call-key semantics without changing the normal music path.
- Bound navigation maneuver definitions by the negotiated storage capacity.
- Record source/APK hashes, independently distinguish Apple sender evidence from
  receiver behavior, and list unavailable phone metadata/audio sources explicitly.
- Commit navigation and call changes separately. Do not install or modify DiPlay.

## Capabilities

### New Capabilities

- `receiver-source-interop`: Reproducible, source-bound receiver contract checks
  and capability-driven navigation/call interoperability.

### Modified Capabilities

None.

## Impact

Android protocol/navigation and CarLife mixing key adapter; optional test tooling
and research records. No added production dependency on DiPlay. Existing
Bluetooth-to-Wi-Fi transport remains the implementation scope. The phone is
Android 17; DiPlay is not enabled on the vehicle. Actual GalaxyPlay display,
full call metadata and cellular PCM routing require separate field evidence.
