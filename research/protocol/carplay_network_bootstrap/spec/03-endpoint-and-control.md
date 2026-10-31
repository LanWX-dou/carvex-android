# 03 — 端点选择与控制连接

## 3.1 端点候选

`R-NB-3.1`（MUST / OPEN）控制端点至少有四类可能来源，实现必须把它们做成可配置/可记录，不能只取其中一种：

1. `0x4301` 的 `wifiIP[]` + `port`；
2. mDNS `_airplay._tcp` 的 `SRV`（端口）与 `A/AAAA`（地址）；
3. 由车机 BSSID/链路本地规则推导的 IPv6 link-local；
4. 其他平台/车型配置（静态表、用户输入、缓存）。

哪一类在某个 profile 中是权威来源，当前未闭合（`OPEN-NB-4`）。

依据：`control/spec/14`（`wifiIP`、`port`）；`airplay_mdns_discovery`；`netstat.txt`；`system_logs.logarchive` 中的 `_airplay._tcp` 浏览事件。

## 3.2 已观测的控制连接

`R-NB-3.2`（OBSERVED / CONFIRMED-样本）`netstat.txt` 记录了 `airplayd` 的一条已建立 TCP 连接：

```text
local   fe80::cb1:d613:6b2b:c5c0%en0.49408
remote  fe80::6edf:4aff:fe14:6eea%en0.7000
state   ESTABLISHED
bytes   96390 / 15661
process airplayd:401
```

对端链路本地地址 `fe80::6edf:4aff:fe14:6eea` 正好由车机 BSSID `6c:df:4a:14:6e:ea` 的 EUI-64 形式导出（首字节 U/L 位翻转：`6c → 6e`，中间插入 `ff:fe`）。这是一个强样本，但**不能**据此断言所有车机都用 BSSID 派生链路本地地址，也不能断言端口恒为 7000。

依据：`sysdiagnose_2026.10.16_22-11-51+0800_iPhone-OS_iPhone_23G90/logs/Networking/netstat.txt:241`；`WiFi/wifi_status.txt`（BSSID）；`WiFi/arp.txt`。

## 3.3 地址与 scope

`R-NB-3.3`（MUST / OBSERVED）使用 IPv6 link-local 时必须携带接口 scope（如 `%en0` 或平台等价的 scope id）。样本的 local/remote 都带 `%en0`；缺少 scope 的 link-local 连接会失败或走错接口。

`R-NB-3.4`（MUST / OBSERVED）本地地址是 Wi-Fi 接口的链路本地地址，不是蜂窝地址；连接必须绑定到 Wi-Fi 接口（见 `R-NB-2.6`）。

## 3.4 端口

`R-NB-3.5`（MUST / OBSERVED）样本端口是 `7000`，与 `airplay_control_plane` 的观测一致；但端口必须来自 `0x4301 port`、mDNS `SRV` 或目标配置，**不得写死 7000**。

依据：`netstat.txt:241`；`airplay_control_plane/spec/01-control-channel.md`；`control/spec/14`（`port`）。

## 3.5 mDNS 不是已证必经步骤

`R-NB-3.6`（MUST / OPEN）当前不能证明“所有 CarPlay 路径都必须先做 mDNS”。样本只证明了：

- `system_logs.logarchive` 中存在 `_airplay._tcp` 浏览事件；
- 最终存在一条 IPv6 link-local:7000 的 `airplayd` TCP 连接；
- `wifi_status`/`netstat` 不能证明该端点是由 mDNS 还是 `0x4301 wifiIP/port` 选出的。

因此实现应：

1. 先尝试 `0x4301`/配置给出的端点；
2. 若不可用或 profile 要求发现，再做 `_airplay._tcp` browse；
3. 记录实际使用的来源；
4. 不把 mDNS 固定放在 `0x4301` 之前或之后（`OPEN-NB-4`）。

依据：`airplay_mdns_discovery/spec/00-scope-and-terms.md`、`spec/01`；`system_logs.logarchive` 字符串；`netstat.txt`。

## 3.6 控制连接建立

`R-NB-3.7`（MUST / OBSERVED）TCP 建立后进入 AirPlay 控制面（`/info`、Pair、FairPlay、SETUP）。本 docset 只写到“TCP 已建立”；不得把 `connect()` 成功当作 CarPlay 成功。

`R-NB-3.8`（MUST / CONFIRMED）连接日志至少包含：本地接口、本地地址、远端地址、scope、端口、端点来源、耗时、失败原因；不得记录口令/密钥。

依据：`airplay_control_plane/spec/01-control-channel.md`；`netstat.txt`。
