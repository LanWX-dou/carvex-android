# analysis/01 — 输入 / 业务 / 生命周期的消息地图

本文件回答一个问题：**本阶段涉及哪些消息，每条消息由哪个函数处理/发送，方向如何判定，门控在哪。**
所有行都能点回固件地址；判定方法写在 1.1，避免"按编号区间猜语义"。

## 1.1 证据来源与判定规则

| 事实 | 来源 | 判定规则 |
|---|---|---|
| 一条消息"入站"（车机 → 设备） | 特性信息表 `__kiAP2FeatureInfoEntries`（`0x10021b550`，29 项）里的处理器表 | 表项 16 字节 `{u32 msg_id; u32 reserved; u64 handler}`，处理器表只被入站分发使用（`sess/A05.7`、`sess/R-4.12`） |
| 一条消息"出站"（设备 → 车机） | 发送函数里的 `iAP2MsgInit(msg, msg_id, …)` 立即数 | 只在**构造消息**时出现，且该 ID 不在任何处理器表里 |
| 参数结构 | 处理器里的参数 ID 分派（跳表或比较链）+ 取值原语 | 取值原语决定宽度：`0x100067e1c` 要求参数总长 6（2 字节值）；`0x100067e4c` 要求 5（1 字节值）；`0x100067f3c` 返回总长<5（合法TLV下为空值，见A12.4），不是变长数据getter |
| 字段名 | 处理器引用的 `os_log` 格式串 | 必须给出串地址；字符串是**旁证**，不是定义 |
| 门控 | `0x100051054`（入站）/ `0x100005138`（出站）两张白名单 | 见 `sess/analysis/07`；本阶段不重推 |

**命名证据**：符号表里这四组函数都有真实名字（`_iap2_hid_*`、`_iap2_nowPlaying_*`、
`_iap2_navigation_*`、`_iap2_assistiveTouch_*`）。名字来自符号表，语义仍以指令为准；
未命名的函数一律写"（无符号）"，**不按名字反推语义**。

## 1.2 本阶段相关的特性

特性表里与本阶段相关的 5 项（其余 24 项属识别/认证/会话/媒体库/语音等，见 `sess/analysis/06`）：

| 特性号 | 处理器表符号 | 处理器数 | 本阶段用途 |
|---|---|---|---|
| 3 | `_kiAP2MessageHandlerEntries_AssistiveTouch` | 4 | 触摸/辅助触控（0x5400 / 0x5401 / 0x5402 / 0x5404） |
| 11 | `_kiAP2MessageHandlerEntries_HID` | 4 | HID 组件（0x6800 / 0x6802 / 0x6803 / 0x6805） |
| 14 | `_kiAP2MessageHandlerEntries_NowPlaying` | 3 | NowPlaying 订阅（0x5000 / 0x5002 / 0x5003） |
| 17 | `_kiAP2MessageHandlerEntries_Navigation` | 3 | 导航/HUD（0x5200 / 0x5203 / 0x0D01） |
| 20 | `_kiAP2MessageHandlerEntries_Vehicle` | 1 | 车况（0x5600 入站 / 0xA100 出站），只作生命周期相邻参考 |

`A01.1`：这五项特性在 `__kiAP2FeatureInfoEntries` 里的 `feature_id` 分别为 3、11、14、17、20，
处理器计数分别为 4、4、3、3、1，合计 15 条入站消息。

## 1.3 入站消息（车机 → 设备）

| msg_id | 特性 | 处理器 | 处理器符号 | 参数上界 | 说明 |
|---|---|---|---|---|---|
| `0x6800` | 11 | `0x100130444` | `_iap2_hid_StartHIDMsgHandler` | 4（0 起 5 个） | 注册 HID 组件 |
| `0x6802` | 11 | `0x100130cf0` | `_iap2_hid_AccessoryHIDReportHandler` | 1（0 起 2 个） | 车机上报 HID 输入报告 |
| `0x6803` | 11 | `0x1001313dc` | `_iap2_hid_StopHIDMsgHandler` | 0 | 清组件状态位，保留字典项/接口 |
| `0x6805` | 11 | `0x10013101c` | `_iap2_hid_AccessoryHIDGetReportResponseHandler` | 3（0 起 4 个） | 车机对 getReport 的响应 |
| `0x5000` | 14 | `0x1001499f0` | `__startNowPlayingUpdatesHandler` | 0–2（比较链） | 开始订阅 NowPlaying |
| `0x5002` | 14 | `0x10014a93c` | `__stopNowPlayingUpdatesHandler` | — | 停止订阅 |
| `0x5003` | 14 | `0x10014aa20` | `__setNowPlayingInfoHandler` | 0–2（比较链） | 设置播放信息 |
| `0x5200` | 17 | `0x10017527c` | `_iap2_navigation_startRouteGuidanceHandler` | 5（0 起 6 个） | 开始导航（参数0为组件项，1–5为空值标记） |
| `0x5203` | 17 | `0x10017593c` | `_iap2_navigation_stopRouteGuidanceHandler` | — | 停止导航 |
| `0x0D01` | 17 | `0x100175c70` | `_iap2_navigation_roadObjectDetectionUpdateHandler` | — | 目标检测更新 |
| `0x5400` | 3 | `0x10014bab4` | `_iap2_assistiveTouch_startAssistiveTouchHandler` | 0 | 开始 AssistiveTouch |
| `0x5401` | 3 | `0x10014bbdc` | `_iap2_assistiveTouch_stopAssistiveTouchHandler` | 0 | 停止 AssistiveTouch |
| `0x5402` | 3 | `0x10014bcf4` | `_iap2_assistiveTouch_startAssistiveTouchUpdateHandler` | 0 | 开始状态更新 |
| `0x5404` | 3 | `0x10014be18` | `_iap2_assistiveTouch_stopAssistiveTouchUpdateHandler` | 0 | 停止状态更新 |
| `0x5600` | 20 | `0x1001670ac` | `_iap2_vehicle_startStatusUpdatesHandler` | — | 车况订阅（本阶段只作生命周期相邻参考） |

`A01.2`：`0x6800` 与 `0x6805` 的参数 ID 上界由跳表给出（`0x100018774` / `0x100018788`），
`0x6802`/`0x6803`/`0x5000`/`0x5003` 用比较链而非跳表，上界由比较链的分支数给出。

## 1.4 出站消息（设备 → 车机）

| msg_id | 发送点 | 符号 | 证据（指令） |
|---|---|---|---|
| `0x6801` | `0x1001316f4` | `_iap2_hid_sendOutReport` | `iAP2MsgInit(…,0x6801)`（`0x1001316f4` 函数体内） |
| `0x6804` | `0x100131864` | `_iap2_hid_sendGetReport` | `iAP2MsgInit(…,0x6804)` |
| `0x6807` | `0x100131a14` | `_iap2_hid_sendComponentUpdate` | `iAP2MsgInit(…,0x6807)` |
| `0x5001` | `0x1001465c4` | `_iap2_nowPlaying_playbackAttributesUpdateHandler` | `_iAP2MsgInit(msg,0x5001,…)`（Ghidra 第 284 行，需回汇编核对） |
| `0x5201` | `0x1000027f4` | `_iap2_navigation_routeGuidanceUpdateHandler` | `OUTLINED_FUNCTION_17(…,0x5201,…)` |
| `0x5202` | `0x1001777c0` | `_iap2_navigation_routeGuidanceManeuverUpdateHandler` | `OUTLINED_FUNCTION_17(…,0x5202,…)` |
| `0x5204` | `0x100177d80` | `_iap2_navigation_laneGuidanceInfoUpdateHandler` | `OUTLINED_FUNCTION_17(…,0x5204,…)` |
| `0x0D02` | `0x1001788f4` | `_iap2_navigation_stopRoadObjectDetectionHandler` | `OUTLINED_FUNCTION_17(…,0xD02,…)` |
| `0x5403` | `0x10014bf24` | `_iap2_assistiveTouch_notifyStatusUpdateHandler` | `_iAP2MsgInit(msg,0x5403,…)` |
| `0xA100` | `0x1001670ac` | `_iap2_vehicle_startStatusUpdatesHandler` | `_iAP2MsgInit(msg,0xA100,…)` |

`A01.3`：出站 ID 的判定只依赖"构造消息时的立即数"，不依赖编号区间语义。
`0x0D02` 与 `0x0D01` 相差 1、`0x5403` 与 `0x5400/0x5402` 相邻，这些**只是观察**，不构成协议规则。

## 1.5 还没有被证到的部分

| 未决 | 影响 | 登记 |
|---|---|---|
| NowPlaying 另外四条平台更新路径（`0x10014569c`/`0x100145e70`/`0x1001474b4`/`0x10014778c`）是否都复用 `0x5001` | 客户端可能漏一条更新消息 | `OPEN-NP-2` |
| 导航 `0x5200` 的options业务含义/profile要求 | HUD 字段填不对 | `OPEN-NAV-2` |
| `0x0D01` 的参数结构（无跳表，需逐条读比较链） | 目标检测无法实现 | `OPEN-NAV-3` |
| 触摸是否只走 `0x54xx`，还是另有 HID 触摸报告 | 触摸实现路径可能错 | `OPEN-INP-3` |
| 休眠/恢复是否有独立 iAP2 消息（本阶段只看到链路层动作） | 生命周期实现可能缺一步 | `OPEN-LIFE-2` |

## 1.6 与第三阶段的接口

- 门控函数：`0x100051054`（入站）/ `0x100005138`（出站），语义见 `sess/analysis/07` 与 `sess/spec/05`；
- 消息头与参数头：`sess/R-3.x`（6 字节头、4 字节参数头），本阶段不重复定义；
- 分发路径：`sessionRouter` → 特性处理器表 → 处理器，见 `sess/R-2.x`；
- 本阶段新增的唯一分发层级是"处理器内部的参数 ID 分派"，见 `analysis/02`。
