"""Read-only integrity check for version/capability audit evidence.

Verifies declared path+sha256 records and bounded cache slices. This does not
validate source interpretation, missing consumer claims, or interoperability.
"""
from __future__ import annotations
import hashlib
import json
import os
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
REPORTS = ("version-header-evidence.json", "iap2-version-capability-evidence.json",
           "airplay-version-capability-evidence.json", "build-profile-audit.json")


def local_path(value):
    value = value.replace("\\", "/")
    if os.name != "nt" and re.match(r"^[A-Za-z]:/", value):
        value = "/mnt/" + value[0].lower() + value[2:]
    elif os.name == "nt" and re.match(r"^/mnt/[a-z]/", value):
        value = value[5].upper() + ":/" + value[7:]
    return Path(value)


def main():
    checked = {}
    counts = {"file_references": 0, "cache_slices": 0}

    def walk(node):
        if isinstance(node, dict):
            if isinstance(node.get("path"), str) and isinstance(node.get("sha256"), str):
                path = local_path(node["path"])
                if path not in checked:
                    with path.open("rb") as stream:
                        checked[path] = hashlib.file_digest(stream, "sha256").hexdigest()
                if checked[path] != node["sha256"]:
                    raise ValueError(f"file hash mismatch: {path}")
                counts["file_references"] += 1
            if all(key in node for key in ("cache_path", "cache_file_offset", "length", "sha256")):
                path = local_path(node["cache_path"])
                assert 0 < node["length"] < 1024 * 1024
                assert node["cache_file_offset"] >= 0
                with path.open("rb") as stream:
                    stream.seek(node["cache_file_offset"])
                    raw = stream.read(node["length"])
                if len(raw) != node["length"] or hashlib.sha256(raw).hexdigest() != node["sha256"]:
                    raise ValueError(f"cache slice mismatch: {path}: {node['cache_file_offset']}")
                if "hex" in node and raw.hex() != node["hex"]:
                    raise ValueError(f"cache hex mismatch: {path}: {node['cache_file_offset']}")
                counts["cache_slices"] += 1
            for value in node.values():
                walk(value)
        elif isinstance(node, list):
            for value in node:
                walk(value)

    for name in REPORTS:
        walk(json.loads((ROOT / "evidence" / name).read_text(encoding="utf-8")))
        print(f"OK {name}: declared file identities/cache slices")
    print(f"OK reports={len(REPORTS)} unique_files={len(checked)} counts={counts}")
    print("LIMIT: recorded identities/slices only; not semantic, runtime, APK or real-headunit validation")


if __name__ == "__main__":
    main()
