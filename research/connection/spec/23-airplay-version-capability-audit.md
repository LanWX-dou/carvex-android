# 23. AirPlay 版本与能力声明：当前 App 一致性审计

后续说明：本章及关联JSON保留修改前审计快照；4301来源保存、请求头和诊断的后续实现见[63](63-alignment-batch1.md)。安全路线覆盖缺口与完整24A446身份迁移仍未完成。

## 1. 结论与范围

当前 App **不是根据“AirPlay 1/2”标签切换两套完整 iPhone 实现**。版本标签基本只用于日志；真正的安全路线由 bootstrap 状态、所选 endpoint 的来源、`features` bit 38 和本地能力门槛决定。若把日志中的 “AirPlay 2” 理解为完整实现了相应认证、协商和媒体能力，会高估当前覆盖范围。


优先级表示后续实现/取证顺序，不表示已确认某辆车连接失败的根因：

| ID | 优先级 | 已确认事项 | 实际影响与边界 |
|---|---|---|---|
| AVC-01 | P1：功能覆盖 | formal 模式及没有 shared secret 的路径会被显式 SAP schema gate 阻断 | 到达该位置后不能继续 authenticated/SETUP；这是 fail-closed 边界，不能删检查冒充实现 |
| AVC-02 | P1：继续取证 | 4301 srcVer/sdkVer 未进入 WifiBootstrap；mutualAuth 只记录；featuresEx 无接收状态字段 | 当前模型不足以证明等价于 iPhone 的能力汇合；尚不能证明每项都必需或一项即可解释特定车辆失败 |
| AVC-03/04 | P2：诊断准确性 | 世代判断把任意非空版本标识、未绑定 peer 的服务线索等当分类依据 | 能产生误导日志；本次未发现这些标签直接改变认证路线 |
| AVC-05 | P2：诊断准确性 | “/info wins from here” 没有对应版本状态更新/安全重选 | 日志不能当成能力已重新协商的证据 |
| AVC-06 | P2：解析合同 | features 注释声称支持十进制，实际无前缀值仍按十六进制解析 | 若输入真是十进制会改变能力位；目标线值是否允许十进制仍需证据 |
| AVC-07 | P2：声明一致性 | 本地 sourceVersion/build 是兼容组合，不是24A446的完整身份 | 改成 iPhone 版本字符串不等于补齐协议实现 |

机器可读证据：[airplay-version-capability-evidence.json](../evidence/airplay-version-capability-evidence.json)。安全分层见[20章](20-airplay-session.md)，4301 与 advertiser 汇合见[21章](21-endpoint-fusion.md)。

## 2. 先分清不同“版本/能力”命名空间

| 输入或声明 | 当前来源及消费 | 能否据此断言实现世代 |
|---|---|---|
| 对端 TXT `protovers` | ReceiverDiscovery:116–117 → metadata.protocolVersion → generation 日志 | 不能；不进入 SecurityInputs |
| 对端 TXT `srcvers` | 同上 → metadata.sourceVersion；estimate 函数不读取它 | 不能；保留、打印并不等于按其实现差异 |
| 对端 `/info protocolVersion/sourceVersion` | 初始 SETUP 后取值；核对日志 | 不能；没有回写 metadata 或重新选择安全路线 |
| 4301 `srcVer/sdkVer` | [21章](21-endpoint-fusion.md)确认参数5/6为对端字符串；当前 wifiConfig 不读取 | 不存在有效默认映射；不是被默认成320.17，而是未纳入结果对象 |
| 本端 `sourceVersion`、`User-Agent`、`_carplay-ctrl srcvers` | 本地常量320.17；User-Agent派生为AirPlay/320.17 | 本端声明，不是对端探测值 |
| `controlVersion` | BootstrapAuthentication → SecurityInputs；限制为1..2 | 是协商控制会话版本，不是 TXT protovers 或 HTTP 协议版本 |
| `X-Apple-ProtocolVersion` | 请求头；此处 /info 写入1 | 与上述版本字符串是不同命名空间；完整请求头一致性见[62章](62-version-capability-audit.md) |

同名 `features` 也不能合并理解：

- Bonjour TXT：字符串解析为64位掩码。
- `/info`：当前只接受 plist 解码后的 `Number`，转为64位掩码；字符串/数组形态在此会成为未知。本章未证明这些形态在目标车上都有效。
- 本端初始 SETUP：写的是 `emptyList<Any>()`，即数组，不是上述掩码。
- Apple 内部 `FeaturesEx`：是 advertiser/property 层对象；与 TXT `featuresEx/fex` 的解析和转换关系需要单独证明，不能只按名字直接赋值。

因此，既不能因 SETUP 的 features 数组为空就断言“没有宣告 bit38”，也不能把收到的整型掩码塞进同名数组字段当修复。[AVC-A02/03/08；AVC-F05]

## 3. 当前实际安全选择

### 3.1 决策链

当前生产源码的主要链路是：

```text
Bonjour metadata + BootstrapAuthentication / StartSession snapshot
  → WifiBootstrap.securityInputs(...)
  → SecurityRouter.route(...)
  → PAIRED：setup或verify（记录只影响这一步）
    SAP：本处不查pair记录
  → formal或shared缺失：SAP schema/trust门槛
  → authenticated → 初始SETUP → /info → 后续能力消费
```

AirPlayGenerations.estimate 在这条链之前/之后生成日志，**其返回值不传入 SecurityRouter**。`PairStrategies.order(generation)` 始终返回空列表；不能把这个兼容接口误读为已有按世代自动尝试认证的实现。[AVC-A01:128–133；AVC-A03:430–443]

### 3.2 route 的有界真值表

以下各行均假设当前 binding/epoch、identity conflict、controlVersion 等前置检查已经通过：

| 条件 | 当前结果 |
|---|---|
| verifyContext存在且绑定匹配 | CONTINUE_VERIFY；但本 AirSession 调用者将其与WAIT一并拒绝 |
| startReady=true，bootstrap认证/网络/端点门槛通过 | PAIRED；此分支不再检查features bit38或版本字符串 |
| startReady=false 且 endpointSource=IAP_START | WAIT_START_PARAMETERS |
| discovery入口但features未知 | SECURITY_INPUT_MISSING，不是自动选择低版本 |
| discovery入口，features已知且bit38为0 | SAP |
| discovery入口，bit38为1且pairedCapabilityGate缺失 | SECURITY_POLICY_UNRESOLVED |
| discovery入口，bit38为1且gate=true/false | 分别PAIRED/SAP |

[AVC-A05:47–64；AVC-A03:482–483]

当前实验性 discovery gate 还要求：明确启用实验、蓝牙/Wi-Fi、没有 startSessionReady、当前网络/端点有效、generation/epoch 匹配、challengeSignatureVerified、bit38、有效 pi/pk、地址/端口及规范化 device ID 匹配。它是**本地实验配置和上下文检查**，不是从 `protovers` 推导出的 Apple 标准选择器。[AVC-A04:35–52]

注意：

1. bit46足以把 generation 日志标成V2，但实际 discovery route 只查bit38。
2. startReady分支可以绕过“必须取得Bonjour features”的需求，但没有绕过认证/网络/端点前提。
3. AirPlayCapabilities 的“未知时保持两路可走”注释与这里的 fail-closed 路由不一致。应修正说明，不能据该注释添加失败后的认证降级。
4. 配对记录不决定SAP/PAIRED；路线先确定，随后记录才决定setup/verify。

### 3.3 最关键的执行边界

AirSession:487–490：

```kotlin
if (!options.experiment || shared == null) {
    SecurityRequirements.requireSapSignatureSchema()
    SecurityRequirements.requireSapTrust()
}
```

SecurityRequirements.requireSapSignatureSchema() 当前始终抛出 `SAP_SIGNATURE_SCHEMA_UNSUPPORTED`。因此，即使 formal PAIRED 分支已经完成 HomeKit.verify，这个条件仍为真；SAP分支也不能通过该位置。只有 `experiment=true && shared!=null` 才不进入此检查；之后仍可能因其他条件失败。

这不是“发现了可以删除的多余检查”。它明确表明当前 formal/SAP 执行材料与实现未闭合。InternalSecurityProfiles.productionReady=false，另列AA trust、SAP schema、SAP trust等阻断项；这些是覆盖范围说明，不是某次已发生认证失败的抓包证明。[AVC-A03:449–491；AVC-A05:92–124]

此外，所审 AirSession 的 mfi 成员初始为null，检索只见读取，不见赋值或实际 /auth-setup 调用。存在 `mfi?.let { et/ekey/eiv }` 的序列化代码不证明SAP握手已接通。[AVC-A03:94,504,1366]

## 4. 版本标签与服务线索的问题

AirPlayGenerations.estimate 的实际顺序为：[AVC-A01:100–124]

1. 若pairVerifyAvailable非null，则true→V2、false→V1；本轮在生产src中没有找到实际传入该字段的调用点。
2. bit38或bit46为true→V2。
3. 服务集合含 `_raop._tcp.`、`_hap._tcp.` → V2。
4. 含 `_carplay-ctrl._tcp.`、`_mfi-config._tcp.` 也→V2，虽然相邻注释说“仅实现线索，不当世代判据”。
5. protocolVersion=="1.0"→V1；随后**任意非null protocolVersion也→V1**，包括未知版本字符串。
6. 否则UNKNOWN；sourceVersion完全未参与函数计算。

这些是项目自己的启发式，不是从本章原函数证明出来的标准映射。尤其V1/V2的描述文字分别声称“/auth-setup only”和“HAP /pair-setup+/pair-verify”，比函数本身证明的内容更强。

ReceiverDiscovery 的 clue 服务浏览只记录类型“出现过”，不解析并匹配该服务的地址、身份或选中车机；API33+只限同一个Network，旧API为全局浏览。这个总集合被写入最终选中候选的 metadata.services。因此同网络其他设备的服务可能影响日志标签；它并不是注释所说的“这台车机的服务集合”。当前 route 不消费 services，故不能把此诊断问题直接升级为认证绕过或实车失败根因。[AVC-A02:34–36,60–75,116–117]

## 5. 4301、扩展能力与 /info 的数据断点

### 5.1 4301版本和mutualAuth

wifiConfig消费无线组、端口、receiver和公钥hint；参数5/6的srcVer/sdkVer没有读取。BootstrapEndpoint的metadata默认null，wifiConfig构造结果也未提供metadata。后续 `resolved(..., metadata)` 可以放入Bonjour元数据，但不是恢复4301丢失的版本来源。[AVC-A07:23–49,875–913]

参数8的mutualAuth：

- 存在且长度为1时读为U8；
- 长度不符时日志后忽略；
- 正常值也只进入“recorded; no platform action”日志，不存入WifiBootstrap，不传SecurityInputs。

原始IapFields仍可通过可选onCarPlayStartRequest回调交出。因此准确说法是“**内建连接状态没有保留/使用这些能力**”，不是“任何外部调用者都不可能拿到原始字节”。本轮全仓Kotlin引用检索仅找到API传递和测试，没有实际解析这些值的生产回调实现。

### 5.2 featuresEx与noPair

ReceiverMetadata没有featuresEx、mutualAuth或noPair字段；生产src中也未找到featuresEx/noPair消费链。这与[21章](21-endpoint-fusion.md)的Apple advertiser/property模型不同。

但本章原证据中的noPair是 `ensurePaired` 的分支结果，**没有证明它是一项必须读取的Bonjour TXT字段**。不能为“补齐字段”自行发明noPair线上参数。featuresEx不消费是否会导致某目标错误选路，也需先闭合其property producer映射。

### 5.3 /info并没有重新选择安全路线

在当前顺序里，初始SETUP成功后才GET /info。读取infoProtocol/infoSource/infoCapabilities之后仅打印版本及generation；没有回写metadata，也没有再次调用SecurityRouter。日志“/info wins from here”和“continuing on capability evidence”因而不能证明版本优先级切换已执行。[AVC-A03:517–556]

这个结论仅针对上述版本/features标签；紧接着的audioFormats、audioLatencies、displays确实有实际消费，不能说“/info全部没用”。多编码bit42也只是提示当前仍发H.264/AVCC，不是自动启用HEVC。[AVC-A03:543–565；另见31章]

## 6. features解析的精确边界

ReceiverIdentity.features：分成一段或low/high两段，去掉可选0x/0X后，**始终以radix=16解析**；两段各限制32位，最后low OR (high << 32)。缺键、解析失败或段数错误返回null。[AVC-A08:23–31]

AirPlayCapabilities.parse注释却声称支持十进制。[AVC-A01:76–77]

算术示例（不是捕获线值或Kotlin测试）：

| 输入字符串 | 若发送方意指十进制 | 当前解析 |
|---|---|---|
| `4294967296` | `0x100000000`，bit32=1、bit38=0 | `0x4294967296`，bit38也为1 |

这说明**解析基数若不一致会影响真实路由输入**，不只是日志。仍需证实目标TXT的合法编码；如果协议约定无前缀也为十六进制，那么应修注释/测试合同，而非自动猜测十进制。不能凭一段只含数字的字符串可靠猜出发送方基数。

## 7. 与24A446原函数的对照

本轮重新计算两份Mach-O及五份原函数raw/ASM/C的SHA-256，并将每份raw逐字节比对到原镜像VA；全部相等。此核验证明函数材料来自所列镜像，**不等于运行了原ARM函数或证明全部调用者语义**。

| 证据 | 原入口与已审分支 | 对当前App的约束 |
|---|---|---|
| AVC-F01 | AirPlaySender 0x251a5e858，ensurePaired；C78–167，ASM 0x251a5e890–0x251a5eb20 | 读取CU/legacy/one-time/unified/access-control等endpoint property，不能只凭“AirPlay2”日志声称等价 |
| AVC-F02 | AirPlaySender 0x251b5ce10；C29–64，ASM 0x251b5ce54–0x251b5cf20 | key holder 的CU/legacy选择读SupportsCoreUtilsPairingAndEncryption |
| AVC-F03 | AirPlaySender Stage1 0x2519c5858；ASM 0x2519c63d0–0x2519c66e0 | pairing之后还有独立AuthenticationType分派，部分状态跳过单独authentication也不代表无校验 |
| AVC-F04 | AirPlaySender 0x251a59708；C210–234 | 本基线SETUP producer的sourceVersion字面量为980.77.1.2 |
| AVC-F05 | APTransport 0x24fd9c6b8；C594–680 | helper构造FeaturesEx/AdvertiserInfo；mutual-auth provider为假时条件设置feature0x1a |

Stage1的认证factory分派见[20章](20-airplay-session.md)：4→FairPlay、8→MFi、0x20→MFiMutualAuth、0x10→Token、1→有条件RSA或Token；这些是**内部AuthenticationType枚举，不是SETUP et**。本章不把bit38→HomeKit这一简化规则宣判为所有车辆都错，而是指出它与原程序的选择维度尚未证明等价。

APTransport helper设置的FeaturesEx以及supportsMutualAuthentication完整provider/手机车机角色仍有OPEN，不能直接把内部helper规则当成每辆车的线上要求。[21章](21-endpoint-fusion.md)

## 8. 本端声明不是“复刻完成”

当前本端：

- sourceVersion=320.17，用于SETUP及控制服务TXT；User-Agent使用同一来源。
- osBuildVersion=21A329是兼容声明。
- model/osVersion来自Android设备，osName="Android"。

24A446在本章所审SETUP构造点使用980.77.1.2。两者不同是确定事实；“把320.17换成980.77.1.2即可兼容所有车”则没有证据。本地build注释还指出它影响接收端兼容行为，不能当纯装饰字段替换。[AVC-A06:1–19；AVC-A03:493–500,982；AVC-F04]

## 9. 后续验收与未闭合项

建议按以下顺序继续，不先改版本字符串：

1. 为每个来源保留值、缺失状态和来源标签：4301、Bonjour、/info、本地配置不能互相伪装；是否实际参与选择另记。
2. 闭合Apple endpoint property producer映射：哪些来自features、featuresEx、版本、4301或会话上下文，哪些为内部合成。由此确定手机端真正支持的安全子集。
3. 给当前选择器补可审计矩阵：startReady有/无、features未知/bit38/bit46、gate未知/真/假、formal/experiment、pair record状态；失败必须说明是能力未决、材料缺失还是对端拒绝。
4. 对版本日志做反例测试：未知protovers、仅bit46、同网其他设备的_raop、缺srcvers、Bonjour与/info冲突；预期不得宣称已切换实际未切换的实现。
5. 对features输入基数和类型按已验证schema测试；未知形态不猜测。
6. 最后用匹配当前源码的APK与实车抓包确认：实际选择的route、exchange、请求头、SETUP和首帧，而非只看“AirPlay 1/2”或车机阶段文字。

仍OPEN：4301版本/mutualAuth到Apple真实provider的完整链；featuresEx到认证属性的完整映射；noPair在其他路径中的含义；各车TXT可接受编码；本机APK与当前源码的一致性。本章没有完成这些项，也没有声称已修复车辆问题。

## 10. 当前源码定位

以下路径的SHA-256及完整原函数路径均在证据JSON中；行号仅适用于该文件hash。

| 证据 | 文件 | 本章主要范围 |
|---|---|---|
| AVC-A01 | [AirPlayFeatures.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/AirPlayFeatures.kt) | 55–77、81–133 |
| AVC-A02 | [ReceiverDiscovery.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/ReceiverDiscovery.kt) | 18–24、34–75、112–117 |
| AVC-A03 | [AirSession.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt) | 429–565、982 |
| AVC-A04 | [BootstrapSecurity.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/BootstrapSecurity.kt) | 11–52 |
| AVC-A05 | [SecurityRouting.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/SecurityRouting.kt) | 32–84、92–124 |
| AVC-A06 | [CarPlaySourceIdentity.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/CarPlaySourceIdentity.kt) | 1–19 |
| AVC-A07 | [Bootstrap.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt) | 18–52、692–725、875–913 |
| AVC-A08 | [ReceiverIdentity.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/ReceiverIdentity.kt) | 23–31 |
| AVC-A09 | [StartSessionFields.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/StartSessionFields.kt) | optional/text等访问器，不自动消费5/6 |
| AVC-A10 | [IapPeerProfile.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapPeerProfile.kt) | PeerVersion接口不证明生产路径实际赋值 |

