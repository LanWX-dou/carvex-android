# captures — 真实车机 mDNS 抓包

**当前为空。** 没有 pcap 时，`STATUS.md` 保持 `PARTIAL`，`spec/08-open-items.md` 里 7 条结论继续 `OPEN`。

## 文件命名

```text
<yyyy-mm-dd>-<capture-point>-<head-unit-slug>.pcap
<yyyy-mm-dd>-<capture-point>-<head-unit-slug>.json
```

例：`2026-11-02-laptop-byd-dilink5.pcap` + 同名 `.json`。

## 元数据必填字段

```json
{
  "file": "2026-11-02-laptop-byd-dilink5.pcap",
  "sha256": "…",
  "interface": "wlan0",
  "channel": "6",
  "captured_at": "2026-11-02T10:00:00+08:00",
  "capture_point": "笔记本 / AP / 车机",
  "head_unit": "BYD DiLink 5.0 / 固件 …",
  "phone": "iPhone18,1 / iOS 27.0.1 (24A446)",
  "scenarios": ["cold-boot", "join", "browse", "goodbye"],
  "notes": "是否同时连蓝牙、是否开着 CarPlay"
}
```

`verify.py` 的 C9 会检查：`captures/` 里每个 `.pcap` 都有同名 `.json`、SHA256 与文件一致、必填字段齐全、`scenarios` 非空；并且有同名 `.packets.json`（用 `replay.py --from-tsv` 导出）能回放出至少一条候选。缺 pcap 时 C9 通过但会打印“captures: 0（符合预期：OPEN-MDNS-7）”。

## 最低要求（任务书完成判据 2）

一份抓包至少要能回放出 **PTR → SRV → TXT → A/AAAA** 四条记录；只有 PTR 的抓包不足以关闭 `OPEN-MDNS-8/9/10`。
