当前已完成 25/38 项：导航契约、会话 relay、当前 Link 订阅、数值核心、队列撤销、投递关联诊断和本地验证。未勾选项保留证据/生产编码/实车缺口；规划或基础设施完成不等于仪表互通完成。任务遵循 [设计](design.md) 和三份 [需求](specs/navigation-source-contract/spec.md)、[发布需求](specs/carplay-navigation-publication/spec.md)、[诊断需求](specs/navigation-delivery-diagnostics/spec.md)。

## 1. P0 实施前状态与证据基线

- [x] 1.1 阅读根/Android AGENT.md，检查两个仓库工作区状态，备份本阶段将修改的已有文件，记录提交/基线，不覆盖用户改动。
- [x] 1.2 复核 accessoryd 原镜像 SHA256 与导航 docset 原始切片，运行对应 verify.py；缺依赖/证据时记录 SKIP/OPEN，不把跳过当通过。
- [x] 1.3 建立导航字段合同表，逐项记录宿主生产者、Apple 原地址、编码/枚举/单位/options/显示门、证据等级和关闭条件；生产启用仅使用两端语义均闭合的项。

## 2. P0 Apple 导航字段与订阅审计

- [ ] 2.1 从 `0x100003b28` 及机动/车道 keyForType 入口追原跳表、常量和消费者，核实三类更新字段键，更新 OPEN-NAV-4 的已证范围与剩余分支。
- [ ] 2.2 从 `0x100004428` 及调用者闭合 active/inactive/rerouting/ended 等真正存在的状态与映射；区分通用结束、取消和抵达，不从数值范围猜名称。
- [ ] 2.3 核 `5201/5202` 距离单位、ETA/剩余时间基准、机动类型/方向/角度与索引含义，记录未证明的枚举及可用字段子集。
- [ ] 2.4 追 `5200` options 的平台消费与出站逐字段门，核无组件 START 的适用语义和 `5203` 组件作用范围；未证细粒度停止时保持全订阅停止策略。
- [ ] 2.5 追 Identification 七项导航显示能力的原解析及消费者，核长度单位、NUL、零值/缺失和机动/车道容量；找到现有 Android 能力对象到 publisher 的接线缺口。
- [ ] 2.6 从 `0x1000027f4/0x1001777c0/0x100177d80` 的调用/消费路径闭合首报、增量、机动/车道定义与引用顺序，以及清除/终态编码；未证顺序继续登记 OPEN-NAV-5。

## 3. P0 宿主生产者语义审计

- [x] 3.1 获取可读的对应版本宿主原 APK/DEX，复核 H01 指令哈希、Boolean isNavi 和整数 action 的生产路径，核首次 HUD 是否能独立产生 Started。
- [ ] 3.2 继续追 UCarMapInfo WHERE/DISTANCE/DISTANCE_UNIT 的外部生产者及有效性，区分机动距离和路线距离；核零值异常边界，禁止 total_distance 映射全程距离。
- [x] 3.3 追 navi_turn 实际图标分类器与原模板，闭合已确认基础方向和 Apple maneuver type 的合同，其他组明确保留 unknown。
- [ ] 3.4 查当前 mixing 公共回调是否提供目的地、ETA、当前路/转向后道路、路线 ID/序号和车道，逐品牌记录能力；将来源迟到样本无法归属的边界单独登记。

## 4. P1 导航契约和会话 relay

- [x] 4.1 在 `:host-api` 定义协议无关的导航事件/有效性类型，在 `:protocol-api` 定义独立发布输入与端口，保持协议接口不依赖宿主包。
- [x] 4.2 在 `:host-carlife-mixing` 生成导航事件，迁移 bridge 的厂商 Intent 解析与严格结束判断；未知品牌能力不自动复用小米合同。
- [x] 4.3 实现 `HostNavigationRelay` 的不可变快照、Absent/Value/Clear 合并、机动/路线从属清理和 revision，取代 `latestNavigation` 业务缓存。
- [x] 4.4 实现绑定/路线代际、双结束幂等、结束后普通更新禁止重激活及旧本地异步结果丢弃；保留上游无标识乱序的 OPEN 边界。
- [x] 4.5 添加契约/relay 行为测试，覆盖缺失不清除、合法零、错误类型、可变输入、机动替换车道清理、双结束、新路线及本地迟到任务。
- [x] 4.6 将 SessionController 接到 relay 与协议端口，通过 `:app` 组装；检查 NavigationGuidance 全局兼容调用者，保证 runtime 授权不读旧 bootstrap 状态。

## 5. P2 当前 Link 订阅和显示能力

- [x] 5.1 将当前 runtime Link 的认证/识别/control 可写与 accessorySends/accessoryReceives 显式交给 publisher，保留四项必需组和 `5204` 独立能力门。
- [x] 5.2 接入已证的 START/STOP 原子验证和 subscriptionEpoch；非法消息保持原状态，无组件 START 不补默认 ID，STOP 同时使未发送项失效。
- [ ] 5.3 将 Identification 组件能力传至 publisher，按组件已证长度/容量限制文本与集合，验证 UTF-8/NUL 与机动/车道引用边界。
- [x] 5.4 实现 Link 失效、新 START 和重连后的旧订阅/能力/编码基线清除；来源仍有效时取得当前 relay 快照并按新订阅重编码。
- [x] 5.5 添加订阅/能力测试，覆盖缺必需声明、缺可选车道、视频 ready 误授权、坏 TLV、重复空标记、空组件 START、STOP 以及组件不同容量。

## 6. P2 路线、机动与结束发布

- [x] 6.1 将 P0 已证字段合同接入类型化 `5201/5202` 编码；未闭合的旧 currentRoad/distanceRemaining 映射不得作为隐性回退保留。
- [x] 6.2 从同一快照构建路线/机动批次，按已证规则维护索引、引用、数量和增量/清除，保证首报、重订阅、新路线的状态完整。
- [x] 6.3 接入已证的宿主开始/重算/结束映射，终态经 `5201` 发送，保留订阅；未闭合终态时只清快照并记录 wire-terminal-unverified，不主动发 `5203`。
- [x] 6.4 在 writer 边界检查 session/binding/Link/订阅/路线代际，串行提交批次；明确 partial-send/queue-rejected，不推进整批成功基线、不增加盲重发。
- [x] 6.5 添加发布集成测试，覆盖同快照引用、START 前缓存、重订阅重编码、未知 turn/单位省略、Ended 屏障、队列失败/部分发送、STOP 和重连旧项失效。

## 7. P3 可选车道

- [x] 7.1 依据已证车道生产者与 Apple 原编码合同生成车道快照；若来源缺失，登记具体 OPEN 和关闭条件，不伪造车道或阻塞核心路线/机动。
- [ ] 7.2 实现 `5204` 嵌套 TLV、组件容量与机动关联，并在真实接收声明存在时发布；未闭合空集合清除格式时不造空 TLV。
- [ ] 7.3 添加车道测试，覆盖无 `5204` 支持、容量过滤、引用一致、新机动清旧车道、STOP/Ended 清理和重订阅当前车道恢复。

## 8. P4 日志、检查与实车验收

- [x] 8.1 添加宿主事件→快照→批次→writer 的关联日志，记录所有代际、字段/证据项、首个阻断原因；遵守现有脱敏规则。
- [x] 8.2 按实际改动运行 `:host-api:test`、`:host-carlife-mixing:testDebugUnitTest`、`:protocol-carplay:testDebugUnitTest`、`:bridge:testDebugUnitTest` 及小米 app Kotlin 编译，接口影响其他 flavor 时补对应编译/测试；运行 diff 空白与文档链接检查。
- [x] 8.3 同步研究的已证边界、阶段结果和用户可见变化说明；涉及入口文档规则/状态变化时同步中英，不把本地测试写成实车互通。
- [ ] 8.4 准备可追溯提交及实车测试步骤；用户自行构建安装，逐项验证开始、机动、距离递减、重算、取消、抵达，保留完整会话/订阅/发送日志。
- [ ] 8.5 独立验证车机 STOP→START、宿主结束后再订阅、导航途中断开重连、不同组件能力；将传输 ACK、业务接受和仪表显示分别记录 PASS/PARTIAL/FAIL/OPEN。
- [x] 8.6 汇总实际完成阶段、启用字段和剩余证据/实车缺口；只有匹配证据达到各项关闭条件后才能关闭对应 OPEN 或标记功能完成。

## 本轮完成范围与剩余边界

新增完成 3.3、5.5、6.1、6.2、6.5：基础图标映射、实际组件容量门、生产数值编码、自包含定义/引用批次以及相关发布测试。未知组继续 unknown，不勾选通用 Apple 顺序/单位或文本/车道合同任务。

2.3 的原状态/类型枚举已闭合，但完整距离单位与 ETA 消费合同仍未齐；2.5/5.3 已接入 p30/p0/p6 正机动容量，文本/NUL 和车道仍 OPEN；2.6 通用 Apple 顺序仍 OPEN，当前清除/合并只限 GalaxyPlay 核查范围。3.2/3.4 保留外部地图阶段、道路角色、routeId/sequence 和可选字段缺口。6.3 现已发布 NotActive，结束原因仍 unknown。7.1 完成的是缺来源分支，不声称实现车道。8.1 已于 2026-11-12 补齐当前链路字段/证据与冻结批次的关联诊断，8.4/8.5 的实车工作尚未执行。

原 docset 完整 FAIL 保留历史记录，新原表/字节复核独立记录，不改写旧 manifest。详细见[实施记录](../../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md)、[数值核心证据](../../../research/connection/spec/navigation-numeric-core-20261111.md)和[检查记录](validation.md)。音乐已由用户确认正常；通话作为下一条独立提交，不能把本地导航修复写成仪表已实车通过。

## 2026-11-12 新版来源补证

日志 7 的 132 条 CarWith 4.0.23 来源输入被旧版本门拒绝，当前 GalaxyPlay 会话已有订阅。已补 3.1/3.3/4.2 的新版范围：独立原 APK 的 9 个方法、18 个未变模板，H02 地址与严格类型，以及 2 项版本升级回归；离线宿主/bridge/协议测试 XML 合计 1,228 项通过，小米编译通过。详见[新版审计](../../../research/connection/spec/carwith-navigation-upgrade-20261112.md)和[实施记录](../../../android/docs/fixes/2026-11-12-carwith-navigation-version.md)。

原清单保持 24/38：此次恢复已实现数值核心的来源适配，不关闭道路/车道/路线时间、全程距离来源或修复后实车项目，不归档变更。

## 2026-11-12 续接：投递诊断

新增完成 8.1，当前 25/38。宿主接收/拒绝、规范化、规划、排队、writer-check 和完成日志关联原快照与批次；道路/目的地/来源 route ID 脱敏，日志异常不改变 writer 有效性决定。新增四项回归及专用车道能力阻断断言。详见[诊断实施记录](../../../android/docs/fixes/2026-11-12-navigation-delivery-diagnostics.md)和[字段原字节续查](../../../research/connection/spec/galaxyplay-navigation-fields-20261112.md)。

2.1/2.5/5.3 和 3.2/3.4/7.2 的字段证据缺口仍未关闭：原地图身份未进入 HUD，Apple shared-cache 长度目标缺失，真实全程公里/分钟来源与本版 5204 支持均未补齐。未打包、安装、提交或实车验收。

## 2026-11-12 日志 8 显示反馈

用户确认已显示“前方 258 米右转”、总距离和时间，前方车道仍缺失。本次 25 条新版宿主来源事件成功解码，45 条导航消息记录本地发送完成，证明日志 7 的版本拒绝已恢复。结果记为 PARTIAL，详见[日志 8 反馈及计数证据](../../../research/connection/spec/navigation-log8-feedback-20261112.md)。

车道同时缺真实 CarWith 来源和当前 GalaxyPlay `5204` 接收支持；原 APK 5 个 DEX、28 个方法复核 PASS，导航 accept 仍只接收 `5201/5202`。全程距离/时间虽已显示，本日志的规范化值缺失且出站未含 p5/p6/p7，显示来源合同仍 OPEN。保持 25/38，不勾选 7.2/7.3 或全部 8.4/8.5；本轮只同步研究状态。
