# airplay_mdns_discovery

AirPlay 的 **mDNS / DNS-SD 发现阶段**文档集：从“车机在 Wi-Fi 上宣告了什么”到“解析出可连接的地址/端口/能力”。

- 任务书：[`TASK.md`](TASK.md)（原样复制 `research/protocol/airplay_mdns_discovery.md`）
- 状态口径：[`STATUS.md`](STATUS.md) — **当前 PARTIAL：没有真实车机 pcap**
- 自校验：`python3 verify.py`

## 读什么

| 想知道 | 去读 |
|---|---|
| 证据怎么取的、边界在哪 | [`analysis/00-method-and-environment.md`](analysis/00-method-and-environment.md) |
| 报文发到哪、TTL/Probe/Announce | [`analysis/01`](analysis/01-mdns-transport-and-announce.md) + [`spec/01`](spec/01-mdns-transport.md) |
| DNS 报文怎么拆 | [`analysis/02-dns-message-format.md`](analysis/02-dns-message-format.md) |
| TXT 键、`features` 位 | [`analysis/03`](analysis/03-txt-and-features.md) + [`spec/03`](spec/03-txt-schema.md) + [`spec/04`](spec/04-features-bits.md) |
| 地址从哪来、候选怎么排 | [`analysis/04`](analysis/04-address-and-event-model.md) + [`spec/05`](spec/05-address-selection.md) |
| 动手写客户端 | [`spec/06`](spec/06-client-guide.md) |
| 怎么验收 | [`spec/07`](spec/07-acceptance.md) |
| 为什么没有抓包、怎么补 | [`analysis/09-runtime-captures.md`](analysis/09-runtime-captures.md) |
| 哪些 OPEN 能只靠固件补 | [`analysis/06-open-items-feasibility.md`](analysis/06-open-items-feasibility.md) |
| 还有哪些没证明 | [`spec/08-open-items.md`](spec/08-open-items.md) |

## 参考实现

纯标准库、不联网、不开套接字：

```bash
# 跑测试向量（10 条合成报文）
python3 reference-impl/mdns_discovery.py --vectors reference-impl/test_vectors.json

# 解一条报文
python3 reference-impl/mdns_discovery.py --hex "0000840000000001..."

# 重新生成向量（改 gen_vectors.py 后）
python3 reference-impl/gen_vectors.py
```

模块提供 `parse_message` / `ServiceGraph` / `rank_candidates`，可以直接嵌进客户端原型；它**只**回答“报文是什么、候选怎么排”，不做连接与配对。

## 校验

```bash
python3 verify.py            # 8 类检查
python3 verify.py --update   # 改了文件后重写 manifest.json
```

## 覆盖项 → 章节（12 项）

| # | 覆盖项 | 主要章节 | 状态 |
|---|---|---|---|
| 1 | mDNS 传输与宣告 | [spec/01](spec/01-mdns-transport.md)、[analysis/01](analysis/01-mdns-transport-and-announce.md) | 部分确认 |
| 2 | DNS 报文格式 | [analysis/02](analysis/02-dns-message-format.md) | 已确认 |
| 3 | 服务类型与浏览 | [spec/02](spec/02-browse-and-instance-names.md)、[analysis/01 §1.5.1](analysis/01-mdns-transport-and-announce.md) | 部分确认 |
| 4 | SRV 解析 | [spec/05](spec/05-address-selection.md)、参考实现 | 部分确认 |
| 5 | TXT 编码 | [spec/03](spec/03-txt-schema.md) | 已确认 |
| 6 | AirPlay TXT 字段 | [analysis/03](analysis/03-txt-and-features.md)、[spec/03](spec/03-txt-schema.md)、[字段表](reference-impl/metadata/txt-keys.json) | 部分确认 |
| 7 | 设备能力位 | [spec/04](spec/04-features-bits.md)、[位表](reference-impl/metadata/features-bits.json) | 部分确认 |
| 8 | 地址解析 | [analysis/04](analysis/04-address-and-event-model.md)、[spec/05](spec/05-address-selection.md) | 部分确认 |
| 9 | 服务选择 | [spec/05](spec/05-address-selection.md) | 部分确认 |
| 10 | 缓存与生命周期 | [spec/10](spec/10-cache-and-security.md) | 部分确认 |
| 11 | 安全边界 | [spec/10](spec/10-cache-and-security.md)、[spec/00](spec/00-scope-and-terms.md) | 部分确认 |
| 12 | 版本与差异 | [spec/09](spec/09-version-differences.md) | OPEN（`OPEN-MDNS-18`） |

## 硬边界

- 发现成功 ≠ AirPlay 可连接 ≠ CarPlay 可用（`spec/00` `R-0.1`）。
- TXT 的 `pk`/`pi`/`gid` 未被证明可用于身份校验，不得当信任锚（`R-0.5`、`R-3.9`）。
- 车机实际宣告内容在本阶段全部 `OPEN`，因为没有 pcap。
