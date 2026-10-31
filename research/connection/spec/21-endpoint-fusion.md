# 21 — 端点汇合：`5703`、`4301`、Bonjour 与 AirPlay 控制端点

日期：2026-10-29。基线：iPhone18,1 / iOS 27.0.1 / build 24A446。

本章只记录静态反编译、原始指令字节来源及已有的有界分析。本轮没有执行 24A446 的生产代码，也没有完成 DNS、Wi‑Fi 关联、认证、真实 AirPlay 控制连接或首帧显示。因此“端点候选已构造”不能写成“网络已连通”或“投屏已成功”。证据索引见 [endpoint-fusion-evidence.json](../evidence/endpoint-fusion-evidence.json)。

## 1. 先给结论

无线连接不是一条可无条件复写的 `5703 → 4301 → Bonjour → AirPlay` 直线：

1. `0x5703` 是配件发给手机的 Wi‑Fi 参数交接。当前 handler 只解析参数并异步交给平台；返回成功只说明本地接收/交接，不说明已经关联、取得地址或有 AirPlay 服务。
2. `0x4301` 是配件发给手机的 CarPlay start-session 请求，可携带 SSID、口令、IP 候选、端口和身份元数据，并调用 `platform_CarPlay_startSession`。它不是所有车型都必经的 `5703` 响应，也不能证明目标端口可达。
3. 已审阅的 APTransport helper 路径会把当前网络/接口、会话身份、会话提供者的地址及端口、Advertiser 信息和显示配置汇合，才发布内部 `StartSessionEvent`。这些“event type 0/1”是进程内事件标签，不是线上帧；helper 的完整手机/车机角色绑定尚未闭合。
4. Bonjour 静态代码确实读取 `deviceID`、`deviceInfo`、`featuresEx` 及 TXT feature 字段，但本轮没有证明任何一个字段对每种车辆都是必填，也没有证明所有端点都必须由 Bonjour 提供。

## 2. 生产者—消费者图

| 生产者/输入 | 直接消费者 | 能证明什么 | 不能证明什么 |
|---|---|---|---|
| iAP2 `0x5703` | accessoryd handler `0x1001703cc` → WiFiSharing/平台异步工作 | 收到 BSSID、SSID、口令、securityType、channel 这组参数 | OS 已关联、地址/路由已就绪、AirPlay 端口已监听 |
| iAP2 `0x4301` | accessoryd handler `0x10016d3ac` → `platform_CarPlay_startSession` `0x100063fd0` | 配件请求手机启动会话；字段被解析并交给平台 | 该 IP/port 属于当前可达端点、认证已完成、视频可显示 |
| 当前网络/会话状态 | APTransport `_carPlayHelperSession_updateNetworkAndSessionState` `0x24fd9c6b8` | 经过接口、身份、地址和时间门槛后可生成内部 StartSessionEvent | 事件已经被异步消费者处理、已发出 DNS/HTTP/RTSP、车机已出首帧 |
| Bonjour device/TXT | APBrowser/APTransport advertiser 及 feature 解码 | 设备身份/能力元数据可作为端点候选输入 | 字段完整性、车机配对信任、网络连通性 |

`5703` 与 `4301` 都承载于当前 iAP2 控制会话，但现有证据没有建立两者的严格事务 ID、固定先后或“一条缺失就必须失败”的全局规则。

## 3. `0x5703`：网络参数交接边界

### 3.1 已证实字段

`0x1001703cc` 按嵌套 TLV 参数解析：

| 参数 | 线值 | 当前可证去向 |
|---|---|---|
| `0` | Data | BSSID 候选；此 handler 未强制长度为 6 |
| `1` | C string | SSID |
| `2` | C string | passphrase；排障记录不得写明文 |
| `3` | U8 | securityType，完整枚举仍 OPEN |
| `4` | U8 | channel |
| `5`,`6` | 未消费 | handler 直接跳过，不编造语义 |

随后调用是异步平台交接。SSID 缺失，或 passphrase 对象存在且 securityType 为 0 时，WiFiSharing 消费函数不会设置 CarPlay Wi‑Fi 参数；`securityType >= 3` 会进入 invalid 诊断并把映射结果置 0，但不能仅凭该分支宣称整条会话必然被拒绝。

### 3.2 验收契约

| 问题 | 必须独立记录 |
|---|---|
| 进入条件 | iAP2 业务准入、所需 message ID 能力、无线允许/CarPlay 配对状态 |
| 接受条件 | TLV 边界/类型通过；handler 成功返回；平台异步任务被创建 |
| 成功证据 | OS Wi‑Fi 关联完成、安全握手完成、接口得到地址、目标服务可达；四项分别取证 |
| 超时/重试/清理 | 本轮没有恢复统一 join 超时数字；配置接收、关联、地址配置、服务发现应分开计时；不要因一次失败删除蓝牙 bond |
| 下一事件 | 等待网络/接口状态，或进入适用的 `4301` / Bonjour / 其它邀请分支；不能直接跳到 AirPlay SETUP |

## 4. `0x4301`：start-session 输入边界

`0x4301` 方向为配件 → 手机。handler 解析后调用 `platform_CarPlay_startSession`；首个参数由 primary endpoint 查得的 ExternalAccessory connection ID，不是 AirPlay deviceID、IP 地址或端口。

| 组/参数 | 字段 | 线值 | 注意 |
|---|---|---|---|
| `0/0` | usbIP | C string，可重复 | 有线元数据，不并入无线地址 |
| `1/0`,`1/1` | ssid/pass | C string | 缺失保持空槽；口令脱敏 |
| `1/2`,`1/4` | channel/securityType | U8 | 不扩大为 U16/U32 |
| `1/3` | wifiIP | C string，可重复 | 只是候选输入；IPv4/IPv6、scope、接口和可达性由下游判定 |
| `2` | port | BE U32 | getter 宽度不等于已完成端口范围校验 |
| `3` | deviceID | C string | 不能因名称当作 MAC |
| `4` | pubKey | C string | 编码/信任尚未闭合 |
| `5`,`6` | srcVer/sdkVer | C string | 对端声明，不是本端版本 |
| `7/0`,`7/1` | assetID/assetVer | C string/BE U32 | 条件元数据，必要性 OPEN |
| `8` | mutualAuth | Bool | 缺失不能自动当 false |

空参数路径仍可继续交接；因此“14 个字段全部存在”不是 handler 的要求。未知 ID 继续遍历，不能自行添加线上 ACK。也没有证据证明 `5703` 必须先到，或 `4301` 必须先到。

## 5. APTransport 的局部汇合点

### 5.1 网络/接口门槛

`_carPlayHelperSession_updateNetworkAndSessionState` 在 24A446 中对 wired/wireless 状态分别评估。反编译可见的拒绝/等待条件包括：

- 网络 SSID、网络对象、接口/会话对象缺失；
- 原函数日志称为 `Local IP` / `Remote IP` 的地址缺失；这是 helper 的命名，尚不能据此绑定到手机/车机角色；
- 会话 UUID 不匹配；
- 会话开始时间超过内部阈值；
- 接口变化仍未被接受，或当前状态与会话 transport 不一致；
- display configuration 生成失败。

地址列表从会话提供者取得，代码以 `firstObject` 开始枚举并对地址族/链路本地 IPv6 做选择；已有交接记录明确指出“偏好 IPv6”及真实 provider 格式仍 OPEN。该函数只构造候选与内部事件，不能证明下游已经执行 DNS、socket connect 或 CarPlay 认证。

### 5.2 `StartSessionEvent` 的内容

满足门槛后，代码执行以下汇合：

1. 创建 `APSFeatures`，设置 feature IDs `7`,`9`,`0x20`,`0x25`,`0x26`；`supportsMutualAuthentication` 为假时另设 `0x1a`。
2. 从当前会话取 `AirPlayVersion`、`DeviceID`、`DeviceName`、`FeaturesEx`、`PublicCUAirPlayPairingIdentity`，写入 `AdvertiserInfo`。
3. 从选定 sockaddr 创建 `APSNetworkAddress`，设置会话提供的端口（调用点使用低 16 位）和接口名。
4. 可选地放入 `PairedVehicleIdentifier` 与 `RequestIdentifier` 的 `SessionHostInfo`。
5. 放入 `AdvertiserInfo`、`NetworkAddress`、`InterfaceType`、可选 `SessionHostInfo`、`InjectConnectCommand` 和 display configuration，发布内部 type=1 的 StartSessionEvent。

如果 display configuration 添加失败，日志明确为 “aborting discovery”；因此“已有地址/端口”仍不等于“允许启动视频”。事件回调的实际投递和消费者处理在本轮没有运行时证明。

## 6. Bonjour/TXT 只说明元数据来源

静态入口 `_APBrowserCreateAdvertiserInfoForDevice`（`0x24fd9842c`）负责构造 advertiser，相关 discovery 路径的已解析 key 索引包含 `featuresEx`、`deviceInfo`、`deviceID`；不能把这份索引当作该函数单独读取了全部 key 的证明。`_APBrowserCopyDeviceIDFromBonjourInfo`（`0x24fd9a298`）调用 CoreUtils `_BonjourDevice_GetDeviceID`。TXT 解析 API 明确包含：

- `deviceid` / `deviceID`；
- `features` / `featuresEx` / `fex`；
- 字符串、整数和 legacy feature flags 的转换/查询。

这些是“字段被解析/可用于构造 advertiser”证据，不是每辆车的必填表，也不证明 DNS-SD 已发现目标、地址已关联到同一车辆，或已完成 Pair-Verify。`_carplay-ctrl._tcp` 的手机服务邀请和手机随后连接的车机 AirPlay 控制端点是相反方向的两个角色，不能交换端口。

## 7. 本地接口地址过滤的范围

调用者 `0x24fd9b168` 的 event=10 分支读取 `NetworkInterfaceName` 和 `IPv4Addresses`，枚举时调用 `0x24fe06c24`，随后交给 `updateIPAddresses(..., interfaceName, filteredArray, 4)`。这是 ConnectivityHelper 的本地接口地址更新管线，**不是 `4301` 的远端 wifiIP 候选拒绝规则**；操作系统 provider 的完整合同仍未审计。

在这一范围内，24A446 的过滤函数 `0x24fe06c24` 首先要求解析成功，再按 family 对 IPv4(2) 或 IPv6(30) 执行已确认筛选：

- IPv4 过滤 `169.254.0.0/16` 与精确 `127.0.0.1`；
- IPv6 过滤精确 `::1`；
- 其它解析值可被追加，但这不是“已支持的 AirPlay host family”，也不是 route/scope/readiness 判断。

独立的诊断建议（`LOCAL_DESIGN`）：分别记录 `4301` 候选、Bonjour 地址和本地接口地址的角色、family、scope、interface、port 及身份来源，再关联到实际 socket；不要把三者混为一个地址，也不要把上述本地过滤直接应用于远端候选。旧网络 endpoint 事务分析还记录了地址更新时间戳、所选条目与后续 reassessment 的局部关系，但它不是完整运行证明；未触发下游不表示网络 ready。

## 8. 首次、再次、异常重连

现有证据只支持“应分别建模”，不支持把三种场景压成一个固定顺序：

| 场景 | 必须重新证明 | 可复用但不能臆定 |
|---|---|---|
| 首次配对 | BT bond、CarPlay 授权、iAP2 识别/认证、Wi‑Fi 参数接受、网络地址、Bonjour/端点身份 | 固件版本和静态 feature 定义 |
| 已配对重连 | 当前 bond/授权仍有效、旧 vehicle/endpoint 身份与新地址匹配、当前网络仍可用 | 持久 pairing 记录；不能因此跳过 AirPlay 会话验证 |
| 异常断线重连 | 旧 socket、事件队列、地址候选和回调均失效；新会话有独立 generation/时间线 | 不应自动删除 bond 或把旧端口当新端口 |

原 helper 在 session-events 未启用、active interface 或 session host 缺失时会清除自身 `+0xe8` 槽并退出该分支；这不等于已经证明整个端点候选、socket、队列都被清除。旧分析中的 service-lost/revoke/generation 规则明确标注为 LOCAL 设计，不能冒充固件行为。本轮没有闭合所有跨队列取消和世代检查。因此现场应记录：`5703/4301` 收到时间、OS 关联、接口/地址变化、Bonjour 记录、StartSessionEvent、控制 TCP、SETUP、首帧；不要只记“车机停在 AirPlay”。

## 9. AP-U01 / B-OPEN-06 状态

- **已关闭的局部事实**：`5703` 与 `4301` 的生产者/消费者及字段边界；APTransport 局部对象构造中的地址、接口、端口、AdvertiserInfo、可选 SessionHostInfo、display configuration；Bonjour/TXT 的静态解析入口；本地接口更新路径的 localhost/link-local 过滤。
- **仍 OPEN**：车机端点身份如何在 `4301`、Bonjour 和 AirPlay advertiser 之间匹配；IP 候选优先级及真实 scope/provider 合同；`5703` 平台异步完成到网络关联的返回/重试；首次/重连的严格时序；内部 StartSessionEvent 到实际 DNS/HTTP/RTSP 的消费者行为。

因此本章不能授权任何“收到某个字段后直接连接固定端口”的实现。下一步应先为一辆车采集端到端时间线，并把每个候选端点标注为 `received`、`accepted-by-platform`、`address-ready`、`service-reachable`、`control-connected`、`displayed` 六个独立状态。该状态命名属于本文诊断设计，不是固件枚举。
