"""24A446 NetTransport 记录结构模型，不实现加密或网络会话。

依据 analysis/13。调用者仍需独立验证 AEAD、方向、初始 nonce 和会话切换。
"""
from __future__ import annotations

READ_LIMIT = 16384
WRITE_LIMIT = 1024


def authentication_input(ciphertext: bytes) -> bytes:
    """返回喂入 Poly1305 的字节串，不计算 Poly1305 密钥或 tag。"""
    if len(ciphertext) > READ_LIMIT:
        raise ValueError("exceeds observed receive limit")
    header = len(ciphertext).to_bytes(2, "little")
    return (header + bytes(14) + ciphertext + bytes(-len(ciphertext) % 16)
            + (2).to_bytes(8, "little") + len(ciphertext).to_bytes(8, "little"))


def frame_ciphertext(ciphertext: bytes, tag: bytes) -> bytes:
    """本地写侧模型；输入必须已由独立 AEAD 生成，函数不验证 tag。"""
    if len(ciphertext) > WRITE_LIMIT or len(tag) != 16:
        raise ValueError("invalid write record size/tag")
    return len(ciphertext).to_bytes(2, "little") + ciphertext + tag


def split_record(record: bytes) -> tuple[bytes, bytes, bytes]:
    """拆一条完整记录，返回 header/ciphertext/tag；不代表认证成功。"""
    if len(record) < 18:
        raise ValueError("truncated record")
    length = int.from_bytes(record[:2], "little")
    if length > READ_LIMIT or len(record) != length + 18:
        raise ValueError("invalid receive record size")
    return record[:2], record[2:2 + length], record[-16:]


def next_nonce(nonce: bytes) -> bytes:
    """LE64 加 1；拒绝回绕为本地安全策略，非固件已观察到的拒绝门。"""
    if len(nonce) != 8:
        raise ValueError("nonce must be 8 bytes")
    value = int.from_bytes(nonce, "little")
    if value == (1 << 64) - 1:
        raise OverflowError("rekey before nonce exhaustion")
    return (value + 1).to_bytes(8, "little")


def self_test() -> None:
    # 独立手写 transcript：AAD=03 00，ciphertext=01 02 03。
    expected = bytes.fromhex(
        "03000000000000000000000000000000"
        "01020300000000000000000000000000"
        "02000000000000000300000000000000")
    assert authentication_input(b"\x01\x02\x03") == expected
    assert next_nonce(bytes.fromhex("ff00000000000000")) == bytes.fromhex("0001000000000000")
    assert next_nonce(bytes.fromhex("ffffffff00000000")) == bytes.fromhex("0000000001000000")
    for n in (0, 1, 15, 16, 17, 1024, 16384):
        ciphertext = bytes(n)
        transcript = authentication_input(ciphertext)
        assert len(transcript) == 32 + ((n + 15) // 16) * 16
        wire = n.to_bytes(2, "little") + ciphertext + bytes(16)
        assert split_record(wire) == (wire[:2], ciphertext, bytes(16))
        if n <= WRITE_LIMIT:
            assert frame_ciphertext(ciphertext, bytes(16)) == wire
    for operation in (
        lambda: next_nonce(bytes(7)),
        lambda: next_nonce(b"\xff" * 8),
        lambda: frame_ciphertext(bytes(1025), bytes(16)),
        lambda: frame_ciphertext(b"x", bytes(15)),
        lambda: split_record(bytes(17)),
        lambda: split_record(bytes.fromhex("0140") + bytes(16385 + 16)),
        lambda: split_record(bytes.fromhex("0100") + bytes(16)),
        lambda: split_record(bytes(19)),
    ):
        try:
            operation()
        except (ValueError, OverflowError):
            pass
        else:
            raise AssertionError("invalid boundary accepted")


if __name__ == "__main__":
    self_test()
    print("record_layout: OK (structure only; no AEAD/interoperability test)")
