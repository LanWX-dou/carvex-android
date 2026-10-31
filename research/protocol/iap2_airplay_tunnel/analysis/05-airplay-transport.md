# analysis/05 — AirPlay 作为 iAP2 传输

## 5.1 位置

在 accessoryd 里，"AirPlay" 是**传输名**，不是协议层。链路对象、会话表、消息处理器与 BT/USB 完全相同；差异只在"字节从哪个设备/插件进来"。

抓包证据（23G90，`A05.1`）：

| 字段 | 值 |
|---|---|
| 连接 UUID | `D927805C-1FAC-47C6-B156-FF3818CEBC3D` |
| 传输列 | `AirPlay` |
| 首个 iAP2 消息会话号 | `session=0x03` |
| SYN 参数尾部 | `… 0f 00 03 00 02`（与 BT 连接的 `… 0f 00 02 00 02` 只差会话号）|
| 帧格式 | `40 40 len msgID params`，与 BT 连接逐字节同构 |

> 结论：**AirPlay 隧道对 iAP2 是透明的字节管道**。隧道自己的帧（如果存在）在 accessoryd 之外，`verify.py` 不能校验它 → `OPEN-TUN-5`。

## 5.2 会话号仍是 3

- 抓包里 SYN 的参数块末尾是 `03 00 02`，之后所有业务消息 `session=0x03`；
- 这与控制会话阶段的结论一致：会话号由 SYN 协商结果决定，不是"业务消息首条才声明"（`control/R-2.x`、`control/A02.x`）；
- 对设备侧实现的含义：**在 AirPlay 传输上重放 SYN/SYNACK 时必须复用协商出的会话号**，不能另选。

## 5.3 证明的与没证明的

| 命题 | 状态 | 依据 |
|---|---|---|
| AirPlay 链路上的 iAP2 帧与 BT 链路同格式 | 已证（运行期）| `A05.1` |
| AirPlay 链路上会话号由 SYN 决定 | 已证（运行期）| `A05.2` |
| AirPlay 链路上有 Location 业务（`0xFFFA/FFFB/FFFC`）| 已证（运行期）| `A05.3` |
| AirPlay 隧道有自己的分片/序号头 | **未证** | `OPEN-TUN-5` |
| AirPlay 上跑过 `0x55xx` 中继 | 未观测 | `OPEN-TUN-4` |
| AirPlay 链路的 MTU / 最大单帧 | **未证** | `OPEN-TUN-5` |

抓包里最大的 iAP2 消息是 `0xAA01` 的 617 字节（链路包 627 字节），只能说明"至少支持到 627"，不能说明上限。

## 5.4 与"AirPlay over iAP2"的关系

原任务书假设的方向（AirPlay 媒体字节装进 iAP2）在本阶段**没有任何指令级或运行期证据**：

- accessoryd 里没有"把 RTSP/RTP 字节装进 iAP2 消息"的函数；
- 抓包里 AirPlay 链路上的 iAP2 消息全是识别/认证/Location，没有媒体载荷；
- 唯一"iAP2 装 iAP2"的机制是 `0x55xx` 中继信封，它装的是**另一条 iAP2 消息**，不是 AirPlay 媒体。

因此本阶段把方向修正记录在 `TASK.md` §0.1 与 `spec/00` §0.3，并在 `spec/05` 给出"若对端确实是 AirPlay-over-iAP2 形态，需要补哪种抓包才能判定"的实验。

## 5.5 未确认点

| 编号 | 内容 |
|---|---|
| `OPEN-TUN-5` | AirPlay 隧道帧格式、MTU、握手（在 accessoryd 之外）|
| `OPEN-TUN-4` | 中继是否只在 AirPlay 上启用 |
| `OPEN-TUN-12` | 没有 24A446 的 AirPlay 运行期样本 |
