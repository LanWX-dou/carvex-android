# 导航来源、重复快照与生命周期诊断

2026-11-11；基线 `fa3000f`。日志 6 的 Release 20028 已发送四组相同类型、索引和 245 米距离，缺少宿主原始字段证据。本轮在现有输入与 relay 加观察日志，使下一次实测可定位源数据和归一化边界。

宿主侧沿用 CarWith 4.0.14-20260801 的严格 Boolean 生命周期与 Int HUD 契约，原 DEX 地址为 classes2 `0x1c5c20/0x16fb48`、`0x16fc3c/0x16f3f0` 与图标分类器 `0x1aedb4/0x1af2fc`。这些契约和导航映射没有变化；新增日志记录原始类型、数值和文字/图标长度及 SHA256。未输出道路正文或图标像素。

relay 新增 `guidanceChanged`、机动代际、转向、机动距离、路线距离/时间与生命周期。同值更新可独立显示 revision 增长而业务内容未变；终态后迟到 HUD 继续按原规则拒绝。新增两项回归覆盖原始类型与脱敏、同值/距离变化/终态/迟到更新。

已运行 host、bridge、protocol 模块单测与小米 Debug Kotlin 编译：共 1222 项，failure/error/skipped 均为 0，构建成功；部分任务复用有效缓存。没有构建、安装 APK 或实车验证。代码诊断不增加任何 Apple 字段、订阅或重发策略。

原厂 APK、GalaxyPlay 可选 HUD 音乐文字替换、地图注册与引导出口，以及日志时序/复现命令见[信息流研究](../../../research/connection/spec/cluster-navigation-flow-20261111.md)。GalaxyPlay 原字节确认音乐标题可经可选设置进入导航快照；现场是否启用、仪表是否绘制仍须车机证据。

用户随后确认：机动距离 245 米已经显示，异常是车机全程剩余里程 -1 米，而高德地图实际剩余约 19 公里。当前 host 没有独立全程距离来源，numeric publisher 也未发布 5201 p7；GalaxyPlay 将缺值转换为 -1 并交给 RemainDistance。已记录本次有限显示确认和后续缺口，本轮诊断不修复全程距离，不将宿主 total_distance 缓存伪装成路线剩余里程。
