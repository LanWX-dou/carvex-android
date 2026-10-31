"""Read-only 24A446 device-side LinkDetached/LinkAttached instruction probe.

Uses the existing frozen runner's explicit allocator/queue/timer/transport and
callback substitutes. Does not execute Android/iOS Bluetooth or kill a process.
Only stdout is written; source images and existing evidence remain untouched.
"""
from pathlib import Path
import hashlib
import json
import runpy
import sys

from unicorn.arm64_const import UC_ARM64_REG_X19

sys.dont_write_bytecode = True
FW = Path(__file__).resolve().parents[2] / "firmware"
runner = FW / "tools/ipsw-research/native-supervisor24.py"
sys.path.insert(0, str(runner.parent))
h = runpy.run_path(str(runner))
n = h["Native"]()
source_sha = h["sha"](n.im.path)
assert source_sha == "2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe"


def fresh():
    n.prepare(1, rx=0, tx=0, window=1, peer_window=0)
    n.put(n.F + 10, 1, "<B")
    n.put(n.D + 0xd4, 0, "<B")
    # Original endpoint profile construction; zero allocation and LinkCreate's
    # fifty-byte copy are explicit setup, not emulated endpoint/OS lifecycles.
    n.u.mem_write(n.D + 0x4000, bytes(50))
    n.u.reg_write(UC_ARM64_REG_X19, n.D + 0x4000 - 0x30)
    n.u.emu_start(0x100129454, 0x1001294a4, count=1000)
    n.u.mem_write(n.D + 0x168, bytes(n.u.mem_read(n.D + 0x4000, 50)))
    n.call(0x100034a7c, [n.D])
    assert n.byte(n.F + 10) == 2


def detect():
    packet = n.packet(0x40, 0, 0, 0)
    n.put(packet + 0x3d, 19, "<H")
    n.call(0x10000ada0, [n.D, packet])
    assert n.byte(n.F + 10) == 3


def propose():
    body = bytes([1, 2, 2, 0, 0, 100, 0, 10, 2, 0, 2, 0, 2])
    n.receive(seq=41, ack=0, payload=body, flags=0x80, session=0)
    assert n.byte(n.F + 10) == 4


def snapshot():
    s = n.state()
    return {key: s[key] for key in [
        "state", "last_rx", "received_ack", "last_tx", "sent_ack",
        "packet_version", "active", "pending", "send_queue", "receive_queue",
    ]} | {"sent": s["trace"]["sent"], "events": s["trace"]["events"],
          "callbacks": s["callbacks"], "delivered": s["trace"]["delivered"]}


cases = []
for initial_state in [2, 3, 4, 5]:
    fresh()
    if initial_state >= 3:
        detect()
    if initial_state >= 4:
        propose()
    if initial_state == 5:
        n.receive(seq=41, ack=n.state()["last_tx"], payload=b"", flags=0x40, session=0)
    assert n.byte(n.F + 10) == initial_state
    before = snapshot()
    n.call(0x100034bbc, [n.D])
    detached = snapshot()
    assert detached["state"] == 1
    assert detached["callbacks"][-1]["connected"] == 0
    assert detached["sent"] == before["sent"], "Detach must not be described as an on-wire RST"
    n.call(0x100034a7c, [n.D])
    attached = snapshot()
    assert attached["state"] == 2
    assert attached["sent"] == detached["sent"], "Attach does not unconditionally send SYN"
    assert attached["callbacks"] == detached["callbacks"]
    cases.append(dict(kind="same_link_detach_attach", initial_state=initial_state,
                      before=before, detached=detached, attached=attached))

# A new endpoint after a terminated process is NOT a reattached link with its
# old working parameters. Reproduce both orphan ACK values seen in the logs.
for seq in [1, 99]:
    for detected in [False, True]:
        fresh()
        if detected:
            detect()
        before = snapshot()
        n.receive(seq=seq, ack=16, payload=b"", flags=0x40, session=0)
        after = snapshot()
        assert after["state"] == before["state"]
        assert after["sent"] == before["sent"]
        assert not after["delivered"]
        assert after["callbacks"] == before["callbacks"]
        assert not any(c["connected"] for c in after["callbacks"])
        propose()
        n.receive(seq=41, ack=n.state()["last_tx"], payload=b"", flags=0x40, session=0)
        recovered = snapshot()
        assert recovered["state"] == 5 and recovered["callbacks"][-1]["connected"] == 1
        cases.append(dict(kind="fresh_ack_then_syn", seq=seq, detected=detected,
                          before=before, after_ack=after, recovered=recovered))

print(json.dumps(dict(build="24A446", source_sha256=source_sha,
    runner_sha256=hashlib.sha256(runner.read_bytes()).hexdigest(),
    case_count=len(cases), cases=cases,
    limits="Original bounded link/FSM instructions with synthetic validated packet metadata and explicit platform substitutes. No Bluetooth disconnect callback chain, OS process-death policy, real-car recovery or universal timeout claim."), indent=2))
