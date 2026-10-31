# analysis/08 — 资源清理与幂等

清理在本阶段有三个可证的机制：**用户计数**（每个业务域各一套）、**detach 回调**、
**endpoint 销毁**。三者的顺序与幂等性是客户端最容易写错的地方。

## 8.1 用户计数（user count）

每个业务域都有自己的"用户计数 +1/−1"：

| 业务域 | +1 | −1 |
|---|---|---|
| HID | `_platform_hid_incrementUserCount` `0x1000b3068` | `_platform_hid_decrementUserCount` `0x1000b3110` |
| NowPlaying | `_platform_nowPlaying_incrementUserCount` `0x10008fc70` | `_platform_nowPlaying_decrementUserCount` `0x10008fcb0` |
| 导航 | `_platform_navigation_incrementUserCount` `0x1000dd9e8` | `_platform_navigation_decrementUserCount` `0x1000dda90` |
| AssistiveTouch | `_platform_assistiveTouch_incrementUserCount` `0x100036fc0` | `_platform_assistiveTouch_decrementUserCount` `0x100037068` |

`A08.1`：计数成对出现且分布在四个域，说明"谁申请谁释放"；
`0x5400`/`0x5401` 这类 Start/Stop 消息内部会动计数（见 `analysis/03`/`04` 的处理器调用序列），
**重复 Stop 是否安全取决于计数是否下溢**；四域的计数都最终落到 `ACCFeatureServer`（ObjC），
HID 的 increment 在计数变 1 时启动插件（`0x1000b3068`），decrement 无返回值（`0x1000b3110`），
下溢分支在 ObjC 实现里，本构建未能读到（`OPEN-LIFE-4` 已缩小）。

## 8.2 HID 组件释放

`__CFDictionaryApplierFunction_releaseHIDComponents`（`0x100131c14`）是字典遍历释放函数，
配合 `_platform_hid_unregister_all_descriptors`（`0x1000b2d1c`）与
`_platform_hid_unregister_descriptor`（`0x1000b2cc8`）完成组件回收。

`A08.2`：`0x6800` 的 block 里同时存在"注册"（`0x100043b48` → `_platform_hid_register_descriptor`）
与"注销"（`0x100043a98` → `_platform_hid_unregister_descriptor`）两条路径，
说明注册失败时会走注销做回滚——这是**幂等清理的现成范例**。

## 8.3 断开时的逐域回调

| 域 | detach 回调 | 地址 |
|---|---|---|
| AssistiveTouch | `_platform_assistiveTouch_accessoryDetached` | `0x100036c08` |
| 导航 | `_platform_navigation_accessoryDetached` | `0x1000dc6a0` |
| 媒体库 | `_platform_mediaLibrary_accessoryDetached` | `0x1000a66e0` |
| 数字音频 | `_platform_digitalAudio_accessoryDetached` | `0x100057274` |
| 语音 | `_platform_voiceOver_accessoryDetached` | `0x1000b8d68` |
| 蓝牙配对 | `_platform_blePairing_accessoryDetached` | `0x1000da7dc` |

`A08.3`：已观察到多域断开回调，不证明不存在统一协调入口。
本地安全建议是先阻止新工作并取消/排空旧回调，再释放其资源；不强制复制 iOS 对象结构。

## 8.4 endpoint 销毁（`0x100030d4c`）

| 地址 | 调用 | 作用 |
|---|---|---|
| `0x100030d88` | `_iap2_power_unregisterForSleepNotification` | 先注销休眠通知 |
| `0x100030db0` | `_acc_platform_packetLogging_logEventForEndpoint` | 记录事件 |
| `0x100030e0c` | `_acc_protocolEndpoint_performSync` | 同步一次 |
| `0x100030e6c`/`0x100030e7c`/`0x100030e84` | 两个惰性绑定桩 `0x1001a2260`×2 + `0x1001a2180` | `braa` 经 GOT 的导入调用（`objc_release` 一类），目标导入未解析 |
| `0x100030f9c` | `_iAP2LinkRunLoopShuttingDown` | 停 run loop |
| `0x100030fa4` | `_iap2_sessionControl_cleanup` | 会话控制清理 |
| `0x100030fac` | `_iap2_sessionFileTransfer_cleanup` | 文件传输清理 |
| `0x100030fb4` | `_iap2_sessionLog_cleanup` | 日志清理 |

`A08.4`：销毁顺序可证到调用序列：注销休眠通知 → 记日志 → 同步 → 停 run loop →
会话控制清理 → 文件传输清理 → 日志清理；中间三个 `0x1001a2xxx` 是惰性绑定桩，
不是"第三个未命名业务函数"（上一轮的说法已更正，见 `A11.6`）。

## 8.5 幂等清单（给实现用的判断依据，不是规范）

| 场景 | 证据 | 能否断言幂等 |
|---|---|---|
| 重复 `0x6803`（StopHID） | 按ID查字典，命中清+18/+1a而不删项；局部返回0（analysis/13） | 仅清零动作重复不改变结果；不等于完整平台清理幂等已证 |
| 重复 `0x5002`（停订阅） | 处理器移除订阅者（`0x10014a93c`） | 不能：计数是否下溢未证（`OPEN-LIFE-4`） |
| 重复 `0x5203`（停导航） | 处理器调 `stopRouteGuidance`（`0x10017593c`） | 不能：同上 |
| 断开后再 detach | `0x1000311f4` 有状态判断 | 部分：状态机是否吸收重复事件未证 |

## 8.6 未决

| 编号 | 内容 | 关闭条件 |
|---|---|---|
| `OPEN-LIFE-4` | 各域 user count 下溢行为（重复 Stop）——已缩小到 `ACCFeatureServer` 的 ObjC 实现 | 需要 ObjC 方法体或运行时观察 |
| `OPEN-LIFE-5` | ~~尾部三个未命名调用~~ **已关闭**：顺序为停 run loop → 三个会话清理；中间是惰性绑定桩 | `A11.6` |
