# spec/05 — 链路状态机

## 5.1 状态集合

`R-5.1`（MUST / CONFIRMED）链路状态机恰有 **8** 个状态，编号与语义如下（编号即状态表下标）：

| # | 状态 | 说明 |
|---|---|---|
| 0 | Init | 刚创建，未 attach |
| 1 | Detached | 传输未就绪 |
| 2 | Detect | 传统 Detect 阶段 |
| 3 | Idle | 等待 SYN |
| 4 | Pending | SYN/ACK 交换中 |
| 5 | Connected | 链路可用 |
| 6 | Suspend | 挂起 |
| 7 | Failed | 失败 |

依据：`A06.1`、`A06.3`（`iAP2LinkCreate` 以 8 个状态创建，状态表 `0x100219600`）、`A06.4`（状态表指针依次指向 8 个 `iAP2LinkDevice*StateEvents` 符号）。

`R-5.2`（MUST / CONFIRMED）事件号上限为 **29**（`0x1D`）；事件号 `>= 29` 视为非法。

依据：`A06.3`（`iAP2FSMCreate` 的第 3 参数 `0x1D`）、`A06.6`（`0x1000063c8`）。

## 5.2 迁移表（规范数据）

`R-5.3`（MUST / CONFIRMED）下表是**生效迁移**的完整集合（只含 handler 非空的条目）。`—` 表示该状态不存在该事件。

| 事件 | Init | Detached | Detect | Idle | Pending | Connected | Suspend | Failed |
|---|---|---|---|---|---|---|---|---|
| `0x00` | →1 | — | — | — | — | — | — | — |
| `0x01` | — | →2 | — | — | — | — | — | — |
| `0x02` | — | — | →4 | →4 | →4 | →4 | — | — |
| `0x03` | — | — | — | — | →4 | — | — | — |
| `0x04` | — | — | — | →4 | →4 | — | — | — |
| `0x06` | — | — | — | →4 | →4 | — | — | — |
| `0x0a` | — | — | — | →3 | — | →5 | →6 | — |
| `0x0b` | — | — | — | — | — | →5 | →6 | — |
| `0x0c` | — | — | — | — | →4 | →5 | →6 | →7 |
| `0x0d` | — | — | — | — | — | →5 | →6 | →7 |
| `0x0e` | — | →1 | →1 | →1 | →1 | →1 | →1 | →1 |
| `0x0f` | — | — | →3 | →3 | →3 | →5 | →6 | — |
| `0x10` | — | — | — | →3 | →3 | →5 | →6 | — |
| `0x11` | — | — | — | →3 | — | →5 | →6 | — |
| `0x12` | — | — | — | — | — | →5 | →6 | — |
| `0x13` | — | — | — | →3 | →3 | →3 | — | — |
| `0x14` | — | — | — | →7 | →7 | →7 | →7 | — |
| `0x15` | — | — | — | →3 | →5 | →5 | — | — |
| `0x16` | — | — | — | — | →3 | — | — | — |
| `0x17` | — | — | →3 | →3 | →3 | →3 | →3 | →3 |
| `0x19` | — | — | →3 | — | — | — | — | — |
| `0x1b` | — | — | — | — | — | →6 | — | — |
| `0x1c` | — | — | — | — | — | — | →5 | — |

`R-5.4`（MUST / CONFIRMED）固件表中还有 5 条 **handler 为空**的条目，它们**不产生迁移**（`R-5.8`）：

| 状态 | 事件 |
|---|---|
| Idle | `0x05` |
| Idle | `0x08` |
| Idle | `0x0b` |
| Idle | `0x0c` |
| Connected | `0x08` |

这三条（Idle 的 `0x05/0x08/0x0b/0x0c`、Connected 的 `0x08`）在实现时必须按"该状态不认识此事件"处理，而不是按表迁移。

`R-5.5`（MUST / CONFIRMED）每个生效条目绑定的动作如下（实现时按此表实现副作用）：

| 事件 | 状态 → 动作（地址） |
|---|---|
| `0x00` | Init: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x01` | Detached: `iAP2LinkDeviceActionAttach` (`0x10002f8dc`) |
| `0x02` | Detect: `iAP2LinkDeviceActionSendResetSYNACK` (`0x10002f920`)<br>Idle: `iAP2LinkDeviceActionSendResetSYNACK` (`0x10002f920`)<br>Pending: `iAP2LinkDeviceActionSendResetSYNACK` (`0x10002f920`)<br>Connected: `iAP2LinkDeviceActionSendResetSYNACK` (`0x10002f920`) |
| `0x03` | Pending: `iAP2LinkDeviceActionResendSYNACK` (`0x10002feb0`) |
| `0x04` | Idle: `iAP2LinkDeviceActionSendSYNACK` (`0x10002fcd4`)<br>Pending: `iAP2LinkDeviceActionSendSYNACK` (`0x10002fcd4`) |
| `0x06` | Idle: `iAP2LinkDeviceActionSendSYNACK` (`0x10002fcd4`)<br>Pending: `iAP2LinkDeviceActionSendSYNACK` (`0x10002fcd4`) |
| `0x0a` | Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Connected: `iAP2LinkActionHandleTimeSyncResponse` (`0x1000826e8`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x0b` | Connected: `iAP2LinkActionStartTimeSync` (`0x100082660`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x0c` | Pending: `iAP2LinkDeviceActionResendSYNACK` (`0x10002feb0`)<br>Connected: `iAP2LinkActionResendData` (`0x1000323f8`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`)<br>Failed: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x0d` | Connected: `iAP2LinkActionSendACK` (`0x100031cc0`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`)<br>Failed: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x0e` | Detached: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Detect: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Idle: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Pending: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Connected: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Suspend: `iAP2LinkActionDetach` (`0x100031c7c`)<br>Failed: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x0f` | Detect: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Pending: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Connected: `iAP2LinkActionHandleData` (`0x100032670`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x10` | Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Pending: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Connected: `iAP2LinkActionSendACK` (`0x100031cc0`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x11` | Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Connected: `iAP2LinkActionResendMissing` (`0x100031ef8`)<br>Suspend: `iAP2LinkActionNone` (`0x100031c50`) |
| `0x12` | Connected: `iAP2LinkActionSendData` (`0x100006680`)<br>Suspend: `iAP2LinkActionSendData` (`0x100006680`) |
| `0x13` | Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Pending: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Connected: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`) |
| `0x14` | Idle: `iAP2LinkActionNone` (`0x100031c50`)<br>Pending: `iAP2LinkDeviceActionHandleMaxRetries` (`0x100030054`)<br>Connected: `iAP2LinkActionNotifyConnectionFail` (`0x10003286c`)<br>Suspend: `iAP2LinkActionNotifyConnectionFail` (`0x10003286c`) |
| `0x15` | Idle: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`)<br>Pending: `iAP2LinkDeviceActionNotifyConnection` (`0x10003009c`)<br>Connected: `iAP2LinkActionHandleACK` (`0x10000bc04`) |
| `0x16` | Pending: `iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled` (`0x100030128`) |
| `0x17` | Detect: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`)<br>Idle: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`)<br>Pending: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`)<br>Connected: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`)<br>Suspend: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`)<br>Failed: `iAP2LinkDeviceActionSendDetect` (`0x10002fac8`) |
| `0x19` | Detect: `iAP2LinkDeviceActionSendRST` (`0x10002fb54`) |
| `0x1b` | Connected: `iAP2LinkDeviceActionSendSuspend` (`0x10003021c`) |
| `0x1c` | Suspend: `iAP2LinkDeviceActionSendResume` (`0x1000302a0`) |

## 5.3 迁移执行

`R-5.6`（MUST / CONFIRMED）一次事件处理流程：

```
if (event >= event_limit) -> 非法，返回，不改状态
state_entry = states[fsm.state]
ev = find(state_entry.events[0..count), event)      // 线性，首个匹配
if (!ev || !ev.handler) -> 非法，返回，不改状态
fsm.last_event = event
ev.handler(fsm, &event)                              // 可改写 event
fsm.state = ev.next_state
if (fsm.state < event_limit) -> 用同一 event 从 R-5.6 开头重复一次
```

依据：`A06.1`、`A06.7`、`A06.8`（`iAP2FSMHandleEvent` `0x10000639c`）。

`R-5.7`（MUST / CONFIRMED）**链式迁移**：迁移后必须用**同一事件**在新状态上再执行一次，直到新状态无法处理该事件为止。

依据：`A06.8`（`0x100006444`–`0x10000644c`）。

`R-5.8`（MUST / CONFIRMED）非法事件（越界 / 当前状态无该事件 / handler 为空）必须**不改变状态、不产生副作用**，只允许写日志。

依据：`A06.7`（`0x100006418`、`0x10000644c`）。

## 5.4 动作与事件的关系

`R-5.9`（MUST / CONFIRMED）链路动作函数（`iAP2Link*Action*`）的第一个参数是 **FSM**，链路对象通过 `fsm[0x10]` 取得；动作函数把 `*event` 置为 `0x1D`（29），真正的状态变化由 `R-5.4` 完成。

依据：`A07.7`（`0x10002fae0`–`0x10002fae8`）、`A05.7`（`iAP2LinkActionHandleACK` `0x10000bc18`）。

## 5.5 状态机的创建与启动

`R-5.10`（MUST / CONFIRMED）状态机对象 0x30 字节；创建时传入状态表、状态数、事件号上限；启动时投事件 `0x00`。

依据：`A06.2`、`A06.3`、`A02.5`（`iAP2LinkStart` `0x100034a70`）。

## 5.6 attach / detach 与状态机

`R-5.11`（MUST / CONFIRMED）attach 时**先**复原 SYN 缺省参数、**再**投事件 `0x01`；detach 时**先**投事件 `0x0E`、**再**复原参数。两者都必须可重复执行。

依据：`A02.4`（`0x100034a7c`）、`A11.1`（`0x100034bbc`）、`A11.2`。

## 5.7 未决项

| ID | 内容 |
|---|---|
| `OPEN-FSM-1` | 状态 2（Detect）事件表尾部的全零条目语义 |
| `OPEN-FSM-2` | 事件号 → 名称的完整映射 |
| `OPEN-FSM-3` | 事件 `0x04`/`0x06`/`0x15`/`0x19` 的精确触发点 |
| `OPEN-FSM-4` | Init 状态的其余初始化步骤（不在状态机内） |
## 本章依据

| 条款 | 分析结论 | 关键地址 |
|---|---|---|
| `R-5.1` | `A06.1`、`A06.3`、`A06.4` | — |
| `R-5.2` | `A06.3`、`A06.6` | — |
| `R-5.6` | `A06.1`、`A06.7`、`A06.8` | — |
| `R-5.7` | `A06.8` | — |
| `R-5.8` | `A06.7` | — |
| `R-5.9` | `A05.7`、`A07.7` | — |
| `R-5.10` | `A02.5`、`A06.2`、`A06.3` | — |
| `R-5.11` | `A02.4`、`A11.1`、`A11.2` | — |

> 上表由条款正文的 `A` 编号与地址自动汇总；逐条依据见各条款下方的"依据"行。
