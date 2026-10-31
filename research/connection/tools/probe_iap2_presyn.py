"""Read-only 24A446 pre-SYN ACK oracle; stdout only, no cache/evidence writes.

Executes original Attach, Ready/Ordered packet processing, device FSM, Detect,
ResetSeqAck, RST construction and wire generator. Reuses the frozen runner's
explicit queue/allocation/timer/transport/callback substitutes. This is NOT a
vehicle test or execution of the full bluetoothd/endpoint initialization path.
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


def attach(profile_version=3, populated_peer=False, endpoint_profile=False):
    n.prepare(1, rx=0, tx=0, window=1, peer_window=4 if populated_peer else 0)
    n.put(n.F + 10, 1, "<B")
    n.put(n.D + 0xd4, 0, "<B")  # no established receive/send sequence flags
    n.put(n.D + 0x4000, profile_version, "<B")
    if endpoint_profile:
        # Execute the ORIGINAL endpoint profile construction, not inferred wire
        # defaults. The endpoint is zero-initialized; its profile begins at +0x30.
        n.u.mem_write(n.D + 0x4000, bytes(50))
        n.u.reg_write(UC_ARM64_REG_X19, n.D + 0x4000 - 0x30)
        n.u.emu_start(0x100129454, 0x1001294a4, count=1000)
    # LinkCreate 0x1000341a4..1c0 copies this complete 50-byte profile to work.
    n.u.mem_write(n.D + 0x168, bytes(n.u.mem_read(n.D + 0x4000, 50)))
    n.call(0x100034a7c, [n.D])
    assert n.byte(n.F + 10) == 2


def detect():
    packet = n.packet(0x40, 0, 0, 0)
    n.put(packet + 0x3d, 19, "<H")  # native parser's complete Detection status
    n.call(0x10000ada0, [n.D, packet])
    assert n.byte(n.F + 10) == 3


def summary():
    s = n.state()
    return {key: s[key] for key in ["state", "last_rx", "received_ack", "last_tx", "sent_ack", "packet_version"]} | {
        "events": s["trace"]["events"], "sent": s["trace"]["sent"],
        "delivered": s["trace"]["delivered"], "callbacks": s["callbacks"],
    }


cases = []
for version in [1, 2, 3]:
    for detected in [False, True]:
        attach(version)
        if detected:
            detect()
        before = summary()
        n.receive(seq=99, ack=16, payload=b"", flags=0x40, session=0)
        after = summary()
        assert after["state"] == (3 if detected else 2)
        assert after["sent"][len(before["sent"]):] == [], (version, detected, before, after)
        assert not after["delivered"]
        assert not any(c["connected"] for c in after["callbacks"])
        # Repeated ACK is not a SYN and cannot publish Connected.
        n.receive(seq=99, ack=16, payload=b"", flags=0x40, session=0)
        repeated = summary()
        assert repeated["state"] == after["state"]
        assert repeated["sent"][len(after["sent"]):] == []
        cases.append(dict(profile_version=version, detected=detected, before=before,
                          after=after, repeated=repeated))

for detected in [False, True]:
    attach(endpoint_profile=True)
    profile = bytes(n.u.mem_read(n.D + 0x4000, 50)).hex()
    if detected:
        detect()
    before = summary()
    n.receive(seq=99, ack=16, payload=b"", flags=0x40, session=0)
    after = summary()
    assert after["events"][-1] == 22
    assert after["state"] == before["state"]
    assert after["sent"] == before["sent"]
    cases.append(dict(kind="original_endpoint_profile", profile=profile, detected=detected,
                      before=before, after=after))

# Counterexample: populated working parameters can classify ACK as event21.
# This is not the pre-SYN endpoint profile above; do not erase that condition.
for detected in [False, True]:
    attach(populated_peer=True)
    if detected:
        detect()
    before = summary()
    n.receive(seq=99, ack=16, payload=b"", flags=0x40, session=0)
    after = summary()
    assert after["events"][-1] == 21
    assert after["sent"][len(before["sent"]):] == (["ff5a0009100000008e"] if detected else [])
    cases.append(dict(kind="populated_work_counterexample", detected=detected, before=before, after=after))

for flags, payload in [(0x10, b""), (0x40, b"\x40\x40\x00\x06\x57\x03")]:
    for detected in [False, True]:
        attach()
        if detected:
            detect()
        before = summary()
        n.receive(seq=99, ack=16, payload=payload, flags=flags, session=0 if not payload else 10)
        after = summary()
        assert after["state"] == (3 if detected or payload else 2)
        assert after["sent"][len(before["sent"]):] == (["ff5a0009100000008e"] if payload else [])
        assert not after["delivered"]
        cases.append(dict(flags=flags, payload_bytes=len(payload), detected=detected, before=before, after=after))

for detected in [False, True]:
    attach(endpoint_profile=True)
    if detected:
        detect()
    n.receive(seq=99, ack=16, payload=b"", flags=0x40, session=0)
    before = summary()
    # Valid peer SYN following the orphan ACK must still negotiate afresh.
    body = bytes([1, 2, 2, 0, 0, 100, 0, 10, 2, 0, 2, 0, 2])
    n.receive(seq=41, ack=0, payload=body, flags=0x80, session=0)
    proposed = summary()
    assert proposed["state"] == 4
    assert not any(c["connected"] for c in proposed["callbacks"])
    n.receive(seq=41, ack=proposed["last_tx"], payload=b"", flags=0x40, session=0)
    after = summary()
    assert after["state"] == 5
    assert after["callbacks"][-1]["connected"] == 1
    cases.append(dict(kind="ack_then_real_handshake", detected=detected, before=before,
                      proposed=proposed, after=after))

print(json.dumps(dict(build="24A446", source_sha256=source_sha, case_count=len(cases), cases=cases,
    runner_sha256=hashlib.sha256(runner.read_bytes()).hexdigest(),
    scope="Native instructions with explicit initialization, original endpoint-profile slice and synthetic counterexamples; validated packet metadata; substituted queues/allocation/timers/transport/callbacks. No full endpoint initialization, Bluetooth, timer-origin or real-car claim."), indent=2))
