# runtime/replay —— 回放

> 现状：**未编写**。等待 `../captures/` 出现至少一份合格抓包。

计划中的 `replay.py`：

```text
输入: ../captures/*.pcap
处理: 过滤 UDP → 按 spec/01 解析固定头与元素区（复用 reference-impl/rtp_parser.py）
输出:
  * 每个流的 PT / 序列号连续性 / 时间戳步进
  * 元素个数分布、1 字节元素出现比例（验证 spec/01 R-1.16）
  * 包长分布（验证 R-1.5 的 1480 上限）
  * 与 spec/01 R-1.12 向量不一致的包（应为 0）
```

在没有抓包之前写这个脚本只会产生"假验证"，因此本目录保持空。

相关未决项：`OPEN-RUN-1`（无抓包）、`OPEN-RTP-1`（元素区与固定头的先后）、`OPEN-RTP-4`（第二套PT掩码语义）。
