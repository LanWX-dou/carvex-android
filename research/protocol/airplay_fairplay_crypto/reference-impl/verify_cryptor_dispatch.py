"""原始分支有限解释：端点属性/keyholder门/type与派生调用参数。

不执行provider、密码库、PAC、CF对象或网络。槽名A/B不代表主备或线上方向。
"""
from pathlib import Path
import hashlib
import json
import re
import struct

from verify_screen_aad import load, ROOT, REPO

SENDER_SHA = "304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f"
SUPPORT_SHA = "d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15"
# Stop before each provider vtable dispatch sequence, not after an assumed successful provider call.
PROVIDERS = {0x2519BCB44: "101-chacha", 0x2519BCC20: "common-chacha", 0x2519BCE4C: "cbc",
             0x2519BCEFC: "100-chacha", 0x2519BCFB8: "106-chacha", 0x2519BCCE4: "107-chacha",
             0x2519BCDB4: "screen-chacha", 0x2519BD0B4: "ctr"}


def route(insns, kind, gate, holder, flag40, out_a):
    r = {"x22": gate, "x21": int(holder), "w23": kind & 0xffffffff, "x26": int(out_a)}
    pc, compared = 0x2519BCACC, None
    # These straight-line vtable authentication sequences are outside the branch model.
    # The skip ends before the tested gate; no claim that PAC/object lookup succeeds.
    opaque = {0x2519BCBEC: 0x2519BCC1C, 0x2519BCD80: 0x2519BCDB0}
    for _ in range(65):
        if pc in PROVIDERS: return PROVIDERS[pc]
        if pc == 0x2519BD120: return "null-common"
        if pc == 0x2519BD054: return "unknown-type"
        if pc == 0x2519BD50C: return "missing-holder"
        if pc == 0x2519BD148: return "early-no-output"
        if pc == 0x2519BCB18: return "early-clear-A-only"
        if pc in opaque: pc = opaque[pc]; continue
        op, args = insns[pc].split(" ", 1)
        values = args.split(", ")
        nxt = pc+4
        if op in ("cbz", "cbnz"):
            take = (r[values[0]] == 0) == (op == "cbz")
            if take: nxt = int(values[1][1:], 16)
        elif op == "cmp": compared = r[values[0]], int(values[1][1:], 0)
        elif op == "sub": r[values[0]] = (r[values[1]]-int(values[2][1:], 0)) & 0xffffffff
        elif op == "mov": r[values[0]] = int(values[1][1:], 0)
        elif op == "ldrb":
            assert args == "w8, [x24, #0x40]"
            r["w8"] = flag40
        elif op == "b": nxt = int(args[1:], 16)
        elif op.startswith("b."):
            left, right = compared
            signed = lambda x: x-(1 << 32) if x & 0x80000000 else x
            cond = {"b.eq": left == right, "b.ne": left != right, "b.le": signed(left) <= signed(right),
                    "b.gt": signed(left) > signed(right), "b.lo": left < right, "b.hs": left >= right}[op]
            if cond: nxt = int(args[1:], 16)
        else: raise AssertionError((hex(pc), insns[pc]))
        pc = nxt
    raise AssertionError("unexpected dispatch loop")


def args_slice(insns, begin, end, connection):
    """执行实际参数准备小片段；基址和connection由测试显式给出，不执行密钥派生。"""
    r = {"sp": 0x10000, "x29": 0x10140, "x21": 0x20000}
    def get(s): return int(s[1:], 0) if s.startswith("#") else r[s]
    for pc in range(begin, end, 4):
        op, args = insns[pc].split(" ", 1)
        a = args.split(", ")
        dest = a[0].replace("w", "x")
        if op == "mov": r[dest] = get(a[1])
        elif op == "add": r[dest] = get(a[1])+get(a[2])
        elif op == "sub": r[dest] = get(a[1])-get(a[2])
        elif op == "ldr":
            assert args == "x1, [sp, #0x60]"
            r[dest] = connection
        else: raise AssertionError((hex(pc), insns[pc]))
    return [r.get(f"x{i}") for i in range(6)]


def property_bytes():
    binary = (ROOT / "source/firmware/AirPlaySender").read_bytes()
    assert hashlib.sha256(binary).hexdigest() == SENDER_SHA
    segments = json.loads((ROOT / "source/metadata/sender/segments.json").read_text(encoding="utf-8"))
    def read(a, n):
        s = next(s for s in segments if s["vmaddr"] <= a and a+n <= s["vmaddr"]+s["filesize"])
        off = s["fileoff"]+a-s["vmaddr"]
        return binary[off:off+n]
    cache = REPO / "firmware/extracted/24A446/dyld/dyld_shared_cache_arm64e.54.dylddata"
    with cache.open("rb") as f:
        header = f.read(512)
        assert header.startswith(b"dyld_v")
        off, count = struct.unpack_from("<II", header, 0x138)
        assert off and 0 < count < 100
        f.seek(off)
        mappings = [struct.unpack("<QQQQQQII", f.read(56)) for _ in range(count)]
        def pointer(slot):
            a, size, fo, slideoff, slidesize, *_ = next(m for m in mappings if m[0] <= slot < m[0]+m[1])
            assert slidesize >= 24
            f.seek(slideoff)
            data = f.read(24)
            assert struct.unpack_from("<I", data)[0] == 5
            base = struct.unpack_from("<Q", data, 16)[0]
            assert base == 0x180000000
            raw = read(slot, 8)
            f.seek(fo+slot-a)
            assert f.read(8) == raw
            p = int.from_bytes(raw, "little")
            assert not p >> 63
            return (base+(p & ((1 << 34)-1))) | (((p >> 34) & 255) << 56)
        cf = pointer(0x2693E7270)
        assert cf == 0x276135310
        addr = pointer(cf+16)
        assert addr == 0x251C1A294
        name = b"SupportsCoreUtilsPairingAndEncryption"
        assert int.from_bytes(read(cf+24, 8), "little") == len(name)
        assert read(addr, len(name)+1) == name+b"\0"
    syms = json.loads((ROOT / "source/metadata/sender/symbols.json").read_text(encoding="utf-8"))
    assert any(x["addr"] == 0x2693E7270 and x["name"] == "_kAPEndpointDescriptionProperty_SupportsCoreUtilsPairingAndEncryption" for x in syms)


def check():
    insns, count = load("AirPlaySender", "asm", ROOT, "sender", SENDER_SHA, {0x2519BBF24})
    support, _ = load("AirPlaySupport", "asm", ROOT, "support", SUPPORT_SHA, {0x226F2F54C})
    property_bytes()
    anchors = {
        0x2519BC010: "adrp x8, #0x2693e7000", 0x2519BC014: "add x8, x8, #0x270",
        0x2519BC018: "ldr x1, [x8]", 0x2519BC01C: "str x1, [sp, #0x40]",
        0x2519BCA6C: "ldr w23, [x19, #8]", 0x2519BCA70: "ldp x26, x25, [x19, #0x20]",
        0x2519BCA90: "ldr x0, [x0, #0x30]", 0x2519BCA94: "ldr x1, [sp, #0x40]",
        0x2519BCA98: "mov x2, #0", 0x2519BCA9C: "bl #0x258109860",
        0x2519BCAA0: "mov x22, x0", 0x2519BCAAC: "ldr x0, [x24, #0x150]",
        0x2519BCA80: "stp xzr, xzr, [sp, #0x78]", 0x2519BCA8C: "str xzr, [sp, #0x70]",
        0x2519BCB18: "str xzr, [x26]", 0x2519BCB1C: "b #0x2519bd208",
        0x2519BCBCC: "bl #0x258109690", 0x2519BCBC8: "mov w2, #1",
        0x2519BCC8C: "bl #0x258109690", 0x2519BCC88: "mov w2, #1",
        0x2519BCD6C: "bl #0x258109690", 0x2519BCD68: "mov w2, #1",
        0x2519BCE20: "bl #0x258109690", 0x2519BCE1C: "mov w2, #0",
        0x2519BCEAC: "bl #0x258109680", 0x2519BCF88: "bl #0x258109690",
        0x2519BCF84: "mov w2, #1", 0x2519BCFA0: "bl #0x258109690",
        0x2519BCF9C: "mov w2, #1", 0x2519BD040: "bl #0x258109690",
        0x2519BD03C: "mov w2, #1", 0x2519BD118: "bl #0x25810d160",
        0x2519BD128: "str x8, [x26]", 0x2519BD13C: "str x8, [x25]",
        0x226F2F570: "mov x20, x2", 0x226F2F5D4: "strb w20, [x22]",
    }
    all_insns = insns | support
    for a, op in anchors.items(): assert all_insns[a] == op, (hex(a), all_insns[a])
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for a, symbol in {"0x258109860": "_APSGetFBOPropertyInt64", "0x258109690": "_APSCryptorChaCha20Poly1305Create",
                      "0x258109680": "_APSCryptorCBCCreate", "0x25810d160": "_APSCryptorCTRCreate"}.items():
        assert f"{a}: {symbol}\n" in stubs
    cases = 0
    types = list(range(256))+[-1, -(1 << 31), (1 << 31)-1, 0xffffffff]
    for t in types:
        for g in (0, 1, 2, (1 << 64)-1):
            for holder in (False, True):
                for flag40 in (0, 1):
                    for out_a in (False, True):
                        if not holder:
                            want = ("early-clear-A-only" if out_a else "early-no-output") if not g and flag40 else "missing-holder"
                        else:
                            want = {96: "common-chacha" if g else "cbc", 102: "common-chacha" if g else "cbc",
                                    103: "common-chacha" if g else "cbc", 100: "100-chacha" if g else "null-common",
                                    101: "101-chacha" if g else "null-common", 106: "106-chacha" if g else "null-common",
                                    107: "107-chacha" if g else "null-common", 110: "screen-chacha" if g else "ctr",
                                    111: "screen-chacha" if g else "ctr", 120: "null-common", 130: "null-common"}.get(t, "unknown-type")
                        assert route(insns, t, g, holder, flag40, out_a) == want, (t, g, holder, flag40, out_a)
                        cases += 1
    starts = [(0x2519BCB94, 0x2519BCBAC, 0, 0x100b0), (0x2519BCC54, 0x2519BCC6C, 0, 0x100b0),
              (0x2519BCD34, 0x2519BCD4C, 0x10080, 0), (0x2519BCDE8, 0x2519BCE00, 0, 0x100b0),
              (0x2519BCF4C, 0x2519BCF64, 0x10080, 0x100b0), (0x2519BD008, 0x2519BD020, 0, 0x100b0)]
    for begin, end, first, second in starts:
        for connection in (0, 0x123456789abcdef0, (1 << 64)-1):
            assert args_slice(insns, begin, end, connection) == [0x20000, connection, 32, first, 32, second]
    print(f"       cryptor dispatch: raw_slices={count+1}, anchors={len(anchors)}, gate/type_cases={cases}, argument_cases=18, property=v5")


if __name__ == "__main__":
    check()
