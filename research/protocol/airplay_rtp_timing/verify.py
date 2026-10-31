#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""airplay_rtp_timing docset 自校验。

用法： python3 verify.py
退出码： 0 = 无失败； 1 = 有失败。

检查项：
  C1  源二进制身份（大小/哈希）与 manifest、metadata 一致
  C2  每个 .bin 与源二进制对应区间逐字节相同，且与 index.json 的 raw_sha256 一致
  C3  每个 .s 头部含地址区间、源 SHA256、"未人工确认"标记
  C4  文档里出现的十六进制地址都落在段窗口内
  C5  spec 条款编号唯一、每条有 `依据：`、引用的 A/R 编号存在、编号前缀与文件名一致
  C6  跨 docset 引用（<docset>/R-x.y）能在对应 docset 的 spec 中找到
  C7  OPEN 项：spec/08 登记 ↔ 正文引用 ↔ manifest 索引 三者闭环
  C8  12 项覆盖状态在 coverage.json 与 STATUS.md 中一致；summary 数字自洽；无未经否定的"全部确认"类表述
  C9  测试向量可由固件公式重算，且与 spec/01、reference-impl/test_vectors.json 一致；参考实现自检通过
  C10 manifest.json 的文件清单与磁盘一致（无缺失、无多余、无哈希漂移）
  C11 解密长度算术两个分支的 8 例与原 .s 有限指令解释交叉核验
  C12 缓冲提交/读取契约、时钟与整数宽度回归
  C13 Compose双游标与长度出参回归
  C14 音频消息API/两条调用链、AAD参数与接收计数回归
"""
from __future__ import annotations

import hashlib
import json
import os
import re
import sys
import importlib.util
import runpy

ROOT = os.path.dirname(os.path.abspath(__file__))
IMAGE = "AirPlaySender"

failures: list[str] = []
warnings: list[str] = []
checks = 0


def ok(msg: str) -> None:
    global checks
    checks += 1


def fail(msg: str) -> None:
    global checks
    checks += 1
    failures.append(msg)


def warn(msg: str) -> None:
    warnings.append(msg)


def sha256(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def read(path: str) -> str:
    with open(path, encoding="utf-8") as f:
        return f.read()


def md_files(subdir: str) -> list[str]:
    out = []
    base = os.path.join(ROOT, subdir)
    for cur, _dirs, names in os.walk(base):
        for n in names:
            if n.endswith(".md"):
                out.append(os.path.join(cur, n))
    return sorted(out)


# ---------------------------------------------------------------- C1
def check_source() -> None:
    man = json.load(open(os.path.join(ROOT, "manifest.json"), encoding="utf-8"))
    meta = json.load(open(os.path.join(ROOT, "source/metadata", IMAGE, "summary.json"),
                          encoding="utf-8"))
    path = os.path.join(ROOT, "source/firmware", IMAGE)
    if not os.path.exists(path):
        fail("C1 源二进制缺失：source/firmware/" + IMAGE)
        return
    if os.path.getsize(path) != man["source"]["size"]:
        fail(f"C1 大小不一致：磁盘 {os.path.getsize(path)} vs manifest {man['source']['size']}")
    elif sha256(path) != man["source"]["sha256"]:
        fail("C1 源二进制哈希与 manifest 不一致")
    elif man["source"]["sha256"] != meta["sha256"]:
        fail("C1 manifest 源哈希与 metadata 不一致")
    else:
        ok("C1 源二进制身份一致")


# ---------------------------------------------------------------- C2
def check_bin_slices() -> None:
    idx = json.load(open(os.path.join(ROOT, "source/asm", IMAGE, "index.json"),
                         encoding="utf-8"))
    blob = open(os.path.join(ROOT, "source/firmware", IMAGE), "rb").read()
    segs = json.load(open(os.path.join(ROOT, "source/metadata", IMAGE, "segments.json"),
                          encoding="utf-8"))
    text = [s for s in segs if s["segname"] == "__TEXT"][0]
    fileoff_base = text["fileoff"] - text["vmaddr"]
    bad = 0
    for f in idx["functions"]:
        addr = int(f["address"], 16)
        end = int(f["end"], 16)
        off = addr + fileoff_base
        raw = blob[off:off + (end - addr)]
        if hashlib.sha256(raw).hexdigest() != f["raw_sha256"]:
            bad += 1
            fail(f"C2 {f['symbol']} 区间哈希不匹配")
            continue
        binp = os.path.join(ROOT, "source/asm", IMAGE, f["bin"])
        if not os.path.exists(binp):
            bad += 1
            fail(f"C2 缺少 {f['bin']}")
            continue
        if open(binp, "rb").read() != raw:
            bad += 1
            fail(f"C2 {f['bin']} 与固件区间不一致")
    if not bad:
        ok(f"C2 {len(idx['functions'])} 个 .bin 与固件逐字节一致")


# ---------------------------------------------------------------- C3
def check_asm_headers() -> None:
    idx = json.load(open(os.path.join(ROOT, "source/asm", IMAGE, "index.json"),
                         encoding="utf-8"))
    src = json.load(open(os.path.join(ROOT, "source/metadata", IMAGE, "summary.json"),
                         encoding="utf-8"))["sha256"]
    bad = 0
    for f in idx["functions"]:
        p = os.path.join(ROOT, "source/asm", IMAGE, f["asm"])
        if not os.path.exists(p):
            bad += 1
            fail(f"C3 缺少 {f['asm']}")
            continue
        head = "\n".join(read(p).splitlines()[:3])
        if f"{IMAGE} {f['address']}-{f['end']}" not in head:
            bad += 1
            fail(f"C3 {f['asm']} 头部地址区间不符")
        elif src not in head:
            bad += 1
            fail(f"C3 {f['asm']} 头部缺源 SHA256")
        elif "未人工确认" not in read(p).splitlines()[2]:
            bad += 1
            fail(f"C3 {f['asm']} 第 3 行缺未人工确认标记")
    if not bad:
        ok(f"C3 {len(idx['functions'])} 个 .s 头部标记完整")


# ---------------------------------------------------------------- C4
def check_addresses() -> None:
    segs = json.load(open(os.path.join(ROOT, "source/metadata", IMAGE, "segments.json"),
                          encoding="utf-8"))
    ranges = [(s["vmaddr"], s["vmaddr"] + s["vmsize"]) for s in segs]
    support_segments = json.load(open(os.path.join(ROOT, "../airplay_fairplay_crypto/source/metadata/support/segments.json"), encoding="utf-8"))
    ranges += [(s["vmaddr"], s["vmaddr"] + s["vmsize"]) for s in support_segments]
    # 0x258000000-0x258200000 是 dyld 共享缓存的 stub 区：反汇编里 `bl #0x25810xxxx`
    # 指向的导入桩不属本镜像的任何段，属"外部符号"，不参与"文档地址必须在段内"的检查。
    external = [(0x258000000, 0x258200000), (0x228180000, 0x228200000)]
    docs = md_files("analysis") + md_files("spec") + [os.path.join(ROOT, "TASK.md"),
                                                      os.path.join(ROOT, "STATUS.md")]
    addr_re = re.compile(r"\b(0x(?:22|25|26|27)[0-9a-fA-F]{6,})\b")
    bad = 0
    for p in docs:
        if not os.path.exists(p):
            continue
        for m in addr_re.finditer(read(p)):
            v = int(m.group(1), 16)
            if any(lo <= v <= hi for lo, hi in external):
                continue
            if not any(lo <= v <= hi for lo, hi in ranges):
                bad += 1
                fail(f"C4 {os.path.relpath(p, ROOT)} 中地址 {m.group(1)} 不在任何段内")
    if not bad:
        ok("C4 文档地址均落在段窗口内")


# ---------------------------------------------------------------- C5
RULE_RE = re.compile(r"^##\s+(R-\d+\.\d+)\b", re.M)
AID_RE = re.compile(r"\bA(\d\d)\.(\d+)\b")
RID_RE = re.compile(r"\bR-(\d+)\.(\d+)\b")


def check_rules() -> None:
    spec_files = md_files("spec")
    a_text = read(os.path.join(ROOT, "analysis", "A-conclusions.md"))
    a_ids = {f"A{m.group(1)}.{m.group(2)}" for m in AID_RE.finditer(a_text)}

    defined: dict[str, str] = {}
    for p in spec_files:
        rel = os.path.relpath(p, ROOT).replace("\\", "/")
        text = read(p)
        blocks = list(RULE_RE.finditer(text))
        for i, m in enumerate(blocks):
            rid = m.group(1)
            if rid in defined:
                fail(f"C5 条款编号重复：{rid}（{defined[rid]} 与 {rel}）")
                continue
            defined[rid] = rel
            if int(rid.split("-")[1].split(".")[0]) != int(os.path.basename(p)[:2]):
                fail(f"C5 {rel}: 条款 {rid} 前缀与文件名不符")
            end = blocks[i + 1].start() if i + 1 < len(blocks) else len(text)
            body = text[m.end():end]
            dep = re.search(r"\*\*依据：\*\*(.+)", body)
            if not dep:
                fail(f"C5 {rel}: {rid} 缺 `依据：` 行")
                continue
            cited_a = {f"A{x.group(1)}.{x.group(2)}" for x in AID_RE.finditer(dep.group(1))}
            if not cited_a:
                fail(f"C5 {rel}: {rid} 的 `依据：` 未引用任何 A 编号")
            missing_a = sorted(a for a in cited_a if a not in a_ids)
            if missing_a:
                fail(f"C5 {rel}: {rid} 引用了不存在的 A 编号 {missing_a}")
    # 跨条款引用必须已定义
    for p in spec_files + md_files("analysis"):
        rel = os.path.relpath(p, ROOT).replace("\\", "/")
        text = read(p)
        for m in re.finditer(r"`?(R-\d+\.\d+)`?", text):
            rid = m.group(1)
            if m.start() > 0 and text[m.start() - 1] == "/":
                continue  # 跨 docset 引用（<docset>/R-x.y），由 C6 处理
            if rid not in defined:
                warn(f"C5 {rel} 引用了不存在（或尚未产出）的条款 {rid}")
    ok(f"C5 条款 {len(defined)} 条，编号唯一且带依据")


# ---------------------------------------------------------------- C6
DOCTYPE_RE = re.compile(r"\b([a-z0-9_]+)/R-(\d+\.\d+)\b")


def check_cross_docset() -> None:
    own = os.path.basename(ROOT)
    docs_root = os.path.dirname(ROOT)
    seen = 0
    for p in md_files("analysis") + md_files("spec") + [os.path.join(ROOT, "TASK.md")]:
        if not os.path.exists(p):
            continue
        for m in DOCTYPE_RE.finditer(read(p)):
            ds, rid = m.group(1), m.group(2)
            if ds == own:
                continue
            seen += 1
            spec_dir = os.path.join(docs_root, ds, "spec")
            if not os.path.isdir(spec_dir):
                fail(f"C6 跨 docset 引用指向不存在的 docset：{ds}/R-{rid}")
                continue
            target_specs = []
            for cur, _d, names in os.walk(spec_dir):
                target_specs.extend(os.path.join(cur, n) for n in names if n.endswith(".md"))
            hit = any(re.search(rf"\bR-{re.escape(rid)}\b", read(q)) for q in target_specs)
            if not hit:
                fail(f"C6 跨 docset 引用无法解析：{ds}/R-{rid}")
    ok(f"C6 跨 docset 引用 {seen} 处可解析")


# ---------------------------------------------------------------- C7
OPEN_RE = re.compile(r"`(OPEN-[A-Z]+-\d+)`")


def check_open_items() -> None:
    reg_path = os.path.join(ROOT, "spec", "08-open-items.md")
    reg_text = read(reg_path)
    registered = set()
    for line in reg_text.splitlines():
        m = re.match(r"\|\s*`(OPEN-[A-Z]+-\d+)`", line)
        if m:
            registered.add(m.group(1))

    man = json.load(open(os.path.join(ROOT, "manifest.json"), encoding="utf-8"))
    closed = set(re.findall(r"^\|\s*`(OPEN-[A-Z]+-\d+)`\s*\|\s*CLOSED\s*\|", reg_text, re.M))
    indexed = set(man["open_items"]) | set(man.get("closed_items", {}))
    if closed != set(man.get("closed_items", {})) or closed & set(man["open_items"]):
        fail("C7 已关闭项目与未决项目未正确分离")
    if man["open_item_count"] != len(man["open_items"]) or man.get("closed_item_count", 0) != len(closed):
        fail("C7 未决/关闭计数错误")

    if registered != indexed:
        fail(f"C7 登记与 manifest 索引不一致：仅登记 {sorted(registered - indexed)}，"
             f"仅索引 {sorted(indexed - registered)}")
    else:
        ok(f"C7 {len(registered) - len(closed)} 个未决、{len(closed)} 个关闭项登记与索引一致")

    # 每个登记项必须在正文（非 08 文件）至少被引用一次
    others = [p for p in md_files("analysis") + md_files("spec")
              if not p.endswith("08-open-items.md")]
    other_text = "\n".join(read(p) for p in others)
    orphan = sorted(o for o in registered if o not in other_text)
    if orphan:
        fail(f"C7 OPEN 项已登记但正文未引用：{orphan}")
    else:
        ok("C7 每个 OPEN 项都在正文被引用")


# ---------------------------------------------------------------- C8
def check_coverage() -> None:
    cov = json.load(open(os.path.join(ROOT, "source/metadata/coverage.json"),
                         encoding="utf-8"))
    items = cov["items"]
    if len(items) != 12:
        fail(f"C8 覆盖项应为 12，实际 {len(items)}")
    status = {i["id"]: i["status"] for i in items}
    if set(status.values()) - {"已确认", "部分确认", "OPEN"}:
        fail("C8 存在非法状态值")

    summary = cov["summary"]
    partial = sum(1 for i in items if i["status"] == "部分确认")
    opens = sum(1 for i in items if i["status"] == "OPEN")
    confirmed = sum(1 for i in items if i["status"] == "已确认")
    if (summary["partial"], summary["open"], summary["confirmed"]) != (partial, opens, confirmed):
        fail(f"C8 coverage.json summary 与条目不一致：{summary}")

    status_md = read(os.path.join(ROOT, "STATUS.md"))
    rows = dict(re.findall(r"^\|\s*(RT-\d+)\s*\|[^|]*\|\s*([^|]+?)\s*\|", status_md, re.M))
    if not rows:
        fail("C8 STATUS.md 缺覆盖状态表")
    else:
        for rid, st in status.items():
            if rid not in rows:
                fail(f"C8 STATUS.md 缺 {rid}")
            elif rows[rid] != st:
                fail(f"C8 {rid} 状态不一致：coverage={st} STATUS={rows[rid]}")

    banned = re.compile(r"(全部确认|全部闭合|已完成|全部验证)")
    for p in md_files("analysis") + md_files("spec") + [os.path.join(ROOT, "STATUS.md")]:
        if not os.path.exists(p):
            continue
        for line in read(p).splitlines():
            if banned.search(line) and not re.search(r"[不未非无禁止没法]", line):
                fail(f"C8 {os.path.relpath(p, ROOT)} 出现未加限定的绝对化表述：{line.strip()[:60]}")
    ok("C8 覆盖状态与 summary/STATUS 一致")


# ---------------------------------------------------------------- C9
def _load_parser():
    path = os.path.join(ROOT, "reference-impl", "rtp_parser.py")
    spec = importlib.util.spec_from_file_location("rtp_parser_ref", path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules["rtp_parser_ref"] = mod
    spec.loader.exec_module(mod)  # type: ignore[union-attr]
    return mod


def check_vectors() -> None:
    mod = _load_parser()
    try:
        mod.self_test()
    except AssertionError as exc:
        fail(f"C9 reference-impl 自检失败：{exc}")
        return

    vec = json.load(open(os.path.join(ROOT, "reference-impl/test_vectors.json"),
                         encoding="utf-8"))
    for row in vec["element_pack"]:
        got = mod.pack_element(row["b7"], row["d14"], row["l10"]).hex().upper()
        if got != row["wire"]:
            fail(f"C9 向量打包不一致 {row}")
        if mod.unpack_element_internal(bytes.fromhex(row["wire"])) != row["internal"]:
            fail(f"C9 内部次序不一致 {row}")
    for k, v in vec["pt_remap"].items():
        if mod.remap_pt_for_merged(int(k, 16)) != int(v, 16):
            fail(f"C9 PT 改写不一致 {k}->{v}")
    for row in vec["header_len"]:
        if mod.header_length(row["elements"], row["merged"]) != row["expected"]:
            fail(f"C9 头长公式不一致 {row}")
    for row in vec["gate"]:
        if mod.has_extended_header(row["pt"], row["merged"]) != row["expect"]:
            fail(f"C9 元素区门不一致 {row}")

    # spec/01 的向量表必须与重算一致
    spec01 = read(os.path.join(ROOT, "spec", "01-rtp-format.md"))
    rows = re.findall(r"\|\s*`0x([0-9A-F]{2})`\s*\|\s*`0x([0-9A-F]+)`\s*\|\s*`0x([0-9A-F]+)`"
                      r"\s*\|\s*`([0-9A-F ]+)`\s*\|", spec01)
    if len(rows) < 4:
        fail("C9 spec/01 向量表行数不足")
    for b7, d14, l10, wire in rows:
        got = mod.pack_element(int(b7, 16), int(d14, 16), int(l10, 16)).hex().upper()
        want = wire.replace(" ", "")
        if got != want:
            fail(f"C9 spec/01 向量错误：B7={b7} D14={d14} L10={l10} 期望 {want} 实算 {got}")
    ok(f"C9 向量 {len(vec['element_pack'])} 组与 spec/01 一致")


def check_decrypt_arithmetic() -> None:
    """解释原 .s 的两个小型算术块，独立核对参考公式；不执行密码库。"""
    asm = read(os.path.join(ROOT, "source/asm/AirPlaySender/f_2519c0934.s"))
    insns = {}
    for line in asm.splitlines():
        m = re.match(r"(0x[0-9a-f]+):\s*(\w+)\s+(.*)", line)
        if m:
            insns[int(m[1], 16)] = (m[2], m[3])
    model = _load_parser()
    for count in (1, 2, 3, 16):
        for start, pt in ((0x2519c09a0, 0x61), (0x2519c09d0, 0x64)):
            base, obj, end = 0x10000, 0x20000, 200
            regs = {"8": base, "19": obj}
            memory = {obj + 0x678: count, base + 0x5c0: end}
            pc = start
            for _ in range(12):
                if pc == 0x2519c09dc:
                    break
                op, operands = insns[pc]
                if op == "b":
                    pc = int(operands.removeprefix("#"), 16)
                    continue
                if op == "ldr":
                    m = re.fullmatch(r"([wx]\d+), \[x(\d+), #(0x[0-9a-f]+)\]", operands)
                    assert m is not None, operands
                    dst, src, imm = m.groups()
                    value = memory[regs[src] + int(imm, 0)]
                else:
                    dst, left, right = operands.split(", ")
                    a = regs[left[1:]]
                    b = int(right[1:], 0) if right.startswith("#") else regs[right[1:]]
                    assert op in ("add", "sub", "lsl"), op
                    value = a + b if op == "add" else a - b if op == "sub" else a << b
                regs[dst[1:]] = value & ((1 << (32 if dst[0] == "w" else 64)) - 1)
                pc += 4
            assert pc == 0x2519c09dc, "算术块未到达共用尾部"
            observed = (regs["22"] - base, regs["21"])
            assert observed == model.observed_decrypt_span(end, pt, False, count), observed
            assert sum(observed) == end
    ok("C11 解密算术两分支 8 例与原 .s 一致（不含库/整函数执行）")


# ---------------------------------------------------------------- C10
def check_manifest() -> None:
    man = json.load(open(os.path.join(ROOT, "manifest.json"), encoding="utf-8"))
    listed = {f["path"]: f for f in man["files"]}
    on_disk = set()
    for cur, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".git") and d != "__pycache__"]
        for n in names:
            rel = os.path.relpath(os.path.join(cur, n), ROOT).replace("\\", "/")
            if rel != "manifest.json":
                on_disk.add(rel)
    missing = sorted(on_disk - set(listed))
    extra = sorted(set(listed) - on_disk)
    if missing:
        fail(f"C10 manifest 缺文件：{missing[:5]}")
    if extra:
        fail(f"C10 manifest 多余条目：{extra[:5]}")
    drift = [p for p in sorted(on_disk & set(listed))
             if sha256(os.path.join(ROOT, p)) != listed[p]["sha256"]]
    if drift:
        fail(f"C10 文件哈希漂移：{drift[:5]}")
    if not (missing or extra or drift):
        ok(f"C10 manifest 覆盖 {len(listed)} 个文件且哈希一致")


def check_buffer_contract() -> None:
    script = os.path.join(ROOT, "reference-impl", "verify_buffer_contract.py")
    result = runpy.run_path(script)["check"]()
    ok("C12 " + result)


def check_compose_layout() -> None:
    script = os.path.join(ROOT, "reference-impl", "verify_compose_layout.py")
    ok("C13 " + runpy.run_path(script)["check"]())


def check_audio_message() -> None:
    script = os.path.join(ROOT, "reference-impl", "verify_audio_message.py")
    ok("C14 " + runpy.run_path(script)["check"]())


def main() -> int:
    for fn in (check_source, check_bin_slices, check_asm_headers, check_addresses,
               check_rules, check_cross_docset, check_open_items, check_coverage,
               check_vectors, check_decrypt_arithmetic, check_buffer_contract, check_compose_layout,
               check_audio_message, check_manifest):
        try:
            fn()
        except Exception as exc:  # noqa: BLE001 - 校验器自身错误也要算失败
            fail(f"{fn.__name__} 抛异常：{exc!r}")

    print(f"checks: {checks}  failures: {len(failures)}  warnings: {len(warnings)}")
    for w in warnings[:10]:
        print("WARN", w)
    if len(warnings) > 10:
        print(f"WARN … 另有 {len(warnings) - 10} 条")
    for f in failures:
        print("FAIL", f)
    return 0 if not failures else 1


if __name__ == "__main__":
    sys.exit(main())
