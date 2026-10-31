
历史快照说明：本章之后用户批准了[81的手机端实现](81-identification-components-message-batch.md)。本章正文、证据哈希和18项探针预期保留为修改前状态；不能用旧探针对修改后源码作一致性证明。原核验工具遇到变化的手机源码会报哈希不匹配，这是历史基线变化，不应覆盖旧哈希来掩盖。本批当前源码与测试证据以81为准。


承接[79](79-iap2-renegotiation-batch.md)后的实际源码，而不是把[14](14-iap2-version-capability-audit.md)/[16](16-identification-lifecycle-branches.md)的旧问题全部重复列为未修。范围是当前control link进入Identification直到网络交接资格；不重新展开SYN、XPC、电源插件、AirPlay密码流程。

## 1. 本轮结论

2. **我们的接受合同仍不完整。** 核心字段已校验，但8/9、承载组件及完整feature/消息组合仍deferred。尤其“6中有4301或5703”只是本地无线启动限制，不是固件完整的CarPlay能力判据。

`1D01`是**车机发给手机**的身份和能力，不是手机往外伪装的iPhone字段。0–5为车机身份/版本，6为车机可发、7为车机可收。手机随后发送的4E09设备名、4E0E标识等是另一组消息，不可混成一份Identification模板。

## 2. 差异 → 触发条件 → 固件分支 → 建议


|---|---|---|---|
| ID-01：控制会话v1/v2 | `IapStartupPolicy.kt:19`与`Bootstrap.kt:300`按v1 AUTH_FIRST、v2 IDENT_FIRST；不支持的schema拒绝 | `iap2/Iap2SenderSession.kt:207`固定1D00→1D01→1D02→AA00；`VirtualIap2Link.kt:497/577`也先识别。默认本地control v2，但采纳对端表后此层不按其version改次序 | `sessionControl_start@10011d310`取session version；`10011d3cc`比较**恰为2**，启动feature1，否则feature0。对已支持的1/2我们匹配；不推导任意高版本可用。**保留** |
| ID-03：缺8/9、17/24坏值或组件不匹配实际承载 | raw保留且日志deferred；未计为成功，但也未阻止1D02，required仅核心子集 | BT接受流程未做这些校验；画像主要读取0/1/2/6/7 | required完整集合含8/9；`10013b920` raw kind2/3要求17、kind4要求24。`1000500a8`解析组件并传播CarPlay flags。**优先补组件模型/实际上下文；不把active强制设成必填，也不固定未知power provider** |
| ID-04：单边4300/4301或5702/5703；另一WiFi组不完整 | `Bootstrap:494`只要6有4301或5703即可进入接受；之后`:397/401`不完整pair只skip。即“接受了但不启动这条路径” | 通常先接受；5702按画像决定，4300在`:363`直接提交，不做同等成对门槛 | `100050af4/100050c2c`区分全无、完整、部分声明；部分在Identification阶段拒绝。feature22先验5700/5701，失败不继续5702/5703；feature26验4300/4301。**补接受前的组合检查，不只补发送时if** |
| ID-05：6中既无4301也无5703 | 非runtime路径直接产生空body 1D03，仍等待纠正；runtime例外 | 不在接受前加该门；可能用旧网络/mDNS/邀请继续 | `isIdentifiedForCarPlay@10013c148`要求Ident6及有效info/feature-set，并读`info+80`组件派生标志；不是上述两个消息号OR。**将“身份可接受”“CarPlay能力”“本地可用交接路径”拆开**；不能只删门，制造无网络路径的假成功 |
| ID-06：稀疏清单缺57xx | 不发5702；未声明的普通入站5703也过不了启动期入站门 | wifiGen UNKNOWN仍发5702；合计≥10项且无57xx才NEW、跳过。某一侧明写57xx即可LEGACY，不要求双向成对 | `RequestAccessoryWiFiConfiguration@100170bb0`调用完整组检查，失败不构造5702；普通方向门还查AA2、Ident6、对应清单。**本原生路径没有清单长度或品牌兜底证据**。保留差异，下一阶段追平台网络入口，不能用经验阈值冒充固件 |
| ID-07：本机拒绝后纠正/迟到取消/局部更新 | [65](65-identification-lifecycle-batch2.md)已实施：同link RETRY_PENDING、原deadline不续、接受后1D05忽略、1D06只更新0–5；BT交接后与Runtime均消费 | BT run无本机1D03字段拒绝/纠正事务，等待中的非目标消息暂存；保活泵除4301外主要日志。虚拟链路用identified标记避免重复接受，未见对应1D05/1D06生命周期处理 | `10013bcc8`只收state1/3；`10013b540`成功后state3；`10013b28c`仅1/3取消；`100050934/0458/0744` state6局部更新、不重发1D02。**保留现有修复**。授权异步、全feature cleanup仍不等价 |
| ID-08：Identification完成但AA未完成 | ready还要求认证完成；实验模式验证本次challenge但不冒充Apple根信任 | BT `run:218–236`跳证书/签名验证、最终自报AA05；虚拟链路也没有等价验签合同 | `10011da74` Ident6且AA0启动AA；AA2才走authAndIDComplete。`10011d7e4`反方向对应。**不复制认证绕过**，挑战长度/可信继承另属AA专题 |

ID-04有一个不能忽略的副作用：只补4300/4301局部规则后就对所有未认识的声明ID统一拒绝，也不正确。原固件先让所有注册feature对消息记账，最后才查未归属ID；我们还未覆盖全部feature。必须记录“未实现的校验”，不能误当“苹果不支持该消息”。


实际调用链：`MainActivity.startConnectionNow:527` → `SessionController.startConnection:542` → BT client/server → 共用`bt/BtSession.kt:28`创建`Iap2SenderSession`。

- `TargetDevicePrefs`保存**目标已配对设备地址**；名字是UI快照，不是车型协议模板。影响连哪台设备，不决定1D01字段合同或auth/ident次序。
- `Iap2SenderSession.logIdentification`在可解析的接收清单存在时调用`ReceiverProfile.classify`；没有该清单时保留UNKNOWN。空/奇长列表在该私有提取器中均为null，因此“合法空清单”和“未知”也被合并了。
- `ReceiverProfile.classify:106–132`的WiFi规则实际是：有5703或5702→LEGACY；否则两方向集合**合计≥10**→NEW；否则UNKNOWN。不是注释某处写的“两份各≥10”，也不保证两份都存在。
- `linkGenerationOf:46`以DELPHI+AUDI+双清单合计1–9判CLASSIC_MIB3；当前`VirtualIap2Link`的marker协商两代走同一分支，不应把日志旧文案当作仍然禁用协商。
- `identityText`的品牌子串与`MfiLengthMemory`影响挑战尝试顺序/记忆，和WiFi代际是不同策略；不代表24A446按车型选择Identification版本。


## 4. 消息组合和网络就绪的边界

从原映像重新核对三组每条12字节的规则：

| 组 | 参数6：车机发送 | 参数7：车机接收 | 部分声明 |
|---|---|---|---|
| CarPlayConnectionRequest，feature26 | 4301 | 4300 | 本组失败，不标记feature26 |
| DeviceWiFiCredentialsSharing，feature22 | 5700 | 5701 | 失败并跳过下一WiFi组 |
| AccessoryWiFiCredentialsSharing，feature22 | 5703 | 5702 | 本组失败 |

全无表示没有请求该组，**不是本条Identification必然失败**；完整组可以参与feature建立，**不是网络已经连通**。接受、认证、平台availability、WiFi关联、端点发现是不同条件。feature26的`start_from_device`原表为NULL，因此不能把“1D02之后固定发4300”说成原生feature starter。



## 5. 本轮实际验证

- 直接从原Mach-O读取**24个完整函数**，按`LC_FUNCTION_STARTS`边界与已有bin缓存核对，保存重新解码指令。函数内分支地址不冒充函数起点。
- 重跑既有feature只读工具：**33个缓存切片匹配原映像、29项注册、3组消息表**。与前述24存在重叠，不能相加成57个独立函数或覆盖率。
- [复核器](../tools/verify_identification_comparison.py)实际通过：24个函数、2196条指令、15段表数据、30份来源/工具快照；文档完整性检查通过50份Markdown、42份JSON。它只验证完整性，不会重跑探针，也不会判断协议语义正确。18项“通过”是对当前行为观察正确，其中含已知缺口，不是18项苹果等价通过。

## 6. 下一批建议：先补承载和能力模型，不新增车型档位

建议按下面顺序做一个有界手机批次，生产修改仍需另行授权：

1. **解析并保存17/24组件**：组件ID/名称/可省active、BT地址、无线CarPlay flags、重复/冲突规则；绑到本次BT或runtime实际上下文，不能借对端自报改变真实承载。失败候选不发布半成功flags。
2. **拆开三个结果**：Identification合法性、CarPlay组件能力、当前可执行的网络交接方案。用这三个结果替代“6含4301或5703就够了”的混合判断；没有可执行网络路线仍明确失败/等待，不能伪造成功。
3. **前置feature22/26组合校验和准确拒绝**：覆盖全无/完整/单边/反向、第一WiFi组失败、同link纠正；不要先扩大到未完成的所有feature全局拒绝。8/9必需合同仍需真实provider上下文，不能因这一批完成而宣布全Identification完成。
4. **再查网络交接三条时间线**，针对稀疏声明差异定位平台可用性、旧网络、邀请与4301/5703晚到的原生分支。这个步骤比继续广泛追蓝牙XPC或凭品牌加补包更直接对应目前差异。

应保留：v1/v2次序、已有生命周期修复、认证安全门槛。应暂缓：无声明5702探测、清单长度阈值、品牌选择挑战档、未经证实的旧网络自动放行。CF等价、全feature、原异步授权/取消及实车互通仍OPEN；G4不升级为完成。
