#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Resolve ADRP(+ADD) pairs inside an exported .s file to the C string they point at.

Usage:  python3 tools/asm-strings.py <image> <file.s>
"""
import json
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MD = os.path.join(ROOT, "source", "metadata")
SRC = os.path.join(ROOT, "source", "firmware")

LINE = re.compile(r"^(0x[0-9a-f]+):\t(\S+)\t(.*)$")


def main() -> int:
    img, path = sys.argv[1], sys.argv[2]
    segs = json.load(open(os.path.join(MD, img, "segments.json"), encoding="utf-8"))
    blob = open(os.path.join(SRC, img), "rb").read()

    def vm2off(v):
        for s in segs:
            if s["vmaddr"] <= v < s["vmaddr"] + s["filesize"]:
                return s["fileoff"] + (v - s["vmaddr"])
        return None

    def cstr(v, n=120):
        o = vm2off(v)
        if o is None:
            return None
        end = blob.find(b"\x00", o)
        if end < 0:
            return None
        raw = blob[o:min(end, o + n)]
        if not raw:
            return None
        try:
            s = raw.decode("utf-8")
        except UnicodeDecodeError:
            return None
        if not all(0x20 <= ord(ch) < 0x7f for ch in s):
            return None
        return s

    regs = {}
    pending = {}
    for line in open(path, encoding="utf-8"):
        m = LINE.match(line.rstrip("\n"))
        if not m:
            continue
        addr, mn, ops = m.group(1), m.group(2), m.group(3)
        if mn == "adrp":
            r = re.match(r"(x\d+), #(0x[0-9a-f]+)", ops)
            if r:
                pending[r.group(1)] = int(r.group(2), 16)
                regs.pop(r.group(1), None)
        elif mn == "add":
            r = re.match(r"(x\d+), (x\d+), #(0x[0-9a-f]+)", ops)
            if r and r.group(2) in pending and pending[r.group(2)] is not None:
                v = pending[r.group(1)] + int(r.group(3), 16)
                s = cstr(v)
                if s is not None:
                    print("%s  %#x  %r" % (addr, v, s))
                pending.pop(r.group(1), None)
        elif mn in ("ldr", "str", "ldrb", "strb", "mov", "bl", "b", "cmp"):
            r = re.match(r"(x\d+),", ops)
            if r:
                pending.pop(r.group(1), None)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
