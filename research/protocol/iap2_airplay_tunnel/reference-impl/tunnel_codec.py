#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""iAP2 隧道信封参考实现（设备侧）。

只做线格式，不做链路/会话：输入输出都是 iAP2 **消息**字节（以 `40 40` 开头）。

对应规范：
    spec/02-wire-format.md      R-2.1 … R-2.16
    spec/03-relay-transaction.md R-3.1 … R-3.8

用法：
    from tunnel_codec import encode_tunnel_data, decode_tunnel_data
    encode_tunnel_data(2, b"\xde\xad\xbe\xef").hex()
"""
from __future__ import annotations

SOM = b"\x40\x40"

# 设备侧发送
MSG_RELAY_READ = 0x5163        # 0x5163 请求重发
MSG_RELAY_DATA = 0x5164        # 0x5164 设备发出的隧道数据
MSG_TUNNEL_DATA_TX = 0x5500    # 信封（设备 → 车机）
MSG_REQUEST_INFO = 0x5502      # 请求配件信息

# 设备侧接收
MSG_TUNNEL_DATA_RX = 0x5501    # 信封（车机 → 设备）
MSG_INFO_UPDATE = 0x5503       # 配件信息更新
MSG_RELAY_REMOTE = 0x5264      # 对端发来的隧道数据
MSG_RELAY_FAIL = 0x5265        # 失败
MSG_RELAY_OK = 0x5266          # 成功

MAX_DATA = 0xFFFF - 15         # 单条信封最大数据（R-2.13）

PARAM_TYPE = 0x0000
PARAM_DATA = 0x0001
PARAM_CAPABILITIES = 0x00F2

INFO_FIELDS = {0: "name", 1: "model", 2: "manufacturer", 3: "serial", 4: "firmware"}


class CodecError(Exception):
    """带错误码的编解码失败。"""

    def __init__(self, code: str, detail: str = "") -> None:
        super().__init__("%s: %s" % (code, detail) if detail else code)
        self.code = code


# --------------------------------------------------------------------------
# 基础 TLV
# --------------------------------------------------------------------------

def _u16(value: int) -> bytes:
    return value.to_bytes(2, "big")


def encode_param(param_id: int, value: bytes) -> bytes:
    total = 4 + len(value)
    if total > 0xFFFF:
        raise CodecError("E_LEN", "param too long: %d" % total)
    return _u16(total) + _u16(param_id) + value


def encode_message(msg_id: int, params=()) -> bytes:
    body = b"".join(encode_param(pid, val) for pid, val in params)
    total = 6 + len(body)
    if total > 0xFFFF:
        raise CodecError("E_LEN", "message too long: %d" % total)
    return SOM + _u16(total) + _u16(msg_id) + body


def parse_message(buf: bytes) -> tuple:
    """返回 (msg_id, [(param_id, value), ...])；失败抛 CodecError。"""
    if len(buf) < 6:
        raise CodecError("E_SHORT", "need >= 6 bytes, got %d" % len(buf))
    if buf[0:2] != SOM:
        raise CodecError("E_SOM", "bad start marker %s" % buf[0:2].hex())
    declared = int.from_bytes(buf[2:4], "big")
    if declared < 6:
        raise CodecError("E_SHORT", "declared length %d < 6" % declared)
    if declared != len(buf):
        raise CodecError("E_LEN", "declared %d != actual %d" % (declared, len(buf)))
    msg_id = int.from_bytes(buf[4:6], "big")
    params = []
    off = 6
    while off < declared:
        if off + 4 > declared:
            raise CodecError("E_LEN", "truncated param header at %d" % off)
        plen = int.from_bytes(buf[off:off + 2], "big")
        if plen < 4 or off + plen > declared:
            raise CodecError("E_LEN", "bad param length %d at %d" % (plen, off))
        pid = int.from_bytes(buf[off + 2:off + 4], "big")
        params.append((pid, buf[off + 4:off + plen]))
        off += plen
    return msg_id, params


# --------------------------------------------------------------------------
# 信封
# --------------------------------------------------------------------------

def encode_tunnel_data(type_: int, data: bytes, msg_id: int = MSG_TUNNEL_DATA_TX) -> bytes:
    """编码 0x5500（默认）或 0x5501 信封。"""
    if not 0 <= type_ <= 2:
        raise CodecError("E_TYPE", "type %r out of range 0..2" % (type_,))
    if len(data) > MAX_DATA:
        raise CodecError("E_LEN", "data %d > %d" % (len(data), MAX_DATA))
    if msg_id not in (MSG_TUNNEL_DATA_TX, MSG_TUNNEL_DATA_RX):
        raise CodecError("E_UNKNOWN_MSG", "0x%04X is not a tunnel message" % msg_id)
    return encode_message(msg_id, [(PARAM_TYPE, bytes([type_])), (PARAM_DATA, data)])


def decode_tunnel_data(buf: bytes) -> dict:
    """解码 0x5501（也容忍 0x5500，见 R-1.6）。

    返回 {"msg_id", "type", "data"}；缺 param1 抛 E_EMPTY_PAYLOAD（R-3.11）。
    """
    msg_id, params = parse_message(buf)
    if msg_id not in (MSG_TUNNEL_DATA_TX, MSG_TUNNEL_DATA_RX):
        raise CodecError("E_UNKNOWN_MSG", "0x%04X" % msg_id)
    type_ = 0
    data = None
    for pid, value in params:
        if pid == PARAM_TYPE:
            if len(value) < 1:
                raise CodecError("E_LEN", "empty type param")
            type_ = value[0]
        elif pid == PARAM_DATA:
            data = value          # 后者覆盖前者（R-2.3）
    if type_ > 2:
        raise CodecError("E_TYPE", "type %d out of range" % type_)
    if data is None:
        raise CodecError("E_EMPTY_PAYLOAD", "no param 1")
    return {"msg_id": msg_id, "type": type_, "data": data}


def encode_request_info() -> bytes:
    return encode_message(MSG_REQUEST_INFO)


def decode_info_update(buf: bytes) -> dict:
    """解码 0x5503；未知 param 忽略（R-2.2）。"""
    msg_id, params = parse_message(buf)
    if msg_id != MSG_INFO_UPDATE:
        raise CodecError("E_UNKNOWN_MSG", "0x%04X" % msg_id)
    out = {"msg_id": msg_id, "params": {}}
    for pid, value in params:
        if pid in INFO_FIELDS:
            out[INFO_FIELDS[pid]] = value.rstrip(b"\x00").decode("utf-8", "replace")
        elif pid == PARAM_CAPABILITIES:
            if len(value) != 8:
                raise CodecError("E_LEN", "capabilities must be 8 bytes")
            out["capabilities"] = int.from_bytes(value, "big")
        else:
            out["params"].setdefault(pid, b"")
            out["params"][pid] = value
    return out


# --------------------------------------------------------------------------
# 中继（0x5163 / 0x5164 / 0x5264）
# --------------------------------------------------------------------------

def wrap_relay(inner: bytes) -> bytes:
    """把内层消息字节包成 0x5164（R-1.7）。"""
    return encode_message(MSG_RELAY_DATA, [(0x0000, inner)])


def unwrap_relay(buf: bytes) -> bytes:
    """从 0x5264 取出第一个参数的内层消息字节。

    固件处理函数调用 ``GetFirstParam``，没有证明会拒绝后续参数；因此
    这里只要求至少一个参数并忽略其余参数。发送侧 0x5164 仍按 R-1.7
    生成单一 param0。
    """
    msg_id, params = parse_message(buf)
    if msg_id != MSG_RELAY_REMOTE:
        raise CodecError("E_UNKNOWN_MSG", "0x%04X is not 0x5264" % msg_id)
    if not params:
        raise CodecError("E_LEN", "0x5264 has no param0")
    return params[0][1]


def encode_relay_read() -> bytes:
    return encode_message(MSG_RELAY_READ)


# --------------------------------------------------------------------------
# 测试向量驱动
# --------------------------------------------------------------------------

def run_vector(vec: dict) -> dict:
    """执行一条测试向量，返回 {"ok": ...} 或 {"error": code}。"""
    op = vec["op"]
    args = vec.get("args", {})
    try:
        if op == "encode_tunnel_data":
            data = bytes.fromhex(args.get("data", ""))
            msg_id = args.get("msg_id", MSG_TUNNEL_DATA_TX)
            return {"ok": {"hex": encode_tunnel_data(args["type"], data, msg_id).hex()}}
        if op == "decode_tunnel_data":
            r = decode_tunnel_data(bytes.fromhex(args["hex"]))
            return {"ok": {"msg_id": r["msg_id"], "type": r["type"],
                           "data": r["data"].hex()}}
        if op == "encode_request_info":
            return {"ok": {"hex": encode_request_info().hex()}}
        if op == "decode_info_update":
            r = decode_info_update(bytes.fromhex(args["hex"]))
            r = dict(r)
            for pid, val in list(r["params"].items()):
                r["params"][pid] = val.hex()
            return {"ok": r}
        if op == "wrap_relay":
            inner = bytes.fromhex(args["inner"])
            return {"ok": {"hex": wrap_relay(inner).hex()}}
        if op == "unwrap_relay":
            return {"ok": {"inner": unwrap_relay(bytes.fromhex(args["hex"])).hex()}}
        if op == "encode_relay_read":
            return {"ok": {"hex": encode_relay_read().hex()}}
        raise CodecError("E_OP", "unknown op %r" % op)
    except CodecError as exc:
        return {"error": exc.code}


if __name__ == "__main__":
    import json
    import pathlib
    import sys
    here = pathlib.Path(__file__).resolve().parent
    vecs = json.loads((here / "test_vectors.json").read_text(encoding="utf-8"))
    bad = 0
    for v in vecs["vectors"]:
        got = run_vector(v)
        if got != v["expect"]:
            bad += 1
            print("FAIL %-6s %s" % (v["id"], v["note"]))
            print("  expect", json.dumps(v["expect"], ensure_ascii=False))
            print("  got   ", json.dumps(got, ensure_ascii=False))
    print("%d/%d vectors passed" % (len(vecs["vectors"]) - bad, len(vecs["vectors"])))
    sys.exit(1 if bad else 0)
