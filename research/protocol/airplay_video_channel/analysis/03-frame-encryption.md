# 03 帧加密

> 本章描述24A446发送端包装器，不将内部对象布局当线上协议。原指令专项核验见 [06](06-wrapper-and-header-audit.md)。旧稿的“明文降级、独立密文缓冲、现代路径恒ChaCha、构造计数器即nonce”均撤回。

## 03.1 调用位置

`_screenstream_dequeueAndProcessSampleBuffer` 构造头后调用：

```text
0x2519b1150  ldur x1, [x29, #-0xa0]  ; headerBB
0x2519b1154  ldr  x0, [sp, #0x70]    ; processing storage
0x2519b1158  ldr  x19, [sp, #0x30]   ; payloadBB
0x2519b115c  mov  x2, x19
0x2519b1160  bl   #0x2519b508c       ; _sbpd_encryptBBuf
0x2519b1164  bl   #0x2519cf9e4       ; outlined helper，不是已证发送点
0x2519b1168  cbnz w0, #0x2519b1490   ; 错误分支
```

可选尾段存在时在 `0x2519b12f0` 用同一headerBB再调一次包装器，再将尾段追加到主载荷。
因此“一条记录一次加密”不是普遍规则。

## 03.2 包装器与输出

`_sbpd_encryptBBuf`（`0x2519b508c`）从storage+0x198读取cryptor；NULL时直接返回0，
本函数不修改载荷。这只证明局部no-op，不证明目标会话允许明文或认证失败可降级。

两次 `CMBlockBufferGetDataPointer` 分别取得头和载荷指针；载荷连续长度与总长不等时返回
`-0x4178`（`0x2519b5104..10c`、`0x2519b52c4`）。class+0x10虚方法在 `0x2519b51c0` 收到：

```text
(cryptor, headerPtr, headerLen,
 payloadPtr, payloadLen, payloadPtr, payloadLen,
 extraPtr, extraLen)
```

第4与第6参数指向同一载荷，属于**原地处理**。extraLen取storage+0x1a0，非零时另分配extraPtr。
成功后将extra包装成独立CMBlockBuffer，并追加到原payloadBB（`0x2519b51fc`、`0x2519b5214`）。
extra不是完整密文buffer；其密码学含义须按具体cryptor确认，不从大小猜tag。
失败并不证明原地载荷与cryptor状态已回滚；失败对象不能直接当原明文重新加密。

## 03.3 构造计数不是密码nonce

`0x2519b11c8..1d0` 在记录拼装成功后将storage+0x470的u32加1；这早于后续对象构造，
不证明已发到socket或对端已收到。同函数 `0x2519b0844` 还有该字段清零。
不能要求它跨重连单调，不能据此设计nonce。不同密文不得复用同一key/nonce是实现安全要求；
nonce的生成与推进必须追cryptor，不能用这个计数器代替。

## 03.4 头与AAD的证据边界

本包装器确认头和载荷独立传参。相邻FairPlay专题的
[接收端原指令分析](../../airplay_fairplay_crypto/analysis/11-screen-aad-and-record-boundaries.md)
已证明其屏幕ChaCha分支以收到的完整128B头作AAD，N=LE32(H[0:4])是body读入长度，
E=LE32(H[28:32])可划分第二段；每个成功认证段分别推进nonce。

这不是所有profile的共同算法，也不独自证明本发送对象绑定的具体虚方法。发送侧的头构造、
实际cryptor选择和库调用状态仍须联合核验；不可把未知AAD、tag长度作为联网时随意试探的选项。

## 03.5 算法选择有条件

不再从 `NetTransportChaCha20Poly1305` 类名推断媒体算法或12B nonce。
[已核分派](../../airplay_fairplay_crypto/analysis/14-cryptor-gates-and-output-slots.md)证明：
type110/111在取得keyholder等前提下，内部属性 `SupportsCoreUtilsPairingAndEncryption`
为0时创建CTR，为非0时创建ChaCha（构造flag=0）。属性的线上来源、flag使用语义及与目标车机
profile的绑定仍需追；该属性不是允许客户端随意切换的线上参数。

## 03.6 派生参数

`coreUtilsKeyHolder_CreateEncryptionKeysForStream`（`0x2519bfecc`）ABI为：

```text
(holder, integerID, inputLength, inputOutCFData, outputLength, outputOutCFData)
```

`ASPrintF`按 `%s%llu` 拼接 `DataStream-Salt` 与传入整数的十进制表示，返回普通分配C缓冲
及字符长度，不是CFString。整数来源不能假设为首流0/1。两次派生：

| 参数 | Input调用bff40 | Output调用bff68 |
|---|---|---|
| info地址 | `0x251bdf658` | `0x251bdf6a9` |
| info原字节 | `DataStream-Input-Encryption-Key` | `DataStream-Output-Encryption-Key` |
| infoLen | 31，不含NUL | 32，不含NUL |
| requested output length | 入参x2保存值 | 入参x4保存值 |
| 输出 | 入参x3指向的CFData槽 | 入参x5指向的CFData槽 |

`CreateDerivedKey`（`0x2519bffc8`）按requested length建立可变CFData，取得mutable bytes，
再以 `(provider, salt, saltLen, info, infoLen, outputLen, outputBytes)` 调provider class+8。
旧稿把 `CFDataCreateMutable/SetLength/GetMutableBytePtr` 错写成“将标签转C串”。

采用CoreUtils pairing provider时，其HKDF-SHA512输入门见
[control analysis15](../../airplay_control_plane/analysis/15-keyholder-role-and-hkdf.md)。
该调用不证明每条媒体流都再派生Control/Events键；那是不同context接口。

## 03.7 Legacy路径与剩余缺口

Legacy不是只有符号线索：相邻专题已核
[Sender KDF直接实现](../../airplay_fairplay_crypto/analysis/15-sender-kdf-positive-evidence.md)，
使用 `SHA512(name || masterKey16)[:16]` 派生屏幕AES材料。不要套用CoreUtils标签/HKDF。

`OPEN-VID-5` 保留目标profile、发送wrapper→cryptor绑定、nonce与附加输出布局、跨段状态和真实互通；
不再把31/32语义或接收端AAD来源列作全未知。代码静态闭合不等于车机已接受。

## 03.8 实现影响

先确定并验证profile，再绑定具体算法/KDF/记录格式；将构造计数与密码状态分离。
可在离线mock中验证原地输出、附加尾段及失败分支，但不得把mock无cryptor路径作为联网明文方案。
实现证据索引为 `A03.1`–`A03.7`，专项补充为 `A06.1`–`A06.5`。
