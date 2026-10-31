# analysis/08 — 控制通道的收包流水线

`analysis/02` 讲到"表项类型 0 → `parseIncomingMessage`"。本文件把这条流水线的每一步和它的四个出口钉死。

## 8.1 入口契约

`_iap2_sessionControl_parseIncomingMessage(component, buf, len)`（`0x10011d518`）：

```
0x10011d540  if (component == 0) → 返回 0
0x10011d548  if (buf == 0)       → 返回 0
0x10011d554–0x10011d580  sp+0x30 处构造一个"空消息对象"
                         （0xAA 填充 + iAP2MsgInit(msg, 0, 0, 0, 0, 0)）
0x10011d584  if (len == 0) → 返回 0
```

`iAP2MsgInit` 在这里被传的全是 0（`0x10011d56c`–`0x10011d57c`：`w1=0, x2=0, w3=0, x4=0, x5=0`），说明**消息对象只是外壳**，真正的缓冲由解析器随后填进去。

## 8.2 逐字节喂解析器

```
0x10011d5c0  loop:
0x10011d5c0      x0 = [component+0x78]        ; ★ 解析器（endpoint+0x78）
0x10011d5c4      w1 = buf[i]
0x10011d5c8      x2 = &msg
0x10011d5cc      bl   #0x10008eb68            ; iAP2MsgParserConsumeByte
0x10011d5d0      cbz  x0 → 下一个字节
```

解析器返回非 0 表示"一条消息拼完了"，返回值就是那条消息的对象。**一次调用只喂一个字节**，所以：

- 消息可以跨任意多个链路包；
- 一个链路包里可以有多条消息；
- 会话层不关心包边界，只关心字节顺序。

这与 `analysis/03` 的"无消息级校验和"是配套设计：顺序由链路层的序列号保证，会话层只做字节流拼装。

## 8.3 四个出口

拿到一条完整消息后，顺序是**日志 → 门控 → 查处理器 → 调用**，三个失败口各自有独立日志：

| 序号 | 条件 | 日志字符串（地址） | 返回 |
|---|---|---|---|
| ① | `*component == 0` | 无（直接跳失败） | 0 |
| ② | 门控不通过 | `"Not identified for incoming message ID: 0x%04X! (endpoint %@)"`（`0x1001db8e2`） | 0 |
| ③ | 无处理器 | `"No message handler found for incoming message ID: 0x%04X!"`（`0x1001db920`） | 0 |
| ④ | 处理器返回 false | `"Message handler returned false! (0x%04X for endpoint %@)"`（`0x1001db95a`） | 0 |
| ⑤ | 成功 | `"Incoming Message ID: 0x%04X (%d bytes) for endpoint %@"`（`0x1001db8ab`） | 1 |

对应指令：

```
0x10011d5d8  ldr x8,[x20]                    ; *component
0x10011d5dc  cbz x8 → 失败
0x10011d5e0  w23 = iAP2MsgGetMsgID(x28)      ; 0x100004b44
0x10011d5ec  w24 = iAP2MsgGetMsgLen(x28)     ; 0x100005274
0x10011d624…0x10011d674  log ⑤（先记日志，再判门控）
0x10011d678  x0 = component ; x1 = msgID
0x10011d680  bl   #0x100051054               ; 入站门控
0x10011d684  tbz  w0,#0 → ②
0x10011d688  x0 = msgID
0x10011d68c  bl   #0x10012e644               ; 全局处理器查找
0x10011d690  cbz  x0 → ③
0x10011d698  x0 = component ; x1 = msg
0x10011d69c  blraaz x8                       ; ★ 间接调用处理器
0x10011d6a4  tbz  w0,#0 → ④
0x10011d6a8  w23 = 1
0x10011d6ac  bl   #0x1000088a4               ; 释放/重置消息对象
0x10011d6b8  i++ ; loop
```

三个观察：

1. **日志在门控之前**。“Incoming Message ID”会为**每一条**拼完的消息打印，包括随后被丢弃的。所以运行日志里出现某个消息 ID，**不代表它被处理了**——这是阅读 sysdiagnose 时最容易误判的一点。
2. **处理器是间接调用**（`blraaz x8`），参数是 `(component, msg)`。也就是说处理器拿到的是 **endpoint 与消息对象**，不是会话表项。会话表项的作用仅限于“选出这条流水线”。
3. **成功一条消息不会重置解析器的字节流**（只重置消息对象），循环继续喂同一缓冲里的后续字节。

## 8.4 另外三个数据面

同一个分发器还有三条出口（`0x10006b878`，见 `analysis/02`）：

| 类型 | 入口 | 本阶段取证程度 |
|---|---|---|
| 0 控制 | `iap2_sessionControl_parseIncomingMessage` `0x10011d518` | 已确认（本文件） |
| 1 文件传输 | `iap2_sessionFileTransfer_handleDatagram` `0x100183b8c` | 仅确认调用点，未读实现 → `OPEN-SES-16` |
| 2 EA | `platform_externalAccessory_handleIncomingEADataFromAccessoryForSessionID` | 仅确认调用点与 16 位子会话号拆分 |
| 4 会话日志 | `iap2_sessionLog_parseIncomingMessage` `0x100136828` | 仅确认调用点，未读实现 → `OPEN-SES-16` |

EA 面的细节值得单独记一笔：载荷前 2 字节是**子会话号（大端）**，其后才是数据，且 `CFDataCreate` 只拷贝 `len-2` 字节（`0x10006b93c` 区）。当 `len == 2` 时构造零长 CFData 的路径被显式短路，改为记日志并返回 1（`"Received EA packet of 0 bytes, no data to process!"`）——即**空 EA 包是合法心跳**，不报错。

## 8.5 未决

- **`OPEN-SES-16`**：文件传输与会话日志两个数据面的实现未读，因此"它们是否共享同一解析器/消息格式"未定。
- `0x10011d6ac` 调用的 `0x1000088a4` 符号名为 `iAP2MsgCleanup`（**符号名存在**，非剥名函数），即"清理消息对象"。其内部是否释放缓冲未读 → 归入 `OPEN-SES-17`：消息对象清理是否释放解析器缓冲未确认（对后续解析行为无影响，对内存审计有影响）。
