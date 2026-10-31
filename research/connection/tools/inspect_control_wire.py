"""Recheck selected 24A446 control-wire function bytes against Mach-O inputs.

Read-only by default; --write writes only this docset's evidence JSON.
No emulation, networking, credentials, or reference-file modifications.
The result proves byte provenance, not protocol semantics or interoperability.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
sys.path.insert(0, str(FW / "tools/ipsw-research"))
from firmware_image import Image

CACHE = FW / "analysis/decompiler-cache/24A446"
AP = CACHE / "APTransport/dcc06dc3316817912f6d/functions"
CU = CACHE / "CoreUtils/8792f09ecc40428a5f65/functions"
ANA = FW / "analysis/24A446"

# Only the reviewed scopes below are semantic claims. Whole-function hashes
# identify bytes but do not certify every instruction or inferred C type.
ROWS = [
    ("CW01", "APTransport", AP, 0x24fda5468, "CSeq old-value argument, URL/context, state=5 send gate"),
    ("CW02", "APTransport", AP, 0x24fda58ec, "Selected method/path/MIME mapping, RTSP/1.0, conditional body"),
    ("CW03", "APTransport", AP, 0x24fdaf86c, "Non-null plist format=200; optional reply must decode to dictionary"),
    ("CW04", "APTransport", AP, 0x24fda4b28, "Original request context; status 100..599 dispatch, not success"),
    ("CW05", "APTransport", AP, 0x24fda6e0c, "Header status 200..299 maps to zero, otherwise status+200000"),
    ("CW06", "APTransport", AP, 0x24fda68f8, "Reply wait seconds to nanoseconds, zero infinite, timeout invalidates"),
    ("CW07", "APTransport", ANA / "control-reply-contract", 0x24fda444c, "One pending waiter, timeout loaded from stream+0xb0"),
    ("CW08", "APTransport", ANA / "control-reply-contract", 0x24fda3ed0, "Completion status/body publication and waiter release"),
    ("CW09", "APTransport", AP, 0x24fda2b9c, "rply branch compares package token before recording status/body"),
    ("CW10", "CoreUtils", CU, 0x18be4da90, "SetBody explicit byte length and optional MIME; sticky allocation error"),
    ("CW11", "CoreUtils", ANA / "http-request-association", 0x18be4f198, "Header commit and header/body iovecs before enqueue"),
    ("CW12", "CoreUtils", ANA / "control-header-finalization", 0x18be4d478, "Text header CRLF and local NUL; one-shot commit marker"),
    ("CW13", "CoreUtils", ANA / "control-header-framing", 0x18be49f60, "8192-byte header scanner, blank line, preserved over-read"),
    ("CW14", "CoreUtils", ANA / "control-header-framing", 0x18be49060, "Selected fixed-body length completion and chunked branch existence"),
    ("CW15", "APTransport", AP, 0x24fda1e78, "Response package constructor preserves HTTPMessage reply-token storage"),
    ("CW16", "APTransport", AP, 0x24fda256c, "Reply-token setter splits high/low32 into HTTPMessage+0x25d0/+0x25d8"),
    ("CW17", "APTransport", ANA / "http-request-association", 0x24fda16a4, "Reply-token getter recombines stored halves"),
]


def sha(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def report() -> dict:
    images = {name: Image(FW / f"extracted/24A446/binaries/{name}/{name}")
              for name in ("APTransport", "CoreUtils")}
    functions = []
    for key, name, folder, address, scope in ROWS:
        raw_path = folder / f"f_{address:x}.bin"
        raw = raw_path.read_bytes()
        image = images[name]
        if not raw or raw != image.read(address, len(raw)):
            raise ValueError(f"source mismatch: {key} {raw_path}")
        segments = [(a, off, seg) for a, end, off, seg in image.segments
                    if a <= address and address + len(raw) <= end]
        if len(segments) != 1:
            raise ValueError(f"ambiguous file mapping: {key}")
        start, offset, segment = segments[0]
        files = [folder / f"f_{address:x}{suffix}"
                 for suffix in (".bin", ".s", ".ghidra.c")]
        functions.append({
            "id": key, "component": name, "address": hex(address),
            "raw_length": len(raw), "raw_sha256": hashlib.sha256(raw).hexdigest(),
            "source_file_offset": offset + address - start, "segment": segment,
            "raw_matches_source": True, "reviewed_scope": scope,
            "symbols": image.symbols.get(address, []),
            "files": [{"path": str(p), "sha256": sha(p)} for p in files if p.exists()],
        })
    strings = []
    for name, address, expected in [
        ("APTransport", 0x24fe4db34, "CSeq"),
        ("APTransport", 0x24fe4db39, "%u"),
        ("CoreUtils", 0x18bf69ce1, "Content-Length"),
        ("CoreUtils", 0x18bf69b12, "%zu"),
        ("CoreUtils", 0x18bf69b05, "Content-Type"),
        ("CoreUtils", 0x18bf69cf0, "Transfer-Encoding"),
        ("CoreUtils", 0x18bf69d02, "chunked"),
    ]:
        value = images[name].cstr(address)
        if value != expected:
            raise ValueError(f"unexpected string {name} {address:#x}: {value!r}")
        strings.append({"component": name, "address": hex(address), "value": value})
    return {
        "schema_version": 1, "build": "24A446", "runtime_observed": False,
        "method": "Mach-O LC_SEGMENT_64 VA mapping, exact byte comparison; bounded source review, no original-function execution",
        "images": [{"component": name, "path": str(img.path), "sha256": sha(img.path)}
                   for name, img in images.items()],
        "functions": functions, "strings": strings,
        "android_sources": [{
            "path": str(p), "sha256": sha(p), "bytes": p.stat().st_size,
            "evidence_level": "ANDROID_NOW_STATIC_SOURCE_ONLY",
        } for p in [
            DOC.parents[1] / "iamr0s/carplay-xiaomi-carlife/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/Rtsp.kt",
            DOC.parents[1] / "iamr0s/carplay-xiaomi-carlife/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt",
        ]],
        "tools": [{"path": str(p), "sha256": sha(p)} for p in
                  (Path(__file__).resolve(), FW / "tools/ipsw-research/firmware_image.py")],
        "limits": [
            "Does not establish the initial CSeq value or all reconnect/allocation paths.",
            "Per-message object context and local token checks do not prove all lower HTTP CSeq filters or late-reply safety.",
            "Header scanner size is not a global response-body maximum.",
            "Generic chunked reader presence is not proof of CarPlay runtime use or all framing-conflict handling.",
            "No claim about vehicle acceptance, display, cryptographic validity or end-to-end reconnection.",
        ],
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true", help="write evidence/control-wire-evidence.json in this docset")
    args = parser.parse_args()
    result = report()
    if args.write:
        destination = DOC / "evidence/control-wire-evidence.json"
        destination.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"functions_verified": len(result["functions"]),
                      "strings_verified": len(result["strings"]), "written": args.write,
                      "runtime_observed": False}))


if __name__ == "__main__":
    main()
