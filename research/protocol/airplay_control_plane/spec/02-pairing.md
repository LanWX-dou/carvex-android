# 02 · 配对

## 2.1 Pair-Setup

- R-2.1 目标 profile 需要建立配对时，此路径发送 `POST /pair-setup`，`Content-Type: application/octet-stream`，body 为 TLV8；何时需要完整 Setup 不能仅由函数存在推导（`A02.1`、`A03.8`）。
- R-2.2 本构建 Setup M1 写 `0`（flags bit0）和 `6`（State=1），条件追加 `0x13`/`0x1f`；不得照搬 Verify M1 而强制加公钥。SRP 的公钥 `3` 与证明 `4` 在外层 state=3 发送；SPAKE2 子协议编号与外层编号须分开（`A02.1`、`A02.4`、`A02.5`）。
- R-2.3 选择 SRP 路径时解析 M2 的 `2`(Salt) 与 `3`(PublicKey)，计算证明；不能把 SRP 字段/固定长度套到 SPAKE2 路径（`A02.4`）。
- R-2.4 M5 的 `5`(EncryptedData) 使用 `Pair-Setup-Encrypt-Salt`/`-Info` 派生密钥，包装调用传入 8 字节 `PS-Msg05`；已核包装器直接选择 `init_64x64`，没有右补零成 12 字节的步骤。转为其它库 API 前仍须核实 nonce 状态及认证输入编排，不能只比较参数宽度（`A02.2`、`A13.4`、`OPEN-AP-43`）。
- R-2.5 M5 明文**必须**含 `1`(Identifier)、`3`(PublicKey)、`10`(Signature, 64 字节)（`A02.3`）。
- R-2.6 `Pair-Setup-Controller-Sign-*` 的 HKDF 输出是签名消息的 32 字节前缀，不是替代长期身份私钥的“签名密钥”；M5 输入为该前缀、ID、公钥的串联。M6 使用 Accessory 标签构造对端校验材料（`A02.3`）。
- R-2.7 SRP 用户名固定为 `Pair-Setup`（`A02.6`）。

## 2.2 Pair-Verify

- R-2.8 采用完整 Pair-Verify 路径时，M1 至少含 `6`(State) 与 `3`(32 字节临时公钥)；是否每次重连执行完整路径、是否恢复会话仍由 profile 与 `OPEN-AP-20` 决定（`A03.1`、`A03.2`、`A03.8`）。
- R-2.9 复现此完整Verify路径时，M1 用32B随机材料和 `Pair-Verify-ECDH-Salt`/`-Info` 经HKDF-SHA512生成32B临时私钥材料并生成Curve25519公钥；M2 用本地私钥与对端32B公钥求共享秘密，拒绝全零结果，再以 `Pair-Verify-Encrypt-Salt`/`-Info` 经HKDF-SHA512派生32B配对TLV加密密钥。不得把ECDH标签用到共享秘密的后处理（`A03.3`、`A14.1`）。
- R-2.10 M2 必须按该配对密钥与8B `PV-Msg02`、空AAD解密并验证标签；常规peer分支解析TLV1的非空ID和TLV10的64B签名，以该ID查得的长期公钥做Ed25519验证，消息为 `对端临时公钥32B || 对端ID原始字节 || 本地临时公钥32B`。callback/AppleID等分支另有规则，不能混用或在失败后擅自降级（`A03.4`、`A14.2`、`OPEN-AP-19`）。
- R-2.11 M3 **必须**用同一会话密钥、`PV-Msg03` nonce 加密（`A03.6`）。
- R-2.12 解析/验签失败不得推进为配对成功。已核ACL失败分支仅在Error(7)/State(3)构造/Detach成功后reset；其它失败可能直接返回状态，不保证发相同TLV或立即关闭socket。客户端清理、重连与禁止降级应作为显式策略（`A03.5`、`A14.4`）。
- R-2.15 非MFi M4分支允许TLV5缺失/为空后继续其它检查；存在密文时使用同一32B配对密钥，8B nonce按flag选择 `PV-Msg04`/`PV-Msg4s`。`Pair-Verify-ResumeSessionID-*` 成功后派生的是8B恢复ID，不是M4解密密钥；完整恢复条件仍须由profile决定（`A14.3`、`OPEN-AP-20`）。

## 2.3 密钥保护

- R-2.13 长期私钥**必须**存放在受保护存储；**不得**写入日志、文档、测试向量（`A09.6`）。
- R-2.14 配对成功**不**代表可解密内容；FairPlay 另走 `/fp-setup`（`A09.1`）。

## 2.4 未闭合

SRP/SPAKE2 选择依据（`OPEN-AP-12`）、M1 的 `0`/`0x19` 字段语义（`OPEN-AP-13`/`OPEN-AP-14`）、
是否强制 PIN（`OPEN-AP-15`）、凭证落盘方式（`OPEN-AP-16`）、MFi 分支（`OPEN-AP-18`）、
M2其它签名分支/profile（`OPEN-AP-19`）、恢复会话（`OPEN-AP-20`）；本路径曲线/API已静态核实（`OPEN-AP-17`）。
