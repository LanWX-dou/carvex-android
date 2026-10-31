#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""RTSP/1.0 message framing used by the AirPlay control plane (reference only).

Wire rules reproduced from 24A446 evidence:
  * request line: "<method> SP <url> SP RTSP/1.0 CRLF"   (A01.2, INFERRED shape)
  * headers: "Name: value CRLF", terminated by an empty CRLF line
  * body: Content-Length bytes, or chunked when Transfer-Encoding: chunked (A01.7/A01.8)
No platform API is used; no key material appears here.
"""


class RTSPError(ValueError):
    pass


def encode_request(method, url, headers, body=b""):
    """Build a request. `headers` is an ordered list of (name, value).

    CSeq must be supplied by the caller: it is per-connection and
    incremented by the caller before use (A01.5).
    """
    if not method or not url:
        raise RTSPError("method/url required")
    names = [h[0].lower() for h in headers]
    if "cseq" not in names:
        raise RTSPError("CSeq is mandatory (A01.5)")
    if body and "content-length" not in names:
        raise RTSPError("Content-Length is mandatory when a body is present (A01.7)")
    if "content-length" in names and not body:
        # 允许，但值必须为 0；这里强制一致以免发出矛盾报文
        pass
    out = bytearray()
    out += ("%s %s RTSP/1.0\r\n" % (method, url)).encode()
    for k, v in headers:
        out += ("%s: %s\r\n" % (k, v)).encode()
    out += b"\r\n"
    out += body
    return bytes(out)


def _parse_head(blob):
    end = blob.find(b"\r\n\r\n")
    if end < 0:
        raise RTSPError("header block not terminated")
    head = blob[:end].decode("latin-1")
    rest = blob[end + 4:]
    lines = head.split("\r\n")
    first, headers = lines[0], []
    for line in lines[1:]:
        if not line:
            continue
        if ":" not in line:
            raise RTSPError("bad header line: %r" % line)
        k, v = line.split(":", 1)
        headers.append((k.strip(), v.strip()))
    return first, headers, rest


def parse_response(blob):
    """Return (status_code, reason, headers, body)."""
    first, headers, rest = _parse_head(blob)
    parts = first.split(" ", 2)
    if len(parts) < 2 or not parts[0].startswith("RTSP/"):
        raise RTSPError("bad status line: %r" % first)
    try:
        code = int(parts[1])
    except ValueError:
        raise RTSPError("bad status code: %r" % first)
    reason = parts[2] if len(parts) > 2 else ""
    hmap = {k.lower(): v for k, v in headers}
    if hmap.get("transfer-encoding", "").lower() == "chunked":
        body, _ = decode_chunked(rest)
        return code, reason, headers, body
    if "content-length" in hmap:
        try:
            n = int(hmap["content-length"])
        except ValueError:
            raise RTSPError("bad Content-Length")
        if len(rest) < n:
            raise RTSPError("truncated body: %d < %d" % (len(rest), n))
        return code, reason, headers, rest[:n]
    return code, reason, headers, rest


def decode_chunked(buf):
    """Decode a chunked body; returns (body, consumed)."""
    out = bytearray()
    pos = 0
    while True:
        eol = buf.find(b"\r\n", pos)
        if eol < 0:
            raise RTSPError("chunk size line not terminated")
        size_line = buf[pos:eol].split(b";", 1)[0].strip()
        try:
            size = int(size_line, 16)
        except ValueError:
            raise RTSPError("bad chunk size: %r" % size_line)
        pos = eol + 2
        if size == 0:
            nxt = buf.find(b"\r\n", pos)
            if nxt < 0:
                raise RTSPError("missing trailer terminator")
            return bytes(out), nxt + 2
        if len(buf) < pos + size + 2:
            raise RTSPError("truncated chunk")
        out += buf[pos:pos + size]
        pos += size
        if buf[pos:pos + 2] != b"\r\n":
            raise RTSPError("chunk not followed by CRLF")
        pos += 2
