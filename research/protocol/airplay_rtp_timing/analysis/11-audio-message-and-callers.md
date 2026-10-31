# 11 — 音频消息坐标、AAD入口与两条装配调用链

> 构建24A446。原始新增导出在`source/asm-audit/`；不修改旧Ghidra输出。AirPlaySupport镜像与元数据复用相邻`airplay_fairplay_crypto/source/`，校验器固定源SHA256并逐字节比对。导入名称取仓库`dsc-stubs.txt`，不是由函数名猜协议。

## 11.1 结论

| 编号 | 结论 | 范围 |
|---|---|---|
| `A11.1` | 音频消息CMBlockBuffer头为10B；GetAudioDataPointer从偏移10返回指针；Create把音频长度加10后创建引用 | 本构建API |
| `A11.2` | Get/SetAudioDataHeader对16位和两份32位字段分别转换大小端；AAD入口返回消息偏移2起8B | 本构建调用参数，不证明所有cryptor算法 |
| `A11.3` | 主发送路径与转码后处理均跳过10B头和元素区；第三参数h预留在数据后的附加输出范围 | 正常成功、长度/连续性前提成立时 |
| `A11.4` | 接收正常终止时C=4B元素数n+1，故4C−3=4n+1 | `OPEN-RTP-14`的正常格式算术已闭合 |
| `A11.5` | 消息M复制到内部buf+2；消息数据M+10对应buf+12，没有相互矛盾的两字节差 | 内部坐标；实际网络封装仍OPEN |
| `A11.6` | 第二调用者使用固定输入PT0x60、非空countOut；后处理后交环/队列，并非已读到直接socket发送 | 不推广为CarPlay当前必用链路 |

## 11.2 三套坐标

设M为音频消息CMBlockBuffer的逻辑起点，B为Compose音频数据起点，I为ReadNewMessage的内部包缓冲。

| 内容 | 消息坐标 | 接收内部坐标 | 证据 |
|---|---|---|---|
| 首16位（序号） | M+0..1，BE16 | I+2..3 | Get/SetAudioDataHeader + ReadNewMessage |
| 时间戳 | M+2..5，BE32 | I+4..7 | 主调用者填头 + 字节转换 |
| 第二32位字段 | M+6..9，BE32 | I+8..11 | 已核主路径填0，不证明所有profile的SSRC规则 |
| 元素/音频数据 | B=M+10 | I+12 | GetAudioDataPointer + 复制偏移2 |
| 外层PT | 不在这10B消息头中 | 由ReadNewMessage第3参数写I+1 | 不可把它当M+1 |

I+0不由这段拷贝设置。本表不是实际UDP/TCP包前缀定义；不得生成`[I+0, PT]`就宣称是可互通网络头。

AirPlaySupport的直接证据：

- GetAudioDataPointer `0x226e6a340`给CMBlockBufferGetDataPointer的offset参数10，`0x226e6a33c`把调用者的数据指针出参放x4；调用者长度出参仍是x2，即`lengthAtOffsetOut`，不是`totalLengthOut`。
- Create `0x226f23d68`把输入音频长度加10，`0x226f23d6c`令引用偏移0，再调用CMBlockBufferCreateWithBufferReference。
- GetHeader `0x226e68a08`–`0x226e68a10`从偏移0复制10B；`0x226e68a20`/`0x226e68a30`分别转换16位及两份32位字段。
- SetHeader先取总长并要求>9（`0x226f23f80`/`0x226f23f84`），分别转换16/32/32位后在偏移0替换10B（`0x226f23fa4`–`0x226f23fb4`）；短缓冲返回`-0x1a31`。不是未经检查写入12B。

块缓冲可能非连续：`lengthAtOffsetOut`与总长度不能无条件等同。当前调用者把这些范围用于直接拷贝/处理；独立客户端应先做连续化或分段处理和完整边界检查，不复制原调用点的隐含假设。

## 11.3 AAD与附加输出边界

GetAudioAADPointer（`0x226e68af0`）：偏移2、数据指针输出x4、两个长度输出传NULL；成功后显式写`*lengthOut=8`（`0x226e68b20`/`0x226e68b24`）。它不自己验证总长度≥10；前置消息有效性必须由调用链保证。该8B对应头内两份BE32字段，不含序号、元素区或PT。

主发送路径在`0x2519c2c70`调用此API，`0x2519c2cec`取出指针/8B长度，送后处理对象虚方法x1/x2。接收DecryptCurrentMessage在`0x2519c09e4`调用同API，`0x2519c0a48`/`0x2519c0a4c`送解密对象x1/x2。已证的是**AAD入口实参**，不是所有实现必有AEAD或该8B足以实现密码层；具体provider/key/nonce/tag仍需核。

正常数值域设g为元素区长度（单包0，合并4n+1）、S为音频数据总长、h为后处理对象槽+8返回的附加输出长度：

```text
消息请求范围：[10B头][g字节元素][S字节数据][h字节附加输出预留]
lengthOut = 10+g
Create参数 = g+S+h             ; API自身另加10
```

主路径从消息起点取数据指针，推进`lengthOut`到数据起点；附加输出地址为消息尾部减h；其虚方法收到数据长度/输出容量均为`消息范围长-(10+g)-h`。这里“消息范围长”来自offset0的`lengthAtOffsetOut`，只有连续完整消息时才等于总长。h的具体算法含义仍取决于provider，不能一律称16B tag。

转码helper `0x251aa7f38` 的参数是`(message, bodyLength, prefixLength, processor, out)`：

- 槽+8取得h，Create音频长度=`h+bodyLength`（`0x251aa7fe8`）。
- `prefixLength`截低32位再加10取数据指针（`0x251aa8018`/`0x251aa801c`），附加输出地址为`M+10+bodyLength`（`0x251aa803c`）。
- 槽+0x10调用的x1/x2为AAD指针/8，x3=x5为数据地址，x4=x6为`bodyLength-low32(prefixLength)`，x7为附加输出地址，栈上第9参数为h（`0x251aa80b8`–`0x251aa80dc`）。
- processor为NULL时跳过调用但仍创建/返回消息引用；存在对象却缺+0x10方法时返回`-0x31ee`。不能由NULL路径推断车机允许未加密媒体。

## 11.4 第二调用者的差异

`f_251b80e54.s`不是“另一种元素交错格式”：它直接调用同一Compose函数。

| 项 | 主路径 | 转码路径 |
|---|---|---|
| 输入PT字段 | 格式映射结果 | `0x251b818d0`/`0x251b818d4`固定0x60 |
| h | 后处理对象槽+8或0 | 同接口槽+8或0，`0x251b81480`–`0x251b8148c` |
| 第5/6参数 | lengthOut / NULL | `[sp+0xc4]` / `[sp+0xc0]`，后者接子包计数 |
| 后处理 | 在主函数内直接计算范围并调用虚方法 | helper分别处理合并消息和单包消息 |
| 向下交付 | 异步callback中的接口槽+0x30 | 环/队列对象，子包计数一并保存 |

转码路径在`0x251b81a1c`取合并消息总长T，然后给helper传`bodyLength=T-h-10`、`prefixLength=lengthOut-10=g`。另一次调用传当前单包音频长度和prefixLength=0（`0x251b81a48`–`0x251b81a5c`）。正常路径下两次都仅处理音频数据、不包含元素区。

`0x251b81aec`把Compose的countOut作为第4参交给`0x251a6f7c0`；后者将它存入环槽数组（`0x251a6f90c`），更新序号并调用外部队列接口，不是已证网络发送终点。主路径callback在`0x2519c2594`调用接口槽+0x30，实参是映射后的类型和音频消息对象。两个接口的最终网络适配/分支选择仍需追踪（`OPEN-RTP-11`、`OPEN-RTP-10`）。

## 11.5 接收计数与几何闭合

ReadNewMessage从offset0取消息数据并复制到I+2（`0x2519c0d24`–`0x2519c0d44`），再写PT到I+1。它用CMBlockBufferGetDataLength总长T写内部结束坐标`L=T+2`（`0x2519c0d54`–`0x2519c0d60`）。因此完整连续消息的`L-12=T-10`，正是除10B消息头后的范围；不是固件中互相矛盾的两字节差。网络输入如何得到消息M仍属`OPEN-RTP-8`的外层缺口。

计数路径：`0x2519c0d70`令w21=1；每个高位1的4B元素令w21加1（`0x2519c0db4`）；遇高位0的1B终止元素直接跳`0x2519c0df0`存C。正常终止时：

```text
C=n+1
4C-3=4(n+1)-3=4n+1=g
解密起点 I+12+g 对应消息 M+10+g
解密输入长度 L-12-g = T-10-g
```

这关闭`OPEN-RTP-14`原本关于C来源与减3的疑问。正常终止且计数上限未触发是必要前提；超过上限可走日志/错误路径或存C=0，不能将公式当作损坏输入的安全验证。无元素分支也存C=1，但不会应用4C−3。

## 11.6 验证及剩余

`reference-impl/verify_audio_message.py`核对新增9份切片、原镜像哈希、反汇编、关键指令与API范围/计数案例；外部CMBlockBuffer调用只按已命名的API契约建模，不执行固件或密码库。尚缺外层网络帧/分片、多段消息实际处理、provider算法、调度背压及真实车机闭环。音频8B AAD不能替代屏幕流的128B AAD取证（FairPlay `OPEN-10`）。
