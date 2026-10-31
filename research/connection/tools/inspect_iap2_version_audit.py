"""Read-only evidence collector for chapter14. Prints JSON; never writes inputs.

Run with python -B. No firmware execution, JVM/Gradle build, device or network use.
Byte identity does not certify all decompiler semantics or runtime behavior.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
APP = Path("D:/carvex-research/android")
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
CACHE = FW / "analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions"
JAVA = APP / "protocol-carplay/src/main/java/io/github/iamr0s/carvex"
ROWS = [
    ("IV01", 0x100103230, "SYN version and three-byte session descriptor parsing"),
    ("IV02", 0x100035154, "Local link version only lowered; copied peer session table"),
    ("IV03", 0x10003009c, "Commit negotiated working block before connected callback"),
    ("IV04", 0x10011d4b8, "Control version fetched from session info byte2"),
    ("IV05", 0x1000ed1ac, "Version-dependent authentication inheritance and AA00 serial request"),
    ("IV06", 0x1000d4c94, "CMD version1 rejection; 0x54/0x55 dispatch to FSM9/10"),
    ("IV07", 0x10011d8dc, "Auth/ID completion and conditional time-sync start"),
    ("IV08", 0x10013aed0, "Identification callback success added to required-success set"),
    ("IV09", 0x10013bc5c, "Missing required success creates rejection/error"),
    ("IV10", 0x10013b920, "Required transport component checks"),
    ("IV11", 0x100050dcc, "Identification acceptance requires successful validation and callback"),
    ("IV12", 0x10006a3e4, "Identification registration table reader"),
]

def sha(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()

def main():
    img = Image(SOURCE)
    functions = []
    for key, address, scope in ROWS:
        raw_path = CACHE / f"f_{address:x}.bin"
        raw = raw_path.read_bytes()
        assert raw and img.read(address, len(raw)) == raw, key
        segment = next((a, o, n) for a, b, o, n in img.segments if a <= address and address + len(raw) <= b)
        functions.append({"id": key, "address": hex(address), "component": "accessoryd",
            "raw_length": len(raw), "raw_sha256": hashlib.sha256(raw).hexdigest(),
            "source_file_offset": segment[1] + address - segment[0], "raw_matches_source": True,
            "reviewed_scope": scope, "symbols": img.symbols.get(address, []),
            "files": [{"path": str(p), "sha256": sha(p)} for suffix in (".bin", ".s", ".ghidra.c")
                      if (p := CACHE / f"f_{address:x}{suffix}").exists()]})
    # Re-read only the required records used by this audit; their locations were
    # recovered in chapter12, not inferred from the Android implementation.
    reg_addresses = list(range(0x10021a810, 0x10021a900, 24)) + [0x10021f1a8, 0x10021f1c0]
    required_records = []
    for address in reg_addresses:
        raw = img.read(address, 24)
        ident = struct.unpack_from("<I", raw)[0]
        assert raw[16] == 1, hex(address)
        required_records.append({"address": hex(address), "id": ident, "required": raw[16],
            "raw_hex": raw.hex(), "sha256": hashlib.sha256(raw).hexdigest()})
    app_paths = ["carplay/core/IapLink.kt", "carplay/core/IapStartupPolicy.kt", "carplay/Bootstrap.kt",
        "carplay/core/IapAuthentication.kt", "carplay/core/RuntimeIap.kt", "carplay/AirSession.kt",
        "sessioncore/PeerNegotiationController.kt", "sessioncore/IapIdentifyInfo.kt", "carplay/core/DeviceAuthPolicy.kt",
        "carplay/core/IapPeerProfile.kt", "carplay/core/IapMessageRouter.kt"]
    result = {"schema_version": 1, "review_date": "2026-10-29", "status": "BOUNDED_STATIC_AUDIT",
        "source": {"component": "accessoryd", "path": str(SOURCE), "sha256": sha(SOURCE)},
        "functions": functions, "required_registration_records": required_records,
        "android_sources": [{"path": str(JAVA / rel), "sha256": sha(JAVA / rel)} for rel in app_paths],
        "tools": [{"path": str(p), "sha256": sha(p)} for p in (Path(__file__), FW / "tools/ipsw-research/firmware_image.py")],
        "runtime_observed": False, "firmware_executed": False, "app_tests_executed": False,
        "claims": [
            {"id": "IAV-01", "priority": "P1", "status": "CONFIRMED_STATIC", "claim": "Android echoes control version >2 and commits link before Bootstrap rejects unsupported control versions."},
            {"id": "IAV-02", "priority": "P1", "status": "CONFIRMED_STATIC", "claim": "Android identification acceptance omits required IDs8/9 and validates presence rather than successful parsing for12/13; transport components are not checked on this acceptance path."},
            {"id": "IAV-03", "priority": "P2", "status": "CONFIRMED_STATIC_BRANCH", "claim": "Second SYNACK path parses a new proposal but commits first proposal's versions/session, using only second MTU and sequence."},
            {"id": "IAV-04", "priority": "P2", "status": "PARTIAL_CANDIDATE", "claim": "Link v2/v3 CMD54/55 is queued but Bootstrap discards null-fields command and AirSession runtime callback handles only NowPlaying; actual peer dependence/extension prerequisites remain unproven."}],
        "limits": ["No audio causality established.", "No exact iPhone local version/profile producer closure; do not force all links to1.",
            "Reproduction vectors in chapter14 are proposed static paths, not executed tests.", "No bypass of authentication or untrusted inheritance is recommended.",
            "Source snapshots may differ from an installed APK; device build provenance not checked."]}
    print(json.dumps(result, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
