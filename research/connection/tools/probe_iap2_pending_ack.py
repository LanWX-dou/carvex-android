"""24A446 pending bad-ACK recovery probe; no firmware/cache modifications.

Runs original bounded device FSM/actions with the existing native runner's
explicit queue, allocator, timer, tick, transport and callback substitutes.
Packets have synthetic validated metadata. Not a Bluetooth/vehicle test.
--write writes only this docset's evidence report; default is read-only.
"""
from pathlib import Path
import argparse
import bisect
import hashlib
import json
import runpy
import sys

from unicorn.arm64_const import UC_ARM64_REG_X19

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / "firmware"
runner = FW / "tools/ipsw-research/native-supervisor24.py"
sys.path.insert(0, str(runner.parent))
h = runpy.run_path(str(runner))
n = h["Native"]()
source_sha = h["sha"](n.im.path)
assert source_sha == "2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe"


def fresh(initial):
    n.prepare(1, rx=0, tx=0, window=1, peer_window=0)
    n.put(n.F + 10, 1, "<B")
    n.put(n.D + 0xd4, 0, "<B")
    n.u.mem_write(n.D + 0x4000, bytes(50))
    n.u.reg_write(UC_ARM64_REG_X19, n.D + 0x4000 - 0x30)
    n.u.emu_start(0x100129454, 0x1001294a4, count=1000)
    n.u.mem_write(n.D + 0x168, bytes(n.u.mem_read(n.D + 0x4000, 50)))
    n.call(0x100034a7c, [n.D])
    packet = n.packet(0x40, 0, 0, 0)
    n.put(packet + 0x3d, 19, "<H")
    n.call(0x10000ada0, [n.D, packet])
    assert n.byte(n.F + 10) == 3
    # Tick is an explicit platform substitute. Execute the native initial-PSN
    # provider/SendSYNACK with a reproducible PSN, including exact log PSN27.
    n.now = (initial - 1) & 255


def body(version=1, zero=False):
    # Exact logged peer v1 parameters; v2/v3 and zero mode are counterexamples.
    fixed = bytes([version, 5]) + bytes.fromhex("0800")
    fixed += bytes(6) if zero else bytes.fromhex("05dc00491e03")
    return fixed + (b"" if version == 1 else b"\0\1") + bytes.fromhex("0a0002")


def state():
    s = n.state()
    return {k: s[k] for k in ("state", "last_rx", "last_tx", "received_ack", "sent_ack", "packet_version", "active", "pending", "send_queue", "receive_queue", "callbacks")} | {
        "sent": s["trace"]["sent"], "events": s["trace"]["events"],
        "proposals": int.from_bytes(n.u.mem_read(n.D + 0x1d0, 4), "little"),
        "retransmissions": int.from_bytes(n.u.mem_read(n.D + 0x1d8, 4), "little"),
    }


cases = []
for version in (1, 2, 3):
    for initial in (0, 1, 27, 254, 255):
        for gap in (0, 1, 2, 11, 255):
            fresh(initial)
            n.receive(seq=105, ack=0, payload=body(version), flags=0x80, session=0)
            before = state()
            assert before["state"] == 4 and before["last_tx"] == initial
            assert bytes.fromhex(before["active"])[11] == 1
            ack = (initial - gap) & 255
            n.receive(seq=105, ack=ack, payload=b"", flags=0x40, session=0)
            after = state()
            if gap > 1:
                assert after["state"] == 3
                assert after["events"][len(before["events"]):] == [19]
                assert after["sent"][len(before["sent"]):] == ["ff5a0009100000008e"]
                assert after["callbacks"] == before["callbacks"]
                assert after["send_queue"] == after["receive_queue"] == []
                assert all(after[k] == 0 for k in ("last_rx", "last_tx", "received_ack", "sent_ack"))
                assert after["proposals"] == before["proposals"]
                assert after["retransmissions"] == before["retransmissions"]
                # Late ACK cannot confirm the abandoned proposal after reset.
                n.receive(seq=105, ack=initial, payload=b"", flags=0x40, session=0)
                assert state()["state"] == 3
                n.receive(seq=106, ack=0, payload=body(version), flags=0x80, session=0)
                replacement = state()
                assert replacement["state"] == 4
                n.receive(seq=106, ack=replacement["last_tx"], payload=b"", flags=0x40, session=0)
                assert state()["state"] == 5 and state()["callbacks"][-1]["connected"] == 1
            else:
                assert after["state"] == 5 and after["callbacks"][-1]["connected"] == 1
            cases.append(dict(version=version, initial=initial, ack=ack, gap=gap,
                              before=before, after=after, final=state()))

for version in (1, 2, 3):
    fresh(27)
    n.receive(seq=105, ack=0, payload=body(version, zero=True), flags=0x80, session=0)
    before = state()
    n.receive(seq=105, ack=16, payload=b"", flags=0x40, session=0)
    after = state()
    assert after["state"] == 3
    assert after["sent"][len(before["sent"]):] == ["ff5a0009100000008e"]
    cases.append(dict(kind="zero-retransmission-offer-active-defaults", version=version, before=before, after=after))

functions = []
for address in (0x1000084b8, 0x10000ada0, 0x10000639c, 0x10002fb54, 0x1000346c8, 0x1000328b0, 0x10002fcd4):
    end = n.im.starts[bisect.bisect_right(n.im.starts, address)]
    functions.append(dict(address=hex(address), end=hex(end), symbols=n.im.symbols.get(address, []),
                          sha256=hashlib.sha256(n.im.read(address, end-address)).hexdigest()))
report = dict(build="24A446", source_sha256=source_sha, runner_sha256=hashlib.sha256(runner.read_bytes()).hexdigest(),
              functions=functions, case_count=len(cases), cases=cases,
              scope=__doc__,
              local_boundary="Android repair only generation0, pure ACK session0 empty payload with current peer PSN, unsigned gap>1. Native gap1 acceptance recorded but NOT enabled in this batch; post-connect resync and other packet forms not generalized.")
parser = argparse.ArgumentParser()
parser.add_argument("--write", action="store_true")
args = parser.parse_args()
if args.write:
    (DOC / "evidence/iap2-pending-ack-recovery.json").write_text(json.dumps(report, indent=2)+"\n", encoding="utf-8")
print(json.dumps(dict(result="PASS", cases=len(cases), source_sha256=source_sha,
                      exact_log_vector="SYNACK27 -> ACK16 -> RST -> fresh SYN -> connected",
                      limits="bounded original instructions with platform substitutes; not vehicle test")))
