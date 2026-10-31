"""Read-only 24A446 SETUP response/GET-info/URL provenance audit (python -B).

Prints JSON; --verify compares a saved snapshot. Never runs Apple code or writes
to the firmware/cache. Instruction provenance is not runtime conformance.
"""
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
from firmware_cache import Cache
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

GROUPS = {
    "AirPlaySender": ("934ec850a9ab7623f1d8", [
        0x251a59338, 0x251b5cfe0, 0x251a5dec0, 0x2519c69f0, 0x2519c5858,
        0x251a5a840, 0x251afe62c, 0x251a56e44, 0x2519bbf24]),
    "CoreUtils": ("8792f09ecc40428a5f65", [
        0x18be373d8, 0x18be37434, 0x18be38df0,
        0x18be36428, 0x18be41338, 0x18be41994, 0x18be588b0, 0x18be40c9c]),
    "APTransport": ("dcc06dc3316817912f6d", [
        0x24fdc8e50, 0x24fdc93c0, 0x24fda58ec]),
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def kernel_symbols(cache):
    """Resolve the two socket-address syscalls from original cached LC_SYMTAB."""
    path = FW / "extracted/24A446/dyld/dyld_shared_cache_arm64e"
    with path.open("rb") as stream:
        header = stream.read(0x100)
        offset, count = struct.unpack_from("<QQ", header, 0x88)
        stream.seek(offset)
        table = stream.read(count * 32)
        matches = []
        for index in range(count):
            _, base, size, path_offset = struct.unpack_from("<16sQII", table, index * 32)
            if base <= 0x237f06a1c < base + size:
                stream.seek(path_offset)
                name = stream.read(512).split(b"\0", 1)[0].decode()
                matches.append((base, name))
    if len(matches) != 1:
        raise ValueError("ambiguous kernel image")
    base, image_name = matches[0]
    header = cache.read(base, 32)
    commands = cache.read(base + 32, struct.unpack_from("<I", header, 20)[0])
    segments = []
    symtab = None
    offset = 0
    for _ in range(struct.unpack_from("<I", header, 16)[0]):
        command, size = struct.unpack_from("<II", commands, offset)
        if command == 25:
            segments.append(struct.unpack_from("<QQQQ", commands, offset + 24))
        elif command == 2:
            symtab = struct.unpack_from("<IIII", commands, offset + 8)
        offset += size
    if symtab is None:
        raise ValueError("kernel LC_SYMTAB missing")

    def read_file(file_offset, length):
        a, _, f, _ = next((a, size, f, fs) for a, size, f, fs in segments
                         if f <= file_offset and file_offset + length <= f + fs)
        return cache.read(a + file_offset - f, length)

    symbol_offset, symbol_count, string_offset, string_length = symtab
    records = read_file(symbol_offset, symbol_count * 16)
    targets = {}
    for index in range(symbol_count):
        string_index, _, _, _, address = struct.unpack_from("<IBBHQ", records, index * 16)
        if address in (0x237f019a0, 0x237f06a1c):
            if string_index >= string_length:
                raise ValueError("bad string index")
            name = read_file(string_offset + string_index, 128).split(b"\0", 1)[0].decode()
            targets.setdefault(hex(address), []).append(name)
    if "_getsockname" not in targets.get("0x237f019a0", []):
        raise ValueError("getsockname not resolved")
    if "_getpeername" not in targets.get("0x237f06a1c", []):
        raise ValueError("getpeername not resolved")
    return {"image": image_name, "image_base": hex(base), "targets": targets,
            "nlist_sha256": digest(records)}


def audit():
    cache = Cache(FW / "extracted/24A446/dyld")
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    sources = {}
    try:
        for component, (folder_id, addresses) in GROUPS.items():
            path = FW / f"extracted/24A446/binaries/{component}/{component}"
            image = Image(path)
            functions = []
            for address in addresses:
                end = image.starts[bisect.bisect_right(image.starts, address)]
                raw = image.read(address, end - address)
                if raw != cache.read(address, len(raw)):
                    raise ValueError(f"dyld/extracted mismatch: {address:#x}")
                if sum(x.size for x in md.disasm(raw, address)) != len(raw):
                    raise ValueError(f"incomplete instruction decode: {address:#x}")
                folder = FW / f"analysis/decompiler-cache/24A446/{component}/{folder_id}/functions"
                cached = folder / f"f_{address:x}.bin"
                if cached.exists() and cached.read_bytes() != raw:
                    raise ValueError(f"cached fragment mismatch: {address:#x}")
                functions.append({"address": hex(address), "end": hex(end),
                                  "sha256": digest(raw), "bytes": len(raw),
                                  "cache_fragment_present": cached.exists(),
                                  "original_dyld_equal": True, "decoded_complete": True})
            sources[component] = {"path_relative_to_firmware": path.relative_to(FW).as_posix(),
                                  "sha256": digest(image.data), "functions": functions}
        bindings = []
        for slot, expected in ((0x2761280d0, 0x276128138),
                               (0x276128158, 0x251afe62c),
                               (0x271bf4d80, 0x237f019a0),
                               (0x271bf4d78, 0x237f06a1c)):
            target = cache.ptr(slot)
            if target != expected:
                raise ValueError(f"unexpected pointer {slot:#x}")
            bindings.append({"slot": hex(slot), "raw": cache.read(slot, 8).hex(),
                             "target": hex(target)})
        keys = []
        for slot, expected in ((0x268104150, "info"), (0x268104158, "skipRecord")):
            first = cache.ptr(slot)
            target = cache.ptr(first)
            value = cache.cfstr(target)
            if value != expected:
                raise ValueError("unexpected response key")
            keys.append({"slot": hex(slot), "indirect": hex(first), "cfstring": hex(target),
                         "value": value})
        scan_slot = 0x18be426d0 + (ord("i") - 0x5b) * 4
        scan_raw = cache.read(scan_slot, 4)
        scan_target = 0x18be41c4c + struct.unpack("<i", scan_raw)[0]
        if scan_target != 0x18be41cb4:
            raise ValueError("unexpected VSNScanF i-dispatch")
        return {"schema": "setup-response-branches-v1", "build": "24A446",
                "firmware_executed": False, "sources": sources,
                "pointer_bindings": bindings, "keys": keys,
                "socket_symbols": kernel_symbols(cache),
                "scan_i_dispatch": {"slot": hex(scan_slot), "raw": scan_raw.hex(),
                                    "target": hex(scan_target)},
                "scope": "Static bounded consumers, numeric conversion and URL producer; not full endpoint/platform or SETUP presence coverage"}
    finally:
        cache.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    result = audit()
    if args.verify:
        expected = json.loads(args.verify.read_text(encoding="utf-8"))
        if expected != result:
            raise SystemExit("FAIL: snapshot differs")
        print("PASS: 20 original functions, response keys, vtable, integer dispatch and socket-address symbols match snapshot")
    else:
        print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
