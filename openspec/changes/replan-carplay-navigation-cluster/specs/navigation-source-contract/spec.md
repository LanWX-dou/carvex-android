## ADDED Requirements

### Requirement: Navigation events have a protocol independent contract

系统 SHALL 在 `:host-api` 提供有类型的导航事件，携带宿主来源、绑定代际、已知来源路线标识/序号及字段有效性。厂商 action、extra 类型、枚举和单位 SHALL 由宿主适配器解释；`:bridge` SHALL 只通过契约编排，`:protocol-carplay` MUST NOT 依赖厂商 Intent 或宿主包。协议发布端口 SHALL 归 `:protocol-api` 且不依赖 `:host-api`，二者转换在 bridge。

#### Scenario: Host produces a supported lifecycle event

- **WHEN** 已验证的宿主发出严格布尔 true 的导航开始通知
- **THEN** 宿主适配器产生来源明确的 Started，bridge 合并事件而不读取厂商 action 或生成 iAP 状态整数

#### Scenario: Another vendor has no verified navigation source

- **WHEN** 某品牌宿主没有已确认的导航回调合同
- **THEN** 系统报告该来源能力未知，不复用 CarWith action/枚举产生导航事件

### Requirement: Source semantics and valid values are explicit

每个导航字段 SHALL 区分已证有效值、缺失、显式清除和语义未确认；整数宽度、距离/时间单位和枚举 SHALL 经来源证据验证。系统 MUST NOT 将 `total_distance` 的提示缓存距离当作全程距离，MUST NOT 将宿主 action 或 navi_turn 数值直接作为 Apple 枚举，也 MUST NOT 从未知/异常转换出的零距离推定抵达。

#### Scenario: HUD contains only unclassified road and distance

- **WHEN** HUD 包含 road_name/remain_distance，但其道路角色、导航阶段距离或零值有效性尚未闭合
- **THEN** 系统保留来源观测与未确认原因，不生成已证的 currentRoad、distanceRemaining 或 arrived

#### Scenario: Wrong lifecycle extra type

- **WHEN** isNavi 为字符串 false、整数 0，或 action 为字符串 3
- **THEN** 系统不产生 Ended，也不改变当前路线生命周期

### Requirement: One immutable snapshot belongs to each active session

系统 SHALL 通过会话级串行 relay 维护唯一规范化导航快照，包括 sourceId、hostBindingEpoch、routeEpoch、revision、生命周期、路线、机动和车道。增量 SHALL 区分 Absent/Value/Clear，保存有效零值，复制可变输入；新路线/机动替换 SHALL 清除其已失效从属字段。协议模块 SHALL 从该快照构建发送数据，不维护第二份可独立变化的业务快照。

#### Scenario: A distance update omits destination

- **WHEN** 同一路线的新有效距离增量没有目的地字段
- **THEN** 快照保留已知目的地、更新距离并递增 revision，不把缺失当作清除

#### Scenario: Maneuver changes after lane data was received

- **WHEN** 新机动替换当前机动且没有新车道数据
- **THEN** 新快照清除旧机动的车道关联，不能将旧车道作为新机动的车道发布

#### Scenario: Host mutates a list after callback

- **WHEN** 宿主回调后修改原机动/车道列表
- **THEN** 已接收的快照内容和待发送批次不随原列表改变

### Requirement: Ending a route is idempotent and prevents stale revival

relay SHALL 对已证 Ended 清除路线/机动/车道并保留最小终态记录，同一路线的重复结束 SHALL 幂等。Ended 后普通 Updated MUST NOT 自行重新激活路线；新的已证 Started SHALL 建立新 routeEpoch。所有本地异步任务 SHALL 检查创建时的绑定/路线代际；缺少上游路线标识或序号时 SHALL 显式记录无法识别跨路线迟到包的边界。

#### Scenario: CarWith sends both end notifications

- **WHEN** 同一来源先发送 isNavi=false，再发送 HUD action=3
- **THEN** 当前 routeEpoch 只结束一次，第二通知不创建新路线或重复生成终态发布修订

#### Scenario: Old local work completes after a new route

- **WHEN** 旧 routeEpoch 的异步转换在新 Started 后完成
- **THEN** 系统丢弃旧转换结果，不能覆盖新路线、机动或车道

#### Scenario: Late ordinary HUD follows an end

- **WHEN** 已结束来源发送普通 HUD Updated，且未出现可靠新 Started
- **THEN** 系统不重新激活或发布该路线；记录迟到或缺少开始边界

### Requirement: Route lifecycle is separate from prompt and display activity

系统 SHALL 只依据已证导航来源确定路线生命周期。提示 PCM 的开始/结束、音频焦点、投屏前后台和车机 `5203` MUST NOT 被解释为宿主路线开始、结束或抵达。无法区分取消/抵达的来源 SHALL 保留 unknown 结束原因。

#### Scenario: A turn prompt finishes while navigation continues

- **WHEN** 导航语音提示自然结束，但宿主仍在导航
- **THEN** 路线快照和仪表订阅保持有效，系统不生成 Ended

#### Scenario: Host sends a generic end

- **WHEN** 来源只能证明导航结束，不能证明取消或抵达
- **THEN** 系统产生结束原因 unknown，不自动映射到 arrived
