#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""verify.py — iap2_control_session docset 自校验（8 类检查）。

用法：
    cd D:\\carvex-research\\research\\protocol\\iap2_control_session && python3 verify.py
    python3 verify.py --quiet        # 只打印失败与汇总

检查类别：
    C1 manifest        清单与实际文件一致（无缺失/多余/改动）
    C2 source          镜像哈希、汇编导出数量、每个 .bin 与镜像切片一致
    C3 readable        selection 中每个函数都有 .ghidra.c 与 .json
    C4 analysis        00–13 + A 结论表存在；A 编号唯一；"位置"指向存在的文件
    C5 spec            条款行格式、编号唯一、依据行引用的 A 编号存在
    C6 cross-docset    所有 link/R-x.y 在上一阶段 spec 中存在
    C7 open-registry   所有 OPEN-SES-n 在 coverage.json 登记；无孤立条目
    C8 coverage         12 个覆盖项状态/引用/汇总自洽
"""
import hashlib
import json
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
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


def md_files():
    out = []
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if d not in (".git",)]
        for n in sorted(names):
            if n.endswith(".md"):
                p = os.path.join(base, n)
                out.append((os.path.relpath(p, ROOT).replace("\\", "/"), read(p)))
    return out


def load_json(path):
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def toint(v):
    if isinstance(v, int):
        return v
    return int(str(v), 16) if str(v).lower().startswith("0x") else int(str(v), 0)


# ---------------------------------------------------------------- C1 manifest
def check_manifest():
    path = rel("manifest.json")
    if not os.path.exists(path):
        fail("C1", "manifest.json 不存在（先运行 gen-manifest.py）")
        return
    man = load_json(path)
    listed = {e["path"]: e for e in man["files"]}
    actual = set()
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if d not in (".git",)]
        for n in names:
            p = os.path.join(base, n)
            r = os.path.relpath(p, ROOT).replace("\\", "/")
            if r == "manifest.json":
                continue
            actual.add(r)
    for r in sorted(actual - set(listed)):
        fail("C1", "清单缺失文件：%s" % r)
    for r in sorted(set(listed) - actual):
        fail("C1", "清单多余文件：%s" % r)
    for r in sorted(actual & set(listed)):
        e = listed[r]
        p = os.path.join(ROOT, r.replace("/", os.sep))
        if os.path.getsize(p) != e["size"]:
            fail("C1", "大小不一致：%s" % r)
        elif sha256(p) != e["sha256"]:
            fail("C1", "哈希不一致（文档已改动，需重生成清单）：%s" % r)


# ------------------------------------------------------------------ C2 source
def check_source():
    cov = load_json(rel("source", "metadata", "coverage.json"))
    want = cov["image"]["sha256"]
    binp = rel("source", "firmware", "accessoryd")
    if not os.path.exists(binp):
        fail("C2", "镜像不存在：source/firmware/accessoryd")
        return
    got = sha256(binp)
    if got != want:
        fail("C2", "镜像哈希不符：%s != %s" % (got, want))
    blob = open(binp, "rb").read()

    sel = load_json(rel("source", "metadata", "selection.json"))
    funcs = load_json(rel("source", "metadata", "ghidra-request.json"))["functions"]
    idx = load_json(rel("source", "asm", "accessoryd", "index.json"))
    if idx.get("missing"):
        fail("C2", "汇编导出有 %d 个缺失" % len(idx["missing"]))
    if len(idx["functions"]) != len(funcs):
        fail("C2", "index 函数数 %d != 请求 %d" % (len(idx["functions"]), len(funcs)))
    if idx.get("exported") not in (None, len(funcs)):
        fail("C2", "index.exported %s != %d" % (idx.get("exported"), len(funcs)))
    if sel.get("functions") and len(sel["functions"]) != len(funcs):
        fail("C2", "selection 函数数 %d != 请求 %d"
             % (len(sel["functions"]), len(funcs)))

    base = 0x100000000
    for f in funcs:
        addr, end = toint(f["address"]), toint(f["end"])
        stem = "f_%x" % addr
        sp = os.path.join(ROOT, "source", "asm", "accessoryd", stem + ".s")
        bp = os.path.join(ROOT, "source", "asm", "accessoryd", stem + ".bin")
        if not os.path.exists(sp) or not os.path.exists(bp):
            fail("C2", "缺少汇编/字节文件：%s" % stem)
            continue
        raw = open(bp, "rb").read()
        if raw != blob[addr - base:end - base]:
            fail("C2", "字节切片与镜像不一致：%s" % stem)
            continue
        head = read(sp).splitlines()[0]
        if ("0x%x" % addr) not in head:
            fail("C2", "%s 首行缺少地址" % stem)
        if want not in head:
            fail("C2", "%s 首行缺少源哈希" % stem)


# ---------------------------------------------------------------- C3 readable
def check_readable():
    funcs = load_json(rel("source", "metadata", "ghidra-request.json"))["functions"]
    d = rel("readable", "ghidra", "accessoryd")
    if not os.path.isdir(d):
        fail("C3", "readable/ghidra/accessoryd 不存在")
        return
    n = 0
    for f in funcs:
        a = toint(f["address"])
        stem = "f_%x" % a
        c = os.path.join(d, stem + ".ghidra.c")
        j = os.path.join(d, stem + ".json")
        if not os.path.exists(c):
            fail("C3", "缺少反编译：%s.ghidra.c" % stem)
            continue
        if not os.path.exists(j):
            fail("C3", "缺少反编译元数据：%s.json" % stem)
        text = read(c)[:600]
        if "original address: 0x%x" % a not in text:
            fail("C3", "%s 头部地址不符" % stem)
        n += 1
    if n == 0:
        fail("C3", "没有任何反编译文件")


# ---------------------------------------------------------------- C4 analysis
A_ROW = re.compile(r"`A(\d\d)\.(\d+)`")
A_POS = re.compile(r"\|\s*(\d\d)\s*§")


def check_analysis():
    adir = rel("analysis")
    if not os.path.isdir(adir):
        fail("C4", "analysis/ 不存在")
        return
    names = sorted(n for n in os.listdir(adir) if n.endswith(".md"))
    for i in range(14):
        if not any(n.startswith("%02d-" % i) for n in names):
            fail("C4", "缺少 analysis/%02d-*.md" % i)
    if "A-conclusions.md" not in names:
        fail("C4", "缺少 analysis/A-conclusions.md")
        return

    text = read(os.path.join(adir, "A-conclusions.md"))
    ids = []
    for line in text.splitlines():
        m = A_ROW.search(line)
        if m and line.lstrip().startswith("|"):
            ids.append("A%s.%s" % (m.group(1), m.group(2)))
            p = A_POS.search(line)
            if p:
                num = p.group(1)
                if not any(n.startswith(num + "-") for n in names):
                    fail("C4", "%s 的位置指向不存在的 analysis/%s-*.md"
                         % ("A%s.%s" % (m.group(1), m.group(2)), num))
    if len(ids) != len(set(ids)):
        dup = sorted({x for x in ids if ids.count(x) > 1})
        fail("C4", "A 编号重复：%s" % ", ".join(dup))
    if len(ids) < 40:
        fail("C4", "A 结论过少（%d 条）" % len(ids))
    check_analysis.ids = set(ids)


# -------------------------------------------------------------------- C5 spec
RULE = re.compile(
    r"`R-(\d+)\.(\d+)`（(MUST|SHOULD|未定义) / (CONFIRMED|INFERRED|OPEN)）")


def check_spec(a_ids):
    sdir = rel("spec")
    if not os.path.isdir(sdir):
        fail("C5", "spec/ 不存在")
        return set()
    names = sorted(n for n in os.listdir(sdir) if n.endswith(".md"))
    for i in range(8):
        if not any(n.startswith("%02d-" % i) for n in names):
            fail("C5", "缺少 spec/%02d-*.md" % i)

    rules = {}
    for n in names:
        text = read(os.path.join(sdir, n))
        matches = list(RULE.finditer(text))
        for k, m in enumerate(matches):
            rid = "R-%s.%s" % (m.group(1), m.group(2))
            if rid in rules:
                fail("C5", "条款编号重复：%s（%s 与 %s）" % (rid, rules[rid], n))
            rules[rid] = n
            end = matches[k + 1].start() if k + 1 < len(matches) else len(text)
            body = text[m.end():end]
            if "依据：" not in body:
                fail("C5", "%s 缺少“依据：”行" % rid)
                continue
            cited = set(A_ROW.findall(body))
            if not cited:
                fail("C5", "%s 的依据未引用任何 A 编号" % rid)
            for a, b in cited:
                aid = "A%s.%s" % (a, b)
                if aid not in a_ids:
                    fail("C5", "%s 引用了不存在的结论 %s" % (rid, aid))
    if len(rules) < 60:
        warn("C5", "条款数偏少：%d" % len(rules))
    return set(rules)


# ------------------------------------------------------------ C6 cross-docset
LINK_REF = re.compile(r"link/(R-\d+\.\d+)")
LINK_RULE = re.compile(r"`R-(\d+)\.(\d+)`")


def check_cross():
    link_spec = os.path.join(os.path.dirname(ROOT), "iap2_link_establish", "spec")
    if not os.path.isdir(link_spec):
        fail("C6", "上一阶段 spec 不存在：%s" % link_spec)
        return
    have = set()
    for n in os.listdir(link_spec):
        if not n.endswith(".md"):
            continue
        for a, b in LINK_RULE.findall(read(os.path.join(link_spec, n))):
            have.add("R-%s.%s" % (a, b))
    if not have:
        fail("C6", "上一阶段未解析出任何条款")
        return
    refs = set()
    for name, text in md_files():
        for r in LINK_REF.findall(text):
            refs.add((r, name))
    for r, name in sorted(refs):
        if r not in have:
            fail("C6", "%s 引用了不存在的上一阶段条款 link/%s" % (name, r))
    if not refs:
        warn("C6", "本文档集未引用任何上一阶段条款")


# ----------------------------------------------------------- C7 open registry
OPEN_REF = re.compile(r"OPEN-SES-(\d+)")


def check_open():
    cov = load_json(rel("source", "metadata", "coverage.json"))
    reg = {}
    for e in cov["open_items"]:
        if e["id"] in reg:
            fail("C7", "OPEN 条目重复登记：%s" % e["id"])
        reg[e["id"]] = e
    seen = {}
    for name, text in md_files():
        for num in OPEN_REF.findall(text):
            seen.setdefault("OPEN-SES-%s" % num, set()).add(name)
    for k in sorted(seen, key=lambda s: int(s.rsplit("-", 1)[1])):
        if k not in reg:
            fail("C7", "%s 在正文出现但未在 coverage.json 登记（%s）"
                 % (k, ", ".join(sorted(seen[k]))[:120]))
    used = set()
    for it in cov["items"]:
        used |= set(it["open"])
    for k, e in sorted(reg.items()):
        if e["where"] == "—":
            continue
        if k not in used:
            fail("C7", "%s 已登记但没有任何覆盖项引用" % k)
    check_open.reg = reg


# --------------------------------------------------------------- C8 coverage
def check_coverage(spec_ids):
    cov = load_json(rel("source", "metadata", "coverage.json"))
    items = cov["items"]
    if len(items) != 12:
        fail("C8", "覆盖项应为 12，实为 %d" % len(items))
    ids = [i["id"] for i in items]
    if len(ids) != len(set(ids)):
        fail("C8", "覆盖项编号重复")
    counts = {}
    for it in items:
        st = it["status"]
        if st not in cov["status_legend"]:
            fail("C8", "%s 状态非法：%s" % (it["id"], st))
        counts[st] = counts.get(st, 0) + 1
        for r in it["spec"]:
            if r not in spec_ids:
                fail("C8", "%s 引用了不存在的条款 %s" % (it["id"], r))
        for a in it["analysis"]:
            if a not in check_analysis.ids:
                fail("C8", "%s 引用了不存在的结论 %s" % (it["id"], a))
        if st in ("部分确认", "OPEN") and not it["open"]:
            fail("C8", "%s 状态为 %s 但未登记 OPEN 条目" % (it["id"], st))
        if not it["note"]:
            fail("C8", "%s 缺少说明" % it["id"])
    want = {k: cov["summary"][k] for k in ("已确认", "部分确认", "OPEN")}
    for k in want:
        if want[k] != counts.get(k, 0):
            fail("C8", "汇总 %s 应为 %d，实为 %d" % (k, want[k], counts.get(k, 0)))

    # 禁止性声明：只拦"断言式"，放行"不得/未/非"等否定语境
    NEG = ("不得", "不要", "不", "未", "非", "禁止", "无法", "没有")
    for name, text in md_files():
        for line in text.splitlines():
            if "全部确认" in line and not any(x in line for x in NEG):
                fail("C8", "%s 出现“全部确认”这类无据断言" % name)
                break


def main() -> int:
    check_manifest()
    check_source()
    check_readable()
    check_analysis()
    spec_ids = check_spec(check_analysis.ids)
    check_cross()
    check_open()
    check_coverage(spec_ids)

    if not QUIET:
        for c, m in WARNS:
            print("WARN  [%s] %s" % (c, m))
    for c, m in FAILS:
        print("FAIL  [%s] %s" % (c, m))
    total = len(FAILS)
    print("---")
    print("checks: C1 manifest / C2 source / C3 readable / C4 analysis / "
          "C5 spec / C6 cross-docset / C7 open-registry / C8 coverage")
    print("failures: %d  warnings: %d" % (total, len(WARNS)))
    return 1 if total else 0


if __name__ == "__main__":
    raise SystemExit(main())
