"""Read-only batch82 inspection of original firmware and current source snapshots.

Emits JSON to stdout; never writes firmware, caches, or production code.
Byte verification is not firmware execution or full branch/runtime coverage.
"""
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
from inspect_iap2_handoff import MD, imports, local_selector, selector

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
SOURCES = {"accessoryd": SOURCE, **{name: FW / "extracted/24A446/binaries" / name / name
    for name in ("APTransport", "WiFiSharing", "AirPlaySender")}}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def inspect(component, addresses, assembly):
    im = Image(SOURCES[component])
    imported = imports(im) if component == "accessoryd" else {}
    cache = Cache(FW / "extracted/24A446/dyld")
    records = []
    try:
        for at in addresses:
            assert at in im.starts, f"not function start: {at:#x}"
            end = im.starts[bisect.bisect_right(im.starts, at)]
            raw = im.read(at, end-at)
            row = dict(address=hex(at), end=hex(end), sha256=sha(raw),
                       symbols=sorted(set(im.symbols.get(at, []))), cache_matches=[])
            if component != "accessoryd":
                row["original_dyld_matches"] = raw == cache.read(at, len(raw))
                assert row["original_dyld_matches"]
            for path in (FW / "analysis/decompiler-cache/24A446" / component).glob(f"*/functions/f_{at:x}.bin"):
                assert path.read_bytes() == raw, str(path)
                row["cache_matches"].append(str(path))
            lines, calls = [], []
            for ins in MD.disasm(raw, at):
                lines.append(f"{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}")
                if ins.mnemonic not in ("b", "bl") or not ins.op_str.startswith("#0x"):
                    continue
                target = int(ins.op_str[1:], 0)
                call = dict(site=hex(ins.address), target=hex(target))
                names = imported.get(target) or {"symbols": sorted(set(im.symbols.get(target, [])))}
                if names.get("symbol") or names.get("symbols"):
                    call.update(names)
                try:
                    if component == "accessoryd":
                        resolved = local_selector(im, target)
                    else:
                        stub = list(MD.disasm(cache.read(target, 12), target))
                        # ADRP/ADD x1 alone also occurs in cold logging functions.
                        # Require the third-instruction tail branch of a selector stub.
                        resolved = selector(cache, target) if len(stub)==3 and stub[2].mnemonic=="b" else None
                    if resolved:
                        call["selector"] = resolved
                except (ValueError, UnicodeError):
                    pass
                if len(call) > 2:
                    calls.append(call)
            assert len(lines)*4 == len(raw), f"incomplete disassembly: {at:#x}"
            row.update(instruction_count=len(lines), calls=calls)
            if assembly:
                row["assembly"] = lines
            records.append(row)
    finally:
        cache.close()
    return dict(component=component, source=str(im.path), source_sha256=sha(im.data), records=records)

def native_path(value):
    if sys.platform == "win32" and value.startswith("/mnt/"):
        return Path(value[5].upper()+":"+value[6:])
    if sys.platform != "win32" and len(value)>2 and value[1] == ":":
        return Path("/mnt/"+value[0].lower()+value[2:].replace("\\", "/"))
    return Path(value)

def verify(path):
    evidence = json.loads(path.read_text(encoding="utf-8"))
    assert evidence["tool_sha256"] == sha(Path(__file__).read_bytes()), "inspector changed"
    functions = instructions = 0
    for saved in evidence["components"]:
        current = inspect(saved["component"], [int(row["address"], 0) for row in saved["records"]], False)
        assert current == saved, saved["component"]
        functions += len(current["records"])
        instructions += sum(row["instruction_count"] for row in current["records"])
    for row in evidence["source_snapshots"]:
        assert sha(native_path(row["path"]).read_bytes()) == row["sha256"], row["path"]
    return dict(ok=True, functions=functions, instructions=instructions,
                source_snapshots=len(evidence["source_snapshots"]),
                limit="provenance only; not branch execution, Android networking or vehicle validation")

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--component", choices=SOURCES, default="accessoryd")
    parser.add_argument("--address", action="append", default=[])
    parser.add_argument("--assembly", action="store_true")
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    out = verify(args.verify) if args.verify else inspect(args.component, [int(a,0) for a in args.address], args.assembly)
    print(json.dumps(out, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
