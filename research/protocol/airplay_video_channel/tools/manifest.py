#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成 research/protocol/airplay_video_channel/manifest.json。

用法：
    cd research/protocol/airplay_video_channel && python3 tools/manifest.py
"""
import hashlib
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def main():
    files = []
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".git")]
        for n in sorted(names):
            p = os.path.join(base, n)
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            if rel == "manifest.json":
                continue
            files.append({"path": rel, "size": os.path.getsize(p), "sha256": sha256(p)})
    files.sort(key=lambda x: x["path"])

    cov = json.load(open(os.path.join(ROOT, "source/metadata/coverage.json"), encoding="utf-8"))
    summary = json.load(open(os.path.join(ROOT, "source/metadata/summary.json"), encoding="utf-8"))

    opens = {}
    for item in files:
        if not item["path"].endswith(".md"):
            continue
        text = open(os.path.join(ROOT, item["path"]), encoding="utf-8").read()
        for m in re.finditer(r"`(OPEN-VID-[0-9]+)`", text):
            opens.setdefault(m.group(1), item["path"])

    manifest = {
        "docset": "airplay_video_channel",
        "build": "24A446",
        "device": "iPhone18,1",
        "source": {
            "binary": "AirPlaySender",
            "path": "source/firmware/AirPlaySender",
            "size": summary["size"],
            "sha256": summary["sha256"],
            "uuid": summary["uuid"],
            "function_starts": summary["function_starts"],
            "symbols": summary["symbol_count"],
        },
        "counts": {
            "files": len(files),
            "analysis_docs": sum(1 for f in files if f["path"].startswith("analysis/")),
            "spec_docs": sum(1 for f in files if f["path"].startswith("spec/")),
            "asm_functions": sum(1 for f in files if f["path"].endswith(".s")),
            "readable_c_files": sum(1 for f in files if f["path"].endswith(".ghidra.c")),
            "open_items": len(opens),
        },
        "coverage": {i["id"]: i["status"] for i in cov["items"]},
        "coverage_summary": cov["summary"],
        "open_items": opens,
        "files": files,
    }
    with open(os.path.join(ROOT, "manifest.json"), "w", encoding="utf-8", newline="\n") as f:
        json.dump(manifest, f, ensure_ascii=False, indent=1)
    print("files:", len(files), "spec:", manifest["counts"]["spec_docs"],
          "asm:", manifest["counts"]["asm_functions"], "open:", len(opens))
    return 0


if __name__ == "__main__":
    sys.exit(main())
