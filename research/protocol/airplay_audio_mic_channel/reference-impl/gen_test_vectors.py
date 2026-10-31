#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成 reference-impl/test_vectors.json。

向量全部由本目录实现自洽生成，不含任何真实抓包；它们只锁定「结构契约」，
不证明车机行为。改动实现后重新运行本脚本并复核 diff。
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

sys.dont_write_bytecode = True

import audio_depacketizer as rtp
import red_decoder as red

HERE = Path(__file__).resolve().parent


def hdr(pt: int, seq: int, ts: int, ssrc: int = 0x11223344, b0: int = 0x80,
        marker: int = 0) -> bytes:
    return bytes([b0, (marker << 7) | pt]) + seq.to_bytes(2, "big") + \
        ts.to_bytes(4, "big") + ssrc.to_bytes(4, "big")


def red_head(blocks, deltas=None):
    """blocks: [(pt, delta, length, primary)]"""
    out = bytearray()
    for pt, delta, length, primary in blocks:
        if primary:
            out.append(pt & 0x7F)
        else:
            word = (1 << 31) | ((pt & 0x7F) << 24) | ((delta & 0x3FFF) << 10) | (length & 0x3FF)
            out += word.to_bytes(4, "big")
    return bytes(out)


def main() -> int:
    cases = []

    # 1. 基本头解析
    pkt = hdr(100, 0x1234, 0x0000BEEF) + bytes(range(8))
    cases.append({
        "name": "rtp_basic_main",
        "kind": "rtp",
        "note": "PT100=main，普通 12 字节头 + 8 字节负载",
        "hex": pkt.hex(),
        "expect": {"pt": 100, "name": "main", "seq": 0x1234,
                   "timestamp": 0x0000BEEF, "ssrc": 0x11223344,
                   "marker": 0, "version": 2},
    })

    # 2. marker 位不参与查表
    pkt = hdr(100, 1, 2, marker=1)
    cases.append({
        "name": "rtp_marker_ignored_for_pt",
        "kind": "rtp",
        "note": "第二字节 0xE4：M=1 且 PT=100，查表用低 7 位",
        "hex": pkt.hex(),
        "expect": {"pt": 100, "marker": 1},
    })

    # 3. 版本字节越界
    pkt = bytes([0xC0, 100]) + bytes(10)
    cases.append({"name": "rtp_bad_version_byte", "kind": "rtp_reject",
                  "note": "首字节 0xC0 超出 0x80..0xBF", "hex": pkt.hex(),
                  "expect_error": "BAD_VERSION_BYTE"})

    # 4. 发送侧专用 PT 不接收
    pkt = hdr(101, 1, 2)
    cases.append({"name": "rtp_sendonly_pt_101", "kind": "rtp_reject",
                  "note": "PT101=alt 只发送，接收掩码不含 bit5", "hex": pkt.hex(),
                  "expect_error": "PT_NOT_RECEIVABLE"})

    pkt = hdr(105, 1, 2)
    cases.append({"name": "rtp_sendonly_pt_105", "kind": "rtp_reject",
                  "note": "PT105=ared 只发送", "hex": pkt.hex(),
                  "expect_error": "PT_NOT_RECEIVABLE"})

    # 5. 未知 PT
    pkt = hdr(110, 1, 2)
    cases.append({"name": "rtp_unknown_pt_110", "kind": "rtp_reject",
                  "note": "PT110 不在表内", "hex": pkt.hex(),
                  "expect_error": "UNKNOWN_PT"})

    # 6. 加密记录切片
    cipher = bytes.fromhex("deadbeef00112233aabb")
    tag = bytes(range(16))
    nonce = bytes.fromhex("0102030405060708")
    pkt = rtp.build_message(7, 8, 0x11223344, cipher + tag + nonce)
    cases.append({
        "name": "record_split_main",
        "kind": "record",
        "note": "合成M消息：10B头+10B密文+tag16+nonce8；非网络包或真实加密向量",
        "hex": pkt.hex(),
        "span": 0, "trailer_layout": "tag16_nonce8",
        "expect": {"ciphertext": cipher.hex(), "tag": tag.hex(),
                   "nonce": nonce.hex(), "aad": pkt[2:10].hex(),
                   "overhead": 24},
    })

    # 7. 记录过短
    pkt = rtp.build_message(1, 1, 0, bytes(24))
    cases.append({"name": "record_short", "kind": "record_reject",
                  "note": "剩余 24 字节全部是开销，密文为空", "hex": pkt.hex(),
                  "span": 0, "trailer_layout": "tag16_nonce8", "expect_error": "SHORT_RECORD"})

    # 8. 两块 RED：1 冗余 + 主块
    body = red_head([(100, 5, 3, False), (100, 0, 4, True)]) + b"abc" + b"wxyz"
    cases.append({
        "name": "red_two_blocks",
        "kind": "red",
        "note": "冗余块 delta=5 len=3，主块 len=4，outerSeq=0x0010",
        "payload": body.hex(),
        "outer_seq": 0x0010,
        "outer_ts": 0x00010000,
        "expect": {"span": 5, "blocks": 2,
                   "seqs": [0x000F, 0x0010],
                   "timestamps": [0x0000FFFB, 0x00010000],
                   "lengths": [3, 4],
                   "primary_index": 1},
    })

    # 9. 四块 RED 且序列号回绕
    body = red_head([(100, 10, 2, False), (100, 8, 2, False),
                     (100, 4, 2, False), (100, 0, 2, True)]) + bytes(8)
    cases.append({
        "name": "red_four_blocks_seq_wrap",
        "kind": "red",
        "note": "outerSeq=2，四块推导 0xFFFF,0x0000,0x0001,0x0002",
        "payload": body.hex(),
        "outer_seq": 2,
        "outer_ts": 1000,
        "expect": {"span": 13, "blocks": 4,
                   "seqs": [0xFFFF, 0x0000, 0x0001, 0x0002],
                   "primary_index": 3},
    })

    # 10. 时间戳回绕
    body = red_head([(100, 5, 1, False), (100, 0, 1, True)]) + bytes(2)
    cases.append({
        "name": "red_timestamp_wrap",
        "kind": "red",
        "note": "outerTs=1，delta=5 -> 0xFFFFFFFC",
        "payload": body.hex(),
        "outer_seq": 9,
        "outer_ts": 1,
        "expect": {"span": 5, "blocks": 2,
                   "timestamps": [0xFFFFFFFC, 1]},
    })

    # 11. 字段边界：delta=0x3fff、length=0x3ff、零长冗余块
    body = red_head([(100, 0x3FFF, 0, False), (100, 0x3FFF, 0x3FF, False),
                     (100, 0, 0, True)]) + bytes(0x3FF)
    cases.append({
        "name": "red_field_maxima",
        "kind": "red",
        "note": "delta 14 位全 1、length 10 位全 1，且允许 0 长块",
        "payload": body.hex(),
        "outer_seq": 0,
        "outer_ts": 0xFFFFFFFF,
        "expect": {"span": 9, "blocks": 3,
                   "deltas": [0x3FFF, 0x3FFF, 0],
                   "lengths": [0, 0x3FF, 0]},
    })

    # 12. 头截断
    body = bytes.fromhex("8064") + b"\x00"  # F=1 但不足 4 字节
    cases.append({"name": "red_truncated_header", "kind": "red_reject",
                  "note": "F=1 头不足 4 字节", "payload": body.hex(),
                  "outer_seq": 1, "outer_ts": 1, "expect_error": "RED_TRUNCATED_HEADER"})

    # 13. 冗余块长度超出可用字节
    body = red_head([(100, 1, 6, False), (100, 0, 0, True)]) + bytes(5)
    cases.append({"name": "red_length_mismatch", "kind": "red_reject",
                  "note": "冗余块声明 6 字节，实际只剩 5 字节（主块取余量）",
                  "payload": body.hex(),
                  "outer_seq": 1, "outer_ts": 1, "expect_error": "RED_LENGTH_MISMATCH"})

    # 14. 超过本地块数上限
    body = red_head([(100, i, 0, False) for i in range(red.MAX_BLOCKS)] + [(100, 0, 0, True)])
    cases.append({"name": "red_too_many_blocks", "kind": "red_reject",
                  "note": f"本地上限 {red.MAX_BLOCKS} 块", "payload": body.hex(),
                  "outer_seq": 1, "outer_ts": 1, "expect_error": "RED_TOO_MANY_BLOCKS"})

    # 15. RED + 加密记录联动
    red_payload = red_head([(100, 6, 2, False), (100, 0, 0, True)]) + b"abcde"
    tag = bytes(range(16))
    nonce = bytes.fromhex("0a0b0c0d0e0f1011")
    pkt = rtp.build_message(0x0200, 0x0200, 0x11223344, red_payload + tag + nonce)
    cases.append({
        "name": "red_then_record",
        "kind": "full",
        "note": "仅合成消息坐标/描述符/显式尾布局联动；不解密，不把密文切为可播放块",
        "hex": pkt.hex(),
        "trailer_layout": "tag16_nonce8",
        "outer_seq": 0x0200,
        "outer_ts": 0x0200,
        "expect": {"span": 5, "blocks": 2,
                   "ciphertext": b"abcde".hex(), "aad": pkt[2:10].hex(),
                   "authenticated": False},
    })

    # Independent literal M header, to catch accidentally reintroducing a 12B offset.
    cases.append({"name": "message_literal_header", "kind": "message",
                  "hex": "123401020304a1b2c3d4abcd",
                  "expect": {"seq": 0x1234, "timestamp": 0x01020304,
                             "second_word": 0xa1b2c3d4, "header_len": 10,
                             "aad": "01020304a1b2c3d4"}})
    for span, error in ((-1, "BAD_SPAN"), (True, "BAD_SPAN"), (100, "SHORT_BODY")):
        cases.append({"name": f"message_invalid_span_{span}", "kind": "record_reject",
                      "hex": (bytes(10) + b"x" + bytes(24)).hex(), "span": span,
                      "trailer_layout": "tag16_nonce8", "expect_error": error})
    cases.append({"name": "message_unknown_layout", "kind": "record_reject",
                  "hex": bytes(40).hex(), "trailer_layout": "auto",
                  "expect_error": "UNKNOWN_TRAILER_LAYOUT"})
    cases.append({"name": "message_header_short", "kind": "record_reject",
                  "hex": bytes(9).hex(), "trailer_layout": "tag16",
                  "expect_error": "SHORT_MESSAGE_HEADER"})
    cases.append({"name": "message_tag_only_layout", "kind": "record",
                  "hex": (bytes(10) + b"x" + bytes(16)).hex(), "trailer_layout": "tag16",
                  "expect": {"ciphertext": "78", "tag": bytes(16).hex(), "nonce": "",
                             "nonce_source": "external_state_required", "overhead": 16,
                             "authenticated": False}})

    # Standards-based RTP inspector boundaries; these do not prove Apple accepts X/P/CC.
    network = [
        ("rtp_csrc", hdr(100, 1, 2, b0=0x81) + bytes.fromhex("01020304") + b"x",
         {"header_len": 16, "csrcs": [0x01020304], "payload": "78"}, None),
        ("rtp_csrc_short", hdr(100, 1, 2, b0=0x81), None, "SHORT_CSRC"),
        ("rtp_extension", hdr(100, 1, 2, b0=0x90) + bytes.fromhex("bede000161626364") + b"x",
         {"header_len": 20, "extension_profile": 0xbede, "extension_data": "61626364", "payload": "78"}, None),
        ("rtp_extension_header_short", hdr(100, 1, 2, b0=0x90) + b"ab", None, "SHORT_EXTENSION_HEADER"),
        ("rtp_extension_data_short", hdr(100, 1, 2, b0=0x90) + bytes.fromhex("bede0001") + b"ab", None, "SHORT_EXTENSION_DATA"),
        ("rtp_padding", hdr(100, 1, 2, b0=0xa0) + b"x\x00\x02",
         {"payload": "78", "padding_len": 2, "payload_end": 13}, None),
        ("rtp_padding_zero", hdr(100, 1, 2, b0=0xa0) + b"\x00", None, "BAD_PADDING"),
        ("rtp_padding_too_long", hdr(100, 1, 2, b0=0xa0) + b"\x02", None, "BAD_PADDING"),
        ("rtp_padding_no_body", hdr(100, 1, 2, b0=0xa0), None, "BAD_PADDING"),
        ("rtp_extension_empty", hdr(100, 1, 2, b0=0x90) + bytes(4),
         {"header_len": 16, "payload": "", "extension_data": ""}, None),
    ]
    for name, packet, expect, error in network:
        case = {"name": name, "kind": "rtp_reject" if error else "rtp", "hex": packet.hex()}
        case["expect_error" if error else "expect"] = error or expect
        cases.append(case)

    payload = {
        "schema": 2,
        "scope": "标准RTP检查与10B内部消息分离；合成结构向量，不含密码执行/网络映射/真实抓包",
        "rtp_header_len": rtp.RTP_HEADER_LEN,
        "audio_message_header_len": rtp.AUDIO_MESSAGE_HEADER_LEN,
        "trailer_layouts": rtp.TRAILER_LAYOUTS,
        "receive_mask": rtp.RECEIVE_MASK,
        "cases": cases,
    }
    out = HERE / "test_vectors.json"
    out.write_text(json.dumps(payload, ensure_ascii=False, indent=1) + "\n", encoding="utf-8")
    print(f"wrote {out} cases={len(cases)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
