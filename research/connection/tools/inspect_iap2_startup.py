"""Read-only startup audit. Original bytes and direct callsites, stdout JSON.

Does not execute firmware, write caches, or prove cross-process runtime order.
"""
from pathlib import Path
import argparse
import bisect
import hashlib
import json
import struct
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image
from firmware_cache import Cache
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = FW / "extracted/24A446/components/24A446__iPhone18,1/root"
SOURCES = {
    "accessoryd": ROOT / "System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd",
    "bluetoothd": ROOT / "usr/sbin/bluetoothd",
    "CoreAccessories": FW / "extracted/24A446/binaries/CoreAccessories/CoreAccessories",
}
TARGETS = {
    "accessoryd": [0x10018a96c, 0x10018e334, 0x100139348, 0x100139034,
        0x10004cce8, 0x1000b845c, 0x1000cf5b8, 0x10017a0f0,
        0x100129350, 0x1000cae38, 0x1000cae54, 0x100033fd0,
        0x100034a70, 0x100031c50, 0x1000cb158, 0x10010395c,
        0x100008698, 0x100034a7c, 0x10002f8dc, 0x10000a5d0,
        0x100102e20, 0x10000ada0, 0x10002fac8, 0x10019c124,
        0x10000995c, 0x100009c3c, 0x100009cf8, 0x10000b308, 0x100007728],
    "bluetoothd": [0x1007a4240, 0x1007a4520, 0x1007a48d0,
        0x1007a4934, 0x1007a4c04, 0x1007a4d78, 0x1007a5360, 0x1007a5628],
    "CoreAccessories": [0x204415740],
}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def import_stubs(im):
    """Resolve Mach-O indirect symbol entries, not guessed stub targets."""
    offset = 32
    sections = []
    symtab = indirect = None
    for _ in range(struct.unpack_from("<I", im.data, 16)[0]):
        cmd, size = struct.unpack_from("<II", im.data, offset)
        if cmd == 2:
            symtab = struct.unpack_from("<IIII", im.data, offset + 8)
        elif cmd == 11:
            indirect = struct.unpack_from("<II", im.data, offset + 56)
        elif cmd == 25:
            for i in range(struct.unpack_from("<I", im.data, offset + 64)[0]):
                at = offset + 72 + i * 80
                flags, reserved1, reserved2 = struct.unpack_from("<III", im.data, at + 64)
                if flags & 0xff == 8:
                    addr, length = struct.unpack_from("<QQ", im.data, at + 32)
                    sections.append((addr, length, reserved1, reserved2))
        offset += size
    assert symtab and indirect
    symoff, nsyms, stroff, strsize = symtab
    rows = []
    for target, expected in [(0x100909f00, "_acc_transportClient_createConnection"),
                             (0x100909f10, "_acc_transportClient_createEndpoint")]:
        addr, length, first, stride = next(s for s in sections if s[0] <= target < s[0] + s[1])
        assert stride and (target - addr) % stride == 0
        index = first + (target - addr) // stride
        assert index < indirect[1]
        symbol = struct.unpack_from("<I", im.data, indirect[0] + index * 4)[0]
        assert symbol < nsyms
        string = struct.unpack_from("<I", im.data, symoff + symbol * 16)[0]
        end = im.data.index(b"\0", stroff + string, stroff + strsize)
        name = im.data[stroff + string:end].decode()
        assert name == expected, (hex(target), name)
        rows.append({"address": hex(target), "indirect_index": index,
                     "symbol_index": symbol, "symbol": name, "hex": im.read(target, stride).hex()})
    return rows

def shared_cache_check(im):
    """Verify wrapper bytes and selector against the original dyld cache."""
    folder = FW / "extracted/24A446/dyld"
    cache = Cache(folder)
    try:
        address = 0x204415740
        end = im.starts[bisect.bisect_right(im.starts, address)]
        raw = cache.read(address, end - address)
        assert raw == im.read(address, end - address)
        stub_address, selector_address = 0x20806b980, 0x1f74b559c
        stub = cache.read(stub_address, 16)
        assert stub.hex() == "41a2f7d0217016919e53fe17200020d4"
        selector = cache.cstr(selector_address)
        assert selector == "createEndpointWithTransportType:andProtocol:andIdentifier:andDataOutHandler:forConnectionWithUUID:publishConnection:"
        slices = []
        for at, data, label in [(address, raw, "C wrapper"), (stub_address, stub, "selector stub"),
                                (selector_address, selector.encode() + b"\0", "selector")]:
            a, b, fo, path = next(m for m in cache.maps if m[0] <= at and at + len(data) <= m[1])
            slices.append({"label": label, "address": hex(at), "size": len(data), "sha256": sha(data),
                           "cache_file": str(path), "file_offset": hex(fo + at - a)})
        return {"wrapper_matches_original_cache": True, "selector": selector,
                "stub_hex": stub.hex(), "slices": slices,
                "limit": "Hashes cover these slices, not the complete shared cache."}
    finally:
        cache.close()

def collect(component, addresses, include_assembly=False):
    path = SOURCES[component]
    im = Image(path)
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    start, length, _ = im.sections[("__TEXT", "__text")]
    rows = []
    for address in addresses:
        idx = bisect.bisect_right(im.starts, address)
        lo = im.starts[idx - 1]
        assert lo == address, f"Not a function start: {address:#x}; use a raw slice for stubs"
        hi = im.starts[idx] if idx < len(im.starts) else start + length
        raw = im.read(lo, hi - lo)
        caches = []
        for cached in (FW / "analysis/decompiler-cache/24A446" / component).glob(f"*/functions/f_{address:x}.bin"):
            same = cached.read_bytes() == raw
            assert same, str(cached)
            caches.append({"path": str(cached), "matches_original": same})
        row = {"address": hex(lo), "end": hex(hi), "sha256": sha(raw),
            "symbols": sorted(set(n for n in im.symbols.get(lo, []) if n)),
            "cache_matches": caches}
        if include_assembly:
            row["assembly"] = [f"{i.address:#x}: {i.bytes.hex()} {i.mnemonic} {i.op_str}"
                for i in md.disasm(raw, lo)]
        rows.append(row)
    calls = []
    target_set = set(addresses)
    for index, (word,) in enumerate(struct.iter_unpack("<I", im.read(start, length))):
        if word & 0x7c000000 != 0x14000000:
            continue
        at = start + index * 4
        offset = word & 0x3ffffff
        if offset & 0x2000000:
            offset -= 0x4000000
        target = at + offset * 4
        if target in target_set:
            calls.append({"site": hex(at), "target": hex(target), "function": hex(im.function(at)),
                "instruction": "bl" if word & 0x80000000 else "b"})
    result = {"component": component, "source": str(path), "sha256": sha(im.data),
        "functions": rows, "direct_calls": calls}
    if component == "bluetoothd":
        result["verified_import_stubs"] = import_stubs(im)
    if component == "CoreAccessories":
        result["original_shared_cache"] = shared_cache_check(im)
    if component == "accessoryd":
        result["constants"] = [{"address": hex(at), "hex": im.read(at, count).hex()}
            for at, count in [(0x1001b32c0, 16), (0x1001b3378, 10), (0x100018ec4, 72)]]
        states = []
        for state in range(4):
            entry = 0x100219600 + state * 16
            table, count = im.ptr(entry), im.read(entry + 8, 1)[0]
            entries = []
            for i in range(count):
                at = table + 16 * i
                raw = im.read(at, 16)
                action = im.ptr(at)
                entries.append({"address": hex(at), "raw": raw.hex(),
                    "action": hex(action) if action else None,
                    "event": raw[9], "next_state": raw[8]})
            states.append({"state": state, "entries": entries})
        result["startup_state_table"] = states
    return result

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--component", choices=list(SOURCES))
    p.add_argument("--address", action="append")
    p.add_argument("--assembly", action="store_true")
    args = p.parse_args()
    components = [args.component] if args.component else list(SOURCES)
    report = {"baseline": "24A446 / iPhone18,1", "firmware_executed": False,
        "tool_sha256": sha(Path(__file__).read_bytes()),
        "components": [collect(c, [int(a, 0) for a in args.address] if args.address else TARGETS[c], args.assembly) for c in components],
        "limits": ["Direct B/BL references exclude indirect calls and cross-process dispatch.",
            "State table entries include reserved zero records; count is not coverage.",
            "CoreAccessories is an extracted dyld image; it is not the accessoryd main executable."]}
    print(json.dumps(report, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
