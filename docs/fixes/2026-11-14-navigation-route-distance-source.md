# 撤下错误的全程距离试验映射

2026-11-14用户明确`total_distance`不是总距离，要求查找其他字段。
CarWith4.0.23原`LauncherDataBusClient.F`（classes2 `17abdc`，缓存分支`17ae52..17ae84`）
将道路提示变化时的机动距离缓存到`f`并发出，原字段不表示独立的到目的地距离。

此前按用户要求把它映射到`distanceRemainingMeters`和5201/p7作试验，现在撤下该映射。
活动HUD将路线距离设为Clear，仅在诊断observation中保留缓存参考值；
机动距离保持独立，未知全程值不补零或估算。
新marker为`route-distance-provider`，不再授予旧`user-test-20261112`试验值发送权限。

[原APK字段调查](../../../research/protocol/carwith_4_0_23/ROUTE_DISTANCE.md)找到EasyConn消息中的
`destinationRemainingDistance`、桥模型`remainDistance`与原生概要`TITLE_1/TITLE_2`。
字段定义/封装存在，但当前混合回调没有传出它们，真实provider和单位仍OPEN，因此没有接入猜测字段。

回归覆盖两个已审版本的活动HUD、缓存参考值与机动距离隔离、有效/零/缺失/非法缓存值、
结束、新路线及外部候选字段不能冒充当前混合HUD字段；generic relay的来源/清除回归继续保留。
本轮运行协议/bridge/宿主单测及小米Kotlin编译，退出0，5s，90 tasks（9 executed/81 up-to-date）：
协议1195为有效Gradle缓存报告，bridge65及宿主37实际重跑，failure/error/skipped均0。
20+2接收合同与7个原worker测试核对通过；没有重跑DiPlay CI或安装/实车验证。
报告及适用提交见[执行记录](../../../openspec/changes/align-business-lifecycle-and-push-fields/execution.md)。
