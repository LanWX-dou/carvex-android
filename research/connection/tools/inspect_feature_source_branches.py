"""Read-only 24A446 fex provenance and Base64 decoder snapshot; never writes firmware/cache."""
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
    "AirPlaySupport": {
        0x226e67c0c: "ASCII string conversion, strlen, Base64DecodeCopy, CFData creation/error",
        0x226f0776c: "endpoint extended representation is preferred; parse error does not try legacy",
        0x226f078a0: "variable-length LSB-first feature lookup",
        0x226f07bf4: "legacy compatibility value uses little-endian first eight bytes",
    },
    "CoreUtils": {
        0x18be43ad0: "Base64DecodeCopy allocation, complete decode and error propagation",
        0x18be447e0: "complete Base64Decode loop, alphabet table, padding termination and residual sextets",
    },
    "APTransport": {
        0x24fd9ac78: "TXT extended getter; only missing-key status permits legacy getter",
    },
    "AirPlaySender": {
        0x2519ca804: "AuthenticationType: feature80 before all lower-bit authentication choices",
        0x251a60f70: "bounded CU creation: reads AuthenticationType, type0x20 is a CU client argument",
    },
}


def audit():
    images = {name: Image(FW / "extracted/24A446/binaries" / name / name) for name in FUNCTIONS}
    cache = Cache(FW / "extracted/24A446/dyld")
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    try:
        sources = []
        for name, image in images.items():
            functions = []
            for address, scope in FUNCTIONS[name].items():
                end = image.starts[bisect.bisect_right(image.starts, address)]
                raw = image.read(address, end - address)
                assert raw == cache.read(address, len(raw)), f"cache mismatch {address:#x}"
                assert sum(ins.size for ins in md.disasm(raw, address)) == len(raw), f"decode {address:#x}"
                functions.append({"address": hex(address), "end": hex(end), "bytes": len(raw),
                                  "sha256": hashlib.sha256(raw).hexdigest(),
                                  "names": image.symbols.get(address, []), "reviewed_scope": scope})
            sources.append({"component": name, "path": str(image.path),
                            "sha256": hashlib.sha256(image.data).hexdigest(), "functions": functions})
        table = cache.read(0x18bf710b0, 256)
        assert [i for i, value in enumerate(table) if value == 0x80] == [9, 10, 11, 12, 13, 32]
        assert table[ord('+')] == table[ord('-')] == 62
        assert table[ord('/')] == table[ord('_')] == 63
        assert table[ord('=')] == 64
        keys = []
        for address, expected in [(0x275fa5380, "fex"), (0x275fa49c0, "features")]:
            chars = cache.ptr(address + 16)
            length = int.from_bytes(cache.read(address + 24, 8), "little")
            assert cache.read(chars, length) == expected.encode("ascii")
            keys.append({"cfstring": hex(address), "chars": hex(chars), "length": length, "value": expected})
        address, end = 0x24fd97840, 0x24fd9786c
        raw = images["APTransport"].read(address, end - address)
        assert raw == cache.read(address, len(raw))
        call_site = {"address": hex(address), "end": hex(end), "sha256": hashlib.sha256(raw).hexdigest(),
                     "scope": "AddAirPlayData loads fex as x1, features as x2, calls helper, propagates non-missing errors",
                     "assembly": [f"{i.address:#x}: {i.mnemonic} {i.op_str}" for i in md.disasm(raw, address)]}
        trampolines = []
        for address, target in [(0x22818b800, 0x18be43ad0), (0x2500ee000, 0x226e67c0c)]:
            raw = cache.read(address, 12)
            decoded = list(md.disasm(raw, address))
            assert [i.mnemonic for i in decoded] == ["adrp", "add", "br"]
            assert int(decoded[0].op_str.split('#')[1], 0) + int(decoded[1].op_str.split('#')[1], 0) == target
            trampolines.append({"address": hex(address), "target": hex(target), "sha256": hashlib.sha256(raw).hexdigest()})
        return {"schema": "feature-source-branches-v1", "build": "24A446", "device": "iPhone18,1",
                "firmware_executed": False, "real_vehicle_verified": False, "sources": sources,
                "txt_key_cfstrings": keys, "txt_call_site": call_site, "trampolines": trampolines,
                "base64_table": {"address": "0x18bf710b0", "sha256": hashlib.sha256(table).hexdigest(), "hex": table.hex()},
                "reviewed_branches": {
                    "fex_absent": "only missing-key status -0x1a47 tries legacy features",
                    "fex_parse_error": "propagate; never retry legacy",
                    "empty_extended": "successful zero-length data, distinct from missing",
                    "base64_terminator": "first '=' ends decode without examining trailing bytes",
                    "base64_residual_sextets": "0 or 1 -> no extra bytes; 2 -> one byte; 3 -> two bytes; unused bits unchecked",
                    "string_boundary": "ASCII conversion before strlen; embedded NUL truncates decoder input",
                    "feature_bit_order": "LSB-first within bytes; byte index = bit/8",
                    "legacy_flags": "little-endian first min(length,8) bytes",
                    "feature80": "AuthenticationType 0x20; CU creation consumes type==0x20, no kind5 blanket bypass"},
                "open": ["all TXT string/number coercion cases", "complete endpoint-info and 4301 producer precedence",
                         "full Apple pairing/authentication engine and trust transcripts", "real device interoperability"]}
    finally:
        cache.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    result = audit()
    if args.verify:
        if json.loads(args.verify.read_text(encoding="utf-8")) != result:
            raise SystemExit("snapshot mismatch")
        print("PASS: 4 source hashes, 9 functions, TXT call site/2 keys, Base64 table and 2 trampolines")
    else:
        print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
