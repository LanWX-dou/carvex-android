# -*- coding: utf-8 -*-
"""Build ghidra-request.json for each image from its asm index."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
for img in ("CoreUtils", "APTransport", "AirPlaySender"):
    idx = json.loads((ROOT / "source/asm" / img / "index.json").read_text(encoding="utf-8"))
    summ = json.loads((ROOT / "source/metadata" / img / "summary.json").read_text(encoding="utf-8"))
    req = {
        "source_sha256": summ["sha256"],
        "timeout_seconds": 300,
        "functions": [
            {"address": f["address"], "end": f["end"], "raw_sha256": f["raw_sha256"]}
            for f in idx["functions"]
        ],
    }
    p = ROOT / "source/metadata" / img / "ghidra-request.json"
    with p.open("w", encoding="utf-8") as handle:
        json.dump(req, handle, indent=1)
    print("wrote", p, len(req["functions"]))
