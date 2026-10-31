# 12 · 流键名与加密记录格式（第 2 批）

本批把抽样从 55 个函数扩到 66 个（`AirPlaySender` 20 / `APTransport` 16 / `CoreUtils` 30），
目标只有一个：把 `OPEN-AP-24`、`OPEN-AP-25`、`OPEN-AP-21` 从"未知"推进到"可写进规范"。

## 12.1 键名解码：先解决"读不出来"

24A446 的三个镜像**没有** `LC_DYLD_CHAINED_FIXUPS`（`source/metadata/*/load-commands.json`，45 条命令里无
`0x80000034`），`__DATA_CONST` 的常量槽位是 arm64e 认证/重定位后的值，Ghidra 只能给到
`cfstringStruct_<地址>`，读不出字符串。本批用两步解码：

1. 槽位 8 字节 → `addr = (slot & 0x7FFFFFFF) | (hi << 32)`，`hi` 取使地址落在已映射段内的值；
2. 该地址是 `__cfstring` 结构 `{isa, flags, data_ptr, length}`（`flags` 在 `+8`，`data_ptr` 在 `+16`，
   `flags & 0x10` 表示 inline），对 `data_ptr` 再做一次同样解码，即得 C 字符串。

三个独立锚点验证（`A12.1`）：

| 符号 | 槽位 | 结构 | 字符串地址 | 内容 |
|---|---|---|---|---|
| `_kAPSenderSessionStreamKey_Type` | `0x2693e7d08` | `0x27612fb30` | `0x251bf5fb9` | `type` |
| `_kAPSenderSessionStreamKey_StreamID` | `0x2693e7c88` | `0x276132150` | `0x251c05b62` | `streamID` |
| `_kAPSenderSessionStreamKey_ConnectionID` | `0x2693e7c38` | `0x276136f70` | `0x251c1db98` | `streamConnectionID` |

复现：`python3 tools/decode-keys.py AirPlaySender _kAPSenderSessionStreamKey`
（49 个符号：解析 49、未解析 0、歧义 0）。`_kAPEndpointStreamConnectionKey` 9/9、
`_kAPEndpointStreamProperty` 全部同样解析。
Ghidra 侧辅助脚本 `tools/ghidra/DumpAt.java` 打印某地址处 Ghidra 认定的数据类型与引用，
可确认这些槽位在 Ghidra 眼里只是 `undefined8`（即它没有替我们做重定位）。

## 12.2 `streams[]` 元素键（`A12.2`）

`_apsession_setupStreamCreatingResponseInternal`（`0x2519bbf24`）用
`func_0x00025810a790(dict, key, value)` 逐键填字典；键来自 `_kAPSenderSessionStreamKey_*`。
解码后（只列与本任务相关者）：

| 符号后缀 | 线上键名 | 备注 |
|---|---|---|
| `_Type` | `type` | 流类型整数，见 12.4 |
| `_StreamID` | `streamID` | 与 `X-Apple-StreamID` 同源 |
| `_ConnectionID` | `streamConnectionID` | 连接标识 |
| `_StreamConnections` | `streamConnections` | 子字典数组，见 12.3 |
| `_NetworkPortControl` | `controlPort` | 控制端口 |
| `_NetworkPortData` | `dataPort` | 数据端口 |
| `_Seed` | `seed` | 流加密种子 |
| `_SharedEncryptionKey` | `shk` | 共享加密密钥（受 `OPEN-AP-34` 约束） |
| `_SampleRate` | `sr` | 采样率 |
| `_FramesPerPacket` | `spf` | 每包帧数 |
| `_CompressionType` | `ct` | 压缩类型 |
| `_AudioFormat` | `audioFormat` | 音频格式 |
| `_AudioFormatIndex` | `audioFormatIndex` | 音频格式索引 |
| `_AudioType` | `audioType` | 音频类型 |
| `_Latency` | `audioLatencyMs` | 延迟（毫秒） |
| `_IsMedia` | `isMedia` | 是否媒体流 |
| `_WantsInput` | `input` | 是否要输入 |
| `_UsingScreen` | `usingScreen` | 屏幕流标记 |
| `_ViewArea` | `viewArea` | 视区 |
| `_SupportsDynamicStreamID` | `supportsDynamicStreamID` | 动态 ID 支持 |

## 12.3 连接子字典键（`A12.3`）

| 符号后缀 | 线上键名 |
|---|---|
| `_Port` | `streamConnectionKeyPort` |
| `_IPAddress` | `streamConnectionKeyIPAddress` |
| `_TransportProtocol` | `streamConnectionKeyTransportProtocol` |
| `_InterfaceType` | `streamConnectionKeyInterfaceType` |
| `_MulticastInterfaceType` | `streamConnectionKeyMulticastInterfaceType` |
| `_UseStreamEncryptionKey` | `streamConnectionKeyUseStreamEncryptionKey` |
| `_EncryptionSeed` | `streamConnectionKeyEncryptionSeed` |
| `_MACAddress` | `streamConnectionKeyMACAddress` |
| `_NetworkInfo` | `streamConnectionKeyNetworkInfo` |

对应值枚举另有 `streamConnectionKeyTransportProtocol` 的 `UDP`/`TCP`/`QUIC` 与
`streamConnectionKeyInterfaceType` 的 `LLW`/`Terminus`（`_kAPEndpointStreamConnectionTransportProtocol_*`、
`_kAPEndpointStreamConnectionInterfaceType_*`），本批未逐条解码，按符号名记录。

## 12.4 `type` 是枚举，`0x82` = 130（`A12.4`）

`0x2519bbf24` 在拿到字典的 `type` 后进入一个比较链（`source/asm/AirPlaySender/f_2519bbf24.s`）：

| 指令 | 比较 | 去向 |
|---|---|---|
| `0x2519bcad4` | `cmp w23,#0x69` | `b.le` 到 `0x2519bcb20`（有符号 ≤105） |
| `0x2519bcadc` | `cmp w23,#0x6d` | `b.le` 到 `0x2519bccd0`（106–109，继续筛选） |
| `0x2519bcae4`–`0x2519bcaec` | `sub w8,w23,#0x6e; cmp w8,#2` | `0x2519bcd80`（110/111） |
| `0x2519bcaf0` | `cmp w23,#0x78` | `0x2519bd120` |
| `0x2519bcaf8` | `cmp w23,#0x82` | `0x2519bd120` |
| `0x2519bcb28` | `cmp w23,#0x60` | `0x2519bcbec` |
| `0x2519bcb30` | `cmp w23,#0x64` | `0x2519bcef8` |
| `0x2519bcb38` | `cmp w23,#0x65` | 继续 |
| `0x2519bcbe0`–`0x2519bcbe8` | `sub w8,w23,#0x66; cmp w8,#2; b.hs` | 仅 102/103 留在 `0x2519bcbec` 分支 |
| `0x2519bccd0`–`0x2519bccdc` | 分别比较 `0x6a`/`0x6b` | 106/107 有专门路径；108/109 到错误分支 |

此比较链有专门处理分支的值为 **96、100、101、102、103、106、107、110、111、120、130**。
`sub #110; cmp #2; b.lo` 只包括 110/111，**不包括 112**；109 也只是分组边界，不是合法值证据。
其余值在该链进入 `0x2519bd054`，装载错误 `0xfffee76f`。分派有分支不代表全部参数、密钥或 profile 验证成功，
也不能据此宣称这是整个 SDK/线上协议的完整类型枚举。`tools/verify-type-dispatch.py` 对原指令执行有限分支解释，覆盖有效值及邻界反例。
`0x2519bd120` 只把输出参数写回并返回（`0x2519bd120`–`0x2519bd148`），**不**创建 cryptor；
120 与 130 共用这一条路径（`A12.5`）。这说明此分派识别 130；不能仅凭无 cryptor 推出它在线上使用什么协议。

仍未证明：130 是否就是"走 iAP2 隧道"（`OPEN-AP-41`）。

## 12.5 加密记录格式（`A12.6`）

读路径 `__NetTransportRead`（`0x18be49968`）：

| 地址 | 指令 | 含义 |
|---|---|---|
| `0x18be49a24` | `mov w2,#2` | 先读 2 字节 |
| `0x18be49a30` | `ldrh w2,[x22,#0x28]` | 小端 u16 = 负载长度 |
| `0x18be49a34` | `str x2,[x22,#0x18]` | 作为剩余字节数 |
| `0x18be49a38` | `cmp w2,#4,lsl#12` | 上限 16384，超出跳 `0x18be49c10` |
| `0x18be49a78` | `mov w2,#0x10` | 再读 16 字节 |
| `0x18be49a84`–`0x18be49a94` | `add x1,x22,#0x4150; bl 0x18be4a104` | 用 `+0x4150` 的 32 字节密钥解封 |

写路径 `__NetTransportWriteV`（`0x18be4d5fc`）：

| 地址 | 指令 | 含义 |
|---|---|---|
| `0x18be4d740` | `strh w22,[x8,#0x178]` | 把聚合长度写入记录头 |
| `0x18be4d750`–`0x18be4d754` | `mov w2,#2; bl 0x18be48df8` | 将 2 字节长度送入 Poly1305，即 AAD；不是 socket 写出 |
| `0x18be4d820`–`0x18be4d838` | `ldrb/add/strb`，最多 8 字节进位 | 逐记录递增 8 字节小端计数器 |
| `0x18be4d83c` | `add x8,x8,#0x10` | 标签 16 字节，紧跟负载 |

缓冲布局：`+0x4178` 长度、`+0x417a` 负载起点、`+0x457a` 负载上限（1024 字节）。

**线上记录 = `u16 LE 负载长度` + `该长度的密文` + `16 字节认证标签`**（`A12.6`）。
`_NetTransportChaCha20Poly1305Configure`（`0x18bf1adbc`）把 32 字节密钥放到 `+0x4150`、
另一方向 32 字节密钥放到 `+0x46a0`，各带一个 8 字节值（`+0x4170`/`+0x46c0`），
并把读/写函数指针装到 `+0x18`/`+0x20`（`0x18bf1ae88`–`0x18bf1aea4`），
所以上面的格式适用于该 AEAD 传输层。

## 12.6 后续复核与剩余缺口

- `A13.1` 已确认长度两字节为 AAD，`OPEN-AP-38` 在本构建静态范围关闭。
- `A13.2` 已确认独立 nonce64 原样初始化/逐记录递增，不是基准再拼计数器；`OPEN-AP-39` 静态关闭。
- `A13.3` 已核 Configure 参数与槽位读写方向；上游角色/HKDF 标签绑定仍属 `OPEN-AP-40`。
- 上表各 type 的业务语义，尤其 130 是否隧道，仍为 `OPEN-AP-41`。
