#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Minimal TLV8 codec (type 1 byte, length 1 byte, value).

Values longer than 255 bytes are split into consecutive chunks of the same type
(the wire has no other length escape). This mirrors the encoder behind
_TLV8BufferAppend (0x18bf41b64); no key material is involved.
"""


def encode(items):
    """items: iterable of (type:int, value:bytes) -> bytes"""
    out = bytearray()
    for t, v in items:
        if not 0 <= t <= 0xFF:
            raise ValueError("type out of range")
        if not v:
            out += bytes([t, 0])
            continue
        i = 0
        while i < len(v):
            chunk = v[i:i + 255]
            out += bytes([t, len(chunk)]) + chunk
            i += 255
    return bytes(out)


def decode(buf):
    """Return list of (type, value) with consecutive same-type chunks coalesced."""
    items = []
    i = 0
    while i < len(buf):
        if i + 2 > len(buf):
            raise ValueError("truncated TLV header")
        t, n = buf[i], buf[i + 1]
        i += 2
        if i + n > len(buf):
            raise ValueError("truncated TLV value")
        v = buf[i:i + n]
        i += n
        if items and items[-1][0] == t:
            items[-1] = (t, items[-1][1] + v)
        else:
            items.append((t, v))
    return items


def get(items, t):
    for k, v in items:
        if k == t:
            return v
    return None
