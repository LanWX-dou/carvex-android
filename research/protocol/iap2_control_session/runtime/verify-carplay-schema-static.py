#!/usr/bin/env python3
"""Static regression checks for the 24A446 CarPlayStartSession mapping.

This verifies original bytes, jump tables, getter widths and a few synthetic
TLV shape checks.  It is not a captured 0x4301 frame and cannot prove
interoperability or downstream CarPlay success.
"""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = ROOT / "iap2_control_session" / "source" / "firmware" / "accessoryd"
BASE = 0x100000000
IMAGE_SHA256 = "2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe"
HANDLER_SHA256 = "7d5db2d7d7b9c2cebd668e773346c3fbba78a4ec697eb1ca6d877fe1eaa98b04"


def blob(addr: int, end: int | None = None) -> bytes:
    data = BIN.read_bytes()
    off = addr - BASE
    return data[off:] if end is None else data[off : end - BASE]


def u32s(addr: int, count: int) -> tuple[int, ...]:
    return struct.unpack("<" + "i" * count, blob(addr, addr + count * 4))


def check(cond: bool, msg: str) -> None:
    if not cond:
        raise AssertionError(msg)


def check_tlv() -> None:
    # Synthetic only: standard big-endian TLV and the schema's string/U8/U32 shapes.
    s = b"192.0.2.1\0"
    p = struct.pack(">HH", 4 + len(s), 0) + s
    check(struct.unpack(">H", p[:2])[0] == len(p), "string length")
    check(p[-1] == 0, "string NUL")
    u8 = struct.pack(">HHB", 5, 2, 6)
    check(len(u8) == 5 and u8[4] == 6, "U8 shape")
    u32 = struct.pack(">HHI", 8, 2, 8080)
    check(len(u32) == 8 and struct.unpack(">I", u32[4:])[0] == 8080, "U32 shape")
    check(struct.pack(">HH", 4, 0) == b"\0\x04\0\0", "len=4 profile sentinel")
    def tlv(pid: int, value: bytes) -> bytes:
        return struct.pack(">HH", 4 + len(value), pid) + value
    payload = tlv(0, p) + tlv(1, tlv(0, b"Lab\0") + u8) + u32 + tlv(8, b"\1")
    message = b"@@" + struct.pack(">HH", 6 + len(payload), 0x4301) + payload
    # Compare the complete spec/14 example, including nested group headers.
    import re
    spec = (ROOT / "iap2_control_session/spec/14-carplay-start-schema.md").read_text(encoding="utf-8")
    example = re.search(r"```text\n(.*?)```", spec, re.S).group(1)
    expected = bytes.fromhex(" ".join(line.split("#", 1)[0] for line in example.splitlines()))
    check(message == expected and len(message) == 54, "spec/14 nested example")


def main() -> int:
    data = BIN.read_bytes()
    check(hashlib.sha256(data).hexdigest() == IMAGE_SHA256, "accessoryd image hash")
    handler = blob(0x10016D3AC, 0x10016E004)
    check(hashlib.sha256(handler).hexdigest() == HANDLER_SHA256, "handler hash")

    outer = tuple(0x10016D594 + x for x in u32s(0x100018DB8, 9))
    check(outer == (
        0x10016D5A0, 0x10016D78C, 0x10016D674, 0x10016D690,
        0x10016D658, 0x10016D914, 0x10016D930, 0x10016D6AC,
        0x10016D94C), "outer jump table")
    nested = tuple(0x10016D7C8 + x for x in u32s(0x100018DDC, 5))
    check(nested == (0x10016D7D4, 0x10016D884, 0x10016D828,
                    0x10016D850, 0x10016D7F0), "nested jump table")

    # Getter machine-code signatures: len=8/U32, len=5/U8, Bool<=1,
    # string last-byte NUL check.  These are exact original bytes.
    check(blob(0x100067DF0, 0x100067E1C) == bytes.fromhex(
        "080040790805c05a1f210071e8079f1a280000b96000005400008052c0035fd6"
        "080440b90009c05ac0035fd6"), "U32 getter bytes")
    check(blob(0x100067E4C, 0x100067E74) == bytes.fromhex(
        "080040790805c05a1f150071e8079f1a280000b96000005400008052c0035fd6"
        "00104039c0035fd6"),
        "U8 getter bytes")
    check(blob(0x100067E74, 0x100067E9C) == bytes.fromhex(
        "08104039090040792905c05a081d0072e0079f1a3f1500710209417ae8979f1a"
        "280000b9c0035fd6"), "Bool getter bytes")
    check(blob(0x100067EE4, 0x100067F30) == bytes.fromhex(
        "080040790805c05a1f150071e9279f1a290000b962000054000080d2c0035fd6"
        "89ff9f520801090b083d001209100091080500d1286968381f010071e8079f1a"
        "280000b9e013899ac0035fd6"), "string getter bytes")
    check_tlv()
    print("carplay schema static checks: PASS (static/synthetic only)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
