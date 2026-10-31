"""CoreUtils AES原切片、指令锚点、有限进位/尾拷贝解释和NIST已知答案。

不执行CommonCrypto二进制，不证明网络profile；局部解释不模拟整个CPU。
"""
from verify_screen_aad import load, ROOT, REPO, CORE_SHA
import fairplay_crypto as fc


def increment_slice(insns, start, stop, counter):
    """原CTR两处循环；只解释字节计数器更新，不模拟AES调用。"""
    pc, r, zero = start, {}, False
    b = bytearray(counter)
    for _ in range(180):
        if pc == stop:
            return bytes(b)
        op = insns[pc]
        next_pc = pc+4
        if op == "mov x8, #-0xf": r[8] = (1 << 64)-15
        elif op == "mov w9, #0x10": r[9] = 16
        elif op == "sub x9, x9, #1": r[9] -= 1
        elif op == "ldrb w10, [x24, x9]": r[10] = b[r[9]]
        elif op == "add w10, w10, #1": r[10] += 1
        elif op == "and w11, w10, #0xff": r[11] = r[10] & 255
        elif op == "strb w10, [x24, x9]": b[r[9]] = r[10] & 255
        elif op == "cmp w11, #0": zero = r[11] == 0
        elif op == "ccmp x8, #0, #4, eq": zero = r[8] == 0 if zero else True
        elif op == "add x8, x8, #1": r[8] = (r[8]+1) & ((1 << 64)-1)
        elif op.startswith("b.ne #"):
            if not zero: next_pc = int(op.split("#")[1], 16)
        else: raise AssertionError((hex(pc), op))
        pc = next_pc
    raise AssertionError("counter loop did not terminate")


def copy_tail(insns, source, moved):
    """解释CBCUpdate在外部Update返回后的指针推进/尾拷贝；moved是显式输入。"""
    assert 0 <= moved <= len(source)
    r = {8: moved, 19: 0, 20: 0, 23: len(source)}
    out = bytearray(len(source))
    pc, equal = 0x18BE62C10, False
    for _ in range(5*len(source)+20):
        op = insns[pc]
        if op == "add x9, x20, x8": r[9] = r[20]+r[8]
        elif op == "add x10, x19, x8": r[10] = r[19]+r[8]
        elif op == "mov x20, x9": r[20] = r[9]
        elif op == "mov x19, x10": r[19] = r[10]
        elif op == "b #0x18be62c2c": pc = 0x18BE62C2C; continue
        elif op == "ldrb w8, [x20], #1": r[8] = source[r[20]]; r[20] += 1
        elif op == "strb w8, [x19], #1": out[r[19]] = r[8]; r[19] += 1
        elif op == "cmp x20, x23": equal = r[20] == r[23]
        elif op == "b.ne #0x18be62c24":
            if not equal: pc = 0x18BE62C24; continue
        elif op == "mov w0, #0": return bytes(out[moved:])
        else: raise AssertionError((hex(pc), op))
        pc += 4
    raise AssertionError("copy loop did not terminate")


def check():
    insns, count = load("CoreUtils", "asm-aes-audit", ROOT.parent / "airplay_control_plane", "CoreUtils", CORE_SHA)
    anchors = {
        0x18BE628DC: "mov w0, #0", 0x18BE628E0: "mov w1, #0", 0x18BE628E4: "mov w2, #2",
        0x18BE628E8: "mov w4, #0x10", 0x18BE628F4: "bl #0x1900cd730",
        0x18BE62900: "stur q0, [x19, #8]", 0x18BE62904: "str xzr, [x19, #0x28]",
        0x18BE62944: "add x23, x0, #0x18", 0x18BE62948: "ldr x8, [x0, #0x28]",
        0x18BE62950: "cbz x8, #0x18be62988", 0x18BE62958: "ldrb w10, [x23, x8]",
        0x18BE62968: "and x25, x11, #0xf", 0x18BE62990: "str x25, [x20, #0x28]",
        0x18BE6299C: "add x24, x20, #8", 0x18BE629AC: "mov w2, #0x10",
        0x18BE629B0: "mov x3, x23", 0x18BE629B8: "bl #0x1900cd770",
        0x18BE629C8: "b.ne #0x18be62af4", 0x18BE62A5C: "bl #0x1900cd770",
        0x18BE62A6C: "b.ne #0x18be62af4", 0x18BE62ACC: "str x25, [x20, #0x28]",
        0x18BE62AF4: "mov w0, #-0x1a57",
        0x18BE62B68: "cmp w3, #0", 0x18BE62B6C: "cset w0, eq", 0x18BE62B70: "mov w1, #0",
        0x18BE62B74: "mov w2, #0", 0x18BE62B7C: "mov w4, #0x10",
        0x18BE62B88: "bl #0x1900cd730", 0x18BE62B94: "stur q0, [x20, #8]",
        0x18BE62BC8: "add x23, x1, x2", 0x18BE62BCC: "ands x21, x2, #-0x10",
        0x18BE62BD4: "b.eq #0x18be62c2c", 0x18BE62BDC: "mov x1, x0",
        0x18BE62BE0: "ldr x0, [x1], #8", 0x18BE62BE4: "bl #0x1900eb6b0",
        0x18BE62BE8: "cbnz w0, #0x18be62c38", 0x18BE62BF8: "mov x2, x21",
        0x18BE62C00: "mov x4, x21", 0x18BE62C04: "bl #0x1900cd770",
        0x18BE62C08: "cbnz w0, #0x18be62c38", 0x18BE62C0C: "ldr x8, [sp, #8]",
        0x18BE62B18: "bl #0x1900cd760", 0x18BE62B20: "mov w1, #0x30",
        0x18BE62B44: "b #0x1900cfdb0", 0x18BE62C6C: "bl #0x1900cd760",
        0x18BE62C74: "mov w1, #0x18", 0x18BE62C98: "b #0x1900cfdb0",
    }
    for addr, expected in anchors.items():
        assert insns[addr] == expected, (hex(addr), insns[addr])
    stubs = (REPO / "firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt").read_text(encoding="utf-8")
    for addr, name in {"0x1900cd730": "_CCCryptorCreate", "0x1900cd770": "_CCCryptorUpdate",
                       "0x1900eb6b0": "_CCCryptorReset", "0x1900cd760": "_CCCryptorRelease",
                       "0x1900cfdb0": "_memset_s"}.items():
        assert f"{addr}: {name}\n" in stubs
    # 两处大端进位循环，含贯穿16B的回绕；参考实现另加耗尽保护。
    for trailing in range(17):
        value = bytes(16-trailing)+b"\xff"*trailing
        expected = ((int.from_bytes(value, "big")+1) & ((1 << 128)-1)).to_bytes(16, "big")
        for start, end in ((0x18BE629CC, 0x18BE629F8), (0x18BE62A70, 0x18BE62A9C)):
            assert increment_slice(insns, start, end, value) == expected
    for n in range(81):
        data = bytes(range(n))
        assert copy_tail(insns, data, n & ~15) == data[n & ~15:]
    # NIST SP800-38A F.2.1 CBC-AES128 / F.5.1 CTR-AES128，独立已知答案，不是本实现生成。
    key = bytes.fromhex("2b7e151628aed2a6abf7158809cf4f3c")
    plain = bytes.fromhex("6bc1bee22e409f96e93d7e117393172a ae2d8a571e03ac9c9eb76fac45af8e51 30c81c46a35ce411e5fbc1191a0a52ef f69f2445df4f9b17ad2b417be66c3710")
    cbc_iv = bytes(range(16))
    cbc_answer = bytes.fromhex("7649abac8119b246cee98e9b12e9197d 5086cb9b507219ee95db113a917678b2 73bed6b8e3c1743b7116e69e22229516 3ff1caa1681fac09120eca307586e1a7")
    ctr_iv = bytes.fromhex("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff")
    ctr_answer = bytes.fromhex("874d6191b620e3261bef6864990db6ce 9806f66b7970fdff8617187bb9fffdff 5ae4df3edbd5d35e5b4f09020db03eab 1e031dda2fbe03d1792170a0f3009cee")
    assert fc.aes128_cbc_frame_encrypt(key, cbc_iv, plain) == cbc_answer
    assert fc.aes128_ctr_crypt(key, ctr_iv, plain) == ctr_answer
    for cut in range(65):
        ctx = fc.AES128CTR(key, ctr_iv)
        assert ctx.update(plain[:cut])+ctx.update(b"")+ctx.update(plain[cut:]) == ctr_answer
        ctx = fc.AES128CTR(key, ctr_iv)
        assert ctx.update(ctr_answer[:cut])+ctx.update(ctr_answer[cut:]) == plain
    ctx = fc.AES128CTR(key, ctr_iv)
    assert b"".join(ctx.update(bytes([x])) for x in plain) == ctr_answer
    for n in range(81):
        p = (plain*2)[:n]
        result = fc.aes128_cbc_frame_encrypt(key, cbc_iv, p)
        assert len(result) == n and result[n & ~15:] == p[n & ~15:]
        assert fc.cbc_frame_candidate(key, cbc_iv, [p, p]) == [result, result]
    # 不同API有不同调用边界：CTR任意切分连续，CBC-frame每次调用重置。
    assert fc.aes128_cbc_frame_encrypt(key, cbc_iv, plain[:16])+fc.aes128_cbc_frame_encrypt(key, cbc_iv, plain[16:]) != cbc_answer
    for key_len in (0, 15, 17, 24, 32):
        for fun in (fc.aes128_ctr_crypt, fc.aes128_cbc_frame_encrypt):
            try: fun(bytes(key_len), cbc_iv, plain)
            except ValueError: pass
            else: raise AssertionError("wrong key size accepted")
    final = fc.AES128CTR(key, b"\xff"*16)
    final.update(b"x")
    final.update(b"y"*15)  # 最后密钥流块的未用字节仍可消费
    final.update(b"")
    try: final.update(b"z")
    except OverflowError: pass
    else: raise AssertionError("local exhaustion guard failed")
    print(f"       AES audit: slices={count}, anchors={len(anchors)}, carry=34, tail=81, NIST=2, CTR_splits=65")


if __name__ == "__main__":
    check()
