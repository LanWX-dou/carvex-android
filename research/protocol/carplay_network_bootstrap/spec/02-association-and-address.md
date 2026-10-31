# 02 — 关联、DHCP 与接口选择

## 2.1 三套观测样本

以下全部是 **sysdiagnose 状态证据**（`wifi_status.txt`、`wifimanager*.log`、`Join.csv`、`known-networks.plist`、`netstat.txt`），不是包级抓包，也不能代表所有车机。

| 样本 | SSID | Security | Band/Channel | IPv4 | Router | IPv6 link-local | DHCP | CarPlayNetwork |
|---|---|---|---|---|---|---|---|---|
| 23G90 | `CFMOTO4801` | WPA2 Personal | 5g157/80 | `192.168.43.113/24` | `192.168.43.1` | `fe80::cb1:d613:6b2b:c5c0` | 3306 ms，lease 60 min | `true`，UUID `80A46250-…` |
| 22H374 | `Audi_MMI_7411_5GHz` | WPA2 Personal | 5g149/40 | `10.174.189.240/24` | `10.174.189.254` | `fe80::1c50:9aa2:ce53:8ab9` | Join 记录未给出有效 latency | 该套未见 `CarPlayNetwork` 键 |
| 21G93 | `全新CT6` | WPA2/WPA3 Personal | 5g153/80 | `10.67.34.114/24` | `10.67.34.16` | `fe80::80d:4908:bafa:5482` | 未取到有效 latency | `true`，UUID `15DBD751-…` |

共同点：**5GHz、WPA2/WPA3 Personal、DHCP、IPv6 link-local、DNS 为空、IPv6 Router 为空**。这不是“所有 CarPlay 车机都必须如此”，只是三台样本的共同观测。

依据：`analysis/00-evidence-index.md` §2。

## 2.2 关联

`R-NB-2.1`（MUST / OBSERVED）实现必须从扫描结果/凭据中选择目标 BSSID，不能写死信道或 BSSID。三套样本都在 5GHz，但 5GHz 不是协议硬性要求；若目标车机只广播 2.4GHz，必须能关联。

`R-NB-2.2`（MUST / OBSERVED）关联使用 `SSID + passphrase + SecurityType + channel` 的组合；channel 是提示/筛选条件，不是“只允许该信道”的硬门。无效 channel 时平台可回退（见 `R-NB-1.4` 的默认 1）。

依据：`spec/01`；`wifimanager-10-16-2026__22:08:31.log`（Association 命令、4-way handshake、`Channel=157`）。

## 2.3 DHCP 与地址

`R-NB-2.3`（MUST / CONFIRMED-样本）IPv4 必须通过 DHCP 取得；样本中 IPv4 Config Method 为 `DHCP`，同时存在 IPv4 地址、路由器地址和到车机的默认路由。不得把 IPv4 地址写死或从 `0x4301 wifiIP` 直接当成本机地址。

`R-NB-2.4`（MUST / OBSERVED）IPv6 使用 Automatic/link-local；样本中 IPv6 Router 为 `None`，`ndp` 为空。客户端必须容忍“只有 link-local、没有全局 IPv6、没有 IPv6 默认路由”的情况。

`R-NB-2.5`（MUST / OBSERVED）样本中 DNS 为 `None`。客户端不得依赖 DNS 解析车机；控制端点必须用 `0x4301` 的 IP/port、mDNS 的 A/AAAA、或链路本地地址。

依据：`wifi_status.txt`（IPv4 Config Method、IPv6 Config Method、DNS、IPv6 Router）；`netstat.txt` 路由表；`ndp-info.txt`。

## 2.4 接口与路由

`R-NB-2.6`（MUST / OBSERVED）CarPlay Wi-Fi 接口在样本中是 `en0`；接口 rank 被设为 `kSCNetworkServicePrimaryRankNever`，`internetAccess` 位为 0，主要网络服务仍是蜂窝 `pdp_ip0`。同时，`netstat` 中存在经 `192.168.43.1` 的默认路由。

因此：

1. 不得假设 CarPlay Wi-Fi 是系统首选接口；
2. 不得依赖系统默认路由把流量送到车机；
3. socket 必须绑定到 Wi-Fi 接口（iOS 侧可用 `IP_BOUND_IF`/`IPV6_BOUND_IF` 或等价机制；其他平台用 `SO_BINDTODEVICE`/接口索引）；
4. 车机侧地址应来自该接口的 DHCP/链路本地/发现结果，而不是全局路由表。

依据：`wifimanager-10-16-2026__22:08:31.log`（`__WiFiDeviceManagerSetInterfaceRank`、`internetAccess bit ZERO`、`kSCNetworkServicePrimaryRankNever`）；`netstat.txt`；`wifi_status.txt`。

## 2.5 时序（仅供参考）

`R-NB-2.7`（SHOULD / OBSERVED）23G90 样本的时间线：

```text
22:11:35.875  Association 命令入队
22:11:35.880  __WiFiDeviceAssociateAsyncQueued（30 s 定时器）
22:11:36.119  4-way handshake 完成（total 18.308 ms）
22:11:36.151  Join 记录（DHCP latency 3306 ms、lease 60 min）
22:11:39.458  IPv4 callback（isIPV4Routable 1、isIPV6Routable 1）
```

这些是样本时序，不是固件常量。实现应使用有界超时（建议至少覆盖 30 s 关联 + 5 s DHCP），并把每一步的实际耗时写日志。

依据：`wifimanager-10-16-2026__22:08:31.log:13780-15020`；`Join.csv`。

## 2.6 失败与重试

`R-NB-2.8`（MUST / OPEN）关联失败、DHCP 超时、错误口令、信道不可用、IPv6 不可用、接口被系统切走后的重试/退避/清理顺序，当前没有单一静态分支或真实失败样本；实现必须把这些做成可配置，并保留 `OPEN-NB-6`。

实现不得：

- 在 DHCP 失败时把 `0x4301 wifiIP` 直接当本机地址；
- 在关联失败时无限重试同一 BSSID/口令；
- 在接口切换后继续使用旧 socket/旧地址。
