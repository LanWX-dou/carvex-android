# spec/04 — 序号、确认与重传

## 4.1 序号空间

`R-4.1`（MUST / CONFIRMED）序号为 8 位，帧头偏移 5；模差为 `(b - a) & 0xFF`。

依据：`A05.1`（`iAP2PacketCalcSeqGap` `0x1000084b8`、`0x100035414`）。

`R-4.2`（MUST / CONFIRMED）初始序号由毫秒时钟派生，取决于 `link[0xd4]` 的 bit2：

```
if (!(flags & 0x04)) seq0 = now_ms & 0xFF
else                 seq0 = (base + 0x47) & now_ms & 0xFF      // base = link[0xbe]
```

`base` 在"首次进入"时被写成新序号（`SendResetSYNACK` 中 `flags & 0x04` 为 0 的分支），复位时清零。

依据：`A05.2`（`iAP2LinkGetNewSeqNum` `0x100034424`）、`A07.9`（`0x10002fa14`–`0x10002fa24`）、`A05.6`（`0x1000346ec`）。

## 4.2 确认窗口

`R-4.3`（MUST / CONFIRMED）窗口为 `link[0x1a5]`（1 字节），**缺省 1**（同一常量还给出 `[0x1a6]=0xFFFF` 的最大接收包长）。两个包的顺序比较：

```
gap = (seqB - seqA) & 0xFF
if (gap == 0) return 0
return (gap <= window) ? gap : (gap | ~0xFF)      // 超窗 → 负数
```

依据：`A05.3`（`__iAP2LinkComparePacketSeq` `0x1000353f8`：`0x100035438`–`0x100035448`）。

`R-4.4`（MUST / CONFIRMED）"序号已被确认"判定：

```
is_acked(seq, ack, window) := (window >= ((ack - seq) & 0xFF))
```

依据：`A05.4`（`iAP2PacketIsSeqACKd` `0x10000b5c0`）。

## 4.3 ACK / EAK

`R-4.5`（MUST / CONFIRMED）ACK 帧控制字段 `0x40`；EAK 帧 `0x60`。ACK 的"处理"在链路层以 FSM 事件 `0x1D`（ACK 动作）与事件 `0x15`（Connected 状态下 `iAP2LinkActionHandleACK`）体现。

依据：`A03.8`、`A05.7`（`0x10000bc18`）、`analysis/06` 状态 5 表（`0x10000bc04` 绑定事件 `0x15`）。

`R-4.6`（未定义 / OPEN）EAK 载荷的缺失序号编码未确认。实现必须把"如何从 EAK 载荷取缺失集合"隔离为可替换函数。

依据：`A05.8`（`iAP2PacketGetMissingSeqFromEAK` `0x1001033bc` 存在但未解读）。`OPEN-SEQ-1`。

## 4.4 复位

`R-4.7`（MUST / CONFIRMED）发送侧复位顺序：清 5 个发送链表 → 复原 SYN 缺省参数 → `reset_seq_ack(link, 1, 0)`。

依据：`A05.5`（`iAP2LinkResetSend` `0x100034464`）。

`R-4.8`（MUST / CONFIRMED）`reset_seq_ack(link, w1, w2)` 的行为：

| 步骤 | 条件 |
|---|---|
| `link[0xbe] = 0` | 总是 |
| 清 `link[0xd4]` bit2、bit3 | 总是 |
| 重建时间同步对象 | 总是 |
| 清 `link[0x1d0]`、`link[0x1d8]`，`link[0xd5] = 1` | `w2 != 0` |
| 清发送包链表 `link[0x120]` | `w1` 的 bit0 == 0 |

依据：`A05.6`（`0x1000346c8`：`0x1000346ec`–`0x100034748`）。

`R-4.9`（MUST / CONFIRMED）四个调用点的参数组合：

| 调用点 | `w1` | `w2` |
|---|---|---|
| `ResetSend` | 1 | 0 |
| `SendResetSYNACK` | 1 | 0 |
| `SendDetect` | 0 | 1 |
| `SendRST` | 0 | 0 |

依据：`A11.4`。

## 4.5 重传

`R-4.10`（MUST / CONFIRMED）存在三个与重传相关的动作函数，其触发由 FSM 事件承载：

| 动作 | 地址 | 生效事件 |
|---|---|---|
| `iAP2LinkActionResendData` | `0x1000323f8` | `0x0c`（Connected） |
| `iAP2LinkActionResendMissing` | `0x100031ef8` | `0x11`（Connected） |
| `iAP2LinkDeviceActionHandleMaxRetries` | `0x100030054` | `0x14`（Pending） |

依据：`A05.9`、`analysis/06` 状态 4/5 表。

`R-4.11`（MUST / CONFIRMED）重试上限来自 SYN 的 `MaxRetransmissions`（合法 1..30，缺省 30）。

依据：`A04.7`、`A04.1`。

`R-4.12`（未定义 / OPEN）三个重传函数的内部策略（按包、按批、是否重置计时器）未确认；实现必须自行定义并标注差异。

依据：`A05.9`。`OPEN-SEQ-2`。

## 4.6 未决项

| ID | 内容 |
|---|---|
| `OPEN-SEQ-1` | EAK 缺失序号编码 |
| `OPEN-SEQ-2` | 重传三函数的分支与触发点 |
| `OPEN-SEQ-3` | 重复帧/乱序帧判定 |
| `OPEN-SEQ-4` | 对端 MOP→工作块→+0x1a5 的提交已确认（A04.13）；全部窗口迁移仍需验证 |
| `OPEN-SEQ-5` | 累积确认如何由单字节 seq 承载 |
## 本章依据

| 条款 | 分析结论 | 关键地址 |
|---|---|---|
| `R-4.1` | `A05.1` | — |
| `R-4.2` | `A05.2`、`A05.6`、`A07.9` | — |
| `R-4.3` | `A05.3` | — |
| `R-4.4` | `A05.4` | — |
| `R-4.5` | `A03.8`、`A05.7` | — |
| `R-4.6` | `A05.8` | — |
| `R-4.7` | `A05.5` | — |
| `R-4.8` | `A05.6` | — |
| `R-4.9` | `A11.4` | — |
| `R-4.10` | `A05.9` | — |
| `R-4.11` | `A04.1`、`A04.7` | — |
| `R-4.12` | `A05.9` | — |

> 上表由条款正文的 `A` 编号与地址自动汇总；逐条依据见各条款下方的"依据"行。
