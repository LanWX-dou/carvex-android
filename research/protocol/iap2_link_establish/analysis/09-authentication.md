# analysis/09 — 认证阶段（载荷级）

对应任务书第 5 节第 9 项。本轮新增 11 个认证相关函数（含 `mfi4Auth_*` 的隧道封装/解包），把第 9 项从"符号级"推进到"**承载方式 + 每条消息的参数级**"，密码学细节仍不在范围内。

## 9.1 两组认证消息

`A09.1`（已确认）`DeviceAuthentication`（`0x100218eb0`，4 项）：

| msg_id | handler | 符号 |
|---|---|---|
| `0xAA10` | `0x100123108` | `iap2_deviceAuthentication_RequestDeviceCertificate` |
| `0xAA12` | `0x100123204` | `iap2_deviceAuthentication_RequestDeviceChallengeResponse` |
| `0xAA14` | `0x10012356c` | `iap2_deviceAuthentication_DeviceAuthenticationFailed` |
| `0xAA15` | `0x100123690` | `iap2_deviceAuthentication_DeviceAuthenticationSucceeded` |

`A09.2`（已确认）`AccAuthentication`（`0x1002205d8`，3 项）：

| msg_id | handler | 符号 |
|---|---|---|
| `0xAA01` | `0x1001850bc` | `iap2_accAuthentication_certificate` |
| `0xAA03` | `0x100185d6c` | `iap2_accAuthentication_challengeResponse` |
| `0xAA06` | `0x1001860d4` | `iap2_accAuthentication_certSerial` |

**符号名直接给出消息角色**，这是本轮最强的语义证据：`0xAA01` = 送证书、`0xAA03` = 挑战响应、`0xAA06` = 证书序列号、`0xAA12` = 请求设备挑战响应、`0xAA14/0xAA15` = 失败/成功通知。

## 9.2 中继路径的隧道封装（不可套用于普通认证消息）

`A09.3`（已确认）`mfi4Auth_util_packIntoTunnelDataiAP2Msg`（`0x100022264`）：

```
malloc(0x48)  → msg 对象
malloc(0xffff) → 0xFFFF 字节缓冲
msg_id = (flag != 0) ? 0x5501 : 0x5500
iAP2MsgInit(msg, msg_id, buf, 0xffff, 0, 0)
iAP2MsgAddU8Param(msg, 0, 0, param_1)              // 组 0 / ID 0 / U8
iAP2MsgAddDataParam(msg, 0, 1, ptr, len)           // 组 0 / ID 1 / 数据
```

这证明该函数构造 `0x5500/0x5501` 隧道消息，参数组固定 0，参数 0 是 U8，参数 1 是数据；**不证明普通 `0xAAxx` 认证消息嵌套此格式**。调用路径边界见 `A09.9`–`A09.11`。

依据：`f_100022264.s` / `.ghidra.c` 全文（含 `_iAP2MsgInit`、`_iAP2MsgAddU8Param`、`_iAP2MsgAddDataParam` 三处调用）。

`A09.4`（已确认）接收侧 `mfi4Auth_util_unpackFromTunnelDataiAP2Msg`（`0x100022398`）与 `mfi4Auth_util_parseMessage`（`0x1000221a8`）成对工作：后者先 `iAP2MsgInitWithSom(...)` 建消息对象，再 `iAP2MsgParserInit(0xffff, cb, 0, ctx)` 得到**逐字节解析器**，循环 `iAP2MsgParserConsumeByte` 消费输入，直到数据耗尽或回调返回非 0。

依据：`f_1000221a8.ghidra.c` 全文（`ConsumeByte` 循环 0x1000221e4 起）。

结论：上述中继路径复用 iAP2 消息解析器。普通 `0xAAxx` handler 直接遍历自己的 TLV 参数，见 §9.9；不得由隧道辅助函数的存在推导普通认证的线上封装。

## 9.3 每条认证消息的参数

`A09.5`（已确认）各 handler 用 `iAP2MsgGetFirstParam(msg, 0)` / `GetParamID` / `GetParamValueData`+`GetParamValueLen` 或 `GetDataAsU8` 遍历**参数组 0**。已确认的参数：

| msg_id | 参数 ID | 类型（getter） | 名称（固件日志字符串） |
|---|---|---|---|
| `0xAA01` certificate | `0x01` | U8（`GetDataAsU8`） | auth type（"Got valid/invalid auth type %d"） |
| | `0x02` | 数据（`GetParamValueData`+`Len`→`CFDataCreate`） | `pAccCertData` / `accCertLen` |
| | `0x00` | 数据 | `pAccIntermediateCertData` / `accIntermediateCertLen` |
| `0xAA03` challengeResponse | `0x00` | 数据 | `pAccSignData` / `accSignLen` |
| `0xAA06` certSerial | `0x00` | 数据 | `pAccSerNumData` / `accSerNumLen` |
| `0xAA10` RequestDeviceCertificate | 无参数解析 | — | 纯触发（见 9.4） |
| `0xAA12` RequestDeviceChallengeResponse | `0x00` | 数据 | `pChallengeBytes` / `challengeLength` |
| `0xAA14` DeviceAuthenticationFailed | 无参数解析 | — | 纯状态通知 |
| `0xAA15` DeviceAuthenticationSucceeded | 无参数解析 | — | 纯状态通知 |

字符串证据（`__TEXT` 内偏移即 VA − `0x100000000`）：

| 字符串 | 地址 |
|---|---|
| `Cert param malformed pAccCertData:%04lX, accCertLen:%04X, paramError:%02X` | `0x10020af13` |
| `Cert param malformed pAccIntermediateCertData:…` | `0x10020af9f` |
| `Cert param malformed pAccSignData:%04lX, accSignLen:%04X, paramError:%02X` | `0x10020b290` |
| `Cert serial number param malformed pAccSerNumData:…` | `0x10020b2e9` |
| `Auth challenge param malformed pChallengeBytes:%04X, challengeLength:%02X` | `0x1001dce53` |
| `Got valid auth type %d` / `Got invalid auth type %d` | `0x10020af13` |

依据：`f_1001850bc`、`f_100185d6c`、`f_1001860d4`、`f_100123204` 的 `.ghidra.c` 参数循环 + 上述字符串常量。

## 9.4 状态与门控

`A09.6`（已确认）`0xAA14` / `0xAA15` 不做参数解析，只调用 `setDeviceAuthState(link, 1)` / `(link, 2)`，并且**先检查 `iap2_feature_getFeature(link, 7)` 非空**；返回 1 表示已处理，0 表示忽略。

依据：`f_10012356c.ghidra.c`、`f_100123690.ghidra.c` 全文（各约 20 行）。

`A09.7`（已确认）`0xAA10` 同样是"触发型"：检查 feature 7 与 `link[0x18]`（处理队列）后，用 `acc_protocolEndpoint_performAsync(...)` 投递异步块，**不读任何参数**。

依据：`f_100123108.ghidra.c`（`0x100123108` 起 252 字节）。`A09.2` 的符号名表明其语义是"请求设备证书"，即由配件请求设备发起证书交换。

`A09.8`（已确认）认证全程**不改变链路状态机**：7 个 handler 都不调用 FSM 或 `iAP2Link*` 的链路动作；只改设备认证状态（1/2）与端点对象状态。

依据：`A09.6`、`A09.7` + `analysis/06` 的迁移表（无认证相关事件）。

## 9.5 未决项

| ID | 内容 |
|---|---|
| `OPEN-AUTH-1` | 认证消息的**发送顺序**与进入条件（谁先发 `0xAA10` 还是 `0xAA01`） |
| `OPEN-AUTH-2` | `0x5500` 与 `0x5501` 的区别（封装函数的 flag 来源） |
| `OPEN-AUTH-3` | 认证失败/超时后是否重试、重试几次 |
| `OPEN-AUTH-4` | `mfi4Auth_protocol_parse` 的报文类型集合（只读了入口） |
| `OPEN-AUTH-5` | 证书链校验与签名验证的具体算法（密码学，不在本阶段） |

## 9.9 认证消息的封装（按消息 + 方向复核）

`A09.9`（已确认）**入站认证消息的参数就在消息自身的参数组 0**，不是嵌套隧道：`iap2_accAuthentication_certificate`（`0xAA01`，`0x1001850bc`）、`challengeResponse`（`0xAA03`，`0x100185d6c`）、`certSerial`（`0xAA06`，`0x1001860d4`）三个 handler 都是 `iAP2MsgGetMsgID` → `iAP2MsgGetFirstParam` → `iAP2MsgGetParamID` → `iAP2MsgGetParamValueData/Len`，中间没有任何 `iAP2MsgParserInit`。

`A09.10`（已确认）**出站 device 认证消息同样不嵌套**：`__iap2_deviceAuthentication_RequestDeviceCertificate_block_invoke`（`0x10002e5b4`）用 `iAP2MsgInit(..., 0xaa11, buf, 0xffff, 0, 0)` + `iAP2MsgAddDataParam` 构造 `0xAA11`；`__…RequestDeviceChallengeResponse_block_invoke`（`0x10002e730`）同样构造 `0xAA13`。

`A09.11`（已确认）**`0x5500/0x5501` 只属于中继路径**：该封装仅由 `mfi4Auth_util_packIntoTunnelDataiAP2Msg`（`0x100022264`）生成，而它的**唯一调用者**是 `mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_TypeData`（`0x100084ef4`，`bl` 点 `0x100084f28`）。据此，旧结论 `A09.3`/`A09.4` 的"认证数据被包成 0x5500/0x5501"**只适用于中继**，不得套在 `0xAA01/0xAA03/0xAA06/0xAA11/0xAA13` 上。
