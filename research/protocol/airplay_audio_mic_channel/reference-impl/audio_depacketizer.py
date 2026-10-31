#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Audio message codecs and a separate standards-based RTP inspection parser.

Firmware messages M have a 10B header (seq16, timestamp32, second_word32).
AAD helper returns M[2:10]. M -> network packet mapping is NOT implemented.
parse_header handles RFC3550 CSRC/extension/padding, not an Apple-profile proof.
No authentication, crypto state, decoder, sockets or plaintext fallback.
"""
from __future__ import annotations

RTP_HEADER_LEN = 12  # minimum, not necessarily the payload offset
AUDIO_MESSAGE_HEADER_LEN = 10
PAYLOAD_TYPES = {96: "gen", 97: "gred", 100: "main", 101: "alt ",
                 104: "mred", 105: "ared", 106: "auxo", 107: "oovc",
                 108: "axrd", 109: "ovrd"}
RECEIVE_MASK = 0x3D13
RECEIVE_PTS = frozenset(pt for pt in range(96, 110) if (RECEIVE_MASK >> (pt - 96)) & 1)
# Explicit local slicing contracts, not negotiated profiles or universal audio formats.
TRAILER_LAYOUTS = {"tag16_nonce8": (16, 8), "tag16": (16, 0)}


class PacketError(ValueError):
    def __init__(self, code: str, detail: str = "") -> None:
        super().__init__(code)
        self.code, self.detail = code, detail


def parse_header(packet: bytes, *, enforce_receive_mask: bool = True) -> dict:
    """Inspect one complete standard RTP datagram; acceptance is not authentication."""
    if len(packet) < RTP_HEADER_LEN:
        raise PacketError("SHORT_HEADER")
    b0 = packet[0]
    if b0 >> 6 != 2:
        raise PacketError("BAD_VERSION_BYTE")
    pt = packet[1] & 0x7F
    if enforce_receive_mask:
        if pt not in PAYLOAD_TYPES:
            raise PacketError("UNKNOWN_PT")
        if pt not in RECEIVE_PTS:
            raise PacketError("PT_NOT_RECEIVABLE")
    count = b0 & 15
    offset = RTP_HEADER_LEN + 4 * count
    if offset > len(packet):
        raise PacketError("SHORT_CSRC")
    csrcs = [int.from_bytes(packet[i:i + 4], "big") for i in range(12, offset, 4)]
    extension_profile = None
    extension_data = b""
    if b0 & 0x10:
        if offset + 4 > len(packet):
            raise PacketError("SHORT_EXTENSION_HEADER")
        extension_profile = int.from_bytes(packet[offset:offset + 2], "big")
        words = int.from_bytes(packet[offset + 2:offset + 4], "big")
        end = offset + 4 + words * 4
        if end > len(packet):
            raise PacketError("SHORT_EXTENSION_DATA")
        extension_data = packet[offset + 4:end]
        offset = end
    payload_end = len(packet)
    padding_len = 0
    if b0 & 0x20:
        if offset == payload_end:
            raise PacketError("BAD_PADDING")
        padding_len = packet[-1]
        if padding_len == 0 or padding_len > payload_end - offset:
            raise PacketError("BAD_PADDING")
        payload_end -= padding_len
    return {
        "version": 2, "padding": (b0 >> 5) & 1, "extension": (b0 >> 4) & 1,
        "csrc_count": count, "csrcs": csrcs, "marker": packet[1] >> 7,
        "pt": pt, "name": PAYLOAD_TYPES.get(pt), "seq": int.from_bytes(packet[2:4], "big"),
        "timestamp": int.from_bytes(packet[4:8], "big"), "ssrc": int.from_bytes(packet[8:12], "big"),
        "header_len": offset, "extension_profile": extension_profile,
        "extension_data": extension_data, "padding_len": padding_len,
        "payload_end": payload_end, "payload": packet[offset:payload_end],
    }


def parse_message_header(message: bytes) -> dict:
    """M[0:10], independent of PT/marker/network wrapper."""
    if len(message) < AUDIO_MESSAGE_HEADER_LEN:
        raise PacketError("SHORT_MESSAGE_HEADER")
    return {"seq": int.from_bytes(message[0:2], "big"),
            "timestamp": int.from_bytes(message[2:6], "big"),
            "second_word": int.from_bytes(message[6:10], "big"),
            "header_len": AUDIO_MESSAGE_HEADER_LEN}


def build_message(seq: int, timestamp: int, second_word: int, body: bytes = b"") -> bytes:
    """Device-side message construction only, not a wire-ready RTP packet."""
    for name, value, bits in (("seq", seq, 16), ("timestamp", timestamp, 32),
                              ("second_word", second_word, 32)):
        if type(value) is not int or not 0 <= value < (1 << bits):
            raise PacketError("FIELD_RANGE", name)
    if not isinstance(body, bytes):
        raise PacketError("BODY_TYPE")
    return (seq.to_bytes(2, "big") + timestamp.to_bytes(4, "big") +
            second_word.to_bytes(4, "big") + body)


def aad_for_message(message: bytes) -> bytes:
    """Known AAD-provider input, not a claim that every media cryptor uses AEAD."""
    parse_message_header(message)
    return message[2:10]


def split_message_record(message: bytes, element_span: int = 0, *,
                         trailer_layout: str) -> dict:
    """Slice an explicit local trailer layout after M+10+element_span.

    Caller must bind the actual provider/profile first. No automatic 24/16 fallback.
    Descriptor span is syntax-checked separately; it is 0 without elements, not 1.
    Empty ciphertext is rejected as a conservative local policy, not a firmware claim.
    Returned ciphertext/descriptor metadata is UNAUTHENTICATED.
    """
    info = parse_message_header(message)
    if type(element_span) is not int or element_span < 0:
        raise PacketError("BAD_SPAN")
    if trailer_layout not in TRAILER_LAYOUTS:
        raise PacketError("UNKNOWN_TRAILER_LAYOUT")
    start = AUDIO_MESSAGE_HEADER_LEN + element_span
    if start > len(message):
        raise PacketError("SHORT_BODY")
    tag_len, nonce_len = TRAILER_LAYOUTS[trailer_layout]
    overhead = tag_len + nonce_len
    body = message[start:]
    if len(body) <= overhead:
        raise PacketError("SHORT_RECORD")
    tag_start = len(body) - overhead
    nonce_start = len(body) - nonce_len
    return {**info, "aad": aad_for_message(message), "ciphertext": body[:tag_start],
            "tag": body[tag_start:nonce_start],
            "nonce": body[nonce_start:] if nonce_len else b"",
            "nonce_source": "record_tail" if nonce_len else "external_state_required",
            "overhead": overhead, "span": element_span, "authenticated": False}
