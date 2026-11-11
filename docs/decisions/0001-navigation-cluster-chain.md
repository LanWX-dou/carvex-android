# 0001 — 导航信息推送车机仪表链路

日期：2026-11-11。状态：已实施数值核心、快照、订阅与投递撤销；实车验收待完成。

## 背景

修改前导航桥接把部分 HUD 道路/距离交给 iAP2 路线更新，宿主状态、机动和车道链路尚未完整接入。规范化路线和车机订阅需要分别管理，以防止结束后回放旧路线、跨 Link 授权或不一致的机动引用。

## 决策

导航链路按宿主事件适配、协议无关契约、会话唯一快照、当前 Link 的能力/订阅门控和 iAP2 发布分层。厂商导航语义归 `:host-carlife-mixing`，契约归 `:host-api`/`:protocol-api`，编排归 `:bridge`，Apple 字段/订阅/编码归 `:protocol-carplay`，`:app` 组装。

车机停止订阅与宿主结束导航具有独立作用。各出站字段必须具有两端来源/编码证据；车机→仪表的内部接收与显示不在手机实现边界内，验收单独记录。

完整设计、需求和任务保存在 [OpenSpec 变更](../../openspec/changes/replan-carplay-navigation-cluster/proposal.md)、[链路设计](../../openspec/changes/replan-carplay-navigation-cluster/design.md) 和 [实施清单](../../openspec/changes/replan-carplay-navigation-cluster/tasks.md)。OpenSpec 需求是实现目标，不替代 `research/` 下的协议事实。

## 后果

先补宿主/Apple 映射证据，再迁移事件契约和快照，随后完成路线/机动及可选车道，最后进行分项实车验收。历史未证字段不会因已有编码器或设备队列记录被升级为 CONFIRMED。

用户授权以 GalaxyPlay 0.1.212 核查结果修复后，已接通 CarWith 基础转向与正数机动距离。Apple 状态/类型/参数宽度由原表闭合，米数消费与清除顺序由此接收端原 DEX 支持；不将其提升为所有 Apple 发送时序。道路/ETA/车道和实车显示仍 OPEN。详见[实施记录](../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md)及[数值核心证据](../../research/connection/spec/navigation-numeric-core-20261111.md)。

## 证据

- [导航协议要求](../../research/protocol/iap2_input_business_lifecycle/spec/03-navigation-hud.md)。
- [导航消息方向与原始地址](../../research/protocol/iap2_input_business_lifecycle/analysis/05-navigation-hud.md)。
- [CarWith 生命周期与距离 DEX 证据](../../research/connection/spec/carwith-4.0.14-host-evidence.md)。
- [既有仪表推送记录及验收缺口](../../research/connection/spec/cluster-publishing-audit-20261109.md)。
