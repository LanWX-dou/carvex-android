# carplay_network_bootstrap — `0x4301` 之后的无线网络引导（v0 草稿）

本 docset 只回答一个问题：**设备侧客户端收到 iAP2 `0x4301` 之后，如何把车机给的 Wi-Fi 参数变成一条可用的 IP 通道，并连到 AirPlay 控制端点。**

范围：

```text
iAP2 0x4301（车机→设备）/ 0x5703（Wi‑Fi Sharing 配置）
  → 解析凭据（0x4301 14 字段 / 0x5703 SSID/口令/security/channel）
  → 保存/更新 CarPlay Wi-Fi 凭据与 CarPlayUUID
  → 关联车机 Wi-Fi
  → DHCP / IPv6 link-local
  → 选择接口/地址/端口
  → 建立 AirPlay 控制 TCP
```

不在范围：AirPlay Pair/RTSP/FairPlay/SETUP（见 `airplay_control_plane`）、媒体/输入（见对应 docset）、有线 USB CarPlay。

## 状态

**v0 草稿，部分完成。** 现有证据由两部分组成：

- **静态**：`accessoryd`/`carkitd`/`WiFiSharing`/`MobileWiFi` 的 `CRWiFiCarManager` 与 `handleAccessoryWiFiInformationForWirelessCarPlay:`；
- **运行状态**：三套 sysdiagnose（Audi MMI / CFMOTO / CT6）的关联、DHCP、IP、路由、`CarPlayNetwork`/`CarPlayUUID` 与 `airplayd` 控制连接。

没有包级 mDNS/RTSP/RTP 抓包；不少运行时选择仍是 `OPEN-NB-*`。不要把本 docset 当作“已互通”证明。

## 阅读顺序

1. [`spec/00-scope-and-terms.md`](spec/00-scope-and-terms.md)
2. [`spec/01-from-4301-to-credentials.md`](spec/01-from-4301-to-credentials.md)
3. [`spec/02-association-and-address.md`](spec/02-association-and-address.md)
4. [`spec/03-endpoint-and-control.md`](spec/03-endpoint-and-control.md)
5. [`spec/04-open-items.md`](spec/04-open-items.md)
6. [`analysis/00-evidence-index.md`](analysis/00-evidence-index.md)
7. [`reference-impl/README.md`](reference-impl/README.md)：纯规划模型与合成测试（不执行真实网络）。

## 证据基线

- 静态：24A446 `iPhone18,1`；`firmware/analysis/decompiler-cache/24A446`。
- 运行：`sysdiagnose/sysdiagnose_2026.10.16_22-11-51+0800_iPhone-OS_iPhone_23G90`（CFMOTO）、`..._22H374`（Audi）、`..._21G93`（CT6）。
- `0x4301` 字段 schema 以 `research/protocol/iap2_control_session/spec/14-carplay-start-schema.md` 为准，本 docset 不重复定义。
