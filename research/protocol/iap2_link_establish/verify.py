#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Acceptance checks for research/protocol/iap2_link_establish.

Run:  cd research/protocol/iap2_link_establish && python3 verify.py

Checks (8 classes):
  C1  source binary identity (size + sha256 vs metadata/function-index)
  C2  every exported asm slice matches the original firmware bytes
  C3  every readable/*.ghidra.c exists, is marked unreviewed, and its metadata
      hash chain matches
  C4  every cited 0x1xxxxxxxxx address falls inside the image window, and every
      function address cited in analysis/13 exists in function-index.json
  C5  checksum test vectors recomputed from the firmware-derived algorithm
  C6  constants quoted in spec/ agree with the firmware bytes / decoded tables
  C7  manifest completeness (all files hashed, no extras), anchor integrity
      (A/R ids referenced by spec exist and are unique) and OPEN item registry
  C8  the shipped reference implementation (reference-impl/) reproduces the
      documented vectors and round-trips

Exit code 0 only when every check passes.
"""
import hashlib
import json
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
FAIL = []
PASS = [0]


def ok(msg):
    PASS[0] += 1


def bad(msg):
    FAIL.append(msg)


def read(rel):
    with open(os.path.join(ROOT, rel), encoding="utf-8") as f:
        return f.read()


def jload(rel):
    return json.loads(read(rel))


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


# ---------------------------------------------------------------- helpers

IMG_LO, IMG_HI = 0x100000000, 0x102180000
ADDR_RE = re.compile(r"0x1[0-9a-fA-F]{9,10}")


def load_firmware():
    return open(os.path.join(ROOT, "source/firmware/accessoryd"), "rb").read()


def fileoff(segs, va):
    for s in segs:
        if s["vmaddr"] <= va < s["vmaddr"] + s["vmsize"]:
            return s["fileoff"] + (va - s["vmaddr"])
    return None


def checksum(data, kind):
    if not data:
        return 0
    if kind == 8:
        return (-sum(data)) & 0xFF
    s1 = s2 = 0xFF
    i = 0
    while i < len(data):
        blk = data[i:i + 20]
        i += 20
        for b in blk:
            s1 += b
            s2 += s1
        s1 = (s1 & 0xFF) + ((s1 >> 8) & 0xFF)
        s2 = (s2 & 0xFF) + ((s2 >> 8) & 0xFF)
    s1 = (s1 & 0xFF) + (s1 >> 8)
    return (-(((s2 + (s2 << 8)) & 0x3FF00) | s1)) & 0xFFFF


# ---------------------------------------------------------------- C1

def check_source():
    meta = jload("source/metadata/summary.json")
    path = os.path.join(ROOT, "source/firmware/accessoryd")
    size = os.path.getsize(path)
    digest = sha256_file(path)
    if size != meta["size"]:
        bad("C1: accessoryd size %d != summary %d" % (size, meta["size"]))
    else:
        ok("C1: size")
    if digest != meta["sha256"]:
        bad("C1: accessoryd sha256 mismatch")
    else:
        ok("C1: sha256")
    fi = jload("function-index.json")
    if fi["source_sha256"] != digest:
        bad("C1: function-index source_sha256 mismatch")
    else:
        ok("C1: function-index hash")
    if fi["exported"] != len(fi["functions"]):
        bad("C1: exported counter inconsistent")
    else:
        ok("C1: exported counter")
    if fi["total_function_starts"] != meta["function_starts"]:
        bad("C1: function_starts mismatch")
    else:
        ok("C1: function starts")


# ---------------------------------------------------------------- C2

def check_asm():
    fw = load_firmware()
    segs = jload("source/metadata/segments.json")
    idx = jload("source/asm/accessoryd/index.json")
    asm_dir = os.path.join(ROOT, "source/asm/accessoryd")
    n = 0
    for f in idx["functions"]:
        a = int(f["address"], 16)
        e = int(f["end"], 16)
        blob = open(os.path.join(asm_dir, "f_%s.bin" % f["address"][2:]), "rb").read()
        want = fw[fileoff(segs, a):fileoff(segs, a) + (e - a)]
        if blob != want:
            bad("C2: %s .bin differs from firmware slice" % f["symbol"])
            continue
        if hashlib.sha256(blob).hexdigest() != f["raw_sha256"]:
            bad("C2: %s raw_sha256 mismatch" % f["symbol"])
            continue
        text = open(os.path.join(asm_dir, "f_%s.s" % f["address"][2:]), encoding="utf-8").read()
        if ("; accessoryd 0x%x-0x%x" % (a, e)) not in text:
            bad("C2: %s header range missing" % f["symbol"])
            continue
        if idx["source_sha256"] not in text:
            bad("C2: %s header source sha missing" % f["symbol"])
            continue
        if "Capstone" not in text:
            bad("C2: %s disassembler tag missing" % f["symbol"])
            continue
        n += 1
    if n == len(idx["functions"]):
        ok("C2: %d asm slices byte-identical" % n)
    want = {"index.json"}
    for f in idx["functions"]:
        want.add("f_%s.s" % f["address"][2:])
        want.add("f_%s.bin" % f["address"][2:])
    have = set(os.listdir(asm_dir))
    if have != want:
        bad("C2: source/asm registry mismatch, extra=%r missing=%r"
            % (sorted(have - want)[:5], sorted(want - have)[:5]))
    else:
        ok("C2: source/asm registry exact (%d files)" % len(have))


# ---------------------------------------------------------------- C3

def check_readable():
    fi = jload("function-index.json")
    n = 0
    for f in fi["functions"]:
        cpath = os.path.join(ROOT, f["ghidra_c"])
        mpath = cpath[:-len(".ghidra.c")] + ".json"
        if not os.path.exists(cpath):
            bad("C3: missing %s" % f["ghidra_c"])
            continue
        if not os.path.exists(mpath):
            bad("C3: missing metadata for %s" % f["symbol"])
            continue
        c = open(cpath, encoding="utf-8").read()
        m = json.loads(open(mpath, encoding="utf-8").read())
        if "RAW GHIDRA DECOMPILATION" not in c:
            bad("C3: %s lacks unreviewed banner" % f["symbol"])
            continue
        if f["address"] not in c or f["raw_sha256"] not in c:
            bad("C3: %s banner identity mismatch" % f["symbol"])
            continue
        if m.get("status") != "DECOMPILED_UNREVIEWED":
            bad("C3: %s status %r" % (f["symbol"], m.get("status")))
            continue
        if m.get("loaded_code_sha256") != f["raw_sha256"]:
            bad("C3: %s loader hash mismatch" % f["symbol"])
            continue
        n += 1
    if n == len(fi["functions"]):
        ok("C3: %d readable files verified" % n)


# ---------------------------------------------------------------- C4

def check_addresses():
    fi = jload("function-index.json")
    known = {f["address"] for f in fi["functions"]}
    outside = []
    for sub in ("analysis", "spec"):
        d = os.path.join(ROOT, sub)
        for name in sorted(os.listdir(d)):
            if not name.endswith(".md"):
                continue
            text = read(sub + "/" + name)
            for m in ADDR_RE.finditer(text):
                v = int(m.group(0), 16)
                if not (IMG_LO <= v < IMG_HI):
                    outside.append((sub + "/" + name, m.group(0)))
    if outside:
        bad("C4: %d addresses outside image window, e.g. %r" % (len(outside), outside[:3]))
    else:
        ok("C4: all cited addresses inside image window")

    inv = read("analysis/13-function-inventory.md")
    cited = ADDR_RE.findall(inv)
    missing = [a for a in cited if a not in known]
    if missing:
        bad("C4: analysis/13 cites addresses not in function-index: %r" % missing[:5])
    else:
        ok("C4: analysis/13 addresses all exported")


# ---------------------------------------------------------------- C5

def check_checksum_vectors():
    spec = read("spec/02-framing-and-checksum.md")
    vectors = [
        (bytes.fromhex("0200EE"), 8, 0x10),
        (bytes.fromhex("04000204EE"), 8, 0x08),
        (bytes.fromhex("0200FE"), 8, 0x00),
        (bytes.fromhex("FF5A000980000000"), 16, 0x581D),
        (bytes.fromhex("FF5A0009C0000000"), 16, 0x57DC),
        (b"", 16, 0x0000),
    ]
    for data, kind, want in vectors:
        got = checksum(data, kind)
        if got != want:
            bad("C5: vector %s type %d -> 0x%x != 0x%x" % (data.hex(), kind, got, want))
        else:
            ok("C5: vector %s" % (data.hex() or "empty"))
        label = "0x%04X" % want if kind == 16 else "0x%02X" % want
        if label not in spec and ("`" + label + "`") not in spec:
            bad("C5: spec/02 does not state %s for %s" % (label, data.hex()))

    # firmware constant must be the Detect frame
    fw = load_firmware()
    segs = jload("source/metadata/segments.json")
    off = fileoff(segs, 0x1001b3378)
    if fw[off:off + 6] != bytes.fromhex("FF550200EE10"):
        bad("C5: Detect template at 0x1001b3378 differs")
    else:
        ok("C5: Detect template constant")
    spec8 = read("spec/08-conformance-checklist.md")
    for lit in ("FF 55 02 00 EE 10", "FF 55 04 00 02 04 EE 08", "FF 55 02 00 FE 00"):
        if lit not in spec8:
            bad("C5: spec/08 missing frame literal %s" % lit)
    ok("C5: spec/08 frame literals")
    payload = bytes.fromhex("0200EE")
    if checksum(payload, 8) != fw[off + 5]:
        bad("C5: Detect checksum byte disagrees with algorithm")
    else:
        ok("C5: Detect checksum recomputed")


# ---------------------------------------------------------------- C6

def check_constants():
    fw = load_firmware()
    segs = jload("source/metadata/segments.json")
    tables = jload("source/metadata/tables.json")

    # SYN defaults: 4 bytes at 0x1001b3348
    off = fileoff(segs, 0x1001b3348)
    if fw[off:off + 4] != bytes.fromhex("01011E00"):
        bad("C6: SYN default constant differs")
    else:
        ok("C6: SYN defaults 01 01 1e 00")
    spec3 = read("spec/03-syn-negotiation.md")
    for token in ("MaxOutstandingPackets", "MaxRetransmissions", "MaxCumAck", "1000", "0xFFFF"):
        if token not in spec3:
            bad("C6: spec/03 lacks %s" % token)
    ok("C6: spec/03 field names present")

    # control values from constructors: check spec/02 table
    spec2 = read("spec/02-framing-and-checksum.md")
    for val, name in ((0x80, "SYN"), (0x40, "ACK"), (0x20, "EAK"), (0x10, "RST"), (0x08, "SUS")):
        if "`0x%02X`" % val not in spec2:
            bad("C6: spec/02 missing control value 0x%02x (%s)" % (val, name))
    ok("C6: spec/02 control values")

    # FSM: 8 states, event limit 29
    if len(tables["link_device_fsm"]["states"]) != 8:
        bad("C6: state count != 8")
    else:
        ok("C6: 8 states")
    spec5 = read("spec/05-state-machine.md")
    if "**8**" not in spec5 or "29" not in spec5:
        bad("C6: spec/05 does not state 8 states / 29 events")
    else:
        ok("C6: spec/05 counts")
    # every effective transition in tables.json must appear as a row in spec/05
    eff = {}
    for st in tables["link_device_fsm"]["states"]:
        for ev in st["events"]:
            if ev["handler"] == "0x100000000":
                continue
            eff.setdefault(ev["event"], set()).add(st["index"])
    for e in sorted(eff):
        row = re.search(r"^\| `0x%02x` \|" % e, spec5, re.M)
        if not row:
            bad("C6: spec/05 missing event 0x%02x" % e)
    ok("C6: spec/05 lists all effective events")

    # message tables quoted in spec/06 must match tables.json
    spec6 = read("spec/06-identification-auth-session.md")
    want = {
        "Identification": [0x1D01, 0x1D06, 0x1D05],
        "DeviceAuthentication": [0xAA10, 0xAA12, 0xAA14, 0xAA15],
        "AccAuthentication": [0xAA01, 0xAA03, 0xAA06],
        "CarPlayStartSession": [0x4301],
        "ExternalAccessory": [0xEA03],
    }
    for name, ids in want.items():
        entries = tables["message_handler_tables"]["kiAP2MessageHandlerEntries_" + name]["entries"]
        got = [x["msg_id"] for x in entries]
        if got != ids:
            bad("C6: %s ids %r != %r" % (name, got, ids))
            continue
        for i in ids:
            if "`0x%04X`" % i not in spec6:
                bad("C6: spec/06 missing msg id 0x%04x" % i)
    ok("C6: spec/06 message ids match tables.json")

    # every rule carries a normative verb
    for n in sorted(os.listdir(os.path.join(ROOT, "spec"))):
        if not n.endswith(".md"):
            continue
        for m in re.finditer(r"^`(R-[\d.]+)`（([^）]*)）", read("spec/" + n), re.M):
            if not re.match(r"(MUST|SHOULD|未定义) / (CONFIRMED|INFERRED|OPEN)$", m.group(2)):
                bad("C6: spec/%s %s lacks normative verb (%r)" % (n, m.group(1), m.group(2)))
    ok("C6: normative verbs")

    # coverage registry
    cov = json.loads(read("source/metadata/coverage.json"))["items"]
    if len(cov) != 12 or [i["no"] for i in cov] != list(range(1, 13)):
        bad("C6: coverage.json must have 12 numbered items")
    else:
        ok("C6: coverage 12 items")
    allowed = {"已确认", "部分确认", "OPEN"}
    for i in cov:
        if i["status"] not in allowed:
            bad("C6: coverage item %d bad status %r" % (i["no"], i["status"]))
    ok("C6: coverage statuses")
    corpus = "".join(read("analysis/" + n) for n in os.listdir(os.path.join(ROOT, "analysis")) if n.endswith(".md"))
    corpus += "".join(read("spec/" + n) for n in os.listdir(os.path.join(ROOT, "spec")) if n.endswith(".md"))
    for i in cov:
        for o in i["open"]:
            if o not in corpus:
                bad("C6: coverage cites unknown open item %s" % o)
    ok("C6: coverage open ids resolve")

    # window default 1 / max recv 0xffff from the -0xff00 constant
    if not read("spec/04-seq-ack-retransmit.md").count("link[0x1a5]"):
        bad("C6: spec/04 does not mention window field")
    else:
        ok("C6: spec/04 window field")


# ---------------------------------------------------------------- C7

def check_manifest_and_anchors():
    man = jload("manifest.json")
    listed = {f["path"]: f for f in man["files"]}
    on_disk = set()
    for base, dirs, names in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith(".")]
        for n in names:
            rel = os.path.relpath(os.path.join(base, n), ROOT).replace("\\", "/")
            if rel == "manifest.json":
                continue
            on_disk.add(rel)
    missing = sorted(set(listed) - on_disk)
    extra = sorted(on_disk - set(listed))
    if missing:
        bad("C7: manifest lists %d absent files, e.g. %r" % (len(missing), missing[:3]))
    else:
        ok("C7: no absent entries")
    if extra:
        bad("C7: %d files not in manifest, e.g. %r" % (len(extra), extra[:3]))
    else:
        ok("C7: no unlisted files")
    for rel, item in listed.items():
        if os.path.exists(os.path.join(ROOT, rel)) and sha256_file(os.path.join(ROOT, rel)) != item["sha256"]:
            bad("C7: sha256 drift for %s" % rel)
            break
    else:
        ok("C7: manifest hashes")
    if man["source"]["sha256"] != sha256_file(os.path.join(ROOT, "source/firmware/accessoryd")):
        bad("C7: manifest source hash")
    else:
        ok("C7: manifest source hash")

    # anchors: every Axx.y referenced in spec/ must exist in analysis/
    analysis_text = "\n".join(read("analysis/" + n) for n in sorted(os.listdir(os.path.join(ROOT, "analysis"))) if n.endswith(".md"))
    defined = set(re.findall(r"`(A\d\d\.\d+[a-z]?)`", analysis_text))
    refs = set()
    for n in sorted(os.listdir(os.path.join(ROOT, "spec"))):
        if n.endswith(".md"):
            refs |= set(re.findall(r"`(A\d\d\.\d+[a-z]?)`", read("spec/" + n)))
    unknown = sorted(refs - defined)
    if unknown:
        bad("C7: spec cites undefined analysis anchors: %r" % unknown[:6])
    else:
        ok("C7: %d analysis anchors resolve" % len(refs))

    # rule ids unique per file
    for n in sorted(os.listdir(os.path.join(ROOT, "spec"))):
        if not n.endswith(".md"):
            continue
        text = read("spec/" + n)
        ids = re.findall(r"^`(R-[\d.]+)`", text, re.M)
        dup = {x for x in ids if ids.count(x) > 1}
        if dup:
            bad("C7: duplicate rule ids in spec/%s: %r" % (n, sorted(dup)))
    ok("C7: rule ids unique")

    # OPEN registry: STATUS must mention every open id from manifest
    status = read("STATUS.md")
    miss = [k for k in man["open_items"] if k not in status]
    if miss:
        bad("C7: STATUS.md misses %d open items, e.g. %r" % (len(miss), miss[:5]))
    else:
        ok("C7: STATUS lists %d open items" % len(man["open_items"]))
    if man["open_item_count"] != len(man["open_items"]):
        bad("C7: open_item_count mismatch")
    else:
        ok("C7: open item count")


def check_reference_impl():
    impl = os.path.join(ROOT, "reference-impl", "test_vectors.py")
    if not os.path.exists(impl):
        bad("C8: reference-impl/test_vectors.py missing")
        return
    proc = subprocess.run([sys.executable, "test_vectors.py"], cwd=os.path.dirname(impl),
                          capture_output=True, text=True)
    tail = (proc.stdout or "").strip().splitlines()[-1:] or [""]
    if proc.returncode != 0:
        bad("C8: reference implementation failed: %s" % tail[0][:160])
    else:
        ok("C8: reference impl %s" % tail[0][:80])


def main():
    for fn in (check_source, check_asm, check_readable, check_addresses,
               check_checksum_vectors, check_constants, check_manifest_and_anchors,
               check_reference_impl):
        try:
            fn()
        except Exception as exc:  # a crashed check is a failed check
            bad("%s raised %s: %s" % (fn.__name__, type(exc).__name__, exc))
    print("checks passed: %d" % PASS[0])
    if FAIL:
        print("FAILED: %d" % len(FAIL))
        for f in FAIL:
            print("  -", f)
        return 1
    print("ALL CHECKS PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
