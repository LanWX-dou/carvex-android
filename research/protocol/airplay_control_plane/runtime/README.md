# runtime · 运行期材料

本目录只放**原始观测**，不放结论。

## 现有

| 文件 | 来源 | 覆盖 |
|---|---|---|
| （无） | — | 本阶段没有 24A446 的 AirPlay 控制面抓包 |

23G90 的蓝牙 iAP2 抓包不属于本目录（它属于 `iap2_control_session/runtime/`，且不含任何 RTSP 报文，见 `analysis/10-runtime-captures.md`）。

## 采集要求（下一轮）

1. 在 `GET /info` 之前开始抓，覆盖到 `RECORD`；
2. 至少两份：首次配对（含 `/pair-setup`）与二次连接（只有 `/pair-verify`）；
3. 记录时间戳、源/目的、TCP 流编号，保存为 pcapng 并附 sha256 与采集拓扑说明。
