"""Read-only 24A446 protocol-header producer and Android declaration audit.

Prints JSON to stdout. Never edits reference material or creates bytecode.
Checks selected original bytes, not real receiver acceptance or execution.
"""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_cache import Cache
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def main():
    cache = Cache(FW / "extracted/24A446/dyld")
    dis = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    images = {name: Image(FW / f"extracted/24A446/binaries/{name}/{name}")
              for name in ("APTransport", "AirPlaySupport", "CoreUtils")}

    def region(address, length):
        matches = [(a, off, path) for a, b, off, path in cache.maps
                   if a <= address and address + length <= b]
        assert len(matches) == 1
        a, offset, path = matches[0]
        raw = cache.read(address, length)
        return {"address": hex(address), "length": length,
                "cache_path": str(path), "cache_file_offset": offset + address - a,
                "sha256": hashlib.sha256(raw).hexdigest(), "hex": raw.hex()}

    raw_path = FW / "analysis/decompiler-cache/24A446/APTransport/dcc06dc3316817912f6d/functions/f_24fda58ec.bin"
    raw = raw_path.read_bytes()
    address = 0x24fda58ec
    assert raw == images["APTransport"].read(address, len(raw)) == cache.read(address, len(raw))
    route = {"component": "APTransport", "address": hex(address),
             "raw_path": str(raw_path), "length": len(raw),
             "sha256": hashlib.sha256(raw).hexdigest(), "raw_matches_image_and_cache": True,
             "reviewed_range": ["0x24fda6330", "0x24fda6388"],
             "instructions": [f"{x.address:#x}: {x.mnemonic} {x.op_str}"
                              for x in dis.disasm(cache.read(0x24fda6330, 0x58), 0x24fda6330)]}
    entry = 0x2500ee660
    stub = region(entry, 16)
    instructions = list(dis.disasm(cache.read(entry, 16), entry))
    target = None
    if instructions[0].mnemonic == "adrp" and instructions[1].mnemonic == "add":
        target = int(instructions[0].op_str.split("#")[1], 0) + int(instructions[1].op_str.split("#")[1], 0)
        if instructions[2].mnemonic == "ldr":
            target = cache.ptr(target)
        elif instructions[2].mnemonic != "br":
            raise ValueError("unreviewed trampoline shape")
    assert target is not None
    stub.update({"instructions": [f"{x.mnemonic} {x.op_str}" for x in instructions], "target": hex(target)})
    provider = None
    for component, image in images.items():
        if target not in image.symbols:
            continue
        starts = [value for value in image.starts if value > target]
        assert starts
        length = min(starts) - target
        assert 0 < length <= 4096
        source_bytes = cache.read(target, length)
        assert source_bytes == image.read(target, length)
        provider = {**region(target, length), "component": component,
                    "symbols": image.symbols[target], "matches_extracted_image": True,
                    "instructions": [f"{x.address:#x}: {x.mnemonic} {x.op_str}"
                                     for x in dis.disasm(source_bytes, target)]}
        break
    assert provider is not None, f"provider target not in reviewed images: {target:#x}"
    cached_support = FW / "analysis/decompiler-cache/24A446/AirPlaySupport/5f566a24689df2ec27cb/functions"
    for start in (0x226ed0894, 0x226ed0950):
        saved = (cached_support / f"f_{start:x}.bin").read_bytes()
        assert saved == cache.read(start, len(saved)) == images["AirPlaySupport"].read(start, len(saved))
    block_address = 0x273d50478
    invoke_address = cache.ptr(block_address + 16)
    support = images["AirPlaySupport"]
    invoke_length = min(value for value in support.starts if value > invoke_address) - invoke_address
    assert 0 < invoke_length <= 4096
    invoke_bytes = cache.read(invoke_address, invoke_length)
    assert invoke_bytes == support.read(invoke_address, invoke_length)
    initializer = {"block": region(block_address, 32), "invoke_pointer_slot": hex(block_address + 16),
                   "invoke": {**region(invoke_address, invoke_length),
                              "symbols": support.symbols.get(invoke_address, []),
                              "matches_extracted_image": True,
                              "instructions": [f"{x.address:#x}: {x.mnemonic} {x.op_str}"
                                               for x in dis.disasm(invoke_bytes, invoke_address)]},
                   "global_initial_bytes": region(0x2704caed0, 4)}
    initializer["arguments"] = [{"address": hex(value), "value": cache.cfstr(value),
                                 "header": region(value, 32),
                                 "characters": region(cache.ptr(value + 16), len(cache.cfstr(value)) + 1)}
                                for value in (0x273d53f40, 0x273d50760)]
    preference_stub = list(dis.disasm(cache.read(0x22818c910, 16), 0x22818c910))
    assert preference_stub[0].mnemonic == "adrp" and preference_stub[1].mnemonic == "add"
    preference_target = int(preference_stub[0].op_str.split("#")[1], 0) + int(preference_stub[1].op_str.split("#")[1], 0)
    if preference_stub[2].mnemonic == "ldr":
        preference_target = cache.ptr(preference_target)
    else:
        assert preference_stub[2].mnemonic == "br"
    initializer["preference_reader"] = {**region(0x22818c910, 16), "target": hex(preference_target),
                                        "instructions": [f"{x.mnemonic} {x.op_str}" for x in preference_stub],
                                        "symbols": [{"component": name, "names": image.symbols[preference_target]}
                                                    for name, image in images.items() if preference_target in image.symbols]}
    phone = Path("D:/carvex-research/android") if os.name == "nt" else Path("/mnt/d/carvex-research/android")
    package = phone / "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay"
    sources = []
    for relative in ("AirSession.kt", "core/Rtsp.kt", "core/CarPlaySourceIdentity.kt"):
        path = package / relative
        lines = path.read_text(encoding="utf-8").splitlines()
        terms = ("X-Apple-ProtocolVersion", 'c.request("SETUP"', 'c.request("GET","/info"',
                 'val h=linkedMapOf("CSeq"', "h.putAll(extra)", "sourceVersion=", "compatibilityOsBuildVersion=")
        selected = [{"line": i, "text": line.strip()} for i, line in enumerate(lines, 1)
                    if any(term in line for term in terms)]
        sources.append({"path": str(path), "sha256": digest(path), "bytes": path.stat().st_size,
                        "selected_lines": selected})
    result = {"build": "24A446", "scope": "X-Apple-ProtocolVersion producer and current Android header presence",
              "method": "read original cache and extracted image; no firmware execution or vehicle test",
              "images": [{"component": name, "path": str(image.path), "sha256": digest(image.path)}
                         for name, image in images.items()],
              "route": route, "provider_trampoline": stub, "provider": provider, "initializer": initializer,
              "strings": [{**region(a, len(value) + 1), "value": value}
                          for a, value in ((0x24fe6d592, "X-Apple-ProtocolVersion"), (0x24fe4db39, "%u"))],
              "android_sources": sources,
              "tools": [{"path": str(path), "sha256": digest(path)} for path in
                        (Path(__file__).resolve(), FW / "tools/ipsw-research/firmware_cache.py",
                         FW / "tools/ipsw-research/firmware_image.py")],
              "limits": ["Static header construction only; no claim that any particular vehicle rejects a missing header.",
                         "Do not equate RTSP version, X-Apple-ProtocolVersion, sourceVersion or osBuildVersion.",
                         "Source snapshot is not an APK/runtime identity; other files may change independently."]}
    for value in result["strings"]:
        assert bytes.fromhex(value["hex"]) == value["value"].encode() + b"\0"
    cache.close()
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
