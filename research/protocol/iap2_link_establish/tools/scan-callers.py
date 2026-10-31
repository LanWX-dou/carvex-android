#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ad-hoc caller/arg scanner for this docset (read-only helpers live in firmware/tools).

Usage:
    scan-callers.py <macho> <target-hex> [<target-hex> ...]

For every direct `bl` to a target it prints:
    call_site  target  caller_symbol  <arg heuristic: nearest preceding mov w<x>, #imm>

Optional: --writes <imm> lists `str/strb/strh wN, [xN, #<imm>]` sites, useful to
find who writes a struct field (e.g. link+0xc0).
"""
import bisect
import json
import sys

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM, ARM64_OP_REG


def load_segments(path):
    data = open(path, "rb").read()
    # minimal Mach-O 64 parser: header + LC_SEGMENT_64
    assert data[:4] == b"\xcf\xfa\xed\xfe", "not a 64-bit Mach-O"
    ncmds = int.from_bytes(data[16:20], "little")
    off = 32
    segs = []
    for _ in range(ncmds):
        cmd = int.from_bytes(data[off:off + 4], "little")
        size = int.from_bytes(data[off + 4:off + 8], "little")
        if cmd == 0x19:
            name = data[off + 8:off + 24].rstrip(b"\x00").decode()
            vmaddr = int.from_bytes(data[off + 24:off + 32], "little")
            vmsize = int.from_bytes(data[off + 32:off + 40], "little")
            fileoff = int.from_bytes(data[off + 40:off + 48], "little")
            filesize = int.from_bytes(data[off + 48:off + 56], "little")
            segs.append((name, vmaddr, vmsize, fileoff, filesize))
        off += size
    return data, segs


def va_to_off(segs, va):
    for name, vmaddr, vmsize, fileoff, filesize in segs:
        if vmaddr <= va < vmaddr + vmsize:
            return fileoff + (va - vmaddr)
    return None


def main() -> int:
    args = sys.argv[1:]
    writes = None
    targets = []
    path = None
    for a in args:
        if a == "--writes":
            writes = True
        elif writes and writes is not True and writes is not None:
            pass
        elif a.startswith("0x"):
            targets.append(int(a, 16))
        else:
            path = a
    if writes:
        # second pass: the first 0x… after --writes is the offset
        rest = args[args.index("--writes") + 1:]
        if rest:
            writes = int(rest[0], 16)
            if writes in targets:
                targets.remove(writes)
    data, segs = load_segments(path)
    text = next(s for s in segs if s[0] == "__TEXT")
    base = text[1]
    blob = data[text[3]:text[3] + text[4]]

    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    md.detail = True
    md.skipdata = True
    insns = []
    for ins in md.disasm(blob, base):
        insns.append(ins)

    funcs = []
    for name, vmaddr, vmsize, fileoff, filesize in segs:
        if name in ("__TEXT", "__TEXT_EXEC"):
            funcs = [vmaddr]
    if not funcs:
        funcs = [base]

    print("call_site\ttarget\tcaller\targ_w6\targ_w1")
    for i, ins in enumerate(insns):
        if ins.mnemonic != "bl" or not ins.operands:
            continue
        if ins.operands[0].type != ARM64_OP_IMM:
            continue
        tgt = ins.operands[0].imm
        if tgt not in targets:
            continue
        w6 = w1 = None
        for back in range(1, 14):
            if i - back < 0:
                break
            p = insns[i - back]
            if p.mnemonic in ("mov", "movz", "orr") and len(p.operands) == 2:
                if p.operands[0].type == ARM64_OP_REG and p.operands[1].type == ARM64_OP_IMM:
                    reg = p.reg_name(p.operands[0].reg)
                    if reg == "w6" and w6 is None:
                        w6 = p.operands[1].imm
                    if reg == "w1" and w1 is None:
                        w1 = p.operands[1].imm
        print("0x%x\t0x%x\t0x%x\t%s\t%s" % (ins.address, tgt,
              max([f for f in funcs if f <= ins.address] or [0]),
              ("0x%x" % w6) if w6 is not None else "-",
              ("0x%x" % w1) if w1 is not None else "-"))
    if writes is not None:
        print("--- writes to [reg, #0x%x]" % writes)
        for ins in insns:
            if not ins.mnemonic.startswith("str") or len(ins.operands) < 2:
                continue
            m = ins.operands[1]
            if m.type == ARM64_OP_MEM and m.mem.disp == writes and ins.reg_name(m.base) in ("x0", "x19", "x20", "x8", "x9", "x10", "x22", "x23", "x24"):
                print("0x%x\t%s\t%s" % (ins.address, ins.mnemonic, ins.op_str))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
