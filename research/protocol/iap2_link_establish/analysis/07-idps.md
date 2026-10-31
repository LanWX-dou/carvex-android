# analysis/07 — IDPS 与"传统 iAP"控制帧

对应任务书第 5 节第 7 项（Identification/IDPS 阶段的前置控制帧）。

本文件只覆盖**链路建立阶段**用到的三类控制帧：Detect、DetectNACK、RequestIdentify。它们不是 iAP2 帧，而是传统 iPod Accessory Protocol 帧，但走同一条传输、由同一个解析器分流。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2PacketCheckDetect` | `0x100102e20` | 判定"这是 Detect 帧" |
| `iAP2PacketCheckDetectNACK` | `0x100102ea0` | 判定"这是 DetectNACK 帧" |
| `iAP2PacketCheckRequestIdentify` | `0x100102f58` | 判定"这是 RequestIdentify 帧" |
| `iAP2LinkDeviceActionSendDetect` | `0x10002fac8` | Detect 阶段的链路动作 |
| `iAP2LinkDeviceActionSendResetSYNACK` | `0x10002f920` | 在收到 SYN 后重置并回 SYNACK |
| `iAP2LinkDeviceActionSendRST` | `0x10002fb54` | 发 RST 并复位 |
| `iAP2PacketParseBuffer` | `0x10000a5d0` | 首字节 `0x55` 分流 |

## 7.1 三种控制帧的字节形状

`A07.1`（已确认）`iAP2PacketCheckDetect` 逐字节匹配 `FF 55 02 00 EE 10`，但允许**首字节 0xFF 可缺省**（即 5 字节形式 `55 02 00 EE 10` 也接受）：

```
0x100102e28: ldrb  w9, [x11], #1        ; b0
0x100102e2c: sub   w10, w9, #0xff
0x100102e30: cmn   w10, #0xfe           ; b0 == 0xFF ?
0x100102e34: cset  w9, lo               ; w9 = (b0 == 0xFF)
0x100102e38: csel  x11, x8, x11, hs     ; 基址 = b0==0xFF ? &b[1] : &b[0]
0x100102e3c: ldrb  w11, [x11]
0x100102e40: cmp   w11, #0x55
0x100102e58: cmp   w11, #2              ; 长度
0x100102e68: cbnz  w11                  ; 命令 = 0x00
0x100102e7c: cmp   w10, #0xee           ; 结束符
0x100102e8c: cmp   w8, #0x10            ; 校验
0x100102e90: cset  w0, eq
```

`A07.2`（已确认）`iAP2PacketCheckDetectNACK` 匹配 `FF 55 04 00 02 04 EE 08`：

```
0x100102eb8: cmp  w10, #0x55
0x100102ed0: cmp  w10, #4               ; 长度 = 4
0x100102ee8: cbnz w10                   ; 命令 = 0x00
0x100102efc: cmp  w10, #2               ; 子命令 = 0x02
0x100102f14: cmp  w10, #4               ; 参数 = 0x04
0x100102f2c: cmp  w10, #0xee            ; 结束符
0x100102f44: cmp  w8, #8                ; 校验
```

`A07.3`（已确认）`iAP2PacketCheckRequestIdentify` 匹配 `FF 55 02 00 FE <cksum>`（只校验到第 4 字节，不校验尾部校验值）：

```
0x100102f88: cmp  w10, #2               ; 长度 = 2
0x100102fa0: cbnz w10                   ; 命令 = 0x00
0x100102fb4: cbz  w10, 0x100102fc0      ; 参数 = 0x00
0x100102fd0: cmp  w8, #0xfe             ; 子命令 = 0xFE
0x100102fd4: cset w0, eq
```

字节形状汇总：

| 帧 | 字节（十六进制） | 校验验证（规则见 `analysis/03` A03.15） |
|---|---|---|
| Detect | `FF 55 02 00 EE 10` | 校验范围 `02 00 EE`，和 `0xF0`，`-0xF0 & 0xFF = 0x10` ✔ |
| DetectNACK | `FF 55 04 00 02 04 EE 08` | 校验范围 `04 00 02 04 EE`，和 `0xF8`，`-0xF8 & 0xFF = 0x08` ✔ |
| RequestIdentify | `FF 55 02 00 FE 00` | 校验范围 `02 00 FE`，和 `0x100`，`-0x100 & 0xFF = 0x00`（按规则计算，固件未比较该字节） |

`A07.4`（已确认）Detect 帧在固件里是**常量**：VA `0x1001b3378` 起 6 字节即 `ff 55 02 00 ee 10`（`analysis/03` A03.16）。因此 Detect 的字节形状不是"从多个比较立即数拼出来的"，而是一个可引用的静态模板。

`A07.4b`（已确认）三类帧的尾部 `0xEE` 是**终止符**，长度字段 `len` 统计"命令 + 参数 + 终止符"的字节数：

- Detect：`len=2` → `00 EE`（命令 `0x00`，无参数）；
- DetectNACK：`len=4` → `00 02 04 EE`（命令 `0x00`，参数 `02 04`）。

`A07.4c`（已确认）三帧的校验值符合 `analysis/03` A03.15 的"排除同步字节"规则；而 iAP2 帧的头部校验包含同步字节 —— 两者共用 8/16 位两补数**算术**，但校验**范围**不同，实现时不可混用。

## 7.2 分流点

`A07.5`（已确认）解析器状态 0 见到 `0x55` 即进入传统帧分支（`0x10000abe4`），见到 `0xFF` 进入 iAP2 分支；两者共用同一个 `packet[0x40]` 头部缓冲：

```
0x10000a6a4: ldrb w8, [x25]
0x10000a6a8: cmp  w8, #0x55
0x10000a6ac: b.eq 0x10000abe4
```

三个 Check 函数都从 `packet[0x40]` 取字节，说明传统帧同样被写进"头部缓冲"，并以 `FF` 开头：

```
0x100102e20: ldr  x8, [x0, #0x40]
```

`A07.6`（未确认 / `OPEN-IDPS-2`）传统帧分支（`0x10000abe4` 起）的完整解析未通读；只确认它会走与 iAP2 帧不同的状态序列。

## 7.3 Detect 阶段的链路动作

`A07.7`（已确认）动作处理函数的第一个参数是 **FSM**，链路通过 `fsm[0x10]` 取得；所有链路动作都把事件置为 `0x1D`（29）：

```
; iAP2LinkDeviceActionSendDetect
0x10002fadc: cbz  x1, 0x10002fb50
0x10002fae0: mov  w8, #0x1d
0x10002fae4: strb w8, [x1]              ; *event = 0x1D
0x10002fae8: ldr  x19, [x0, #0x10]      ; link = fsm->owner
```

`A07.8`（已确认）`SendDetect` 的步骤：

1. `iAP2LinkResetSeqAck(link, 0, 1)`（`0x10002faf8`）：清序号基值、清 `[0xd4]` bit2/bit3、重建时间同步、并把校验类型恢复为 1；
2. 把调用方保存的 SYN 参数结构（`link[0x160]` 指向）复制到 `link+0x168`（`0x10002fb04`–`0x10002fb18`）；
3. 调 `iAP2LinkConnectedCB(link, 0)`（`0x10002fb24`）；
4. 尾部跳到 `iAP2LinkSendDetectCB`（`0x10019c124`，`w1=0`）。

`A07.9`（已确认）`SendResetSYNACK` 展示了"收到 SYN → 解析 → 协商"的完整局部流程：

```
0x10002f968: mov  x0, x20
0x10002f96c: bl   0x100034424           ; GetNewSeqNum
0x10002f970: mov  x21, x0
0x10002f978: mov  w1, #0
0x10002f97c: bl   0x100103970           ; ConnectedCB(link, 0)
0x10002f980: ldr  x22, [x20, #0x118]    ; 待响应的 SYN 包
0x10002f984: cbz  x22, 0x10002f9f0
0x10002f98c: bl   0x1000328b0           ; SetDefaultSYNParam(link+0x19a)
0x10002f99c: bl   0x1000346c8           ; ResetSeqAck(link, 1, 0)
0x10002f9a0: ...（复制调用方 SYN 参数到 link+0x168）
0x10002f9c4: mov  x0, x22
0x10002f9c8: bl   0x100006120           ; GetPayloadLen(syn)
0x10002f9d0: mov  x2, sp
0x10002f9d8: bl   0x100103230           ; ParseSYNData(payload, len, out)
0x10002f9dc: cbz  w0, 0x10002fa0c
0x10002f9e4: mov  x0, x20
0x10002f9e8: bl   0x100035154           ; CheckNegotiation(link, out)
0x10002fa0c: mov  x0, x20
0x10002fa10: bl   0x100034464           ; ResetSend(link)
0x10002fa14: ldrb w8, [x20, #0xd4]
0x10002fa18: tbnz w8, #2, 0x10002fa2c
0x10002fa1c: strb w21, [x20, #0xbe]     ; 首次：写入序号基值
0x10002fa20: orr  w8, w8, #4            ; 标记 bit2
```

要点：

- 收到 SYN 后**先解析、再协商**，协商结果由 `iAP2LinkCheckNegotiation` 处理（`analysis/04` A04.11）；
- 之后 `ResetSend` 清发送队列并复原 SYN 缺省；
- 首次（`[0xd4] bit2 == 0`）把新生成的序号写入 `link[0xbe]` 并置 bit2；后续沿用原值 —— 这就是 `GetNewSeqNum` 中 `(0x47 + link[0xbe]) & time` 的来源（`analysis/05` A05.2）。

`A07.10`（已确认）`SendRST` 的复位顺序与上面不同：先 `ResetSeqAck(link, 0, 0)`（不重建时间同步、不恢复校验类型），再 `SetDefaultSYNParam`，再复制调用方 SYN，然后比较 `link[0x1d0]` 与 `11`：

```
0x10002fc28: bl   0x1000346c8           ; ResetSeqAck(link,0,0)
0x10002fc30: bl   0x1000328b0           ; SetDefaultSYNParam(link+0x19a)
0x10002fc54: ldrb w8, [x20, #0xd4]
0x10002fc58: tbnz w8, #5, 0x10002fc74
0x10002fc5c: ldr  w8, [x20, #0x1d0]
0x10002fc60: cmp  w8, #0xb
```

`link[0x1d0]` 疑似重试计数（与 11 比较），未取得完整语义 → `OPEN-IDPS-3`。

## 7.4 IDPS 与消息阶段的交界

`A07.11`（已确认）IDPS 之后的识别阶段由**消息层**承载，消息 ID 见 `analysis/12`：

- Identification 特性表 3 条：`0x1D01`、`0x1D06`、`0x1D05`（`kiAP2MessageHandlerEntries_Identification`，`0x10021a7e0`）；
- 另有 `kiAP2IdentificationParamHandlerEntries_*` 共 9 张表，给"识别参数"分配 handler（见 `analysis/08`）。

`A07.12`（未确认 / `OPEN-IDPS-4`）"谁触发 `SendDetect`、Detect 的超时与重发次数、Detect 与 RequestIdentify 的先后"没有在链路层函数中取到证据：FSM 只规定"Detect 状态下收到事件 `0x17` 就发 Detect 并转 Idle"。这几步应由上层 `acc_protocolParser_iAP2_run` 的命令码驱动 → `OPEN-TX-2`。

## 7.5 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-IDPS-1` | RequestIdentify 帧尾校验字节的值 |
| `OPEN-IDPS-2` | 传统帧分支（`0x10000abe4`）的完整解析状态 |
| `OPEN-IDPS-3` | `link[0x1d0]`（与 11 比较）的语义 |
| `OPEN-IDPS-4` | Detect / RequestIdentify 的触发者与重试策略 |
