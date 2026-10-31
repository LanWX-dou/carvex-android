# analysis/01 — 会话对象模型

本文件回答"会话相关的东西住在哪个对象里"。结论一句话：

> **iPhone 侧没有"会话对象"。** 会话是一张**表项**，挂在链路对象上；每个表项 4 字节，描述"这条会话号对应哪种数据面"。控制会话本身没有独立的分配对象，它的全部状态就是 endpoint 对象里的一个 0xFFFF 字节缓冲和一张全局消息处理器字典。

这个结论和直觉相反（"控制会话"听起来像一个长生命周期对象），所以下面把两个对象、一个表、一张字典分别取证。

## 1.1 endpoint 对象

`_iap2_endpoint_create`（`0x100129350`）是唯一分配点：

```
0x10012935c  calloc(1, 0x1d8)      ; 对象总长 0x1d8 = 472 B
0x100129364  *context = param_1    ; +0x00 protocolEndpoint
0x1001295c0  iAP2LinkRunLoopGetBuffSize(0x7f, 0xffff)
0x1001295cc  iAP2LinkRunLoopCreateDevice(context+6, context, 1, 0, 0x7f, 0xffff, buf)
0x1001295e0  malloc(0x1001f)       ; 65567 B 消息解析缓冲
0x1001295e4  iAP2MsgParserInit(0xffff, buf, link, 0x4040)
0x100129600  iAP2LinkRunLoopAttached(link)
```

已确认字段：

| 偏移 | 宽度 | 内容 | 证据 |
|---|---|---|---|
| `+0x000` | 8 | 传输层 endpoint 指针 | `0x100129364` |
| `+0x008` | 8 | CFString（拷贝自 `[ep+0x10]`） | `0x1001293a0` 区 |
| `+0x010` | 8 | CFString（拷贝自 `[ep+0x8]`） | `0x1001293b8` 区 |
| `+0x018` | 8 | 串行队列 `"iAP2Endpoint"` | `0x10012938c` |
| `+0x020` | 1 | 是否自建队列 | `0x1001293f4` |
| `+0x028` | 8 | **link run loop** | `0x1001295d4`，`0x10011d4bc` 读 |
| `+0x068` | 1 | **链路是否已连**（0/1） | `0x1000311f4` 读改写 |
| `+0x078` | 8 | **iAP2 消息解析器** | `0x1001295f0`，`0x10011d518` 读 |
| `+0x0c8` | 8 | **控制通道缓冲，`malloc(0xffff)`** | `0x10011d180`–`0x10011d184` |
| `+0x0d0` | 29×8 | 特性槽数组（按特性号索引） | `0x10013e49c` 读改写 |
| `+0x1b8` | 8 | 文件传输状态 | `0x1001835b8` 写入 |
| `+0x1d0` | 8 | 创建时刻（`CFAbsoluteTimeGetCurrent`） | `0x1001295a8` |

`+0x030`–`+0x050` 是传给建链的打包参数块（`0x100129418`–`0x100129480` 连续写入，含 `0xFFFF`、`0x7FFF`、`0xFFFFFFFF` 等常量），逐字段语义未定 → `OPEN-SES-5`。

**为什么 +0x0d0 是 29 槽**：`0x10013e49c` 里 `*(long *)(param_1 + 0xd0 + uVar14 * 8) = lVar7;`，`uVar14` 取 `__kiAP2FeatureInfoEntries` 的特性号，该表实测 29 项、特性号 0–28（`source/metadata/tables.json`）。`0xd0 + 29*8 = 0x1b8`，正好接上文件传输字段，说明槽数组长度就是 29。

## 1.2 链路对象与"会话表"

`_iAP2LinkCreate`（`0x100033fd0`）分配的不是会话，而是**链路**：

```
0x10003401c  memset(link, 0, 0x268)        ; 链路对象 0x268 = 616 B
0x100034024  *link = link                  ; 自重指针
0x1000340a4  [link+0xb8] = w27             ; 链路类型
0x1000340a8  [link+0xb0] = x26             ; 传输层 context
0x1000340ac  [link+0xc0] = w25 (u16)       ; 最大包长
0x1000340c8  [link+0xd4].bit6 = (hasSYN)
0x1000340d0  [link+0xc2] = 0xff
0x1000340d8  [link+0xd5] = 1
0x1000340dc  [link+0xd7] = w22
0x10003410c  [link+0xc8] = 定时器对象
...
0x1000341ec  [link+0x1a4] = 0xffff0100     ; 会话表：项数 = 低字节 = 0
```

会话表几何（读侧三处一致，`0x100032828` / `0x100005740` / `0x10000b26c`）：

| 偏移 | 宽度 | 内容 |
|---|---|---|
| `+0x1a4` | 1（有效） | **表项数**（`0x100032830`: `ldrb w9,[x0,#0x1a4]`，`cbz` 后循环） |
| `+0x1b8` | 4×n | 表项数组，`add x8,x8,#0x1b8`，步长 4（`0x100032840`、`0x100005754`） |
| 表项 `+0` | 1 | **会话号**（8 位，即 `hdr[7]`） |
| 表项 `+1` | 1 | **数据面类型**（0/1/2/4，见 `analysis/08`） |
| 表项 `+2` | 1 | **版本**（`0x10011d4f4`: `ldrb w0,[x0,#2]`） |
| 表项 `+3` | 1 | 标志位，bit0 被 `0x10000b2xx` 处测试 |

建链、重置发送、连接、断连、发 RST 五处都把它清成"0 项"：`0x1000341ec`、`0x1000344e0`、`0x100034aa8`、`0x100034b54`、`0x100034c08`，写入值都是 `0xFFFF0100`。所以**连接建立之前表是空的**，这解释了为什么"连上之前发控制消息"必然无会话可路由。

> **`OPEN-SES-1`（部分闭合）**：会话表填充和提交已在 `analysis/02 §2.9` 找到：SYN 条目先写工作块，NotifyConnection 整体复制到生效块。最初 profile 分配、多会话冲突及跨版本选择仍未闭合；不要硬编码样本会话号。

## 1.3 每类型的发送队列数组

`+0x130` 是一个 **5 槽指针数组**（`i = 0..4`），在建链时逐个创建：

```
0x10003416c  add x24, x19, #0x130
0x100034170  mov w25, #5
0x100034174  loop:
0x100034180      x22 = iAP2ListInit(x22, 0xff, 8)     ; 每槽容量 255、元素 8 B
0x100034184      [x24 + i*8] = x22
0x100034198      i++
0x10003419c      subs w25, w25, #1
0x1000341a0      b.ne loop
```

使用侧：

- 发送：`0x100006934` `ldrb w9,[x27,#1]`（表项的类型）→ `0x10000693c` `ldr x0,[x20 + w9*8]`，`x20 = link+0x130`。
- 发送（另一条路径）：`0x1000073c8` 同构，`x19 = [link+0x130 + w8*8]`。
- 计数：`_iAP2LinkGetSessSendPckListCount`（`0x1000084d0`）就是 `iAP2ListGetCount(link->queues[w1])`，三条指令而已。

**类型值 0–4 与 5 个槽恰好对齐**，这是"类型即队列下标"的直接证据，也是 `analysis/08` 里那张分发表的可信度来源。

## 1.4 全局消息处理器字典

控制会话不持有处理器表，处理器在**全局字典**里：

```
_iap2_messageHandlers_getHandler(msgID)  0x10012e644
    if (__MergedGlobals != 0) CFDictionaryGetValue(__MergedGlobals, msgID);

_iap2_messageHandlers_setHandler(msgID, fn)  0x10012e4c4
    CFDictionarySetValue(__MergedGlobals, msgID, fn);
```

`_iap2_features_registerMessageHandlers`（`0x10006a1d0`）在第一次调用时把 29 项特性信息表里所有处理器灌进该字典：

```
0x10006a1d0  if (handlersRegistered & 1) return 1;      ; 幂等标志
0x10006a1d0  log "Registering message handlers..."
              for (i = 0; i != 0x1d; i++)                ; 29 项
                  info = kiAP2FeatureInfoEntries[i]
                  if (info == 0 || info->handlers == 0)      -> cold 报错
                  if (info->count != 0)
                      for (k = 0; k < info->count; k++)
                          setHandler(entry[k].msgID, entry[k].fn)   ; 每项 0x10 B
              handlersRegistered = 1;
```

实测规模（`tables.json`）：29 项特性，其中 **27 项有处理器表**，合计 **96 个处理器**。所以"消息 ID → 处理函数"是一个 96 条的全局映射，与控制会话的生命周期无关——`analysis/09` 会说明这带来的一处**行为差异**（处理器在断连后依然存在）。

## 1.5 三者的引用关系

```
endpoint(+0x1d8)
  +0x028 ──► link run loop
                 +0x018 ──► link(+0x268+缓冲)
                              +0x1a4 表项数 ─┐
                              +0x1b8 表项数组 ─┤ 会话 = 表项
                              +0x130[0..4] 每类型发送队列
  +0x078 ──► 消息解析器（缓冲 0x1001f）
  +0x0c8 ──► 控制通道缓冲（0xffff）
  +0x0d0 ──► 29 个特性槽 ──► 各自的状态对象
全局: CFDictionary(96 条 msgID → handler)
```

读写这些偏移的函数清单见 `analysis/13`。
