#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""airplay_audio_mic_channel 文档集自检。

用法： cd research/protocol/airplay_audio_mic_channel && python3 verify.py

检查项：
  C1  必需文件与目录齐全
  C2  条款编号唯一、格式合法，每条都有「级别 / 证据 / 依据」行
  C3  条款引用的 A-* 结论存在，引用的 OPEN-* 已在 spec/10-open-items.md 登记
  C4  登记的 OPEN-* 至少被一处正文引用（无孤儿）
  C5  覆盖要求表恰好 12 行，状态合法，OPEN 行必须有 OPEN-* 编号
  C6  禁止表述（"全部确认"、"已抓包"）必须带否定词
  C7  参考实现回放 reference-impl/test_vectors.json 全部通过
  C8  manifest.json 与目录树一致（文件集合、大小、sha256、计数）
  C9  无 TODO/TBD/XXX 占位符
  C10 消息原切片回归
  C11 配置字段原证据
  C12 整数格式映射与转换原指令仿真
  C13 能力匹配证据、掩码原指令仿真与顺序模型
"""

from __future__ import annotations

import hashlib
import json
import re
import subprocess
import sys
import traceback
from pathlib import Path

sys.dont_write_bytecode = True

ROOT = Path(__file__).resolve().parent

REQUIRED = [
    "TASK.md", "STATUS.md", "manifest.json", "verify.py",
    "analysis/00-method-and-environment.md",
    "analysis/01-audio-streams.md",
    "analysis/02-codecs-and-rtp.md",
    "analysis/03-red.md",
    "analysis/04-decryption.md",
    "analysis/05-playback-and-mixing.md",
    "analysis/06-microphone-uplink.md",
    "analysis/07-teardown.md",
    "analysis/08-runtime-captures.md",
    "analysis/09-message-coordinate-audit.md",
    "analysis/10-config-field-audit.md",
    "analysis/11-format-id-map-audit.md",
    "analysis/12-capability-policy-audit.md",
    "analysis/A-conclusions.md",
    "spec/00-scope-and-terms.md",
    "spec/01-audio-streams.md",
    "spec/02-codecs.md",
    "spec/03-red.md",
    "spec/04-decryption.md",
    "spec/05-playback-mixing.md",
    "spec/06-microphone.md",
    "spec/07-teardown.md",
    "spec/08-client-guide.md",
    "spec/09-conformance-checklist.md",
    "spec/10-open-items.md",
    "spec/11-format-id-map.md",
    "tools/verify-format-map.py",
    "spec/12-capability-selection.md",
    "tools/verify-capability-policy.py",
    "reference-impl/audio_depacketizer.py",
    "reference-impl/red_decoder.py",
    "reference-impl/gen_test_vectors.py",
    "reference-impl/test_vectors.json",
    "runtime/README.md",
]

RULE_RE = re.compile(r"^#### (R-[0-9]+\.[0-9]+) (\S.*)$")
META_RE = re.compile(
    r"^级别：(MUST NOT|MUST|SHOULD NOT|SHOULD|MAY|未定义) ｜ 证据：(CONFIRMED|INFERRED|OPEN) ｜ 依据：(?:.+)"
)
A_ID_RE = re.compile(r"\bA[0-9]{2}\.[0-9]+\b")
OPEN_RE = re.compile(r"`(OPEN-[A-Z]+-[0-9]+)`")
# 其它文档集登记的编号：允许交叉引用，但不在本集登记表里查
FOREIGN_PREFIXES = ("OPEN-SES-", "OPEN-SYN-", "OPEN-MSG-", "OPEN-RF-")
COVER_ROW = re.compile(r"^\| *([0-9]{1,2}) *\|(.+)$")

failures: list[str] = []
warnings: list[str] = []


def fail(message: str) -> None:
    failures.append(message)


def read(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8")


def check_files() -> None:
    for rel in REQUIRED:
        if not (ROOT / rel).exists():
            fail(f"C1 missing {rel}")
    for rel in ("runtime/captures", "runtime/replay", "reference-impl"):
        if not (ROOT / rel).is_dir():
            fail(f"C1 missing dir {rel}")


def spec_files() -> list[Path]:
    return sorted((ROOT / "spec").glob("*.md"))


def collect_rules() -> dict[str, tuple[str, str]]:
    """返回 {rule_id: (file, meta_line)}，同时校验格式与重复。"""
    rules: dict[str, tuple[str, str]] = {}
    for path in spec_files():
        text = read(str(path.relative_to(ROOT)))
        lines = text.splitlines()
        for index, line in enumerate(lines):
            match = RULE_RE.match(line)
            if not match:
                continue
            rule_id = match.group(1)
            if rule_id in rules:
                fail(f"C2 duplicate rule {rule_id} in {path.name} (first in {rules[rule_id][0]})")
                continue
            meta = ""
            for follow in lines[index + 1: index + 6]:
                if follow.startswith("级别："):
                    meta = follow
                    break
                if follow.startswith("#"):
                    break
            if not meta:
                fail(f"C2 {rule_id} ({path.name}) has no 级别/证据/依据 line within 5 lines")
                rules[rule_id] = (path.name, "")
                continue
            if not META_RE.match(meta):
                fail(f"C2 {rule_id} ({path.name}) malformed meta: {meta[:60]}")
            if meta.startswith("级别：未定义") and "证据：OPEN" not in meta:
                fail(f"C2 {rule_id}: undefined rules must remain OPEN")
            rules[rule_id] = (path.name, meta)
    if len(rules) < 40:
        fail(f"C2 only {len(rules)} rules found (<40)")
    return rules


def collect_conclusions() -> set[str]:
    text = read("analysis/A-conclusions.md")
    return set(re.findall(r"^\| *(A[0-9]{2}\.[0-9]+) *\|", text, re.M))


def collect_registered_open() -> dict[str, str]:
    """spec/10 的登记表：| OPEN-... | 含义 | 阻塞点 |"""
    text = read("spec/10-open-items.md")
    rows = {}
    for line in text.splitlines():
        match = re.match(r"^\| *`?(OPEN-[A-Z]+-[0-9]+)`? *\|", line)
        if match:
            rows[match.group(1)] = line
    return rows


def check_references(rules: dict[str, tuple[str, str]]) -> None:
    conclusions = collect_conclusions()
    registered = collect_registered_open()
    if not conclusions:
        fail("C3 A-conclusions.md has no A-xx.y table rows")
    if not registered:
        fail("C3 spec/10-open-items.md has no OPEN registry rows")

    cited_open: dict[str, set[str]] = {}
    all_files = sorted((ROOT / "analysis").glob("*.md")) + spec_files() + [ROOT / "STATUS.md"]
    for path in all_files:
        rel = path.relative_to(ROOT).as_posix()
        text = path.read_text(encoding="utf-8")
        for a_id in set(A_ID_RE.findall(text)):
            if a_id not in conclusions:
                fail(f"C3 {rel} cites unknown conclusion {a_id}")
        for open_id in set(OPEN_RE.findall(text)):
            if open_id.startswith(FOREIGN_PREFIXES):
                continue
            cited_open.setdefault(open_id, set()).add(rel)
            if open_id not in registered and rel != "spec/10-open-items.md":
                fail(f"C3 {rel} cites unregistered {open_id}")

    for open_id in registered:
        users = {f for f in cited_open.get(open_id, set()) if f != "spec/10-open-items.md"}
        if not users:
            fail(f"C4 orphan OPEN item {open_id}: registered but never cited elsewhere")

    for open_id, users in cited_open.items():
        if open_id in registered and "spec/10-open-items.md" in users:
            continue
    for rule_id, (name, meta) in rules.items():
        if "OPEN" not in meta and not meta:
            continue


def check_coverage() -> None:
    text = read("analysis/A-conclusions.md")
    rows = []
    in_section = False
    for line in text.splitlines():
        if line.startswith("## "):
            in_section = "覆盖" in line
            continue
        if not in_section:
            continue
        match = COVER_ROW.match(line)
        if not match:
            continue
        number = int(match.group(1))
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 5:
            fail(f"C5 coverage row {number} has {len(cells)} cells")
            continue
        rows.append((number, cells))
    if len(rows) != 12:
        fail(f"C5 coverage table has {len(rows)} rows, expected 12")
        return
    numbers = [r[0] for r in rows]
    if numbers != list(range(1, 13)):
        fail(f"C5 coverage numbering {numbers}")
    statuses = {}
    for number, cells in rows:
        status = cells[2]
        if status not in ("已确认", "部分确认", "OPEN"):
            fail(f"C5 coverage row {number} bad status {status!r}")
            continue
        statuses[status] = statuses.get(status, 0) + 1
        if status == "OPEN" and not OPEN_RE.search(cells[3] + cells[4]):
            fail(f"C5 coverage row {number} is OPEN but cites no OPEN-* id")
    for status in ("已确认", "部分确认", "OPEN"):
        statuses.setdefault(status, 0)
    text_status = read("STATUS.md")
    expect = f"{statuses['已确认']} 已确认 / {statuses['部分确认']} 部分确认 / {statuses['OPEN']} OPEN"
    if expect not in text_status:
        fail(f"C5 STATUS.md must contain {expect!r}")
    registered = collect_registered_open()
    for number, cells in rows:
        for open_id in OPEN_RE.findall(" ".join(cells)):
            if open_id not in registered:
                fail(f"C5 coverage row {number} cites unregistered {open_id}")


def check_banned() -> None:
    negations = ("不", "未", "非", "禁止", "无法", "没有", "无")
    for path in sorted(ROOT.rglob("*.md")):
        rel = path.relative_to(ROOT).as_posix()
        for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
            for phrase in ("全部确认", "已抓包"):
                if phrase not in line:
                    continue
                if any(neg in line for neg in negations):
                    continue
                fail(f"C6 {rel}:{number} uses {phrase!r} without negation")


def check_vectors() -> None:
    sys.path.insert(0, str(ROOT / "reference-impl"))
    try:
        import audio_depacketizer as rtp
        import red_decoder as red
    except Exception:
        fail("C7 cannot import reference-impl modules:\n" + traceback.format_exc())
        return

    data = json.loads(read("reference-impl/test_vectors.json"))
    cases = data.get("cases") or []
    if len(cases) < 12:
        fail(f"C7 only {len(cases)} vectors")
    for case in cases:
        name = case["name"]
        kind = case["kind"]
        try:
            if kind in ("rtp", "rtp_reject", "record", "record_reject", "message"):
                packet = bytes.fromhex(case["hex"])
                if kind == "rtp":
                    got = rtp.parse_header(packet)
                elif kind == "message":
                    got = {**rtp.parse_message_header(packet), "aad": rtp.aad_for_message(packet)}
                    info = rtp.parse_message_header(packet)
                    rebuilt = rtp.build_message(info["seq"], info["timestamp"], info["second_word"], packet[10:])
                    if rebuilt != packet:
                        fail(f"C7 {name}: message encode differs from literal vector")
                elif kind == "record":
                    got = rtp.split_message_record(packet, case.get("span", 0), trailer_layout=case["trailer_layout"])
                else:
                    try:
                        if kind == "rtp_reject":
                            rtp.parse_header(packet)
                        else:
                            rtp.split_message_record(packet, case.get("span", 0), trailer_layout=case["trailer_layout"])
                    except rtp.PacketError as exc:
                        if exc.code != case["expect_error"]:
                            fail(f"C7 {name}: error {exc.code} != {case['expect_error']}")
                        continue
                    fail(f"C7 {name}: expected {case['expect_error']}, got success")
                    continue
            elif kind in ("red", "red_reject", "full"):
                payload = bytes.fromhex(case.get("payload") or case["hex"])
                if kind == "full":
                    # Prefix syntax only: never split ciphertext into audio frames.
                    packet = bytes.fromhex(case["hex"])
                    got = red.parse_descriptors(packet[rtp.AUDIO_MESSAGE_HEADER_LEN:])
                    record = rtp.split_message_record(packet, got["span"], trailer_layout=case["trailer_layout"])
                    got = {**got, "ciphertext": record["ciphertext"].hex(),
                           "aad": record["aad"].hex(), "authenticated": record["authenticated"]}
                try:
                    if kind != "full":
                        got = red.parse_red(payload, case["outer_seq"], case["outer_ts"])
                except red.RedError as exc:
                    if kind == "full":
                        fail(f"C7 {name}: unexpected RED error {exc.code}")
                    elif exc.code != case["expect_error"]:
                        fail(f"C7 {name}: error {exc.code} != {case['expect_error']}")
                    continue
                if kind == "red_reject":
                    fail(f"C7 {name}: expected {case['expect_error']}, got success")
                    continue
                if kind != "full":
                    got["seqs"] = [entry["seq"] for entry in got["entries"]]
                    got["timestamps"] = [entry["timestamp"] for entry in got["entries"]]
                    got["lengths"] = [entry["length"] for entry in got["entries"]]
                    got["deltas"] = [entry["delta"] for entry in got["entries"]]
                    got["primary_index"] = next(e["index"] for e in got["entries"] if e["primary"])
            else:
                fail(f"C7 {name}: unknown kind {kind}")
                continue
            for key, want in (case.get("expect") or {}).items():
                have = got.get(key)
                if isinstance(have, (bytes, bytearray)):
                    have = have.hex()
                if have != want:
                    fail(f"C7 {name}: {key}={have!r} expected {want!r}")
        except Exception:
            fail(f"C7 {name} raised:\n{traceback.format_exc()}")


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def check_manifest() -> None:
    manifest = json.loads(read("manifest.json"))
    listed = {item["path"]: item for item in manifest.get("files", [])}
    actual: dict[str, dict] = {}
    for path in ROOT.rglob("*"):
        if not path.is_file():
            continue
        rel = path.relative_to(ROOT).as_posix()
        if rel == "manifest.json" or "__pycache__" in rel or rel.endswith(".pyc"):
            continue
        actual[rel] = {"size": path.stat().st_size, "sha256": sha256(path)}
    missing = sorted(set(actual) - set(listed))
    extra = sorted(set(listed) - set(actual))
    if missing:
        fail(f"C8 manifest missing {missing[:5]} (+{max(0, len(missing) - 5)})")
    if extra:
        fail(f"C8 manifest lists {extra[:5]} not on disk")
    for rel in sorted(set(actual) & set(listed)):
        if listed[rel]["sha256"] != actual[rel]["sha256"]:
            fail(f"C8 stale hash {rel}")
    counts = manifest.get("counts", {})
    if counts.get("files") != len(actual):
        fail(f"C8 counts.files={counts.get('files')} actual={len(actual)}")
    if counts.get("spec_docs") != len(list(ROOT.glob("spec/*.md"))):
        fail(f"C8 counts.spec_docs={counts.get('spec_docs')}")
    if counts.get("analysis_docs") != len(list(ROOT.glob("analysis/*.md"))):
        fail(f"C8 counts.analysis_docs={counts.get('analysis_docs')}")
    registered = collect_registered_open()
    if manifest.get("open_item_count") != len(registered):
        fail(f"C8 open_item_count={manifest.get('open_item_count')} registry={len(registered)}")


def check_placeholders() -> None:
    for path in sorted(ROOT.rglob("*.md")):
        rel = path.relative_to(ROOT).as_posix()
        for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
            for token in ("TODO", "TBD", "XXX", "FIXME"):
                if token in line:
                    fail(f"C9 {rel}:{number} contains {token}")


def main() -> int:
    check_files()
    rules = collect_rules()
    check_references(rules)
    check_coverage()
    check_banned()
    check_vectors()
    check_manifest()
    check_placeholders()
    # Cross-docset original-byte evidence, not merely self-generated vectors.
    audit = subprocess.run([sys.executable, "-B", str(ROOT.parent / "airplay_rtp_timing" /
                           "reference-impl/verify_audio_message.py")],
                           capture_output=True, text=True, encoding="utf-8", errors="replace")
    if audit.returncode:
        fail("C10 message source audit: " + audit.stdout + audit.stderr)
    else:
        print("C10 " + audit.stdout.strip())

    fields = subprocess.run([sys.executable, "-B", str(ROOT / "tools/verify-config-fields.py")],
                            capture_output=True, text=True, encoding="utf-8", errors="replace")
    if fields.returncode:
        fail("C11 config source audit: " + fields.stdout + fields.stderr)
    else:
        print(fields.stdout.strip())

    formats = subprocess.run([sys.executable, "-B", str(ROOT / "tools/verify-format-map.py")],
                             capture_output=True, text=True, encoding="utf-8", errors="replace")
    if formats.returncode:
        fail("C12 format map audit: " + formats.stdout + formats.stderr)
    else:
        print(formats.stdout.strip())

    policy = subprocess.run([sys.executable, "-B", str(ROOT / "tools/verify-capability-policy.py")],
                            capture_output=True, text=True, encoding="utf-8", errors="replace")
    if policy.returncode:
        fail("C13 capability policy audit: " + policy.stdout + policy.stderr)
    else:
        print(policy.stdout.strip())

    print(f"rules: {len(rules)}")
    print(f"failures: {len(failures)}  warnings: {len(warnings)}")
    for line in failures:
        print("  FAIL", line)
    for line in warnings:
        print("  WARN", line)
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
