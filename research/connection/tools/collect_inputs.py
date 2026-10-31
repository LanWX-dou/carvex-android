"""Collect provenance and redacted observations, without editing reference trees.

The existing PacketLogger parser is imported only after its top-level code was
reviewed. Its writing main() is never called. Generated output is restricted to
this new documentation directory. This is not an interoperability test.
"""
from __future__ import annotations

import collections
import argparse
import datetime as dt
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import plistlib
import re
import subprocess
import sys
import zipfile

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
ROOT = DOC.parent
PHONE = Path("D:/carvex-research/android") if os.name == "nt" else Path("/mnt/d/carvex-research/android")
FW = ROOT / "firmware"


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def file_record(path, role):
    return {"path": str(path.resolve()), "bytes": path.stat().st_size,
            "sha256": digest(path), "role": role}


def write_generated(name, value):
    target = (DOC / "evidence" / name).resolve()
    if not target.is_relative_to(DOC.resolve()):
        raise ValueError("Output outside authorized documentation directory")
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def baseline():
    archive = FW / "ipsw/iPhone18,1_27.0.1_24A446_Restore.ipsw"
    with zipfile.ZipFile(archive) as source:
        raw_manifest = source.read("BuildManifest.plist")
        manifest = plistlib.loads(raw_manifest)
    records = [file_record(archive, "LOCAL_IPSW_UNVERIFIED_SIGNATURE")]
    for name in ("AirPlaySender", "AirPlaySupport", "APTransport", "CarKit", "CoreUtils",
                 "MFAAuthentication", "MobileWiFi", "WiFiSharing", "Platform-Bluetooth"):
        records.append(file_record(FW / f"extracted/24A446/binaries/{name}/{name}", "EXTRACTED_IPHONE_BINARY"))
    component_root = FW / "extracted/24A446/components/24A446__iPhone18,1/root"
    for name in ("accessoryd", "carkitd", "bluetoothd"):
        matches = list(component_root.rglob(name))
        records.extend(file_record(path, "EXTRACTED_IPHONE_BINARY") for path in matches if path.is_file())
    for relative in (
        "bridge/src/main/java/io/github/iamr0s/carvex/session/SessionController.kt",
        "bridge/src/main/java/io/github/iamr0s/carvex/session/VideoEncoder.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/ReceiverDiscovery.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/CarPlaySourceIdentity.kt",
    ):
        records.append(file_record(PHONE / relative, "CURRENT_ANDROID_IMPLEMENTATION_NOT_APPLE_SPEC"))
    def git(*args):
        return subprocess.check_output(["git", "-C", str(PHONE), *args], text=True, encoding="utf-8").strip()
    report = {
        "collected_at": dt.datetime.now(dt.timezone.utc).isoformat(),
        "firmware": {"build": manifest.get("ProductBuildVersion"), "version": manifest.get("ProductVersion"),
                     "products": manifest.get("SupportedProductTypes"), "version_source": "IPSW BuildManifest.plist",
                     "manifest_sha256": hashlib.sha256(raw_manifest).hexdigest(),
                     "apple_signature_verified": False, "download_origin_verified": False},
        "phone_git_head": git("rev-parse", "HEAD"),
        "phone_worktree_dirty": bool(git("status", "--porcelain")),
        "files": records,
        "limits": ["Hash verifies identity, not Apple signature or extraction correctness.",
                   "Dirty current source is identified by per-file hash, not HEAD alone.",
                   "No fresh extraction or runtime execution of the IPSW performed."],
    }
    write_generated("baseline.json", report)
    return report


def captures():
    parser = FW / "tools/ipsw-research/reassemble-audit-captures.py"
    spec = importlib.util.spec_from_file_location("readonly_capture_parser", parser)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    cases = []
    for directory in sorted((ROOT / "sysdiagnose").glob("sysdiagnose_*")):
        build = directory.name.rsplit("_", 1)[-1]
        for path in sorted((directory / "logs/Bluetooth").glob("*.pklg")):
            parsed = module.analyze(path)
            # Validate reconstructed provenance without exporting message bodies.
            raw = path.read_bytes()
            for message in parsed["messages"]:
                wire = b"".join(raw[p["offset"]:p["offset"] + p["length"]] for p in message["provenance"])
                assert len(wire) == message["total"] == int.from_bytes(wire[2:4], "big")
                assert wire[:2] == b"@@" and wire[4:6].hex() == message["id"]
                assert hashlib.sha256(wire).hexdigest() == message["sha256"]
            cases.append({"build_label": build, "build_label_source": "sysdiagnose directory, not verified OS attestation",
                          "input": file_record(path, "OTHER_BUILD_PACKETLOGGER"),
                          "records": parsed["record_count"], "warnings": parsed["warnings"],
                          "message_counts": dict(collections.Counter(m["id"] for m in parsed["messages"])),
                          "frames": parsed["frames"], "messages": parsed["messages"]})
    report = {"kind": "REPARSED_EXISTING_RAW_CAPTURES", "parser": file_record(parser, "REUSED_PARSER"),
              "direction": {"1": "phone sent ACL (PacketLogger type 2)", "2": "phone received ACL (PacketLogger type 3)"},
              "limitations": ["Existing parser reused; not an independent second parser or fresh capture.",
                              "Credit-mode assumptions and gap warnings remain; missing message is not proof of absence.",
                              "Temporal adjacency is not proof of transaction dependency or authentication success.",
                              "No current24A446, IP/AirPlay video, display or reconnect verification."], "cases": cases}
    write_generated("capture-observations.json", report)
    return report


def text_logs():
    results = []
    for path in sorted((ROOT / "sysdiagnose").glob("sysdiagnose_*/crashes_and_spins/accessoryd-packets*.log.ips")):
        events = []
        for number, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            fields = [part.strip() for part in line.split(";")]
            if len(fields) < 6:
                continue
            payload_match = re.search(r"payload\([^)]*\)=<([0-9a-fA-F ]*)>", line)
            record = {"line": number, "time": fields[0].removesuffix(" LOG"), "relative_seconds": fields[1],
                      "carrier": fields[3], "side_label": fields[4]}
            if fields[4] == "Event":
                record["event"] = fields[5]
            elif payload_match:
                wire = bytes.fromhex(payload_match.group(1))
                record["payload_bytes"] = len(wire)
                record["payload_sha256"] = hashlib.sha256(wire).hexdigest()
                for key in ("control", "seq", "ack", "session"):
                    match = re.search(r"\b" + key + r"=(0x[0-9a-fA-F]+)", line)
                    if match:
                        record[key] = match.group(1)
                if len(wire) >= 6 and wire[:2] == b"@@":
                    record["message_id"] = wire[4:6].hex()
                    record["declared_message_bytes"] = int.from_bytes(wire[2:4], "big")
                    record["complete_in_log_line"] = len(wire) == record["declared_message_bytes"]
            else:
                continue
            # Never export session UUID, certificate, nonce, credential or raw text.
            events.append(record)
        results.append({"input": file_record(path, "OTHER_BUILD_ACCESSORYD_PACKET_LOG"), "events": events})
    report = {"limits": ["Packet text log, not an independent capture of IP transport.",
                         "AirPlay carrier label establishes only the daemon's label, not displayed video.",
                         "No transaction order inferred merely from line adjacency."], "logs": results}
    write_generated("runtime-log-observations.json", report)
    return report


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()
    base = baseline()
    capture = captures()
    logs = text_logs()
    print(json.dumps({"firmware": base["firmware"], "baseline_files": len(base["files"]),
                      "captures": [{"build": c["build_label"], "messages": len(c["messages"]),
                                    "warnings": c["warnings"]} for c in capture["cases"]],
                      "text_logs": len(logs["logs"]), "output_root": str(DOC)}, ensure_ascii=False))
