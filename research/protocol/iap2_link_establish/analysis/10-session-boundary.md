# analysis/10 — 会话启动边界

对应任务书第 5 节第 10 项：链路建立到"会话可用"的分界，以及会话与链路的分层。

## 10.1 分层证据

`A10.1`（已确认）iAP2 在这一层是 **link → session** 两段式：链路负责帧，会话负责消息路由。证据是接收路径上存在"按键/服务号查会话"的映射：

```
; iAP2LinkDataReadyCB(link, buf, len, ?, service)
0x10019bfdc: mov  x1, x4
0x10019bfe0: bl   0x100032828        ; iAP2LinkGetSessionInfo(link, service)
0x10019bfe4: cbz  x0, 0x10019c108    ; 查不到会话 → 丢弃
0x10019c064: and  w3, w20, #0xffff
0x10019c068: mov  x0, x21            ; transport
0x10019c06c: mov  x1, x22            ; 会话对象
0x10019c070: mov  x2, x19            ; 数据
0x10019c074: bl   0x10006b878        ; 投递
```

`A10.2`（已确认）存在按"服务号"取会话的公开函数 `iAP2LinkGetSessionForService`（`0x100005740`）与 `iAP2LinkGetSessionInfo`（`0x100032828`），说明会话表由链路对象持有（`link+0x120`/`+0x128` 两个链表的语义待定，见 `OPEN-SES-1`）。

## 10.2 `CarPlayStartSession` 是唯一的会话启动消息

`A10.3`（已确认）`kiAP2MessageHandlerEntries_CarPlayStartSession`（`0x10021e650`）只有 1 项：

| msg_id | handler |
|---|---|
| `0x4301` | `0x10016d3ac` |

"只有一条"说明会话启动是**单个消息**触发，不是请求/响应族。这与 `ExternalAccessory`（`0xEA03`，同样单条）结构相同。

`A10.4`（部分确认 / `OPEN-SES-2`）`0x4301` 的静态嵌套 schema 已在 control docset `spec/14` 由 `0x10016d3ac` 的跳表/getter 闭合；本 docset 仍不证明运行时平台必填性、错误响应、谁在所有 profile 先发，以及完整 CarPlay 下游结果。

## 10.3 会话控制的符号证据

`A10.5`（推断，符号名）会话层有独立的控制函数族：

| 符号 | 地址 |
|---|---|
| `iap2_sessionControl_sendOutgoingMessage` | `0x100005130` |
| `iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK` | `0x10002a9bc` |
| `iap2_sessionControl_cleanup`（block invoke） | `0x10002a934` / `0x10002a980` |
| `iap2_sessionLog_writeSessionSyncToFile` | `0x10004b1c0` |

其中 `...AndCallbackOnACK` 表明会话层可以要求"消息被 ACK 后回调"，这依赖链路层的 ACK 机制（`analysis/05`）。

## 10.4 建立完成的判定

`A10.6`（已确认）链路层"可用"的标志是 FSM 进入 `Connected`（状态 5）：

- 进入条件：`Pending` 状态收到事件 `0x15`（`analysis/06` 表）；
- 进入时会话启动消息（`0x4301`）才有意义 —— 因为链路层在这之前会丢弃找不到会话的数据（A10.1 的 `cbz x0`）。

`A10.7`（未确认 / `OPEN-SES-3`）"会话已启动"是否有独立状态位（例如 `link[0xd4]` 的某一位）未定位；FSM 的 `Connected` 与会话可用之间是否一一对应也未取证。

## 10.5 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-SES-1` | `link+0x120`/`+0x128` 两个链表的角色（收发包 vs 会话） |
| `OPEN-SES-2` | `0x4301` 运行时平台必填性、错误/重试、下游 CarPlay 结果与所有 profile 的发起方 |
| `OPEN-SES-3` | "会话已启动"的状态位与 `Connected` 的对应关系 |
| `OPEN-SES-4` | 多会话并发时的路由键（服务号 vs 会话 ID） |
