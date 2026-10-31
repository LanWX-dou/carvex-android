# 蓝牙服务与连接方向：Android 实现边界及下一批设计

日期：2026-10-30。承接 [69 — 24A446 蓝牙角色与连接方向复核](69-bluetooth-role-direction-audit.md)。


## 1. 结论

1. **以所核查的 AOSP 为准，普通应用不能用现有公共 API 精确表达苹果“两个自定义 SDP 记录共享一个 RFCOMM listener/channel”的结构。** 两次 `listenUsingRfcommWithServiceRecord` 会创建两个独立监听，不能当作一个监听的两个别名。
2. **Android 蓝牙栈内部能把记录注册与通道创建分开，不能说 Android 底层完全做不到。** 但通用注册入口没有在所核查的 Binder 接口中开放给应用；现有 Shizuku 功能也没有提供这条能力。系统权限、反射和能访问这个内部对象是三件不同的事。
3. **新增字段差异：AOSP 自定义 UUID 的通用记录构造没有添加 attribute `0x0009`（BluetoothProfileDescriptorList）。** 24A446 普通 WiAP 的两条记录有 `0x1101 / 0x0102`；仅解决 UUID 或共用通道，仍未补齐此差异。
4. Android 普通 RFCOMM 的 `accept()` 返回的是已经建立的连接。它没有向应用提供与苹果底层入站 callback 等价的逐连接、接纳前策略入口。不能靠“不调用 accept”就宣称复刻苹果的入站拒绝。
5. 可以先在应用层对齐角色、服务证据分级与连接状态机；共享通道、完整 SDP 字段和接纳前拒绝要单列为平台能力缺口。**没有证明这些差异是某一车型连接失败的根因。**

## 2. 证据范围与可复现性

### 苹果侧

仍使用 24A446 的 `iPhone18,1` bluetoothd，SHA-256：

`cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1`

本轮从原 Mach-O 再解析四个属性数组，各三项：`0x100bca5e8`、`0x100bca630`、`0x100bcedf8`、`0x100bcee40`，确认 `0x0001 / 0x0004 / 0x0009`。角色条件及调用链依据69，不重复宣称做了全固件审阅。

```powershell
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_bluetooth_policy.py sdp --address 0x100bca5e8 --address 0x100bca630 --address 0x100bcedf8 --address 0x100bcee40 --count 3
```

这是固件内部描述结构，不是空中抓包；动态字段值、最终编码和其他附加属性仍要单独核实。

### Android 侧

- 主基线：AOSP `platform/packages/modules/Bluetooth` 的 `android-16.0.0_r1`，解析到不可变提交 `4b73ee6039271ffbf71ebdc8c109fc98eac8e137`，以下文件行号均基于此提交。
- 本地 SDK `sources/android-36` 的关键 Java API 与该基线交叉检查。
- 另检查当次请求的 `main` 所解析提交 `745ee92b87ed62b5a8a1bac47d5df8cad623bf59` 的两份 SDP native 文件和两份 Binder 接口：两份 native 文件与主基线字节相同；接口均未发现通用自定义 SDP 注册方法。这只是另一个提交的交叉检查，**不能把 main 名称当作 Android 17 的证明**。
- 当前项目 `minSdk=29`、`compileSdk=37`、`targetSdk=37`。本轮没有取得用户手机 ROM 的蓝牙模块二进制，也没有覆盖 Android 10–17 每一版本或厂商修改。
- [证据清单](../evidence/android-bluetooth-feasibility.json)保存25份下载文件的提交、URL、长度和 SHA-256；各提交的 NOTICE 同时保留。文件仅用于研究，不进入手机工程。
- [下载复核脚本](../tools/fetch-aosp-bluetooth-evidence.ps1)默认固定主基线；若本地快照与上游不同则报错，不覆盖已有文件。

### 我们的权限实现

`D:/carvex-research/android/app/src/main/kotlin/io/github/iamr0s/carvex/ShizukuBluetoothMac.kt` 只执行 `settings get secure bluetooth_address` 并校验地址。

当前 manifest 声明 `BLUETOOTH_CONNECT`，未声明 `BLUETOOTH_PRIVILEGED`；仅凭 manifest 也不能确定厂商是否授予了特殊能力。**已存在 Shizuku 依赖，不等于已经具备 SDP 注册后端**。未改权限、未调用隐藏事务、未连接设备做实验。

## 3. 公共监听接口实际做了什么

核查调用链：

```text
BluetoothAdapter.listenUsingRfcommWithServiceRecord(name, uuid)
  → createNewRfcommSocketAndRecord：新建 BluetoothServerSocket
  → BluetoothSocket.bindListen
  → IBluetoothSocketManager.createSocketChannel(type, name, uuid, port, flags)
  → BluetoothSocketManagerBinder → JNI → native listen
  → btsock_rfc_listen：新建 RFCOMM slot
  → BTA_JvGetChannelId：分配 SCN
  → create_server_sdp_record：注册该 slot 的一条 SDP 记录
  → BTA_JvRfcommStartServer
```

定位：`BluetoothAdapter.java:3051,3273`；`BluetoothSocket.java:765`；`BluetoothSocketManagerBinder.java:164`；`com_android_bluetooth_btservice_AdapterService.cpp:1816`；`btif_sock_rfc.cc:360,516,1013,1073`。

每个 slot 有自己的 UUID、SCN、SDP handle 与文件描述符。清理时删除该 slot 的 SDP handle、关闭传输、释放 SCN（`btif_sock_rfc.cc:541`附近）。没有“发现同一 app 的另一个 UUID 后自动合并到已有监听”的分支。

`BluetoothSocketSettings` 新接口仍为单一 `rfcommUuid`；`BluetoothAdapter.java:4439` 的普通 RFCOMM 分支仍创建一个 server socket，不是多记录管理接口。

注意时序：`BTA_JV_GET_SCN_EVT` 先把通道号送到 Java，再调度 SDP 创建和 RFCOMM 服务启动。因此 Java 监听方法返回本身不能作为“对端已能搜索到 SDP”的证据；需要外部查询确认。

### 为什么反射固定通道不是解法

隐藏 `listenUsingRfcommOn(channel,...)` 创建的也是新监听，不是向现有监听挂记录。`bta_jv_act.cc:721` 对指定正通道执行 `BTA_TryAllocateSCN`，已占用或无效即失败，不会把两个 listener 合并。

隐藏 `SOCKET_CHANNEL_AUTO_STATIC_NO_SDP` 能要求不自动创建 SDP；它只完成“创建通道”这一半，仍缺少可供普通应用调用的自定义记录注册/注销入口。

也不能固定车机远端 channel 为1或3：它们是苹果某些本地注册调用的初值，既不是所有车机的通道，也不是恒定最终分配值。

## 4. 新增的 SDP 属性差异

对四个 WiAP UUID，AOSP 不命中 SPP/OPP/PBAP 等特例，走 `btif_sock_sdp.cc:405` 的 `add_rfc_sdp_by_uuid → add_sdp_by_uuid`。

`add_sdp_by_uuid:157` 和 `create_base_record:94` 添加自定义 ServiceClassIDList、L2CAP/RFCOMM ProtocolDescriptorList、非空服务名、Public Browse Group；`SDP_CreateRecord` 另外添加记录 handle。该路径没有调用 `SDP_AddProfileDescriptorList`。标准 SPP UUID 的专用路径确实添加 profile descriptor，但我们的自定义 UUID不走它。

| 已核查项目 | 24A446 普通 WiAP | 目前调用方式在此 AOSP 基线下 |
|---|---|---|
| 本地服务类 UUID | legacy `…cafe` 与 v2 `…0a77`，各一条记录 | 可分别注册这两个 UUID |
| legacy/v2 的 RFCOMM 通道 | 同一个运行时分配通道 | 两个独立分配通道 |
| attribute `0x0009` | profile `0x1101`，version `0x0102` | 自定义 UUID通用路径不添加 |
| 本地 Sink 组 | 上游 `enableSink` 条件选择的替代角色 | 我们另行无条件尝试发布 `…caff/…0a78` |

Sink 记录的 profile version 为 `0x0100`，不能拿它替换普通 WiAP 的 `0x0102`。两者都是 SDP 层字段，不是 iAP2 或 AirPlay 的版本。

不能把服务名改成 `Wireless iAP 1.2` 来补 attribute `0x0009`；服务名与结构化 profile descriptor 是不同属性。也不能改用标准 SPP 服务类 UUID 来换取 profile descriptor：那会改变车机搜索的服务类。

尚未确认苹果最终是否添加其他服务名、browse/language 等属性，也未获得小米实际 SDP 响应。因此本表不是最终 on-wire 全属性差分。

## 5. 底层可行，不等于应用可用

`system/include/hardware/bt_sdp.h` 的内部 `btsdp_interface_t` 明确支持先建无 SDP 的监听，再单独创建引用其 channel 的记录。

关键补充：`btif_sdp_server.cc:392` 的 `SDP_TYPE_RAW` **不是完全未实现**。当 `rfcomm_channel_number > 0` 时，它调用 `add_rfc_sdp_rec(name, uuid, channel)`，不会为这条记录再创建 RFCOMM listener。因此在蓝牙栈内部，可给同一 channel 注册不同 UUID 的记录。

但是：

- 这里的 RAW 不是“任意 SDP 属性字节原样写入”。此创建分支只使用 name/UUID/channel，仍回到上述通用构造；仅填 `hdr.profile_version` 不会自动生成自定义 WiAP 的 `0x0009`。
- `SdpManagerNativeInterface.java` 与 `com_android_bluetooth_sdp.cpp` 的 JNI注册表暴露 MAP/PBAP/OPP/SAP 等专用创建函数，没有通用 RAW 自定义创建函数。
- `IBluetooth.aidl` 有 `sdpSearch`，但那是查询远端；它与 `IBluetoothSocketManager.aidl` 都没有把内部通用记录注册/注销能力暴露给应用。
- `startRfcommServer` 是受限制的系统托管监听接口，仍以单个 UUID注册监听，不是共享通道记录别名接口。
- 内部 `SDP_AddAttribute` 修改的是蓝牙栈进程内的 SDP 数据库。不能通过在普通 app 进程中复制 JNI类或加载一个同名库，就假定能修改正在运行的系统数据库。

能力分层：

| 运行层级 | 本轮能支持的结论 |
|---|---|
| 普通 app + 公共 SDK | 可做独立 UUID监听、主动连接、UUID发现与应用层仲裁；无所需的精确共享记录接口 |
| 反射 / 隐藏 API | 有指定通道、无 SDP监听、远端 SDP查询线索；不是完整注册解法，且有隐藏 API及ROM限制 |
| Shizuku shell Binder | 可以改变已有服务调用的身份/可用性；不会凭空增加缺失的 Binder 方法。当前工程没有对应后端 |
| 已授权的厂商扩展服务 | 只有确认其接口、权限、生命周期及实际响应后，才可视为能力；本轮未确认存在 |
| 修改/扩展手机系统蓝牙栈 | 技术上可在拥有数据库的进程内增加共享注册和属性构造，但不是普通 APK升级；需要新的实施范围与用户授权 |

本轮不建议以注入、换系统库或修改车机来绕过上述边界。系统栈方案仅记录为可能的工程路线，未实施，也未视为用户已授权。

## 6. 入站接纳与服务发现的两处容易误判

### 6.1 不调用 accept，并不等于苹果的接纳前拒绝

普通路径 `btif_sock_rfc.cc:708 on_srv_rfc_connect` 收到 `RFCOMM_SRV_OPEN`，建立 connected slot，再把 FD和连接信号发给 Java。`BluetoothSocket.accept:927` 消费此信号并返回 socket。

该提交确有 `is_accepting` 字段，但其拒绝检查位于 hardware-offload 的专用路径（`on_srv_rfc_connect_offload:691`）；不能把它套到本项目使用的普通 socket 路径，而且该检查本身也不是逐设备、接纳前的 app callback。

因此应用可以保证“只让一条已连接 socket 进入后续协议”，却不能保证“对端从未看到另一条连接建立”。关闭重复连接仍可能影响对端状态，不能用本机赢家日志证明双方选中了同一条连接。

### 6.2 UUID广播不等于新鲜且完整的 SDP记录

`BluetoothDevice.java:2451` 的 `getUuids` 只读缓存；`fetchUuidsWithSdp:2498` 是异步请求。其文档明确：超时、失败或配对期间，`ACTION_UUID` 也可能返回缓存。

所以：

- 请求返回 true，只能记录请求已受理/将有广播，不能记录“SDP成功”。
- 收到目标设备的广播，可记录观察结果；仅凭公共 API，不能保证它是本轮新鲜空中查询结果。
- 非空且只有 HFP/A2DP 等 UUID，不能解释成已验证 legacy WiAP存在。
- 缺少 v2 UUID，不能直接解释成“成功查询到 v2记录不存在”。
- UUID列表本身没有 RFCOMM channel及任意属性；不能据它区分记录缺失、attribute4解析失败、远端拒绝和链路超时。
- `createRfcommSocketToServiceRecord` 的底层仍会走 UUID→SDP→channel 路径；“我们的代码没有显式刷新UUID”不等于“Android连接时从不做SDP”。

应保留平台原始异常和可用错误码，但不要把通用 IOException/SDP失败写成明确的“服务不存在”。例如 native `handle_discovery_comp:1128` 把 discovery失败和零SCN一起处理，已经损失部分细分信息。隐藏 `sdpSearch` 是可进一步评估的增强观察入口，不是本轮已验证可跨ROM使用的方案。

## 7. 建议的应用层实施合同（未实施）

这不是“逐车配置表”，而是固定手机角色、依据运行时服务证据和连接事件决策。

### 7.1 角色与后端能力分开

- 手机发送端以 `PHONE_WIAP` 为设计基线：本地正常组 `…cafe / …0a77`，主动搜索对端 `…caff / …0a78`。不因固件有 Sink代码就同时扮演 Sink。
- `enableSink` 的完整设置来源仍未闭合；上述是与已查普通角色一致的产品选择，不是宣称每台 iPhone永远取同一配置。
- 将目前误导性的 `SINK_LEGACY_UUID/SINK_V2_UUID` 命名改为明确的本地普通角色名称；不能据现有变量名推断协议角色。
- 平台后端应明确报告：是否可共享记录通道、是否可定制profile属性、是否可接纳前拒绝、是否能取得带状态的完整远端SDP。
- 标准SDK后端若保留两个普通角色listener，必须记录 `independent_channels` 和 profile属性能力缺失；这是保留双UUID可达性的近似，不是已证等价方案。
- 不默认强断HFP/A2DP/LE Audio；69尚未建立苹果的通用先断音频规则。

### 7.2 服务证据模型

分开保存 `uuidHints`、`recordKnowledge`、`selectedService`，不要继续用一个 `sdpKnown = uuids.isNotEmpty()` 统领所有决策。

`recordKnowledge` 至少区分：`UNKNOWN`、`PRESENT_VALID`、`ABSENT_CONFIRMED`、`PRESENT_MALFORMED`、`QUERY_FAILED`。公共UUID列表通常只能提供提示，不能直接生产后三种确定结论。

严格后端：v2的attribute4查找返回失败才转legacy；该查找成功后channel解析失败或连接失败，结束该次尝试。这里要保留 `ATTRIBUTE4_LOOKUP_FAILED` 这一操作结果，不能一律缩写成“v2服务不存在”。这与已查固件局部分支一致，上层重试另计。

公共后端：如果证据不足而保留有界 v2→legacy探测，应显式命名为 `probe_on_unknown` 兼容策略，并记录为何探测。不能把所有 v2 IOException都包装成苹果规定的fallback。具体探测时限需实测，不复制当前20/60/65秒当作固件常量。

### 7.3 单一连接状态所有者

建议将角色、generation、服务级 pending-outgoing、已有socket与终止状态交给一个串行事件处理器；IO工作线程只回报事件，不各自抢“赢家”。

| 状态/事件 | 决策与边界 |
|---|---|
| PREPARING | 检查权限、蓝牙开关、目标配对、角色与监听资源；记录部分注册失败 |
| DISCOVERING / READY | 获取服务观察；允许已确认目标的入站事件进入仲裁，不把发现等待变成必然阻塞 |
| 发起主动连接 | 同步保留服务级 outgoing状态，再启动阻塞connect；不让多个UUID并行主动拨号 |
| OUTGOING_PENDING 时到达入站socket | 普通SDK后端关闭并记录 `closed_after_accept_pending_outgoing`，不冒充底层拒绝；有系统级能力的后端才可接纳前拒绝 |
| 无pending、无已有socket的有效入站 | 验证目标、generation、蓝牙/停止状态；接管该socket，阻止再启动主动连接 |
| 主动连接成功 | 只有当前generation和仍持有该预留的尝试可接管；其他迟到成功必须关闭 |
| 主动连接失败 | 确认尝试资源关闭后清除pending；按证据决定同轮fallback/等待入站，不把取消当失败重试 |
| CONNECTED | 只交付一个socket给后续协议；清理未选中的监听/尝试；保留重复连接诊断 |
| 取消、蓝牙关闭、目标改变 | 递增generation，关闭阻塞IO，等待工作线程退出；禁止迟到回调恢复会话 |

苹果 service队列检查不只是“同地址才拒绝”，实现设计应保留服务级语义；我们产品的单车会话限制也不能由固件容量5直接改成五会话。

上表是平台受限的近似设计，不是已经证明能在两端同时主动连接时完成一致仲裁。若实测出现双方各自保留出站、关闭对方入站，则仍需追上游发起时机/重试分支或提供接纳前能力，不能用随机延迟掩盖为固件规则。

## 8. 实施前与实施后的验证门槛

第一批可以先改手机应用层的角色、证据模型、串行仲裁和日志，保持音频与其他阶段不动。标准SDK限制要作为明确诊断输出；若用户要求连SDP拓扑也完全一致，应先确认是否接受手机系统级工作，不能在APK中假装已完成。

最小单元测试集合：仅legacy提示、仅v2提示、双UUID、空提示、仅无关UUID、请求被拒、广播超时、旧广播迟到、v2存在但channel错误、主动/入站同刻完成、取消后迟到成功、蓝牙关闭、目标不匹配、第二条监听创建失败、关闭资源只执行一次、失败不提前释放pending。

实机验证必须另做：

1. 记录手机系统/蓝牙模块版本与实际授予权限；这一步不修改系统。
3. 单独比较iPhone真实发布记录与Android实际发布记录，再检查同车连接方向、重复连接、错误阶段。当前固件静态表不能替代iPhone运行样本。
4. 检查主动连接期间入站是否先成功后断开、双方是否持有同一连接，以及取消/重试后有无遗留记录。
5. 分别记录“角色修正”“方向仲裁”“SDP精确化”的实验结果，避免一次改完再把成功归因于某个字段。

### 仍开放

小米ROM实际SDP、Android37对应实现、苹果enableSink设置来源、远端SDP缓存刷新生命周期、上层连接发起/失败重试、profile切换条件、attribute0x0301的业务含义、所有SDP编码字段与各车实测。

## 9. 上游源码入口

以下URL固定到主基线提交；完整路径和SHA-256见证据清单。

- [公共监听与隐藏监听API](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/framework/java/android/bluetooth/BluetoothAdapter.java)
- [Socket绑定、连接与accept](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/framework/java/android/bluetooth/BluetoothSocket.java)
- [UUID缓存与SDP请求语义](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/framework/java/android/bluetooth/BluetoothDevice.java)
- [Socket Binder接口](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/android/app/aidl/android/bluetooth/IBluetoothSocketManager.aidl)
- [RFCOMM slot、创建和入站回调](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/system/btif/src/btif_sock_rfc.cc)
- [自定义UUID SDP构造](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/system/btif/src/btif_sock_sdp.cc)
- [分离的SDP创建与RAW分支](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/system/btif/src/btif_sdp_server.cc)
- [SDP内部接口声明](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/system/include/hardware/bt_sdp.h)
- [固定通道分配](https://android.googlesource.com/platform/packages/modules/Bluetooth/+/4b73ee6039271ffbf71ebdc8c109fc98eac8e137/system/bta/jv/bta_jv_act.cc)

## 10. 本轮验证记录

- 25份源码快照的SHA-256与长度均与证据清单相符。
- 下载脚本PowerShell语法检查通过；对已有快照重复下载复核通过，未覆盖原文件。
- 文档完整性检查通过：41份Markdown、33份JSON；只验证链接/结构，不验证协议语义。
- 24A446四组静态SDP数组重新从原镜像读取并核对。
- 未运行APK编译、手机连接测试、空中抓包或实车测试；没有因此关闭任何兼容性开放项。

## 11. 决策台账：先保留平台缺口，推进可对齐部分


### 11.1 平台缺口，不视为已完成

这里的“不能”限定为**当前普通APK + 已核查AOSP公共接口**，不是断言所有Android厂商系统永远不能支持。

| 编号 | 固件行为 | 当前限制与暂定处理 | 重新评估条件 |
|---|---|---|---|
| BT-LIM-01 | 同角色legacy/v2两条SDP记录共享一个RFCOMM监听通道 | 公共接口分别创建监听；保留双UUID时只能明确标记为独立通道近似 | 找到已授权可用的系统接口，且外部SDP查询证实两条记录指向同一实际监听 |
| BT-LIM-02 | 按固件生成SDP profile等结构化属性 | 自定义UUID公共注册路径不能补普通WiAP的`0x0009=0x1101/0x0102`；不能用服务名冒充 | 有可用的属性注册后端，并核对手机实际SDP响应 |
| BT-LIM-03 | RFCOMM接纳前做服务状态与pending-outgoing检查 | 普通app只能对已建立的入站连接做检查/关闭，无法保证对端没看到短暂连接 | 有真正接纳前的策略接口及两端时序验证 |
| BT-LIM-04 | 按内部SDP属性查询结果精确区分查找失败与channel解析/连接失败 | 公共UUID缓存/广播和连接异常不足以复原所有信息；保留UNKNOWN，不虚构“服务不存在” | 得到带明确结果语义的完整记录查询能力，并验证缓存、失败与广播生命周期 |

### 11.2 能推进的项目，按对齐程度区分

| 项目 | 能做什么 | 不能夸大的地方 |
|---|---|---|
| 手机角色 | 普通WiAP与Sink分开；手机路径不再无条件发布两组角色服务 | 固件enableSink设置来源未全部闭合；不是已知按车型动态切换规则 |
| 新旧服务支持 | 保留普通组legacy/v2及对应远端服务查找，避免只实现一个版本 | 我们当前已经有v2代码，不应把未来工作宣传成首次增加v2；共享通道仍受BT-LIM-01限制 |
| 服务证据判断 | 不再把“UUID非空”当完整SDP已知；区分缓存提示、查询受理、未知、明确结果与连接错误 | 发起刷新或收到广播不保证新鲜SDP；精确固件fallback仍受BT-LIM-04限制 |
| 连接生命周期 | 串行管理主动尝试、入站、已有连接、取消、世代与资源关闭；避免重复交付 | 是实现固件状态约束的应用层设计；接纳时机仍受BT-LIM-03限制，不能保证双端仲裁天然一致 |

HFP/A2DP切换、精确主动发起/重试时机、`0x0301`含义属于**研究尚未闭合**，不是已证明的Android平台限制。先不引入通用强断音频策略，也不把局部反编译条件当作完整恢复流程。



- `bt/Iap2BluetoothServer.kt:49,86`：本地发布普通legacy `…cafe`；`bt/Iap2BluetoothClient.kt:52,328`：主动连接远端legacy `…caff`。这两条路径未实现v2。
- `bt/TargetDevicePrefs.kt`保存地址和名称，是目标选择，不是此蓝牙阶段的按车型方向配置。不能由其他阶段有配置就推断蓝牙也是按车型分派。
- `Iap2BluetoothClient.kt:245`与`BtProfiles.kt:76`：在主动连接前尝试断开目标设备的音频profile。其仓库记录了奥迪经验，但本轮没有复核对应原始实车样本，不能据此推断苹果通用策略，也不能认为删除此行为必然增加兼容性。

兼容性判断：

1. **相对我们当前实现**，纠正混合角色、错误服务信息判定和竞争路径有明确工程价值，但每项连接收益仍需验证。
3. **更接近固件不等于兼容集合单调扩大。** Android近似的接纳时机、缺失的上层重试、车机历史状态或实现缺陷，都可能让部分对齐产生回归。特别不能只照搬一个“拒绝入站”条件，却遗漏苹果何时主动连接及何时解除pending。

建议验收同时看：同手机/同车机/同配对与音频profile初始状态下的首次连接、再次连接、失败恢复；记录双端连接方向、服务与重复连接，再检查首帧及持续会话。已有成功样本不得因新增路径而失效；无同条件实测不做“支持更多车”的结论。
