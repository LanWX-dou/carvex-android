# analysis/05 — 导航 / HUD（特性 17）

导航是本阶段消息最多的一组：入站 3 条（`0x5200`/`0x5203`/`0x0D01`），出站 5 条
（`0x5201`/`0x5202`/`0x5204`/`0x0D00`/`0x0D02`）。本文件重点写清**两条硬事实**：
1. 每条消息的方向不是靠编号区间猜的，而是由固件里的"必需消息表"逐条给出；
2. 方向决定它是被"入站集合"还是"出站集合"校验的。

## 5.1 必需消息表（第二道门）

`0x5200` 处理器解析参数、取得特性对象后才调用
`_iap2_identification_checkRequiredMsgIDs(endpoint, &_gskMsgNavigationMainList, 5, &out)`
（调用点见 `analysis/02` 的 `0x10017527c` 段；被调函数 `0x100050c2c`）。

`0x100050c2c` 的表项布局（指令证据）：

| 偏移 | 宽度 | 含义 | 证据 |
|---|---|---|---|
| `+0` | u16 | `msg_id` | `ldrh w1,[x27]`（`0x100050c7c`） |
| `+4` | u32 | 方向：`1` = 查**出站**集合，`0` = 查**入站**集合 | `ldr w8,[x27,#4]` / `cmp w8,#1`（`0x100050c80`–`0x100050c8c`） |
| `+8` | u8 | `required`：0 表示"可选" | `ldrb w9,[x27,#8]`（`0x100050cb4`） |
| 步长 | 12 B | `index*3*4` | `add x8,x24,x24,lsl#1` + `lsl #2`（`0x100050c74`–`0x100050c78`） |

`A05.1`：`_gskMsgNavigationMainList`（`0x1001b40e0`）5 项，逐字节解出：

| # | msg_id | 方向 | required |
|---|---|---|---|
| 0 | `0x5200` | 入站 | 是 |
| 1 | `0x5201` | 出站 | 是 |
| 2 | `0x5202` | 出站 | 是 |
| 3 | `0x5203` | 入站 | 是 |
| 4 | `0x5204` | 出站 | 否 |

`A05.2`：`_gskMsgRoadObjectDetectionMainList`（`0x1001b411c`）4 项：

| # | msg_id | 方向 | required |
|---|---|---|---|
| 0 | `0x0D00` | 出站 | 是 |
| 1 | `0x0D01` | 入站 | 是 |
| 2 | `0x0D02` | 出站 | 是 |
| 3 | `0x0900` | 入站 | 否 |

这就是 `0x0D00`/`0x0D02` 方向与"`0x0D01` 是入站"的直接证据，也解释了
`0x1001783bc` 里出现的 `0xD00` 立即数（`analysis/05` 5.4）。

## 5.2 `0x5200` StartRouteGuidance：参数表

| 参数 ID | 类型 | 去向 | 证据 |
|---|---|---|---|
| `0` | U16 | 组件 ID | 跳表 `0x100018xxx`（`analysis/02` 给出 `case` 地址 `0x1001753c0`），取值原语 `0x100067e1c` |
| `1` | 空值（总长4） | options标记，不进组件列表 | `case 0x100175450`；取值原语 `0x100067f3c`；`A11.3` |
| `2` | 空值（总长4） | options标记 | `case 0x100175420` |
| `3` | 空值（总长4） | options标记 | `case 0x100175438` |
| `4` | 空值（总长4） | options标记 | `case 0x100175408` |
| `5` | 空值（总长4） | options标记 | `case 0x100175468` |

`A05.3`（本轮纠错）：参数0的U16值加入 `componentIdList`；参数1–5是空值标记，
置位后组装成 `options`。非空/重复标记返回失败，不解析子参数组（A12.4/A12.5）。最终交给平台——
`_platform_navigation_startRouteGuidance(endpoint, componentIdList, options)`（`0x1000dc778`），
日志 `navigation startRouteGuidance: %@, componentIdList=%@, options=%llxh`。
`0x5200` **不携带**显示能力：7 个"显示能力"设置函数由**识别解析器**
`__parseIdentificationParams`（`0x1000c5704`）在识别阶段调用（调用点 `0x1000c5c78`–`0x1000c5d38`）。
依据：A12.5；`OPEN-NAV-2` 改为 options 业务含义及profile要求，原“内部子结构”前提撤回。

日志串证明处理器的语义：
`iAP2Navigation StartRouteGuidance Handler %@`（`0x100202688`）、
`iAP2Navigation StartRouteGuidance: for componentList=%@`（`0x1002026db`）。

## 5.3 `0x5203` / `0x0D01`

- `0x5203` StopRouteGuidance：日志 `iAP2Navigation StopRouteGuidance Handler %@`（`0x100202713`）、
  `… : for componentList=%@`（`0x100202764`），调用 `_platform_navigation_stopRouteGuidance`（`0x1000dc880`）；
- `0x0D01` RoadObjectDetectionUpdate：日志 `… process paramID=%d`（`0x1002027cf`），
  逐个参数调用 `_platform_navigation_objectDetectionInfoGetItem` 并最终调用
  `_platform_navigation_objectDetectionUpdateInfo(endpoint, 0, info)`（`0x1000dc974`）。

`A05.4`：`0x0D01` 的参数没有跳表（`analysis/02` 显示 `limit=None`），
它按 `process paramID=%d` 逐条处理，参数 ID 集合未闭合（`OPEN-NAV-3`）。

## 5.4 出站四条

| msg_id | 发送点 | 符号 | 语义（来自符号/日志） |
|---|---|---|---|
| `0x5201` | `0x1000027f4` | `_iap2_navigation_routeGuidanceUpdateHandler` | 路况更新（`OUTLINED_FUNCTION_17(…,0x5201,…)`） |
| `0x5202` | `0x1001777c0` | `_iap2_navigation_routeGuidanceManeuverUpdateHandler` | 机动点更新 |
| `0x5204` | `0x100177d80` | `_iap2_navigation_laneGuidanceInfoUpdateHandler` | 车道指引更新 |
| `0x0D00` | `0x1001783bc` | `_iap2_navigation_startRoadObjectDetectionHandler` | 开始目标检测（立即数 `0xD00`，`0x1001786b8`） |
| `0x0D02` | `0x1001788f4` | `_iap2_navigation_stopRoadObjectDetectionHandler` | 停止目标检测（立即数 `0xD02`，`0x100178ac4`） |

## 5.5 字段与状态转换

| 函数 | 地址 | 用途 |
|---|---|---|
| `_platform_navigation_routeGuidanceInfoKeyForType` | `0x100003b18` | 类型 → 字典键 |
| `+[ACCNavigationRouteGuidanceUpdateInfo keyForType:]` | `0x100003b28` | 同上（ObjC 侧） |
| `__convertRouteGuidanceStateTypeForFunc` | `0x100004428` | 导航状态值转换 |
| `_platform_navigation_maneuverInfoKeyForType` | `0x1000dd130` | 机动点字段键 |
| `_platform_navigation_laneGuidanceInfoKeyForType` | `0x1000dd140` | 车道指引字段键 |
| `_platform_navigation_laneInfoKeyForType` | `0x1000dd150` | 车道字段键 |

`A05.5`（部分确认）：字段名由 `keyForType:` 一族函数按"类型号"给出，类型号 → 键的映射表
在这些函数体内（未逐条读完），因此**字段名可枚举但顺序未证**（`OPEN-NAV-4`）。

## 5.6 门控与顺序

- 三条入站都需 `认证==2 ∧ 识别==6 ∧ ID 在入站集合`（`sess/R-5.x`）；
- 额外的"必需消息表"检查发生在处理器内部：`checkRequiredMsgIDs` 返回 0 时处理器直接放弃
  （`0x10017527c` 的 `if (iVar4 != 0)` 分支，见 `analysis/02`），
  也就是说**车机没在识别阶段声明这些 ID，导航消息会被静默丢弃**；
- 顺序：`0x5200`（开始）→ `0x5201`/`0x5202`/`0x5204`（更新）→ `0x5203`（停止）；
  `0x0D00`（开始检测）→ `0x0D01`（更新）→ `0x0D02`（停止）。更新先于开始的行为未证（`OPEN-NAV-5`）。

## 5.7 未决

| 编号 | 内容 | 关闭条件 |
|---|---|---|
| `OPEN-NAV-2` | `0x5200` options位业务含义与profile要求（空值格式已证） | 需平台options解释；旧“组件描述子结构”前提由A12.5撤回 |
| `OPEN-NAV-3` | `0x0D01` 的参数 ID 全集与嵌套结构 | 逐条读比较链，或抓包 |
| `OPEN-NAV-4` | `keyForType` 的类型号 → 字段名完整映射 | 读三个 `keyForType` 函数体 |
| `OPEN-NAV-5` | 更新消息先于开始消息时的行为 | 抓包 |
