# 14 · Pair-Verify 密钥用途与 M2/M4 分支复核

依据 `CoreUtils/f_18bf29408.s` 与对应原始字节，Ghidra C 仅辅助理解。
外部 stub 名称来自 `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`：
`0x1900cf870=_ccsha512_di`、`0x1900cf190=_cchkdf`、
`0x1900ec2b0=_cccurve25519_make_pub`、`0x1900ec2a0=_cccurve25519`、
`0x1900cf130=_cced25519_verify`。下列 HKDF 表示 HKDF-SHA512，长度均为字节。

## 14.1 不得混同三种密钥用途（A14.1）

| 阶段 | 输入/标签 | 输出与消费者 | 指令范围 |
|---|---|---|---|
| M1 临时私钥材料 | RandomBytes(32)，`Pair-Verify-ECDH-Salt`/`Pair-Verify-ECDH-Info`（各21B） | HKDF输出32B原地写到 `sess+0x1ee`，随后 make_pub 写公钥32B到 `+0x1ce` | `0x18bf295a4..5ec` |
| M2 共享秘密 | 本地私钥 `+0x1ee`、对端TLV3公钥32B `+0x24e` | Curve25519输出32B到 `+0x28e`；全零被拒绝 | `0x18bf29964..9cc` |
| M2 TLV 加密密钥 | 上述共享秘密，`Pair-Verify-Encrypt-Salt`/`Pair-Verify-Encrypt-Info`（各24B） | HKDF输出32B到 `+0x1ae`，用于 `PV-Msg02` 解密及后续配对消息 | `0x18bf299d0..0x18bf29a00` |

旧条款把 ECDH 标签用于共享秘密的后处理，会派生出错误的握手加密密钥。
ECDH **共享秘密**、配对 **TLV加密密钥**、控制记录 **方向密钥**必须分别命名，不能统称一个“会话密钥”。
`OPEN-AP-17` 的本调用路径曲线/API 子项静态闭合；这里未重实现底层密码函数或证明所有 profile 相同。

## 14.2 常规 peer 查找分支的签名输入（A14.2）

- `0x18bf29ff8..0x18bf2a024` 取解密TLV1 Identifier，非空，按ID查找 peer，公钥存到 `sess+0x26e`。
- `0x18bf2a03c..050` 取TLV **10**，最小/最大均64字节；不是TLV9。
- `0x18bf2a08c..090` 复制对端临时公钥32B至签名消息开头；
  `0x18bf2a094..09c` 复制Identifier；`0x18bf2a0a0..0b4` 在其后复制本地临时公钥32B。
- `0x18bf2a0b8..0d0` 调 Ed25519 verify，以已查得的长期公钥验证：
  `peer_ephemeral_public[32] || peer_identifier[原始字节] || local_ephemeral_public[32]`。

该顺序只针对这里的常规 peer 分支。另有 callback 分支（`0x18bf29e8c..ec0`）传
`peer_ephemeral || local_ephemeral` 的64B，以及 AppleID 分支；不能把三段消息强加到所有分支。
`OPEN-AP-19` 因此是部分闭合，目标 CarPlay profile 的选择仍需另核。

## 14.3 M4 的可选密文与恢复 ID（A14.3）

非 MFi 分支在 `0x18bf29d64..d80` 允许 TLV5 不存在/为空继续后续检查；非空而长度<16则失败。
存在可解密内容时，`0x18bf29d90..dac` 仍使用 `sess+0x1ae` 的32B密钥，
nonce 按 flag `0x20000000` 选择 `PV-Msg04` 或 `PV-Msg4s`，长度8、空AAD。
“允许缺少密文”不等于绕过后续 AppleID/组信息等检查，也不等于所有车机 M4 都为空。

`Pair-Verify-ResumeSessionID-Salt`/`-Info`（各32B）出现在成功后的另一个分支：
`0x18bf29efc..f50` 受 bit1 门控，用共享秘密 `+0x28e` 派生 **8B恢复ID**，保存到 `+0x188`，
再调用保存恢复状态函数；不是派生 M4 的32B解密密钥。恢复是否启用仍为 `OPEN-AP-20`。

## 14.4 错误与 MFi 不能越界推断（A14.4）

- `0x18bf2a0f0..1f8` 的 ACL 失败分支构造 Error(7)/State(3)，仅构造/Detach成功后调用 reset。
  其它解析/验签错误可直接返回状态；不能声称所有 M2 错误都发送该TLV，或函数会直接关闭socket。
- M4日志“bad status”来自输入 **TLV7** 的状态映射，不是此函数检查 HTTP 200。
- MFi调用 `0x18bf29e20..e3c` 仍传共享秘密 `sess+0x28e`、长度32，因此“MFi分支替代了ECDH”错误。
  它对认证分支增加的要求与目标 CarPlay 适用性仍属 `OPEN-AP-18`/`34`，不据名字推断凭证可省略。

## 14.5 回归范围

`tools/verify-pair-verify.py` 将本函数及流描述符函数的切片与原镜像/反汇编核对，
检查关键调用、分支和常量。检查不执行完整握手、密码学或网络，不是独立密码向量/设备验收。
