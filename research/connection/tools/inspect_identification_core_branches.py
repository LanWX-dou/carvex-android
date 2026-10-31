"""Read-only 24A446 Identification core branch inventory; JSON to stdout.

Original Mach-O slices are matched against cached .bin and re-disassembled.
The inventory is not semantic coverage, firmware execution, or device testing.
Use python -B; this tool never writes source, cache, or evidence files.
"""
from __future__ import annotations

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
from firmware_image import Image
import capstone

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
CACHE = FW / "analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions"
APP = Path("D:/carvex-research/android")
FUNCTIONS = (
    (0x100067ee4, "CString framing", "IC-01"),
    (0x1000f2bac, "CF string conversion wrapper", "IC-02"),
    (0x10004f0d4, "String output ownership and status", "IC-03"),
    (0x1000512e8, "Core parameter switch and occurrence counter", "IC-04/05/06"),
    (0x100067f30, "Raw data getter", "IC-07"),
    (0x10013adf0, "Direction-specific message set replacement", "IC-07"),
    (0x10013aed0, "Registered callback and required-success insertion", "IC-08"),
    (0x10013bc5c, "Required-success membership check", "IC-09"),
)


def sha(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def flow_kind(mnemonic: str) -> str | None:
    if mnemonic.startswith("b.") or mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
        return "conditional_branch"
    if mnemonic in ("csel", "csinc", "csinv", "csneg", "cset", "csetm", "cinc", "cinv", "cneg"):
        return "conditional_value"
    if mnemonic in ("br", "braa", "brab", "braaz", "brabz", "blr", "blraa", "blrab", "blraaz", "blrabz"):
        return "indirect_control"
    if mnemonic in ("b", "bl"):
        return "direct_control"
    return None


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--summary", action="store_true")
    args = parser.parse_args()
    image = Image(SOURCE)
    disassembler = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    records = []
    for address, scope, row in FUNCTIONS:
        raw_path = CACHE / f"f_{address:x}.bin"
        raw = raw_path.read_bytes()
        assert raw and raw == image.read(address, len(raw)), hex(address)
        decoded = list(disassembler.disasm(raw, address))
        assert sum(instruction.size for instruction in decoded) == len(raw), hex(address)
        edges = []
        for instruction in decoded:
            kind = flow_kind(instruction.mnemonic)
            if kind is None:
                continue
            entry = {"address": hex(instruction.address), "bytes": instruction.bytes.hex(),
                     "kind": kind, "instruction": instruction.mnemonic + " " + instruction.op_str}
            if kind in ("direct_control", "conditional_branch"):
                operand = instruction.op_str.rsplit(",", 1)[-1].strip()
                if operand.startswith("#0x"):
                    target = int(operand[1:], 16)
                    entry["target"] = hex(target)
                    entry["target_symbols"] = image.symbols.get(target, [])
                    entry["target_in_slice"] = address <= target < address + len(raw)
            edges.append(entry)
        records.append({"address": hex(address), "symbols": image.symbols.get(address, []),
                        "scope": scope, "semantic_table_rows": row,
                        "raw_path": str(raw_path), "length": len(raw), "sha256": sha(raw_path),
                        "raw_matches_source": True, "decoded_all_slice_bytes": True,
                        "conditional_branch_count": sum(e["kind"] == "conditional_branch" for e in edges),
                        "conditional_value_count": sum(e["kind"] == "conditional_value" for e in edges),
                        "indirect_control_count": sum(e["kind"] == "indirect_control" for e in edges),
                        "flow_inventory": edges})
    # Decode the exact core switch rather than treating Ghidra's default as all unknown IDs.
    switch_address, switch_base = 0x1000188e0, 0x100051350
    switch_raw = image.read(switch_address, 35 * 4)
    switch_rows = [{"id": i, "target": hex(switch_base + offset)}
                   for i, offset in enumerate(struct.unpack("<35i", switch_raw))]
    sources = [
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfo.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/Wire.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt",
        "protocol-carplay/src/test/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfoTest.kt",
        "protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/BootstrapNegotiationTest.kt",
    ]
    result = {"schema_version": 1, "baseline": "iPhone18,1 / iOS 27.0.1 / 24A446",
              "date": "2026-10-29", "status": "BOUNDED_STATIC_REVIEW",
              "source": {"path": str(SOURCE), "sha256": sha(SOURCE)},
              "functions": records,
              "core_switch": {"table": hex(switch_address), "relative_base": hex(switch_base),
                              "sha256": hashlib.sha256(switch_raw).hexdigest(), "entries": switch_rows},
              "android_sources": [{"path": str(APP / p), "sha256": sha(APP / p)} for p in sources],
              "tool": {"path": str(Path(__file__)), "sha256": sha(Path(__file__)),
                       "capstone_version": capstone.__version__},
              "limits": ["Branches and calls are an inventory, not a coverage percentage.",
                         "Semantic review is recorded separately in chapter18, including OPEN dependencies.",
                         "Calls, allocation failure, CF conversion/equality and all platform dependencies are not fully closed.",
                         "No firmware execution or vehicle observation; no end-to-end compatibility claim."]}
    if args.summary:
        result = {"source_sha256": result["source"]["sha256"], "functions": len(records),
                  "all_slices_match_source": True, "core_switch_entries": len(switch_rows),
                  "conditional_branches": sum(r["conditional_branch_count"] for r in records),
                  "conditional_values": sum(r["conditional_value_count"] for r in records),
                  "indirect_control": sum(r["indirect_control_count"] for r in records),
                  "limit": "Inventory is not semantic or runtime coverage."}
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
