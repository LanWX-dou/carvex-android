# analysis/10 — 控制通道的发包路径

出站方向有两条入口、一条公共校验、一条公共出口。会话层在这里只做两件事：**查会话号**、**把消息交给链路**。它不做分片、不做序号、不做重传。

## 10.1 两个入口

| 入口 | 指令 | 语义（按第三参数区分） |
|---|---|---|
| `iap2_sessionControl_sendOutgoingMessage` `0x100005130` | `mov w2,#0` ; `b 0x100004f14` | 普通发送 |
| `iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK` `0x10002a9bc` | `mov w2,#1` ; `b 0x100004f14` | 发送并要求确认回调 |

两个函数都只有 8 字节：把第三参数置 0/1 后**尾调用**同一个实现。所以"要不要确认回调"是唯一区别，其余逻辑完全共享。

## 10.2 公共实现

`__sendOutgoingMessage(component, msg, wantAckCallback)`（`0x100004f14`）：

```
0x100004f14  要求 component != 0、msg != 0、*component != 0，否则跳失败
0x100004f2c  msgID = iAP2MsgGetMsgID(msg)          ; 0x100004b44
0x100004f34  msgLen = iAP2MsgGetMsgLen(msg)        ; 0x100005274
0x100004f38  w = isIdentifiedForOutgoingMessageID(component, msgID)   ; 0x100005138
0x100004f3c  tbz → 失败
0x100004f44  if (wantAckCallback == 0)
0x100004f44      iAP2MsgSendControl(component[5], msg)        ; component+0x28 = run loop
0x100004f4c  else
0x100004f4c      iAP2MsgSendControlAndCallbackOnAck(...)
0x100004f50  记日志 "Outgoing Message ID: 0x%04X (%d bytes) for endpoint %@"   ; 0x1001db82d
0x100004f60  返回 1
失败:        记日志 "Failed to send, Outgoing Message ID: 0x%04X (%d bytes) for endpoint %@" ; 0x1001db864
             返回 0
```

三点：

1. **门控在发送之前**，且失败时**只记日志、不返回错误给上层**（返回 0，但两个入口都是尾调用，调用者拿到的就是 0）。
2. 第一参数是 **endpoint**，而 `component[5]`（`+0x28`）就是 run loop —— 与 `analysis/02` 的对象图一致。
3. 成功日志在真正入队**之后**打印，所以"日志里有 Outgoing Message ID"等价于"已交给链路"，不等价于"已上线"。

## 10.3 装配消息

`iAP2MsgSendControl(runloop, msg)`（`0x10000530c`）：

```
0x100005320  x19 = msg ; x20 = runloop
0x10000532c  w21 = iAP2MsgCalcMessageLen(msg)      ; 0x1000053a4（重算并回填总长）
0x100005334  x0 = [x20+0x10] ; x1 = msg
0x10000533c  bl  #0x100005738                       ; 发送前处理（详见 OPEN-SES-20）
0x100005340  strb (w21>>8),[buf+2] ; strb w21,[buf+3]   ; 再次写总长（大端）
0x100005354  ands w8,w21,#0xffff ; b.eq → 直接返回（长度 0 视为空发送）
0x10000535c  [msg+0x00] = buf                      ; 消息对象指向自己的缓冲
0x100005364  [msg+0x08] = 长度 ; [msg+0x0c] = 0
0x100005368  [msg+0x38] = 0                        ; 清标志
0x10000536c  x0 = [x20+0x18]                       ; ★ run loop+0x18 = link
0x100005390  b  #0x100005bd0                       ; __iAP2LinkDataSentCB(link, msg)
```

`0x100005354` 的 `b.eq` 是一个**静默短路**：算出来的消息总长为 0 时直接返回，不发包也不记日志。正常路径下 `iAP2MsgCalcMessageLen` 至少返回 6（消息头），所以这条分支实际上打不到；它的存在说明代码容忍"空消息对象"。

## 10.4 会话号从哪来

`iAP2MsgSendCtlDataWithSentCallback(obj, …)`（`0x1000055e4`）是唯一显式查会话号的发送函数：

```
0x100005628  x0 = [x0+0x18]                 ; link
0x10000562c  w1 = 0                          ; ★ 服务/类型 = 0
0x100005630  bl  #0x100005740               ; iAP2LinkGetSessionForService(link, 0)
0x100005634  x22 = x0                        ; 会话号
0x100005638  strb w19,[sp]                   ; 第 8 个参数走栈
0x10000563c  重排 x0..x7
0x10000565c  bl  #0x100006758               ; iAP2LinkRunLoopQueueSendDataWithSentCallback(…, x3 = 会话号, …)
```

`0x10000565c` 的第三参数位置（`x3`）正好是 `iAP2LinkQueueSendDataWithSentCallback`（`0x100006868`）用来匹配 `表项[0]` 的那个值（`analysis/02` 的 `0x1000068d4`）。

**常量 0** 就是这里出现的唯一硬编码：类型 0 = 控制通道。这与 `analysis/08` 分发侧的"类型 0 → 控制"闭合，构成"控制通道类型号 = 0"的双向证据。

## 10.5 可靠性落在哪一层

| 机制 | 会话层 | 链路层 |
|---|---|---|
| 序号 | **无** | 有（包序号，`link/R-3.x`） |
| 重传 | **无** | 有（超时/最大重传次数） |
| 校验和 | **无** | 有（头校验 + 载荷校验） |
| 确认 | 仅"要求确认回调" | 有（ACK 包 / 累积确认） |
| 分片 | **无**（消息 ≤ 65535，由解析器跨包重组） | 有（按最大载荷切包） |

所以**控制消息的可靠传输完全依赖链路层**。会话层唯一的"确认"概念是 `sendOutgoingMessageAndCallbackOnACK` 注册的一个回调——它挂在包级确认上，不是消息级确认。

> **`OPEN-SES-20`**：`0x100005738`（发送前处理，符号表未命名）未读。它拿 `runloop+0x10`（endpoint）与消息，可能做"发送前状态检查"或"参数补全"，未取证。
> **`OPEN-SES-21`**：`iAP2MsgSendControlAndCallbackOnAck`（`0x1000a0520`）未读，因此"确认回调在什么时机被调用、超时如何处理"未定。
> **`OPEN-SES-22`**：`__iAP2LinkDataSentCB`（`0x100005bd0`）虽有名，但它是"把消息入队"还是"标记已发送"未读；本文件只据其参数（link, msg）描述为"交给链路层发送入口"。
