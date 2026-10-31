# analysis/14 — 认证协议与密码学操作（算法层）

对应任务书第 5 节第 9 项的后半部分。本文件回答两件事：

1. 认证**协议**：有哪些消息、各自由谁发出、在什么条件下发出（序列与门控）；
2. 认证**算法**：哪些密码学操作被执行、输入输出是什么、由谁提供实现（**不复刻公有算法**，只定位与描述）。

> **协议族提示**：本文分析的是 **MFi4Auth**（构造侧 `0x51xx`），不是 23G90 的 **AccAuthentication** `0xAAxx` 七步。线上 ID 映射与设备侧/配件侧分表见 `spec/06 R-6.6.2`；分派侧的成组/复用仍是 `OPEN-AUTH-1`。

证据等级约定：`已确认` = 汇编/数据里能点到；`推断` = 由符号名与调用关系得出，未做交叉跳转证明。

## 14.1 协议消息集（已确认：符号存在）

`mfi4Auth_protocol_*` 一族函数名直接给出协议消息。发送侧与处理侧成对出现：

| 消息（协议名） | 发送侧符号 | 接收侧符号 |
|---|---|---|
| RequestAuthSetup | `mfi4Auth_protocol_initMessage_RequestAuthSetup` `0x100132e28` | `mfi4Auth_protocol_handle_AuthSetup` `0x100045148` |
| AuthSetup | `mfi4Auth_protocol_authSetupStart` `0x100044ee4` | 同上（对端视角） |
| RequestAuthStart | `mfi4Auth_protocol_initMessage_RequestAuthStart` `0x100132fc0` | `mfi4Auth_protocol_handle_AuthStart` `0x100046830` |
| AuthStart | `mfi4Auth_protocol_initMessage_AuthStart` `0x1000464e8` | 同上 |
| RequestAuthCert | `mfi4Auth_protocol_initMessage_RequestAuthCert` `0x100048904` | `mfi4Auth_protocol_handle_RequestAuthCert` `0x1000468dc` |
| AuthCert | `mfi4Auth_protocol_initMessage_AuthCert` `0x1001330e0` | `mfi4Auth_protocol_handle_AuthCert` `0x100046c78` |
| RequestAuthChallengeResponse | `mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse` `0x100044f3c` | `mfi4Auth_protocol_handle_AuthChallengeResponse` `0x100048bd8` |
| AuthChallengeResponse | 同上（对端） | 同上 |
| AuthFinish | — | `mfi4Auth_protocol_handle_AuthFinish` `0x100048a1c` |
| AuthenticationSucceeded | `mfi4Auth_protocol_initMessage_AuthenticationSucceeded` `0x1001334b8` | `mfi4Auth_protocol_handle_AuthenticationSucceeded` `0x10013358c` |
| AuthenticationFailed | — | `mfi4Auth_protocol_handle_AuthenticationFailed` `0x100048e90` |
| AuthenticationReset | — | `mfi4Auth_protocol_handle_AuthenticationReset` `0x100048d70` |
| RefreshAccessStateResponse | — | `mfi4Auth_protocol_handle_RefreshAccessStateResponse` `0x100048f44` |

另有独立的 NVM 子协议（`RequestUserNVMRead/Write`、`RequestNVMAuthStart/Finish`、`RequestNVMPublicKeyChallenge`、`RequestNVMErasePublicKey`、`NVM*Response`）与中继子协议（`DeviceiAP2RelayRemote*`），**不属于链路建立所必需的认证路径** → `OPEN-AUTH-6`。

## 14.2 会话创建与入口条件

`A14.1`（已确认）认证会话由 `mfi4Auth_protocol_initSessionCommon`（`0x100037928`）创建，配套 `cleanupSessionCommon`（`0x100037a40`）；会话对象通过回调注册与 iAP2 链路解耦：

| 回调 | 函数 | 用途 |
|---|---|---|
| 出站数据 | `setOutgoingDataHandler` `0x100037c10` | 把认证消息交给 iAP2 |
| 会话关闭 | `setSessionCloseHandler` `0x100037c74` | 清理 |
| 认证状态 | `setAuthStateHandler` `0x100037cd8` | 上报"通过/失败" |
| NVM 读 | `setNvmReadHandler` `0x100037da0` | 可选 |

`A14.2`（已确认）**认证由设备侧主动发起**：`accAuthProtocol_endpoint_sendAuthSetupStart`（`0x10004d4fc`）与 `mfi4Auth_endpoint_sendAuthSetupStart`（`0x100164928`）都调用 `mfi4Auth_protocol_authSetupStart`；存在 `setupAuthSetupStartTimer`（`0x10004d8a4` 等），说明发起有定时器保护。定时器上限由 `mfi4Auth_endpoint_timeoutForTransportInSeconds`（`0x1000a9414`）给出 → 具体秒数 `OPEN-TMR-AUTH`。

`A14.10`（已确认）**AuthSetup 决定分支**：设备收到 `AuthSetup` 后读取 `authType`（协议对象 `+0xe0`，日志串 `handle_AuthSetup: authType:%x`）并三选一：

| `authType` | 设备下一动作 | 附带数据 |
|---|---|---|
| `0` | 发 `RequestAuthChallengeResponse` | 16 字节随机数（`arc4random_buf(+0x2c0, 0x10)`） |
| `1` | 发 `RequestAuthStart` | 16 位会话标识（`arc4random()` 重试到非 `0`/非 `0xffff`，写入 `+0x152`） |
| `2` | 走 `AuthStart` 分支（要求标志位 3/4 已置，否则报错） | — |
| 其它 | 走错误出口（`LAB_10004540c`） | — |

依据：`f_100045148.ghidra.c` 第 103–175 行（`iVar4 = *(int *)(param_1 + 0xe0)` 的三段）。

`A14.11`（已确认）设备侧**先发 `RequestAuthSetup` 再等对端 `AuthSetup`**：`authSetupStart`（`0x100044ee4`）只做一件事——构造并发出 `initMessage_RequestAuthSetup`；发起动作由 `sendAuthSetupStart` 触发，且配有 `setupAuthSetupStartTimer` 超时保护。

依据：`f_100044ee4.ghidra.c`（唯一出站调用是 `initMessage_RequestAuthSetup`）。

`A14.3`（已确认）入站路径：`mfi4Auth_protocol_processIncomingMessage`（`0x100049224`）→ `mfi4Auth_protocol_parse`（`0x1000d3094`）→ 用 `iAP2MsgParserInit(0xFFFF, cb, 0, ctx)` 把**隧道载荷**解析成嵌套 iAP2 消息（与 `A09.4` 一致），再按消息 ID 分派到 `handle_*`。

## 14.3 密码学操作清单（算法层）

`A14.4`（已确认）**挑战是随机数**：`acc_auth_protocol_generateChallenge`（`0x10008e434`）调用 `arc4random_buf` 填充挑战缓冲；长度由 `acc_auth_protocol_challengeSizeForCertificate`（`0x10008dea0`）按证书决定。

`A14.5`（已确认）**签名验证与证书链校验不在此二进制内实现**，而是经 ObjC 消息转发给平台：

| 操作 | 入口 | 实际提供者 |
|---|---|---|
| 证书链校验 | `acc_auth_protocol_validateCertificateChain` `0x10008d72c` | `validateCertificateChain:type:realtime:error:`（`objc_msgSend$…` `0x1001abfe0`） |
| 挑战响应验证 | `acc_auth_protocol_verifyChallengeResponse` `0x10008e528` | 同类 ObjC 转发 |
| 证书解析 | `X509CertificateParse` `0x10010e1ec` 等 6 个函数 | 本二进制内的轻量 X.509 解析器（只解析结构，不做签名运算） |
| 序列号生成 | `platform_auth_createCertificateSerialNumber` `0x1000b6810` | 平台 API |
| 摘要/加密 | `mfi4Auth_protocol_encryptPayload` `0x100132acc` / `decryptPayload` `0x100132318` | 隧道载荷的加解密（对称） |

**结论**：本阶段能给出"**什么数据、做什么操作、按什么顺序**"，但具体算法参数（曲线、摘要、密钥长度）由平台框架提供，二进制里没有可复刻的实现 → 这正是"算法层"与"算法实现"的分界。规范里只写操作与数据流，不写曲线参数。

`A14.6`（推断）证书链相关操作顺序：`createCertificateData`（`0x10008c0c4`）→ `setPeerLeafCertificateData`（`0x10008cd80`）/`addPeerIntermediateCertificateData`（`0x10008cedc`）→ `validatePeerCertificateChain`（`0x10008d0f4`）。三者调用关系来自命名与相邻布局，未逐条跳转证明。

## 14.4 序列（分支已证明，完整时序未证明）

`A14.12`（已确认）每个 handler 的**出站消息**已逐一定位（收到 X → 发 Y）：

| 收到 | handler | 发出的消息 |
|---|---|---|
| `AuthSetup` | `0x100045148` | 按 `authType` 三选一（`RequestAuthChallengeResponse` / `RequestAuthStart` / `AuthStart`） |
| `RequestAuthCert` | `0x1000468dc` | `AuthCert`（设备证书链） |
| `AuthCert` | `0x100046c78` | `RequestAuthCert` + `AuthenticationSucceeded` |
| `AuthChallengeResponse` | `0x100048bd8` | `RequestAuthCert` |
| `AuthFinish` | `0x100048a1c` | `RequestAuthCert` |
| `AuthSetupFailed` | `0x1000467e4` | 无（只上报失败状态） |

依据：各 handler 的 `.ghidra.c` 中 `initMessage_*` 调用点。

`A14.7`（推断）由此得到两条主路径：

```
路径 A（authType = 0，challenge-first）
  设备 → RequestAuthSetup → 配件 → AuthSetup
  设备 → RequestAuthChallengeResponse（16B 随机数）
  配件 → AuthCert / AuthChallengeResponse
  设备 → RequestAuthCert → 配件 → AuthCert
  设备 → AuthenticationSucceeded（或 AuthenticationFailed）

路径 B（authType = 1/2，full）
  设备 → RequestAuthSetup → 配件 → AuthSetup
  设备 → RequestAuthStart（16 位会话标识）/ AuthStart
  配件 → RequestAuthCert → 设备 → AuthCert
  配件 → AuthChallengeResponse → 设备 → RequestAuthCert
  配件 → AuthFinish → 设备 → RequestAuthCert
  设备 → AuthenticationSucceeded
```

两条路径的**消息集合与每条消息的应答关系**都有证据；但"路径 A/B 由谁选择、每一步的推进条件"仍取决于对端与 `authType` → `OPEN-AUTH-1` 缩小为"完整时序"。

`A14.16`（已确认）**失败后的"重试"是认证类型回退，不是重传计数**：`handle_AuthenticationFailed`（`0x100048e90`）读取协议对象 `+0x90` 的**位图**，把"当前尝试的类型"标记为已试过，然后：

| 位图状态 | 动作 |
|---|---|
| `(mask & 3) == 1` | 置 `mask |= 0x03` |
| `(mask & 0xc) == 4` | 置 `mask |= 0x0c` |
| `(mask & 0x30) == 0x10` | 置 `mask |= 0x30` |
| 低位半字节全满（`(mask ^ 0xff) & 0xf == 0`）或 `(mask & 0x30) == 0x30` | `handle_AuthState(1)` → **放弃并上报失败** |
| 否则 | 重新 `initMessage_RequestAuthSetup` → **用下一个类型重开会话** |

即低位 4 位（`0x01/0x02/0x04/0x08`）与高位 2 位（`0x10/0x20`）各代表一种尝试类型，最多 6 次不同尝试，不存在"同一类型重发 N 次"的逻辑。

依据：`f_100048e90.ghidra.c` 全文。

`A14.17`（已确认）状态回调取值：`handle_AuthState(protocol, 1)` = 失败，`(protocol, 2)` = 成功（`handle_AuthenticationSucceeded` 传 2）。

依据：`0x100046780` 调用点（`f_10013358c.ghidra.c:94` 传 `2`；失败出口均传 `1`）。

`A14.18`（部分确认）`AuthenticationReset` 受配置键 `IgnoreAuthReset` 控制：`handle_AuthenticationReset`（`0x100048d70`）先读 `_kCFACCUserDefaultsKey_IgnoreAuthReset`，为真时进入日志为 `"AuthenticationReset: Ignored"` 的分支；该分支之后是否完全跳过复位未逐行读出。

依据：`f_100048d70.ghidra.c` 第 20–55 行。

## 14.5 状态、失败与超时

`A14.8`（已确认）认证结果只有两个落点：`setDeviceAuthState(link, 1)`（失败，`0xAA14`）与 `(link, 2)`（成功，`0xAA15`），且都以 `iAP2Feature 7` 存在为前提（`A09.6`）。

`A14.14`（已确认）**认证超时缺省 10 秒**：`mfi4Auth_endpoint_timeoutForTransportInSeconds`（`0x1000a9414`）在传输类型为 `3` 时返回 **10**，其它类型返回 **0**；可用用户默认键 `MFi4AuthTimeoutValueS`（字符串位于 `0x100221750` 附近）覆盖，覆盖值为负时按 0 处理。

依据：`f_1000a9414.ghidra.c` 全文（约 15 行）。

`A14.15`（已确认）状态上报走回调：`handle_AuthState(protocol, state)` 调用协议对象 `+0x22` 注册的处理器，`state` 取值见 `A14.17`。

`A14.9`（已确认）失败路径至少三条：`AuthenticationFailed` 消息、`AuthenticationReset` 消息、会话超时（`setupAuthSetupStartTimer` + `timeoutForTransportInSeconds`）。重试次数未取证 → `OPEN-AUTH-3`。

## 14.6 未决项

| ID | 内容 | 状态变化 |
|---|---|---|
| `OPEN-AUTH-1` | 完整时序与每步推进条件（分支已证明，见 `A14.12`/`A14.13`） | 仍开，范围已缩小 |
| `OPEN-AUTH-2` | `0x5500` 与 `0x5501` 的区别 | 仍开 |
| `OPEN-AUTH-3` | 失败重试 | **关闭**：按认证类型回退，最多 6 种，见 `A14.16` |
| `OPEN-AUTH-4` | `mfi4Auth_protocol_parse` 的报文类型集合 | **关闭**：见 14.1 |
| `OPEN-AUTH-5` | 证书链/签名的算法参数 | 仍开（由平台提供，二进制内不可得） |
| `OPEN-AUTH-6` | NVM/中继子协议是否参与链路建立 | 新增 |
| `OPEN-TMR-AUTH` | 认证超时的具体秒数 | **关闭**：缺省 10 s，见 `A14.14` |
| `OPEN-AUTH-7` | 认证状态回调取值 | **关闭**：1 失败 / 2 成功，见 `A14.17` |
