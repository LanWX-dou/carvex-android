# 02 编解码与打包

#### R-2.1 SETUP 请求的音频形状
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.3`、`A02.4`、`0x2519be828..0x2519be958`

```text
{
  "streams": [
    {
      "type": <raw int>,
      "audioType": <string>,
      "audioFormat": <integer format ID>,
      "audioLatencyMs": <int>,
      ...可选...
    }
  ]
}
```

`type` 在 `streams[i]` 里，其余字段是同层兄弟键，**不是** `type` 的子字典。
回复只接受 `streams` 数组长度为 1、且 `type` 与请求相等的形状（`INFERRED` SS-04）。

#### R-2.2 字段写入条件
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.4`

| 条件 | 必须写入 |
|---|---|
| 总是 | `audioType`、`audioFormat`、`audioLatencyMs` |
| `audioType=="telephony"` 且与 100 比较相等 | `vocoderInfo` |
| `controlPort` 已知且 >0 | `controlPort` 与 `spf`（`spf` = `[stream+0x24]`，即格式描述 +0x14） |
| 本机监听端口已就绪且 >0 | `input=true` 与 `dataPort` |
| 总是 | `supportsHighAccuracyTimestamps=true` |
| `[sp+0x5c]!=0`（与 RED 深度同源，`A02.16`） | `supportsRTPPacketRedundancy=true` |
| raw==107（OutOfBandAVVCAudio）且值非空 | `streamStartTimestamp` |
| raw==107 | `burstPeriodMs` |

后三行是本轮复核的：`streamStartTimestamp`/`burstPeriodMs` **只在 107 上出现**（`A02.14`），
不是通用字段。`supportsRTPPacketRedundancy` 的上游算法（是否等价于「非 USB 且 raw!=102」）
仍未证，见 `OPEN-RED-1`。

顺序无关，但**条件不满足就不写**：不要用 0 或空字典占位（车机按「存在性」判断）。

#### R-2.3 `vocoderInfo` 只属于 telephony
级别：MUST NOT ｜ 证据：CONFIRMED ｜ 依据：`A02.7`、`0x27612e7b0`、`0x2519be878..0x2519be89c`

只有在 `audioType` 与常量 `telephony` 逐字节相等、且另一寄存器与 100 比较相等时
才追加 `vocoderInfo`（该寄存器是否 raw type 未证，见 `A02.7`）。
对 `main`/`alert`/`speechRecognition` 等其它类型加这个键，属于自创字段。

#### R-2.4 能力标志与写入条件
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.4`、`0x2519be920..0x2519be958`

该构造路径将supportsHighAccuracyTimestamps写为true；supportsRTPPacketRedundancy的写入门是
[sp+0x5c]!=0，上游是否等价于“非USB且raw!=102”未闭合。独立实现应如实声明能力；
缺失与false是否等价须按profile核对，不能直接改字段当作已验证兼容策略。

#### R-2.5 `audioFormat` 必须写整数格式标识
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.10`、analysis10 §10.1

该CarPlay SETUP构造器从格式对象+0x60读取标识，以CFDictionarySetInt64写入audioFormat。
不要发送 `PCM/48000/16/2` 等本地名称字符串；audioType仍是独立字符串字段。
整数→基础描述的59行映射已核，见[spec11](11-format-id-map.md)，并按R-11.6区分传输/HAL转换。
能力过滤与最终选择仍未闭合，不能自行猜位值或照名称表编枚举。

#### R-2.10 按整数映射，不解析名称
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.10`、`A11.1`、`A11.2`

撤回旧版split("/")线上解析算法和缺省位深16规则。本地描述字符串不是能力字典schema。
使用spec11整数位→ASBD表；能力集合不能作为单个格式，未知/多位输入不能自动取第一位。
后续仍需追完整能力条目解析、交集优先级与回退，不把这些工作改成仅待车机抓包。

#### R-2.11 编码器配置与 ASBD
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A11.1`、`A11.4`

使用R-11.2基础表和R-11.6调用者转换：lpcm传输flags OR2而HAL清2，压缩格式保留传输描述并
另建PCM HAL。不能把ASBD bits与第三输出bits混同，也不能按名称字符串填所有codec的PCM标志。
完整codec附加配置和运行时属性仍需补齐；spf整数和局部运算见R-2.12，不能以HAL的1F/packet覆盖传输帧长。

#### R-2.12 码率/VBR：只对支持 VBR 的格式
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A02.11`、`0x251bef139`、`0x251be40c4`、`0x251be44b9`

固件会打「`Setting bitrate to: %u (Packet size limit bits: %u)`」，并对不支持 VBR 的格式打
「`PacketSizeLimit ignored ...`」「`VBRBitRate ignored ...`」。因此：

- PCM/ALAC 这类固定码率格式不要下发 `VBRBitRate`/`PacketSizeLimit`，会被忽略；
- AAC 系列可以下发，但实际生效值取决于车机；
- RED 是否启用是**运行期判定**（`RFC2198 redundancy support: %s`），不要写死。

码率与包大小的算法（`A02.13`，已复核）：

```text
pps                 = trunc(sampleRate / spf)
packetSizeLimitBits = bitrate // pps
bitrate 阶梯:  rate<=24000 -> 48000 | rate<=32000 -> 64000 | rate>32000 -> 96000
               raw102(MainHigh) -> 256000
'lpcm' 格式直接跳过这一步（不设码率，也不设包大小上限）
```

`sampleRate` 是格式描述里的double，`spf` 是同结构+0x14的无符号整数，
不是float；`ucvtf`转换后相除，`fcvtzu`向零截断，最后`udiv`整数除法（analysis10 §10.4）。
公式限定正有限且转换/除法有效的输入；48000/512得到pps=93，96000//93=1032。
格式映射、spf来源、有效性检查及运行时变更仍属OPEN-CODEC-2，不是只差车机选值。

#### R-2.13 RED 相关的三个可选键
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.15`、`A02.14`、`0x251bbb90c`、`0x2519be97c`

- 独立`_audioStream_resumeInternal`路径：`redundantAudio`取对象+0x74，按有符号≥1才写整数。
- 同路径：对象+0x28与`LowLatencyAudio`经FigCFEqual相等才写`disableRetransmits=true`；
  不相等省略键，不写false。不是能力字典含键测试。
- CarPlay构造路径：仅raw==107写`burstPeriodMs`；本地com.apple.airplay偏好
  jarvisDefaultBurstPeriod缺失时取200（analysis10 §10.3）。

这些是两个构造上下文的局部条件，不是所有流的通用三键模板。
发送端偏好默认200不等于车机缺键默认200；接收消费者及适用profile仍属OPEN-CODEC-3。

#### R-2.6 10B音频消息与外层网络头分离
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.5`、`A09.1`、`0x226e689e0`

```text
消息M+0  2B sequence   BE16
消息M+2  4B timestamp  BE32
消息M+6  4B secondWord BE32（已核主生产者写0，不推广所有SSRC规则）
消息M+10 ... 元素/音频数据
```

M被复制到内部I+2、外部参数PT写I+1，不证明I为网络包。网络↔M适配仍待核。
标准RTP有12B最小头，但CSRC/扩展会改变payload偏移，padding会改变payload末尾；
参考parse_header按标准检查这些边界，不构成目标CarPlay支持所有组合的证据。

#### R-2.7 payload type 表
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.2`、`0x24fe44bc0`、RL-02

| PT | 名字 | 接收 | 发送 |
|---:|---|---|---|
| 96 | gen | 条件（RED 时） | 是 |
| 97 | gred | 是 | 是 |
| 100 | main | 是 | 是 |
| 101 | alt | 否 | 是 |
| 104 | mred | 是 | 是 |
| 105 | ared | 否 | 是 |
| 106 | auxo | 是 | 是 |
| 107 | oovc | 是 | 是 |
| 108 | axrd | 是 | 是 |
| 109 | ovrd | 是 | 是 |

发送时 PT 由「内部消息标签 → PT」决定（`INFERRED` RL-02），不允许调用方随手填数字。

#### R-2.8 载荷长度与分片
级别：SHOULD ｜ 证据：OPEN ｜ 依据：`OPEN-CODEC-2`

本阶段没有确定单包最大载荷、是否分片、分片标记怎么用。实现必须把上限做成配置，
并在超过时**拒绝发送**而不是截断。局域网 MTU 推断属于本地策略，不是协议要求。

#### R-2.9 不得假设编解码器一致
级别：MUST NOT ｜ 证据：OPEN ｜ 依据：`OPEN-CODEC-1`、`research/protocol/airplay_audio_mic_channel.md` §3

不同车机可能给不同 `audioFormat`；同一车机的媒体音与麦克风也可能不同。
实现应按流/方向选择编码器或解码器，SETUP及重连后核验配置有效性，不能盲用上次会话缓存。
