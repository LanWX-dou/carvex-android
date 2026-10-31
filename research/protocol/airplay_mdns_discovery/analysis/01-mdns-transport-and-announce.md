# 01 — mDNS 传输与宣告

> 本章回答任务书覆盖项 1 的前半：**报文发到哪、用什么端口、TTL 与缓存刷新位怎么用、Probe/Announce/Goodbye 的节奏**。
> 后半（“车机实际怎么发”）没有抓包，全部落 `OPEN-MDNS-2`。

## 1.1 端点与传输

| 项 | 值 | 证据 |
|---|---|---|
| IPv4 组播地址 | `224.0.0.251` | `[RFC 6762]`（离线引用，见 `00` §0.5） |
| IPv6 组播地址 | `ff02::fb` | `[RFC 6762]` |
| UDP 端口 | `5353` | `[RFC 6762]` |
| 传输层 | UDP，单播查询用 QU 位请求 | `[RFC 6762]` |
| 报文 ID | 查询与响应都用 `0`（mDNS 不使用事务 ID） | `[RFC 6762]`；参考实现按此解析 |

**OPEN-MDNS-2**：车机是否只发组播、是否接受单播查询、是否走 AWDL/NAN 而非基础设施 Wi-Fi，本阶段无证据。iOS 侧确实存在 AWDL/NAN 变体（`A01.3` 的模式名里就有 `AirPlayAWDLPartial`、`AirPlayOpenNAN`），但**这些模式何时启用**没有证据。

## 1.2 TTL 与缓存

| 记录 | 样本/工程默认 | 说明 | 证据 |
|---|---|---|---|
| 含主机名的记录（A/AAAA，以及 rdata 内嵌主机名的 SRV） | 120 s（示例默认） | 实现必须以报文实际 TTL 为准 | `[RFC 6762 §10]` |
| 其他记录（PTR/TXT 等） | 4500 s（示例默认） | 实现必须以报文实际 TTL 为准 | `[RFC 6762 §10]` |
| Goodbye | `TTL=0` | 撤销记录；接收方应把该 RR 的缓存寿命压到约 1 s，再删除 | `[RFC 6762 §10.1]`；参考实现 `ServiceGraph._add_rr` 进入宽限窗口并记日志 |

**实现要求**：接收方必须能处理“同一记录被 TTL=0 撤销”，在约 1 s 宽限后删除该 RR；事件层可以提前上报撤销，但不能把其它 responder 的救援窗口立即抹掉。参考实现的 `goodbye-ttl0` 向量覆盖这条。

## 1.3 cache-flush 位与 QU 位

| 位 | 位置 | 语义 | 本阶段处理 |
|---|---|---|---|
| cache-flush | RR 的 CLASS 最高位（`0x8000`） | 同一名字/类型/类的旧 RRset 进入一秒淘汰窗口 | 解析时保留为 `cache_flush` 字段；参考实现只保留标志，完整 RRset 淘汰仍是 `OPEN-MDNS-3` |
| QU（unicast-response） | question 的 CLASS 最高位 | 请求对方单播回应 | 解析为 `unicast_response`；`browse-query-qu` 向量覆盖 |
| 截断 TC | DNS 头 bit 9 | 报文被截断 | 解析为 `tc`；重传/分片处理 `OPEN-MDNS-3` |

## 1.4 Probe / Announce / Goodbye 的节奏

若本端要发布名字，按 `[RFC 6762 §8]` 先做冲突检测（Probe），至少 3 次、间隔约 250 ms；宣告（Announce）至少 2 次、间隔约 1 s；冲突时改名重来；撤销用 TTL=0 的 goodbye。发现方只需接收/解析这些行为，不承担发布方节奏。

**本阶段不能证明车机遵守这些节奏**：没有任何抓包。`analysis/09` 给了抓包 SOP，抓到后用 `runtime/replay` 的脚本可以直接统计间隔。

## 1.5 24A446 静态证据：谁在浏览、浏览什么

`APTransport` 是 AirPlay 传输层，内含 Bonjour 浏览器（`APBonjourBrowser`）。它不是 mDNS 协议栈本身——真正的收发在系统 `mDNSResponder`，**该二进制不在本次提取集合里**，所以“Probe/Announce 由谁发”在本阶段无法从代码回答（`OPEN-MDNS-2`）。

能在本镜像里确认的是**服务类型清单**与**浏览模式**：

| 字符串 | 地址 | 说明 |
|---|---|---|
| `_airplay._tcp.` | `0x24fe5019f` | AirPlay 主服务 |
| `_airplay-alt._tcp.` | `0x24fe507e1` | 备用 AirPlay 服务 |
| `_airplay-p2p._tcp.` | `0x24fe508a9` | 点对点（AWDL/NAN 路径） |
| `_raop._tcp.` | `0x24fe507fd` | RAOP（AirPlay 1 音频） |
| `_sideplay._tcp.` | `0x24fe50168` | SidePlay |

引用点（`_APBonjourBrowserSetModeInternal`，`0x24fd900f0`–`0x24fd908ac`）：

| 指令地址 | 引用的服务类型 |
|---|---|
| `0x24fd90434` | `_airplay-alt._tcp.` |
| `0x24fd9049c`、`0x24fd906f0` | `_airplay-p2p._tcp.` |
| `0x24fd9054c`、`0x24fd9056c` | `_raop._tcp.` |

同一函数还用模式名区分“通用/本地”浏览，见 `A01.3`。

`_airplay._tcp.` 的引用点由 Ghidra 数据引用补上了：`_APBonjourBrowserCreate` 在 `0x24fdce420`–`0x24fdce478` 按一个布尔位选服务类型：

| 条件 | 服务类型 | 后缀 | 模式名 |
|---|---|---|---|
| `w21 & 1 == 0`（默认） | `_airplay._tcp.` `0x24fe5019f` | `local.` `0x24fe49e7f` | `APBonjourBrowserBonjourGeneralAirPlay` `0x24fe501ae` |
| `w21 & 1 != 0` | `_sideplay._tcp.` `0x24fe50168` | `local.` | `APBonjourBrowserBonjourGeneralSidePlay` `0x24fe50178` |

指令形态是 `tst w21,#1` + 两条 `csel`，随后 `stp x9, x11` 把（服务类型，`local.`）存进浏览器对象、`str x10` 存一个 `0x0800000000000000`（仅 SidePlay 分支非零）。因此 **24A446 默认按 `_airplay._tcp.local.` 建浏览器**，`_sideplay._tcp.` 是另一分支，不是“猜测”。
`OPEN-MDNS-4` 据此关闭；仍不能证明的是**车机是否真的宣告该服务**（`OPEN-MDNS-8`）。

### 1.5.1 反向服务：`_carplay-ctrl._tcp`

`APTransport` 里还有一条**手机侧自己发布**的服务类型：

| 项 | 值 |
|---|---|
| 字符串 | `_carplay-ctrl._tcp`（注意没有尾点）`0x24fe6c193` |
| 引用点 | `_APCarPlayControlServerAddInterface` `0x24fe01f6c`；`____APCarPlayControlServerControl_block_invoke_2` `0x24fe02714`；`.cold.1` `0x24fe38ce0`；`_OUTLINED_FUNCTION_4` `0x24fd91e14` |

含义（`A01.7`，`INFERRED`）：手机侧存在 **CarPlay 控制服务**，并把该服务类型与某个接口绑定；从函数名（`AddInterface`/`Control`）和 block 结构看，它很可能是通过 mDNS 注册/应答，但“真的调用了 `DNSServiceRegister`”没有指令级证据（导入符号被 chained fixups 隐藏）。

对客户端实现的含义：**发现不是单向的**。设备侧模拟 iPhone 时，除了“浏览车机的 AirPlay”，可能还要“应答车机对自己的 `_carplay-ctrl._tcp` 查询”。本阶段只把这条记为边界提示，不展开实现（`OPEN-MDNS-8`）。

### 1.5.2 assisted 模式：动态 service + `awdl0`

`-[APAssistedModeBrowser startBonjourBrowser]`（`0x24fdfde98`–`0x24fdfdf64`，204 B，51 条指令）：

| 步骤 | 指令/地址 | 含义 |
|---|---|---|
| 取服务名 | `0x24fdfdef0` 调 `0x2500858a0` | `_bonjourServiceName` 属性 |
| 取协议 | `0x24fdfdf00` 调 `0x250001110` | `_bonjourProtocol` 转 C 串 |
| 域 | `0x24fdfdf08` `"local."` `0x24fe49e7f` | 固定 `local.` |
| 接口 | `0x24fdfdf10` `"awdl0"` `0x24fe48357` | 固定 `awdl0` |
| flags | `0x24fdfdf1c`/`0x24fdfdf20` | `x4 = 0x0408_0000_0000_0000`（低 32 位为 0；ABI 含义未知） |
| 创建 | `0x24fdfdf24` 调 `0x2500ee8a0` | 返回浏览器引用 |

类里另有 `getExpectedBonjourService`（`0x24fdfe744`，把两个属性经 `0x250001ff0` 拼成期望 service；格式串 `0x275fa7900` 未能解码）、`startTimerWithTimeout:`（`0x24fdfe1d0`）与 `stopBrowsingWithError:`（`0x24fdfe408`）。

要点（`A01.9`，代码级 `CONFIRMED`）：assisted 模式的 service 类型来自**属性**（车机在 `assistedInfo` 里给的名字/协议），不是写死 `_airplay._tcp`；接口固定 `awdl0`、域 `local.`，并带超时。它与主浏览路径（§1.5 的 `_airplay._tcp.` + `local.`）是两条不同的入口；“先 0x4301 再走哪条”仍是 `OPEN-MDNS-1`。

## 1.6 服务图的形状

```text
PTR  _airplay._tcp.local.           → <instance>. _airplay._tcp.local.
SRV  <instance>._airplay._tcp.local. → <host>.local. : <port>
TXT  <instance>._airplay._tcp.local. → key=value ...
A    <host>.local.                  → IPv4
AAAA <host>.local.                  → IPv6
```

- PTR 的 TTL 是“服务存在性”，SRV/TXT 的 TTL 是“实例详情”，A/AAAA 的 TTL 是“主机地址”；三者可以独立过期（`[RFC 6763 §5.2]`）。参考实现按 (service, instance) 聚合，SRV/TXT/A 分别可缺——缺 SRV 时无法得到端口，缺 A/AAAA 时无法得到地址，二者都直接决定候选是否 `usable`。
- 实例名是 DNS-SD 的“服务实例名”，允许空格与 UTF-8；线上仍是长度前缀的 wire label。展示/配置字符串可按 DNS-SD 约定把标签内的 `.` 写成 `\.`（`[RFC 6763 §4.1.1]`），不能把该文本形式当作线上编码。

## 1.7 本章未解决

| 编号 | 问题 |
|---|---|
| `OPEN-MDNS-2` | 车机是否走基础设施 Wi-Fi、是否用 AWDL/NAN、是否响应 QU |
| `OPEN-MDNS-3` | 截断/重传、cache-flush 淘汰策略、EDNS0 是否出现 |
| `OPEN-MDNS-5` | 车机的 Probe/Announce 次数与间隔（无抓包） |
