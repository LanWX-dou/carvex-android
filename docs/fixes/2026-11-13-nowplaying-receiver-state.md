# OPSX 2 — 接收播放状态与封面联测

本次修改对应 DiPlay 的 CarPlayPlaybackStatus、ClusterSongState 与 CarPlayMediaKeys。
5001 多组属性与封面文件通道依据见24A446 accessoryd构造点146ac8、1461c0及OPSX协议审计。
0/1/2/3/4状态映射沿用两端既有模型，本次为接收消费者的本地合同修正，不宣称闭合Apple全部平台状态。

CarPlayNowPlaying保留原始U8状态，省略/错误长度保留旧值；未知值保留且不冒充STOPPED。
活动布尔信号涵盖PLAYING/SEEK_FORWARD/SEEK_BACKWARD，供播放listener与仪表卡使用。
Android MediaSession分别映射STOPPED、PLAYING、PAUSED、FAST_FORWARDING、REWINDING；
未知值映射STATE_NONE。收到状态但尚无标题/进度时也使用该状态，不能让音频活跃标记覆盖暂停或停止。
没有状态时保留原音频fallback；无快进/快退速率来源时冻结进度外推，状态变化不重建元数据。
clear清除状态授权，clearAll清除全部会话元数据。

新增接收状态/非法长度/增量/清理、Android状态与时间戳、仪表卡和音乐导航独立回归。
receiver-interop新增实际文件接收器源码哈希及封面取消/替换、原始播放状态合同。
旧prepare输入615b32c不代表新接收实现，这批新联测尚未执行。

2026-11-13封面生产改动的手机最低检查已成功：协议142 suites/1166 tests，failure/error为0；
小米Kotlin编译通过。随后添加的两个interop用例尚未执行。
DiPlay完整CI尝试先遇Gradle下载超时；同版本归档校验通过后，联网构建越过插件配置，
NDK28.2自动下载持续0字节。本轮CI已取消，尚无DiPlay编译通过或APK产物结论。
用户随后明确要求先提交代码；2.3 provider、2.4完整接收联测、2.5编译与实车保持待验证。
