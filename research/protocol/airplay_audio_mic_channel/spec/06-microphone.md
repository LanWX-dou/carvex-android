# 06 麦克风上行

#### R-6.1 接收白名单
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A06.1`、`0x2519c0b88..0x2519c0c08`

麦克风方向的收包回调只放行四个消息标签：

```text
0x6d61696e  "main"
0x6d726564  "mred"
0x6f6f7663  "oovc"
0x6f767264  "ovrd"
```

其它标签（含 `gen`/`gred`/`auxo`/`axrd`）立即返回，不进队列、不解密。
注意这与 `R-1.2` 的全局 PT 准入是**两个独立的门**：过了全局门也可能在这里被拒。

#### R-6.2 先建监听，再发 SETUP
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A06.4`、`0x2519be194..0x2519be3f8`

顺序固定为：

1. 建 input transport（UDP listener，`minp`）；
2. 读取实际绑定端口（`LocalNetworkPort`）；
3. 把 `input=true` + `dataPort=<该端口>` 写进 SETUP 请求；
4. 发送 SETUP，等待回复。

先发 SETUP 再监听，会让车机把音频发到没人收的端口。端口读不到时**不得**用 0 或猜测值。

#### R-6.3 `dataPort` 在 input 方向是「本机端口」
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A02.6`、`A06.4`、`0x2519be8f4..0x2519be91c`

所述input请求中的dataPort是本机监听端口；响应dataPort的方向必须按该流及控制路径核验，
不能仅凭“回复里的端口”就认定它属于另一方向。不要互换本机与远端端口。

#### R-6.4 handler 创建失败必须显式处理
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A06.4`

固件在 `0x2519be3e4` 调用 `APSRTPPacketHandlerCreate(allocator, 2, 2, NULL, &handler)`
之后**没有检查返回值**就继续。本端必须：

- 检查返回码，非 0 即中止该流并上报；
- 不得假设NULL handler仍能维持完整接收能力；是否必崩需追后续路径，不能从未检查返回值直接推断。

#### R-6.5 暂存项的 type 语义
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A06.2`、MR04

固件的暂存队列只存消息本体，排空时把**当前**回调的 type 赋给所有 pending 包。
这是已知缺陷面。本端应在队列项里保存每包自己的 `pt`/标签，并在文档里标注为本端增强。

#### R-6.6 采集格式未定
级别：MUST NOT ｜ 证据：OPEN ｜ 依据：`OPEN-MIC-1`、`A02.10`

车机麦克风送到本设备的实际格式/帧长仍待核；设备侧负责接收与解码，不是默认本地采集上行。实现应：

- 将车机实际采集/发送能力与本设备接收/解码能力匹配，能力字典Input/Output的端点视角须逐路径核对；
- 将选定格式对象的整数标识写进SETUP的audioFormat，不回显本地名称字符串；基础映射/传输与HAL转换见spec11，完整选择仍见OPEN-CODEC-1；
- 未识别格式时拒绝该流，不要用默认 PCM 顶上。

#### R-6.7 增益/降噪/回声
级别：MAY ｜ 证据：OPEN ｜ 依据：`OPEN-MIC-2`

固件片段里没有增益、降噪、回声消除分支。本端可以做，但必须：

- 默认关闭或保守参数；
- 在文档里标为「本端处理」，不写成协议要求；
- 不得用 AGC 改变音频时间戳/帧长（会破坏 RTP 节奏）。

#### R-6.8 语音与电话的状态约束仍需追踪
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A06.6`、`0x251bef033`、`0x251bef021`

固件包含如下日志线索：
「Cannot setup a Speech stream while Telephony state is active」；
语音状态下恢复 AVVC 流也会被拒：「Car is in speech state; resuming AVVCAudio stream is invalid」。
这些字符串尚不足以证明所有语音流全局互斥；需要引用实际条件、状态来源与拒绝路径。
不能由此禁止所有并发telephony/speech流。车机上行门控与焦点仍属`OPEN-MIC-3`。

#### R-6.9 麦克风走同一套 RED/解密
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A06.5`、`R-3.5`、`R-4.1`

所述麦克风路径将+0x180对象交给解密处理；消息头为10B，AAD入口为M[2:10]。
实际网络封装、provider、尾布局及方向键须分别绑定；不能泛化成所有麦克风都是12B网络头加24B尾。

#### R-6.10 麦克风方向的 handler 参数
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A06.4`、`A03.6`、MR-04

媒体路径以 `(1, maxPackets)` 创建 handler（`A03.6`），麦克风路径按前序记录以 `(2, 2)`
创建（`0x2519be3e4`）。由此：

- 只能记录这两个实参为2，不能在语义未证时推出麦克风冗余深度恒2；
- 这两个数字的语义（是否 SeqQ、方向位）未证，**不要**照抄数字去解释含义；
- 收包侧仍按白名单（`R-6.1`）与 F 链解析，不假设对端深度。
