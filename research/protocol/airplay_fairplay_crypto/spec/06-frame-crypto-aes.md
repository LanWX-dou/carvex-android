# spec 06 AES 帧（CTR 与 CBC-frame）

## R-6.1 AES-CTR：等长、原地、计数器与剩余密钥流连续

```
AES_CTR_Update(ctx, buf, len, buf)     // dst == src，len 不变
```

- **不**为每帧重设 IV；计数器在上下文里连续推进。
- 输出长度 == 输入长度，没有 tag、没有填充。
- 计数器为128位大端，每生成16B密钥流后+1；不足一块也推进，并保留未消费密钥流及偏移供下一调用。
- 任意分块输入应等价于同上下文一次输入拼接数据。不要每个网络分片/媒体段重新传IV新建对象。
- 原固件允许计数器回绕；独立实现应在重复使用计数器前停止/换key，参考实现的耗尽拒绝是本地安全策略。
依据：A-22、A-41（CoreUtils原函数与两处进位循环）。级别：A（状态行为）；耗尽拒绝为本地策略。

## R-6.2 AES-CTR 的初始化点

已核屏幕setter在其状态门允许时，若CTR已启用先Final再Init；成功置CTR flag，失败不置。
它不清ChaCha flag，不保证调用后解密选择CTR；不能从本setter推广全会话只初始化一次。
依据：A-22、A-36。级别：A。

## R-6.3 AES-CBC-frame：逐调用重置IV，整块加密，尾部直通

- 每次Update：`full=len & ~15`；full>0时CCCryptorReset使用初始化保存的IV，再以无填充CBC处理full字节。
- 正常库输出长度为full，尾部len%16字节原样复制；长度<16时整段直通，长度0无输出。
- 不链接上一调用末密文、不填充、不做ciphertext stealing；Final只是释放和清零，不输出额外块。
- 本函数按库返回moved推进拷贝指针，没有额外验证moved==full；库错误直接返回，不能保证输出未改动。
- “一次Update”的输入边界须按具体媒体调用者确定，不可自行按TCP分片切开，亦不能把多记录随意合并。
依据：A-40、A-42。级别：A（原函数与公开CommonCrypto契约）；历史OPEN-11的库级语义已关闭，网络profile仍待核。

## R-6.4 会话级（非屏幕）加密用 CBC，且只用解密方向

`__SetSecurityInfoAES` 建的是 `dir=0`（解密）上下文，并把 key/iv 各 16 字节拷贝进会话对象
（`+0x160`/`+0x170`）。
依据：A-21（`0x2518d3bdc`）。级别：A。

## R-6.5 key/iv 长度

本次两个CoreUtils Init都固定给CCCryptorCreate传keyLength=16，并复制IV16B；不提供AES192/256选择。
上层构造器只检查非NULL不等于长度安全；独立客户端应要求精确16/16B，不模拟短缓冲读取风险。
依据：A-20、A-42。级别：A（本包装器固定大小）；历史OPEN-9关闭，不推广其他API。

## R-6.6 失败表现

| 现象 | 含义 |
|---|---|
| 首帧就全乱码 | 检查 key/iv、模式、索引和数据边界；不能单凭现象定位 |
| 第 2 帧起乱码 | 检查跨帧状态、IV、丢包和帧边界；不能断言必为 CBC 链接问题 |
| 长度变化 | CTR等长；成功ChaCha每段减16；本CBCFrame正常路径等长、尾部直通，无填充 |

依据：A-21、A-23、A-19。级别：B（经验判据，非固件直证）。

## R-6.7 命名对照（便于与 CoreUtils 对齐）

```
AES_CTR_Init / Update / Final
AES_CBCFrame_Init(key, iv, dir) / Update / Final
```

CBCFrame的dir非零映射CCCryptorCreate operation0（加密），dir=0映射operation1（解密）；已核调用者传1/0。
本地Final不是CCCryptorFinal：只释放句柄并清零状态。
依据：A-40、A-42及公开CommonCrypto接口。级别：A。
