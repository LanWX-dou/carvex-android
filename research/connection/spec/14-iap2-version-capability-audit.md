# 14 · iAP2 版本、能力与接受承诺审计

后续说明：本章及关联JSON保留修改前审计快照；用户授权后的手机端第一批修改和测试见[63](63-alignment-batch1.md)。其中版本支持与第二SYNACK已作有界处理，Identification等未完成项仍保留；不要用本章旧源码哈希断言当前代码未变。

状态：`BOUNDED_STATIC_AUDIT`。日期：2026-10-29。对象为当前 Android App 源码与 `24A446 / iPhone18,1 / accessoryd`，不是安装包或实机验证结果。


复刻目标是24A446有证据的行为；当前App只是被审计的过渡兼容实现，不能用其已有分支倒推苹果规范，也不能因其暂时能连接就把它作为目标实现。证据未闭合的profile生产与条件分支仍保留OPEN，不猜测所有iAP link version固定为1。

## 1. 证据范围与结论等级

本轮直接从原始 `accessoryd` 映射地址重读12个函数，与已有 `.bin` 逐字节核对，全部一致；重读12条 required 参数注册记录。源文件 SHA-256：`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

[证据 JSON][E] 保存源文件位置/哈希、函数虚拟地址/原文件偏移/原字节哈希、相邻汇编与可用反编译文件哈希、11份 Android 源码哈希、12条注册记录原字节。复查器见[只读脚本][T]。字节一致只能确认缓存来自该样本，不能自动确认所有反编译类型或完整行为。

- `CONFIRMED_STATIC`：当前源码可直接确定的条件、输出和后续处理不一致；未表示车辆已触发。
- `CONFIRMED_STATIC_BRANCH`：某个输入分支的提交不一致可直接确定，但对端实际是否会合法发送该组合仍待确认。
- `PARTIAL_CANDIDATE`：缺少消费路径已有证据，但功能协商前提、真实对端依赖和影响未闭合。
- P1/P2 是后续实现审查的优先级，不是漏洞等级或实车故障严重度结论。

## 2. 不要混为一谈的版本与能力

| 字段或事件 | 来源与方向 | 固件消费事实 | App 消费/发送事实 | 本轮结论 |
|---|---|---|---|---|
| SYN body 首字节 link version | 双方链路提议，最终选择需一致 | IV01独立解析；IV02根据本地工作版本与对端版本协商；IV03提交工作块 | 接收1–3，回复首份对端 link version，影响后续帧处理 | 本地 profile 生产链未全恢复，不能规定所有车都强制 v1 |
| type0 descriptor 第3字节 control version | SYN 中 control session 提议 | IV01与 link version 分离；IV04从会话信息 byte2取值 | 链路只检查大于0并回发；Bootstrap仅实现1/2 | IAV-01：承诺边界与实现边界不一致 |
| `1D01` 参数6/7消息集 | 配件 → 手机；6=配件可发，7=配件可收 | identification/feature 校验和后续认证分支消费 | 解析 BE16 列表；普通启动要求6含4301或5703 | 配件的声明不是手机自己的能力；不能颠倒方向 |
| `1D02` IdentificationAccepted | 手机 → 配件 | 校验成功且授权回调允许后才发送 | 当前 required ID出现、基础解析及局部CarPlay声明通过后发送 | IAV-02：接受条件弱于本固件样本 |
| link CMD `54/55` | 链路控制帧，不是CSM的`0x0054/0x0055`能力声明 | IV06非link1进入FSM事件9/10；IV07另有条件启动时间同步 | 接收入队，但两条已审查上层路径不消费其动作 | IAV-04仅候选；不能由link2/3直接推出所有时间同步前提已满足 |
| AA继承/AA00空pid0 | 手机侧认证策略，受control版本、能力和可信父连接约束 | IV05有独立分支 | App新做认证；请求serial主要由AA06声明决定 | 见§7；不建议伪造身份、跳过认证或照搬可信缓存捷径 |

link version 与 control version 是不同层；`link1 + control2` 不能仅因数字不同而判错。iAP2 identification 接受、AA信任、网络建立、AirPlay配对以及视频首帧也不能互相替代。

## 3. IAV-01 · P1 · 不支持的 control 版本先被回发/提交，之后才拒绝

状态：`CONFIRMED_STATIC`。

[IapLink 解析][A01] 仅要求 type0 唯一且 version>0（第196行）。第401–404行直接取对端control版本，>2只打印日志；第422行将其写入自己的SYN|ACK。最终第473行提交 `negotiatedControlSession`。但 [Bootstrap 第313行][A02] 才要求control版本属于1..2，[IapStartupPolicy][A03]也只有这两个CarPlay schema。

因此版本3..255能跨过链路响应和提交点，却不能进入后续控制会话。对端看到的是“已经选定此会话版本”，本地下一层才宣布不支持；它会把不支持版本表现为链路建立后失败，而不是明确的协商失败。

原固件证据：

- IV01 `0x100103230`：link版本与session描述符分开解析。
- IV04 `0x10011d4b8`：control版本来自session info byte2。
- IV02 `0x100035154`：`0x1000351f8..0x1000352cc` 比较本地工作块 `+0x168` 与对端版本，仅在本地大于对端时下调；另拷贝session表至 `+0x186`。
- IV03 `_iAP2LinkDeviceActionNotifyConnection@0x10003009c`：将工作块 `+0x168` 拷贝到active `+0x19a`，再更新当前版本并通知连接。

这些固件点支持“版本有独立协商与提交边界”，不证明所有iPhone的本地profile都等于1，也没有恢复出可直接抄写的完整control支持集合。

后续修复方向：把实际支持的control版本/schema纳入发SYN|ACK之前的准入或明确协商规则；不允许回发一个Bootstrap一定拒绝的版本。遇到未知版本不应静默假装支持，也不能在没有线协议依据时自行把它改成1。

拟议回归向量（未执行）：其余字段合法的link1 SYN，type0 id1/version3；对端用纯ACK确认本地当前PSN。当前静态路径为回复version3→提交→Bootstrap拒绝。预期合同是在线上承诺前完成支持判断；测试应同时检查“有没有发送”和“本地有没有提交”，不能只断言最终异常。

## 4. IAV-02 · P1 · `1D02` 接受条件缺少必需字段成功解析与承载检查

状态：`CONFIRMED_STATIC`。这是手机对配件身份/能力的接受差异，不是“手机应该伪造配件字段”。

[Bootstrap 第493行][A04] required列表为 `0,1,2,3,4,5,6,7,12,13`，只检查ID是否出现。第494行known也不含8/9，因此会把8/9记录成unregistered；但这不是本固件的注册事实。第509行调用 [IapIdentifyInfo][A05]，实际只解析0..5字符串和6/7消息列表，12/13仅保留raw bytes。第515行通过局部CarPlay消息判断后，第516行发送 `1D02`。这一路径没有对应的承载组件校验。

原固件证据：

- IV12 `0x10006a3e4` 读注册表。直接重读 `0x10021a810..0x10021a8e8` 的10条核心记录与 `0x10021f1a8 / 0x10021f1c0` 两条power记录，required集合为 **0–9、12、13**，不是0–7、12、13。
- IV08 `0x10013aed0` 只有注册回调返回bit0=1且该ID必需，才将其加入 `info+0x78` 成功集合。
- IV09 `0x10013bc5c` 检查成功集合成员，缺项添加拒绝并置 `info+0x90`；“字段出现”不等于“解析成功”。
- IV10 `0x10013b920` 按实际raw transport kind额外检查组件：kind2/3要求17，kind4要求24；不能把required=0理解为任何场景都可省。
- IV11 `0x100050dcc` 要求授权回调允许且validation结果为0，才尝试接受发送。详细字段/拒绝合同见[第12章][C12]。

拟议回归向量（未执行）：

1. 其余0..7、12、13与消息能力合法，但完全省略8/9。当前App路径可接受；本固件对应required-success校验不能通过。不要将“存在未知字段”与“遗漏必需注册字段”混为一类。
2. 12或13出现但不是有效的固件字符串形态。当前App不解析其值，不能用其出现作为成功依据；本固件必须由该字段回调成功。应选一个明确的非法样本，例如缺末尾NUL，而不是臆造全部语言码规范。
3. 已确定为Bluetooth raw kind2/3的端点缺17，或wireless raw kind4缺24。当前接受路径未表达该条件；原固件有承载组件门槛。App自己的transport enum与原始kind映射仍应另验，不能直接把数字照搬。

后续修复方向：先建立带参数ID的解析结果、required-success集合与真实承载条件，再决定接受/拒绝；不要只把8/9加进“出现过”列表就认为完整复刻。power字段9还依赖动态provider限额，不能无证据固定为0。不得通过放松AA、伪造1D01或随意增加声明来掩盖不完整支持。

## 5. IAV-03 · P2 · 第二份 SYN|ACK 已确认，但提交的是首份提案

状态：`CONFIRMED_STATIC_BRANCH`。

[IapLink 第461行][A06] 的SYN|ACK分支校验形态后解析 `second`，只采用其MTU与序列号；第466行发纯ACK。随后第473–475行仍提交第一份SYN的 `controlEntry` / `selectedLinkVersion`；window、重传/ACK相关选择也来自第一份。分支没有要求两份提案一致，也没有把第二份完整重协商后提交。

拟议回归向量（未执行）：首份合法SYN为link1/control id1/version1；对端下一帧为合法SYN|ACK，正确确认本地PSN，但提议control id2/version2。当前分支发纯ACK却仍记录id1/version1；随后id2数据在 [IapLink 第673行][A07] 被当作unsupported session丢弃。

这里确认的是App分支的内部不一致。是否允许对端在此状态更改提案、真实车机是否会发送、iPhone在该精确同时开链路径如何选择最终集合，本轮没有全部恢复。不能把此向量写成已经发生的车辆故障。

原固件IV02/IV03提供工作块→active的一致提交边界，但不代替此精确分支的完整复原。后续应先确定分支合同：不允许变化则在ACK前明确拒绝不一致；允许则完整重协商并一致提交。不能一边注释“采纳它的提议”，一边只采纳MTU/seq。

## 6. IAV-04 · P2 · CMD54/55 消费缺口，仍属候选

状态：`PARTIAL_CANDIDATE`。

[IapLink 第569行][A08] 对非link1的CMD更新receiveSeq，54/55分别记为FSM事件9/10，封装 `IapCommand.Control` 入队。该类型 `fields=null`。审查到的下游：

- 启动期：各[IapPeerProfile][A09]不把Control分类成lingo；Bootstrap第464行见 `fields==null` 记录unclassified并continue。
- Runtime：RuntimeIap第104行只调用传入message消费者；[AirSession 第149行][A10]仅处理NowPlaying START/STOP/5003，54/55没有动作。

固件IV06 `0x1000d4c94` 的非link1分支不仅保留opcode，还实际调用FSM事件9/10。IV07 `__authAndIDComplete@0x10011d8dc` 仅在相关flags低两位都置位时调用 `iAP2TimeSyncStart`。因此“认识opcode并入队”不等于实现了对应状态机行为。

但App SYN扩展数量声明为0；本轮未闭合这些扩展、flags生产者、时间戳上下文以及对端何时可依赖该行为。所以不能简单说“接受link2/3就一定错误承诺全部时间同步能力”，更不能据此解释AirPlay音频的具体时间戳或此前卡顿。下一轮应单独恢复功能协商前提→FSM动作→回复/超时→时间戳消费者，再决定支持或显式禁用的边界。

## 7. 认证次序、能力门槛与可信继承：已知差异和保留项

当前App的control1走AUTH_FIRST、control2走IDENT_FIRST。这一分支确实存在；本轮没有重新闭合iPhone最初如何选择control profile与全部启动顺序，不能只因旧文档写法不同就判错。

IV05 `__startFeatureFromDevice@0x1000ed1ac` 中：

- control版本恰为2排除该处父连接认证继承捷径；其他版本仍须父连接已认证、认证信息存在、cert capabilities/serial可用、CTAAllowed等条件。
- 在feature标志尚未置位时，control版本>=2且Identification允许接收AA06，才构造带空pid0的AA00；否则发不带该参数的AA00。feature标志已有值的路径不能忽略。

[IapAuthentication][A11]的serial请求主要由AA06声明决定，没有显式control版本参数。但正常control1 auth-first阶段尚无已识别消息集，会发bare AA00；control2 ident-first才可能带AA06声明。因此当前正常顺序间接覆盖了一部分版本条件。未证明存在越界实际调用路径前，不列成独立已确认错误；后续回归应覆盖顺序重入与runtime另一路径。

App runtime选择重新认证，不自动继承可信父连接。没有完整可信绑定和失效合同前，这属于保守差异，不应为贴近iPhone而跳过认证。当前还明确区分production trust门槛与experimental integrity模式；后者验证challenge并发送AA05，但日志说明Apple root未验证。此限制不能包装成生产认证完整支持，也不能据此在本轮外推安全漏洞或连接失败根因。

## 8. 后续实现审查顺序与验收边界

1. 先关闭IAV-01：所有在线上回发的control版本，必须具有可执行的后续schema；拒绝发生在承诺前。
2. 对IAV-03建立两份提案一致性/重协商合同和可重复向量，明确“已解析、已ACK、已提交”三个不同事件。
3. 按第12章补齐IAV-02的字段成功集合、承载条件、接受/拒绝路径；用原固件条件作预期，不以当前App自己的mock PASS自证。
4. IAV-04先补前提与动作证据，暂不凭opcode名称补写时间同步。

每条回归记录至少应带：源码/安装包版本、链路generation/epoch、首份与第二份提案字段、最终提交版本/session、输出消息、失败所在阶段。身份字符串、证书、Wi-Fi密钥不应原样写入普通诊断日志。


[E]: ../evidence/iap2-version-capability-evidence.json
[T]: ../tools/inspect_iap2_version_audit.py
[C12]: 12-identification-contract.md
[A01]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:141
[A02]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt:313
[A03]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapStartupPolicy.kt:11
[A04]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt:493
[A05]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfo.kt:14
[A06]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:461
[A07]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:673
[A08]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:569
[A09]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapPeerProfile.kt:73
[A10]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt:149
[A11]: ../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapAuthentication.kt:21
