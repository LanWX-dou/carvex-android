# 01 FairPlay 面：类接口与被混淆的核心

本文件只回答「有哪些入口、谁调谁」。语义级别的结论在 02（编排）与 03（密钥材料）。

---

## A-06 `AirPlaySender` 里的 FairPlay 客户端对象

`AirPlaySender` 用 CMBaseObject 风格实现了一个「FairPlay 认证客户端」类：

| 项 | 地址 | 说明 |
|---|---|---|
| 类 vtable | `0x276127410` | `_kAPAuthenticationClientFairPlayVTable` |
| 类对象 | `0x276127488` | `_kAPAuthenticationClientFairPlayClass` |
| 工厂 | `0x251ace54c` | `_APAuthenticationClientFairPlayCreate`（248 B） |
| `Finalize` | `0x251ace644` | 释放派生存储 |
| `CopyDebugDescription` | `0x251ace6c8` | 调试串 |
| `GetAuthenticationType` | `0x251ace720` | 8 B，直接返回常量 4（见 A-14 对 4 的交叉印证） |
| `AuthenticateEndpoint` | `0x251ace728` | 824 B，握手编排（A-08） |
| `CreateEncryptedKey` | `0x251acea60` | 280 B，密钥封装（A-09） |

这五个方法就是「客户端一侧 FairPlay 的全部对外动作」：**认证一次 + 需要时把 16 字节密钥包起来一次**。
再没有别的入口（类面穷尽性依据：vtable 里其余槽位是 `Finalize`/`CopyDebugDescription`/`GetTypeID` 一类的
CMBaseObject 标准槽，且调用图里不存在其他 `_fpAuthentication_*`）。

## A-07 被混淆的 FairPlay 核心：七个函数与调用关系

`AirPlaySender` 内嵌一套符号名本身是乱码的函数（名字是**字面**存在的，不是我们编的）：

| 地址 | 符号（字面） | 大小 | 角色（由调用点定性） |
|---|---|---|---|
| `0x2519dc1c0` | `_NROcmM` | 12 B | 极小；无参数处理，疑似常量/getter 形态 |
| `0x2519dcb7c` | `_U4HBs` | 5,484 B | **把 16 字节明文密钥变成密文 blob**（A-09） |
| `0x2519de244` | `_Mib5yocT` | 15,528 B | **握手状态机**：`(type, hwInfo, ctx, in, inLen, &out, &outLen, &state)` |
| `0x2519f2904` | `_zxcm2Qme0x` | 7,264 B | 未被本阶段函数直接调用；用途未定（`OPEN-2`） |
| `0x2519fa054` | `_IPaI1oem5iL` | 956 B | 上下文销毁 |
| `0x2519fa410` | `_cp2g1b9ro` | 3,988 B | 上下文创建：`(outCtx, hwInfo)` |
| `0x2519fb3a4` | `_jEHf8Xzsv8K` | 304 B | 释放 `_U4HBs`/`_OowSGu` 产出的 blob |
| `0x2519ffebc` | `_OowSGu` | 736 B | `(ctx, in, inLen, &out, &outLen)`：**解密 blob → 明文密钥** |

调用关系（`xref-scan.py` 全量调用图，`from` 落在函数体内才算）：

- `_U4HBs` ← `_fpAuthentication_CreateEncryptedKey` @ `0x251acead4`
- `_Mib5yocT` ← `_fpAuthentication_AuthenticateEndpoint` @ `0x251ace804` 与 `0x251ace91c`（同一循环两处）
- `_cp2g1b9ro` / `_IPaI1oem5iL` ← `_fpAuthentication_AuthenticateEndpoint`，以及
  `AirPlayReceiver` 的 `/fp-setup` 处理函数（A-10）
- `_OowSGu` ← `AirPlayReceiver` 的取键路径（`_GetDecryptKey`，已被内联，仅存日志串；A-24），用的是**接收侧自己的副本**
  `0x2517d8830`
- `_jEHf8Xzsv8K` ← `_fpAuthentication_CreateEncryptedKey`、接收侧 `/fp-setup` 与取键路径

**对偶性**：`AirPlayReceiver` 在同一份固件里有同一套核心的另一份副本：

| 符号 | 发送侧 | 接收侧 |
|---|---|---|
| `_Mib5yocT` | `0x2519de244` | `0x2517d0848` |
| `_U4HBs` | `0x2519dcb7c` | `0x2517d19a4` |
| `_jEHf8Xzsv8K` | `0x2519fb3a4` | `0x2517d314c` |
| `_OowSGu` | `0x2519ffebc` | `0x2517d8830` |
| `_cp2g1b9ro` | `0x2519fa410` | `0x2517dc080` |
| `_IPaI1oem5iL` | `0x2519fa054` | `0x2517df450` |
| `_zxcm2Qme0x` | `0x2519f2904` | `0x2517df9e8` |

结论（也是本层边界）：**同一套闭源核心被两端各自静态链接**，双方用同样的 `type` 常量驱动它，
所以协议编排可从两侧互相印证；但核心内部（SAP 密钥封装）无法从字节还原成可移植实现。
这一条直接支撑 `OPEN-1`（见 `08-open-items.md`）。

## 复算

- 类面：读 `source/metadata/sender/symbols.json` 里 `_fpAuthentication_*` 与 `_APAuthenticationClientFairPlayCreate`。
- 调用关系：`python3 firmware/tools/xref-query.py …\xrefs-sender.json source\metadata\sender …\dsc-stubs.txt callers _U4HBs _Mib5yocT`
  （接收侧把 `xrefs-sender`/`metadata\sender` 换成 receiver）。
- 核心大小：`export-asm.py` 的 `index.json` 里 `size` 字段即「到下一个函数起点」的上界。
