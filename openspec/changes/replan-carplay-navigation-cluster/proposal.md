## Why

现有链路把 CarWith HUD 的 `road_name`、`remain_distance` 直接转成 `5201` 的当前道路和路线剩余距离，宿主开始通知尚未形成可发布的导航状态，转向机动 `5202` 与车道 `5204` 也未接通。重新规划需要同时闭合宿主语义、CarPlay/iAP2 字段映射和当前 Link 的订阅生命周期，让仪表收到一致、可追溯的导航数据。

## What Changes

- 建立协议无关的导航事件与快照契约，包含来源、路线代际、生命周期、路线概览、机动和车道；厂商 Intent 在宿主适配器内解析。
- 将会话导航快照与 Link 导航订阅分别管理，通过当前认证/识别、消息方向声明、显示组件能力和实际 `5200` 授权发布。
- 以 `5201` 发布路线指引，以 `5202` 发布机动，以可选 `5204` 发布车道；上线字段必须具有宿主生产者和 Apple 编码证据；用户授权的 GalaxyPlay 兼容范围可使用此接收端原字节消费证据，并保持通用 Apple 单位/时序 OPEN。
- 明确车机 `5203` 是停止订阅；宿主结束导航通过已证的 `5201` 状态表达。尚未闭合结束状态时只清本地路线并记录缺口，禁止手机发送 `5203` 冒充结束通知。
- 统一不可变快照、队列失效、重订阅重编码和断开代际隔离；显示能力取自 Identification，未知容量不得解释成无限。
- 增加从宿主事件到仪表验收的诊断关联，以及按阶段推进的固件、宿主、JVM 和实车验证任务。
- **BREAKING**：桥接层的厂商导航 Intent 分支迁入宿主模块，使用新增的导航契约；内部调用方同步迁移。未证 HUD 道路/距离不再发布，车机消息格式不自行扩展。

## Capabilities

### New Capabilities

- `navigation-source-contract`：宿主导航事件、类型与单位、来源证据、快照合并、结束去重和路线代际。
- `carplay-navigation-publication`：当前 Link 能力与订阅门控、`5201/5202/5204` 编码、显示边界、停止与重连处理。
- `navigation-delivery-diagnostics`：事件/快照/订阅/队列关联、阻断原因、分级验证和实车验收证据。

### Modified Capabilities

无既有 OpenSpec 主规格。上述新增规格描述本次实现目标；已有协议事实继续以 `research/protocol/iap2_input_business_lifecycle/` 为单一来源，不把设计决策提升为 Apple 协议结论。

## Impact

- 计划影响 Android 的 `:host-api`、`:host-carlife-mixing`、`:protocol-api`、`:bridge`、`:protocol-carplay`，以及 `:app` 的必要接线；不新增第三方依赖。
- 重点迁移 `SessionController.kt` 的导航解析及快照，扩展 `NavigationPublisher.kt`，保留 `NavigationGuidance.kt` 作为纯协议解析/编码入口。
- 证据推进落在导航 docset 的 `analysis/`、`source/`、`spec/` 与 `research/connection/` 的宿主/运行记录，遵守原固件字节与 DEX 指令证据规则。
- 用户已授权修改代码。当前交付包含事件/快照/订阅迁移、排队撤销及基础转向/正数机动距离/结束 reset。机动容量使用实际 Identification；文本/车道、通用单位/时序和实车缺口保留 OPEN。音乐已由用户确认正常；通话单独提交。详见 [实施记录](../../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md)。未构建 APK 或安装。
