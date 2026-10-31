#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""解析 23G90 的 accessoryd 包日志，打印 AirPlay 连接的逐帧表。

用法（在 research/protocol/iap2_airplay_tunnel 下）：
    python3 runtime/parse-capture.py [文件]

只做结构解析：链路头字段 + iAP2 消息头；不解释消息语义。
"""
import hashlib
import re
import sys

FRAME = re.compile(
    r"; (?P<uuid>[0-9A-F-]{36}); (?P<transport>[^;]+); (?P<side>Acc|iPod); "
    r"len=0x(?P<len>[0-9a-f]+); control=0x(?P<ctl>[0-9a-f]+); "
    r"seq=0x(?P<seq>[0-9a-f]+); ack=0x(?P<ack>[0-9a-f]+); "
    r"session=0x(?P<ses>[0-9a-f]+); hdrChk=0x(?P<hc>[0-9a-f]+); "
    r"payload\(len=(?P<plen>\d+) chk=0x(?P<pc>[0-9a-f]+)\)=<(?P<payload>[^>]*)>"
)


def main() -> int:
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    want_all = "--all" in sys.argv
    path = args[0] if args else \
        "runtime/accessoryd-packets-2026-10-16-221117.log.ips"
    blob = open(path, "rb").read()
    print("file     :", path)
    print("size     :", len(blob))
    print("sha256   :", hashlib.sha256(blob).hexdigest())
    text = blob.decode("utf-8", "replace")
    frames = []
    for line in text.splitlines():
        m = FRAME.search(line)
        if not m:
            continue
        payload = bytes.fromhex(m.group("payload"))
        frames.append({
            "transport": m.group("transport").strip(),
            "side": m.group("side"),
            "len": int(m.group("len"), 16),
            "ctl": int(m.group("ctl"), 16),
            "seq": int(m.group("seq"), 16),
            "ses": int(m.group("ses"), 16),
            "plen": int(m.group("plen")),
            "payload": payload,
        })
    uuids = {}
    for f in frames:
        uuids.setdefault((f["transport"],), 0)
    print("frames   :", len(frames))
    print()
    if not want_all:
        frames = [f for f in frames if f["transport"].startswith("AirPlay")]
        print("filter   : transport=AirPlay,", len(frames), "frames")
        print()

    idx = 0
    for f in frames:
        if f["plen"] == 0:
            continue
        idx += 1
        p = f["payload"]
        kind = "?"
        if len(p) >= 6 and p[0:2] == b"\x40\x40":
            total = int.from_bytes(p[2:4], "big")
            msgid = int.from_bytes(p[4:6], "big")
            ok = "ok" if total == len(p) else "LEN-MISMATCH %d!=%d" % (total, len(p))
            kind = "iAP2 0x%04X (%s)" % (msgid, ok)
        else:
            kind = "link-control"
        print("%2d %-6s ctl=0x%02x seq=0x%02x ses=0x%02x len=%4d  %s"
              % (idx, f["side"], f["ctl"], f["seq"], f["ses"], f["len"], kind))
        if len(p) and p[0:2] == b"\x40\x40":
            print("      " + p[:32].hex(" "))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
