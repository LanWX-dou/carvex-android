# 10 — 蓝牙、iAP2 与无线网络建立

状态：第一轮原始证据核验；不是已经闭合的无线 CarPlay 全栈规范。静态基线为 iPhone18,1 / 24A446；本章不把其他 iOS 版本的运行记录提升为该版本事实。

本章只写已核验的连接路径和明确的缺口。`S` 表示静态证据；`D` 表示诊断/实现建议，不是苹果常量；`OPEN` 表示还不能给出实现结论。证据键 `Bxx` 对应 [bootstrap-evidence.json](../evidence/bootstrap-evidence.json)，包含原文件绝对路径规则、函数地址、原字节 SHA256 及本次原 Mach-O 字节比对结果。

## 1. 首先不要把连接画成一条必经直线

- `S/B01`：iPhone 存在主动建立 outgoing Wireless iAP RFCOMM 的路径：查询服务记录，解析协议描述符，再以取出的通道调用连接函数。蓝牙 bond 已存在，不等于该 RFCOMM 通道已经打开。
- `S/B03–B11`：iAP2 链路 connected、Identification accepted、Accessory Authentication passed 是不同状态。业务消息准入还检查该消息是否由配件声明；不能只设一个 `iapReady=true`。
- `S/B12–B16`：Wi-Fi 配置交换 `0x5702/0x5703` 和 CarPlay 会话启动 `0x4300/0x4301` 是不同入口。`0x5703` 没有 AirPlay IP/port 字段；`0x4301` 同时可携带 Wi-Fi 凭据和端点。当前证据不支持“所有车必须先 5703，再 4301”，也不支持把两路分别命名为“首次连接/重连”。
- `S/B13`：无线允许状态与“已配对 CarPlay”的检查会参与设备传输标识通知。普通蓝牙配对、CarPlay 用户授权、Wi-Fi 凭据、AirPlay 配对身份不能视为同一份状态。
- `D`：收到 Wi-Fi 配置、操作系统开始关联、拿到地址、选定正确网络接口、目标服务可达，应分别记录。任一前项都不能代替后项。

后续服务发现与 AirPlay 会话见 [20](20-airplay-session.md)，局部网络/端点汇合见 [21](21-endpoint-fusion.md)。本章不推定 `0x4301` 端点一定优先于 Bonjour，也不推定仅有 `0x5703` 就一定收到 `/ctrl-int` 邀请；完整身份匹配和实际运行时证据仍未闭合。

## 2. 阶段 B0：发现、配对与 RFCOMM 打开

| 问题 | 当前可用结论 |
|---|---|
| 进入条件 | 对端身份已选定；BT 开启及平台连接权限满足属于实现条件。首次发现、配对与授权的全部原生触发条件尚未闭合。 |
| 发起方/承载 | `B01` 确认手机可主动连接；经典蓝牙服务查询后建立 RFCOMM。不能由此排除另一条被动路径。 |
| 请求/响应 | 原函数查询两份 WiAP 描述符、属性 `4`，遍历协议描述符提取 RFCOMM channel；随后调用 `0x1003c2b00`。服务响应与 RFCOMM connect 成功是两次独立事件。 |
| 字段及来源 | channel 来自对端记录，连接调用仅取低 8 位；不是把它当成 L2CAP PSM。该函数另传 `0x3ef`、`0x3b01`，尚不将其语义/单位升级为客户端必填常量。 |
| 固定/动态 | 旧 WiAP sink 描述符原数据为 `00000000decafadedecadeafdecacaff`；channel 动态。新描述符的内存字节与线上 UUID 转换尚 OPEN，见下。 |
| 接受/拒绝 | `0x1007a3c38–0x1007a3c78` 检查描述符形状；找不到通道的 sentinel 为 `-1`；连接调用非零失败分支最终返回 `0x131`。不把内部错误码当线上错误报文。 |
| 成功证据 | 平台 RFCOMM socket/handle 已连接，且双方字节流可用；单有 bond、设备名、HFP 音频连接或 SDP 成功均不够。 |
| 超时/重试/清理 | 当前没有核验出适用于本主线的统一超时数字；不得照抄旧文档的 2/5/30 秒作为苹果要求。建议独立记录 SDP 与 RFCOMM 超时、关旧 handle，按会话代次避免旧回调污染新连接。后半句为 D。 |
| 下一预期事件 | iAP2 Detect 或 SYN 等链路输入/输出，取决于启动状态；不是立即发送 CarPlay 业务消息。 |

`B01` 汇编在 `0x1007a3c00–0x1007a3c28` 查询新/旧描述符；`0x1007a3d94` 把动态 channel 放入参数；`0x1007a3da4` 调连接函数。日志文本是 `Initiating outgoing Wireless IAP connection request ... on rfcomm channel ...`。

`B22` 直接从 bluetoothd 原 Mach-O 读取：旧描述符指向 `0x100955190` 的 16 字节；新描述符指向 `0x1009551b0` 的 `020303021d19415f86f222a2106a0a78`。这只证明**本地描述符数据**；旧材料同时出现 `08ed27c3-...` 的文本，因此本轮不把新描述符字节直接写成线上 UUID 标准。需要追 `0x1005ebdf0` 的 UUID 规范化及 SDP 编解码，或有版本归属的原始报文。

诊断建议：应用若用操作系统 RFCOMM 字节流，不应把 SABM/UA/信用控制作为应用载荷再写一遍；平台栈与应用 iAP2 的边界应单独记录。此为 API 分层建议，不是从 `B01` 一函数推出的完整蓝牙协议规范。

## 3. 阶段 B1：iAP2 链路成功，不等于业务完成

| 问题 | 当前可用结论 |
|---|---|
| 进入条件 | 承载字节流可用且绑定当前 endpoint。 |
| 发起方/承载 | `B02` 为手机 Device 路径处理对端 SYN 后发送 SYNACK；[11](11-iap2-state-machine.md) 已核对 Detection 的局部事件表，但谁在各 transport 首次触发该事件仍 OPEN。 |
| 请求/响应 | 接收 SYN payload → `ParseSYNData` → `LinkCheckNegotiation` → `CreateSYNPacket` → `LinkSendPacket`；不可把第一批 `FF 5A` 字节当作握手完成。 |
| 字段及来源 | 对端 SYN 参数先解析/协商，本端序号由 `LinkGetNewSeqNum` 产生并缓存。[11](11-iap2-state-machine.md) 已补基本载荷布局；完整 profile 约束、扩展条目与 session ID 协商仍 OPEN。 |
| 固定/动态 | 重发分支复用缓存序号；不能每次重发都当新消息生成独立序号。也不能复制抓包中的固定序号。 |
| 接受/拒绝 | `B02` 体现解析/协商调用；该函数本身不足以证明整个接收状态机所有拒绝条件。 |
| 成功证据 | `B03` 的 NotifyConnection 拷贝协商参数，发 LinkEventNotify(2)，调用 LinkConnectedCB(...,1)。现场需相应链路状态转移及完整握手方向/seq/ack，而非只有 send 成功。 |
| 超时/重试/清理 | [11](11-iap2-state-machine.md) 区分 SendSYNACK 的 `+0x1d0` 计数（部分模式达到 `0xb` 触发 `0x14`）与 ResendSYNACK 的 `+0x1d8`/`+0x19c` 预算；不得写成统一“必重试11次”。packet 重传与累积 ACK timer 分开。全清理/承载差异仍 OPEN；清除本连接重组/序号/session状态为 D。 |
| 下一预期事件 | 控制 session 上的识别/认证流程；具体启动先后取决于 session/transport 路径，不能硬编码为所有版本同一顺序。 |

若发生蓝牙到 IP 承载迁移，应给每条 iAP2 link 单独的 connection/endpoint/session 关联键。不能把第二次 SYN、识别或认证误判成第一次握手“回退”。原始跨版本运行记录由总证据清单另列；不能据此声称 24A446 每次都迁移。

## 4. 阶段 B2：识别、配件认证和业务准入

认证对象必须拆开：这里的 Accessory Authentication 是**手机验证配件证书/挑战签名**；不是蓝牙链路加密，不是 Wi-Fi 的 WPA 握手，也不是 AirPlay Pair-Verify。

逐字段接受/拒绝、required-success 集合、条件组件与再次提交见 [12 — 识别合同](12-identification-contract.md)。下表仅保留阶段索引。

### 4.1 当前已核验消息骨架

| 消息 | 方向 | 原始证据与成功语义 |
|---|---|---|
| `0x1D00` | 手机 → 配件 | `B04`：识别 state0 时构造并发送；发送成功后 state1。 |
| `0x1D01` | 配件 → 手机 | `B23` 原 handler 表指向 `0x10013bcc8`；仅 identification state1/3 接收，本轮已核对注册/核心字段和局部校验，完整 feature 组合仍 OPEN，见12。 |
| `0x1D02` | 手机 → 配件 | `B05`：校验回调允许且无识别错误时发送；**发送成功才把 identification state 设为6**。 |
| `0x1D03` | 手机 → 配件 | 普通字段拒绝是同ID空TLV，本地reason不写入其body；6/7可带BE16拒绝消息列表，成功提交后state3可再次收1D01。完整更新识别/超时仍OPEN，见12。 |
| `0xAA00` | 手机 → 配件 | `B07`：认证开始；session version及已继承认证信息会改变路径；可条件增加 ID0 void 参数。不能假设所有启动都必须重新请求相同证书。 |
| `0xAA01` | 配件 → 手机 | `B23` 原表 → `0x1001850bc`，证书 handler；完整证书链/验证路径规则须继续审计，不能仅见证书字节就宣布认证成功。 |
| `0xAA02` | 手机 → 配件 | `B08`：回调允许、prepared==1、nonce指针与长度非零才发送；参数0为原始 nonce bytes，不是固定挑战。 |
| `0xAA03` | 配件 → 手机 | `B23/B10`：参数0取首个非空签名响应，调用 `platform_auth_verifyNonceSignature(保存的证书,保存的nonce,响应)`。 |
| `0xAA04` / `0xAA05` | 手机 → 配件 | `B09`：失败/成功完成消息；随后 auth state=1/2。原函数未用 enqueue 返回值证明对端已收到；本地 state2不能替代线上证据。 |

`B06` 是重要门槛：常规 incoming 业务消息需 `auth state==2`、`identification state==6`，并包含在识别声明对应的集合中；认证/识别的引导消息有例外。不能把“所有消息都要求认证+识别完成”写成循环依赖。

`B11` 的 `authAndIDComplete` 标 endpoint initialized、创建/启动 features；无线 CarPlay bridge connect 还依赖 connectionUUID、endpointUUID 和 parent connection。缺失时有明确错误：`Missing connectionUUID, endpointUUID, or pConnection for wireless CarPlay bridge connect`。

### 4.2 九问与验收

| 问题 | 当前结论 |
|---|---|
| 进入条件 | 当前 iAP2 控制 session 可用；识别和认证各有本地状态，不以单一 UI 阶段代替。 |
| 发起方/承载 | 手机发识别/认证请求，配件回识别信息/证书/签名；均承载于当前控制 session。 |
| 请求/响应 | 上表是骨架，不是完整强制排序；认证继承和 session version 分支必须保留。 |
| 字段/必填/缺省 | 已核验的 nonce、signature 和状态门槛如上；IdentificationInfo 全表、证书链与 AA06 分支列入 OPEN。 |
| 固定/动态 | 消息号固定；证书来自配件；nonce每次认证上下文生成；签名绑定当前证书与nonce，不能复用旧会话。 |
| 接受/拒绝 | 原验证回调与识别校验分别决定结果；不允许为了“跑通”无条件发 AA05/1D02。 |
| 成功证据 | 识别Accepted、配件认证完成、声明的CarPlay/WiFi feature与消息集合满足、相应业务实际启动；各项分开记录。 |
| 超时/重试/清理 | 本轮不宣称全局固定认证/识别超时；需补状态机计时器所有者、重复消息与失效回调行为。D：日志记录验证错误类及当前会话代次，不记录完整密钥或nonce签名素材。 |
| 下一预期事件 | feature启动、无线可用性/传输标识通知、Wi-Fi配置请求或CarPlay平台回调；具体分支由已识别能力和用户状态决定。 |

## 5. 阶段 B3：无线可用性与网络信息

### 5.1 `0x4300` 与无线状态通知不是同一消息

`S/B14`：`iap2_CarPlayAvailability` 接收平台 dictionary。仅当 `wiredAvailable`、`wirelessAvailable` **至少一个对象存在**时构造 `0x4300`；不是判断其中至少一个值为true。

| `0x4300` 参数路径 | 类型 | 出现条件/来源 |
|---|---|---|
| `0/0` | Bool | 有 `wiredAvailable` 对象；有线分支，仅用于区分，不混入无线必需流程。 |
| `0/1` | C string | 有 `usbIdentifier` 对象且组0已创建。 |
| `1/0` | Bool | 有 `wirelessAvailable` 对象。 |
| `1/1` | C string | 有 `bluetoothIdentifier` 对象且组1已创建。 |
| `2/0` | Bool | 有 `themeAssetsAvailable` 对象。 |

不要硬编码“无线可用=true”。`B13` 另有设备通知 `0x4E0D`，参数0为U8，可用值由按配件证书serial查询的平台策略获得；重复可用性可被抑制。发送传输标识还检查请求订阅、无线允许、CarPlay已配对、未发送过等条件。消息 `0x4E0E` 的完整字段编码尚未在本轮闭合。

### 5.2 `0x5702` 请求与 `0x5703` 响应

`S/B15`：手机先经 `checkRequiredMsgIDs(...,count=2)` 检查能力声明，再发送无本函数添加参数的 `0x5702`。这是 feature 条件调用，不能看见链路建立就无条件发。

`S/B16`：配件发 `0x5703`，按下表解析，再异步交给平台工作队列；返回1仅代表本地handler接收/交接。

| 参数ID | 线值类型 | 接收去向与边界 |
|---|---|---|
| 0 | Data | 候选 BSSID，按实际长度建立CFData；此handler未强制长度6。不可把“通常MAC”提升为此函数的已证实长度门槛。 |
| 1 | C string | SSID；平台后续使用。 |
| 2 | C string | passphrase；不要把明文写入诊断文档或日志。 |
| 3 | U8 | securityType；转为CFNumber不改变线宽。枚举名称的完整映射尚 OPEN。 |
| 4 | U8 | channel；同样不是U16/U32。频段/带宽不能从这个单字节凭空推出。 |
| 5、6 | 未消费 | 本handler switch直接跳过；不可编造其语义。 |
| 其他 | 未识别 | 有诊断分支，继续遍历。 |

`S/B21`：WiFiSharing平台消费函数在 SSID=nil，或“passphrase对象存在且securityType==0”时不设置CarPlay Wi-Fi参数。它只证明nil判断，不证明空字符串也被该判断拒绝。`securityType>=3` 进入invalid诊断并给映射结果置0，**不能把这段误写成必然return拒收**；后续保存/关联结果还需追踪。

### 5.3 `0x4301`：车机要求手机启动会话

`S/B12`：方向为**配件→手机**，不能让手机仿照配件发送。handler只接消息号 `0x4301`，解析后调用 `platform_CarPlay_startSession`（`0x100063fd0`）。

| 参数路径 | 字段 | 线值类型 | 缺省/重复/来源 |
|---|---|---|---|
| `0/0` | usbIP | C string，可重复 | 追加USB数组；无线流程不应把它冒充Wi-Fi地址。 |
| `1/0` | ssid | C string | 缺失保持空槽；配件给定。 |
| `1/1` | pass | C string | 缺失保持空槽；日志脱敏。 |
| `1/2` | channel | U8 | 单字节，不猜默认信道。 |
| `1/3` | wifiIP | C string，可重复 | 按出现次序追加数组；IPv4/IPv6与接口scope需下游独立校验。 |
| `1/4` | securityType | U8 | 不把容器中的数值宽度当线宽。 |
| `2` | port | U32，大端 | 不是U16；合法TCP端口范围是下游消费约束，不能从U32 getter推得已校验。 |
| `3` | deviceID | C string | 不由字段名推定必为MAC。 |
| `4` | pubKey | C string | 不能因名称就当原始DER或假定base64；编码尚待下游追证。 |
| `5` | srcVer | C string | 对端声明；不能当本端版本。 |
| `6` | sdkVer | C string | 对端声明。 |
| `7/0` | assetID | C string | 条件性资产元数据；是否为视频启动必要项待平台追证。 |
| `7/1` | assetVer | U32，大端 | 缺失不等于线上发送0。 |
| `8` | mutualAuth | Bool | 缺失为空槽，不自动等同false；是否开启额外认证由下游决定。 |

`S/B17–B20` 的参数 getter 确认 TLV 总长含4字节头：U32总长8，U8总长5，Bool总长5且值仅0/1，字符串总长至少5且最后一字节NUL。字段组仍按嵌套TLV解析，不能把14项铺成平面ID0…13。getter长度检查不替代外层边界/消息完整性检查。

原函数 `0x10016d9f0` 的空参数路径清空所有标量后仍继续交接；所以“14项全部非空”不是此handler的要求。未知ID继续，已知字段解析失败走忽略本消息路径；本轮未见统一的 `0x4301` 错误响应，不能自行编造线上ACK。标量重现为覆盖槽，IP字段为追加；但**平台最终要求哪些字段组合仍 OPEN**。

平台调用第一个参数由 primary endpoint 查 legacy ExternalAccessory connection ID 得到；其后才是14项。connection ID 不是 AirPlay deviceID，不是本次UDP/TCP端口，也不能用USB endpoint指针替代。

### 5.4 九问与网络验收

| 问题 | 当前结论 |
|---|---|
| 进入条件 | 相应识别能力与业务准入满足；用户无线允许/CarPlay配对状态分别可用。 |
| 发起方/承载 | 5702手机→车机、5703车机→手机；4300手机→车机、4301车机→手机，均当前iAP2控制session。 |
| 请求/响应 | 不将四条绑定成单一事务；5703给凭据，4301给启动参数。 |
| 字段/缺省 | 如上三表；缺失对象与值false/0明确区分。 |
| 固定/动态 | 消息ID与参数ID固定；SSID/口令/地址/port/标识由当前配件及平台状态产生；禁止照抄他车值。 |
| 接受/拒绝 | iAP2 handler语法检查、平台Wi-Fi策略、OS网络安全协商是三个独立层级。 |
| 成功证据 | 配置已收仅是B3a；Wi-Fi关联与安全握手完成为B3b；地址/路由和目标接口可达为B3c；服务端点建立另属AirPlay阶段。 |
| 超时/重试/清理 | 尚未确证统一Wi-Fi join超时与重连策略；建议按配置接收/关联/地址配置/服务发现分计时。不能认证失败就删除BT bond，也不能短暂断线就删所有Wi-Fi凭据。后两句为D。 |
| 下一预期事件 | 若仅有凭据，等待网络建立及适用的端点发现/邀请；若4301已有端点，也必须经实际网络可达与平台允许检查，不能直接宣称会话成功。 |

## 6. 首次、再次、异常重连的状态要分别保存

| 状态 | 首次连接需确认 | 已配对再次连接需确认 | 断线清理/重连需确认 |
|---|---|---|---|
| BT bond | 用户是否完成配对 | bond是否仍有效 | 不由业务超时自动抹除bond（D） |
| CarPlay授权 | 无线是否允许、是否已CarPlay配对 | 按配件证书身份重新读取允许状态（B13） | 用户撤销授权与暂时断线分别处理 |
| Wi-Fi凭据 | 从哪条消息获得，平台是否接受 | 是否存在、是否与当前车身份匹配 | 换SSID/密码时不能无限复用旧配置 |
| iAP2 link/session | 新建seq/ack及协商session | 不把bond当已建立业务session | 丢弃旧承载的重组、重传和回调关联（D） |
| 配件认证 | 真实验证结果 | B07存在继承/版本分支，但不能无条件跳过 | 新nonce不得混用旧签名/证书关联（D） |
| AirPlay身份 | 见AirPlay章节 | 与上述状态不同层级 | 不用本章推定Pair-Verify可跳过 |

表中没有证据键的项是**待验证的问题/诊断建议**，不是已证明的苹果生命周期。需要以相同车机的首次/再次/异常恢复三组时间线验证。

## 7. 卡阶段定位与待补证

| UI停留位置 | 最后成功事件 | 下一期望/缺失事件 | 需区分的原因与证据 |
|---|---|---|---|
| 蓝牙 | bond成功 | 目标WiAP SDP记录、动态channel、RFCOMM连接 | 服务选择/UUID表示、失效通道、平台拒绝、另一蓝牙profile连接冒充成功；要SDP原始记录及socket结果。 |
| 蓝牙/iAP2 | RFCOMM连接 | 完整Detect/SYN/SYNACK/ACK及Connected | 谁先发、流重组、协商参数、seq/ack、重试；需要双向payload时间线，不能只看总字节数。 |
| iAP2 | LinkConnected | 1D02成功与真实AA05认证完成 | 识别字段被拒、证书/挑战失败、handler未被声明；要识别状态、认证错误、消息集。 |
| iAP2 | 认证/识别完成 | feature启动、无线允许、5702或4300相关事件 | 用户授权/CarPlay配对、missing endpoint/connection身份、消息能力缺失；查B11/B13明确分支。 |
| iAP2/AirPlay | 收5703或4301 | 平台配置接受、Wi-Fi安全握手与地址配置 | SSID空/不存在、security矛盾、旧凭据、网络绑定错误；查OS关联与IP接口，口令仅记是否存在。 |
| AirPlay | 网络可达 | 实际端点解析/邀请与控制连接 | 不能把5703视为给了IP/port；不能把4301数组首项永远当可用地址；见AirPlay章节。 |

优先OPEN清单：

1. `B-OPEN-01`：首次发现、配对授权触发、被动RFCOMM路径、新WiAP UUID线表示、服务查询失败策略。
2. `B-OPEN-02`：**部分关闭**，见 [11](11-iap2-state-machine.md)：Detection 长度及局部状态表、SYN 基本布局、发送/重发计数和计时器归属已补；运行时触发、完整 profile/session、ACK 边界和所有 transport 差异仍 OPEN。
3. `B-OPEN-03`：**部分关闭**，见 [12](12-identification-contract.md)：注册required-success语义、核心字段、条件组件和1D03拒绝格式已核对；所有嵌套/feature组合、更新识别、授权取消与运行覆盖仍OPEN。
4. `B-OPEN-04`：证书链信任、AA06、session认证继承、nonce算法/长度与真正验证成功的独立证据；本章不宣称完成认证密码学复现。
5. `B-OPEN-05`：5703平台交接到carkitd的完整关联；security枚举及异常结果；保存/更新/删除Wi-Fi凭据的决策者。
6. `B-OPEN-06`：**部分关闭**，见 [21](21-endpoint-fusion.md)：字段交接及局部门槛已补；IP 候选优先级、角色/scope/provider 合同、身份匹配与 Bonjour/邀请完整融合仍 OPEN。
7. `B-OPEN-07`：首次、再次、异常断线三场景的实际时序和时间预算；本轮静态证据不足以称这些场景已验收。

本章没有修改任何手机或车机代码，也没有以模拟互通代替实车视频显示验收。
