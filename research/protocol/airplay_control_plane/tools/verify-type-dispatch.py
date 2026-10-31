"""有限解释实际 ARM64 类型分派；不是完整函数模拟或车机能力测试。"""
from pathlib import Path
import hashlib
import json
import re

import capstone

ROOT = Path(__file__).resolve().parents[1]
ASM = ROOT / "source/asm/AirPlaySender"
START = 0x2519BBF24
STOPS = {
    0x2519BCB40, 0x2519BCBEC, 0x2519BCEF8, 0x2519BCCE0,
    0x2519BCFB4, 0x2519BCD80, 0x2519BD120, 0x2519BD054,
}


def load_instructions(image="AirPlaySender", start=START, directory="asm"):
    asm_dir = ROOT / "source" / directory / image
    index = json.loads((asm_dir / "index.json").read_text(encoding="utf-8"))
    entry = next(e for e in index["functions"] if int(e["address"], 16) == start)
    binary = (ROOT / "source/firmware" / image).read_bytes()
    assert hashlib.sha256(binary).hexdigest() == index["source_sha256"]
    segments = json.loads((ROOT / "source/metadata" / image / "segments.json").read_text(encoding="utf-8"))
    segment = next(s for s in segments if 0 <= start - s["vmaddr"]
                   and start - s["vmaddr"] + entry["size"] <= s["filesize"])
    offset = segment["fileoff"] + start - segment["vmaddr"]
    raw = binary[offset:offset + entry["size"]]
    assert raw == (asm_dir / entry["bin"]).read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry["raw_sha256"]
    decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
               for i in capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM).disasm(raw, start)}
    recorded = {}
    for line in (asm_dir / entry["asm"]).read_text(encoding="utf-8").splitlines():
        match = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
        if match:
            recorded[int(match[1], 16)] = " ".join(match[2].split())
    assert decoded == recorded
    return decoded


def signed32(value):
    return value - (1 << 32) if value & (1 << 31) else value


def dispatch(insns, value):
    # 从实际分派入口开始；上游对象/密钥门控不在本解释器范围。
    registers = {"w23": value & 0xFFFFFFFF}
    pc = 0x2519BCAD4
    compared = None
    for _ in range(40):
        if pc in STOPS:
            return pc
        instruction = insns[pc]
        op, operands = instruction.split(" ", 1)
        args = operands.split(", ")
        following = pc + 4
        if op == "cmp":
            compared = (registers[args[0]], int(args[1][1:], 0))
        elif op == "sub":
            registers[args[0]] = (registers[args[1]] - int(args[2][1:], 0)) & 0xFFFFFFFF
        elif op == "b":
            following = int(operands[1:], 0)
        elif op in ("b.le", "b.gt", "b.lo", "b.hs", "b.eq", "b.ne"):
            assert compared is not None
            left, right = compared
            taken = {
                "b.le": signed32(left) <= signed32(right),
                "b.gt": signed32(left) > signed32(right),
                "b.lo": left < right, "b.hs": left >= right,
                "b.eq": left == right, "b.ne": left != right,
            }[op]
            if taken:
                following = int(operands[1:], 0)
        else:
            raise AssertionError((hex(pc), instruction))
        pc = following
    raise AssertionError("unexpected dispatch loop")


def check():
    insns = load_instructions()
    expected = {
        96: 0x2519BCBEC, 100: 0x2519BCEF8, 101: 0x2519BCB40,
        102: 0x2519BCBEC, 103: 0x2519BCBEC, 106: 0x2519BCFB4,
        107: 0x2519BCCE0, 110: 0x2519BCD80, 111: 0x2519BCD80,
        120: 0x2519BD120, 130: 0x2519BD120,
    }
    cases = list(range(256)) + [-1, -(1 << 31), (1 << 31) - 1, 0xFFFFFFFF]
    for value in cases:
        assert dispatch(insns, value) == expected.get(value, 0x2519BD054), value
    for value in (104, 105, 108, 109, 112):
        assert dispatch(insns, value) == 0x2519BD054
    print("type dispatch: raw slice/disassembly + %d finite branch cases OK (11 handled values)" % len(cases))


if __name__ == "__main__":
    check()
