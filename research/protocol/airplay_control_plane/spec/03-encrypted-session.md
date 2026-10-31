# 03 · 加密会话

## 3.1 何时开始

- R-3.1 设备在 Pair-Verify 成功后具备配置控制面加密的条件；本构建的密钥装配路径要求读写密钥就绪，但**切换发生在 M3/M4、下一条业务请求前还是其它边界，仍由 `OPEN-AP-23` 限定**。实现不得把“Verify 成功”单独当作已证明的线上切换时刻（`A03.8`、`A04.1`）。
- R-3.2 配对消息内的 TLV 级加密与外层传输 AEAD 是两层不同处理；不能因存在 TLV 加密就断言全部配对消息都在外层明文发送。加密起始消息，尤其 M3/M4 的边界仍为 `OPEN-AP-23`。

## 3.2 密钥

- R-3.3 控制通道读写密钥**必须**各 ≥32 字节，来自 `Control-Salt` + `Control-Read/Write-Encryption-Key`（`A04.1`、`A04.2`）。
- R-3.4 事件通道用 `Events-Salt` + `Events-Read/Write-Encryption-Key`；数据流用 `DataStream-Salt` + `DataStream-Input/Output-Encryption-Key`；三类**不得**互换（`A04.3`）。
- R-3.5 客户端应把密钥绑定到当前连接/流上下文并在新连接重新派生；现有指令只显示连接上下文初始化路径，未单独证明所有实现都禁止外部缓存复用，因此不得把“绝不跨连接复用”扩写成固件全局规则（`A04.1`、`A04.3`；连接绑定为本地策略）。

## 3.3 记录格式

- R-3.6 本构建记录为 `u16 小端密文长度` + 密文 + `16` 字节标签；Read 在长度 **>16384** 时拒绝，WriteV 一次最多聚合 **1024** 字节。它们是本构建本地边界，不是所有车机的统一上限（`A12.6`、`A13.5`）。
- R-3.7 复现本构建记录层时，AAD 必须是线上原样的两个 LE16 长度字节；读写各用独立 8 字节小端 nonce，直接传入 `init_64x64`，不再拼接记录计数器。APTransport 已核配置分支初值为零；读验证成功并核对输出长度后递增，写生成密文/tag 并核对长度后递增（早于 socket 发送完成）。部分写须继续发送缓存的同一密文记录，不能重新加密或再次递增（`A13.1`、`A13.2`）。
  认证输入为 `H || zero[14] || C || zero[(-len(C)) mod 16] || LE64(2) || LE64(len(C))`，其中 `H=LE16(len(C))`；实现不得仅凭库支持 8 字节 nonce 就认定 tag 编排兼容。禁止 key/nonce 重用、耗尽前重建会话为本地安全策略。结构模型见 `reference-impl/record_layout.py`，它不执行 AEAD 或证明互通。
- R-3.8 标签验证成功前不得发布原地解密产生的明文。tag 不符返回 `-0x1a62`，输出长度不符为 `-0x1a6a`，超长为 `-0x1a57`，不得混同。失败后不得仅因 nonce 未推进就自动重试同一记录；底层函数未关 socket，上层断开/恢复时机仍为 `OPEN-AP-42`（`A13.5`）。

## 3.4 失败

- R-3.9 在调用本构建的加密配置路径时，任一方向密钥缺失或长度不足必须拒绝该次加密配置（`A04.1` 的 `>= 0x20` 检查）；这条指令证据不能单独推出所有失败场景都立即关闭底层连接。
- R-3.10 Configure 第3/5参数分别是本地read/write密钥，第4/6为可选nonce8。已核CoreUtils key holder的Ctrl上下文中，IsServer=0时本地read使用Control-Read标签、write使用Control-Write标签；IsServer非零则交换。IsServer与IsListener不是同一选项，目标调用者/provider选择仍由 `OPEN-AP-40` 限定（`A13.3`、`A15.1`、`A15.2`）。
- R-3.11 对已核CoreUtils pairing provider中使用 `sess+0x28e` 共享秘密的分支，控制方向密钥为 `HKDF-SHA512(shared_secret32, Control-Salt, Control-Read/Write-Encryption-Key, 32)`，标签不含末尾NUL，不能改用配对TLV加密密钥作为输入。必须满足该provider内部派生门：type3/4要求state5，type5/6要求state3；type1/2另需state7及非空可变长材料。这些是本构建内部状态，不是可直接填入线上TLV的值；其它provider/目标profile仍见 `OPEN-AP-22`（`A15.3`）。
