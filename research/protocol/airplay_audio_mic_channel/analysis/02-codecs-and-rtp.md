# 02 编解码与 RTP 打包

## 2.1 SETUP 里的音频流描述

一次音频流协商的请求形状是 `{streams: [ {type, ...} ]}`（`streams` 键名 `0x2693e7c08`）。
每流字典的音频字段键名全部来自 AirPlaySender 的 CFString 常量表 `0x2693e7c00` 起：

| 键名 | 常量槽 | 值类型 | 何时写入 | 证据 |
|---|---|---|---|---|
| `audioType` | `0x2693e7c28` | string | 总是 | `CONFIRMED` `0x2519be828` |
| `audioFormat` | `0x2693e7c18` | integer | 总是 | `CONFIRMED` `0x2519be814..84c`，analysis10 §10.1 |
| `audioLatencyMs` | `0x2693e7c48` | int | 总是（取 `[x23]` 首字） | `CONFIRMED` `0x2519be850` |
| `vocoderInfo` | `0x2693e7d28` | dict | 仅 `audioType=="telephony"` 且 raw==100 | `CONFIRMED` `A02.7` |
| `controlPort` | `0x2693e7c68` | int | 控制口 >0 | `CONFIRMED` `0x2519be8a0` |
| `spf` | `0x2693e7c80` | int | 与 `controlPort` 同条件，取 `[x27+0x14]` | `CONFIRMED` `0x2519be8c4` |
| `input` | `0x2693e7c40` | bool=true | 本机 `dataPort`>0 | `CONFIRMED` `0x2519be8fc` |
| `dataPort` | `0x2693e7c78` | int | 本机 `dataPort`>0 | `CONFIRMED` `0x2519be910` |
| `supportsHighAccuracyTimestamps` | `0x2693e7d30` | bool=true | 总是 | `CONFIRMED` `0x2519be920` |
| `supportsRTPPacketRedundancy` | `0x2693e7d38` | bool=true | sp+5c非零，上游条件待核 | `CONFIRMED` `0x2519be93c` |
| `streamConnectionID` | `0x2693e7c38` | int | 会话侧生成 | `INFERRED` SS-03 |
| `streamID` | `0x2693e7c88` | int | 回复里读回 | `INFERRED` SI-01 |

同一张表里还有本轮未用到的音频相关键：`isMedia`、`arrivalToRenderLatencyMs`、
`audioBufferSize`、`redundantAudio`、`disableRetransmits`、`burstPeriodMs`、
`streamStartTimestamp`、`latencyMin/Max`、`audioSessionID`、`clientID`。
其中后三个可选参数的局部写入条件已有analysis10补证；其它键不能只凭存在推导语义/必填性。

`audioType` 的取值里只有 `telephony` 被本阶段直接读出（CFString 对象 `0x27612e7b0`，
比较点 `0x2519be878..0x2519be89c`，相等才追加 `vocoderInfo`）。其余取值
（`main`/`speechRecognition`/`default`/`alert`/`media`）来自前序规则 MA-06，
本阶段未重跑（`A02.9`，`INFERRED`）。

**字段类型已核，映射待追**：audioFormat来自格式对象+0x60，以整数写入；audioType才走对象值。
能力字典用audioInputFormats/audioOutputFormats的选择线索来自MA-06（INFERRED），
不证明能力条目是名称字符串。整数标识→基础ASBD及传输/HAL转换已由analysis11/C12补证，
能力交集和优先级仍需追；不能从名称表推出“整串回显”。

## 2.2 消息结构与网络边界

已核内部音频消息M为10B头（seq BE16、timestamp BE32、第二BE32字段）及元素/数据区。
M复制到内部I+2，数据M+10对应I+12；PT另写入I+1，而I+0不由该复制设置。
详见analysis09及相邻RTP analysis11，不能由2+10直接宣布完整网络头恒12B。

AAD入口取M[2:10]，只在所述复制关系下等价I[4:12]。网络↔M映射仍待核，
标准RTP的CSRC/扩展/padding也不能忽略。具体provider决定密码输入及附加输出，
raw100某分支的24B线索不能推广所有音频。

## 2.3 首字节与 PT 的准入（可复算）

```text
0x24fdad41c  cmp  x8,#1            ; 长度 < 2 直接拒绝
0x24fdad424  ldrsb w9,[x8]         ; 首字节按有符号读
0x24fdad428  cmn  w9,#0x40         ; w9 + 0x40
0x24fdad42c  b.ge  fail            ; 必须 0x80..0xBF
0x24fdad430  ldrb w8,[x8,#1]
0x24fdad434  and  w23,w8,#0x7f     ; marker 位不参与查表
0x24fdad438  sub  w8,w23,#0x60
0x24fdad440  cmp  w9,#0xe          ; 只接受 96..109
0x24fdad448  mov  w9,#0x3d13       ; 位掩码
0x24fdad44c  lsr  w9,w9,w8
0x24fdad450  tbz  w9,#0,fail
0x24fdad458  adrp x9,0x24fe44000
0x24fdad45c  add  x9,x9,#0xbc0     ; PT 名表
0x24fdad460  ldr  w1,[x9,x8,lsl#2]
```

因此：`0x80..0xBF` 之外的包必须拒；PT 取低 7 位；PT 必须在 96..109 且掩码允许。
`0xE4`（marker=1, PT=100）是合法 main 包，`0xC0`、`0x7F`、PT=110 都必须拒。

## 2.4 发送侧标签

`0x24fdabdf4..0x24fdabf3c` 用一串 32 位立即数与内部消息标签比较：
`alt `=`0x616c7420`、`ared`=`0x61726564`、`auxo`=`0x6175786f`、`axrd`=`0x61787264`、
`ovrd`=`0x6f767264`、`gred`=`0x67726564`、`main`=`0x6d61696e`（`CONFIRMED` 常量本身）。
标签到 PT 的数值映射来自 RL-02（`INFERRED`）：

| 内部名 | PT |
|---|---:|
| gen | 96 |
| gred | 97 |
| main | 100 |
| alt | 101 |
| mred | 104 |
| ared | 105 |
| auxo | 106 |
| oovc | 107 |
| axrd | 108 |
| ovrd | 109 |

**不要用这张表反向推 SETUP 的 `type`**：`raw102` 在既定上下文中映射到 `gen`(96)，
属于「传输流类型 → 包内标签」的二次映射，不是同一个编号空间（`A01.5`）。

## 2.5 未闭合

- `OPEN-CODEC-1`：`audioFormat` 的候选值与最终选定规则。
- `OPEN-CODEC-2`：采样率/声道/帧长/码率，以及是否允许运行时改格式。
- `OPEN-CODEC-3`：`redundantAudio`、`burstPeriodMs`、`disableRetransmits` 的实际语义。

## 2.6 本地格式名称表（不是线上 audioFormat schema）

下列本地名称字面量是继续追表/构造器的线索；旧稿把它们直接当成线上audioFormat，已撤回。
原名称簇位于 `0x251be410f..0x251be44b3` 及 `0x251c23c4e..0x251c23c62` 附近；
这些范围不构成完整格式映射，也不证明全部项适用于CarPlay。名称可呈下列形状：

```text
CODEC / rate [ / depth ] / channels
depth    ∈ {16, 20, 24, 32f}                    ; "32f" = 32-bit float
channels ∈ {1, 2, 5.1, 5.1.2, 5.1.4, 7.1, 7.1.2, 7.1.4, 9.1.6}
```

| 编解码器 | 出现的格式（节选，全部字面量见上两段地址） |
|---|---|
| `PCM` | `PCM/8000/16/1..2`、`PCM/16000/16/1..2`、`PCM/24000/16/1..2`、`PCM/32000/16/1..2`、`PCM/44100/16/1..2`、`PCM/44100/24/1..2`、`PCM/48000/16/1..2`、`PCM/48000/24/1..2`、`PCM/48000/32f/1..2`、`PCM/48000/{16,32f}/5.1`、`.../5.1.2`、`.../5.1.4`、`.../7.1`、`.../7.1.2`、`.../7.1.4`、`.../9.1.6` |
| `ALAC` | `ALAC/44100/16/2`、`ALAC/44100/20/2`、`ALAC/44100/24/2`、`ALAC/48000/16/2`、`ALAC/48000/20/2`、`ALAC/48000/24/2` |
| `AAC-LC` / `AAC_LC` | `AAC-LC/44100/2`、`AAC-LC/48000/2`、`AAC_LC/48000/5.1`、`AAC_LC/48000/5.1.2`、`AAC_LC/48000/7.1` |
| `AAC-ELD` / `AAC_ELD` | `AAC-ELD/16000/1`、`AAC-ELD/24000/1`、`AAC-ELD/32000/1`、`AAC-ELD/44100/1`、`AAC-ELD/48000/1`、`AAC-ELD/44100/2`、`AAC-ELD/48000/2`、`AAC_ELD/48000/5.1`、`AAC_ELD/48000/5.1.2` |
| `OPUS` | `OPUS/16000/1`、`OPUS/24000/1`、`OPUS/48000/1` |
| `DDPLUS` | `DDPLUS/48000/{2,5.1,5.1.2,7.1.4,9.1.6}` |
| `QAAC` / `QAACHE` / `QAACHEV2` / `PAAC` | `QAAC/44100/2`、`QAAC/48000/{2,5.1,5.1.2}`、`QAACHE/...`、`QAACHEV2/44100/2`、`PAAC/44100/2` |
| `QLAC` | `QLAC/48000/24/2` |
| `QC3` | `QC3/48000/{2,5.1,5.1.2,7.1.4,9.1.6}` |

这张表不能直接生成客户端协议解析器：

1. 名称中的数字只作线索；实现采用spec11已绑定原转换函数/格式对象的整数表，不按名称推定。
2. 不能仅按单声道/采样率给流指定麦克风或媒体用途；OPEN-MIC-1还缺方向与格式选择链。
3. 名称同时出现连字符/下划线，不证明线上需要兼容两套字符串；本构造器发送的是整数。

配套的码率证据（`A02.11`，字符串地址已知，取值来源未证）：

```text
0x251bef139  "%@: Setting bitrate to: %u (Packet size limit bits: %u)"
0x251be40c4  "PacketSizeLimit ignored since audio format(%s) doesnt support vbr"
0x251be44b9  "VBRBitRate ignored since audio format(%s) doesnt support vbr"
0x251bef332  "%@: RFC2198 redundancy support: %s"
```

也就是说：码率与「包大小上限」只在支持 VBR 的格式上生效（PCM/ALAC 这类不吃），
RED 支持是**运行期判定**后打的日志，不是编译期常量。

`carAudioStream_setupTransportStreams` 的签名串（`0x251bef1a0`）还确认了一个细节：
媒体流与麦克风流的传输流是在同一处创建的，并会
「Adding a dummy input stream to force %@ to be input-output rather than output-only」
（`0x251bef21d`）——即为了拿到「输入+输出」形态，固件会补一条哑输入流（`A05.5`）。

能力字典侧的键名（`A02.17`）：`audioInputFormats`（`0x251c36a29`）、
`audioOutputFormats`（`0x251c36a3b`）、`audioOutputFormatsExtended`（`0x251c36707`）。
同一簇里还有 `CarPlayAudioFormats`（`0x251bedcb2`）、`AudioFormatInfo`（`0x251bedc87`）
以及车机特例串 `BMW`（`0x251bedd8b`）、`NBTEvo`（`0x251bedd8f`）。

品牌字符串仅提示待追的特例路径，不能仅据此确认分支行为。
OPEN-CODEC-1的整数映射已有analysis11补证，仍需静态闭合完整能力schema、交集/回退/特例；
给定车机能力输入后可按已证规则计算候选，真实会话选择另作运行验证。

## 2.7 原指令纠错入口

见[analysis10](10-config-field-audit.md)：audioFormat整数写入、LowLatencyAudio条件布尔、
burstPeriodMs发送端偏好缺失默认200、spf整数与向零截断。C11固定原镜像/指令回归，不需先抓包。

新增[analysis11](11-format-id-map-audit.md)/[spec11](../spec/11-format-id-map.md)：
59行完整基础描述映射、Sender逐位调用绑定、传输/HAL转换和局部能力键选择；C12重新执行原函数，
不依赖名称猜测，不等于完整格式协商或真实编码器运行。

