# 88 — 手机端正常断开的整会话停止


## 1. 修复范围与证据边界

手机原先先取消会话任务，随后按资源析构顺序拆音视频流并关闭 socket；音频异步拆流可能未收到响应，控制连接已被关闭。原实现没有整会话 TEARDOWN。用户另观察到手动断开后车机图标仍亮；这一观察不能未经时间关联就绑定到日志中某个 attempt。

现在正常断开先保留当前会话资源，经当前控制连接完成整会话停止事务（或有界失败），然后取消会话任务并释放资源。异常断线、Service 销毁保留强制清理入口。

**这修复了确定的本地停止合同缺口，不是已经证明七次 ACK-only / NO_SYN 的根因，也不是实车连接成功的保证。** Android 强停不能保证执行此停止流程。未删除配对、未自动开关蓝牙、未增加 SYN/RST 试探。

## 2. 固件合同与本地实现的区别

依据[24章](24-disconnect-reconnect.md) LC01/LC02 及87的复核：

- `EnsureStopped @0x251b5e7c4` 的非共享/全停止分支清 stream registry，向 helper 传 NULL stream 数组和内部 type2；connected 时发送，helper 成功后才到 `disconnectControlStream`。
- `sendTeardownWithStreamDescArray @0x2519ce5c4` 对 NULL 数组不放 `streams`。`teardownType` 仅在 `UseConnectionSharing` 对应槽非零时出现。
- 当前手机没有实现连接共享，故发送 binary plist 空字典，不发 `streams:[]`、不无条件加 `teardownType=2`。URL、Session、CSeq、加密输出和响应关联全部使用当前 RtspClient。
- **本地策略**：停止事务总预算5秒，覆盖已接纳请求排空、控制写锁/写入和等待响应；超时由独立 deadline 关闭当前 socket 解除阻塞。这不是固件的50秒 TEARDOWN 上限。
- **本地策略**：失败后仍强制释放本地资源，避免永远留在断开中；不能冒充原 `EnsureStopped` 错误分支无条件调用 disconnect。
- 本地硬件 codec/Binder 释放等仍由原资源关闭机制处理；5秒是控制事务预算，不是整个 Android 清理动作的严格耗时承诺。

## 3. 实施位置与顺序

`SessionController`：

1. 每 attempt 创建独立 `SessionTermination`。正常断开先保留清理权，不能先 cancel job。
2. failure/finally 若同时请求关闭，只登记在同一停止流程下，不抢先关控制 socket；attempt 的 finally 等真实清理完成后才退出。
3. 调用当前 `AirSession.stopNormally()`；结束后在 `NonCancellable + IO` 中取消旧 job、执行一次资源清理并等待旧 job 完成。
4. `disconnecting` 保持启动门关闭，直到旧任务清理完成。尚未发布 AirSession 的取消在其准备入口再校验，避免空快照后继续建立 AirPlay。
5. Service `close()` 可强制打断正常等待；不会为了等待车机而阻止硬清理。

`RtspClient`：

- 原子停止接纳普通 `request/send`。此前已接纳的事务仍使用旧连接完成；其计数覆盖请求方处理响应的阶段，不仅检查 `pendingCount==0`。
- 排空后只发一次整会话 TEARDOWN；并发或重复停止共享成功/失败结果，不再次发包。未进入异步控制阶段不能借此发送会话停止。
- 无关/缺失 CSeq 的回复不能确认停止。reader 保留到响应完成；已交付匹配2xx后对端立即关闭，不抹掉已确认的事务。
- 对端请求的响应仍可使用独立 reader/event 路径，防止停止时不读控制回复；新的本地业务请求则被门控拒绝。

`AirSession / AirPlaySetupSession`：

- 先标 stopping，停止新的媒体输出、音频预约与业务事件；注销本地屏幕/音频注册，不把注销当成对端确认。
- 整会话停止期间跳过新的部分 TEARDOWN 和音频所有权释放通知。已进入 RtspClient 的旧事务在 full stop 之前排空。
- 屏幕迟到 SETUP 不安装新屏幕，也不补发 full stop 后的单流拆除；音频迟到回复检查 stopping，后续控制写入仍由统一门控兜底。
- 关闭单条流时原部分 TEARDOWN 语义保留。正常停止与异常关闭不合并成同一线上报文。
- 停止前不持有事件回调锁等待宿主业务退出；runtime 的 close 留给 socket 已关闭后的原逆序清理阶段，避免等待仍在写数据的 iAP link 锁。

## 4. 自动化验证

最终结果见[本批源码与验证快照](../evidence/normal-disconnect-batch.json)。测试是 JVM 内存控制报文/并发测试，不是 Android Service 完整运行或实车验证。

最终协议模块 **1021项/126 suites**，core **81项/13 suites**，全部零失败/错误/跳过；小米 Kotlin 编译通过。core完整模块在本批已执行通过，最终命令为UP-TO-DATE；小米编译在本批执行通过，最后命令亦为UP-TO-DATE。新增21项测试，非新增1021项。未打包、安装或实车测试。

新增覆盖：整/部分字段区别、Session/URL/CSeq沿用、停止前排空、响应已交付但调用方尚未完成、拒绝新请求、并发一次性、无响应/无关响应/500、排空和写入超时、强制关闭、配对阶段拒发、迟到屏幕SETUP，以及正常停止与资源清理联动后创建新连接。

验证过程保留两项说明：

- 首轮扩展后的联动测试返回类型不是 JUnit 要求的 Unit，导致该测试类初始化失败；已修正后重跑，没有放宽断言。
- 一次完整回归触发旧 `BootstrapNegotiationTest.nextRaw()` 把 session0 纯ACK当成 session17 CSM 的偶发失败（expected17/actual0）。单独复跑通过；现修正**测试辅助读取器**只跳过 `flags=0x40/session=0/空payload` 的 ACK，并新增“保留4E0C、不生成ACK-of-ACK”测试；未修改 iAP2 生产逻辑。失败XML保存在本批备份中。

执行命令：

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
```

本批既有文件备份（包含修改前所有脏内容）：`D:/carvex-research/local-backups/normal-disconnect-20261030-182650`。87的历史证据及源码哈希未被覆盖。

## 5. 需要实车确认

用户自行打包。成功投屏后在 App 内点断开，记录车机是否退出投屏、图标/连接状态如何变化；等 App 完成断开再连接，重复数次并保留从成功连接、手动停止到下一次连接的完整日志。先不混入强停 App、删配对或重启蓝牙操作。

日志新增 `AirPlay whole-session TEARDOWN begin/accepted/unconfirmed/skipped`；与 RTSP CSeq 的 RESPONSE/FAILED 和资源关闭完成分别判断。图标可能表示“可用入口”而非“仍有活跃会话”，不能只凭图标断言远端状态；需要与是否退出投屏、后续握手一起核对。

若仍遇到“仅 ACK、没有 SYN”，继续按87的独立问题追踪，不重复把这批正常停止修复称为已解决所有偶发连不上。
