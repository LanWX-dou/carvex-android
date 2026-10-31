"""Pair-Verify 密钥用途与流描述符的原切片/指令锚点；不执行握手。"""
from pathlib import Path
import json
import runpy

ROOT = Path(__file__).resolve().parents[1]


def check():
    load = runpy.run_path(str(ROOT / "tools/verify-type-dispatch.py"))["load_instructions"]
    insns = load("CoreUtils", 0x18BF29408)
    insns.update(load("AirPlaySender", 0x251AB1780))
    anchors = {
        0x18BF295A4: "add x24, x21, #0x1ee",
        0x18BF295B0: "bl #0x18be4667c",
        0x18BF295B4: "bl #0x1900cf870",
        0x18BF295B8: "str x24, [sp]",
        0x18BF295D0: "mov x2, x24",
        0x18BF295D4: "mov w3, #0x15",
        0x18BF295DC: "mov w7, #0x20",
        0x18BF295E0: "bl #0x1900cf190",
        0x18BF295E4: "add x0, x21, #0x1ce",
        0x18BF295EC: "bl #0x1900ec2b0",
        0x18BF29998: "add x1, x21, #0x1ee",
        0x18BF299A4: "bl #0x1900ec2a0",
        0x18BF299CC: "cbz w8, #0x18bf2a324",
        0x18BF299D0: "add x24, x21, #0x1ae",
        0x18BF299F0: "mov x2, x27",
        0x18BF299F4: "mov w3, #0x18",
        0x18BF29A00: "bl #0x1900cf190",
        0x18BF2A03C: "mov w2, #0xa",
        0x18BF2A040: "mov w3, #0x40",
        0x18BF2A08C: "ldp q0, q1, [x28]",
        0x18BF2A090: "stp q0, q1, [x24]",
        0x18BF2A098: "add x0, x24, #0x20",
        0x18BF2A09C: "bl #0x1900cc480",
        0x18BF2A0A4: "add x8, x8, #0x20",
        0x18BF2A0AC: "add x8, x21, #0x1ce",
        0x18BF2A0B4: "stp q1, q0, [x9]",
        0x18BF2A0D0: "bl #0x1900cf130",
        0x18BF29D70: "cbz x0, #0x18bf29db4",
        0x18BF29D78: "cbz x8, #0x18bf29db4",
        0x18BF29D90: "add x0, x21, #0x1ae",
        0x18BF29DAC: "bl #0x18be578a4",
        0x18BF29E20: "add x4, x21, #0x28e",
        0x18BF29F20: "add x2, x21, #0x28e",
        0x18BF29F30: "mov w7, #8",
        0x18BF29F3C: "str x5, [x21, #0x188]",
        0x18BF2A1EC: "cbnz w0, #0x18bf2a2cc",
        0x18BF2A1F4: "bl #0x18be483bc",
        0x251AB179C: "cbz w0, #0x251ab181c",
        0x251AB17E4: "bl #0x25810a790",
        0x251AB17E8: "cbz w22, #0x251ab1800",
        0x251AB17F8: "mov x2, x20",
        0x251AB17FC: "bl #0x25810a790",
    }
    for address, expected in anchors.items():
        assert insns.get(address) == expected, (hex(address), insns.get(address), expected)
    binary = (ROOT / "source/firmware/CoreUtils").read_bytes()
    segments = json.loads((ROOT / "source/metadata/CoreUtils/segments.json").read_text(encoding="utf-8"))
    strings = {
        0x18BF6BD6A: b"Pair-Verify-ECDH-Salt", 0x18BF6BD80: b"Pair-Verify-ECDH-Info",
        0x18BF6D511: b"Pair-Verify-Encrypt-Salt", 0x18BF6D52A: b"Pair-Verify-Encrypt-Info",
        0x18BF6DA92: b"Pair-Verify-ResumeSessionID-Salt",
        0x18BF6DAB3: b"Pair-Verify-ResumeSessionID-Info",
    }
    for address, expected in strings.items():
        segment = next(s for s in segments if 0 <= address - s["vmaddr"]
                       and address - s["vmaddr"] + len(expected) + 1 <= s["filesize"])
        offset = segment["fileoff"] + address - segment["vmaddr"]
        assert binary[offset:offset + len(expected) + 1] == expected + b"\0"
    print("Pair-Verify/descriptor: 2 raw slices + %d anchors + 6 label constants OK" % len(anchors))


if __name__ == "__main__":
    check()
