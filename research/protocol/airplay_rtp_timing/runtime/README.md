# runtime —— 运行期素材

> 本目录存放"能跑起来"的素材：抓包、回放、可重复实验。规范本身在 `spec/`。

| 子目录 | 内容 | 现状 |
|---|---|---|
| `captures/` | 真实媒体抓包与索引（`captures/README.md` 是配方，`captures/INDEX.md` 是登记表） | **空**：本仓库没有 RTP/RTCP 抓包（`OPEN-RUN-1`） |
| `replay/` | 把抓包喂给 `reference-impl/rtp_parser.py` 的回放脚本 | 待抓包到位后编写 |

## 为什么这里是空的

前三个阶段（蓝牙 RFCOMM、iAP2 链路、iAP2 控制会话）的证据都来自**固件字节 + 23G90 蓝牙链路转录**；媒体面走 Wi-Fi/以太网，现有 sysdiagnose 里没有任何 `pcap`。这一点在 `analysis/00` §0.7 与 `analysis/A-conclusions.md` 的 `A00.3` 有记录。

## 补齐顺序

1. 按 `captures/README.md` 抓一份包；
2. 填 `captures/INDEX.md`；
3. 写 `replay/replay.py`（读 pcap → 按 `spec/01` 解析 → 输出统计）；
4. 关闭 `OPEN-RUN-1` 与相应 `OPEN-RTP-*`，同步更新 `spec/08-open-items.md`、`manifest.json`。
