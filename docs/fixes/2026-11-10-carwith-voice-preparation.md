# CarWith 语音启动等待输入准备

2026-11-10，关联 G07 普通语音路径。此前协议语音动作异步请求 speech 通道后就发送启动键，助手可能先于麦克风安装开始取数据；手动8107没有共用准备流程，切换到停止也会提前请求通道。本次修复会话调度顺序。

## 原字节依据与本端差异

CarWith 4.0.14-20260801 APK SHA256：`c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。以下均为 DEX 文件内 code item 偏移，指令正文从偏移加16 bytes开始。

classes6 `CarlifeHw.onKeyEvent` `0x0a98e8` 的原 packed-switch 将8107分派到 `0x0a9a50`、8108到 `0x0a9a40`。语音DOWN直接调用宿主回调，不经过普通按键延迟；UP在 `0x0a9932..0x0a9940` 直接返回true。classes2 `HomeActivity$f.b/c` `0x1a538c/0x1a5340` 在小爱准备门通过后进入 classes7 `voiceassistant.a.m` `0x0e682c`，启动 VoiceService。`processIntentInternal` `0x0ead0c` 将START交给任务d，STOP交给stopEngine。`execute.j.d` `0x0f3fa4` 发布Handler工作；`j$f.run` `0x0f3298` 经j.x进入j.K，`0x0f4300` 调用ASR入口i.T0。这些分支没有为本端异步建立麦克风通道提供屏障。

输入消费另由原队列证明：classes6 `CarlifeAudioListener.onReceiveAudioStream` `0x0adf90` 将PCM送入 classes `h1.a.a` `0x48ef6c`；`PhoneAudioCast.B` `0x4328e0` 的CarLife分支读取同一队列，classes5 `be.f.d` `0x1b1fc8` 经DataBus读取助手输入。另一分支 `be.g.d` `0x1b20bc` 使用手机AudioRecord。以上证明宿主入口与数据消费的关系，没有规定 Apple SETUP 字段、超时或资源政策。

## 修复行为

协议切换动作和手动8107/8108进入同一有序工作协程。选择START时先保留本地请求，再等待会话发布准备入口；有已声明车端输入能力时，复用现有speech SETUP，等待对应完成对象，并检查实际输入已安装且没有电话占用，最后发送启动DOWN/UP。完成对象在启动SETUP协程之前发布，避免仅等待类别锁先于准备协程获得锁。

准备失败时不发START，也不将本地请求状态改成活动。STOP跳过准备；它仍按队列顺序执行，不能超车或取消前一项RTSP事务。准备和宿主调用不持有切换状态锁；断开撤销保留的请求，取消或异常释放保留状态，迟到准备结果不能继续启动。DOWN被宿主接受后才提交本地状态；UP仍用于按键清理。

未声明车端输入能力时保留宿主自行选择手机输入的既有路径，不建立额外输入服务。实际车端输入准备失败时本次START被拒绝；本端尚不能读取宿主明确选择手机麦克风的偏好，故不能区分这一情况下是否应继续启动。未改宿主查询答复、唤醒能力声明、用户偏好或CarPlay音频协商规则。

## 验证与剩余边界

新增6项确定性协程回归，覆盖准备前不发START/不允许超车、准备失败保留下一次START、手动与切换STOP跳过准备、断开拒绝迟到启动、取消释放请求，以及准备成功但DOWN拒绝时不提交状态。

```powershell
.\gradlew.bat :core:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

本轮测试和小米 Debug Kotlin 编译实际执行成功：core112项/19 suites、bridge51项/9 suites、protocol1110项/135 suites，失败、错误、跳过均为0；whitespace检查通过。单元测试验证本地准备与请求状态，不执行宿主Binder、RTSP往返或真实助手消费。

宿主DOWN返回true仍可能是回调缺失或小爱未准备；输入安装也不证明助手已消费PCM。录音源选择仍受宿主初始化和偏好控制，识别自然结束到公开mixing回调的链路尚未闭合，本地requestedActive可能残留。没有把输出category3停止或notifyAudioState整数解释为识别结束，也未增加增强Siri/Aux能力。G07继续PARTIAL，未打包、安装、推送或实车验收。详细证据见研究仓库 `research/connection/spec/carwith-artwork-voice-20261110.md`。
