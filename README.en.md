# CarVeX — Vehicle Connectivity Protocol Research and Implementation

[中文](README.md) | English

> The goal is to connect phones with head units across multiple vehicle connectivity protocols, including CarPlay, HiCar, CarLife, ICCOA, CarWith and CAR+. **CarPlay is the first protocol being reproduced field by field from iPhone firmware.**
>
> Status: research preview. The CarPlay path is the most complete; other protocols are extension directions and remain `OPEN` where unimplemented. Real-vehicle interoperability is **not** claimed.

## Why this exists

The era seems to open wider and close tighter at the same time. Each vendor turns its protocol into a fence and its ecosystem into a rope, claiming openness while enclosing territory; users are lifted high and then discarded when no longer useful.

We want interoperability to return to the protocol itself: not a vendor configuration table, not a lock-in to one ecosystem, but behavior derived from the protocol stack, negotiated fields and capability bits so that phones and head units can connect as broadly as possible.

> “These walls are funny. First you hate 'em, then you get used to 'em. Enough time passes, you get so you depend on them. That's institutionalized.”
>
> — Red, *The Shawshank Redemption*

## Donation

If this project has helped you, you are welcome to donate as a thank-you. Donations are optional and do not constitute any support commitment.

<p align="center">
  <img src="assets/donation/alipay.jpg" width="200" alt="Alipay">
  <img src="assets/donation/wxpay.jpg" width="200" alt="WeChat Pay">
  <img src="assets/donation/binance.jpg" width="200" alt="Binance Pay">
</p>

<p align="center">Alipay · WeChat Pay · Binance Pay</p>

## Community

The CarVeX developer group on QQ, for protocol work, head-unit compatibility and field
debugging.

<p align="center">
  <a href="https://qm.qq.com/cgi-bin/qm/qr?k=KyWBLDmahaZW2TKDU51x3hs-6irSn6UX&amp;jump_from=webapi&amp;authKey=qFX04xLs8pXluNhr7O18mECpkt8MP3ooZzKf81NPWjq9C4QDf42TixqzTWrEXQG1">
    <img src="https://pub.idqqimg.com/wpa/images/group.png" alt="CarVeX developer group (QQ)">
  </a>
</p>

## What this is

This is not a CarPlay-only research project. The goal is multi-protocol vehicle connectivity: connect an Android phone to head units supporting CarPlay, HiCar, CarLife, ICCOA, and ecosystems such as CarWith and CAR+. CarPlay is the first protocol reproduced from iPhone firmware; other protocols are added through the same module boundaries.

The root repository references two independent repositories as Git submodules:

1. `carvex-research` (this directory, root repository `iamr0s/carvex-carplay-research`): research documents and connection analysis.
2. `android/` (git submodule, repository `iamr0s/carvex-android`): **CarVeX**, the Android implementation of multi-protocol vehicle connectivity, currently CarPlay-first.
3. `firmware/` (git submodule, repository `iamr0s/carvex-ios-firmware`): CarPlay firmware evidence, extracts, decompiled text and analysis tools. The raw IPSW and head-unit firmware are not tracked.

`research/` has two parts: `research/protocol/` is phone-side protocol research, and `research/connection/` covers connection lifecycle and failure recovery.

Design goal: drive behavior from the protocol stack and negotiated fields, not from per-vehicle or configuration-table state machines. For CarPlay, the first protocol, reproduce iPhone firmware field by field and timing by timing, then improve compatibility where evidence supports it. Other protocols plug into the same module boundaries. The Android side is modular: protocol implementations, platform adapters, session orchestration and host integration are decoupled. Adding HiCar, CarLife, ICCOA or another protocol means adding a separate protocol module, not rewriting the existing CarPlay implementation. Host and mirroring integrations are modular too: Xiaomi CarWith, OPPO CAR+ and similar ecosystems plug in through `host-*` adapters without changing the protocol stack.

The CarPlay path researched so far:

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

## Status and scope

- This is a research workspace, not a finished product. Local tests prove only the conditions they check; they do not prove interoperability with a real head unit.
- State machines and events are derived from the protocol stack and negotiated fields, not from a per-vehicle or configuration-table state machine.
- `CONFIRMED`, `INFERRED` and `OPEN` are kept separate on purpose. Missing evidence is never filled in with assumptions.
- CarPlay is the current implementation. HiCar, CarLife, ICCOA and others are not implemented yet; only module boundaries are reserved, and unfinished parts stay `OPEN`.
- Head-unit firmware and third-party receiver software are not modified here.
- This project is not affiliated with Apple, Baidu, or any phone, vehicle or head-unit vendor. CarPlay is a trademark of Apple Inc.

## Repository layout

| Path | Git reference | Purpose |
|---|---|---|
| root | root repository `iamr0s/carvex-carplay-research` | Research documents, connection analysis, project documentation and README donation images |
| `android/` | submodule `iamr0s/carvex-android` | **CarVeX**: the Android implementation of multi-protocol vehicle connectivity, currently CarPlay-first |
| `firmware/` | submodule `iamr0s/carvex-ios-firmware` | CarPlay firmware evidence, extracts, decompiled text and analysis tools |
| `research/protocol/` | root repository | Multi-protocol research docsets, currently CarPlay/iPhone sender-side first |
| `research/connection/` | root repository | Connection lifecycle, failure recovery and cross-stage timing |
| `docs/` | root repository | Project-level architecture, workflows, status and decision records |
| `assets/donation/` | root repository | Donation QR images used by the READMEs |
| `firmware/ipsw/` | `carvex-ios-firmware` | `SOURCE.md` and checksums only; the IPSW is obtained through the download entry |
| `firmware/extracted/` | `carvex-ios-firmware` | Mach-O files, components and headers extracted from the IPSW |
| `firmware/analysis/` | `carvex-ios-firmware` | Summaries, key JSON and assembly; per-function slices and Ghidra caches are not tracked |
| `firmware/tools/`, `firmware/setup/` | `carvex-ios-firmware` | Extraction, disassembly, symbol and verification tools plus environment setup |
| `local-backups/` | not committed | Local pre-edit snapshots |

## CarPlay evidence flow

```text
firmware/ipsw
  -> firmware/extracted
  -> firmware/analysis
  -> research/protocol/ and research/connection/
  -> android/
```

Raw firmware is authoritative. Generated extraction and analysis data must be
reproducible from the original files. Old notes, function names, selectors and
decompiler output are indexes, not protocol proof.

## Evidence rules

- Protocol behavior must be traced to original firmware bytes and instructions.
- `CONFIRMED`, `INFERRED` and `OPEN` stay separate. Only `CONFIRMED` may close a
  protocol item; `INFERRED` changes keep their remaining uncertainty explicit.
- A third-party implementation can suggest a hypothesis, never establish one.
- Do not claim real interoperability without matching device-side evidence.
- Do not modify head-unit firmware or external receiver software.

## Quick start

Firmware docsets, in WSL/Linux:

```bash
cd /mnt/d/carvex-research
python3 -m pip install -r requirements.txt
python3 -B firmware/tools/verify-all.py
```

Single docset or a subset:

```bash
python3 -B firmware/tools/verify-all.py --only iap2_link_establish iap2_control_session
cd research/protocol/bluetooth_rfcomm && python3 -B verify.py
```

Android build, on Windows:

```powershell
cd D:\carvex-research\android
.\gradlew.bat :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin
```

The Android build uses the signing material published under `android/.signing/`; see
[`android/README.en.md`](android/README.en.md#build) and
[`android/AGENT.en.md`](android/AGENT.en.md). Missing signing material is a
hard configuration failure by design.

## Documentation map

| Document | Read it for |
|---|---|
| [`AGENT.en.md`](AGENT.en.md) | Mandatory process, evidence rules, debug and verification workflow |
| [`android/AGENT.en.md`](android/AGENT.en.md) | Android-only module, signing, flavor and test rules |
| [`docs/README.md`](docs/README.md) | Project documentation index |
| [`docs/architecture.md`](docs/architecture.md) | Workspace layers and ownership boundaries |
| [`docs/workflows.md`](docs/workflows.md) | Research and Android change workflows |
| [`docs/status.md`](docs/status.md) | Current structure and priorities |
| [`research/protocol/README.md`](research/protocol/README.md) | Docset structure and scope |
| [`research/connection/README.md`](research/connection/README.md) | Latest connection research, evidence and open items |
| [GalaxyPlay / DiPlay interoperability record](research/connection/spec/receiver-source-interop-20261111.md) | Separate navigation/call repairs, receiver source tests and field acceptance limits |
| [`android/README.en.md`](android/README.en.md) | Application features, build, signing, brands and status |

Durable architecture or process decisions belong in `docs/decisions/` as numbered
records. Protocol specifications belong in `research/`, not in this README.

## License

GNU General Public License v3.0. See [`LICENSE`](LICENSE).

Not affiliated with Apple, Baidu, or any phone, vehicle or head-unit vendor. CarPlay is a trademark of Apple Inc.
