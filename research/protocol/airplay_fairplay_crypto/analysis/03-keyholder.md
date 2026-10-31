# 03 密钥材料与生命周期：keyholder

一句话结论：**master key 与 master IV 都是本机随机生成的 16 字节；master key 由 FairPlay 加密后外发，
master IV 明文外发；一组 stream 的密钥由 SHA-512 KDF 从 master key 派生（见 04）。**

---

## A-11 keyholder 家族与派生存储布局

`AirPlaySender` 里与 keyholder 相关的实现有四个家族（符号均实存）：

| 家族 | 工厂 | 关键方法（地址） |
|---|---|---|
| Legacy | `_APKeyHolderLegacyCreate` `0x251aa9060` | `CopyMasterAESKeyAndIV` `0x251aa9490`、`CreateEncryptedMasterAESKeyAndIV` `0x251aa9524`、`UpdateMasterAESKeyAfterSharing` `0x251aa9668`、`CreateDerivedAESKeyAndIVForLegacyStream` `0x251aa97a0`、`CreateDerivedKey` `0x251aa98fc`、`createDerivedKeyLegacy` `0x251aa9a60`、`GetAuthenticationType` `0x251aa93f4` |
| Shared | `_APKeyHolderSharedKeyCreate` `0x251aafde0` | `CopyMasterAESKeyAndIV` `0x251ab0108`、`CreateEncryptedMasterAESKeyAndIV` `0x251ab019c`、`GetAuthenticationType` `0x251ab006c` |
| CoreUtils | `_APKeyHolderCoreUtilsCreate` `0x251a355d0` | `CreateDerivedKey` `0x2519bffc8`、`CreateEncryptionKeysForStream` `0x2519bfecc`、`CreateEncryptionKeysForContext` `0x251a358e4` |
| APS 便捷层 | — | `_APSKeyHolderCreateEncryptionKeysForStream` `0x251a89d50`、`_APSKeyHolderGetAuthenticationType` `0x251a9ff20`、`_apsession_ensureKeyHolderSetUp` `0x251b5ce10` |

`_APKeyHolderLegacyCreate` 的派生存储布局（`0x251aa9060`，逐条对得上）：

| 偏移 | 内容 | 证据 |
|---|---|---|
| `+0x00` | 传输对象（`CFRetain`） | `0x251aa90xx`: `plVar3[0] = param_2; CFRetain(param_2)` |
| `+0x08` | 身份/会话对象（`CFRetain`） | `plVar3[1] = param_3; CFRetain(param_3)` |
| `+0x10` | **master key（16 字节，随机）** | `RandomBytes(plVar3+2, 0x10)` |
| `+0x20` | **master IV（16 字节，随机）** | `RandomBytes(plVar3+4, 0x10)` |
| `+0x30` | 安全内存分配器 | `APSCreateSecureMemAllocator()` |

`RandomBytes` 的符号来自 A-03 的桩解析（`0x258101e80 → _RandomBytes`）；两步调用都是 `(buf, 16)`。

**因此：客户端不需要「协商」master key——它是本机熵源产生的。**

## A-12 ekey / eiv 的确切语义：`CreateEncryptedMasterAESKeyAndIV`（`0x251aa9524`）

```
keyData = CFDataCreate(alloc, storage+0x10, 0x10)        ; 明文 master key 包成 CFData
若 storage+0x08 (transport) 存在：
    vtable = CMBaseObjectGetVTable(transport)
    (*(vtable[+0x10]+0x18))(transport, keyData, alloc, &encKeyData)   ; FairPlay 加密该 16 字节
ivData  = CFDataCreate(alloc, storage+0x20, 0x10)        ; master IV：**不加密**，直接包 CFData
返回 (encKeyData, ivData)
```

可写结论：

- **`ekey` = FairPlay 加密后的 16 字节 master key**，长度由 FairPlay 决定（不保证 16，见 A-09）。
- **`eiv` = 明文 16 字节 master IV**。这一点很容易写错（很多二手资料把 IV 也当加密的）；
  本固件的字节是：`CFDataCreate(alloc, +0x20, 0x10)` 直接返回，中间没有任何加密调用。
- 接收侧与此完全对称：取键路径（`_GetDecryptKey`，内联后仅存日志串）用 FairPlay 把 ekey 解成 16 字节、把 eiv 直接读 16 字节（A-24）。

## A-13 刷新（sharing）：`UpdateMasterAESKeyAfterSharing`（`0x251aa9668`）

```
transport = storage+0x08；若为空直接返回 0
authType = (*(transport.vtable[+0x10]+0x08))(transport)      ; GetAuthenticationType
若 authType == 4:                                            ; 4 = FairPlay（与 A-06 的 GetAuthenticationType 返回值一致）
    (*(storage[0].vtable[+0x10]+0x08))(storage[0], &masterKey, 0x10, 0, 0, 0x10, &masterKey)
```

可写结论：

- 刷新动作**只针对 authType == 4**（FairPlay）的传输，其它认证方式直接跳过。
- 刷新就地替换本地16B master缓冲（输入输出同一位置）；不证明所有派生副本或对端旧key同时失效。
- 「什么时候调用」在固件里看不到（没有直接调用者，见 A-04 的线性扫描局限）；调用时机进 `OPEN-4`。
- 本函数不保留该缓冲旧值；对端/在用流的失效窗口与重传仍需上层证据→OPEN-5。

## A-14 认证类型常量

- `_fpAuthentication_GetAuthenticationType`（`0x251ace720`，8 字节）直接返回常量 **4**。
- `UpdateMasterAESKeyAfterSharing` 只在 **4** 时动作（A-13）。
- 接收侧取键路径（`_GetDecryptKey`，已内联）用 `param_5` 与 `APReceiverSystemInfoCopyProperty(...)` 的结果决定是否
  额外调用 keyholder 的 `+0x18` 方法（A-24 末段）。

因此：**4 是 FairPlay 的认证类型标识**，两端一致。其它取值（0/1/2/3…）本阶段没有证据 → 不写。

## A-15 清理路径

- FairPlay 上下文：`IPaI1oem5iL`（`0x2519fa054`）。
- `U4HBs` / `OowSGu` 产出的 blob：`jEHf8Xzsv8K`（`0x2519fb3a4`）。
- 派生密钥用的临时名缓冲区：`createDerivedKeyLegacy` 用 `memset` 清零后再 `free`（A-17 有细节）。
- keyholder 自身：`Finalize`（`0x251aa91ac`）在对象析构时释放，未被本阶段逐条阅读 → 标记**未复核**。

## 复算

- `readable/ghidra/AirPlaySender/f_251aa9060.ghidra.c`（布局）、`f_251aa9524`（ekey/eiv）、
  `f_251aa9668`（刷新）。
- 桩名：`dsc-stubs.txt` 里 `0x258101e80`、`0x25810d150`。
- 汇编：`source/asm/AirPlaySender/f_251aa9524.s`（`0x251aa95xx` 处两次 `CFDataCreate`）。
