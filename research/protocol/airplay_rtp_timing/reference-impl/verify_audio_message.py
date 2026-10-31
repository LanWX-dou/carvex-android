"""24A446音频API与调用链：原切片、锚点、有限计数解释及坐标案例。"""
from pathlib import Path
import hashlib
import json
import re
import runpy

import capstone

ROOT = Path(__file__).resolve().parents[1]
REPO = next(
    parent for parent in ROOT.parents
    if (parent / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").is_file()
)
SOURCES = {
    "AirPlaySender": (ROOT, "AirPlaySender", "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f"),
    "AirPlaySupport": (ROOT.parent / "airplay_fairplay_crypto", "support", "d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15"),
}


def load(image, directory="asm-audit"):
    source, metadata, expected = SOURCES[image]
    binary = (source / "source/firmware" / image).read_bytes()
    assert hashlib.sha256(binary).hexdigest() == expected
    segments = json.loads((source / "source/metadata" / metadata / "segments.json").read_text(encoding="utf-8"))
    base = ROOT / "source" / directory / image
    index = json.loads((base / "index.json").read_text(encoding="utf-8"))
    assert index["source_sha256"] == expected
    result = {}
    for entry in index["functions"]:
        start, end = int(entry["address"], 16), int(entry["end"], 16)
        segment = next(s for s in segments if s["vmaddr"] <= start < end <= s["vmaddr"] + s["filesize"])
        offset = segment["fileoff"] + start - segment["vmaddr"]
        raw = binary[offset:offset + end - start]
        assert raw == (base / entry["bin"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == entry["raw_sha256"]
        decoded = {i.address: " ".join((i.mnemonic + " " + i.op_str).split())
                   for i in capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM).disasm(raw, start)}
        recorded = {}
        for line in (base / entry["asm"]).read_text(encoding="utf-8").splitlines():
            match = re.match(r"(0x[0-9a-f]+):\s*(.*)", line)
            if match:
                recorded[int(match[1], 16)] = " ".join(match[2].split())
        assert decoded == recorded
        result.update(decoded)
    return result


def scan_count(insns, first_bytes, maximum):
    """解释d70初始化及d9c到df0；元素读取调用只返回给定首字节。

    不模拟原读取器的越界行为；无终止输入在此模型明确失败。
    超限选日志门直接落dec的已存在路径，不假定所有日志状态一样。
    """
    assert insns[0x2519C0D70] == "mov w21, #1"
    pc, count, position, byte, compare = 0x2519C0D9C, 1, 0, 0, 0
    for _ in range(1000):
        op, _, args = insns[pc].partition(" ")
        next_pc = pc + 4
        if pc == 0x2519C0DA8:
            assert (op, args) == ("bl", "#0x251ace454")
            assert position < len(first_bytes), "synthetic input lacks terminator"
            byte = first_bytes[position]
            position += 1
        elif op == "tbz":
            assert args == "w8, #7, #0x2519c0df0"
            if not byte & 0x80:
                next_pc = 0x2519C0DF0
        elif pc == 0x2519C0DB4:
            assert (op, args) == ("add", "w21, w21, #1")
            count = (count + 1) & 0xFFFFFFFF
        elif pc == 0x2519C0DBC:
            assert (op, args) == ("cmp", "w21, w8")
            compare = count - maximum
        elif pc == 0x2519C0DC0:
            assert (op, args) == ("b.ls", "#0x2519c0d9c")
            next_pc = 0x2519C0D9C if compare <= 0 else 0x2519C0DEC
        elif pc == 0x2519C0DEC:
            assert (op, args) == ("mov", "w21, #0")
            count = 0
        elif pc == 0x2519C0DF0:
            assert (op, args) == ("str", "w21, [x19, #0x678]")
            return count
        else:
            assert pc in (0x2519C0D9C, 0x2519C0DA0, 0x2519C0DA4, 0x2519C0DAC, 0x2519C0DB8)
        pc = next_pc
    raise AssertionError("scan did not terminate")


def check():
    insns = load("AirPlaySender") | load("AirPlaySupport") | load("AirPlaySender", "asm")
    anchors = {
        0x226E6A33C: "mov x4, x1", 0x226E6A340: "mov w1, #0xa",
        0x226E6A344: "mov x3, #0", 0x226E6A348: "bl #0x22818be80",
        0x226F23D64: "mov x5, x3", 0x226F23D68: "add x3, x2, #0xa",
        0x226F23D6C: "mov x2, #0", 0x226F23D74: "bl #0x22818be50",
        0x226E68A08: "mov x1, #0", 0x226E68A0C: "mov w2, #0xa",
        0x226E68A10: "bl #0x22818be20", 0x226E68A20: "rev w8, w8",
        0x226E68A30: "rev32 v0.8b, v0.8b",
        0x226F23F80: "cmp x0, #9", 0x226F23F84: "b.ls #0x226f23fd4",
        0x226F23F8C: "rev w8, w8", 0x226F23F9C: "rev32 v0.8b, v0.8b",
        0x226F23FAC: "mov x2, #0", 0x226F23FB0: "mov w3, #0xa",
        0x226F23FB4: "bl #0x22818bec0", 0x226F23FEC: "mov w19, #-0x1a31",
        0x226E68B04: "mov x4, x1", 0x226E68B08: "mov w1, #2",
        0x226E68B0C: "mov x2, #0", 0x226E68B10: "mov x3, #0",
        0x226E68B14: "bl #0x22818be80", 0x226E68B20: "mov w8, #8",
        0x226E68B24: "str x8, [x19]",
        0x251B818D0: "mov w8, #0x60", 0x251B818D4: "str w8, [x21]",
        0x251B818D8: "add x4, sp, #0xc4", 0x251B818DC: "add x5, sp, #0xc0",
        0x251B818F0: "bl #0x2519c348c", 0x251B81A1C: "bl #0x25810aca0",
        0x251B81A40: "bl #0x251aa7f38", 0x251B81AEC: "ldr w3, [sp, #0xc0]",
        0x251AA800C: "bl #0x25810dfb0", 0x251AA8018: "mov w27, w23",
        0x251AA801C: "add x1, x27, #0xa", 0x251AA803C: "add x1, x21, #0xa",
        0x251AA80B8: "sub x4, x21, x27", 0x251AA80BC: "str x22, [sp]",
        0x251AA80D4: "mov x6, x4", 0x251AA80D8: "mov x7, x23",
        0x251AA80DC: "blraa x9, x8", 0x251AA7FFC: "cbz x20, #0x251aa80e4",
        0x251AA80F8: "mov w24, #-0x31ee", 0x251A6F90C: "str w22, [x8, x9, lsl #2]",
        0x2519C2590: "mov x2, x22", 0x2519C2594: "blraa x9, x8",
        0x2519C0D24: "bl #0x25810eae0", 0x2519C0D40: "add x0, x8, #2",
        0x2519C0D44: "bl #0x2580f43e0", 0x2519C0D54: "bl #0x25810aca0",
        0x2519C0D58: "add x9, x0, #2", 0x2519C09E4: "bl #0x25810dfb0",
        0x2519C0A48: "mov x1, x23", 0x2519C0A4C: "mov x2, x24",
    }
    for addr, expected in anchors.items():
        assert insns[addr] == expected, (hex(addr), insns[addr])
    # 导入符号也作为可检查证据，不仅靠人工注释给API命名。
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for address, symbol in {
        "0x22818be80": "_CMBlockBufferGetDataPointer",
        "0x22818be50": "_CMBlockBufferCreateWithBufferReference",
        "0x22818be20": "_CMBlockBufferCopyDataBytes",
        "0x22818bec0": "_CMBlockBufferReplaceDataBytes",
        "0x25810dfb0": "_APSTransportMessageGetAudioAADPointer",
        "0x25810aca0": "_CMBlockBufferGetDataLength",
    }.items():
        assert f"{address}: {symbol}\n" in stubs
    # 头转换按rev16/rev32的独立字节交换模型，非宿主结构体直接dump。
    little = bytes.fromhex("3412 44332211 ddccbbaa")
    message_header = little[:2][::-1] + little[2:6][::-1] + little[6:10][::-1]
    assert message_header.hex() == "123411223344aabbccdd"
    assert message_header[2:10].hex() == "11223344aabbccdd"
    Slice = runpy.run_path(str(ROOT / "reference-impl/verify_compose_layout.py"))["Slice"]
    cases = 0
    for n in (0, 1, 2, 16):
        count = scan_count(insns, [0xE0] * n + [0x60], n + 1)
        assert count == n + 1
        g = 4 * count - 3
        assert g == 4 * n + 1
        for overhead in (0, 16, 24):
            data_length = 53 + n
            total = 10 + g + data_length + overhead
            s = Slice(insns)
            s.put("sp", 0x20000)
            s.put("x0", total)  # GetDataLength结果
            s.write(0x20078, overhead.to_bytes(8, "little"))
            s.write(0x200C4, (10 + g).to_bytes(4, "little"))
            s.run(0x251B81A20, 0x251B81A30)
            assert (s.get("x1"), s.get("w2")) == (g + data_length, g)
            # helper复制入口参数后执行实际长度算术块。
            s.put("x21", s.get("x1"))
            s.put("x23", s.get("w2"))
            s.run(0x251AA8018, 0x251AA801C)
            assert s.get("x1") == 10 + g
            s.run(0x251AA80B8, 0x251AA80B8)
            assert s.get("x4") == data_length
            # 接收映射: M->I+2，尾部附加输出仍在解密输入范围内。
            assert (total + 2) - 12 - g == data_length + overhead
            cases += 1
    assert scan_count(insns, [0x80, 0x80, 0x60], 1) == 0
    return f"9 audit slices + original slices, {len(anchors)} anchors, 6 imports, {cases} caller/count cases + overflow path OK"


if __name__ == "__main__":
    print(check())
