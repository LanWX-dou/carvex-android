# 08 · 错误、超时与重试

> 覆盖要求 #9。本轮只能给出"有哪些错误面"与"错误如何可见"，超时参数与重试策略未取证。

## 8.1 已确认的错误面

| 场景 | 表现 | 证据 |
|---|---|---|
| 连接未就绪就发请求 | 直接返回错误，不发字节 | `0x24fda5504`（状态 ≠ 5 → `b.ne`） |
| 类型 4CC 未知 | 不组包，记日志后返回错误 | `0x24fda679c`、`func_0x0002500ee220(0xffffbefd,...)` |
| 正文长度不符 | 解析失败 | `"### Bad content length: %llu vs %zu"` `0x18bf69498` |
| chunk 头异常 | 解析失败 | `"### Bad chunk wrap"` `0x18bf6950f`、`"### Chunked body too large"` `0x18bf6952e` |
| Pair-Verify M2 的 ACL/错误分支 | 在错误 TLV 构造与 Detach 成功的特定分支中发送 TLV `7`+`6`，随后 reset；不能推广为所有签名/解析错误 | `0x18bf2a1a8`/`0x18bf2a1cc`；`analysis/14` A14.4 |
| Pair-Verify M2 无 ACL | 进入上述已核 ACL 错误分支；其它 profile/失败路径未由此表闭合 | `"### PairVerify client -- server lacks ACL"` |
| Pair-Verify M4 的 bad status 日志 | 输入 TLV `7` 的状态映射触发错误日志；这不是本函数检查 HTTP 状态码是否为 200 | `"### PairVerify client M4 bad status: 0x%X, %#m"`；`analysis/14` A14.4 |
| Pair-Setup 服务端不支持 SPAKE2+ | 回落到另一条路径或失败 | `"### PairSetup client SPAKE2+ not supported by server"` `0x18bf6c24e` |
| Pair-Setup 无口令 | 失败 | `"### PairSetup client SPAKE2 start failed: no password"` `0x18bf6c625` |

`A08.1`：`0xFFFFBEFD` 是"未知消息类型"路径返回的 OSStatus 值（`0x24fda679c` 之后的
`func_0x0002500ee220(0xffffbefd,"APTransportPackageHTTPGetHTTPMessage",0x3b7,0)`）；它的符号名未在三个镜像里给出。

## 8.2 超时

**未取证**。三个镜像里没有针对控制面单请求超时的显式参数被本轮读到；
`APTransportConnectionHTTPCreate` 的选项字典里是否有超时键也未解析。

`A08.2`：在拿到连接选项字典（`APTransportConnectionCreate`/`...HTTPCreate` 的 options）之前，
规范只能写"客户端应自行实现请求超时并重连"，不写具体秒数（`OPEN-AP-31`）。

## 8.3 重试

**未取证**。`apsession_EnsureStarted` 里有阶段推进，但没有读到达不到条件时的退避逻辑。

`A08.3`：本轮不能从固件证明哪些 AirPlay 请求可安全重发，也不能证明 `SETUP` 重发前必须
`TEARDOWN` 或一定会留下悬挂流。实现可以按目标 profile 制定幂等/清理策略，但必须把它标为
客户端策略并用真实车机或协议级样本验证；不能把“`/info`、`/pair-verify` 可重发”写成固件事实。

## 8.4 OPEN

| id | 问题 |
|---|---|
| `OPEN-AP-31` | 控制面请求超时的实际值/来源 |
| `OPEN-AP-32` | 断开后自动重连的条件与次数 |
| `OPEN-AP-33` | `0xFFFFBEFD` 对应的公开错误名 |
