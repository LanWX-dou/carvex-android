"""Read-only 24A446 security property/selector provenance. JSON/stdout, python -B."""
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
from firmware_image import Image
from firmware_cache import Cache
import capstone

FUNCTIONS = {
    "AirPlaySender": {
        0x251999fec: "FeaturesEx preference, compression/encryption fallback, version filter",
        0x25199a4fc: "feature-copy error becomes false, otherwise bit query",
        0x25199a588: "bounded security property dispatcher only: CU, legacy, HK, system, unified, auth, one-time, access",
        0x2519bd6fc: "CU OR terms: 38, 46, 43, 48",
        0x2519ca804: "complete AuthenticationType priority and no-feature failure",
        0x2519a3d44: "one-time pairing from systemFlags bit9",
        0x2519a3dc0: "accessControlType primary and level/status fallback",
        0x2519a6020: "HK access enabled: feature46 AND systemFlags bit10",
        0x251a5e858: "bounded no-pair/broker prerequisite prefix, not complete pairing retry engine",
        0x251a60f70: "bounded kind5 CU peer identifier and authentication input creation",
    },
    "AirPlaySupport": {
        0x226f078a0: "APSFeaturesHasFeature null/data/length handling and bit indexing",
        0x226f0776c: "extended representation preferred over legacy flags",
        0x226f07ae8: "clear bit helper used by sourceVersion filter",
    },
    "APTransport": {0x24fd94564: "advertiser missing property returns null/error"},
    "CoreUtils": {0x18be3f804: "sync integer getter returns zero on null property"},
}
SLOTS = {
    0x2680fbae8: "_kAPAdvertiserInfoProperty_FeaturesEx",
    0x2680fba50: "_APAdvertiserInfoCopyProperty",
    0x2680fbba0: "_kAPAdvertiserInfoProperty_SystemFlags",
    0x2680fba78: "_kAPAdvertiserInfoProperty_AccessControlType",
    0x2680fba70: "_kAPAdvertiserInfoProperty_AccessControlLevelHK",
    0x2680fbaa0: "_kAPAdvertiserInfoProperty_CompressionTypes",
    0x2680fbae0: "_kAPAdvertiserInfoProperty_EncryptionTypes",
    0x2680d3188: "_kCFBooleanFalse",
    0x2680d3198: "_kCFBooleanTrue",
}
TRAMPOLINES = {
    0x25810a8d0: (0x18be3f804, "_CFObjectGetPropertyInt64Sync"),
    0x25810c6f0: (0x24fd94564, "_APAdvertiserInfoCopyProperty"),
    0x2581097c0: (0x226f078a0, "_APSFeaturesHasFeature"),
    0x25810d430: (0x226f07ae8, "_APSFeaturesClearFeature"),
    0x25810d440: (0x226f0776c, "_APSFeaturesCreateFromEndpointInfoFeatureRepresentations"),
}


def audit():
    images = {name: Image(FW / "extracted/24A446/binaries" / name / name)
              for name in (*FUNCTIONS, "CoreFoundation")}
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    cache = Cache(FW / "extracted/24A446/dyld")
    try:
        source_records = []
        for name, image in images.items():
            functions = []
            for address, scope in FUNCTIONS.get(name, {}).items():
                end = image.starts[bisect.bisect_right(image.starts, address)]
                raw = image.read(address, end - address)
                if raw != cache.read(address, len(raw)):
                    raise ValueError(f"source/cache mismatch {address:#x}")
                decoded = list(md.disasm(raw, address))
                if sum(i.size for i in decoded) != len(raw):
                    raise ValueError(f"incomplete instruction decoding {address:#x}")
                functions.append({"address": hex(address), "end": hex(end), "bytes": len(raw),
                                  "sha256": hashlib.sha256(raw).hexdigest(),
                                  "names": image.symbols.get(address, []), "reviewed_scope": scope,
                                  "original_cache_equal": True, "decoded_complete": True})
            source_records.append({"component": name, "path": str(image.path),
                                   "sha256": hashlib.sha256(image.data).hexdigest(), "functions": functions})
        slots = []
        for slot, expected in SLOTS.items():
            target = cache.ptr(slot)
            names = [n for im in images.values() for n in im.symbols.get(target, [])]
            if expected not in names:
                raise ValueError(f"unresolved original pointer {slot:#x}: {names}")
            slots.append({"slot": hex(slot), "target": hex(target), "symbol": expected,
                          "raw_sha256": hashlib.sha256(cache.read(slot, 8)).hexdigest()})
        trampolines = []
        for address, (target, expected) in TRAMPOLINES.items():
            raw = cache.read(address, 12)
            decoded = list(md.disasm(raw, address))
            if len(decoded) != 3 or [i.mnemonic for i in decoded] != ["adrp", "add", "br"]:
                raise ValueError(f"unexpected trampoline {address:#x}")
            page = int(decoded[0].op_str.split("#")[1], 0)
            offset = int(decoded[1].op_str.split("#")[1], 0)
            names = [n for im in images.values() for n in im.symbols.get(target, [])]
            if page + offset != target or expected not in names:
                raise ValueError(f"trampoline target mismatch {address:#x}")
            trampolines.append({"address": hex(address), "target": hex(target), "symbol": expected,
                                "sha256": hashlib.sha256(raw).hexdigest()})
        return {"schema": "airplay-security-branches-v1", "build": "24A446", "device": "iPhone18,1",
                "firmware_executed": False, "real_vehicle_verified": False,
                "sources": source_records, "dyld_v5_pointer_slots": slots,
                "original_trampolines": trampolines,
                "closed_static": {"cu_feature_or": [38, 46, 43, 48], "legacy": 27,
                    "hk_access": 46, "system": 43, "unified_mfi": 51,
                    "one_time_system_flags_bit": 9, "hk_access_system_flags_bit": 10,
                    "authentication_priority": [[80, 32], [[26, 51], 8], [14, 4], [23, 1], [31, 16]],
                    "no_authentication_feature_status_u32": "0xfffee7b6"},
                "open": ["complete TXT/4301 provenance and override for each endpoint",
                         "extended feature80 wire input in Android",
                         "complete CU/HK/system/transient pairing transaction and trust validation",
                         "unified MFi transcript, SAP signature contract and trust material",
                         "iAP2 AA trust/AA06/inheritance and real first/reconnection coverage"]}
    finally:
        cache.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verify", type=Path)
    parser.add_argument("--summary", action="store_true")
    args = parser.parse_args()
    report = audit()
    if args.verify:
        if json.loads(args.verify.read_text(encoding="utf-8")) != report:
            raise SystemExit("snapshot mismatch")
        print("PASS: 5 source hashes, 15 original functions, 9 dyld slots and 5 trampolines")
    elif args.summary:
        print(json.dumps({"functions": sum(len(s["functions"]) for s in report["sources"]),
                          "sources": len(report["sources"]), "closed_static": report["closed_static"]}))
    else:
        print(json.dumps(report, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
