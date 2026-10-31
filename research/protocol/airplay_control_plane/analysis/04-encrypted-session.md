# 04 · 加密控制会话

> 覆盖要求 #4。问题：控制面从哪一刻开始加密、密钥从哪来、算法与记录格式。

## 4.1 开关点

```text
_httpconnection_ConfigureEncryption            0x24fdc8688
_httpconnection_configureEncryptionInternal    0x24fdc97e8
```

`configureEncryptionInternal` 在装配加密器前检查两个密钥长度：

```text
反编译 f_24fdc97e8 第 71 行：if (lVar3 < 0x20) -> cold_7（错误）
反编译 f_24fdc97e8 第 77 行：if (lVar3 < 0x20) -> cold_6（错误）
```

`A04.1`：读、写两个方向的密钥都不少于 **32 字节**；短于此会被拒绝。

## 4.2 密钥标签

密钥不是由控制面自己算的，而是"钥匙串"按上下文派生：

| 上下文 | 标签 | 地址（`AirPlaySender`） |
|---|---|---|
| 控制通道 | `Control-Salt` | `0x251bdf6ca` |
| | `Control-Read-Encryption-Key` | `0x251bdf6d7` |
| | `Control-Write-Encryption-Key` | `0x251bdf6f3` |
| 事件通道 | `Events-Salt` | `0x251bdf710` |
| | `Events-Read-Encryption-Key` | `0x251bdf71c` |
| | `Events-Write-Encryption-Key` | `0x251bdf737` |
| 数据流 | `DataStream-Salt` | `0x251bdf648` |
| | `DataStream-Input-Encryption-Key` | `0x251bdf658` |
| | `DataStream-Output-Encryption-Key` | `0x251bdf6a9` |

派生入口：`coreUtilsKeyHolder_CreateEncryptionKeysForContext`（`0x251a358e4`，控制/事件）
与 `coreUtilsKeyHolder_CreateEncryptionKeysForStream`（`0x2519bfecc`，数据流）。

`A04.2`：**读与写各有独立密钥**（不是同一密钥双向使用），因此两方向的 nonce/计数器也相互独立。
`A04.3`：控制、事件、每个数据流是**不同上下文**，密钥不可互换。

## 4.3 算法

| 项 | 值 | 证据 |
|---|---|---|
| AEAD | ChaCha20-Poly1305 | `_ChaCha20Poly1305EncryptMessage` `0x18be560fc`、`_ChaCha20Poly1305DecryptMessage` `0x18be5a694` |
| 上下文 | `CryptoAEADCreate` `0x18be7bb64` | 名称 + 参数 |
| 传输层命名 | `NetTransportChaCha20Poly1305` `0x18bf6ae15`、`NetSocketChaCha20Poly1305` `0x18bf6ac65` | 字符串 |

## 4.4 记录格式（以 analysis/12、13 的后续复核为准）

`A12.6`、`A13.1`–`A13.5` 已确认本构建传输层为 u16 LE 长度、密文、16 字节标签；
长度两字节为 AAD，读写分别使用独立 nonce64 状态。读侧上限 16384，写聚合最多 1024。
传输实际调用的是 `init_64x64` 与增量 encrypt/decrypt/final/verify 链，不能仅凭上表 Message 包装器名称推断布局。

详细地址、认证输入编排、nonce 推进与部分写规则见 [analysis/13](13-record-aad-nonce-and-key-direction.md)。
Configure 的底层密钥槽位已确定，`A15.1`–`A15.3` 进一步闭合CoreUtils provider的标签/角色/派生输入链；
目标CarPlay调用者采用哪种provider/角色及加密切换时刻仍未闭合。

## 4.5 本章 OPEN

| id | 问题 |
|---|---|
| `OPEN-AP-21` | 基本分帧已静态闭合；AAD/nonce 由 `OPEN-AP-38`/`39` 后续闭合 |
| `OPEN-AP-22` | 会话密钥（HKDF 输入）与 `Control-Salt` 的组合方式 |
| `OPEN-AP-23` | 加密从第几条消息开始（`/pair-verify` 的 M3/M4 是否已在加密层内） |
