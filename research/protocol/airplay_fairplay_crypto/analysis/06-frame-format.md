# 06 帧格式：CBC-frame / CTR / ChaCha20-Poly1305

一句话结论：**ChaCha加密段为密文+16B tag，已核屏幕AAD为128B网络头，可含双段；CTR保留连续密钥流；CBCFrame每次Update重置初始IV、尾部直通。** 见analysis/11、13；实际profile与真实互通仍未闭合。

---

## A-21 会话级 AES = CBC-frame（接收侧 `__SetSecurityInfoAES` `0x2518d3bdc`）

```
AES_CBCFrame_Final(session+0x140)                 ; 若已有上下文，先收尾
AES_CBCFrame_Init(session+0x140, key, iv, 0)      ; 方向参数 = 0（解密方向；加密方向在 A-20 里是 1）
session+0x158 = &session+0x140                    ; 保存上下文指针
session+0x160..0x16f = key[16]                    ; 拷贝 key
session+0x170..0x17f = iv[16]                     ; 拷贝 iv
```

与 A-20 的 `APSCryptorCBCCreate` 对照：那里同一个 key/iv 建了 **两个**上下文
（`+0x18` 偏移、方向 1 与 0），这里只建解密方向。两者一致地说明：CBC 的加/解密上下文是分开建的。

后续已补CoreUtils原实现（A-40）：每次Update使用保存的初始IV重置，并将不足16B尾部直通。
历史OPEN-11库级语义关闭；不能用上一调用末块链接，也不能把任意网络分片当Update边界。

## A-22 屏幕级：CTR 与 ChaCha 的并存（接收侧 `_aprscreen_SetSecurityInfo*`）

| 函数 | 地址 | 动作 | 状态位 |
|---|---|---|---|
| `_aprscreen_SetSecurityInfoAES` | `0x251859b8c` | 若 `+0x2c0` 已置则收尾旧CTR；初始化新CTR | 仅初始化成功置 `+0x2c0 = 1`，失败为0 |
| `_aprscreen_SetSecurityInfoChaCha` | `0x251859a60` | 要求 key 长度**恰好 0x20**（否则 `0xfffee647`）；把 `+0x160` 起 0x130 字节清零；把 32 字节 key 写到 `+0x268..+0x287` | `+0x160 = 1` |

两setter均有+0xb8/+0xb9状态门，且**不清另一模式flag**，不能称互斥模式切换。
两flag均置位时解密优先ChaCha，详见A-36。

`+0x288` 起 8 字节是 **nonce 计数器**，成功调用ChaCha setter后为0；不推广到任意重连。

## A-23 屏幕帧解密：`_aprscreen_decryptBuffer`（`0x25185ba2c`）——ChaCha 帧格式的完整证据

```
if (buf == NULL || session[4] != 0) return 0;      ; 不处理；session此处表示derived storage
if (session+0x160 != 0) {                          ; ChaCha 模式
    if (len < 16) return 0;                        ; 0x25185ba78..7c → bb5c；不改 *len
    payloadLen = len - 16;                         ; tag 占尾部 16 字节
    chacha20_poly1305_init_64x64(ctx=+0x168, key=+0x268, nonce=+0x288)   ; 0x25185ba90
    chacha20_poly1305_add_aad(ctx, session, 0x80)                        ; 0x25185baa0（x1=structure base, w2=0x80）
    off = chacha20_poly1305_decrypt(ctx, buf, payloadLen, buf)           ; 0x25185bab4（原地）
    chacha20_poly1305_verify(ctx, buf+off, buf+payloadLen, &err)         ; 0x25185bacc
    if (err != 0) return err;                     ; 不推进nonce，不保证缓冲尚未改写
    if (off + verify_len != payloadLen) → 0xffffe596
    8 字节小端自增：for (i=0;i<8;i++) if (++nonce[i]) break;             ; 0x25185baf0..0x25185bb10
}
else if (session+0x2c0 != 0) {                     ; CTR 模式
    AES_CTR_Update(+0x290, buf, len, buf);         ; 0x25185bb30（原地，长度不变）
}
else { *len 不变，返回 0 }                          ; 未启用加密状态，原样返回
```

可以写进规范的字节布局（单次调用的ChaCha加密段，不是整条网络记录）：

```
frame = candidate_ciphertext(payload, key, nonce) ‖ tag(16)
payloadLen = frameLen - 16
AAD = 已核路径的128B原始网络头（A-34）
nonce = 8 字节小端计数器，成功设置后从0开始，每段验签和长度检查成功后+1
```

三条必须写死的细节：

1. **tag 在尾部**，且长度固定 16；`frameLen < 16` 返回 0，未修改输出长度。是否丢帧/统计是调用者行为，不能由本函数推出。
2. **nonce 是 8 字节计数器而不是随机数**，且只在验签成功后才自增（失败帧不会推进计数器，
   下一次调用仍使用同一计数器值；这不证明有重传机制，也不授权发送端用同一 key/nonce 加密不同明文）。
3. **原地解密**：`dst == src`，实现时不要假设有独立输出缓冲。

AAD 参数确实是storage起点和0x80，但接收循环先向这里完整读入网络头（A-34）。
因此应保留头的原始字节，不使用零AAD。A-35还证明一条记录可能调用两次解密，成功时nonce共+2。
`OPEN-10`收窄为头构造、其他profile/回调路径及真实跨段互通；不再声称必须有内部对象才能构造AAD。

调用点未显式传入 ChaCha 初始 block counter，不能把它写死为 0。tag 验证失败返回库写入的错误（`0x25185bad4`–`0x25185bb80`）；仅长度不匹配分支显式写 `-0x1a6a = 0xffffe596`（`0x25185bb9c`）。没有库内部证据时，两类错误不得混写成同一码。

## 与 AES-CTR 的对比

| 维度 | AES-CTR（屏幕） | ChaCha20-Poly1305（屏幕） |
|---|---|---|
| key | 16 字节 | 32 字节（严格校验） |
| 每次处理参数 | 连续计数器流，长度不变 | 8B nonce，每个验签及长度检查成功的加密段+1 |
| 完整性 | 无（靠上层） | 尾部 16 字节 tag |
| 帧长关系 | `outLen == inLen` | `outLen == inLen - 16` |
| 原地 | 是 | 是 |

## 复算

- `source/asm/AirPlayReceiver/f_25185ba2c.s`：`0x25185ba90`（init）、`0x25185baa0`（add_aad）、
  `0x25185bab4`（decrypt）、`0x25185bacc`（verify）、`0x25185baf0`–`0x25185bb10`（计数器自增）。
- `source/asm/AirPlayReceiver/f_251859b8c.s` / `f_251859a60.s`（两种设置）。
- `source/asm/AirPlayReceiver/f_2518d3bdc.s`（CBC-frame 设置）。
