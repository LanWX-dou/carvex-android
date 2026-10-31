# 05 流类型 → 加密器：客户端要选哪一个

一句话结论：**加密器由端点属性G、keyholder存在性与type共同决定，不能仅按type选模式。**
完整表和对象门见analysis/14（A-43–A-45）；无对象不等于线上明文。

---

## A-19 分派表：`apsession_createCryptors`（内联在 `_apsession_setupStreamCreatingResponseInternal`，`0x2519bbf24`）

type来自`0x2519bca6c ldr w23,[x19,#8]`。G为端点描述属性
`SupportsCoreUtilsPairingAndEncryption`在`0x2519bca9c`的getter返回值。
假定keyholder和方法有效、调用成功时：

| type | G=0 | G≠0 |
|---|---|---|
| 96/102/103 | A=CBC | A=ChaCha(flag1) |
| 100 | A/B=NULL | A/B各ChaCha(flag1) |
| 101/106 | A/B=NULL | A=ChaCha(flag1) |
| 107 | A/B=NULL | B=ChaCha(flag1) |
| 110/111 | A=CTR | A=ChaCha(flag0) |
| 120/130 | A/B=NULL | A/B=NULL |

未列的槽为NULL。其他type在到达分派时进入`0xfffee76f`；此前keyholder门可早退（A-45）。
A/B只是出参槽，不叫主备；这里没有证明同帧序号。NULL不是GetNull单例，也不证明无外层加密。
历史OPEN-7的属性名已关闭；属性能力来源与目标profile仍需核，不可当本地任意配置。

> 注意：类型码的**语义名字**（哪个是视频、哪个是音频）本阶段**没有**固件证据可以断言。
> 能断言的是「码 → 行为」这一张表。语义名字留 `OPEN-8`，需靠实测（发哪个码，车机建哪种会话）确认。

## A-20 加密器构造约束（`AirPlaySupport`）

| 构造器 | 地址 | 入参 | 约束（字节级） |
|---|---|---|---|
| `APSCryptorChaCha20Poly1305Create` | `0x226f2f54c` | `(alloc, CFDataRef key, Boolean flag, &out)` | `key != NULL`；`CFDataGetLength(key) > 0x1f` 即 **≥ 32 字节**，否则返回 `0xfffee7e1`（内部 `0x98`）；key 被 `CFRetain` 存到 storage `+0x108`；`flag` 存 `+0` |
| `APSCryptorCTRCreate` | `0x226e8d208` | `(alloc, CFDataRef key, CFDataRef iv, &out)` | key、iv 都不能为 NULL（否则 `0xfffee7e1`，行 `0x83`/`0x84`）；`AES_CTR_Init(storage, keyPtr, ivPtr)` |
| `APSCryptorCBCCreate` | `0x226efbecc` | `(alloc, CFDataRef key, CFDataRef iv, &out)` | key、iv 都不能为 NULL；**建两个上下文**：`AES_CBCFrame_Init(storage, key, iv, 1)`（加密）与 `AES_CBCFrame_Init(storage+0x18, key, iv, 0)`（解密） |
| `APSCryptorGetNull` | `0x226e83b30` | — | 进程级空加密器单例；本次分派切片未调用它，不能据此把任何type命名为明文 |

AES构造器本身只查非NULL；后续CoreUtils核验（A-42）已证两种Init固定传keyLength16、复制IV16B。
本包装器没有192/256选项；历史OPEN-9关闭。独立API应严格校验长度，不照搬未校验缓冲行为。

## 相关原语（供实现者对齐命名）

`AirPlaySupport` 直接导入的 CoreUtils 符号（A-03 的桩表）：

```
_AES_CTR_Init / _AES_CTR_Update / _AES_CTR_Final
_AES_CBCFrame_Init / _AES_CBCFrame_Update / _AES_CBCFrame_Final
_chacha20_poly1305_init_64x64 / _chacha20_poly1305_add_aad /
_chacha20_poly1305_encrypt / _chacha20_poly1305_decrypt / _chacha20_poly1305_verify
```

`chacha20_poly1305_init_64x64` 的名字说明是 **64-bit nonce + 64-bit counter** 变体，
这与A-23观察到的8B nonce每成功段自增相呼应；完整MAC编排与替代库兼容性仍待闭合，不只靠名字保证。

## 复算

- `readable/ghidra/AirPlaySender/f_2519bbf24.ghidra.c` 第 560–800 行（分派表逐个分支）。
- `readable/ghidra/AirPlaySupport/f_226f2f54c.ghidra.c` 第 26–33 行（`0x1f` 比较与 `0x98` 错误码）。
- `f_226e8d208.ghidra.c` 第 36–43 行（CTR：两次 `CFDataGetBytePtr` + 一次 `AES_CTR_Init`）。
- `f_226efbecc.ghidra.c` 第 37–47 行（CBC：两个上下文，方向参数 1 与 0）。
