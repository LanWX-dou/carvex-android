#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find ADRP(+ADD|LDR) xrefs to a virtual address inside one image.

Usage:
    python3 tools/find-xrefs.py <image> <target-hex> [--all]

Reads source/metadata/<image>/segments.json and source/firmware/<image>.
Prints instruction addresses (and the enclosing zone by symbol when available).
"""
import json
import os
import struct
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MD = os.path.join(ROOT, "source", "metadata")
SRC = os.path.join(ROOT, "source", "firmware")


def segs(img):
    return json.load(open(os.path.join(MD, img, "segments.json"), encoding="utf-8"))


def text_range(img):
    for s in segs(img):
        if s["segname"] == "__TEXT":
            return s["vmaddr"], s["fileoff"], s["filesize"]
    raise SystemExit("no __TEXT")


def main() -> int:
    img = sys.argv[1]
    target = int(sys.argv[2], 16)
    show_all = "--all" in sys.argv
    vm, fo, fs = text_range(img)
    blob = open(os.path.join(SRC, img), "rb").read()
    body = blob[fo:fo + fs]
    hits = []
    for i in range(0, len(body) - 8, 4):
        word = struct.unpack_from("<I", body, i)[0]
        if (word & 0x9F000000) != 0x90000000:
            continue
        rd = word & 0x1F
        imm = (((word >> 5) & 0x7FFFF) << 2) | ((word >> 29) & 0x3)
        if imm & (1 << 20):
            imm -= 1 << 21
        pc = vm + i
        page = ((pc >> 12) << 12) + (imm << 12)
        follow = struct.unpack_from("<I", body, i + 4)[0]
        val = None
        if (follow & 0xFF800000) == 0x91000000 and ((follow >> 5) & 0x1F) == rd:
            imm12 = (follow >> 10) & 0xFFF
            if (follow >> 22) & 0x1:
                imm12 <<= 12
            val = page + imm12
        elif (follow & 0xFFC00000) == 0xF9400000 and ((follow >> 5) & 0x1F) == rd:
            val = page + ((follow >> 10) & 0xFFF) * 8
        if val == target:
            hits.append(pc)
    print("image=%s target=0x%x hits=%d" % (img, target, len(hits)))
    for pc in (hits if show_all else hits[:40]):
        print("  0x%x" % pc)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
