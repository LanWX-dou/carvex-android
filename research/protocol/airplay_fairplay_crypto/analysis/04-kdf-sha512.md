# 04 派生：SHA-512 KDF（可完整移植）

一句话结论：**`key16 = SHA-512(name || K)[0..15]`，`iv16 = SHA-512(name' || K)[0..15]`，
name 是 ASCII 前缀 + 十进制索引；K 在 Legacy 路径上是 16 字节 master key。**

这是本阶段**唯一**可以给出参考实现并可被向量验证的密钥派生环节。

---

## A-16 通用 KDF：`_APSEncryptionUtilsDeriveAESKeySHA512`（`AirPlaySupport` `0x226ee961c`）

签名（由调用点与寄存器用法还原）：

```
void APSEncryptionUtilsDeriveAESKeySHA512(
        const uint8_t *keyMaterial, size_t keyLen,      // x0, x1
        const char *nameKey, size_t nameKeyLen,         // x2, x3
        const char *nameIV,  size_t nameIVLen,          // x4, x5
        uint8_t outKey[16],                             // x6（可为 NULL）
        uint8_t outIV[16]);                             // x7（可为 NULL）
```

指令级流程（`0x226ee961c`）：

```
0x226ee9698  CC_SHA512_Init(&ctx)
0x226ee96a0  CC_SHA512_Update(&ctx, nameKey, nameKeyLen)
0x226ee96b0  CC_SHA512_Update(&ctx, keyMaterial, keyLen)
0x226ee96c0  CC_SHA512_Final(digest64, &ctx)
0x226ee96cc  ldr q0, [digest] ; str q0, [outKey]     ; 只取前 16 字节
（outIV 分支重复一次，把 nameKey 换成 nameIV）
0x226ee9714  把 64 字节 digest 清零
```

要点：

1. **拼接顺序是 `name || key`**，不是 `key || name`（`Update` 的先后就是它）。
2. **输出截断到 128 bit**（`ldr q0` 只搬 16 字节），但内部摘要用的是完整 SHA-512。
3. 输入 `keyMaterial` 的长度是参数，不写死；Legacy 路径传 16（A-17），屏幕路径也传 16（A-18）。
4. 两个输出可独立请求（`outKey`/`outIV` 任一为 NULL 就跳过对应分支）。
5. `ctx` 是 216 字节（`SHA512_CTX`）—— `0x226ee9620` 一次性 `sub sp, sp, #0x180` 并在
   `0x226ee9664`–`0x226ee9684` 清零整块，正好覆盖该结构。

## A-17 Legacy 路径：名字与索引

`_legacyKeyHolder_CreateDerivedAESKeyAndIVForLegacyStream`（`AirPlaySender` `0x251aa97a0`）：

```
0x251aa97d4  x8 = "AirPlayStreamKey"            ; __cstring @ 0x251c18c36
0x251aa97f0  ASPrintF(&name1, "%s%llu", "AirPlayStreamKey", index)   ; "%s%llu" @ 0x251bdf641
0x251aa97f8  x8 = "AirPlayStreamIV"             ; __cstring @ 0x251c18c47
0x251aa980c  ASPrintF(&name2, "%s%llu", "AirPlayStreamIV",  index)
0x251aa9824  createDerivedKeyLegacy(self, name1, len1, &keyData)
0x251aa983c  createDerivedKeyLegacy(self, name2, len2, &ivData)
```

`_legacyKeyHolder_createDerivedKeyLegacy`（`0x251aa9a60`）等价于通用 KDF 的「keyMaterial 固定 16 字节」版本：

```
lVar2 = CMBaseObjectGetDerivedStorage(self)      ; master key @ lVar2+0x10
buf   = CFDataCreateMutable(allocator, 16); CFDataSetLength(buf, 16)
CC_SHA512_Init(&ctx); CC_SHA512_Update(&ctx, name, nameLen)
CC_SHA512_Update(&ctx, lVar2+0x10, 0x10)         ; ← master key（16 字节）
CC_SHA512_Final(digest, &ctx)
memcpy(CFDataGetMutableBytePtr(buf), digest, 16)
```

由此**完全确定**：

```
streamKey_i = SHA512("AirPlayStreamKey" || decimal(i) || masterKey16)[0..15]
streamIV_i  = SHA512("AirPlayStreamIV"  || decimal(i) || masterKey16)[0..15]
```

`i` 的格式是**十进制无前导零**（`%llu`），因此 `i=0` → `"AirPlayStreamKey0"`。
这一点必须写死在规范里，否则拼串错一位就全盘错。

## A-18 屏幕路径：`_APSEncryptionUtilsDeriveAESKeySHA512ForScreen`（`AirPlaySupport` `0x226ee9764`）

它只是 A-16 的薄包装：自己用同样的 `"%s%llu"` 与同样的两个前缀拼名字，然后调用通用 KDF：

```
0x226ee97a4  ASPrintF(&name1, "%s%llu", "AirPlayStreamKey", param_3)   ; param_3 = 索引
0x226ee97cc  ASPrintF(&name2, "%s%llu", "AirPlayStreamIV",  param_3)
0x226ee97e0  ldp x4, x2, [sp, #0x10]     ; x4 = name2, x2 = name1
0x226ee97ec  x3 = len1 ; 0x226ee97f0 x5 = len2 ; x6 = param_4 ; x7 = param_5
0x226ee97fc  APSEncryptionUtilsDeriveAESKeySHA512(param_1, param_2, name1, len1, name2, len2,
                                                  outKey=param_4, outIV=param_5)
```

调用点（`AirPlayReceiver` `_AirPlayReceiverSessionSetup` `0x2518d4338`，调用在 `0x2518d5c30`）：

```
0x2518d5c1c  x0 = x20 + 0x160     ; 16 字节密钥材料
0x2518d5c28  w1 = 0x10            ; 长度 16
0x2518d5c2c  x2 = x19             ; 索引（u64）
0x2518d5c20  x3 = sp+0x188 (outKey)
0x2518d5c24  x4 = sp+0x178 (outIV)
0x2518d5c30  BL APSEncryptionUtilsDeriveAESKeySHA512ForScreen
```

可写结论：

- **屏幕/流密钥同样走 `AirPlayStreamKey/IV` + 索引的名字空间**，与 Legacy 完全同名同构。
- 差别只在「密钥材料」：Legacy 用 keyholder 的 16 字节 master key；屏幕路径用会话对象
  `+0x160` 处的 16 字节材料（其写入点未定位 → `OPEN-6`）。
- 因为名字空间一致，一个实现可以只写一份 KDF，两条路径共用。

整数的局部来源见A-46：Receiver先取字典整数再传给ForScreen，不是由此证明从0/1起算的本地流序号。
Legacy的同公式代码本身就在Sender，不能因为没调用Support包装器就排除发送侧使用该KDF。

## 与 ChaCha 的关系（避免误用）

`APSCryptorChaCha20Poly1305Create` 要求 **32 字节** key（A-20），而本 KDF 只产 16 字节。
本16B结果不能直接用作ChaCha key，也没有依据把key16与iv16拼接作32B key。
已核分派的ChaCha分支从keyholder class+0x38请求32B CFData（受G/type门控制，见A-44/A-45）。
应分别核验provider的算法，不从一个接口的输出长度否定上游任何可能的派生步骤。

## 复算

1. `source/asm/AirPlaySupport/f_226ee961c.s`：第 31–70 行，四个 `CC_SHA512_*` 调用与 `ldr q0/str q0`。
2. `source/asm/AirPlaySupport/f_226ee9764.s`：第 18–42 行，两个前缀地址 `0x226f51f63` / `0x226f51f74`。
3. `source/asm/AirPlaySender/f_251aa97a0.s`：第 17–43 行，`ASPrintF` 与两次派生。
4. 字面量：`read-cstr.py` 读 `0x226f51f63`→`AirPlayStreamKey`、`0x226f51f74`→`AirPlayStreamIV`、
   `0x251bdf641`→`%s%llu`。
