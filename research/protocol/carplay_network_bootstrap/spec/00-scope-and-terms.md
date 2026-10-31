# 00 — 范围、角色与术语

## 0.1 角色

| 角色 | 在本阶段做什么 |
|---|---|
| 设备侧客户端（模拟 iPhone） | 解析 `0x4301`；保存/更新车机 Wi-Fi 凭据；关联；取得地址；连接 AirPlay 控制端口 |
| 车机 / accessory | 发 `0x4301`；广播/提供 CarPlay Wi-Fi；DHCP；提供 AirPlay 控制端点 |

本 docset 只写设备侧客户端。若实现角色反转为车机/配件，本阶段的状态机入口和凭据方向都要镜像，本文不覆盖。

## 0.2 层次

```text
iAP2 0x4301
  ↓ 字段解析（control/spec/14）
Wi-Fi 凭据（SSID/passphrase/security/channel）
  ↓ 保存/更新（CarPlayNetwork / CarPlayUUID）
平台 Wi-Fi 关联
  ↓
IPv4 DHCP / IPv6 link-local
  ↓
接口/地址/端口选择
  ↓
AirPlay 控制 TCP（本样本 IPv6 link-local:7000）
```

## 0.3 术语

| 术语 | 本文含义 |
|---|---|
| CarPlay 网络 | 车机为 CarPlay 提供的 Wi-Fi 网络；iPhone 侧可标记 `CarPlayNetwork=true` 并保存 `CarPlayUUID` |
| `CarPlayUUID` | iPhone Wi-Fi 配置中与该 CarPlay 网络关联的 UUID；本文只证“被写入/保存”，不证生成规则（`OPEN-NB-3`） |
| `EAConnectionID` | ExternalAccessory 连接标识；`0x4301` handler 用它作为平台调用的第一个实参（`control R-13.9`） |
| primary endpoint | 用于查找已连接 ExternalAccessory 的端点 UUID（`control R-13.9`） |
| link-local | IPv6 `fe80::/10` 地址；本样本控制连接使用带 `%en0` scope 的 link-local |
| 接口绑定 | 将 socket/路由绑定到 Wi-Fi 接口；不能依赖系统默认路由或 DNS |

## 0.4 证据等级

- `CONFIRMED`：反汇编/原始立即数直接证明，或 sysdiagnose 直接记录。
- `INFERRED`：由调用关系/符号/状态推断，未逐指令闭合。
- `OBSERVED`：在某一台车/某一版 iOS 的 sysdiagnose 中看到，不能推广。
- `OPEN-NB-*`：未证明；实现必须留出配置/失败分支，不得猜造。

## 0.5 不覆盖

- `0x4301` 的线格式与 TLV 校验：见 `iap2_control_session/spec/14`。
- AirPlay Pair/Verify/FairPlay/SETUP：见 `airplay_control_plane`、`airplay_fairplay_crypto`。
- 媒体/音频/视频/输入：见对应 docset。
- USB/有线 CarPlay。
- 真实车机互通认证；本 v0 没有端到端成功记录。
