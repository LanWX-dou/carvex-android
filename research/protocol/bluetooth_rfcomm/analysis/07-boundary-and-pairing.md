# 07 蓝牙 → iAP2 边界与配对

覆盖需求项：**（10）Bluetooth → iAP2 Link 边界**，并补充配对完成后的通道可用条件（与（6）相关）。

## 1. 目标

1. 明确"谁负责 RFCOMM 帧，谁负责 iAP2 报文"，边界在哪一行代码。
2. 说明边界两侧的数据形态（字节流 vs 帧、fd vs 回调）。
3. 说明配对在协议链中的位置，以及"配对完成"与"RFCOMM 可用"的先后关系。

## 2. 结论

### C1 边界位于"逐帧回调"，参数为 `(DLCI, 数据指针, 长度)` `CONFIRMED`

`0x1003c59a0` C 行 348–349：

```c
(**(code **)(*(long *)(dlci + 0x28) + 8))(*(undefined2 *)(dlci + 8), param_2, uVar14);
```

- 调用点是 `OI_Rfcomm_ReceiveFrame` 的 UIH 交付分支，**每收到一个通过全部校验的 UIH 帧调用一次**。
- 第 3 个参数 `uVar14` 就是该帧的信息字段长度（解码自长度字段），不含地址/控制/长度/FCS。
- 该函数指针来自 DLCI 记录的 `+0x28` 回调块，由 `OI_RFCOMM_Connect` 的 `param_2`（出向）或服务端注册项（入向）复制而来。

**结论**：bluetoothd 向上一层交付的是"RFCOMM 信息字段的边界",而不是字节流。任何跨帧的报文重组都在边界**之上**完成。

### C2 同一通道还有一条 fd 通路，上层实际用 fd 传数据 `CONFIRMED`

`0x10040c934`（连接完成通知）C 行 62–83：

| 键 | 类型 | 说明 |
|---|---|---|
| `kCBMsgArgDeviceUUID` | UUID | 对端设备 |
| `kCBMsgArgResult` | int64 | 连接结果 |
| `kCBMsgArgRFCOMMChannelID` | int64 | 通道号 |
| `kCBMsgArgMTU` | int64 | 实为最大帧长 N1（`05` C9） |
| `kCBMsgArgIsIncoming` | bool | 入向/出向 |
| `kCBMsgArgSocket` | **fd** | `_xpc_dictionary_set_fd` 交给客户端 |
| `kCBMsgArgServiceUUID` | data | 该通道对应的服务 UUID |

对应地，`0x1000eb4e8` 从 `os_channel` 读数据（`_os_channel_advance_slot` / `_os_channel_sync` / `_os_channel_available_slot_count`），并按 `channel_type`（1 = L2CAP、2 = RFCOMM）分别投递。

**结论**：bluetoothd 与上层之间的数据面是**内核管道 + 文件描述符**；回调路径用于事件与可选的内嵌交付，主数据通路是 fd 上的字节流。

### C3 bluetoothd 内部没有任何 iAP2 协议实现（否定性证据）`CONFIRMED`

对 `source/firmware/bluetoothd`（13,092,096 B）做全字符串统计：

| 关键字 | 出现次数 |
|---|---|
| `iap2`（大小写不敏感） | **0** |
| `Wireless IAP` | 10 |
| `OBEX` | 130 |
| `SDP_PARSER` | 4 |

`Wireless IAP` 的 10 条全部是**服务名或日志文案**：

```
Wireless IAP / Wireless IAP Sink / Wireless iAP / Wireless iAP v2 /
Wireless iAP Sink / Wireless iAP Sink v2 /
Wireless IAP Service is not supported by device %{public}s /
Initiating outgoing Wireless IAP connection request to device %{public}s on rfcomm channel %d, %{public}s
```

也就是说：bluetoothd 认识"这是个无线 iAP 设备"，会**主动发起 RFCOMM 连接**（`0x1007a3ba4`，见 `03` C5），但**完全不解析 iAP2 报文**。

### C4 连接发起决策在 bluetoothd，报文语义在上层（分层结论）`CONFIRMED`

`0x1007a3ba4` 的完整行为链（`03` C5）：解析设备 SDP 结果 → 找 RFCOMM 通道号 → 判 `New WiAP UUID` / `Old WiAP UUID` → 建 RFCOMM 连接。它**不接触 payload**。

因此平台无关的分层是：

```
[RFCOMM 帧层]      bluetoothd：地址/控制/长度/FCS、DLCI、信用、DISC/DM
      ⇕ 每帧一次回调（DLCI, ptr, len） 或 fd 字节流
[字节流层]         内核 os_channel（单次 ≤ 2570 字节）
      ⇕
[iAP2 Link 层]     上层进程：iAP2 报文头、长度、序号、校验、会话
      ⇕
[iAP2 应用层]      CarPlay / 配件业务
```

### C5 边界处必须遵守的三条不变量 `CONFIRMED（由 C1/C2 直接推出）`

1. RFCOMM 交付的单位是"一个信息字段"，**不能假设信息字段 == 一条 iAP2 报文**；反之一条 iAP2 报文也可能被拆成多个 RFCOMM 帧。
2. RFCOMM 不保证"不丢、不重"以外的顺序之外语义：本实现的接收路径在长度不符时**静默丢弃整帧**（`05` C4），因此 iAP2 Link 层必须自带完整性/重传机制。
3. 发送侧单块上限 2570 字节（`os_channel` 层），超出必须由上层分块；协议栈按 MBUF 队列串行发送（`05` C7）。

### C6 配对位于通道建立之前，且由上层驱动 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| 函数名 | `CBStackControllerBTStack::pairingContinueWithPairingInfo:error:`（`0x100233530`，名字来自调试符号还原的 objc 方法） |
| C 行 43–47 | 错误码 `0xffffe5cf` + 文案 `No pairing device` |
| C 行 60–61 | 错误码 `0xffffe5a7` + 文案 `No pairing agent handle to continue` |
| C 行 64–68 | 取配对代理句柄（`lRam...100c1b9a8`），`FUN_1007807e8(handle, param_1+0x40)` 继续配对流程 |
| C 行 76–77 | `FUN_10078ac1c` + `FUN_10077dca8(handle, info, buf)` 提交配对信息 |

语义：蓝牙配对是一个**需要上层提供信息**（PIN、确认、OOB 数据）的异步流程；bluetoothd 只提供"继续"接口和"配对代理"句柄，实际 UI/策略在 `BluetoothManager`/上层框架。

### C7 配对与 RFCOMM 的时序关系 `PARTIAL`

| 依据 | 内容 |
|---|---|
| `0x1003c2b00` C 行 40–44 | 连接前只校验参数（N1、信用窗口），**不检查链路是否已认证/加密** |
| `0x1003c5c70` | 入向 SABM 处理只检查会话状态、地址、C/R，**不检查安全状态** |
| `0x100296714` 的 `forcing disconnect` | 存在外部强制断链入口，可能用于安全降级 |

因此可以确定：**RFCOMM 层自身不做安全校验**；"必须先配对/加密"由 L2CAP 之上的策略层或上层应用保证（蓝牙规范允许在 SDP/RFCOMM 建立后再做安全提升，但本实现未见显式的"拒绝未加密连接"分支）。

`PARTIAL` 原因：未在抽样函数中定位到"检查链路密钥/加密状态"的判定点，不能断言"无检查"，只能说"RFCOMM 处理路径内无检查"。

### C8 交接形态的补充取证：pipe/socketpair、双向中继与帧边界丢失 `CONFIRMED / INFERRED`

为把「交出去的东西」定义到可实现（`spec/08-handoff-contract.md`），补充取证如下：

| 事实 | 证据 | 等级 |
|---|---|---|
| pipe 由 `socketpair` 创建，每条 pipe 有独立编号 | 串表 `Failed to create socket pair for pipe 0x%04x with result %d` @ `0x100acbb3d` | `CONFIRMED` |
| pipe 与 `os_channel`（skywalk）绑定 | 串表 `os_channel_create_extended failed for pipe 0x%04x (errno %d: %s); aborting skywalk pipe registration` @ `0x100acbfa5` | `CONFIRMED` |
| 方向一：socket → 空口（客户端写、协议栈读） | 串表 `Failed to transmit data from socket on pipe 0x%04x with result %u` @ `0x100acc74f`，该串位于已抽样函数 `0x1000eb4e8` | `CONFIRMED` |
| 方向二：空口 → socket（协议栈写、客户端读） | 串表 `Failed to send data to socket on pipe 0x%04x with result %d` @ `0x100acc42f`（函数未抽样） | `INFERRED` |
| fd 随 XPC 交给客户端 | `0x10040c934` C 行 62–83（`kCBMsgArgSocket`，`_xpc_dictionary_set_fd`） | `CONFIRMED` |
| 客户端侧关闭可见为 EOF / 错误 | 串表 `Read zero bytes from socket on pipe 0x%04x` @ `0x100acc896`、`Received error %d from socket on pipe 0x%04x` @ `0x100acc8c1` | `INFERRED` |
| 回调指针是进程内地址 | `0x1003c59a0` C 行 348–349 直接调用函数指针，无序列化/跨进程机制 | `CONFIRMED` |
| 缓冲在回调后立即失效 | 投递后 `_os_channel_advance_slot()` 归还槽位（`0x1000eb4e8` C 行 406–413） | `INFERRED` |
| 单块上限 2570 | `0x1000eb4e8` C 行 72、87–90（`spec/05` T-08） | `CONFIRMED` |

由 C1/C2/C8 汇总出的帧边界结论：帧边界只在**进程内回调**通路存在；
fd 通路是 `socketpair` 字节流，不存在每帧长度前缀或控制消息。
因此 `spec/06` 旧 R-6.24 的「传输桥层必须不丢失帧边界」与固件不符，已改写为 `spec/06` R-6.28。

### C9 两条路径的证据清单：哪些是固件、哪些只是运行时/推演 `CONFIRMED / INFERRED / OPEN`

`spec/09` 同时描述"主动连"与"监听"两种角色。两者的证据等级**并不相同**，本节把差别摊开，
避免读者把运行时形态误当成固件结论。

**A. 主动连（iPhone 作为发起方）——固件确认**

| 环节 | 证据 | 等级 |
|---|---|---|
| SDP 结果里取通道号、判 New/Old WiAP UUID、发起连接 | `0x1007a3ba4`；日志引用点 `0x1007a3d34`（`Initiating outgoing Wireless IAP connection request ... on rfcomm channel %d`） | `CONFIRMED` |
| 连接参数（N1、信用窗口）校验与 DLCI 公式 | `0x1003c2b00` | `CONFIRMED` |
| PN 编码/解析、信用 `& 7` | `0x1003c7644`…`0x1003c7678` | `CONFIRMED` |
| 发送串行队列与完成事件 | `0x1003c3c20` | `CONFIRMED` |
| 单块上限 2570、槽位推进 | `0x1000eb4e8` C 行 72、87–90、406–413 | `CONFIRMED` |

**B. 监听（接受对端连入）——机构有固件，绑定环节缺**

| 环节 | 证据 | 等级 |
|---|---|---|
| 已注册服务查表：表基址 `0x100c38318`、步长 `0x38`、通道字节 `+0x1a`、命中后调 `+0x08` 回调 | `0x1003c2314` C 行 18–34 | `CONFIRMED` |
| 服务注册入口（失败日志 `RFCOMM registration failed!`） | `0x1002f1300` | `CONFIRMED` |
| 入向 SABM 五道拒收（会话/地址/C/R/…） | `0x1003c5c70` | `CONFIRMED` |
| 入向 DISC→UA、状态分派 | `0x1003c59a0` C 行 382–462 | `CONFIRMED` |
| **iAP2 的 SDP 记录注册**（`Failed to register WiAP v2 SDP service record`） | 字符串 `0x100b46435`；引用点 **`0x1008f5fb8`（非抽样函数）** | 只有字符串 |
| **WiAP Sink 记录注册**（`... WiAP Sink v2 ...`） | 字符串 `0x100b6eb82`；引用点 **`0x100905330`（非抽样函数）** | 只有字符串 |
| 记录里的 RFCOMM 通道由谁承载（是否就是 `0x1002f1300` 注册的服务端） | 无直接证据 | `OPEN`（`OPEN-CLI-2`） |

**C. 运行时形态（跨构建，非 24A446，只作佐证）**

| 事实 | 来源 |
|---|---|
| iPhone 侧记录 `00000000-deca-fade-deca-deafdecacafe`，名字 `Wireless iAP`，21G93 样本 PDL 通道 = **1** | `runtime/observations/sdp-records-iap2.md` §3 |
| 车机侧记录 `…caff`，通道 **4 / 1 / 5**，名字 `RFCOMM-SPP` / `iAP2` / 空 | 同上 §2 |
| 首个 UIH 载荷均为 `FF 5A` 且由车机（配件侧）先发 | 同上 §4 |

**D. 两代服务（legacy / v2）与「两条通道」**

| 事实 | 证据 | 等级 |
|---|---|---|
| 两套 UUID：legacy `00000000-deca-fade-deca-deafdecacafe`（`…cafe`）/ `00000000-deca-fade-deca-deafdecacaff`（`…caff`）、v2 `08ed27c3-…a77`/`…a78` | `spec/01` R-1.12（名称表 `0x1003d56fc`）、`analysis/01` C5/C5.1 | `CONFIRMED` |
| 连接时**区分**用的是哪一代：日志 `New WiAP UUID` / `Old WiAP UUID` | `0x1007a3ba4`（引用点 `0x1007a3d34`） | `CONFIRMED` |
| 通道号**取自对端 SDP 记录**，两代各取各的 | 同上：`uVar8` 来自协议描述符解析，随后传入 `FUN_1003c2b00(…, uVar8 & 0xff, 0x3ef, 0x3b01, …)` | `CONFIRMED` |
| 连接参数就是 N1=**1007**（`0x3ef`）、信用窗口=**15105**（`0x3b01`） | 同一调用点 | `CONFIRMED` |
| 服务端**分别注册**两代记录（v2 有独立注册失败日志） | 字符串 `0x100b46435`、`0x100b6eb82`；引用点非抽样 | 只有字符串 |
| **v2 的实际通道号** | 四个抓包里 v2 的两个 UUID 出现次数均为 **0** | `OPEN`（`OPEN-CLI-3`） |
| legacy 通道号 | iPhone 侧 `…cafe` 通道 **1**（21G93）；车机侧 `…caff` 通道 4/1/5 | 运行时 |

**结论**：`spec/09` 的 A 路径每一步都有指令级依据；B 路径的**RFCOMM 机构**有依据，
但"iPhone 为 iAP2 注册监听记录"这一环只有字符串 + 运行时形态，属 `INFERRED`，已登记 `OPEN-CLI-2`。

## 3. 对实现的约束（进入 spec）

1. 边界必须定义清楚：回调通路交付粒度 = 帧，fd 通路 = 字节流；上层必须自己做报文重组与长度校验（完整契约见 `spec/08`）。
2. 发送路径必须接受"单块 ≤ 2570 字节"的约束，并有队列化发送语义。
3. 必须上报"最大帧长 N1"给上层，命名不要叫 MTU（会被误用为 L2CAP MTU）。
4. 连接完成的回调必须同时给出：设备标识、通道号、方向、fd/句柄、服务 UUID。
5. 配对是可中断、可重入的异步流程，必须有"无配对代理"与"设备不存在"两种明确错误。

## 4. 未决

| 编号 | 内容 | 原因 |
|---|---|---|
| `OPEN-BND-1` | 已关闭：两条通路并存，**跨进程客户端只能用 fd**（回调是进程内函数指针，`0x1003c59a0` C 348–349）；残留的「运行时使用比例」不属于固件可证范围 | `analysis/07` C8、`spec/08` R-8.1/R-8.2 |
| `OPEN-BND-2` | `kCBMsgArgServiceUUID` 在入向连接时如何确定（来自本地注册还是 SDP） | 只看到取值来源 `FUN_1005fc690`，未展开 |
| `OPEN-BND-3` | 是否存在"RFCOMM 上必须加密"的强制策略 | 见 C7 |
| `OPEN-BND-4` | 已关闭：iAP2 报文格式不在 bluetoothd 内（C3），现有证据表明上层自带 **16 位长度 + 8 位序号 + ACK/重传**（2026-10 由 link 侧确认，属跨 docset 佐证，非本 docset 固件证据） | 本 docset 只证「不解析、不重组、不重传」（R-8.22–R-8.24），格式本身由 iAP2 side 定义 |
| `OPEN-BND-5` | fd 通路的**背压/短写**反馈（阻塞、`EAGAIN`、静默排队） | 中继函数未抽样；串表只给了失败日志，没有返回码语义 |
| `OPEN-CLI-1` | iPhone 对**入向** iAP2 连接是否应答 SABM/PN 的**运行时样本**缺失（角色策略已定：主动连与监听都支持，见 `spec/09` R-9.33） | 三次抓包都是 iPhone 作为发起方（出向），没有入向 SABM 样本；`spec/09` §9.7 的监听流程由固件入向路径（`0x1003c5c70`/`0x1003c2314`）支撑，缺的只是端到端样本 |
| `OPEN-CLI-2` | WiAP 的 SDP 记录注册函数未抽样，且该记录对应的 RFCOMM 监听端是否由 `0x1002f1300` 注册未证 | 注册字符串的引用点 `0x1008f5fb8`/`0x100905330` 都落在非抽样函数（工具：`tools/find-str-xref.py`）；只有运行时 `…cafe` 记录 + 名字可佐证 |
| `OPEN-CLI-3` | iPhone 的 **v2 记录**用哪个 RFCOMM 通道、与 legacy 是否不同 | 四个抓包里 `08ed27c3-…`/`02030302-…` 出现次数均为 0；注册函数（`0x1008f5fb8`/`0x100905330`）非抽样；只能确定「两代各取自己记录里的通道」 |
