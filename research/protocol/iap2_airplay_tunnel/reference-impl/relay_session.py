#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""中继停等状态机参考实现（设备侧）。

对应规范条款：
    spec/01 R-1.11   状态迁移
    spec/03 R-3.1…R-3.12
    spec/04 R-4.6    背压：链路不可发时停在 IDLE

设计要点（固件观察与本地策略分开）：
  * 一次只有一条请求在途是保守策略；最近命令字段本身不证明协议禁止并发；
  * 收到 `0x5266` 后**立刻**发 `0x5163`（固件 `0x1000849a4` 就是这么做的）；
  * 收到 `0x5265` 视为认证失败，直接关闭，不再重试（固件 `0x100084a40` → AuthState(1)）；
  * 仅外层 0x5264 缺少首参数时可选延时 1 ms 重读；内层格式错误不重读。
  * max_retry 默认 0（关闭），正数为本地上限，不是固件常量。
  * 仅明文 codec/事务模型；secure=True 只收紧长度，不实现 MFi4 AEAD。

用法：
    s = RelaySession()
    s.enqueue(2, b"hello")
    for msg in s.tick():            # 发出去
        ...
    events = s.on_message(reply)    # 收进来，返回事件列表
"""
from __future__ import annotations

from collections import deque
from time import monotonic

from tunnel_codec import (
    MSG_RELAY_FAIL,
    MSG_RELAY_OK,
    MSG_RELAY_REMOTE,
    CodecError,
    decode_info_update,
    decode_tunnel_data,
    encode_message,
    encode_request_info,
    encode_relay_read,
    encode_tunnel_data,
    parse_message,
    unwrap_relay,
    wrap_relay,
)

MAX_RELAY_DATA_PLAINTEXT = 0xFFFF - 25  # 0x5164 外层包裹后的 u16 长度
MAX_RELAY_DATA_SECURE = MAX_RELAY_DATA_PLAINTEXT - 16  # MFi4 AEAD +16 的保守值

IDLE = "IDLE"
WAIT_RESP = "WAIT_RESP"
CLOSED = "CLOSED"

MAX_RETRY = 0  # 本地默认关闭；不是固件的重试次数常量


class RelaySession:
    def __init__(self, type_enabled=None, max_retry: int = MAX_RETRY, secure: bool = False, clock=monotonic) -> None:
        if max_retry < 0:
            raise ValueError("max_retry must be non-negative")
        self.state = IDLE
        self.pending = None          # "data" | "read"
        self.queue = deque()         # [(type, payload)]
        self.type_enabled = type_enabled or (lambda t: t == 2)
        self.max_retry = max_retry
        self.max_data = MAX_RELAY_DATA_SECURE if secure else MAX_RELAY_DATA_PLAINTEXT
        self.retry = 0
        self.clock = clock
        self.retry_due = None
        self.events = []
        self.last_cmd = None         # 对应固件 [auth+0x1c]

    # ---------------- 发送侧 ----------------
    def enqueue(self, type_: int, data: bytes) -> bool:
        """R-3.2：type<3、槽位启用、数据非空、长度合法。"""
        if self.state == CLOSED:
            return False
        if not 0 <= type_ <= 2 or not self.type_enabled(type_):
            return False
        # 本地策略：拒绝空 bytes。固件 cbz x2 只检查对象指针非 NULL，
        # 不证明零长度 CFData 也被拒绝；格式 codec 仍允许零长度。
        if not data:
            return False
        if len(data) > self.max_data:
            return False
        self.queue.append((type_, bytes(data)))
        return True

    def tick(self) -> list:
        """返回本轮应发送的消息（0 或 1 条）。R-3.9 停等。"""
        if self.retry_due is not None and self.state != CLOSED:
            if self.clock() < self.retry_due:
                return []
            self.retry_due = None
            return self._read_request()
        if self.state in (CLOSED, WAIT_RESP):
            return []
        if self.queue:
            type_, data = self.queue.popleft()
            msg = wrap_relay(encode_tunnel_data(type_, data))
            self.pending = "data"
            self.last_cmd = 0x5164
            self.state = WAIT_RESP
            return [msg]
        # 空闲时不必主动轮询：固件是在 0x5266 之后才拉 0x5163（R-3.8）
        return []

    def _read_request(self) -> list:
        self.pending = "read"
        self.last_cmd = 0x5163
        self.state = WAIT_RESP
        return [encode_relay_read()]

    # ---------------- 接收侧 ----------------
    def on_message(self, buf: bytes) -> list:
        """处理一条顶层中继消息（R-3.4）。返回事件列表。"""
        if self.state == CLOSED:
            return [{"event": "closed"}]
        try:
            msg_id, params = parse_message(buf)
        except CodecError as exc:
            return [{"event": "error", "code": exc.code}]

        if msg_id == MSG_RELAY_FAIL:                      # R-3.7
            self.state = CLOSED
            self.pending = None
            self.retry_due = None
            self.queue.clear()
            return [{"event": "auth_failed"}]

        if msg_id == MSG_RELAY_OK:                        # R-3.8
            self.retry_due = None
            self.pending = None
            self.state = IDLE
            return [{"event": "relay_ok"}] + [
                {"event": "send", "hex": m.hex()}
                for m in self._read_request()
            ]

        if msg_id != MSG_RELAY_REMOTE:
            return [{"event": "error", "code": "E_UNKNOWN_MSG", "msg_id": msg_id}]

        self.pending = None
        self.state = IDLE
        self.retry_due = None
        # f_10008449c: GetFirstParam 返回 NULL 才走 1 ms 重读分支。
        # 有参数但值为空、内层缺 param1、解包失败均不进入此分支。
        if not params:
            if self.retry < self.max_retry:
                self.retry += 1
                self.retry_due = self.clock() + 0.001
                self.pending = "read"
                self.state = WAIT_RESP
                return [{"event": "retry_scheduled", "delay_ms": 1, "retry": self.retry}]
            return [{"event": "error", "code": "E_LEN"}]
        self.retry = 0
        try:
            inner = unwrap_relay(buf)
        except CodecError as exc:
            return [{"event": "error", "code": exc.code}]

        try:
            inner_id, _ = parse_message(inner)
        except CodecError as exc:
            return [{"event": "error", "code": exc.code}]

        if inner_id == 0x5503:                            # R-3.5 信息更新
            try:
                info = decode_info_update(inner)
            except CodecError as exc:
                return [{"event": "error", "code": exc.code}]
            return [{"event": "info", "info": info}]

        # 真实入站路径只把 0x5501 当作业务数据；0x5500 是设备侧出站
        # 形态，codec 允许解析它只是为了格式向量，不应在 relay 会话中投递。
        if inner_id == 0x5501:
            try:
                tunnel = decode_tunnel_data(inner)
            except CodecError as exc:
                return [{"event": "error", "code": exc.code}]
            self.retry = 0
            # f_10008449c: CFDataGetLength(unpacked) <= 5 被拒绝；
            # 对 0x5501，unpacked 是 param1 的 data，不是整个内层信封。
            if len(tunnel["data"]) <= 5:
                return [{"event": "error", "code": "E_SHORT"}]
            if not self.type_enabled(tunnel["type"]):
                return [{"event": "error", "code": "E_TYPE", "type": tunnel["type"]}]
            return [{"event": "data", "type": tunnel["type"], "hex": tunnel["data"].hex()}]

        return [{"event": "error", "code": "E_UNKNOWN_MSG", "msg_id": inner_id}]

    # ---------------- 能力协商 ----------------
    def on_capabilities(self, mask: int, *, action_pending: bool = False) -> list:
        """R-3.13：复现固件的 if/else 优先级。

        bit0 新置位时只发 0x5502；只有 bit0 本次未新置位时，bit2
        新置位才启用 type=2。不要把两个动作合并成同一次固件调用。
        """
        # 调用方提供固件 +0x58 闸门是否非零；这里只演示位处理，
        # 不冒充完整握手调度器，也不自行推断闸门何时清除。
        if action_pending:
            return []
        processed = getattr(self, "processed", 0)
        out = []
        if (mask & 1) and not (processed & 1):
            out.append({"event": "send", "hex": encode_request_info().hex()})
            processed |= 1
        elif (mask & 4) and not (processed & 4):
            out.append({"event": "enable_type", "type": 2})
            processed |= 4
        # 只把已执行动作的位记为 processed；未知位不应被伪装成已消费。
        self.processed = processed
        return out


# --------------------------------------------------------------------------
def self_test() -> bool:
    """最小闭环：发数据 → 0x5266 → 0x5163 → 0x5264(0x5501) → data 事件。"""
    s = RelaySession(type_enabled=lambda t: t == 2)

    # 1) 上层要发 type=2 的数据
    assert s.enqueue(2, b"hello"), "enqueue 失败"
    out1 = s.tick()
    assert len(out1) == 1, "应发出 0x5164"
    relay = out1[0]
    msg_id, params = parse_message(relay)
    assert msg_id == 0x5164 and len(params) == 1
    inner_id, _ = parse_message(params[0][1])
    assert inner_id == 0x5500, "内层应为 0x5500"

    # 2) 停等：响应到达前 tick 不得再发
    assert s.tick() == [], "停等被破坏"

    # 3) 对端回成功 → 立刻要 0x5163
    ev = s.on_message(encode_message(MSG_RELAY_OK))
    assert ev[0]["event"] == "relay_ok", ev
    assert any(e.get("event") == "send" for e in ev), "成功回调未发 0x5163"
    read_msg = bytes.fromhex([e for e in ev if e.get("event") == "send"][0]["hex"])
    assert parse_message(read_msg)[0] == 0x5163

    # 4) 合成六字节 data，满足 relay 投递长度门；不是合法 T56 握手向量。
    inner = encode_tunnel_data(2, b"\x77" * 6, msg_id=0x5501)
    reply = encode_message(MSG_RELAY_REMOTE, [(0, inner)])
    ev = s.on_message(reply)
    assert ev[0]["event"] == "data" and ev[0]["type"] == 2 and ev[0]["hex"] == "77" * 6, ev
    for size in (0, 1, 5):
        short = encode_tunnel_data(2, b"x" * size, msg_id=0x5501)
        ev = s.on_message(encode_message(MSG_RELAY_REMOTE, [(0, short)]))
        assert ev == [{"event": "error", "code": "E_SHORT"}], ev

    # 真实入站路径不把设备侧 0x5500 当作车机业务数据。
    outbound_inner = encode_tunnel_data(2, b"x", msg_id=0x5500)
    outbound_reply = encode_message(MSG_RELAY_REMOTE, [(0, outbound_inner)])
    ev = s.on_message(outbound_reply)
    assert ev[0]["event"] == "error" and ev[0]["code"] == "E_UNKNOWN_MSG", ev

    # 5) 失败即终止
    s.enqueue(2, b"x")
    s.tick()
    ev = s.on_message(encode_message(MSG_RELAY_FAIL))
    assert ev[0]["event"] == "auth_failed"
    assert s.state == CLOSED and s.tick() == [], "失败后仍在发送"

    # 6) 能力协商
    s2 = RelaySession()
    ev = s2.on_capabilities(1)
    assert any(e["event"] == "send" for e in ev), "bit0 未触发 0x5502"
    ev = s2.on_capabilities(5)
    assert any(e["event"] == "enable_type" for e in ev), "bit2 未启用 type2"
    # 固件是 if/else：从 0 一次收到 bit0+bit2 时先处理 bit0，不能同时启用 type2。
    s3 = RelaySession()
    ev = s3.on_capabilities(5)
    assert any(e["event"] == "send" for e in ev)
    assert not any(e["event"] == "enable_type" for e in ev)
    assert s3.processed == 1
    assert s3.on_capabilities(5, action_pending=True) == []
    ev = s3.on_capabilities(5)
    assert any(e["event"] == "enable_type" for e in ev)
    assert s3.processed == 5 and not s3.on_capabilities(5)
    s5 = RelaySession()
    assert s5.on_capabilities(4) == [{"event": "enable_type", "type": 2}]
    s4 = RelaySession(type_enabled=lambda t: t == 2)
    assert not s4.enqueue(2, b""), "空业务数据不得进入 relay 队列"
    # 无首参数才可重读；用可控时钟验证 1 ms，而非在处理函数里立即发送。
    now = [0.0]
    s6 = RelaySession(max_retry=1, clock=lambda: now[0])
    empty_outer = encode_message(MSG_RELAY_REMOTE)
    assert RelaySession().on_message(empty_outer) == [{"event": "error", "code": "E_LEN"}]
    assert s6.on_message(empty_outer)[0]["event"] == "retry_scheduled"
    assert s6.tick() == []
    now[0] = 0.001
    assert s6.tick() == [encode_relay_read()]
    assert s6.on_message(empty_outer) == [{"event": "error", "code": "E_LEN"}]
    for value in (b"", encode_message(0x5501, [(0, b"\x02")])):
        ev = s6.on_message(encode_message(MSG_RELAY_REMOTE, [(0, value)]))
        assert ev[0]["event"] == "error" and s6.retry_due is None, ev
    return True


if __name__ == "__main__":
    self_test()
    print("relay_session self-test: OK")
