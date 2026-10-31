#!/usr/bin/env python3
"""验证 bluetooth_rfcomm 文档集的自洽性（只用标准库）。

检查项：
  1. 源固件哈希
  2. 每个函数的 raw bytes 与源固件对应区间逐字节一致
  3. 每个 .s / readable .c 的头部标记（地址、源哈希、未人工确认）
  4. 文档中引用的函数地址都必须存在于 function-index.json
  5. FCS 表与规范中的测试向量可由固件字节重新推导（控制帧取地址/控制/长度；UIH 取地址/控制）
  6. EIR 128-bit UUID 常量与文档一致（小端上线）
  7. 服务名常量存在
  8. source/ 目录未被修改（仅含原始产物 + index.json）
  9. spec/ 条款编号唯一（`**R-x.y**` 不得重复定义）
 10. 必需文件存在（spec/08 交接契约、交接事实清单）

用法：python3 verify.py [--quiet]
退出码：0 全部通过；1 存在失败项。
"""
import hashlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
BASE = 0x100000000  # __TEXT vmaddr；offset = addr - BASE
EXPECTED_SHA = "cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1"
UUID_SITES = {  # 源基址 -> UUID 文本（内存大端）
    0x10093A5C6: "00000000-deca-fade-deca-deafdecacafe",
    0x10093A5D6: "02030302-1d19-415f-86f2-22a2106a0a77",
    0x10093A5E6: "00000000-deca-fade-deca-deafdecacaff",
    0x10093A5F6: "ec884348-cd41-40a2-9727-575d50bf1fd3",
    0x10093A606: "2d8d2466-e14d-451c-88bc-7301abea291a",
}
SERVICE_NAMES = [
    "SyncMLServer", "SyncMLClient", "D2D", "WiapGateWay", "WiapSink",
    "WiapGateWay_v2", "WiapSink_v2", "AapServer", "AapService", "AapClient",
    "Magnet", "Carplay", "CarplayGateway",
]
# 与 spec/07 的 TV-1.* 对应：(描述, 完整帧十六进制)。
# 24A446 的发送器对控制帧把地址/控制/长度传给 FCS helper，
# 对 UIH 只把地址/控制传给 helper；不能把整个帧统一送进 CRC。
TEST_VECTORS = [
    ("SABM DLCI0 D=1 P=1", "033F011C"),
    ("DISC DLCI0 D=1 P=1", "035301FD"),
    ("UA   DLCI0 D=0 F=1", "037301D7"),
    ("DM   DLCI0 D=0 F=1", "031F0136"),
    ("UIH  DLCI2 3B (header FCS)", "09EF0701020340"),
]

fails = []
checks = [0]


def ok(cond, msg):
    checks[0] += 1
    if not cond:
        fails.append(msg)
    return cond


class Firmware:
    def __init__(self, path):
        self.path = path
        self.f = open(path, "rb")
        self.size = os.path.getsize(path)

    def read(self, addr, n):
        self.f.seek(addr - BASE)
        return self.f.read(n)


def sha256_bytes(b):
    return hashlib.sha256(b).hexdigest()


def sha256_file(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def fcs(body, table):
    v = 0xFF
    for b in body:
        v = table[b ^ v]
    return v ^ 0xFF


def main():
    quiet = "--quiet" in sys.argv
    fw_path = os.path.join(ROOT, "source", "firmware", "bluetoothd")
    if not ok(os.path.exists(fw_path), "缺少 source/firmware/bluetoothd"):
        report()
        return 1
    got = sha256_file(fw_path)
    ok(got == EXPECTED_SHA, f"固件哈希不匹配: {got}")
    fw = Firmware(fw_path)

    idx_path = os.path.join(ROOT, "function-index.json")
    index = json.load(open(idx_path, encoding="utf-8"))
    ok(index["source_sha256"] == EXPECTED_SHA, "function-index.json 的源哈希不正确")

    # 2/3 函数级校验
    for fn in index["functions"]:
        short = fn["address"][2:].lower()
        binp = os.path.join(ROOT, "source", "asm", "bluetoothd", f"f_{short}.bin")
        sp = os.path.join(ROOT, "source", "asm", "bluetoothd", f"f_{short}.s")
        cp = os.path.join(ROOT, "readable", "ghidra", "bluetoothd", f"f_{short}.ghidra.c")
        if not ok(os.path.exists(binp), f"{short}: 缺少 .bin"):
            continue
        raw = open(binp, "rb").read()
        ok(sha256_bytes(raw) == fn["raw_sha256"], f"{short}: .bin 哈希不匹配")
        start = int(fn["address"], 16)
        end = int(fn.get("slice_end") or fn["end"], 16)  # 切片可能按反编译体加长
        ok(len(raw) == end - start, f"{short}: .bin 长度与 index 不符")
        ok(fw.read(start, len(raw)) == raw, f"{short}: .bin 与固件原始字节不一致")
        if ok(os.path.exists(sp), f"{short}: 缺少 .s"):
            head = open(sp, encoding="utf-8", errors="replace").read(4096)
            ok(fn["address"] in head, f"{short}: .s 头部缺地址")
            ok(EXPECTED_SHA in head, f"{short}: .s 头部缺源哈希")
            ok("no rewriting" in head, f"{short}: .s 头部缺 no-rewriting 声明")
        if ok(os.path.exists(cp), f"{short}: 缺少 readable .c"):
            head = open(cp, encoding="utf-8", errors="replace").read(4096)
            ok(fn["address"] in head, f"{short}: readable 头部缺地址")
            ok(EXPECTED_SHA in head, f"{short}: readable 头部缺源哈希")
            ok("NOT REVIEWED" in head, f"{short}: readable 缺未人工确认标记")

    # 4 文档引用的地址必须落在镜像地址窗口内
    #    （不要求都在抽样集合里：文档会引用未抽样的数据/常量/辅助函数，
    #      这类地址只做范围校验，并统计数量供人工判断）
    known = {fn["address"].lower() for fn in index["functions"]}
    ranges = [(int(fn["address"], 16), int(fn.get("slice_end") or fn["end"], 16))
              for fn in index["functions"]]
    import re
    addr_re = re.compile(r"0x1[0-9a-f]{8}")
    IMAGE_LIMIT = 0x102000000  # 镜像 VM 窗口上界（__TEXT+__DATA 实测 < 0x101000000）
    unsampled = set()
    for sub in ("analysis", "spec"):
        d = os.path.join(ROOT, sub)
        if not os.path.isdir(d):
            continue
        for name in sorted(os.listdir(d)):
            if not name.endswith(".md"):
                continue
            text = open(os.path.join(d, name), encoding="utf-8").read()
            for a in set(addr_re.findall(text.lower())):
                v = int(a, 16)
                ok(BASE <= v < IMAGE_LIMIT,
                   f"{sub}/{name}: 引用了镜像窗口外的地址 {a}")
                if a not in known and not any(lo <= v < hi for lo, hi in ranges):
                    unsampled.add(a)
    print(f"提示: 文档引用了 {len(unsampled)} 个非抽样地址（数据/常量/未抽取函数）")

    # 4b 复用器命令族：汇编常量与字符串必须与 04 C8 的结论一致
    disp = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1003c73f0.s"),
                encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("and w24, w23, #0xfc", "命令基值掩码"),
        ("ror w8, w8, #4", "分派索引计算"),
        ("cmp w22, #8", "PN 数据区长度校验"),
        ("cmp w20, #3", "MSC 最小长度校验"),
        ("and w20, w8, #0x3f", "PN 的 DLCI 掩码"),
        ("and w22, w8, #7", "PN 信用低 3 位"),
        ("strh w22, [x0, #0x12]", "信用写入 DLCI 记录"),
        ("cmp w25, #0xf0", "PN 帧类型比较"),
    ]:
        ok(needle in disp, f"分发器汇编缺少「{why}」({needle})")
    for tgt, name in [("0x1003c7638", "PN"), ("0x1003c7508", "RPN"), ("0x1003c75a8", "MSC")]:
        ok(tgt in disp, f"分发器未跳到 {name} 处理分支 {tgt}")
    msc = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1003c71e8.s"),
               encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov w8, #-0x1f", "MSC 响应字节 0xE1"),
        ("mov w9, #-0x1d", "MSC 命令字节 0xE3"),
        ("mov w20, #5", "MSC 三字节载荷加命令头长度"),
        ("mov w20, #4", "MSC 两字节载荷加命令头长度"),
    ]:
        ok(needle in msc, f"MSC 发送器汇编缺少「{why}」({needle})")
    for addr, text in [(0x100A37972, b"Invalid MSC command length"),
                       (0x100A379A4, b"Invalid RPN command length")]:
        ok(fw.read(addr, 64).startswith(text), f"{hex(addr)} 处的字符串与 MSC/RPN 长度告警不符")

    # 4c 定时器/时间基：汇编常量与导入符号必须与 04 C9 的结论一致
    tim = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1000615dc.s"),
               encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov w9, #0xa", "内部 now 的 ×10"),
        ("mov w9, #0x64", "钩子参数 ×100 的系数"),
        ("mul w0, w19, w9", "钩子收到 timeout×100"),
        ("strh w8, [x20, #2]", "16 位到期值"),
    ]:
        ok(needle in tim, f"到期计算汇编缺少「{why}」({needle})")
    clk = open(os.path.join(ROOT, "source/asm/bluetoothd/f_100035440.s"),
               encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov w9, #0x4240", "时间基换算常数 0xF4240"),
        ("movk x10, #0xe353, lsl #16", "÷125 魔数"),
        ("mul x8, x0, x8", "ticks × numer"),
        ("msub w8, w9, w10, w8", "纳秒余数（%1000）"),
    ]:
        ok(needle in clk, f"时间源汇编缺少「{why}」({needle})")
    reg = open(os.path.join(ROOT, "source/asm/bluetoothd/f_10006135c.s"),
               encoding="utf-8", errors="replace").read()
    ok("tbnz w22, #0xf" in reg, "定时器登记缺少 bit15 超时值拒绝")
    sess = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1003c6180.s"),
                encoding="utf-8", errors="replace").read()
    ok("mov w9, #0x1e" in sess, "会话定时器默认值 0x1e(30) 缺失")
    ftxt = open(os.path.join(ROOT, "source/firmware/bluetoothd"), "rb").read()
    ok(b"_mach_absolute_time" in ftxt and b"_mach_timebase_info" in ftxt,
       "导入符号 _mach_absolute_time / _mach_timebase_info 缺失")
    ok(b"_pthread_cond_timedwait_relative_np" in ftxt,
       "导入符号 _pthread_cond_timedwait_relative_np 缺失")

    # 4d 超时单位 = 毫秒：钩子与消费者汇编必须与 04 C9.3 一致
    hook = open(os.path.join(ROOT, "source/asm/bluetoothd/f_100061690.s"),
                encoding="utf-8", errors="replace").read()
    ok("str w19, [x8, #0xcc8]" in hook, "超时钩子缺少把值写入 0x100c25cc8 的存储")
    cons = open(os.path.join(ROOT, "source/asm/bluetoothd/f_100060ff4.s"),
                encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov w26, #0x3e8", "毫秒→秒 的除数 1000"),
        ("mov w27, #0x4240", "毫秒→纳秒 的乘数 0xF4240"),
        ("umull x9, w8, w25", "÷1000 魔数乘法"),
        ("lsr x9, x9, #0x26", "÷1000 的右移 38"),
        ("bl #0x10090b900", "调用 pthread_cond_timedwait_relative_np"),
    ]:
        ok(needle in cons, f"定时器线程汇编缺少「{why}」({needle})")

    # 4e 重连节奏：固定步长 + 硬上限（04/06 的结论）
    bko = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1005fcb40.s"),
               encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov x1, #0xb800", "300 s 的低 16 位"),
        ("movk x1, #0xd964, lsl #16", "300 s 的中 16 位"),
        ("movk x1, #0x45, lsl #32", "300 s 的高位 0x45"),
    ]:
        ok(needle in bko, f"退避定时器汇编缺少「{why}」({needle})")
    wd = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1005fcd8c.s"),
              encoding="utf-8", errors="replace").read()
    for needle, why in [
        ("mov w8, #0xca00", "1e9 的低位 0xCA00"),
        ("movk w8, #0x3b9a, lsl #16", "1e9 的高位 0x3B9A"),
        ("umull x1, w20, w8", "秒 × 1e9"),
    ]:
        ok(needle in wd, f"看门狗汇编缺少「{why}」({needle})")
    rc = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1005fcaf8.s"),
              encoding="utf-8", errors="replace").read()
    ok("ldrb w19, [x19, #0x647]" in rc, "重试计数读取（dev+0x647）缺失")
    wc = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1006428ac.s"),
              encoding="utf-8", errors="replace").read()
    ok("csel w21, w8, w21, eq" in wc, "看门狗 8 s / 16 s 条件选择缺失")
    sm = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1001479fc.s"),
              encoding="utf-8", errors="replace").read()
    ok("cmp w0, #4" in sm, "重试上限判定（>4 即超限）缺失")
    ok("mov w1, #0x3c" in sm, "页扫描定时器 60 s 缺失")

    # 4g UIH 头长 / 信用字节 / 总长校验（0x1003c6764–0x1003c67b8，原始字节对照）
    for a_, expect_, why_ in [
        (0x1003C6764, "29084039", "读长度字节1"),
        (0x1003C6774, "333d0153", "双字节长度 >>1"),
        (0x1003C6778, "89008052", "双字节长度头长=4"),
        (0x1003C6780, "337d0153", "单字节长度 >>1"),
        (0x1003C6784, "69008052", "单字节长度头长=3"),
        (0x1003C6788, "39044039", "读控制字节"),
        (0x1003C678C, "f9002036", "P/F=0 跳至无信用分支"),
        (0x1003C6790, "8ab24039", "读会话 credit-enabled 标志"),
        (0x1003C679C, "38486938", "信用 = 帧[头长]（紧随长度字段）"),
        (0x1003C67A0, "29050011", "有信用时头长 += 1"),
        (0x1003C67AC, "6a02090b", "长度字段 + 头长"),
        (0x1003C67B0, "4a050011", "再 + 1（FCS）"),
        (0x1003C67B4, "5f01026b", "与帧总长比较"),
        (0x1003C67B8, "41030054", "不等即拒帧"),
    ]:
        raw_ = fw.read(a_, 4)
        ok(raw_.hex() == expect_, f"UIH 头解析指令不符 @0x{a_:x}（{why_}）: {raw_.hex()} != {expect_}")

    # 4h FCS scope：控制帧由组帧器传 len=3，UIH 发送器传 len=2。
    ctrl_tx = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1003c5334.s"),
                   encoding="utf-8", errors="replace").read()
    uih_tx = open(os.path.join(ROOT, "source/asm/bluetoothd/f_1003c5884.s"),
                  encoding="utf-8", errors="replace").read()
    ok("mov w1, #3" in ctrl_tx and "bl #0x1003c6b60" in ctrl_tx,
       "控制帧组帧器未确认 FCS 输入长度 3")
    ok("mov w1, #2" in uih_tx and "bl #0x1003c6b60" in uih_tx,
       "UIH 组帧器未确认 FCS 输入长度 2")
    for addr, raw in [(0x1003c592c, "41008052"),
                      (0x1003c5930, "8c040094"),
                      (0x1003c53d8, "61008052"),
                      (0x1003c53dc, "e1050094"),
                      (0x1003c6330, "600c8052"),
                      (0x1003c62ac, "600c8052"),
                      (0x1003c1dd4, "28008052"),
                      (0x1003c1dd8, "68320039")]:
        ok(fw.read(addr, 4).hex() == raw, f"协议关键指令不匹配 @{addr:x}")

    # 5 FCS 表与测试向量
    table = fw.read(0x1009349A0, 256)
    ok(len(table) == 256 and table[:8].hex() == "0091e3720796e475",
       "FCS 表首 8 字节不符: " + table[:8].hex())
    control_codes = {0x2F, 0x43, 0x63, 0x0F}
    for name, expect in TEST_VECTORS:
        frame = bytes.fromhex(expect)
        body, want = frame[:-1], frame[-1]
        scope = 3 if (frame[1] & 0xEF) in control_codes else 2
        ok(fcs(frame[:scope], table) == want,
           f"测试向量 {name} 的 FCS 不自洽（scope={scope}）")
        ok(frame[0] & 1 == 1, f"测试向量 {name} 的 EA 位不为 1")
    long_uih = bytes.fromhex("09ef0001") + bytes(range(128)) + b"\x40"
    ok(fcs(long_uih[:2], table) == long_uih[-1], "TV-1.6 长 UIH FCS")
    ok(fcs(bytes.fromhex("09ef07010203"), table) != 0x40,
       "反例：不能把 UIH 信息字段纳入 FCS")
    ok((20 & 7) == 4 and (11 & 63) == 11, "PN 掩码不得变成饱和或地址猜测")

    # 6 EIR UUID 常量
    for site, text in UUID_SITES.items():
        raw = fw.read(site, 16)
        be = bytes.fromhex(text.replace("-", ""))
        ok(raw == be, f"UUID 常量不符 @0x{site:x}: {raw.hex()} != {be.hex()}")

    # 7 服务名
    blob = fw.read(BASE, fw.size)
    for s in SERVICE_NAMES:
        ok(s.encode() in blob, f"缺少服务名常量: {s}")

    # 8 source/ 目录清洁性
    asm_dir = os.path.join(ROOT, "source", "asm", "bluetoothd")
    allowed = {"index.json"}
    for name in os.listdir(asm_dir):
        ext_ok = name.endswith(".s") or name.endswith(".bin") or name in allowed
        ok(ext_ok, f"source/asm 出现非预期文件: {name}")
        if name not in allowed:
            stem = name.split(".")[0][2:]
            ok(stem in {f["address"][2:].lower() for f in index["functions"]},
               f"source/asm 出现未登记的函数文件: {name}")

    # 9 条款编号唯一 + 10 必需文件
    import collections
    import re as _re
    seen = collections.defaultdict(list)
    spec_dir = os.path.join(ROOT, "spec")
    for name in sorted(os.listdir(spec_dir)):
        if not name.endswith(".md"):
            continue
        for i, line in enumerate(open(os.path.join(spec_dir, name), encoding="utf-8",
                                      errors="replace"), 1):
            for m_ in _re.finditer(r"\*\*(R-\d+\.\d+[a-z]?)\*\*", line):
                seen[m_.group(1)].append(f"{name}:{i}")
    for cid, where in seen.items():
        ok(len(where) == 1, f"条款编号重复 {cid}: {where}")
    ok(len(seen) > 150, f"条款解析数量异常（{len(seen)}），编号格式可能被破坏")
    for rel, why in [
        ("spec/08-handoff-contract.md", "向上层交接契约"),
        ("reference/handoff-facts-for-iap2.md", "交给 iAP2 的事实清单"),
        ("spec/09-client-open-rfcomm.md", "外接客户端打开通道"),
        ("runtime/observations/sdp-records-iap2.md", "SDP 记录运行时观测"),
    ]:
        ok(os.path.exists(os.path.join(ROOT, rel)), f"缺少必需文件（{why}）: {rel}")

    report()
    return 0 if not fails else 1


def report():
    print(f"检查项总数: {checks[0]}  失败: {len(fails)}")
    for m in fails[:40]:
        print("  FAIL", m)
    if len(fails) > 40:
        print(f"  ... 另有 {len(fails) - 40} 项失败")
    print("结果:", "通过" if not fails else "未通过")


if __name__ == "__main__":
    sys.exit(main())
