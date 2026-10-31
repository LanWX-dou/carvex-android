#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Extract the 4CC -> (method, path, content-type) switch from APTransportPackageHTTPGetHTTPMessage.

Heuristic, instruction-level: tracks mov/movk into the register compared against w21,
then follows the taken branch and collects adrp/add pairs assigned to x23/x24/x22
(method/path/content-type) until the next control transfer.

Usage: python3 tools/extract-4cc-table.py <image> <file.s>
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

    def cstr(v, n=80):
        for s in segs:
            if s["vmaddr"] <= v < s["vmaddr"] + s["filesize"]:
                o = s["fileoff"] + (v - s["vmaddr"])
                end = blob.find(b"\x00", o)
                if end < 0 or end - o > n:
                    return None
                raw = blob[o:end]
                if not raw:
                    return None
                try:
                    out = raw.decode("utf-8")
                except UnicodeDecodeError:
                    return None
                if all(0x20 <= ord(c) < 0x7f for c in out):
                    return out
        return None

    ins = []
    for line in open(path, encoding="utf-8"):
        m = LINE.match(line.rstrip("\n"))
        if m:
            ins.append((int(m.group(1), 16), m.group(2), m.group(3)))
    byaddr = {a: (m, o) for a, m, o in ins}

    def mov_val(i):
        """Collect value built by consecutive mov/movk into one register at ins[i]."""
        a, mn, ops = ins[i]
        m = re.match(r"(w\d+|x\d+), #(0x[0-9a-f]+)", ops)
        if not m or mn not in ("mov", "movk"):
            return None
        reg, val = m.group(1), int(m.group(2), 16)
        shift = 0
        mm = re.search(r"lsl #(\d+)", ops)
        if mm:
            shift = int(mm.group(1))
        val <<= shift
        # walk backwards for movk pieces of same reg
        j = i - 1
        while j >= 0:
            pa, pmn, pops = ins[j]
            pm = re.match(r"(%s), #(0x[0-9a-f]+)" % re.escape(reg), pops)
            if pmn in ("mov", "movk") and pm:
                pv = int(pm.group(2), 16)
                psv = re.search(r"lsl #(\d+)", pops)
                psh = int(psv.group(1)) if psv else 0
                mask = ~(0xFFFF << psh) & 0xFFFFFFFFFFFFFFFF
                val = (val & mask) | ((pv & 0xFFFF) << psh)
                j -= 1
                continue
            break
        return val

    rows = []
    for i, (a, mn, ops) in enumerate(ins):
        if mn != "cmp" or not ops.startswith("w21,"):
            continue
        m = re.match(r"w21, (w\d+)", ops)
        if not m:
            continue
        # find the definition of the compared register just above
        reg = m.group(1)
        val = None
        for j in range(i - 1, max(0, i - 6), -1):
            if ins[j][2].startswith(reg + ",") and ins[j][1] in ("mov", "movk"):
                val = mov_val(j)
                if val is not None:
                    break
        if val is None:
            continue
        # next b.eq
        tgt = None
        for j in range(i + 1, min(len(ins), i + 4)):
            mm = re.match(r"#(0x[0-9a-f]+)", ins[j][2])
            if ins[j][1] in ("b.eq", "b.ne") and mm:
                if ins[j][1] == "b.eq":
                    tgt = int(mm.group(1), 16)
                break
        if tgt is None:
            continue
        # walk target block: collect string assignments + follow plain branches
        seen = set()
        cur = tgt
        method = ctype = url = None
        for _ in range(60):
            if cur in seen or cur not in byaddr:
                break
            seen.add(cur)
            k = [x[0] for x in ins].index(cur)
            mn2, ops2 = ins[k][1], ins[k][2]
            if mn2 == "adrp":
                rm = re.match(r"(x\d+), #(0x[0-9a-f]+)", ops2)
                if rm and k + 1 < len(ins) and ins[k + 1][1] == "add":
                    am = re.match(r"(%s), %s, #(0x[0-9a-f]+)" % (rm.group(1), rm.group(1)), ins[k + 1][2])
                    if am:
                        s = cstr(int(rm.group(2), 16) + int(am.group(2), 16))
                        if s:
                            if rm.group(1) == "x23":
                                method = s
                            elif rm.group(1) == "x24":
                                url = s
                            elif rm.group(1) == "x22":
                                ctype = s
            if mn2 in ("b", "b.eq") and ops2.startswith("#"):
                cur = int(ops2[1:], 16)
                continue
            if mn2 == "ret" or mn2 == "retab":
                break
            cur += 4
        rows.append((val, method, url, ctype, a))

    print("const       4CC   method              path                     content-type            cmp@")
    for val, method, url, ctype, a in rows:
        fourcc = bytes([(val >> s) & 0xFF for s in (24, 16, 8, 0)]).decode("latin-1")
        print("0x%08x  %-5s %-19s %-24s %-23s 0x%x" % (val, fourcc, method, url, ctype, a))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
