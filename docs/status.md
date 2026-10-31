# Current Status

```text
firmware/             carvex-ios-firmware: CarPlay firmware extracts, analysis, tools
research/protocol/    Phone-side protocol research docsets
research/connection/  Connection lifecycle research
android/              CarVeX: CarPlay Android implementation
docs/                 Project-level documentation
```

Current priorities:

- Keep the CarPlay protocol specs aligned with original firmware and the extracted binaries.
- Reserve clean module boundaries for HiCar, CarLife, ICCOA and other protocols; do not
  claim them as supported before they are implemented.
- Resolve iAP2 session negotiation and connection direction behavior.
- Preserve complete evidence for field-test changes.
- Do not claim vehicle interoperability without matching device logs.

Repository notes:

- `firmware/` and `android/` are separate repositories tracked by the root
  `carvex-carplay-research` repository as git submodules.
- The raw IPSW and head-unit firmware are not distributed; see `firmware/README.md`.
- The Android signing keystore and passwords are intentionally public for reproducible
  builds and are not a security boundary.
