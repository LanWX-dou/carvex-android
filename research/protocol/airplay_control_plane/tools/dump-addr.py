# -*- coding: utf-8 -*-
"""Dump C strings at virtual addresses for an image."""
import json, re, sys
from pathlib import Path
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = Path(__file__).resolve().parents[1]
MD = ROOT / "source/metadata"
SRC = ROOT / "source/firmware"

img = sys.argv[1]
addrs = [int(a, 16) for a in sys.argv[2:]]
blob = (SRC / img).read_bytes()
segs = json.loads((MD / img / "segments.json").read_text(encoding="utf-8"))

def vm2off(v):
    for s in segs:
        if s["vmaddr"] <= v < s["vmaddr"] + s["filesize"]:
            return s["fileoff"] + (v - s["vmaddr"])
    return None

for a in addrs:
    o = vm2off(a)
    if o is None:
        print("0x%x : unmapped" % a); continue
    end = blob.find(b"\x00", o)
    raw = blob[o:min(end, o + 240)]
    try:
        s = raw.decode("utf-8")
    except UnicodeDecodeError:
        s = raw.decode("latin-1")
    print("0x%x : %r" % (a, s))
