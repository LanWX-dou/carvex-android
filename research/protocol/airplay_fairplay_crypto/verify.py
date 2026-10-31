#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""airplay_fairplay_crypto docset 自检。

用法：
  python3 verify.py              # 全部检查（缺抓包相关项显式 SKIP）
  python3 verify.py --write      # 重新生成 manifest.json 与 function-index.json

检查项（与 TASK.md §6 对应）：
  C1  三份镜像的 sha256 与 TASK.md / metadata 一致
  C2  asm 导出物自洽：.bin 哈希 == index.json，大小 == end-start，.s 首地址 == start
  C3  spec 规则编号唯一；每条规则有「依据：」；引用的 A-id 在 analysis 中存在
  C4  spec 引用的 OPEN-n 都在 analysis/08 台账里
  C5  TASK.md 的 12 个覆盖项齐全；STATUS.md 三态计数与实际一致
  C6  reference-impl 自检通过；向量可重算并与已提交文件逐字节一致
  C7  负例确实全部失败（错 key / 错 nonce / 改 tag / 短帧）
  C8  禁用词扫描（「全部确认」「所有版本」「所有流」等）
  C9  manifest.json 与当前树一致（多了/少了/改了都报错）
  C10 抓包相关：无抓包时显式 SKIP，不静默通过（TASK §6 A2）
  C11 屏幕AAD读链、原切片、分段指令与合成记录回归（需要capstone）
  C12 CFString原字节、dyld v5元数据及ET分支锚点
  C13 AES原切片、状态/尾拷贝有限解释、NIST CBC/CTR已知答案
  C14 加密器分派的属性门、keyholder门、type分支和provider参数
  C15 Sender Legacy KDF直接调用、公式输入/截断及Receiver整数入参锚点
"""
from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.abspath(__file__))
sys.dont_write_bytecode = True   # 不要在 docset 里留 __pycache__（会破坏 C9 清单）
FAIL: list[str] = []
SKIP: list[str] = []
OK = 0

IMAGES = {
    "AirPlaySender": "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f",
    "AirPlayReceiver": "ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a",
    "AirPlaySupport": "d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15",
}


def rel(*p: str) -> str:
    return os.path.join(ROOT, *p)


def sha256_file(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def check(name: str, fn) -> None:
    global OK
    skips_before = len(SKIP)
    try:
        fn()
    except AssertionError as e:
        FAIL.append(f"{name}: {e}")
        print(f"  FAIL {name}: {e}")
    else:
        if len(SKIP) == skips_before:
            OK += 1
            print(f"  ok   {name}")


def read_text(path: str) -> str:
    with open(path, encoding="utf-8") as f:
        return f.read()


def walk_ext(ext: str) -> list[str]:
    out = []
    for base, _dirs, names in os.walk(ROOT):
        for n in names:
            if n.endswith(ext):
                out.append(os.path.join(base, n))
    return sorted(out)


# --------------------------------------------------------------------------- #
def c1_images() -> None:
    task = read_text(rel("TASK.md"))
    for name, want in IMAGES.items():
        p = rel("source", "firmware", name)
        assert os.path.isfile(p), f"缺 {name}"
        got = sha256_file(p)
        assert got == want, f"{name} sha256 不符（{got}）"
        assert want in task, f"TASK.md 未列出 {name} 的哈希"


def c2_asm() -> None:
    total = 0
    for img in ("AirPlaySender", "AirPlayReceiver", "AirPlaySupport"):
        idx_path = rel("source", "asm", img, "index.json")
        idx = json.loads(read_text(idx_path))
        assert idx.get("image") == img, f"{img}: index.image 不符"
        seen = set()
        for f in idx["functions"]:
            a = int(f["address"], 16)
            assert a not in seen, f"{img}: 地址重复 {f['address']}"
            seen.add(a)
            binp = rel("source", "asm", img, f["bin"])
            assert os.path.isfile(binp), f"{img}: 缺 {f['bin']}"
            raw = open(binp, "rb").read()
            assert hashlib.sha256(raw).hexdigest() == f["raw_sha256"], f"{img}: {f['bin']} 哈希不符"
            assert len(raw) == int(f["end"], 16) - a, f"{img}: {f['bin']} 大小不符"
            s_path = rel("source", "asm", img, f["asm"])
            lines = read_text(s_path).splitlines()
            data = [ln for ln in lines if ln.startswith("0x")]
            if data:
                first = data[0].split(":", 1)[0]
                assert int(first, 16) == a, f"{img}: {f['asm']} 首指令地址不符"
            assert f"source SHA256 {idx['source_sha256']}" in lines[0], f"{img}: {f['asm']} 头部哈希不符"
            total += 1
    assert total >= 50, f"导出函数过少（{total}）"


RULE_RE = re.compile(r"^##\s+(R-\d+\.\d+)\b", re.M)
AID_RE = re.compile(r"\bA-(\d{2})\b")
OPEN_RE = re.compile(r"\bOPEN-(\d{1,2})\b")


def c3_rules() -> None:
    analysis = {os.path.basename(p) for p in walk_ext(".md") if os.sep + "analysis" + os.sep in p}
    a_ids = set()
    for p in walk_ext(".md"):
        if os.sep + "analysis" + os.sep in p:
            a_ids |= {f"A-{m}" for m in AID_RE.findall(read_text(p))}
    assert a_ids, "analysis 里没有任何 A-id"

    rules: dict[str, str] = {}
    for p in walk_ext(".md"):
        if os.sep + "spec" + os.sep not in p:
            continue
        text = read_text(p)
        for m in RULE_RE.finditer(text):
            rid = m.group(1)
            assert rid not in rules, f"规则编号重复：{rid}（{os.path.basename(p)} 与 {rules[rid]}）"
            rules[rid] = os.path.basename(p)
        # 每条规则必须带「依据：」
        blocks = re.split(r"^##\s+", text, flags=re.M)
        for b in blocks:
            m = re.match(r"(R-\d+\.\d+)\b", b)
            if not m:
                continue
            assert "依据：" in b, f"{m.group(1)} 缺「依据：」"
    assert len(rules) >= 25, f"规则过少（{len(rules)}）"

    for p in walk_ext(".md"):
        if os.sep + "spec" + os.sep not in p:
            continue
        for aid in {f"A-{m}" for m in AID_RE.findall(read_text(p))}:
            assert aid in a_ids, f"{os.path.basename(p)} 引用了不存在的 {aid}"
    print(f"       rules={len(rules)} analysis_a_ids={len(a_ids)} analysis_files={len(analysis)}")


def c4_open() -> None:
    ledger = read_text(rel("analysis", "08-open-items.md"))
    defined = {f"OPEN-{m}" for m in OPEN_RE.findall(ledger)}
    assert defined, "台账为空"
    for p in walk_ext(".md"):
        if os.sep + "spec" + os.sep not in p:
            continue
        for oid in {f"OPEN-{m}" for m in OPEN_RE.findall(read_text(p))}:
            assert oid in defined, f"{os.path.basename(p)} 引用了未登记的 {oid}"
    closed = {f"OPEN-{m}" for m in re.findall(r"^\| `OPEN-(\d+)` \| CLOSED", ledger, re.M)}
    assert closed == {"OPEN-7", "OPEN-9", "OPEN-11", "OPEN-13"}
    print(f"       open_items={len(defined-closed)} closed_items={len(closed)}")


def c5_coverage() -> None:
    task = read_text(rel("TASK.md"))
    for i in range(1, 13):
        assert f"| C{i} |" in task, f"TASK.md 缺覆盖项 C{i}"
    st = read_text(rel("STATUS.md"))
    m = re.search(r"<!-- counts:(\d+),(\d+),(\d+) -->", st)
    assert m, "STATUS.md 缺计数标记 <!-- counts:x,y,z -->"
    ev, part, op = (int(x) for x in m.groups())
    body = st
    for label, want in (("有证据", ev), ("部分", part), ("OPEN", op)):
        mm = re.search(rf"\| {label} \| (\d+) \|", body)
        assert mm, f"STATUS.md 缺「{label}」计数行"
        assert int(mm.group(1)) == want, f"STATUS.md「{label}」计数 {mm.group(1)} != {want}"
    assert ev + part + op == 12, f"三态计数和应为 12，实际 {ev + part + op}"


def c6_vectors() -> None:
    impl = rel("reference-impl")
    sys.path.insert(0, impl)
    import fairplay_crypto as fc  # noqa: E402

    fc.selftest()

    tmp = tempfile.mkdtemp(prefix="apvec_")
    env = dict(os.environ, PYTHONIOENCODING="utf-8", PYTHONDONTWRITEBYTECODE="1")
    r = subprocess.run([sys.executable, os.path.join(impl, "gen_vectors.py"), tmp],
                       capture_output=True, text=True, env=env)
    assert r.returncode == 0, f"gen_vectors 失败：{r.stderr[-400:]}"
    for name in ("kdf.json", "chacha.json", "ctr.json", "cbc.json", "negative.json"):
        a = read_text(os.path.join(tmp, name))
        b = read_text(rel("runtime", "vectors", name))
        assert a == b, f"{name} 与已提交向量不一致（重新生成会改变结果）"

    # KDF 与独立计算对照
    kdf = json.loads(read_text(rel("runtime", "vectors", "kdf.json")))
    for v in kdf["vectors"]:
        k = bytes.fromhex(v["K_hex"])
        idx = v["index"]
        key = hashlib.sha512(b"AirPlayStreamKey" + str(idx).encode() + k).digest()[:16]
        iv = hashlib.sha512(b"AirPlayStreamIV" + str(idx).encode() + k).digest()[:16]
        assert key.hex() == v["key16_hex"], f"{v['id']} key 不符"
        assert iv.hex() == v["iv16_hex"], f"{v['id']} iv 不符"
        assert v["name_key"] == f"AirPlayStreamKey{idx}"

    # ChaCha 向量可解密
    ch = json.loads(read_text(rel("runtime", "vectors", "chacha.json")))
    for v in ch["vectors"]:
        aad = bytes.fromhex(v["aad_hex"]) if v.get("aad_hex") else b""
        if "frames" in v:
            for fr in v["frames"]:
                out = fc.chacha20_poly1305_open(bytes.fromhex(v["key_hex"]),
                                                bytes.fromhex(fr["nonce_hex"]),
                                                bytes.fromhex(fr["frame_hex"]), aad)
                assert out is not None and out.hex() == fr["plaintext_hex"], f"{v['id']} 帧解密不符"
        else:
            out = fc.chacha20_poly1305_open(bytes.fromhex(v["key_hex"]),
                                            bytes.fromhex(v["nonce_hex"]),
                                            bytes.fromhex(v["frame_hex"]), aad)
            assert out is not None and out.hex() == v["plaintext_hex"], f"{v['id']} 解密不符"

    ctr = json.loads(read_text(rel("runtime", "vectors", "ctr.json")))
    for v in ctr["vectors"]:
        out = fc.aes128_ctr_crypt(bytes.fromhex(v["key_hex"]), bytes.fromhex(v["iv_hex"]),
                                  bytes.fromhex(v["plaintext_hex"]))
        assert out.hex() == v["ciphertext_hex"], f"{v['id']} CTR 不符"
    cbc = json.loads(read_text(rel("runtime", "vectors", "cbc.json")))
    for frame in cbc["frames"]:
        out = fc.aes128_cbc_frame_encrypt(bytes.fromhex(cbc["key_hex"]), bytes.fromhex(cbc["iv_hex"]),
                                          bytes.fromhex(frame["plaintext_hex"]))
        assert out.hex() == frame["ciphertext_hex"], "CBC合成向量不符"


def c7_negative() -> None:
    sys.path.insert(0, rel("reference-impl"))
    import fairplay_crypto as fc  # noqa: E402

    neg = json.loads(read_text(rel("runtime", "vectors", "negative.json")))
    n = 0
    for v in neg["vectors"]:
        key = bytes.fromhex(v["key_hex"])
        nonce = bytes.fromhex(v["nonce_hex"])
        frame = bytes.fromhex(v["frame_hex"])
        if v["expect"] == "discard":
            assert len(frame) < 16, f"{v['id']} 短帧长度不对"
            assert fc.chacha20_poly1305_open(key, nonce, frame, aad=fc.DEFAULT_AAD) is None
        else:
            assert fc.chacha20_poly1305_open(key, nonce, frame, aad=fc.DEFAULT_AAD) is None, f"{v['id']} 竟然验签通过"
        n += 1
    assert n >= 4, f"负例过少（{n}）"


BANNED = ["全部确认", "所有版本可用", "所有流都能解", "所有流都可用"]


def c8_banned() -> None:
    fence = re.compile(r"```.*?```", re.S)
    for p in walk_ext(".md"):
        text = fence.sub("", read_text(p))   # 代码块里允许出现「禁用词清单」本身
        for w in BANNED:
            assert w not in text, f"{os.path.basename(p)} 出现禁用表述「{w}」"


def build_function_index() -> dict:
    images = {}
    total = 0
    for img in ("AirPlaySender", "AirPlayReceiver", "AirPlaySupport"):
        idx = json.loads(read_text(rel("source", "asm", img, "index.json")))
        funcs = []
        for f in idx["functions"]:
            entry = {k: f[k] for k in ("symbol", "address", "end", "size", "raw_sha256", "asm", "bin")}
            entry["group"] = f.get("group", "")
            read = rel("readable", "ghidra", img, f"f_{int(f['address'], 16):x}.ghidra.c")
            entry["readable"] = (os.path.relpath(read, ROOT).replace("\\", "/")
                                 if os.path.isfile(read) else None)
            funcs.append(entry)
        images[img] = {"source_sha256": idx["source_sha256"], "count": len(funcs), "functions": funcs}
        total += len(funcs)
    audits = {}
    for img in ("AirPlayReceiver", "CoreUtils"):
        audits[img] = json.loads(read_text(rel("source", "asm-audit", img, "index.json")))
    aes_audits = {"CoreUtils": json.loads(read_text(rel("source", "asm-aes-audit", "CoreUtils", "index.json")))}
    return {"docset": "airplay_fairplay_crypto", "images": images, "total_functions": total,
            "audit_images": audits, "aes_audit_images": aes_audits,
            "audit_functions": sum(x["count"] for x in audits.values()) + aes_audits["CoreUtils"]["count"]}


def write_manifest() -> None:
    files = []
    for base, _dirs, names in os.walk(ROOT):
        for n in names:
            if n == "manifest.json":
                continue
            p = os.path.join(base, n)
            files.append({
                "path": os.path.relpath(p, ROOT).replace("\\", "/"),
                "size": os.path.getsize(p),
                "sha256": sha256_file(p),
            })
    files.sort(key=lambda x: x["path"])
    fi = build_function_index()
    with open(rel("function-index.json"), "w", encoding="utf-8", newline="\n") as f:
        json.dump(fi, f, indent=1, ensure_ascii=False)
        f.write("\n")
    # function-index.json 已在上一步写入，重新收集一次以纳入清单
    files = [f for f in files if f["path"] != "function-index.json"]
    files.append({
        "path": "function-index.json",
        "size": os.path.getsize(rel("function-index.json")),
        "sha256": sha256_file(rel("function-index.json")),
    })
    files.sort(key=lambda x: x["path"])
    manifest = {
        "docset": "airplay_fairplay_crypto",
        "source": {img: {"path": f"source/firmware/{img}", "sha256": h} for img, h in IMAGES.items()},
        "counts": {
            "files": len(files),
            "analysis": len([f for f in files if f["path"].startswith("analysis/")]),
            "spec": len([f for f in files if f["path"].startswith("spec/")]),
            "functions": fi["total_functions"],
            "audit_functions": fi["audit_functions"],
            "vectors": len([f for f in files if f["path"].startswith("runtime/vectors/")]),
        },
        "files": files,
    }
    manifest["audit_sources"] = {
        "CoreUtils": {"path": "../airplay_control_plane/source/firmware/CoreUtils",
                      "metadata": "../airplay_control_plane/source/metadata/CoreUtils",
                      "sha256": fi["audit_images"]["CoreUtils"]["source_sha256"]},
        "import_symbols": "../../../firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt",
        "dictionary_slide_metadata": "../../../firmware/extracted/24A446/dyld/dyld_shared_cache_arm64e.54.dylddata",
    }
    with open(rel("manifest.json"), "w", encoding="utf-8", newline="\n") as f:
        json.dump(manifest, f, indent=1, ensure_ascii=False)
        f.write("\n")
    print(f"wrote manifest.json（{len(files)} 文件）与 function-index.json（{fi['total_functions']} 函数）")


def c9_manifest() -> None:
    assert os.path.isfile(rel("manifest.json")), "缺 manifest.json（先跑 --write）"
    man = json.loads(read_text(rel("manifest.json")))
    listed = {f["path"]: f for f in man["files"]}
    actual = set()
    for base, _dirs, names in os.walk(ROOT):
        for n in names:
            if n == "manifest.json":
                continue
            actual.add(os.path.relpath(os.path.join(base, n), ROOT).replace("\\", "/"))
    missing = actual - set(listed)
    extra = set(listed) - actual
    assert not missing, f"清单缺文件：{sorted(missing)[:5]}"
    assert not extra, f"清单多出：{sorted(extra)[:5]}"
    for p, meta in listed.items():
        assert os.path.getsize(rel(p)) == meta["size"], f"{p} 大小变了"
        assert sha256_file(rel(p)) == meta["sha256"], f"{p} 内容变了（重新 --write）"


def c10_capture() -> None:
    cap = rel("runtime", "captures")
    files = [n for n in os.listdir(cap)] if os.path.isdir(cap) else []
    media = [n for n in files if n.lower().endswith((".pcap", ".pcapng", ".jsonl", ".bin"))]
    if not media:
        SKIP.append("C10 真实抓包闭环：runtime/captures 下无 AirPlay 媒体抓包，"
                    "TASK §6 A2 未达成（见 STATUS.md 缺口）")
        return
    raise AssertionError("发现抓包文件但本脚本尚未实现抓包比对，请补 C10 的比对逻辑")


def main() -> int:
    if "--write" in sys.argv:
        write_manifest()
        return 0

    print(f"verify {ROOT}")
    check("C1 镜像哈希", c1_images)
    check("C2 asm 导出物自洽", c2_asm)
    check("C3 spec 规则与依据", c3_rules)
    check("C4 OPEN 台账", c4_open)
    check("C5 12 覆盖项与 STATUS 计数", c5_coverage)
    check("C6 参考实现与向量", c6_vectors)
    check("C7 负例", c7_negative)
    check("C8 禁用表述", c8_banned)
    check("C9 manifest 一致性", c9_manifest)
    check("C10 抓包闭环", c10_capture)
    sys.path.insert(0, rel("reference-impl"))
    from verify_screen_aad import check as screen_aad_check
    check("C11 屏幕AAD与记录边界", screen_aad_check)
    from verify_dictionary_keys import check as dictionary_check
    check("C12 字典键与ET分支", dictionary_check)
    from verify_aes_state import check as aes_check
    check("C13 AES状态与帧边界", aes_check)
    from verify_cryptor_dispatch import check as cryptor_dispatch_check
    check("C14 加密器分派门与参数", cryptor_dispatch_check)
    from verify_sender_kdf import check as sender_kdf_check
    check("C15 Sender Legacy KDF正面证据", sender_kdf_check)

    for s in SKIP:
        print(f"  SKIP {s}")
    print(f"\n结果：{OK} 通过，{len(FAIL)} 失败，{len(SKIP)} 跳过")
    if FAIL:
        for f in FAIL:
            print("  -", f)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
