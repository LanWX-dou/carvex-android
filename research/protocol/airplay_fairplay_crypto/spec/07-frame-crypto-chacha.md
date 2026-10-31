# spec 07 ChaCha20-Poly1305 帧（屏幕流）

这是本阶段**字节级最完整**的一段：帧布局、tag 位置、nonce 演进有较强指令证据；库 ABI 与线上互操作仍需真实样本闭合。

## R-7.1 单个加密段布局

本节的frame指一次decryptBuffer输入的加密段，**不等于一条网络记录**（见R-7.8）。

```
frame = C ‖ T
C = ChaCha20(key, nonce, counter).keystream XOR P      // 长度 = len(frame) - 16
T = Poly1305 tag                                       // 固定 16 字节，位于帧尾
payloadLen = frameLen - 16
```

- `frameLen < 16` 时本函数返回 0，输入缓冲和输出长度不变；不能据此推断调用者会丢帧或不计统计。独立实现应另设短帧校验，避免把这种返回值当作认证成功。
- 解密后长度 = `frameLen - 16`；**没有任何填充**。
- 原地解密（`dst == src`）。
依据：A-23（`0x25185bab4` 前后：`len-16`、`buf+payloadLen` 指向 tag、verify 后校验
`off + verifyOutputLen == payloadLen`；只有长度不匹配显式设置 `0xffffe596`，tag 失败传播库错误）。级别：A。

## R-7.2 算法变体：**64-bit nonce + 64-bit counter（强线索，待互操作闭合）**

`chacha20_poly1305_init_64x64` 的命名与「8 字节 nonce」用法是强线索，但只有确认目标库 ABI、nonce 编码和 counter 语义后，才能称为完整互操作算法。

> 8 字节 nonce 不能直接传给要求 12 字节的 IETF API。也不能仅因非 IETF API 接受 8 字节 nonce 就认定其 Poly1305 编排与目标库一致；需比对 padding、长度认证和 block counter 的独立向量。当前没有确认可直接替换的库 API。
依据：A-20（`0x226f2f54c` 与桩名）、A-23（`+0x288` 处 8 字节计数器）。级别：A（目标库/调用约定线索；算法闭合仍 OPEN）。

## R-7.3 nonce = 8 字节小端计数器，从 0 开始

```
nonce = 0x0000000000000000        // 8 字节全零
每个加密段成功解密、验签并通过输出长度检查后：
for (i = 0; i < 8; i++) { if (++nonce[i] != 0) break; }   // 小端自增，带进位，回绕
```

- 成功设置 ChaCha 安全信息时清零状态区（`+0x160` 起 `0x130` 字节），此时nonce为0；不代表任意重连自动归零。
- 计数器是**每成功加密段+1**，两段记录可+2；不是每记录一次，也不是按字节偏移。
- 验签失败时**不**自增；这只证明本地状态保留，不证明协议有重传。发送端不得用同一 key/nonce 加密不同明文；计数器耗尽前应停止或重建密钥上下文。
依据：A-22（清零范围）、A-23（`0x25185baf0`–`0x25185bb10` 的 8 字节循环自增）。级别：A。

## R-7.4 AAD

已核type=0接收路径先完整读取128B网络头H到storage起点，再将该区域作为AAD。
因此AAD是H的原始字节，不是空串、128个零或内部指针；两段记录的两次调用使用同一H。
不要解析后重建、归零未知字段，或将N/E改成明文长度后认证。其他回调路径与目标profile适用性仍为`OPEN-10`。
依据：A-23、A-34（读槽构造、min=max=128、dst=storage、add_aad）、A-35。级别：A（限定已核路径，非跨profile保证）。

## R-7.5 失败处理

| 情况 | 处理 |
|---|---|
| `frameLen < 16` | 函数不处理，`*outLen` 不变，返回 0；调用者是否丢帧未证 |
| tag 校验失败 | 传播验证库写入的错误，**不推进 nonce**；本函数不能证明固定错误值 |
| 解密长度与声明不符 | `0xffffe596` |
| ChaCha 状态未启用且 CTR 状态也未启用 | 函数返回成功、`*outLen` 保持不变；这只能称为“未加密/未处理路径”，不是已证明的线上明文协商 |

依据：A-23、A-22。级别：A。

## R-7.6 key 长度

屏幕setter要求非NULL且**恰好32B**，不符返回0xfffee647。
另一个APSCryptor构造器只检查CFData长度>=32，不能把其`>0x1f`比较误写成严格相等。
独立客户端对本屏幕接口固定32B；较长CFData被构造器接受不证明更长ChaCha密钥变体。
依据：A-20、A-22/A-36。级别：A（区分两个接口的检查条件）。

## R-7.7 参考实现与向量

`reference-impl/fairplay_crypto.py` 提供**候选**seal/open，要求显式AAD；R-7.2库语义和真实互通仍未闭合。
`screen_record_layout.py`仅切分已证头/段边界，不生成可直接发送的完整协议头。
`runtime/vectors/chacha.json`有6组合成向量，包含非零128B头的两段记录和空明文；旧零/空AAD仅保留为候选算法自检。
`runtime/vectors/negative.json`有4个负例：错key、错nonce、改tag末字节、短段。
依据：`runtime/vectors/`、`reference-impl/`。级别：C（候选实现，可复现但不等于线上兼容）。

## R-7.8 记录级分段

已核路径：H长128，N=LE32(H[0:4])，type=H[4]=0，E=LE32(H[28:32])。
body长N。E=0时单段；0<E<N时分为body[:N-E]与body[N-E:]；E>=N且非零被拒绝。
N/E含各段tag，分段须在解密前完成。第一段错误或中间对象创建失败不会调用第二段。
两次都完成ChaCha验证时nonce+2；第二段失败不回滚第一段状态。
独立实现应预先检查每段至少16B、精确body长度及配置的资源上限；这些检查是本地安全策略，不冒充固件全部现有检查。
依据：A-35（`0x25185ab30..abcc`）、A-23。级别：A（分段与推进）；本地安全策略另标。

## R-7.9 安全信息设置与优先级

两个setter均受storage+0xb8/+0xb9状态门限制。ChaCha setter仅成功后清其状态并归零nonce；
AES setter仅按CTR初始化结果置flag。两者不清对方flag，不能用它们保证模式互斥切换。
decryptBuffer先检查ChaCha，未启用才考虑CTR；两flag都置位时选择ChaCha。
依据：A-22、A-36。级别：A。
