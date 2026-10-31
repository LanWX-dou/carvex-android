"""Read-only 24A446 control-SETUP producer oracle; never executes firmware.

Use python -B. Prints original-byte/key provenance as JSON; --verify compares
an existing snapshot. It does not generate docs or write firmware/cache files.
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
        0x251a59708, 0x251a59338, 0x251b5cfe0, 0x2519c5858,
        0x2519c4688, 0x251a587a0, 0x251a53780, 0x251a58ddc,
        0x251b5b358, 0x251a54d0c, 0x251a61ab0]),
    "APTransport": ("dcc06dc3316817912f6d", [
        0x24fda8330, 0x24fda839c, 0x24fe11400]),
    "AirPlaySupport": ("not-used", [0x226e65c24]),
}
KEYS = {
    0x27612eff0: "updateSessionRequest", 0x27612f010: "k5lVWbXuiZHLA17KGiVUAA",
    0x27612f030: "sessionCorrelationUUID", 0x27612f170: "timingPort",
    0x27612f190: "isRemoteControlOnly", 0x27612f1b0: "isScreenMirroringSession",
    0x27612f1d0: "isAuxiliaryScreenSession", 0x27612f1f0: "isSharedConnection",
    0x27612f210: "diagnosticsAndUsage", 0x27612f230: "internalBuild",
    0x27612f250: "osName", 0x27612f270: "osVersion",
    0x27612f290: "keepAliveLowPower", 0x27612f2b0: "features",
    0x27612f2d0: "modelCode", 0x27612f2f0: "udid",
    0x27612f310: "timingProtocol", 0x27612efd0: "timingPeerInfo",
    0x27612f330: "timingPeerList", 0x27612efb0: "asyncPTPClockConfig",
    0x27612f610: "combinedGetInfoWithControlSetup", 0x27612f630: "qualifier",
    0x27612eb70: "None", 0x27612eb90: "PTP", 0x27612ebb0: "NTP",
    0x27612ecb0: "ptpReenableRedundantClusterLinks",
}
IMPORTS = {
    0x2680fbfc0: "TransportType", 0x2680fbfc8: "UUID",
    0x2680fc050: "LocalMACAddress", 0x268104060: "PortLocal",
    0x268104070: "NetworkClock_Type", 0x268104088: "NetworkClockType_PTP",
    0x2680d3038: "ProductName", 0x2680d3050: "ProductVersion",
}
ANCHORS = {
    0x251a5995c: "1f150071", 0x251a59968: "00010054",
    0x251a59970: "28bf9a95", 0x251a599b8: "350c00b4",
    0x251a599bc: "130c00b5", 0x251a59d90: "82c380b9",
    0x251a59d94: "a2000034", 0x251a59dec: "a1010054",
    0x251a59ed8: "c0010034", 0x251a59f54: "8bc49a95",
    0x251a59f68: "86c49a95", 0x251a59f84: "41030054",
    0x251a59fa8: "a8430035", 0x251a59fac: "1f080071",
    0x251a59fd0: "a20000b4", 0x251a59fe8: "e1000014",
    0x251a5908c: "e0c200b9", 0x2519c61ac: "410740f9",
    0x2519c61c8: "865b0694", 0x251a587cc: "f6d700a9",
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def symbols_at(cache, target):
    """Resolve original cached Mach-O LC_SYMTAB, not a decompiler's names."""
    path = FW / "extracted/24A446/dyld/dyld_shared_cache_arm64e"
    with path.open("rb") as stream:
        header = stream.read(0x100)
        offset, count = struct.unpack_from("<QQ", header, 0x88)
        stream.seek(offset)
        entries = stream.read(count * 32)
        matches = []
        for index in range(count):
            _, base, size, path_offset = struct.unpack_from("<16sQII", entries, index * 32)
            if base <= target < base + size:
                stream.seek(path_offset)
                name = stream.read(512).split(b"\0", 1)[0].decode()
                matches.append((base, name))
    if len(matches) != 1:
        raise ValueError(f"ambiguous image for {target:#x}")
    base, name = matches[0]
    header = cache.read(base, 32)
    commands = cache.read(base + 32, struct.unpack_from("<I", header, 20)[0])
    segments, symtab = [], None
    offset = 0
    for _ in range(struct.unpack_from("<I", header, 16)[0]):
        command, size = struct.unpack_from("<II", commands, offset)
        if command == 25:
            segments.append(struct.unpack_from("<QQQQ", commands, offset + 24))
        elif command == 2:
            symtab = struct.unpack_from("<IIII", commands, offset + 8)
        offset += size
    if symtab is None:
        raise ValueError("missing LC_SYMTAB")

    def read_file(file_offset, length):
        a, _, f, _ = next((a, vs, f, fs) for a, vs, f, fs in segments
                         if f <= file_offset and file_offset + length <= f + fs)
        return cache.read(a + file_offset - f, length)

    off, count, string_off, string_len = symtab
    raw = read_file(off, count * 16)
    names = []
    for index in range(count):
        string_index, _, _, _, address = struct.unpack_from("<IBBHQ", raw, index * 16)
        if address == target:
            if string_index >= string_len:
                raise ValueError("bad symbol string offset")
            names.append(read_file(string_off + string_index, 256).split(b"\0", 1)[0].decode())
    return {"image": name, "address": hex(target), "names": names,
            "nlist_sha256": sha(raw)}


def audit():
    cache = Cache(FW / "extracted/24A446/dyld")
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    try:
        sources = {}
        for component, (folder_id, addresses) in GROUPS.items():
            path = FW / f"extracted/24A446/binaries/{component}/{component}"
            im = Image(path)
            functions = []
            for address in addresses:
                end = im.starts[bisect.bisect_right(im.starts, address)]
                raw = im.read(address, end - address)
                if raw != cache.read(address, len(raw)):
                    raise ValueError(f"dyld/extracted mismatch {address:#x}")
                if sum(x.size for x in md.disasm(raw, address)) != len(raw):
                    raise ValueError(f"incomplete instruction decode {address:#x}")
                cached = FW / f"analysis/decompiler-cache/24A446/{component}/{folder_id}/functions/f_{address:x}.bin"
                if cached.exists() and cached.read_bytes() != raw:
                    raise ValueError(f"cached fragment mismatch {address:#x}")
                functions.append({"address": hex(address), "end": hex(end), "bytes": len(raw),
                                  "sha256": sha(raw), "original_dyld_equal": True,
                                  "decoded_complete": True, "cached_fragment_present": cached.exists()})
            sources[component] = {"sha256": sha(im.data), "functions": functions}
        keys = []
        for address, expected in KEYS.items():
            value = cache.cfstr(address)
            if value != expected:
                raise ValueError(f"CFString mismatch {address:#x}: {value}")
            keys.append({"address": hex(address), "value": value})
        imports = []
        for slot, expected in IMPORTS.items():
            first = cache.ptr(slot)
            target = cache.ptr(first)
            value = cache.cfstr(target)
            if value != expected:
                raise ValueError(f"import mismatch {slot:#x}")
            imports.append({"slot": hex(slot), "indirect": hex(first),
                            "cfstring": hex(target), "value": value})
        anchors = []
        for address, expected in ANCHORS.items():
            raw = cache.read(address, 4)
            if raw.hex() != expected:
                raise ValueError(f"anchor mismatch {address:#x}")
            insn = next(md.disasm(raw, address))
            anchors.append({"address": hex(address), "bytes": raw.hex(),
                            "instruction": f"{insn.mnemonic} {insn.op_str}".strip()})
        providers = [symbols_at(cache, a) for a in [0x226e65c24, 0x1806ba8d8, 0x18efab8e0, 0x187f0defc]]
        boot_key = cache.cstr(0x226f4e4b1)
        if boot_key != "kern.bootsessionuuid":
            raise ValueError("boot UUID sysctl key differs")
        return {"schema": "control-setup-request-v1", "build": "24A446",
                "firmware_executed": False, "sources": sources, "keys": keys,
                "imports": imports, "anchors": anchors, "provider_symbols": providers,
                "boot_uuid_key": {"address": "0x226f4e4b1", "value": boot_key},
                "scope": "Common control SETUP producer and kind5 early exit, timing/feature-input provenance. Not all higher-layer providers or runtime conformance."}
    finally:
        cache.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args()
    result = audit()
    if args.verify:
        expected = json.loads(args.verify.read_text(encoding="utf-8"))
        if result != expected:
            raise SystemExit("FAIL: snapshot differs")
        print("PASS: 15 original functions, SETUP key imports, branch anchors and provider symbols match snapshot")
    else:
        print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
