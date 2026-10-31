# 06 — 客户端实现指南

> 把前面各章拼成一条可执行的路径。伪代码是**建议实现**，不是 iOS 的行为描述；每条规则都能点回 `analysis/A-conclusions.md`。

## 6.1 前置条件

- **R-6.1**（MUST）客户端必须已经处在能收到车机 mDNS 的网络里：要么与车机同一 Wi-Fi（由 iAP2 的 `0x4301` 提供 SSID/密码/IP/端口，见 `research/protocol/iap2_control_session`），要么在同一有线/无线网段。发现的先后与依赖未取证（`OPEN-MDNS-1`）。
  依据：`OPEN-MDNS-1`、`A09.3`

- **R-6.2**（MUST）如果同时连着多个网络（Wi-Fi + 有线 + VPN），必须显式选择接口，不得依赖系统默认路由。
  依据：`A04.2`、`R-5.11`

## 6.2 主流程

```text
1. 选接口 iface
2. socket(AF_INET, SOCK_DGRAM, 0); bind(0.0.0.0:5353, SO_REUSEADDR)
   IP_ADD_MEMBERSHIP(224.0.0.251, iface)
   （可选）socket(AF_INET6); IPV6_JOIN_GROUP(ff02::fb, iface)
3. 发 PTR 查询：_airplay._tcp.local. PTR IN
4. recv 循环：每收一包 → parse_message → graph.add_message
5. 若某实例有 PTR 但缺 SRV/TXT：对 <instance> 发 SRV/TXT 查询（QU 可选）
6. 每秒生成候选快照：graph.candidates() → rank_candidates(cands, local_net)
7. 有 usable 候选 → 交上层；没有 → 继续等，按退避重发查询
8. 收到 TTL=0 → 从候选里移除；记录日志
```

- **R-6.3**（MUST）实现必须按“服务类型 → 实例 → 主机”分层建模，并能在缓存/附加区缺记录时发起后续查询；不能只发一次 PTR 就假定一定拿到了 SRV/TXT/A。DNS-SD 允许一个报文携带多个 question，也允许 additional 记录直接补全，因此不强制固定查询顺序或逐层各发一包。
  依据：`A02.1`、`[RFC 6763 §5]`

- **R-6.4**（SHOULD，工程策略）每一步应有可配置超时；`1 s` 起步、指数退避、上限 `60 s` 只是本参考实现的默认策略，不是车机或 mDNS 的协议常量。进程退出前必须能干净关闭 socket 并离开组播组。
  依据：`A02.1`

- **R-6.5**（MUST）接收循环必须容忍畸形报文：解析异常只丢该包并计数，不得终止整个发现过程。
  依据：`A02.2`、`bad-pointer`/`truncated-question` 向量

- **R-6.6**（MUST）每收到一条 PTR 都要能回答“这个实例的 SRV/TXT 从哪来”：来自同一条报文的 additional，还是后续补查。日志里要能区分。
  依据：`A02.1`、`A05.1`

## 6.3 数据结构（建议）

```python
@dataclass
class Candidate:
    service: str          # "_airplay._tcp.local."
    instance: str         # 全名，保留转义
    host: str | None      # SRV target
    port: int | None      # SRV port
    addresses: list[str]  # A/AAAA 原始字节转文本
    txt: dict[str, list[bytes]]
    ttl_hint: int | None
    usable: bool
    reasons: list[str]    # 排序与不可用原因
```

- **R-6.7**（MUST）`txt` 必须保留**原始字节**（同名多值用列表），不得只存 str；判断 `features` 时再按需转文本。
  依据：`A02.2`、`R-3.4`

- **R-6.8**（MUST）`instance` 必须存全名；`service` 单独存。不要用 `instance` 当唯一键跨服务类型复用。
  依据：`A02.1`、`R-2.5`、`R-2.9`

## 6.4 与 iAP2 的衔接

- **R-6.9**（SHOULD，路径建议）从 `0x4301` 拿到 SSID/密码后，客户端可以加入该 Wi-Fi 再开始浏览；如果 `0x4301` 同时给了 `wifiIP` 与端口，可按上层 profile 选择直接连接或继续发现。两条路径的先后与依赖未取证（`OPEN-MDNS-1`），不能写成强制顺序。
  依据：`OPEN-MDNS-1`、`A09.3`

- **R-6.10**（MUST NOT）不得把 `0x4301` 里的端口直接当成 AirPlay 端口写死；端口以 SRV 为准。
  依据：`R-5.4`、`OPEN-MDNS-9`

## 6.5 日志与可诊断性

- **R-6.11**（MUST）发现失败的日志必须包含：接口名、发出的查询、收到的报文条数与解析失败数、每个候选的 `reasons`、最后一次 goodbye 时间。
  依据：`A04.2`、`A05.1`

- **R-6.12**（SHOULD）支持把原始报文按 hex 落盘（`runtime/captures/` 格式），便于事后回放与补充证据。
  依据：`A09.1`、`R-6.5`

## 6.6 常见坑

| 坑 | 表现 | 对策 |
|---|---|---|
| 多网卡只加入默认接口 | 收不到车机组播 | `R-6.2` |
| Windows 防火墙/驱动过滤组播 | 发得出收不到 | 换 AP 侧抓包或 Linux |
| 把 PTR 名字当主机名 | 地址解析失败 | `R-5.1` |
| IPv6 link-local 不带 scope | 连接超时 | `R-5.5` |
| 只解析第一条 A | 车机换网段后连不上 | `R-5.2` |
| 用实例名当设备身份 | 同名不同设备互相覆盖 | `R-2.9` |
| 收到 goodbye 仍保留候选 | 连到已下线服务 | `R-1.5` |
