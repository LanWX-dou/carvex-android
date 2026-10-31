#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Resolve `_kAP*` CFString constant names in 24A446 images.

Why this exists: the constant pointer slots carry arm64e auth/rebased values
(bit31 flipped, image nibble in the payload) and the images have no
LC_DYLD_CHAINED_FIXUPS, so neither otool nor Ghidra relocates them.

Decode used (empirically validated against three independently known targets):
    addr = (slot_u64 & 0x7FFFFFFF) | (hi << 32)     for hi in 0..0xF
A slot points at a __cfstring struct  {isa, flags, data_ptr, length}; the
string bytes live at data_ptr (same decode). We accept a candidate only when
the final bytes are printable ASCII and report ambiguity explicitly.
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load(img):
    base = os.path.join(ROOT, "source")
    segs = json.load(open(os.path.join(base, "metadata", img, "segments.json"), encoding="utf-8"))
    blob = open(os.path.join(base, "firmware", img), "rb").read()
    syms = json.load(open(os.path.join(base, "metadata", img, "symbols.json"), encoding="utf-8"))
    return segs, blob, syms


def off_of(segs, va):
    for s in segs:
        if s["vmaddr"] <= va < s["vmaddr"] + s["filesize"]:
            return s["fileoff"] + (va - s["vmaddr"])
    return None


def cstr(blob, o, limit=96):
    end = blob.find(b"\x00", o, o + limit)
    if end < 0:
        return None
    raw = blob[o:end]
    if not raw or any(c < 0x20 or c > 0x7E for c in raw):
        return None
    return raw.decode("ascii")


def candidates(segs, blob, slot):
    o = off_of(segs, slot)
    if o is None:
        return []
    v = int.from_bytes(blob[o:o + 8], "little")
    low = v & 0x7FFFFFFF
    return [low | (hi << 32) for hi in range(16) if off_of(segs, low | (hi << 32)) is not None]


def decode_string(segs, blob, va):
    """va -> (string, struct_va, data_va) or (None, None, None)."""
    o = off_of(segs, va)
    if o is None:
        return None, None, None
    d = cstr(blob, o)
    if d:
        return d, None, None
    struct = va
    flags = int.from_bytes(blob[o + 8:o + 12], "little")
    if flags & 0x10:  # inline buffer
        return cstr(blob, o + 0x10), struct, va
    ptr = int.from_bytes(blob[o + 16:o + 24], "little")
    low = ptr & 0x7FFFFFFF
    for hi in range(16):
        da = low | (hi << 32)
        oo = off_of(segs, da)
        if oo is None:
            continue
        s = cstr(blob, oo)
        if s:
            return s, struct, da
    return None, None, None


def resolve(segs, blob, slot):
    hits = []
    for va in candidates(segs, blob, slot):
        s, struct, data = decode_string(segs, blob, va)
        if s:
            hits.append((s, va, struct, data))
    return hits


def main():
    img = sys.argv[1] if len(sys.argv) > 1 else "AirPlaySender"
    prefix = sys.argv[2] if len(sys.argv) > 2 else "_kAP"
    segs, blob, syms = load(img)
    rows = []
    for s in syms:
        if not s["name"].startswith(prefix):
            continue
        hits = resolve(segs, blob, s["addr"])
        rows.append({"name": s["name"], "slot": s["addr"], "hits": hits})
    rows.sort(key=lambda r: r["name"])
    bad = 0
    amb = 0
    for r in rows:
        if not r["hits"]:
            bad += 1
            print("%-54s slot=%#x  UNRESOLVED" % (r["name"], r["slot"]))
            continue
        if len(r["hits"]) > 1:
            amb += 1
        s, va, struct, data = r["hits"][0]
        print("%-54s slot=%#x  cf=%#x  data=%#x  %-30s%s" % (
            r["name"], r["slot"], struct or 0, data or 0, '"' + s + '"',
            "  AMBIGUOUS(%d)" % len(r["hits"]) if len(r["hits"]) > 1 else ""))
    print("\n%d symbols, %d unresolved, %d ambiguous" % (len(rows), bad, amb))


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8", errors="backslashreplace")
    main()
