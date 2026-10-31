"""Read-only provenance checks for the bounded 24A446 runtime-control audit.

No networking/emulation or writes to firmware/cache. --write only updates this
docset's evidence. Byte equality does not prove semantics or interoperability.
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
AS = CACHE / "AirPlaySender/934ec850a9ab7623f1d8/functions"
AP = CACHE / "APTransport/dcc06dc3316817912f6d/functions"
KA = FW / "analysis/24A446/keepalive-transaction"
ROWS = [
    ("RC01", "AirPlaySender", AS / "f_251babc44", 0x251babc44, "ordinary iAP command passes inSendAsync=0; alternate RCS path retained"),
    ("RC02", "AirPlaySender", AS / "f_251ae8e90", 0x251ae8e90, "command dictionary creation and dispatch block captures"),
    ("RC03", "AirPlaySender", AS / "f_251baaa94", 0x251baaa94, "TransportControlStream; async=false calls type vtable+0x38 with reply output=NULL"),
    ("RC04", "AirPlaySender", AS / "f_251af5a74", 0x251af5a74, "outlined helper sets stream, comm, request buffer arguments"),
    ("RC05", "APTransport", KA / "APTransport-24fda3f70", 0x24fda3f70, "ordinary keep calls type vtable+0x38 with reply output; lkee remains distinct"),
    ("RC06", "APTransport", KA / "APTransport-24fda45bc", 0x24fda45bc, "pending keepalive skips another send; stall notification is not request timeout"),
    ("RC07", "APTransport", AP / "f_24fe001e8", 0x24fe001e8, "resumed standard keepalive publishes Failed status"),
    ("RC08", "APTransport", AP / "f_24fda68f8", 0x24fda68f8, "SendMessageCreatingReply waits even without output pointer; timeout schedules invalidation"),
]


def report():
    images = {name: Image(FW / f"extracted/24A446/binaries/{name}/{name}")
              for name in ("AirPlaySender", "APTransport")}
    functions = []
    for key, name, stem, address, scope in ROWS:
        raw = stem.with_suffix(".bin").read_bytes()
        if not raw or images[name].read(address, len(raw)) != raw:
            raise ValueError(f"cache mismatch: {key}")
        functions.append(dict(id=key, image=name, address=hex(address), size=len(raw),
                              sha256=hashlib.sha256(raw).hexdigest(),
                              path=str(stem.with_suffix(".bin")), reviewed_scope=scope))

    # These extracted cache images retain shared-cache rebases: low32 is an
    # offset from 0x180000000, NOT from an individual Mach-O's __TEXT base.
    # Validate every selected target against its expected VA and mapped bytes;
    # do not use this bounded decoder for arbitrary binds or other firmware.
    def rebase(image, slot, expected):
        raw = image.u64(slot)
        if raw & (1 << 62):
            raise ValueError(f"unexpected bind at {slot:#x}")
        target = 0x180000000 + (raw & 0xffffffff)
        if target != expected:
            raise ValueError(f"unexpected target at {slot:#x}: {target:#x}")
        image.read(target, 1)
        return dict(slot=hex(slot), raw=hex(raw), target=hex(target))

    ap, sender = images["APTransport"], images["AirPlaySender"]
    pointers = [rebase(ap, 0x275fa2cc0, 0x275fa2d28),
                rebase(ap, 0x275fa2d60, 0x24fda68f8),
                rebase(sender, 0x2693e7aa8, 0x276136990),
                rebase(sender, 0x2761369a0, 0x251c1d7c6)]
    if sender.cstr(0x251c1d7c6) != "TransportControlStream":
        raise ValueError("control stream property mismatch")
    if sender.cstr(0x180000000 + (sender.u64(0x27613a780) & 0xffffffff)) != "iAPSendMessage":
        raise ValueError("iAP command constant mismatch")
    instructions = [
        ("AirPlaySender", 0x251babdc4, "03008052", "inSendAsync=0"),
        ("AirPlaySender", 0x251babdcc, "31f4fc97", "call sendCommandInternal"),
        ("AirPlaySender", 0x251baacfc, "098d43f8", "load type vtable+0x38"),
        ("AirPlaySender", 0x251baad98, "030080d2", "reply-output pointer NULL, not async send"),
        ("APTransport", 0x24fda40d4, "098e43f8", "normal keepalive type vtable+0x38"),
        ("APTransport", 0x24fda410c, "a3e300d1", "normal keepalive reply output pointer"),
    ]
    for name, address, data, _ in instructions:
        if images[name].read(address, 4).hex() != data:
            raise ValueError(f"instruction mismatch at {address:#x}")
    return dict(baseline="iPhone18,1 / 24A446", status="PARTIAL",
                execution="static byte/provenance checks only, not firmware execution",
                source_sha256={n:hashlib.sha256(im.data).hexdigest() for n,im in images.items()},
                functions=functions, pointers=pointers,
                instructions=[dict(image=n,address=hex(a),bytes=b,scope=s) for n,a,b,s in instructions],
                open_items=["why the observed receiver stops replying after 0x5001",
                            "all RCS and lower HTTP engine branches",
                            "actual vehicle recovery and interoperability"])


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()
    result = report()
    if args.write:
        (DOC / "evidence/runtime-control-evidence.json").write_text(
            json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(functions=len(result["functions"]), pointers=len(result["pointers"]),
                         instructions=len(result["instructions"]), status="OK")))
