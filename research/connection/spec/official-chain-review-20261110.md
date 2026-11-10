# 音乐、导航、方控、通话官方资料对照复查

日期：2026-11-10。Android 基线：`7676c62`，包含之前 `b1173c5`、`a80e581`、`23e03d7`。
本次为静态审查，未修改生产代码、未打包、未新增提交、未开展实车验证。

## 结论

**四条链路均不能认定为完整遵循苹果官方协议实现。** 音乐、导航、方控有已实现且与公开
行为相符的部分；通话目前只有实验性麦克风输入。共同的资源与应用状态管理明显不足。
之前 1272 项单元测试通过证明的是既有实现的测试条件，不是 Apple 协议符合性。

## 证据范围

直接阅读的 Apple 官方资料：

```text
WWDC 2016 / 722 — Developing CarPlay Systems, Part 1
https://developer.apple.com/videos/play/wwdc2016/722/
WWDC 2016 / 723 — Developing CarPlay Systems, Part 2
https://developer.apple.com/videos/play/wwdc2016/723/
```

722 页面本轮从 Apple 官网取得；723 使用本日上一轮直接取得的官网 HTML，重新读取 transcript。
原文件分别保存在忽略目录 `local-backups/2026-11-10-official-chain-review/` 与
`local-backups/2026-11-10-call-uplink/evidence/`。本记录仅转述，不复制整篇 transcript。

| 资料时间 | 本次采用的行为要求 |
|---|---|
| 722，480–522 秒 | 主音频双向；备用音频与主音频混合；2016 无线方案要求压缩，媒体使用 AAC-LC，其余音频使用 OPUS 或 AAC-ELD。 |
| 722，752–758、1414–1422 秒 | 语音按钮要传递按下/松开；媒体控制支持播放、暂停、上下曲及快进/快退。 |
| 723，293–340、739–789 秒 | 主音频包含媒体、语音和电话；telephony 提供麦克风及扬声器；导航使用不参与 take/borrow 的备用音频。 |
| 723，522–544 秒 | 导航期间调导航音量；结束后恢复媒体音量上下文。 |
| 723，585–599、674–719、1113–1150 秒 | take 与 borrow 不同，电话/语音等临时用途结束要归还并恢复之前的所有者。 |
| 723，968–1016、1226–1252 秒 | changeModes 是接收端请求，modesChanged 发布控制端决定；资源优先级和借用约束影响仲裁。 |
| 723，1362–1501 秒 | TurnByTurn、PhoneCall、Speech 应用状态协调双方行为，原生电话与 CarPlay 电话不能冲突。 |

这些是 **2016 年公开系统设计资料**，不是完整或最新的 MFi CarPlay/iAP2 规范。
不同年代的格式支持不能只凭该视频硬改；如要保留扩展行为，需要新版官方或对应固件证据。
Android MediaSession、宿主 AIDL 接口及内部类别号属于本端适配，不是 Apple 官方 API。

另外本轮直接重新反汇编 24A446 原始 `AirPlaySender`，核对
`0x2519be814..0x2519be958`，SHA256：
`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`。
此项用于字段来源抽查，不声称完成整个音频栈的固件等价验证。

## 发现一：资源管理只实现子集，应用状态没有实际联动（高优先级）

代码：`android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/ScreenResourceModes.kt`：

- 第 18 行拒绝所有非空 `appStates`；第 47 行出站三个应用状态固定为 entity=0。
- 第 20 行仅允许一次申请一个资源；第 22 行只接受 resourceID 与 transferType，带
  transferPriority/takeConstraint/borrowConstraint 等字段的请求被拒绝。
- 第 8 行 `audio(phone)` 直接重写永久音频所有者并清除借用状态。电话通过
  `AirSession.createCallMicrophoneLocked()` 调用同一个 `takeOwn()`，并没有临时借用的历史。
- `AirSession.kt:880` 对不能处理的请求返回业务 status=1。它没有把不支持的请求误报成功，
  但也不能完成官方展示的完整资源协商。

影响：车机导航与手机导航的互斥、原生电话保护、临时语音/电话结束后的资源恢复不完整。
这不是把音频字段改为 telephony 或把导航改为 type101 就能补齐的功能。
文档依据为 723 的资源借用、约束及 appStates 章节。已有 ScreenResourceModesTest 明确
测试“拒绝约束和 appStates”，因此测试通过并不代表这些能力已经支持。

## 发现二：通话缺少完整双向音频及电话状态上报（高优先级）

代码：`CallMicrophonePlan.kt:17`、`AirSession.kt:1225`、`SessionController.kt:138/973`、
`host-carlife-mixing/.../VendorCastHost.kt:265`、`PhoneSubscriptions.kt:3`。

已实现：蜂窝 OFFHOOK 驱动 telephony 输入，实际端口与解码器先于 SETUP 建立，认证后
交给宿主，挂断撤销投递并清理资源。这与电话使用麦克风的方向一致。

仍缺少：

1. 独立的 telephony 下行发送与对应宿主来声来源，当前方法明确是 input-only。
2. PhoneCall appState；来电 RINGING 也没有本次专用铃声/电话生命周期分支。
3. 从 PhoneCallMonitor 到 iAP2 `4155`/`4158` 的状态发布连接；PhoneSubscriptions
   仅保存订阅并提供编码函数，真实电话状态没有驱动这些发布。
4. `IRemoteAudioListener.onReceiveAudioStream()` 后音频进入蜂窝通话的证据。
   回调正常返回不能证明调制解调器消费了 PCM。

官方 722（486–489 秒）及 723（335–340、754–760 秒）描述双向电话音频。
**因此 `7676c62` 是可供分段测试的输入实现，不是已经完整实现的 CarPlay 电话链路。**

此外，`SessionController.kt:143` 在任意通话活动时设置 callSuspendedMedia=true；
第 918 行对 category1 直接返回 true，而第 266 行只在返回非 true 时转发 PCM。
所以 raw102 即使保留 transport，也停止接收新的媒体 PCM。不能把“保留 raw102 资源”
描述成“raw102 音乐继续传输”；此行为也不等于已通知播放器暂停或已实现完整电话焦点切换。
挂断仅恢复准入，媒体是否恢复依赖后续实际来源及所有权状态。

## 发现三：无线编码策略与所查官方资料不同，不能标为官方默认（中优先级）

代码：`CarPlayAudioPlan.kt:74/112/134`、`CallMicrophonePlan.kt:7`。

当前音乐、导航、语音、电话使用共同偏好 `AAC-ELD → AAC-LC → OPUS`，只要用途对应的
接收端格式和本地编解码器支持就可选择；播放协商还允许 PCM 兼容回退。
它没有落实 722（511–522 秒）按媒体/其他用途区分的无线编码策略。

这说明当前实现包含本地兼容策略，不能称为直接照官方文档实现。这里只标记差异及证据缺口，
不据 2016 视频断言 24A446 或所有车机必然拒绝其他编码。修复前应核对所选 profile 的新版
官方要求与原固件选择链，再确定用途、传输方式和格式的交集。

## 发现四：方控基本语义已映射，但未知状态与长按行为仍不完整（中优先级）

代码：`SessionController.kt:439–462`、`core/.../MediaPlaybackToggle.kt:20–36`、
`host-carlife-mixing/.../MixingKeys.kt:38–46`。

已实现按 HID 页面/usage 映射明确 Play、Pause、Next、Previous；真实播放器状态可通过
MediaPlaybackMonitor 同步至 Now Playing，符合控制当前播放和上报当前状态的方向。

缺口：

- 没有通知访问权限、未唯一匹配播放器或状态未知时，toggle 仍由音频类别活动及旧键值猜测。
  导航造成音频源暂时停止，不等于播放器已暂停；因此这一回退仍可能发错 Play/Pause。
- `choose()` 在队列接纳和宿主发送之前改变推测状态；拒绝或发送失败不会回滚。
- Consumer 释放只更新输入状态，宿主收到立即合成的 down/up。快进/快退 usage 没有
  MixingKeyMapper 映射，不能把现有单击上下曲支持视为完整长按媒体控制支持。

官方 722（1414–1422 秒）要求媒体按钮对接媒体行为。Siri 按钮还有独立的按下/松开要求，
本轮没有将 requestSiri 动作号或宿主模拟语音请求认定为与 iPhone 长按交互完全等价。

## 发现五：SETUP 延迟值仍固定，部分流字段沿用兼容实现（中优先级）

代码：`AudioSetupDescription.kt:14`、`CallMicrophonePlan.kt:17`。

音乐/导航/语音和新通话输入统一写 `audioLatencyMs=100`。本轮原始指令显示：
`0x2519be820` 获取 latency info，`0x2519be85c` 从该对象读取值后写入字典；
这不是本段硬编码 100 的行为。当前 `receiverAudioLatencies` 在创建音频处用于日志，
没有参与这两个描述符的延迟选取。

`0x2519be8ac..0x2519be8d8` 显示 controlPort/spf 按有效本地控制端口条件写入；
现有 AudioSetupDescription 则要求并统一写入 controlPort/spf，其注释也明确声明
100/101 与 102 的控制传输差别尚未完整复现。此处不能从“编译/SETUP 成功”推出字段与固件等价。

与导航切换卡顿的因果关系仍未证明。另一个本地风险是 `SessionController.kt:940–942`
只保存一块首 PCM，超过 100 ms 就丢弃；SETUP 期间尚无 binding 的后续 PCM 也无法播放。
短提示可能缺头甚至整段丢失，应单独验证，不能把本地 drain 成功当成首段和车机播放均正确。

## 分链路判断与后续顺序

| 链路 | 已对齐的部分 | 当前结论 |
|---|---|---|
| 音乐 | 主音频媒体用途、格式能力交集、Now Playing 订阅、图片文件传输 | 部分对齐；编码策略、资源恢复及字段来源仍有缺口。 |
| 导航 | 独立 AltAudio、不申请 MainAudio、自然结束本地 drain 后 TEARDOWN | 通道方向对齐；TurnByTurn 状态缺失，首段/尾段及音量恢复待设备验证。 |
| 方控 | HID 页面/描述符、明确播放暂停上下曲、真实状态同步 | 基本单击路径具备；未知状态回退及持续按键语义不完整。 |
| 通话 | telephony 输入、接收解码、代际清理、宿主 PCM 交付 | 输入实验链路；完整电话上/下行及应用状态尚未闭合。 |

建议先补共同的资源仲裁与 appStates，再明确宿主通话双向接口；随后按用途核对编码、
latency/SETUP 字段，最后处理方控未知状态和导航首尾音频。每项需独立测试和提交。
若宿主没有蜂窝 PCM 注入能力，单靠调整 Apple 侧 SETUP 不能解决对方听不见。
