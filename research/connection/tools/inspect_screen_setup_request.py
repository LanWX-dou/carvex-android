"""Read-only 24A446 screen SETUP producer provenance audit (python -B).

Print JSON or compare --verify snapshot. Does not execute firmware, access a
phone/headunit, or prove runtime compatibility. No filesystem writes.
"""
from __future__ import annotations
import argparse
import bisect
import hashlib
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_cache import Cache
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

GROUPS = {
    "AirPlaySender": ("934ec850a9ab7623f1d8", [
        0x2519bbf24, 0x251bd65d8, 0x251b40be8, 0x251b443cc,
        0x251bd94ec, 0x251b43fc4, 0x2519b4600, 0x251a9bcf0,
        0x251a9be54, 0x251b434e4]),
    "AirPlaySupport": ("5f566a24689df2ec27cb", [0x226e64870, 0x226e63f48]),
    "CoreUtils": ("8792f09ecc40428a5f65", [0x18be501d4, 0x18be4320c]),
    "CoreFoundation": (None, [0x18061fff0]),
    "CoreMedia": (None, [0x18ee7d728]),
}

# Original shared-cache jump islands, not assumed names from a decompiler.
STUBS = [
    (0x25810d090, 0x226e64870, "AirPlaySupport", "_APSCarPlayScreenLatencyMs"),
    (0x25810bd60, 0x18be501d4, "CoreUtils", "_UUIDGet"),
    (0x25810a790, 0x18be4320c, "CoreUtils", "_CFDictionarySetInt64"),
    (0x258101810, 0x18061fff0, "CoreFoundation", "_CFDictionaryAddValue"),
    (0x258102650, 0x18065b068, "CoreFoundation", "_CFDictionaryCreateMutableCopy"),
    (0x258102680, 0x18060c0f8, "CoreFoundation", "_CFDictionaryGetValue"),
    (0x2580f7000, 0x180622f64, "CoreFoundation", "_CFDictionarySetValue"),
    (0x25810b140, 0x18ee7d728, "CoreMedia", "_FigCFDictionarySetInt32"),
    (0x25810f7c0, 0x196f5bca4, None, None),
]

KEYS = [
    (0x27613fcb0, "latencyMs"), (0x276131cf0, "uuid"),
    (0x27612ff30, "timestampInfo"), (0x27612ff50, "streams"),
    (0x276136f70, "streamConnectionID"), (0x27612fb30, "type"),
    (0x27613fcd0, "DemoDeviceInfo"), (0x27613b530, "ExtraStreamOptions"),
    (0x2761339d0, "UUID"), (0x276134f50, "IsCarPlay"),
    (0x276134f70, "IsConnectedOverUSB"),
    (0x273d50fa0, "screenLatencyCarPlayUSBMs"), (0x273d50f40, "screenLatencyMs"),
]

PROBES = {
    0x251bd66c8: "ldr w2, [x24, #0x49c]",
    0x251bd66d4: "bl #0x25810b140",
    0x251bd66dc: "cbz x8, #0x251bd6754",
    0x251bd66e4: "cbz w8, #0x251bd6790",
    0x251bd66e8: "ldr x2, [x24, #0x138]",
    0x251bd66f8: "bl #0x2580f7000",
    0x251bd66fc: "ldr x0, [x24, #0x78]",
    0x251bd674c: "bl #0x25810a640",
    0x251b43fc8: "b #0x258101810",
    0x251b41224: "ldrb w0, [x25, #0x185]",
    0x251b41228: "bl #0x25810d090",
    0x251b41238: "str w0, [x25, #0x49c]",
    0x226e64870: "cbz w0, #0x226e64888",
    0x226e64880: "mov w2, #0x19",
    0x226e64894: "mov w2, #0x4b",
    0x226e64898: "b #0x226e63f48",
    0x251b447dc: "ldrb w8, [x19, #0x182]",
    0x251b447e0: "cbnz w8, #0x251b44810",
    0x251b447fc: "bl #0x251a9bcf0",
    0x251b44d90: "cbz x8, #0x251b44e5c",
    0x251bd9564: "mov w8, #-0x4178",
    0x251a9beb4: "ldr x0, [x22, #0x18]",
    0x251a9bebc: "add x1, x1, #0xcf0",
    0x251a9bec0: "b #0x251a9bf74",
    0x251a9bf74: "bl #0x258102680",
    0x2519bc108: "bl #0x258102650",
    0x2519bc14c: "bl #0x25810a790",
    0x2519bc228: "bl #0x25810bd60",
    0x2519bc230: "rev x2, x8",
    0x2519bc248: "bl #0x25810a790",
    0x2519bc250: "cmp w8, #5",
    0x2519bc254: "b.ne #0x2519bc314",
    0x2519bc25c: "b #0x2519bc340",
    0x2519bc314: "bl #0x25810f7c0",
    0x2519bc31c: "cbz x0, #0x2519bc340",
    0x2519bc330: "bl #0x2580f7000",
}


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def audit():
    cache = Cache(FW / "extracted/24A446/dyld")
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    images = {}
    sources = {}
    try:
        for component, (folder_id, addresses) in GROUPS.items():
            path = FW / f"extracted/24A446/binaries/{component}/{component}"
            image = Image(path)
            images[component] = image
            functions = []
            for address in addresses:
                end = image.starts[bisect.bisect_right(image.starts, address)]
                raw = image.read(address, end - address)
                if raw != cache.read(address, len(raw)):
                    raise ValueError(f"original dyld mismatch: {address:#x}")
                if sum(x.size for x in md.disasm(raw, address)) != len(raw):
                    raise ValueError(f"instruction decode incomplete: {address:#x}")
                cached = (FW / f"analysis/decompiler-cache/24A446/{component}/{folder_id}/functions/f_{address:x}.bin") if folder_id else None
                present = cached is not None and cached.exists()
                if present and cached.read_bytes() != raw:
                    raise ValueError(f"cached fragment mismatch: {address:#x}")
                functions.append({"address": hex(address), "end": hex(end),
                                  "symbols": image.symbols.get(address, []),
                                  "bytes": len(raw), "sha256": digest(raw),
                                  "original_dyld_equal": True,
                                  "decoded_complete": True,
                                  "cache_fragment_present": present})
            sources[component] = {"path_relative_to_firmware": path.relative_to(FW).as_posix(),
                                  "sha256": digest(image.data), "functions": functions}
        keys = []
        for address, expected in KEYS:
            value = cache.cfstr(address)
            if value != expected:
                raise ValueError(f"wrong CFString at {address:#x}")
            keys.append({"address": hex(address), "value": value})
        stubs = []
        for address, target, component, symbol in STUBS:
            raw = cache.read(address, 12)
            instructions = list(md.disasm(raw, address))
            wanted = [f"adrp x16, #{target & ~0xfff:#x}",
                      f"add x16, x16, #{target & 0xfff:#x}", "br x16"]
            actual = [f"{x.mnemonic} {x.op_str}" for x in instructions]
            if actual != wanted:
                raise ValueError(f"wrong direct stub {address:#x}: {actual}")
            if component and symbol not in images[component].symbols.get(target, []):
                raise ValueError(f"symbol mismatch: {target:#x}")
            stubs.append({"address": hex(address), "target": hex(target),
                          "raw": raw.hex(), "component": component,
                          "symbol": symbol, "symbol_resolved": symbol is not None})
        probes = []
        for address, expected in PROBES.items():
            raw = cache.read(address, 4)
            instruction = list(md.disasm(raw, address))
            actual = " ".join([instruction[0].mnemonic, instruction[0].op_str])
            if actual != expected:
                raise ValueError(f"probe differs: {address:#x} {actual}")
            probes.append({"address": hex(address), "raw": raw.hex(), "instruction": actual})
        bindings = []
        for slot, expected in [(0x2693e7c38, "streamConnectionID"),
                               (0x2693e7d08, "type"), (0x2693e6ac8, "UUID"),
                               (0x2693e7168, "IsCarPlay"), (0x2693e7170, "IsConnectedOverUSB")]:
            target = cache.ptr(slot)
            value = cache.cfstr(target)
            if value != expected:
                raise ValueError(f"key pointer mismatch: {slot:#x}")
            bindings.append({"slot": hex(slot), "target": hex(target), "value": value})
        return {"schema": "screen-setup-request-v1", "build": "24A446",
                "firmware_executed": False, "sources": sources, "keys": keys,
                "direct_stubs": stubs, "instruction_probes": probes,
                "pointer_bindings": bindings,
                "defaults": {"CarPlay_wireless_latencyMs": 75, "CarPlay_USB_latencyMs": 25,
                             "configurable_local_preferences": True},
                "scope": "Bounded screen request producer/defaults/UUID getter; excludes whole-session equivalence, generic timestamp payload, all extras callers and hardware acceptance"}
    finally:
        cache.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    result = audit()
    if args.verify:
        if json.loads(args.verify.read_text(encoding="utf-8")) != result:
            raise SystemExit("FAIL: screen SETUP snapshot differs")
        print("PASS: 16 original functions, 9 direct stubs, 13 keys, 36 instruction probes and 5 bindings match")
        print("LIMIT: static source provenance only; no phone/headunit/firmware execution")
    else:
        print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
