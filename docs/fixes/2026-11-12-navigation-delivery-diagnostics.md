# 导航投递关联诊断

日期：2026-11-12。延续 CarWith 4.0.23 来源适配，完善当前导航数值核心的诊断；道路、路线概览与车道没有新增生产字段，仪表显示仍待验收。

此前 publisher 在 START 之前只记录 no-subscription，难以看出宿主快照是否已存在；relay 对被拒绝的事件只记录当前代际，无法区分 incoming 与 active binding。writer/completion 日志也缺组件、字段证据和冻结批次的完整归属。

本次变更对应 OpenSpec 8.1 和[诊断需求](../../../openspec/changes/replan-carplay-navigation-cluster/specs/navigation-delivery-diagnostics/spec.md)：

- `HostNavigationRelay` 在校验前记录来源、版本、变化与 sequence；拒绝时区分 incoming/active source 和 binding。source route ID 只记录有无；规范化结果带字段证据。
- `SessionController` 将成功应用后的事件命名为 host-applied；session ID 沿现有 BridgeStore 日志归属关联。
- `NavigationPublisher` 区分 Link 未就绪、必需声明缺失与 lane-capability-missing。阻断日志包含可用/缺失字段名称、证据、未证项、组件/options 和当前快照身份。
- 每个计划批次固定 binding/route/revision/maneuverGeneration、Link/subscription/delivery 代际、消息/字段 ID 与证据。排队、writer-check 和 transport 完成沿用同一冻结上下文。
- writer-check 只在既有发送前有效性回调中记录一次；使用原有无 publisher/relay 锁的检查，并隔离日志异常，避免诊断改变有效性结果。AirSession 外层会话门可能先拒绝，届时完成记录中 writerChecked=false；不将其描述为已经写出。

这只是观察现有合同，未修改 `5201/5202` 字段、数值、定义/引用顺序或 START/STOP 行为。原发送门来自 accessoryd `0x1001b40e0`、`0x10017527c`、`0x10017593c`；[字段续查](../../../research/connection/spec/galaxyplay-navigation-fields-20261112.md)记录本轮新增原字节边界。

日志不输出道路、目的地、机动 ID、原 route ID 或异常 message。保留证据标签、字段名称、枚举/数值及异常类名；冻结上下文避免迟到完成被归到更新后的路线。

验证先执行宿主/bridge/协议测试与小米 Kotlin 编译，BUILD SUCCESSFUL（2m 50s），XML 共 1,231 项，0 失败/错误/跳过。最后补充 writer 日志异常回归，再执行协议测试与小米编译，BUILD SUCCESSFUL（1m 3s）。最终 XML 合计 1,232 项：宿主 25 项有效 up-to-date、bridge 本轮执行 61 项、协议最终重跑 1,146 项，均无失败/错误/跳过。最终结果见[验证记录](../../../research/connection/evidence/navigation-diagnostics-validation-20261112.json)。四项新增回归覆盖拒绝绑定归属/私有标识、无订阅但有快照、延迟 writer/完成与旧批次归属，以及日志异常不能改变当前/过期发送判断；原无车道声明测试补上专用原因断言。

所有 Gradle 命令显式使用 `--gradle-user-home D:\Java\gradle`，未改全局环境。原 docset 完整 FAIL 保留。未构建 APK、安装、创建提交/推送或增加实车验收。
