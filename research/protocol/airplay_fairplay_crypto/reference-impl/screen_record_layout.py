"""24A446已核type=0路径的记录切分；不是线上头构造器或密码库实现。

严格段长/资源上限为本地安全策略。必须先完成流重组，不能将TCP分片当记录。
未知头字段保持原样；这里不证明这些字段的profile合法性。
"""
from dataclasses import dataclass


@dataclass(frozen=True)
class ScreenRecord:
    aad: bytes
    segments: tuple[bytes, ...]


def split_chacha_record(header: bytes, body: bytes, *, max_body: int) -> ScreenRecord:
    """输入一个完整头与body；调用方必须给出自己的资源上限，无协议默认值。"""
    if len(header) != 128:
        raise ValueError("screen header must be exactly 128 bytes")
    if header[4] != 0:
        raise ValueError("only the audited type=0 path is supported")
    if max_body < 16:
        raise ValueError("local body limit must allow at least one tag")
    n = int.from_bytes(header[:4], "little")
    e = int.from_bytes(header[28:32], "little")
    if len(body) != n or n > max_body:
        raise ValueError("body length mismatch or local limit exceeded")
    if e and e >= n:
        raise ValueError("nonzero tail length must be less than total body length")
    parts = (bytes(body[:n-e]), bytes(body[n-e:])) if e else (bytes(body),)
    if any(len(part) < 16 for part in parts):
        raise ValueError("local policy: every ChaCha segment must contain a full tag")
    return ScreenRecord(bytes(header), parts)
