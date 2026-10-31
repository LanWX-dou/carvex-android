#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""iAP2 消息编解码的最小参考实现（仅用于自测向量，不是产品代码）。

结构来源（见 analysis/01、sess/R-3.x）：
  6 字节消息头：0x40 0x40 | u16 总长(BE, 含头) | u16 消息 ID(BE)
  参数：u16 参数总长(BE, 含 4 字节参数头) | u16 参数 ID(BE) | 值

本模块不做任何协议语义判断，只负责字节 <-> 结构。
"""

from __future__ import annotations

import struct

MAGIC = b"\x40\x40"
HEADER_LEN = 6
PARAM_HEADER_LEN = 4


def encode_message(msg_id: int, params: list[dict]) -> bytes:
    body = b""
    for p in params:
        body += encode_param(p)
    total = HEADER_LEN + len(body)
    return MAGIC + struct.pack(">HH", total, msg_id) + body


def encode_param(p: dict) -> bytes:
    kind = p["type"]
    if kind == "u8":
        value = _encode_uint(p["value"], 8, "B")
    elif kind == "u16":
        value = _encode_uint(p["value"], 16, "H")
    elif kind == "u32":
        value = _encode_uint(p["value"], 32, "I")
    elif kind == "empty":
        value = b""
    elif kind == "data":
        value = bytes.fromhex(p["value"])
    else:
        raise ValueError(f"unknown param type: {kind}")
    total = PARAM_HEADER_LEN + len(value)
    return struct.pack(">HH", total, p["id"]) + value


def _encode_uint(value: int, bits: int, fmt: str) -> bytes:
    # Local validation: never silently truncate caller data.
    if type(value) is not int or not 0 <= value < (1 << bits):
        raise ValueError(f"invalid u{bits}: {value!r}")
    return struct.pack(">" + fmt, value)


def decode_message(data: bytes) -> dict:
    if len(data) < HEADER_LEN or data[:2] != MAGIC:
        raise ValueError("bad magic")
    total, msg_id = struct.unpack(">HH", data[2:6])
    if total != len(data):
        raise ValueError(f"length mismatch: header={total} actual={len(data)}")
    params = []
    off = HEADER_LEN
    while off < len(data):
        if off + PARAM_HEADER_LEN > len(data):
            raise ValueError("truncated param header")
        plen, pid = struct.unpack(">HH", data[off : off + PARAM_HEADER_LEN])
        if plen < PARAM_HEADER_LEN or off + plen > len(data):
            raise ValueError(f"bad param length {plen}")
        value = data[off + PARAM_HEADER_LEN : off + plen]
        params.append({"id": pid, "len": plen, "value": value.hex()})
        off += plen
    return {"msg_id": msg_id, "length": total, "params": params}


REQUIRED_LEN = {"empty": 4, "u8": 5, "u16": 6, "u32": 8}


def param_total_len(param: dict) -> int:
    kind = param["type"]
    if kind == "u8":
        vlen = 1
    elif kind == "u16":
        vlen = 2
    elif kind == "u32":
        vlen = 4
    elif kind == "empty":
        vlen = 0
    elif kind == "data":
        vlen = len(bytes.fromhex(param["value"]))
    else:
        raise ValueError(f"unknown param type: {kind}")
    return PARAM_HEADER_LEN + vlen


def wire_len_ok(wire: bytes, kind: str) -> bool:
    """完整单 TLV 长度检查；不代替消息 schema 或嵌套父边界检查。

    empty 对应已过通用遍历器的 0x100067f3c 条件；data 可空。
    """
    if kind not in REQUIRED_LEN and kind != "data":
        raise ValueError(f"unknown param type: {kind}")
    if len(wire) < PARAM_HEADER_LEN:
        return False
    plen = struct.unpack(">H", wire[:2])[0]
    if plen != len(wire):
        return False
    if kind in REQUIRED_LEN:
        return plen == REQUIRED_LEN[kind]
    return plen >= PARAM_HEADER_LEN


def _self_test() -> None:
    # Independent literal bytes, not generated expected values.
    empty = bytes.fromhex("00040001")
    assert wire_len_ok(empty, "empty") and wire_len_ok(empty, "data")
    assert not wire_len_ok(bytes.fromhex("000300"), "empty")
    assert not wire_len_ok(bytes.fromhex("0005000100"), "empty")
    assert wire_len_ok(bytes.fromhex("0008001100000001"), "u32")
    for width in range(0, 11):
        wire = width.to_bytes(2, "big") + b"\0" * max(0, width - 2)
        for kind, expected in REQUIRED_LEN.items():
            assert wire_len_ok(wire, kind) == (width == expected)
    for kind, bits in (("u8", 8), ("u16", 16), ("u32", 32)):
        for val in (-1, 1 << bits, True, 1.5):
            try:
                encode_param({"id": 0, "type": kind, "value": val})
            except ValueError:
                pass
            else:
                raise AssertionError("out-of-range value accepted")
        for val in (0, (1 << bits) - 1):
            assert wire_len_ok(encode_param({"id": 0, "type": kind, "value": val}), kind)
    try:
        wire_len_ok(empty, "unknown")
    except ValueError:
        pass
    else:
        raise AssertionError("unknown type accepted")
    # Nested group carries a 4-byte empty item, not a 1-byte placeholder.
    raw = bytes.fromhex("4040000e50000008000000040001")
    parsed = decode_message(raw)
    assert parsed["params"][0]["value"] == "00040001"
    assert encode_message(0x5000, [{"id": 0, "type": "data", "value": "00040001"}]) == raw
    for raw in (bytes.fromhex("4040000a500000030000"),
                bytes.fromhex("4040000a500000050000")):
        try:
            decode_message(raw)
        except ValueError:
            pass
        else:
            raise AssertionError("bad TLV accepted")


if __name__ == "__main__":  # 手工自测
    msg = encode_message(0x6800, [{"id": 0, "type": "u16", "value": 1},
                                  {"id": 3, "type": "u8", "value": 1}])
    print(msg.hex())
    print(decode_message(msg))
    print(wire_len_ok(msg[6:12], "u16"), wire_len_ok(msg[12:], "u8"))
