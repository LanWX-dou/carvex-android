# 05 RFCOMM 数据通道：接收拆帧、发送与信用流控

覆盖需求项：**（7）接收缓冲 / 拆帧 / 投递**、**（8）发送部分写 / 完成 / 失败**、并为（10）边界提供依据。

## 1. 目标

1. UIH 帧的完整校验顺序与长度字段解码规则。
2. 一帧数据最终交给"上一层"的**确切接口形态**（函数、参数）。
3. 发送侧的排队、部分写与完成回调。
4. 信用（credit）流控的两个计数器与溢出后果。

## 2. 结论

### C1 接收入口的六道校验 `CONFIRMED`

函数 `0x1003c59a0`（`OI_Rfcomm_ReceiveFrame`，日志 `OI_Rfcomm_ReceiveFrame invalid frame length=%d`）。

| 序 | 校验 | 失败行为 | 依据（C 行） |
|---|---|---|---|
| 1 | 会话存在（按 CID 查） | 日志 `No session found with CID %d` | 34–41 |
| 2 | 帧总长 ≥ 4 | 日志 `invalid frame length=%d` | 52–58 |
| 3 | 控制码分类：`ctrl & 0xEF` ∈ {0x2F,0x43,0x63,0x0F} 或 == 0xEF | 其他 → 静默丢 | 69–72 |
| 4 | FCS 正确 | 日志 `UIH FCS Error: %@` / `FCS Error: %@` | 74–91、357–373 |
| 5 | 地址 bit0（EA）= 1；C/R 与会话方向匹配 | 日志 `%! (%d)` | 99–139 |
| 6 | 会话状态 == 7；地址 < 0xF8；DLCI != 1 | 日志 `%! (%d)` | 204–223 |

FCS 校验使用 `FUN_1003c6be4(addr_byte, ctrl_byte, last_byte)`——可见 FCS 覆盖范围包含地址与控制字节（符合 TS 07.10）。

### C2 长度字段解码（1 或 2 字节，带 EA 位）`CONFIRMED`

| 依据 | 内容 |
|---|---|
| C 行 143 前后 | `if ((param_2[2] & 1) != 0)` → **1 字节长度**：`uVar14 = param_2[2] >> 1`，头长 `0x1003c5c80` 记为 3 |
| 否分支 | `uVar14 = CONCAT11(param_2[3], param_2[2]) >> 1` → **2 字节长度**，头长 4 |
| 依据（汇编） | 1 字节分支中 `ldrb/ubfx` 之后 `cmp w?, #3`；2 字节分支 `ldrh` 后 `lsr #1` |

即长度字段的 bit0 是 EA 扩展位，`0x01` 表示"长度 0"，`0x03` 表示"长度 1"，依此类推；两字节形式为 `(b0 | b1<<8) >> 1`（小端序拼装后右移）。

### C3 P/F 位置位时携带 1 字节信用 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| C 行 130 前后 | `if (ctrl bit4 set) { if (session[0x2c] != 1) 报错; credits = param_2[header]; header++; }` |
| 语义 | `session[0x2c] == 1` 表示"本会话启用基于信用的流控"；此位未启用时，对端在 P/F 帧里带信用会被判为错误 |
| 依据（汇编） | `0x1003c678c` `tbz w25,#4` → 无信用；`0x1003c679c` `ldrb w24,[x1,w9,uxtw]` → 信用 = 帧[头长]；`0x1003c67a0` `add w9,w9,#1` → 头长 +1 |

### C3.1 信用字节的位置与计数方式（汇编逐字节核对，2026-10 补充）

`0x1003c6764`–`0x1003c67b8` 原始字节的反汇编（机器码即固件字节，可直接复核）：

| 地址 | 机器码 | 指令 | 含义 |
|---|---|---|---|
| `0x1003c6764` | `29084039` | `ldrb w9, [x1, #2]` | 读第 1 个长度字节 |
| `0x1003c6768` | `c9000037` | `tbnz w9, #0, 0x1003c6780` | EA=1 → 单字节长度 |
| `0x1003c676c` | `2a0c4039` | `ldrb w10, [x1, #3]` | 读第 2 个长度字节 |
| `0x1003c6770` | `29210a2a` | `orr w9, w9, w10, lsl #8` | 小端拼装 |
| `0x1003c6774` | `333d0153` | `ubfx w19, w9, #1, #0xf` | 长度字段 = 拼装值 >> 1 |
| `0x1003c6778` | `89008052` | `mov w9, #4` | 双字节长度 → 头长 4 |
| `0x1003c6780` | `337d0153` | `lsr w19, w9, #1` | 单字节长度 = 字节 >> 1 |
| `0x1003c6784` | `69008052` | `mov w9, #3` | 单字节长度 → 头长 3 |
| `0x1003c6788` | `39044039` | `ldrb w25, [x1, #1]` | 读 Control 字节 |
| `0x1003c678c` | `f9002036` | `tbz w25, #4, 0x1003c67a8` | P/F=0 → 跳去"无信用" |
| `0x1003c6790` | `8ab24039` | `ldrb w10, [x20, #0x2c]` | 读会话 credit-enabled |
| `0x1003c6794` | `5f050071` | `cmp w10, #1` | 必须是 1 |
| `0x1003c6798` | `81060054` | `b.ne 0x1003c6868` | 否则按非法帧处理 |
| `0x1003c679c` | `38486938` | `ldrb w24, [x1, w9, uxtw]` | **信用 = 帧[头长]**（紧随长度字段） |
| `0x1003c67a0` | `29050011` | `add w9, w9, #1` | **有信用时头长 +1** |
| `0x1003c67a4` | `02000014` | `b 0x1003c67ac` | |
| `0x1003c67a8` | `18008052` | `mov w24, #0` | 无信用 → 信用数 0 |
| `0x1003c67ac` | `6a02090b` | `add w10, w19, w9` | 长度字段 + 头长 |
| `0x1003c67b0` | `4a050011` | `add w10, w10, #1` | 再 +1（FCS） |
| `0x1003c67b4` | `5f01026b` | `cmp w10, w2` | 与传入的总长比较 |
| `0x1003c67b8` | `41030054` | `b.ne 0x1003c6820` | 不等 → 拒帧 |

复现：

```
python3 -c "from capstone import *; f=open('research/protocol/bluetooth_rfcomm/source/firmware/bluetoothd','rb').read(); \
 [print(hex(i.address), i.bytes.hex(), i.mnemonic, i.op_str) for i in \
  Cs(CS_ARCH_ARM64,CS_MODE_ARM).disasm(f[0x3c6764:0x3c67bc],0x1003c6764)]"
```

结论（与 `runtime/captures/2026-10-rfcomm-pklg-reanalysis.md` §8 的线上观测完全一致）：

1. 信用字节位于**长度字段之后、用户数据之前**，是**头部**的一部分；
2. 信用字节**不计入长度字段**——长度字段 == 用户数据长度；
3. 一帧总长 == `长度字段 + 头长(3/4，有信用时 4/5) + 1(FCS)`，多一字节少一字节都拒收；
4. P/F=1 而会话未启用信用流控 → 直接判非法帧。

> **切片边界说明（`OPEN-BASE-3` 已关闭）**：`source/asm/bluetoothd/f_1003c59a0.s` 现在按
> **Ghidra 反编译体**导出为 `0x1003c59a0..0x1003c6b60`（4544 字节，1136 条指令），
> 与同名 `.ghidra.c` 的范围对齐，本节的指令已包含在切片内，可直接在同一文件内核对。
> 该区间内 `LC_FUNCTION_STARTS` 另有 5 个函数起点（`0x1003c5c70`/`0x1003c5e80`/`0x1003c6180`/
> `0x1003c63f8`/`0x1003c6648`），Ghidra 把整段识别为一个函数；索引里用 `slice_end` 记录切片终点、
> `end` 保留链接器边界，差异记在 `analysis/09` §5.1。

### C4 帧长必须精确匹配 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| C 行 187 | `if (uVar14 + uVar13 + 1 != param_3)` → 报错返回 |

`uVar14` = 信息长度，`uVar13` = 头部长度（3 或 4，含信用字节），`+1` = FCS。**多一字节或少一字节都直接丢弃**，不做容错，不留残余。

### C5 数据投递给上层的接口形态 `CONFIRMED（关键）`

C 行 348–349（`LAB_1003c6a48` 之后）：

```c
(**(code **)(*(long *)(dlci + 0x28) + 8))(*(undefined2 *)(dlci + 8), param_2, uVar14);
```

含义：

- `dlci + 0x28` 是一个**回调块指针**（由 `OI_RFCOMM_Connect` 的 `param_2` 或服务注册项复制而来，见 `04` C4/C7）。
- 取该块第 2 个函数指针（`+8`）调用。
- 参数为 `(uint16 DLCI 号, uint8* 数据, uint32 长度)`。

**这是"蓝牙 → 上层"的协议边界**：RFCOMM 每交付一帧 UIH，就调用一次该回调，数据指针指向该帧信息字段，长度等于该帧信息长度。RFCOMM 层**不做跨帧重组、不做流式拼接**，也不解析 payload——以上全部属于上层（见 `07`）。

### C6 信用流控的两个计数器 `CONFIRMED`

| 字段 | 语义 | 依据 |
|---|---|---|
| `dlci[0x0e]` | 己方已授予对端、尚未被消耗的信用（byte） | C 行 278、293、334 |
| `dlci[0x12]` | 对端授予己方、可用于发送的信用（uint16） | C 行 255、271–272 |

收到数据帧时（C 行 277–295）：

```
if (info_len != 0) {
    if (dlci[0x0e] == 0) log("Received data when remote credits = 0!");   // 仅记录，仍交付
    else dlci[0x0e] -= 1;
    goto 交付;
}
```

收到带 P/F 的信用授予时（C 行 253–276）：

```
if (P/F && credits != 0) {
    if ((dlci[0x12] ^ 0xFFFF) <= credits) {         // 相加会溢出 16 位
        FUN_1003c31b4(dlci_number, 0x39A);          // 状态 922
        return;
    }
    dlci[0x12] += credits;
    if (credits == dlci[0x12]) FUN_1003c50a8();     // 首次授予 → 唤醒发送
}
```

主动补充信用（C 行 333–342）：当 `dlci[0x0e] <= 全局阈值（0x100cadd68+2 字节）` 时，按 `dlci[0xa2]`/`dlci[0xa3]` 计算补发数量并调用 `FUN_1003c5030(dlci, count)`。

`0x39A` = 922（信用溢出）。

### C7 发送：会话级队列 + 完成回调 `CONFIRMED`

函数 `0x1003c3c20`（RFCOMM 写完成回调），日志 `RFCOMM Write failed %!`、`RFCOMM session has gone away - freeing orphaned MBUF %lx`、`Write failed`。

| 依据 | 内容 |
|---|---|
| C 行 27–40 | `param_4`（状态）非 0 → 日志 `RFCOMM Write failed %!` |
| C 行 44–60 | 会话已销毁 → 日志 `RFCOMM session has gone away - freeing orphaned MBUF %lx`，释放 MBUF |
| C 行 61–65 | 断言 `session[0x48] == mbuf`，随后清零并释放 MBUF |
| C 行 66–67 | `cVar8 = session[0x50]`（DLCI 索引）、`cVar1 = session[0x51]` |
| C 行 113–122 | 若会话发送队列（`session+0x38`，双向链表）非空：`FUN_1003d8540()` 出队，`FUN_1000c00c4(write_fn, session_cid, 0, mbuf, 0)` **把下一块写入内核通道**，成功后更新 `session[0x50]/[0x51]/[0x48]` |
| C 行 124–137 | 入队失败 → 日志 `Write failed` |
| C 行 170–177 | 完成后调用 `(**(code **)(dlci + 0x50))(dlci+8, mbuf, status)` → 写完成回调交还上层 |
| C 行 140–167 | 无 DLCI 上下文的收尾路径（DISC/DM 的延迟处理） |

即：**每个会话维护一条 MBUF 发送队列，逐块串行发出；每块完成才发下一块**。这就是"部分写"的实际形态——不是把一个大缓冲区截断重发，而是由上层提供多个 MBUF 分块，协议栈按块推进队列。

### C8 发送数据来自内核通道（socket/pipe），单块上限 0xA0A `CONFIRMED`

函数 `0x1000eb4e8`，日志：

- `MAX buffer size for the RFCOMM Channel is %d getWriteBufferUsed=%d`
- `MAX buffer size for the L2CAP Channel is %d getWriteBufferUsed=%d`
- `Failed to transmit data from socket on pipe 0x%04x with result %u`

| 依据 | 内容 |
|---|---|
| C 行 72 | `_bzero(auStack_a7a, 0xa0a)` → 栈上暂存缓冲 **2570 字节** |
| C 行 87–90 | `if (0xa09 < uVar15) uVar15 = 0xa0a;` → 单次最多取 2570 字节 |
| C 行 83–85 | `iVar19 = channel_type`：1 = L2CAP、2 = RFCOMM，分别走不同日志与通道 |
| C 行 406–413 | `_os_channel_advance_slot(fd, bytes)` 推进读位置；`_os_channel_available_slot_count()`；`_os_channel_sync(fd, 1)` |

含义：ACL/RFCOMM 的数据通路是 `os_channel`（内核管道），**上层与协议栈之间通过文件描述符传数据**，每次最多 2570 字节；只有发送成功后才 `advance_slot` 前进，因此未发送的部分自然留在管道里等待下次——这就是"部分写"在内核通道层的实现。

### C9 上层的可见参数：`kCBMsgArgMTU` 实为帧长 `CONFIRMED`

`0x10040c934`（连接完成通知），日志原文：

```
RFCOMM Channel connected: result: 0x%x, rfcommChannelID: 0x%x, frameSize: 0x%x, link handle: 0x%x, incoming?: %d, sock: 0x%x
```

XPC 键设置（C 行 62–83）：

| 键 | 值来源 |
|---|---|
| `kCBMsgArgDeviceUUID` | 设备 UUID（16 字节） |
| `kCBMsgArgResult` | `param_3` |
| `kCBMsgArgRFCOMMChannelID` | `param_4` |
| `kCBMsgArgMTU` | `param_5` ← 日志里叫 `frameSize` |
| `kCBMsgArgIsIncoming` | `param_7` |
| `kCBMsgArgSocket` | `param_8`（**文件描述符**，`_xpc_dictionary_set_fd`） |
| `kCBMsgArgServiceUUID` | 该通道对应的服务 UUID（来自 SDP 解析结果） |

**因此上层看到的"MTU"是 RFCOMM 的 N1（最大信息字段长度），不是 L2CAP MTU。** 平台实现若把该值当 L2CAP MTU 使用，会低估可用载荷。

## 3. 对实现的约束（进入 spec）

1. 收帧必须做"总长 == 头 + 信息 + 1"的精确校验，禁止容错吞字节。
2. 长度字段按 EA 位解码，`0x01` 表示长度 0。
3. 每帧独立投递，回调参数为 `(DLCI, 数据, 长度)`；不得在 RFCOMM 层假设消息边界之外的分片。
4. 信用流控需两个独立计数器，且发送信用累加必须做 16 位溢出检查。
5. 发送必须串行排队，一块完成再发下一块；单块上限 2570 字节（本实现）。
6. 上层拿到的 `kCBMsgArgMTU` 应解释为最大帧长 N1。

## 4. 未决

| 编号 | 内容 | 原因 |
|---|---|---|
| `OPEN-RF-6` | `FUN_1003c4edc`（`Save received packet failed in Receive_UIH`）的触发条件与"保存"语义 | 该分支在"信息长度为 0"路径，可能是空帧/信用帧的暂存；未展开 |
| `OPEN-RF-7` | 补充信用的数量计算（`dlci[0xa2]` / `[0xa3]`） | 只看到公式骨架，未见初值来源 |
| `OPEN-RF-8` | `FUN_1003c5030` / `FUN_1003c50a8` 发出的信用帧格式 | 两个函数未纳入抽样 |
| `OPEN-RF-9` | TF_CON（流量控制开）与 TF_COFF（流量控制关）在接收侧的处理 | 分发函数 `0x1003c73f0` 的命令→分支映射未解出（见 `OPEN-RF-5`） |
| `OPEN-RF-10` | 会话[0x38] 队列与 os_channel 队列的关系（是否两级缓冲） | 两处独立的"下一块"逻辑，未证明是同一队列 |
