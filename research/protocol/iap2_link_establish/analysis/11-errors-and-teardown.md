# analysis/11 — 异常、拆除与清理

对应任务书第 5 节第 11 项。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2LinkDetached` | `0x100034bbc` | 传输 detach：投 FSM 事件 `0x0E` 后复原参数 |
| `iAP2LinkAttached` | `0x100034a7c` | 传输 attach：复原参数后投事件 1 |
| `iAP2LinkActionDetach` | `0x100031c7c` | 链路动作：置事件并触发上层 detach |
| `iAP2LinkDelete` | `0x1000347b0` | 销毁链路对象 |
| `iAP2LinkHandleSuspend` | `0x100034db4` | 挂起 |
| `iAP2LinkHandleResume` | `0x100034e68` | 恢复 |
| `iAP2LinkDeviceActionSendRST` | `0x10002fb54` | 发 RST（复位后） |
| `iAP2LinkDeviceActionHandleMaxRetries` | `0x100030054` | 重试上限 |
| `iAP2LinkResetSeqAck` | `0x1000346c8` | 序号/确认复位 |
| `iAP2LinkResetSend` | `0x100034464` | 发送侧复位 |

## 11.1 detach 的固定顺序

`A11.1`（已确认）`iAP2LinkDetached(link)` **先**向 FSM 投事件 `0x0E`，**再**复原 SYN 缺省参数：

```
0x100034bd4: ldr  x0, [x0, #8]        ; link->fsm
0x100034bd8: mov  w1, #0xe
0x100034bdc: bl   0x10000639c         ; FSM 事件 0x0E
0x100034be0: add  x8, x19, #0x19a
0x100034bec: str  w10, [x9]           ; [0x19e]=0xFFFF, [0x1a0]=0x03E8
0x100034bf4: strh w9, [x19, #0x1a2]   ; [0x1a2]=10
0x100034c00: str  d0, [x8]            ; 0x1001b3348 的 4 字节
0x100034c08: str  w8, [x19, #0x1a4]   ; [0x1a4]=00, [0x1a5]=01, [0x1a6]=FF, [0x1a7]=FF
```

`A11.2`（已确认）`iAP2LinkAttached(link)` 的顺序相反：**先**复原参数，**再**投事件 1（`analysis/02` A02.4）。两者都以"参数复原"为边界，说明 attach/detach 是可重复的（幂等）。

`A11.3`（已确认）事件 `0x0E` 在所有活动状态（Detect/Idle/Pending/Connected/Suspend/Failed）都迁移到 Detached（`analysis/06` 表）。因此 detach 不区分当前状态。

## 11.2 拆除时的复位动作

`A11.4`（已确认）`iAP2LinkResetSend` 与 `iAP2LinkResetSeqAck` 的分工：

| 函数 | 复位内容 | 证据 |
|---|---|---|
| `ResetSend` | 5 个发送链表 + SYN 参数复原 + 调 `ResetSeqAck(link,1,0)` | `0x100034494`（5 次循环）、`0x1000344b8`–`0x100034510` |
| `ResetSeqAck(link,w1,w2)` | 序号基值 `[0xbe]=0`、清 `[0xd4]` bit2/bit3、重建时间同步；`w2!=0` 时额外清 `[0x1d0]/[0x1d8]` 并恢复校验类型；`w1 bit0 == 0` 时清发送包链表 `[0x120]` | `0x1000346ec`–`0x100034748` |

`ResetSeqAck` 的两个布尔参数在固件中的实际取值组合：

| 调用点 | w1 | w2 | 场景 |
|---|---|---|---|
| `iAP2LinkResetSend` | 1 | 0 | 常规发送侧复位 |
| `SendResetSYNACK` | 1 | 0 | 收到 SYN 后 |
| `SendDetect` | 0 | 1 | Detect 前（清发送链表 + 恢复校验类型） |
| `SendRST` | 0 | 0 | 发 RST 前（保留时间同步与校验类型） |

## 11.3 失败与上限

`A11.5`（已确认）FSM 中只有事件 `0x14` 会进入 Failed（`analysis/06`：Idle/Pending/Connected/Suspend 均有 `0x14 → 7`），且 Failed 只有四条出边（`0x0c`/`0x0d` 自环、`0x0e` → Detached、`0x17` → Idle）。

`A11.6`（已确认）`iAP2LinkDeviceActionHandleMaxRetries`（`0x100030054`）存在，其内部判定与"事件 `0x14`"的对应关系未逐条核对 → `OPEN-ERR-1`。

`A11.7`（已确认）`iAP2LinkDelete`（`0x1000347b0`）存在，但**析构顺序**（先停定时器、还是先清链表）未通读 → `OPEN-ERR-2`。同一文件还导出 `iAP2LinkHandleSuspend`（`0x100034db4`）/`iAP2LinkHandleResume`（`0x100034e68`），二者都由运行循环的 bit2/bit3 触发（`analysis/02` A02.3）。

## 11.4 异常帧的处置（已确认的部分）

`A11.8`（已确认）收到 RST 时：

- FSM 事件 `0x0F` 在 Detect 状态触发 `SendRST` 并回 Idle；在 Connected 状态保持 Connected（`analysis/06` 表）；
- `SendRST` 内部先 `ResetSeqAck(link,0,0)`、再复原 SYN、再比较 `link[0x1d0]` 与 `11`（`0x10002fc60`）→ 该比较的语义未确定（`OPEN-IDPS-3`）。

`A11.9`（已确认）收到非法事件（事件号越界或当前状态无该事件）时**不改变状态、不产生副作用**（`analysis/06` A06.6）。

## 11.5 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-ERR-1` | `HandleMaxRetries` 的判定与事件 `0x14` 的对应 |
| `OPEN-ERR-2` | `iAP2LinkDelete` 的析构顺序与定时器/链表清理 |
| `OPEN-ERR-3` | Suspend/Resume 对已排队数据与定时器的处理 |
| `OPEN-ERR-4` | 链路层是否向上层报告错误码（未见独立错误回调） |
