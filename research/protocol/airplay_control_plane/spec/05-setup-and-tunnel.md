# 05 · SETUP 与隧道交接

## 5.1 SETUP

- R-5.1 `SETUP` 的 body **必须**是 binary plist，并带 `X-Apple-ProtocolVersion`（`A06.1`、`A06.2`）。
- R-5.2 `streams` 元素使用字典键 `type`、`streamID` 等；不能仅凭键名存在就断言每个阶段全部必填。`type` 为整数，已核 24A446 分派对
  96、100、101、102、103、106、107、110、111、120、130 有专门路径；112 在该链进入错误分支。这不是完整 SDK 枚举或车机接受能力表（`A12.2`、`A12.4`）。
- R-5.3 每个流**应**在 SETUP 响应里取得端口参数：控制端口键 `controlPort`，数据端口键 `dataPort`（`A12.2`）。

## 5.2 流键名（已解出）

- R-5.4 对 **24A446**，已解出的流键名取自下表（`A12.2`）；拼写与大小写均区分。其它构建或车机返回的 plist 仍必须按实际键集合解析，不能把本表当跨版本闭集。

  | 键 | 含义 | 键 | 含义 |
  |---|---|---|---|
  | `type` | 流类型 | `streamID` | 流标识 |
  | `streamConnectionID` | 连接标识 | `streamConnections` | 连接子字典数组 |
  | `controlPort` | 控制端口 | `dataPort` | 数据端口 |
  | `seed` | 流加密种子 | `shk` | 共享加密密钥 |
  | `sr` | 采样率 | `spf` | 每包帧数 |
  | `audioFormat` | 音频格式 | `ct` | 压缩类型 |
  | `audioLatencyMs` | 延迟 | `isMedia` | 是否媒体流 |
  | `input` | 是否要输入 | `usingScreen` | 屏幕流标记 |
  | `viewArea` | 视区 | `supportsDynamicStreamID` | 动态 ID 支持 |

- R-5.5 对 **24A446**，连接子字典观察到的键为 `streamConnectionKeyPort`、`streamConnectionKeyIPAddress`、
  `streamConnectionKeyTransportProtocol`、`streamConnectionKeyInterfaceType`、
  `streamConnectionKeyUseStreamEncryptionKey`、`streamConnectionKeyEncryptionSeed`、
  `streamConnectionKeyMACAddress`、`streamConnectionKeyNetworkInfo`（`A12.3`）。
- R-5.6 `type` 各取值对应的具体流语义（尤其 130 是否为 iAP2 隧道）仍为 `OPEN-AP-41`；实现**不得**仅凭数值推断。

## 5.3 交接

- R-5.7 “交接”在本项目中定义为：控制面完成 `SETUP` 后，把该流的数据面交给上层读取；`FLUSH`/`TEARDOWN` 是否仍由控制面负责，当前只作客户端生命周期策略，未由 `A07.4` 闭合。
- R-5.8 客户端应在 `RECORD` 前等待 `SETUP` 成功响应作为保守策略；该顺序只是 `INFERRED`，并由 `OPEN-AP-30` 保留，不宣称为所有对端的硬性要求（`A07.3`）。

## 5.4 顺序

候选推进顺序（推断，不是已证明的全序）：`/info` → `/pair-setup`（需要长期配对时）→ `/pair-verify` → 加密 → `/fp-setup` → `SETUP` → `RECORD`；事件通道时机另见 `OPEN-AP-29`，加密边界见 `OPEN-AP-23`。
失败重试点见 `OPEN-AP-28`。
