# 无线 CarPlay：从蓝牙到车机显示视频


研究基线：本地 `iPhone18,1_27.0.1_24A446_Restore.ipsw`。版本来自本次直接读取的 IPSW `BuildManifest.plist`，不靠文件名推断。旧版 iPhone 抓包单列，不能冒充此版本的运行证据。

## 阅读顺序

1. [研究基线与证据规则](spec/00-baseline.md)
2. [端到端时序、状态与阶段验收](spec/01-connection-map.md)
3. [蓝牙、iAP2 与网络建立](spec/10-bluetooth-iap2-network.md)
4. [iAP2 检测、SYN 与链路状态机](spec/11-iap2-state-machine.md)
5. [识别字段、拒绝与再次提交](spec/12-identification-contract.md)
6. [Identification 核心字段分支复核](spec/18-identification-core-field-branches.md)
7. [AirPlay 控制会话](spec/20-airplay-session.md)
8. [网络、身份与控制端点汇合](spec/21-endpoint-fusion.md)
9. [控制报文封装、响应归属与等待](spec/22-control-wire-contract.md)
10. [断开、部分流关闭与重新连接](spec/24-disconnect-reconnect.md)
11. [视频协商、传输与首帧](spec/30-video-first-frame.md)
12. [视频配置、帧附件与密码对象](spec/31-video-codec-contract.md)
13. [故障定位与日志关联](spec/40-failure-localization.md)
14. [首次连接、再次连接与断线测试](spec/50-test-matrix.md)
15. [当前手机实现差异](spec/60-implementation-differences.md)
16. [连接消息索引](spec/70-message-index.md)
17. [开放问题与完成审计](spec/90-open-items.md)

新增[GalaxyPlay 接收端音乐、仪表与通话审计](spec/galaxyplay-receiver-audit-20261111.md)：0.1.212 / 240 原 APK、5 个 DEX 的 28 处方法归属/指令哈希复核通过。用户确认音乐正常；导航数值核心已按本版接收端修复，实际仪表显示待验收；通话运行期订阅/状态编码/清理已独立修复，完整元数据与蜂窝下行仍缺来源。未修改或安装车机 APK。

新增[导航链路修复](../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md)与[数值核心原始证据](spec/navigation-numeric-core-20261111.md)：host/protocol 契约、唯一 relay、当前 Link 订阅和旧队列撤销已接入。启用基础转向、正数机动距离与结束 reset；道路/ETA/车道、通用 Apple 米数/完整时序及实车显示继续 OPEN。相关单测与五个 flavor Kotlin 编译通过。

此前[G01–G11 按优先级分项实施](spec/gap-implementation-20261110.md)：按用户要求每项独立提交。G04已修有序候选读取及扩展保存，新增14项回归、协议1099项与桥接27项通过，小米编译通过；最终格式选择仍OPEN。后续按P0/P1/P2推进，不以局部实现关闭整组缺口。

新增[CarWith封面更新与语音控制](spec/carwith-artwork-voice-20261110.md)：Android `8148ed5`单独修复普通语音START等待实际输入准备、失败拒绝、STOP跳过准备及断开/取消隔离；新增6项回归，core112/bridge51/protocol1110项和小米编译实际通过。前轮 `05fee8f`封面失败恢复保留独立提交。原APK的6份DEX、101处指令与语音switch复核通过；麦克风用户偏好、识别自然结束回传与频闪实车效果仍OPEN。

此前[CarWith歌词展示与播放器状态匹配](spec/carwith-4.0.14-host-evidence.md#r03--g08歌词展示与真实播放器匹配)：原DEX证实song可放歌词、artist可放完整歌名-歌手，Android `3c92c9d` 补唯一候选组合匹配；新增11项回归，平台13项、桥接48项、协议1110项及小米编译通过。通知访问仍必需，暂停效果未实车复测；完整G08与其他缺口未关闭。

此前[Release 20013 方控与图片实测反馈](spec/media-feedback-20013-20261110.md)：14次相关按键全部为Play，47次播放器状态均unknown；用户确认未开启通知访问。图片出现36对空/非空引用，已修复带图元数据的中间清空并增加去重，桥接27项单测及小米编译通过；新实现尚未实车复测。台账 R01/R03 已记录本次观察及复测条件。

此前[统一缺口台账（2026-11-10）](spec/90-open-items.md#34-官方资料续查后的实现缺口2026-11-10)：登记 G01–G11 的优先级、状态和关闭条件，另记文档同步 D01 及修复后的设备验收 R01–R03。基线为 Android `67b68e3`（Release 20013）；该轮仅整理记录，没有新增实现或实车结果。

新增[苹果官方资料续查（2026-11-10）](spec/official-followup-20261110.md)：对照 2016/2019/2023/2024 官方系统资料及 Android `67b68e3`，重新区分已修复与剩余缺口。优先核候选能力读取、完整资源/appStates、电话双向链路及状态发布；新增增强缓冲、辅助语音、多屏/HEVC 与短暂断链边界。已有 WPA3/iAP2 端点交接不记作完全缺失。本轮为静态审查，没有新增实车结果。

此前 [Release 20005 音频切换、方控与封面反馈（2026-11-10）](spec/media-feedback-20261110.md)：用户确认该次焦点音频正常、音乐已上仪表。三次方控均发 Play，332 次音乐更新均未携带播放状态；封面传输当时未实现。五次导航拆流成功，切回音乐的轻微卡顿仍待定位。后续播放状态、图片传输和导航缓冲已有代码修复，当前边界见上述续查。

此前[仪表音乐与导航推送核查（2026-11-09）](spec/cluster-publishing-audit-20261109.md)：日志已有 5001/5201 发送，但遗漏音乐进度广播和运行期导航订阅处理。已修复这两处及音乐回调顺序、订阅隔离问题，1163 项单测和小米 Kotlin 编译通过。音乐真实播放状态与导航转向/生命周期映射仍缺宿主证据；该轮尚未进行仪表验收。

已有运行样本单列于 [旧版本运行观察](spec/05-existing-runtime-observations.md)，不作为 24A446 的运行验收。

每章分别标注原固件静态证据、其他版本运行观察、当前 Android 行为与未证实事项。“待验证”不是可随意选择的默认值，也不是文档已全部完成。

## 当前优先阅读：声明与实现是否一致

新增[88 — 正常断开整会话停止实现](spec/88-normal-disconnect-implementation.md)：已补手机App断开的整会话TEARDOWN、统一控制请求停止门、清理保留/完成栅栏及迟到SETUP保护。普通非共享连接不发streams/teardownType；5秒控制事务预算及失败强制清理明确属于本地策略。未打包、未改车机、未实车验收；不宣称ACK-only根因已定或偶发连不上全部解决。

此前[87 — ACK-only与手动断开生命周期核查](spec/87-reconnect-lifecycle-audit.md)：成功/失败均有phone主动方向，七次ACK-only的seq1与前一轮源蓝牙末尾一致但ACK值不同，尚不能判根因；原蓝牙按handle/endpointUUID串行归属。当时确认手机缺整会话TEARDOWN，异步拆流可与control关闭竞争；正常停止缺口现由88有界实施。87保留修改前历史证据，图标仍亮与缺SYN的因果仍待实测。

新增[86 — 初始握手错误ACK恢复](spec/86-iap2-pending-ack-recovery.md)：针对日志SYNACK27/ACK16，24A446局部原指令78项验证event19→零RST→等待新SYN；手机已补同传输、有界且不补充预算的恢复。只限初始握手窗口外纯ACK，不泛化gap1或连接后重同步。七次始终无SYN的ACK-only失败仍OPEN；未打包、未改车机、未实车验收。

新增[85 — Runtime iAP控制事务与失联清理](spec/85-runtime-control-recovery.md)：24A446普通iAP命令使用TransportControlStream并等待结果，NULL reply输出不等于单向发送；普通feedback同样处理回复/失败。手机已补等待与有界失效、socket解阻及一次性失败通知，1069项单测和小米Kotlin编译通过；未打包、未改车机。5001后的静默触发原因和实车恢复仍未证实。

新增[84 — 强停后ACK-only重连审计](spec/84-iap2-force-stop-reconnect-audit.md)：区分主动断开后成功重连与强停/重开后的失败；两份附件实际相同。8项原指令探针验证局部Detach/Attach不主动发SYN/RST，新端点孤立ACK继续等待。手机生产代码未新增修改，强停恢复仍待承载层对照；不能把清理日志缺失直接判为自动崩溃。

最新[83 — 手机端异步网络交接](spec/83-network-handoff-implementation.md)已接通本轮可用配置立即联网、先发布ctrl再发现端点、单消费者处理迟到4301、提交后冻结与取消/世代保护；同一发布实例复用到AirSession。最终协议970+core79=1049项通过，小米Kotlin编译成功；未打包、未改车机、未实车验收。完整availability、身份融合和Apple security枚举仍OPEN。






最新[77 — 扩展修正与等待边界](spec/77-iap2-extension-wait-boundary.md)已落实54/55的原生OR集合语义：成对重复项可接受，数量/长度/session门仍独立；定向70项、完整协议模块875项回归通过。77同时排除了普通蓝牙type=2在所审构造链中的受限模式入口，并把睡眠断言5秒到期分支与iAP2等待分开；attached通知只追到XPC client filter/remote proxy边界。首次Detection/SYN策略、上层超时owner和实车互通仍未关闭。

此前[76 — XPC交接与蓝牙HID回调](spec/76-iap2-xpc-handoff-hid.md)补74前两项：protocol=0在指定客户端→XPC→端点链中原样传递；未知协议发布不进入已知协议专属启动分支；属性回调首层归属为HidService/Bluetooth_HIDFunction。76当时只更新研究目录，并发现75的54/55数量==2条件偏严；该条件已在77修正。76的研究快照及此前872项历史结果保留，不把历史测试通过解释成错误条件的苹果一致性证明。





针对“为什么有的车能连、有的不能连”，先看 [版本／能力一致性审计](spec/62-version-capability-audit.md)，再看 [iAP2 专项](spec/14-iap2-version-capability-audit.md) 和 [AirPlay 专项](spec/23-airplay-version-capability-audit.md)。它们按字段输入、实际分支、当前实现和触发条件组织，不以车型名字或单纯版本号高低判断兼容性。源码不一致、静态条件风险和已修历史问题分别列出；尚无新的车型实测结论。

上述审计及证据JSON保留修改前快照。后续源码变化、已经实施的项目和单测结果以[63](spec/63-alignment-batch1.md)为准，不覆盖历史哈希来掩盖输入变化。

用户要求深入各条件分支后，新增[64 — Identification深度审阅收口](spec/64-identification-deep-review.md)，由[电源/承载15](spec/15-identification-power-transport-branches.md)、[生命周期16](spec/16-identification-lifecycle-branches.md)、[feature/消息17](spec/17-identification-feature-message-branches.md)、[核心字段18](spec/18-identification-core-field-branches.md)交叉核对。本轮是进一步审阅，未再改生产代码；44项旧测试通过不代表其预期均符合固件。

后续已实施[65 — Identification生命周期第二批](spec/65-identification-lifecycle-batch2.md)：同链路拒绝纠正、条件取消、1D06增量更新及蓝牙/运行时实际消费。最终本地792项通过及Kotlin编译成功；初次全字段/feature合同和实车验收仍未完成。64与其证据保留为修改前审计，不能把历史描述当作修改后现状。

再后续[66 — 初次核心字段第三批](spec/66-identification-core-batch3.md)实现有序标量/消息列表、语言/PPID、核心成功集合与24A446注册分类拒绝；本地全量820项及Kotlin编译通过。并行新增[19 — Power上下文](spec/19-identification-power-provider-context.md)追查实际连接来源；8/9与全feature生产校验、CF等价及实车仍未完成。

最新[67 — 连接主线第四批](spec/67-connection-mainline-batch4.md)已回到网络→AirPlay→SETUP：补4301/5703语法与部分配置交接、同源地址端口、安全能力错误分类、内嵌info/skipRecord/可选eventPort、单屏响应与失败清理。完整890项通过，小米Kotlin编译成功。新原证据见[25网络](spec/25-network-handoff-branches.md)、[26安全能力](spec/26-airplay-security-branches.md)、[27 SETUP](spec/27-setup-response-branches.md)；全认证、全部请求presence和实车仍未完成。

随后[68 — 连接主线第五批](spec/68-connection-mainline-batch5.md)落实扩展能力`fex`与无线kind5请求分支：保留F80和解析错误，不误入未实现认证；移除通用timing字段及无来源的空features；屏幕改用无线默认75ms、必需显示UUID，不自动注入timestampInfo。完整回归与编译结果见68。现有320.17/21A329仍是过渡兼容声明，boot correlation/transport字段提供者、身份融合和完整密码事务仍未完成。

## 证据与复核

- [G11网络回调边界](spec/g11-network-callback-boundary.md)：实际读取API36 SDK原源码，区分register观察与request选择、物理断开与不满足条件。尚无目标ROM的L2/Network/socket关联，未添加固定等待或将其标为修复。

- [CarWith 4.0.14 原DEX核对](spec/carwith-4.0.14-host-evidence.md)：39处原code item与来源哈希、歌词展示与状态匹配、导航结束生产链、CarLife助手共享队列与独立VoIP麦克风路径。G03结束缓存和歌词播放器匹配已分别提交；最新平台13项/协议1110项/桥接48项及小米编译通过。完整状态/机动/车道与蜂窝音频仍PARTIAL。`tools/inspect_carwith_host.py <现有APK路径>`只读复核原字节身份，不运行供应商代码。

- `evidence/reconnect-lifecycle-audit.json`：87的11个原函数、9份当前手机源码哈希、7次ACK-only及手动TEARDOWN脱敏元数据；`tools/inspect_reconnect_lifecycle.py`默认只读，`--write`只写本证据。未证明ACK-only根因或图标状态。
- `evidence/iap2-pending-ack-recovery.json`：86的78项有界原指令向量、镜像/runner/函数哈希。`tools/probe_iap2_pending_ack.py`默认只读复跑，`--write`仅更新本证据；平台依赖替身及合成元数据不等于真实蓝牙/车机测试。
- `evidence/network-handoff-implementation.json`：83修改后源码、研究依据及1049项XML快照；`tools/verify_network_handoff_implementation.ps1 -CheckTests`只读核验哈希与计数，不代表Android联网或实车成功。
- `evidence/baseline.json`：源文件实际 SHA-256、大小、版本来源、手机源码快照定位。
- `evidence/capture-observations.json`：重新读取 PacketLogger 原始文件所得的脱敏消息清单、偏移及解析警告。
- `evidence/runtime-log-observations.json`：原始 accessoryd 文本日志中的承载、方向、消息号与时间；不导出凭据、密钥或设备身份。
- 各专项证据 JSON：关键原函数、地址、反编译/汇编定位与哈希。
- `evidence/iap2-state-evidence.json`：accessoryd 的链路状态表、Detection、SYN/SYNACK、计数器与计时器局部路径；不等于所有承载已经运行验证。
- `evidence/iap2-startup-initiation.json`：74的BT成功回调、protocol=0识别、Start/Attach及收到Detection后的回复链；`tools/inspect_iap2_startup.py`只读核对原镜像与原dyld切片，不执行苹果代码，不证明全部启动入口已闭合。
- `evidence/iap2-xpc-handoff-hid.json`：76的XPC参数交接、发布分支、HID属性及虚表证据和75勘误；`tools/inspect_iap2_handoff.py verify`复核60个函数字节/哈希，不证明全部上层超时或实车互通。
- `evidence/iap2-extension-wait-boundary.json`：77的扩展门修正、受限模式/睡眠断言可达性和attached条件转发；`tools/verify_iap2_wait_boundary.py --check-android`独立检查24个原函数/既有缓存、两份手机文件及875项XML结果，不证明全部上层超时或实车互通。
- `evidence/iap2-syn-negotiation-audit.json`：78的本地模板、第二SYNACK分支、字段合并/提交和16个内存报文观察；`tools/verify_iap2_negotiation.py --check-implementations`只读核对原函数/表/常量与源码快照，`tools/run-iap2-negotiation-probe.ps1`重新编译相关源码并运行探针。验证不是苹果代码执行或实车验收，16项断言通过不等于16种协议处理正确。
- `evidence/iap2-renegotiation-batch.json`：79修改后四份手机文件、历史参照及897项XML快照；`tools/verify_iap2_renegotiation_batch.py --check-tests`只读核对。78的源码检查/探针是修改前预期，不能在79上原样运行并要求通过，也不覆盖其历史结果。
- `evidence/identification-three-way-audit.json`：80的24个原函数、三组消息规则/四项feature描述符、当前两套源码快照及18项本地解析行为观察；`tools/verify_identification_comparison.py`只读核对完整性，`tools/run-identification-comparison-probe.ps1`另行执行当前解析器探针。观察包含已知缺口，不代表修复、苹果等价或实车通过。
- `evidence/identification-contract-evidence.json`：字段注册、required-success、条件组件、接受/拒绝与再次提交的局部合同。
- `evidence/endpoint-fusion-evidence.json`：5703/4301 交接、APTransport 网络/地址/身份/显示配置及 Bonjour 解析入口；完整身份匹配与实际可达性仍未闭合。
- `evidence/control-wire-evidence.json`：方法/URL/载荷、CSeq旧值、回复对象关联、分层成功判据、waiter与消息边界；附当前RTSP源码快照。
- `evidence/disconnect-evidence.json`：整会话/部分流TEARDOWN、控制/事件失效队列、屏幕Suspend/fatal及超时生产者；不等于重连实测通过。
- `evidence/video-codec-evidence.json`：avcC配置、帧附件标志、MaxFPS条件、cryptor虚表/初始状态和排除错误编码参数解释。
- `evidence/control-response-keys.json`：不依赖旧字段索引，从24A446共享缓存重新解析 `info`/`skipRecord` 键与原始 getter 跳板；只证明静态来源和局部消费。
- `tools/collect_inputs.py`：只读取既有输入，只在本目录生成上述证据；不得把数据完整性校验解释成实车兼容验证。
- `tools/validate_docset.py`：只读检查章节、相对链接和 JSON 可解析性；不验证协议结论或车机互通。
- `tools/inspect_control_wire.py`：默认只读复核17个控制函数字节及7个字符串；`--write`只生成本目录对应证据JSON，不运行苹果原代码。
- `tools/verify_batch_evidence.py`：只读复核12/22/24/31四分册的源镜像哈希与72条函数切片记录；重复引用也分别检查，不把数量当作覆盖率或语义正确性证明。
- `evidence/version-header-evidence.json`、`iap2-version-capability-evidence.json`、`airplay-version-capability-evidence.json`、`build-profile-audit.json`：版本／能力的条件分支和当前源码快照；Toyota库单列，不当作苹果发送端或所有车型行为。
- `tools/inspect_version_headers.py`：只读解析原协议版本头provider、跳板与源码调用点；输出JSON到stdout。
- `tools/verify_profile_audit.py`：只读核对本批JSON声明的文件哈希和有定位的cache切片；不证明语义或互通。

文档中的图表达已知依赖与有条件分支，不是一份可无条件重放的报文脚本。车机真实显示并持续更新、断线重连成功必须有相应观察，发送端单边日志不能证明这些结果。

新增[通话订阅链路修复](spec/call-subscription-chain-20261111.md)：当前 Link 独立状态、显式/默认编码分支和麦克风异常关闭清理；原 Apple 声明表/处理器字节复核 PASS，相关单测/编译结果见实施记录。卡片与双向音频仍 OPEN。
