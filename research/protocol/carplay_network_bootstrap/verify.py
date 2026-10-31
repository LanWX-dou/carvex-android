#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Structural verifier for carplay_network_bootstrap (v0).

Checks:
  C1 required files exist
  C2 manifest matches disk (hashes/sizes; ignores __pycache__)
  C3 R-NB clause IDs unique and carry a valid status token
  C4 every OPEN-NB-* referenced in prose is registered in spec/04
  C5 each spec file with R-NB clauses has at least one 依据 anchor
  C6 no forbidden "interop proven" phrases
  C7 reference-impl synthetic tests pass
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
MANIFEST = ROOT / "manifest.json"

REQUIRED = [
    "README.md",
    "TASK.md",
    "STATUS.md",
    "spec/00-scope-and-terms.md",
    "spec/01-from-4301-to-credentials.md",
    "spec/02-association-and-address.md",
    "spec/03-endpoint-and-control.md",
    "spec/04-open-items.md",
    "analysis/00-evidence-index.md",
]

RULE_RE = re.compile(r"`R-NB-(\d+)\.(\d+)`（([^）]*)）")
VALID_STATUS = {
    "MUST / CONFIRMED",
    "MUST / CONFIRMED-样本",
    "MUST / INFERRED",
    "MUST / OPEN",
    "MUST / OBSERVED",
    "SHOULD / CONFIRMED",
    "SHOULD / INFERRED",
    "SHOULD / OPEN",
    "SHOULD / OBSERVED",
    "OBSERVED / CONFIRMED-样本",
    "MAY / CONFIRMED",
    "MAY / INFERRED",
    "MAY / OPEN",
    "未定义 / OPEN",
}
OPEN_RE = re.compile(r"OPEN-NB-(\d+)")
FORBIDDEN = ["已完成互通", "已验证互通", "保证互通", "互通已验收"]


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def doc_files() -> list[Path]:
    out = []
    for p in sorted(ROOT.rglob("*")):
        if not p.is_file():
            continue
        if "__pycache__" in p.parts or p.name == "manifest.json":
            continue
        out.append(p)
    return out


def write_manifest() -> None:
    files = [
        {"path": str(p.relative_to(ROOT)).replace("\\", "/"), "size": p.stat().st_size, "sha256": sha256(p)}
        for p in doc_files()
    ]
    opens = sorted({f"OPEN-NB-{m.group(1)}" for p in doc_files() if p.suffix == ".md" for m in OPEN_RE.finditer(p.read_text(encoding="utf-8"))}, key=lambda s: int(s.split("-")[-1]))
    m = {
        "docset": "carplay_network_bootstrap",
        "status": "v0-draft",
        "build": "24A446 + sysdiagnose 23G90/22H374/21G93",
        "files": files,
        "counts": {
            "files": len(files),
            "md_files": sum(1 for p in doc_files() if p.suffix == ".md"),
            "spec_docs": sum(1 for p in doc_files() if p.parent.name == "spec"),
        },
        "open_items": opens,
    }
    MANIFEST.write_text(json.dumps(m, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {MANIFEST} files={len(files)} opens={len(opens)}")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--write-manifest", action="store_true")
    args = ap.parse_args()
    if args.write_manifest:
        write_manifest()
        return 0

    fails: list[str] = []

    def fail(check: str, msg: str) -> None:
        fails.append(f"[{check}] {msg}")

    # C1
    for rel in REQUIRED:
        if not (ROOT / rel).is_file():
            fail("C1", f"missing {rel}")

    # C2
    if not MANIFEST.is_file():
        fail("C2", "manifest.json missing (run --write-manifest)")
    else:
        m = json.loads(MANIFEST.read_text(encoding="utf-8"))
        listed = {e["path"]: e for e in m.get("files", [])}
        actual = {str(p.relative_to(ROOT)).replace("\\", "/"): p for p in doc_files()}
        for rel, p in actual.items():
            if rel not in listed:
                fail("C2", f"manifest missing file {rel}")
            else:
                e = listed[rel]
                if e.get("size") != p.stat().st_size:
                    fail("C2", f"size drift {rel}")
                elif e.get("sha256") != sha256(p):
                    fail("C2", f"sha256 drift {rel}")
        for rel in listed:
            if rel not in actual:
                fail("C2", f"manifest lists missing file {rel}")

    # C3
    rules: dict[str, str] = {}
    for p in sorted((ROOT / "spec").glob("*.md")):
        text = p.read_text(encoding="utf-8")
        for m in RULE_RE.finditer(text):
            rid = f"R-NB-{m.group(1)}.{m.group(2)}"
            status = m.group(3).strip()
            if rid in rules:
                fail("C3", f"duplicate {rid} in {p.name}")
            rules[rid] = status
            if status not in VALID_STATUS:
                fail("C3", f"{rid} has unrecognized status `{status}`")
        if "R-NB-" in text and "依据" not in text:
            fail("C5", f"{p.name} has R-NB clauses but no 依据 anchor")
    if not rules:
        fail("C3", "no R-NB clauses found")

    # C4
    registered = set()
    reg_text = (ROOT / "spec/04-open-items.md").read_text(encoding="utf-8")
    for line in reg_text.splitlines():
        if line.startswith("| `OPEN-NB-"):
            registered.add(line.split("`")[1])
    used = set()
    for p in ROOT.rglob("*.md"):
        used.update(m.group(0) for m in OPEN_RE.finditer(p.read_text(encoding="utf-8")))
    for oid in sorted(used, key=lambda s: int(s.split("-")[-1])):
        if oid not in registered:
            fail("C4", f"{oid} used but not registered in spec/04")

    # C6
    for p in ROOT.rglob("*.md"):
        text = p.read_text(encoding="utf-8")
        for phrase in FORBIDDEN:
            if phrase in text:
                fail("C6", f"forbidden phrase `{phrase}` in {p.relative_to(ROOT)}")

    # C7
    test = ROOT / "reference-impl/test_bootstrap.py"
    if not test.is_file():
        fail("C7", "missing reference-impl/test_bootstrap.py")
    else:
        proc = subprocess.run(
            [sys.executable, "-B", str(test)],
            cwd=str(test.parent),
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
        if proc.returncode:
            fail("C7", ((proc.stdout or "") + (proc.stderr or ""))[-800:])

    print(f"rules={len(rules)} open_registered={len(registered)} open_used={len(used)} files={len(list(ROOT.rglob('*.md')))}")
    if fails:
        for f in fails:
            print("FAIL", f)
        print(f"failures: {len(fails)}")
        return 1
    print("OK  C1..C7 全部通过（结构/引用/合成测试，不是互通验证）")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
