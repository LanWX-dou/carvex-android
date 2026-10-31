"""Read-only ACK-only/normal-disconnect audit; --write only saves docset evidence.

Extracts allowlisted log metadata, checks original firmware slices against existing
caches, and fingerprints current phone sources. Does not execute firmware or a
phone, validate HCI/peer state, or modify the phone/headunit/firmware repositories.
"""
import argparse
import bisect
from datetime import datetime
import hashlib
import json
from pathlib import Path
import re
import sys

sys.dont_write_bytecode = True
from inspect_iap2_handoff import Image, Cache, MD, imports, local_selector, SOURCES

DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
PHONE = Path("/mnt/d/carvex-research/android")
LOG = Path("/mnt/c/Users/iamr0s/.codex/attachments/51bc0fbc-6bd2-4cb5-aa32-c58a1b765715/已粘贴的文本.txt")
EXPECTED_LOG = "a2dcb2a14a1dfaa1e1a4876bdbe26f078fa806cf1545382f61a84ae17fa50999"
ACK_ONLY = ["070da178", "85d42998", "fdc1adb3", "cad30f56", "201ee382", "bbde96dd", "23273c32"]
SELECTED = ["a23f8475", "262ad5f0", *ACK_ONLY, "d5db4abf", "8ad4898d", "7f019410", "273a5a62"]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def function(im, address, cache=None):
    assert address in im.starts
    end = im.starts[bisect.bisect_right(im.starts, address)]
    raw = im.read(address, end-address)
    cached = list((FW / "analysis/decompiler-cache/24A446" / im.path.name).glob(f"*/functions/f_{address:x}.bin"))
    for path in cached:
        assert path.read_bytes() == raw, path
    if cache is not None:
        assert cache.read(address, len(raw)) == raw
    imported = imports(im)
    selectors, calls, assembly = [], [], []
    for ins in MD.disasm(raw, address):
        assembly.append(f"{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}")
        if ins.mnemonic in ("b", "bl") and ins.op_str.startswith("#0x"):
            target = int(ins.op_str[1:], 0)
            if target in imported:
                calls.append(dict(site=hex(ins.address), target=hex(target), **imported[target]))
            if cache is None:
                try:
                    decoded = local_selector(im, target)
                    if decoded:
                        selectors.append(dict(site=hex(ins.address), **decoded))
                except (ValueError, UnicodeError):
                    pass
    return dict(address=hex(address), end=hex(end), sha256=sha(raw),
                cached_bytes_matched=len(cached), original_dyld_matched=cache is not None,
                imports=calls, selectors=selectors, assembly=assembly)


def logs():
    raw = LOG.read_bytes()
    assert sha(raw) == EXPECTED_LOG
    attempts = {key: [] for key in SELECTED}
    for no, line in enumerate(raw.decode("utf-8-sig").splitlines(), 1):
        match = re.match(r"(\S+) \[([0-9a-f]{8})\] (.*)", line)
        if not match or match[2] not in attempts:
            continue
        attempts[match[2]].append((no, match[1], match[3]))
    output = []
    for key, entries in attempts.items():
        row = dict(attempt=key, startup=[], bluetooth_api_close_completed=[])
        auth_started = False
        detect_at = None
        for no, time, msg in entries:
            if msg == "stage AUTH":
                auth_started = True
            if msg.startswith("Resource close type=BluetoothSocket elapsedMs=") and "elapsedMs=null" not in msg:
                row["bluetooth_api_close_completed"].append(dict(line=no, time=time))
            if auth_started:
                continue
            event = None
            if msg.startswith("RFCOMM selected initiator="):
                event = dict(type="selected", direction=msg.split("=")[1].split(";")[0])
            elif "first-byte deadline" in msg:
                event = dict(type="idle_detection_tx")
                detect_at = datetime.fromisoformat(time.replace("Z", "+00:00"))
            elif msg.startswith("iAP detection RX="):
                event = dict(type="detection_rx")
            elif msg.startswith("iAP synchronized "):
                event = dict(type="synchronized")
            elif msg.startswith("iAP NO_SYN:"):
                event = dict(type="no_syn")
            else:
                match = re.fullmatch(r"iAP frame (RX|TX) ([a-f0-9]+)/([0-9]+)/([0-9]+)/([0-9]+)/([0-9]+)(?: csm=[a-f0-9]+)?", msg)
                if match:
                    event = dict(type="frame", direction=match[1], flags=int(match[2],16),
                                 seq=int(match[3]), ack=int(match[4]), session=int(match[5]), length=int(match[6]))
                    if match[1] == "RX" and detect_at is not None:
                        at = datetime.fromisoformat(time.replace("Z", "+00:00"))
                        event["ms_since_idle_detection"] = round((at-detect_at).total_seconds()*1000,3)
            if event:
                row["startup"].append(dict(line=no, time=time, **event))
        if key in ACK_ONLY:
            frames = [x for x in row["startup"] if x["type"] == "frame"]
            assert len(frames) == 1
            assert [frames[0][k] for k in ("direction","flags","seq","ack","session","length")] == ["RX",64,1,16,0,0]
            assert any(x["type"] == "no_syn" for x in row["startup"])
        output.append(row)
    # Only pre-PAIR frames are unambiguously in the source Bluetooth bootstrap.
    source_frames = []
    for no, time, msg in attempts["262ad5f0"]:
        if msg == "stage PAIR":
            break
        if msg.startswith("iAP frame "):
            source_frames.append(dict(line=no,time=time,metadata=msg))
    assert source_frames[-1]["metadata"] == "iAP frame TX 40/235/1/0/0"
    teardown = []
    for no, time, msg in attempts["a23f8475"]:
        if "Control exchange" in msg and "method=TEARDOWN " in msg:
            # Do not export URL/IP/session token or body; allowlist transaction fields.
            fields = dict(re.findall(r"\b(phase|cseq|bodyBytes|elapsedMs|status|error)=([^ ]+)",msg))
            teardown.append(dict(line=no,time=time,**fields))
    return dict(sha256=EXPECTED_LOG, attempts=output, ack_only_count=len(ACK_ONLY),
                prior_source_last_frames=source_frames[-3:], manual_disconnect_teardown=teardown,
                transport_attribution_limit="After AirPlay starts, current iAP frame logs share attempt ID and no link ID; do not attribute all of them to RFCOMM.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()
    bt = Image(SOURCES["bluetoothd"])
    assert sha(bt.data) == "cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1"
    bt_functions = [function(bt, at) for at in (0x1007a3680,0x1007a4240,0x1007a4520,
                    0x1007a4e4c,0x1007a4fa8,0x1007a511c,0x1007a5200,0x10062cd3c,0x10062d114)]
    ap = Image(FW / "extracted/24A446/binaries/AirPlaySender/AirPlaySender")
    assert sha(ap.data) == "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f"
    cache = Cache(FW / "extracted/24A446/dyld")
    try:
        ap_functions = [function(ap, at, cache) for at in (0x2519ce5c4,0x251b5e7c4)]
    finally:
        cache.close()
    phone_paths = [
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapFrameReader.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt",
        "protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/AirPlaySetupSession.kt",
        "core/src/main/java/io/github/iamr0s/carvex/sessioncore/State.kt",
        "bridge/src/main/java/io/github/iamr0s/carvex/session/SessionController.kt",
        "host-carlife-mixing/src/main/java/com/baidu/carlife/service/CarlifeConnectService.kt",
        "app/src/main/kotlin/io/github/iamr0s/carvex/ui/model/DeviceViewModel.kt",
    ]
    report = dict(build="24A446", tool_sha256=sha(Path(__file__).read_bytes()),
                  log=logs(), firmware=[dict(component="bluetoothd",sha256=sha(bt.data),functions=bt_functions),
                                       dict(component="AirPlaySender",sha256=sha(ap.data),functions=ap_functions)],
                  phone=[dict(path=p,sha256=sha((PHONE/p).read_bytes())) for p in phone_paths],
                  limits=__doc__, firmware_executed=False, vehicle_tested=False,
                  ack_only_root_cause_proven=False, manual_stop_causes_ack_only_proven=False)
    if args.write:
        (DOC / "evidence/reconnect-lifecycle-audit.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(dict(result="PASS",firmware_functions=11,phone_sources=len(phone_paths),
                         ack_only=report["log"]["ack_only_count"],
                         teardown=report["log"]["manual_disconnect_teardown"],
                         bt_selectors=[dict(address=f["address"],selectors=[s["selector"] for s in f["selectors"]]) for f in bt_functions],
                         limit="Integrity and log metadata only; no root-cause/vehicle proof")))


if __name__ == "__main__":
    main()
