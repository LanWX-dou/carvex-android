"""Sender Legacy KDF的正面证据；不执行CF对象、密码库或真实握手。"""
import json

from verify_screen_aad import load, ROOT, REPO, RECEIVER_SHA
from verify_cryptor_dispatch import SENDER_SHA


def check():
    sender, ns = load("AirPlaySender", "asm", ROOT, "sender", SENDER_SHA,
                      {0x251AA97A0, 0x251AA9A60})
    receiver, nr = load("AirPlayReceiver", "asm", ROOT, "receiver", RECEIVER_SHA,
                        {0x2518D4338})
    anchors = {
        # Darwin variadic arguments are on the stack: prefix, input x1 (not a local counter).
        0x251AA97C4: "mov x19, x1", 0x251AA97D4: "adrp x8, #0x251c18000",
        0x251AA97D8: "add x8, x8, #0xc36", 0x251AA97DC: "stp x8, x1, [sp]",
        0x251AA97E0: "adrp x20, #0x251bdf000", 0x251AA97E4: "add x20, x20, #0x641",
        0x251AA97EC: "mov x1, x20", 0x251AA97F0: "bl #0x25810a1a0",
        0x251AA97F8: "adrp x8, #0x251c18000", 0x251AA97FC: "add x8, x8, #0xc47",
        0x251AA9800: "stp x8, x19, [sp]", 0x251AA9808: "mov x1, x20",
        0x251AA980C: "bl #0x25810a1a0", 0x251AA9824: "bl #0x251aa9a60",
        0x251AA983C: "bl #0x251aa9a60",
        # Helper: name/length saved, derived storage acquired, SHA(name then key16), first16 copied.
        0x251AA9A80: "mov x21, x2", 0x251AA9A84: "mov x22, x1",
        0x251AA9A98: "bl #0x25810ac50", 0x251AA9A9C: "mov x23, x0",
        0x251AA9AE0: "bl #0x25810e690", 0x251AA9AE8: "mov x1, x22",
        0x251AA9AEC: "mov x2, x21", 0x251AA9AF0: "bl #0x25810e6a0",
        0x251AA9AF8: "add x1, x23, #0x10", 0x251AA9AFC: "mov w2, #0x10",
        0x251AA9B00: "bl #0x25810e6a0", 0x251AA9B08: "sub x0, x29, #0x78",
        0x251AA9B0C: "mov x1, sp", 0x251AA9B10: "bl #0x25810e680",
        0x251AA9B18: "bl #0x25810e780", 0x251AA9B1C: "ldur q0, [x29, #-0x78]",
        0x251AA9B20: "str q0, [x0]",
        # Receiver source of the formatted integer: dictionary result, not loop index 0/1.
        0x2518D5AF4: "mov x0, x22", 0x2518D5AF8: "adrp x1, #0x276119000",
        0x2518D5AFC: "add x1, x1, #0xdd0", 0x2518D5B00: "mov x2, #0",
        0x2518D5B04: "bl #0x25810a6f0", 0x2518D5B08: "cbz x0, #0x2518d6eb4",
        0x2518D5B0C: "mov x19, x0", 0x2518D5B14: "cbz x21, #0x2518d5c1c",
        0x2518D5C1C: "add x0, x20, #0x160", 0x2518D5C20: "add x3, sp, #0x188",
        0x2518D5C24: "add x4, sp, #0x178", 0x2518D5C28: "mov w1, #0x10",
        0x2518D5C2C: "mov x2, x19", 0x2518D5C30: "bl #0x2581096f0",
    }
    insns = sender | receiver
    for address, instruction in anchors.items():
        assert insns[address] == instruction, (hex(address), insns[address])
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    symbols = {"0x25810a1a0": "_ASPrintF", "0x25810ac50": "_CMBaseObjectGetDerivedStorage",
               "0x25810e690": "_CC_SHA512_Init", "0x25810e6a0": "_CC_SHA512_Update",
               "0x25810e680": "_CC_SHA512_Final", "0x25810e780": "_CFDataGetMutableBytePtr",
               "0x25810a6f0": "_CFDictionaryGetInt64",
               "0x2581096f0": "_APSEncryptionUtilsDeriveAESKeySHA512ForScreen"}
    for address, symbol in symbols.items():
        assert f"{address}: {symbol}\n" in stubs, (address, symbol)
    binary = (ROOT / "source/firmware/AirPlaySender").read_bytes()
    segments = json.loads((ROOT / "source/metadata/sender/segments.json").read_text(encoding="utf-8"))
    strings = {0x251C18C36: b"AirPlayStreamKey\0", 0x251C18C47: b"AirPlayStreamIV\0",
               0x251BDF641: b"%s%llu\0"}
    for address, expected in strings.items():
        segment = next(s for s in segments if s["vmaddr"] <= address and
                       address+len(expected) <= s["vmaddr"]+s["filesize"])
        offset = segment["fileoff"]+address-segment["vmaddr"]
        assert binary[offset:offset+len(expected)] == expected
    print(f"       Sender Legacy KDF: slices={ns+nr}, anchors={len(anchors)}, strings={len(strings)}, imports={len(symbols)}")


if __name__ == "__main__":
    check()
