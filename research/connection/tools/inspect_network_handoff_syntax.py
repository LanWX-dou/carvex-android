"""Read-only original-byte verification for the bounded 24A446 handoff audit.

--write only creates this docset's evidence/network-handoff-syntax.json.
Byte provenance is not branch execution, CF equivalence, or real-car testing.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image

ROOT = FW / "analysis/decompiler-cache/24A446"
SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
ROWS = [
    ("NH01", "accessoryd", 0x10016d3ac, "ordered 4301 groups/scalars, getter failure exits before platform dispatch"),
    ("NH02", "accessoryd", 0x1001703cc, "5703 ordered scalar slots, arbitrary BSSID length, unknown/5/6 ignored, async dispatch"),
    ("NH03", "accessoryd", 0x100067ee4, "CString total length >=5 and final byte NUL"),
    ("NH04", "accessoryd", 0x100067e4c, "U8 total length 5"),
    ("NH05", "accessoryd", 0x100067df0, "U32 total length 8, big endian"),
    ("NH06", "accessoryd", 0x100067e74, "Bool total length 5, value 0 or 1"),
    ("NH07", "WiFiSharing", 0x2431186ac, "SSID nil/present password with security0 guard; mapping remains unresolved here"),
]


def sha(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def collect() -> dict:
    images = {"accessoryd": Image(SOURCE), "WiFiSharing": Image(FW / "extracted/24A446/binaries/WiFiSharing/WiFiSharing")}
    folders = {"accessoryd": ROOT / "accessoryd/18405d82c74429b84ed4/functions",
               "WiFiSharing": ROOT / "WiFiSharing/daf85b4040f95838b28e/functions"}
    results = []
    for key, component, address, scope in ROWS:
        raw_path = folders[component] / f"f_{address:x}.bin"
        raw = raw_path.read_bytes()
        if not raw or raw != images[component].read(address, len(raw)):
            raise ValueError(f"original byte mismatch: {key}")
        results.append({"id": key, "component": component, "address": hex(address),
                        "raw_length": len(raw), "raw_matches_source": True, "reviewed_scope": scope,
                        "files": [{"path": str(path), "sha256": sha(path)} for path in
                                  [folders[component] / f"f_{address:x}{suffix}" for suffix in (".bin", ".s", ".ghidra.c")]]})
    return {"schema_version": 1, "build": "24A446", "runtime_observed": False,
            "method": "Mach-O virtual-address byte comparison plus bounded C/ASM review; no original-function execution",
            "images": [{"component": key, "path": str(value.path), "sha256": sha(value.path)} for key, value in images.items()],
            "functions": results,
            "open": ["Wi-Fi security enum/platform credential lifecycle", "CF conversion/allocation equivalence",
                     "4301/Bonjour/invitation identity and candidate fusion", "full first-connect/reconnect platform timeline"],
            "local_design": ["normalization into grouped IapFields", "Android SSID/passphrase/port/address constraints",
                             "unchanged bounded wait before 5703-only fallback", "partial 5703 waits for usable credentials within original deadline",
                             "same local readiness predicate on reused/new Android networks"]}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    report = collect()
    if args.verify:
        if json.loads(args.verify.read_text(encoding="utf-8")) != report:
            raise ValueError("saved provenance differs from current original inputs")
        print("PASS: 2 original images, 7 function slices, saved provenance unchanged")
    elif args.write:
        target = DOC / "evidence/network-handoff-syntax.json"
        target.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
        print(str(target))
    else:
        print(json.dumps(report, indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()
