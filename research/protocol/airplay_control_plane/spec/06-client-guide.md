# 06 · 客户端实现指引

## 6.1 候选实现顺序（非已证全序）

下列是原型拆分顺序，不是适用于所有车机的强制握手；配对分支、恢复、加密切换与事件时机仍须核实。

1. 从发现结果取地址/端口，建 TCP 连接（`R-1.1`、`R-1.2`）；
2. 实现 RTSP 编解码：请求行 + `CSeq` + `Content-Length` + 可选 `Content-Type`（`R-4.1`–`R-4.7`）；
3. `GET /info`，解析能力（方法映射见 `R-4.8`；响应字段/schema 仍 `OPEN-AP-45`）；
4. 按目标 profile 判断是否需 `POST /pair-setup`，选择 TLV8 + SRP/SPAKE2 分支（`R-2.1`–`R-2.7`）；
5. `POST /pair-verify`，ECDH + HKDF + ChaCha20-Poly1305（`R-2.8`–`R-2.12`）；
6. 切换控制面加密（`R-3.1`、`R-3.3`）；
7. `POST /fp-setup`，再 `SETUP`（`R-5.1`）；
8. `RECORD`，按需建事件通道，收尾 `TEARDOWN`（`R-1.9`、`R-5.7`）。

## 6.2 状态机（建议）

`IDLE → CONNECTED → INFO → PAIRED → ENCRYPTED → FP → SETUP → PLAYING → TEARDOWN`。
原型可选择失败后回到 `IDLE` 并释放本次连接资源，这是保守策略；不允许在密钥/身份未确认时发受保护业务请求。实际恢复/重连时机见 `OPEN-AP-42`，不得将原型策略当作固件全局规则。

## 6.3 日志

设备**应**记录：方法、URL、`CSeq`、状态码、响应头 `Content-Type`/`Content-Length`、失败原因。
**不得**记录：任何密钥、nonce、明文 TLV、证书私钥（`R-2.13`）。

## 6.4 常见失败

| 现象 | 先查 |
|---|---|
| 连上但无响应 | 端口是否来自发现结果（`OPEN-AP-1`）、请求行版本是否 `RTSP/1.0` |
| 401/403 | 响应正文与profile认证要求；不能只凭状态码归因为缺Verify或CSeq不连续 |
| 配对TLV解密失败 | 是否误用ECDH标签代替Encrypt标签、8B nonce和tag编排、M4是否把恢复ID当密钥（`A14.1`、`A14.3`） |
| 控制记录解密失败 | 上游角色/标签方向（`OPEN-AP-40`）、两字节长度AAD、nonce推进与部分写缓存（`A13.1`–`A13.5`） |
| `SETUP` 失败 | `streams` 结构（`OPEN-AP-25`）、URL 是否一致（`OPEN-AP-9`） |

## 6.5 自测

用 `reference-impl/` 的解析器做回环：构造请求→解析→比对字段；配对状态机用固定向量测试 TLV 编解码（不含真实密钥）。
