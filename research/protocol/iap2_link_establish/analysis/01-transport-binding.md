# analysis/01 — 传输绑定

对应任务书第 5 节第 1 项：iAP2 链路从哪种传输取帧、回调如何注册、与蓝牙阶段出口如何对接。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `acc_protocolParser_iAP2_create` | `0x10017b5fc` | 创建协议解析器对象（0x18 字节） |
| `acc_protocolParser_iAP2_reset` | `0x10017b680` | 复位解析器 |
| `acc_protocolParser_iAP2_destroy` | `0x10017b6a8` | 销毁 |
| `acc_protocolParser_iAP2_run` | `0x1000cf5b8` | 解析器命令分发（11 个命令码） |
| `iAP2LinkRegisterEventCallback` | `0x100034f50` | 注册链路事件回调 |
| `iAP2LinkDataReadyCB` | `0x10019bfac` | 数据就绪回调 |
| `iAP2LinkSendPacketWaitCB` | `0x10019c120` | 发送完成回调（等待型） |
| `iAP2LinkConnectedCB` | `0x100103970` | 连接建立回调 |
| `__iAP2LinkDataSentOutCB` | `0x100008678` | 数据已发出回调 |
| `iAP2LinkSendPacketCB` | `0x100008a44` | 发送完成回调（普通） |

## 1.1 三层结构：link → runloop → transport

`A01.1`（已确认）链路对象不直接持有传输，而是通过运行循环中转：

```
; iAP2LinkRunLoopCreate：transport 存在 runloop+0x10
0x1000cae90: str  x1, [x7, #0x10]
0x1000cae94: mov  x1, x7            ; runloop 作为 LinkCreate 的 x1
0x1000cae9c: bl   0x100033fd0
```

```
; iAP2LinkCreate：x1 存到 link+0xb0
0x1000340a8: str  x26, [x19, #0xb0]
```

```
; iAP2LinkConnectedCB(link)：transport = link->[0xb0]->[0x10]
0x100103970: ldr  x8, [x0, #0xb0]
0x100103974: ldr  x0, [x8, #0x10]
0x100103978: b    0x1000311f4
```

`A01.2`（已确认）数据就绪回调同样经 `link[0xb0]` 取 transport：

```
; iAP2LinkDataReadyCB(link, buf, len, ?, session_id)
0x10019bfd4: ldr  x8, [x0, #0xb0]
0x10019bfd8: ldr  x21, [x8, #0x10]   ; transport
0x10019bfdc: mov  x1, x4
0x10019bfe0: bl   0x100032828        ; iAP2LinkGetSessionForService(link, x4)
0x10019bfe4: cbz  x0, 0x10019c108
0x10019c064: and  w3, w20, #0xffff
0x10019c068: mov  x0, x21
0x10019c06c: mov  x1, x22
0x10019c070: mov  x2, x19
0x10019c074: bl   0x10006b878        ; 投递到会话
```

**结论**：传输实现只需要向 runloop 提供 `transport` 对象，链路层通过 `link[0xb0]→[0x10]` 取回；运行循环每轮的 Attached/Detached 位即"传输就绪/断开"。

## 1.2 发送方向：回调 + 计时

`A01.3`（已确认）`__iAP2LinkSendPacketCommon` 是唯一的出口，它把帧交给两个"发送完成回调"之一，并按 ACK 位启动定时器：

```
; 发送计数与字节统计
0x100007950: ldr  w8, [x19, #0x20c]
0x100007954: add  w8, w8, #1
0x100007958: str  w8, [x19, #0x20c]
0x10000795c: ldrh w8, [x20, #0x36]
0x100007960: ldr  w9, [x19, #0x204]
0x100007964: add  w8, w9, w8
0x100007968: str  w8, [x19, #0x204]
```

```
; 控制位 bit6（ACK）置位时：把 link[0xbc] 写进 hdr[6]
0x10000796c: ldrb w8, [x23, #4]
0x100007970: tbz  w8, #6, 0x10000799c
0x100007974: ldrb w8, [x23, #6]
0x100007978: ldrb w9, [x19, #0xbc]
0x100007980: b.eq 0x10000798c
0x100007984: strb w9, [x23, #6]        ; hdr[6] = link[0xbc]
0x100007990: ldrb w8, [x19, #0xd4]
0x100007994: orr  w8, w8, #8
0x100007998: strb w8, [x19, #0xd4]
```

```
; 记录发送时刻、累计 RTT 差值
0x10000799c: bl   0x1000024e4           ; now_ms
0x1000079a4: ldr  w8, [x20, #0x30]      ; 上包时间戳
0x1000079a8: sub  w8, w0, w8
0x1000079ac: add  x9, x19, #0x254
0x1000079b0: ldr  d0, [x9]
0x1000079b4: movi v1.2s, #1
0x1000079b8: mov  v1.s[0], w8
0x1000079bc: add  v0.2s, v1.2s, v0.2s  ; {计数, 累计}
0x1000079c0: str  d0, [x9]
0x1000079c4: str  w0, [x20, #0x30]
```

```
; ACK 位 → 取消重传定时器；随后按参数选择完成回调
0x1000079d0: ldr  x0, [x19, #0xc8]
0x1000079d4: ldrb w1, [x19, #0xc2]
0x1000079d8: bl   0x1000066e0           ; iAP2TimeCancelTimer
0x1000079dc: mov  w8, #0xff
0x1000079e0: strb w8, [x19, #0xc2]
0x1000079ec: tbz  w21, #0, 0x100007a40
0x1000079f0: bl   0x10019c120           ; iAP2LinkSendPacketWaitCB
0x100007a40: bl   0x100008a44           ; iAP2LinkSendPacketCB
```

```
; 数据包且非 no-retransmit → 启动 ACK 定时，时长 = SYN 结构 +0x06
0x100007a44: add  x0, x19, #0x19a
0x100007a48: bl   0x100008590           ; iAP2LinkIsNoRetransmit
0x100007a50: tbnz w0, #0, 0x100007a70
0x100007a54: ldr  x0, [x19, #0xc8]
0x100007a58: ldrh w2, [x19, #0x1a0]     ; SYN[+0x06]
0x100007a5c: mov  w1, #0xc              ; 定时器 id = 0xC
0x100007a60: bl   0x100007ce8           ; iAP2TimeCallbackAfter
```

`A01.4`（已确认）`SYN[+0x06]` 就是 **ACK 定时器的超时时长**（定时器 id `0xC`），缺省 1000，单位与 `iAP2TimeGetCurTimeMs` 一致（毫秒）。这修正了 `analysis/04` 中该字段"未命名"的状态：现在是"语义已确认、合法性下限（>19）原因未确认"。

`A01.5`（已确认）`iAP2LinkSendPacketWaitCB`（`0x10019c120`）只是 `iAP2LinkSendPacketCB`（`0x100008a44`）的跳转；两个回调的差异在调用点参数，不在实现。

## 1.3 接收方向：解析器与"两种帧"

`A01.6`（已确认）接收缓冲的上层入口是 `acc_protocolParser_iAP2_run(parser, cmd, ctx)`，它按 `*(u32*)cmd[8]` 分派 11 个命令码：

```
0x1000cf5b8: ldr  w8, [x1]
0x1000cf5bc: cmp  w8, #4
0x1000cfc0: b.ne 0x1000cfd8c        ; cmd[0] != 4 → 其它分支
0x1000cf5ec: ldr  x24, [x1, #8]
0x1000cf5f0: ldr  w21, [x24]
0x1000cf5f4: cmp  w21, #0xa
0x1000cf5f8: b.hi 0x1000cf88c       ; 命令码 > 10 → 非法
0x1000cf614: ldrsw x16, [x17, x16, lsl #2]   ; 跳表 0x100018f4c
0x1000cf620: br   x16
```

`A01.7`（已确认）帧解析器在同一缓冲上分辨两种帧：iAP2 帧以 `FF 5A` 开始，传统 iAP 帧以 `FF 55` 开始：

```
; iAP2PacketParseBuffer 状态 0
0x10000a6a4: ldrb w8, [x25]
0x10000a6a8: cmp  w8, #0x55
0x10000a6ac: b.eq 0x10000abe4        ; → 传统 iAP 分支
0x10000a6b0: cmp  w8, #0xff
0x10000a6b4: b.ne 0x10000aca8        ; 其它 → 错误
```

两种帧的格式见 `analysis/03`（iAP2）与 `analysis/07`（传统 iAP，Detect/DetectNACK/RequestIdentify）。

## 1.4 与蓝牙阶段出口的对接

`A01.8`（已修订，`OPEN-TX-1`）蓝牙阶段确认的出口是 RFCOMM 数据回调 `(**(code**)(*(dlci+0x28)+8))(dlci[8], ptr, len)` 与 `os_channel` 文件描述符。本二进制中：

- 存在 `acc_protocolParser_iAP2_*` 这一层"协议解析器"（创建/复位/销毁/运行），其对象只有 0x18 字节，字段为 `{ptr, u32, u16, u8, u64, u16, u8}`（`0x10017b640`–`0x10017b658`）；
- 没有出现 `RFCOMM`/`dlci`/`kCBMsgArgSocket` 等蓝牙侧标识（字符串检索为 0，见 `runtime/` 记录）；
- `iAP2LinkDataReadyCB` 的调用者已定位为 `iAP2LinkActionHandleData`（`0x100032670`，调用点 `0x10003271c`），它位于**解析之后、交给会话之前**，属消费侧，不是传输适配层（见 `A15.6`）。

**修订说明**：本条旧版写"`iAP2LinkDataReadyCB` 的调用者是传输适配层"，与 `A15.6` 冲突；按字节证据改正。`OPEN-TX-1` 的问题随之变为：**谁调用 `acc_protocolParser_iAP2_run` / `iAP2PacketParseBuffer`**。

因此"RFCOMM 字节 → iAP2 解析器"的具体函数链**未取得直接证据**，`OPEN-TX-1` 保持。可以确认的是接口形状：适配层只需 (a) 在 attach 时置运行循环的 Attached 位，(b) 把收到的字节喂给 `iAP2PacketParseBuffer`，(c) 通过 `iAP2LinkSendPacketWaitCB`/`iAP2LinkSendPacketCB` 把帧写回传输。

## 1.5 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-TX-1` | 传输适配层（RFCOMM / `os_channel` / USB）到解析器的具体函数与注册点 |
| `OPEN-TX-2` | `acc_protocolParser_iAP2_run` 的 11 个命令码中与"打开/写入/关闭"的对应关系 |
| `OPEN-TX-3` | 运行循环 Attached 位的置位者（谁在传输就绪时置位） |
| `OPEN-TX-4` | `link[0xbc]`（写入 `hdr[6]` 的字节）的赋值来源 |
