# G03：宿主导航结束后清除路线缓存

CarWith `4.0.14-20260801` 的结束通知此前只记录日志；HUD `action=3` 中的零距离仍被当作有效路线发送并缓存。现在 `isNavi=false` 和 `action=3` 均清除桥接及运行期发布器的路线缓存与本地 HUD 文本。结束包不再生成零距离更新，稍后的 `5200` 不会重放结束前的路线。

宿主依据是用户提供的 `com.miui.carlink` APK，SHA256 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。SDK dexdump 直接反汇编原 DEX：`classes2.dex` 的 `LauncherDataBusClient.C()`，code item `0x16fb48`，在 `0x16fb6a..0x16fb6c` 写入布尔 `isNavi=false`，在 `0x16fb90..0x16fb92` 写入整数 `action=3`，同时将两个距离置零、道路置空。`0x16f8e4` 经 `j.G`，`classes6.dex 0x0a88bc` 最终调用 `ICarLifeCastCallback.invokeMethod(Intent)`，与本工程宿主回调一致。字节定位与哈希见[宿主证据](../../../research/connection/spec/carwith-4.0.14-host-evidence.md)。

本地数据源失效与车机订阅分别处理：`NavigationPublisher.clearRoute()` 只删除样本，保留 `5200` 选择的组件和选项。下一条真实路线沿现有订阅发送；没有向车机发送猜测的状态值，也没有伪造方向相反的 `5203`。既有 Apple 订阅门继续对应 accessoryd `0x10017527c` / `0x10017593c`，本次改动不声称闭合 Apple 导航状态枚举。

新增 7 项回归：布尔/整数的严格类型、两个结束通知、合法零距离活动更新不误判、缺失/坏类型不清缓存、结束前后订阅及下一条真实样本。完整协议 1110 项、桥接 41 项零失败/错误/跳过，小米 Debug Kotlin 编译通过，whitespace 检查通过。未打包、推送、安装或实车验证。

G03 仍为 PARTIAL。活动 HUD 的道路语义、机动距离到 iAP 的量纲映射、guidanceState、机动及车道生产链尚未闭合；本次保留活动包的历史适配，不把该适配标为已确认。结束时车机屏幕上的导航状态是否随此变化也未验证，需真实 wire 状态映射及实车结果。
