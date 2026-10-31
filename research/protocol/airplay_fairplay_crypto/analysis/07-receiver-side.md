# 07 车机侧怎么用这些字节（对偶校验 + 错误码）

本文件的价值：**别人写车机时看到的行为，和我们要写的客户端必须能对上**。所有结论都来自
`AirPlayReceiver`，与发送侧的结论互为独立证据。

---

## A-24 取解密键（`_GetDecryptKey`，已被内联进 `_AirPlayReceiverSessionSetSecurityInfo` `0x2518d3704`）

> 命名说明：`_GetDecryptKey` **没有独立符号**；它是被内联后残留在函数体里的日志/断言串
> （`"OSStatus _GetDecryptKey(...)"`，行号 `0x157a`/`0x159e`）才让我们知道这段代码原名如此。
> 引用时只能写「`0x2518d3704` 内部的取键路径」，不能说「调用 `_GetDecryptKey`」。

入参（由调用点还原）：`(session, infoDict, keyHolder, FPSAPContextRef *fpCtx, int flag, uint8_t *key, uint8_t *iv)`。

两条互斥路径：

```
路径 1（直接给键）：key/iv 都非空 → __SetSecurityInfoAES(session, key, iv)      ; 0x2518d37f4
路径 2（从字典取键）：
    ET = CFDictionaryGetInt64(infoDict, "et", &err)
    若err非0或ET==1 → 返回槽置0、删除ekey/eiv；不执行下面的密钥安装（A-39）
    if (ET != 8 && ET != 32) → 0xffffe5cf "Bad ET: %d"     ; 0x2518d38xx
    ekey = CFDictionaryGetData(infoDict, K_ekey, …, &len)
    若 fpCtx 或 *fpCtx 为空 → 0xffffe59e
    out = OowSGu(*fpCtx, ekey, ekeyLen, &blob, &blobLen)   ; FairPlay 解密
    若 blobLen != 0x10 → 0xffffe5a9                        ; **必须恰好 16 字节**
    jEHf8Xzsv8K(blob)                                     ; 释放
    iv = CFDictionaryGetData(infoDict, K_iv, buf16, 0x10, …, &len)
    若 len != 0x10 → 0xffffe5a9
    __SetSecurityInfoAES(session, key16, iv16)
    正常收尾清掉字典里的 ekey / iv 两个键（CFDictionaryRemoveValue）；错误路径可能绕过
```

对客户端的三条硬约束：

1. **ekey 解出来必须是 16 字节**（`0x10`），多一字节都算错（`0xffffe5a9`）。
2. **eiv 必须是 16 字节明文**，且会被长度校验（同样要求 `0x10`）——印证 A-12 的「IV 不加密」。
3. 本构建正常收尾会删除本地字典里的 ekey/eiv；这不证明线上字段一次性，也不证明重连一定重做 FairPlay。不要将 Apple Receiver 实现直接等同于任意车机。

## A-25 错误码表（两端合并，全部为 `OSStatus` 负值）

| 码 | 出现位置 | 含义（按调用点定性） |
|---|---|---|
| `0xfffee785` | 发送侧 `CreateEncryptedKey` | `U4HBs` 产出空指针 |
| `0xfffee786` | 发送侧 `AuthenticateEndpoint` | 状态字节既非 0 也非 1（握手异常） |
| `0xfffee788` | 发送侧 `CreateEncryptedKey` | 入参 CFData 长度不足 16（`CFDataGetBytes` 失败） |
| `0xfffee7d7` | `createDerivedKeyLegacy` | keyholder 无传输对象（无法派生） |
| `0xfffee7d8` | keyholder / 派生 | 内存分配失败 |
| `0xfffee7e1` | `APSCryptor*Create` | key/iv 为空或 key 长度不合规 |
| `0xfffee76f` | 发送侧分派表 | 未知流类型码 |
| `0xfffee704` | 接收侧 `/fp-setup` | "Bad ET"：ET 既非 8 也非 32 |
| `0xfffee703` | 接收侧 `/fp-setup` | FairPlay 核心处理失败 |
| `0xfffee702` | 接收侧 `/fp-setup` | 通用失败（含响应构造失败） |
| `0xfffee706` | 接收侧 `/fp-setup` | ACL 判定不允许连接 |
| `0xfffee645` | 接收侧屏幕 | 当前状态不允许设置安全信息 |
| `0xfffee647` | 接收侧屏幕 ChaCha | key 长度不是 0x20 |
| `0xffffe5cf` | 接收侧取键 | "Bad ET"（另一条路径的同一判定） |
| `0xffffe59e` | 接收侧取键 | 通用失败（含 FP 上下文为空） |
| `0xffffe5a9` | 接收侧取键 | 长度不是 16（key 或 iv） |
| `0xffffe596` | 接收侧解密/设置 | 解密输出长度不匹配、AES 安全信息设置失败的映射；tag 失败由库返回，不能假定恒为此码 |
| `0xffffce12` | 两端 | vtable 方法缺失 |

用法：这些是所分析函数的本地返回/日志值；只有确认线上响应携带同一数值及映射后，才能用于解释车机响应。不能假定所有本地 `OSStatus` 原样发到网络上。

## A-26 谁触发取键：`/setup` 的解析入口

`_AirPlayReceiverSessionSetSecurityInfo` 的调用者（调用图，非虚调用）：

```
0x2518a344c  in _airplayReqProcessor_requestProcessSetupPlist   ; 0x2518a2c18
0x2518a459c  in _airplayReqProcessor_requestProcessSetupSDP     ; 0x2518a3f70
```

这些调用点证明setup路径使用安全信息处理，不证明所有流逐流必含三个键；
schema层级/profile仍须核各调用者。`/fp-setup`负责FP交换，不是这里的密钥解封（A-10/A-39）。

完整时序（两端合并后的最小闭环）：

```
1) /fp-setup      : 状态驱动的 FairPlay 交换；轮数及内部标记未闭合
2) /setup (plist) : 按profile给安全信息et/ekey/eiv；FP分支解出key16并读iv16
3) 建立媒体通道   : 按流类型选加密器（A-19），屏幕走 CTR 或 ChaCha（A-22）
4) 屏幕记录       : decryptBuffer（A-23/A-35），优先ChaCha、否则CTR；不是这里执行CBC
```

`A-26` 只证明了 2) 与 3) 的衔接；1) 与 2) 之间「上下文如何被会话持有」的代码路径未逐条阅读
（`param_4` 是 `FPSAPContextRef *`，指向会话内某处），标记**未复核**。

## 复算

- `readable/ghidra/AirPlayReceiver/f_2518d3704.ghidra.c`（取键全流程，第 60–165 行）。
- `python3 firmware/tools/xref-query.py …\xrefs-receiver.json source\metadata\receiver …\dsc-stubs.txt callers _AirPlayReceiverSessionSetSecurityInfo`
- 错误码可回查各自 `_APSLogErrorAt` / `_airplayReqProcessor_*` 的行号参数。
