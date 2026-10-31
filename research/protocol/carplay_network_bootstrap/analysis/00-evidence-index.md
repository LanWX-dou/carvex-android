# 00 — 证据索引

本文件把 `spec/01`–`spec/03` 的结论映射到静态函数与 sysdiagnose 文件。所有地址均为 24A446 的未加 slide 虚拟地址；所有运行值只代表对应样本。

## 1. 静态证据

### 1.1 `0x4301` schema

- `research/protocol/iap2_control_session/spec/14-carplay-start-schema.md`：14 字段映射、TLV 合法性、平台交接边界。
- 关键结论：外层 `0/1/2/3/4/5/6/7/8`；外层 1 子 ID `0…4`；外层 7 子 ID `0…1`；`port`/`assetVer` 为 BE U32；`securityType`/`channel` 为 U8；字符串 NUL 结尾。

### 1.2 Wi-FiSharing

`firmware/analysis/decompiler-cache/24A446/WiFiSharing/daf85b4040f95838b28e/functions/f_2431186ac.ghidra.c`

- `:28-45`：读取 `WiFiBSSID`、`WiFiSSID`、`WiFiPassphrase`、`SecurityType`、`Channel`、`LegacyAccessoryExternalAccessoryConnectionID`。
- `:47-68`：SSID 为空或“有口令但 securityType 为 none” → 拒绝。
- `:100-140`：`securityType` 0/1/2 进入映射表，`>=3` 报 “Invalid accessory security type”。

### 1.3 0x5703 Wi‑Fi Sharing

`firmware/analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions/f_1001703cc.ghidra.c`

- 函数名：`iap2_wifisharing_AccessoryWiFiConfigurationInformation`（`0x1001703cc`）。
- feature 22 `kiAP2MessageHandlerEntries_WiFiSharing`（`control/analysis/14-message-table.md:120`）。
- `:40-205`：按 param ID 解析 `0x5703`：ID 0 = data（BSSID 候选）、ID 1 = SSID 字符串、ID 2 = 口令字符串、ID 3 = securityType U8、ID 4 = channel U8。
- 23G90 样本 `22:11:33.737`：`57 03` 携带 `CFMOTO4801`、口令、securityType `0x02`、channel `0x9d`（157），随后 `22:11:35.875` Association。

### 1.4 carkitd / CRWiFiCarManager
`firmware/analysis/decompiler-cache/24A446/carkitd/a44efe703bd24020fb63/functions/`

| 函数 | 地址 | 作用 |
|---|---|---|
| `hasCredentialsForCarPlayUUID:` | `0x100083c2c` | 按 CarPlayUUID 查凭据 |
| `carplayUUIDForNetworkWithSSID:` | `0x100083c4c` | 从 SSID 取 UUID |
| `disassociateFromNetworkWithCarPlayUUID:` | `0x100083c94` | 断开指定 CarPlay 网络 |
| `networkForCarPlayUUID:` | `0x100083f50` | 按 UUID 找网络 |
| `networkForSSID:` | `0x100084038` | 按 SSID 找网络 |
| `updateExistingNetwork:password:securityType:channel:carPlayUUID:` | `0x10008413c` | 更新 password/security/channel；置 `CARPLAY_NETWORK`、`CARPLAY_UUID` |
| `saveNetworkCredentials:forCarPlayUUID:` | `0x100084514` | 读取 `SSID_STR`/`password`/`CHANNEL`/`securityType`/`CARPLAY_PPID`；channel 无效回退 1 |
| `removeNetworkCredentialsForCarPlayUUID:` | `0x100084cc4` | 删除凭据 |
| `setInCar:carPlayUUID:` | `0x100084db8` | 标记 in-car 状态 |

`CarKit`：

- `CRSaveWiFiCredentialsForAccessoryConnectionIdentifier`（`0x1c255e2d8`）：连接标识 → 凭据保存的接口线索；与 `CarPlayUUID` 的精确对应仍 OPEN。

### 1.5 MobileWiFi

`firmware/analysis/decompiler-cache/24A446/MobileWiFi/2993cc726f8d4837bc57/functions/`

- `_WiFiNetworkSetCarPlayInternetCheckState`（`0x291a1e550`）
- `_WiFiNetworkSetPublicAirPlayNetwork`（`0x291a1ef30`）
- `_WiFiNetworkSetAccessoryIdentifier`（`0x291a1f024`）

这些 setter 证明平台有 CarPlay/AirPlay 相关网络属性；本阶段没有把它们的调用者全部追完。

## 2. 运行状态证据

### 2.1 23G90（CFMOTO）

目录：`sysdiagnose/sysdiagnose_2026.10.16_22-11-51+0800_iPhone-OS_iPhone_23G90/`

| 证据 | 值 |
|---|---|
| `WiFi/wifi_status.txt` | SSID `CFMOTO4801`；BSSID `6c:df:4a:14:6e:ea`；WPA2 Personal；5g157/80；IPv4 `192.168.43.113`；Router `192.168.43.1`；IPv6 `fe80::cb1:d613:6b2b:c5c0`；DNS None；IPv6 Router None；IPv4 Config DHCP |
| `runtime/accessoryd-packets-2026-10-16-221117.log.ips` `22:11:33.737` | `0x5703` Wi‑Fi 配置：SSID `CFMOTO4801`、口令、securityType `0x02`、channel `0x9d`（157）；早于 Association |
| `WiFi/Entity_…_Join.csv` | `2026-10-16_22:11:36.151`；`dhcpLatencyMs=3306`；`dhcpLeaseMins=60`；`dhcpSuccess=1`；`ipv4Addr=1898686656`（网络字节序）；`routerMAC=6c:df:4a:14:6e:ea` |
| `WiFi/wifimanager-…22:08:31.log` | `22:11:35.875` Association；`22:11:36.119` 4-way total 18.308 ms；`22:11:36.139` `internetAccess bit ZERO`；`22:11:36.140` `kSCNetworkServicePrimaryRankNever`；`22:11:39.458` IPv4 callback（v4/v6 routable） |
| `logs/Networking/netstat.txt:241` | `airplayd` TCP6 ESTABLISHED，local `fe80::cb1:d613:6b2b:c5c0%en0.49408` → remote `fe80::6edf:4aff:fe14:6eea%en0.7000`，96390/15661 bytes |
| `WiFi/com.apple.wifi.known-networks.plist` | `CarPlayNetwork=true`；`CarPlayUUID=80A46250-7FB2-4A9F-ACF1-8F551F286B88`；`JoinedBySystemAt=2026-10-16 14:11:36`；`WPA/WPA2 Personal` |
| `WiFi/arp.txt` | `192.168.43.1 at 6c:df:4a:14:6e:ea on en0` |

### 2.2 22H374（Audi）

`sysdiagnose/sysdiagnose_2026.10.14_19-51-56+0800_iPhone-OS_iPhone_22H374/WiFi/wifi_status.txt`

- SSID `Audi_MMI_7411_5GHz`；BSSID `9a:49:14:f8:42:13`；WPA2 Personal；5g149/40；IPv4 `10.174.189.240`；Router `10.174.189.254`；IPv6 `fe80::1c50:9aa2:ce53:8ab9`。

### 2.3 21G93（CT6）

`sysdiagnose/sysdiagnose_2026.10.16_22-24-53+0800_iPhone-OS_iPhone_21G93/`

- `WiFi/wifi_status.txt`：BSSID `26:54:08:0c:e1:80`；WPA3 Personal；5g153/80；IPv4 `10.67.34.114`；Router `10.67.34.16`；IPv6 `fe80::80d:4908:bafa:5482`。
- `WiFi/com.apple.wifi.known-networks.plist`：SSID `全新CT6`；`CarPlayNetwork=true`；`CarPlayUUID=15DBD751-9521-4785-B76D-B5566FFD2B24`；`WPA2/WPA3 Personal`。

## 3. 证据边界

- 三套 sysdiagnose 都是**状态快照/统计库/日志**，不是包级抓包。
- 没有 mDNS/RTSP/FairPlay/RTP 原始报文；端点来源只能看到最终 socket，不能证明由 mDNS 还是 `0x4301` 选出。
- `CarPlayUUID`/`EAConnectionID` 的生成规则没有闭合。
- `securityType` 数值到名称的完整映射没有闭合。
- 没有真实车机上的客户端端到端成功记录；本 docset 是 v0 草稿。
