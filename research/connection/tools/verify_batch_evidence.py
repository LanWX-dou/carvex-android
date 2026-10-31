"""Read-only source identity and function-slice audit for chapters 12/22/24/31.

Checks the reports' named Mach-O images and each function's exact source slice.
Does NOT validate C/ASM interpretation, dyld fixup claims, field semantics,
local-model results, runtime behavior, or real-headunit acceptance.
"""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import re
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / "firmware/tools/ipsw-research"))
from firmware_image import Image


def local_path(value: str) -> Path:
    value = value.replace("\\", "/")
    if os.name != "nt" and re.match(r"^[A-Za-z]:/", value):
        value = "/mnt/" + value[0].lower() + value[2:]
    return Path(value)


def sha(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def main() -> None:
    reports = (
        "identification-contract-evidence.json",
        "control-wire-evidence.json",
        "disconnect-evidence.json",
        "video-codec-evidence.json",
    )
    images: dict[Path, Image] = {}
    checked = 0
    for name in reports:
        report = json.loads((ROOT / "evidence" / name).read_text(encoding="utf-8"))
        sources = report.get("images") or [report["source"]]
        named = {}
        for source in sources:
            path = local_path(source["path"])
            if sha(path) != source["sha256"]:
                raise ValueError(f"image hash mismatch: {name}: {path}")
            if path not in images:
                images[path] = Image(path)
            named[source.get("component", source.get("name"))] = images[path]
        count = 0
        for function in report["functions"]:
            address = int(function["address"], 16)
            length = function.get("raw_length", function.get("length"))
            expected = function.get("raw_sha256", function.get("sha256"))
            path = function.get("raw_path")
            if path is None:
                candidates = [f["path"] for f in function["files"] if f["path"].endswith(".bin")]
                if len(candidates) != 1:
                    raise ValueError(f"raw path ambiguity: {name}: {address:#x}")
                path = candidates[0]
            raw = local_path(path).read_bytes()
            component = function.get("component", function.get("image"))
            if component is None and len(named) == 1:
                component = next(iter(named))
            if len(raw) != length or hashlib.sha256(raw).hexdigest() != expected:
                raise ValueError(f"raw hash/length mismatch: {name}: {address:#x}")
            if named[component].read(address, length) != raw:
                raise ValueError(f"Mach-O bytes mismatch: {name}: {address:#x}")
            count += 1
        checked += count
        print(f"OK {name}: source_function_records={count}")
    print(f"OK reports={len(reports)} function_records={checked} unique_images={len(images)}")
    print("LIMIT: identity and function slices only; not semantic, cache-pointer, runtime or vehicle validation")


if __name__ == "__main__":
    main()
