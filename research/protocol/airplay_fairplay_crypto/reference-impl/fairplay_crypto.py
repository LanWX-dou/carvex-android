#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""AirPlay FairPlay / 帧加密参考实现（纯标准库，无第三方依赖）。

覆盖 spec/04（KDF）、spec/06（AES-128-CTR）、spec/07（ChaCha20-Poly1305, 64-bit nonce）。

证据边界（必须与文档一致）：
  * KDF 的输入输出、拼接顺序、截断长度 —— 有指令级证据（analysis/04）。
  * ChaCha 段布局、tag位置、nonce每次验签和长度检查成功后+1 —— A-23/A-35。
  * ChaCha 的 AAD —— 已核屏幕接收路径为完整128B原始网络头（A-34）；
    本实现要求显式AAD。空/零AAD仅保留为历史合成自检，不是线上候选默认值。
  * AES-CTR：原CoreUtils已证128位大端+1、跨Update保留剩余密钥流（A-41）。
  * AES-CBCFrame：每次Update重置初始IV，只处理整块前缀、尾部直通（A-40）；这里只提供加密端。
  * 原语与边界复算不等于目标CarPlay profile/真实媒体互通。

不实现FairPlay SAP本身（OPEN-1）；集成须确认目标profile及可用合法实现/授权接口。
"""

from __future__ import annotations

import hashlib
import struct

__all__ = [
    "derive_stream_keys",
    "chacha20_poly1305_seal",
    "chacha20_poly1305_open",
    "aes128_ctr_crypt",
    "AES128CTR",
    "aes128_cbc_frame_encrypt",
    "selftest",
]

M32 = 0xFFFFFFFF
M64 = 0xFFFFFFFFFFFFFFFF


# --------------------------------------------------------------------------- #
# spec/04  SHA-512 KDF
# --------------------------------------------------------------------------- #
def derive_stream_keys(master_key: bytes, stream_index: int) -> tuple[bytes, bytes]:
    """key16 = SHA512(b"AirPlayStreamKey" + dec(i) + K)[:16]; iv16 同理。

    拼接顺序：名字在前、密钥在后；索引用 %llu 十进制（无前导零）。
    """
    if len(master_key) == 0:
        raise ValueError("master key 不能为空")
    idx = str(int(stream_index)).encode("ascii")
    key = hashlib.sha512(b"AirPlayStreamKey" + idx + master_key).digest()[:16]
    iv = hashlib.sha512(b"AirPlayStreamIV" + idx + master_key).digest()[:16]
    return key, iv


# --------------------------------------------------------------------------- #
# ChaCha20（原始变体：64-bit counter + 64-bit nonce）
# --------------------------------------------------------------------------- #
def _rotl32(v: int, c: int) -> int:
    return ((v << c) & M32) | (v >> (32 - c))


def _chacha20_block(key: bytes, counter: int, nonce: bytes) -> bytes:
    if len(key) != 32:
        raise ValueError("ChaCha20 需要 32 字节 key")
    if len(nonce) != 8:
        raise ValueError("本实现是 64-bit nonce 变体，nonce 必须 8 字节")
    const = (0x61707865, 0x3320646E, 0x79622D32, 0x6B206574)
    st = list(const) + list(struct.unpack("<8I", key))
    st += list(struct.unpack("<2I", struct.pack("<Q", counter & M64)))
    st += list(struct.unpack("<2I", nonce))
    x = st[:]

    def qr(a: int, b: int, c: int, d: int) -> None:
        x[a] = (x[a] + x[b]) & M32
        x[d] = _rotl32(x[d] ^ x[a], 16)
        x[c] = (x[c] + x[d]) & M32
        x[b] = _rotl32(x[b] ^ x[c], 12)
        x[a] = (x[a] + x[b]) & M32
        x[d] = _rotl32(x[d] ^ x[a], 8)
        x[c] = (x[c] + x[d]) & M32
        x[b] = _rotl32(x[b] ^ x[c], 7)

    for _ in range(10):
        qr(0, 4, 8, 12)
        qr(1, 5, 9, 13)
        qr(2, 6, 10, 14)
        qr(3, 7, 11, 15)
        qr(0, 5, 10, 15)
        qr(1, 6, 11, 12)
        qr(2, 7, 8, 13)
        qr(3, 4, 9, 14)
    return struct.pack("<16I", *[((x[i] + st[i]) & M32) for i in range(16)])


def _chacha20_xor(key: bytes, nonce: bytes, data: bytes, counter: int) -> bytes:
    out = bytearray(len(data))
    for off in range(0, len(data), 64):
        ks = _chacha20_block(key, counter + off // 64, nonce)
        chunk = data[off:off + 64]
        for i, b in enumerate(chunk):
            out[off + i] = b ^ ks[i]
    return bytes(out)


# --------------------------------------------------------------------------- #
# Poly1305
# --------------------------------------------------------------------------- #
def _poly1305(key: bytes, msg: bytes) -> bytes:
    if len(key) != 32:
        raise ValueError("Poly1305 需要 32 字节一次性 key")
    r = int.from_bytes(key[:16], "little") & 0x0FFFFFFC0FFFFFFC0FFFFFFC0FFFFFFF
    s = int.from_bytes(key[16:], "little")
    p = (1 << 130) - 5
    acc = 0
    for i in range(0, len(msg), 16):
        chunk = msg[i:i + 16]
        acc = ((acc + int.from_bytes(chunk + b"\x01", "little")) * r) % p
    return ((acc + s) & ((1 << 128) - 1)).to_bytes(16, "little")


def _pad16(n: int) -> bytes:
    return b"\x00" * ((16 - (n % 16)) % 16)


def _aead_mac_data(aad: bytes, ct: bytes) -> bytes:
    return (aad + _pad16(len(aad)) + ct + _pad16(len(ct))
            + struct.pack("<Q", len(aad)) + struct.pack("<Q", len(ct)))


EXPERIMENTAL_ZERO_AAD = b"\x00" * 0x80   # 仅合成向量候选，不是线上默认
# 仅为旧合成向量兼容名称；它不是线上默认，调用方仍必须显式传入 aad。
DEFAULT_AAD = EXPERIMENTAL_ZERO_AAD


def chacha20_poly1305_seal(key: bytes, nonce: bytes, plaintext: bytes,
                           aad: bytes | None = None) -> bytes:
    """返回 frame = 密文 ‖ 16 字节 tag（spec/07 R-7.1）。"""
    if aad is None:
        raise ValueError("必须显式传入AAD；已核屏幕路径使用128B原始网络头（A-34）")
    if len(key) != 32:
        raise ValueError("ChaCha20-Poly1305 需要 32 字节 key")
    if len(nonce) != 8:
        raise ValueError("nonce 必须 8 字节")
    poly_key = _chacha20_block(key, 0, nonce)[:32]
    ct = _chacha20_xor(key, nonce, plaintext, counter=1)
    tag = _poly1305(poly_key, _aead_mac_data(aad, ct))
    return ct + tag


def chacha20_poly1305_open(key: bytes, nonce: bytes, frame: bytes,
                           aad: bytes | None = None) -> bytes | None:
    """候选算法验签通过返回明文；失败/短段返回None，不映射固件固定错误码。"""
    if aad is None:
        return None
    if len(frame) < 16:
        return None
    ct, tag = frame[:-16], frame[-16:]
    poly_key = _chacha20_block(key, 0, nonce)[:32]
    if _poly1305(poly_key, _aead_mac_data(aad, ct)) != tag:
        return None
    return _chacha20_xor(key, nonce, ct, counter=1)


def next_nonce(nonce: bytes) -> bytes:
    """8 字节小端 +1（带进位、回绕）—— 对应 analysis/06 A-23 的循环自增。"""
    b = bytearray(nonce)
    for i in range(8):
        b[i] = (b[i] + 1) & 0xFF
        if b[i] != 0:
            break
    return bytes(b)


# --------------------------------------------------------------------------- #
# AES-128（加密方向即可满足 CTR）
# --------------------------------------------------------------------------- #
def _build_sbox() -> list[int]:
    exp = [0] * 512
    log = [0] * 256
    x = 1
    for i in range(255):
        exp[i] = x
        log[x] = i
        t = x << 1
        if t & 0x100:
            t ^= 0x11B
        x ^= t
    for i in range(255, 512):
        exp[i] = exp[i - 255]
    sbox = [0] * 256
    for i in range(256):
        inv = 0 if i == 0 else exp[255 - log[i]]
        s = inv
        for _ in range(4):
            inv = ((inv << 1) | (inv >> 7)) & 0xFF
            s ^= inv
        sbox[i] = s ^ 0x63
    return sbox


SBOX = _build_sbox()


def _xtime(a: int) -> int:
    a <<= 1
    if a & 0x100:
        a ^= 0x11B
    return a & 0xFF


def _expand_key(key: bytes) -> list[int]:
    if len(key) != 16:
        raise ValueError("本实现只支持 AES-128")
    w = list(struct.unpack(">4I", key))
    rcon = 1
    for i in range(4, 44):
        t = w[i - 1]
        if i % 4 == 0:
            t = ((t << 8) | (t >> 24)) & M32
            t = ((SBOX[(t >> 24) & 0xFF] << 24) | (SBOX[(t >> 16) & 0xFF] << 16)
                 | (SBOX[(t >> 8) & 0xFF] << 8) | SBOX[t & 0xFF])
            t ^= rcon << 24
            rcon = _xtime(rcon)
        w.append(w[i - 4] ^ t)
    return w


def _round_key_bytes(rk: list[int], r: int) -> bytes:
    return b"".join(struct.pack(">I", word) for word in rk[r * 4:r * 4 + 4])


def _encrypt_block(rk: list[int], block: bytes) -> bytes:
    s = [a ^ b for a, b in zip(block, _round_key_bytes(rk, 0))]
    for r in range(1, 11):
        s = [SBOX[b] for b in s]
        s = _shift_rows(s)
        if r != 10:
            s = _mix_columns(s)
        s = [a ^ b for a, b in zip(s, _round_key_bytes(rk, r))]
    return bytes(s)


def _shift_rows(s: list[int]) -> list[int]:
    # 状态按列存放：s[c*4+r]
    out = [0] * 16
    for c in range(4):
        for r in range(4):
            out[c * 4 + r] = s[((c + r) % 4) * 4 + r]
    return out


def _mix_columns(s: list[int]) -> list[int]:
    out = [0] * 16
    for c in range(4):
        a = s[c * 4:c * 4 + 4]
        t = a[0] ^ a[1] ^ a[2] ^ a[3]
        out[c * 4 + 0] = a[0] ^ t ^ _xtime(a[0] ^ a[1])
        out[c * 4 + 1] = a[1] ^ t ^ _xtime(a[1] ^ a[2])
        out[c * 4 + 2] = a[2] ^ t ^ _xtime(a[2] ^ a[3])
        out[c * 4 + 3] = a[3] ^ t ^ _xtime(a[3] ^ a[0])
    return out


class AES128CTR:
    """同一上下文跨update连续消费密钥流；耗尽拒绝是本地策略，不是固件已有检查。"""

    def __init__(self, key: bytes, iv: bytes):
        if len(iv) != 16:
            raise ValueError("CTR需要16字节IV")
        self.rk = _expand_key(key)
        self.counter = int.from_bytes(iv, "big")
        self.block = b""
        self.offset = 0
        self.exhausted = False

    def update(self, data: bytes) -> bytes:
        # 在改写任何状态前校验资源，避免部分输出后才报告耗尽。
        remaining = 16-self.offset if self.offset else 0
        blocks = (max(0, len(data)-remaining)+15)//16
        available = 0 if self.exhausted else (1 << 128)-self.counter
        if blocks > available:
            raise OverflowError("CTR counter exhausted; establish a new key context")
        out = bytearray()
        for byte in data:
            if self.offset == 0:
                self.block = _encrypt_block(self.rk, self.counter.to_bytes(16, "big"))
                self.counter = (self.counter+1) & ((1 << 128)-1)
                self.exhausted = self.counter == 0
            out.append(byte ^ self.block[self.offset])
            self.offset = (self.offset+1) & 15
        return bytes(out)


def aes128_ctr_crypt(key: bytes, iv: bytes, data: bytes) -> bytes:
    """新上下文的一次调用；多次/多帧处理请保留同一个AES128CTR对象。"""
    return AES128CTR(key, iv).update(data)


def aes128_cbc_frame_encrypt(key: bytes, iv: bytes, data: bytes) -> bytes:
    """对应一次CBCFrame_Update的加密端：固定IV重置、整块CBC、尾部原样，不填充。"""
    if len(iv) != 16:
        raise ValueError("CBC-frame需要16字节IV")
    rk = _expand_key(key)
    full = len(data) & ~15
    out = bytearray()
    previous = iv
    for off in range(0, full, 16):
        previous = _encrypt_block(rk, bytes(a ^ b for a, b in zip(data[off:off+16], previous)))
        out.extend(previous)
    out.extend(data[full:])
    return bytes(out)


# --------------------------------------------------------------------------- #
def cbc_frame_candidate(key: bytes, iv: bytes, frames: list[bytes]) -> list[bytes]:
    """历史函数名兼容入口；已改为A-40的逐调用IV重置，不再链接上一帧末块。"""
    return [aes128_cbc_frame_encrypt(key, iv, frame) for frame in frames]


def selftest() -> None:
    # FIPS-197 AES-128 已知答案
    assert _encrypt_block(_expand_key(bytes(range(16))),
                          bytes.fromhex("00112233445566778899aabbccddeeff")
                          ).hex() == "69c4e0d86a7b0430d8cdb78070b4c55a"
    # KDF 与独立计算一致
    k = bytes(range(16))
    key, iv = derive_stream_keys(k, 7)
    assert key == hashlib.sha512(b"AirPlayStreamKey7" + k).digest()[:16]
    assert iv == hashlib.sha512(b"AirPlayStreamIV7" + k).digest()[:16]
    # ChaCha 往返
    sk = bytes(range(32))
    n0 = b"\x00" * 8
    pt = b"frame payload of arbitrary length...."
    fr = chacha20_poly1305_seal(sk, n0, pt, aad=DEFAULT_AAD)
    assert len(fr) == len(pt) + 16
    assert chacha20_poly1305_open(sk, n0, fr, aad=DEFAULT_AAD) == pt
    # 错 key / 错 nonce / 改 tag 必须失败
    assert chacha20_poly1305_open(bytes(32), n0, fr, aad=DEFAULT_AAD) is None
    assert chacha20_poly1305_open(sk, b"\x01" + b"\x00" * 7, fr, aad=DEFAULT_AAD) is None
    bad = bytearray(fr)
    bad[0] ^= 1
    assert chacha20_poly1305_open(sk, n0, bytes(bad), aad=DEFAULT_AAD) is None
    # nonce 自增（含进位）
    assert next_nonce(b"\xff" * 8) == b"\x00" * 8
    assert next_nonce(b"\x00" * 8) == b"\x01" + b"\x00" * 7
    assert next_nonce(b"\xff\x00\x00\x00\x00\x00\x00\x00") == b"\x00\x01" + b"\x00" * 6


if __name__ == "__main__":
    selftest()
    print("selftest OK")
