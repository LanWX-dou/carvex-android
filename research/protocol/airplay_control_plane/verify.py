#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Acceptance checks for research/protocol/airplay_control_plane (iteration 1).

Run:  cd research/protocol/airplay_control_plane && python3 verify.py
Exit code 0 = all checks pass.
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

IMAGES = {
    "AirPlaySender": "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f",
    "APTransport": "e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d",
    "CoreUtils": "3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083",
}
FAILS = []


def fail(check, msg):
    FAILS.append((check, msg))


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for c in iter(lambda: f.read(1 << 20), b""):
            h.update(c)
    return h.hexdigest()


def md_files(sub):
    d = os.path.join(ROOT, sub)
    if not os.path.isdir(d):
        return []
    return [os.path.join(d, n) for n in sorted(os.listdir(d)) if n.endswith(".md")]


def read(p):
    return open(p, encoding="utf-8").read()


# ---------------------------------------------------------------- C1 manifest
def c1():
    p = os.path.join(ROOT, "manifest.json")
    if not os.path.exists(p):
        return fail("C1", "manifest.json 不存在")
    m = json.load(open(p, encoding="utf-8"))
    listed = {f["path"]: f for f in m.get("files", [])}
    actual = set()
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".git")]
        for n in names:
            rel = os.path.relpath(os.path.join(base, n), ROOT).replace("\\", "/")
            if rel != "manifest.json":
                actual.add(rel)
    missing = sorted(set(listed) - actual)
    extra = sorted(actual - set(listed))
    if missing:
        fail("C1", "manifest 列出但磁盘缺失: %s" % missing[:5])
    if extra:
        fail("C1", "磁盘有但 manifest 未列: %s" % extra[:5])
    bad = []
    for rel, f in listed.items():
        p2 = os.path.join(ROOT, rel)
        if not os.path.exists(p2):
            continue
        if os.path.getsize(p2) != f["size"] or sha256(p2) != f["sha256"]:
            bad.append(rel)
    if bad:
        fail("C1", "hash/大小不符: %s" % bad[:5])


# ------------------------------------------------------------ C2 image hashes
def c2():
    for name, want in IMAGES.items():
        p = os.path.join(ROOT, "source", "firmware", name)
        if not os.path.exists(p):
            fail("C2", "缺少镜像 %s" % name)
            continue
        got = sha256(p)
        if got != want:
            fail("C2", "%s sha256 不符: %s" % (name, got))
    doc = read(os.path.join(ROOT, "analysis", "00-method-and-environment.md"))
    for name, h in IMAGES.items():
        if h not in doc:
            fail("C2", "analysis/00 未记录 %s 的 sha256" % name)


# --------------------------------------------------------- C3 readable output
def c3():
    for name, h in IMAGES.items():
        d = os.path.join(ROOT, "readable", "ghidra", name)
        if not os.path.isdir(d):
            fail("C3", "缺少 readable/ghidra/%s" % name)
            continue
        cs = [n for n in os.listdir(d) if n.endswith(".ghidra.c")]
        jss = [n for n in os.listdir(d) if n.endswith(".json")]
        if len(cs) < 10 or len(jss) != len(cs):
            fail("C3", "%s 反编译文件数异常: c=%d json=%d" % (name, len(cs), len(jss)))
        for n in jss[:200]:
            m = json.load(open(os.path.join(d, n), encoding="utf-8"))
            if m.get("source_sha256") != h:
                fail("C3", "%s/%s source_sha256 不符" % (name, n))
                break
            if m.get("evidence_status") != "RAW_DECOMPILER_OUTPUT_UNREVIEWED":
                fail("C3", "%s/%s 未标注未复核" % (name, n))
                break


# ------------------------------------------------------------ C4 analysis set
def c4():
    need = ["00-method-and-environment", "01-control-channel-and-rtsp", "02-pair-setup",
            "03-pair-verify", "04-encrypted-session", "05-rtsp-methods", "06-setup-and-type130",
            "07-tunnel-handoff", "08-errors-timeouts", "09-security", "10-runtime-captures",
            "11-function-inventory", "A-conclusions"]
    for n in need:
        if not os.path.exists(os.path.join(ROOT, "analysis", n + ".md")):
            fail("C4", "缺少 analysis/%s.md" % n)
    ids = []
    for p in md_files("analysis"):
        if os.path.basename(p) == "A-conclusions.md":
            continue
        ids += re.findall(r"\b(A\d\d\.\d+)\b", read(p))
    dup = sorted({i for i in ids if ids.count(i) > 1})
    # 同一 id 在正文中被引用多次是正常的；只要求 A 登记表覆盖全集
    reg = read(os.path.join(ROOT, "analysis", "A-conclusions.md"))
    uniq = sorted(set(ids))
    miss = [i for i in uniq if i not in reg]
    if miss:
        fail("C4", "A 结论未登记: %s" % miss[:5])
    if len(uniq) < 40:
        fail("C4", "A 结论过少: %d" % len(uniq))


# ----------------------------------------------------------------- C5 spec set
def c5():
    spec = os.path.join(ROOT, "spec")
    need = ["00-scope-and-terms", "01-control-channel", "02-pairing", "03-encrypted-session",
            "04-rtsp", "05-setup-and-tunnel", "06-client-guide", "07-conformance-checklist",
            "08-open-items"]
    for n in need:
        if not os.path.exists(os.path.join(spec, n + ".md")):
            fail("C5", "缺少 spec/%s.md" % n)
    # 只有"条款定义"（行首 - R-x.y 或 R-x.y）需要 依据；正文里的 R-x.y 是引用，不参与重复判定
    rid = {}
    defpat = re.compile(r"^\s*(?:[-*]\s+)?(R-\d+\.\d+)\s")
    for p in md_files("spec"):
        lines = read(p).splitlines()
        for i, line in enumerate(lines):
            m = defpat.match(line)
            if not m:
                continue
            rid.setdefault(m.group(1), []).append(os.path.basename(p))
            ctx = " ".join(lines[i:i + 5])
            if ("依据" not in ctx) and not re.search(r"A\d\d\.\d", ctx) and ("OPEN-AP" not in ctx):
                fail("C5", "%s 中 %s 缺依据" % (os.path.basename(p), m.group(1)))
    dup = {k: v for k, v in rid.items() if len(v) > 1}
    if dup:
        fail("C5", "R 编号跨文件重复: %s" % list(dup)[:5])
    reg = read(os.path.join(spec, "08-open-items.md"))
    for p in md_files("spec"):
        for oid in set(re.findall(r"OPEN-AP-\d+", read(p))):
            if oid not in reg:
                fail("C5", "%s 引用未登记的 %s" % (os.path.basename(p), oid))


# ------------------------------------------------------------ C6 cross-docset
def c6():
    m = {"cs": "iap2_control_session", "link": "iap2_link_establish", "bt": "bluetooth_rfcomm"}
    for p in md_files("analysis") + md_files("spec"):
        text = read(p)
        for pre, ref in re.findall(r"\b(cs|link|bt)/(R-\d+\.\d+)\b", text):
            d = os.path.join(DOCS, m[pre], "spec")
            hit = False
            if os.path.isdir(d):
                for q in os.listdir(d):
                    if q.endswith(".md") and ref in read(os.path.join(d, q)):
                        hit = True
                        break
            if not hit:
                fail("C6", "%s 引用 %s/%s 无法解析" % (os.path.basename(p), pre, ref))


# ----------------------------------------------------------- C7 OPEN registry
def c7():
    reg = read(os.path.join(ROOT, "spec", "08-open-items.md"))
    reg_ids = set(re.findall(r"OPEN-AP-(\d+)", reg))
    used = set()
    for p in md_files("analysis") + md_files("spec"):
        used |= {x for x in re.findall(r"OPEN-AP-(\d+)", read(p))}
    miss = sorted(used - reg_ids, key=int)
    if miss:
        fail("C7", "OPEN 未登记: %s" % ["OPEN-AP-" + x for x in miss[:5]])
    if len(reg_ids) < 30:
        fail("C7", "OPEN 登记过少: %d" % len(reg_ids))
    for p in md_files("spec"):
        t = read(p)
        for bad in ("全部确认", "实测"):
            if bad in t:
                fail("C7", "%s 出现禁用表述 %s" % (os.path.basename(p), bad))


# -------------------------------------------------------------- C8 coverage
def c8():
    p = os.path.join(ROOT, "coverage.json")
    if not os.path.exists(p):
        return fail("C8", "coverage.json 不存在")
    c = json.load(open(p, encoding="utf-8"))
    items = c.get("items", [])
    if len(items) != 12:
        fail("C8", "覆盖项应为 12，实为 %d" % len(items))
    reg = read(os.path.join(ROOT, "analysis", "A-conclusions.md"))
    op = read(os.path.join(ROOT, "spec", "08-open-items.md"))
    for it in items:
        if it.get("status") not in ("CONFIRMED", "PARTIAL", "OPEN"):
            fail("C8", "第 %s 项 status 非法" % it.get("id"))
        for a in it.get("evidence", []):
            if a not in reg:
                fail("C8", "第 %s 项引用不存在的 %s" % (it.get("id"), a))
        for o in it.get("open", []):
            if o not in op:
                fail("C8", "第 %s 项引用未登记的 %s" % (it.get("id"), o))
    rt = read(os.path.join(ROOT, "analysis", "10-runtime-captures.md"))
    if "不存在" not in rt and "OPEN-AP-37" not in rt:
        fail("C8", "运行期章节未如实记录缺抓包")


def c9():
    """有限汇编锚点回归：防止把 Verify M1 套到 Setup；不执行密码学。"""
    source = read(os.path.join(ROOT, "source", "asm", "CoreUtils", "f_18bf24d98.s"))
    insns = {}
    for line in source.splitlines():
        m = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
        if m:
            insns[int(m[1], 16)] = " ".join(m[2].split())
    anchors = {
        0x18bf24f58: "cmp w8, #1",
        0x18bf24f5c: "b.eq #0x18bf25004",
        0x18bf25014: "mov w1, #0",
        0x18bf25018: "bl #0x18bf41da8",
        0x18bf25028: "mov w1, #6",
        0x18bf25034: "bl #0x18bf41b64",
        0x18bf250ac: "mov w8, #2",
        0x18bf24f00: "cmp w8, #3",
        0x18bf24f04: "b.eq #0x18bf24f98",
        0x18bf252c4: "mov w1, #3",
        0x18bf252c8: "bl #0x18bf41b64",
        0x18bf252dc: "mov w1, #4",
        0x18bf252e0: "bl #0x18bf41b64",
        0x18bf26678: "mov w1, #0xa",
        0x18bf2667c: "mov w3, #0x40",
    }
    for addr, expected in anchors.items():
        if insns.get(addr) != expected:
            fail("C9", "Setup 指令锚点不符: %#x" % addr)
    m1_types = [op for addr, op in insns.items()
                if 0x18bf25004 <= addr < 0x18bf25094 and op.startswith("mov w1,")]
    if m1_types != ["mov w1, #0", "mov w1, #6", "mov w1, #0x13", "mov w1, #0x1f"]:
        fail("C9", "Setup M1 字段选择与已核分支不符")


def run_audit(check, script):
    result = subprocess.run([sys.executable, "-B", os.path.join(ROOT, "tools", script)],
                            capture_output=True, text=True, encoding="utf-8", errors="replace")
    if result.returncode:
        fail(check, result.stdout + result.stderr)
    else:
        print(result.stdout.strip())


def c10():
    run_audit("C10", "verify-crypto-audit.py")


def c11():
    run_audit("C11", "verify-type-dispatch.py")


def c12():
    run_audit("C12", "verify-pair-verify.py")


def c13():
    run_audit("C13", "verify-keyholder.py")


def main():
    for fn in (c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13):
        fn()
    if FAILS:
        print("failures: %d" % len(FAILS))
        for c, m in FAILS:
            print("  [%s] %s" % (c, m))
        return 1
    print("OK  C1..C13 全部通过（含有限汇编/结构回归，不是握手互通测试）")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
