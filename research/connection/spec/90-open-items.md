# 开放问题与完成审计

初始审计日期：2026-10-30；缺口台账更新：2026-11-10。本文是本目录的收口清单，不是苹果协议的补充规范，也不是“已经能投屏”的声明。每项必须有对应的原始证据、同一连接 attempt 的关联时间线，或车机端可观察结果后才能关闭。

本次新增的实现缺口见 §3.4，文档同步和修复后的设备验收见 §3.5；以 Android `67b68e3`（Release 20013）的已有静态复查为记录基线。此前分批审计及阶段门槛保留各自证据范围，本次不将其整体升级为通过。

## 1. 证据等级

新增[86 — 初始握手错误ACK恢复](86-iap2-pending-ack-recovery.md)：手机已对已发SYNACK后的窗口外纯ACK添加RST/同传输等待新SYN，保留预算；78项局部原指令向量不是完整iPhone或实车验证。七次ACK-only/NO_SYN的来源与恢复仍OPEN，gap1接受及连接后容错未泛化，G3/G12不因此关闭。

最新[83 — 手机端异步网络交接](83-network-handoff-implementation.md)已实施可用配置立即联网、ctrl提前发布、单消费者迟到4301、端点提交冻结、失效/取消和注册清理；协议970+core79=1049项通过，小米Kotlin编译成功。JVM测试未运行Android平台网络或完整SessionController，仍需首次/再次/已有Wi-Fi实测；完整availability、重连身份融合及原生security枚举继续OPEN，G5/G7不整体关闭。

此前只读比较见[82 — 网络交接三方核对](82-network-handoff-three-way-audit.md)：当时入口未接5703/4301、先发现后发布及迟到4301无分派已定位，现由83有界实施。原5703独立异步平台交接及识别/connectionType门已核；20函数原字节核验不等于全部分支或运行通过，旧源码哈希保留不覆盖。

最新实施见[81 — 承载组件与消息组合](81-identification-components-message-batch.md)：17/24解析和本地上下文要求、三层能力分离、22/26消息组合及拒绝内容已接入手机。最终1007项本地测试与小米Kotlin编译通过；8/9与其他feature/承载、生产信任和实际网络/车机表现仍独立待证，G4/G5不因此整体关闭。下一步聚焦网络交接不同路径，不新增车型脚本或未声明5702试探。

| 标记 | 含义 | 可以得出的结论 |
|---|---|---|
| `CLOSED-STATIC` | 原 24A446 镜像中已定位函数/字节，并完成指定范围复核 | 该代码路径在该镜像中存在；不等于所有设备都走该分支 |
| `OBSERVED` | 有可关联的运行日志或抓包 | 只适用于记录中的设备、版本和承载；不能外推到未观察分支 |
| `PARTIAL` | 上游或下游检查点已证实，但跨模块链条未闭合 | 可用于定位下一步，不得标作端到端成功 |
| `OPEN` | 仍缺直接证据或存在多个条件分支 | 保留未知；不能用固定值、注释或相邻日志填空 |
| `NOT_RUN` | 测试矩阵中尚未实际执行 | 不是失败，也不是通过 |


后续[64](64-identification-deep-review.md)新增Identification四路深度分支表，确认了初次/更新/取消、注册分派和字段重复处理的更多差异；本轮未修生产代码，G4仍为PARTIAL。未执行的分支向量、平台provider/CF及授权取消依赖不可因文档增多改为通过。

再后续[65](65-identification-lifecycle-batch2.md)已经落实手机端初次/更新/取消/拒绝纠正入口和实际蓝牙/Runtime消费，本地协议713项、core79项通过。仅对应本批列出的生命周期/更新向量转为本地已执行；初次全字段、provider/CF、原授权回调、其他feature及车机运行仍未闭合，G4不因此升级。

最新[66](66-identification-core-batch3.md)将初次0–7/12/13/34的有序处理、核心required成功集合、真未知/19拒绝和精确拒绝重复项落到手机端，全量741+79=820项通过。Power来源调查见[19](19-identification-power-provider-context.md)，但8/9生产校验、承载组件、消息组合与全部feature尚未接入；原CF/授权和端到端运行仍OPEN，G4仍PARTIAL。

再后续[67连接主线第四批](67-connection-mainline-batch4.md)已实际落实网络语法/部分配置等待、同源地址端口、CU能力错误分类、SETUP内嵌info/skipRecord/可选事件端口/屏幕响应/prepare失败与迟到成功清理；全量811+79=890项通过。原属性来源及SETUP局部链新增于25/26/27。已知部分差异已修，但G5/G8/G9不因此整体关闭；网络身份融合、完整安全事务、请求presence、所有恢复分支及实车仍OPEN。

## 2. 从蓝牙到首帧的完成门槛


最新[79](79-iap2-renegotiation-batch.md)已实施78的有界pending再次协商：当前work逐字段合并、第二SYNACK继续等待确认、latest peer限制、generation/session/版本最后生效，并保留提议/重发预算。定向108项、完整协议模块897项通过；只改手机，不改车机、不打包。可靠模式中途切换、同PSN内容变更、全容错/profile/session/实际互通仍未完成；G3不升级为端到端完成。


最新[77](77-iap2-extension-wait-boundary.md)在76基础上落实54/55原生OR集合语义与回归：成对重复项不再被手机端过严拒绝；定向70项、完整协议模块875项通过。指定XPC服务/对象/协议参数交接及HID首层回调仍为CLOSED-STATIC；publish通知下游已追到XPC client filter/remote proxy边界，受限模式对普通蓝牙type=2已排除，但上层预算和其他入口仍PARTIAL/OPEN。发现的5秒睡眠断言到期定时器不等同iAP2 SYN等待。G3不升级。


后续[75](75-iap2-link-repair-batch.md)已按24A446有界分支实现pending新SYN恢复、SYNACK定时重传和54/55扩展集合校验；定向67项及最终完整模块872项通过。实车双端字节流、跨进程入口、上层超时、第二SYNACK完整重协商及Identification仍未关闭，G3继续PARTIAL。


| 阶段 | 必须闭合的事实 | 当前状态 | 证据入口 |
|---|---|---|---|
| G1 设备前提 | 首次配对/授权或已存在 bond 的状态被单独记录 | `OPEN` | [10](10-bluetooth-iap2-network.md) B-OPEN-01、[50](50-test-matrix.md) T01/T02 |
| G2 RFCOMM | 目标服务、实际 socket/handle、方向和连接世代 | `PARTIAL` | B01；禁止用蓝牙图标替代 |
| G4 识别与认证 | Identification、配件认证、能力声明和业务 gate 各自成功 | `PARTIAL` | [12](12-identification-contract.md) 静态合同、[65](65-identification-lifecycle-batch2.md)/[66](66-identification-core-batch3.md)手机有界实施；AA/全feature/运行证据仍独立待证，不得合并为一个authenticated位 |
| G5 网络/启动输入 | 5702/5703 与 4300/4301 的实际字段、平台消费和分支选择 | `PARTIAL` | B-OPEN-05/B-OPEN-06 |
| G6 网络就绪 | 关联、安全、有效地址、接口和路由均有记录 | `OPEN` | 10 §“平台交接”；不能把收到 5703 当作已联网 |
| G7 端点/邀请 | `_carplay-ctrl._tcp`、发现、邀请或 4301 端点的实际入口和身份匹配 | `PARTIAL` | [20](20-airplay-session.md) A、[21](21-endpoint-fusion.md)、AP-U01/AP-U02；局部汇合不等于完整身份/端点链 |
| G8 AirPlay 控制 | 当前控制 TCP、配对/验证、key holder、控制 SETUP 和事件路径 | `PARTIAL` | 20 B–D、[22](22-control-wire-contract.md)；封装/响应局部证据已补，安全路线和全量字段仍有 OPEN |
| G9 视频流 | 单流 SETUP 响应恰一项且 type 匹配，数据端口可达 | `PARTIAL` | [30](30-video-first-frame.md) V02/V03的局部结构校验已静态证明；端口可达/整段运行未证明 |
| G10 记录与帧 | RECORD（若条件要求）、配置记录、关键帧和后续帧实际写出 | `PARTIAL` | 30 V05–V08、[31](31-video-codec-contract.md)；avcC/附件/cryptor局部已补，实际样本/写出与全部生命周期仍 OPEN |
| G11 首帧显示 | 目标车机出现本次会话可辨识画面 | `OPEN` | 30 V-OPEN-07；手机预览或 socket 写出不算 |
| G12 持续更新/重连 | 观察窗口内持续变化，断开后新 attempt 独立恢复 | `OPEN` | 50 T03/T09、[24](24-disconnect-reconnect.md) 局部退出不能替代实际重连；30 V-OPEN-07 |

一次显示的G1–G11应能关联到该次attempt，已有bond/网络等前提可引用其来源；G12的重连必须跨旧、新两个attempt分别验证。静态函数审计可以关闭有明确边界的结构性问题，但不能替代G11/G12的车机观察；不可因某函数已静态验证而把整段端口可达或视频成功标为关闭。

## 3. 未关闭问题总表

### 3.1 蓝牙、iAP2 与网络

| 编号 | 问题 | 关闭所需证据 |
|---|---|---|
| B-OPEN-01 | 首次发现、配对授权触发、被动 RFCOMM 路径、新 WiAP UUID 线表示和服务查询失败策略 | 同一车型首次配对的系统结果、SDP 原响应、实际 socket 方向及失败分支 |
| B-OPEN-03 | IdentificationInfo 全字段验证、必需组合、重识别和 1D03 拒绝字段（部分关闭） | [65](65-identification-lifecycle-batch2.md)/[66](66-identification-core-batch3.md)已实现有界生命周期/核心字段；[80](80-identification-three-way-audit.md)复核当前三方差异。仍缺8/9、承载组件/全部feature校验、组件能力与交接分层、原异步授权及实车正负样本；不把已修更新/取消重复写为完全未实现 |
| B-OPEN-04 | 证书链信任、AA06、session 认证继承、nonce 算法/长度和真正验证成功 | 脱敏的挑战/响应结果、验证失败负例、peer-store 提交边界；不记录秘密 |
| B-OPEN-05 | 5703 平台交接到网络服务的完整关联、security 枚举和凭据生命周期 | [82](82-network-handoff-three-way-audit.md)定位缺口，[83](83-network-handoff-implementation.md)已接通本轮协调器及复用失网监控；仍需验证Android回调/接口/路由/异常与实际连接，原生security枚举未闭合。不将Wi-Fi凭据写入日志 |
| B-OPEN-06 | 4301 字段组合、IP 候选优先级、接口绑定，以及与 Bonjour/邀请的融合（部分关闭） | [21](21-endpoint-fusion.md) 已核对字段交接和局部门槛；还缺跨入口身份匹配、端点角色、真实 provider/scope 合同与实际选中连接的证据 |
| B-OPEN-07 | 首次、再次、异常断线三种场景的真实时序和时间预算 | 每种场景独立 attempt、资源清理和重连结果；不能以一次成功覆盖三种场景 |
| B-OPEN-08 | Android公共接口不能精确表达的蓝牙行为：共享SDP通道、profile属性、接纳前拒绝、完整记录查询语义 | [71 §11平台缺口台账](71-android-bluetooth-feasibility.md)的BT-LIM-01～04逐项取得系统能力及实际行为证据；应用层近似不算关闭 |

### 3.2 AirPlay 控制与安全

| 编号 | 问题 | 关闭所需证据 |
|---|---|---|
| AP-U01 | 4301、5703、Bonjour 邀请与车辆身份在平台层的融合顺序（部分关闭） | [21](21-endpoint-fusion.md)补局部汇合；[82](82-network-handoff-three-way-audit.md)定位条件互等/迟到丢弃，[83](83-network-handoff-implementation.md)已实施有界异步协调及同一publication复用。首次/重连/已有网络时间线、端点身份融合与提交后重连策略仍OPEN |
| AP-U02 | endpoint 属性的线端来源、缺失默认和 override（部分推进） | [68](68-connection-mainline-batch5.md)补Bonjour fex变长解析、source/problem保留和F80拒绝误选；认证前/后info更新、全部override及身份绑定仍未闭合，不得把缺失属性全设为false |
| AP-U03 | 当前车机能力所选 pairing/auth 路线的线格式、peer-store、证书和签名约束 | 一条完整密码学事务及错 peer、坏签名、取消、部分提交负例 |
| AP-U04 | 全栈超时、重试预算和请求 URL 构造（部分关闭） | [22](22-control-wire-contract.md) 已核局部URL/CSeq/waiter；[24](24-disconnect-reconnect.md) 补kind5控制输入10/event默认60或覆盖、条件fallback；完整URL、底层绑定/全部覆盖/实际时间线仍OPEN |
| AP-U05 | `skipRecord` 与内嵌 `info` 的来源与消费（部分关闭） | 原共享缓存的精确键名与 getter 已由 [control-response-keys.json](../evidence/control-response-keys.json) 核对；仍缺所有响应生产者、类型异常及 Stage2 跨会话消费，不推断 RECORD 必发/必省 |
| AP-U06 | 全量字段 presence、timing 和功能协商（部分推进） | [68](68-connection-mainline-batch5.md)落实kind5提前结束、真实timingPort、缺省features省略；boot correlation、TransportType、全部feature生产及网络时钟算法仍OPEN，不能把通用AirPlay字段表当必填 |
| AP-U07 | 正常 TEARDOWN、部分流关闭、恢复重试和跨队列世代保护（部分关闭） | [24](24-disconnect-reconnect.md) 已核条件字典、注销先于发送、局部清理与返回值边界；全错误出口、race、配对记录和真实恢复仍OPEN |
| AP-U08 | 真实持续显示与重连 | 同一车机、同一版本的控制/发送/显示关联记录；Started 或 socket 写出不够 |

### 3.3 视频首帧与持续传输

| 编号 | 问题 | 关闭所需证据 |
|---|---|---|
| V-OPEN-01 | display 线上字段到内部属性/编码参数的映射及屏幕资源许可（部分推进） | [31](31-video-codec-contract.md) 已核字典类型门与MaxFPS条件上限；完整getter/资源/最终编码器映射仍OPEN |
| V-OPEN-02 | 24A446 screen SETUP 的完整 presence、URL、超时及与 RECORD/资源许可的偏序（部分推进） | [32](32-screen-setup-request-branches.md)/[68](68-connection-mainline-batch5.md)落实75ms无线默认、普通显示UUID与kind5不自动生成timestampInfo；extras、aux、streamID/密码生命周期及资源许可仍OPEN；需区分初配与重连 |
| V-OPEN-03 | TCP 记录路径与其它屏幕传输路径的选择条件 | 精确能力门和模式门；不从系统含 UDP 类推所有 CarPlay 必须 UDP |
| V-OPEN-04 | NAL 长度、SPS/PPS、profile/GOP/位率以及关键帧实际随机访问（部分推进） | [31](31-video-codec-contract.md) 已补avcC/附件规则；原编码样本、NAL及随机访问/离线解码/实车仍缺 |
| V-OPEN-05 | cryptor 完整生命周期和 legacy 材料链（部分推进） | [31](31-video-codec-contract.md) 已核现代虚表/导入/初始零计数/AAD；legacy完整材料、异常/重用/恢复仍OPEN |
| V-OPEN-06 | 所有退出原因到 Suspend/teardown/重连的转换和超时（部分关闭） | [24](24-disconnect-reconnect.md) 已核Suspend/fatal的skip生产链；全部原因、异步取消和真实重连未证 |
| V-OPEN-07 | 目标车机收到并显示 24A446 对应视频 | 对齐版本的两端记录、首帧/持续更新/重连验收 |

### 3.4 官方资料续查后的实现缺口（2026-11-10）

来源：[苹果官方资料续查](official-followup-20261110.md)与[分项修复记录](../../../android/docs/fixes/2026-11-10-followup-status.md)。Android 基线：`67b68e3c143d6a9c3b9c7e775906b64f31b60710`（Release 20013）。本节整理已有审查结果，没有新增原固件审计或实车结果。

下表沿用续查的 G01–G11 编号，与 §2 的连接阶段 G1–G12 分属不同清单。`PARTIAL` 表示已有相关实现但链路未闭合；`OPEN` 保留未实现能力、证据缺口或尚未验证的边界风险。公开资料只能说明其适用年代的功能方向，线上字段和状态转换仍须原固件证据。

| 编号 | 优先级 | 状态 | 剩余缺口与证据入口 | 关闭条件 |
|---|---|---|---|---|
| G01 | P0 | `PARTIAL` | 组合请求和拒绝后的空状态通知已修，见[实施记录](gap-implementation-20261110.md)；完整资源约束、TurnByTurn / PhoneCall / Speech及临时借用恢复仍未闭合。 | 闭合原固件请求、优先级、约束消费与状态发布；覆盖原生电话、语音、倒车借屏、导航交替和异常恢复。 |
| G02 | P0 | `PARTIAL` | 通话双向音频与仪表状态：已有 telephony 输入；CarWith原DEX已追到共享mic队列及SDK助手读取适配器，见[宿主证据](carwith-4.0.14-host-evidence.md)。蜂窝modem/HAL消费、专用下行、真实电话快照及4155/4158仍未闭合。 | 分别取得上下行消费者、真实电话状态和订阅门证据；验证双方声音及仪表状态。OFFHOOK或普通助手/VoIP回调成功不能代替蜂窝接通或上行成功。 |
| G03 | P1 | `PARTIAL` | 已按CarWith原DEX修复isNavi=false/action3结束后的双层缓存清理，见[分项实施](gap-implementation-20261110.md)及[宿主证据](carwith-4.0.14-host-evidence.md)。活动道路/距离iAP语义、guidanceState、TurnByTurn及5202/5204仍未闭合。 | 米制转换及宿主生命周期已核；继续核地图数据完整语义、iAP单位/状态/机动/车道映射，分别验收仪表/HUD与订阅重建。 |
| G04 | P0 | `PARTIAL` | 已修正有序候选读取、零集合遮蔽、default覆盖/厂商门和扩展保存，见[分项实施](gap-implementation-20261110.md)。原规则见[能力选择 R-12.2](../../protocol/airplay_audio_mic_channel/spec/12-capability-selection.md)。最终单格式选择、政策绑定及完整extended schema仍未闭合。 | 已证候选差异有14项新增回归；继续闭合最终格式选择、本地编解码交集及实际选值，不将局部修复作整体完成。 |
| G05 | P1 | `PARTIAL` | 100/101输出控制口与spf条件已修，见[实施记录](gap-implementation-20261110.md)；SETUP latency=100、本地延迟政策绑定及采集时间映射仍未闭合。 | 已核延迟首字段来自本地政策，继续闭合构造/选择绑定与时间来源；不能直接把接收端微秒延迟换算为SETUP字段。 |
| G06 | P2 | `OPEN` | 增强媒体缓冲：未接通按能力选择的缓冲媒体发送、控制和同步链。见[续查 §4](official-followup-20261110.md#4-音频公开架构之外还有已经可定位的实现差异)。 | 核实接收端能力、固件流选择和可提前传送的数据源；闭合暂停、清除、媒体时间线及重新入队。导航本地缓冲不构成此能力。 |
| G07 | P2 | `PARTIAL` | 增强 Siri / Aux 音频：已有语音动作和普通输入，触发时间、历史音频、辅助输入/输出及并行媒体链未闭合。见[续查 §4](official-followup-20261110.md#4-音频公开架构之外还有已经可定位的实现差异)。 | 核实车端声明、时间单位、Aux 调用链与宿主消费者；明确车端 ECNR/历史采集职责，不能以本端语音动作代替完整 Siri 能力。 |
| G08 | P1 | `PARTIAL` | 单击切换、标准系统快进/快退映射、DOWN/UP及断开清理已修；另按CarWith原DEX补歌词展示的唯一播放器匹配，Android `3c92c9d`，见[实施记录](gap-implementation-20261110.md)。通知访问仍必需，目标应用持续seek/释放停止的消费与效果仍未闭合。 | 核宿主或目标应用begin/end seek契约；分别验证快进、快退、释放和取消，不把媒体键投递当播放确认或猜测长按连发。 |
| G09 | P2 | `OPEN` | HEVC：当前只选 AVC，HEVC 流声明与帧封装未实现。见[续查 §5](official-followup-20261110.md#5-输入显示和网络的进一步缺口)。 | 核接收端与编码器能力、流声明和帧配置；验证协商及显示，保留 H.264 兼容路径。 |
| G10 | P2 | `PARTIAL` | 多屏、尺寸与焦点：单显示/单视频实例，动态区域、触摸坐标、焦点位置及每屏外观未闭合。见[续查 §5](official-followup-20261110.md#5-输入显示和网络的进一步缺口)。 | 闭合每显示身份、会话与能力门；验证区域变化、编码/触摸同步、焦点位置和每屏外观。 |
| G11 | P1 | `OPEN` | 短暂断链边界：API36原SDK及官方回调合同已核，onLost也可表示不再满足请求；register观察与request选择分别处理，见[事件边界](g11-network-callback-boundary.md)。目标ROM短暂L2抖动、Network与socket关系仍未证明。 | 分类L2、请求条件、网络租约/替换与实际TCP错误；核可保留socket的条件和失败预算，再做干扰/切换测试。不能据此添加盲目等待。 |

建议顺序：先 G04 与 G01，再 G02/G03；随后 G05/G08。G11 先核事件边界；G06/G07/G09/G10 按接收端能力及数据源条件推进。每项实施和验收独立记录，不以一项成功关闭整组。

### 3.5 文档同步与修复后的设备验收

| 编号 | 状态 | 待办与关闭条件 |
|---|---|---|
| D01 | `OPEN` | [音频流规范 R-1.6](../../protocol/airplay_audio_mic_channel/spec/01-audio-streams.md)仍将独立导航流视为未决并建议可配置用途。需对照[导航生命周期实施记录](89-navigation-audio-lifecycle.md)及[续查 §6](official-followup-20261110.md#6-研究文档本身也需要同步证据边界)，同步来源、适用层与剩余线上字段边界；不能将公开功能说明升级为固件字段 CONFIRMED。 |
| R01 | `OBSERVED` | Release 20013 用户实测图片频闪，日志36对空/非空引用，见[本次反馈](media-feedback-20013-20261110.md)。已修复带图元数据的中间清空并增加图片去重，桥接27项测试及小米编译通过；新实现未实车复测。需关联图片获取、订阅、传输标识与稳定显示后才能关闭。 |
| R02 | `NOT_RUN` | 导航首段缓冲已有实现；SETUP 前结束、缓冲溢出、短提示首尾、切回音乐卡顿及音量恢复仍需设备验收。分别关联 PCM、RTP、最后包/TEARDOWN 和听感，不将本地 drain 成功当作播放完整。 |
| R03 | `OBSERVED` | Release 20013 用户实测暂停无效；14次相关按键全部为Play，47次播放器状态均unknown，用户确认未开启通知访问，见[本次反馈](media-feedback-20013-20261110.md)。后续 `3c92c9d` 按原DEX补歌词展示时的完整组合匹配，见[宿主证据](carwith-4.0.14-host-evidence.md)，不是该次未授权测试的唯一根因证明。先授权「音乐播放状态同步」，再关联普通/歌词展示下的真实状态、5001发布、HID输入和宿主实际动作；验收仍未关闭。G08 持续按键另验。 |

R01/R03 已记录 Release 20013 的失败反馈与运行前提；最新图片修复尚未实车复测，R02 的导航边界验收仍待执行。历史 Release 20005 的焦点音频及仪表文字用户反馈保留在[媒体反馈](media-feedback-20261110.md)，不能代替修复版本的图片、按键或导航边界验证。

组合资源请求、资源结果版本隔离、单击切换和导航启动缓冲已在[分项修复记录](../../../android/docs/fixes/2026-11-10-followup-status.md)中记录，不再列为完全缺失。WPA3、4301 接收及 iAP2 端点交接也已有代码，后续按条件验证。下一代车端 Local UI / Overlay / Punch-through 保留为扩展研究，不纳入当前手机端 APK 的缺失功能数量。

## 4. 关闭流程

每个 OPEN 项目按以下顺序处理：

1. 先声明目标 `attempt_id`、手机构建、车机/固件和网络前提；不要把不同版本的日志拼成一条成功链。
2. 只改变一个实验条件，保留成功或失败基线；敏感材料记录长度、哈希或脱敏 ID。
3. 记录最后一个已成功检查点、下一预期事件、实际结果和证据定位。控制消息按连接、CSeq、方向关联，iAP2 按链路世代和 session 关联。
4. 先闭合发送端写出，再分别确认车机接收、解密、解码、首帧显示和持续更新；上游日志不能代替下游观察。
5. 通过后在本表与对应专项章节同时更新状态，并保留原始证据哈希；若只得到静态证据，标 `CLOSED-STATIC`，不得改成 `OBSERVED`。

## 5. 当前结论

Identification三方历史审计见[80](80-identification-three-way-audit.md)，当前有界实现与结果见[81](81-identification-components-message-batch.md)；最新SYN再次协商实现见[79](79-iap2-renegotiation-batch.md)。[77](77-iap2-extension-wait-boundary.md)保留扩展/等待边界证据。75/76中的扩展重复项“待修正”是历史状态，手机端已在77完成修正并通过回归。普通BT type=2的受限模式和睡眠断言5秒≠SYN等待也已作边界排除；上层预算、所有入口、端到端互通仍OPEN/PARTIAL。

首次握手的第5项差异已单列于[74](74-iap2-startup-initiation.md)；[75](75-iap2-link-repair-batch.md)已落实前三项有界修复。当前仍支持接收驱动的局部原生路径，不支持将“主动发包一定更兼容”当作结论；完整入口策略仍PARTIAL。


