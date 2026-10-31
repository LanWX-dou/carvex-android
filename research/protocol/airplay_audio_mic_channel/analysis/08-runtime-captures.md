# 08 运行期素材

## 8.1 现状：没有音频抓包

| 素材 | 是否存在 | 内容 | 能否作为音频证据 |
|---|---|---|---|
| `research/protocol/iap2_control_session/runtime/23G90-bt-classic-2026-10-16.md` | 有 | 蓝牙经典 RFCOMM 上的 iAP2 会话（识别/认证/CarPlay 启动前） | **不能**：没有 Wi-Fi、没有 RTP |
| 24A446 运行日志 `accessoryd-packets-*.ips` | 有 | iAP2 层 | 不能 |
| sysdiagnose `23G90` / `21G93` | 有 | 系统摘要、logarchive、WiFi 诊断 | 不能：没有 RTP 记录 |
| AirPlay 音频 pcap | **没有** | — | — |

所以本阶段的「播放/麦克风」结论全部来自静态字节，**没有任何一条来自运行期**。
这也是为什么覆盖表里「媒体播放/麦克风上行/同步」只能是 `部分确认` 或 `OPEN`。

## 8.2 为什么 23G90 抓包帮不上

那份抓包是 BT Classic 上的 iAP2：消息是 `0x1D00/0xAA0x/0x4301` 这类 iAP2 消息，
帧头 `40 40`，走 RFCOMM。AirPlay 音频走的是 Wi-Fi 上的 RTP（PT 96..109），
两套封装、两套传输，无法互推。`0x4301` 之后车机才开始建 AirPlay 连接，
音频包必然出现在**别的**接口上。

## 8.3 要抓什么（下一次运行期）

按优先级：

1. **一条媒体音单流**：设备播一段有标志性的音频（例如 440 Hz 正弦 + 语音报数），
   抓 10 秒，记录 `SETUP` 请求/回复、包数、PT 分布。
2. **麦克风上行**：车机侧说话，同时抓设备侧收包，确认 `dataPort`、包速率、PT。
3. **RED 触发**：人为丢包（tc/netem 或 AP 侧），看是否切到 `mred`/`gred`，冗余深度。
4. **teardown**：正常停流 + 直接断链各一次，对比是否发 `tdwn`。
5. **多路同时**：导航提示音 + 媒体音，看是否第二条流或混音。

每条抓包至少要能回答：时间、接口、五元组、`SETUP` 的 streams 全文、每包 `len/pt/seq/ts/ssrc`、
尾部 24 字节是否像 tag+nonce。

## 8.4 怎么抓

设备是发送端，车机是接收端，所以抓点在两者之间：

- 手机与车机同连一个可控 AP，在 AP/网桥上 `tcpdump -i br0 -s0 -w aud.pcap 'udp and (portrange 6000-7000 or host <车机IP>)'`；
- 或在车机侧抓（若车机有调试口）；
- 或让车机连一个 Linux AirPlay 接收端做替身，先拿到「设备发什么」，再回到真车机复验。

抓完必须把 pcap 的 sha256、抓取时间、车型/固件、触发动作写进 `runtime/captures/`，
并把解析结果落到 `runtime/replay/`。

## 8.5 抓包能闭合哪些 OPEN

| 抓包 | 可闭合 |
|---|---|
| 媒体音单流 | `OPEN-CODEC-1`、`OPEN-CODEC-2`、`OPEN-PORT-1` |
| 麦克风上行 | `OPEN-MIC-1`、`OPEN-MIC-3` |
| 人为丢包 | `OPEN-RED-1`、`OPEN-RED-2` |
| teardown | `OPEN-TEAR-1` |
| 多路同时 | `OPEN-AUD-1`、`OPEN-PLAY-2` |

## 8.6 登记

`OPEN-RUNTIME-1`：24A446 / 目标车机的 AirPlay 音频抓包缺失。它阻塞的是「通道完全正确」的
结论，不阻塞按本文件实现的骨架代码——但**不允许**在没有抓包时把任何一条写成 `CONFIRMED`
运行期事实。
