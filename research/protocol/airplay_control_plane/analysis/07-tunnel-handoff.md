# 07 · 会话阶段与交接

> 覆盖要求 #8（从控制面到流建立的推进顺序）。本章只给"有哪些阶段"和"边界在哪"，
> 阶段之间的进入条件多数仍 `OPEN`。

## 7.1 已定位的阶段函数

| 阶段 | 函数 | 地址 | 已知 |
|---|---|---|---|
| 启动 | `apsession_EnsureStarted` | `0x251a57ffc` | 协调者入口；内部按阶段推进 |
| 阶段 1 | `apsession_PerformStage1StartTransaction` | `0x251a587a0` | 先于阶段 2 |
| 阶段 2 | `apsession_PerformStage2StartTransaction` | `0x251a5885c` | 含 `SETUP` |
| 事件流 | `apsession_ensureEventStreamCreated` | `0x251a5dec0` | 事件通道按需创建 |
| 事件回复 | `carEndpoint_handleEventCreatingReply` | `0x2519b20a8` | 处理事件流创建应答 |
| 流创建 | `apsession_CreateTransportStreamWithID` | `0x2519c8f04` | 按 ID 建流 |
| 配对（peer 管理） | `APSenderSessionAirPlayPerformPairingPeersListManagement` | `0x251a5507c` | `/pair-add`、`/pair-remove` 一侧 |

`A07.1`：阶段 1 与阶段 2 是**两个独立事务函数**（各自有 Start/结束配对），不是同一个循环里的两次请求；
`A07.2`：事件流是独立通道（`Events-Salt` 密钥，见 04 章），与控制通道分开加密。

## 7.2 顺序（推断）

综合方法表与阶段函数，客户端最小推进序列为：

```text
TCP 连接
 -> GET /info
 -> POST /pair-setup       （首次）
 -> POST /pair-verify      （每次）
 -> 控制通道切换到 AEAD
 -> POST /fp-setup         （FairPlay）
 -> SETUP                  （建流）
 -> RECORD                 （启动）
 -> 事件通道（可选）
```

`A07.3`（`INFERRED`）：上表顺序由"方法依赖关系"推出——`SETUP` 需要配对后的会话密钥，
`RECORD` 需要已 `SETUP` 的流。**没有**一条指令直接断言这个全序；`OPEN-AP-28`。

## 7.3 交接点（到 `type=130`）

"交接"指控制面把某条流交给上层隧道（`type=130`）。本轮能确认的只有：

- 存在按流 ID 的创建入口（`APTransportStreamIDMake` `0x24fdfad5c`、`MakeWithPort` `0x24fdfad94`）；
- 存在流类别访问器（`APTransportStreamIDGetStreamCategory` `0x24fda863c`）；
- 事件通道有独立的创建/应答路径。

**不能**确认：`type=130` 的值、它在 `streams` 数组里的位置、交接后由谁读这条流。
`A07.4`：在拿到 `apsession_setupStreamCreatingResponseInternal`（`0x2519bbf24`）的逐指令分析前，
任何"130 = iAP2 隧道"的写法都只能是外部知识，不得进入规范（`OPEN-AP-25`）。

## 7.4 OPEN

| id | 问题 |
|---|---|
| `OPEN-AP-28` | 阶段全序与失败重试点 |
| `OPEN-AP-29` | 事件通道何时必须建立 |
| `OPEN-AP-30` | `RECORD` 之前是否必须收到 `SETUP` 的 200 |
