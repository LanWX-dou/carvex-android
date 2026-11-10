# 导航自然结束时完成本地音频队列

用户反馈导航切换音乐时略有卡顿。日志中五次导航 TEARDOWN 都成功，媒体 staleAU 计数
没有在这些切换期间增加；现有日志不能确认卡顿发生在发送端、宿主混音还是车机播放端。
本修复针对源码中可确定的缺口：导航 state=0 立即 close 编码器并清空桥接队列，
已经接收的尾部 PCM、编码器延迟输出和待发 RTP 可能在自然结束时被截断。
不把这个缺口认定为此次卡顿的唯一根因。

## 依据与边界

沿用研究仓库 `research/connection/spec/89-navigation-audio-lifecycle.md` 的独立
AltAudio 生命周期和原有单流 TEARDOWN。原镜像
`firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender`，SHA256
`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`。
本次再次直接反汇编核对：`0x2519cd624` 调用 teardownTransportStreams，
`0x2519cd62c` 随后调用 teardownAudioProcessing。描述符、路由、能力协商和
接收端确认条件沿用现有实现。

本次只增加 Android 源结束前的本地队列完成策略，不声称该队列或 MediaCodec EOS
是 iPhone 固件的实现，也不增加网络 FLUSH、固定等待、自动播放键或音量控制字段。

## 修改

1. 已安装的导航收到停止后同步拒绝新 PCM，在已接收块之后排入完成标记；原有过期
   丢弃界限继续生效，不重放陈旧音频。处理完成之前不清空这条队列。
2. 压缩发送器调用已有 encoder.finish()，等 EOS 输出进入发送队列，再关闭队列入口、
   等待 UDP writer 处理完队列，最后走原 close/TEARDOWN。PCM 发送器在桥接队列完成后关闭。
3. 下一次导航 prepare 先等待本地收尾，再由已有 AudioStreamLifecycle 等待车机关闭确认。
   媒体使用独立队列，导航收尾不阻塞 Binder 回调或媒体发送。
4. 尚未安装的 SETUP、断开和故障仍立即关闭。自然收尾有 5 秒故障上限，正常完成即释放，
   不固定等待 5 秒；失败/超时仍释放本地资源并触发原关闭流程。
5. 日志新增 `Audio finish category=2 phase=drained/timeout/failed`；drained 只证明
   本地队列完成，不证明车机扬声器已经播放完。

## 验证

新增 JVM 测试覆盖尾部块保留、迟到 PCM、音乐同时发送、下一次导航等待本地完成及
接收端 TEARDOWN 确认、连续五次播报、断开、未完成安装、编码器故障和收尾超时。
core 90 项、protocol-carplay 1075 项、bridge 19 项单元测试及 Xiaomi Debug Kotlin 编译通过，
失败、错误和跳过均为 0；加上第一项修改已通过的平台 9 项，共 1193 项。
JVM 使用替身传输，未运行真实 Android MediaCodec；未打包、安装或实车验收。
切换是否平滑及目标编码器 EOS 是否正常，仍需要设备验证。
