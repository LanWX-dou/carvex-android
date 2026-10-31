# spec/07 — 异常、拆除与清理

## 7.1 断开

`R-7.1`（MUST / CONFIRMED）detach 顺序：向 FSM 投事件 `0x0E` → 复原 SYN 缺省参数（`R-3.2` 的七元组）。

依据：`A11.1`（`iAP2LinkDetached` `0x100034bbc`：`0x100034bd4`–`0x100034c08`）。

`R-7.2`（MUST / CONFIRMED）事件 `0x0E` 在所有活动状态都迁移到 `Detached`（状态 1），因此 detach 与当前状态无关。

依据：`A11.3`、`analysis/06` 迁移表。

`R-7.3`（MUST / CONFIRMED）attach/detach 必须**幂等**：两者都以"参数复原"为边界，可重复执行而不改变结果。

依据：`A11.2`。

## 7.2 失败

`R-7.4`（MUST / CONFIRMED）只有事件 `0x14` 进入 `Failed`（状态 7）；`Failed` 的出边只有：`0x0c`/`0x0d` 自环、`0x0e` → Detached、`0x17` → Idle。

依据：`analysis/06` 状态 7 表。

`R-7.5`（MUST / CONFIRMED）`0x14` 在不同状态绑定不同动作：

| 状态 | 动作 |
|---|---|
| Pending | `iAP2LinkDeviceActionHandleMaxRetries`（`0x100030054`） |
| Connected / Suspend | `iAP2LinkActionNotifyConnectionFail`（`0x10003286c`） |
| Idle | `iAP2LinkActionNone`（`0x100031c50`，无副作用） |

依据：`analysis/06` 事件表（`A06.6`）。

`R-7.6`（未定义 / OPEN）`HandleMaxRetries` 的判定条件（与 `MaxRetransmissions` 的关系）未确认。

依据：`A11.6`。`OPEN-ERR-1`。

## 7.3 非法事件

`R-7.7`（MUST / CONFIRMED）非法事件（事件号越界 / 当前状态无该事件 / handler 为空）必须**不改变状态、不产生副作用**，只允许写日志。

依据：`A06.7`（`iAP2FSMHandleEvent`：`0x100006418`、`0x10000644c`、`0x10000664c`）。

`R-7.8`（MUST / CONFIRMED）事件表尾部的"全零条目"是容量填充；表中的 handler 为空但事件号非零的条目是"死条目"（`R-5.4`），二者都必须按"不认识此事件"处理。

依据：`A06.4`（空 handler 的 5 条：Idle `0x05/0x08/0x0b/0x0c`、Connected `0x08`）。

## 7.4 RST

`R-7.9`（MUST / CONFIRMED）发 RST 前的复位顺序：`reset_seq_ack(link, 0, 0)` → 复原 SYN 缺省 → 复制调用方 SYN 参数 → 比较 `link[0x1d0]` 与 `11`。

依据：`A07.10`、`A11.8`。

`R-7.10`（未定义 / OPEN）`link[0x1d0]` 的语义（疑为重试计数）与 `11` 比较的用途未确认。

依据：`A07.10`。`OPEN-IDPS-3`。

## 7.5 销毁

`R-7.11`（未定义 / OPEN）`iAP2LinkDelete`（`0x1000347b0`）的析构顺序未确认。实现须自行保证：先停定时器、再清链表、最后释放，且要能与"正在发送"并发安全。

依据：`A11.7`。`OPEN-ERR-2`。

## 7.6 挂起 / 恢复

`R-7.12`（MUST / CONFIRMED）挂起由事件 `0x1b`（`iAP2LinkDeviceActionSendSuspend` `0x10003021c`）触发 `Connected → Suspend`；恢复由事件 `0x1c`（`iAP2LinkDeviceActionSendResume` `0x1000302a0`）触发 `Suspend → Connected`。

依据：`analysis/06` 表。

`R-7.13`（未定义 / OPEN）挂起期间对已排队数据、定时器、时间同步的处理未确认。

依据：`A11.7`。`OPEN-ERR-3`。

## 7.7 未决项

| ID | 内容 |
|---|---|
| `OPEN-ERR-1` | `HandleMaxRetries` 判定 |
| `OPEN-ERR-2` | `iAP2LinkDelete` 析构顺序 |
| `OPEN-ERR-3` | Suspend/Resume 的队列与定时器处理 |
| `OPEN-ERR-4` | 错误是否上报上层 |
## 本章依据

| 条款 | 分析结论 | 关键地址 |
|---|---|---|
| `R-7.1` | `A11.1` | — |
| `R-7.2` | `A11.3` | — |
| `R-7.3` | `A11.2` | — |
| `R-7.5` | `A06.6` | — |
| `R-7.6` | `A11.6` | — |
| `R-7.7` | `A06.7` | — |
| `R-7.8` | `A06.4` | — |
| `R-7.9` | `A07.10`、`A11.8` | — |
| `R-7.10` | `A07.10` | — |
| `R-7.11` | `A11.7` | — |
| `R-7.13` | `A11.7` | — |

> 上表由条款正文的 `A` 编号与地址自动汇总；逐条依据见各条款下方的"依据"行。
