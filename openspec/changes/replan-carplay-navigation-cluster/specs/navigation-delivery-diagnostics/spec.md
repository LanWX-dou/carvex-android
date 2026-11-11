## ADDED Requirements

### Requirement: A navigation update can be traced across the delivery chain

系统 SHALL 在宿主接收、规范化、规划、排队和 writer 发送阶段关联 sessionId、来源绑定代际、routeEpoch、revision、linkEpoch、subscriptionEpoch、组件、options、消息 ID 和字段 ID。每个映射 SHALL 可追溯到字段证据项；日志 SHALL 遵守现有脱敏和设备私有数据规则。

#### Scenario: One host update produces two navigation messages

- **WHEN** 同一快照产生路线与机动消息
- **THEN** 两条消息可关联到同一来源事件/revision，且能分别查看字段、订阅代际和实际发送结果

### Requirement: Blocked publication explains the first failed condition

系统 SHALL 明确记录无订阅、control 未就绪、认证/识别未就绪、必需声明缺失、可选能力缺失、非法 TLV、未知来源语义/单位/枚举、显示限制未知、引用不一致、旧代际、队列拒绝和终态未闭合等阻断原因，不以笼统发送失败替代。

#### Scenario: Route cannot be sent because no start was received

- **WHEN** 有有效快照而没有当前 Link START
- **THEN** 日志指出 no-subscription 和该快照身份，不能误报宿主没有数据

#### Scenario: Lane support is absent while route support exists

- **WHEN** 只有 `5204` 缺少接收声明
- **THEN** 日志明确 lane-capability-missing，不能将核心导航描述为整体未订阅或完全不支持

### Requirement: Protocol mapping evidence is independently verifiable

每个启用字段的登记 SHALL 包含宿主版本与原始生产者位置、Apple 基线哈希与原始地址、值域/单位/编码/门控、当前证据等级和验证入口。生产代码、字符串名、自动反编译或单元测试 MUST NOT 单独作为 Apple 协议证明；仍未闭合项 SHALL 有下一原始分支及关闭条件。

#### Scenario: An encoder exists but semantics are not proven

- **WHEN** Kotlin 编码器支持一个字段宽度而对应枚举或消费者语义未闭合
- **THEN** 登记保留语义 OPEN，不能仅因测试通过就启用该枚举或关闭协议缺口

### Requirement: Local validation and vehicle acceptance have separate results

系统 SHALL 将原字节/指令复核、JVM 行为测试、编译和实车验收分别记录。实车记录 SHALL 绑定提交/构建、会话、车机实际订阅、发送批次和操作步骤；开始、机动、距离、重算、取消、抵达、STOP/START、断开重连 SHALL 分项记录 PASS/PARTIAL/FAIL/OPEN。队列成功或链路 ACK MUST NOT 被报告为仪表显示成功。

#### Scenario: JVM tests pass without a vehicle run

- **WHEN** 映射与生命周期测试通过，但没有匹配实车证据
- **THEN** 记录本地检查通过，仪表显示与互通保持 OPEN

#### Scenario: Packets are acknowledged but display is unknown

- **WHEN** 导航包收到传输 ACK，而没有接收端业务或仪表显示证据
- **THEN** 只记录传输 ACK，不能将路线/转向/清屏验收标为 PASS

### Requirement: Unsupported optional data does not block verified core work

实施与诊断 SHALL 分离已证核心路线/机动、可选车道和独立路面目标检测。无车道来源或 `5204` 支持时 SHALL 保持相应项 OPEN，继续验证满足证据条件的 `5201/5202`；目标检测 `0Dxx` 缺口 MUST NOT 被当作本次导航路线的前置条件。

#### Scenario: No lane producer is available

- **WHEN** 已证路线/机动链路可用但当前宿主没有车道生产者
- **THEN** 系统验证核心链路并单独记录车道 OPEN，不虚构车道数据或将核心工作整体标为阻塞
