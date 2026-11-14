# 目的地剩余距离与时间实车试验

2026-11-14用户明确要求：`destinationRemainingDistance`先按米、
`destinationRemainingTime`先按秒设置，实测不符后再调整。
这替代此前候选字段暂不启用的实现决定；不恢复已被用户否定的`total_distance`路线映射。

## 输入与发布

已审CarWith 4.0.14/4.0.23的活动`carlife_show_hud_info`（action 1/2）读取两个同名extra。
接受非负Int/Long；距离上限为U32，时间上限为非负Long。显式0是有效值，不推断到达。
缺失、负值、非法类型或越界时清除对应快照字段；不从路口距离、缓存距离或TITLE文本生成值。
原始诊断显示两个字段的类型/数值及`routeUnits=meters/seconds`，
规范化诊断继续显示`routeDistance`/`routeSeconds`。
字段携带`user-test-20261114:destination-HUDINFO:meters-seconds`来源标签，
并保留`destination-distance-time-user-test`未验证标记。

发布器将距离写入`5201/p7 U32`，剩余时间写入`5201/p6 U64`，不换算。
时间缺失也先发送NotActive reset再重建活动路线，避免接收端保留旧时间；
结束、旧代际撤销、实际订阅、组件声明及机动容量合同沿用原链路。
本次不新增到达时刻字段。

## 证据边界

CarWith 4.0.23原APK的EasyConn `HUDINFO` getter直接读取`k:I`和`l:I`：
距离指令`classes8:200454`，时间指令`classes8:20046c`；消息将它们写入同名JSON键。
`classes8:200e40..200e50`将时间加入`Calendar.SECOND`。
Apple 24A446 accessoryd `100002b74..100002b8c`选择p6并调用字段writer，
`100002b94..100002ba8`选择p7及U32 writer。既有route编码器保持p6的U64布局。
DiPlay原`BydHudRouteState`按p6读取U64剩余秒数，p7读取U32米数，reset清除两者。
详见研究仓库[字段调查](../../../research/protocol/carwith_4_0_23/ROUTE_DISTANCE.md)。

SDK模型可调用不代表当前mixing回调一定携带它们。本次启用的是用户授权的输入映射试验；
不修改CarWith进程、不构造空HUDINFO对象、不宣称已取得真实实时来源。
若实车日志显示`destinationRemainingDistance=absent`或`destinationRemainingTime=absent`，
需继续接通宿主上游来源；仅调整单位无法产生缺失的数据。

## 验证

宿主测试覆盖两个已审版本、action 1/2、单位直传、显式0、Int/Long、非法/缺失/越界、结束与诊断。
编码测试覆盖p6的8字节、无到达时刻补值、时间清除、重算及结束。
新增原DiPlay接收合同覆盖连续秒数变化、0、超过U32的时间、时间清除与路线距离/箭头隔离。
本轮协议/bridge/宿主单测及小米Kotlin编译成功：Gradle退出0，1m，90 tasks（13 executed/77 up-to-date）。
协议1197、bridge65、宿主38，failure/error/skipped均0；21+2原接收合同与7原worker测试核对通过。
三模块单测本轮实际执行，原接收源码来自DiPlay提交`ad4ccbfb`，不进入生产APK。
尚未打包、安装或实车观察。
