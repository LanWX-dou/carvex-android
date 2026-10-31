#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""iap2_input_business_lifecycle 自检。

主体使用标准库；C16原指令复核需要Capstone（已核版本5.0.7）。
在 docset 根目录运行：python3 -B verify.py
退出码 0 表示全部通过，1 表示有 failure。
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
FAILS: list[str] = []
CHECKS: list[tuple[str, str]] = []


def fail(check: str, msg: str) -> None:
    FAILS.append(f"[{check}] {msg}")


def ok(check: str, msg: str) -> None:
    CHECKS.append((check, msg))


def sha256_file(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def read(path: str) -> str:
    with open(path, encoding="utf-8") as fh:
        return fh.read()


def rel(*parts: str) -> str:
    return os.path.join(ROOT, *parts)


BIN = rel("source", "firmware", "accessoryd")
ASM_DIR = rel("source", "asm", "accessoryd")
GH_DIR = rel("readable", "ghidra", "accessoryd")
ANALYSIS = rel("analysis")
SPEC = rel("spec")


def md_files(folder: str) -> list[str]:
    out = []
    if not os.path.isdir(folder):
        return out
    for name in sorted(os.listdir(folder)):
        if name.endswith(".md"):
            out.append(os.path.join(folder, name))
    return out


def main() -> int:
    manifest = json.loads(read(rel("manifest.json"))) if os.path.exists(rel("manifest.json")) else None
    coverage = json.loads(read(rel("coverage.json")))

    # ---------- C1 源二进制 ----------
    if not os.path.exists(BIN):
        fail("C1", "缺少 source/firmware/accessoryd")
        return report()
    src_sha = sha256_file(BIN)
    size = os.path.getsize(BIN)
    if manifest is None:
        fail("C1", "缺少 manifest.json")
    else:
        if manifest.get("source_sha256") != src_sha:
            fail("C1", f"manifest.source_sha256={manifest.get('source_sha256')} 与文件 {src_sha} 不一致")
        elif manifest.get("source_size") != size:
            fail("C1", f"manifest.source_size={manifest.get('source_size')} 与文件 {size} 不一致")
        else:
            ok("C1", f"源二进制哈希与大小一致（{size} B）")

    # ---------- C2 .bin 与源二进制一致 ----------
    with open(BIN, "rb") as fh:
        blob = fh.read()
    idx_path = os.path.join(ASM_DIR, "index.json")
    index = json.loads(read(idx_path)) if os.path.exists(idx_path) else None
    if index is None:
        fail("C2", "缺少 source/asm/accessoryd/index.json")
    else:
        funcs = index["functions"] if isinstance(index, dict) else index
        bad = 0
        for f in funcs:
            addr = int(f.get("addr") or f["address"], 16)
            path = os.path.join(ASM_DIR, f["bin"])
            if not os.path.exists(path):
                fail("C2", f"缺少 {f['bin']}")
                bad += 1
                continue
            data = open(path, "rb").read()
            off = addr - 0x100000000
            if blob[off : off + len(data)] != data:
                fail("C2", f"{f['bin']} 与源二进制区间不一致")
                bad += 1
        if not bad:
            ok("C2", f"{len(funcs)} 个 .bin 与源二进制逐字节一致")

    # ---------- C3 .s 头 ----------
    bad = 0
    for name in sorted(os.listdir(ASM_DIR)) if os.path.isdir(ASM_DIR) else []:
        if not name.endswith(".s"):
            continue
        text = read(os.path.join(ASM_DIR, name))
        head = "\n".join(text.splitlines()[:3])
        if src_sha not in head:
            fail("C3", f"{name} 头部缺少源哈希")
            bad += 1
        elif "未人工确认" not in head:
            fail("C3", f"{name} 头部缺少未人工确认标记")
            bad += 1
        elif not re.search(r"accessoryd 0x[0-9a-f]+-0x[0-9a-f]+", head):
            fail("C3", f"{name} 头部缺少地址区间")
            bad += 1
    if not bad:
        ok("C3", "全部 .s 头部含地址区间、源哈希、未人工确认标记")

    # ---------- C4 反编译文件 ----------
    bad = 0
    count = 0
    for name in sorted(os.listdir(GH_DIR)) if os.path.isdir(GH_DIR) else []:
        if not name.endswith(".json"):
            continue
        count += 1
        meta = json.loads(read(os.path.join(GH_DIR, name)), strict=False)
        if meta.get("source_sha256") != src_sha:
            fail("C4", f"{name} source_sha256 不一致")
            bad += 1
        if meta.get("status") not in {"DECOMPILED_UNREVIEWED", "DECOMPILE_FAILED"}:
            fail("C4", f"{name} 缺少 DECOMPILED_UNREVIEWED/DECOMPILE_FAILED 状态")
            bad += 1
        if meta.get("status") == "DECOMPILE_FAILED" and not meta.get("diagnostic"):
            fail("C4", f"{name} 反编译失败但没有 diagnostic")
            bad += 1
        cpath = os.path.join(GH_DIR, meta.get("c_file", ""))
        if not os.path.exists(cpath):
            fail("C4", f"{name} 指向的 .c 不存在")
            bad += 1
            continue
        ctext = read(cpath)
        if "NOT REVIEWED" not in ctext.splitlines()[0]:
            fail("C4", f"{meta['c_file']} 首行缺少 NOT REVIEWED")
            bad += 1
        if meta.get("c_sha256") != sha256_file(cpath):
            fail("C4", f"{meta['c_file']} 哈希与 json 不符")
            bad += 1
    if not bad and count:
        ok("C4", f"{count} 份反编译均带未人工确认标记且哈希一致")

    # ---------- C5 地址窗口 ----------
    bad = 0
    addr_re = re.compile(r"0x(100[0-9a-f]{6})\b")
    for path in md_files(ANALYSIS) + md_files(SPEC) + [rel("TASK.md")]:
        if not os.path.exists(path):
            continue
        for lineno, line in enumerate(read(path).splitlines(), 1):
            for m in addr_re.finditer(line):
                v = int(m.group(1), 16)
                if not (0x100000000 <= v < 0x100000000 + size):
                    fail("C5", f"{os.path.basename(path)}:{lineno} 地址 {m.group(0)} 超出镜像窗口")
                    bad += 1
    if not bad:
        ok("C5", "文档中引用的镜像地址均在窗口内")

    # ---------- C6/C7 规范条款 ----------
    rule_re = re.compile(r"^`(R-(\d+)\.(\d+)(?:\.(\d+))?)`", re.M)
    rules: dict[str, str] = {}
    dup = 0
    for path in md_files(SPEC):
        text = read(path)
        for m in rule_re.finditer(text):
            rid = m.group(1)
            if rid in rules:
                fail("C6", f"条款编号重复：{rid}（{os.path.basename(rules[rid])} 与 {os.path.basename(path)}）")
                dup += 1
            else:
                rules[rid] = path
    if not dup and rules:
        ok("C6", f"{len(rules)} 条 R 编号唯一")

    # 每条条款段落必须含"依据："
    no_basis = 0
    for path in md_files(SPEC):
        text = read(path)
        lines = text.splitlines()
        cur = None
        buf: list[str] = []
        blocks = []
        for line in lines:
            m = re.match(r"^`(R-\d+\.\d+(?:\.\d+)?)`", line)
            if m:
                if cur:
                    blocks.append((cur, "\n".join(buf)))
                cur = m.group(1)
                buf = [line]
            elif cur:
                buf.append(line)
        if cur:
            blocks.append((cur, "\n".join(buf)))
        for rid, block in blocks:
            if "依据" not in block:
                fail("C7", f"{os.path.basename(path)} 的 {rid} 缺少“依据：”")
                no_basis += 1
    if not no_basis:
        ok("C7", "每条条款都带依据")

    # ---------- C8 依据里的 A 编号必须存在 ----------
    a_text = read(os.path.join(ANALYSIS, "A-conclusions.md"))
    a_ids = set(re.findall(r"`(A\d+\.\d+)`", a_text))
    bad = 0
    for path in md_files(SPEC) + md_files(ANALYSIS):
        for lineno, line in enumerate(read(path).splitlines(), 1):
            if "依据" not in line and "依据：" not in line:
                continue
            for aid in re.findall(r"\bA(\d+\.\d+)\b", line):
                if f"A{aid}" not in a_ids:
                    fail("C8", f"{os.path.basename(path)}:{lineno} 引用未登记的 {('A'+aid)}")
                    bad += 1
    if not bad:
        ok("C8", f"依据中引用的 A 编号均已在 A-conclusions 登记（共 {len(a_ids)} 条）")

    # ---------- C9 OPEN 登记与引用 ----------
    open_spec = read(os.path.join(SPEC, "10-open-items.md"))
    registered = set(re.findall(r"`(OPEN-[A-Z]+-[A-Z0-9]+)`", open_spec))
    referenced: dict[str, set[str]] = {}
    for path in md_files(SPEC) + md_files(ANALYSIS):
        if os.path.basename(path) == "10-open-items.md":
            continue
        for oid in re.findall(r"`(OPEN-[A-Z]+-[A-Z0-9]+)`", read(path)):
            referenced.setdefault(oid, set()).add(os.path.basename(path))
    for oid in registered:
        if oid not in referenced:
            fail("C9", f"{oid} 已登记但正文未引用")
    for oid in referenced:
        if oid not in registered:
            fail("C9", f"{oid} 被引用但未在 spec/10 登记")
    if not any(f.startswith("[C9]") for f in FAILS):
        ok("C9", f"{len(registered)} 个 OPEN 编号登记与引用一致")

    # ---------- C10 coverage ----------
    items = coverage.get("coverage_items", [])
    if len(items) != 12:
        fail("C10", f"coverage_items 应为 12 项，实际 {len(items)}")
    seen_ids = sorted(i["id"] for i in items)
    if seen_ids != list(range(1, 13)):
        fail("C10", f"coverage 编号不连续：{seen_ids}")
    statuses = {"已确认", "部分确认", "OPEN"}
    for it in items:
        if it["status"] not in statuses:
            fail("C10", f"第 {it['id']} 项状态非法：{it['status']}")
        for rid in it.get("rules", []):
            if rid not in rules:
                fail("C10", f"第 {it['id']} 项引用不存在的条款 {rid}")
        for oid in it.get("opens", []):
            if oid not in registered:
                fail("C10", f"第 {it['id']} 项引用未登记的 {oid}")
        for apath in it.get("analysis", []):
            if not os.path.exists(rel(*apath.split("/"))):
                fail("C10", f"第 {it['id']} 项引用不存在的文件 {apath}")
        if it["status"] in {"部分确认", "OPEN"} and not it.get("opens"):
            fail("C10", f"第 {it['id']} 项为 {it['status']} 却没有 OPEN 编号")
    if not any(f.startswith("[C10]") for f in FAILS):
        ok("C10", "coverage 12 项状态/条款/OPEN/证据路径均自洽")

    # ---------- C11 不得声称 ----------
    bad = 0
    for path in md_files(SPEC) + md_files(ANALYSIS) + [rel("TASK.md")]:
        if not os.path.exists(path):
            continue
        for lineno, line in enumerate(read(path).splitlines(), 1):
            if "全部确认" in line and not re.search(r"[不未非无]", line):
                fail("C11", f"{os.path.basename(path)}:{lineno} 出现无否定的“全部确认”")
                bad += 1
    if not bad:
        ok("C11", "未出现无否定的“全部确认”式表述")

    # ---------- C13 编码自测向量 ----------
    import importlib.util

    def load_module(name: str, path: str):
        spec = importlib.util.spec_from_file_location(name, path)
        mod = importlib.util.module_from_spec(spec)
        sys.modules[name] = mod
        spec.loader.exec_module(mod)
        return mod

    codec_path = rel("reference-impl", "input_codec.py")
    vec_path = rel("reference-impl", "test_vectors.json")
    if not (os.path.exists(codec_path) and os.path.exists(vec_path)):
        fail("C13", "缺少 reference-impl/input_codec.py 或 test_vectors.json")
    else:
        codec = load_module("input_codec", codec_path)
        vec = json.loads(read(vec_path))
        facts_text = read(os.path.join(ANALYSIS, "02-handler-facts.md"))
        known = {int(m, 16) for m in re.findall(r"`0x([0-9a-fA-F]{4})`", facts_text)}
        known |= {0x6801, 0x6804, 0x6807, 0x5001, 0x5201, 0x5202, 0x5204, 0x0D00, 0x0D02, 0x5403, 0xA100}
        bad = 0
        for v in vec["vectors"]:
            mid = int(v["msg_id"], 16)
            raw = bytes.fromhex(v["hex"])
            if codec.encode_message(mid, v["params"]) != raw:
                fail("C13", f"{v['name']} 重编码结果与向量不一致")
                bad += 1
            dec = codec.decode_message(raw)
            if dec["msg_id"] != mid or [p["id"] for p in dec["params"]] != [p["id"] for p in v["params"]]:
                fail("C13", f"{v['name']} 解码结果与向量不一致")
                bad += 1
            if mid not in known:
                fail("C13", f"{v['name']} 的消息 ID {v['msg_id']} 未在固件事实里出现")
                bad += 1
        for n in vec["negative"]:
            if codec.wire_len_ok(bytes.fromhex(n["wire"]), n["type"]) != n["expect_ok"]:
                fail("C13", f"负例 {n['name']} 的长度判定与预期不符")
                bad += 1
        if not bad:
            ok("C13", f"{len(vec['vectors'])} 组编码向量 + {len(vec['negative'])} 个负例全部通过")
        try:
            codec._self_test()
        except (AssertionError, ValueError) as exc:
            fail("C13", f"空TLV/整数/类型边界测试失败: {exc}")
        else:
            ok("C13", "空TLV、U32、未知类型、整数越界与父长度负例通过")

    # ---------- C14 状态机与规范一致 ----------
    fsm_path = rel("reference-impl", "lifecycle_fsm.py")
    if not os.path.exists(fsm_path):
        fail("C14", "缺少 reference-impl/lifecycle_fsm.py")
    else:
        fsm = load_module("lifecycle_fsm", fsm_path)
        spec06 = read(os.path.join(SPEC, "06-lifecycle.md"))
        row_re = re.compile(
            r"^\| `(ACTIVE|SUSPENDED|RESUMED|DISCONNECTED|RECONNECTING|NEGOTIATING)` \| `([A-Z_]+)` \| "
            r"`(ACTIVE|SUSPENDED|RESUMED|DISCONNECTED|RECONNECTING|NEGOTIATING)` \|",
            re.M,
        )
        parsed = {(m.group(1), m.group(2)): m.group(3) for m in row_re.finditer(spec06)}
        if not parsed:
            fail("C14", "spec/06 未解析到迁移表")
        elif parsed != fsm.TRANSITIONS:
            only_doc = set(parsed.items()) - set(fsm.TRANSITIONS.items())
            only_code = set(fsm.TRANSITIONS.items()) - set(parsed.items())
            fail("C14", f"规范与实现不一致：仅文档 {sorted(only_doc)} 仅代码 {sorted(only_code)}")
        else:
            ok("C14", f"状态机 {len(parsed)} 条迁移与 spec/06 一致")
        try:
            fsm._self_test()
        except (AssertionError, ValueError) as exc:
            fail("C14", f"状态机行为测试失败: {exc}")
        else:
            ok("C14", "初始/握手/恢复门、READY组合、旧epoch及失败/取消/断开行为通过")

    # ---------- C15 function-index ----------
    fi_path = rel("function-index.json")
    if not os.path.exists(fi_path):
        fail("C15", "缺少 function-index.json")
    else:
        fi = json.loads(read(fi_path))
        if fi.get("source_sha256") != src_sha:
            fail("C15", "function-index.source_sha256 与源二进制不一致")
        n_asm = len(index["functions"]) if index else 0
        if fi.get("count") != n_asm:
            fail("C15", f"function-index 条数 {fi.get('count')} 与汇编索引 {n_asm} 不一致")
        bad = 0
        for e in fi.get("functions", []):
            bin_path = os.path.join(ASM_DIR, e["bin"])
            if not os.path.exists(bin_path):
                fail("C15", f"缺少 {e['bin']}")
                bad += 1
                continue
            if sha256_file(bin_path) != e["raw_sha256"]:
                fail("C15", f"{e['bin']} 哈希与 function-index 不符")
                bad += 1
            if e.get("ghidra_c") and not os.path.exists(os.path.join(GH_DIR, e["ghidra_c"])):
                fail("C15", f"{e['ghidra_c']} 不存在")
                bad += 1
        if not bad:
            ok("C15", f"function-index {fi['count']} 条与汇编/反编译一致")

    # ---------- C16 original-image branch and header audit ----------
    import subprocess
    audit = subprocess.run([sys.executable, "-B", rel("tools", "verify-lifecycle-audit.py")],
                           capture_output=True, text=True, encoding="utf-8", errors="replace")
    if audit.returncode:
        fail("C16", audit.stdout + audit.stderr)
    else:
        ok("C16", audit.stdout.strip())

    hid_audit = subprocess.run([sys.executable, "-B", rel("tools", "verify-hid-audit.py")],
                               capture_output=True, text=True, encoding="utf-8", errors="replace")
    if hid_audit.returncode:
        fail("C17", hid_audit.stdout + hid_audit.stderr)
    else:
        ok("C17", hid_audit.stdout.strip())

    np_audit = subprocess.run([sys.executable, "-B", rel("tools", "verify-nowplaying-audit.py")],
                              capture_output=True, text=True, encoding="utf-8", errors="replace")
    if np_audit.returncode:
        fail("C18", np_audit.stdout + np_audit.stderr)
    else:
        ok("C18", np_audit.stdout.strip())

    # ---------- C12 manifest 覆盖文件 ----------
    if manifest:
        files = manifest.get("files", {})
        missing = 0
        checked = 0
        for relpath, expected in files.items():
            full = rel(*relpath.split("/"))
            if not os.path.exists(full):
                fail("C12", f"manifest 记录的文件不存在：{relpath}")
                missing += 1
                continue
            checked += 1
            if sha256_file(full) != expected:
                fail("C12", f"{relpath} 哈希与 manifest 不符")
                missing += 1
        if not missing:
            ok("C12", f"manifest 记录的 {checked} 个文件哈希一致")

    return report()


def report() -> int:
    for check, msg in CHECKS:
        print(f"  ok {check}: {msg}")
    if FAILS:
        print()
        for f in FAILS:
            print(f"  FAIL {f}")
        print(f"\n{len(FAILS)} failure(s)")
        return 1
    print("\n0 failures")
    return 0


if __name__ == "__main__":
    sys.exit(main())
