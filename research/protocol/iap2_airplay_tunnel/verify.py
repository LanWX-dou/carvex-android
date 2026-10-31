#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""research/protocol/iap2_airplay_tunnel 的自动校验。

    cd research/protocol/iap2_airplay_tunnel && python3 verify.py

十个检查项（C1–C10）对应 TASK.md §7。任何一项失败 → 退出码 1。
"""
from __future__ import annotations

import hashlib
import json
import pathlib
import re
import sys

sys.dont_write_bytecode = True

ROOT = pathlib.Path(__file__).resolve().parent
SOURCE = ROOT / "source"
METADATA = SOURCE / "metadata"
ASM = SOURCE / "asm" / "accessoryd"
READABLE = ROOT / "readable" / "ghidra" / "accessoryd"
ANALYSIS = ROOT / "analysis"
SPEC = ROOT / "spec"
IMPL = ROOT / "reference-impl"

EXPECTED_SHA = "2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe"
SPEC_ID = re.compile(r"\bA\d{2}\.\d{1,2}\b")
RULE_ID = re.compile(r"^\*\*(R-\d+\.\d+)\*\*", re.M)
OPEN_ID = re.compile(r"OPEN-TUN-\d+")
XREF = re.compile(r"(link|control)/([RA]-\d+\.(?:\d+|x))")

results = []


def check(name: str, ok: bool, detail: str = "") -> bool:
    results.append((name, ok, detail))
    print("%s %-58s %s" % ("PASS" if ok else "FAIL", name, detail))
    return ok


def sha256(path: pathlib.Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def read(path: pathlib.Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


# --------------------------------------------------------------------------
def c1_source_identity() -> bool:
    summary = json.loads(read(METADATA / "summary.json"))
    binary = SOURCE / "firmware" / "accessoryd"
    if not binary.exists():
        return check("C1 源二进制", False, "缺 source/firmware/accessoryd")
    got = sha256(binary)
    ok = got == EXPECTED_SHA == summary["sha256"]
    return check("C1 源二进制哈希", ok, got[:16])


def c2_slices() -> bool:
    index = json.loads(read(ASM / "index.json"))
    binary = (SOURCE / "firmware" / "accessoryd").read_bytes()
    text = json.loads(read(METADATA / "summary.json"))["text_section"]
    bad = []
    for fn in index["functions"]:
        blob = ASM / fn["bin"]
        if not blob.exists():
            bad.append(fn["bin"] + ":missing")
            continue
        data = blob.read_bytes()
        if sha256(blob) != fn["raw_sha256"]:
            bad.append(fn["bin"] + ":sha")
            continue
        if len(data) != fn["size"]:
            bad.append(fn["bin"] + ":size")
            continue
        off = text["fileoff"] + (int(fn["address"], 16) - text["addr"])
        if binary[off:off + len(data)] != data:
            bad.append(fn["bin"] + ":slice")
    n = len(index["functions"])
    return check("C2 函数切片与固件一致", not bad and n == index["count"],
                 "%d 个函数%s" % (n, "" if not bad else "，坏项 " + ",".join(bad[:4])))


def c3_headers() -> bool:
    bad = []
    for asm in ASM.glob("*.s"):
        head = read(asm)[:400]
        if EXPECTED_SHA not in head or "unreviewed" not in head:
            bad.append(asm.name)
    c_files = list(READABLE.glob("*.ghidra.c"))
    for c in c_files:
        if "RAW GHIDRA DECOMPILATION" not in read(c)[:400]:
            bad.append(c.name)
    ok = not bad and len(c_files) == len(list(ASM.glob("*.s")))
    return check("C3 反汇编/反编译横幅", ok,
                 "%d .s, %d .c%s" % (len(list(ASM.glob("*.s"))), len(c_files),
                                     "" if not bad else "，坏项 " + ",".join(bad[:3])))


def parse_rules():
    rules = []
    for path in sorted(SPEC.glob("*.md")):
        text = read(path)
        matches = list(RULE_ID.finditer(text))
        for i, m in enumerate(matches):
            end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
            rules.append({"id": m.group(1), "file": path.name,
                          "block": text[m.start():end]})
    return rules


def c4_rules(rules) -> bool:
    ids = [r["id"] for r in rules]
    dups = {i for i in ids if ids.count(i) > 1}
    missing = [r["id"] for r in rules if "依据：" not in r["block"]]
    ok = bool(rules) and not dups and not missing
    return check("C4 条款编号唯一且带依据", ok,
                 "%d 条%s%s" % (len(rules),
                                "" if not dups else "，重复 " + ",".join(sorted(dups)),
                                "" if not missing else "，缺依据 " + ",".join(missing[:4])))


def c5_basis(rules) -> bool:
    a_table = set()
    for line in read(ANALYSIS / "A-conclusions.md").splitlines():
        m = re.match(r"\|\s*(A\d{2}\.\d{1,2})\s*\|", line)
        if m:
            a_table.add(m.group(1))
    missing = []
    for r in rules:
        cited = set(SPEC_ID.findall(r["block"]))
        if not cited:
            missing.append(r["id"] + ":no-A")
        for a in cited:
            if a not in a_table:
                missing.append("%s->%s" % (r["id"], a))
    return check("C5 依据指向已登记的 A", not missing and bool(a_table),
                 "%d 个 A%s" % (len(a_table), "" if not missing else "，坏项 " + ",".join(missing[:4])))


def c6_open_items() -> bool:
    cov = json.loads(read(METADATA / "coverage.json"))
    registered = set(cov["open_items"])
    used = set()
    for path in list(ANALYSIS.glob("*.md")) + list(SPEC.glob("*.md")):
        used |= set(OPEN_ID.findall(read(path)))
    missing_reg = used - registered
    referenced = set()
    for req in cov["requirements"]:
        referenced |= set(req.get("open", []))
    unreferenced = registered - referenced
    ok = not missing_reg and not unreferenced
    return check("C6 OPEN 登记完整且被引用", ok,
                 "%d 登记 / %d 引用%s%s" % (len(registered), len(used),
                                            "" if not missing_reg else "，未登记 " + ",".join(sorted(missing_reg)),
                                            "" if not unreferenced else "，无覆盖引用 " + ",".join(sorted(unreferenced))))


def c7_xrefs() -> bool:
    targets = {
        "link": ROOT.parent / "bluetooth_rfcomm" / "spec",
        "control": ROOT.parent / "iap2_control_session",
    }
    bad = []
    seen = set()
    for path in list(SPEC.glob("*.md")) + list(ANALYSIS.glob("*.md")):
        for prefix, ref in XREF.findall(read(path)):
            base = targets[prefix]
            if not base.exists():
                bad.append("%s/%s:docset-missing" % (prefix, ref))
                continue
            if ref.endswith(".x"):
                chapter = ref.split(".")[0]
                hit = any(re.search(r"\b%s\.\d" % re.escape(chapter), read(p))
                          for p in base.rglob("*.md"))
            else:
                hit = any(ref in read(p) for p in base.rglob("*.md"))
            if not hit and (prefix, ref) not in seen:
                seen.add((prefix, ref))
                bad.append("%s/%s" % (prefix, ref))
    return check("C7 跨 docset 引用可解析", not bad,
                 "" if not bad else "，缺失 " + ",".join(sorted(bad)[:6]))


def c8_coverage() -> bool:
    cov = json.loads(read(METADATA / "coverage.json"))
    reqs = cov["requirements"]
    counts = {}
    for r in reqs:
        counts[r["status"]] = counts.get(r["status"], 0) + 1
    ok = len(reqs) == 12 and counts == cov["counts"]
    # 禁止无条件"全部确认"
    bad_claim = []
    for path in list(SPEC.glob("*.md")) + [ROOT / "STATUS.md"]:
        if not path.exists():
            continue
        for line in read(path).splitlines():
            if "全部确认" in line and not any(w in line for w in ("不", "未", "非", "禁止", "无法", "没有")):
                bad_claim.append(path.name)
    return check("C8 12 项覆盖与 summary 一致", ok and not bad_claim,
                 "%s%s" % (counts, "" if not bad_claim else "，违规断言 " + ",".join(bad_claim)))


def c9_vectors() -> bool:
    sys.path.insert(0, str(IMPL))
    try:
        import tunnel_codec  # noqa: F401
    except Exception as exc:  # pragma: no cover
        return check("C9 测试向量复算", False, "import 失败: %s" % exc)
    doc = json.loads(read(IMPL / "test_vectors.json"))
    bad = []
    for vec in doc["vectors"]:
        got = tunnel_codec.run_vector(vec)
        if got != vec["expect"]:
            bad.append(vec["id"])
    # 状态机自检（R-5.14）：停等、0x5266→0x5163、0x5265 终止、能力协商
    try:
        import relay_session
        relay_ok = relay_session.self_test() is True
    except Exception as exc:  # pragma: no cover
        relay_ok = False
        bad.append("relay_session:%s" % exc)
    ok = not bad and len(doc["vectors"]) >= 18 and relay_ok
    return check("C9 测试向量与状态机自检", ok,
                 "%d 条向量%s%s" % (len(doc["vectors"]),
                                    "，状态机 OK" if relay_ok else "，状态机失败",
                                    "" if not bad else "，失败 " + ",".join(bad[:5])))


def c10_manifest() -> bool:
    path = ROOT / "manifest.json"
    if not path.exists():
        return check("C10 清单一致", False, "缺 manifest.json")
    man = json.loads(read(path))
    files = man["files"]
    bad = []
    for entry in files:
        p = ROOT / entry["path"]
        if entry["path"] == "manifest.json":
            continue
        if not p.exists():
            bad.append(entry["path"] + ":missing")
        elif sha256(p) != entry["sha256"] or p.stat().st_size != entry["size"]:
            bad.append(entry["path"] + ":diff")
    on_disk = {str(p.relative_to(ROOT)).replace("\\", "/")
               for p in ROOT.rglob("*")
               if p.is_file() and "__pycache__" not in p.parts}
    listed = {e["path"] for e in files}
    extra = on_disk - listed - {"manifest.json"}
    ok = not bad and not extra and man["file_count"] == len(files)
    return check("C10 清单与磁盘一致", ok,
                 "%d 文件%s%s" % (len(files),
                                  "" if not bad else "，变更 " + ",".join(sorted(bad)[:3]),
                                  "" if not extra else "，未登记 " + ",".join(sorted(extra)[:3])))


def main() -> int:
    print("== research/protocol/iap2_airplay_tunnel verify ==")
    rules = parse_rules()
    c1_source_identity()
    c2_slices()
    c3_headers()
    c4_rules(rules)
    c5_basis(rules)
    c6_open_items()
    c7_xrefs()
    c8_coverage()
    c9_vectors()
    c10_manifest()
    failed = [n for n, ok, _ in results if not ok]
    print("\n%d/%d 通过" % (len(results) - len(failed), len(results)))
    if failed:
        print("失败：" + "、".join(failed))
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
