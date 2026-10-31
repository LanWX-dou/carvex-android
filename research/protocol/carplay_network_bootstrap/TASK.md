# 任务书 — carplay_network_bootstrap（v0）

## 目标

给出“设备侧客户端收到 `0x4301` 之后到 AirPlay 控制 TCP 建立”的平台无关规范，使实现者知道：

1. `0x4301` 的哪些字段进入 Wi-Fi 凭据；
2. 凭据如何校验、保存、更新，如何标记 CarPlay 网络与 CarPlayUUID；
3. 如何关联车机 Wi-Fi、取得 IPv4/IPv6 地址；
4. 如何选择接口、地址、端口；
5. 何时算“网络引导完成”，以及失败/重试的边界。

## 输入

- `0x4301` 的 14 字段（`iap2_control_session/spec/14`）。
- 车机广播的 Wi-Fi（SSID/BSSID/security/channel），来自凭据或扫描。
- 平台 Wi-Fi/网络 API（关联、DHCP、接口、路由、socket）。
- 可选：mDNS `_airplay._tcp` 发现结果（`airplay_mdns_discovery`）。

## 输出

- 一个已关联的 Wi-Fi 接口，拥有 IPv4 地址（以及可用的 IPv6 link-local）。
- 一条到车机 AirPlay 控制端口的 TCP 连接。
- 可诊断日志：SSID/BSSID/channel/security、接口、地址、路由、端口、失败原因（口令脱敏）。

## 分级验收

| 级别 | 判据 | 当前文档 |
|---|---|---|
| N0 | 解析 `0x4301`，按 `spec/14` 校验字段；不要求 14 字段全非空 | 静态可支持 |
| N1 | 保存/更新 Wi-Fi 凭据，设置 `CarPlayNetwork`/`CarPlayUUID` | 静态 + 运行状态可支持 |
| N2 | 关联车机 Wi-Fi，取得 IPv4（DHCP）与 IPv6 link-local | 三套 sysdiagnose 观测 |
| N3 | 绑定接口，连上车机 AirPlay 控制 TCP（本样本 IPv6 link-local:7000） | 端点观测；mDNS vs 直连仍 OPEN |
| N4 | 完成 AirPlay Pair/Verify/SETUP，进入媒体/输入 | 不在本 docset |

## 非目标

- 不定义 `0x4301` 的字段线格式（以 `control/spec/14` 为准）。
- 不定义 AirPlay 控制/媒体协议（以 `airplay_control_plane` 等为准）。
- 不覆盖 USB/有线 CarPlay。
- 不把“收到 `0x4301`”“Wi-Fi 已关联”“TCP 已建立”单独当成 CarPlay 成功。

## 必须遵守的证据规则

- 静态结论标 `CONFIRMED/INFERRED`；运行时选择标 `OBSERVED` 或 `OPEN-NB-*`。
- 三套 sysdiagnose 是状态证据，不是包级抓包；不能据此宣称 mDNS/RTSP/FairPlay 已完成。
- 口令、密钥、证书不写入文档或日志明文。
- 任何“已互通”表述必须有真实车机的端到端记录，本 v0 不提供。
