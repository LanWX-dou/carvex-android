"""Resolve AP-U05 in the original dyld subcaches, never rewriting references.

Reads shared-cache mappings and v5 slide pointers using the reviewed read-only
firmware_cache module. Output contains public constants/code only, no secrets.
Uses no historic field-reference JSON as input. NOT a runtime/vehicle test.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_cache import Cache
from firmware_image import Image


def sha(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def run():
    cache = Cache(FW / "extracted/24A446/dyld")
    touched = set()
    def region(va, length):
        matches = [(a, b, off, path) for a, b, off, path in cache.maps if a <= va and va + length <= b]
        assert len(matches) == 1, (hex(va), length, len(matches))
        a, b, off, path = matches[0]
        touched.add(path)
        raw = cache.read(va, length)
        assert len(raw) == length
        return {"address": hex(va), "bytes": length, "file": str(path),
                "file_offset": off + va - a, "sha256": hashlib.sha256(raw).hexdigest(), "raw_hex": raw.hex()}
    def pointer(slot):
        raw = struct.unpack("<Q", cache.read(slot, 8))[0]
        slide = [(a, b, base) for a, b, base in cache.slide if a <= slot < b]
        assert len(slide) <= 1
        target = cache.ptr(slot)
        return {"storage": region(slot, 8), "raw_u64": hex(raw), "target": hex(target),
                "v5_value_add": hex(slide[0][2]) if slide else None,
                "interpretation": "v5: value_add + low34; unauth high8 restored" if slide else "plain pointer"}
    keys = []
    for slot in (0x268104150, 0x268104158):
        p1 = pointer(slot)
        p2 = pointer(int(p1["target"], 16))
        cf = int(p2["target"], 16)
        header = region(cf, 32)
        length = struct.unpack("<Q", cache.read(cf + 24, 8))[0]
        assert 0 < length < 1024
        chars = pointer(cf + 16)
        data = region(int(chars["target"], 16), length + 1)
        raw = bytes.fromhex(data["raw_hex"])
        assert raw[-1] == 0
        value = raw[:-1].decode("utf-8")
        assert cache.cfstr(cf) == value
        keys.append({"slot": hex(slot), "pointer_chain": [p1, p2], "cfstring_header": header,
                     "length": length, "characters_pointer": chars, "characters": data, "value": value})
    # CFString type accessor, dictionary typed getter, integer getter, and the
    # command request bridge: inspect original trampoline bytes and symbols.
    from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN
    disassembler = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    images = {name: Image(FW / f"extracted/24A446/binaries/{name}/{name}")
              for name in ("CoreUtils", "CoreFoundation", "APTransport")}
    imports = []
    for entry in (0x25810a710, 0x25810a6f0, 0x258102670, 0x25810e4e0):
        area = region(entry, 16)
        instructions = list(disassembler.disasm(bytes.fromhex(area["raw_hex"]), entry))
        target = None
        if instructions[0].mnemonic == "adrp" and instructions[1].mnemonic == "add":
            target = int(instructions[0].op_str.split("#")[1], 0) + int(instructions[1].op_str.split("#")[1], 0)
            if instructions[2].mnemonic == "ldr":
                target = cache.ptr(target)
            elif instructions[2].mnemonic != "br":
                target = None
        imports.append({"entry": area, "instructions": [f"{x.mnemonic} {x.op_str}" for x in instructions],
                        "target": hex(target) if target is not None else None,
                        "symbols": [{"image": name, "names": image.symbols[target]}
                                    for name, image in images.items() if target in image.symbols]})
    source = FW / "extracted/24A446/binaries/AirPlaySender/AirPlaySender"
    image = Image(source)
    base = FW / "analysis/decompiler-cache/24A446/AirPlaySender/934ec850a9ab7623f1d8/functions"
    functions = []
    for va in (0x251a59338, 0x2519c69f0):
        raw_path = base / f"f_{va:x}.bin"
        raw = raw_path.read_bytes()
        assert raw == image.read(va, len(raw)) == cache.read(va, len(raw))
        region(va, len(raw))
        functions.append({"address": hex(va), "raw_matches_image_and_cache": True,
                          "files": [{"path": str(base / f"f_{va:x}{suffix}"),
                                     "sha256": sha(base / f"f_{va:x}{suffix}")}
                                    for suffix in (".bin", ".s", ".ghidra.c", ".json")]})
    report = {"build": "24A446", "scope": "AP-U05: exact response keys and selected consumer/guard code provenance",
              "method": "Original cache mapping+v5 pointer decoding; no old field-resolution JSON input; not execution",
              "keys": keys, "imports": imports, "functions": functions,
              "files": [{"path": str(p), "bytes": p.stat().st_size, "sha256": sha(p)} for p in sorted(touched)],
              "tools": [{"path": str(p), "sha256": sha(p)} for p in
                        [Path(__file__).resolve(), FW / "tools/ipsw-research/firmware_cache.py", FW / "tools/ipsw-research/firmware_image.py"]],
              "images": [{"path": str(source), "sha256": sha(source)}] +
                        [{"path": str(i.path), "sha256": sha(i.path)} for i in images.values()],
              "limits": ["Cached v5 pointers interpreted, not executing dyld fixups or Apple signature verification.",
                         "Does not prove endpoint chose combined info/skipRecord in a vehicle session.",
                         "Does not establish all CF coercion defaults or complete Stage2 lifecycle."]}
    cache.close()
    out = DOC / "evidence/control-response-keys.json"
    out.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"keys": [{"slot": k["slot"], "value": k["value"]} for k in keys],
                      "imports": [{"entry": i["entry"]["address"], "symbols": i["symbols"]} for i in imports],
                      "subcache_files": len(touched), "functions_verified": len(functions), "output": str(out)}))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()
    run()
