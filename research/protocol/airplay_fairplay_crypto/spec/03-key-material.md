# spec 03 密钥材料与生命周期

## R-3.1 master key 与 master IV 各自独立随机生成，长度都是 16 字节

```
masterKey = RandomBytes(16)
masterIV  = RandomBytes(16)
```

两者分开生成（两次 `RandomBytes` 调用，缓冲偏移 `+0x10` 与 `+0x20`），不是「一个 32 字节拆两半」。
依据：A-11（`_APKeyHolderLegacyCreate` `0x251aa9060`）。级别：A。

## R-3.2 `ekey` 加密、`eiv` 明文

```
ekey = FairPlay_Encrypt(masterKey)     // 长度不固定，由核心决定
eiv  = masterIV                        // 字段值本身不经 FairPlay 包裹；传输层可另行加密
```

依据：A-12（`CFDataCreate(alloc, +0x20, 0x10)` 直接返回，中间无加密调用）。级别：A。

## R-3.3 接收侧对长度的硬校验

- `ekey` 经 FairPlay 解出后必须**恰好 16 字节**，否则 `0xffffe5a9`。
- `eiv` 必须**恰好 16 字节**，否则 `0xffffe5a9`。
依据：A-24。级别：A。

## R-3.4 字段的本地清理

本构建正常收尾路径删除本地字典中的 `ekey`/`eiv`，不能据此推导第二次 `/setup` 或重连的接受规则。密钥、nonce 与会话生命周期必须由已验证 profile 管理，不能将本地删除当作对端已失效通知。依据：A-24、R-1.6。级别：A（本地清理）；线上重连规则未闭合。

## R-3.5 刷新：仅 FairPlay 传输，且就地替换

```
if (transport != NULL && GetAuthenticationType(transport) == 4) {
    newMasterKey = keyHolderTransportTransform(masterKey)   // 原地，输入输出同一 16 字节缓冲
}
```

- 刷新后此缓冲的旧 master key 被覆盖；不能据此证明所有派生副本或对端旧 key 同时失效。
- 需要新 master key 的流必须按 R-4.1 派生；在用流的切换时机不能仅由这次写入推导。
- 触发时机 → `OPEN-4`；旧 key 的容忍窗口/重传 → `OPEN-5`。
依据：A-13（`0x251aa9668`）、A-14。级别：A（行为）/ C（时机）。

## R-3.6 中间材料的清理

| 材料 | 清理方式 | 证据 |
|---|---|---|
| 明文 master key 的临时副本（`CreateEncryptedKey` 内） | 用完清零 | A-09 |
| FairPlay 输出的密文 blob | 用后立刻 `jEHf8Xzsv8K` 释放 | A-09、A-15 |
| 派生用的名字缓冲 | 清零后释放 | A-15 |
| FairPlay 上下文 | `IPaI1oem5iL` | A-15 |
| KDF 的 64 字节摘要 | 取完 16 字节后整块清零 | A-16 |

依据：A-09、A-15、A-16。级别：A（行为）/ B（清零是否覆盖所有路径未逐一验证）。

## R-3.7 不许做的事

- 不要用固定 key 或空 IV 做「测试通过」的结论。
- 不要把 `eiv` 也送进 FairPlay 包裹；其字段要求原始 16 字节 IV，不能无证据断言包裹后恒为 32 字节。
- 不要自行猜测刷新时机；必须确认两端对在用流的密钥切换约定（`OPEN-4`/`OPEN-5`）。
依据：A-12、A-24、A-13。级别：A。
