# 02 · Pair-Setup（配对建立）

> 覆盖要求 #3 的上半：`POST /pair-setup` 的 TLV 字段、密码学操作与状态机。
> 主证据：`CoreUtils` 的 `_SetupClientExchange`（`0x18bf24d98`，8,548 B）与它引用的 HKDF 标签字符串。

## 2.1 传输

| 项 | 值 | 证据 |
|---|---|---|
| 方法/路径 | `POST /pair-setup` | 4CC `psul`（`0x24fda5db8`），见 `05-rtsp-methods.md` |
| Content-Type | `application/octet-stream` | 同上分支 `x22` = `0x24fe6d336` |
| body | TLV8 序列（`type(1) len(1) value(len)`，无外层长度） | `_TLV8BufferAppend`（`0x18bf41b64`）为唯一编码入口 |
| 编码器 | `_TLV8GetNext`（`0x18bf41440`）/`_TLV8Get`（`0x18bf413cc`） | 解析侧 |

`A02.1`：此路径的 body 使用 TLV8。按类型查找不等于任意重排安全；分片、重复项与状态相关字段仍须遵循所选 profile，不能把同类型片段排序打散。

## 2.2 消息序列（客户端视角）

`_SetupClientExchange` 内部状态由 `pairingSession+0x80` 字节推进；它及 `PairingSessionExchange` 处理 TLV 交换，HTTP 承载由上层完成，不能把 TLV 状态机本身当 HTTP 客户端。以下区分外层 Setup 状态与 SPAKE2 子协议消息编号：

| 消息 | 方向 | 关键 TLV | 证据（指令/字符串） |
|---|---|---|---|
| M1 | C→S | `0`=本地 flags bit0、`6`=State(1)；条件追加 `0x13`/`0x1f`；此分支不写 `3` | state=1 → `0x18bf25004`；append 于 `0x18bf25018`/`0x18bf25034`，随后 detach 并置 state=2 |
| M2（SRP） | S→C | `6`=State、`2`=Salt、`3`=PublicKey；3072-bit SRP 对应 384B 公钥，不推广到 SPAKE2 | SRP 参数/消费路径；分支选择见 §2.4 |
| M3（SRP） | C→S | `6`=State(3)、`3`=客户端公钥、`4`=Proof | state=3 → `0x18bf24f98`；append 于 `0x18bf24fbc`/`0x18bf252c8`/`0x18bf252e0` |
| M4 | S→C | `6`=State(4)、`4`=Proof | 校验失败走错误路径 |
| M5 | C→S | `6`=State(5)、`5`=EncryptedData{`1`=Identifier,`3`=PublicKey,`0xa`=Signature}，另有条件字段 | `PS-Msg05` `0x18bf6c416`（引用点 `0x18bf26be8`）；append `0x18bf26644..80` |
| M6 | S→C | `6`=State(6)、`5`=EncryptedData{`1`,`3`,`0xa`} | `PS-Msg06` `0x18bf6c4c1`（引用点 `0x18bf25c44`） |

`A02.2`：M5/M6 使用 ChaCha20-Poly1305 包装调用，密钥来自 HKDF 的 `Pair-Setup-Encrypt-Salt` / `Pair-Setup-Encrypt-Info`。M5 在 `0x18bf26be4..0x18bf26c00` 传 `"PS-Msg05"`、长度 8、空 AAD；M6 对应 `"PS-Msg06"`。后续 `A13.4` 确认 encrypt_all/decrypt_all 对 8 字节参数直接调用 `init_64x64`，不是右补零。替代库适配与其它调用分支仍须逐项验证（`OPEN-AP-43`）。

## 2.3 签名与密钥派生

| 用途 | 标签 | 地址 |
|---|---|---|
| 控制器（客户端）签名 | `Pair-Setup-Controller-Sign-Salt` / `-Info` | `0x18bf6c3c7` / `0x18bf6c3e7` |
| 配件（车机）签名 | `Pair-Setup-Accessory-Sign-Salt` / `-Info` | `0x18bf6c4ca` / `0x18bf6c4e9` |
| MFi 凭证路径 | `MFi-Pair-Setup-Salt` / `-Info` | `0x18bf6c366` / `0x18bf6c37a` |
| SRP 盐派生 | `SRP-Salt-Salt` / `SRP-Salt-Info` | `0x18bf6f90f` / `0x18bf6f91d` |

`A02.3`：M5 构造的签名输入是 `HKDF输出32字节 ‖ 本地ID ‖ 本地公钥32字节`：`0x18bf262c0` 派生到缓冲开头，`0x18bf262c8..cc` 复制 ID 到 +32，`0x18bf262d0..e0` 追加公钥；总长为 ID 长度 +64。随后调用签名实现/回调，不能将此误写为“以 HKDF 输出为私钥的 HMAC”。结果写入类型 10、长度 64（`0x18bf26678..80`）；具体签名 API 仍须与身份密钥实现对齐。
（`0xa` 在 HAP TLV 里是 `Signature`；本 docset 只确认"类型 10、64 字节"这一事实，不引用外部规范。）

## 2.4 SRP 与 SPAKE2 两条路径（重要）

24A446 的 `_SetupClientExchange` 里**同时存在两条**：

- 经典 SRP-6a：`_SRPClientStart_libsrp`（`0x18bf36d10`）、`_SRPClientVerify_libsrp`（`0x18bf36f60`），
  "SRP-6a client (tjw)" 字符串 `0x18bf69121`；
- SPAKE2：`_SetupClientSPAKE2Start`（`0x18bf25140` 处引用）、`_SetupClientSPAKE2Verify`（`0x18bf259d4` 处引用），
  日志 `"PairSetup client SPAKE2 start"`（`0x18bf6c607`）、`"### PairSetup client SPAKE2+ not supported by server"`（`0x18bf6c24e`），
  以及 `"### PairSetup client SPAKE2 start failed: no password"`（`0x18bf6c625`）。

`A02.4`：客户端实现**必须**能识别服务端走哪条；选择依据不在本函数里闭合（`OPEN-AP-12`）。
`A02.5`：`0x22` 与 `0x20` 分别在 SPAKE2 start/verify 分支追加（`0x18bf25838`、`0x18bf26124`）。前者由外层 Setup state=3 的 `+0x2c1` 分支进入（`0x18bf2511c`），不能因日志称 SPAKE2 “M1” 就当成外层 Pair-Setup M1；它们也不是同一条 M1 必须同时携带的字段。完整分支选择仍为 `OPEN-AP-12`。

## 2.5 用户名

`"Pair-Setup"`（`0x18bf6c283`）在 `0x18bf25274` 处作为 SRP 用户名常量使用（`A02.6`）。
它不是 HTTP 用户名，而是 SRP 计算里的 `I`；客户端与车机必须一致。

## 2.6 OPEN

| id | 问题 | 影响 |
|---|---|---|
| `OPEN-AP-12` | SRP / SPAKE2 的选择依据（对端 flag？配对类型？） | 能否连上 |
| `OPEN-AP-13` | M1 的 `0` 类型语义（方法？保留？） | 互操作 |
| `OPEN-AP-14` | `0x19`（25）类型在 verify M1 的含义 | 互操作 |
| `OPEN-AP-15` | 是否要求 PIN（`/pair-setup-pin`、`/ensure-pair-pin` 的另一条路） | 首次配对 |
| `OPEN-AP-16` | 配对结果是否落盘、以什么键 | 二次连接免配对 |
