#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""iAP2 link layer — platform-independent reference implementation.

This module is a non-normative codec companion of `spec/02`, `spec/03` and
`spec/04`, not a complete link FSM or a CarPlay client. It contains no OS,
transport or language-framework dependency: it turns frames into bytes and
bytes into frames, nothing else.

Everything implemented here is backed by a rule in `spec/`; the mapping is:

    checksum / legacy_frame     -> R-2.2 .. R-2.12  (spec/02)
    build_syn / parse_syn       -> R-3.1 .. R-3.8   (spec/03)
    seq_acked / seq_gap         -> R-4.1 .. R-4.5   (spec/04)

Deliberately absent (documented as OPEN, do not guess):

    * how to open the transport (link/OPEN-TX-1)
    * the MFi authentication exchange (link/OPEN-AUTH-1)
    * any session/control-session behaviour (separate phase)
"""

from __future__ import annotations

MAGIC = b"\xff\x5a"
LEGACY_MAGIC = b"\xff\x55"

CTRL_SYN = 0x80
CTRL_ACK = 0x40
CTRL_EAK = 0x20
CTRL_RST = 0x10
CTRL_SUS = 0x08

# Legacy templates (spec/02 R-2.11); RequestIdentify trailer is calculated.
LEGACY_DETECT = b"\xff\x55\x02\x00\xee\x10"
LEGACY_DETECT_NACK = b"\xff\x55\x04\x00\x02\x04\xee\x08"
LEGACY_REQUEST_IDENTIFY = b"\xff\x55\x02\x00\xfe\x00"


class FrameError(ValueError):
    """Raised when a byte string is not a well-formed iAP2 frame."""


# --------------------------------------------------------------------- checksum

def checksum(data: bytes, kind: int = 16) -> int:
    """iAP2 checksum.

    kind == 8  : one byte, ``(-sum(bytes)) & 0xFF`` (R-2.6)
    kind == 16 : two bytes, 20-byte blocks with the fold described in R-2.6

    An empty input yields 0. Framing chooses whether a trailer exists.
    """
    if not data:
        return 0
    if kind == 8:
        return (-sum(data)) & 0xFF
    s1 = s2 = 0xFF
    for i in range(0, len(data), 20):
        for b in data[i:i + 20]:
            s1 += b
            s2 += s1
        s1 = (s1 & 0xFF) + ((s1 >> 8) & 0xFF)
        s2 = (s2 & 0xFF) + ((s2 >> 8) & 0xFF)
    s1 = (s1 & 0xFF) + (s1 >> 8)
    # 0x100008b78: add w8,w8,w8,lsl #8; do not discard s2's carry.
    return (-(((s2 + (s2 << 8)) & 0x3FF00) | s1)) & 0xFFFF


# ----------------------------------------------------------------- legacy frame

def legacy_frame(payload: bytes) -> bytes:
    """Build a legacy iAP frame: ``FF 55 <len:1> <payload> <cksum:1>``.

    The checksum covers ``len + payload`` and explicitly **excludes** the
    ``FF 55`` marker (`spec/02` R-2.10). The payload layout is not a fixed
    "terminator + command" pair: the observed frames end with 0xEE, 0xEE and
    0xFE respectively, so callers must pass the exact bytes (`OPEN-FRM-1`).
    """
    if len(payload) > 0xFE:
        raise FrameError("legacy payload too long")
    body = bytes([len(payload)]) + payload
    return LEGACY_MAGIC + body + bytes([checksum(body, 8)])


def parse_legacy(blob: bytes) -> bytes:
    """Validate a legacy frame and return its payload."""
    if len(blob) < 5 or blob[:2] != LEGACY_MAGIC:
        raise FrameError("not a legacy frame")
    n = blob[2]
    if len(blob) != 3 + n + 1:
        raise FrameError("legacy length mismatch")
    body = blob[2:3 + n]
    if checksum(body, 8) != blob[3 + n]:
        raise FrameError("legacy checksum mismatch")
    return blob[3:3 + n]


# -------------------------------------------------------------------- iAP2 frame

def iap2_frame(control: int, seq: int, link_type: int, payload: bytes = b"",
               cs16: bool = False, extra: int = 0) -> bytes:
    """Build one iAP2 frame (R-2.1, R-2.2).

    Legacy API names: ``link_type`` is ACK, ``extra`` is session ID.
    Layout: ``FF 5A | len(BE, whole frame) | ctrl | seq | ack | session |
    hdr_cksum | payload | payload_cksum``

    ``len`` counts the whole frame including both checksums. The header
    checksum covers ``FF 5A`` and every header byte (R-3.7), the payload
    checksum covers the payload only (R-3.8).
    """
    if not 0 <= seq <= 0xFF:
        raise FrameError("seq out of range")
    hdr_cs = 2 if cs16 else 1
    total = 8 + hdr_cs + len(payload) + (hdr_cs if payload else 0)
    if total > 0xFFFF:
        raise FrameError("frame too long")
    header = bytearray(MAGIC)
    header += total.to_bytes(2, "big")
    header += bytes([control & 0xFF, seq & 0xFF, link_type & 0xFF, extra & 0xFF])
    value = checksum(bytes(header), 16 if cs16 else 8)
    header += value.to_bytes(hdr_cs, "big")
    body = bytes(header) + payload
    if payload:
        body += checksum(payload, 16 if cs16 else 8).to_bytes(hdr_cs, "big")
    return body


def parse_iap2(blob: bytes, cs16: bool | None = False) -> dict:
    """Parse and validate an iAP2 frame; returns a dict of fields.

    ``cs16`` selects the checksum width. Passing ``None`` tries 2-byte first and
    falls back to 1-byte (diagnostic mode only). The creation default is
    1 byte (`link+0xd5=1`); production callers must select the profile width.
    """
    if len(blob) < 9 or blob[:2] != MAGIC:
        raise FrameError("not an iAP2 frame")
    total = int.from_bytes(blob[2:4], "big")
    if total != len(blob):
        raise FrameError("length field %d != %d" % (total, len(blob)))
    candidates = [cs16] if cs16 is not None else [True, False]
    last = None
    for width in candidates:
        try:
            return _parse_iap2_with(blob, width)
        except FrameError as exc:
            last = exc
    raise last


def _parse_iap2_with(blob: bytes, cs16: bool) -> dict:
    control, seq, link_type, extra = blob[4], blob[5], blob[6], blob[7]
    hdr_cs = 2 if cs16 else 1
    header_size = 8 + hdr_cs
    if len(blob) < header_size:
        raise FrameError("truncated header")
    got = int.from_bytes(blob[8:8 + hdr_cs], "big")
    want = checksum(blob[:8], 16 if cs16 else 8)
    if got != want:
        raise FrameError("header checksum %#x != %#x" % (got, want))
    payload = b""
    if len(blob) != header_size:
        if len(blob) <= header_size + hdr_cs:
            raise FrameError("missing payload or truncated payload checksum")
        payload = blob[header_size:-hdr_cs]
        got = int.from_bytes(blob[-hdr_cs:], "big")
        want = checksum(payload, 16 if cs16 else 8)
        if got != want:
            raise FrameError("payload checksum %#x != %#x" % (got, want))
    return {
        "length": int.from_bytes(blob[2:4], "big"),
        "control": control,
        "seq": seq,
        "link_type": link_type,
        "extra": extra,
        "payload": payload,
        "cs16": cs16,
        "is_syn": bool(control & CTRL_SYN),
        "is_ack": bool(control & CTRL_ACK),
        "is_eak": bool(control & CTRL_EAK),
        "is_rst": bool(control & CTRL_RST),
        "is_sus": bool(control & CTRL_SUS),
    }


# ------------------------------------------------------------------------- SYN

SYN_FIELDS = ("version", "mop", "max_packet", "ack_timeout", "cumack_timeout",
              "max_retrans", "max_cumack")


def build_syn(version: int = 1, mop: int = 1, max_packet: int = 0xFFFF,
              ack_timeout: int = 1000, cumack_timeout: int = 10,
              max_retrans: int = 30, max_cumack: int = 0,
              extras: list[bytes] | None = None,
              features: list[bytes] | None = None) -> bytes:
    """Encode SYN layout (R-3.4/R-3.6), not full negotiation validity.

    Wire order: ``version, mop, max_packet(BE), ack_timeout(BE),
    cumack_timeout(BE), max_retrans, max_cumack``; when ``version >= 2`` a tail
    follows: ``extra_count, extras..., feature_count, 3-byte feature entries``.

    Version 1 appends raw three-byte session entries, without counts/extras.
    Zero entries are useful for codec tests, but fail the target validator.
    """
    extras = extras or []
    features = features or []
    if len(features) > 5 or any(len(f) != 3 for f in features):
        raise FrameError("expected at most five three-byte session entries")
    extra_bytes = b"".join(extras)
    if len(extra_bytes) > 5:
        raise FrameError("at most five extension bytes")
    if version < 2 and extra_bytes:
        raise FrameError("extensions require version >= 2")
    if version == 0 and features:
        raise FrameError("version 0 has no session tail")
    for name, value, limit in (("version", version, 255), ("mop", mop, 255),
                              ("max_packet", max_packet, 65535),
                              ("ack_timeout", ack_timeout, 65535),
                              ("cumack_timeout", cumack_timeout, 65535),
                              ("max_retrans", max_retrans, 255),
                              ("max_cumack", max_cumack, 255)):
        if not 0 <= value <= limit:
            raise FrameError(name + " out of wire range")
    out = bytearray()
    out.append(version & 0xFF)
    out.append(mop & 0xFF)
    out += (max_packet & 0xFFFF).to_bytes(2, "big")
    out += (ack_timeout & 0xFFFF).to_bytes(2, "big")
    out += (cumack_timeout & 0xFFFF).to_bytes(2, "big")
    out.append(max_retrans & 0xFF)
    out.append(max_cumack & 0xFF)
    if version >= 2:
        out.append(len(extra_bytes))
        out += extra_bytes
        out.append(len(features))
    if version >= 1:
        for f in features:
            if len(f) != 3:
                raise FrameError("feature entry must be 3 bytes")
            out += f
    return bytes(out)


def parse_syn(payload: bytes) -> dict:
    """Decode a SYN payload produced by ``build_syn``."""
    if len(payload) < 10:
        raise FrameError("SYN payload shorter than 10 bytes")
    out = {
        "version": payload[0],
        "mop": payload[1],
        "max_packet": int.from_bytes(payload[2:4], "big"),
        "ack_timeout": int.from_bytes(payload[4:6], "big"),
        "cumack_timeout": int.from_bytes(payload[6:8], "big") if len(payload) >= 8 else None,
        "max_retrans": payload[8] if len(payload) >= 9 else None,
        "max_cumack": payload[9] if len(payload) >= 10 else None,
        "raw": payload,
    }
    # Strict bounds are implementation hardening, not a replica of every
    # malformed-input acceptance in the firmware parser.
    version = payload[0]
    extra_bytes = b""
    if version == 0:
        if len(payload) != 10:
            raise FrameError("version 0 has no tail")
        tail = b""
    elif version == 1:
        tail = payload[10:]
    else:
        if len(payload) < 12:
            raise FrameError("truncated SYN extension header")
        k = payload[10]
        if k > 5 or len(payload) < 12 + k:
            raise FrameError("invalid SYN extension length")
        extra_bytes = payload[11:11 + k]
        n = payload[11 + k]
        tail = payload[12 + k:]
        if len(tail) != 3 * n:
            raise FrameError("SYN session count mismatch")
    if len(tail) % 3 or len(tail) > 15:
        raise FrameError("invalid SYN session tail")
    out["extras"] = extra_bytes
    out["features"] = [tail[i:i + 3] for i in range(0, len(tail), 3)]
    return out


# ---------------------------------------------------------------- flow control

def seq_gap(seq: int, ack: int) -> int:
    """Distance from ``ack`` to ``seq`` in the 8-bit sequence space (R-4.1)."""
    return (seq - ack) & 0xFF


def seq_acked(seq: int, ack: int, window: int) -> bool:
    """True when ``seq`` is already acknowledged (R-4.4).

    ``window`` is the negotiated window (``link+0x1a5``); its default is 1
    (`A05.3b`), i.e. one outstanding frame.
    """
    return window >= ((ack - seq) & 0xFF)
