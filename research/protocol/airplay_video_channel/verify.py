#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""verify.py — airplay_video_channel docset 自校验。

用法：
    cd D:\\carvex-research\\research\\protocol\\airplay_video_channel && python3 verify.py
    python3 verify.py --quiet

检查类别：
    C1 manifest        清单与实际文件一致（无缺失/多余/改动）
    C2 source          镜像哈希、汇编导出、.bin 与镜像切片逐字节一致、.s 字节列一致
    C3 readable        selection 中每个函数都有 .ghidra.c 与 .json
    C4 analysis        00–07 + A 结论表存在；A 编号唯一；位置指向存在文件
    C5 spec            条款编号唯一、格式合法、依据引用的 A 编号存在
    C6 cross-docset    所有 ctrl/R-x.y 与 link/R-x.y 在对应 docset 中存在
    C7 open-registry   所有 OPEN-VID-n 在 coverage.json 登记且被覆盖项引用
    C8 coverage        12 个覆盖项状态/引用/汇总自洽
    C9 addresses       文档中的代码地址落在 __TEXT 窗口内
    C10 wrapper-header 固定SHA/五份重反汇编、ABI/标签/字段锚点及局部边界
"""
import hashlib
import json
import os
import re
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
DOCS = os.path.dirname(ROOT)
QUIET = "--quiet" in sys.argv

FAILS = []
WARNS = []


def fail(check, msg):
    FAILS.append((check, msg))


def warn(check, msg):
    WARNS.append((check, msg))


def rel(*parts):
    return os.path.join(ROOT, *parts)


def read(path):
    with open(path, "rb") as f:
        return f.read().decode("utf-8", "replace")


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def load_json(path):
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def walk_files():
    out = []
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if d not in (".git",)]
        for n in names:
            p = os.path.join(base, n)
            out.append(os.path.relpath(p, ROOT).replace("\\", "/"))
    return out


def md_files():
    return [(p, read(rel(p))) for p in walk_files() if p.endswith(".md")]


# ---------------------------------------------------------------- C1 manifest
def check_manifest():
    if not os.path.exists(rel("manifest.json")):
        fail("C1", "manifest.json 不存在（先运行 python3 tools/manifest.py）")
        return
    man = load_json(rel("manifest.json"))
    listed = {e["path"]: e for e in man["files"]}
    actual = set(walk_files()) - {"manifest.json"}
    for r in sorted(actual - set(listed)):
        fail("C1", "清单缺失文件：%s" % r)
    for r in sorted(set(listed) - actual):
        fail("C1", "清单多余文件：%s" % r)
    for r in sorted(actual & set(listed)):
        e = listed[r]
        p = rel(r)
        if os.path.getsize(p) != e["size"]:
            fail("C1", "大小不一致：%s" % r)
        elif sha256(p) != e["sha256"]:
            fail("C1", "哈希不一致（文档已改动，需重生成清单）：%s" % r)


# ------------------------------------------------------------------ C2 source
def check_source():
    cov = load_json(rel("source", "metadata", "coverage.json"))
    img = cov["image"]
    binp = rel("source", "firmware", "AirPlaySender")
    if not os.path.exists(binp):
        fail("C2", "镜像不存在：source/firmware/AirPlaySender")
        return
    got = sha256(binp)
    if got != img["sha256"]:
        fail("C2", "镜像哈希不符：%s != %s" % (got, img["sha256"]))
    blob = open(binp, "rb").read()
    if len(blob) != img["size"]:
        fail("C2", "镜像大小不符：%d" % len(blob))

    idx = load_json(rel("source", "asm", "airplaysender", "index.json"))
    if idx["source_sha256"] != img["sha256"]:
        fail("C2", "index.json 的源哈希不符")
    if idx["count"] < 10:
        fail("C2", "汇编函数过少：%d" % idx["count"])

    for f in idx["functions"]:
        p = rel("source", "asm", "airplaysender", f["bin"])
        if not os.path.exists(p):
            fail("C2", "缺 .bin：%s" % f["bin"])
            continue
        raw = open(p, "rb").read()
        if sha256(p) != f["raw_sha256"]:
            fail("C2", ".bin 哈希不符：%s" % f["bin"])
        if len(raw) != f["size"]:
            fail("C2", ".bin 大小不符：%s" % f["bin"])
        start = int(f["address"], 16)
        if blob[start - 0x251996000:start - 0x251996000 + f["size"]] != raw:
            fail("C2", ".bin 与镜像切片不一致：%s" % f["bin"])

        sp = rel("source", "asm", "airplaysender", f["asm"])
        head = read(sp).splitlines()[:3]
        if not head[0].startswith("; airplaysender "):
            fail("C2", ".s 头部缺失镜像名：%s" % f["asm"])
        if img["sha256"] not in head[0]:
            fail("C2", ".s 头部源哈希不符：%s" % f["asm"])

        # 抽 3 条指令，字节列必须与镜像一致
        lines = [l for l in read(sp).splitlines()[3:] if l.startswith("0x")][:200]
        for line in (lines[:1] + lines[len(lines) // 2:len(lines) // 2 + 1] + lines[-1:]):
            parts = line.split("\t")
            if len(parts) < 2:
                continue
            addr = int(parts[0].split(":")[0], 16)
            code = parts[1].strip()
            if not re.fullmatch(r"[0-9a-f]{8}", code):
                continue
            rawins = bytes.fromhex("".join(reversed([code[i:i + 2] for i in range(0, 8, 2)])))
            off = addr - 0x251996000
            if blob[off:off + 4] != rawins:
                fail("C2", ".s 字节列与镜像不符：%s @ 0x%x" % (f["asm"], addr))


# ---------------------------------------------------------------- C3 readable
def check_readable():
    sel = load_json(rel("source", "metadata", "selection.json"))
    img = load_json(rel("source", "metadata", "coverage.json"))["image"]
    for f in sel["functions"]:
        stem = "f_%x" % int(f["address"], 16)
        c = rel("readable", "ghidra", "airplaysender", stem + ".ghidra.c")
        j = rel("readable", "ghidra", "airplaysender", stem + ".json")
        if not os.path.exists(c):
            fail("C3", "缺反编译：%s" % stem)
            continue
        if not os.path.exists(j):
            fail("C3", "缺 readable json：%s" % stem)
            continue
        text = read(c)
        if img["sha256"] not in text:
            fail("C3", "反编译源哈希不符：%s" % stem)
        if "RAW GHIDRA DECOMPILATION" not in text:
            fail("C3", "反编译缺少未审标记：%s" % stem)
        d = load_json(j)
        if d.get("evidence_status") != "DECOMPILED_UNREVIEWED":
            fail("C3", "readable json 状态不符：%s" % stem)


# ---------------------------------------------------------------- C4 analysis
A_RE = re.compile(r"`A(\d\d)\.(\d+)`")
POS_RE = re.compile(r"\|\s*(\d\d)\s*§")


def check_analysis():
    need = ["00-method-and-environment.md", "01-stream-identity-and-setup.md",
            "02-screen-record-format.md", "03-frame-encryption.md",
            "04-avc-payload.md", "05-transport-timing-recovery.md",
            "06-wrapper-and-header-audit.md", "07-codec-config-and-flags.md", "A-conclusions.md"]
    for n in need:
        if not os.path.exists(rel("analysis", n)):
            fail("C4", "缺 analysis/%s" % n)
    if not os.path.exists(rel("analysis", "A-conclusions.md")):
        return set()
    text = read(rel("analysis", "A-conclusions.md"))
    ids = set()
    rows = 0
    for line in text.splitlines():
        if not line.startswith("|"):
            continue
        m = A_RE.search(line)
        if not m:
            continue
        rows += 1
        aid = "A%s.%s" % (m.group(1), m.group(2))
        if aid in ids:
            fail("C4", "A 编号重复：%s" % aid)
        ids.add(aid)
        pm = POS_RE.search(line)
        if not pm:
            fail("C4", "A 行缺位置：%s" % aid)
            continue
        num = pm.group(1)
        if not any(n.startswith(num + "-") for n in need):
            fail("C4", "%s 的位置指向不存在的文件：%s" % (aid, num))
    if rows < 30:
        fail("C4", "A 结论过少：%d" % rows)
    return ids


# -------------------------------------------------------------------- C5 spec
RULE_RE = re.compile(r"\*\*(R-\d+\.\d+)（(MUST|SHOULD|未定义) / (CONFIRMED|INFERRED|OPEN)）\*\*")


def check_spec(a_ids):
    files = sorted(n for n in os.listdir(rel("spec")) if n.endswith(".md"))
    if len(files) < 9:
        fail("C5", "spec 文件过少：%d" % len(files))
    ids = []
    for n in files:
        text = read(rel("spec", n))
        cur = None
        cur_line = 0
        have = False
        for i, line in enumerate(text.splitlines(), 1):
            m = RULE_RE.search(line)
            if re.search(r"\*\*R-\d+\.\d+（", line) and not m:
                fail("C5", "%s:%d 条款元数据格式错误，不能静默漏检" % (n, i))
            if m:
                if cur and not have:
                    fail("C5", "%s 的条款 %s 缺 依据 行" % (n, cur))
                cur = m.group(1)
                cur_line = i
                have = False
                if cur in ids:
                    fail("C5", "条款编号重复：%s" % cur)
                ids.append(cur)
                continue
            if cur and not have and line.strip().startswith("依据："):
                have = True
                for a in A_RE.findall(line):
                    aid = "A%s.%s" % a
                    if a_ids and aid not in a_ids:
                        fail("C5", "%s 引用了不存在的结论 %s" % (cur, aid))
        if cur and not have:
            fail("C5", "%s 的条款 %s 缺 依据 行" % (n, cur))
    if len(ids) < 30:
        fail("C5", "条款过少：%d" % len(ids))
    return ids


# ------------------------------------------------------------ C6 cross-docset
def check_cross():
    ctrl_dir = os.path.join(DOCS, "iap2_control_session", "spec")
    link_dir = os.path.join(DOCS, "iap2_link_establish", "spec")
    texts = {"ctrl": "", "link": ""}
    for key, d in (("ctrl", ctrl_dir), ("link", link_dir)):
        if not os.path.isdir(d):
            fail("C6", "找不到上一阶段 docset：%s" % d)
            continue
        for n in os.listdir(d):
            if n.endswith(".md"):
                texts[key] += read(os.path.join(d, n)) + "\n"
    for p, text in md_files():
        for key, rid in re.findall(r"`(ctrl|link)/(R-\d+\.\d+)`", text):
            if ("`%s`" % rid) not in texts.get(key, ""):
                fail("C6", "%s 引用的 %s/%s 不存在" % (p, key, rid))


# ---------------------------------------------------------------- C7 open ids
def check_open():
    cov = load_json(rel("source", "metadata", "coverage.json"))
    reg = {o["id"]: o for o in cov["open_items"]}
    used = set()
    for p, text in md_files():
        for oid in set(re.findall(r"OPEN-VID-\d+", text)):
            used.add(oid)
            if oid not in reg:
                fail("C7", "%s 出现未登记的 %s" % (p, oid))
    for oid in sorted(set(reg) - used):
        fail("C7", "%s 已登记但文中从未引用" % oid)
    for it in cov["items"]:
        for oid in it.get("open", []):
            if oid not in reg:
                fail("C7", "%s 引用了未登记的 %s" % (it["id"], oid))
    referenced = {oid for it in cov["items"] for oid in it.get("open", [])}
    for oid in sorted(set(reg) - referenced):
        fail("C7", "%s 未被任何覆盖项引用" % oid)


# ------------------------------------------------------------------ C8 cover
def check_coverage():
    cov = load_json(rel("source", "metadata", "coverage.json"))
    items = cov["items"]
    if len(items) != 12:
        fail("C8", "覆盖项应为 12，实为 %d" % len(items))
    legend = set(cov["status_legend"])
    for it in items:
        if it["status"] not in legend:
            fail("C8", "%s 的状态非法：%s" % (it["id"], it["status"]))
        if it["status"] in ("部分确认", "OPEN") and not it.get("open"):
            fail("C8", "%s 为 %s 但没有 open 项" % (it["id"], it["status"]))
        if it["status"] == "已确认" and not it.get("rules"):
            fail("C8", "%s 已确认但没有条款" % it["id"])
        if not it.get("analysis"):
            fail("C8", "%s 没有 analysis 引用" % it["id"])
    s = cov["summary"]
    if s["total_items"] != len(items):
        fail("C8", "summary.total_items 不一致")
    for k, st in (("confirmed", "已确认"), ("partial", "部分确认"), ("open", "OPEN")):
        n = sum(1 for i in items if i["status"] == st)
        if s[k] != n:
            fail("C8", "summary.%s=%d，实际 %d" % (k, s[k], n))
    if s["open_ids"] != len(cov["open_items"]):
        fail("C8", "summary.open_ids 不一致")
    for p, text in md_files():
        for line in text.splitlines():
            if "全部确认" in line and not any(x in line for x in ("不", "未", "非", "禁止", "无法", "没有")):
                fail("C8", "%s 出现无据的“全部确认”" % p)
                break


# ----------------------------------------------------------------- C9 address
def check_addresses():
    seg = load_json(rel("source", "metadata", "segments.json"))
    t = [s for s in seg if s["segname"] == "__TEXT"][0]
    lo, hi = t["vmaddr"], t["vmaddr"] + t["vmsize"]
    for p, text in md_files():
        for line in text.splitlines():
            if "[跨镜像]" in line:
                continue
            for a in re.findall(r"0x(251[0-9a-f]{6})", line):
                v = int(a, 16)
                if not (lo <= v <= hi):
                    fail("C9", "%s 的地址 0x%s 越出 __TEXT" % (p, a))


def main() -> int:
    check_manifest()
    check_source()
    check_readable()
    a_ids = check_analysis()
    check_spec(a_ids)
    check_cross()
    check_open()
    check_coverage()
    check_addresses()
    audit = subprocess.run([sys.executable, "-B", rel("tools", "verify-wrapper.py")],
                           capture_output=True, text=True, encoding="utf-8", errors="replace")
    if audit.returncode:
        fail("C10", (audit.stdout + audit.stderr).strip())
    elif not QUIET:
        print(audit.stdout.strip())

    codec_audit = subprocess.run([sys.executable, "-B", rel("tools", "verify-codec-config.py")],
                                 capture_output=True, text=True, encoding="utf-8", errors="replace")
    if codec_audit.returncode:
        fail("C11", (codec_audit.stdout + codec_audit.stderr).strip())
    elif not QUIET:
        print(codec_audit.stdout.strip())

    if not QUIET:
        for c, m in WARNS:
            print("WARN  [%s] %s" % (c, m))
    for c, m in FAILS:
        print("FAIL  [%s] %s" % (c, m))
    print("---")
    print("checks: C1 manifest / C2 source / C3 readable / C4 analysis / C5 spec / "
          "C6 cross-docset / C7 open-registry / C8 coverage / C9 addresses / C10 wrapper-header / C11 codec-config")
    print("failures: %d  warnings: %d" % (len(FAILS), len(WARNS)))
    return 1 if FAILS else 0


if __name__ == "__main__":
    raise SystemExit(main())
