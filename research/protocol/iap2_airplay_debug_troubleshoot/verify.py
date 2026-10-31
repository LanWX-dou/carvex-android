#!/usr/bin/env python3
"""Offline evidence/fixture checks. PASS is not field validation; SKIPs remain explicit."""
from pathlib import Path
import importlib.util
import json
import re
import shutil
import struct
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parent
DOCS = ROOT.parent
FAILS = []
SKIPS = []


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


def check(name, fn):
    try:
        fn()
    except Exception as exc:
        FAILS.append(name)
        print(f"FAIL {name}: {type(exc).__name__}")
    else:
        print(f"PASS {name}")


def run_script(path, *args):
    out = subprocess.run([sys.executable, "-B", str(path), *args], capture_output=True,
                         text=True, encoding="utf-8", errors="replace", timeout=60)
    if out.returncode:
        # These are maintained fixture scripts; they never consume real credentials.
        print(out.stdout, out.stderr)
        raise AssertionError("dependent verification failed")
    print(out.stdout.strip())


def main():
    inv = load("debug_manifest", ROOT / "tools/manifest.py")

    def hashes():
        manifest = json.loads((ROOT / "manifest.json").read_text(encoding="utf-8"))
        actual = {p.relative_to(ROOT).as_posix(): inv.sha(p) for p in inv.authored_files()}
        assert manifest["files"] == actual
        assert set(manifest["dependencies"]) == set(inv.DEPENDENCIES)
        for name, expected in manifest["dependencies"].items():
            assert inv.sha(DOCS / name) == expected, name
    check("C1 inventory and dependency hashes", hashes)

    def coverage():
        data = json.loads((ROOT / "coverage.json").read_text(encoding="utf-8"))
        assert [i["id"] for i in data["items"]] == list(range(1, 13))
        opens = set(re.findall(r"OPEN-DBG-\d+", (ROOT / "spec/07-open-items.md").read_text(encoding="utf-8")))
        assert len(opens) == 7
        book = (ROOT / "spec/05-casebook.md").read_text(encoding="utf-8")
        for item in data["items"]:
            assert item["paths"] and item["open"]
            for path in item["paths"]:
                assert (ROOT / path).is_file()
            assert set(item["open"]) <= opens
            assert all(case in book for case in item.get("cases", []))
        fixtures = load("debug_repro", ROOT / "reference-impl/reproduce.py")
        assert set(fixtures.CASES) == {f"D{i:02}" for i in range(1, 11)}
    check("C2 twelve content requirements and seven OPENs", coverage)

    def links():
        for path in ROOT.rglob("*.md"):
            for target in re.findall(r"\]\(([^)]+)\)", path.read_text(encoding="utf-8")):
                if target.startswith(("https://", "http://", "#")):
                    continue
                assert (path.parent / target.split("#")[0]).exists(), (path.name, target)
    check("C3 authored local Markdown links", links)
    check("C4 ten synthetic fault fixtures", lambda: run_script(ROOT / "reference-impl/reproduce.py", "--case", "ALL"))

    def anchors():
        sender = (DOCS / "airplay_video_channel/source/asm/AirPlaySender/f_2519b508c.s").read_text(encoding="utf-8")
        derive = (DOCS / "airplay_control_plane/source/asm/CoreUtils/f_18be5021c.s").read_text(encoding="utf-8")
        assert re.search(r"0x2519b52c4:\s+mov\s+w22, #-0x4178", sender)
        assert re.search(r"0x18be50244:\s+mov\s+w0, #-0x1a4f", derive)
        assert re.search(r"0x18be50324:\s+mov\s+w0, #-0x1a35", derive)
        assert -0x4178 == -16760 and (-0x4178 & 0xffffffff) == 0xffffbe88
        assert -0x1a4f == -6735 and (-0x1a4f & 0xffffffff) == 0xffffe5b1
        assert -0x1a35 == -6709 and (-0x1a35 & 0xffffffff) == 0xffffe5cb
        # Original-image and whole-slice checks live with the owning audited docsets.
        run_script(DOCS / "airplay_video_channel/tools/verify-wrapper.py")
        run_script(DOCS / "airplay_control_plane/tools/verify-keyholder.py")
    check("C5 local return anchors plus original-image audits (Capstone required)", anchors)

    diag = load("debug_diag", ROOT / "reference-impl/diagnostic.py")

    def extra_boundaries():
        assert diag.inspect_rtsp_response(b"", 1)["result"] == "NEED_MORE"
        assert diag.inspect_rtsp_response(b"x" * 65537, 1)["result"] == "LOCAL_LIMIT"
        for header, result in ((b"CSeq: x", "BAD_CSEQ"), (b"cSeQ: 1", "MATCHED_RESPONSE"),
                               (b"CSeq: 1\r\nContent-Length: 1048577", "LOCAL_LIMIT"),
                               (b"CSeq: 1\r\nContent-Length: 0\r\nContent-Length: 0", "AMBIGUOUS_HEADER")):
            raw = b"RTSP/1.0 200 OK\r\n" + header + b"\r\n\r\n"
            assert diag.inspect_rtsp_response(raw, 1)["result"] == result
        unknown = diag.inspect_rtsp_response(b"RTSP/1.0 777 X\r\nCSeq: 1\r\n\r\n", 1)
        assert unknown["status"] == 777  # don't invent extension semantics
    check("C6 parser diagnostic limits and ambiguous headers", extra_boundaries)

    # Empty synthetic Ethernet pcap is only for offline grammar compilation, not field validation.
    selected = diag.filters("192.0.2.10", [7123, 49152], [51000, 51001])
    with tempfile.TemporaryDirectory(prefix="carplay-debug-filter-") as temp:
        fixture = Path(temp) / "empty-synthetic.pcap"
        fixture.write_bytes(struct.pack("<IHHIIII", 0xa1b2c3d4, 2, 4, 0, 0, 65535, 1))
        tshark = shutil.which("tshark")
        if tshark:
            def display_compile():
                for expr in (selected["display"], "udp.port == 5353", "ip or ipv6 or arp",
                             "btrfcomm", "rtsp", "tcp.flags.reset == 1", "tcp.analysis.retransmission"):
                    out = subprocess.run([tshark, "-r", str(fixture), "-Y", expr], capture_output=True, timeout=30)
                    assert out.returncode == 0
            check("C7 display-filter offline compilation", display_compile)
        else:
            SKIPS.append("C7 display-filter compilation: tshark unavailable")
        tcpdump = shutil.which("tcpdump")
        if tcpdump:
            def bpf_compile():
                for expr in (selected["capture"], "udp port 5353", "ip or ip6 or arp"):
                    out = subprocess.run([tcpdump, "-r", str(fixture), "-ddd", expr], capture_output=True, timeout=30)
                    assert out.returncode == 0
            check("C8 BPF offline Ethernet compilation", bpf_compile)
        else:
            SKIPS.append("C8 BPF compilation: tcpdump unavailable (target interface validation remains OPEN)")
    SKIPS.append("C9 real-car failures/filters/frame selection/interoperability: no samples")
    for reason in SKIPS:
        print("SKIP " + reason)
    print(f"{len(FAILS)} failures; {len(SKIPS)} skips; NO field-validation claim")
    return int(bool(FAILS))


if __name__ == "__main__":
    raise SystemExit(main())
