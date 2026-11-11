## ADDED Requirements

### Requirement: Publication requires the current authenticated subscription

publisher SHALL 只使用当前 runtime Link 的认证、Identification、control session 可写状态、车机发送/接收声明及有效 `5200` 订阅授权导航发布。必需组 SHALL 为 accessorySends 的 `5200/5203` 和 accessoryReceives 的 `5201/5202`；`5204` SHALL 独立检查。视频 SETUP、bootstrap 全局导航状态及旧 Link 订阅 MUST NOT 授权当前 Link。

#### Scenario: Host route exists before a subscription

- **WHEN** 当前会话有有效导航快照但尚未接受当前 Link 的 START
- **THEN** 系统保留快照并记录无订阅，不能发送 `5201/5202/5204`

#### Scenario: Receiver does not support lane messages

- **WHEN** 四项必需能力齐全并已 START，车机未声明接收 `5204`
- **THEN** 已证路线/机动仍可发布，车道消息被阻断并记录能力缺失

#### Scenario: Video becomes ready without control readiness

- **WHEN** 视频 SETUP 成功但导航 control session 或认证/识别尚未达到要求
- **THEN** 系统不能以视频成功设置导航 ready 或复用 bootstrap 订阅

### Requirement: Subscription commands are validated before mutation

START/STOP SHALL 先通过通用 TLV 父边界与长度验证，再进行消息解析。START p0 SHALL 为可重复 U16，p1–p5 SHALL 为空载荷且各至多出现一次；STOP p0 SHALL 为 U16；未知参数 SHALL 按已证处理器规则处理。非法消息 MUST NOT 修改已有订阅。无 p0 的合法 START SHALL 保留空组件语义，不填默认组件；发送解释未证时 SHALL 阻断相应消息并记录原因。

#### Scenario: Start contains a repeated option marker

- **WHEN** START 重复 p1，或某个 p1–p5 带非空载荷
- **THEN** 整条 START 被拒绝，当前组件、options 和 subscriptionEpoch 不变

#### Scenario: Stop has an invalid component width

- **WHEN** STOP p0 的载荷不是两字节
- **THEN** 系统拒绝 STOP，原订阅和可发布快照仍有效

#### Scenario: Start has no component parameter

- **WHEN** START 的 TLV 与可选标记合法且没有 p0
- **THEN** 系统接受空组件解析结果，不补一个仪表 ID；未闭合的发布语义有明确阻断诊断

### Requirement: Route maneuver and lane messages use verified mappings

系统 SHALL 以同一不可变快照构建 `5201` 路线、`5202` 机动及可选 `5204` 车道。每个启用字段 SHALL 具备宿主生产者语义及 Apple 键/编码/枚举证据；用户授权的 GalaxyPlay 0.1.212 数值核心兼容范围可由本版原字节消费者验证米数与清除顺序，通用 Apple 单位/完整时序继续 OPEN；未知字段 SHALL 省略或阻断相应功能，并保留证据缺口。容量选择后的机动/车道引用、索引和数量 SHALL 一致。跨消息顺序与增量/清除编码 SHALL 经原固件调用链、匹配抓包或上述明确范围的接收端原字节闭合，不从现有 Kotlin 类型反推协议。

#### Scenario: A turn has a verified source and wire mapping

- **WHEN** 已证机动快照、索引/类型/距离及目标消息顺序满足当前订阅与能力
- **THEN** 系统构建引用一致的路线/机动批次，使用同一 revision 与 routeEpoch

#### Scenario: Turn integer is unknown

- **WHEN** 宿主提供未闭合的 navi_turn 数值
- **THEN** 系统不把整数照抄为 `5202` type，不虚构机动定义或路线引用

#### Scenario: Capacity filtering removes a maneuver

- **WHEN** 当前组件能力使某机动不能进入发布窗口
- **THEN** 系统重新计算已证格式下的引用和数量，不发出指向该机动的悬空引用

### Requirement: Identification governs component display boundaries

publisher SHALL 从当前 Identification 取得七项导航显示文本/集合限制，并按每个订阅组件检查。长度单位、零值、缺失值和 NUL 计数 SHALL 以证据为准；未知限制 MUST NOT 被视为无限。截断 SHALL 仅在行为和编码规则已证时执行，不能破坏 UTF-8、TLV 边界或集合引用。必需字段不能合规时 SHALL 阻断对应消息并给出原因。

#### Scenario: Two subscribed components have different limits

- **WHEN** 两个导航显示组件文本/机动容量不同
- **THEN** 系统按已证组件分组规则分别约束编码，不能用第一组件的上限覆盖第二组件

#### Scenario: Text boundary falls inside a UTF-8 character

- **WHEN** 已证字节容量将落在多字节字符中间
- **THEN** 仅在允许截断且 NUL 计数规则已证时取完整字符边界；否则省略字段或阻断消息并记录限制

### Requirement: Accessory stop and host end have different effects

有效车机 STOP SHALL 清当前导航订阅、递增订阅代际并阻止三类导航后续发送，不改变宿主是否正在导航。宿主 Ended SHALL 清本地路线/机动/车道而保留车机订阅；终态 SHALL 仅经已证 `5201` 状态/必要字段表达。手机 MUST NOT 主动发送 `5203` 充当宿主结束。终态映射未闭合时 SHALL 清本地缓存并记录 wire-terminal-unverified，不能报告仪表已清屏。

#### Scenario: Receiver stops subscribing during an active route

- **WHEN** 当前 Link 接受合法 STOP
- **THEN** 尚未交给 writer 的该订阅导航项失效，后续导航消息停止，宿主会话路线可继续更新

#### Scenario: Source ends before terminal state mapping is known

- **WHEN** 已证宿主 Ended 到来但 Apple 终态映射未闭合
- **THEN** 清当前路线/机动/车道，保留车机订阅，不发 `5203` 或猜测终态，并记录未完成的远端清屏能力

#### Scenario: Source ends after terminal state mapping is verified

- **WHEN** 已证 Ended、当前订阅和终态必要字段均满足发布条件
- **THEN** 系统发送已证的终态 `5201`，使旧导航定义失效，不生成重复终态批次

### Requirement: Reconnect and replacement subscriptions invalidate old work

每个发布项 SHALL 携带 session/binding、Link、订阅、路线代际及 revision。writer SHALL 在交付前验证相关代际；新 START、STOP、Ended、Link 失效和宿主解绑 SHALL 使冲突的未发送项失效。新 Link SHALL 重新认证/识别和 START 后才发布；来源仍有效时从当前会话快照按新组件/options 重编码，不能复用旧 TLV。

#### Scenario: A queued update survives into a new Link

- **WHEN** 旧 Link 关闭并建立新 Link，旧导航项还在队列
- **THEN** 旧项不能交给新 Link writer；新 START 后仅按新能力编码当前有效快照

#### Scenario: Receiver replaces a subscription

- **WHEN** 新 START 修改组件/options
- **THEN** 旧订阅批次失效，当前快照按新订阅重编码，投递基线重新建立

### Requirement: Queue outcomes do not imply complete delivery

批次 SHALL 通过单一 writer 按已证顺序提交；系统 SHALL 区分 planned、queued、writer-sent、传输 ACK 和业务/显示验收。队列拒绝或部分消息失败 MUST NOT 推进整个批次的成功基线。导航层 MUST NOT 新增固定延时重发或无条件重发；链路可靠传输 SHALL 继续由 iAP2 传输层负责。

#### Scenario: A batch fails after its first message

- **WHEN** 三类导航批次中的首消息已发送而后续队列提交失败
- **THEN** 系统记录已发送部分与失败原因，不把整个快照标记为已交付，不启动盲目重发计时器

### Requirement: Numeric core has an explicit compatibility boundary

当前实现 SHALL 使用已证 Apple 状态/类型、5202 p1/p3 和 5201 p1/p10/p13，构建每次自包含的定义与引用。实际 START 组件 SHALL 各有唯一合法 p30/p0/p6 正容量。文本/车道合同未知 SHALL 不阻断合法数值核心。局部 receiver 单位/清除合同 MUST NOT 被宣称为所有 Apple 时序或实车 PASS。

#### Scenario: Current maneuver distance becomes unknown

- **WHEN** 已知机动的距离变为零、异常或 unknown
- **THEN** 系统 reset 后重新定义与引用当前机动，并省略距离，防止 receiver 合并旧 segment

#### Scenario: Source ends with an unknown reason

- **WHEN** 已证来源 Ended 但无法区分取消/抵达
- **THEN** 系统仅发布 NotActive，不制造 Arrived，也不改变当前订阅
