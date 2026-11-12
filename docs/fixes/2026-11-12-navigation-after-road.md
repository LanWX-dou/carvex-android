# 转向后道路名称发送修复

日期：2026-11-12。用户确认 CarWith HUD 的 `road_name` 是转向后的道路。

用户提供的本地 `device-log.txt` 有 94,371 行，诊断头版本为 20037。913 次活动 HUD 更新均带非空道路文字，规划却始终将 `currentRoad`、`maneuver.description`、`maneuver.afterRoad` 标为 unavailable，并附 `road_name-role`。实际 5201/5202 发送字段没有道路文字。原始日志及道路正文只用于本地分析，不加入仓库。

此前 `CarWithNavigation` 将道路保存为观察值，`NavigationWireEncoding` 只发布数值核心。按用户确认的语义，两个已审 CarWith 版本的 HUD 道路现映射至 `HostNavigationManeuver.afterRoad`；通过既有 relay 进入协议快照，移除道路角色未确认标记。机动定义的 5202 参数 4 使用现有 UTF-8 NUL 结尾编码发送，仍先定义、再在 5201 中引用同一索引与距离。当前道路和导航指令没有新增来源字段。

每个有效机动定义都包含参数 4，缺失、空白或错误类型的道路写为空 C 字符串，避免接收端合并复用索引时保留旧路名。沿用现有导航文本校验：嵌入 NUL、未配对 UTF-16 代理字符或超过 4,096 UTF-8 字节的文本清旧值，不抛异常打断数值导航，也不截成另一条路名。未知转向继续 reset 后发布无引用的活动状态；结束仅发布 NotActive。

六项新增回归覆盖：两个已审版本的道路角色、缺失/空白/错误类型输入、relay 距离更新/道路切换/结束、UTF-8 编码与定义引用、接收端合并索引的道路更新/清除及非法文字、未知转向与结束。宿主 32 项、bridge 62 项、协议 1,149 项，共 1,243 项通过，0 失败/错误/跳过；小米 Debug Kotlin 编译通过。首次测试编译发现跨模块 nullable 属性不能 smart cast，修正测试后最终 BUILD SUCCESSFUL。

```powershell
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain --gradle-user-home C:\Users\admin\.gradle
```

复测时查看 `available` 中出现 `maneuver.afterRoad`，实际 TX 有 `id=5202 field=4 name=afterRoad`，再对照仪表显示、道路切换和导航结束。此变更验证的是输入至发送路径；接收端文字显示和文本容量仍需实车核对。
