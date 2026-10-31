#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""verify.py — airplay_mdns_discovery docset 自校验（8 类）。

用法：
    cd D:\\carvex-research\\research\\protocol\\airplay_mdns_discovery && python3 verify.py
    python3 verify.py --update      # 重写 manifest.json
    python3 verify.py --quiet

检查：
    C1 manifest        清单与实际文件一致（无缺失/多余/改动）
    C2 source          主镜像 SHA256/大小与 summary.json 一致
    C3 analysis        analysis/*.md 齐全；A 编号唯一；状态/证据/位置三列齐全
    C4 spec            条款编号唯一；每条有“依据：”；依据里的 A 编号存在
    C5 open-registry   正文 OPEN 编号 = spec/08 登记 = coverage 引用
    C6 vectors         参考实现跑通全部测试向量，且向量标注为合成
    C7 coverage        12 个覆盖项状态/引用/汇总自洽
    C8 claims          禁用词、STATUS 的诚实声明、清单计数
    C9 runtime         captures 元数据齐全（没有抓包时不算失败）+ pcap 导出回放 + replay 自测
    C10 tables         字段表 / 能力位表 / 地址选择用例（任务书判据 3）
"""
import hashlib
import json
import os
import re
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(ROOT)))
QUIET = "--quiet" in sys.argv
UPDATE = "--update" in sys.argv

FAILS = []
WARNS = []

ANALYSIS_FILES = [
    "analysis/00-method-and-environment.md",
    "analysis/01-mdns-transport-and-announce.md",
    "analysis/02-dns-message-format.md",
    "analysis/03-txt-and-features.md",
    "analysis/09-runtime-captures.md",
    "analysis/A-conclusions.md",
]

STATUS_VALUES = {"CONFIRMED", "CONFIRMED（否定）", "CONFIRMED（自测）", "INFERRED", "OPEN"}
COVERAGE_STATUS = {"已确认", "部分确认", "未开始", "OPEN"}


def fail(check, msg):
    FAILS.append((check, msg))


def warn(check, msg):
    WARNS.append((check, msg))


def rel(*parts):
    return os.path.join(ROOT, *parts)


def read(path):
    with open(path, "rb") as fh:
        return fh.read().decode("utf-8", "replace")


def text_files():
    out = []
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".") and d != "__pycache__"]
        for n in sorted(names):
            p = os.path.join(base, n)
            out.append(os.path.relpath(p, ROOT).replace("\\", "/"))
    return sorted(out)


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


# ---------------------------------------------------------------- C1


def build_manifest():
    cov = json.load(open(rel("source/metadata/coverage.json"), encoding="utf-8"))
    summary = json.load(open(rel("source/metadata/summary.json"), encoding="utf-8"))
    files = []
    for r in text_files():
        if r == "manifest.json":
            continue
        files.append({"path": r, "size": os.path.getsize(rel(r)), "sha256": sha256(rel(r))})
    opens = {}
    for item in files:
        if item["path"].endswith(".md"):
            for m in re.finditer(r"`(OPEN-MDNS-\d+)`", read(rel(item["path"]))):
                opens.setdefault(m.group(1), item["path"])
    man = {
        "docset": os.path.basename(ROOT),
        "build": summary["build"],
        "device": summary["device"],
        "source": summary["primary_binary"],
        "counts": {
            "files": len(files),
            "analysis_docs": sum(1 for f in files if f["path"].startswith("analysis/")),
            "spec_docs": sum(1 for f in files if f["path"].startswith("spec/")),
            "md_files": sum(1 for f in files if f["path"].endswith(".md")),
        },
        "coverage": cov["items"],
        "coverage_summary": {
            k: sum(1 for i in cov["items"] if i["status"] == k)
            for k in ("已确认", "部分确认", "未开始", "OPEN")
        },
        "open_items": opens,
        "open_item_count": len(opens),
        "files": files,
    }
    with open(rel("manifest.json"), "w", encoding="utf-8", newline="\n") as fh:
        json.dump(man, fh, indent=1, ensure_ascii=False)
        fh.write("\n")
    return man


def check_manifest():
    if UPDATE or not os.path.exists(rel("manifest.json")):
        man = build_manifest()
        if not QUIET:
            print(f"[C1] manifest rebuilt: {len(man['files'])} files")
        return man
    man = json.load(open(rel("manifest.json"), encoding="utf-8"))
    actual = {r for r in text_files() if r != "manifest.json"}
    listed = {f["path"] for f in man["files"]}
    for missing in sorted(actual - listed):
        fail("C1", f"manifest 缺文件: {missing}")
    for extra in sorted(listed - actual):
        fail("C1", f"manifest 多文件: {extra}")
    for f in man["files"]:
        if f["path"] in actual:
            p = rel(f["path"])
            if os.path.getsize(p) != f["size"]:
                fail("C1", f"大小不符: {f['path']}")
            elif sha256(p) != f["sha256"]:
                fail("C1", f"哈希不符: {f['path']}")
    return man


# ---------------------------------------------------------------- C2


def check_source():
    summary = json.load(open(rel("source/metadata/summary.json"), encoding="utf-8"))
    pb = summary["primary_binary"]
    path = os.path.join(REPO, pb["path"].replace("/", os.sep))
    if not os.path.exists(path):
        warn("C2", f"主镜像不在工作区，跳过哈希校验: {pb['path']}")
        return summary
    if os.path.getsize(path) != pb["size"]:
        fail("C2", f"主镜像大小不符: {os.path.getsize(path)} != {pb['size']}")
    got = sha256(path)
    if got != pb["sha256"]:
        fail("C2", f"主镜像 SHA256 不符: {got}")
    return summary


# ---------------------------------------------------------------- C3


def parse_conclusions():
    text = read(rel("analysis/A-conclusions.md"))
    rows = {}
    for line in text.splitlines():
        if not line.startswith("| A"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 5:
            fail("C3", f"A 表列数不足: {line[:60]}")
            continue
        aid, conclusion, status, evidence, location = cells[0], cells[1], cells[2], cells[3], cells[4]
        if not re.fullmatch(r"A\d\d\.\d+", aid):
            fail("C3", f"A 编号格式不对: {aid}")
            continue
        if aid in rows:
            fail("C3", f"A 编号重复: {aid}")
        if status not in STATUS_VALUES:
            fail("C3", f"{aid} 状态不在允许集合: {status}")
        if not evidence:
            fail("C3", f"{aid} 缺证据列")
        if not location:
            fail("C3", f"{aid} 缺位置列")
        rows[aid] = {"status": status, "evidence": evidence, "location": location}
    return rows


def check_analysis(conclusions):
    for f in ANALYSIS_FILES:
        if not os.path.exists(rel(f)):
            fail("C3", f"缺文件: {f}")
    if not conclusions:
        fail("C3", "A-conclusions 没有解析到任何结论")
    # 位置列里的路径必须存在（只检查看起来像路径的片段）
    for aid, row in conclusions.items():
        for m in re.finditer(r"`([\w./-]+\.(?:md|py|json|java|log))`", row["location"]):
            frag = m.group(1)
            if frag.startswith(("firmware/", "research/protocol/", "analysis/", "spec/", "reference-impl/", "source/", "runtime/")):
                cand = os.path.join(REPO, frag) if frag.startswith("firmware/") else rel(frag)
                if not os.path.exists(cand) and not os.path.exists(rel(frag)):
                    fail("C3", f"{aid} 位置指向不存在的文件: {frag}")


# ---------------------------------------------------------------- C4


def check_spec(conclusions):
    rules = {}
    for name in sorted(os.listdir(rel("spec"))):
        if not name.endswith(".md"):
            continue
        path = rel("spec", name)
        lines = read(path).splitlines()
        for i, line in enumerate(lines):
            m = re.match(r"^- \*\*(R-\d+\.\d+)\*\*", line)
            if not m:
                continue
            rid = m.group(1)
            if rid in rules:
                fail("C4", f"条款编号重复: {rid}（{rules[rid]} 与 {name}）")
            rules[rid] = name
            basis = lines[i + 1].strip() if i + 1 < len(lines) else ""
            if not basis.startswith("依据："):
                fail("C4", f"{rid} 缺“依据：”行")
                continue
            cites = re.findall(r"A\d\d\.\d+", basis)
            if not cites and not re.search(r"RFC|OPEN-MDNS|建议", basis):
                fail("C4", f"{rid} 依据既无 A 编号也无 RFC/OPEN: {basis[:60]}")
            for c in cites:
                if c not in conclusions:
                    fail("C4", f"{rid} 引用了不存在的 {c}")
    if not rules:
        fail("C4", "没有解析到任何条款")
    return rules


# ---------------------------------------------------------------- C5


def parse_open_registry():
    text = read(rel("spec/08-open-items.md"))
    reg = {}
    for line in text.splitlines():
        m = re.match(r"^\|\s*`(OPEN-MDNS-\d+)`\s*\|", line)
        if m:
            cells = [c.strip() for c in line.strip().strip("|").split("|")]
            status = cells[-1] if cells else "OPEN"
            reg[m.group(1)] = status
    return reg


def check_open(reg, cov):
    used = {}
    for f in text_files():
        if f.endswith(".md") and f != "spec/08-open-items.md":
            for m in re.finditer(r"`(OPEN-MDNS-\d+)`", read(rel(f))):
                used.setdefault(m.group(1), f)
    for oid, where in used.items():
        if oid not in reg:
            fail("C5", f"{where} 用了未登记的 {oid}")
    for oid, status in reg.items():
        if status == "CLOSED":
            continue
        if oid not in used:
            fail("C5", f"{oid} 已登记但正文没有引用")
        if not any(oid in item["open"] for item in cov["items"]):
            fail("C5", f"{oid} 没有被任何覆盖项引用")
    # 覆盖项里引用的 OPEN 必须存在
    for item in cov["items"]:
        for oid in item["open"]:
            if oid not in reg:
                fail("C5", f"{item['id']} 引用了未登记的 {oid}")
    return used


# ---------------------------------------------------------------- C6


def check_vectors():
    vec = rel("reference-impl/test_vectors.json")
    if not os.path.exists(vec):
        fail("C6", "缺 test_vectors.json")
        return
    doc = json.load(open(vec, encoding="utf-8"))
    if "合成" not in doc.get("note", ""):
        fail("C6", "test_vectors.json 没有标注“合成”，可能被误当抓包")
    if len(doc.get("vectors", [])) < 8:
        fail("C6", f"向量数量不足: {len(doc.get('vectors', []))}")
    proc = subprocess.run(
        [sys.executable, rel("reference-impl/mdns_discovery.py"), "--vectors", vec],
        capture_output=True, text=True, encoding="utf-8",
    )
    if proc.returncode != 0:
        fail("C6", "参考实现向量失败：" + (proc.stdout or proc.stderr).strip().splitlines()[-1])
    else:
        tail = proc.stdout.strip().splitlines()[-1] if proc.stdout.strip() else ""
        if "0 failures" not in tail:
            fail("C6", f"向量汇总异常: {tail}")
        if not QUIET:
            print(f"[C6] {tail}")


# ---------------------------------------------------------------- C7


def check_coverage(cov):
    items = cov["items"]
    if len(items) != 12:
        fail("C7", f"覆盖项不是 12 个: {len(items)}")
    ids = [i["id"] for i in items]
    if ids != [f"CS-{n:02d}" for n in range(1, 13)]:
        fail("C7", f"覆盖项编号不连续: {ids}")
    counts = {}
    for item in items:
        if item["status"] not in COVERAGE_STATUS:
            fail("C7", f"{item['id']} 状态非法: {item['status']}")
        counts[item["status"]] = counts.get(item["status"], 0) + 1
        for ref in item["spec"]:
            if not os.path.exists(rel(ref)) and not os.path.exists(os.path.join(REPO, ref)):
                fail("C7", f"{item['id']} 引用不存在的文件: {ref}")
        if not item.get("notes"):
            fail("C7", f"{item['id']} 缺 notes")
    want = {
        "已确认": counts.get("已确认", 0),
        "部分确认": counts.get("部分确认", 0),
        "未开始": counts.get("未开始", 0),
        "OPEN": counts.get("OPEN", 0),
    }
    if cov["summary"] != {"total": 12, **want}:
        fail("C7", f"summary 与实际不一致: {cov['summary']} vs {{'total':12,...{want}}}")


# ---------------------------------------------------------------- C9

CAPTURE_FIELDS = ("file", "sha256", "interface", "captured_at", "capture_point",
                  "head_unit", "phone", "scenarios")


def check_runtime():
    cap_dir = rel("runtime/captures")
    pcaps = sorted(p for p in os.listdir(cap_dir) if p.endswith((".pcap", ".pcapng"))) \
        if os.path.isdir(cap_dir) else []
    if not pcaps:
        if not QUIET:
            print("[C9] captures: 0 份（符合预期：OPEN-MDNS-7）")
    for name in pcaps:
        meta_path = rel("runtime/captures", os.path.splitext(name)[0] + ".json")
        if not os.path.exists(meta_path):
            fail("C9", f"{name} 缺同名 json 元数据")
            continue
        try:
            meta = json.load(open(meta_path, encoding="utf-8"))
        except json.JSONDecodeError as exc:
            fail("C9", f"{name}.json 不是合法 JSON: {exc}")
            continue
        for field in CAPTURE_FIELDS:
            if field not in meta:
                fail("C9", f"{name}.json 缺字段 {field}")
        if meta.get("sha256") and sha256(rel("runtime/captures", name)) != meta["sha256"]:
            fail("C9", f"{name} 的 SHA256 与元数据不一致")
        if not meta.get("scenarios"):
            fail("C9", f"{name}.json 的 scenarios 为空")
        # 有 pcap 就必须能从它重放出服务图（任务书 §6 要求）
        packets = rel("runtime/captures", os.path.splitext(name)[0] + ".packets.json")
        if not os.path.exists(packets):
            fail("C9", f"{name} 缺导出文件 {os.path.basename(packets)}（先用 replay.py --from-tsv 导出）")
            continue
        proc = subprocess.run(
            [sys.executable, rel("runtime/replay/replay.py"), "--packets", packets, "--json"],
            capture_output=True, text=True, encoding="utf-8",
        )
        if proc.returncode != 0:
            fail("C9", f"{name} 回放失败：" + (proc.stdout or proc.stderr).strip().splitlines()[-1])
        else:
            out = json.loads(proc.stdout)
            if not out.get("candidates"):
                fail("C9", f"{name} 回放没有产出候选（服务图为空）")
            elif not QUIET:
                print(f"[C9] {name}: 候选 {len(out['candidates'])} 条")
    proc = subprocess.run(
        [sys.executable, rel("runtime/replay/replay.py"), "--self-test"],
        capture_output=True, text=True, encoding="utf-8",
    )
    if proc.returncode != 0:
        fail("C9", "replay 自测失败：" + (proc.stdout or proc.stderr).strip().splitlines()[-1])
    elif not QUIET:
        print("[C9] " + proc.stdout.strip().splitlines()[-1])


# ---------------------------------------------------------------- C10

def check_tables():
    """字段表 / 能力位表 / 地址选择用例：任务书判据 3 的机器可读部分。"""
    key_path = rel("reference-impl/metadata/txt-keys.json")
    bit_path = rel("reference-impl/metadata/features-bits.json")
    if not os.path.exists(key_path) or not os.path.exists(bit_path):
        fail("C10", "缺 reference-impl/metadata/{txt-keys,features-bits}.json")
        return
    keys = json.load(open(key_path, encoding="utf-8"))
    bits = json.load(open(bit_path, encoding="utf-8"))
    analysis03 = read(rel("analysis/03-txt-and-features.md"))

    names = [k["key"] for k in keys["keys"]]
    if len(names) < 20:
        fail("C10", f"字段表只有 {len(names)} 个键，少于 20")
    if len(set(names)) != len(names):
        fail("C10", "字段表有重复键")
    for k in keys["keys"]:
        if not re.fullmatch(r"0x[0-9a-f]{6,}", str(k.get("addr", ""))):
            fail("C10", f"字段 {k['key']} 的 addr 非法: {k.get('addr')}")
        if k["key"] not in analysis03:
            fail("C10", f"字段表里的 {k['key']} 在 analysis/03 未出现（表与文档不一致）")
        role = k.get("role")
        if role in ("read", "both") and not k.get("reader"):
            fail("C10", f"{k['key']} 声称有读方但没有 reader")
        if role in ("write", "both") and not k.get("writer"):
            fail("C10", f"{k['key']} 声称有写方但没有 writer")
        if role not in ("read", "write", "both", "unknown"):
            fail("C10", f"{k['key']} 的 role 非法: {role}")
    if not keys.get("absent_note"):
        fail("C10", "字段表缺 absent_note（任务书列出的候选键缺失说明）")

    idx = sorted(b["index"] for b in bits["bits"])
    if idx != [55, 56]:
        fail("C10", f"能力位表应只登记 55/56，实际 {idx}")
    if bits.get("order") != "unknown":
        fail("C10", "能力位表的位序必须标 unknown（OPEN-MDNS-11）")
    for b in bits["bits"]:
        if not re.search(r"0x[0-9a-f]{8,}", b.get("evidence", "")):
            fail("C10", f"位 {b['index']} 的 evidence 没有指令地址")
        if "OPEN" not in b.get("status", ""):
            fail("C10", f"位 {b['index']} 的 status 必须标 OPEN")
        if b.get("meaning") is not None:
            fail("C10", f"位 {b['index']} 不得写含义（无行为证据）")

    # 地址选择用例：直接跑参考实现，断言排序/可用性
    sys.path.insert(0, rel("reference-impl"))
    import mdns_discovery as md  # noqa: PLC0415
    response = bytes.fromhex("000084000000000000000000")
    query = bytes(12)
    if md.parse_datagram(response, source_port=5354) is not None:
        fail("C10", "mDNS 响应源端口非 5353 必须静默忽略")
    if md.parse_datagram(response, source_port=5353) is None or md.parse_datagram(query, source_port=53000) is None:
        fail("C10", "合法响应和 legacy 查询不应被源端口门混淆")
    # 独立原始字节反例，不由同一个编码器生成预期数据。
    raw_txt = bytes.fromhex("04666c616705666c61673d074b45593d6f6e65076b65793d74776f00")
    pairs = md.decode_txt(raw_txt)
    if pairs != [("flag", None), ("flag", b""), ("KEY", b"one"), ("key", b"two")]:
        fail("C10", "TXT 必须区分无值/空值并保留原始重复项")
    if md.effective_txt(pairs) != {"flag": None, "key": b"one"}:
        fail("C10", "TXT 业务键必须 ASCII 不区分大小写且 first-wins")
    if md.encode_txt([("flag", None), ("empty", "")]) != b"\x04flag\x06empty=":
        fail("C10", "TXT 编码不得混同 key-only 和空值")
    if md.encode_txt([]) != b"\x00" or md.decode_txt(b"\x00") != [] or md.decode_txt(b"") != []:
        fail("C10", "空 TXT 编码/兼容解析错误")
    if md.effective_txt([("", b"x"), ("\udcff", b"x"), ("ok", b"\xff")]) != {"ok": b"\xff"}:
        fail("C10", "非法 TXT 键不应生效，二进制值必须保留")
    doc = json.load(open(rel("reference-impl/test_vectors.json"), encoding="utf-8"))
    by_name = {v["name"]: v for v in doc["vectors"]}
    ll = md.run_vector(by_name["ipv6-linklocal-only"])
    if not ll["ranked"] or ll["ranked"][0]["usable"]:
        fail("C10", "IPv6 link-local 缺 scope 时必须不可用（R-5.5）")
    else:
        scoped = md.rank_candidates(ll["flat"], interface="test-interface")
        if not scoped[0]["usable"] or scoped[0].get("preferred_scope") != "test-interface":
            fail("C10", "IPv6 link-local 必须保留调用方提供的实际接口")
        if not scoped[0].get("preferred_address", "").startswith("fe80"):
            fail("C10", "IPv6 link-local 的地址字节改变")
        zero_port = dict(ll["flat"][0], srv=dict(ll["flat"][0]["srv"], port=0))
        if md.rank_candidates([zero_port], interface="test-interface")[0]["usable"]:
            fail("C10", "端口 0 必须不可用（R-5.3）")
    multi = md.run_vector(by_name["multi-instance-one-unresolvable"])
    usable = [r for r in multi["ranked"] if r["usable"]]
    unusable = [r for r in multi["ranked"] if not r["usable"]]
    if len(usable) != 1 or len(unusable) != 1:
        fail("C10", f"多实例用例：应 1 可用 1 不可用，实际 {len(usable)}/{len(unusable)}")
    if not all(r.get("reasons") for r in multi["ranked"]):
        fail("C10", "多实例用例：候选缺少 reasons")
    if not QUIET:
        print(f"[C10] 字段 {len(names)} 个；能力位 {idx}；地址选择用例通过")


# ---------------------------------------------------------------- C8


def count_statuses(conclusions) -> dict:
    out = {"CONFIRMED": 0, "INFERRED": 0, "OPEN": 0}
    for row in conclusions.values():
        s = row["status"]
        for k in out:
            if s.startswith(k):
                out[k] += 1
                break
    return out


def check_claims(man, cov, conclusions):
    banned = ["全部确认", "已完全验证", "完全覆盖", "所有车机", "保证可用"]
    negations = ("不", "未", "非", "禁止", "无法", "没有", "不得", "不能")
    for f in text_files():
        if not f.endswith(".md") or f == "TASK.md":
            continue  # TASK.md 是任务书原文，禁止语出现在它的禁令里
        for line in read(rel(f)).splitlines():
            for b in banned:
                if b in line and not any(n in line for n in negations):
                    fail("C8", f"{f} 出现禁用表述: {b}（{line.strip()[:60]}）")
    status = rel("STATUS.md")
    if not os.path.exists(status):
        fail("C8", "缺 STATUS.md")
        return
    st = read(status)
    for need in ("未获取", "PARTIAL", "抓包"):
        if need not in st:
            fail("C8", f"STATUS.md 缺少诚实声明: {need}")
    got = count_statuses(conclusions)
    for level, n in got.items():
        m = re.search(r"^\|\s*" + level + r"\s*\|\s*(\d+)\s*\|", st, re.M)
        if not m:
            fail("C8", f"STATUS.md 缺 {level} 统计行")
        elif int(m.group(1)) != n:
            fail("C8", f"STATUS.md 的 {level} 统计 {m.group(1)} != 实际 {n}")
    m = re.search(r"^\|\s*合计\s*\|\s*(\d+)\s*\|", st, re.M)
    if not m or int(m.group(1)) != len(conclusions):
        fail("C8", f"STATUS.md 的合计统计与实际 {len(conclusions)} 不符")
    if man["counts"]["files"] != len(man["files"]):
        fail("C8", "manifest 文件计数不自洽")
    if man["open_item_count"] != len(man["open_items"]):
        fail("C8", "manifest open_item_count 不自洽")


def main():
    man = check_manifest()
    if UPDATE:
        cov = json.load(open(rel("source/metadata/coverage.json"), encoding="utf-8"))
        conclusions = parse_conclusions()
        check_source()
        check_analysis(conclusions)
        check_spec(conclusions)
        reg = parse_open_registry()
        check_open(reg, cov)
        check_vectors()
        check_runtime()
        check_tables()
        check_coverage(cov)
        check_claims(man, cov, conclusions)
        print(f"manifest updated: files={man['counts']['files']} open_items={man['open_item_count']}")
        return 0

    cov = json.load(open(rel("source/metadata/coverage.json"), encoding="utf-8"))
    check_source()
    conclusions = parse_conclusions()
    check_analysis(conclusions)
    rules = check_spec(conclusions)
    check_open(parse_open_registry(), cov)
    check_vectors()
    check_runtime()
    check_tables()
    check_coverage(cov)
    check_claims(man, cov, conclusions)

    for c, m in WARNS:
        print(f"[warn {c}] {m}")
    if FAILS:
        for c, m in FAILS:
            print(f"[FAIL {c}] {m}")
        print(f"\nfailures: {len(FAILS)}  warnings: {len(WARNS)}")
        return 1
    if not QUIET:
        print(f"rules: {len(rules)}  conclusions: {len(conclusions)}  "
              f"coverage: {len(cov['items'])}  files: {man['counts']['files']}")
        print(f"OK  failures: 0  warnings: {len(WARNS)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
