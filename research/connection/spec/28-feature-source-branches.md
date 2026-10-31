# 28 — Bonjour fex 的实际编码、能力长度与安全选路边界


## 1. 本轮纠正的关键点

**fex不是十六进制features的别名，也不能截成64位。** 原固件将它作为ASCII字符串解Base64，保留变长字节对象。Feature80位于第11字节最低位，随后参与AuthenticationType选择。只保留ULong会丢掉它，使后续选择错误。

**这里也不能直接换成Java标准Base64严格解码器。** 24A446的CoreUtils原函数允许若干非规范但可解码形式：无padding、最后一个孤立sextet、首个`=`后的任意ASCII后缀等。代码按本轮核实的原分支处理；不会把这些形式误判为坏数据后尝试旧能力。

## 2. 原字节证据与完整度

[证据快照](../evidence/feature-source-branches.json)与[只读工具](../tools/inspect_feature_source_branches.py)核对4个源镜像哈希、9个函数原dyld字节及完整指令解码、1段TXT调用点、2个CFString键、256字节Base64表、2个跳板。**完整解码不等于所有语义都已解释**：scope字段和下表限定了本轮审阅范围；没有执行原ARM函数，没有实车验证。

| 原位置 | CONFIRMED的本轮结论 |
|---|---|
| APTransport `AddAirPlayData`内`0x24fd97840–0x24fd97868` | 传入扩展键`fex`和旧键`features`；CFString原指针分别解到`0x275fa5380`和`0x275fa49c0`，不是猜字段名 |
| `0x24fd9ac78` TXT helper | 扩展getter仅返回missing-key错误`-0x1a47`时才尝试legacy；扩展字符串解析失败不走legacy |
| AirPlaySupport `0x226e67c0c` | CFString转换ASCII，`strlen`取得decoder长度，调用Base64DecodeCopy，建立CFData；失败保留错误 |
| CoreUtils `0x18be43ad0` / `0x18be447e0` | 前者分配并调用后者；后者完整循环、终止与尾组分支见下节 |
| `0x226f0776c` | endpoint-info扩展字符串非null时优先；错误不回退legacy；null才转legacy flags |
| `0x226f078a0` / `0x226f07bf4` | 变长bytes按低位优先索引；兼容legacy值只取前8字节，按little-endian组装 |
| AirPlaySender `0x2519ca804` | F80优先产出内部AuthenticationType `0x20`，然后才检查F26/F51、F14、F23、F31 |
| `0x251a60f70` CU client分支 | 读取AuthenticationType，并把成功且类型为`0x20`作为CU factory参数；没有“kind5即可忽略F80”的整体豁免 |

最后一项仍只是原CU创建条件，不代表Android现有HAP事务具备MFiMutualAuth。`startReady`是本地模型，不能拿它当原固件跳过认证类型的证据。

## 3. Base64容错范围

以下均来自`Base64Decode@0x18be447e0`及表`0x18bf710b0`；它不是RFC严格校验器。

| 输入分支 | 原行为及手机本批处理 |
|---|---|
| `A–Z/a–z/0–9` | 正常sextet |
| `+`与`-`；`/`与`_` | 分别都映射62、63；可混用 |
| ASCII `09 0A 0B 0C 0D 20` | 跳过；不扩大到Unicode whitespace |
| 首个`=` | 立即停止并按当前尾组输出；不检查其后ASCII字符 |
| 末尾剩0或1个sextet | 成功，不追加字节；因此`A`得到空集合，而不是malformed |
| 末尾剩2或3个sextet | 分别输出1或2字节；未使用的低位不要求为0；无需padding |
| 终止前出现其他ASCII字符 | 错误，不fallback到features |
| 字符串中有非ASCII | ASCII转换先失败，即使字符位于`=`之后 |
| 内嵌NUL | 原`strlen`使decoder输入在此终止；ASCII转换仍先处理整个字符串 |
| 空字符串 | 原decoder可返回成功的0长度bytes；与key缺失不同 |

手机另保留**本地资源限制**：扩展文本最多1024个字符，超限为`MALFORMED_LENGTH`；不是宣称苹果协议有该长度上限。Bonjour整条候选原有总属性大小限制仍在。原TXT getter所有CF类型转换、非法UTF-8如何变成CFString仍OPEN；Android将不能形成ASCII的文本保留为`UNSUPPORTED_ENCODING`，不放宽为缺失。

## 4. 已接入手机端，不只是文档

文件根：`D:/carvex-research/android/protocol-carplay/src/`。

- 新增`core/AirPlayFeatureSet.kt`：不可变bytes拷贝、任意非负bit查询、低64位兼容视图、source/problem证据。保留`MISSING / LEGACY_FLAGS / BONJOUR_FEX / ENDPOINT_INFO_FEATURES_EX`区分；后一种只提供解析API，不宣称已接入未追完的endpoint-info producer。
- `ReceiverDiscovery.kt`：真实读取TXT `fex`；仅缺键才解析`features`；空fex是有效空集合；malformed fex附在已选候选元数据上，不被默默丢弃后降级。仅日志输出来源、长度、错误类别，不输出任意TXT原文。
- `ReceiverMetadata`末尾增加`featureEvidence`，原positional构造仍兼容；`effectiveFeatureEvidence/effectiveFeatures`以显式证据为准，矛盾旧mask不覆盖它。
- `BootstrapSecurity.kt`：完整证据传到`SecurityInputs`，实验HAP gate也消费该来源。gate不授予MFi能力。
- `AirPlaySecurityCapabilities.kt`：保留原低64构造，增加证据参数与F80状态；不存在证据和格式错误不再等同“能力全false”。
- `SecurityRouting.kt`：新事务discovery中，malformed为本地`SECURITY_INPUT_MALFORMED`，missing仍是`SECURITY_INPUT_MISSING`；已知F80明确`PAIRING_MECHANISM_UNSUPPORTED`，不执行HAP/SAP。ready前置通过后也不能忽略已知malformed/F80。绑定/schema检查、已绑定verify continuation、尚未ready的iAP等待优先级保留。

这不新开启CU/HK/system/transient/MFi认证。F38政策和先前已有的其他低位机制范围仍按[26](26-airplay-security-branches.md)；本轮不是重新实现全部pairing selector。ready入口在没有TXT能力证据时仍保持旧有界行为，不宣称此行为已与苹果所有路径等价。

## 5. 合成测试和仍待完成的工作

新增17项JUnit方法已纳入主任务的完整回归，全部通过。完整917项及编译结果见[68](68-connection-mainline-batch5.md)：

- `AirPlayFeatureSetTest`的10项：跨63/64/80边界、全部低64保留、不可变拷贝、标准/URL-safe混用、6种ASCII空白、实际原decoder尾组/终止容错、missing/malformed/empty分离、不fallback、本地长度限制。
- `ExtendedFeatureSecurityRoutingTest`的4项：F80和低位优先关系、显式证据压过矛盾mask、malformed/缺失区分、binding/continuation/ready边界。
- `ReceiverFeatureEvidenceTest`的3项：旧构造兼容、metadata→bootstrap完整F80、malformed贯穿到实际router。

原字节核验命令（本轮已PASS）：

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_feature_source_branches.py --verify D:\carvex-research\research\connection\evidence\feature-source-branches.json
```

**仍OPEN**：完整endpoint-info/4301所有来源的覆盖顺序与角色；原TXT getter全部畸形类型转换；真正的CU/HK/system/transient/MFiMutualAuth事务、证书信任与peer-store提交；实车首次连接/重连。本章不能据此宣布“所有车型无需适配”或“AirPlay认证已复刻”。
