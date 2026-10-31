# 24A446：蓝牙角色、服务发布与连接方向复核

日期：2026-10-29。范围：经典蓝牙 WiAP 的服务初始化、SDP 记录、出入站选择与 HFP/A2DP 协调线索。未进入 iAP2 Detect/SYN 或 AirPlay。


## 1. 结论与旧判断修正

1. **不能把固件中存在普通 WiAP、WiAP Sink 两套实现，解释成 iPhone 应当无条件同时发布四条服务。** 服务管理器存在 `WiAP / enableSink` 的本地角色选择条件，两套服务在这条初始化路径上互斥。它不是已证明的按车型选择条件。
2. **普通 WiAP 的 legacy/v2 是两条 SDP 记录，但共享一个 RFCOMM listener/channel 描述。** 我们对每个 UUID 调用一次 Android 监听 API，并不等价于这个拓扑。
3. **固件的双向连接不是简单的“先连上者获胜”。** 普通 WiAP 入站接纳会经过 profile 状态、电源、连接容量、service 主动连接队列和已有句柄检查。

以上纠正的是证据解释，不表示已经证明某一车型失败的原因，也不授权立即删除监听或强断蓝牙音频。

## 2. 镜像与复核方法

- bluetoothd：`../firmware/extracted/24A446/components/24A446__iPhone18,1/root/usr/sbin/bluetoothd`
- SHA256：`cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1`
- carkitd：`../firmware/extracted/24A446/components/24A446__iPhone18,1/root/usr/libexec/carkitd`
- SHA256：`87e352056b30cc29e206b265786dac43eeab8536e8cebeae14711e8e3fdaf8cd`
- bluetoothd 缓存：`../firmware/analysis/decompiler-cache/24A446/bluetoothd/c98ecfbc6d67966e54f7/functions/`
- 本轮 carkitd 缓存：`../firmware/analysis/decompiler-cache/24A446/carkitd/683446d11fdb309e5cb0/functions/`

先从固件原字符串找 ADRP/ADD 引用候选，再读完整函数及汇编、解析只读数据表和 arm64e 本地重定位指针。候选引用不是语义证明。Ghidra 的寄存器返回值和间接调用签名经常失真，分支条件以汇编为准。

本轮对下面 13 个关键缓存函数重新从原 Mach-O 读取函数全段，比对 `.bin`，全部一致：

`10063e520, 100653368, 1007a38cc, 10087d918, 1007a3ba4, 1007a4000, 10062c974, 10063ad64, 1007a79e8, 1007a5ae0, 1007a7b2c, 1005e1b30, 10080adac`。

工具：[inspect_bluetooth_policy.py](../tools/inspect_bluetooth_policy.py)。输出只到 stdout；不写镜像或缓存。`xrefs` 是候选扫描；`pointers` 只应用于已识别的指针槽，不能把任意整数解释成指针。

## 3. 本地角色选择，不是把所有分支同时打开

入口 `bluetoothd:0x10063e520`：

- 初始化局部 `enableSink` 为 0。
- 从设置提供者读取命名空间 `WiAP` 下的 `enableSink`。提供者配置的来源/设备部署差异尚未全部追完，不能将默认值当成所有 iPhone 运行时值。
- `0x10063eae0–0x10063eaf4`：能力检查参数 `0x80`，通过后还要求 `enableSink` 的 bit0 为 0，才加入普通 WiAP 服务。
- `0x10063efd4` 起：能力检查参数 `0x20000`，并要求与 `enableSink` 的合取为 1，才加入 WiAP Sink 服务。
- WirelessCarPlay 另有 `0x40000` 能力分支，不能把它与上述两个服务或 BLE CarPlay 混成同一开关。

解析对象构造链，而不是仅凭日志命名：

| 服务 | 构造链中的关键节点 | profile 与本地服务记录 |
|---|---|---|
| 普通 WiAP | `648230 → 7a7a74 → 7a79e8`；service mask `0x80`；profile 单例 `c1fbf0` | 单例 block `7a7eec → 7a378c → 7a3680`；注册入口 `7a38cc` |
| WiAP Sink | `648508 → 7a5b6c → 7a5ae0`；service mask `0x20000`；profile 单例 `c1fc00` | 单例 block `7a5fc0 → 87d848 → 87d7b8`；注册入口 `87d918` |

地址在本表省略共同前缀 `0x100`。

`0x100653368` 的发现广播构造也分别出现 `Advertising WiAP`、`Advertising WiAP Sink and Classic CarPlay`，并有相应能力/角色条件。这是对角色分离的补充证据，不代表 SDP 全部生命周期已审完。

**与我们对照：** `Bootstrap.kt:139–165` 无该角色选择，普通组和 Sink 组均尝试注册。其注释“固件还发布第二组，所以也发布”遗漏了上游接入条件，不能作为实现依据。

## 4. 两条服务记录共用一条传输路径

从原 Mach-O 解析注册表：

| 本地角色 | ServiceClassIDList 的 128-bit 字节表示 | attribute 0x0004 共用数据地址 | attribute 0x0009 的 profile descriptor |
|---|---|---|---|
| 普通 WiAP legacy | `00000000-deca-fade-deca-deafdecacafe` | `0x100bca708` | `0x1101, 0x0102` |
| 普通 WiAP v2 | `02030302-1d19-415f-86f2-22a2106a0a77` | 同上 | 同上 |
| WiAP Sink legacy | `00000000-deca-fade-deca-deafdecacaff` | `0x100bceed8` | `0x1101, 0x0100` |
| WiAP Sink v2 | `02030302-1d19-415f-86f2-22a2106a0a78` | 同上 | 同上 |

普通组属性数组为 `0x100bca5e8 / 0x100bca630`；Sink 组为 `0x100bcedf8 / 0x100bcee40`。每条 ServiceClassIDList 在这些静态描述中只有一个 UUID；旧注释“因为 Android 只能单 UUID，所以拆成四条”等说法并不能解释真实差别。

普通组两条记录的 ProtocolDescriptorList 是同一个指针，RFCOMM channel 引用节点共指 `0x100c95de8`；Sink 组共指 `0x100c96cb0`。各注册入口均先调用一次 RFCOMM 注册，再把返回 channel 写入该组共享的动态描述，之后按 legacy→v2 顺序注册 SDP。默认传入 channel 初值分别为 1 和 3，但实际传给 SDP 的是注册调用后的值，不能据此硬编码车机的出站 channel。

上述 `0x0102 / 0x0100` 属于 SDP profile descriptor，**不是 iAP2 SYN 版本、Identification 版本或 AirPlay sourceVersion**。

**与我们对照：** 四次 `listenUsingRfcommWithServiceRecord` 创建独立 server socket，不能保证等价于苹果“同一角色的两个服务别名指向同一监听通道”。Android 标准 API 是否能表达这种记录拓扑，需要单独验证系统栈接口，不能假设换个名字就能做到。

## 5. 入站接纳：在 RFCOMM 接受前执行状态策略

普通 WiAP `0x1007a4000` 的实质条件：

1. 调 `0x10062c974` 做 profile/service 接纳检查；返回 false 就拒绝。
2. 调 `0x10062cd3c` 查该设备已有句柄；非零就拒绝。
3. 通过后才调用底层接纳接口，成功后登记句柄和连接状态。

`0x10062c974` 展开：

- 设备必须存在，profile state `+0x50` 必须为 1（日志说明是 started）。
- 电源状态 getter `0x10002fd70` 必须返回 1；失败日志明确是 Bluetooth power is not on。
- 连接集合数量必须小于 profile 的虚方法容量上限；普通 WiAP 的 `vtable+0x10 → 0x1007a58d8` 返回 5。这是内部 profile 容量，不能直接解释成允许五个并行 CarPlay 会话。
- 最后调用所属 service 的 `vtable+0x80`。

普通 WiAP service vtable `0x100bca978` 和 Sink service vtable `0x100bca818` 的 `+0x80` 都指向 `0x10063ad64`。该函数持锁检查 service 的 `+0xb0` 队列计数；非零即返回 false，日志为 `already has a pending outgoing connection ...`。这个检查本身没有按入站地址与队列头再做匹配，不能缩写成“只拒绝同一设备的重复出站”。

**与我们对照：** 当前是出入站同时尝试，已建连 socket 通过 `compareAndSet` 选赢家。它保证本机只将一条 socket 送入 iAP，但不是固件这套接纳前的状态策略，也不能保证对端持有的是同一条连接。Android `accept()` 返回后能做的检查与苹果底层接纳 callback 不是同一层，移植时必须处理平台差异。

## 6. 服务发现还有自己的状态与版本分类

### 6.1 主动建连的 fallback 边界

`0x1007a3ba4` 查询新描述符的 attribute 0x0004，查找失败才查询旧描述符；然后解析 RFCOMM channel 并发起连接。这里的查询对象是设备内部 SDP 数据，不是证明此函数必然触发一次新的无线 SDP 查询。

新描述符查到但解析不到有效 channel、或者打开 channel 失败时，本函数走错误返回；不能概括成“所有 v2 失败都回退 legacy”。上层是否另起一轮请求是另一层问题。

我们用 Android `device.uuids` 非空作为 `sdpKnown`，与这套完整 SDP 属性查询不是同一个条件。

### 6.2 `wIAPVersion` 不是猜一个固定版本号

`0x1007a7b2c` 的服务识别过程：

- 先检查设备内部 SDP 集合是否非空（`0x1005ec154`）；无数据走另一种状态结果。
- 分别检查 legacy `…caff`、v2 `…0a78` 的 attribute 0x0004。
- 均不匹配时写 WIAP version 0；legacy 匹配时写 1；仅 v2 匹配时写 2。
- 版本 setter `0x1005f3794` 写设备 `+0x330` 的 16-bit 值，日志明确为 `Setting WIAP version to %d`。
- legacy 匹配分支查询其 attribute `0x0301`；仅 v2 匹配分支查 v2 的 `0x0301`。有效 uint32 元素传给 `0x1005f2934`，后者写设备 `+0x392` 为值是否非零并通知上层。

`0x0301` 的业务含义与消费者尚未闭合，不能命名为“CarPlay 版本”或“必须发送的 iAP2 能力”。两种 UUID 同时存在时，服务分类和最终 RFCOMM 选择的优先顺序不同；不能将所有层合并成一个 `preferV2` 开关。

补充：`0x10019da5c` 在两侧均为 128-bit UUID 时直接比较两个 64-bit 字块；本比较步骤未做自定义 UUID 映射。SDP 完整编码、线上字节序验证仍不能仅靠这个比较函数替代。

## 7. HFP/A2DP：查到了什么，尚未证明什么

### 已读到的相关路径

- `carkitd: -[CRWirelessPairingServiceSession _mainQueue_connectDevice:session:completion:]`，入口 `0x100052c64`：注册服务回调，计算 intended service mask，调用 `BTDeviceConnectServices`，等待回调/计时器；所读函数没有先断开 HFP/A2DP 的步骤。
- `_intendedServiceMask` 位于 `0x100051cec`。selector stub 和指针槽确认调用的是 `intent`：intent==2 时返回 `0x80`，否则返回 `0xffffffff`。数字 intent 的完整业务枚举尚待上层调用核实；不能把非2分支当成已证实的 CarPlay 路径。请求只连接 WiAP，不等于断开已有音频 profile。
- `-[CRBluetoothManager connectWithBluetoothAddress:]`，`0x100061394`，通过 `_deviceForBluetoothAddress:` 获得对象后调用 `connect`。BluetoothManager 框架内部与更高层模式切换仍需追踪。
- `bluetoothd:0x1005e1b30` 是 profile 断开结果处理，不是“开始连接前先断开”。成功的 WiAP profile 断开后，特定分支读取保存的车辆设置并更新 `CarPlayEnabled`。不能反过来当作连接前断音频的证据。
- `bluetoothd:0x10080adac` 在 CarPlay 活跃分支按 A2DP/HFP streaming 状态调整扫描参数。它是共存/扫描策略，不能证明同一车机上所有 profile 可以同时工作，也不能证明必须提前全部断开。
- 本轮还检查了通用 service disconnect 入口的若干直接调用者，包含客户端请求、GATT 传输切换、配对提示和 LE 消息等，未建立“每次 WiAP connect 前必断音频”的关联。间接调用与跨进程上游仍未穷尽。

### 当前证据边界


## 8. 对实现工作的建议顺序

1. 先修正设计依据：以手机侧角色为基线，不把固件的 Sink 替代角色默认并入手机路径。
2. 明确 Android 平台可表达的 SDP 记录/共享通道能力，必要时设计有证据支持的近似方案并记录差异，不能声称完全复刻。
3. 将 `服务信息未知 / 服务明确不存在 / channel 解析失败 / transport 连接失败` 分开，并实现可测试的方向状态机；不要先拼车型表。
4. HFP/A2DP 暂不增加全局强断策略；继续追 intended service mask 的上游意图、BluetoothManager `connect` 及 profile 切换策略的条件与时机。

本轮没有覆盖：所有能力提供者、SDP 刷新生命周期、属性编码全路径、profile 回连恢复、全部出入站竞态、不同机型运行时配置和实车行为。
