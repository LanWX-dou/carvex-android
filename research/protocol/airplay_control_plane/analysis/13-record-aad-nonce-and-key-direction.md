# 13 · 控制记录 AAD、nonce 与方向（24A446 静态复核）

本章依据原始 CoreUtils/APTransport 指令及符号表；不是抓包或设备互通报告。
原有三条传输函数仍在 `source/asm/CoreUtils/`；另从同一镜像导出九个密码包装函数到
`source/asm-audit/CoreUtils/`，没有修改已有证据文件。选择文件为 `tools/crypto-audit-selection.json`。

## 13.1 长度前缀是 AAD（A13.1）

不能把 `0x18be4d754` 的调用解释为“写出长度”：目标 `0x18be48df8` 是 `_poly1305_update`，
不是 socket write。读写端分别执行以下链：

| 路径 | 初始化 | 认证前缀 | AAD 字节计数 |
|---|---|---|---|
| Read | `0x18be49a84..94`，AEAD ctx=`base+0x4050` | `0x18be49a98..aa8`：Poly1305 ctx=`base+0x40d8`，data=`base+0x28`，len=2 | `0x18be49aac..ab4`：`base+0x4138 += 2` |
| WriteV | `0x18be4d724..38`，AEAD ctx=`base+0x45a0` | `0x18be4d744..54`：Poly1305 ctx=`base+0x4628`，data=`base+0x4178`，len=2 | `0x18be4d758..60`：`base+0x4688 += 2` |

两者都是 AEAD ctx 的 `+0x88` Poly1305 状态与 `+0xe8` AAD 长度。
独立的 `_chacha20_poly1305_add_aad`（`0x18be48ef0..f24`）执行同样两步，确认这里是内联 AAD 操作。
因此 AAD 是**线上原样的两个小端长度字节**，不是十进制文本，也不含整个 RTSP 头。

后续 encrypt/decrypt（`0x18be4d1f4` / `0x18be4b298`）首次处理内容前按 AAD 长度模 16 补零；
final/verify（`0x18be4d06c` / `0x18be4b330`）认证密文尾部补零及两个 LE64 长度。
补零地址 `0x18bf711b4` 的原始 64 字节为零。认证输入可写为：

```text
H = LE16(len(C))
Poly1305_input = H || zero[14] || C || zero[(-len(C)) mod 16]
                || LE64(2) || LE64(len(C))
record = H || C || tag[16]
```

这里只确定认证输入编排，不靠一个兼容库自我回环来证明真实密钥或互通。

## 13.2 两个独立的 8 字节 nonce 状态（A13.2）

`__NetTransportRead` 用 `base+0x4170`，`__NetTransportWriteV` 用 `base+0x46c0`，
两者都直接作为第三实参传给 `_chacha20_poly1305_init_64x64`（`0x18be4a104`）。
此函数将 nonce 的两个 32 位字存到 ChaCha 状态 `+0x38/+0x3c`，而 `+0x30` 的独立 64 位
block counter 被置零（`0x18be4a174..198`）；不是“8 字节基准值再拼另一个记录计数器”。

- 读：只有 tag 验证和输出长度匹配成功，才在 `0x18be49b00..18` 小端带进位加 1，再发布明文区间。
- 写：密文/tag 生成与长度校验成功后，在 `0x18be4d820..38` 加 1，**早于 socket 写完**；
  `+0x4590/+0x4598` 保存待发送密文区间，部分写后续发送同一记录，不应重新加密或再推进 nonce。
- 初值来自 Configure 的可选指针；APTransport 两条已读分支都传 NULL。
  Configure 使用 `_malloc_type_calloc`（stub `0x1900cc460`），所以这些路径的初始状态为零。
  stub 名称可复核 `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`。
- 固件循环最多传播 8 字节，算术可回绕；独立客户端应在状态耗尽前重建安全会话，
  禁止同一 key/nonce 加密不同明文。拒绝回绕是本地安全策略，不是此函数已实现的检查。

这里的 64-bit **记录 nonce** 与 ChaCha 的 **block counter** 是两个变量；不得混用。
也不代表所有媒体流都复用这套记录规则。

## 13.3 Configure 的六个参数与角色交换（A13.3）

`_NetTransportChaCha20Poly1305Configure`（`0x18bf1adbc`）可复核为：

```text
Configure(outTransport, logCategory, readKey32, optionalReadNonce8,
          writeKey32, optionalWriteNonce8)
```

| 实参 | 保存到新分配对象 | 实际消费者 |
|---|---|---|
| x2（第 3 参数） | `+0x4150..+0x416f` | Read 初始化密钥 |
| x3 | `+0x4170..+0x4177`，NULL 则保持 calloc 的零 | Read nonce |
| x4（第 5 参数） | `+0x46a0..+0x46bf` | WriteV 初始化密钥 |
| x5 | `+0x46c0..+0x46c7`，NULL 则保持零 | WriteV nonce |

证据为 `0x18bf1add8..e8` 保存寄存器、`0x18bf1ae34..60` 拷贝与前两节消费者。
APTransport `f_24fdc97e8.s` 调 Configure 的 stub 为 `0x2500ef300`；上游 key holder 的两个输出
暂记 `K_A=[fp-0x28]`、`K_B=[fp-0x30]`：

| 内部 `obj+0x100` | 传给 readKey | 传给 writeKey | 地址 |
|---|---|---|---|
| 非零 | K_B | K_A | `0x24fdc98f4..0x24fdc9924` |
| 零 | K_A | K_B | `0x24fdc99a8..0x24fdc99d8` |

后续 `A15.1`–`A15.3` 已确认该flag为 **IsServer**，在CoreUtils key holder的Ctrl上下文中
K_A/K_B分别使用Read/Write标签；非服务器本地read=Read、write=Write，服务器交换。
派生输入/状态门见 [analysis/15](15-keyholder-role-and-hkdf.md)。剩余为目标CarPlay调用者的provider/角色选择，
不能扩写成“所有手机通道永远用同一个方向”。

## 13.4 配对包装器按 nonce 长度选择变体（A13.4）

`__chacha20_poly1305_encrypt_all`（`0x18be55eec`）：
`0x18be55f5c..84` 分别比较 12/8；8 字节直接调用 init_64x64，12 字节才调用 init_96x32。
decrypt_all（`0x18be578a4`）在 `0x18be57914..3c` 对称分派。
因此已核 Setup M5 传入的 `PS-Msg05` 8 字节直接占 nonce64，不存在右补零的中间步骤。

本函数也显式认证 `AAD || pad16 || C || pad16 || LE64(aadLen) || LE64(cipherLen)`。
不能因为两个 API 都接受 8 字节 nonce 就假定兼容，尤其不能直接套历史非 IETF AEAD 的另一种 tag 编排。
本章不提供“任意库可以直接替换”的结论；替代库适配仍需独立密码向量与目标会话对照。

`OPEN-AP-43` 的“包装器是否补零”子问题已关闭；不同配对分支的具体调用者、库适配与互通仍须分别核实。

## 13.5 长度门、错误与未认证明文（A13.5）

读路径 `cmp #0x4000; b.hi` 明确是 **大于 16384 才拒绝**，16384 可通过该门；
写路径一次聚合最多 `0x457a-0x417a=1024` 字节，并非全方向 16384。
这些是此构建本地边界，不是所有车机接受上限。

verify 函数将计算 tag 与输入 16 字节 tag 做 XOR/归约，非零写 `-0x1a62 = 0xffffe59e`
（`0x18be4b470..490`）；Read 输出长度不匹配另返回 `-0x1a6a`，超长返回 `-0x1a57`。
错误码来自不同判断，不应合并为“认证失败码”。

Read 会先原地解密，再 verify；**验签之前内存里已有明文不等于可交给业务**。
发布读区间及推进 nonce 在成功分支之后。该函数本身不关闭 socket，认证失败后也没有进入“安全重试同记录”状态；
不得将 nonce 未推进推断为允许自动重传。上层断开/恢复仍为 `OPEN-AP-42`。

## 13.6 回归与范围

`tools/verify-crypto-audit.py` 核对新增切片与原镜像逐字节一致、符号/指令锚点、零填充常量及
`reference-impl/record_layout.py` 的结构反例。后者只构造认证输入/记录几何，**不实现 AEAD**。
通过这些检查不表示执行了固件密码函数，更不表示与车机完成配对或认证。
