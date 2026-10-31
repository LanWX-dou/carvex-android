# Firmware Protocol Docsets

Each docset covers one protocol layer and normally uses this structure:

| Path | Purpose |
|---|---|
| `spec/` | Implementation-facing protocol requirements |
| `analysis/` | Function-level review and evidence notes |
| `source/` | Original bytes and assembly slices |
| `readable/` | Automatically produced decompiler output |
| `runtime/` | Captures and runtime evidence |
| `tools/` | Verification and extraction helpers |
| `verify.py` | Structural, hash and local-vector checks |

## Docsets

| Docset | Scope |
|---|---|
| `bluetooth_rfcomm/` | Bluetooth discovery, SDP, RFCOMM and multiplexing |
| `iap2_link_establish/` | Detection, SYN, ACK and link establishment |
| `iap2_control_session/` | Identification, authentication and control sessions |
| `carplay_network_bootstrap/` | Wi-Fi configuration and network handoff |
| `airplay_mdns_discovery/` | Bonjour discovery and receiver metadata |
| `airplay_control_plane/` | RTSP, control and event channels |
| `airplay_fairplay_crypto/` | FairPlay and encrypted control material |
| `iap2_airplay_tunnel/` | iAP2 tunnel and AirPlay transport |
| `airplay_video_channel/` | Video SETUP, framing and first frame |
| `airplay_audio_mic_channel/` | Audio, microphone and RTP/RED |
| `iap2_input_business_lifecycle/` | HID, touch, business messages and lifecycle |
| `airplay_rtp_timing/` | RTP clocks and timing |
| `iap2_airplay_debug_troubleshoot/` | Cross-layer diagnostics |

## Rules

- `source/` and `readable/` are evidence layers, not implementation text.
- Generated manifests must match the current source hashes.
- Missing evidence stays `OPEN`; do not fill it with assumptions.
- Local tests prove only the checked conditions, not real vehicle interop.
