# 07 TEARDOWN

## 7.1 两级收尾

| 级别 | 消息 | 载荷 | 证据 |
|---|---|---|---|
| 单流 | `tdwn`（`0x7464776e`） | `{streams: [ {type, streamID?} ], teardownType: <raw int>}` | `INFERRED` TD-03 |
| 整会话 | 同一命令，无 `streams`，`teardownType=2` | 清本地注册表后再发 | `INFERRED` TD-05 |

`teardownType` 只在 `raw storage+0x10 != 0` 时插入（TD-03），所以它**不是必填**；
把字段名当真值之前先按「可选」实现。

## 7.2 顺序

单流 teardown 的已恢复顺序（`INFERRED` TD-01/02，`0x2519cce10`）：

1. 入口把 session/type/options 拷进异步操作；
2. 内部读 `storage[0]`，已 disposed 则直接退出（幂等的第一层）；
3. 用 raw type + options 里的 `streamID`（options 为 NULL 时用 0）查本地注册表；
4. 命中且在控制传输上：复制/创建 options、强制写 `type`、追加到数组、取 `streamID`；
5. **先本地注销**，再调用 sender（数组, teardownType=0）；
6. sender 的错误只记日志；keepalive 重启结果作为返回值；
7. 原始实现里「send=-6722 且 keeper=0 仍返回 0」——**发送失败不等于整体失败**。

## 7.3 与「链路断开」的区别

- teardown 是**协议内**动作：发 `tdwn`，等车机回；
- 链路断开（socket/HTTP 断开）不产生 `tdwn`，本地仍要清理，但不能把它当作「车机已知情」；
- 重连时不要复用旧 `streamID` 的注册项，先按 7.2 第 5 步注销。

本阶段没有抓到 teardown 的请求/回复，所以「车机是否回、错误码集合、超时」都没有证据
（`OPEN-TEAR-1`）。**禁止**把 socket EOF 当成对端确认（TD-OPEN 的原文要求）。

## 7.4 与麦克风/媒体流的对应

- 麦克风：`transport teardown` 释放 `+0x190`（handler）与 `+0x188`（input transport），
  再清 `+0x180`（InputKey）——`INFERRED`，`0x2519cd844`；
- 音频对象：释放 sink `+0x178` 并 drain 暂存队列 `+0x1a0`——`INFERRED`，`0x2519ce884`；
- 统一 `suspendInternal`（`0x2519cd2d0`）在 `+0xb8 == 0` 时**早退**，所以「SETUP 前的失败」
  不一定走到完整 suspend 块。失败回滚全覆盖仍未证（`OPEN-TEAR-2`）。

## 7.5 幂等性

固件里能看到两层：`storage[0]` 的 disposed 早退、注册表未命中即跳过。两处都只覆盖
「本进程内重复调用」，不覆盖「重复发送 `tdwn` 给车机」或「teardown 与断链并发」。
后者登记 `OPEN-TEAR-1`。
