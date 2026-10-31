#!/usr/bin/env python3
"""Offline diagnostic helpers: no sockets, credentials or automatic root-cause claims."""
import argparse
import ipaddress
import json
import re


def filters(peer, tcp_ports, udp_ports):
    """Use CURRENT negotiated ports. Returns BPF and display strings, not commands."""
    if not isinstance(peer, str) or "%" in peer:
        raise ValueError("invalid peer; select scope via capture interface")
    addr = ipaddress.ip_address(peer)

    def ports(values):
        if any(type(x) is not int or not 1 <= x <= 65535 for x in values):
            raise ValueError("invalid port")
        return sorted(set(values))

    tcp, udp = ports(tcp_ports), ports(udp_ports)
    if not tcp and not udp:
        raise ValueError("negotiated endpoints required")
    bpf = [f"{proto} port {p}" for proto, values in (("tcp", tcp), ("udp", udp)) for p in values]
    display = [f"{proto}.port == {p}" for proto, values in (("tcp", tcp), ("udp", udp)) for p in values]
    family = "ip" if addr.version == 4 else "ipv6"
    return {
        "capture": f"(udp port 5353) or (host {addr} and ({' or '.join(bpf)}))",
        "display": f"(udp.port == 5353) or ({family}.addr == {addr} and ({' or '.join(display)}))",
    }


ENUMS = {
    "layer": {"bluetooth", "iap2_link", "identification", "authentication", "network",
              "pairing", "rtsp", "crypto", "video", "audio", "microphone", "input", "lifecycle"},
    "event": {"queued", "written", "received", "parsed", "gate", "verified", "decoded",
              "presented", "timeout", "detached", "dropped"},
    "outcome": {"pass", "fail", "pending"},
    "direction": {"tx", "rx", "local"},
    "domain": {"local", "posix", "winsock", "hci", "iap2", "rtsp", "pairing_tlv",
               "coreutils", "airplay_sender"},
}
REQUIRED_INTS = {"conn_id", "epoch", "op_id", "mono_ns"}
OPTIONAL_INTS = {"stream_id", "byte_count", "frame_count", "dropped_count"}


def safe_event(fields):
    """Whitelist metadata only; NOT a sanitizer for raw captures/third-party log strings.

    Fixed rejection message never echoes field names, values or secret-containing exceptions.
    Caller must allocate anonymous integer IDs, not encode identifiers into integers.
    """
    allowed = set(ENUMS) | REQUIRED_INTS | OPTIONAL_INTS | {"code"}
    if type(fields) is not dict or set(fields) - allowed or not (set(ENUMS) | REQUIRED_INTS) <= set(fields):
        raise ValueError("invalid diagnostic event")
    for k, choices in ENUMS.items():
        if type(fields[k]) is not str or fields[k] not in choices:
            raise ValueError("invalid diagnostic event")
    for k in REQUIRED_INTS | OPTIONAL_INTS:
        if k in fields and (type(fields[k]) is not int or not 0 <= fields[k] < 2**63):
            raise ValueError("invalid diagnostic event")
    if "code" in fields and (type(fields["code"]) is not int or not -(2**31) <= fields["code"] < 2**32):
        raise ValueError("invalid diagnostic event")
    return json.dumps(fields, sort_keys=True, separators=(",", ":"))


def inspect_rtsp_response(data, expected_cseq):
    """Inspect first plaintext RTSP/1.0 response after stream reassembly/authentication.

    Caller scopes expected_cseq to current connection/epoch. No HTTP, binary interleaving,
    chunk decoding, encryption, or full RTSP parser. Limits are LOCAL diagnostic policy.
    No body/header value is returned or logged. Bytes after the first message are counted.
    """
    if type(data) is not bytes or type(expected_cseq) is not int or not 0 <= expected_cseq <= 2**31-1:
        raise ValueError("invalid diagnostic input")
    split = data.find(b"\r\n\r\n")
    if split < 0:
        return {"result": "LOCAL_LIMIT" if len(data) > 65536 else "NEED_MORE"}
    if split > 65536:
        return {"result": "LOCAL_LIMIT"}
    lines = data[:split].split(b"\r\n")
    first = re.fullmatch(rb"RTSP/1\.0 ([0-9]{3})(?: [^\r\n]*)?", lines[0])
    if not first:
        return {"result": "UNSUPPORTED_OR_BAD_STATUS_LINE"}
    status = int(first[1])
    headers = {}
    for line in lines[1:]:
        if b":" not in line:
            return {"result": "BAD_HEADER", "status": status}
        name, value = line.split(b":", 1)
        if not re.fullmatch(rb"[!#$%&'*+.^_`|~0-9A-Za-z-]+", name):
            return {"result": "BAD_HEADER", "status": status}
        name, value = name.lower(), value.strip(b" \t")
        if name in (b"cseq", b"content-length", b"transfer-encoding") and name in headers:
            return {"result": "AMBIGUOUS_HEADER", "status": status}
        headers[name] = value
    if b"transfer-encoding" in headers:
        return {"result": "UNSUPPORTED_TRANSFER_ENCODING", "status": status}
    seq = headers.get(b"cseq", b"")
    length = headers.get(b"content-length", b"0")
    if not re.fullmatch(rb"[0-9]{1,10}", seq):
        return {"result": "BAD_CSEQ", "status": status}
    if not re.fullmatch(rb"[0-9]{1,10}", length):
        return {"result": "BAD_LENGTH", "status": status}
    size = int(length)
    if size > 1024 * 1024:
        return {"result": "LOCAL_LIMIT", "status": status}
    end = split + 4 + size
    if len(data) < end:
        return {"result": "NEED_MORE", "status": status}
    # Diagnostic result is not evidence the peer executed the requested operation.
    result = "CSEQ_MISMATCH" if int(seq) != expected_cseq else "MATCHED_RESPONSE"
    return {"result": result, "status": status, "status_class": status // 100,
            "consumed": end, "remaining": len(data) - end}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate offline filters from actual negotiated endpoints")
    parser.add_argument("--peer", required=True)
    parser.add_argument("--tcp", nargs="*", type=int, default=[])
    parser.add_argument("--udp", nargs="*", type=int, default=[])
    args = parser.parse_args()
    print(json.dumps(filters(args.peer, args.tcp, args.udp), indent=2))
