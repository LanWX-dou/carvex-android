# 01 — 从 `0x4301` 到 Wi-Fi 凭据

## 1.1 入口

`R-NB-1.1`（MUST / CONFIRMED）`0x4301` 的线格式、嵌套组和 getter 合法性以 `iap2_control_session/spec/14` 的 `R-13.1`–`R-13.7` 为准；本阶段只消费其中与网络引导有关的字段：

| `0x4301` 字段 | 本阶段用途 |
|---|---|
| `ssid` / `pass` | Wi-Fi 凭据 |
| `securityType` | 凭据安全类型 |
| `channel` | 关联信道提示 |
| `wifiIP[]` | 候选 IPv4 地址（不是本机地址） |
| `port` | 候选控制端口 |
| `deviceID` | 连接/设备标识；不能直接当作 `CarPlayUUID` |

不得把 14 个字段全部非空当作统一前置条件（`control R-13.6`）。字段缺失时按 `spec/14` 的记录/失败策略处理，不猜造。

**另一条已观测的凭据来源是 `0x5703`（Wi‑Fi Sharing）；它不是 `0x4301` 的字段，而是独立消息。** 23G90 样本在 `22:11:33.737` 收到一条 `0x5703`，携带 SSID `CFMOTO4801`、口令、securityType `0x02`、channel `0x9d`（157）；随后 `22:11:35.875` 发起 Association。`0x5703` 的 handler 是 `iap2_wifisharing_AccessoryWiFiConfigurationInformation`（`0x1001703cc`，feature 22 `kiAP2MessageHandlerEntries_WiFiSharing`），参数映射为：ID 0 = data（BSSID 候选）、ID 1 = SSID 字符串、ID 2 = 口令字符串、ID 3 = securityType U8、ID 4 = channel U8。它**不是 NowPlaying**；NowPlaying 是 `0x5000/0x5001/0x5002/0x5003`。

因此本阶段的凭据来源至少有两类：`0x4301` 的 14 字段与 `0x5703` 的 Wi‑Fi 配置。二者的先后、优先级和平台触发点仍未闭合（`OPEN-NB-1`），实现必须把两者都做成输入并记录实际来源。

依据：`control/spec/10` 的 `0x5702/0x5703` 行；`firmware/analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions/f_1001703cc.ghidra.c:40-205`；`research/protocol/iap2_control_session/runtime/accessoryd-packets-2026-10-16-221117.log.ips` 的 `22:11:33.737` 行。

依据：`control/spec/14` `R-13.1`–`R-13.7`、`R-13.9`。

## 1.2 映射到 Wi-Fi 凭据

`R-NB-1.2`（MUST / CONFIRMED）设备侧把车机 Wi-Fi 信息交给 `ACCPlatformPluginWiFiSharing` 的无线 CarPlay 处理路径；该路径读取以下键：

| 键 | 用途 | 备注 |
|---|---|---|
| `WiFiBSSID` | 目标 BSSID | 可缺失 |
| `WiFiSSID` | SSID | 必须有值 |
| `WiFiPassphrase` | 口令 | 无口令网络可为空 |
| `SecurityType` | 安全类型 | 数值；语义见 `OPEN-NB-2` |
| `Channel` | 信道 | 无效时平台可回退 |
| `LegacyAccessoryExternalAccessoryConnectionID` | 连接标识 | 与 `EAConnectionID`/CarPlayUUID 的关系仍 OPEN |

依据：`firmware/analysis/decompiler-cache/24A446/WiFiSharing/daf85b4040f95838b28e/functions/f_2431186ac.ghidra.c:28-45`；`analysis/00-evidence-index.md`。

## 1.3 校验规则

`R-NB-1.3`（MUST / CONFIRMED）实现必须在保存前执行以下校验：

1. SSID 为空 → 拒绝，不得进入关联；
2. 口令存在但 `SecurityType` 为“无安全” → 拒绝（“either SSID is nil, or passphrase is present but securityType is none”）；
3. `SecurityType` 数值 0/1/2 进入映射表；大于 2 记录 “Invalid accessory security type” 并拒绝；
4. 不得把“口令为空”自动解释为开放网络；是否开放由 `SecurityType` 决定。

数值 0/1/2 到 WPA/WPA2/WPA3 名称的完整映射尚未闭合，登记为 `OPEN-NB-2`；实现应保留枚举表并记录原值，不要用名称猜测。

依据：`f_2431186ac.ghidra.c:47-68,100-140`。

## 1.4 保存/更新凭据

`R-NB-1.4`（MUST / CONFIRMED）保存路径读取 `SSID_STR`、`password`、`CHANNEL`、`securityType`、`CARPLAY_PPID`；SSID 或口令缺失/为空时失败；`CHANNEL` 无效时记录 “invalid Wi-Fi channel, set channel to 1” 并回退到 1。

依据：`firmware/analysis/decompiler-cache/24A446/carkitd/a44efe703bd24020fb63/functions/f_100084514.ghidra.c:52-100`。

`R-NB-1.5`（MUST / CONFIRMED）更新已有网络时，平台会写入/比较：

- password；
- securityType；
- channel；
- `CARPLAY_NETWORK = true`；
- `CARPLAY_UUID`（当传入的 UUID 与网络现有值不同）。

依据：`f_10008413c.ghidra.c`（`WiFiNetworkSetProperty` 的 `kWiFiNetworkPasswordStringKey`、`CHANNEL`、`CARPLAY_NETWORK`、`CARPLAY_UUID` 调用点）。

## 1.5 CarPlayUUID / 连接标识

`R-NB-1.6`（MUST / OPEN）`CarPlayUUID` 被写入并持久化，这是已证事实；但它的**生成规则、与 `EAConnectionID`/`0x4301 deviceID` 的对应关系、重连时是否复用**未闭合（`OPEN-NB-3`）。

实现不得：

- 把 `0x4301 deviceID` 直接当 `CarPlayUUID`；
- 把 `LegacyAccessoryExternalAccessoryConnectionID` 直接当 `CarPlayUUID`；
- 在 UUID 缺失时伪造一个“看起来像”的值。

依据：`f_10008413c.ghidra.c`；`f_100084514.ghidra.c`；`CarKit` `CRSaveWiFiCredentialsForAccessoryConnectionIdentifier`。

## 1.6 状态机（候选）

`R-NB-1.7`（MUST / INFERRED）建议实现按以下状态推进，并把每步的输入/输出写日志：

```text
PARSE_4301 / PARSE_5703
  → VALIDATE_FIELDS
  → SAVE_OR_UPDATE_CREDENTIALS
  → MARK_CARPLAY_NETWORK (CarPlayNetwork=true, CarPlayUUID)
  → ASSOCIATE
  → ADDRESS (DHCP / IPv6 link-local)
  → ENDPOINT
```

`PARSE_4301`/`PARSE_5703` 到 `ASSOCIATE` 的**精确平台触发点与先后**仍未被单一分支证明（`OPEN-NB-1`）：静态可见 `CRWiFiCarManager` 的保存/更新与 `WiFiSharing` 的参数处理，运行日志可见 `carkitd` 删除/重建网络后 `WiFiManager` 发起 Association，以及 `0x5703` 早于 Association；但“哪一次调用必然触发关联”不能写成 CONFIRMED。

依据：`f_2431186ac.ghidra.c`；`f_10008413c.ghidra.c`；`f_100084514.ghidra.c`；`wifimanager-10-16-2026__22:08:31.log`（`carkitd` → RemoveNetwork → Auto-Join → Association）。

## 1.7 日志与脱敏

`R-NB-1.8`（MUST / CONFIRMED）口令、`ekey`/`eiv`、证书私钥材料不得写入日志；SSID/BSSID/channel/securityType 可记录，但应按部署策略脱敏。失败日志至少包含：阶段、字段名（不包含值）、错误码/原因。

依据：本项目日志规范与 `control/spec/14` 的脱敏要求。
