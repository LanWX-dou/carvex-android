"""有限静态验证：CoreUtils provider 的角色/标签/派生门，非握手。"""
from pathlib import Path
import runpy

ROOT = Path(__file__).resolve().parents[1]


def derive_gate(insns, kind, state, has_pointer, has_length):
    regs = {"x0": 0x100000, "x25": 0x100000}
    pc, compared, zero = 0x18BE50240, (0, 0), False
    for _ in range(60):
        if pc == 0x18BE502AC:
            return "secret32"
        if pc == 0x18BE502DC:
            return "variable"
        if pc == 0x18BE50308:
            return regs["w0"]
        op, operands = insns[pc].split(" ", 1)
        following = pc + 4
        if op in ("ldr", "ldrb"):
            target = operands.split(",", 1)[0]
            if "#0x60]" in operands:
                regs[target] = kind & 0xFFFFFFFF
            elif "#0x80]" in operands:
                regs[target] = state
            elif "#0x300]" in operands:
                regs[target] = int(has_pointer)
            elif "#0x308]" in operands:
                regs[target] = int(has_length)
            else:
                raise AssertionError(insns[pc])
        elif op == "mov":
            dst, src = operands.split(", ")
            regs[dst] = int(src[1:], 0) if src.startswith("#") else regs.get(src, 0)
        elif op == "lsl":
            dst, left, right = operands.split(", ")
            regs[dst] = (regs[left] << (regs[right] & 31)) & 0xFFFFFFFF
        elif op == "cmp":
            left, right = operands.split(", ")
            compared = (regs[left], int(right[1:], 0))
            zero = compared[0] == compared[1]
        elif op == "tst":
            left, right = operands.split(", ")
            zero = not (regs[left] & int(right[1:], 0))
        elif op == "cbz":
            src, target = operands.split(", ")
            if regs[src] == 0:
                following = int(target[1:], 0)
        elif op in ("b", "b.hi", "b.eq", "b.ne"):
            take = {"b": True, "b.hi": compared[0] > compared[1],
                    "b.eq": zero, "b.ne": not zero}[op]
            if take:
                following = int(operands[1:], 0)
        else:
            raise AssertionError((hex(pc), insns[pc]))
        pc = following
    raise AssertionError("gate did not terminate")


def check():
    load = runpy.run_path(str(ROOT / "tools/verify-type-dispatch.py"))["load_instructions"]
    sources = [
        ("CoreUtils", 0x18BE5021C, "asm"), ("CoreUtils", 0x18BF1ADBC, "asm"),
        ("APTransport", 0x24FDC7034, "asm"), ("APTransport", 0x24FDC97E8, "asm"),
        ("AirPlaySender", 0x251A358E4, "asm"), ("AirPlaySender", 0x2519BD76C, "asm"),
        ("AirPlaySender", 0x251A355D0, "asm-audit"), ("AirPlaySender", 0x2519BFFC8, "asm-audit"),
    ]
    insns = {}
    for image, start, directory in sources:
        insns.update(load(image, start, directory))
    anchors = {
        0x24FDC7168: "add x1, x1, #0x5e0",
        0x24FDC7180: "strb w8, [x22, #0x100]",
        0x24FDC718C: "strb wzr, [x22, #0x100]",
        0x24FDC986C: "ldr x9, [x16, #0x40]!",
        0x24FDC98A4: "sub x3, x29, #0x28", 0x24FDC98A8: "sub x5, x29, #0x30",
        0x24FDC98E4: "ldrb w9, [x20, #0x100]",
        0x24FDC98EC: "cbz w9, #0x24fdc99a4",
        0x24FDC98F4: "ldur x0, [x29, #-0x30]", 0x24FDC9900: "ldur x0, [x29, #-0x28]",
        0x24FDC99A8: "ldur x0, [x29, #-0x28]", 0x24FDC99B4: "ldur x0, [x29, #-0x30]",
        0x251A35908: "mov x19, x5", 0x251A3590C: "mov x20, x3",
        0x251A35A6C: "add x6, sp, #0x18", 0x251A35A7C: "mov x3, x28",
        0x251A35AE0: "add x6, sp, #0x10", 0x251A35AF0: "ldr x3, [sp, #8]",
        0x251A35B08: "ldr x8, [sp, #0x18]", 0x251A35B0C: "str x8, [x20]",
        0x251A35B1C: "ldr x8, [sp, #0x10]", 0x251A35B20: "str x8, [x19]",
        0x251A35604: "add x1, x1, #0xae0",
        0x2519C0058: "ldr x9, [x16, #8]!",
        0x2519BD7C0: "bl #0x25810ba10",
        0x18BE502B4: "add x2, x25, #0x28e", 0x18BE502B8: "mov w1, #0x20",
        0x18BE502AC: "bl #0x1900cf870", 0x18BE50300: "bl #0x1900cf190",
    }
    for address, expected in anchors.items():
        assert insns.get(address) == expected, (hex(address), insns.get(address))
    decoder = runpy.run_path(str(ROOT / "tools/decode-keys.py"))
    for image, strings, pointers in (
        ("APTransport", {0x275FA45E0: "IsServer"}, {}),
        ("AirPlaySender", {0x27612C250: "Ctrl", 0x27612C270: "Events"}, {
            0x276124AF0: 0x276124B58, 0x276124B88: 0x2519BFFC8,
            0x276124B98: 0x251A358E4, 0x276126D20: 0x276126D88,
            0x276126D90: 0x2519BD76C,
        }),
    ):
        segments, binary, symbols = decoder["load"](image)
        for address, expected in strings.items():
            assert decoder["decode_string"](segments, binary, address)[0] == expected
        for address, expected in pointers.items():
            assert decoder["candidates"](segments, binary, address) == [expected]
        if image == "AirPlaySender":
            for address, expected in {
                0x251BDF6CA: "Control-Salt", 0x251BDF6D7: "Control-Read-Encryption-Key",
                0x251BDF6F3: "Control-Write-Encryption-Key", 0x251BDF710: "Events-Salt",
                0x251BDF71C: "Events-Read-Encryption-Key", 0x251BDF737: "Events-Write-Encryption-Key",
            }.items():
                offset = decoder["off_of"](segments, address)
                assert binary[offset:offset + len(expected) + 1] == expected.encode() + b"\0"
    cases = 0
    for kind in list(range(8)) + [0xFFFFFFFF]:
        for state in range(9):
            for pointer, length in ((False, False), (False, True), (True, False), (True, True)):
                expected = -0x1A4F if kind not in range(1, 7) else -0x1A35
                if kind in (1, 2) and state == 7 and pointer and length:
                    expected = "variable"
                if (kind in (3, 4) and state == 5) or (kind in (5, 6) and state == 3):
                    expected = "secret32"
                assert derive_gate(insns, kind, state, pointer, length) == expected, (kind, state, pointer, length)
                cases += 1
    print("keyholder: 8 raw slices, %d anchors, CFStrings/vtables/labels and %d gate cases OK" % (len(anchors), cases))


if __name__ == "__main__":
    check()
