# STATUS — carplay_network_bootstrap（v0）

## 结论

**部分完成（v0 草稿）。** 可以把“`0x4301` → 凭据保存/更新 → 关联 → DHCP/IPv6 → 控制 TCP”写成有静态与运行状态证据的实现指南；但以下关键点仍是 OPEN：

- `0x4301` 到平台 Wi-Fi 关联的**精确触发点**与平台必填性；
- `securityType` 数值到 WPA/WPA2/WPA3 的完整枚举；
- `CarPlayUUID` 与 `EAConnectionID`/`0x4301 deviceID` 的生成与生命周期；
- 端点来源：`0x4301 wifiIP/port`、mDNS、还是链路本地推导；
- DHCP 选项/IPv6 RA/DNS、失败重试、跨车型差异；
- 无包级 mDNS/RTSP/FairPlay/RTP 抓包。

## 覆盖表

| 项 | 状态 | 依据 |
|---|---|---|
| `0x4301` 字段解析与校验 | 静态已证 | `control/spec/14`（R-13.1–R-13.7） |
| `0x5703` Wi‑Fi 配置（SSID/password/security/channel） | 静态 + 运行样本已证 | `iap2_wifisharing_AccessoryWiFiConfigurationInformation` `0x1001703cc`；23G90 `22:11:33.737` |
| `0x4301` 平台必填性/下游交接 | OPEN | `OPEN-SES-2`、`OPEN-NB-7` |
| Wi-Fi 凭据键与校验 | 静态已证 | `WiFiSharing` `0x2431186ac` |
| 凭据保存/更新、CarPlayNetwork/CarPlayUUID | 静态已证 | `carkitd` `CRWiFiCarManager` |
| 关联车机 Wi-Fi | 运行观测（3 车） | sysdiagnose WiFi |
| DHCP/IPv4/路由 | 运行观测（3 车） | `wifi_status`、`Join.csv`、`netstat` |
| IPv6 link-local | 运行观测（3 车） | `wifi_status`、`netstat` |
| 接口 rank/默认路由策略 | 运行观测（CFMOTO） | `wifimanager` 日志 |
| 控制端点（IPv6 link-local:7000） | 运行观测（CFMOTO） | `netstat.txt` |
| mDNS 是否必经 | OPEN | `OPEN-NB-4`；`mdns` docset |
| 失败/重试/超时 | OPEN | `OPEN-NB-6` |
| 跨车型/版本差异 | 部分（3 样本） | `OPEN-NB-10` |

## 验证

```bash
python3 -B research/protocol/carplay_network_bootstrap/verify.py
```

`verify.py` 检查文件结构、条款编号、OPEN 登记、证据引用，并运行 `reference-impl/test_bootstrap.py` 的 14 个合成用例；它不验证协议语义或真实互通。

## 下一轮

1. 在真实车机上按 `spec/01`–`03` 做一次带 wire log 的客户端连接，记录 `0x4301 → 关联 → DHCP → TCP` 时间线。
2. 补一份 Wi-Fi 监听模式抓包，关闭 mDNS/端点来源与 DHCP 选项 OPEN。
3. 若能取得更多车型/版本，扩展 `spec/02` 的兼容性矩阵。
