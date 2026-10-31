#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成 runtime/vectors/*.json 中的测试向量（可重跑，输出确定）。

用法： python3 gen_vectors.py [输出目录]
默认输出到 ../runtime/vectors。
"""
from __future__ import annotations

import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import fairplay_crypto as fc  # noqa: E402


def h(b: bytes) -> str:
    return b.hex()


def build_kdf() -> dict:
    out = []
    cases = [
        (bytes(range(16)), 0),
        (bytes(range(16)), 7),
        (bytes([0xA5] * 16), 12345),
    ]
    for n, (k, idx) in enumerate(cases, 1):
        key, iv = fc.derive_stream_keys(k, idx)
        out.append({
            "id": f"kdf-{n}",
            "K_hex": h(k),
            "index": idx,
            "name_key": f"AirPlayStreamKey{idx}",
            "name_iv": f"AirPlayStreamIV{idx}",
            "key16_hex": h(key),
            "iv16_hex": h(iv),
        })
    return {
        "spec": "spec/04-kdf.md R-4.1 / R-4.2",
        "algorithm": "key16 = SHA-512(nameKey||K)[0:16]; iv16 = SHA-512(nameIV||K)[0:16]",
        "note": "名字为 ASCII 前缀 + %llu 十进制索引；K 长度由调用方给（Legacy 路径为 16 字节）",
        "vectors": out,
    }


def build_chacha() -> dict:
    key = bytes(range(32))
    out = []
    # 1) 单帧
    pt1 = b"airplay screen frame #0"
    out.append({
        "id": "chacha-1",
        "sort": "single-frame",
        "key_hex": h(key),
        "nonce_hex": h(b"\x00" * 8),
        "aad_hex": h(fc.DEFAULT_AAD),
        "plaintext_hex": h(pt1),
        "payload_len": len(pt1),
        "frame_hex": h(fc.chacha20_poly1305_seal(key, b"\x00" * 8, pt1, aad=fc.DEFAULT_AAD)),
    })
    # 2) 多个独立加密段：nonce逐段+1，不表示每个网络记录只有一段
    frames = []
    nonce = b"\x00" * 8
    for i in range(3):
        pt = bytes([i]) * (40 + i)
        frames.append({
            "index": i,
            "nonce_hex": h(nonce),
            "plaintext_hex": h(pt),
            "frame_hex": h(fc.chacha20_poly1305_seal(key, nonce, pt, aad=fc.DEFAULT_AAD)),
        })
        nonce = fc.next_nonce(nonce)
    out.append({
        "id": "chacha-2",
        "sort": "multi-frame-nonce-advance",
        "key_hex": h(key),
        "aad_hex": h(fc.DEFAULT_AAD),
        "frames": frames,
        "note": "第 0 帧 nonce 全零；验签成功后 8 字节小端 +1（带进位）",
    })
    # 3) 历史空AAD候选算法自检；不是线上AAD二选一判据
    pt3 = b"aad variant probe"
    out.append({
        "id": "chacha-3",
        "sort": "aad-empty-probe",
        "key_hex": h(key),
        "nonce_hex": h(b"\x00" * 8),
        "aad_hex": "",
        "plaintext_hex": h(pt3),
        "payload_len": len(pt3),
        "frame_hex": h(fc.chacha20_poly1305_seal(key, b"\x00" * 8, pt3, aad=b"")),
        "note": "仅候选算法MAC敏感性自检；已核屏幕AAD为原始128B头，不以空/零二选一判定OPEN-10",
    })
    # 4) 非空短载荷（不是最短加密段；纯tag也可进入验证）
    pt4 = b"\x42"
    out.append({
        "id": "chacha-4",
        "sort": "one-byte-payload",
        "key_hex": h(key),
        "nonce_hex": h(b"\x00" * 8),
        "aad_hex": h(fc.DEFAULT_AAD),
        "plaintext_hex": h(pt4),
        "payload_len": 1,
        "frame_hex": h(fc.chacha20_poly1305_seal(key, b"\x00" * 8, pt4, aad=fc.DEFAULT_AAD)),
    })
    # 5) 16B纯tag：空明文。6) 单记录双段，各自消费一次nonce。
    header = bytearray(range(128))
    header[:4] = (16).to_bytes(4, "little")
    header[4] = 0
    header[28:32] = bytes(4)
    out.append({
        "id": "chacha-5", "sort": "empty-plaintext",
        "key_hex": h(key), "nonce_hex": h(bytes(8)), "aad_hex": h(header),
        "plaintext_hex": "", "payload_len": 0,
        "frame_hex": h(fc.chacha20_poly1305_seal(key, bytes(8), b"", aad=bytes(header))),
    })
    payloads = (b"screen body", b"synthetic tail")
    header[:4] = (sum(map(len, payloads)) + 32).to_bytes(4, "little")
    header[28:32] = (len(payloads[1]) + 16).to_bytes(4, "little")
    frames = []
    for i, payload in enumerate(payloads):
        nonce = i.to_bytes(8, "little")
        frames.append({"index": i, "nonce_hex": h(nonce), "plaintext_hex": h(payload),
                       "frame_hex": h(fc.chacha20_poly1305_seal(key, nonce, payload, aad=bytes(header)))})
    out.append({
        "id": "chacha-6", "sort": "two-segment-record", "key_hex": h(key),
        "aad_hex": h(header), "frames": frames,
        "note": "合成非零128B头，同一AAD、nonce0/1；未定义字段只是夹具，不是可发送的合法profile头",
    })
    return {
        "spec": "spec/07-frame-crypto-chacha.md R-7.1 / R-7.3 / R-7.4",
        "construction": "候选ChaCha20-Poly1305, 64-bit nonce + 64-bit counter；未证明目标库互操作",
        "frame_layout": "frame = ciphertext || tag16",
        "vectors": out,
    }


def build_ctr() -> dict:
    key = bytes(range(16))
    iv = bytes(range(16, 32))
    out = []
    for n, pt in enumerate([b"0123456789abcdef", bytes((i * 5) & 0xFF for i in range(70))], 1):
        out.append({
            "id": f"ctr-{n}",
            "key_hex": h(key),
            "iv_hex": h(iv),
            "plaintext_hex": h(pt),
            "ciphertext_hex": h(fc.aes128_ctr_crypt(key, iv, pt)),
        })
    return {
        "spec": "spec/06-frame-crypto-aes.md R-6.1",
        "note": "A-41已证128位大端+1；多次Update须保留未消费密钥流，不能每帧新建上下文；这些是合成向量",
        "vectors": out,
    }


def build_cbc() -> dict:
    key, iv = bytes(range(16)), bytes(range(16, 32))
    frames = [b"", b"tail", bytes(range(16)), bytes(range(31)), bytes(range(32)), bytes(range(16))]
    return {
        "spec": "spec/06 R-6.3; analysis/13 A-40",
        "note": "合成向量；每条对应一次Update，不是任意TCP分片；每次初始IV重置，尾部直通",
        "key_hex": h(key), "iv_hex": h(iv),
        "frames": [{"plaintext_hex": h(p), "ciphertext_hex": h(fc.aes128_cbc_frame_encrypt(key, iv, p))}
                   for p in frames],
    }


def build_negative() -> dict:
    key = bytes(range(32))
    nonce = b"\x00" * 8
    pt = b"negative test payload"
    frame = fc.chacha20_poly1305_seal(key, nonce, pt, aad=fc.DEFAULT_AAD)
    bad_tag = bytearray(frame)
    bad_tag[-1] ^= 0x80
    return {
        "spec": "spec/07 R-7.5 / spec/08 R-8.2",
        "vectors": [
            {
                "id": "neg-1-wrong-key",
                "kind": "wrong_key",
                "key_hex": h(bytes(32)),
                "nonce_hex": h(nonce),
                "frame_hex": h(frame),
                "expect": "auth_fail",
            },
            {
                "id": "neg-2-wrong-nonce",
                "kind": "wrong_nonce",
                "key_hex": h(key),
                "nonce_hex": h(b"\x01" + b"\x00" * 7),
                "frame_hex": h(frame),
                "expect": "auth_fail",
            },
            {
                "id": "neg-3-tampered-tag",
                "kind": "tampered_tag",
                "key_hex": h(key),
                "nonce_hex": h(nonce),
                "frame_hex": h(bytes(bad_tag)),
                "expect": "auth_fail",
            },
            {
                "id": "neg-4-short-frame",
                "kind": "short_frame",
                "key_hex": h(key),
                "nonce_hex": h(nonce),
                "frame_hex": h(frame[:12]),
                "expect": "discard",
            },
        ],
        "note": "auth_fail为本地结果，不映射固定OSStatus；短段拒绝为本地安全策略，固件原函数返回0但未认证",
    }


def main() -> None:
    outdir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, "..", "runtime", "vectors")
    outdir = os.path.abspath(outdir)
    os.makedirs(outdir, exist_ok=True)
    for name, payload in (
        ("kdf.json", build_kdf()),
        ("chacha.json", build_chacha()),
        ("ctr.json", build_ctr()),
        ("cbc.json", build_cbc()),
        ("negative.json", build_negative()),
    ):
        path = os.path.join(outdir, name)
        with open(path, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(payload, fh, indent=1, ensure_ascii=False)
            fh.write("\n")
        print("wrote", path)


if __name__ == "__main__":
    main()
