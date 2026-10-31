"""Read-only selected Toyota ELF build-profile audit. Never writes inputs.

Run with python -B. --inspect prints bounded original disassembly for review;
the default prints a byte-provenance JSON report. No device/network execution.
"""
from pathlib import Path
import argparse
import hashlib
import json
import struct
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
PHONE = DOC.parents[1] / "iamr0s/carplay-xiaomi-carlife"
TOYOTA = FW / "headunits/toyota/extract/vendor/carplay/libs/libAirPlay.so"


class Elf64:
    def __init__(self, path):
        self.path = path
        self.data = path.read_bytes()
        assert self.data[:6] == b"\x7fELF\x02\x01", "expected little-endian ELF64"
        h = struct.unpack_from("<16sHHIQQQIHHHHHH", self.data)
        self.machine = h[2]
        self.segments = []
        for i in range(h[10]):
            p = struct.unpack_from("<IIQQQQQQ", self.data, h[5] + i * h[9])
            if p[0] == 1:
                self.segments.append((p[3], p[3] + p[5], p[2], p[1]))
        self.sections = []
        for i in range(h[12]):
            self.sections.append(struct.unpack_from("<IIQQQQIIQQ", self.data, h[6] + i * h[11]))
        names = self.sections[h[13]]
        table = self.data[names[4]:names[4] + names[5]]
        self.section_names = [table[s[0]:].split(b"\0", 1)[0].decode() for s in self.sections]
        self.symbols = {}
        self.symbol_tables = {}
        for sec in self.sections:
            if sec[1] not in (2, 11):
                continue
            strings = self.sections[sec[6]]
            st = self.data[strings[4]:strings[4] + strings[5]]
            entries = []
            for at in range(sec[4], sec[4] + sec[5], sec[9]):
                name, info, other, index, value, size = struct.unpack_from("<IBBHQQ", self.data, at)
                symname = st[name:].split(b"\0", 1)[0].decode() if name else ""
                entries.append((symname, value, size))
                if name and value:
                    self.symbols.setdefault(value & ~1, []).append(symname)
            self.symbol_tables[self.sections.index(sec)] = entries
        self.relocations = {}
        for sec in self.sections:
            if sec[1] == 4:
                for at in range(sec[4], sec[4] + sec[5], sec[9]):
                    offset, info, addend = struct.unpack_from("<QQq", self.data, at)
                    self.relocations[offset] = {"symbol": self.symbol_tables[sec[6]][info >> 32],
                                                 "type": info & 0xffffffff, "addend": addend}

    def read(self, address, length):
        for start, end, offset, flags in self.segments:
            if start <= address and address + length <= end:
                return self.data[offset + address - start:offset + address - start + length]
        raise ValueError(f"unmapped {address:#x}+{length}")

    def cstr(self, address):
        return self.read(address, 160).split(b"\0", 1)[0].decode()

    def va_for_offset(self, offset):
        for start, end, file_offset, flags in self.segments:
            if file_offset <= offset < file_offset + end - start:
                return start + offset - file_offset
        raise ValueError("unmapped file offset")


def disassemble(image, address, length):
    from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN
    md = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    md.skipdata = True
    return list(md.disasm(image.read(address, length), address))


def inspection(image, spec):
    address, length = [int(x, 0) for x in spec.split(":")]
    for ins in disassemble(image, address, length):
        print(f"{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}")


def plt_binding(image, address):
    ins = disassemble(image, address, 16)
    if len(ins) != 4 or ins[0].mnemonic != "adrp" or ins[1].mnemonic != "ldr":
        return None
    base = int(ins[0].op_str.split("#")[1], 0)
    offset = int(ins[1].op_str.split("#")[1].rstrip("]"), 0)
    return {"stub": hex(address), "got": hex(base + offset),
            "relocation": image.relocations.get(base + offset)}


def report(image):
    import re
    def sha(raw):
        return hashlib.sha256(raw).hexdigest()
    def file_record(path, lines=None):
        raw = path.read_bytes()
        result = {"path": str(path), "sha256": sha(raw), "bytes": len(raw)}
        if lines:
            text = raw.decode("utf-8-sig").splitlines()
            result["reviewed_lines"] = [{"first": a, "last": b,
                "text": "\n".join(text[a - 1:b])} for a, b in lines]
        return result
    ranges = [
        ("B01", 0x17d20, 0xc8, "CompareOSBuildVersionStrings: sscanf %d%c%d; first parse error=-1, second=+1, lexicographic numeric/upper-case letter/numeric subtraction"),
        ("B02", 0x18268, 0x50, "SETUP osBuildVersion string copy to session+0xa0; minimum provider call"),
        ("B03", 0x182b4, 0x68, "provider failure skips gate; successful minimum vs client comparison; positive result sets -0x1a3b"),
        ("B04", 0x17ec0, 0x98, "SETUP error path callback/teardown/local error return"),
        ("B05", 0xd01c, 0x98, "minimum build provider: config dictionary then synchronous property callback fallback"),
        ("B06", 0xc48c, 0x58, "server+0x88 config CString getter"),
        ("B07", 0x1af74, 0x24, "main/alt inbound modern flag=Compare(13A1,sessionBuild)<0"),
        ("B08", 0x252c0, 0x150, "APSRTPPacketHandlerDecryptCurrentMessage: legacy RTP pointer/12, modern pointer+4/8, add_aad call"),
        ("B09", 0x1b6b0, 0xc0, "microphone transmitter build threshold and modern AAD pointer+4/8"),
        ("B10", 0x1b7dc, 0xc, "microphone transmitter legacy AAD pointer/12"),
        ("B11", 0xdd4c, 0x98, "AirPlayCopyServerInfo display property; Compare(clientBuild,18A0)>=0 bypasses legacy transformation"),
        ("B12", 0xe2ec, 0x2a8, "copy display/viewAreas; only if safeArea missing create from width/height/originX/originY; install returned displays"),
        ("B13", 0x1715c, 0x28, "gen local consumer constant AAD length8 before helper1453c"),
        ("B14", 0x1724c, 0x28, "second gen local consumer constant AAD length8 before helper1453c"),
        ("B15", 0xebe8, 0x40, "info handler reads X-Apple-ProtocolVersion; no independent required-header gate established"),
    ]
    slices = []
    for ident, address, length, scope in ranges:
        raw = image.read(address, length)
        slices.append({"id": ident, "address": hex(address), "length": length,
                       "sha256": sha(raw), "raw_hex": raw.hex(), "reviewed_scope": scope})
    full_functions = []
    for wanted in ("CompareOSBuildVersionStrings", "AirPlayReceiverSessionSetup", "AirPlayCopyServerInfo", "AirPlayGetMinimumClientOSBuildVersion", "APSRTPPacketHandlerDecryptCurrentMessage"):
        entry = next(row for rows in image.symbol_tables.values() for row in rows if row[0] == wanted and row[1])
        name, address, length = entry
        full_functions.append({"name": name, "address": hex(address), "length": length,
            "sha256": sha(image.read(address, length)), "scope": "Full-function hash is provenance only; reviewed portions are listed in slices."})
    strings = []
    for address, expected in ((0x2af90, "%d%c%d"), (0x2b59d, "13A1"), (0x2888b, "18A0"),
        (0x295b5, "osBuildVersion"), (0x27ccc, "clientOSBuildVersionMin"), (0x27e16, "displays"),
        (0x27e27, "viewAreas"), (0x27e39, "safeArea"), (0x27e4a, "widthPixels"),
        (0x27e5e, "heightPixels"), (0x27e73, "originXPixels"), (0x27e89, "originYPixels"),
        (0x288d2, "X-Apple-ProtocolVersion")):
        value = image.cstr(address)
        assert value == expected, (hex(address), value, expected)
        strings.append({"address": hex(address), "value": value, "raw_hex": image.read(address, len(value) + 1).hex()})
    callsites = []
    for sec, name in zip(image.sections, image.section_names):
        if name == ".text":
            for ins in disassemble(image, sec[3], sec[5]):
                if ins.mnemonic in ("bl", "b") and ins.op_str in ("#0x17d20", "#0xa470"):
                    callsites.append(hex(ins.address))
    assert callsites == ["0xdd78", "0x182fc", "0x1af84", "0x1b6c8"], callsites
    main = PHONE / "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay"
    sources = [file_record(main / "core/CarPlaySourceIdentity.kt", [(4, 20)]),
        file_record(main / "core/MediaAudioPackets.kt", [(19, 26), (44, 68)]),
        file_record(main / "core/AudioRtpInput.kt", [(33, 44), (56, 74)]),
        file_record(main / "core/DisplayCapabilities.kt", [(24, 43)]),
        file_record(main / "AirSession.kt", [(493, 500), (509, 524), (561, 569)]),
        file_record(main / "CarPlayMediaAudio.kt", [(74, 80)]),
        file_record(main / "CarPlayMicReceiver.kt", [(27, 32)]),
        file_record(PHONE / "protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/core/CarPlaySourceIdentityTest.kt")]
    no_geometry = []
    for path in main.rglob("*.kt"):
        if re.search(r"\b(?:safeArea|viewAreas)\b", path.read_text(encoding="utf-8-sig")):
            no_geometry.append(str(path))
    sys.path.insert(0, str(FW / "tools/ipsw-research"))
    from firmware_image import Image
    from firmware_cache import Cache
    apple = Image(FW / "extracted/24A446/binaries/AirPlaySupport/AirPlaySupport")
    cache = Cache(FW / "extracted/24A446/dyld")
    try:
        address = 0x226e68af0
        raw_path = FW / "analysis/24A446/audio-receive-aad-history/f_226e68af0.bin"
        raw = raw_path.read_bytes()
        assert raw == apple.read(address, len(raw)) == cache.read(address, len(raw))
        apple_record = {"image": file_record(apple.path), "name": apple.symbols.get(address),
            "address": hex(address), "length": len(raw), "sha256": sha(raw),
            "matches_extracted_image_and_original_cache": True,
            "reviewed_scope": "APSTransportMessageGetAudioAADPointer success writes AAD length8; pointer-selector interpretation and all writer callers not re-audited in this task."}
    finally:
        cache.close()
    return {"schema_version": 1, "review_date": "2026-10-29", "runtime_observed": False,
        "vehicle_tested": False, "status": "PARTIAL_STATIC_AUDIT",
        "method": "Original ELF64 PT_LOAD reads; ARM64 Capstone disassembly; dynamic symbol and RELA PLT binding; exact iOS cached-slice/image/cache comparison. No original function execution, no unit-test rerun, no APK build.",
        "toyota_image": file_record(TOYOTA), "functions": full_functions, "slices": slices,
        "strings": strings, "plt_bindings": [plt_binding(image, a) for a in
            (0xa470, 0xa5f0, 0xa960, 0xab30, 0xa520, 0xaf20, 0xa5b0, 0xa660, 0xb300, 0xac50, 0xb010, 0xa630, 0xb860, 0xaf60, 0xbb50, 0xa780, 0xafe0, 0xb5d0)],
        "minimum_build_callback_got": {"address": "0x3efd8", "raw_hex": image.read(0x3efd8, 8).hex(),
            "relocation": image.relocations.get(0x3efd8), "limit": "Binding is evidence; complete callback behavior/default not audited."},
        "comparison_direct_calls": {"method": "All direct B/BL in ELF .text to implementation17d20 or its resolved PLT a470. Does not cover indirect calls or other comparison functions.", "callsites": callsites},
        "apple_aad_helper": apple_record, "android_current_sources": sources,
        "geometry_string_scan": {"scope": str(main), "extensions": [".kt"], "matches": no_geometry,
            "meaning": "No literal viewAreas/safeArea source references in this bounded module scan; not a proof about generic external components."},
        "current_conclusions": [
            "Current osBuildVersion=21A329; model/osName/osVersion remain Android. Initial SETUP and /setup retry reuse the same encoded body. sourceVersion/User-Agent remain320.17.",
            "Current main/alt output uses RTP[4,12) AAD for plain and RED packets. Compare(13A1,21A329)=-8 by the reviewed static formula, selecting the same modern Toyota receiver branch. The historical raw Android Build.ID mismatch is not present in these current source lines.",
            "For this Toyota image, an unparsable second build supplied to Compare(13A1,build) selects legacy full RTP[0,12); equality13A1 also selects legacy. Actual previous device Build.ID comes from historical reports, not a new device read.",
            "AirPlayReceiverSessionSetup: if minimum getter succeeds and Compare(minimum,current)>0, sets-6715, reports error, tears down and returns it. Getter failure branches past comparison. Minimum is config key clientOSBuildVersionMin, then synchronous property fallback; no concrete default/callback implementation or actual vehicle minimum is proven.",
            "AirPlayCopyServerInfo: only clientBuild<18A0 takes legacy displays/viewAreas transformation; absent safeArea is filled from that view area's width/height/originX/originY. Current21A329 skips transformation. Current DisplayCapabilities selects only type,widthPixels,heightPixels,maxFPS,uuid. This shows observable behavior coupling, not a reproduced current video failure.",
            "Current microphone input tries multiple authenticated layouts/AADs, including none, with chosen preferred but fallback still enabled every packet. It is local compatibility behavior, not proof of one fixed declared profile or iPhone equivalence. Failed authentication is not published.",
            "X-Apple-ProtocolVersion parsing exists in info handler eb24/ebf4-ec08; this audit does not establish a reject-on-missing/value gate.",
        ],
        "historical_context": {"source": file_record(PHONE / "docs/audio-build-aad-repair-2026-10-29.md"),
            "evidence_level": "HISTORICAL_REPORT_ONLY", "scope": "Reports prior CP2A Build.ID, prior original-comparison execution and model tests. Not rerun or used as current failure proof."},
        "limits": ["Local Toyota library not independently matched to user's vehicle firmware.",
            "No proof of universal receiver behavior, complete build/sourceVersion capability matrix, or all version consumers.",
            "No new playback/connection/video/vehicle test; historical user success remains separate evidence.",
            "21A329 above18A0/13A1 does not mean it implements every21A329 behavior; changing it to24A446 merely for appearance is unsupported.",
            "Full source/version declaration and crypto/security capability agreement require separate negotiated-state and lifetime audits."],
        "tools": [file_record(Path(__file__).resolve())]}


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--inspect", action="append", default=[])
    p.add_argument("--locate", action="store_true")
    p.add_argument("--string", action="append", default=[])
    p.add_argument("--plt", action="append", default=[])
    args = p.parse_args()
    image = Elf64(TOYOTA)
    if args.string or args.plt:
        for address in args.string:
            print(address, repr(image.cstr(int(address, 0))))
        for address in args.plt:
            print(plt_binding(image, int(address, 0)))
        return
    if args.inspect:
        for spec in args.inspect:
            inspection(image, spec)
        return
    if args.locate:
        print("sha256", hashlib.sha256(image.data).hexdigest(), "machine", image.machine)
        for literal in (b"13A1\0", b"18A0\0", b"safeArea\0", b"osBuildVersion\0", b"X-Apple-ProtocolVersion\0"):
            offsets = []
            at = 0
            while True:
                at = image.data.find(literal, at)
                if at < 0:
                    break
                offsets.append(hex(image.va_for_offset(at)))
                at += 1
            print(literal.decode().rstrip("\0"), offsets)
        for start, end, offset, flags in image.segments:
            if not flags & 1:
                continue
            for ins in disassemble(image, start, end - start):
                if ins.mnemonic in ("bl", "b") and ins.op_str in ("#0x17d20", "#0xa470"):
                    print("build_compare_direct_call", hex(ins.address))
                if ins.mnemonic == "add" and ins.op_str.endswith("#0x88b"):
                    print("candidate_18A0_reference", hex(ins.address))
        for address in (0xa470, 0xa5f0, 0xa960, 0xab30, 0xa520, 0xaf20, 0xa5b0, 0xa660):
            print("plt", plt_binding(image, address))
        for address, names in image.symbols.items():
            if any("Build" in name or "Version" in name or "Screen" in name or "Setup" in name or "CopyServerInfo" in name for name in names):
                print("symbol", hex(address), names)
        return
    print(json.dumps(report(image), ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
