#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Build manifest.json for research/protocol/airplay_control_plane (three-image docset).

Differs from firmware/tools/gen-manifest.py (single-binary, phase-3 layout):
here the source is three dylibs, so images[] replaces source{}.
"""
import hashlib
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP = {"manifest.json"}
IMAGES = ["AirPlaySender", "APTransport", "CoreUtils"]


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for c in iter(lambda: f.read(1 << 20), b""):
            h.update(c)
    return h.hexdigest()


def main():
    files = []
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".git")]
        for n in sorted(names):
            p = os.path.join(base, n)
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            if rel in SKIP:
                continue
            files.append({"path": rel, "size": os.path.getsize(p), "sha256": sha256(p)})
    files.sort(key=lambda x: x["path"])

    images = []
    total_starts = 0
    for name in IMAGES:
        s = json.load(open(os.path.join(ROOT, "source/metadata", name, "summary.json"), encoding="utf-8"))
        images.append({
            "name": name,
            "path": "source/firmware/" + name,
            "size": s["size"],
            "sha256": s["sha256"],
            "uuid": s.get("uuid", ""),
            "function_starts": s["function_starts"],
            "symbols": s.get("symbol_count", 0),
        })
        total_starts += s["function_starts"]

    exported = 0
    for name in IMAGES:
        idx = json.load(open(os.path.join(ROOT, "source/asm", name, "index.json"), encoding="utf-8"))
        exported += idx["count"]

    audit_exported = 0
    for name in IMAGES:
        index_path = os.path.join(ROOT, "source/asm-audit", name, "index.json")
        if os.path.exists(index_path):
            with open(index_path, encoding="utf-8") as f:
                audit_exported += json.load(f)["count"]

    open_items = {}
    for item in files:
        if not item["path"].endswith(".md"):
            continue
        text = open(os.path.join(ROOT, item["path"]), encoding="utf-8").read()
        for m in re.finditer(r"`(OPEN-AP-[0-9]+)`", text):
            open_items.setdefault(m.group(1), item["path"])

    cov = json.load(open(os.path.join(ROOT, "coverage.json"), encoding="utf-8"))
    manifest = {
        "docset": "airplay_control_plane",
        "build": "24A446",
        "device": "iPhone18,1",
        "iteration": cov.get("iteration", 1),
        "images": images,
        "counts": {
            "files": len(files),
            "analysis_docs": sum(1 for f in files if f["path"].startswith("analysis/") and f["path"].endswith(".md")),
            "spec_docs": sum(1 for f in files if f["path"].startswith("spec/") and f["path"].endswith(".md")),
            "asm_files": sum(1 for f in files if f["path"].startswith("source/asm/") and f["path"].endswith(".s")),
            "readable_c_files": sum(1 for f in files if f["path"].endswith(".ghidra.c")),
            "exported_functions": exported,
            "audit_asm_files": sum(1 for f in files if f["path"].startswith("source/asm-audit/") and f["path"].endswith(".s")),
            "audit_exported_functions": audit_exported,
            "function_starts_total": total_starts,
            "sampling": round(exported / total_starts, 5) if total_starts else 0,
        },
        "coverage": cov["items"],
        "coverage_summary": {k: sum(1 for i in cov["items"] if i["status"] == k)
                             for k in ("CONFIRMED", "PARTIAL", "OPEN")},
        "open_items": open_items,
        "open_item_count": len(open_items),
        "files": files,
    }
    path = os.path.join(ROOT, "manifest.json")
    json.dump(manifest, open(path, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
    print("wrote", path, "files=", len(files), "open_items=", len(open_items))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
