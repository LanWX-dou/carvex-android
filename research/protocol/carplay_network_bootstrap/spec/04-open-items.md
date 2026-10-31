# 04 — OPEN 登记

`R-NB-4.1`（MUST / CONFIRMED）任何在正文出现的 `OPEN-NB-<n>` 必须在本表登记；关闭时必须给出新证据（原汇编地址/日志行/抓包片段）、被修改条款与回归结果。

依据：`README.md`、`TASK.md`、`STATUS.md` 与本 docset 的 `verify.py`。

| ID | 含义 | 阻塞什么 | 关闭条件 |
|---|---|---|---|
| `OPEN-NB-1` | `0x4301` / `0x5703` 到平台 Wi‑Fi 关联的精确触发点、先后与必填性 | 自动化网络引导状态机 | 追 `platform_CarPlay_startSession` 与 `0x5703` handler 下游到 `CRWiFiCarManager`/`WiFiManager` 的调用链，配合一次真实连接日志 |
| `OPEN-NB-2` | `securityType` 数值 0/1/2 到 none/WEP/WPA/WPA2/WPA3 的完整映射；WPA3 处理 | 关联参数选择 | 读 `f_2431186ac` 的 `DAT_26909c888` 表与 `MobileWiFi` setter；目标车机抓包/日志 |
| `OPEN-NB-3` | `CarPlayUUID` 与 `EAConnectionID`/`0x4301 deviceID` 的生成、对应与生命周期 | 凭据复用、重连 | 追 `carkitd`/`CarKit` 的 UUID 来源与 `SavePeer`/重连分支；运行样本 |
| `OPEN-NB-4` | 端点来源：`0x4301 wifiIP/port`、mDNS、BSSID 派生 link-local，谁优先 | 首次连接与重连 | 一份 Wi-Fi 监听抓包（mDNS + TCP）+ 客户端日志；目标车机对照 |
| `OPEN-NB-5` | DHCP 选项、IPv6 RA、DNS 的完整行为 | 地址/路由策略 | DHCP/RA 抓包；多车型对照 |
| `OPEN-NB-6` | 关联/DHCP/接口切换失败的重试、退避、清理 | 鲁棒性 | 故障注入 + 真实失败样本 |
| `OPEN-NB-7` | `0x4301` 平台层必填字段/至少一个 IP/组合策略 | N0/N1 验收 | 平台调用下游逐字段判空/分支；运行日志 |
| `OPEN-NB-8` | 5GHz 信道/带宽选择与 MIS channel 切换 | 关联成功率 | `wifimanager` 的 CarPlay join 分支 + 抓包；多车型 |
| `OPEN-NB-9` | 无包级 mDNS/RTSP/FairPlay/RTP 抓包 | 所有媒体/控制面结论 | 取得监听模式/车机侧抓包并脱敏 |
| `OPEN-NB-10` | 跨车型/版本差异（仅 3 台样本） | 兼容性矩阵 | 至少 2 车型 × 2 iOS 版本的可重放记录 |

## 关闭记录

（尚无关闭项。）
