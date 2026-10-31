# 07 TEARDOWN

#### R-7.1 单流 teardown 请求
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A07.1`、TD-03、`0x2519ce5c4`

```text
命令: tdwn                     # 0x7464776e
载荷: { "streams": [ { "type": <raw int>, "streamID": <int> } ],
        "teardownType": <raw int> }   # teardownType 可选
```

`teardownType` 只在内部 `storage+0x10 != 0` 时出现（TD-03），本端按可选字段实现：
没有依据时**不要**硬塞 0。

#### R-7.2 顺序
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A07.2`、TD-02、`0x2519cce10`

1. 置「正在拆」标志，拒绝新的入队；
2. 从本地注册表移除该 `(type, streamID)`；
3. 组 `streams` 数组并发送 `tdwn`；
4. 释放该流的解密器、解码器、队列、端口；
5. 记录结果。

**先注销再发送**，避免发送期间又收到包而重复处理。释放必须幂等（`R-7.4`）。

#### R-7.3 不得把链路断开当对端确认
级别：MUST NOT ｜ 证据：INFERRED ｜ 依据：`A07.3`、TD-OPEN

`socket EOF`、HTTP 连接关闭、iAP2 链路断开都**不是**车机对 teardown 的确认。
没有收到回复时，状态必须是「未知/超时」，不能写「已关闭」。

#### R-7.4 幂等
级别：MUST ｜ 证据：INFERRED ｜ 依据：`A07.4`、TD-01

重复调用 teardown（同一 type+streamID）必须：

- 第二次直接返回成功，不再发 `tdwn`；
- 已释放的资源不得二次释放；
- 并发调用需要有锁/串行队列保护。

#### R-7.5 发送失败不升级为整体失败
级别：MAY ｜ 证据：INFERRED ｜ 依据：`A07.2`

固件里 sender 发送失败只记日志，整体仍可返回 0。本端可以更严格（返回失败），
但必须区分「本地清理成功」与「对端已确认」两件事，并在状态里分别记录。

#### R-7.6 整会话收尾
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A07.3`、TD-05

整个 AirPlay 会话关闭时：清空本地注册表 → 发不带 `streams` 的 `tdwn`（`teardownType=2`）
→ 再关控制连接。控制连接先断会导致 `tdwn` 发不出去；但也不要为了发它而阻塞过久，
超时地放弃并记录。

#### R-7.7 重连语义
级别：SHOULD ｜ 证据：OPEN ｜ 依据：`OPEN-TEAR-2`

断链重连后不得复用旧 `streamID`/旧密钥；必须重新 SETUP、重新派生。
`OPEN-TEAR-2` 记录：车机侧是否保留旧流、重连后旧流是否会自动过期，本阶段无证据。
