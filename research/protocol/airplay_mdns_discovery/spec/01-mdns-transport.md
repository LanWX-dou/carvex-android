# 01 — mDNS 传输与宣告

> 对应覆盖项 1（传输与宣告）与覆盖项 3 的一半（浏览什么服务类型）。
> 源端口与缓存条文已于 2026-10-26 对照 RFC Editor 原文；固件静态证据与 RFC 通用要求分别标注。

## 1.1 端点

- **R-1.1**（MUST）客户端向 IPv4 `224.0.0.251:5353` 与（若启用）IPv6 `ff02::fb:5353` 发送查询。所有 mDNS 响应的 UDP 源端口必须为 5353，接收方静默忽略其它源端口的响应；非 5353 源端口可用于 legacy **查询**，不能与响应混淆。参考 `parse_datagram(..., source_port=...)` 提供此门；裸 `parse_message` 没有 UDP 元数据，不负责它。
  依据：`[RFC 6762 §3, §6]`；`A02.1`

- **R-1.2**（MUST）发送 multicast mDNS 查询/响应时 ID 与 OPCODE 都必须为 `0`；接收 multicast 响应时 ID 必须忽略，OPCODE 非 `0` 的报文必须忽略（实现可计数诊断，但不得继续解析其答案）。legacy unicast response 的 ID 按对应查询匹配。
  依据：`[RFC 6762 §18.1, §18.3]`；`A02.1`

- **R-1.3**（MUST）完整持续查询器从 UDP 5353 发送查询并监听组播目的端口 5353，按 QR 区分查询/响应；legacy 一次性查询器用非 5353 源端口并匹配单播响应。RFC 不要求必须是同一个操作系统 socket；IPv4/IPv6、多接口和平台 DNS-SD API 可采用不同实现。
  依据：`[RFC 6762 §6]`；`A02.1`

## 1.2 TTL 与记录生命周期

- **R-1.4**（MUST）缓存必须使用 RR 中实际宣告的 TTL 递减，过期后删除，不得无限保留。`120 s`（A/AAAA/SRV）与 `4500 s`（PTR/TXT）只能作为本项目样本/工程默认，不能当作 mDNS 通用固定值。
  依据：`[RFC 6762 §10]`；`A02.1`

- **R-1.5**（MUST）收到 TTL=0 的记录必须按 RFC 6762 §10.1 进入 goodbye 过期流程：将相同 RR 的缓存寿命压到约 1 s，并在到期后删除；不得把它当作长期有效的 TTL=0 记录。服务消失事件可以在收到 goodbye 时先行上报，但缓存实现不能因此破坏同网段其它 responder 的一秒救援窗口。
  依据：`[RFC 6762 §10.1]`；`A02.2`（参考实现 `goodbye-ttl0` 向量在 `snapshot_at=1s` 验证淘汰）

- **R-1.6**（MUST，完整缓存实现）cache-flush 按同名/TYPE/CLASS 的 RRset 处理：超过一秒未刷新且未被本次记录刷新者标为一秒后到期；最近一秒收到的记录保留，以支持多报文 RRset 与多网卡。不得按“同名立即全替换”实现。参考 ServiceGraph 仍是简化缓存，不满足完整 cache-flush；iOS 具体实现保持 `OPEN-MDNS-3`。
  依据：`A02.1`、`OPEN-MDNS-3`

## 1.3 查询与响应

- **R-1.7**（MAY）需要单播回应时，查询方应在 question 的 CLASS 最高位置 QU 位；响应方可以单播回复。
  依据：`[RFC 6762 §5.4]`；`A02.1`（`browse-query-qu` 向量）

- **R-1.8**（针对服务发布方的 SHOULD）若客户端还要发布自己的 mDNS 名称，发布方应按 RFC 做至少 3 次 Probe（间隔约 250 ms）和至少 2 次 Announce（间隔约 1 s）。仅作为发现方连接车机时，不应把这套发布节奏当成客户端必须执行的发现步骤；车机是否遵守未取证（`OPEN-MDNS-5`）。
  依据：`[RFC 6762 §8.1, §8.3]`、`OPEN-MDNS-5`

- **R-1.9**（MUST）接收方必须容忍未知 TYPE/TXT 键并把原始字节保留；不得因未知字段拒绝整条报文。
  依据：`A02.1`、`A02.2`、`OPEN-MDNS-6`

## 1.4 服务类型

- **R-1.10**（MUST）客户端至少应能浏览并解析 `_airplay._tcp`。24A446 的 `APTransport` 还包含 `_airplay-alt._tcp`、`_airplay-p2p._tcp`、`_raop._tcp`、`_sideplay._tcp` 四个字符串；它们是该构建的可配置 profile 观察值，不是所有 AirPlay 客户端都必须支持的全局清单。
  依据：`A01.1`、`A01.2`

- **R-1.11**（MUST）实现不得假设只有 `_airplay._tcp` 一种服务；也不得假设车机一定宣告 `_raop._tcp`。
  依据：`A01.1`、`OPEN-MDNS-8`

- **R-1.12**（MUST）客户端默认按 `_airplay._tcp.local.` 建浏览器：24A446 在 `_APBonjourBrowserCreate` 里以 `w21 & 1 == 0` 选中 `_airplay._tcp.` + `local.`，另一分支是 `_sideplay._tcp.`；实现应至少支持这两个分支，但服务类型必须可配置，不得写死成唯一来源。
  依据：`A01.5`

## 1.5 车机取值的边界

- **R-1.13**（MUST）以下内容在拿到真实抓包前一律 `OPEN`，实现只能“解析得到什么就报什么”，不得填默认值：车机宣告的服务类型集合、实例名、TTL、是否发 Goodbye、是否用 AWDL/NAN、是否响应 QU。
  依据：`A09.1`、`A09.3`、`OPEN-MDNS-7`、`OPEN-MDNS-8`

- **R-1.14**（MUST）实现不得假设“必须先做 mDNS 发现才能连 AirPlay”：iAP2 的 `0x4301` 可能直接给出 Wi-Fi 凭据与端口（见 `research/protocol/iap2_control_session`），两条路径的先后与依赖关系未取证。
  依据：`OPEN-MDNS-1`、`A09.3`

- **R-1.15**（MUST）assisted 路径必须支持**车机提供**的 service 类型/协议：`APAssistedModeBrowser` 用属性里的名字+协议在 `local.`、`awdl0` 上浏览，而不是写死 `_airplay._tcp`；实现不得只支持固定服务名。
  依据：`A01.9`、`OPEN-MDNS-1`
