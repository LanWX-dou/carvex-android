# 08 — OPEN 清单（本阶段未取证的事实）

> 规则：每个 `OPEN` 都有编号、影响、关闭条件。`verify.py` C5 会强制：正文里出现的每个 `OPEN-MDNS-n` 必须在这里登记，且至少被一个覆盖项引用。
> 关闭条件达到后，把“状态”改成 `CLOSED` 并把结论移进 `analysis/A-conclusions.md`，不要只删编号。

| 编号 | 问题 | 影响 | 关闭条件 | 状态 |
|---|---|---|---|---|
| `OPEN-MDNS-1` | mDNS 发现与 iAP2 `0x4301` 给出的 Wi-Fi/端口之间，先后与依赖关系是什么 | 决定客户端要不要先做发现 | 一份同时含 iAP2 与 Wi-Fi 抓包的记录 | OPEN |
| `OPEN-MDNS-2` | 车机是否走基础设施 Wi-Fi、是否用 AWDL/NAN、是否响应 QU | 决定监听哪个接口、要不要 AWDL | 车机抓包 | OPEN |
| `OPEN-MDNS-3` | 截断（TC）、重传、cache-flush 淘汰、EDNS0 的实际形态 | 解析健壮性 | 抓包中出现对应报文 | OPEN |
| `OPEN-MDNS-4` | `_airplay._tcp.` 在 24A446 中的确切引用路径 | 决定“客户端是否必定浏览 `_airplay._tcp`” | **已关闭**：Ghidra 数据引用 `0x24fdce464`（`_APBonjourBrowserCreate`，默认分支） | CLOSED |
| `OPEN-MDNS-5` | 车机 Probe/Announce 的次数与间隔、TTL 实际取值、是否发 Goodbye | 缓存与重连策略 | 车机抓包 | OPEN |
| `OPEN-MDNS-6` | 车机报文中的未知 TYPE/RR（NSEC、OPT 等）及解析影响 | 兼容性 | 车机抓包 | OPEN |
| `OPEN-MDNS-7` | 没有真实车机 mDNS pcap（完成判据 2 未满足） | 所有“车机取值”结论 | 归档一份带 SHA256 的 pcap | OPEN |
| `OPEN-MDNS-8` | 车机宣告的服务类型集合与实例名格式 | 浏览与展示 | 抓包 | OPEN |
| `OPEN-MDNS-9` | SRV 端口是否固定、target 是否 `.local`、是否多 SRV | 连接目标 | 抓包 | OPEN |
| `OPEN-MDNS-10` | 车机 TXT 键集合与取值 | 能力判断 | 抓包 | OPEN |
| `OPEN-MDNS-11` | `features` **剩余位**的语义（`0x37`/`0x38` 之外）；索引 55/56 已定位为 extended 半第 23/24 位（`A02.7`），语义仍未知 | 能力判断 | 行为验证或 Apple 文档 | OPEN |
| `OPEN-MDNS-12` | IPv6 是否可用、link-local scope 怎么给 | 地址选择 | 抓包 + 实连 | OPEN |
| `OPEN-MDNS-13` | `pk`/`pi`/`gid` 能否作为身份或配对依据 | 安全边界 | 配对阶段 + 固件证据 | OPEN |
| `OPEN-MDNS-14` | `features` 文本语法 —— **已关闭**：`A02.6` 证明只有 `0x%X` 与 `0x%X,0x%X`（低,高）两种形态，大写十六进制 | 解析 | 已由 `0x24fd940a0` 逐指令确认 | CLOSED |
| `OPEN-MDNS-15` | `fex` 的**内部结构**与“是否完全替代 `features`”；已确认 `fex` 是字符串且与 `features` 独立（`A02.8`） | 能力判断 | 抓包 + 代码 | OPEN |
| `OPEN-MDNS-16` | 多条地址之间的优先级与失败回退顺序（iOS 与车机两侧） | 连接成功率与重试策略 | 抓包 + 实连行为 | OPEN |
| `OPEN-MDNS-17` | 车机实例名的实际形态（空格/中文/随机后缀、是否出现转义） | 展示、匹配与去重 | 抓包 | OPEN |
| `OPEN-MDNS-18` | 不同 iOS 版本 / 车机固件在服务类型、TXT 键、`features` 位上的差异 | 兼容性与版本分支 | 第二个构建或第二台车机 | OPEN |
| `OPEN-MDNS-19` | 网络切换、休眠代理、多接口切换时车机的实际宣告行为 | 缓存清理与重连 | 抓包（含切网场景） | OPEN |
| `OPEN-MDNS-20` | 同名冲突、地址冲突、伪造宣告是否出现 | 防冒充与缓存投毒 | 抓包 + 对抗实验 | OPEN |
| `OPEN-MDNS-21` | 车机休眠/唤醒后的重新宣告节奏与 TTL 刷新方式 | 重连等待策略 | 抓包（休眠/唤醒场景） | OPEN |

## 统计

- 共 21 条：19 条 `OPEN`，2 条 `CLOSED`（`OPEN-MDNS-4` 服务类型默认值、`OPEN-MDNS-14` features 文本语法）。
- 没有真实抓包（`OPEN-MDNS-7`）是其中 10 条的共同前置。
