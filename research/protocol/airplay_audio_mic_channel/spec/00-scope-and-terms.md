# 00 范围与术语

本章定义本规格使用的术语、方向约定与证据分级。所有条款编号 `R-<章>.<序>` 在本文档集内唯一。

#### R-0.1 方向与角色命名
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`research/protocol/iap2_control_session/spec/09-device-side-startup.md` §8.1、`A01.4`

本规格站在**设备侧**（模拟 iPhone 的客户端）描述：

- **设备 / 发送端**：本客户端。AirPlay 意义上的 sender。
- **车机 / 接收端**：AirPlay 意义上的 receiver。

媒体音（设备 → 车机）是「上行」在 AirPlay 语义里叫 output；麦克风（车机 → 设备）叫 input。
文档里统一写「方向」而不是「上下行」，避免与 iAP2 的 inbound/outbound 混淆。

#### R-0.2 证据分级的使用方式
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`analysis/00-method-and-environment.md` §0.2

每条条款必须带 `证据：` 标记：

| 标记 | 实现者应如何对待 |
|---|---|
| `CONFIRMED` | 可按条款直接实现；仍须用本机抓包复验 |
| `INFERRED` | 可按条款实现，但必须在代码里留「可切换」开关，并在日志里标记来源 |
| `OPEN` | 不得实现为固定行为；走配置/探测，或直接不做 |

凡条款正文与 `analysis/A-conclusions.md` 冲突，以 A 表为准并提 issue。

#### R-0.3 本规格覆盖的边界
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`research/protocol/airplay_audio_mic_channel.md` §7

本规格覆盖：流类型与方向、SETUP 音频字段、载荷结构、RED、记录加密、播放缓冲与就绪门、
麦克风上行、TEARDOWN。

不覆盖：视频、FairPlay 算法本身、RTP 头字段语义/抖动缓冲/时钟同步（`airplay_rtp_timing`）、
AirPlay 控制面（`airplay_control_plane`）、iAP2 隧道分片（`iap2_airplay_tunnel`）。
遇到这些内容，只写「转介」并给出目标文档，不在这里下结论。

#### R-0.4 不得把静态推断写成运行期事实
级别：MUST NOT ｜ 证据：CONFIRMED ｜ 依据：`A08.1`、`A08.2`

本阶段**没有任何 AirPlay 音频抓包**。因此：

- 不得在任何文档里写「实测某车机会发送 X」；
- 不得把 `INFERRED` 的条款描述为「已验证」；
- 验收报告必须写明本次验证用的是**合成向量**还是**真实抓包**。

#### R-0.5 与 iAP2 文档集的关系
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`research/protocol/iap2_control_session/spec/09-device-side-startup.md`

音频通道的前提是：iAP2 会话已建立、认证完成、`0x4301`（CarPlay 启动）成功、车机侧 AirPlay
接收端可达。本规格从「AirPlay SETUP 已能发」开始写，不重复 iAP2 的连接步骤。
`0x4301` 的参数映射仍是 `OPEN-SES-2`，属控制会话文档集的范围。
