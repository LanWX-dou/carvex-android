"""Read-only batch3 provenance: original registry and parser/reject functions.

Run python -B. JSON goes to stdout. Never executes firmware or rewrites old evidence.
Function-byte matching and instruction counts are not semantic branch coverage.
"""
from __future__ import annotations
import bisect
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
FUNCTIONS = [0x100067ee4, 0x1000f2bac, 0x10004f0d4, 0x1000512e8,
             0x10013adf0, 0x10013aed0, 0x10013bc5c, 0x10013bcc8,
             0x10006782c, 0x10006a3e4, 0x10013c788, 0x10004e91c,
             0x100067ce0, 0x100003a68]

def sha(raw):
    return hashlib.sha256(raw).hexdigest()

def main():
    image = Image(SOURCE)
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    def pointer(address):
        raw = image.u64(address)
        if not raw:
            return 0
        if raw >> 62 & 1:
            raise ValueError("expected local chained rebase")
        target = image.base + (raw & 0xffffffffff)
        image.read(target, 1)
        return target
    def span(address, length):
        raw = image.read(address, length)
        offset = next(off + address - a for a, b, off, _ in image.segments
                      if a <= address and address + length <= b)
        return {"address": hex(address), "length": length, "file_offset": offset, "sha256": sha(raw)}
    functions = []
    for address in FUNCTIONS:
        cached = CACHE / f"f_{address:x}.bin"
        length = cached.stat().st_size if cached.exists() else image.starts[bisect.bisect_right(image.starts, address)] - address
        raw = image.read(address, length)
        if cached.exists():
            assert raw == cached.read_bytes(), hex(address)
        decoded = list(md.disasm(raw, address))
        assert sum(ins.size for ins in decoded) == length, hex(address)
        functions.append(dict(span(address, length), symbols=image.symbols.get(address, []),
            cache_matches=cached.exists() or None,
            instructions=[{"at": hex(ins.address), "bytes": ins.bytes.hex(),
                           "asm": ins.mnemonic + " " + ins.op_str} for ins in decoded]))
    records = []
    for index in range(29):
        entry = 0x10021b550 + index * 16
        descriptor = pointer(entry + 8)
        if not descriptor:
            continue
        table = pointer(descriptor + 0x18)
        count = image.read(descriptor + 0x20, 1)[0]
        if not table:
            continue
        for item in range(count):
            address = table + item * 24
            raw = image.read(address, 24)
            records.append(dict(span(address, 24), descriptor=hex(descriptor),
                feature=struct.unpack("<I", image.read(entry, 4))[0],
                id=struct.unpack_from("<I", raw)[0], callback=hex(pointer(address + 8)),
                required=raw[16], raw_hex=raw.hex()))
    expected = list(range(27)) + [29, 30, 33, 34, 38, 240, 241]
    assert sorted(row["id"] for row in records) == expected
    required = [row["id"] for row in records if row["required"]]
    assert required == list(range(8)) + [12, 13, 8, 9]
    result = {"source": str(SOURCE), "source_sha256": sha(image.data),
        "tool_sha256": sha(Path(__file__).read_bytes()), "functions": functions,
        "registration": records, "required_registration_order": required,
        "firmware_executed": False, "full_branch_coverage": False,
        "limitations": ["Registry for this build only; not a future-version promise.",
            "CF conversion/equality and allocation failures not executed.",
            "Other registered feature callbacks remain separately audited/deferred."]}
    if "--compact" in sys.argv:
        for record in functions:
            record["decoded_instructions"] = len(record.pop("instructions"))
    if "--summary" in sys.argv:
        result = {"source_sha256": result["source_sha256"], "functions": len(functions),
                  "registry_records": len(records), "required_order": required,
                  "all_available_cache_slices_match": True, "firmware_executed": False}
    print(json.dumps(result, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
