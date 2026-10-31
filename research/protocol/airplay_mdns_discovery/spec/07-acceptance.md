# 07 — 验收清单

> 对应任务书 §9。分三级：**L0 单机可验**、**L1 同网段可验**、**L2 真车必需**。
> 当前阶段 L0 全部通过，L1 可用合成发包机验证，**L2 因无 pcap/无实车全部未做**。

## 7.1 L0 — 单机（现在就能过）

| # | 检查 | 方法 | 判据 | 状态 |
|---|---|---|---|---|
| L0-1 | 参考实现能解析全部向量 | `python3 reference-impl/mdns_discovery.py --vectors ...` | `0 failures` | ✅ 通过 |
| L0-2 | 文档自校验 | `python3 verify.py` | `failures: 0` | ✅ 通过 |
| L0-3 | 畸形报文不崩 | `bad-pointer`、`truncated-question` 向量 | 抛 `DnsError` 且进程正常退出 | ✅ 通过 |
| L0-4 | TXT 边界 | `duplicate-key`、`unknown-key-binary` | 重复键保留、非 UTF-8 保留 | ✅ 通过 |
| L0-5 | goodbye 处理 | `goodbye-ttl0` | 实例从服务图移除 | ✅ 通过 |
| L0-6 | 不可用候选 | `multi-instance-one-unresolvable` | 缺地址的实例 `usable=false`，不参与排序 | ✅ 通过 |
| L0-7 | 字节级可复核 | `manifest.json` | 每个文件的 SHA256 与磁盘一致 | ✅ 通过 |

## 7.2 L1 — 同网段（需要一台发包机）

用一台机器（Linux/树莓派）脚本化发出合成 mDNS 响应，被测客户端跑在另一台机器上：

| # | 检查 | 方法 | 判据 | 状态 |
|---|---|---|---|---|
| L1-1 | 能发现合成服务 | 发包机宣告 `Test._airplay._tcp.local.` | 客户端 5 s 内列出该实例 | 未做 |
| L1-2 | SRV/TXT 补查 | 首包只发 PTR | 客户端发起 SRV/TXT 查询并补全 | 未做 |
| L1-3 | TTL=0 撤销 | 发 goodbye | 候选在 1 s 内消失 | 未做 |
| L1-4 | 多地址排序 | 同时发 A 与 AAAA | 顺序符合 `R-5.6` 且 `reasons` 可读 | 未做 |
| L1-5 | 接口选择 | 多网卡环境 | 只从选定接口收包 | 未做 |
| L1-6 | 畸形包鲁棒 | 混发截断/坏指针包 | 不崩、计数正确 | 未做 |

## 7.3 L2 — 真车（缺 pcap，全部阻塞）

| # | 检查 | 方法 | 判据 | 状态 |
|---|---|---|---|---|
| L2-1 | 真实服务图 | 车机开机后抓 60 s | 能回放出 `PTR → SRV → TXT → A/AAAA` | **阻塞**：无抓包（`OPEN-MDNS-7`） |
| L2-2 | 车机服务类型 | 看抓包 | 实际宣告集合与 `R-2.2` 对照 | **阻塞** |
| L2-3 | 实例名形态 | 看抓包 | 与 `R-2.6`/`R-2.8` 对照 | **阻塞**（`OPEN-MDNS-17`） |
| L2-4 | 端口与 target | 看抓包 | 与 `R-5.4` 对照 | **阻塞**（`OPEN-MDNS-9`） |
| L2-5 | TXT 取值 | 看抓包 | 与 `R-3.7`/`R-3.13` 对照 | **阻塞**（`OPEN-MDNS-10`） |
| L2-6 | `features` 位 | 抓包 + 行为 | 与 `R-4.2` 对照，语义仍 OPEN | **阻塞**（`OPEN-MDNS-11`） |
| L2-7 | TTL/Probe/Announce | 看抓包时序 | 与 `R-1.4`/`R-1.8` 对照 | **阻塞**（`OPEN-MDNS-5`） |
| L2-8 | IPv6 | 抓包 + 实连 | 与 `R-5.5` 对照 | **阻塞**（`OPEN-MDNS-12`） |

## 7.4 验收流程

1. 跑 L0：`python3 verify.py` + 向量，`failures: 0`。
2. 跑 L1：发包机脚本 + 被测客户端，逐条记录。
3. 拿到 pcap 后跑 L2：用 `analysis/09` §9.5 的方式导出 hex，喂 `mdns_discovery.py --hex`，把结果与 `A-conclusions` 对照；把每个 `OPEN` 改成结论并更新 `coverage.json`。
4. 任何一条 L2 未过，`STATUS.md` 必须保持 `PARTIAL`，不得写“已验收”。

## 7.5 验收记录模板

```json
{
  "level": "L1",
  "date": "2026-xx-xx",
  "client": "本仓库 reference-impl 嵌入版 / 自研客户端",
  "iface": "wlan0",
  "cases": [{"id": "L1-1", "result": "pass", "note": "5s 内发现 Test 实例"}],
  "failures": 0
}
```
