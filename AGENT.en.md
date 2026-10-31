# AGENT.md

[中文](AGENT.md) | English

Mandatory reading before any protocol implementation, debugging, or code change in this workspace. If you work inside `android/`, read [`android/AGENT.en.md`](android/AGENT.en.md) as well; that file adds Android-only module, signing, flavor and test rules.

## 0. Read order

1. This file.
2. `android/AGENT.en.md` when the change touches Android code or builds.
3. The `README.en.md` and relevant `spec/` chapter of the affected research docset.
4. `docs/architecture.md`, `docs/workflows.md`, `docs/status.md`.

Do not start with the current Android implementation. It is a candidate, not evidence.

## 1. Goal and baseline

This is not a CarPlay-only project. The goal is a multi-protocol connectivity layer
between phones and head units, covering CarPlay, HiCar, CarLife, ICCOA and ecosystems such
as CarWith and CAR+. CarPlay is the first protocol and currently has the strongest
evidence chain. Each protocol needs its own evidence; conclusions must not be copied
across protocols.

For the CarPlay path, the core rule is:

> Use the original iPhone IPSW firmware as the only baseline for sender behavior, and
> reproduce its fields, timing and state transitions closely enough to interoperate with
> CarPlay-capable head units.

CarPlay baseline firmware:

```text
firmware/ipsw/iPhone18,1_27.0.1_24A446_Restore.ipsw
```

The version must be read from the IPSW's `BuildManifest.plist`; do not infer it from the
file name.

Current CarPlay research path:

```text
Bluetooth RFCOMM
  -> iAP2 link
  -> Identification / Authentication
  -> Wi-Fi handoff
  -> AirPlay control
  -> RTSP SETUP
  -> video / audio / microphone
  -> normal teardown and reconnect
```

Implementation strategy:

- Reproduce firmware behavior first. Compatibility improvements require firmware or device evidence and must not become per-vehicle or configuration-table branches.
- The goal is broad head-unit compatibility without vehicle configuration files, driven by the protocol stack, negotiated fields and capability bits.
- The Android side is modular. A new protocol should be a new `protocol-*` module implementing `protocol-api`, wired through `bridge`, `platform-android` and `host-*` without modifying the main CarPlay path.
- Host and mirroring integrations use separate `host-*` adapters; adding Xiaomi CarWith, OPPO CAR+ or another ecosystem must not modify protocol modules.

## 2. Repository and research layout

The root repository references `android/` and `firmware/` as git submodules:

| Directory | Reference | Contents |
|---|---|---|
| `carvex-research/` (this directory) | `iamr0s/carvex-carplay-research` | Research documents, connection analysis, project documentation and README donation images |
| `android/` | submodule `iamr0s/carvex-android` | **CarVeX**: the Android implementation of multi-protocol vehicle connectivity, currently CarPlay-first; includes the protocol stack, session orchestration and five vendor hosts |
| `firmware/` | submodule `iamr0s/carvex-ios-firmware` | CarPlay firmware evidence, extracts, decompiled text, analysis tools and setup; the raw IPSW and head-unit firmware are not tracked |

`research/` has two entry points:

- `research/protocol/`: multi-protocol research docsets, currently CarPlay/iPhone sender-side first. CarPlay is split into protocol-layer docsets (RFCOMM, iAP2, identification/authentication, Wi-Fi handoff, AirPlay, FairPlay, video, audio/mic, input, RTP timing and more); other protocols follow the same structure.
- `research/connection/`: connection lifecycle, failure recovery, cross-stage timing and field differences.

Layout:

```text
D:\carvex-research\
├─ AGENT.md / AGENT.en.md        workspace rules
├─ README.md / README.en.md      entry points
├─ assets/donation/              README donation images
├─ docs/                         architecture, workflows, status, decisions
├─ research/
│  ├─ protocol/                  phone-side protocol docsets
│  └─ connection/                connection lifecycle and recovery
├─ firmware/                     git submodule carvex-ios-firmware
└─ android/                      git submodule carvex-android, the CarVeX implementation
```

### `docs/`

Project-level documentation only; protocol specifications do not live here.

```text
docs/
├─ README.md
├─ architecture.md
├─ workflows.md
├─ status.md
└─ decisions/
```

### `research/protocol/`

Phone-side protocol research. Formal, verifiable docsets. A docset normally has:

```text
research/protocol/<docset>/
├─ spec/         normative protocol requirements
├─ analysis/     function-level analysis and reasoning
├─ source/       original bytes and assembly slices
├─ readable/     generated decompiler output
├─ runtime/      captures, logs and runtime samples
├─ tools/        docset-specific tools
└─ verify.py     structural and evidence verifier
```

Current docsets cover Bluetooth RFCOMM, iAP2 link, identification/authentication/control
session, Wi-Fi bootstrap, mDNS, AirPlay control, FairPlay, iAP2 tunnel, video, audio and
microphone, input and business lifecycle, RTP timing, and cross-layer troubleshooting.

### `research/connection/`

Connection lifecycle, failure recovery and cross-stage timing. Its `README.md` is the
entry point and carries the latest evidence state; chapter links are in
`research/connection/spec/`.

### `firmware/`

git submodule `carvex-ios-firmware`. Tracked:

- `ipsw/SOURCE.md` and `SHA256SUMS.partial`: source, size and SHA256 of the raw IPSW.
- `extracted/24A446/binaries`, `components` and `headers`: key binaries and headers extracted from the IPSW.
- Top-level summaries, key JSON, assembly and focused analysis under `analysis`;
  per-function slice directories stay local.
- Scripts and configuration under `tools` and `setup`.

Not tracked: raw `*.ipsw`, `extracted/*/images`, `extracted/*/dyld`, `headunits/`,
Ghidra projects/caches, and download archives. The raw IPSW is obtained through the
download entry and SHA256 in the firmware README; it is not redistributed here.

### `android/`

**CarVeX**, the Android implementation of multi-protocol vehicle connectivity, currently
CarPlay-first. It is the git submodule `iamr0s/carvex-android` and must remain buildable on
its own. Module
responsibilities and build rules are in [`android/AGENT.md`](android/AGENT.en.md).

## 3. Protocol evidence: firmware for CarPlay, separate evidence for other protocols

For the CarPlay path, do not derive Apple behavior from existing Android code, old
documentation, string names, selector names, decompiler output, or another product's
implementation.

Other protocols (HiCar, CarLife, ICCOA, CarWith, CAR+) must not reuse iPhone firmware
conclusions. Each needs its own phone-side implementation, public specification, captures
and head-unit behavior, with the same evidence levels.

### Evidence levels

- `CONFIRMED` — original firmware bytes, assembly, or a closed call/data-flow chain.
- `INFERRED` — supported by evidence, but with unread branches or boundaries.
- `OPEN` — insufficient evidence. Do not fill it from experience.

### Allowed as evidence

- Original Mach-O, dyld cache and system components inside the IPSW.
- Disassembly of original bytes.
- Function addresses, control flow and data flow tied to the target behavior.
- Head-unit firmware paths that receive, ACK, lock, clean up, or change state.
- Runtime logs and captures bound to the exact firmware version.

### Index only

- Old Markdown documents.
- Function names, selectors, strings and generated C.
- The current Android implementation.
- Other products' behavior.

Decompiler output is a reading aid only. Any change to fields, ordering, timeouts, state
transitions or error branches must go back to original bytes and assembly.

### State machines come from the protocol stack, not configuration

The implementation must not be a per-vehicle or configuration-table state machine. States,
events, transition conditions, timeouts and cleanup paths are derived from the firmware's
protocol stack and framework paths: message dispatch, callbacks, timers and error branches.

Configuration may provide runtime inputs such as identity, addresses, certificates, codec
parameters and transport capabilities. It must not:

- select a different state machine per vehicle or configuration;
- skip declaration, authentication, session synchronization or cleanup;
- change transition order, event ownership or timeout semantics;
- use "this vehicle model connects" as a branch condition.

Vehicle differences must be expressed through negotiated fields, capability bits and actual
messages, not configuration branches. Unknown or unclosed paths stay `OPEN`.

## 4. Rules for changing protocol code

Before editing:

1. Run `git status` and inspect existing uncommitted changes.
2. Back up every file you are about to change to
   `local-backups/<YYYY-MM-DD>-<topic>/`.
3. Never revert, overwrite or reformat the user's unrelated changes.

Every production change must state:

1. The IPSW binary address or code branch it follows.
2. Why the current implementation differs.
3. How the new implementation aligns with firmware.
4. Which tests verify it.
5. Whether it has been verified in a vehicle.

Forbidden:

- Per-vehicle or per-model hardcoded branches.
- Blind fixed delays.
- Unconditional retransmission.
- Skipping declaration or authentication checks.
- Replacing firmware evidence with a third-party implementation.
- Closing an `OPEN` item without evidence.
- Adding features that depend on a guess about Apple behavior.

The Android signing keystore and passwords are intentionally public; do not treat them as
secrets. Do not commit `local.properties`, device-private data or other credentials. The donation QR images in `android/app/src/main/assets/` are intentional app
assets; do not remove or rename them without updating the app, both READMEs and
`LocalVideoDisplay.kt`.

## 5. Debugging workflow

### 5.1 Locate the first broken stage

Check in order:

```text
BLUETOOTH
  -> DETECT
  -> SYN / SYNACK / ACK
  -> AUTH
  -> IDENTIFICATION
  -> WIFI HANDOFF
  -> ENDPOINT DISCOVERY
  -> AIRPLAY CONTROL
  -> RTSP SETUP
  -> VIDEO / AUDIO / INPUT
```

Do not start from the last exception. Find the first message, state or thread that departs
from the firmware expectation.

### 5.2 Logs must contain

- APK versionCode and build type
- session ID
- target Bluetooth address
- connection initiation direction
- negotiated link/control version
- complete session table
- SYN/SYNACK/ACK sequence numbers
- last successfully sent message
- next expected message
- first timeout or resource-close point
- actual Network, interface and address source

### 5.3 Commands

Android connection log:

```powershell
adb devices
adb logcat -c
adb logcat -v time > carvex-log.txt
```

Bluetooth state:

```powershell
adb shell dumpsys bluetooth_manager > bluetooth-state.txt
```

Network state:

```powershell
adb shell dumpsys connectivity > connectivity-state.txt
adb shell ip addr
adb shell ip route
```

### 5.4 Log interpretation rules

- A link ACK does not mean a business message was accepted.
- `1D00` ACK does not mean the head unit will send `1D01`.
- A successful RFCOMM connection does not mean the iAP service is established.
- Receiving SYN does not mean link synchronization is complete.
- Receiving `5703` does not mean Wi-Fi is connected.
- Receiving `4301` does not mean the AirPlay endpoint is reachable.
- SETUP 200 does not mean the first frame succeeded.

## 6. Research and verification

### 6.1 External toolchain

The repository is not fully self-contained. After moving the directory, system-level
dependencies and machine-local configuration must be prepared again.

| Tool / dependency | Purpose | Moves with repo |
|---|---|---|
| Git | versioning, source hashes, Gradle version code | No |
| Python 3.10+ | firmware research, verifiers, tool scripts | No |
| `capstone==5.0.7` | ARM64 disassembly verification | No |
| `unicorn==2.1.4` | bounded ARM64 execution verification | No |
| `cryptography==41.0.7` | verifier crypto helpers | No |
| `lzfse>=0.3.0` | sysdiagnose logarchive parsing (optional) | No |
| WSL2 Ubuntu 24.04 | firmware tooling and Python environment | No |
| Java 21 JDK | Ghidra 12.1.4 | No |
| Android Studio JBR / JDK 17+ | Gradle and Kotlin builds | No |
| Android SDK 37 + build-tools 36.0.0 | `compileSdk 37` and packaging | No |
| `adb` | device logs, Bluetooth and network state | No |
| Gradle Wrapper | Android build | Yes; still needs Java |
| Ghidra 12.1.4 | firmware decompilation | Yes; under `firmware/tools/ghidra` |
| `ipsw` CLI | IPSW, dyld and Mach-O inspection | Archived in repo; currently installed in WSL at `/usr/local/bin` |
| `apfs-fuse` / `apfsutil` | APFS image access | No; installed by `install-linux-tools.sh` |
| `ffmpeg`, `tshark`, `tcpdump` | audio/video samples and capture verification | No; optional, report SKIP when missing |

Machine-local configuration that must never be treated as repository content:

- `android/local.properties` (`sdk.dir`)
- `JAVA_HOME`
- `ANDROID_HOME` / `ANDROID_SDK_ROOT`
- `GHIDRA_HOME`
- `GHIDRA_ANALYZE_HEADLESS`

Python dependencies:

```powershell
cd D:\carvex-research
python -m pip install -r requirements.txt
```

WSL toolchain:

```bash
cd /mnt/d/carvex-research/firmware/setup
sudo bash install-linux-tools.sh
```

Ghidra environment:

```bash
source /mnt/d/carvex-research/firmware/setup/ghidra-env.sh
```

After moving the project, recheck `local.properties`, Android SDK paths, Java versions,
WSL paths, whether `ipsw` is on `PATH`, Ghidra paths, and Python package versions.

### 6.2 Firmware docsets

Full verification:

```powershell
cd D:\carvex-research
python -B firmware/tools/verify-all.py
```

One or several docsets:

```powershell
python -B firmware/tools/verify-all.py --only bluetooth_rfcomm
python -B firmware/tools/verify-all.py --only iap2_link_establish iap2_control_session
```

Direct docset verifier:

```powershell
cd D:\carvex-research\research\protocol\bluetooth_rfcomm
python -B verify.py
```

`verify-all.py` distinguishes `PASS`, `SKIP` and `FAIL`. `SKIP` means a dependency is
missing; it is not a pass. Do not report a skipped evidence check as verified.

### 6.3 Android

```powershell
cd D:\carvex-research\android
.\gradlew.bat :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin
```

Additional modules when touched:

```powershell
.\gradlew.bat :core:testDebugUnitTest :bridge:testDebugUnitTest
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest
```

The CI workflow also runs `:pcm-core:test`, `:host-api:test`, every flavor's unit tests,
`lintRelease` and `assembleRelease`. Local verification must at least cover every module
whose behavior you changed.

## 7. Field testing

1. Confirm the code is at a verifiable stage.
2. Commit first so the tested build is traceable.
3. The user packages and installs unless they explicitly ask otherwise.
4. Test one hypothesis at a time.
5. Keep the complete log from the start of the connection, not only the final exception.
6. Record manual disconnects, stale sessions on the head unit, and whether the head unit
   was restarted.
7. Do not close a compatibility issue after a single success.

Results:

```text
PASS      complete expected stage reached
PARTIAL   some stages reached, with a clear first breakpoint
FAIL      target stage not reached
OPEN      insufficient evidence
```

## 8. Current focus

Connection work must continue to be checked against firmware for:

- RFCOMM direction arbitration.
- SYN/SYNACK session-table negotiation.
- iAP2 Identification startup conditions.
- Session routing for control CSMs.
- Wi-Fi handoff and late endpoints.
- Normal disconnect, resource cleanup and reconnect-generation isolation.

Multi-protocol work only reserves `protocol-*` / `host-*` module boundaries. Until HiCar,
CarLife, ICCOA or another protocol is implemented, do not claim support in code, UI or
documentation.

A phenomenon where "another implementation can connect" is a candidate hypothesis only,
never a direct basis for a production change.

## 9. Documentation maintenance

- The entry documents are four pairs: `README.md` / `README.en.md`, `AGENT.md` /
  `AGENT.en.md`, `android/README.md` / `README.en.md`, and
  `android/AGENT.md` / `AGENT.en.md`. The Chinese file is primary. Update both
  languages in the same change; do not leave one side stale.
- `README.md` is onboarding material. `AGENT.md` is normative. Protocol conclusions belong
  in `research/`, not in either README.
- When a path, command, module, flavor, package name or signing rule changes, update the
  layout and documentation tables in both language versions and both repositories.
- Durable architecture or process decisions go to `docs/decisions/NNNN-title.md` with
  context, decision, consequences and evidence links. Update `docs/README.md` when adding
  a document type.
- Keep one source of truth. Do not copy a full protocol spec into `docs/` or a README;
  link to the docset instead.
- The root repository, `android/` and `firmware/` each keep their own `assets/donation/`
  folder for their README. The Android repository also bundles copies under
  `app/src/main/assets/` for `LocalVideoDisplay.kt`. Never reference images across
  repository boundaries. Renaming an image requires updating every copy and README.
  Donations must never gate a feature.
