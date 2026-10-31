# Workspace Architecture

The project targets multi-protocol vehicle connectivity between phones and head units;
CarPlay is the first protocol and currently has the strongest evidence chain. The root repository
tracks `android/` and `firmware/` as git submodules:

```text
carvex-research/   Research documents, connection analysis, project docs
  research/protocol/    Phone-side protocol docsets
  research/connection/  Connection lifecycle and recovery
  docs/                 Project-level documentation
  assets/donation/      README donation images

android/           CarVeX, the Android implementation of CarPlay
firmware/          carvex-ios-firmware, extracted firmware and analysis tools
```

## Ownership

- `firmware/ipsw`: only `SOURCE.md` and checksums are tracked; the raw IPSW is local.
- `firmware/extracted`: extracted binaries, components and headers are tracked; images and
  dyld caches are local.
- `firmware/analysis`: summaries and key JSON are tracked; per-function slices and Ghidra
  caches are local.
- `research/protocol`: multi-protocol research docsets, currently CarPlay/iPhone sender-side first.
- `research/connection`: connection lifecycle, failure recovery and cross-stage analysis.
- `android`: implementation, tests, signing material and build configuration.

## Dependency Direction

```text
firmware -> research -> android
```

Implementation must not be treated as protocol evidence. Research conclusions must point
back to original firmware bytes or identified runtime captures.
