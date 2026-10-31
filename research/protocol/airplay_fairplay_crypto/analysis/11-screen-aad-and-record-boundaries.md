# 11 屏幕 AAD 来源与网络记录／加密段边界

范围：24A446 的 `_aprscreen_Start` 接收 block、`_aprscreen_decryptBuffer` 与
CoreUtils NetSocket。这里的屏幕记录不等于 RTP 音频消息，也不等于任意 CarPlay profile。
新增 5 份 `source/asm-audit/` 原切片；没有新增或改写 Ghidra C。

## A-34 AAD 的起点是网络读取目标，不是不可复制的内部对象

`___aprscreen_Start_block_invoke`（`0x251859c8c`）的证据链：

1. `0x251859e2c..34` 把 `_NetSocket_CreateWithNative` 的输出放到 storage+0xe8。
   CoreUtils `0x18bf1cfd8` 调用 Create，`0x18bf1cfe4` 保存 native fd。
2. `_NetSocket_Create` 在 `0x18bf1c708..714` 将 `0x18bf1c798`
   （ReadInternal）签名后放入对象+0x18，故读槽不是仅凭函数名猜测。
3. `0x25185a108..128` 取该读槽，以 min=max=128、dst=storage 读取头。
   ReadInternal 的 x1/x2/x3 分别是 min/max/dst；会先消费缓存或继续 socket 读取，
   EOF 且不足 min 时失败。因此成功路径不是只收到部分头。
4. `0x25185a150` 从 storage[0:4] 读取 LE32 的 body 长度 N；
   `0x25185a17c..19c` 再以 min=max=N 读到单独的 body 缓冲 x19。
5. type 字节 storage[4] 为 0 时走媒体路径。已核 IgnoreTimestamp 分支
   `0x25185a428..434` 到 `0x25185ab30`，未改写前128字节。
6. decryptBuffer `0x25185ba98..baa0` 仍以 storage、128 调用 add_aad。

因此，在上述路径 **AAD = 接收到的完整 128B 头 H**。客户端不需要复制 Apple 对象布局；
应保留 H 的原始字节，不能解析后归零未知字段或改写长度再用于认证。
“AAD 是空或128个零，二选一试解”及“没有该结构体无法构造”均撤回。
`_aprscreen_ntpTimestamp`（`0x25185b970`）读取 +0x80/+0x88，不构成头字段改写证据。
其他时间戳／回调路径的副作用、发送侧头构造、完整字段语义与目标车机适用性仍需核实。

## A-35 一条网络记录可包含两个独立解密段

在 type=0 路径 `0x25185ab30..abcc`：

| 原始头偏移 | 已证含义 | 使用点 |
|---|---|---|
| 0x00，4B LE | N：读入的 body 总长 | a150、ab30 |
| 0x04，1B | type；本路径要求0 | a284、ba64 |
| 0x1c，4B LE | E：可选尾段的输入长度 | ab34 |

E=0：只调用一次 decryptBuffer，输入 body[0:N]。
E>0：`subs`/`b.ls` 拒绝 E>=N，第一段 body[0:N-E]，第二段 body[N-E:N]。
这里的 N/E 是**解密前长度**，含各段自身的 tag（若 ChaCha 生效）。
不能先从 N 扣 tag 再用 E 切段。

- 第一调用在 ab80，错误直接离开；之后的 CMBlockBuffer 创建也必须成功。
- 尾指针非NULL才在 abcc 调第二次；两次都以同一 storage 头作 AAD。
- 每次完整 ChaCha 验签和输出长度检查成功，nonce 各+1；两段都成功是+2。
- 第二段错误不回滚第一段已推进的 nonce；也不能把后续对象创建失败理解成 nonce 未推进。
- 原函数对输入长度<16返回0而未认证。独立实现应先验证每段>=16；这是安全策略，
  不是固件已有的拒绝条件。长度恰好16允许进入验证（空明文+tag），不是“最短17”。

这不是网络重传协议，也不证明整条记录原子提交。独立发送端不得复用同一 key/nonce
加密不同内容。音频消息的8B AAD与这里的128B头不能混用。

## A-36 setter 不保证 CTR／ChaCha 状态互斥

两 setter 均在 storage+0xb8 或 +0xb9 非零时返回 `0xfffee645`。
ChaCha 还要求非NULL key 且长度32（否则 `0xfffee647`）。
成功后清 `[+0x160,+0x290)`、写 key 到+0x268、置+0x160；nonce+0x288因此归零。
它**不清** CTR flag+0x2c0。

AES setter 仅收尾旧 CTR、初始化+0x290并按结果写+0x2c0，**不清** ChaCha flag+0x160。
decryptBuffer 先看+0x160，仅为0才看+0x2c0；两者同时置位时优先 ChaCha。
所以不能把两个setter当自动切换模式的接口，也不能称任意重连都会归零nonce。

## 可复算与剩余边界

`reference-impl/verify_screen_aad.py` 对镜像SHA、8份相关原切片、重反汇编、关键锚点、
局部分段指令解释和合成记录负例做回归；不是完整CPU仿真或密码库互操作测试。
CoreUtils镜像/segments复用相邻 `airplay_control_plane`，导入名表来自
`firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`。
`OPEN-10` 保留真实profile、头构造及跨段互通问题，不再把AAD来源本身列为全未知。
