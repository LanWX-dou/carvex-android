# 03 · Pair-Verify（配对校验）

> 覆盖要求 #3 的下半。主证据：`CoreUtils` 的 `_VerifyClientExchange`（`0x18bf29408`，4,280 B）
> 与其内部 `_VerifyClientM1`/`_VerifyClientM2`/`_VerifyClientM3`（`0x18bf31614`）/`_VerifyClientM4`。
> 密钥用途、签名分支和恢复ID已按 [analysis/14](14-pair-verify-key-schedule.md) 修正。

## 3.1 传输

`4CC pave` → `POST /pair-verify`，`Content-Type: application/octet-stream`，
指令级证据：`0x24fda5cac`（`cmp w21,0x70617665`）→ `0x24fda6118`（`x24=0x24fe6d412` = `/pair-verify`）→ `0x24fda6184`（`x22=0x24fe6d336`）。见 `05` 章抽检行。

## 3.2 M1（C→S）

```text
0x18bf29610  TLV8BufferAppend(buf, 0x00, &byte,    1)   ; 类型 0，1 字节
0x18bf29628  TLV8BufferAppend(buf, 0x06, &byte,    1)   ; 类型 6，1 字节（State）
0x18bf29640  TLV8BufferAppend(buf, 0x03, sess+0x1ce, 0x20) ; 类型 3，32 字节（临时公钥）
```

另有 `_TLV8BufferAppendUInt64(&buf, 0x19)`（反编译 `f_18bf29408` 第 531 行）——**类型 0x19** 的整数值。

`A03.1`：M1 的临时公钥是 **32 字节**（`mov w3,#0x20` 在 `0x18bf2963c`，随后 `0x18bf29640` 调Append），存放在会话对象 `+0x1ce`。
`A03.2`：M1 至少含 `6`(State) 与 `3`(PublicKey) 两个 TLV；`0` 与 `0x19` 的语义未闭合（`OPEN-AP-13`/`OPEN-AP-14`）。

## 3.3 共享密钥

`A03.3`（修正，详见 `A14.1`）：M1 先用 RandomBytes(32) 与 HKDF-SHA512 的
`Pair-Verify-ECDH-Salt`/`-Info`（各21B）生成临时私钥材料到 `+0x1ee`，再生成公钥到 `+0x1ce`。
M2 调 Curve25519 用本地私钥及对端32B公钥得到共享秘密到 `+0x28e`，拒绝全零输出；
再用 **`Pair-Verify-Encrypt-Salt`/`-Info`**（各24B）HKDF-SHA512 派生32B配对加密密钥到 `+0x1ae`。
ECDH标签不是共享秘密的后处理标签。调用/参数证据为 `0x18bf295a4..5ec`、`0x18bf29964..0x18bf29a00`。
`OPEN-AP-17` 的本路径曲线/API已静态闭合；不代表所有profile或替代密码库已验证。

## 3.4 M2（S→C）与校验

| 步骤 | 动作 | 证据 |
|---|---|---|
| 1 | 取 TLV `5`（EncryptedData） | 反编译 `f_18bf29408` 第 217 行错误串 `get encrypted data` |
| 2 | 用 `Pair-Verify-Encrypt-Salt`（`0x18bf6d511`）/`-Info`（`0x18bf6d52a`）派生会话加密密钥 | 同文件第 206–207 行 |
| 3 | ChaCha20-Poly1305 解密，nonce=`"PV-Msg02"`（`0x18bf6d57d`，8 字节） | 同第 231 行 `PV-Msg02`,8 |
| 4 | 常规 peer 分支取 `1`(Identifier)、`10`(Signature,64B)，不是9 | `0x18bf29ff8..0x18bf2a050` |
| 5 | 常规分支 Ed25519 验签输入为对端临时公钥 + 对端ID + 本地临时公钥；callback/AppleID 分支另计 | `0x18bf2a08c..0d0`，`A14.2` |
| 6 | 校验 ACL（服务端是否允许该 peer） | 同第 390 行 `server lacks ACL`；`__PairingSessionVerifyACL` |
| 7 | ACL 失败且错误TLV构造/Detach成功时回 `7`=Error(7) + `6`=State(3) 并 reset；不是所有失败共用 | `0x18bf2a190..1f8`、`A14.4` |

`A03.4`：M2 的 nonce 是**固定字符串** `"PV-Msg02"`，不是随机数；`A03.5`：已核 ACL 失败分支可产出错误TLV并reset，
其它错误可直接返回状态，不能从此函数推出“直接断开socket”或“全部失败发送同一错误TLV”。

## 3.5 M3 / M4

- M3：`__VerifyClientM3`（`0x18bf31614`）把 `"PV-Msg03"`（`0x18bf6d804`）加密后作为 TLV `5` 发出；
  它复用 M2 的会话加密密钥（`A03.6`）。
- M4：非MFi路径允许 TLV5 缺失/为空后继续其它检查；有密文时复用 `+0x1ae` 配对加密密钥，
  nonce按flag `0x20000000` 选择 `PV-Msg04`/`PV-Msg4s`（`A03.7`、`A14.3`）。
  `Pair-Verify-ResumeSessionID-*` 是成功后按bit1选择派生的 **8B恢复ID**，不是解密密钥。
  “M4 bad status”日志来自输入 TLV7 状态映射，不是此函数检查 HTTP 状态码200（`A14.4`）。

## 3.6 MFi 变体

同一函数里还有 `MFi-Pair-Verify-Salt`（`0x18bf6da68`）/`MFi-Pair-Verify-Info`（`0x18bf6da7d`）分支
（`0x18bf29e00..e3c`），此校验调用仍传入 `+0x28e` 的32B共享秘密，不能说它替代 ECDH。
CarPlay 场景是否走它、凭证要求及具体校验仍未闭合（`OPEN-AP-18`、`A14.4`）。

## 3.7 与 Pair-Setup 的关系

`A03.8`：Setup 与 Verify 有独立状态机/HKDF 标签，Verify 路径会查找已有 peer；这支持“建立身份材料”与“校验已有身份”的职责区分，但不足以证明 Setup 只在首次、Verify 在每次连接无例外执行。恢复会话、MFi/profile 分支和调用者门控仍为 `OPEN-AP-18`/`OPEN-AP-20`。

## 3.8 OPEN

| id | 问题 |
|---|---|
| `OPEN-AP-17` | 本路径 Curve25519 API/32B输入输出已静态闭合，替代库需另验 |
| `OPEN-AP-18` | CarPlay 是否走 MFi 校验分支 |
| `OPEN-AP-19` | 常规peer分支串联顺序已核；callback/AppleID等profile适用性仍缺 |
| `OPEN-AP-20` | 恢复会话（`PV-Msg4s`）在哪些条件下启用 |
