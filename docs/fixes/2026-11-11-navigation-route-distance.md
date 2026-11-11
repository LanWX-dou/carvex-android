# 全程剩余里程发布

2026-11-11；基线 `fa3000f`。用户确认转向距离 245 米已显示，但全程里程为 -1 米；本次先补可独立实施的发布器缺口。当前 CarWith 标准导航提示/HUD/ICCOA 消息仍没有已确认的全程距离来源，因此不能据此宣称现场约 19 公里已显示。

原先 `NavigationWireEncoding.plan()` 未读取快照中的 `route.distanceRemainingMeters`，即使 relay 已接收有字段证据的全程值，也不会写入 `5201 p7`。现在仅在该值具有非空 `distanceRemainingMeters` 来源证据且处于 U32 范围 `0..4294967295` 时发布；明确提供的零保留为零，缺失、负数、越界或无证据的值省略。转向距离继续独立写入 p10。没有用 `total_distance`、提示距离或零补齐缺值。

Apple 24A446 accessoryd 原路线编码器 `0x100002b94..0x100002ba8` 选择 p7、查询路线字典并调用 U32 数字追加器。键跳转表 `0x100003d60` 的第七项指向 `0x100003c4c`，该分支读取 `0x10023dc10` 的 DistanceRemaining 键；p10 则读取 DistanceRemainingToNextManeuver。追加器 `0x100004650` 对缺失值跳过，`0x1000046d0..0x100004734` 预留八字节参数并以 `rev w8`、四字节 store 写大端 U32。原字节身份、参数选择和调用目标由[数值核心复核器](../../../research/connection/tools/inspect_navigation_numeric_core.py)检查，记录在[原始证据](../../../research/connection/evidence/navigation-numeric-core-20261111.json)。

GalaxyPlay 0.1.212 原 classes2 `updateRoute` 的 `0x024c6a..0x024c8e` 将四字节 p7 写入 remainingMeters，缺值分支保留旧值；状态 0/2 分支 `0x024d20` 调用 reset，`0x024838` 清除 remainingMeters。因此在全程值未知时先发 NotActive reset，再发当前机动定义和 Active/Rerouting 引用/转向距离，防止旧里程跨清除、新路线或重订阅残留。其他已有 reset 原因仍只产生一次 reset。没有机动时仍可发布有证据的全程距离；Ended/Invalidated 仅清屏，不再携带已结束路线的里程。

每批次继续自包含，沿用 Link 能力、START/STOP 订阅、组件容量与旧队列撤销。没有增加已送达快照缓存或重发定时器。清除及恢复顺序是此版接收端的兼容策略，不证明 Apple 的全部增量时序；reset 与后续更新之间的瞬时显示仍待实车验证。

验证结果：

- 修改前新增的实际发布器 p7 回归失败，原因是 p7 未编码。
- 修改后协议 1155 项、宿主 25 项、桥接 60 项，共 **1240 项通过，失败/错误/跳过均为零**；其中 14 项直接执行未修改的 DiPlay `615b32c` 接收源码，覆盖全程/转向距离分离、19 公里递减、明确零、U32 上界、未知值清除、新路线、结束、单槽和容量复用。
- 小米 Debug Kotlin 编译检查通过；部分编译任务复用有效缓存。GalaxyPlay 原 APK 与 Apple/CarWith 原字节复核通过；三处内存修改夹具（p7 参数选择、U64 写入器替换、键跳转）均被拒绝。
- 未构建或安装 APK，未连接手机或进行实车验收。测试中的全程值为人工输入，用于验证发布/接收合同。

命令及报告哈希见[验证记录](../../../research/connection/evidence/navigation-route-distance-validation-20261111.json)。此前已有的[来源与生命周期诊断](2026-11-11-navigation-source-diagnostics.md)一并保留，可在后续会话日志中区分宿主缺值与发布问题。
