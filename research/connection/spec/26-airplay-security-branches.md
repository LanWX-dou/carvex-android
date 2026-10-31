# 26 — AirPlay 安全能力：原属性来源、选择分支与手机端有界落地


## 1. 本轮新增结论

之前“只知道 selector 读了属性，还不知道属性怎样算”的缺口，本轮关闭了一部分：原固件的 `SupportsCoreUtilsPairingAndEncryption` 确实是 feature **38、46、43、48 的 OR**，不是仅38，也不是只要版本标签叫 AirPlay2 就支持。

另一个重要区别：**需要配对、采用哪种配对、是否还要独立认证、建立哪种 key holder 是不同决策**。当前 App 的 `PAIRED/SAP` 二分法不能代表苹果的完整选择器。不能把补齐能力位解释成已经实现这些密码学事务，更不能删除 SAP 或证书门槛来让状态变绿。

证据：[airplay-security-branches.json](../evidence/airplay-security-branches.json)。只读复核工具：[inspect_airplay_security_branches.py](../tools/inspect_airplay_security_branches.py)。本轮核对5个源镜像哈希、15个函数的原dyld字节与完整指令解码、9个dyld v5指针槽、5个直接跳板；语义范围以下表为准，不代表大型函数所有分支都解释完。

## 2. 原输入不是简单的一个64位 features

链条是 `AdvertiserInfo → copyFeaturesInternal → hasFeatureInternal → endpoint property → pairing/authentication selector`。

| 原函数 | 已核实分支 | 缺失／错误行为和边界 |
|---|---|---|
| `0x251999fec copyFeaturesInternal` | 首先复制 advertiser 的 `FeaturesEx`；存在时复制特征对象。若版本不满足内部阈值`0x1e9998`，清 feature7/0 | 阈值保留原内部值，不擅自转换成版本字符串。没有FeaturesEx时另走CompressionTypes/EncryptionTypes旧表示转换，不等于得到空集合 |
| 同函数的旧表示分支 | compression非零设置9，bit0/1/2/3分别设置18/19/20/21；encryption bit1/4/0分别设置23/26/22 | 属性读取失败、分配失败可返回错误；没有适用编解码或加密位时另有清集合分支，不能把输入的原数值直接当feature mask |
| `0x25199a4fc hasFeatureInternal` | 成功取得特征对象后调用`APSFeaturesHasFeature` | 复制失败时记录错误并返回false。这是这个已经组装过原输入的局部行为，不授权Android把“没发现TXT”一律当无能力 |
| `0x226f078a0 APSFeaturesHasFeature` | 以bit号索引变长byte buffer | null、超出长度、无数据返回false；不是固定64位掩码，feature80确实能表示 |
| `0x226f0776c` | endpoint-info扩展表示存在时解析扩展字符串；缺失时用legacy flags | 扩展表示畸形会失败，不自动退到legacy；本章未完成扩展字符串全schema |

指针解码已确认 `0x2680fbae8→_kAPAdvertiserInfoProperty_FeaturesEx`、`0x2680fbaa0→CompressionTypes`、`0x2680fbae0→EncryptionTypes`。不是按相似字段名猜出的结论。TXT/4301到每一种advertiser输入的全链条仍未闭合，不能把当前App的ULong称作整个FeaturesEx。

## 3. 属性生产者与真假分支

大分派函数`0x25199a588`只审下列安全相关分支；不声明全函数所有属性已覆盖。下面F(n)是原特征对象中的feature，不是任何一条线上消息的参数ID。

| endpoint属性 | 原规则 | 证据 |
|---|---|---|
| SupportsCoreUtilsPairingAndEncryption | `F38 OR F46 OR F43 OR F48`，按这个顺序短路 | helper `0x2519bd6fc`全函数、汇编`0x2519bd714–760` |
| SupportsLegacyPairing | F27 | dispatcher C700–705与公共feature返回块 |
| SupportsHKPairingAndAccessControl | F46 | dispatcher C693–699 |
| SupportsSystemPairing | F43 | dispatcher C706–711 |
| SupportsUnifiedPairingAndMFi | F51 | dispatcher C770–776 |
| OneTimePairingRequired | SystemFlags bit9为1时true，否则false | `0x2519a3d44`；`0x2680fbba0`已解为SystemFlags，两个CFBoolean槽已解符号 |
| IsHKAccessControlEnabled | F46且SystemFlags bit10为1 | `0x2519a6020` |
| AccessControlType | 首先读显式AccessControlType；成功直接返回；失败后若AccessControlLevelHK为1/2，返回SystemFlags bit10，否则保留第一次getter结果 | `0x2519a3dc0`；缺property时整数getter返回0已追到`0x18be3f804`，不能把所有错误转换都宣称等价 |

`APAdvertiserInfoCopyProperty@0x24fd94564`在缺键时返回null，错误为`0xffffe5b9`；`CFObjectGetPropertyInt64Sync@0x18be3f804`在null结果时直接返回0，不去调用`CFGetInt64`。后者存在值时的所有CF转换/畸形类型仍独立待审。

## 4. AuthenticationType的优先级不是SETUP et

`copyAuthenticationType@0x2519ca804`全函数及汇编核查得到：

| 按顺序命中 | 返回内部AuthenticationType | Stage1已有factory证据 |
|---|---|---|
| F80 | `0x20` | MFiMutualAuth |
| 否则F26或F51 | `8` | MFi |
| 否则F14 | `4` | FairPlay |
| 否则F23 | `1` | RSA或Token条件分派 |
| 否则F31 | `0x10` | Token |
| 以上全无 | 错误`0xfffee7b6`，不输出成功类型 | 不能补0或跳过认证 |

这张表是原端点属性产生规则；后续Stage1仍可能因统一配对等状态不再做**独立**认证。不得由“无需独立auth-setup”推出“无需验证MFi”。Stage1 factory的局部审阅见[20](20-airplay-session.md)。本轮没有将以上内部值填入SETUP `et`。

## 5. 无配对分支、kind5身份和当前能力范围

`ensurePaired@0x251a5e858`入口会先检查broker条件与CU能力的一致性。其no-pair局部条件是：CU/Legacy/OneTime/Unified都为false，AccessControlType不为2，session `+0x160`未置位，而且kind不属于7/8/9，才可以在该步骤直接返回0。`+0x160`完整producer及所有broker策略仍OPEN，不能强填false以复刻no-pair。

`createPairingClient@0x251a60f70`还有重要的kind5限定：

- CU为false时创建legacy client并消费PeerPublicKey。
- CU为true且`kind!=5 && SystemPairing=true`，才选CUSystemIdentifier。
- CU为true且kind5，使用CUAirPlayIdentifier，即使SystemPairing为true。
- CU client创建还消费AuthenticationType，并把类型`0x20`作为额外条件；所以“支持CU”不等于当前HomeKit.kt的一条固定事务足够。

当前手机HomeKit只实现已有setup/verify事务；原CU Setup/Verify中的条件MFiCertificate验证、系统/临时配对上下文、统一MFi transcript与SAP签名合同未在本批补齐。现有`startReady`入口总是选择PAIRED，但仍检查bootstrap认证、网络和端点；它是当前受限实现，不是原固件所有分支等价证明。

## 6. 本批已接入手机代码

手机文件位于`D:/carvex-research/android/protocol-carplay/src/`：

- 新增`main/java/io/github/iamr0s/carvex/carplay/core/AirPlaySecurityCapabilities.kt`：保留未知/false/true，按原规则表达CU/legacy/HK/system/transient/unified能力；提供不包含身份、密钥或任意TXT原文的诊断摘要。明确只接受现有低64位视图，不假装支持feature80。
- 修改`SecurityRouting.kt`：discovery入口若F38不存在、但F43/F46/F48任一存在，明确返回本地`PAIRING_MECHANISM_UNSUPPORTED`，不再误归SAP，也不自动开放当前HomeKit路径。该reason不是线上错误码。
- F38存在时保留原capability gate；未知掩码仍是`SECURITY_INPUT_MISSING`。startReady、等待4301、现有verify上下文及绑定检查的优先级不变。已有音频和版本声明不变。
- 修正`AirPlayFeatures.kt`两处不符实现的注释：未知能力不授权认证降级；features字符串按十六进制解析而非猜十进制。未重构世代日志行为。

| 输入（已通过绑定检查） | 本批行为 |
|---|---|
| discovery、features未知 | 输入缺失，未选路线 |
| discovery、F38=0且F43/F46/F48任一=1 | 明确未实现的CU入口，不返回任何认证action |
| discovery、F38=1，gate未知 | 策略未决 |
| discovery、F38=1，gate真/假 | 保留现有PAIRED/SAP；假gate语义仍是本地受限策略，不称苹果等价 |
| discovery、上述CU位全无 | 保留既有SAP选择，执行层仍受SAP schema/trust门槛约束 |
| startReady | 保留现有认证/网络/端点前置，选择PAIRED；不因上述新模型自动扩张或替换身份 |

新增6项能力模型测试和4项安全路由测试；覆盖全部16种CU组合、所有低64位单bit、unknown/zero、gate/record矩阵、绑定/源检查优先级与startReady边界。这里是本地单测向量，不是原ARM执行或线上握手。实际测试执行结果以本批总报告为准。

## 7. 还需要补什么，不能用“门槛已删除”代替

1. `4301 mutualAuth`到实际advertiser/AuthenticationType的完整producer链；APTransport helper条件设F26的手机/车机角色尚需证据，不能直接令mutualAuth=true等于F80。
2. Bonjour/endpoint-info扩展特征编码与来源优先级，至少包含F80和畸形值处理。
3. 每种选中CU/HK/system/transient路线的完整事务、peer-store提交、证书链/签名验证、取消与恢复；不能靠改OR掩码实现。
4. SAP实际签名schema与信任材料；formal门槛仍保留。当前`mfi`序列化槽存在不等于已经完成auth-setup。
5. iAP2上游AA trust、AA06和认证继承全链条仍独立OPEN。蓝牙bond、iAP2 AA、AirPlay pairing不是同一认证。

本章关闭的是有界属性计算与一处错误路线分类；不把整个AirPlay安全阶段改成完成，不宣称某车型因此能连接。

## 8. 复核命令

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_airplay_security_branches.py --verify D:\carvex-research\research\connection\evidence\airplay-security-branches.json
```

本轮实际输出PASS。验证不会修改固件或缓存，不执行原认证函数，不接触设备或网络。
