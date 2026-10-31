# spec 04 密钥派生（SHA-512 KDF）

本节给出已有指令证据的KDF公式；可独立实现公式，不代表已确认目标profile的输入来源和选择条件。

## R-4.1 定义

```
KDF(K, nameKey, nameIV) -> (key16, iv16)
key16 = SHA-512(nameKey ‖ K)[0..15]
iv16  = SHA-512(nameIV  ‖ K)[0..15]
```

- 拼接顺序：**名字在前、密钥在后**。
- 摘要算法：标准 SHA-512（64 字节），取**前 16 字节**。
- 两个输出可独立求（只给一个名字就只算一个）。
依据：A-16（`0x226ee961c`，`CC_SHA512_Update(name)` 在 `Update(key)` 之前；`ldr q0/str q0` 只搬 16 字节）。级别：A。

## R-4.2 名字的拼法（写错必错）

```
nameKey = "AirPlayStreamKey" + decimal(i)
nameIV  = "AirPlayStreamIV"  + decimal(i)
```

- 前缀是**纯 ASCII、大小写敏感**：`AirPlayStreamKey` / `AirPlayStreamIV`。
- 索引用 `%llu` 格式化：**十进制、无前导零、无分隔符**。`i=0` → `"AirPlayStreamKey0"`。
- 名字长度不固定（随 `i` 的位数变化），KDF 接受显式长度。
依据：A-17（前缀常量 `0x251c18c36`/`0x251c18c47`，格式串 `%s%llu` @`0x251bdf641`；`0x226f51f63`/`0x226f51f74`）。级别：A。

## R-4.3 密钥材料 `K`

| 场景 | `K` | 长度 | 证据 |
|---|---|---|---|
| AirPlaySender中的Legacy keyholder | master key（`storage+0x10`） | 16 | A-11、A-17、A-46 |
| 车机屏幕会话建立 | 会话对象 `+0x160` 处材料 | 16（硬编码 `w1=0x10`） | A-18、`OPEN-6` |

`K` 的来源不同，但**派生公式与名字空间完全相同**——一份实现可以复用。
依据：A-17、A-18。级别：A（公式）/ C（屏幕材料来源）。

## R-4.4 整数 `i` 的来源

`i` 是传给派生函数并按无符号64位十进制格式化的整数；不能仅因文档称其“索引”就假设它是从0/1递增的流序号。
已核Receiver入口先取字典整数，再把原值送给KDF；本轮未闭合该字段的发送/接收全链。
独立实现应保留实际协商值；来源未证时应标未支持，不能用可配置0/1替代协议取值。
依据：A-17、A-46、`OPEN-15`。级别：A（传值/格式）；来源/profile仍OPEN。

## R-4.5 发送侧的适用范围不能仅由直接调用点决定

Sender的Legacy实现已直接证明同一公式：`0x251aa97a0`拼两个名字并两次调用
`0x251aa9a60`；后者直接执行SHA-512(name || masterKey16)，截取16B到CFData。
它不必调用Support的同名工具函数。因此旧稿“发送侧不用该KDF”与正面证据矛盾，撤回。
本分派从keyholder provider取得CFData；应区分Legacy的已证公式与目标会话实际选择哪个provider，后者仍需绑定。

因此：

- 客户端可实现该Legacy KDF，但不把它用于未经确认的CoreUtils/ChaCha路径。
- 已知 `K` 与 `i` 时仍可用它验证车机侧派生是否一致，但这不是线上使用该KDF的证明。
依据：A-17、A-31、A-46、A-44。级别：A（Legacy公式）；目标profile/provider选择未闭合。

## R-4.6 与 ChaCha 的隔离

本 KDF 只产 16 字节，而 ChaCha 要求 ≥32 字节 key。**不得**把 `key16‖iv16` 拼成 32 字节当 ChaCha key
（无法由该 KDF 推出所需 32 字节密钥；不能据此宣称兼容，也不能预测对端固定返回某错误码）。
依据：A-20、A-23。级别：A。

## R-4.7 自检向量

`runtime/vectors/kdf.json` 含 3 组向量（不同 `i`、不同 `K`），由 `reference-impl` 生成并经第二实现
（独立写的纯 Python `hashlib` 计算）交叉核对。`verify.py` C6 会重跑。
依据：`runtime/vectors/kdf.json`、`reference-impl/fairplay_crypto.py`。级别：A（可复现）。
