# 01 音频流

#### R-1.1 SETUP 的 type 与包内 PT 是两套编号
级别：MUST NOT ｜ 证据：CONFIRMED ｜ 依据：`A01.1`、`A01.5`、`0x24fdad414..0x24fdad464`

`SETUP.streams[i].type`（96/100/101/102/103/106/107/108/109/110/111/120）与 RTP 包的
payload type（96/97/100/101/104/105/106/107/108/109）数值区间重叠但语义不同。

跨媒体的type名字表位于`0x2693e5da0`，索引=type-96，掩码`0x100fcf1`
（`A01.6`）。名字是 GeneralAudio(96)、MainAudio(100)、AltAudio(101)、MainHighAudio(102)、
BufferedAudio(103)、AuxAudio(106)、OutOfBandAVVCAudio(107)、
AuxAudioWithRedundancy(108)、OutOfBandAVVCAudioWithRedundancy(109)、MainScreen(110)、
AltScreen(111)、Playback(120)。这不是音频流合法白名单；110/111属于屏幕，具体音频支持集合应核构造/协商分支。
禁止把 `type=100` 直接当 PT 100 用，或把 PT 104 当 SETUP type 发出去。
唯一已知的二次映射是「`raw102` → `gen`(96)」（`INFERRED`）。

#### R-1.2 接收侧准入
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.1`、`A02.2`、`0x24fdad41c..0x24fdad454`、`0x24fe44bc0`

所引入口先检查至少2B并按首字节/PT筛选；这只是入口门，不是完整包合法性证明。
参考标准RTP诊断解析器额外检查如下结构（不是所有CarPlay profile的接收规范）：

1. 至少12B固定头，CSRC/扩展/填充长度分别校验；
2. 首字节∈0x80..BF（V=2）；P/X/CC非零时不能仍固定payload偏移12；
3. `pt = pkt[1] & 0x7F`（marker 位不参与）；
4. `pt ∈ {96,97,100,104,106,107,108,109}`（位掩码 `0x3d13`）。

`pt ∈ {101,105}` 是发送侧专用，收到必须拒（`A01.2`）。`pt ∉ 96..109` 同样是拒。

#### R-1.3 同一 raw type 的方向由 `input` 决定
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A01.4`、`MA-02`、MR04

`raw100` 不带 `input` 时是媒体音（设备 → 车机，回复里的 `dataPort` 是车机端口）；
带 `input=true` 时是麦克风（车机 → 设备，请求里的 `dataPort` 是本机监听端口）。
实现应分别管理两方向的配置、密钥与处理状态，但不强制复制Apple对象数量；raw100本身还存在双输出槽构造路径。

#### R-1.4 SETUP 音频字段的键名
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.3`、`0x2693e7c00..0x2693e7d58`

以下是已见键名，不是每条流必须全部发送的字段清单；按spec02及适用profile确认写入条件：

`audioType`、`audioFormat`、`audioLatencyMs`、`streamID`、`streamConnectionID`、
`controlPort`、`dataPort`、`input`、`spf`、`vocoderInfo`、
`supportsHighAccuracyTimestamps`、`supportsRTPPacketRedundancy`。

type（整数）是流类型键；字典插入顺序不是已证线上要求。

#### R-1.5 端口数值必须来自协商
级别：MUST NOT ｜ 证据：OPEN ｜ 依据：`OPEN-PORT-1`、`A02.4`

不得把 `controlPort`/`dataPort` 写死成「公开资料里的常见值」。请求里的本机 `dataPort`
必须是真实 bind 成功并已开始监听的那个端口；回复里的 `dataPort` 必须原样取用，
不得改写、不得与请求值互换。

#### R-1.6 导航提示音不得假设
级别：MUST NOT ｜ 证据：OPEN ｜ 依据：`A05.4`、`OPEN-AUD-1`

本阶段没有证据表明导航提示音走独立流、独立 `raw` 还是与媒体音混音。
实现必须：

- 先按「单条媒体流」跑通；
- 把「第二条流」做成可配置（开关 + 独立 `raw`/`audioType` 参数）；
- 在拿到抓包前，不得声称提示音优先级/闪避已实现。

#### R-1.7 未证语义的 PT 只可透传
级别：MAY ｜ 证据：OPEN ｜ 依据：`A01.2`、`OPEN-AUD-2`

`106 auxo`、`107 oovc`、`108 axrd`、`109 ovrd` 只在准入层放行，语义未证。
实现可以「收下并计入统计」，但不得据此决定播放/丢弃策略，也不得把它们映射到媒体音解码器。

#### R-1.8 多流并存
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A05.1`、`A05.3`

每条流应独立维护：SETUP 状态、端口、密钥方向、解密器、队列、统计。
禁止用「一条流的 ready 标志」代表全部流就绪（`A05.2` 的 `+0xb8` 与输入门是两套）。
