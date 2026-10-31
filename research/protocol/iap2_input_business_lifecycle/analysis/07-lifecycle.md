# analysis/07 — 生命周期：挂起 / 恢复 / 休眠 / 断开

本阶段看到的"生命周期"分成三层，**不要混在一起实现**：

| 层 | 触发者 | 载体 | 函数 |
|---|---|---|---|
| 链路层挂起/恢复 | 设备侧主动 | **SUS / ACK 控制包**（不是 16 位消息） | `_iAP2LinkDeviceActionSendSuspend` `0x10003021c`、`_iAP2LinkDeviceActionSendResume` `0x1000302a0` |
| 系统休眠/唤醒 | iOS 电源通知 | 平台回调 | `_iap2_power_registerForSleepNotification` `0x1000c2c58`、`_iap2_power_sleepUpdateHandler` `0x1000c2d7c` |
| 断开/销毁 | 链路断开或进程退出 | endpoint 状态机 | `_iap2_endpoint_linkStateChanged` `0x1000311f4`、`_iap2_endpoint_destroy` `0x100030d4c` |

## 7.1 设备侧主动挂起（`0x10003021c`）

逐指令事实（`source/asm/accessoryd/f_10003021c.s`）：

| 地址 | 指令 | 含义 |
|---|---|---|
| `0x100030234` | `mov w8,#0x1d` / `strb w8,[x1]` | 把 `0x1D` 写进**调用方给的出参**（不是包载荷） |
| `0x100030240` | `add x2,x19,#0x168` | `link+0x168` 是**事件通知**的参数区（`_iAP2LinkEventNotify` 的第 3 实参），不是 SUS 包载荷 |
| `0x100030248` | `mov w1,#7` | 事件号 7 |
| `0x10003024c` | `bl _iAP2LinkEventNotify` | 通知链路事件 |
| `0x100030258` | `bl _iAP2PacketCreateSUSPacket` | **构造 SUS 包**（类型 `0x08`、无载荷） |
| `0x100030274` | `bl _iAP2LinkSendPacketWaitSend` | 发送并等待 |

`A07.1`：挂起**不是** iAP2 消息层的 16 位消息，而是链路层的 SUS 包（类型 `0x08`）；
`_iAP2PacketCreateSUSPacket`（`0x100103210`）展开为
`_iAP2PacketCreate(link, 8, seq, 0, payload=0, len=0, 0, 1)`——**没有载荷**。
因此它不受两张准入名单约束（那两张名单只管 16 位消息 ID）。

## 7.2 设备侧主动恢复（`0x1000302a0`）

| 地址 | 指令 | 含义 |
|---|---|---|
| `0x1000302b8` | `mov w8,#0x1d` / `strb` | 同一个 `0x1D` 写出参（不是包载荷） |
| `0x1000302d0` | `bl _iAP2LinkEventNotify`（事件号 **8**） | 与挂起的 7 不同 |
| `0x1000302ec` | `bl _iAP2PacketCreateACKPacket` | **构造 ACK 包**（类型 `0x40`，不是 RES 包） |
| 后续 | `_iAP2LinkSendPacketWaitSend` | 发送 |

`A07.2`（部分确认）：恢复路径构造 **ACK** 包，`_iAP2PacketCreateACKPacket`（`0x100006f8c`）
展开为 `_iAP2PacketCreate(link, 0x40, link[0xBE], link[0xBC], payload=0, len=0, 0, 1)`：
`hdr[5]=link[0xBE]`、`hdr[6]=link[0xBC]`、`hdr[7]=0`、无载荷。它为什么用 ACK 而不是专门的 RES 包、
`link[0xBC]` 的完整维护链仍未核（构造器将它写入确认号，见 A12.1）（`OPEN-LIFE-2`）。

## 7.3 收到挂起/恢复（对端发起）

- `_iAP2LinkHandleSuspend` `0x100034db4`：前段为日志门；检查 link、FSM 对象及 link+0xb8==1 后，把 FSM 事件 `0x1b` 投进去
  （`_iAP2FSMHandleEvent`，`0x100034e40`）；
- `_iAP2LinkHandleResume` `0x100034e68`：结构相同，事件号 `0x1c`（`0x100034ef0`）；
- run loop 侧：`_iAP2LinkRunLoopHandleSuspend` `0x1000cb1f0`、`_iAP2LinkRunLoopHandleResume` `0x1000cb23c`。

`A07.3`：处理函数是"状态判断 + FSM 事件"，不是"直接改标志位"；
不能据此强制独立实现复制内部 FSM；业务门和定时器策略见 A12.3。

## 7.4 系统休眠/唤醒

| 函数 | 地址 | 作用 |
|---|---|---|
| `_iap2_power_registerForSleepNotification` | `0x1000c2c58` | 注册（endpoint 创建时） |
| `_iap2_power_unregisterForSleepNotification` | `0x1000c2d68` | 注销（endpoint 销毁时，`0x100030d88` 调用） |
| `_iap2_power_sleepUpdateHandler` | `0x1000c2d7c` | 休眠回调 |
| `_platform_power_sendSleepUpdate` | `0x100027c94` | 平台侧广播"睡了" |
| `_platform_power_sendWakeUpdate` | `0x100027ddc` | 平台侧广播"醒了" |
| `_platform_power_registerForSleepWakeUpdate` | `0x100028150` | 平台侧注册 |
| `_platform_power_unregisterForSleepWakeUpdate` | `0x100028278` | 平台侧注销 |

`A07.4`：endpoint 创建时注册、销毁时注销，注册/注销成对出现在 `0x100030d88`（销毁路径）
与创建路径，说明**休眠通知是按 endpoint 维度管理的**，不是全局单例。

## 7.5 断开

| 函数 | 地址 | 作用 |
|---|---|---|
| `_iap2_endpoint_linkStateChanged` | `0x1000311f4` | 链路状态变化入口 |
| `_iAP2LinkDetached` | `0x100034bbc` | 链路 detach |
| `_iAP2LinkActionDetach` | `0x100031c7c` | detach 动作 |
| `_iAP2LinkRunLoopDetached` | `0x1000cb1a4` | run loop 侧 detach |
| `_platform_btConnectionStatus_accessoryDetached` | `0x1000206e0` | 蓝牙连接状态：配件断开 |

`A07.5`：detach 后每个特性各有自己的断开回调（`platform_*_accessoryDetached`），
说明固件有逐域通知；独立实现需清理所有资源，但允许统一协调入口（A12.3）。

## 7.6 与抓包的关系

23G90 抓包里有断开（`0x5703` 之后链路关闭），但**没有**挂起/恢复帧，
因此 7.1/7.2 的 SUS/ACK 包**没有线上样本**（`OPEN-LIFE-3` 已按固件关闭：
包类型与载荷已确定，帧头规则沿用 `link/`；仍缺的是"这一帧在真车链路上出现"的观察）。
