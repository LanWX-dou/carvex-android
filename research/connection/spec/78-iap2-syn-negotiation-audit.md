# 78 — SYN/SYNACK 参数提供者、再次协商与提交边界


后续实施见[79](79-iap2-renegotiation-batch.md)：有界pending再次协商已修改手机并通过完整模块897项回归。本章及JSON、16个探针保留修改前观察；其源码哈希检查/探针预期不适用于修改后的手机。原固件字节复核仍独立有效。

## 1. 结论与下一步

最值得修的是**再次协商模型缺失**，不是再找一个车型参数表：

1. 我们的第二份 SYNACK 与“对端第一份提议”比较，而不是与“当前协商结果”比较。对端接受了我们自己的修改，也可能被拒绝。已用当前源码的内存报文测试复现。
3. 24A446 有独立的本地能力模板、协商工作区和生效区；收到 SYNACK 后做条件分类、校验/修正、按字段合并，在 pending 内发送下一份 SYNACK，另经确认事件提交。不是“参数变化就断开”，也不是“收到带 ACK 的包就完成”。
4. 原生默认模板与我们确实不同，但模板数值不等于每次上车实际发送值。先实现协商语义，再审平台能力与默认上限，不能盲目把 window 改为127或宣称所有 session/扩展都已实现。

建议下一批只改手机 `IapLink` 的 pending 协商状态及回归测试；不改首次 Detection/SYN 发起策略、不增加车型开关。全量 Identification 三方核对应排在这项之后。上层 XPC/睡眠/电源通知追踪暂停在77的边界，除非新的失败证据重新指向它。

## 2. 一个已复现的错误拒绝

```text
车机第一份 SYN：重传超时 2000 ms
    → 我们 SYNACK：min(本地1000, 对端2000) = 1000 ms
    → 车机第二份 SYNACK：1000 ms，ACK 正确关联当前回复
    → 我们：与第一份2000比较，抛出 SYNC_RENEGOTIATION_REQUIRED
```

这是测试 N02，不是实车抓包；它证明当前实现拒绝这类输入，不能据此认定某辆未连接车辆就是此原因。

同类已复现：累计 ACK 超时500→我们回复10→对端回复10（N14）；maxCumAck 3→我们回复0→对端回复0（N15）；对端原有两个session→我们只回control→对端也只回control（N10）。这些字段既然由我们主动修改，就必须支持对端对修改作出响应。

原生本地模板的重传上限是65535，**不会在同一个2000 ms输入上自动提出我们自己的1000 ms**。原生对“2000后再收到1000”的静态路径是 event6→重新协商；我们的例子用来说明比较对象错误，不伪称执行过iPhone或双方初始配置相同。

手机定位：[`IapLink.kt`](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:448)，尤其第二SYNACK门 `second.copy(maxPacket=peer.maxPacket,sessions=peer.sessions)==peer`；`peer`始终是第一份提议。接受后直接发纯ACK并提交，当前还没有继续发送新提议的分支。

## 3. 参数来自哪里

以下区分本地模板、对端声明与实际回复，不能混用。

|---|---|---|---|
| link版本 | 接受1..3；回复对端版本 | decoder只接受1；首发1 | 模板上限3，最低版本1；协商取较小版本 |
| 本地window | 默认1，构造许可1..32 | 初始SYN为4；回显SYNACK改成127 | 模板127，并以127/65535分配runloop所需buffer |
| 本地接收MTU | 默认65535，与对端发送限制分开 | 回显对端MTU作为本方MTU | 模板65535；协商另存对端MTU |
| 重传/累计ACK超时 | 本地1000/10，与首提议取min | 首发4000/500；SYNACK回显对端值 | 模板65535/32767；与当前工作区逐轮取min |
| 重传次数/maxCumAck | 默认30/0；次数取min，maxCumAck用本地值 | 首发4/3；SYNACK回显对端值 | 模板30/127；逐轮取min |
| session | 仅回复选定control；只支持control v1/v2 | 首发(10,0,2)、(11,2,1)、(12,1,2)；回显对端表 | 模板sessionCount=0；按kind的最大版本[2,2,1,1,1]、最小版本[0,0,0,0,0]用于校验/修正，协商工作区保存处理后的对端表 |
| 扩展 | link2/3验证集合；本地回复不声明扩展 | 该decoder不支持link2/3 | 本地内存模板与线端结果分离；device协商复制处理后的对端扩展 |



### 3.1 原模板与构造实参

`iap2_endpoint_create@0x100129350` 从原常量 `0x1001b32c0` 取前4字节 `03 7f 1e 7f`；从`0x1001b32c8`取`02 02 01 01`，第五kind的max另写1；MTU/retrans写ffff，ACK timeout写7fff。`CreateDevice@0x1000cae38` 把role置1；`RunLoopCreate@0x1000cae54`传给`LinkCreate@0x100033fd0`，最低版本实参为1，构造校验flag为0。device角色仍在CheckNegotiation中调用参数修正，不因该flag为0跳过。

模板不是一份可直接照发的SYN：sessionCount初始为0；calloc零初始化后，`0x100129488..490`把模板`+0x18`写为3、`+0x19..1b`为`54 55 00`。这是内存构造事实，**不代表线上发送三项扩展，也不代表00通过feature谓词**。收到提议后，Validate/CheckNegotiation重建工作区扩展。不要把内存模板、有效性谓词与最终wire payload当成同一份数据。

## 4. 原生的参数工作区

以下为内部结构偏移，不是线端报文偏移：

| 数据 | link内位置 | 作用 |
|---|---|---|
| 本地profile指针 | `+0x160` | 本地能力、session版本边界；新SYN重启时恢复的来源 |
| 协商工作区 | `+0x168`，长度0x32 | 当前提议，下一轮在其基础上继续合并 |
| 已生效区 | `+0x19a`，长度0x32 | 当前链路使用值；不能提前被未确认提议替换 |

工作区参数相对偏移：`+0`版本、`+1`本地方window、`+2`重传次数、`+3`maxCumAck、`+4`本地MTU、`+6`重传timeout、`+8`ACK timeout、`+a`session数、`+b/+c`对端window/MTU、`+18/+19`扩展数/数组、`+1e`四字节内部session记录。

### 4.1 收到第二份 SYNACK：分类不是提交

`ProcessInOrderPacket@0x10000b690` 在长度/ParseSYNData门之后调用 `IsValidSynParam@0x1000328dc`。有效SYNACK在`0x10000bb14..bb70`与**当前工作区**比较六项：link版本、重传timeout、ACK timeout、重传次数、maxCumAck、session数量。

window、MTU、session描述符内容、扩展数组不在这六项相等比较中；它们仍有其他校验和合并路径，不能据此说苹果忽略它们。

在device状态4（pending）的已审事件表中：

| 输入分类 | 事件 | 本状态动作与后继 |
|---|---|---|
| 有效、六项相等且ACK命中当前已发送PSN | 4 | SendSYNACK，仍为4；不是直接ready |
| 参数不一致/无效等，且未选noRetransmit特殊门 | 6 | SendSYNACK→Parse→CheckNegotiation，仍为4 |
| 六项相等但ACK不命中 | 5 | 无对应动作；本次FSM dispatch不改变状态 |
| 当前work为noRetransmit、输入转可靠等特殊分类 | 7 | 无对应动作；本次FSM dispatch不改变状态 |
| 新PSN的纯SYN | 2 | ResetSYNACK，从本地profile重建工作区，仍为4 |
| 同PSN的纯SYN | 3 | ResendSYNACK，仍为4 |
| 重传timer | 12 | ResendSYNACK，仍为4 |
| 确认路径产生连接事件 | 21 | NotifyConnection，转5，工作区提交到生效区 |
| 确认参数不可用 | 22 | 对应失败动作，转3 |
| 提议/收包等预算用尽 | 20 | 对应终止动作，转7 |

`FSMHandleEvent@0x10000639c`核对了无匹配/空handler的行为：跳过action和state写入、结束本次dispatch。**这不取消既有timer，也不保证之后永不失败。** event6也覆盖部分无效/解析异常分类，不可把它统一命名为“合法参数修改”。到达该表前还存在帧、顺序、ACK窗口等门；上表不是跳过这些门的无条件处理规则。

ACK路径另见`HandleReadyPacket@0x10000ada0`以及`ProcessInOrderPacket@0x10000b9e8..ba7c`：纯ACK形状、工作参数重建/有效性及对端MTU界限都参与处理。不能因为一个ACK bit就提交，也不能把纯ACK路径简化成与六字段SYNACK比较完全相同。

### 4.2 按字段合并，而不是整个payload回显或整体判等

`CheckNegotiation@0x100035154`的device分支先调用`ValidateSynParam@0x1000333f4`；后者返回false时会发通知code3，但本函数仍继续其后的合并，返回false不等同在此直接拆链。

普通可靠模式的核心处理：

| 字段 | 此轮合并行为 |
|---|---|
| link版本、两项timeout、retries、maxCumAck | 处理后的输入与当前work取min |
| 本地方window、本地接收MTU | 普通可靠路径保留本地值，不用对端值覆盖 |
| 对端window/MTU | 更新单独保存的peer字段，而非永远保留第一份值 |
| session数量和描述符 | 复制校验/修正后的输入表；相等比较只看数量不等于这里丢弃内容 |
| 扩展 | device路径复制处理后的数量与数组 |

noRetransmit有独立分支：若当前work是noRetransmit而被处理的输入为可靠，函数内存在恢复默认window1/retries30/MTU65535/retrans1000/ACK10/maxAck0的代码；输入noRetransmit时还会复制本地方window。**函数内存在不表示pending第二SYNACK必然可达**：分类可能先产生event7，状态4没有其动作。该切换不能直接套普通可靠路径。

`SendSYNACK@0x10002fcd4`依据当前work构造下一包，提议计数独立于重发计数。原发送函数在新发送路径用报文PSN更新`link+0xbe@0x100007ad4`；SYNACK构造使用其下一值。重复SYN/timer重发与生成新提议应分开，不可用重协商无限重置预算。

`NotifyConnection@0x10003009c`才将0x32字节work复制到active，切换版本并通知connected。按原LC_FUNCTION_STARTS，它在`0x100030128`结束；旧反编译文本越过这一边界的内容不能算该函数自身行为。

### 4.3 有效性检查与修正是两件事

`IsValidSynParam`是分类用谓词；`ValidateSynParam`在到达对应动作后会钳制部分数值、按profile调整session版本、处理非法/重复描述符和扩展。这与Android严格拒绝无效报文有边界差异，不能把77的feature谓词表理解成苹果所有状态下的最终处置表。

具体限制：session版本越界修正分支先于普通重复检查；汇编显示该分支不经过同一重复ID/type循环。control补齐条件也受先前见到的kind0标志影响。故这里不把原函数概括成“任何坏表都能修成合法表”，更不建议取消Android的长度/数量/重复/实际支持能力保护。

扩展修正`CommandValidateFeatureSets@0x1000d4f44`与77所审`IsFeatureSetValid`不同：前者在mask含任一已知位时写出`54 55`并设count2，没有已知位时count0，另保存mask；后者判mask是否为0或3。两者调用阶段不同。是否、何时容错这些输入，以及扩展实际业务实现，保留为后续独立合同，本批不放宽生产解析器。

原ParseSYNData对部分数量做截断、link1按完整三字节数计算session；不能以复刻为名照搬潜在截断/不完整解析。保留安全边界不妨碍修复合法输入的再次协商。

## 5. 16个真实实现探针


| 用例 | 第二轮变化 | 手机结果 |
|---|---|---|
| N01 | 不变 | 完成 |
| N02 | 接受我们提出的retry1000 | 错误拒绝 |
| N03/N04 | retry100→50 / 200 | 拒绝再次协商 |
| N05 | peer window5→7 | 拒绝再次协商 |
| N06/N07 | peer MTU2048→1024 / 4096 | 均完成；TX限制分别为1024 / 2048 |
| N08/N09 | control ID10→11 / version2→1，数量不变 | 拒绝再次协商 |
| N10 | 接受我们提出的control-only列表 | 错误拒绝 |
| N11 | 同一session集合重排 | 完成 |
| N12 | 未变化参数但错误ACK | 正确拒绝；不能为了兼容放弃关联保护 |
| N13 | 正确纯ACK对照 | 完成 |
| N14/N15 | 接受我们提出的ACK timeout10 / maxCumAck0 | 错误拒绝 |
| N16 | retries30→2 | 拒绝再次协商 |



## 6. 可实施、应保留与未闭合

### 下一批可直接据此设计

1. 将“本地能力、当前pending提议、peer接收限制、active参数”显式分开，第二轮以当前work为基准。
2. 普通可靠且本机实际支持的字段变化，按原字段规则生成新SYNACK；保持pending，正确确认后一次性提交generation/session/版本，不能删掉guard后照旧直接ready。
3. fresh SYN重建work；第二SYNACK继续work；重发复用原提议。序号回绕、旧ACK、新提议预算、重传预算和取消必须各有测试。
4. 会话变化必须同步影响后续Control schema/Identification启动次序；不只改线上数字。未实现服务和54/55业务不可仅因对端声明就自动承诺。

### 不能直接照搬

- window127与buffer预算、排队/重传能力绑定；现手机构造上限32，先保留真实能力，不改数值冒充实现。
- 原生65535/32767等是能力模板上限，不是要求每个连接固定用此超时；本地1000/10也不能再被无依据称为原生profile。

### 验收与剩余边界

实施前先把N02/N10/N14/N15改成期望的pending→新SYNACK→确认→提交行为测试，再覆盖参数变更、同值再次提议、超限提议、重复/timer、错误ACK、旧世代、断开取消、noRetransmit、link1/2/3与frame版本切换。已有测试预期若与原生不同，应说明修改原因，不能仅增加通过数量。

本批闭合的是指定device路径的模板来源、第二SYNACK分类/合并/提交静态链和两实现16个输入的实际表现。所有transport入口、same-PSN改payload组合、noRetransmit完整状态组合、扩展业务、全session服务、全Identification及实车互通仍非完成。修复能去掉已复现的兼容性障碍，不能承诺连接所有车型。

## 7. 证据与复核

- [只读复核器](../tools/verify_iap2_negotiation.py)：重新读原镜像、缓存、表项/常量；`--check-implementations`额外核对13个源码快照及研究探针工具。
- 最终只读复核通过：20/20函数及既有缓存一致、993条指令锚点、8状态/93记录、13份实现源码、3份研究工具；16个探针结果已存档。文档完整性检查通过：48份Markdown、40份JSON。复核器只核对已存探针结果结构，不替代重新运行探针。

字节/哈希复核不是语义的自动证明；静态状态表不是实机时序。后续实施必须另外记录修改快照、本地回归和实际车机验收，不覆盖本章的修改前观察。
