"""原切片/有限分支检查；外部池函数作为不透明调用，不模拟其副作用。"""
from pathlib import Path
import hashlib
import json
import re

import capstone

ROOT = Path(__file__).resolve().parents[1]


def check():
    asm_dir = ROOT / "source/asm/AirPlaySender"
    index = json.loads((asm_dir / "index.json").read_text(encoding="utf-8"))
    binary = (ROOT / "source/firmware/AirPlaySender").read_bytes()
    segments = json.loads((ROOT / "source/metadata/AirPlaySender/segments.json").read_text(encoding="utf-8"))
    all_insns = {}
    for address in (0x2519C19B4, 0x2519C18F0, 0x251BD0250, 0x2519C0C90):
        item = next(e for e in index["functions"] if int(e["address"], 16) == address)
        size = int(item["end"], 16) - address
        segment = next(s for s in segments if 0 <= address - s["vmaddr"]
                       and address - s["vmaddr"] + size <= s["filesize"])
        offset = segment["fileoff"] + address - segment["vmaddr"]
        raw = binary[offset:offset + size]
        assert raw == (asm_dir / item["bin"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == item["raw_sha256"]
        decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
                   for i in capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM).disasm(raw, address)}
        recorded = {}
        for line in (asm_dir / item["asm"]).read_text(encoding="utf-8").splitlines():
            match = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
            if match:
                recorded[int(match[1], 16)] = " ".join(match[2].split())
        assert decoded == recorded
        all_insns.update(decoded)
    anchors = {
        0x2519C1918: "mov x23, x4", 0x2519C191C: "mov x25, x3",
        0x2519C1924: "mov x24, x1", 0x2519C1934: "cbnz x23, #0x2519c1994",
        0x2519C193C: "mul w23, w8, w20", 0x2519C1944: "b.lo #0x2519c199c",
        0x2519C1964: "cbnz w0, #0x2519c19a8", 0x2519C1968: "str x23, [x21]",
        0x2519C1A00: "fcvtzu d0, d0", 0x2519C1A04: "str s0, [x1, #4]",
        0x2519C1A08: "mov w8, w20", 0x2519C1A20: "str xzr, [x19, #0x68]",
        0x2519C1A2C: "bl #0x25810da90", 0x2519C1A30: "mov w0, #0",
        0x2519C1A50: "mov w0, #-0x4199", 0x2519C1A5C: "mov w0, #-0x4198",
        0x251BD0298: "b.ne #0x251bd02dc", 0x251BD02C0: "cbnz x8, #0x251bd02dc",
        0x251BD02D8: "bl #0x251b3cfac", 0x251BD02DC: "ldr x0, [x19, #0x78]",
        0x2519C0DF8: "cbz w8, #0x2519c0eb0", 0x2519C0E48: "cmp w9, #0x1e",
        0x2519C0E4C: "b.gt #0x2519c0eb0", 0x2519C0E54: "b.eq #0x2519c0e9c",
        0x2519C0EB0: "mov x0, x20",
    }
    for address, expected in anchors.items():
        assert all_insns.get(address) == expected, (hex(address), all_insns.get(address))
    # 有限解释Commit在“持有且指针匹配”门之后的显式路径。
    for length, flag, expected_clear, expected_call, expected_status in (
        (0, False, False, 0x25810DA90, 0),
        (1, True, True, 0x25810DAA0, 0),
        (1460, True, True, 0x25810DAA0, 0),
        (1, False, False, 0x251BCC3FC, -0x4198),
    ):
        pc, cleared, calls, status = 0x2519C19F0, False, [], None
        for _ in range(32):
            instruction = all_insns[pc]
            op, _, args = instruction.partition(" ")
            following = pc + 4
            if op == "retab":
                break
            if op == "cbz":
                assert args.startswith("x20,")
                if length == 0:
                    following = int(args.split("#")[1], 16)
            elif op == "tbz":
                assert args.startswith("w8, #0,")
                if not flag:
                    following = int(args.rsplit("#", 1)[1], 16)
            elif op == "b":
                following = int(args[1:], 16)
            elif op == "bl":
                calls.append(int(args[1:], 16))  # 不执行外部调用。
            elif instruction == "str xzr, [x19, #0x68]":
                cleared = True
            elif instruction.startswith("mov w0, #"):
                status = int(args.split("#")[1], 0)
            pc = following
        else:
            raise AssertionError("Commit path did not return")
        assert (cleared, calls, status) == (expected_clear, [expected_call], expected_status)
    # 独立边界反例：原生W乘法会回绕，故不能视为完整容量检查。
    for per_frame, frames, expected in ((4, 3, 12), (0x40000000, 4, 0), (0xFFFFFFFF, 2, 0xFFFFFFFE)):
        assert (per_frame * frames) & 0xFFFFFFFF == expected
    assert (int(4294967297.75) & 0xFFFFFFFF) == 1  # 有限正数域的u64后低32位。
    return "4 raw slices, 25 anchors, 4 Commit paths and width counterexamples OK"


if __name__ == "__main__":
    print(check())
