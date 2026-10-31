# 11 — iAP2 Detection、SYN 与重传状态机

状态：`PARTIAL`；下文有明确地址/范围的局部静态事实可记为 `CLOSED-STATIC`，不代表整个 iAP2 链路规范已闭合。基线为 24A446 `accessoryd`；不是运行捕获，也不是“任何车机都按此顺序”的互通保证。证据见 [iap2-state-evidence.json](../evidence/iap2-state-evidence.json)。

本章专门补充 [10 — 蓝牙、iAP2 与网络建立](10-bluetooth-iap2-network.md) 中的 `B-OPEN-02`。它回答的是：原固件把 Detection、SYN/SYNACK、ACK 和重传分别归给哪个状态/计时器。连接方向仍须在同一 `attempt_id` 的双端字节流中确认。

## 1. 先分清三层

| 层 | 本章能确认的边界 | 不能据此推出 |
|---|---|---|
| 传输 attach | `iAP2LinkDeviceActionAttach`（`0x10002f8dc`）写入事件字节 `0x1d`，调用 `iAP2LinkSetDefaultSYNParam`（`0x1000328b0`） | attach 会自动发 Detection、SYN 或 SYNACK |
| 传统检测帧 | `iAP2LinkSendDetectCB`（`0x10019c124`）在 callback 参数为 0 时取常量并发送；检测状态表另有事件 `0x17` 进入该动作 | 检测帧就是 iAP2 SYN，或每个 profile 都必须先发它 |
| iAP2 链路帧 | SYN 解析/协商、SYNACK 构造、ACK 和数据重传走 `iAP2Packet*`/`iAP2Link*` 路径 | 一次 `send()`、一个 ACK 位或一个本地 state 就等于车机已接受 |

`accessoryd` 内部状态表不是线上字段。表中 handler 指针和 next-state 是本地 FSM 调度资料；线上必须记录真正的帧方向、序号、确认号、链路世代和结果。

## 2. Detection：固定 6 字节，触发点不是 attach

### 2.1 静态常量

原镜像 `0x1001b3378` 起的 10 个字节为：

```
FF 55 02 00 EE 10 00 00 06 00
```

`iAP2LinkSendDetectCB` 从 `0x1001b3378` 取数据指针，`0x10019c1a0` 的 `ldrh` 从 `0x1001b3380` 读取本机小端 u16：内存 `06 00` 为长度值 `6`，随后调用发送包装。这是本地元数据的端序，不是在线帧中附带该长度。因此本次静态可证的线上 Detection 帧是前 6 字节：

```
FF 55 02 00 EE 10
```

末尾的 4 字节是相邻长度/填充，不属于发送帧；不得把 10 字节整体复制到线上。`FF 55` 只表示传统 iAP 帧前导，不能当作 SYN 头。

### 2.2 状态表布局与 Detection 状态

状态表根地址 `0x100219600`，共 8 项；每项 16 字节，`u64+0` 是事件表指针（链式指针规则为 `0x100000000 + (raw & 0xffffffffff)`，raw=0 时保持 NULL），`u8+8` 是事件数量。原始 128 字节切片 SHA-256：`d841f9404b1f2a4af4367444666ba97e43f0e811ab849729ae0f612edc468fdd`。

状态 2 的事件表指针是 `0x100219060`，计数是 **29（0x1d）**。其中只有下列 5 项有非空 handler；其余 24 项是零槽。零槽并不代表“执行一个隐含动作”：FSM 命中空 handler 时不会调用动作，也不能把它解释成状态迁移。

| 当前状态 | 事件（十六进制） | handler | next-state | 静态可读语义 |
|---:|---:|---:|---:|---|
| 2 | `0x02` | `0x10002f920` | 4 | 收到 SYN 后 Reset + SYNACK 路径 |
| 2 | `0x0e` | `0x100031c7c` | 1 | detach/断开动作 |
| 2 | `0x17` | `0x10002fac8` | 3 | SendDetect |
| 2 | `0x19` | `0x10002fb54` | 3 | RST 路径（动作名仍以原函数为准） |
| 2 | `0x0f` | `0x10002fb54` | 3 | RST 路径（同一 handler） |

因此，`Attach → 自动 Detection` 不是这张表能支持的结论：Attach 只初始化 SYN 默认参数并投递内部事件；在状态 2 中，Detection 是事件 `0x17` 选择 `SendDetect` 后才发生。`0x10002fac8` 会清发送/序号相关状态、调用 `SendDetectCB(...,0)`；`SendDetectCB(...,1)` 走日志/非发送分支。

## 3. SYN 解析、协商和提交

### 3.1 `ParseSYNData` 可读字段

`iAP2PacketParseSYNData`（`0x100103230`）要求载荷长度至少 10；它将线上字节转换到内部工作块。可直接从指令读出的布局为：

| 线上载荷偏移 | 宽度 | 进入工作块 | 备注 |
|---:|---:|---:|---|
| 0 | 1 | `+0` | version/版本字节 |
| 1 | 1 | `+1` | MOP / MaxOutstandingPackets；校验入口 `0x100033114`，不是能力位图 |
| 2–3 | 2，大端 | `+4` | 语义仍 `OPEN-SYN-1` |
| 4–5 | 2，大端 | `+6` | ACK timer；发送公共路径把它作为 timer 延迟（毫秒时基） |
| 6–7 | 2，大端 | `+8` | 累积 ACK 相关值；完整触发规则仍 OPEN |
| 8 | 1 | `+2` | MR/重传上限候选；版本/模式影响其有效性 |
| 9 | 1 | `+3` | MCA/窗口候选；版本/模式影响其有效性 |
| 10 及以后 | 变长 | `+0x18`、`+0x19`… | v1 及以上扩展/条目；每条 3 字节的完整语义仍 OPEN |

函数在字节 0 为 0、字节 0 为 1、以及更高版本时分别采用不同的条目处理；条目数被限制到 5。不能把缺省向量当成车机必发常量。

### 3.2 缺省值与协商

`iAP2LinkSetDefaultSYNParam`（`0x1000328b0`）写入的内部缺省包括：版本字段 `1`、`+4=0xffff`、`+6=0x03e8`、`+8=0x000a`、扩展计数为 0，以及内部初始化的 MR/MCA 材料。这里的 `0x03e8` 只有在被发送公共路径作为 `link+0x1a0` 延迟使用时，才可称为 ACK timer 的毫秒数；不能把所有字段都命名成标准常量。

`iAP2LinkCheckNegotiation`（`0x100035154`）会按当前模式/版本分支检查对端工作块，保存对端 MOP、包长、MR/MCA 和 timeout 的收紧结果；无重传模式下还可能写入本地 fallback。`iAP2LinkNotifyConnection`（`0x10003009c`）再把工作块 50 字节提交到生效块，并保存 checksum 宽度字段。工作块提交前不能进入“协商完成”结论。

## 4. 状态 3/4：SYNACK 初次发送、重发和连接提交

状态表中与 SYNACK 最相关的局部路径如下；未列出的 null handler、错误出口和上层驱动仍保持 OPEN。

| 当前状态 | 事件 | handler | next-state | 可证行为 |
|---:|---:|---:|---:|---|
| 3 | `0x02` | `0x10002f920` | 4 | ResetSYNACK：复位发送/序号，解析并协商对端 SYN，构造 SYNACK |
| 3 | `0x04` / `0x06` | `0x10002fcd4` | 4 | SendSYNACK：使用当前工作块，构造并发送 |
| 4 | `0x02` | `0x10002f920` | 4 | 再次走 ResetSYNACK |
| 4 | `0x03` / `0x0c` | `0x10002feb0` | 4 | ResendSYNACK：检查重发计数，再发送或耗尽 |
| 4 | `0x14` | `0x100030054` | 7 | 最大重试/失败处理候选；完整退出语义 OPEN |
| 4 | `0x15` | `0x10003009c` | 5 | NotifyConnection：提交协商块并通知 Connected |
| 4 | `0x0e` | `0x100031c7c` | 1 | detach/断开 |

两条容易混淆的预算必须分开：

- `SendSYNACK` 在 `0x10002fcd4` 中增加 `link+0x1d0` 及相关发送计数；非特定模式下计数达到 `0x0b` 会把事件槽写为 `0x14`。这不是 ResendSYNACK 的预算。
- `ResendSYNACK` 在 `0x10002feb0` 中比较 `link+0x1d8` 与协商/配置的 `link+0x19c` 上限；未达到时递增 `0x1d8` 并发包，达到时转耗尽事件。不能把 `0x0b` 写成苹果统一“重试 11 次”，也不能用 `0x1d8` 解释所有 SYNACK 发送。

`ResetSYNACK` 与 `SendSYNACK` 都可能经过 `ParseSYNData → CheckNegotiation`；区别在于前者先做 reset/恢复调用方工作块，后者在已有工作块上继续。两者的精确进入条件由状态表和上层事件共同决定。

## 5. ACK、序号和计时器归属

### 5.1 发送公共路径

`iAP2LinkSendPacketCommon`（`0x100007914`）是本组静态证据中的发送出口：

1. 记录/更新发送统计和当前包时间。
2. 若包 flags 的 ACK 位（bit 6）置位，使用 `link+0xbc` 覆写包头 ACK 字节，并取消 `link+0xc8` 上的 timer id `link+0xc2`；这只说明 ACK 位对应的本地 timer 操作，不等于取消所有重传。
3. 对需要可靠发送且不处于 no-retransmit 模式的数据包，读取生效 SYN 的 `link+0x1a0`（`u16`）作为延迟，调用 `iAP2TimeCallbackAfter`（timer event `0x0c`），再把返回 timer id 绑定到包。
4. 接收路径若尚未注册累积 ACK timer，则使用 `link+0x1a2`（对应生效 SYN 的 `+8`）创建独立的 timer event `0x0d`；发送 ACK 位的包会取消该 link 级 timer。`0x0c`（待确认包/重传）和 `0x0d`（累积 ACK）不可合并。
5. `iAP2PacketCreateSYNPacket`（`0x100102fdc`）从传入的 `seq/ack` 及工作块生成 SYN/SYNACK；其 ACK 形式由调用者选择 `0x80` 或 `0xc0`，不是该函数单独决定的线上成功。

计时器容器属于 link；timer id 附着 packet，超时事件再通过 run loop 投递到当前 FSM。事件 `0x0c/0x0d/0x1a/0x0b` 在 run loop 中分别映射到不同的超时位，不能把所有超时都归为“重发 SYN”。

### 5.2 序号缓存与重发

`SendSYNACK`/`ResetSYNACK` 在构造前生成新序号；发送公共出口会把实际使用的序号写入包/链路相关缓存（`link+0xbe` 等）。`ResendSYNACK` 重新构造时使用当前缓存和计数路径，不能每次超时都无条件分配一个新的独立会话序号。

`iAP2PacketIsSeqACKd`（`0x10000b5c0`）本身只做一个有界的序号窗口比较；ACK 是否对应某个待确认包还要结合包队列、方向、链路世代及上游 `HandleReadyPacket`/`ProcessInOrderPacket`。因此：

- 单看 ACK 位不能证明 SYNACK 已被车机接受；
- 单看本地 state=5 不能证明对端收到所有先前包；
- 旧实验中“迟到 ACK 仍可进入后续状态”的结果只能作为测试线索，不能升级为 24A446 量产线上行为。

## 6. 可执行的抓包/日志验收

每个 attempt 至少记录以下字段，且按链路世代隔离：

| 记录 | 最低字段 |
|---|---|
| Detection | 承载、方向、`FF550200EE10` 的长度/哈希、触发事件（若可见） |
| SYN/SYNACK | flags、seq、ack、payload 长度、SYN 版本、`+4/+6/+8` 协商值、方向 |
| ACK | 其确认的链路世代、确认号、是否命中待确认包；不能只记“ACK received” |
| Timer | owner link、timer id、event、delay 来源、创建/取消/超时时间 |
| Reset/Detach | 事件、状态前后、发送队列和重组/回调是否清理 |

G3 的运行验收须按当前承载/分支记录适用的 Detection（若有）、完整 SYN/SYNACK/ACK 协商及后续识别/认证的进展证据，均关联到同一 link 与 attempt。不能要求每个 profile 都双向发送 Detection；车机后续响应也可提供对端继续处理的证据，不强求能取得车机内部日志。静态状态表本身不能关闭 G3 或宣称“已连接”。

## 7. 仍然开放

- 谁在真实 RFCOMM 适配层调用 `acc_protocolParser_iAP2_run`、何时投递事件 `0x17`，以及 Detection 的运行时超时/重发预算；
- 具体 profile 下 SYN `+4` 的名称、完整扩展条目语义和版本选择；
- 所有 transport（RFCOMM、IP/ATTACH 等）是否共享上述入口，及迁移时 connection/session 关联；
- 状态表中 null handler、事件 `0x14/0x16` 等错误/复位出口的完整线上结果；
- ACK 到底确认哪个待发包、迟到/重复/乱序 ACK 的车机端行为；
- 状态 5/6/7 的全部业务消息门槛、teardown 和重连清理。


