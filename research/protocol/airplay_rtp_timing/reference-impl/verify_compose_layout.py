"""原字节/反汇编锚点及Compose双游标有限解释；不执行外部API或队列。"""
from pathlib import Path
import hashlib
import json
import re

import capstone

ROOT = Path(__file__).resolve().parents[1]


def instructions():
    directory = ROOT / "source/asm/AirPlaySender"
    index = json.loads((directory / "index.json").read_text(encoding="utf-8"))
    binary = (ROOT / "source/firmware/AirPlaySender").read_bytes()
    segments = json.loads((ROOT / "source/metadata/AirPlaySender/segments.json").read_text(encoding="utf-8"))
    result = {}
    for start in (0x2519C348C, 0x2519C2770):
        item = next(e for e in index["functions"] if int(e["address"], 16) == start)
        size = int(item["end"], 16) - start
        segment = next(s for s in segments if 0 <= start - s["vmaddr"]
                       and start - s["vmaddr"] + size <= s["filesize"])
        offset = segment["fileoff"] + start - segment["vmaddr"]
        raw = binary[offset:offset + size]
        assert raw == (directory / item["bin"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == item["raw_sha256"]
        decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
                   for i in capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM).disasm(raw, start)}
        recorded = {}
        for line in (directory / item["asm"]).read_text(encoding="utf-8").splitlines():
            match = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
            if match:
                recorded[int(match[1], 16)] = " ".join(match[2].split())
        assert decoded == recorded
        result.update(decoded)
    return result


class Slice:
    """只支持本测试所选连续块；未知指令失败，不跳过。调用拷贝作为模型。"""

    def __init__(self, insns):
        self.insns, self.regs, self.mem = insns, {}, {}

    def get(self, name):
        if name.startswith("#"):
            return int(name[1:], 0)
        value = self.regs.get(name[1:] if name[0] in "wx" else name, 0)
        return value & (0xFFFFFFFF if name[0] == "w" else 0xFFFFFFFFFFFFFFFF)

    def put(self, name, value):
        self.regs[name[1:] if name[0] in "wx" else name] = value & (
            0xFFFFFFFF if name[0] == "w" else 0xFFFFFFFFFFFFFFFF)

    def read(self, address, length):
        return bytes(self.mem.get(address + i, 0) for i in range(length))

    def write(self, address, data):
        self.mem.update((address + i, b) for i, b in enumerate(data))

    def run(self, first, last):
        for pc in range(first, last + 1, 4):
            op, _, args = self.insns[pc].partition(" ")
            if op in ("ldr", "ldur", "ldrb", "str", "strb", "ldp"):
                match = re.fullmatch(r"([wx]\d+)(?:, ([wx]\d+))?, \[(sp|x\d+)(?:, #(-?0x[0-9a-f]+|\d+))?\](?:, #(\d+))?", args)
                assert match, args
                dst, second, base, offset, post = match.groups()
                address = self.get(base) + int(offset or "0", 0)
                size = 1 if op.endswith("b") else 4 if dst[0] == "w" else 8
                if op.startswith("str"):
                    self.write(address, (self.get(dst) & ((1 << (size * 8)) - 1)).to_bytes(size, "little"))
                else:
                    self.put(dst, int.from_bytes(self.read(address, size), "little"))
                    if second:
                        self.put(second, int.from_bytes(self.read(address + size, size), "little"))
                if post:
                    self.put(base, self.get(base) + int(post))
            elif op == "bl":
                assert args == "#0x2580f43e0"
                self.write(self.get("x0"), self.read(self.get("x1"), self.get("x2")))
            else:
                a = args.split(", ")
                dst = a[0]
                if op == "mov":
                    value = self.get(a[1])
                elif op in ("add", "sub", "lsl", "and", "orr"):
                    left, right = self.get(a[1]), self.get(a[2])
                    if len(a) == 4:
                        assert a[3] == "lsl #24"
                        right <<= 24
                    value = {"add": lambda: left + right, "sub": lambda: left - right,
                             "lsl": lambda: left << right, "and": lambda: left & right,
                             "orr": lambda: left | right}[op]()
                elif op in ("bfi", "bfxil", "ubfiz"):
                    source, shift, width = self.get(a[1]), self.get(a[2]), self.get(a[3])
                    mask = (1 << width) - 1
                    if op == "bfi":
                        value = (self.get(dst) & ~(mask << shift)) | ((source & mask) << shift)
                    elif op == "bfxil":
                        value = (self.get(dst) & ~mask) | ((source >> shift) & mask)
                    else:
                        value = (source & mask) << shift
                elif op == "rev":
                    value = int.from_bytes(self.get(a[1]).to_bytes(4, "little"), "big")
                else:
                    raise AssertionError((hex(pc), op, args))
                self.put(dst, value)


def check():
    insns = instructions()
    anchors = {
        0x2519C34B4: "mov x27, x4", 0x2519C34B8: "mov x28, x3",
        0x2519C34BC: "mov x24, x2", 0x2519C3534: "ldr x0, [x28, #8]",
        0x2519C3540: "bl #0x25810dfd0", 0x2519C3558: "ldr x28, [sp, #0x58]",
        0x2519C35B4: "str w8, [x9]", 0x2519C3584: "mov w20, #0xa",
        0x2519C3588: "b #0x2519c37f8", 0x2519C3704: "ldr x0, [x27, #0x10]",
        0x2519C3710: "bl #0x25810dfd0", 0x2519C3808: "bl #0x25810dfd0",
        0x2519C3844: "bl #0x25810dfa0", 0x2519C3854: "str w20, [x27]",
        0x2519C2A6C: "str x0, [sp, #0x18]", 0x2519C2A78: "str xzr, [sp, #0x18]",
        0x2519C2B64: "ldp x25, x24, [sp, #0x18]", 0x2519C2C40: "mov x2, x25",
        0x2519C2C98: "ldr w28, [sp, #0x8c]", 0x2519C2CA0: "add x23, x8, x28",
    }
    for address, expected in anchors.items():
        assert insns[address] == expected, (hex(address), insns[address])
    for merged, payloads in ((True, []), (True, [b"abc"]),
                             (True, [b"ab", b"12345"]), (False, [])):
        for overhead in (0, 16):
            s = Slice(insns)
            base, sp, fp = 0x10000, 0x20000, 0x200C0
            n, current = len(payloads), b"CURRENT"
            for reg, value in (("sp", sp), ("x29", fp), ("x28", base),
                               ("x8", base), ("w22", n), ("x24", overhead)):
                s.put(reg, value)
            s.write(sp + 0x58, base.to_bytes(8, "little"))
            s.write(sp + 0x3C, (1000).to_bytes(4, "little"))
            expected_elements = b""
            if merged:
                s.run(0x2519C36C0, 0x2519C36D0)
                for i, data in enumerate(payloads):
                    source, desc = 0x30000 + i * 0x1000, 0x40000
                    s.write(source, data)
                    s.put("x27", desc)
                    s.write(desc, (0x60 + i).to_bytes(4, "little"))
                    s.write(sp + 0x38, (990 - i).to_bytes(4, "little"))
                    s.write(sp + 0x60, source.to_bytes(8, "little"))
                    s.write(fp - 0x58, len(data).to_bytes(8, "little"))
                    s.run(0x2519C3728, 0x2519C3768)
                    expected_elements += (0x80000000 | ((0x60 + i) << 24)
                                          | ((10 + i) << 10) | len(data)).to_bytes(4, "big")
                s.run(0x2519C37D8, 0x2519C37DC)
                s.put("x22", 0x40000)
                s.write(0x40000, b"\xe5")
                s.run(0x2519C37E4, 0x2519C37EC)
                expected_elements += b"\x65"
            else:
                s.run(0x2519C3584, 0x2519C3584)
            # GetAudioDataPointer作为不透明成功调用，向栈提供当前音频数据。
            s.write(0x50000, current)
            s.put("x1", 0x50000)
            s.put("x2", len(current))
            s.run(0x2519C3820, 0x2519C3824)
            expected = expected_elements + b"".join(payloads) + current
            assert s.read(base, len(expected)) == expected
            s.put("x8", len(current))
            s.run(0x2519C383C, 0x2519C383C)
            assert s.get("x2") == overhead + len(expected)
            assert s.get("w20") == (4 * n + 11 if merged else 10)
    # 实际指令截断，不等于可安全接受超长载荷；只检查元素取低位，不做超长拷贝。
    s = Slice(insns)
    s.put("w8", 0xE0000000)
    s.put("x2", 1025)
    s.run(0x2519C3740, 0x2519C3740)
    assert s.get("w8") & 1023 == 1
    return "2 raw slices, 20 anchors, 8 dual-cursor/single layouts and L10 truncation OK"


if __name__ == "__main__":
    print(check())
