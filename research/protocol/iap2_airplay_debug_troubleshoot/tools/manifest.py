#!/usr/bin/env python3
"""Inventory authored docs and explicitly selected dependencies; never collects private captures."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
DOCS = ROOT.parent
DEPENDENCIES = [
    "iap2_link_establish/reference-impl/iap2_link.py",
    "iap2_link_establish/spec/02-framing-and-checksum.md",
    "iap2_link_establish/spec/04-seq-ack-retransmit.md",
    "iap2_link_establish/spec/07-errors-teardown.md",
    "iap2_control_session/spec/09-device-side-startup.md",
    "iap2_control_session/spec/11-device-authentication.md",
    "iap2_input_business_lifecycle/reference-impl/input_codec.py",
    "iap2_input_business_lifecycle/reference-impl/lifecycle_fsm.py",
    "iap2_input_business_lifecycle/analysis/12-lifecycle-and-empty-param-audit.md",
    "iap2_input_business_lifecycle/analysis/14-nowplaying-dataflow-audit.md",
    "airplay_audio_mic_channel/reference-impl/audio_depacketizer.py",
    "airplay_audio_mic_channel/analysis/09-message-coordinate-audit.md",
    "airplay_audio_mic_channel/analysis/10-config-field-audit.md",
    "airplay_audio_mic_channel/tools/verify-config-fields.py",
    "airplay_audio_mic_channel/analysis/11-format-id-map-audit.md",
    "airplay_audio_mic_channel/spec/11-format-id-map.md",
    "airplay_audio_mic_channel/tools/verify-format-map.py",
    "airplay_audio_mic_channel/analysis/12-capability-policy-audit.md",
    "airplay_audio_mic_channel/spec/12-capability-selection.md",
    "airplay_audio_mic_channel/tools/verify-capability-policy.py",
    "airplay_fairplay_crypto/reference-impl/fairplay_crypto.py",
    "airplay_fairplay_crypto/analysis/11-screen-aad-and-record-boundaries.md",
    "airplay_video_channel/analysis/06-wrapper-and-header-audit.md",
    "airplay_video_channel/analysis/07-codec-config-and-flags.md",
    "airplay_video_channel/tools/verify-codec-config.py",
    "airplay_video_channel/analysis/02-screen-record-format.md",
    "airplay_video_channel/source/asm/AirPlaySender/f_2519b508c.s",
    "airplay_video_channel/tools/verify-wrapper.py",
    "airplay_control_plane/analysis/13-record-aad-nonce-and-key-direction.md",
    "airplay_control_plane/analysis/14-pair-verify-key-schedule.md",
    "airplay_control_plane/analysis/15-keyholder-role-and-hkdf.md",
    "airplay_control_plane/source/asm/CoreUtils/f_18be5021c.s",
    "airplay_control_plane/tools/verify-keyholder.py",
]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def authored_files():
    # Only authored artifact file types; captures/logs/private never auto-collected.
    return sorted(p for p in ROOT.rglob("*") if p.is_file()
                  and p.suffix in {".md", ".py", ".json"}
                  and not {"__pycache__", "private", "captures", "logs"}.intersection(p.relative_to(ROOT).parts)
                  and p != ROOT / "manifest.json")


def main():
    data = {"docset": ROOT.name, "date": "2026-10-26",
            "scope": "authored files and explicit dependencies; not runtime validation",
            "files": {p.relative_to(ROOT).as_posix(): sha(p) for p in authored_files()},
            "dependencies": {name: sha(DOCS / name) for name in DEPENDENCIES}}
    (ROOT / "manifest.json").write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"manifest: {len(data['files'])} authored files, {len(data['dependencies'])} dependencies")


if __name__ == "__main__":
    main()
