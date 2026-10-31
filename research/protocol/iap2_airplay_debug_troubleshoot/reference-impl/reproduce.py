#!/usr/bin/env python3
"""Explicit local fault fixtures; not real peer failures or a protocol simulator."""
import argparse
import importlib.util
from pathlib import Path
import sys

sys.dont_write_bytecode = True
DOCS = Path(__file__).resolve().parents[2]


def load(name, rel):
    spec = importlib.util.spec_from_file_location(name, DOCS / rel)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


diag = load("debug_diagnostic", "iap2_airplay_debug_troubleshoot/reference-impl/diagnostic.py")


def reject(fn, *args, **kwargs):
    try:
        fn(*args, **kwargs)
    except ValueError:
        return
    raise AssertionError("expected rejection")


def D01():
    link = load("debug_link", "iap2_link_establish/reference-impl/iap2_link.py")
    # Hand-calculated 8-bit header checksum (-419)&255 = 0x5d.
    good = bytes.fromhex("ff5a0009400100005d")
    parsed = link.parse_iap2(good, cs16=False)
    assert parsed["seq"] == 1 and parsed["link_type"] == 0 and parsed["extra"] == 0
    reject(link.parse_iap2, good[:-1] + b"\x5c", cs16=False)
    reject(link.parse_iap2, good[:-1], cs16=False)
    # Restore the exact original baseline; no automatic checksum-width fallback.
    assert link.parse_iap2(good, cs16=False)["is_ack"]


def D02():
    codec = load("debug_codec", "iap2_input_business_lifecycle/reference-impl/input_codec.py")
    # Presence flag in 0x5200: total4 valid, total5 not an empty flag.
    good = bytes.fromhex("4040000a520000040001")
    bad = bytes.fromhex("4040000b52000005000100")
    assert codec.decode_message(good)["params"][0]["len"] == 4
    assert codec.decode_message(bad)["params"][0]["len"] == 5  # structural decode succeeds
    assert codec.wire_len_ok(good[6:], "empty")
    assert not codec.wire_len_ok(bad[6:], "empty")  # semantic typed check differs
    # Only this typed boundary is executed; firmware handler effects are not emulated.


def D03():
    response = b"RTSP/1.0 200 OK\r\nCSeq: 7\r\nContent-Length: 0\r\n\r\n"
    assert diag.inspect_rtsp_response(response, 7)["result"] == "MATCHED_RESPONSE"
    assert diag.inspect_rtsp_response(response, 8)["result"] == "CSEQ_MISMATCH"
    assert diag.inspect_rtsp_response(response.replace(b"CSeq: 7", b"CSeq: 7\r\nCSeq: 8"), 7)["result"] == "AMBIGUOUS_HEADER"


def D04():
    response = b"RTSP/1.0 200 OK\r\nCSeq: 7\r\nContent-Length: 4\r\n\r\nab"
    assert diag.inspect_rtsp_response(response, 7)["result"] == "NEED_MORE"
    assert diag.inspect_rtsp_response(response + b"cd", 7)["result"] == "MATCHED_RESPONSE"
    out = diag.inspect_rtsp_response(response + b"cdNEXT", 7)
    assert out["remaining"] == 4  # not misreported as oversized first body
    assert diag.inspect_rtsp_response(response.replace(b"Length: 4", b"Length: -1"), 7)["result"] == "BAD_LENGTH"
    chunk = b"RTSP/1.0 200 OK\r\nCSeq: 7\r\nTransfer-Encoding: chunked\r\n\r\n"
    assert diag.inspect_rtsp_response(chunk, 7)["result"] == "UNSUPPORTED_TRANSFER_ENCODING"


def D05():
    crypto = load("debug_crypto", "airplay_fairplay_crypto/reference-impl/fairplay_crypto.py")
    # Public synthetic inputs, never a real session/key. Candidate algorithm only.
    key, nonce, aad = bytes(range(32)), bytes(8), bytes(range(128))
    sealed = crypto.chacha20_poly1305_seal(key, nonce, b"synthetic", aad)
    assert crypto.chacha20_poly1305_open(key, nonce, sealed, aad) == b"synthetic"
    assert crypto.chacha20_poly1305_open(key, nonce, sealed[:-1] + bytes([sealed[-1] ^ 1]), aad) is None
    changed = bytes([aad[0] ^ 1]) + aad[1:]
    assert crypto.chacha20_poly1305_open(key, nonce, sealed, changed) is None
    assert crypto.chacha20_poly1305_open(key, nonce, sealed, aad) == b"synthetic"
    # Same visible failure for two different inputs: not sufficient to identify root cause.


def D06():
    audio = load("debug_audio", "airplay_audio_mic_channel/reference-impl/audio_depacketizer.py")
    good = bytes.fromhex("806000010000000100000001aabb")
    assert audio.parse_header(good)["header_len"] == 12
    bad = bytes([0x82]) + good[1:]  # declares 2 CSRCs that aren't there
    try:
        audio.parse_header(bad)
    except audio.PacketError as exc:
        assert exc.code == "SHORT_CSRC"
    else:
        raise AssertionError("short CSRC accepted")
    msg = bytes.fromhex("00010102030405060708") + b"x" + bytes(24)
    assert audio.aad_for_message(msg) == bytes.fromhex("0102030405060708")
    out = audio.split_message_record(msg, trailer_layout="tag16_nonce8")
    assert out["authenticated"] is False  # slicing != decryption/verification


def D07():
    fsm = load("debug_fsm", "iap2_input_business_lifecycle/reference-impl/lifecycle_fsm.py")
    lc = fsm.Lifecycle()
    lc.apply("RECONNECT", epoch=lc.epoch)
    old = lc.epoch
    lc.apply("ESTABLISHED", epoch=lc.epoch)
    assert not lc.can_send_business
    reject(lc.apply, "READY", epoch=lc.epoch, authenticated=False, identified=True, feature_ready=True)
    lc.apply("DETACH", epoch=lc.epoch)
    lc.apply("RECONNECT", epoch=lc.epoch)
    lc.apply("ESTABLISHED", epoch=lc.epoch)
    reject(lc.apply, "READY", epoch=old, authenticated=True, identified=True, feature_ready=True)
    assert not lc.can_send_business
    lc.apply("READY", epoch=lc.epoch, authenticated=True, identified=True, feature_ready=True)
    lc.apply("SUSPEND", epoch=lc.epoch)
    lc.apply("RESUME", epoch=lc.epoch)
    assert lc.timers_paused and not lc.can_send_business


def D08():
    out = diag.filters("192.0.2.10", [49152, 7123], [51000, 51001])
    assert out["capture"] == "(udp port 5353) or (host 192.0.2.10 and (tcp port 7123 or tcp port 49152 or udp port 51000 or udp port 51001))"
    assert "tcp.port == 7123" in out["display"] and "udp.port == 51001" in out["display"]
    assert "7000" not in out["capture"] and "6000" not in out["capture"]
    assert "ipv6.addr == fe80::1" in diag.filters("fe80::1", [7123], []) ["display"]
    for ports in ([0], [65536], [True], ["7000"]):
        reject(diag.filters, "192.0.2.10", ports, [])
    reject(diag.filters, "192.0.2.10 or host 1.1.1.1", [7123], [])
    reject(diag.filters, "fe80::1%3", [7123], [])
    reject(diag.filters, "192.0.2.10", [], [])


def D09():
    # A synthetic SETUP failure envelope: no claim that any real car returned it.
    out = diag.inspect_rtsp_response(b"RTSP/1.0 461 Unsupported Transport\r\nCSeq: 9\r\nContent-Length: 0\r\n\r\n", 9)
    assert out["result"] == "MATCHED_RESPONSE" and out["status"] == 461
    assert out["status_class"] == 4
    server = diag.inspect_rtsp_response(b"RTSP/1.0 500 Error\r\nCSeq: 9\r\n\r\n", 9)
    assert server["status"] == 500 and server["status_class"] == 5
    assert "root_cause" not in out and "osstatus" not in out


def D10():
    good = dict(conn_id=1, epoch=2, op_id=3, mono_ns=10, layer="pairing", event="verified",
                outcome="fail", direction="local", domain="coreutils", code=-6709)
    assert '"code":-6709' in diag.safe_event(good)
    for injected in ({**good, "key": "SECRET"}, {**good, "code": {"secret": "SECRET"}},
                     {**good, "event": "verified\nSECRET"}, {**good, "mono_ns": True},
                     {**good, "domain": "SECRET"}):
        try:
            diag.safe_event(injected)
        except ValueError as exc:
            assert str(exc) == "invalid diagnostic event"
        else:
            raise AssertionError("unsafe metadata accepted")


CASES = {name: globals()[name] for name in ("D01", "D02", "D03", "D04", "D05", "D06", "D07", "D08", "D09", "D10")}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--case", choices=["ALL", *CASES], default="ALL")
    args = parser.parse_args()
    selected = CASES if args.case == "ALL" else {args.case: CASES[args.case]}
    for name, fn in selected.items():
        fn()
        print(f"PASS {name}: SYNTHETIC local checks only")


if __name__ == "__main__":
    main()
