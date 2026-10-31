"""Read-only 24A446 native Mach-O inspection. Output goes only to stdout.

Xrefs are bounded ADRP/ADD candidates, not semantic proof. Review the complete
containing function. Original bytes, function boundaries and source hash are
reported; no source image or existing decompiler cache is modified.
"""
from pathlib import Path
import argparse
import bisect
import hashlib
import json
import re
import struct
import sys

sys.dont_write_bytecode = True
FW = Path(__file__).resolve().parents[2] / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("mode", choices=["xrefs", "function", "pointers", "methods", "callers", "verify", "sdp", "field", "slice"])
    p.add_argument("--component", default="bluetoothd")
    p.add_argument("--address", action="append", default=[])
    p.add_argument("--regex", default="CarPlay|Carplay|carplay|WiAP|Wireless IAP")
    p.add_argument("--count", type=int, default=16)
    a = p.parse_args()
    sources = list((FW / "extracted/24A446/components").rglob(a.component))
    sources = [x for x in sources if x.is_file()]
    assert len(sources) == 1, sources
    im = Image(sources[0])
    print(json.dumps({"component": a.component, "source": str(sources[0]),
                      "sha256": hashlib.sha256(im.data).hexdigest()}))
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    start, length, _ = im.sections[("__TEXT", "__text")]

    def bounds(at):
        i = bisect.bisect_right(im.starts, at)
        return im.starts[i - 1], im.starts[i] if i < len(im.starts) else start + length

    addresses = [int(x, 0) for x in a.address]
    if a.mode == "methods":
        for row in im.methods:
            if re.search(a.regex, row["name"], re.I):
                print(json.dumps(row))
    elif a.mode in ("function", "verify", "slice"):
        for at in addresses:
            lo, hi = (at, at + a.count * 4) if a.mode == "slice" else bounds(at)
            raw = im.read(lo, hi - lo)
            print(json.dumps({"start": hex(lo), "end": hex(hi), "symbols": im.symbols.get(lo, []),
                              "raw_sha256": hashlib.sha256(raw).hexdigest()}))
            if a.mode == "verify":
                for cached in (FW / "analysis/decompiler-cache/24A446" / a.component).glob(f"*/functions/f_{lo:x}.bin"):
                    print(json.dumps({"cache": str(cached), "matches_source": cached.read_bytes() == raw}))
            else:
                for ins in md.disasm(raw, lo):
                    print(f"{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}")
    elif a.mode == "sdp":
        def element(at, depth=0):
            assert depth < 8
            raw = im.read(at, 16)
            kind, width, count = struct.unpack_from("<BBH", raw)
            row = {"address": hex(at), "raw": raw.hex(), "kind": kind, "width": width, "count": count}
            if kind in (6, 7):
                ptr = im.ptr(at + 8)
                assert count <= 20
                row["children"] = [element(ptr + i * 16, depth + 1) for i in range(count)]
            elif kind in (3, 4) and count > 4:
                ptr = im.ptr(at + 8)
                row["data_address"] = hex(ptr)
                row["data_hex"] = im.read(ptr, count).hex()
            else:
                row["value_raw"] = raw[8:].hex()
            return row
        for base in addresses:
            for at in range(base, base + a.count * 24, 24):
                print(json.dumps({"attribute": hex(struct.unpack("<I", im.read(at, 4))[0]),
                                  "element": element(at + 8)}))
    elif a.mode == "pointers":
        for base in addresses:
            for at in range(base, base + a.count * 8, 8):
                row = {"slot": hex(at), "raw": im.read(at, 8).hex()}
                try:
                    ptr = im.ptr(at)
                    row["target"] = hex(ptr)
                    if ptr:
                        row["bytes"] = im.read(ptr, 16).hex()
                        row["symbols"] = im.symbols.get(ptr, [])
                        try:
                            text = im.cstr(ptr)
                            if text and all(c.isprintable() or c in "\n\t" for c in text):
                                row["string"] = text
                        except (ValueError, UnicodeError):
                            pass
                except ValueError as e:
                    row["unresolved"] = str(e)
                print(json.dumps(row))
    elif a.mode == "field":
        offsets = set(addresses)
        for index, (word,) in enumerate(struct.iter_unpack("<I", im.read(start, length))):
            if word & 0xFFC00000 not in (0x39400000, 0x39000000):
                continue
            if (word >> 10 & 0xFFF) in offsets:
                at = start + index * 4
                ins = next(md.disasm(im.read(at, 4), at))
                print(json.dumps({"site": hex(at), "function": hex(bounds(at)[0]), "instruction": ins.mnemonic + " " + ins.op_str}))
    elif a.mode == "callers":
        targets = set(addresses)
        for index, (word,) in enumerate(struct.iter_unpack("<I", im.read(start, length))):
            if word & 0x7C000000 != 0x14000000:
                continue
            at = start + index * 4
            imm = word & 0x3FFFFFF
            if imm & 0x2000000:
                imm -= 0x4000000
            target = at + imm * 4
            if target in targets:
                print(json.dumps({"site": hex(at), "target": hex(target), "function": hex(bounds(at)[0]),
                                  "kind": "bl" if word & 0x80000000 else "b"}))
    elif a.mode == "xrefs":
        targets = {x: "explicit" for x in addresses}
        raw_index = FW / "analysis/24A446/raw" / (a.component + ".txt")
        if not targets:
            for line in raw_index.read_text(encoding="utf-8").splitlines():
                m = re.match(r'(0x[0-9a-f]+):\s+"(.*)"', line)
                if m and re.search(a.regex, m[2], re.I):
                    targets[int(m[1], 16)] = m[2]
        pages = {x & ~4095 for x in targets}
        recent = {}
        # Short linear candidate scan. Intervening writes/branches must be
        # reviewed in exported original assembly before accepting a reference.
        for index, (word,) in enumerate(struct.iter_unpack("<I", im.read(start, length))):
            at = start + index * 4
            if word & 0x9F000000 == 0x90000000:
                imm = ((word >> 5 & 0x7FFFF) << 2) | (word >> 29 & 3)
                if imm & 0x100000:
                    imm -= 0x200000
                page = (at & ~4095) + imm * 4096
                recent[word & 31] = (at, page)
            elif word & 0xFF000000 == 0x91000000:
                source = word >> 5 & 31
                if source not in recent:
                    continue
                prev, page = recent[source]
                if page not in pages or at - prev > 48:
                    continue
                offset = (word >> 10 & 0xFFF) << (12 if word & 0x400000 else 0)
                target = page + offset
                if target in targets:
                    print(json.dumps({"adrp": hex(prev), "site": hex(at), "function": hex(bounds(at)[0]),
                                      "target": hex(target), "string": targets[target],
                                      "qualification": "ADRP_ADD_CANDIDATE_REQUIRES_ASSEMBLY_REVIEW"}))


if __name__ == "__main__":
    main()
