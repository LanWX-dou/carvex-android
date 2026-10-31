#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成 reference-impl/test_vectors.json（合成报文，不是车机抓包）。

每条向量的 hex 都由本脚本用 mdns_discovery 的编码器现场生成，
期望值写在 expect 里，由 mdns_discovery.py --vectors 校验。

注意：这些报文是**构造出来的**，只用于证明解析器行为，不能当作
“车机实际宣告”的证据。
"""
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mdns_discovery as md  # noqa: E402

SVC = "_airplay._tcp.local."
INST = "Living Room."
HOST = "Demo-Receiver.local."

TXT_FULL = [
    ("srcvers", "220.68"),
    ("deviceid", "AA:BB:CC:DD:EE:FF"),
    ("features", "0x5A7FFFF7,0x1E"),
    ("model", "AppleTV6,2"),
    ("flags", "0x4"),
    ("vv", "2"),
    ("serialNumber", "SYNTHETIC-0001"),
    ("pk", "c3ludGhldGljLXBr"),
    ("zzz", "unknown-kept"),
]


def ann(answers, additional):
    return md.build_message(answers, flags=0x8400, additional=additional).hex()


def raw_txt(chunks):
    out = bytearray()
    for c in chunks:
        out.append(len(c))
        out += c
    return bytes(out)


VECTORS = []

# 1. 完整链
VECTORS.append({
    "name": "full-chain",
    "note": "合成：PTR 在 answer，SRV/TXT/A/AAAA 在 additional",
    "src": "192.168.50.2",
    "packets": [{"hex": ann(
        [md.rr_ptr(SVC, INST)],
        [md.rr_srv(INST, HOST, 7000), md.rr_txt(INST, TXT_FULL), md.rr_a(HOST, "192.168.50.2"),
         md.rr_aaaa(HOST, "fe80::1c2a:3bff:fe4d:5e6f")],
    )}],
    "expect": {
        "instances": [INST],
        "ports": [7000],
        "addresses": ["192.168.50.2", "fe80::1c2a:3bff:fe4d:5e6f"],
        "txt": {"features": ["0x5A7FFFF7,0x1E"], "srcvers": ["220.68"]},
        "ranked": [INST],
        "usable": [True],
    },
})

# 2. 浏览查询 + QU 位
VECTORS.append({
    "name": "browse-query-qu",
    "note": "合成：PTR 查询，QU 位置 1",
    "packets": [{"hex": md.build_message(
        [], questions=[{"name": SVC, "type": md.TYPE_PTR, "qu": True}], flags=0x0000).hex()}],
    "expect": {"questions": [[SVC, True]]},
})

# 3. 缺 TXT
VECTORS.append({
    "name": "missing-txt",
    "note": "合成：只有 PTR/SRV/A，没有 TXT",
    "packets": [{"hex": ann([md.rr_ptr(SVC, INST)], [md.rr_srv(INST, HOST, 7000), md.rr_a(HOST, "192.168.50.2")])}],
    "expect": {"instances": [INST], "ports": [7000], "addresses": ["192.168.50.2"], "usable": [True]},
})

# 4. 重复键
VECTORS.append({
    "name": "duplicate-key",
    "note": "合成：features 出现两次，必须保留为两条",
    "packets": [{"hex": ann([md.rr_ptr(SVC, INST)], [
        md.rr_srv(INST, HOST, 7000),
        md.rr_txt(INST, [("features", "0x5A7FFFF7,0x1E"), ("features", "0x5A7FFFF7,0x1F")]),
        md.rr_a(HOST, "192.168.50.2")])}],
    "expect": {"txt_lists": {"features": ["0x5A7FFFF7,0x1E", "0x5A7FFFF7,0x1F"]}},
})

# 5. 未知键 + 非 UTF-8 值
VECTORS.append({
    "name": "unknown-key-binary",
    "note": "合成：未知键 zzz 保留；raw 值为非 UTF-8，转成 0x 十六进制",
    "packets": [{"hex": ann([md.rr_ptr(SVC, INST)], [
        md.rr_srv(INST, HOST, 7000),
        {"name": INST, "type": md.TYPE_TXT, "ttl": 4500, "cache_flush": True,
         "rdata": raw_txt([b"zzz=unknown-kept", b"raw=\xff\xfe"])},
        md.rr_a(HOST, "192.168.50.2")])}],
    "expect": {"txt": {"zzz": ["unknown-kept"], "raw": ["0xfffe"]}},
})

# 6. 只有 IPv6 link-local
VECTORS.append({
    "name": "ipv6-linklocal-only",
    "note": "合成：只有 AAAA fe80::/10",
    "packets": [{"hex": ann([md.rr_ptr(SVC, INST)], [
        md.rr_srv(INST, HOST, 7000), md.rr_aaaa(HOST, "fe80::1c2a:3bff:fe4d:5e6f")])}],
    "expect": {"addresses": ["fe80::1c2a:3bff:fe4d:5e6f"], "usable": [False], "ranked": [INST]},
})

# 7. 多实例：一个缺地址
VECTORS.append({
    "name": "multi-instance-one-unresolvable",
    "note": "合成：Kitchen 有 SRV 但无 A/AAAA，必须排后且标记不可用",
    "packets": [{"hex": ann(
        [md.rr_ptr(SVC, "Living Room."), md.rr_ptr(SVC, "Kitchen.")],
        [md.rr_srv("Living Room.", HOST, 7000), md.rr_a(HOST, "192.168.50.2"),
         md.rr_srv("Kitchen.", "Kitchen.local.", 7001)])}],
    "expect": {"instances": ["Kitchen.", "Living Room."], "ranked": ["Living Room.", "Kitchen."],
               "usable": [True, False]},
})

# 8. goodbye
VECTORS.append({
    "name": "goodbye-ttl0",
    "note": "合成：第二条 PTR TTL=0 撤销实例",
    "snapshot_at": 1.0,
    "packets": [
        {"hex": ann([md.rr_ptr(SVC, INST)], [md.rr_srv(INST, HOST, 7000), md.rr_a(HOST, "192.168.50.2")])},
        {"hex": ann([md.rr_ptr(SVC, INST, ttl=0)], [])},
    ],
    "expect": {"instances": [], "log_contains": ["goodbye PTR"]},
})

# 9. 压缩指针环
VECTORS.append({
    "name": "bad-pointer",
    "note": "合成：名称指针指向自身，必须报错而不是死循环",
    "packets": [{"hex": (struct.pack("!HHHHHH", 0, 0x8400, 0, 1, 0, 0) + b"\xc0\x0c" + b"\x00\x0c\x00\x01\x00\x00\x00\x00\x00\x00").hex()}],
    "expect": {"error": True},
})

# 10. 截断
VECTORS.append({
    "name": "truncated-question",
    "note": "合成：header 声称 1 个问题，但后面没有字节",
    "packets": [{"hex": struct.pack("!HHHHHH", 0, 0x0000, 1, 0, 0, 0).hex()}],
    "expect": {"error": True},
})


def main() -> None:
    doc = {
        "note": "全部为合成报文（code-generated），不是车机抓包；见 analysis/09-runtime-captures.md",
        "generated_by": "reference-impl/gen_vectors.py",
        "vectors": VECTORS,
    }
    out = os.path.join(os.path.dirname(os.path.abspath(__file__)), "test_vectors.json")
    with open(out, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(doc, fh, ensure_ascii=False, indent=2)
        fh.write("\n")
    print(f"wrote {out}: {len(VECTORS)} vectors")


if __name__ == "__main__":
    main()
