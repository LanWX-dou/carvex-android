# 89 — 导航播报结束与音量上下文恢复

日期：2026-11-09。用户报告：播报结束后音乐仍被压低，车机旋钮仍调整导航音量。
本轮没有连接手机或车机，不能把代码缺口与实车现象的因果关系标为已验证。

## 静态依据

修改前，`SessionController.audioState()` 只更新 `HostAudioBridge` 的本地活动状态；
`HostAudioBridge.state()` 停止时只清队列，transport 仍 ready，没有触发单流 TEARDOWN。
启动计划还预建语音、提示音、媒体三类通道。原 `AudioDemandGate` 将关闭的通道当作失败，
最多两次尝试，没有正常播报结束后开始下一次活动的入口。

原镜像：`firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender`。
SHA256：`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`。
本轮直接用 NDK `llvm-objdump` 反汇编该镜像，核对以下原指令：

- `0x2519cd300–0x2519cd304`：`suspendInternal` 检查 `+0xb8`，未就绪可早退。
- `0x2519cd624`：调用 `0x2519cd844` 清理传输流；`0x2519cd62c` 随后调用
  `0x2519ce884` 清理音频处理资源。
- `0x2519cd86c`：teardown 参数非零时跳过发送分支，不是所有 suspend 都发包。
- `0x2519cd8c4–0x2519cd8f4` 与跳表 `0x2519cddb0`：raw100/101/102 的普通类型分派。
- `0x2519cda90–0x2519cda9c`：该分支传递 session、raw type、NULL options 给 teardown 槽。

局部指令确认 suspend 中有传输结束和处理资源释放路径。描述符沿用现有
`AudioTeardownDescriptor.forType()`；详见
[音频 teardown 分析](../../protocol/airplay_audio_mic_channel/analysis/07-teardown.md)。
将宿主 category=2/state=0 映射为导航源结束、只预热媒体及提示流独占类型，均为本端
生命周期策略，不声称 Android 回调或调度规则来自 iPhone。车机音量恢复仍需实测。

## 修复行为

1. 只预热媒体。导航从真实 PCM 按需建立；语音保留显式请求和 PCM 入口。
2. 导航停止撤销当前 ticket，关闭已返回或正在 attach 的 transport，触发现有异步
   TEARDOWN。迟到 PCM 不重开流；下一次 state=1 后重新允许需求。
3. 同一分类串行执行 create 与 install，迟到的旧 SETUP 先关闭。新流继续等待旧流的
   TEARDOWN 确认；关闭未确认时保持阻断，不通过无限重试掩盖失败。
4. 正常结束重置活动，失败仍限每次活动两次。旧失败、安装结果和首块音频不能进入
   下一次活动；取消异常仍传播。
5. 导航 lease 独占其 raw type。若 type100 已被媒体或语音占用，只能选择双方支持的
   独立路由（如已广告的 type101）；没有可用路由就明确失败，不拆已有流。
   导航活动期间也阻止另一用途进入相同类型；其他非导航用途的原并发策略保持。
6. 单流关闭后从 Resources 注销，避免连续播报累计已关闭的 transport/codec。
   追加 `Audio teardown category=... type=... phase=begin/accepted` 日志。

媒体流不会随导航停止关闭。应用切换仍由宿主提供新的 PCM，歌曲信息回调不被误当作
音频焦点控制。没有新增宿主 API、固定延时、音量倍率或伪造的 Android 焦点请求。
语音输出结束不等于识别结束，因此 category=3/state=0 不用于关闭麦克风。

## 验证与限制

项目 Gradle 回归通过：core 83 项、protocol-carplay 1054 项、bridge 14 项，
共 1151 项测试，失败、错误和跳过均为 0；小米 Debug 的应用 Kotlin 编译通过。

`NavigationAudioLifecycleTest` 覆盖五次连续播报、迟到 PCM、SETUP/attach 与停止竞争、
旧首块隔离、有限失败重试、等待关闭确认、导航后新媒体 PCM、提示流类型冲突及能力回退。
同时运行已有音频桥、需求门、所有权、音频计划、单流生命周期、描述符和本地 UDP 测试。

在 `android/` 目录执行并通过：

```powershell
.\gradlew.bat :core:testDebugUnitTest :protocol-carplay:testDebugUnitTest :bridge:testDebugUnitTest :app:compileXiaomiDebugKotlin --no-daemon --console=plain
```

最初离线检查因缺少 `android-37.0` 在任务依赖阶段失败；获准执行完整 Gradle 检查后，
工具链安装 SDK 37.0 revision 2，再使用项目配置完成测试和编译。
未降低 compileSdk、修改依赖版本或关闭检查来绕过环境问题。首次完整回归发现一条旧测试
仍要求预建三类音频流，已更新为仅预热媒体，并保留导航与语音按需编解码选择的断言。

此前独立 JVM 回归通过 76 项测试，编译与测试期间源码哈希保持不变。
该回归使用现有 Kotlin 2.4.10、JDK 17、JUnit 4.13.2、coroutines 1.10.2、
Bouncy Castle 1.80.2；SDK 36 android.jar 只提供宿主接口的类型声明，没有执行 Android
音频实现。其结果作为补充，最终模块检查以以上项目 Gradle 回归为准。
脚本、结果及验证时的源文件哈希位于本地忽略目录
`local-backups/2026-11-09-navigation-audio-lifecycle/`。

真实车机音量和旋钮恢复、宿主停止/启动回调是否完整，以及首次短播报受 SETUP 往返影响
的程度仍需设备验证。没有打包、安装或实车验收。

## 2026-11-09 后续实测反馈：需要手动播放才能恢复

用户报告：导航播报完成后，仍需再按一次方控播放键才交还音乐；媒体音量调节正常。
目标是播报期间方控调整导航音量，播报结束后自动恢复音乐及媒体音量控制。
用户随后确认：导航结束后音乐进度条继续走，仍能听见音乐但音量很低；此时方控不显示
音量条，而媒体正常时调节会显示媒体音量条。这是持续低音量现象，不应按音乐完全暂停
处理，也不能把“不显示音量条”写成“正在显示或调节导航音量”。
现象支持继续检查压低音量未解除、导航通道或车机音频上下文未释放；尚不能确定压低
发生在手机宿主还是车机。尚未取得本次测试的构建号和完整日志。
本轮 `adb devices` 返回空列表，不能从设备核验。此前本地回归不代表该目标已通过实车验证。

本次导航路由修改前的源码观察（只描述实现，不作为 Apple 协议证据）：

- `CarPlayAudioPlan.selectPlayback()` 对媒体依次选择 `102/media`、`100/media`，
  对导航依次选择 `100/alert`、`101/default`；实际结果还取决于能力、编码器和流占用。
- `SessionController.audioState()` 依赖导航 `category=2/state=0` 关闭导航 transport。
  `AirSession.finishClose()` 发送单流 TEARDOWN，但响应成功不等于扬声器、音量上下文
  或手机音乐应用已恢复。
- 方控播放事件经宿主按键入口下发；该操作成功恢复声音不能单独区分宿主压低音量
  未解除、导航流未结束和车机资源未归还。没有证据支持自动补发播放键或固定延迟恢复。

下次取证应覆盖同一会话的连接、音乐播放、一次导航、播报后调音量、手动播放恢复：

1. 构建号及 `Audio category=2 selected type=...`，确定实际导航路由。
2. `Audio host state observed category=2 state=0` 与
   `Audio teardown category=2 ... phase=begin/accepted`，确定结束通知是否闭合。
3. 导航结束前后 category=1 的状态、PCM 和 RTP 日志，以及 `MainAudio owner` /
   `Resource modes applied`，区分源停止、发送被所有权门阻止和接收端播放问题。
4. 方控播放的 `HID press delivered` 前后事件，以及现场观察的音量类别和音乐播放状态。

本轮仅补充反馈与排障依据，未修改生产音频行为，未重新运行构建或测试。

## 2026-11-09 导航改走独立 AltAudio

用户明确要求先将导航接入导航音频链路，目标是播报时方控调节导航音量并显示导航音量条。
本次把宿主 category=2 的运行时选择和静态类别映射统一改为 `type101/default`。
原来 `100/alert → 101/default` 的选择会优先建立主音频提示流，即使接收端同时声明
AltAudio；该旧选择策略由本节取代。媒体与语音的选择规则保持原状。

### 依据和边界

- 本轮重新读取同一 AirPlaySender 原镜像并核对 SHA256，仍为本章前述
  `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`。
  `0x2519c456c–0x2519c4594` 的 raw type 读取、减 96 和名字表索引，以及
  `0x2693e5da0` 表的索引 5 与 `0x251beecf4` 原字节 `AltAudio\0`，支持 type101
  对应 AltAudio。此处仅确认流类型，不以名字表推导导航业务或音量 UI。
- 重新反汇编 `carPlayAudioFormat_getFormatsKeyForAudioType`：
  `0x251adc920–0x251adc92c` 对 107、100 特判，101 走 `0x251adc954` 分支。
  导航仍使用现有的输出格式能力交集、编码器和封包实现，没有新造音量控制字段。
- Apple 官方 WWDC 2016 session 723 “Developing CarPlay Systems, Part 2”
  （`https://developer.apple.com/videos/play/wwdc2016/723/`）的公开 transcript
  将 Alternate Audio 用于导航等高优先级提示，并说明播报期间调节导航音量、
  媒体播放时调节媒体音量。2026-11-09 直接读取官方页面核对。
  该材料用于说明接收端预期，不替代 24A446 发送端指令证据，也不证明目标车机 UI 已通过。
- 将 Android 宿主 category=2 映射到已实现的 `101/default` 是本次明确选择的本端路由策略；
  24A446 从导航业务到具体流创建的完整调用链仍未闭合，不把此改动标为完整固件等价。

### 实现行为

1. 仅使用接收端声明且本地可以编码/封包的 `101/default` 输出格式。保留该通道的压缩编码
   优先序和既有 PCM 兼容路径；输入方向、其他用途或 type100 的格式不能借用。
2. 通道缺失、被占用、没有共同格式或被显式拒绝时，明确报告导航通道不可用。
   不回退到主音频 Alert，避免静默改变音量类别。显式拒绝仍在本会话内记录，取消递归换路。
3. 保留 sourceState 停止后关闭导航流、单流 TEARDOWN、等待关闭确认及迟到 PCM 隔离。
   这次没有新增焦点请求、播放按键、音量倍率或固定延迟。
4. 音量条由车机呈现。此改动使导航从独立通道送出，但导航音量条是否出现、播报结束后
   音乐是否解除压低，均需目标车机验证；没有新增 Android 音量条作为替代。

### 验证

补充双方同时声明 Alert/AltAudio 时的导航选择、AltAudio 被排除、能力缺失、只有输入格式、
未知格式位、编码器不可用及错误用途的测试；更新 OPUS/PCM 选择与需求门的导航预期。
同时保留已有独立流关闭、重复播报及 RTP 加密封包测试。

在 `android/` 执行本章既有完整检查命令成功：core 83 项（Gradle 判定 UP-TO-DATE）、
protocol-carplay 1055 项、bridge 14 项，共 1152 项，XML 中 failures/errors/skipped 均为 0；
`:app:compileXiaomiDebugKotlin` 成功。`git diff --check` 通过。
修改前备份在 `local-backups/2026-11-09-navigation-alternate-route/`。
本次未打包或安装，导航音量条及播报结束后的音乐音量恢复仍待实车验收。
