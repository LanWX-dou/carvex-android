# runtime — 运行期材料

本目录只放**真实运行期证据**，不放合成数据。

| 子目录 | 内容 | 现状 |
|---|---|---|
| `captures/` | 真实抓包（`.pcap` + 同名 `.json` 元数据） | **空**：工作区没有任何 mDNS 抓包（`OPEN-MDNS-7`） |
| `replay/` | 回放工具：把抓包导出成 packets.json，喂参考实现，输出候选表 | 已有 `replay.py`，可用合成向量自测 |

## 规矩

- 抓包必须带 SHA256、接口、时区、车机型号/固件、手机型号/iOS；字段见 `captures/README.md`。
- 合成向量只在 `reference-impl/test_vectors.json`，**不得**复制进 `captures/` 冒充真实数据。
- 回放结果只是“解析器在这些字节上做了什么”，不等于“车机就是这样”。要下结论必须同时给抓包与解析输出。

## 拿到 pcap 后的最短路径

```bash
# 1) 导出每包的原始字节
tshark -r captures/xxx.pcap -Y "udp.port==5353" -T fields -e frame.number -e data.data > raw.tsv

# 2) 转成 packets.json（frame,hex 两列，制表符分隔）
python3 replay/replay.py --from-tsv raw.tsv --out captures/xxx.packets.json

# 3) 回放，得到候选表
python3 replay/replay.py --packets captures/xxx.packets.json

# 4) 与 analysis/A-conclusions.md 对照，逐条关闭 spec/08-open-items.md 里的 OPEN
```
