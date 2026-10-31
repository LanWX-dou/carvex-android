#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""AirPlay RTP 参考解析/打包实现（只实现 spec/01 中有证据的部分）。

设计约束（来自 spec/01）：
  * 固定头 12 字节；序列号在 +2（大端 16 位）；时间戳在 +4（大端 32 位）；
  * payload type 在 +1，判定时 & 0x7f；
  * 元素区从 +12 开始，元素按首字节 bit7 分为 1 字节 / 4 字节两态；
  * 4 字节元素：W[31]=1, W[30:24]=B7, W[23:10]=D14, W[9:0]=L10（大端）；
  * 元素区只在 PT ∈ {0x61,0x68,0x69,0x6c,0x6d} 或 (PT==0x60 且合并模式) 时存在；
  * 子包时间戳 = 包头时间戳 − D14（最后一个子包不减）；
  * 接收路径长度门：长度 >= 1481 字节（0x5c9）拒绝；发送侧同值仅作为保守策略。

未实现（按 spec/01 §1.13–§1.15 的规定保持未定义）：
  * SSRC / marker / padding / CSRC；
  * 外层音频消息到实际网络包的映射；
  * 跨profile的 B7 / L10 语义（这里只做字段透传）。
"""
from __future__ import annotations

import struct
from dataclasses import dataclass, field

HEADER_LEN = 12
# 24A446 接收路径的长度门是 len >= 0x5c9；因此可接受长度最大为 1480。
# 这不是已证明的发送侧或跨版本线上最大包长。
MAX_PACKET = 1481
PT_WITH_EXT = frozenset({0x61, 0x68, 0x69, 0x6C, 0x6D})
PT_LEGACY_MERGED = 0x60


def has_extended_header(payload_type: int, merged: bool) -> bool:
    """spec/01 R-1.9：元素区是否存在。"""
    pt = payload_type & 0x7F
    if pt in PT_WITH_EXT:
        return True
    return pt == PT_LEGACY_MERGED and merged


def pack_element(b7: int, d14: int, l10: int) -> bytes:
    """spec/01 R-1.7 的打包方向；返回 4 字节大端。"""
    b7 &= 0x7F
    d14 &= 0x3FFF
    l10 &= 0x3FF
    w = 0x80000000 | (b7 << 24) | (d14 << 10) | l10
    return struct.pack(">I", w)


def unpack_element(raw: bytes) -> tuple[int, int, int]:
    """spec/01 R-1.7 的解包方向；raw 为 4 字节大端。"""
    if len(raw) != 4:
        raise ValueError("4 字节元素长度错误")
    w = struct.unpack(">I", raw)[0]
    if not w & 0x80000000:
        raise ValueError("bit31 必须为 1")
    b7 = (w >> 24) & 0x7F
    d14 = (w >> 10) & 0x3FFF
    l10 = w & 0x3FF
    return b7, d14, l10


def unpack_element_internal(raw: bytes) -> int:
    """spec/01 R-1.11 的内部次序：(L10 << 22) | (D14 << 8) | byte。"""
    b7, d14, l10 = unpack_element(raw)
    return (l10 << 22) | (d14 << 8) | (0x80 | b7)


def remap_pt_for_merged(payload_type: int) -> int:
    """spec/07 R-7.2 / analysis A03.3：合并模式的 PT 改写。"""
    table = {0x60: 0x61, 0x64: 0x68, 0x65: 0x69, 0x6A: 0x6C}
    return table.get(payload_type, payload_type)


def header_length(element_count: int, merged: bool = True) -> int:
    """兼容旧名称：装配函数长度出参 = 4n+11 / 10，不是通用 RTP 头长。"""
    if not merged:
        return 10
    return 4 * element_count + 11


def observed_decrypt_span(stored_end: int, payload_type: int, merged: bool,
                          element_count: int) -> tuple[int, int]:
    """R-9.2 的内部读路径算术模型，返回 (缓冲相对偏移, 调用长度)。

    stored_end 是内部 +0x5c0 值，不接受它已等于线上包长的假设。
    不调用解密器，也不是可用的线上组包算法；OPEN-RTP-8/14 仍保留。
    下溢/非法计数拒绝是本地防御策略，不冒充原函数已有边界检查。
    """
    extra = 0
    if has_extended_header(payload_type, merged):
        if not 1 <= element_count <= 0x3FFFFFFF:
            raise ValueError("内部元素计数超出算术模型范围")
        extra = 4 * element_count - 3
    offset = HEADER_LEN + extra
    if stored_end < offset:
        raise ValueError("内部结束坐标小于解密起点")
    return offset, stored_end - offset


@dataclass
class PhonyPacket:
    """合成12B头坐标视图，不是已验证的网络适配器。

    element_count若给出是含终止元素的扫描上限，不代替线上终止符。
    merged控制PT=0x60的模式门；其余扩展PT仍按已证集合判定。
    """

    raw: bytes
    element_count: int | None = None
    merged: bool = True
    payload_type: int = field(init=False)
    sequence: int = field(init=False)
    timestamp: int = field(init=False)
    elements: list[tuple[int, int, int]] = field(default_factory=list)
    payload: bytes = field(default=b"")

    def __post_init__(self) -> None:
        if len(self.raw) < HEADER_LEN:
            raise ValueError("包短于 12 字节")
        if len(self.raw) >= MAX_PACKET:
            raise ValueError("合成模型保守长度限制1481；不是已证线上MTU")
        if self.element_count is not None and self.element_count < 1:
            raise ValueError("元素扫描上限必须为正数")
        self.payload_type = self.raw[1] & 0x7F
        self.sequence = struct.unpack(">H", self.raw[2:4])[0]
        self.timestamp = struct.unpack(">I", self.raw[4:8])[0]
        off = HEADER_LEN
        if has_extended_header(self.payload_type, merged=self.merged):
            while True:
                if self.element_count is not None and len(self.elements) >= self.element_count:
                    raise ValueError("达到扫描上限但未见终止元素")
                if off >= len(self.raw):
                    raise ValueError("缺少终止元素")
                first = self.raw[off]
                if not first & 0x80:
                    # 1 字节元素：既是元素，也是"元素列表结束"的信号
                    self.elements.append((first & 0x7F, 0, 0))
                    off += 1
                    break
                if off + 4 > len(self.raw):
                    raise ValueError("4字节元素被截断")
                self.elements.append(unpack_element(self.raw[off:off + 4]))
                off += 4
        self.payload = self.raw[off:]

    def sub_packet_timestamps(self) -> list[int]:
        """spec/01 R-1.8：最后一个子包不减。"""
        if not self.elements:
            return [self.timestamp]
        out = []
        for i, (_b7, d14, _l10) in enumerate(self.elements):
            out.append(self.timestamp if i == len(self.elements) - 1
                       else (self.timestamp - d14) & 0xFFFFFFFF)
        return out


def build_packet(payload_type: int, sequence: int, timestamp: int,
                 elements: list[tuple[int, int, int]], payload: bytes,
                 merged: bool = True) -> bytes:
    """仅构造合成12B头测试夹具，不保证车机接受。

    elements是旧载荷4B描述符；自动补当前PT的1B终止元素。
    payload是已串接的音频数据；不校验其与描述符的对应关系。
    """
    pt = remap_pt_for_merged(payload_type) if merged else payload_type
    head = bytearray(HEADER_LEN)
    head[0] = 0x80                      # 未定义字段：按 spec/01 R-1.13 保留默认形态
    head[1] = pt & 0x7F                 # R-1.4
    head[2:4] = struct.pack(">H", sequence & 0xFFFF)      # R-1.2
    head[4:8] = struct.pack(">I", timestamp & 0xFFFFFFFF)  # R-1.3
    with_elements = has_extended_header(pt, merged)
    if elements and not with_elements:
        raise ValueError("当前PT/模式不允许元素区")
    for b7, d14, l10 in elements:
        if not (0 <= b7 <= 0x7F and 0 <= d14 <= 0x3FFF and 0 <= l10 <= 0x3FF):
            raise ValueError("元素字段越界；组包不能静默截断")
    body = (b"".join(pack_element(*e) for e in elements) + bytes([payload_type & 0x7F])
            if with_elements else b"")
    pkt = bytes(head) + body + payload
    if len(pkt) >= MAX_PACKET:
        raise ValueError("合成模型保守长度限制1481；不是已证线上MTU")
    return pkt


def self_test() -> None:
    vec = [
        (0x05, 0x2ABC, 0x155, "85AAF155"),
        (0x00, 0x0000, 0x000, "80000000"),
        (0x7F, 0x3FFF, 0x3FF, "FFFFFFFF"),
        (0x01, 0x0001, 0x001, "81000401"),
        (0x12, 0x0005, 0x2AA, "920016AA"),
    ]
    for b7, d14, l10, hexs in vec:
        raw = pack_element(b7, d14, l10)
        assert raw.hex().upper() == hexs, (raw.hex().upper(), hexs)
        assert unpack_element(raw) == (b7, d14, l10)
    assert header_length(0) == 11
    assert header_length(3) == 23
    assert header_length(0, merged=False) == 10
    assert has_extended_header(0x61, merged=False)
    assert not has_extended_header(0x60, merged=False)
    assert has_extended_header(0x60, merged=True)
    assert remap_pt_for_merged(0x64) == 0x68
    assert remap_pt_for_merged(0x6D) == 0x6D
    pkt = build_packet(0x64, 0x1234, 0x1000,
                       [(0x05, 0x2ABC, 0x155), (0x06, 0, 0x010)], b"\xaa" * 8)
    p = PhonyPacket(pkt, element_count=3)
    assert p.payload_type == 0x68, hex(p.payload_type)
    assert p.sequence == 0x1234
    assert p.timestamp == 0x1000
    assert p.payload == b"\xaa" * 8
    assert p.sub_packet_timestamps() == [(0x1000 - 0x2ABC) & 0xFFFFFFFF, 0x1000, 0x1000]
    marked = bytearray(pkt)
    marked[1] |= 0x80
    assert PhonyPacket(bytes(marked), element_count=3).payload_type == 0x68
    # 最后元素即使 D14 非零，最后子包仍走保留时间戳分支。
    nonzero_last = build_packet(0x64, 1, 100, [(0, 7, 0), (0, 9, 0)], b"x")
    # 最后一个4B元素并非最后子包：其后还有1B当前元素。
    assert PhonyPacket(nonzero_last, element_count=3).sub_packet_timestamps() == [93, 91, 100]
    # 独立检查时间戳helper的末项分支，不把该合成状态当有效线上元素列表。
    p.elements = [(0, 7, 0), (0, 9, 0)]
    p.timestamp = 100
    assert p.sub_packet_timestamps() == [93, 100]
    assert observed_decrypt_span(100, 0x61, False, 3) == (21, 79)
    assert observed_decrypt_span(100, 0x60, False, 3) == (12, 88)
    assert observed_decrypt_span(100, 0x60, True, 3) == (21, 79)

    # 1 字节元素即终止符：其后再无元素，剩余全是载荷
    tail = HEADER_LEN + 4 + 1
    pkt2 = build_packet(0x61, 1, 7, [], b"")[:0] + bytes([0x00] * HEADER_LEN)
    pkt2 = bytearray(pkt2)
    pkt2[1] = 0x61
    pkt2 = bytes(pkt2) + pack_element(0x07, 0x10, 0x20) + bytes([0x00]) + b"\xbb\xcc"
    p2 = PhonyPacket(pkt2)
    assert p2.elements == [(0x07, 0x10, 0x20), (0x00, 0, 0)], p2.elements
    assert p2.payload == b"\xbb\xcc", p2.payload
    assert tail == HEADER_LEN + 5
    # 必须自动扫描到终止符，不能靠外部count掩盖损坏布局。
    assert PhonyPacket(pkt).payload == b"\xaa" * 8
    for raw, limit in ((pkt[:HEADER_LEN], None),
                       (pkt[:HEADER_LEN] + b"\x80", None),
                       (pkt, 2)):
        try:
            PhonyPacket(raw, element_count=limit)
        except ValueError:
            pass
        else:
            raise AssertionError("截断/缺终止符/上限反例未拒绝")
    plain = build_packet(0x60, 1, 2, [], b"\x80abc", merged=False)
    assert PhonyPacket(plain, merged=False).payload == b"\x80abc"
    assert build_packet(0x64, 1, 2, [], b"x")[12:] == b"\x64x"


if __name__ == "__main__":
    self_test()
    print("rtp_parser self_test: ok")
