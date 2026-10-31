"""Read-only chapter15 evidence collector. Run python -B; prints JSON only."""
from pathlib import Path
import hashlib
import json
import struct
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
FW = ROOT.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
CACHE = FW / "analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions"
ADDRESSES = [0x1000c07a8, 0x1000c0758, 0x10002a650, 0x100067e1c, 0x100067e4c,
    0x10004f870, 0x10004fa38, 0x1000500a8, 0x10004fedc, 0x10004ea7c,
    0x1000512e8, 0x10013aed0, 0x10013b920, 0x10013bcc8, 0x10013b540,
    0x100067720, 0x100067f30, 0x100067f3c, 0x1000f2bac, 0x100067ee4,
    0x10004e91c, 0x10004ea3c, 0x10013bc5c, 0x10001234c, 0x10003182c,
    0x1000c0c70, 0x10006782c, 0x100050264, 0x10004df7c, 0x10013ab84,
    0x10004e29c, 0x10013bbdc, 0x100050af4, 0x1000c2e00, 0x1000c2e50,
    0x10018f17c, 0x100050c2c, 0x1000c2f4c, 0x100050dcc, 0x100050da8, 0x10013cad8]

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    img = Image(SOURCE)
    if len(sys.argv) > 1 and sys.argv[1] == "--power-descriptor":
        items=[]
        for address in range(0x10021eef8,0x10021ef20,8):
            try:
                target=img.ptr(address)
                items.append({"address":hex(address),"raw":hex(img.u64(address)),"target":hex(target),
                    "symbols":img.symbols.get(target,[])})
            except ValueError:
                items.append({"address":hex(address),"raw":hex(img.u64(address)),"target":None})
        print(json.dumps(items,indent=2))
        return
    if len(sys.argv) > 1 and sys.argv[1] == "--lookup":
        needles = [s.lower() for s in sys.argv[2:]]
        print(json.dumps([{ "va": hex(a), "names": names } for a, names in img.symbols.items()
            if any(n in " ".join(names).lower() for n in needles)], indent=2))
        return
    rows = []
    for address in ADDRESSES:
        raw_path = CACHE / f"f_{address:x}.bin"
        raw = raw_path.read_bytes()
        assert raw and img.read(address, len(raw)) == raw, hex(address)
        segment = next((a, o) for a, b, o, _ in img.segments if a <= address and address + len(raw) <= b)
        rows.append({"address": hex(address), "symbols": sorted(set(img.symbols.get(address, [])) - {""}),
            "source_file_offset": segment[1] + address - segment[0], "raw_length": len(raw),
            "raw_sha256": hashlib.sha256(raw).hexdigest(), "raw_matches_source": True,
            "files": [{"path": str(p), "sha256": sha(p)} for suffix in (".bin", ".s", ".ghidra.c")
                if (p := CACHE / f"f_{address:x}{suffix}").exists()]})
    records = []
    for address in [0x10021a948, 0x10021a960] + list(range(0x10021f1a8, 0x10021f220, 24)):
        raw = img.read(address, 24)
        records.append({"address": hex(address), "id": struct.unpack_from("<I",raw)[0],
            "required": raw[16], "raw_hex": raw.hex(), "sha256": hashlib.sha256(raw).hexdigest()})
    app_root = Path("D:/carvex-research/android/protocol-carplay/src/main/java/io/github/iamr0s/carvex")
    app_files = [app_root / p for p in ["sessioncore/IapIdentifyInfo.kt", "carplay/Bootstrap.kt", "carplay/core/Wire.kt"]]
    data_ranges=[]
    for address, length, role in [(0x10021eef8,40,"power feature callback pointers"),
            (0x1001b4050,16,"power feature initial four u32 values"),
            (0x1001b4060,72,"six 12-byte power message declarations")]:
        raw=img.read(address,length)
        data_ranges.append({"address":hex(address),"role":role,"length":length,"raw_hex":raw.hex(),
            "sha256":hashlib.sha256(raw).hexdigest()})
    result = {"schema_version": 1, "date": "2026-10-29", "status": "BOUNDED_BRANCH_AUDIT",
        "source": {"path": str(SOURCE), "sha256": sha(SOURCE)}, "functions": rows,
        "registration_records": records, "original_data_ranges": data_ranges,
        "android_sources": [{"path": str(p), "sha256": sha(p)} for p in app_files if p.exists()],
        "tool": {"path": str(Path(__file__)), "sha256": sha(Path(__file__))},
        "runtime_observed": False, "firmware_executed": False, "app_tests_executed": False,
        "full_branch_coverage": False,
        "limits": ["ObjC plugin current-limit implementation and real provider values are not executed.",
            "Types and semantic names inferred from disassembly require separately documented bounds.",
            "No inference of audio failure causality or real vehicle compatibility."]}
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
