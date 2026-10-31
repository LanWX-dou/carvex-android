"""Read-only 24A446 Identification lifecycle slices; JSON to stdout.

--inspect accepts one or more VA:hex-length ranges. Original code is never run.
Inputs and old caches remain read-only. Use python -B.
"""
from pathlib import Path
import argparse
import bisect
import hashlib
import json
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
CACHE = FW / "analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions"
FUNCTIONS = (
    0x1000511d0, 0x10013bcc8, 0x100050da8, 0x100050dcc,
    0x10013b540, 0x10013b414, 0x10004dd50, 0x10013b28c,
    0x100050934, 0x100050458, 0x100050744,
    0x10011e1f0, 0x10011dfd8, 0x10002ab44, 0x10002acd4,
    0x10002af18, 0x10002b02c, 0x10002b084,
    0x10011da74, 0x10004df7c, 0x10004eba4, 0x100050338,
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--inspect", nargs="+")
    parser.add_argument("--summary", action="store_true")
    parser.add_argument("--compact", action="store_true", help="omit raw bytes and branch inventory from provenance snapshot")
    args = parser.parse_args()
    image = Image(SOURCE)
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    if args.inspect:
        for spec in args.inspect:
            address, length = [int(v, 0) for v in spec.split(":")]
            print(f"RANGE {address:#x}+{length:#x} {image.symbols.get(address, [])}")
            for ins in md.disasm(image.read(address, length), address):
                suffix = ""
                if ins.mnemonic in ("bl", "b") and ins.op_str.startswith("#0x"):
                    suffix = " " + repr(image.symbols.get(int(ins.op_str[1:], 16), []))
                print(f"{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}{suffix}")
        return
    records = []
    for address in FUNCTIONS:
        next_address = image.starts[bisect.bisect_right(image.starts, address)]
        raw = image.read(address, next_address - address)
        cached = CACHE / f"f_{address:x}.bin"
        cached_raw = cached.read_bytes() if cached.exists() else None
        if cached_raw is not None:
            assert cached_raw == image.read(address, len(cached_raw)), hex(address)
        decoded = list(md.disasm(raw, address))
        assert sum(i.size for i in decoded) == len(raw), hex(address)
        records.append({"address": hex(address), "symbols": image.symbols.get(address, []),
            "length_from_function_starts": len(raw), "sha256": hashlib.sha256(raw).hexdigest(),
            "source_raw_hex": raw.hex(), "cached_path": str(cached) if cached_raw is not None else None,
            "cached_length": len(cached_raw) if cached_raw is not None else None,
            "cached_matches_source": True if cached_raw is not None else None,
            "branch_inventory": [{"address": hex(i.address), "instruction": i.mnemonic + " " + i.op_str}
                for i in decoded if i.mnemonic.startswith("b.") or i.mnemonic in ("cbz", "cbnz", "tbz", "tbnz", "csel", "cset", "blr", "blraa", "blraaz")]})
    phone = DOC.parents[1] / "iamr0s/carplay-xiaomi-carlife"
    names = ("protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/RuntimeIap.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/PeerNegotiationController.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfo.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt",
        "protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/BootstrapNegotiationTest.kt",
        "bridge/src/main/java/io/github/iamr0s/carvex/session/SessionController.kt")
    result = {"schema_version": 1, "review_date": "2026-10-29", "status": "BOUNDED_STATIC_LIFECYCLE_AUDIT",
        "runtime_observed": False, "original_code_executed_this_round": False,
        "source": {"path": str(SOURCE), "sha256": hashlib.sha256(image.data).hexdigest()},
        "functions": records, "android_sources": [{"path": str(phone / n),
            "sha256": hashlib.sha256((phone / n).read_bytes()).hexdigest()} for n in names],
        "method": "Mach-O LC_SEGMENT_64 mapped reads; LC_FUNCTION_STARTS bounded slices; original bytes re-disassembled with Capstone; existing cached slices compared where present. JSON records are provenance, not semantic or runtime coverage.",
        "limits": ["Chapter16 states exact reviewed branch semantics and unresolved dependencies.",
            "No full queue cancellation/session lifetime proof, no device or headunit execution.",
            "No original or production code modified; no Gradle or APK build."]}
    if args.summary:
        result = {"source_sha256": result["source"]["sha256"], "functions": len(records),
            "existing_cached_slices_matched": sum(r["cached_matches_source"] is True for r in records),
            "all_function_starts_slices_disassembled": True, "runtime_observed": False}
    elif args.compact:
        for record in records:
            record.pop("source_raw_hex")
            record.pop("branch_inventory")
            record["symbols"] = sorted(set(s for s in record["symbols"] if s))
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
