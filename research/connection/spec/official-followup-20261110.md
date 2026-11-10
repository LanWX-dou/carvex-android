# 苹果官方资料续查：当前实现的剩余缺口

日期：2026-11-10。Android 基线：`67b68e3c143d6a9c3b9c7e775906b64f31b60710`
（Release 20013）。接续 [此前四条链路复查](official-chain-review-20261110.md)，
重新检查其后四个修复提交；历史缺口不直接当作当前缺口。

本轮交付为官方资料与当前源码的静态对照。结论区分功能缺失、已有固件证据与实现差异、
以及需要设备验证的边界。没有新的实车结果；上一轮 APK 的测试结果不构成协议符合性证明。

## 1. 官方来源与适用范围

本轮直接从 Apple 官网获取以下页面及视频 transcript。原始 HTML、带时间点的句子索引
与 SHA256 清单保存在忽略目录 `local-backups/2026-11-10-official-followup/`。
这里使用转述与时间定位，不复制整篇资料。
另在线阅读 Apple AVFoundation 的增强缓冲开发文档；该项未保存完整页面快照。

| 编号 | 官方资料 | 本次使用的范围 |
|---|---|---|
| O16A | Developing CarPlay Systems, Part 1，WWDC 2016/722 | 480–522 秒：音频方向和当年的无线编码；752–758、1414–1422 秒：语音及媒体按键。 |
| O16B | Developing CarPlay Systems, Part 2，WWDC 2016/723 | 522–544 秒：导航音量上下文；585–599、1113–1252 秒：借用、归还和约束；1384–1530 秒：应用状态。 |
| O17 | Developing Wireless CarPlay Systems，WWDC 2017/717 | 无线建立、首次配对、传输切换的历史设计背景。 |
| O19 | Advances in CarPlay Systems，WWDC 2019/252 | 95–169、210–266、400–552 秒：显示区域、多流与动态尺寸；648–932 秒：增强 Siri 音频架构。 |
| O23 | Optimize CarPlay for vehicle systems，WWDC 2023/10150 | 110–188、315–504 秒：显示与焦点；680–810 秒：网络；822–964 秒：缓冲、混音及编码。 |
| O24 | Meet the next generation of CarPlay architecture，WWDC 2024/10111 | 183–393、470–592 秒：车端和手机端渲染的职责边界。 |
| OM | MFi 官方 FAQs，本轮获取 | CarPlay、iAP2 属于 MFi 技术；完整技术资料的访问范围。 |
| OAB | Implementing flexible enhanced buffering for your content，Apple AVFoundation 文档 | 支持车机上的提前传输、媒体时间线和缓冲清除后的重新入队；属于应用层 API。 |

官方地址：

```text
O16A https://developer.apple.com/videos/play/wwdc2016/722/
O16B https://developer.apple.com/videos/play/wwdc2016/723/
O17  https://developer.apple.com/videos/play/wwdc2017/717/
O19  https://developer.apple.com/videos/play/wwdc2019/252/
O23  https://developer.apple.com/videos/play/wwdc2023/10150/
O24  https://developer.apple.com/videos/play/wwdc2024/10111/
OM   https://mfi.apple.com/en/faqs
OAB  https://developer.apple.com/documentation/avfoundation/implementing-flexible-enhanced-buffering-for-your-content
```

这些公开系统资料能确认功能和方向，但没有给出完整的消息编号、枚举和密码协议。
O23 也将具体实现引向 CarPlay specification 与 communication plugin；MFi 技术资料
受其访问机制约束。本工作区现有材料不能因此宣称“已完整实现最新 Apple 规范”。
后续线上字段仍须绑定 24A446 原始固件证据，不能从视频中的功能名猜测整数值。

## 2. 已修复的部分重新定界

| 此前发现 | 当前状态 |
|---|---|
| 屏幕与音频只能单独申请 | `be8bb5b` 已支持当前传输子集中的组合申请；带约束的仲裁仍未支持。 |
| 迟到的资源结果覆盖新声明 | `9486ef8` 已增加版本隔离和准确回滚；没有补齐应用状态或完整借用历史。 |
| 方控切换从音频焦点或已发送键推测状态 | `cea62bf` 已改为发送时使用真实播放器状态；未知时保留原生切换，持续按键另查。 |
| 导航 SETUP 期间只留一块 PCM、超过 100 ms 丢弃 | `67b68e3` 已增加有界活动首段缓冲；提示提前结束、缓冲溢出与接收端播放仍有边界。 |
| 专辑图片只有检测，没有传输 | 当前已有图片读取与文件传输实现；显示结果仍需车机验收。 |

逐项细节见 [后续修复记录](../../../android/docs/fixes/2026-11-10-followup-status.md)。
“需要设备验证”与“没有代码实现”在本表中分别记录。

## 3. 共同的资源和通话链路：先补这一组

### G01：完整资源仲裁与三个应用状态，P0

O16B 明确区分永久占用与临时借用，并介绍请求优先级、限制和 TurnByTurn、PhoneCall、
Speech 的相互协调。例如电话结束应恢复之前的资源归属，原生电话不应被另一端电话打断。

[ScreenResourceModes.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/ScreenResourceModes.kt)
40–52 行仍拒绝非空 `appStates` 与约束字段；80 行将三个状态固定写为未知。
10 行的本端音频申请改变永久所有者并清除借用标志。
因此组合请求的修复没有补齐带约束仲裁、临时用途恢复及双方活动状态联动。

关闭条件：追完原固件请求生产、优先级决策、约束消费和状态发布；覆盖原生电话、
临时语音、倒车借屏、原生导航与手机导航交替，以及异常结束恢复的独立场景。
只解析约束再忽略它们不满足本项。

### G02：电话上下行及仪表状态来源，P0

O16A/O16B 描述双向电话音频；O19 290–324 秒也区分仪表电话信息与交互。
当前 `createCallMicrophoneLocked()` 建立的是车机到本端的 telephony 输入，
缺少已验证的宿主蜂窝 PCM 消费契约和通话专用下行来源。

[PhoneCallMonitor.kt](../../../android/platform-android/src/main/java/io/github/iamr0s/carvex/platform/PhoneCallMonitor.kt)
42–44 行只聚合 OFFHOOK 为 Boolean；其注释明确 OFFHOOK 也包含拨号和保持。
它没有输出可区分来电、接通、保持和结束的每通电话快照。
[PhoneSubscriptions.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/PhoneSubscriptions.kt)
100/146 行有状态编码器，但本轮源码检索没有找到生产调用将电话监听结果发布为
`4155`/`4158`。订阅被接受并不表示已提供状态。

关闭条件：分别确认宿主上下行消费者、可获得的真实电话状态和订阅发布门。
不得将 OFFHOOK 编成“对方已接听”，也不得把通用 PCM 回调返回成功作为上行通话成功。

### G03：导航生命周期、机动和车道，P1

O16B 的 TurnByTurn 状态负责双方导航协调；O19 的仪表/HUD 导航可采用 iAP2 元数据。
当前 [SessionController.kt](../../../android/bridge/src/main/java/io/github/iamr0s/carvex/session/SessionController.kt)
325–344 行只观察 `isNavi`、`action`、`navi_turn`；线上 5201 的宿主适配仍主要提供道路和距离。
`NavigationGuidance` 有 5202/5204 编码器，不能由此推断已接入机动和车道数据源。

关闭条件：取得宿主生命周期、距离单位、机动与车道枚举的消费者证据，连接开始、更新、
结束和订阅重建；再分别验证仪表显示。已有导航音频首段缓冲不替代这些元数据功能。

## 4. 音频：公开架构之外，还有已经可定位的实现差异

### G04：候选集合读取与既有固件审计不一致，P0

这是已有原固件证据与当前代码的差异，不是 O23 给出了某个编码优先级。
[音频能力规范 R-12.2](../../protocol/airplay_audio_mic_channel/spec/12-capability-selection.md)
已核：按顺序遇到无用途项或精确用途项即停；零集合不继续向后寻找；之前 default 的覆盖
和 Apple 前缀回退有独立条件。

[CarPlayAudioPlan.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/CarPlayAudioPlan.kt)
46–51 行则过滤出所有精确用途项后 `flatMap().distinct()`，丢失上述遮蔽/停止语义；
`AudioCapabilities` 也未保留 extended 集合。最终单个格式选择器仍未完全闭合。

关闭条件：先实现有原指令支持的候选获取与方向/传输过滤，再追最终格式选择和本地
编解码交集。特别保留“早项零集合、晚项非零”的反例。不能把共同的
`AAC-ELD → AAC-LC → OPUS` 本端策略标为 Apple 对所有用途的公开统一顺序。

### G05：SETUP 延迟、控制端口及时间来源，P1

`AudioSetupDescription.kt:14` 与 `CallMicrophonePlan.kt:17` 仍写固定
`audioLatencyMs=100`。本轮没有新增原始反汇编；此前已核的
`0x2519be820..0x2519be85c` 是读取格式相关对象再写字典，不是本段固定 100。
100/101 与 102 控制传输条件、高精度采集时间映射仍未闭合。

关闭条件：追值的创建和消费、区分采集/输出/传输延迟，核每种流的端口与 `spf` 写入条件。
接收端声明不能未经核实直接换算为该 SETUP 字段；本端编码 PTS 也不能等同于实际采集时刻。

### G06：增强媒体缓冲，P2，按能力条件推进

O23 822–867 秒介绍 Main Buffered Audio、超过实时速度的传输和接收端至多两分钟缓冲。
当前生产路由和发包器只覆盖 100/101/102，尚无对应的缓冲媒体传输与控制链。
导航首段缓冲及 `USB_BUFFERED` 掩码不构成该能力的实现。

关闭条件：确认目标接收端能力、原固件流选择、发送/控制/同步/暂停与清除流程。
“两分钟”描述接收端组件，不是要求本端存两分钟 PCM；本端只有实时宿主 PCM 时，
还须明确能否取得可提前传送的数据。这项不据公开视频直接硬发某个 type。
OAB 进一步说明使用音频 renderer 与 synchronizer 管理媒体时间线，并在自动清除后
从指定媒体时刻重新入队。它可用于核验本端数据源和时间线能力；这些 iOS 应用 API
不是 Android 可直接调用的 CarPlay 传输协议。

### G07：增强 Siri 及辅助音频，P2，按能力条件推进

O19 648–932 秒描述车端持续 ECNR、历史麦克风环形缓冲、Aux In/Out、
触发时间对应的音频和并行混音。当前主要通过 `requestSiri` 分发宿主语音动作；
`siriTriggerTimestamp` 只进入日志，语音输入仍为按需创建。
现有普通麦克风解码与语音开始/停止不具备完整历史音频和辅助输出语义。

关闭条件：确认车端功能声明，追触发时间单位、Aux 输入/输出与媒体共存的原调用链，
再核宿主语音接口。ECNR 和历史采集属于车端生产职责，不能给 Android 增加一个空缓冲
就宣称实现 Apple Siri；本端语音助手也不能直接等同于 iPhone 的二次触发检测。

## 5. 输入、显示和网络的进一步缺口

| 编号/优先级 | 官方依据 | 当前源码与缺口 | 关闭条件 |
|---|---|---|---|
| G08/P1，持续媒体按键 | O16A 752–758、1414–1422 秒 | `MixingKeyMapper.mediaKey()` 没有快进/快退映射；现有宿主投递主要为合成 down/up。单击切换修复不覆盖持续按压。 | 核 HID 按下/保持/释放与宿主 seek 的对应契约，分别测试快进、快退及取消；不把长按猜成连发上下曲。 |
| G09/P2，HEVC | O23 948–964 秒 | `VideoEncoder` 只选 AVC；`AirSession.kt:609` 明确保留 HEVC 封装缺口。 | 核对接收端、本地编码器、流声明和帧配置；保留官方要求的 H.264 兼容路径。 |
| G10/P2，多屏、尺寸和焦点 | O19 95–169、210–266、400–552 秒；O23 315–504 秒 | `DisplayCapabilities.select()` 最终只返回一个显示；`Screen`/视频 socket 单实例。没有完整 view/safe area 和动态尺寸流水线；`deviceOfferFocus` 的位置只记日志，随后调用无参 `focusOffer()`。外观处理主要是单个 `nightMode`。 | 核每显示身份/会话、显示区域、编码与触摸坐标更新，以及焦点位置和每屏外观。车端圆角合成也须保留职责边界。 |
| G11/P1，短暂断链处理 | O23 756–810 秒 | `Bootstrap.kt:969/1032` 对所选 Android Network 的 `onLost` 立即报会话失败；尚无区分可恢复链路抖动和永久网络失效的完整策略。 | 对齐 L2 事件、Android Network 租约与实际 TCP 错误；确认可保留 socket 的条件和失败预算，再做干扰/切换测试。 |

G11 是待验证的边界风险。Apple 的“不因短暂 L2 断链关闭 TCP”不等于要求在 Android
已永久撤销网络租约时无限保留失效 socket；本轮也没有证明每次短暂 Wi-Fi 抖动都会
触发 `onLost`。频道切换和 BSS 引导的生产者主要在车端，不应被记作手机必须自行实现的 AP 功能。

本轮确认的已有能力：`Bootstrap.kt:995` 有 WPA3 分支；4301 接收和 iAP2 端点交接已存在。
因此 O23 的免 Bonjour 新连接流程和 WPA3 不能笼统列为“代码完全没有”，还需要按目标
profile 验证版本、条件与实际可用性。USB/car key 配对涉及尚未展开的传输和生态能力，
不等同于当前蓝牙模式中的现成修复点。

## 6. 研究文档本身也需要同步证据边界

`airplay_audio_mic_channel/spec/01-audio-streams.md` 的 R-1.6 仍把独立导航流视为未决，
并建议可配置 raw/用途；它与已有 [导航生命周期实施记录](89-navigation-audio-lifecycle.md)
和 O16B 的 AltAudio 功能描述不一致。后续应同步该条的来源、适用层和剩余线上字段缺口，
避免把历史未知误读为任意选择协议参数的授权。公开功能证据也不能自动升级原固件字段为 CONFIRMED。

O24 的 Local UI、Overlay UI、Punch-through 和资产验证主要属于下一代车端架构。
本项目当前做手机端桥接，把这些职责纳入当前 APK 的完成标准会混淆范围；
它们应作为扩展研究，而不是以一条手机视频流已经实现整车架构。

## 7. 建议实施顺序与验收

先处理 G04 的已证候选读取差异，并追 G01 的资源/应用状态；随后补 G02/G03 的真实宿主
状态来源。G05/G08 分别核线上音频描述和持续按键。G06/G07/G09/G10 按接收端能力逐项
建立专题；G11 先完成网络事件分类及验证条件，不添加盲目等待。

每项实施前备份并绑定原固件或宿主消费者证据；测试验证具体状态和错误分支，
实车另验声音、电话对端、仪表显示、按键动作及恢复。当前记录不自动关闭任何运行 OPEN。

本轮核验：七个官方页面获取成功、transcript 索引可读取；当前源码调用点、分支及已有
修复记录已核对；研究入口新增链接。生产源码无修改，因此未重复运行 Android 构建。
