# analysis/02 — 会话表与数据面路由

本文件追踪一条入站数据从"链路已排序包"到"控制会话解析器"的**完整字节路径**，并把中间那个 8 位 demux 键钉死。

## 2.1 对象自证：run loop / link / endpoint 三者互指

三个对象靠指针互指，且互相印证，所以本节的结构不是猜的：

```
link+0x0b0 ──► run loop
run loop+0x010 ──► endpoint        （= 各 iap2_session* 的第一个参数）
run loop+0x018 ──► link
endpoint+0x028 ──► run loop
```

| 边 | 证据 |
|---|---|
| `link+0xb0 → run loop` | `0x10019bfd4` `ldr x8,[x0,#0xb0]`（`x0` = link） |
| `run loop+0x10 → endpoint` | `0x10019bfd8` `ldr x21,[x8,#0x10]`，随后 `0x10019c068` `mov x0,x21` 作为 `processSessionData` 第一参数，最终落到 `parseIncomingMessage` 并解引用 `[x0+0x78]`/`[x0+0xc8]` |
| `run loop+0x18 → link` | `0x10011d4bc` `ldr x8,[x0,#0x28]`；`0x10011d4d4` `ldr x19,[x8,#0x18]` |
| `endpoint+0x28 → run loop` | `0x10011d4bc` |

闭环验证：`endpoint+0x28 → runloop+0x18 → link`，以及 `link+0xb0 → runloop+0x10 → endpoint`，两条路径回到原点。因此"`parseIncomingMessage` 的第一参数就是 endpoint"不是假设。

## 2.2 入站：包 → 表项 → 数据面

### 步骤 1：取出 `hdr[7]` 作 demux 键

`_iAP2LinkActionHandleData`（`0x100032670`）：

```
0x10003268c  cbz x1 …                          ; 出参非空
0x100032694  strb w8,[x1]  (w8 = 0x1d)         ; 协议动作号 0x1D 写回
0x100032698  x19 = [x0+0x10]                   ; link
0x10003269c  x20 = [x19+0x118]                 ; 当前收包
0x1000326a0  x22 = [x20+0x40]                  ; 包头指针
0x1000326ac  [link+0x218] += w0                ; 累计收字节
0x1000326bc  [link+0x220] += 1                 ; 累计收包数
0x1000326c4  ldrb w8,[x19,#0x1a4]              ; 表项数
0x1000326c8  cbz  x8 → 0x100032724             ; 空表：不路由
0x1000326d4  ldrb w11,[x22,#7]                 ; ★ hdr[7] = 候选会话号
0x1000326d8  add  x12,x19,#0x1b8               ; 表基址
0x1000326dc  add  x13,x12,x10,lsl #2           ; 第 i 项（步长 4）
0x1000326e0  ldrb w14,[x13]                    ; 项[0]
0x1000326e4  cmp  w14,w11
0x1000326e8  csel x9,x13,x9,eq                 ; 记下最后一个相等项
0x1000326f0  subs x8,x8,#1 ; b.ne loop
0x1000326f8  cbz  x9 → 0x100032724             ; 无匹配：不路由
```

`hdr` 是 8 字节链路头上 `[x20+0x40]` 指向的缓冲区起始，`hdr[7]` 即 `iAP2PacketCreate` 产出头的第 8 字节。**这是 `hdr[7]` = 会话号的第一处证据**（读侧）。

### 步骤 2：`DataReadyCB` 再查一次表并交给路由器

`_iAP2LinkDataReadyCB`（`0x10019bfac`）：

```
0x10019bfd4  x8  = [link+0xb0]                 ; run loop
0x10019bfd8  x21 = [x8+0x10]                   ; ★ endpoint（路由器第一参数）
0x10019bfdc  x1  = x4                          ; x4 = 调用方传的 hdr[7]
0x10019bfe0  bl  #0x100032828                  ; iAP2LinkGetSessionInfo(link, 会话号)
0x10019bfe4  cbz x0 → 返回 0                    ; 查不到：丢弃
0x10019c064  w3 = len & 0xffff
0x10019c068  x0 = x21 ; x1 = x22 (表项) ; x2 = x19 (载荷)
0x10019c074  bl  #0x10006b878                  ; iap2_sessionRouter_processSessionData
```

调用方 `0x100032700`–`0x10003271c` 把 `x4` 设成 `ldrb w4,[x22,#7]`（即 `hdr[7]`），`x1` 设成 `[x20+0x48]`（载荷），`x3` 设成包对象。所以 **`hdr[7]` 从链路层一路传到会话层，中间没有任何二次映射**。

### 步骤 3：按表项类型分发

`_iap2_sessionRouter_processSessionData(transport 上下文, 表项, 载荷, 长度)`（`0x10006b878`）：

```
bVar1 = *(byte *)(param_2 + 1)        ; ★ 表项[1] = 数据面类型
0 → iap2_sessionControl_parseIncomingMessage(param_1, buf, len)
1 → iap2_sessionFileTransfer_handleDatagram(param_1, buf, len)
2 → EA:  len <  3 → 若 len==2 记录 "Received EA packet of 0 bytes, no data to process!"
                  返回 1（len==2）或 0
         len >= 3 → 会话号 = BE16(buf[0..1])；CFDataCreate(buf+2, len-2)
                    platform_externalAccessory_handleIncomingEADataFromAccessoryForSessionID
    默认 → 返回 0
4 → iap2_sessionLog_parseIncomingMessage(param_1, buf, len)
```

要点：

- 类型 `2`（外部配件 EA）**在会话号之外还有一层 16 位子会话号**（载荷前 2 字节，大端），这是本层唯一的"会话内复用"。
- 类型 `3` 没有分支：落到 `else` 链外，返回 0（**静默丢弃**）。类型数组有 5 个发送队列（0–4），但分发只实现 0/1/2/4 → `OPEN-SES-6`。
- 类型 `2` 的 `len==2` 分支把"只有子会话号、没有数据"当成正常事件返回 1，而 `len<2` 返回 0 —— 这是刻意的：EA 允许空数据包。

### 步骤 4：收包后的链路定时器

`0x1000327d8`：

```
0x1000327d8  add  x0,x19,#0x19a
0x1000327dc  bl   #0x100008590         ; iAP2LinkIsNoRetransmit(link+0x19a)
0x1000327e0  tbnz w0,#0 → 尾              ; 为真则不启动
0x1000327e4  ldrb w8,[x19,#0xc2]        ; 定时器句柄
0x1000327e8  cmp  w8,#0xff → 尾         ; 已在运行则不重复启动
0x1000327f0  x0 = [link+0xc8]           ; 定时器对象
0x1000327f4  w2 = [link+0x1a2]          ; 超时参数
0x1000327f8  w1 = 0xd                   ; 定时器类型
0x1000327fc  bl   #0x100007ce8
0x100032800  strb w0,[x19,#0xc2]        ; 记下句柄
```

这条路径**不区分会话**，是全链路共用的定时器（见 `analysis/11`）。`link+0x19a` 处是发送方向的 SYN 参数字节组，`link+0x1a2` 是其中一项超时参数，其链路层语义属上一阶段范围。

## 2.3 出站：会话号写进 `hdr[7]`

`_iAP2LinkQueueSendDataPacketInternal`（`0x10000733c`）：

```
0x100007388  ldrb w8,[x26,#0x1a4]              ; 表项数
0x10000738c  cbz  → 失败
0x100007390  mov  x10,#0 ; x9,#0
0x100007398  add  x12,x26,#0x1b8
  循环：ldrb w11,[x13] ; cmp w11,w23(会话号) ; csel x9,...
0x1000073bc  x8 = [x22+0x40]                   ; 包头
0x1000073c0  strb w23,[x8,#7]                  ; ★ 会话号 → hdr[7]
```

**这是 `hdr[7]` = 会话号的第二处证据**（写侧），而且写的就是最终发包头的第 8 字节。同一函数随后用表项的 `[1]` 选发送队列（`ldrb w8,[x19,#1]` → `[link+0x130 + type*8]`）。

另一条发送路径 `_iAP2LinkQueueSendDataWithSentCallback`（`0x100006868`）结构相同：`0x1000068b0` 读表项数，`0x1000068d4` 匹配 `项[0]==会话号`，`0x100006934` 用 `项[1]` 选队列。

控制会话发出站消息时的会话号来源见 `analysis/10`：`iAP2MsgSendCtlDataWithSentCallback`（`0x1000055e4`）以**常量 0**（服务/类型 0）查 `iAP2LinkGetSessionForService`，把返回值当会话号传下去。

## 2.4 表的两个查询函数

| 函数 | 匹配字段 | 返回 | 证据 |
|---|---|---|---|
| `iAP2LinkGetSessionInfo(link, 会话号)` `0x100032828` | 项[0] | 表项指针（最后一个相等项），无则 0 | `0x100032830` `ldrb w9,[x0,#0x1a4]`；`0x100032840` 基址；`0x10003284c` `csel` |
| `iAP2LinkGetSessionForService(link, 类型)` `0x100005740` | 项[1] | 项[0]（会话号，`and w0,#0xff`） | `0x100005744` 表项数；`0x100005754` 基址；`0x100005764` `ldrb w15,[x8,#1]` |

两者是同一张表的两种索引方向：**类型 → 会话号**（发送时选会话）与**会话号 → 表项**（接收时分发）。

## 2.5 未决

- **`OPEN-SES-1`**：填充/提交路径已由 §2.9 确认；保留最初 profile 分配、多会话冲突与跨版本选择规则，不能固定会话号。
- **`OPEN-SES-6`**：类型 3 无分发分支，但占用一个发送队列槽；用途未知。
- **`OPEN-SES-7`**：`0x100032694` 写出参 `0x1d` 是协议动作号（"动作 0x1D"），其语义表在上一阶段的链路 FSM 里，未在本阶段展开。
- **`OPEN-SES-3`**：表项第 4 字节（flags）的 bit1–bit7 语义未取证；本阶段只确认 bit0 被使用，其余位没有写入者证据。

## 2.6 历史字面偏移扫描及其局限（由 §2.9 补正）

以下只保留扫描方法的历史记录。它不能排除先计算基址再复制的写法，不能据此断言镜像没有非零写入者；§2.9 已找到实际写入链。

### 扫描方法

对整段 `__text`（0x100000000 起，到镜像尾部）逐条反汇编，按操作数字符串筛出所有引用 `#0x1a4` / `#0x1b8` 的指令，再按函数起点归档：

| 筛法 | 结果 |
|---|---|
| 所有引用 `+0x1a4` 的指令 | 5 处 `str w8,[…,#0x1a4]`，写入值全部是 `0xFFFF0100`（清空） |
| 所有引用 `+0x1b8` 的指令 | 全部是 `add xN,xM,#0x1b8`（算出数组基址）或对**别种结构**的访问 |
| 8 个表使用函数里的寄存器索引写（`str …, [xN, xM]`）与后变址写（`str …, [xN], #4`） | **0 条** |
| 与表同窗口（`+0x198`–`+0x1c7`）的字面 `st*` 扫描 | 旧分析将 SYN 参数与会话表分开，漏掉 `+0x19a` 基址上的向量块复制；该否定推论撤回 |

8 个表使用函数是：`iAP2LinkGetSessionForService` `0x100005740`、`iAP2LinkGetSessionInfo` `0x100032828`、`iAP2LinkQueueSendDataWithSentCallback` `0x100006868`、`iAP2LinkQueueSendDataPacketInternal` `0x10000733c`、`iAP2LinkProcessOutQueue` `0x1000080dc`、`iAP2LinkHandleReadyPacket` `0x10000ada0`、`iAP2LinkProcessInOrderPacket` `0x10000b690`、`iAP2LinkActionHandleData` `0x100032670`。**它们都只读。**

### 4 字节复制函数的真实边界

符号表里有一个极具诱惑的名字：`iAP2PacketCopySessionInfo`（`0x100103720`）。它只有 3 条指令：

```
0x100103720  ldr w8,[x1]
0x100103724  str w8,[x0]
0x100103728  ret
```

它拷贝 SYN 结构中的一个 4 字节会话条目；3 个调用点位于 SYN 校验（`0x100032a54`、`0x100033ac4`、`0x100033c24`）。它不是生效表的直接提交函数，但 SYN 条目正是后续表的来源，旧文“与链路会话表无关”错误。

### 修正后的结论

创建/复位清成 0 项只是初始状态，连接动作会通过计算基址和块复制填入非零条目（§2.9）。实现应使用协商条目建立路由，而不是等待业务帧来猜测或重新分配会话号。

## 2.7 类型编号：从查询调用点反向验证

表的另一半是"类型"。分发器（收侧）给出 0/1/2/4 四类，但那是**switch 的形状**；更有力的是**查表时传入的常量**（发侧）。把两处 `GetSessionForService` 与 `GetSessionInfo` 的 **26 个调用点**全部反汇编，取紧邻 `w1` 的立即数：

| 调用点 | 函数 | 传入类型 |
|---|---|---|
| `0x100005630` | `iAP2MsgSendCtlDataWithSentCallback` | **0**（控制）|
| `0x10006d238`、`0x10006d244` | `iAP2FileTransferCreate` | **1**（文件传输）|
| `0x10006df1c`、`0x10006df28` | `iAP2FileTransferHandleRecv` | **1** |
| `0x100183b54`、`0x100183b60` | `iap2_sessionFileTransfer_getVersion` | **1** |
| `0x10014600c` | `iap2_nowPlaying_mediaItemArtworkUpdateHandler` | **1** |
| `0x100147a28`、`0x100147a38` | `iap2_nowPlaying_playbackQueueListInfoResponseHandler` | **1** |
| `0x10014a5c4` | `__startNowPlayingUpdatesHandler` | **1** |
| `0x100152d7c` | `__appLinksAppIconResponse` | **1** |
| `0x10004b178` | `__iap2_sessionLog_sendOutgoingMessage_block_invoke` | **4**（会话日志）|
| `0x1001554ac`、`0x100155964`、`0x100156440` | 外部配件（EA）三个函数 | 变量（非立即数）|
| `0x10015bb00`、`0x10015bbd8`、`0x10015bbe4`、`0x10015d21c`、`0x10015d22c` | 媒体库两个 handler | 变量 |
| `0x10006ceac`、`0x10006d0c0` | 文件传输缓冲 ID 分配/释放 | 变量 |
| `0x10011d4e0`、`0x10011d4ec` | `sessionControl_getVersion` | 变量（被 outlined 片段遮蔽）|
| `0x10019bfe0` | `iAP2LinkDataReadyCB` | 变量（来自包头的会话号）|

三点结论：

1. **0 与 4 双向一致**：控制面发侧用常量 0，收侧 switch 的 0 号分支就是控制解析器；会话日志发侧用 4，收侧 4 号分支是日志解析器。
2. **1 的用途比"文件传输"更宽**：NowPlaying 的封面图、播放队列、App 图标都走类型 1。这说明类型 1 是"通用数据传输面"，而不仅是"文件传输"，任何"把一堆字节搬过去"的业务都挂在它上面。
3. **外部配件（EA）与媒体库的类型是变量**，说明它们的类型号不是硬编码常量，而是从会话对象里读出来的 —— 这一点与"表里存类型"（`项[1]`）自洽：读出来再查表是多余动作，所以它们查的其实是**别的会话**（EA 面要找到承载它的那条会话）。

对实现方的意义：**类型编号（0/1/2/4）可以硬编码**，它有三处独立证据且有常量支撑；而**会话号不行**（`OPEN-SES-1` 仍未闭合）。这两件事必须分开对待，不要因为类型稳定就推断会话号也稳定。

## 2.8 运行时证据：会话号每连接递增（23G90）

静态侧的填充链见 §2.9；运行时给出两次具体取值。样本见 `runtime/23G90-bt-classic-2026-10-16.md`（构建 **23G90**，非目标构建 24A446）。

同一台手机、同一台车机、同一份 sysdiagnose 里的两次连接：

| 连接 | 链路控制包 `hdr[7]` | 第一条 iAP2 消息的 `hdr[7]` | 之后所有 iAP2 消息 |
|---|---|---|---|
| 第一次（蓝牙经典）| `0x00` | **`0x02`**（`0x1D00` 开始识别）| `0x02` |
| 第二次（AirPlay 链路）| `0x00` | **`0x03`**（`0x1D00`）| `0x03` |

由此得到三条可直接用于实现的事实，以及一条仍未闭合的机制：

1. **链路控制包与 iAP2 消息分属两个"会话空间"**：SYN/SYNACK/纯 ACK 的 `hdr[7]` 恒为 0，iAP2 消息从第一条起就是非 0。这与 `analysis/03` 说"`hdr[7]` 是会话号"并不矛盾——会话号只对承载 iAP2 消息的包有意义，链路控制包填 0。
2. **纠正原“设备侧首次声明”推论**：原始日志第 4/5 行的车机 SYN 和 iPhone SYNACK，在 version 1 固定头后的条目均为 `02 00 02`；第 41/42 行均为 `03 00 02`。它们早于 `0x1D00`。因此不能忽略 SYN 载荷，仅凭 iPhone 首条业务帧认定配件被动接受任意会话号。
3. 两次连接分别使用 2/3，且业务 `hdr[7]` 与握手条目首字节一致。仿 iPhone 实现须追踪握手条目，不能固定号或另行任意选号；条目解析见 link `R-3.4`–`R-3.6`。
4. **仍未闭合**：多会话选择、冲突处理和初始 profile 分配规则仍为 `OPEN-SES-1`。表填充点已由 §2.9 确认；两次连接的行为证据不是全版本协商规范。

另有一条与编码有关的实测细节：设备发出的 `0xAA00` 帧尾部是 `00 04 00 00`，即**参数总长为 4 的空参数**。而顶层/子项边界检查允许长度 4（父参数自身另有总长 ≥5 条件）。该样本说明 profile 可以使用零值 presence 参数；实现必须按 `parent`/`prev` 正确遍历，并按 profile 决定是否跳过该项。

依据：`A02.13`、`A02.14`、`A03.8`。

## 2.9 SYN → 工作表 → 生效表：实际写入链

`A02.15`（24A446 指令确认）以下原始汇编均位于 `../iap2_link_establish/source/asm/accessoryd/`，对应 Ghidra C 位于同 docset 的 `readable/ghidra/accessoryd/`。

1. `f_100033fd0.s` 的 `0x1000341a4..1c0` 把调用方 SYN 参数复制到 `link+0x168`：48 字节向量加 2 字节尾部，共 50 字节。之后初始化的是另一个块 `link+0x19a`，不是覆盖工作块。
2. `f_10002f920.s` 的 `0x10002f9d8..9e8` 解析对端 SYN 后调用 `iAP2LinkCheckNegotiation`。
3. `f_100035154.s` 的 `0x100035380..394` 将 `peer[0xa]` 写到 `link[0x172]`，复制 `peer+0x1e` 的 `4*n` 字节到 `link+0x186`。这是工作块的计数与条目。
4. `f_10003009c.s` 的 `0x1000300c0..dc` 将 50 字节从 `link+0x168` 整体复制到 `link+0x19a`。目的计数正好是 `0x19a+0xa=0x1a4`，条目首址是 `0x19a+0x1e=0x1b8`，末址是 `0x1cb`。解析器最多复制 5 个条目（`f_100103230.s` 的 `0x100103328..330`）。
5. 同一连接动作在 `0x1000300e0..ec` 保存旧 `link[0xd5]` 到 `0xd6`，把生效 SYN version 写到 `0xd5`，随后上报连接。控制会话版本则来自条目第三字节，**不是** SYN version；两者不要混淆。

因此旧“48 字节结构”“44 项容量”“SYN 与会话表无关”“没有非零写入点”均撤回。该证据闭合已核对路径的填充与提交，不等于已验证全部 profile 分配、多会话竞争与真实车机互通。
