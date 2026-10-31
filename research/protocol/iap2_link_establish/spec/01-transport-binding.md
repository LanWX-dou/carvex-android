# spec/01 — 传输绑定与运行循环

## 1.1 对象层次

`R-1.1`（MUST / CONFIRMED）实现必须保持三层：**link → runloop → transport**。

```
transport  : 由平台提供（RFCOMM / socket / USB），持有真实 I/O
runloop    : 事件泵，字段 +0x10 = transport，+0x18 = link
link       : iAP2 链路，字段 +0xb0 = runloop
```

取 transport 的唯一合法路径是 `link[0xb0] → [0x10]`；链路层不得缓存 transport。

依据：`A01.1`（`iAP2LinkRunLoopCreate` `0x1000cae90`–`0x1000cae9c`、`iAP2LinkCreate` `0x1000340a8`、`iAP2LinkConnectedCB` `0x100103970`）。

`R-1.2`（MUST / CONFIRMED）对象大小：runloop 头 **0x60** 字节，其后紧跟链路缓冲；链路对象 **0x268** 字节。

依据：`A02.1`（`0x1000cae7c`–`0x1000cae8c`）、`A02.2`。

## 1.2 运行循环单步

`R-1.3`（MUST / CONFIRMED）`run_once()` 每次处理一个事件位掩码，返回 0 表示已关闭：

| 位 | 动作 |
|---|---|
| `0x0001` | `link_attached()` |
| `0x0002` | `link_detached()` |
| `0x0004` | `link_suspend()` |
| `0x0008` | `link_resume()` |
| `0x1000` | `link_renegotiate(param)` |

依据：`A02.3`（`iAP2LinkRunLoopRunOnce` `0x100008698`：`0x1000086d4`–`0x100008748`）。

`R-1.4`（MUST / CONFIRMED）运行循环关闭标志是 `runloop[0x2c]` 的 bit0；置位后 `run_once` 直接返回 0。

依据：`A02.3`（`0x1000086b8`–`0x1000086c4`）。

`R-1.5`（未定义 / OPEN）驱动源（线程/队列/定时器）未确认。实现必须把 `run_once` 的调用点做成可配置，不得假设固件的调度方式。

依据：`A02.7`。`OPEN-INIT-1`。

## 1.3 发送路径

`R-1.6`（MUST / CONFIRMED）发送只有一个出口，顺序为：

1. 计数：`link.packets_sent++`（`+0x20c`）、`link.bytes_sent += frame_len`（`+0x204`）；
2. 若控制位 bit6（ACK）置位：`hdr[6] = link.hdr6_byte`，并置 `link.flags |= 0x08`；
3. 记录 `packet.timestamp = now_ms`，累计 RTT 差值到 `link+0x254`；
4. 若控制位 bit6 置位：取消重传定时器并把 `link.timer_reload = 0xFF`；
5. 调用传输完成回调（两选一，由调用方标志决定）；
6. 若为数据帧且本地非"无重传"：启动 ACK 定时器（id `0xC`，时长 `SYN[0x06]` 毫秒）。

依据：`A01.3`、`A01.4`（`__iAP2LinkSendPacketCommon` `0x100007914`）。

`R-1.7`（MUST / CONFIRMED）发送完成回调有两个入口，行为相同：普通入口 `0x100008a44`、等待型入口 `0x10019c120`（后者直接跳转到前者）。

依据：`A01.5`。

## 1.4 接收路径

`R-1.8`（MUST / CONFIRMED）接收数据必须按"服务号 → 会话"路由；找不到会话则丢弃。

```
session = link_get_session(link, service)
if (!session) drop
else transport.deliver(session, data, len)
```

依据：`A01.2`、`A10.1`（`iAP2LinkDataReadyCB` `0x10019bfac`：`0x10019bddc` 起）。

`R-1.9`（MUST / CONFIRMED）接收缓冲的第一步是逐字节解析器；解析器按 `packet[0x3d]` 的状态分派，首字节 `0xFF` 进入 iAP2 分支、`0x55` 进入传统分支。

依据：`A03.12`、`A07.5`（`iAP2PacketParseBuffer` `0x10000a5d0`）。

## 1.5 attach / detach

`R-1.10`（MUST / CONFIRMED）attach：复原 SYN 缺省参数 → 投 FSM 事件 `0x01`；detach：投 FSM 事件 `0x0E` → 复原参数。二者必须幂等。

依据：`A02.4`、`A11.1`、`A11.2`。

## 1.6 传输接口契约（iAP2 半边）

本节定义"把 iAP2 链路接到任意字节流传输"时必须满足的接口。传输侧实现（RFCOMM/os_channel/fd 细节）见蓝牙 docset，本节只约束触点行为。

`R-1.11`（MUST / CONFIRMED）**接收必须是字节流，不得依赖帧边界**：链路侧的解析器按字节消费（`iAP2MsgParserConsumeByte` 语义），传输可以任意切分，接收方不得要求"一次回调恰好一帧"。

依据：`A09.4`、`A15.5`。

`R-1.12`（未定义 / OPEN）**一次接收回调的缓冲生命周期**未取证：实现必须在回调返回前消费或拷贝，不得把调用方指针留到回调之后使用。

依据：`A15.6`（只能证明数据就绪后被消费，不能证明链路侧是否持有指针）。

`R-1.13`（MUST / CONFIRMED）**发送上限以建链参数为默认值（本轮实测 `0xFFFF`），不是传输单块上限**；传输若不能一次承载，必须自行切块，链路层不分片。

注意：`0xFFFF` 是**本地建链默认值**（`A15.5`），实际可用上限还受 SYN 协商结果（`+0x16c` 一族）与接收方包长约束，未证部分见 `OPEN-FRAME-7`。

依据：`A15.1`–`A15.5`、`A15.5a`。

`R-1.14`（未定义 / OPEN）**attach / detach 的触发者**未取证：实现必须提供显式的 attach/detach 入口（不得靠"读到 EOF"隐式完成），但"由谁在何时触发"属未决项 `OPEN-TX-3`。**EOF 或传输错误可以作为触发信号，但不得视为已完成 detach**：实现必须仍需执行显式 detach 流程（投事件 `0x0E` 并释放资源）。

依据：`A15.1`（只证明绑定顺序，不证明触发者）、`spec/05` 状态表。

`R-1.15`（未定义 / OPEN）**传输错误如何上报、断线后是否自动重连**未取证；实现须把错误与重连策略做成可配置项。

依据：`A15.7`、`OPEN-TX-1`。

`R-1.16`（未定义 / OPEN）**传输对象的生命周期与线程模型**（谁在哪个队列上调用接收回调）未取证；实现须显式串行化收发。

依据：`A15.7`、`OPEN-TX-2`。

`R-1.17`（MUST / CONFIRMED）**不要把 RFCOMM 的 N1 当作 iAP2 帧上限**：iAP2 帧必须遵守有效建链参数；适配层以实际平台 API 发送并处理部分写，接收侧按帧头长度跨块重组。`min(N1,2570)=1007` 是特定 iOS 内部队列/N1 配置的保守块长，不是通用 socket 上限。传输切块不能改变 iAP2 帧的长度或校验。

依据：`A15.4`、`A15.5`；蓝牙侧 N1/`os_channel` 单块上限引用 `research/protocol/bluetooth_rfcomm/` 的对应结论（不在本文件重复）。

## 1.7 未决项

| ID | 内容 |
|---|---|
| `OPEN-TX-1` | 平台传输（RFCOMM/`os_channel`/USB）到解析器的具体注册点 |
| `OPEN-TX-2` | `acc_protocolParser_iAP2_run` 的 11 个命令码语义 |
| `OPEN-TX-3` | Attached 位的置位者 |
| `OPEN-TX-4` | `link[0xbc]`（写入 `hdr[6]` 的字节）的来源 |
| `OPEN-INIT-1` | 运行循环驱动源 |

## 本章依据

| 条款 | 分析结论 |
|---|---|
| `R-1.1` | `A01.1` |
| `R-1.2` | `A02.1`、`A02.2` |
| `R-1.3` | `A02.3` |
| `R-1.4` | `A02.3` |
| `R-1.5` | `A02.7` |
| `R-1.6` | `A01.3`、`A01.4` |
| `R-1.7` | `A01.5` |
| `R-1.8` | `A01.2`、`A10.1` |
| `R-1.9` | `A03.12`、`A07.5` |
| `R-1.10` | `A02.4`、`A11.1`、`A11.2` |
| `R-1.11` | `A09.4`、`A15.5` |
| `R-1.12` | `A15.6` |
| `R-1.13` | `A15.1`、`A15.5`、`A15.5a` |
| `R-1.14` | `A15.1` |
| `R-1.15` | `A15.7` |
| `R-1.16` | `A15.7` |
| `R-1.17` | `A15.4`、`A15.5` |

> 上表由条款正文的 `A` 编号自动汇总；逐条依据见各条款下方的"依据"行。
