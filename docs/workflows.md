# Workflows

## Protocol Research

1. Locate the original IPSW, extracted binary or head-unit firmware input.
2. Extract the exact binary or source artifact.
3. Record hashes and function addresses.
4. Review assembly and only use decompiler output as a reading aid.
5. Update the relevant `research/` spec and evidence.
6. Run the local verifier.

## Android Change

1. Find the corresponding firmware-derived requirement.
2. Check the current implementation and existing uncommitted changes.
3. Back up files before protocol edits.
4. Add focused tests.
5. Run:

```powershell
cd D:\carvex-research\android
.\gradlew.bat :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin
```

6. Commit before creating an APK for field verification.

The Android repository is `android/` (submodule `iamr0s/carvex-android`). The firmware
repository is `firmware/` (submodule `iamr0s/carvex-ios-firmware`). The root repository
`carvex-carplay-research` tracks both as git submodules.
