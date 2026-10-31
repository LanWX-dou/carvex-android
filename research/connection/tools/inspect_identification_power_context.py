"""Read-only 24A446 power-provider context audit. JSON/stdout only; python -B."""
from __future__ import annotations
import argparse
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
from firmware_cache import Cache

SOURCE = FW / "extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd"
ADDRESSES = [0x1000c0758, 0x10018f128, 0x1001939fc, 0x10018f134,
             0x10018f17c, 0x1000fad70, 0x1000f5c18, 0x1000f8c68,
             0x100191698, 0x10018a96c, 0x10019288c, 0x1000cd970,
             0x1000cdac4, 0x1000cdf60, 0x10002a650]

def audit():
    """Recompute the bounded chapter-19 snapshot from original source bytes."""
    groups = {
        "accessoryd": (SOURCE, [0x1000c0758, 0x1000c07a8, 0x10018f128,
            0x1001939fc, 0x100016a64, 0x10018f134, 0x10018f17c,
            0x100191698, 0x10018a96c, 0x10019288c, 0x1000f6094,
            0x1000cd970, 0x1000fad70, 0x1000f5c18]),
        "bluetoothd": (FW / "extracted/24A446/components/24A446__iPhone18,1/root/usr/sbin/bluetoothd", [0x1007a4520]),
        "AirPlaySender": (FW / "extracted/24A446/binaries/AirPlaySender/AirPlaySender", [0x251af5e58, 0x251af6b08]),
        "CoreAccessories": (FW / "extracted/24A446/binaries/CoreAccessories/CoreAccessories", [0x204415440, 0x204415740]),
    }
    cache = Cache(FW / "extracted/24A446/dyld")
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    sources = {}
    try:
        for label, (path, addresses) in groups.items():
            image = Image(path)
            records = []
            for address in addresses:
                end = image.starts[bisect.bisect_right(image.starts, address)]
                raw = image.read(address, end - address)
                decoded = list(md.disasm(raw, address))
                if sum(ins.size for ins in decoded) != len(raw):
                    raise ValueError(f"incomplete decode: {label} {address:#x}")
                record = {"address": hex(address), "end": hex(end), "length": len(raw),
                          "sha256": hashlib.sha256(raw).hexdigest(), "decoded_complete": True}
                if label in ("AirPlaySender", "CoreAccessories"):
                    if cache.read(address, len(raw)) != raw:
                        raise ValueError(f"extracted image/cache mismatch: {label} {address:#x}")
                    record["original_dyld_bytes_equal"] = True
                records.append(record)
            sources[label] = {"path_relative_to_firmware": path.relative_to(FW).as_posix(),
                              "sha256": hashlib.sha256(image.data).hexdigest(), "functions": records}
        tables = []
        for name, address, count, indices in (
            ("_kACCConnection_Type_Strings", 0x26c2c8b08, 12, [2, 3, 5, 6, 11]),
            ("_kACCEndpoint_TransportType_Strings", 0x26c2c8e30, 20, [0, 2, 3, 4, 8, 19]),
        ):
            entries = []
            for index in indices:
                slot = address + 8 * index
                target = cache.ptr(slot)
                value = cache.cstr(target)
                entries.append({"index": index, "raw_u64": hex(struct.unpack("<Q", cache.read(slot, 8))[0]),
                                "target": hex(target), "string": value})
            tables.append({"name": name, "address": hex(address), "length": count * 8,
                           "sha256": hashlib.sha256(cache.read(address, count * 8)).hexdigest(),
                           "pointer_decoder": "original dyld v5 slide metadata; firmware_cache.Cache.ptr",
                           "selected_entries": entries})
        acc_imports = imported_symbols(Image(SOURCE))
        bt_imports = imported_symbols(Image(groups["bluetoothd"][0]))
        return {"schema": "identification-power-provider-context-v1", "build": "24A446",
                "device": "iPhone18,1", "firmware_executed": False,
                "scope": "bounded static producer/getter audit; Android runtime mapping not implemented",
                "sources": sources, "tables": tables,
                "indirect_symbols": {"accessoryd": {hex(a): acc_imports[a] for a in [0x10022b420, 0x10022b438]},
                                     "bluetoothd": {hex(a): bt_imports[a] for a in [0x100909f00, 0x100909f10]}},
                "airplay_dynamic_symbol_strings": {hex(a): cache.cstr(a) for a in [0x251bff4b1, 0x251bff4d6]},
                "open": ["platform power mode4 provider", "Android live transport-context mapping",
                         "all other connection/endpoint producers", "real-vehicle equivalence"]}
    finally:
        cache.close()

def names(image, address):
    return sorted(set(n for n in image.symbols.get(address, []) if n))

def imported_symbols(image):
    """Resolve Mach-O indirect symbol entries, not guessed chained-fixup binds."""
    data = image.data
    symtab = indirect = None
    sections = []
    offset = 32
    for _ in range(struct.unpack_from("<I", data, 16)[0]):
        command, size = struct.unpack_from("<II", data, offset)
        if command == 2:
            symtab = struct.unpack_from("<IIII", data, offset + 8)
        elif command == 0xb:
            indirect = struct.unpack_from("<II", data, offset + 56)
        elif command == 0x19:
            count = struct.unpack_from("<I", data, offset + 64)[0]
            for index in range(count):
                at = offset + 72 + 80 * index
                address, length = struct.unpack_from("<QQ", data, at + 32)
                flags, reserved1, reserved2 = struct.unpack_from("<III", data, at + 64)
                if flags & 0xff in (6, 7, 8):
                    stride = reserved2 if flags & 0xff == 8 else 8
                    sections.append((address, length, reserved1, stride))
        offset += size
    records = {}
    if symtab and indirect:
        symbol_offset, symbol_count, string_offset, string_size = symtab
        indirect_offset, indirect_count = indirect
        for address, length, first, stride in sections:
            if stride <= 0:
                raise ValueError("invalid indirect-symbol stride")
            for index in range(length // stride):
                if first + index >= indirect_count:
                    raise ValueError("indirect-symbol index out of range")
                symbol = struct.unpack_from("<I", data, indirect_offset + 4 * (first + index))[0]
                if symbol & 0xc0000000:
                    continue
                if symbol >= symbol_count:
                    raise ValueError("symbol index out of range")
                name_index = struct.unpack_from("<I", data, symbol_offset + 16 * symbol)[0]
                start = string_offset + name_index
                end = data.find(b"\0", start, string_offset + string_size)
                if end < 0:
                    raise ValueError("unterminated symbol")
                records[address + stride * index] = data[start:end].decode("utf-8")
    return records

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--image", type=Path, default=SOURCE,
                        help="Original read-only Mach-O image (default: accessoryd)")
    parser.add_argument("--inspect", nargs="+", type=lambda value: int(value, 0))
    parser.add_argument("--xrefs", nargs="+", type=lambda value: int(value, 0))
    parser.add_argument("--strings", nargs="+", type=lambda value: int(value, 0))
    parser.add_argument("--imports", nargs="+", type=lambda value: int(value, 0))
    parser.add_argument("--summary", action="store_true")
    parser.add_argument("--asm", action="store_true")
    parser.add_argument("--audit", action="store_true")
    parser.add_argument("--verify", type=Path, help="Read-only compare a saved --audit snapshot")
    args = parser.parse_args()
    if args.audit or args.verify:
        report = audit()
        if args.verify:
            if json.loads(args.verify.read_text(encoding="utf-8")) != report:
                raise SystemExit("snapshot mismatch")
            print("PASS: source hashes, original code bytes, dyld tables and imported symbols match snapshot")
        else:
            print(json.dumps(report, ensure_ascii=False, separators=(",", ":")))
        return
    image = Image(args.image)
    imports = imported_symbols(image)
    for address, name in imports.items():
        image.symbols.setdefault(address, []).append(name + " [indirect symbol]")
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    if args.imports:
        print(json.dumps([{"address": hex(a), "import": imports.get(a)} for a in args.imports], indent=2))
        return
    if args.strings:
        print(json.dumps([{"address": hex(a), "string": image.cstr(a)} for a in args.strings], indent=2))
        return
    if args.xrefs:
        md.skipdata = True
        targets = set(args.xrefs)
        refs = []
        address, length, _ = image.sections[("__TEXT", "__text")]
        for ins in md.disasm(image.read(address, length), address):
            if ins.mnemonic not in ("bl", "b") or not ins.op_str.startswith("#0x"):
                continue
            target = int(ins.op_str[1:], 16)
            if target in targets:
                function = image.function(ins.address)
                refs.append({"at": hex(ins.address), "target": hex(target), "function": hex(function),
                             "names": names(image, function)})
        print(json.dumps(refs, indent=2))
        return
    records = []
    for address in args.inspect or ADDRESSES:
        index = bisect.bisect_right(image.starts, address)
        end = image.starts[index]
        raw = image.read(address, end-address)
        decoded = list(md.disasm(raw, address))
        decoded_length = sum(ins.size for ins in decoded)
        if args.asm:
            print(hex(address), names(image, address), "end=" + hex(end),
                  "decoded=" + str(decoded_length) + "/" + str(len(raw)))
            for ins in decoded:
                target_names = names(image, int(ins.op_str[1:], 16)) if ins.mnemonic in ("b", "bl") and ins.op_str.startswith("#0x") else []
                print(hex(ins.address), ins.mnemonic, ins.op_str, " | ".join(target_names))
            continue
        record = {"address": hex(address), "names": names(image, address), "end": hex(end),
                  "length": len(raw), "sha256": hashlib.sha256(raw).hexdigest(),
                  "decoded_length": decoded_length, "decoded_complete": decoded_length == len(raw)}
        if not args.summary:
            record["instructions"] = [{"at": hex(ins.address), "bytes": ins.bytes.hex(),
                                       "asm": ins.mnemonic + " " + ins.op_str,
                                       **({"target_names": names(image, int(ins.op_str[1:], 16))}
                                          if ins.mnemonic in ("bl", "b") and ins.op_str.startswith("#0x") else {})}
                                      for ins in decoded]
        records.append(record)
    if args.asm:
        return
    print(json.dumps({"source": str(args.image), "source_sha256": hashlib.sha256(image.data).hexdigest(),
                      "functions": records, "firmware_executed": False}, indent=2))

if __name__ == "__main__":
    main()
