# 04 — 地址解析与事件模型

> 对应覆盖项 8（地址解析）与 9 的前半（候选从哪来）。
> 本章定位了事件字典函数，但尚未证实 `IPAddress`/`Port` 是其键；**iOS 如何在多条地址间挑选**没有证据。

## 4.1 浏览器 → 事件

`APTransport` 里与“发现结果交付”相关的符号与字符串：

| 项 | 地址 | 说明 |
|---|---|---|
| `__APBonjourBrowserCreateEventInfoDictionary` | `0x24fd99e88`–`0x24fd99f1c`（148 B，37 条指令） | 构造事件字典的函数；函数体内**没有任何字符串引用**，键应来自调用方或常量 CFSTR |
| 字符串 `IPAddress` | `0x24fe52561` | 可能是事件键；**Ghidra 引用数 0** |
| 字符串 `Port` | `0x24fe523fa` | 可能是事件键；**Ghidra 引用数 0** |
| 字符串 `InterfaceName` | `0x24fe4628c` | 可能是事件键；**Ghidra 引用数 0** |
| 字符串 `awdl0` | `0x24fe48357`（另有 `__const` 副本 `0x24fe44b78`） | AWDL 接口名 |
| 字符串 `nan0` | `0x24fe48362`（另有 `__const` 副本 `0x24fe44b89`） | NAN 接口名 |

**结论（`A04.1`，`INFERRED`）**：存在一个“把设备信息装进字典”的函数，但**它的键无法确认**——三个候选键字符串在 `__cstring` 里存在却在 Ghidra 里零引用，说明它们要么是别的用途（日志/诊断），要么经本镜像之外的常量表引用。因此本阶段**不写“事件字典 = {IPAddress, Port, InterfaceName}”**；参考实现里的候选结构是本项目自己的建模（`A05.1`），不是对 iOS 事件形状的复刻。

## 4.2 接口绑定

`awdl0`/`nan0` 的引用点（Ghidra 参数引用，`A04.2`）：

| 字符串 | 引用点 | 所在函数 |
|---|---|---|
| `awdl0` | `0x24fdc3c58` | `_APTSessionHealthReporterReportNetworkStatus` |
| `awdl0` | `0x24fdfdf14` | `-[APAssistedModeBrowser startBonjourBrowser]` |
| `awdl0` | `0x24fe1c3e8` | `__APBonjourBrowserTickleDetailedMode` |
| `nan0` | `0x24fe1c20c` | `__APBonjourBrowserReconfirmDevice` |

另外 `__APBonjourBrowserSetModeInternal` 在 `0x24fd90480`/`0x24fd90620` 分别引用 `__const` 里的 `awdl0`/`nan0` 副本。这说明浏览可以绑定到**特定网络接口**，不是只在一个默认接口上收组播；AWDL 与 NAN 是两条独立的后端路径。

顺带一条：`local.`（`0x24fe49e7f`）被 `_APCarPlayControlServerAddInterface`（`0x24fe01f80`）与 `_BonjourDiscoveryDelegateStart`（`0x24fd928d0`）引用，说明手机侧也会在 `local.` 域里宣告/浏览 CarPlay 控制服务（`A04.6`）——但谁先谁后、车机是否也浏览手机，仍未取证。

对客户端实现的含义：

- 基础设施 Wi-Fi 上浏览时，绑定 Wi-Fi 接口；
- 若要覆盖 AWDL/NAN，需要单独的接口与后端（Windows/Linux 上没有等价物，`OPEN-MDNS-2`）；
- 组播加入要按接口做（IPv4 `IP_ADD_MEMBERSHIP` 指定 `imr_interface`，IPv6 `IPV6_JOIN_GROUP` 指定 `ipv6mr_interface`），否则多网卡机器会收错接口。

## 4.3 地址解析

- SRV 的 `target` 是**主机名**（如 `Receiver.local.`），不是地址；必须再用 A/AAAA 解析（`A02.1`）。
- 一个 target 可以有多条 A/AAAA，也可能只有 IPv6（`ipv6-linklocal-only` 向量）。
- link-local（`fe80::/10`）必须带 scope/接口才可连接；只给地址不给接口时参考实现标 `link_local=true` 且不给“可直接连接”的结论（`A04.4`）。

### 4.3.1 IPv6 与 link-local（新证据，字符串级）

`APTransport` 里有一整组 `_APConnectivityHelper*` 函数名以 `__func__` 字符串形式存在（说明函数确实存在，名字被剥离）：

| 字符串 | 地址 |
|---|---|
| `_APConnectivityHelperStartIPv4AddressListener` | `0x24fe5b892` |
| `_APConnectivityHelperStartIPv6AddressListener` | `0x24fe5b6ae` |
| `_APConnectivityHelperHandleIPv6ChangedEvent` | `0x24fe5b75f` |
| `[%{ptr}] IPv6 Address changed (for interface %@): %@ = %@` | `0x24fe5b7f1` |
| `IPv4Addresses` / `IPv6Addresses` | `0x24fe580cc` / `0x24fe580be` |
| `SupportsIPv6` | `0x24fe44ad1`（`__const`） |
| `enableForceIPv4Addressing` | `0x24fe4ca2a` |

`AirPlaySender` 里还有一条明确的转换日志：`[%{ptr}] <APUGL> Converting addresses if IPv6 link local: %@`（`0x251c1e186`）。

结论（`A04.7`、`A04.8`，`INFERRED`）：iOS 侧对 IPv4/IPv6 是**分别监听**的，且发送侧存在“把 link-local 地址做转换”的路径；“强制 IPv4”偏好键存在但其语义/用途未证。**车机是否宣告 IPv6、scope 怎么给**仍无证据（`OPEN-MDNS-12`）。

## 4.4 候选排序

参考实现 `rank_candidates` 的默认打分（`A05.1`，自测）：

| 条件 | 分值 |
|---|---|
| IPv4 地址 | +3 |
| IPv4 与浏览接口同网段 | +2 |
| IPv6 全局地址 | +2 |
| IPv6 link-local | 调用方提供实际接收接口后 +1；无 scope 时不可用 |
| 缺 SRV、端口 0、缺地址或仅有无 scope 的 link-local 地址 | 直接 `usable=false`，不参与打分 |

排序是**可解释**的：每个候选带 `reasons` 列表；实现不得静默重排、也不得自动连接第一个（`R-5.4`）。

## 4.5 iOS 怎么选

**没有证据**。`APTransport` 里没有找到“比较多个地址并选一个”的明确函数；`APTransportConnection` 的连接逻辑属后续阶段。因此：

- 参考实现的排序是**本项目的工程选择**，不是 iOS 行为；
- 车机可能只宣告一条地址（常见），也可能同时有 IPv4/IPv6；
- 多地址选择策略记 `OPEN-MDNS-16`。

## 4.6 本章未解决

| 编号 | 问题 |
|---|---|
| `OPEN-MDNS-16` | iOS/车机场景下多地址的优先级与回退顺序 |
| `OPEN-MDNS-12` | IPv6 是否可用、link-local scope 怎么给 |
| `OPEN-MDNS-9` | 车机 SRV 端口与 target 形态 |
