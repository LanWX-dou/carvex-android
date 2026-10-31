#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""RFC 2198 风格 RED 描述符解析与序列号/时间戳还原。

固件依据（原 24A446，地址见 analysis/03-red.md）：

* 4 字节冗余块头按大端读入 W：
  offset(delta) = (W >> 10) & 0x3fff，length = W & 0x3ff，F = bit31。
  0x251ace464 rev / 0x251ace46c lsr #2 / 0x251ace470 and #0x3fff00 / 0x251ace474 lsl #22
* 主块头 1 字节：bit7 = 0，低 7 位是 payload type。0x251ace484 tst #0x80 / csinc 4,1
* 冗余块在前、主块在后；描述符总长 = 4*blocks-3。0x2519c348c（span 计算）
* 块序列号 = (outerSeq + index - (blocks-1)) & 0xFFFF；
  块时间戳 = outerTs - delta（主块用 outerTs）。RED-03 / MR02

本模块只做结构解析与推导，不做时间戳时钟换算、不去重、不做丢包恢复策略。
"""

from __future__ import annotations

MAX_BLOCKS = 16  # 本地实现上限（RED-05 的本地约束，不是固件上限）

# 需要 RED 描述符的 PT。96 只有在 maxPackets>1 的上下文中才按 RED 解析（RED-02）。
RED_PTS = frozenset({97, 104, 105, 108, 109})


class RedError(ValueError):
    def __init__(self, code: str, detail: str = "") -> None:
        super().__init__(code)
        self.code = code
        self.detail = detail


def needs_red(pt: int, max_packets: int = 1) -> bool:
    if pt == 96:
        return max_packets > 1
    return pt in RED_PTS


def parse_descriptors(payload: bytes) -> dict:
    """Parse only the clear descriptor prefix; never classify the trailing bytes.

    May run before authentication solely to locate the candidate ciphertext.
    Returned lengths/metadata are untrusted until the selected profile validates them.
    """
    if not payload:
        raise RedError("RED_EMPTY")

    headers = []
    off = 0
    while True:
        if len(headers) >= MAX_BLOCKS:
            raise RedError("RED_TOO_MANY_BLOCKS", f">={MAX_BLOCKS}")
        if off >= len(payload):
            raise RedError("RED_TRUNCATED_HEADER", f"off={off}")
        b0 = payload[off]
        if b0 & 0x80:
            if off + 4 > len(payload):
                raise RedError("RED_TRUNCATED_HEADER", f"off={off}")
            word = int.from_bytes(payload[off: off + 4], "big")
            headers.append({
                "pt": b0 & 0x7F,
                "delta": (word >> 10) & 0x3FFF,
                "length": word & 0x3FF,
                "primary": False,
            })
            off += 4
        else:
            headers.append({"pt": b0 & 0x7F, "delta": 0, "length": 0, "primary": True})
            off += 1
            break

    span = off
    blocks = len(headers)
    if span != 4 * blocks - 3:
        raise RedError("RED_BAD_SPAN", f"span={span} blocks={blocks}")

    return {"span": span, "blocks": blocks, "headers": headers}


def parse_red(payload: bytes, outer_seq: int, outer_timestamp: int) -> dict:
    """Split descriptors + CLEAR audio blocks (authenticated or synthetic).

    No RTP/message header or crypto trailer is included. Do not pass ciphertext
    here and publish the sliced blocks as decoded audio. Sequence inference uses
    the documented consecutive-block model, not a universal RFC2198 guarantee.
    """
    parsed = parse_descriptors(payload)
    span, blocks, headers = parsed["span"], parsed["blocks"], parsed["headers"]

    if len(payload) < span:
        raise RedError("RED_TRUNCATED_BODY", f"len={len(payload)} span={span}")

    # 主块头只有 1 字节，长度不入线：主块取余量（RED-02 "primary takes remainder"）。
    available = len(payload) - span
    redundant_total = sum(h["length"] for h in headers if not h["primary"])
    if redundant_total > available:
        raise RedError("RED_LENGTH_MISMATCH",
                       f"declared={redundant_total} available={available}")
    headers[-1]["length"] = available - redundant_total

    out = []
    cursor = span
    for index, header in enumerate(headers):
        primary = header["primary"]
        seq = (outer_seq + index - (blocks - 1)) & 0xFFFF
        timestamp = outer_timestamp if primary else (outer_timestamp - header["delta"]) & 0xFFFFFFFF
        out.append({
            "index": index,
            "primary": primary,
            "pt": header["pt"],
            "delta": header["delta"],
            "length": header["length"],
            "seq": seq,
            "timestamp": timestamp,
            "offset": cursor,
            "data": payload[cursor: cursor + header["length"]],
        })
        cursor += header["length"]

    return {"span": span, "blocks": blocks, "entries": out}
