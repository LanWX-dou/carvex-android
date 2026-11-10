# 蜂窝通话麦克风：第一条可实测链路

日期：2026-11-10。状态：本地验证通过后供实车测试；对方可听见状态为 **OPEN**。

## 问题与范围

用户反馈对方听不到说话，希望先按苹果文档实现链路，实测有问题再分析日志。
原实现仅在宿主类别 3 建立 `100/speechRecognition` 输入，没有蜂窝电话状态触发的
`100/telephony` 路径。语音识别输入不能据此视为已经接通电话上行。

本次实现以下路径：

```text
Android 每张活动 SIM 的电话状态（READ_PHONE_STATE）
  → 任一 SIM 为 OFFHOOK
  → MainAudio 所有权与 raw100 流生命周期
  → SETUP type=100 / audioType=telephony / input=true / 本地 UDP dataPort
  → 车机麦克风 RTP → 认证、排序、解码
  → HostAudioBridge → 既有 CarLife mixing IRemoteAudioListener
  → 宿主如何接入蜂窝通话：OPEN，等待实测/宿主证据
```

OFFHOOK 包括拨号、活动或保持中的通话，不能解释为对方已经接听。本次是输入链路，
未增加电话下行音频类别、未猜测厂商通话注入方法，也没有将 VR 的 `is_use_phone_mic`
查询视为蜂窝通话支持证明。没有新增录音文件或读取号码。网络语音通话不在本次范围内。

## 文档与原固件证据

公开行为说明来自 Apple WWDC 2016 Session 723，Developing CarPlay Systems：

```text
https://developer.apple.com/videos/play/wwdc2016/723/
```

- 293–335 秒：MainAudio 包含电话、语音识别和媒体；电话使用麦克风与扬声器。
- 725–770 秒，特别是 760 秒：电话使用 telephony，语音识别使用 speechRecognition。
- 1481–1495 秒：原生 HFP 电话对 MainAudio 有独占关系；不能绕过接收端所有权决定。
- 公开说明不等于完整的协议字段规格，也不证明宿主能将 PCM 注入蜂窝调制解调器。

按工作区规则，字段分支另行核对原始 Mach-O：

```text
firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender
SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
```

| 地址 | 原始分支与本次对应关系 |
|---|---|
| `0x251adc910..0x251adc9ac`，telephony 比较 `0x251adc96c..0x251adc984` | Main 的 default/telephony/speechRecognition 选择输入格式键；只从接收端 telephony input mask 与本地解码器交集选择格式。 |
| `0x2519be86c` | vocoderInfo 源对象不存在时跳过；本实现没有宿主编码元数据，不编造此字段。 |
| `0x2519be870..0x2519be89c` | type 100 且 telephony、源对象存在时才写 vocoderInfo；telephony 常量对象 `0x27612e7b0`。 |
| `0x2519be8f4..0x2519be91c` | 有效本地端口启用 input 并发布 dataPort；实际 socket/decoder 在 SETUP 前建立。 |
| `0x2519cd624`、`0x2519cd62c` | 流暂停先 teardownTransportStreams，后 teardownAudioProcessing；沿用类型关闭屏障，旧流关闭未确认时禁止复用。 |

相关 docset 位于研究工作区：`research/protocol/airplay_audio_mic_channel/` 的 `TASK.md`、
`STATUS.md`、spec 02/06/11，以及 `research/connection/spec/` 的 89 音频生命周期章节。
本记录描述实现差异，不替代 docset。

Android 状态监听依据：

```text
https://developer.android.com/reference/android/telephony/TelephonyCallback.CallStateListener
https://developer.android.com/reference/android/telephony/TelephonyManager
```

API 31+ 使用每订阅的 TelephonyCallback；29–30 使用 PhoneStateListener。仅请求
READ_PHONE_STATE。增加或移除其他 SIM 时保留未变化 SIM 的状态；移除订阅的迟到回调失效。

## 实现行为与边界

- 没有电话状态权限时保留原连接能力，记录原因；设置页提供授权，授权后刷新监听。
- 通话活动需求可以先于 CarPlay SETUP；会话就绪后建立一次输入，不循环重试 SETUP。
- 通话期间阻止新语音识别/媒体 SETUP，等待旧准备任务结束；仅关闭冲突的 raw100 媒体，
  已建立的 raw102 媒体保留。挂断后恢复需求准入，由实际 PCM/用户动作触发恢复，不自动按播放。
- 电话独占 raw100，等待旧 speechRecognition 的类型 TEARDOWN 完成。关闭失败需重连，
  不让迟到的类型 TEARDOWN 关闭新电话流。SETUP 仍在进行时，输入停止也要等待其结束再发 TEARDOWN。
- 每次通话使用独立的代际检查；挂断立即撤销后续 PCM 投递，已进入宿主回调的数据不可撤回。
  即使 PCM 等待桥接锁，也在获得锁后重新验证代际。旧输入清理不会移除新输入。
- 输入只在 SETUP 接受、当前通话仍活动且 MainAudio 属于本端时交给宿主。
- 复用现有输入 RTP、HKDF、认证、解码和宿主 16 kHz 单声道 PCM 转换；释放解码输出缓冲后
  才调用宿主，避免把 MediaCodec 缓冲持有到 Binder 调用结束。
- 没有新增 `phoneCall` appState 的 wire 映射；该映射及完整电话双向协商仍为 OPEN。
  若车机依赖这些信息才能提供输入，本次实测会停在协商或无 RTP 阶段。
- 宿主回调成功只说明接口调用返回，**不能证明对方已听见**。宿主未注册监听时明确报告，
  不把普通 Android AudioRecord/AudioTrack 误当成可用的蜂窝上行注入接口。

## 本地验证

新增测试：

- CallMicrophonePlanTest：telephony input/decoder 交集、错误方向/用途拒绝、受约束的 PCM
  回退、输入描述及端口校验、旧 speech 关闭屏障与 raw102 并存。
- CallMicrophoneSessionTest：就绪前通话、重复状态、挂断期间 SETUP、连续通话代际、
  失败不自动重试、断开取消及关闭已安装输入。
- CallMicrophoneBridgeTest：旧输入清理、宿主拒绝不计成功字节、等待桥接锁期间挂断、
  等待旧媒体准备任务丢弃结果。

运行模块：core（98）、platform-android（9）、protocol-carplay（1080）、bridge（19）、
host-carlife-mixing（15）、app 的 Xiaomi debug（51），共 1272 项单元测试通过，其中新增 13 项。
Xiaomi Kotlin 编译与 MainManifest 合并通过。未打包 APK。
这些测试不覆盖真实 SIM 回调、MediaCodec、车机录音或宿主蜂窝注入。

## 单一实车验证流程

1. 从本次提交自行构建安装，在设置中允许读取电话状态，重新连接车机。
2. 用普通蜂窝电话拨出并接通，正常说话，确认对方是否听见；同时确认原有来声是否正常。
3. 挂断后再打一次，确认第二次仍可用，挂断后媒体/语音识别可按原操作恢复。
4. 若异常，再导出从连接开始到挂断后的完整日志，并说明拨出/接听、对方听感、手机及宿主版本。

定位顺序：`Call state` → `Call microphone demand` → `setup-begin/accepted` →
`Microphone phase=first-datagram purpose=telephony` → `Microphone health` 中 authenticated →
deliveredPCM → `Microphone sink accepted` → 宿主 `microphone-host-callback-delivered`。
`microphone-no-host-listener` 表示宿主没有注册输入消费者。健康日志包含零包情况；
不要把会话结束后重置的全局计数误读为通话期间统计。

设备结果：**OPEN，尚未实车验证**。无实测前不宣称“通话已修复”。
