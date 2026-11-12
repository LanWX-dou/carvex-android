# total_distance 全程剩余里程试验

日期：2026-11-12。用户明确要求把 `total_distance` 放入全程剩余里程，随后实车观察其含义。

本次是按用户要求实施的试验映射，不能将其视为已确认的全程剩余距离来源。APK 4.0.23 的 `LauncherDataBusClient.F`（classes2 code item `0x17abdc`）在 `where` 文本变化时保存当时的机动距离到缓存字段 `f`，再将此缓存写入 `total_distance`；因此现场可能观察到该数值保持不变并在道路提示切换时跳变。

两个已审 CarWith 版本的 HUD action 1/2 将有效 Int `total_distance` 直接按米写入 `HostNavigationDelta.distanceRemainingMeters`。来源证据包含 `total_distance-route:user-test-20261112`，未确认字段保留 `total_distance-route-role-user-test`，供导出日志辨认此次试验。`remain_distance` 继续独立供给机动距离；不按比例修正、递减或估算全程里程。

通过既有 relay 和发布器，试验值写入 `5201` 参数 7，机动距离仍写入参数 10。零值明确发送为零；缺失、错误类型、负数或 `Int.MAX_VALUE` 清除旧试验值，沿用发布器 reset 避免接收端缓存残留。导航结束及新路线不继承旧里程。没有剩余时间或 ETA 来源，因此不添加时间值。

复测时对照原始 `total_distance`、normalized `routeDistance`、实际 TX `id=5201 field=7` 和仪表全程里程，同时记录 `remain_distance` / 机动距离。重点比较同一路段距离递减、道路提示切换、主动结束与重新导航。此次构建也包含此前待打包的转向后道路文字修复。

验证命令：

```powershell
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain --gradle-user-home C:\Users\admin\.gradle
```

验证通过：宿主 34 项、bridge 63 项、协议 1,149 项，共 1,246 项，无失败、错误或跳过；小米 Debug Kotlin 编译成功。新增回归覆盖两个已审版本的两种活动 HUD action、独立全程/机动距离、零、无效/缺失清除、结束与新路线；协议既有实际 p7/p10 编码回归继续通过。实车含义与仪表显示待用户测试。
