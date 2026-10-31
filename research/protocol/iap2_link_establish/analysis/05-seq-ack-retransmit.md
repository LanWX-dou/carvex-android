# analysis/05 — 序号、确认与重传

对应任务书第 5 节第 5 项。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2LinkGetNewSeqNum` | `0x100034424` | 生成初始序号 |
| `iAP2PacketCalcSeqGap` | `0x1000084b8` | 8 位模差 |
| `__iAP2LinkComparePacketSeq` | `0x1000353f8` | 两包顺序比较（含窗口） |
| `iAP2PacketIsSeqACKd` | `0x10000b5c0` | 序号是否落在确认窗口内 |
| `iAP2LinkResetSeqAck` | `0x1000346c8` | 序号/确认复位 |
| `iAP2LinkResetSend` | `0x100034464` | 发送侧复位（含 SYN 参数复原） |
| `iAP2LinkActionHandleACK` | `0x10000bc04` | ACK 动作（发 FSM 事件 0x1D） |
| `iAP2LinkActionResendData` | `0x1000323f8` | 重传数据 |
| `iAP2LinkActionResendMissing` | `0x100031ef8` | 补发缺失（EAK） |
| `iAP2LinkDeviceActionHandleMaxRetries` | `0x100030054` | 重试上限处理 |
| `iAP2LinkIsNoRetransmit` | `0x100008590` | 无重传判定 |

## 5.1 序号空间：8 位、模 256

`A05.1`（已确认）序号占 1 字节（帧头偏移 5），比较用 8 位模差：

```
; iAP2PacketCalcSeqGap(seqA, seqB)
0x1000084b8: sub  w8, w1, w0
0x1000084bc: and  w0, w8, #0xff
```

序号字段的读取位置：

```
; __iAP2LinkComparePacketSeq(pktA**, pktB**)
0x100035410: ldr  x8, [x19, #0x40]     ; pktA->hdr
0x100035414: ldrb w0, [x8, #5]         ; 序号 = hdr[5]
0x10003541c: ldrb w1, [x8, #5]         ; pktB->hdr[5]
```

## 5.2 初始序号

`A05.2`（已确认）初始序号由毫秒时钟派生，可选加一个基值偏移：

```
; iAP2LinkGetNewSeqNum(link)
0x100034434: ldrb w8, [x0, #0xd4]
0x100034438: tbnz w8, #2, 0x100034444   ; bit2 置位 → 走带偏移分支
0x10003443c: bl   0x1000024e4           ; iAP2TimeGetCurTimeMs
0x100034444: ldrb w8, [x0, #0xbe]       ; 基值字节
0x100034448: add  w19, w8, #0x47        ; +0x47
0x10003444c: bl   0x1000024e4
0x100034450: and  w0, w19, w0           ; 与时钟低位相与
0x100034454: and  w0, w0, #0xff
```

即：

- `link[0xd4] bit2 == 0`：`seq0 = time_ms & 0xFF`；
- `link[0xd4] bit2 == 1`：`seq0 = (link[0xbe] + 0x47) & time_ms & 0xFF`。

`iAP2TimeGetCurTimeMs`（`0x1000024e4`）名字与实现共同表明时间单位为**毫秒**；`iAP2LinkResetSeqAck` 会把 `link[0xbe]` 清零（`0x1000346ec: strh wzr,[x19,#0xbe]`）。

## 5.3 确认窗口

`A05.3`（已确认）窗口大小为 `link[0x1a5]`（1 字节），比较函数在链路相同的条件下把超窗的差值变成负数：

```
; __iAP2LinkComparePacketSeq
0x100035420: bl   0x1000084b8          ; gap = CalcSeqGap(seqA, seqB)
0x100035424: ldr  x8, [x19]            ; pktA->link
0x100035428: ldr  x9, [x20]            ; pktB->link
0x10003542c: cmp  x8, x9
0x100035430: b.ne 0x100035460          ; 不同链路 → 断言/日志
0x100035438: cbz  w9, 0x100035450      ; gap == 0 → 返回 0
0x10003543c: ldrb w8, [x8, #0x1a5]     ; 窗口
0x100035440: orr  x10, x9, #0xffffffffffffff00
0x100035444: cmp  w9, w8
0x100035448: csel x0, x10, x9, hi      ; gap > 窗口 → 负数
```

`A05.3b`（已确认）窗口的**缺省值为 1**：`iAP2LinkCreate` 中 `mov w8,#-0xff00`（= `0xFFFF0100`）后 `str w8,[x19,#0x1a4]`，逐字节为 `[0x1a4]=0x00`、`[0x1a5]=0x01`、`[0x1a6]=0xFF`、`[0x1a7]=0xFF`；`Attached`/`Detached`/`ResetSend` 用同一常量复位（`0x100034aa4`、`0x100034c04`、`0x1000344dc`）。因此确认窗口默认为 1，且 `[0x1a6]`（最大接收包长）默认为 `0xFFFF`。

`A05.4`（已确认）"是否已确认"判定为窗口内包含：

```
; iAP2PacketIsSeqACKd(seq, ack, window)
0x10000b5c0: sub  w8, w1, w0           ; ack - seq
0x10000b5c4: cmp  w2, w8, uxtb
0x10000b5c8: cset w0, hs               ; window >= gap
```

## 5.4 发送侧复位

`A05.5`（已确认）`iAP2LinkResetSend` 清空 5 个发送链表、复原 SYN 缺省参数，再调用序号/确认复位：

```
; iAP2LinkResetSend(link)
0x100034484: bl   0x1000345d8
0x10003448c: add  x21, x19, #0x130
0x100034490: mov  w22, #5
0x100034494: ldr  x0, [x21, x20, lsl #3]  ; link->lists[i]（5 个）
0x1000344a8: bl   0x100099494             ; 清空
...
0x1000344b8: add  x8, x19, #0x19a          ; 复原 SYN 缺省
0x1000344c0: mov  w10, #0x3e8ffff
0x1000344c4: str  w10, [x9]
0x1000344c8: mov  w9, #0xa
0x1000344cc: strh w9, [x19, #0x1a2]
0x1000344d4: ldr  d0, [x9, #0x348]
0x1000344d8: str  s0, [x8]
0x1000344dc: mov  w8, #-0xff00
0x1000344e0: str  w8, [x19, #0x1a4]
0x1000344e4: mov  x0, x19
0x1000344e8: mov  w1, #1
0x1000344ec: mov  w2, #0
0x100034510: b    0x1000346c8              ; ResetSeqAck(link, 1, 0)
```

`A05.6`（已确认）`iAP2LinkResetSeqAck(link, w1, w2)`：

```
0x1000346e8: bl   0x1000345d8
0x1000346ec: strh wzr, [x19, #0xbe]    ; 序号基值 = 0
0x1000346f0: ldrb w8, [x19, #0xd4]
0x1000346f4: and  w8, w8, #0xfffffff3   ; 清 bit2、bit3
0x1000346f8: strb w8, [x19, #0xd4]
0x1000346fc: ldr  x0, [x19, #0x108]     ; 时间同步对象
0x100034700: bl   0x100083130           ; TimeSyncCleanup
0x100034704: ldr  x0, [x19, #0x108]
0x100034708: bl   0x10008305c           ; TimeSyncInit
0x100034710: cbz  w20, 0x10003472c      ; w2 == 0 → 跳过以下
0x100034714: str  xzr, [x19, #0x1d0]
0x100034718: str  wzr, [x19, #0x1d8]
0x10003471c: mov  w8, #1
0x100034720: sturh w8, [x19, #0xd5]     ; 校验类型恢复为 1
0x10003472c: tbnz w21, #0, 0x100034768  ; w1 bit0 == 1 → 结束
0x100034730: ldr  x0, [x19, #0x120]     ; 发送包链表
0x100034744: bl   0x100099494           ; 清空
```

## 5.5 ACK / EAK 动作

`A05.7`（已确认）`iAP2LinkActionHandleACK(link, &event)` 并不直接操作数据，只把事件置为 `0x1D`（29）：

```
0x10000bc18: mov  w8, #0x1d
0x10000bc1c: strb w8, [x1]
```

这与状态机的事件号上限 29（`0x1D`）一致，说明 ACK 的实质处理发生在状态机的链式迁移中，而不是在这个 action 里。

`A05.8`（已确认）EAK 帧由 `iAP2PacketCreateEAKPacket`（`0x1001031d0`）构造，控制字段 `0x60`（ACK|EAK）；其"缺失序号列表"由 `iAP2PacketGetMissingSeqFromEAK`（`0x1001033bc`，未导出到本轮汇编集合）提取 → 载荷格式 `OPEN-SEQ-1`。

## 5.6 重传触发与上限

`A05.9`（部分确认）重传相关动作以 FSM 事件形式存在，触发点未全部取证：

- `iAP2LinkActionResendData`（`0x1000323f8`）：重传数据包；
- `iAP2LinkActionResendMissing`（`0x100031ef8`）：按 EAK 补发缺失；
- `iAP2LinkDeviceActionHandleMaxRetries`（`0x100030054`）：达到 `MaxRetransmissions` 时的处置；
- 重试上限的取值来自 SYN 协商的 `MaxRetransmissions`（缺省 30，合法区间 1..30，见 `analysis/04` A04.7）。

这三个函数的完整分支需要逐个通读（合计约 4 KB 汇编），本阶段未做穷尽 → `OPEN-SEQ-2`。

## 5.7 重复帧

`A05.10`（部分确认）重复帧的判定入口是 `iAP2LinkHandleReadyPacket`（`0x10000ada0`）/`iAP2LinkProcessInOrderPacket`（`0x10000b690`）中对序号与期望值的比较；本轮未逐条核对这两个函数的比较逻辑 → `OPEN-SEQ-3`。

## 5.8 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-SEQ-1` | EAK 载荷中缺失序号的编码 |
| `OPEN-SEQ-2` | 重传三函数（ResendData / ResendMissing / HandleMaxRetries）的完整分支与触发点 |
| `OPEN-SEQ-3` | 重复帧与乱序帧的判定/丢弃路径 |
| `OPEN-SEQ-4` | 写入来源已确认：对端 SYN MOP 保存到 +0x173，连接时提交至 +0x1a5（A04.13）；全部窗口状态迁移仍需验证 |
| `OPEN-SEQ-5` | ACK 的"累积确认"语义是否由 seq 字段单独承载（帧头只有 1 个序号字节） |
