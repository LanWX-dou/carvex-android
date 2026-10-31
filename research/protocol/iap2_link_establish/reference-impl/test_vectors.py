#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Executable test vectors for `iap2_link.py`.

Run directly (no dependencies):  python3 test_vectors.py

The first six checks are the arithmetic vectors in `spec/02` and `spec/08`;
V4/V5 are not valid complete frame headers. Additional tests cover literal
bytes, malformed input, ACK direction and cross-build parsed packet logs.
Round-trips alone are not evidence of firmware or head-unit interoperability.
"""

import sys
import re
from pathlib import Path

sys.dont_write_bytecode = True
import iap2_link as L

FAILS = []
CHECKS = 0


def check(name, got, want):
    global CHECKS
    CHECKS += 1
    if got != want:
        FAILS.append("%s: got %r want %r" % (name, got, want))


def rejects(name, operation):
    global CHECKS
    CHECKS += 1
    try:
        operation()
    except L.FrameError:
        return
    FAILS.append(name + ": malformed input accepted")


def main() -> int:
    # V1..V3 — legacy frame checksum scope (R-3.4)
    check("V1 legacy detect", L.checksum(bytes.fromhex("0200EE"), 8), 0x10)
    check("V2 legacy detect-nack", L.checksum(bytes.fromhex("04000204EE"), 8), 0x08)
    check("V3 legacy request-identify", L.checksum(bytes.fromhex("0200FE"), 8), 0x00)

    # V4..V5 — iAP2 header checksum, 16-bit (R-3.7)
    check("V4 syn hdr", L.checksum(bytes.fromhex("FF5A000980000000"), 16), 0x581D)
    check("V5 ack hdr", L.checksum(bytes.fromhex("FF5A0009C0000000"), 16), 0x57DC)

    # V6 — empty input is zero (R-3.6)
    check("V6 empty", L.checksum(b"", 16), 0x0000)
    # For 01: folded s1=1,s2=256. add/shift/mask => 0x10100;
    # OR 1 and negate => 0xfeff. Dropping s2's carry would give 0xffff.
    check("16-bit carry retained", L.checksum(b"\x01", 16), 0xFEFF)

    # Legacy frames: the three firmware constants must re-encode to themselves.
    check("legacy detect constant", L.legacy_frame(bytes.fromhex("00EE")), L.LEGACY_DETECT)
    check("legacy detect-nack constant",
          L.legacy_frame(bytes.fromhex("000204EE")), L.LEGACY_DETECT_NACK)
    check("legacy request-identify constant",
          L.legacy_frame(bytes.fromhex("00FE")), L.LEGACY_REQUEST_IDENTIFY)
    for blob in (L.LEGACY_DETECT, L.LEGACY_DETECT_NACK, L.LEGACY_REQUEST_IDENTIFY):
        payload = L.parse_legacy(blob)
        check("legacy roundtrip %s" % blob.hex(), L.legacy_frame(payload), blob)

    # iAP2 frames: round-trip both checksum widths and both control classes.
    for cs16 in (True, False):
        for ctrl, payload in ((0x80, L.build_syn()), (0x40, b""),
                              (0x60, b""), (0x00, bytes(range(40)))):
            frame = L.iap2_frame(ctrl, 7, 0, payload, cs16=cs16)
            got = L.parse_iap2(frame, cs16=cs16)
            check("frame ctrl=%#x cs16=%s seq" % (ctrl, cs16), got["seq"], 7)
            check("frame ctrl=%#x cs16=%s payload" % (ctrl, cs16), got["payload"], payload)
            check("frame ctrl=%#x cs16=%s length" % (ctrl, cs16),
                  got["length"], len(frame))

    # SYN: encode/decode agreement, v1 without tail and v2 with extras/features.
    syn = L.parse_syn(L.build_syn())
    check("syn version", syn["version"], 1)
    check("syn max_packet", syn["max_packet"], 0xFFFF)
    check("syn ack_timeout", syn["ack_timeout"], 1000)
    long_syn = L.build_syn(version=2, extras=[bytes.fromhex("AABB")],
                           features=[bytes.fromhex("010203")])
    check("syn v1 length", len(L.build_syn()), 10)
    check("syn v2 length", len(long_syn), 10 + 1 + 2 + 1 + 3)
    check("syn v2 version", L.parse_syn(long_syn)["version"], 2)
    check("syn v2 extension byte count", long_syn[10], 2)
    check("syn v2 extensions", L.parse_syn(long_syn)["extras"], b"\xaa\xbb")
    check("syn v2 entries", L.parse_syn(long_syn)["features"], [b"\x01\x02\x03"])
    observed_syn = bytes.fromhex("0101100003e801f40f00020002")
    check("23G90 SYN exact bytes", L.build_syn(max_packet=4096,
          cumack_timeout=500, max_retrans=15, features=[b"\x02\x00\x02"]), observed_syn)
    check("23G90 SYN session entry", L.parse_syn(observed_syn)["features"], [b"\x02\x00\x02"])
    for payload in (b"", observed_syn[:7], observed_syn[:9], observed_syn[:-1],
                    b"\x02" + observed_syn[1:10],
                    b"\x02" + observed_syn[1:10] + b"\x00\x02\x02\x00\x02"):
        rejects("SYN bounds " + payload.hex(), lambda p=payload: L.parse_syn(p))

    # Flow control helpers (R-5.2, R-5.3)
    check("gap wrap", L.seq_gap(0x02, 0xFE), 4)
    check("acked in window", L.seq_acked(0x02, 0x03, 1), True)
    check("future sequence not acked", L.seq_acked(0x03, 0x02, 1), False)
    check("acked across wrap", L.seq_acked(0xFF, 0x00, 1), True)
    check("future across wrap not acked", L.seq_acked(0x00, 0xFF, 1), False)
    check("not acked outside window", L.seq_acked(0x05, 0x02, 1), False)

    # Framing rejects malformed input instead of guessing.
    for blob in (b"", L.LEGACY_DETECT[:-1], L.iap2_frame(0x40, 0, 0, cs16=True)[:-1],
                 b"\xff\x55\x02\x00\xee\x00"):
        try:
            (L.parse_legacy if blob[:2] == L.LEGACY_MAGIC else L.parse_iap2)(blob)
        except L.FrameError:
            pass
        else:
            FAILS.append("malformed input accepted: %s" % blob.hex())

    # Compare every logged SYN/data/ACK field against encoding, not a codec's
    # own round-trip. Log has parsed fields/payload, not an independent pcap.
    log = Path(__file__).resolve().parents[2] / "iap2_control_session/runtime/accessoryd-packets-2026-10-16-221117.log.ips"
    pattern = re.compile(r"len=0x([0-9a-f]+); control=0x([0-9a-f]+); seq=0x([0-9a-f]+); ack=0x([0-9a-f]+); session=0x([0-9a-f]+); hdrChk=0x([0-9a-f]+); payload\(len=(\d+) chk=0x([0-9a-f]+)\)=<([^>]*)>")
    packets = 0
    for line in log.read_text(encoding="utf-8").splitlines():
        match = pattern.search(line)
        if not match:
            continue
        length, ctrl, seq, ack, sid, hc = [int(x, 16) for x in match.groups()[:6]]
        if length == 6:  # legacy Detect represented by synthetic log fields
            continue
        payload = bytes.fromhex(match[9])
        packets += 1
        wire = L.iap2_frame(ctrl, seq, ack, payload, cs16=False, extra=sid)
        check("sample length", len(wire), length)
        check("sample header checksum", wire[8], hc)
        check("sample payload checksum", L.checksum(payload, 8), int(match[8], 16))
        check("sample parsed payload", L.parse_iap2(wire, cs16=False)["payload"], payload)
    check("runtime corpus present", packets > 10, True)
    ack = bytes.fromhex("ff5a000940740f00db")
    check("9-byte ACK encode", L.iap2_frame(0x40, 0x74, 0x0f), ack)
    check("9-byte ACK decode", L.parse_iap2(ack)["payload"], b"")
    rejects("truncated 16-bit header", lambda: L.parse_iap2(ack, cs16=True))

    for f in FAILS:
        print("FAIL", f)
    print("%d checks, %d failed" % (CHECKS, len(FAILS)))
    return 1 if FAILS else 0


if __name__ == "__main__":
    sys.exit(main())
