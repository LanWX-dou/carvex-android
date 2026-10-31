# analysis/06 — 链路状态机

对应任务书第 5 节第 6 项。本文件给出状态取值、迁移表、守卫条件与非法事件处理，全部来自固件中的数据表 `__DATA_CONST` 与状态机执行函数。

证据函数 / 数据：

| 对象 | 地址 | 作用 |
|---|---|---|
| `iAP2FSMCreate` | `0x10006baac` | 创建状态机对象 |
| `iAP2FSMGetBuffSize` | `0x10006baa4` | 对象大小 `0x30` |
| `iAP2FSMHandleEvent` | `0x10000639c` | 迁移核心 |
| `iAP2LinkDeviceStates` | `0x100219600` | 状态表（8 项，每项 16 字节） |
| `iAP2LinkDeviceInitStateEvents` | `0x100219030` | 状态 0 的事件表 |
| `iAP2LinkDeviceDetachedStateEvents` | `0x100219040` | 状态 1 |
| `iAP2LinkDeviceDetectStateEvents` | `0x100219060` | 状态 2 |
| `iAP2LinkDeviceIdleStateEvents` | `0x100219230` | 状态 3 |
| `iAP2LinkDevicePendingStateEvents` | `0x100219330` | 状态 4 |
| `iAP2LinkDeviceConnectedStateEvents` | `0x100219400` | 状态 5 |
| `iAP2LinkDeviceSuspendStateEvents` | `0x100219500` | 状态 6 |
| `iAP2LinkDeviceFailedStateEvents` | `0x1002195c0` | 状态 7 |

## 6.1 状态表结构

`A06.1`（已确认）状态表每项 16 字节：`{ 事件表指针 (8), 事件数 (1), 保留 (7) }`；事件表每项 16 字节：`{ 处理函数 (8), 目标状态 (1), 事件号 (1), 保留 (6) }`。

证据 `iAP2FSMHandleEvent`：

```
0x1000063c4: ldrb w8, [x19, #9]        ; fsm->event_count（事件个数上限）
0x1000063c8: cmp  w20, w8
0x1000063cc: b.hs 0x100006454          ; 事件号越界 → 非法事件
0x1000063d0: ldr  x8, [x19]            ; fsm->states
0x1000063d4: ldrb w9, [x19, #0xa]      ; fsm->state（当前状态索引）
0x1000063d8: add  x10, x8, x9, lsl #4  ; &states[state]
0x1000063dc: ldr  x9, [x10]            ; events = states[state].events
0x1000063e0: ldrb w11, [x10, #8]       ; count = states[state].count
0x1000063e4: add  x10, x9, x11, lsl #4 ; 事件表末尾
0x1000063ec: add  x21, x9, #9
0x1000063f0: ldrb w11, [x9, #9]        ; ev->event
0x1000063f4: cmp  w11, w20
0x1000063f8: b.eq 0x100006410          ; 命中
0x1000063fc: add  x9, x9, #0x10
0x100006400: add  x21, x21, #0x10
0x100006404: cmp  x9, x10
0x100006408: b.lo 0x1000063f0
```

命中后：

```
0x100006414: ldr  x8, [x9]             ; ev->handler
0x100006418: cbz  x8, 0x1000064a0      ; handler == NULL → 与"非法事件"同路径
0x10000641c: strb w20, [x19, #0xb]     ; fsm->last_event = event
0x100006428: blraaz x8                 ; handler(fsm, &event)
0x10000642c: ldurb w8, [x21, #-1]      ; ev->next_state
0x100006430: strb w8, [x19, #0xa]      ; fsm->state = next_state
0x100006444: ldrb w8, [x19, #9]
0x100006448: cmp  w20, w8
0x10000644c: b.lo 0x1000063d0          ; 用同一事件在新状态上再跑一次
```

`A06.2`（已确认）状态机对象 0x30 字节（`iAP2FSMGetBuffSize` 返回 `0x30`），字段：

| 偏移 | 含义 | 证据 |
|---|---|---|
| `+0x00` | 状态表指针 | `0x1000063d0` |
| `+0x08` | 状态个数 | `0x100006434` 比较 |
| `+0x09` | 事件号上限（29） | `0x1000063c4` |
| `+0x0a` | 当前状态 | `0x1000063d4` / `0x100006430` |
| `+0x0b` | 最近事件 | `0x10000641c` |
| `+0x18` | 名称指针（可空） | `0x1000064fc`–`0x100006510` |
| `+0x20` | 状态名表（可空） | `0x100006558` |
| `+0x28` | 事件名表（可空） | `0x10000651c` |

`A06.3`（已确认）`iAP2LinkCreate` 以 8 个状态、29 个事件号上限创建状态机，状态表为 `0x100219600`：

```
0x10003405c: adrp x3, #0x100219000
0x100034060: add  x3, x3, #0x600       ; states = 0x100219600
0x10003406c: mov  w0, #8               ; 状态数
0x100034070: mov  w1, #0
0x100034074: mov  w2, #0x1d            ; 事件号上限 29
0x100034084: bl   0x10006baac          ; iAP2FSMCreate
```

## 6.4 状态与事件表（来自固件数据，逐项解码）

解码规则：`target = 0x100000000 + (value & 0xFFFFFFFFFF)`（rebase 与 chained-fixup 统一）。

`A06.4`（已确认）**handler 为空 = 该条目不生效**：`iAP2FSMHandleEvent` 在命中条目后先判 `cbz x8, 0x1000064a0`，
为空则走日志分支并直接返回（`0x10000664c: b 0x100006650`），**不写入 next_state、不记录 last_event**。
因此下表把空 handler 的条目标为"不生效"——它们占位但不会导致迁移。

`A06.5`（已确认）状态名来源：状态表第 0..7 项指针依次指向 8 个 `iAP2LinkDevice*StateEvents` 符号，符号名给出状态语义；
固件中没有独立的状态名数组（`fsm+0x20` 为 NULL），故状态名属"表符号名推断"，方向由迁移结构佐证。

### 状态 0 — Init（``0x100219030``，表长 1，有效 1 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x00` | iAP2LinkActionNone | 1 Detached | 是 |

### 状态 1 — Detached（``0x100219040``，表长 2，有效 2 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x01` | iAP2LinkDeviceActionAttach | 2 Detect | 是 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |

### 状态 2 — Detect（``0x100219060``，表长 29，有效 5 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x02` | iAP2LinkDeviceActionSendResetSYNACK | 4 Pending | 是 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |
| `0x19` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x0f` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |

### 状态 3 — Idle（``0x100219230``，表长 16，有效 12 条 / 不生效 4 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x02` | iAP2LinkDeviceActionSendResetSYNACK | 4 Pending | 是 |
| `0x04` | iAP2LinkDeviceActionSendSYNACK | 4 Pending | 是 |
| `0x05` | （空） | 3 Idle | 否 |
| `0x06` | iAP2LinkDeviceActionSendSYNACK | 4 Pending | 是 |
| `0x08` | （空） | 3 Idle | 否 |
| `0x0a` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x0b` | （空） | 3 Idle | 否 |
| `0x0c` | （空） | 3 Idle | 否 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |
| `0x0f` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x10` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x11` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x14` | iAP2LinkActionNone | 7 Failed | 是 |
| `0x15` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |
| `0x13` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |

### 状态 4 — Pending（``0x100219330``，表长 13，有效 13 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x02` | iAP2LinkDeviceActionSendResetSYNACK | 4 Pending | 是 |
| `0x03` | iAP2LinkDeviceActionResendSYNACK | 4 Pending | 是 |
| `0x04` | iAP2LinkDeviceActionSendSYNACK | 4 Pending | 是 |
| `0x06` | iAP2LinkDeviceActionSendSYNACK | 4 Pending | 是 |
| `0x0c` | iAP2LinkDeviceActionResendSYNACK | 4 Pending | 是 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |
| `0x0f` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x10` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x13` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x14` | iAP2LinkDeviceActionHandleMaxRetries | 7 Failed | 是 |
| `0x15` | iAP2LinkDeviceActionNotifyConnection | 5 Connected | 是 |
| `0x16` | iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled | 3 Idle | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |

### 状态 5 — Connected（``0x100219400``，表长 16，有效 15 条 / 不生效 1 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x02` | iAP2LinkDeviceActionSendResetSYNACK | 4 Pending | 是 |
| `0x08` | （空） | 3 Idle | 否 |
| `0x0a` | iAP2LinkActionHandleTimeSyncResponse | 5 Connected | 是 |
| `0x0b` | iAP2LinkActionStartTimeSync | 5 Connected | 是 |
| `0x0f` | iAP2LinkActionHandleData | 5 Connected | 是 |
| `0x0c` | iAP2LinkActionResendData | 5 Connected | 是 |
| `0x0d` | iAP2LinkActionSendACK | 5 Connected | 是 |
| `0x10` | iAP2LinkActionSendACK | 5 Connected | 是 |
| `0x13` | iAP2LinkDeviceActionSendRST | 3 Idle | 是 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |
| `0x11` | iAP2LinkActionResendMissing | 5 Connected | 是 |
| `0x12` | iAP2LinkActionSendData | 5 Connected | 是 |
| `0x14` | iAP2LinkActionNotifyConnectionFail | 7 Failed | 是 |
| `0x15` | iAP2LinkActionHandleACK | 5 Connected | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |
| `0x1b` | iAP2LinkDeviceActionSendSuspend | 6 Suspend | 是 |

### 状态 6 — Suspend（``0x100219500``，表长 12，有效 12 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x0a` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x0b` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x0c` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x0d` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x0e` | iAP2LinkActionDetach | 1 Detached | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |
| `0x0f` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x10` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x11` | iAP2LinkActionNone | 6 Suspend | 是 |
| `0x12` | iAP2LinkActionSendData | 6 Suspend | 是 |
| `0x1c` | iAP2LinkDeviceActionSendResume | 5 Connected | 是 |
| `0x14` | iAP2LinkActionNotifyConnectionFail | 7 Failed | 是 |

### 状态 7 — Failed（``0x1002195c0``，表长 4，有效 4 条 / 不生效 0 条）

| 事件 | 处理函数 | 目标状态 | 生效 |
|---|---|---|---|
| `0x0c` | iAP2LinkActionNone | 7 Failed | 是 |
| `0x0d` | iAP2LinkActionNone | 7 Failed | 是 |
| `0x0e` | iAP2LinkActionNone | 1 Detached | 是 |
| `0x17` | iAP2LinkDeviceActionSendDetect | 3 Idle | 是 |

`A06.6`（已确认）事件号语义由**处理函数名**给出（每个生效事件都绑定了具名动作）。同一事件号在不同状态绑定不同动作，因此事件语义必须按"状态 + 事件"联合解释：

| 事件 | 生效状态 → 处理函数 | 推断语义 |
|---|---|---|
| `0x00` | Init→1 `iAP2LinkActionNone` | 初始化完成 |
| `0x01` | Detached→2 `iAP2LinkDeviceActionAttach` | 传输 attach |
| `0x02` | Detect→4 `iAP2LinkDeviceActionSendResetSYNACK`；Idle→4 `iAP2LinkDeviceActionSendResetSYNACK`；Pending→4 `iAP2LinkDeviceActionSendResetSYNACK`；Connected→4 `iAP2LinkDeviceActionSendResetSYNACK` | 收到 SYN（重置后回 SYNACK） |
| `0x03` | Pending→4 `iAP2LinkDeviceActionResendSYNACK` | 重发 SYNACK |
| `0x04` | Idle→4 `iAP2LinkDeviceActionSendSYNACK`；Pending→4 `iAP2LinkDeviceActionSendSYNACK` | 发 SYNACK |
| `0x06` | Idle→4 `iAP2LinkDeviceActionSendSYNACK`；Pending→4 `iAP2LinkDeviceActionSendSYNACK` | 发 SYNACK（另一触发点） |
| `0x0a` | Idle→3 `iAP2LinkDeviceActionSendRST`；Connected→5 `iAP2LinkActionHandleTimeSyncResponse`；Suspend→6 `iAP2LinkActionNone` | 时间同步响应 |
| `0x0b` | Connected→5 `iAP2LinkActionStartTimeSync`；Suspend→6 `iAP2LinkActionNone` | 启动时间同步 |
| `0x0c` | Pending→4 `iAP2LinkDeviceActionResendSYNACK`；Connected→5 `iAP2LinkActionResendData`；Suspend→6 `iAP2LinkActionNone`；Failed→7 `iAP2LinkActionNone` | 重传数据 |
| `0x0d` | Connected→5 `iAP2LinkActionSendACK`；Suspend→6 `iAP2LinkActionNone`；Failed→7 `iAP2LinkActionNone` | 发 ACK |
| `0x0e` | Detached→1 `iAP2LinkActionDetach`；Detect→1 `iAP2LinkActionDetach`；Idle→1 `iAP2LinkActionDetach`；Pending→1 `iAP2LinkActionDetach`；Connected→1 `iAP2LinkActionDetach`；Suspend→1 `iAP2LinkActionDetach`；Failed→1 `iAP2LinkActionNone` | detach |
| `0x0f` | Detect→3 `iAP2LinkDeviceActionSendRST`；Idle→3 `iAP2LinkDeviceActionSendRST`；Pending→3 `iAP2LinkDeviceActionSendRST`；Connected→5 `iAP2LinkActionHandleData`；Suspend→6 `iAP2LinkActionNone` | 收到数据 / 发 RST |
| `0x10` | Idle→3 `iAP2LinkDeviceActionSendRST`；Pending→3 `iAP2LinkDeviceActionSendRST`；Connected→5 `iAP2LinkActionSendACK`；Suspend→6 `iAP2LinkActionNone` | 发 ACK / 发 RST |
| `0x11` | Idle→3 `iAP2LinkDeviceActionSendRST`；Connected→5 `iAP2LinkActionResendMissing`；Suspend→6 `iAP2LinkActionNone` | 补发缺失（EAK） |
| `0x12` | Connected→5 `iAP2LinkActionSendData`；Suspend→6 `iAP2LinkActionSendData` | 发送数据 |
| `0x13` | Idle→3 `iAP2LinkDeviceActionSendRST`；Pending→3 `iAP2LinkDeviceActionSendRST`；Connected→3 `iAP2LinkDeviceActionSendRST` | 发 RST |
| `0x14` | Idle→7 `iAP2LinkActionNone`；Pending→7 `iAP2LinkDeviceActionHandleMaxRetries`；Connected→7 `iAP2LinkActionNotifyConnectionFail`；Suspend→7 `iAP2LinkActionNotifyConnectionFail` | 失败 |
| `0x15` | Idle→3 `iAP2LinkDeviceActionSendRST`；Pending→5 `iAP2LinkDeviceActionNotifyConnection`；Connected→5 `iAP2LinkActionHandleACK` | 协商成功 / 处理 ACK |
| `0x16` | Pending→3 `iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled` | 以新校验模式发 RST |
| `0x17` | Detect→3 `iAP2LinkDeviceActionSendDetect`；Idle→3 `iAP2LinkDeviceActionSendDetect`；Pending→3 `iAP2LinkDeviceActionSendDetect`；Connected→3 `iAP2LinkDeviceActionSendDetect`；Suspend→3 `iAP2LinkDeviceActionSendDetect`；Failed→3 `iAP2LinkDeviceActionSendDetect` | 发 Detect |
| `0x19` | Detect→3 `iAP2LinkDeviceActionSendRST` | 发 RST（超时/放弃） |
| `0x1b` | Connected→6 `iAP2LinkDeviceActionSendSuspend` | 发 SUS |
| `0x1c` | Suspend→5 `iAP2LinkDeviceActionSendResume` | 发 Resume |

## 6.6 非法事件处理

`A06.7`（已确认）两类非法情形合并处理：

1. 事件号 `>= fsm[9]`（29）→ 直接进日志分支（`0x1000063cc`）；
2. 当前状态的事件表中找不到该事件，或找到但 handler 为 NULL → 同样进日志分支（`0x10000649c` / `0x100006418`）。

日志分支只在 `0x10023d280` 首位为 1 时输出（`0x100006454`–`0x100006460`），否则直接返回，**不改变状态、不产生副作用**：

```
0x10000644c: b.lo 0x1000063d0
0x100006450: b    0x100006650          ; 退出循环
0x1000064a0: ...（日志）
0x10000664c: b    0x100006650          ; 无副作用返回
```

`A06.8`（已确认）**链式迁移**：一次事件处理完成后，若新状态的索引 `< fsm[9]`，会用**同一事件**在新状态上再执行一次（`0x100006444`–`0x10000644c`）。实现者必须复现这一行为，否则会出现"少走一个状态"的差异。

## 6.7 事件发布点（谁触发迁移）

`A06.9`（已确认）用 Capstone 全量扫描 `__TEXT` 中对 `iAP2FSMHandleEvent`（`0x10000639c`）的直接调用，共 **17 处**，其中 **14 处**可由调用前的 `mov w1, #imm` 解出事件号：

| 调用点 | 事件 | 发布者 |
|---|---|---|
| `0x100034a78` | `0x00` | `iAP2LinkStart` |
| `0x100034ab4` | `0x01` | `iAP2LinkAttached` |
| `0x10000bbb0` | `0x06` | `iAP2LinkProcessInOrderPacket` |
| `0x100034af8` | `0x08` | `iAP2LinkRenegotiate` |
| `0x1000d4e10` | `0x0a` | `iAP2LinkProcessInOrderPacketCMD` |
| `0x100034bdc` | `0x0e` | `iAP2LinkDetached` |
| `0x10000b71c` | `0x0f` | `iAP2LinkProcessInOrderPacket` |
| `0x10000b2dc` | `0x10` | `iAP2LinkHandleReadyPacket` |
| `0x100006370` | `0x12` | `iAP2LinkProcessSendBuff` |
| `0x10000b00c` | `0x13` | `iAP2LinkHandleReadyPacket` |
| `0x10000b84c` | `0x14` | `iAP2LinkProcessInOrderPacket` |
| `0x10000bbe4` | `0x15` | `iAP2LinkProcessInOrderPacket` |
| `0x100034e40` | `0x1b` | `iAP2LinkHandleSuspend` |
| `0x100034ef4` | `0x1c` | `iAP2LinkHandleResume` |

其余 3 处的事件号不是立即数：

- `0x10000adfc`–`0x10000ae04`（`iAP2LinkHandleReadyPacket`）：`event = (packet[+0x3d] + 4) & 0xFF`，且仅当该字节 `>= 0x13` 时走这条路径；
- `0x100034318`（`iAP2LinkHandleTimerExpire`）与 `0x100034f3c`（`iAP2LinkHandleTimeout`）：事件号来自定时器记录，未逐条读出。

结论：**链路动作、收包、定时器**三条来源都会发布事件；但事件 `0x02`–`0x05`、`0x07`、`0x09`、`0x0b`、`0x11`、`0x16`–`0x19` 的发布点仍在未采样函数中 → `OPEN-FSM-3` 保留；`packet[+0x3d]` 语义 → `OPEN-FSM-4`。

## 6.8 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-FSM-1` | 各状态事件表中全零条目的语义（容量 vs 有效条目） |
| `OPEN-FSM-2` | 事件号 → 名称的完整映射（无名称表） |
| `OPEN-FSM-3` | 事件 `0x04` / `0x06` / `0x15` / `0x19` 的精确触发点（需要 handler 与调用者交叉取证） |
| `OPEN-FSM-4` | 状态 0（Init）只有 1 条事件，初始化流程的其余步骤不在状态机内（见 `analysis/02`） |
