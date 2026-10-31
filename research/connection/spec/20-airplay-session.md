# 20 — AirPlay 控制建连：从有效端点到视频启动许可

日期：2026-10-29。研究基线：**24A446 的手机发送端**。本章是本轮重新查阅原反编译/汇编后的有界结论，不是苹果公开规范，也不是整条协议已经验证通过的声明。

后续说明：本章Android差异表保留当时审计快照。`/setup`及屏幕根路径fallback、固定GET `/info`、未消费skipRecord、强制eventPort等已在[67](67-connection-mainline-batch4.md)有界修正；更多原始分支见[27](27-setup-response-branches.md)。不要把旧表当当前源码，也不要据局部修正推断全SETUP完成。

证据与文件 SHA-256：[airplay-evidence.json](../evidence/airplay-evidence.json)。其中 AP-01…AP-25 是本章引用编号，包含原文件绝对路径、函数入口、原二进制哈希、缓存文件哈希。23 个所引函数的 `.bin` 已在本轮逐字节与提取 Mach-O 对应虚拟地址区间比较，相同。**字节相同只证明来源一致，不证明对所有分支的解释正确。**未把历史测试结果当成本轮执行，也未据此宣称实车兼容。

## 1. 先保留这些边界

- 网络配置不等于 AirPlay 端点。`0x4301` 和 `0x5703` 的字段及生产/消费链见 [蓝牙/iAP2/网络章](10-bluetooth-iap2-network.md)。前者可携带 IP/端口；后者仅给网络配置。不能把“收到 5703”直接转成“已知控制服务器”，也不能把两条入口分别命名为首次配对/再次连接。
- 手机注册 `_carplay-ctrl._tcp` 是让车机请求手机发起连接；手机随后连接的车机 AirPlay 控制端点，是另一角色。不要把两个监听端口互换。[AP-01/02/03]
- 控制 TCP 已连接、配对/认证成功、控制 SETUP 完成、事件通道可用、屏幕流 SETUP 完成、会话开始、首帧显示是不同证据层。[AP-07/08/14/15/16/21]
- 固件有独立 `/info`，也有 verification 或 SETUP 携带信息的分支；有条件 `RECORD`，不是每次都必须按固定的 `/info → SETUP → RECORD` 模板发包。[AP-11/12/16/19]
- 本章确认存在 Bonjour 邀请入口，但**未闭合“5703-only 必然经该入口”这一跨进程因果链**。需把车辆匹配、网络接口、控制邀请、端点发现的关联一起追踪；不能仅靠时间相邻推断。

## 2. 各阶段的九问契约

以下“成功证据”是排障时应取得的证据，不表示已有该车的实测结果。超时未恢复之处明确保留未知，禁止照搬我们 App 的秒数作为固件默认。

### A. 邀请入口与有效接收端

1. **前置**：存在可用接口、手机控制服务监听对象及目标身份上下文。接口建立时机、首次配对/重连时的发布政策仍需上游链闭合。
2. **发起方/通道**：手机在指定接口发布 `_carplay-ctrl._tcp`、`local.`；车机向手机控制服务发出 connect 邀请；成功接收后手机异步安排后续连接。[AP-01: C 41–81；AP-02；AP-03: C 41–95]
3. **消息**：处理器按 URL 组件解析 `ctrl-int`、`1` 和剩余命令；读取 `AirPlay-Receiver-Device-ID`，格式为十进制 `%llu`。上层只接受 `connect`。[AP-02: C 31–79；AP-03: C 46–110]
4. **字段/缺省**：该 ID 必须被扫描出一个值；不是把冒号 MAC 文本直接放进该 header。URL 错误走 404；命令回调失败走 400；成功走 200。header 扫描失败是此函数返回 `0x1c8`，**尚不能称为线上 HTTP 456**，因为上层错误转换未在本章闭合。[AP-02]
5. **值来源**：发布端口来自服务对象，不得固定抄一个手机抓包端口；接收端 ID 来自请求，需要与接收端候选绑定。身份如何融合进端点对象仍待完整追踪。[AP-01/02]
6. **接受条件**：路由匹配、ID 能解析、命令上层接受。存在测试偏好 `ignoreCarPlayHUConnectCmd`，可回 200 但忽略 connect，因此 **200 本身不证明手机已开始对外连接**。[AP-02/03]
7. **成功证据**：同一接口上的服务发布 + 对应邀请的接收/应答 + 被选中的车机 ID + 随后的真实控制 TCP 连接。每项分别记录。
8. **失败/退出**：记录坏 URL、缺 ID、上层命令拒绝、邀请已应答但无连接。调用方是否验证 HTTP method、重试定时和重复邀请去重本章尚未闭合。
9. **下一事件**：手机获得有效控制端点并连接；不要求此邀请必须先于或晚于某一条 iAP2 消息，直到同版本端到端证据确定。

### B. 控制连接和安全分支选择

1. **前置**：已选定接收端、接口、地址族/IPv6 scope、控制端口及可信的能力来源。
2. **发起方/通道**：手机创建 transport/control stream，绑定消息回调并连接接收端；成功后才进入 pairing。[AP-08: C 769–1102、1407–1512]
3. **消息**：原发送层按内部 4CC 生成 RTSP 方法/路径；`/pair-setup`、`/pair-verify`、`/auth-setup` 是不同路由，不可视作同一个“认证包”。[AP-04]
4. **字段/缺省**：pairing selector 读取 `SupportsCoreUtilsPairingAndEncryption`、`SupportsLegacyPairing`、`OneTimePairingRequired`、`SupportsUnifiedPairingAndMFi`、`AccessControlType` 等。**未知字段不等于明确的 false**：属性访问器的缺失/类型错误默认还需追到定义。[AP-09: C 78–180]
5. **值来源**：能力来自 endpoint；已知 peer 来自 pairing client/store；transport 必须来自当前会话。kind=5 且走 CoreUtils 时采用 `PairingPeerCUAirPlayIdentifier`，不能因为支持 SystemPairing 就改用 CUSystemIdentifier。[AP-10: C 49–173]
6. **接受条件**：安全分支根据能力、配对记录、交互要求选择。`ensurePaired` 有 noPair 返回 0 的路径，**仅代表该步骤无须执行 pairing，不代表整个安全握手已通过**；后面仍有独立认证分派。[AP-09；AP-07]
7. **成功证据**：控制 socket 的实际连接 + 所选安全路线及选择依据 + 该路线的密码学验证/身份绑定结果。单条“authenticated”应用日志不能替代这些证据。
8. **失败/退出**：原代码多处检查取消，connect/pairing 失败可进入 `_apsession_ensureDisconnected`；重试会考虑 transport fallback。具体每车可重试错误集合、次数、等待值未完整恢复。[AP-08: C 1162–1204、1641–1642]
9. **下一事件**：选中的配对/认证分支完成、key holder 建立，然后控制 SETUP；不可无条件把首次连接等同 pair-setup、重连等同 pair-verify。

### C. 独立认证与 key holder

1. **前置**：当前控制通道、endpoint 的认证属性、已建立的 pairing client（若该分支要求）。
2. **发起方/通道**：手机 Stage1 按条件创建认证客户端，在控制链路上交换所选机制的报文；key holder 与后续流加密/控制加密相关，不等于蓝牙 bond。[AP-07/10/13]
3. **消息**：路由编码器同时具有 binary-plist 与 octet-stream 形态的 `/auth-setup`，及 `/fp-setup`、配对路由。**同一路径并不能唯一决定载荷格式，需看所选对象和内部消息类型。**[AP-04: C 320–470]
4. **字段/缺省**：Stage1 读取 `AuthenticationType`，读取错误走失败；部分状态跳过单独 authentication，包括 UnifiedPairingAndMFi 分支。这里跳过不证明无 MFi 校验。[AP-07: ASM 0x2519c63d0–0x2519c64b0；AP-24/25]
5. **值来源**：下面的 `AuthenticationType` 是内部枚举，**不是可直接填入 SETUP `et` 的值**。证明所选 factory 不等于证明其证书、签名、密钥材料或对端验证已正确实现。
6. **接受条件**：factory 创建成功后执行 AuthenticateEndpoint；后续操作成功才保留对象；失败不得视为就绪。[AP-07: ASM 0x2519c6528–0x2519c69c4]
7. **成功证据**：路线、实际往返、验证对象身份、密码学检查、当前会话 key holder。任何秘密不得原文写入排障日志。
8. **失败/退出**：区分缺能力、缺用户输入、peer/store 绑定不符、证书或签名校验失败、网络超时。不可用全部属性设 false 来“兼容”安全门槛。
9. **下一事件**：key holder 成功后控制 SETUP。Stage1 原始直接调用顺序是 key holder `0x251b5ce10` → control setup `0x251b5cfe0` → event stream `0x251a5dec0`，中间仍有 timing 条件分支。[AP-07: ASM 0x2519c6060–0x2519c630c]

|已核查内部值|选择的 factory|原始调用地址|本章证明范围|
|---|---|---|---|
|4|FairPlayCreate|0x2519c6558 → 0x251ace54c|只证明该分支存在，未证明普通无线车机会选择|
|8|MFiCreate|0x2519c65d0 → 0x251b26ef4|同上|
|0x20|MFiMutualAuthCreate|0x2519c6570–0x2519c65b4 → 0x251a33a18|还要求已有 pairing client/transcript|
|0x10|TokenCreate|0x2519c66d4 → 0x251aa03d0|不能从名字推断它等同 MFiSAP|
|1|RSA 或 Token 分支|0x2519c6664–0x2519c66d4|受运行时 predicate 与 kind 条件控制|

表内依据均为 AP-07 汇编。原函数反编译状态 FAILED，本章没有把残缺 C 当完整控制流。CoreUtils 的 Setup/Verify 本身也有条件 MFiCertificate 验证（AP-25: C 234–244；AP-24: C 240–253），故“未调用独立 `/auth-setup`”不能推出“没有配件信任验证”。完整 TLV8/MFiSAP 密码学线格式尚未在本章重建。

### D. 控制 SETUP、信息与事件通道

1. **前置**：控制 stream 存在；上述路线就绪；字段对应的网络/timing/身份提供者有效。
2. **发起方/通道**：手机在控制连接上发送 SETUP，request helper 用 `stup`；失败立即返回，不进入响应消费者成功路径。[AP-12: C 29–67]
3. **消息**：SETUP 使用 binary plist；请求 wrapper 对非空 plist 以格式常量 200 序列化，回复有 body 时要求能解为字典。[AP-04/06]
4. **字段/缺省**：请求可携带 `updateSessionRequest`、身份、timing、功能及条件加密字段；响应的 `eventPort`/`keepAlivePort` 不是在此层一律必填。详见下表。[AP-12/13/14]
5. **值来源**：设备、当前 transport、session UUID、选定 key holder 与本地能力；不能复制另一部 iPhone 的 UUID、端口和密钥。此版本实际 sourceVersion 字面量是 `980.77.1.2`，不代表其它 iOS 版本也应使用它。[AP-13: C 204–233]
6. **接受条件**：先响应格式成功，再按字段类型与状态消费。`enabledFeatures` 在 kind=5 被读取；缺键错误 `-0x1a47` 被忽略，但其它读取错误可失败。**可选不等于畸形值必然被接受。**[AP-14: C 112–139]
7. **成功证据**：具体 SETUP CSeq/状态/body 解析 + 实际 feature 结果 + eventPort 若非零时的事件连接结果。SETUP 200 与事件 TCP connect 成功必须分开。
8. **失败/退出**：单独记录格式错误、类型错误、事件端口不可达与 key context 不符。Stage1 失败会断开 control stream，不能把半成品留作已启动会话。[AP-07: ASM 0x2519c6384–0x2519c6418；AP-17]
9. **下一事件**：取得所需 displays/info 后建立屏幕流，完成 Stage2；信息可能来自 verification、SETUP 内嵌 `info` 或独立 GET `/info`。[AP-11/12/16/19]

### E. 屏幕 SETUP 和开始会话

1. **前置**：有效显示能力、流描述和当前控制会话，详见视频章；不要把音频/远控流的 descriptor 填到屏幕流。
2. **发起方/通道**：手机在控制通道发送流 SETUP，使用协商回复建立数据传输。[AP-21]
3. **消息**：流 SETUP 回复通过 `streams` 数组消费；本函数一次建立一条流，要求数组恰好一项且 `type` 匹配请求。[AP-21: C 405–441]
4. **字段/缺省**：`streamID`、`streamConnectionID` 与 `type` 不是同一标识；缺 `streamID` 时只有特定分支会从注册表生成，不可一律拒绝，也不可一律补常量。[AP-21: C 442–483]
5. **值来源**：端口来自实际回复；流身份来自该请求/响应与会话注册表。编码配置和关键帧是后续独立证据，不由 SETUP 200 自动证明。
6. **接受条件**：Stage2 的会话已启动位与 SETUP `skipRecord` 状态控制是否发 RECORD；未启动且未声明 skipRecord 的路径发送 `rcrd`，路由映射为 RECORD。[AP-12/16/04]
7. **成功证据**：有效流回复、数据连接、RECORD（若分支要求）的成功响应、Started、编码输出、接收/解码/显示，逐层记录。**Started 仍不等于车机首帧显示。**
8. **失败/退出**：Stage2 失败调用 `_apsession_disconnectControlStream`。已经看到 socket 断开时，应先寻找前面的控制错误，而非只写“视频断流”。[AP-16: C 1216–1218]
9. **下一事件**：视频配置与关键帧进入正确数据通道，并取得车机实际显示证据；随后检验持续更新和可重连。

### F. 断开与重新连接

本节为索引；整会话/部分流presence、清理的具体条件和超时生产者已补入 [24](24-disconnect-reconnect.md)，不能用概括的“断开成功”替代那里分开的结果。

1. **前置**：当前会话明确失败/取消/正常退出；区分 transport 断开与用户取消配对。
2. **发起方/通道**：本轮确认失败路径会主动清理控制连接，不要求等待车机先断。[AP-07/16/17]
3. **消息**：24章已核对NULL/非NULL数组、UseConnectionSharing控制teardownType、无control的本地成功，以及注销先于发送；所有错误出口和恢复仍未闭合，不能从路由存在推断每次异常都能成功发送。[AP-04；24 LC01–07]
4. **字段/缺省**：断开清理中释放 session 的认证对象、pairing client、key holder 等，并清相关 setup/info 状态。[AP-17: C 26–58]
5. **值来源**：下次尝试需重新证明网络/端点/临时会话材料仍有效；持久配对记录的删除不是“清掉 session+0x140”。
6. **接受条件**：旧回调不得推进新连接是测试要求；本轮尚未全量证明 24A446 每个跨队列 race 的取消/世代规则。
7. **成功证据**：断开后旧通道和任务停止，新连接有独立时间线且再次显示持续画面；历史成功不代替本次成功。
8. **失败/重试**：发送 wrapper 有超时等待和 timeout 后 invalidate 分支；等待值为零时可无限等待，不存在从该函数得出的统一“总是 10 秒”。具体全栈预算需逐层读取。[AP-18: C 100–108、155–163]
9. **下一事件**：按当前网络与信任状态重新选择入口和安全路线。首次配对/已配对/异常重连必须各自测试，不把一次成功当三种都成功。

## 3. 已复核的关键消息与字段

### 3.1 控制帧和事务

|对象|本轮证实|不能外推的部分|
|---|---|---|
|请求版本|路由编码函数写 `RTSP/1.0`。[AP-04: C 474–481]|不能把邀请服务 HTTP handler 与 RTSP 媒体会话当同一 socket|
|方法/路径|`stup`→SETUP；`rcrd`→RECORD；`tdwn`→TEARDOWN；`info`→GET `/info`；对应 pairing/auth routes。[AP-04]|仅证明映射，未证明所有路由在每辆车上使用|
|CSeq|按 `%u`写连接对象 `+0x110` 的**旧u32值**，同时保存旧值+1；反编译省略varargs时易误读。[AP-05；ASM 0x24fda555c–5580；[22](22-control-wire-contract.md) CW01]|首值与所有重连路径尚未闭合；u32递增会回绕，不能单靠CSeq作跨连接身份|
|ProtocolVersion|SETUP 与 info 分支追加 `X-Apple-ProtocolVersion`。[AP-04: C 478–481]|[62](62-version-capability-audit.md) 已补provider：初始化u32为0/1/2时原样返回，其余映射1；真实偏好和底层reader未全闭合，不宣称运行中恒为1|
|body|通用 plist wrapper 对非空请求用 CFPropertyList format=200；有回复 body 时解为字典。[AP-06: C 60–94]|路径相同的不同认证类型不能混用 plist 与原始握手载荷|
|超时|reply wait 使用设置值×1,000,000,000 构造 deadline；零值为无限；特定 timeout 错误 invalidate。[AP-18]|[24](24-disconnect-reconnect.md) 已补kind5控制创建输入10与event provider默认60/覆盖；底层消费/fallback和本次实际deadline仍不能直接等同创建参数|

控制线格式、body边界、原请求对象关联、100…599响应分派与200…299成功映射的区别，详见 [22 — 控制报文合同](22-control-wire-contract.md)。该分册没有据未找到CSeq读取就宣称所有底层路径均不检查CSeq。

### 3.2 初始控制 SETUP（字段子集，不是完整字段白名单）

|字段|类型/来源|存在条件/缺省与注意点|证据|
|---|---|---|---|
|updateSessionRequest|plist Boolean，request helper 的调用参数|helper 明确写 true/false；更新路径传 true，初始 ensureControlStreamSetup 传 false|AP-12: C 42–50；AP-14: C 59–63|
|deviceID|字符串，六字节设备标识格式化，kind5另有偏好覆盖|不能抄另一手机；具体平台设备ID提供者仍待闭合|AP-13: C 163–186|
|macAddress|字符串，当前 control transport 的 LocalMACAddress|不等于任意持久随机ID|AP-13: C 199–210；CFString 0x27612f0b0|
|model/name/osBuildVersion|字符串，由本地提供者写入|是协议可观察输入，不是随便放一段文本；提供者含义须继续追踪|AP-13: C 211–221；CFString 0x27612f0d0/0x27612f0f0/0x27612f110|
|sessionUUID|字符串，transport UUID属性转换|必须与当前会话相关，不固定复制|AP-13: C 222–234；CFString 0x27612f130|
|sessionCorrelationUUID|字符串，另一个身份/关联提供者|kind<6且kind!=3才进入此写入分支；不等于sessionUUID|AP-13: C 183–189；CFString 0x27612f030|
|sourceVersion|字符串，本基线字面量 `980.77.1.2`|仅24A446此构造点，不能拿它给任意版本“统一身份”|AP-13: C 231–234；CFString 0x27612f150|
|et|整数，由 key holder 类型映射|进入key holder分支时8→16、4→32、1→2，其它/无getter结果落0并写入；跳过整个分支才不写。不是统一必须16|AP-13: C 525–546；ASM 0x251a59a38附近|
|ekey/eiv|key holder 输出对象写入字典|getter/准备操作成功才写；字节长度和封装按所选机制另外验证，不能仅由字段名推断|AP-13: C 547–568|
|combinedGetInfoWithControlSetup/qualifier|Boolean及数组，条件分支|会话+0x5b开启合并请求；本调用给qualifier构造器的txtAirPlay参数为0，displayCapabilities取会话+0x161|AP-13: C 455–470；AP-20: C 22–30|
|qualifier成员|`txtAirPlay`、`displayCapabilities`|两个独立开关追加，不是固定“必须同时带两项”|AP-20；CFString 0x27612f690/0x27612bff0|

上表 CFString 本轮从提取 AirPlaySender 的段映射读取并解引用核实，不是从旧文档照抄字段名。除 sourceVersion 等可直接看到的字面量之外，未把本地运行结果臆造为固定 iPhone 值。完整 timing、features 和 session flags 仍需按被选中的无线 kind5 配置继续缩小。

### 3.3 SETUP 响应与事件通道

|字段|消费者行为|排障含义|证据|
|---|---|---|---|
|info|有内嵌字典时交 processGetInfoResponse|没有独立GET /info不一定是少步骤|AP-12: C 73–105|
|skipRecord|本轮从24A446原始dyld v5指针链解析出精确CFString键；通过`CFDictionaryGetInt64`消费，非零时设session+0xdd|后续可能合法不发RECORD；这只闭合键名/读取类型和局部guard，不证明所有会话都省略RECORD|AP-12: C 106–121；AP-16；[control-response-keys.json](../evidence/control-response-keys.json)|
|eventPort|取值成功才输出；错误清零继续|随后event creator的入参0直接成功返回，不建立event stream；不等于所有车型都可以删事件链|AP-14: C 65–70；AP-15: C 77–83|
|keepAlivePort|取值失败清零继续|可选UDP低功耗分支，不可当视频端口|AP-14: C 71–76|
|enabledFeatures|kind5读取数组；missing(-0x1a47)忽略，其它读取错误失败|缺键与类型错必须区分|AP-14: C 112–130|
|uiPreloaded|成功读到才写入会话stats；未拿到不阻断本函数|不能等价于“车机已显示第一帧”|AP-14: C 132–147|
|streams|本单流SETUP回复必须恰好1项，type相同|不是全局禁止一次多流的所有API，而是这个调用契约|AP-21: C 410–441|

事件 stream 创建时会安装 `_apsession_eventStreamMessageCallback` 与 reply callback；支持 CU 且 key holder 存在时传 `Events` 加密 context，然后连接。[AP-15: C 141–198、240–279] 因此，媒体SETUP之前/之后收到车机请求时，不能只写响应不读、或把事件加密 context 当控制 context；具体 HKDF 标签和计数器布局尚需对应 crypto 章继续闭合。

## 4. 当前 Android 手机实现的可证实差异

下面是审查当日源码，不是修改建议，更不能以原固件“存在一条分支”认定当前实现一定错误。当前工作音频基线保持不动。

|当前实现|24A446对照|影响/结论边界|
|---|---|---|
|固定 sourceVersion=320.17，compatibility build=21A329，实际Android model/osName/osVersion。[AP-23]|SETUP构造器sourceVersion字面量980.77.1.2。[AP-13]|身份是兼容组合，不是同一iPhone版本复刻；不能为外观一致盲改|
|初始SETUP拒绝后回退 `/setup`。[AP-22: L517–525]|原路由已核查SETUP使用调用者URL；本轮未证明 `/setup` 回退是苹果行为。[AP-04]|记录为自定义兼容策略，不称iPhone标准流程|
|初始SETUP之后无条件独立GET `/info`。[AP-22: L527–533]|原固件有合并info、条件public/protected info路径。[AP-11/12/19]|差异已证实；能否触发特定车机失败要实际事务证据|
|有屏路径内不检查skipRecord而发送RECORD。[AP-22: L689–693]|原Stage2按已启动和skipRecord状态决定。[AP-16]|差异限于已审有屏路径，不代表无屏会话也必发；代码修改另行确认|
|eventPort必须存在且1..65535。[AP-22: L747]|原consumer容忍missing，event creator入参0直接返回。[AP-14/15]|潜在严格度差异；不能推断缺eventPort仍能实现全部CarPlay控制|
|无display时继续无屏会话。[AP-22: L563–574]|本项目目标要求车机实际显示|此种会话可存活但**本阶段目标未达成**|

源码哈希已存于AP-22/23；之后发生改动必须重新核对行号和行为。

## 5. 连接卡点定位

|车机提示/表象|最后明确成功|下一应有事件|要补的区分证据|
|---|---|---|---|
|还显示蓝牙/iAP2，手机已入Wi-Fi|实际网络地址就绪|有效目标端点/邀请/控制connect之一|5703是否只给了网络；是否有4301 IP/port；接口scope；手机控制服务是否真正可发现|
|已收到connect邀请但仍无画面|邀请200|目标匹配与手机对外TCP连接|该200是排队成功、测试忽略还是已进入事务；正确的十进制ID与目标身份|
|停AirPlay|控制socket成功|对应pair/verify/auth下一响应|路由选择依据、消息类型、载荷类型、状态、验证失败点；勿把蓝牙bond当airplay配对记录|
|SETUP200后断开|响应被解析|事件connect、信息取得、流SETUP|eventPort实际值/可达性、字段错误与缺失、是否已combined info、事件key context|
|视频SETUP200但无画面|streams/type有效|数据通道、开始会话、配置帧/关键帧|RECORD是否该发且成功、dataPort绑定、编码输出、解密/解码/显示证据|
|首次能连，重连失败|上一会话曾显示|旧会话清理并新建当前通道|旧socket/旧callback残留、失效地址、peer record仍有效、当前加密计数器和key|

所有行均是诊断分叉，不是已经证实的某辆车故障根因。记录 `attempt-id / session-id / interface / peer-id / endpoint / message / CSeq / direction / status / elapsed / last-success / next-expected`，敏感材料只记长度、校验结果或受控脱敏标识。

## 6. 未闭合项与关闭标准

|编号|未知项|怎样关闭，而不是猜一个值|
|---|---|---|
|AP-U01|4301直接端点、5703网络配置、Bonjour邀请与配对车辆身份在平台层的融合顺序|**部分关闭：** [21](21-endpoint-fusion.md) 已核对交接与局部网络/接口/元数据/显示配置门槛；身份匹配、候选优先级、角色绑定及首次/重连异步时间线仍 OPEN|
|AP-U02|端点属性的线端来源、缺失默认与override|从TXT/4301/info解析点逐个追到endpoint属性读取；不能全设0通过selector|
|AP-U03|被选配对/认证路线的完整线格式、peer-store提交和证书/签名约束|闭合当前实际车机能力选择的一条完整密码学事务，负例包含错peer、坏签名、取消与部分提交|
|AP-U04|全栈超时、重试预算和请求URL构造|**部分关闭：** 22已补封装/CSeq/waiter，24已补timeout producer/分支/fallback；完整URL、所有覆盖、底层绑定及实际运行预算仍OPEN|
|AP-U05|skipRecord及内嵌info的跨镜像CFString pointer chain|**部分关闭：** 原始键名和两个getter已解析；仍需闭合所有响应生产者、类型异常和Stage2跨会话消费，不能因键名已知而把RECORD写成必经/必省略|
|AP-U06|所有字段的完整presence表、timing方式和功能协商|锁定无线kind5实际配置，追每个producer到接收端consumer，禁抄全量通用AirPlay键|
|AP-U07|正常TEARDOWN、部分流关闭、恢复重试、跨队列世代保护|**部分关闭：** [24](24-disconnect-reconnect.md) 已核条件字段、无control成功、注销/发送/最终返回差别和局部异步失效；完整错误出口、race与重连仍OPEN|
|AP-U08|真实持续显示与重连|原iPhone/当前App分别在同一车机上取得可关联的显示记录；控制Started及发包日志不够|

## 7. 证据阅读索引

所有条目的完整路径和哈希以 JSON 为准；`.ghidra.c` 是原反编译输出，只有本章点名的范围经过本轮解释审查。`L`/`C`为该文件行号；ASM地址为运行时VA，不是文件偏移。

|编号|镜像/入口|本章使用范围|
|---|---|---|
|AP-01|APTransport 0x24fe01ea4|服务注册参数；C41–81，邻接汇编|
|AP-02|APTransport 0x24fe387fc|URL/header/状态处理；C31–111，ASM0x24fe38838起|
|AP-03|AirPlaySender 0x251a95354|connect异步派发；C41–110|
|AP-04|APTransport 0x24fda58ec|方法/URL/content type/版本；C77–100、233–283、320–481|
|AP-05|APTransport 0x24fda5468|CSeq/header；C43–68|
|AP-06|APTransport 0x24fdaf86c|请求序列化/回复字典；C35–110|
|AP-07|AirPlaySender 0x2519c5858|只使用汇编；key holder/setup/event与独立auth分派|
|AP-08|AirPlaySender 0x251a5b22c|control创建/连接→pairing、失败清理；指定范围非全函数闭合|
|AP-09|AirPlaySender 0x251a5e858|pairing能力门槛、noPair和取消分支；C78–190|
|AP-10|AirPlaySender 0x251a60f70|pairing identity/transport构造；C49–173|
|AP-11|AirPlaySender 0x251a61474|验证附带info；全函数条件阅读|
|AP-12|AirPlaySender 0x251a59338|SETUP请求与响应；C29–132|
|AP-13|AirPlaySender 0x251a59708|本章表内字段子集；不声称全量白名单|
|AP-14|AirPlaySender 0x251b5cfe0|响应可选/错误条件；C59–147|
|AP-15|AirPlaySender 0x251a5dec0|事件port0和事件创建/加密/连接；指定范围|
|AP-16|AirPlaySender 0x2519c69f0|条件RECORD、Started/keepalive、失败disconnect；C989–1218|
|AP-17|AirPlaySender 0x251a56e44|失败清理；C26–58|
|AP-18|APTransport 0x24fda68f8|发送等待/timeout；C100–108、155–163|
|AP-19|AirPlaySender 0x251b5db18|public info条件；C58–62|
|AP-20|AirPlaySender 0x251a5af78|qualifier两个独立开关；C22–30|
|AP-21|AirPlaySender 0x2519bbf24|单流SETUP回复guards；C405–483|
|AP-22/23|当前Android源码|只证明本实现行为，不证明苹果行为|
|AP-24/25|AirPlaySender 0x251b87acc / 0x251b88c94|CU Verify/Setup中的条件MFiCertificate校验；未声称密码学闭合|

本轮还发现旧材料把 `et` 未命中分支解释成“不写字段”，把 type103 后续操作解释成“清空统计buffer”；前者原C显示写 `et=0`。后者经[24章](24-disconnect-reconnect.md)进一步复核，是对现存控制/event对象尝试设置timeout provider值且不检查setter结果，不能继续沿用固定 `0x78` 或清buffer的旧解释。这提醒：**旧claim的 confirmed 标签不能代替原函数复核。**
