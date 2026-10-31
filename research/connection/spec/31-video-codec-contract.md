# 31 — 视频配置、帧附件与密码对象：有界合同

基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`PARTIAL`。本章补充 [30 视频主线](30-video-first-frame.md) 的 V-OPEN-01/04/05，不宣称已经恢复全部编码器、全部 codec 或接收端合同。证据索引为 [video-codec-evidence.json](../evidence/video-codec-evidence.json)。

本轮重新比对了 11 份原函数切片、当前提取 Mach-O 和原共享缓存；重新解析指定 CFString、Objective-C selector、密码虚表和跳板。还重跑只读 C10/C11 检查，其中部分样例是 Python 本地逻辑模型，不是执行苹果编码器。没有运行密码原语、建立网络、生成真实视频样本或做车机显示测试。

## 1. 已新增闭合的事实

1. `avc1` 且特定模式位为零时，格式描述的 `SampleDescriptionExtensionAtoms` 内 `avcC` CFData 被缓存；缓存变化可触发独立 type=1 配置正文。不是仅发现了字符串。
2. 帧头 `+0x05.bit7` 来自 `APInterestingFrame == kCFBooleanTrue`；`bit4` 来自第一个合法 CFBoolean `NotSync` 的反值。二者均不能替代 NAL/随机访问帧证据。
3. 完整 128 字节帧头作为现代 ChaCha 路径的 AAD；密码虚表已直接绑定到已审 encrypt/overhead 函数，不再只靠旧索引名称。
4. 新 ChaCha 对象的 `0x118` 字节存储经零填充；计数器位于 `+0x110`，构造函数没有覆盖它，所以该新对象初始计数器为零。每次成功走到加密尾部按小端递增 8 字节，不等同每条视频记录仅递增一次。
5. legacy 屏幕构造分支的直接跳板确实指向 `APSCryptorCTRCreate`；完整 legacy key/IV 来源、CTR 参数与失败生命周期仍未闭合。
6. 另一个 AVConference/UDP 包装器中的 `1.0`、`30.0`、`5` 已解析为 RTCP interval/timeout 和 SRTP/SRTCP cipher-suite 参数，不能误写成视频 FPS、GOP 或关键帧间隔。

## 2. 显示描述到内部参数：能确认什么

### 2.1 显示对象不等于线上字段已经完整验证

`APEndpointDisplayDescriptionCreateWithDisplayInfo @ 0x251a9baf0` 要求非空输出指针、非空输入且输入是 CFDictionary，随后保存该字典。它没有在构造时逐项校验所有显示字段。因此：对象创建成功不证明像素、物理尺寸、UUID、帧率等每项都已经满足后续消费者；也不能把内部属性名直接写成线上键名。[VC-D01]

`screenstream_initDisplayInfo @ 0x251b443cc` 后续分别读取 EDID、PixelSize、PhysicalSize、UUID 等属性，部分读取返回非零会走错误出口。这里的“属性读取成功”与“原始响应中一定存在同名字节键”仍须通过属性 getter 闭合，不能合并。[VC-D02]

### 2.2 MaxFPS 是条件上限，不是无条件最终帧率

已核对 `0x251b44a50–0x251b44a74`：只有 MaxFPS 对象存在、整数转换结果至少为 1、且低于当前内部帧率 `storage+0x1d0` 时才写入该结果。缺失、非正值或更大值均不由此处提高当前帧率。其默认值来自先前状态，不应在文档中填一个猜测值。

该函数的部分尺寸修整只在 `IsCarPlay` 对应内部标志 `+0x183==0` 时执行；不能把镜像通用路径的 1280/1920 等常量直接要求 CarPlay 使用。线上字段→属性 getter→选定 display→最终编码器的全链仍为 V-OPEN-01。

## 3. 配置记录合同：avcC 通路

| 九问 | 当前已证范围 |
|---|---|
| 进入状态 | 已有编码 sample、格式描述和 screen 数据生产上下文；此路径检查 subtype=`avc1`（`0x61766331`）且 `storage+0x3c8==0`。 |
| 发起方/承载 | 手机发送端从 sample 取格式资料，在屏幕记录数据通道中生成 type=1；不是额外 RTSP 请求。 |
| 输入/输出 | `CMFormatDescriptionGetExtension(..., SampleDescriptionExtensionAtoms)`；字典分支取 `avcC`，另有数组取首项分支；结果须为 CFData，进入 codec 缓存。 |
| 类型/来源/缺省 | 配置正文为上述 CFData 内容，不是任意 SPS/PPS 拼接；无缓存时构造器存在格式描述序列化备用路径，该路径的 wire schema 未闭合，不填空 avcC 替代。 |
| 固定/动态 | 记录头 128 字节、type=1 为此路径常量；正文长度、正文、几何、时间、标志动态。 |
| 接受/拒绝 | CFData 类型、缓存比较和配置构造返回码属于发送端本地检查；不是已恢复目标车机的接受规则。 |
| 真正成功 | 配置构造、放入 transport、实际网络写出、接收端接受分别取证；构造成功不算车机首帧。 |
| 重试/退出 | CFData 相等时不因这一条件重发；变化更新缓存并触发配置。尺寸变化等其它条件也可触发。异常路径不能默认为重发相同对象。 |
| 下一事件 | 本地 buffer 组装顺序为可选配置记录→帧头→帧载荷；是否已到网络需独立证据。 |

关键地址：`0x2519b04cc–0x2519b04fc` subtype/模式门；`0x2519b061c–0x2519b0660` 扩展/字典入口；`0x2519b0888–0x2519b0994` 数组、CFData 类型、比较与缓存；`0x2519b0e5c–0x2519b0e6c` 条件构造；`0x251b43ff8–0x251b44024` 从缓存创建正文；`0x2519b1178–0x2519b11bc` 组装顺序。[VC-C01/02、C11]

配置头字段补充（ARM64 此路径的小端原位存储）：

| 偏移 | 类型 | 来源/条件 |
|---|---|---|
| `0x00` | LE U32 | 正文长度，不含128字节头。 |
| `0x04` | U8 | 1。 |
| `0x05` | U8 | 配置 storage `+0x60` 的低字节；不能在未追上游时赋予全部 bit 语义。 |
| `0x06` | U8 | 基础 `0x12`；`+0x1bc!=0` 时先加1；cryptor存在 OR `0x04`；`+0x64!=0` OR `0x40`；格式描述对象存在 OR `0x08`。不是恒定 `0x16`。 |
| `0x07` | U8 | 1。 |
| `0x10,0x14` | LE float32 | 配置 storage 的 double `+0x10,+0x18` 经 FCVT。 |
| `0x20…0x2c` | 4个 LE float32 | double `+0x20…0x38` 经 FCVT。 |
| `0x30…0x3c` | 4个 LE float32 | double `+0x40…0x58` 经 FCVT。 |

头 `+0x18…0x1f` 不在上述几何写入组内；不能连续打包十个 float 覆盖这个间隔。几何完整坐标系/单位及 `+0x08` 时间生产者见30章，仍未全闭合。[VC-C02、C10]

## 4. 帧记录：同步附件不是码流证明

### 4.1 两个标志的精确局部规则

| 字段 | 读取链 | 缺失/类型规则 |
|---|---|---|
| `header[5] & 0x80` | sample 的 `APInterestingFrame` 附件与 `kCFBooleanTrue` 对象指针相等 | 其它值不由该条件置位；不是“首个NAL为IDR”。 |
| `header[5] & 0x10` | `CMSampleBufferGetSampleAttachmentsArray(sample,0)`；逐项调用 `FigCFDictionaryGetBooleanIfPresent(..., NotSync, &byte)`，遇第一个成功读取立即停止；最后取反 | 无/空数组置1；无合法CFBoolean则初始byte=0，最终置1；数字0/1不是CFBoolean。 |

`FigCFDictionaryGetBooleanIfPresent @ 0x18efac1c8` 返回的是“有合法布尔值”，不是布尔值本身：读取 `false` 后也返回1，所以 `[false,true]` 得 bit4=1，`[true,false]` 得 bit4=0。C11本轮重新核对了该函数、两个 ABI helper、6个直接跳板及对应导出名；341组本地样例仅检查上述算法，没有执行 CoreMedia。[VC-C01、C11]

协议实现不能依据 header bit4、type=0 或 `forceKeyFrame` 请求成功就宣布实际随机访问帧已生成。必须另核 codec 配置与实际 NAL/sample：本轮仍没有选定24A446会话的真实 SPS/PPS、NAL长度宽度、IDR/其它随机访问类型、profile/GOP样本。

### 4.2 正文长和可选尾段

帧头 `+0x00` 的 LE U32 是编码主载荷长度加所选 cryptor overhead；存在可选尾段时，再加尾段长度及该段自身 overhead。`+0x1c` 是尾段的相应总长度，缺尾段时为0。[VC-C01、C10]

主载荷与可选尾段可分别调用加密包装器，且使用同一帧头作为 AAD。因此“每条 type=0 记录消耗恰一个 nonce”不成立；本轮没有恢复尾段的完整生产者/schema，不能自行构造该扩展。

## 5. 现代屏幕密码路径的虚表和初始状态

### 5.1 分支与类型绑定

`apsession_setupStreamCreatingResponseInternal @ 0x2519bbf24` 的110/111分支在现代 key-holder 路径请求32字节输出材料，并以 flag=0 调 `0x258109690`。本轮直接读取跳板，它指向 `APSCryptorChaCha20Poly1305Create @ 0x226f2f54c`；另一分支 `0x25810d160` 指向 `APSCryptorCTRCreate @ 0x226e8d208`。[VC-S01、VC-P01]

原缓存 v5 指针绑定如下（不是线上字段，也不是运行时PAC执行）：

| 位置 | 解析结果 |
|---|---|
| ChaCha vtable `0x273d50040 + 0x08` | base-class wrapper `0x273d50058` |
| wrapper `+0x08` 原始 U64 | storage size=`0x118`；这是整数，不能当slide pointer解码。 |
| vtable `+0x10` | cryptor class `0x273d500b8` |
| cryptor class `+0x08` | `GetEncryptionOverheadLength @ 0x226e6772c` |
| cryptor class `+0x10` | `EncryptMessage @ 0x226e645f8` |

发送包装器 `0x2519b508c` 先调用 `CMBaseObjectGetVTable`，再取 vtable `+0x10` 的 class、class `+0x10` 方法，故这条间接调用已与上述 encrypt 目标绑定。[VC-P02]

### 5.2 初始 nonce、AAD 和附加输出

构造器经 `0x22818bff0 → CMDerivedObjectCreate @ 0x18ee2efdc` 创建对象。该函数在 `0x18ee2f0cc–0x18ee2f0dc` 取 wrapper size，把对象 `+0x20` 起的 derived storage 交给零填充函数（直接跳板 `0x1900cc250 → 0x18c3778e0`）。本轮核对了该零填充入口及覆盖 `0x118` 长度的存储循环。构造器随后仅写 storage 的 flag `+0` 与 retained key `+0x108`，未覆盖 `+0x110…+0x117`。[VC-K01/02、VC-P03]

因此可确认**新构造对象**的8字节计数器为0；不能据此在旧对象重用、恢复或部分写失败时擅自归零。

`EncryptMessage` 直接调用原 CoreUtils 的 `chacha20_poly1305_init_64x64`、`add_aad`、`encrypt`、`final`。头指针/完整头长传入 AAD；编码载荷输入和输出为同一指针。flag=0时附加16字节；flag!=0时附加24字节，后8字节是本次使用的计数材料。已审screen创建点使用flag=0，但不能外推所有流。[VC-K03/04、VC-P04]

计数从 `storage+0x110` 低字节开始进位；成功执行到尾部后递增。原循环没有在此处拒绝8字节回绕，但这不是允许应用重复 nonce 的实现建议。全失败出口、部分原地变更、后续 append 失败和资源清理仍需联动审计；**不能失败后重新加密同一对象再当作原包重发**。

配置记录构造器的本地路径不调用该帧加密包装器；与 frame cryptor 分开，不能给配置正文无条件加16字节tag。这里仅闭合该记录构造路径，不覆盖未审的其它codec/transport配置形式。

## 6. 编码参数的一个重要排除项：不要抄错路径

`APEndpointStreamScreenAVCWrapper::createVideoStreamConfig… @ 0x251a773c4` 属于已看到的 AVConference/ScreenUDP 包装器；尚未证明目标无线 CarPlay 的128字节记录路径实际使用此配置。因此下面是**局部参数来源**，不是车机必填值或全局默认值。[VC-E01]

| 已直接解析的 setter | 该调用点传值 | 能得出的结论 |
|---|---|---|
| `setVideoResolution:` | 12 | 内部枚举，不是12像素或线上codec ID。 |
| `setCustomWidth:` / `setCustomHeight:` | 前置宽高函数输出 | 动态值；宽高也存在本地 override 键。 |
| `setFramerate:` | screenOptions `+0x10` 非零时设置 | 不能从下述30.0推断帧率固定30。 |
| `setTxMaxBitrate:` / `setTxMinBitrate:` | 本地查询 `AVConferenceBasedMirroringMaxRate/MinRate`；调用传入fallback为40,000,000/5,000,000 | 值有本地配置来源；完整getter默认/单位及所选路径未全部闭合，不当成所有CarPlay固定码率。 |
| `setRtcpTimeOutEnabled:` | 1 | RTCP配置，不是编码开关。 |
| `setRtcpSendInterval:` | double 1.0 | RTCP interval；本轮未追下游单位。 |
| `setRtcpTimeOutInterval:` | double 30.0 | RTCP timeout，不是FPS/GOP。 |
| `setSRTPCipherSuite:` / `setSRTCPCipherSuite:` | 5 / 5 | 内部安全枚举，不是GOP=5或5秒关键帧。 |

setter名字由原 selector stub 的 ADRP+ADD 指向原字符串重新读取，而不是根据伪代码数字猜测。`setReceiveMasterKey:` / `setSendMasterKey:` 还分别取前一配置或当前options；本章不导出其内容，也不把这个SRTP上下文与type110的ChaCha对象混为一份密钥。

## 7. 对故障定位的直接影响

| 最后成功事件 | 下一检查 | 区分证据 |
|---|---|---|
| display字典对象创建 | 后续PixelSize/PhysicalSize/UUID/MaxFPS读取和选中屏幕 | 保存属性读取结果；不要把对象构造日志当能力全部有效。 |
| screen数据transport可用 | 配置是否产生且在帧前写出 | codec config长度/哈希、配置世代、网络实际写出顺序。 |
| frame标志bit4=1 | 实际样本是否可随机访问 | 使用对应codec配置解析真实NAL/样本；标志和forceKeyFrame请求仅是上游证据。 |
| 主帧加密完成 | append/网络写入是否成功，是否存在尾段 | 同一cryptor对象、调用次数、正文总长、旧新连接世代；不得记录密钥。 |
| 首次播放成功，重连黑屏 | 是否为新连接配置与新密码对象 | 新SETUP、连接ID、配置和关键帧、旧生产者停止；不能只看counter重新从0开始。 |

这些记录项属于 `LOCAL_DESIGN` 诊断方案。实际车机显示、持续更新与独立重连仍按30章P4–P6验收；中间层不可见就标未观察，不要求修改车机取证。

## 8. 未关闭项及边界

- **V-OPEN-01 部分推进**：显示对象的字典类型门和MaxFPS条件上限已核；线上字段到属性getter、屏幕资源许可、最终编码器的完整映射未闭合。
- **V-OPEN-04 部分推进**：avcC→type1正文和两个附件标志已闭合；NAL长度宽度/端序转换、SPS/PPS内容及重复、H.264/HEVC/profile/GOP/实际随机访问帧仍缺原生产者与样本证据。AVConference参数不能替代该缺口。
- **V-OPEN-05 部分推进**：现代cryptor虚表、直接导入、初始零计数、AAD/16字节附加输出链已核；legacy完整材料、所有异常/恢复/回绕策略、模式迁移仍未闭合。
- 没有新增24A446网络捕获、真实编码输出、车机接收/解码/显示或重连证据；本章不关闭G10–G12运行验收。

