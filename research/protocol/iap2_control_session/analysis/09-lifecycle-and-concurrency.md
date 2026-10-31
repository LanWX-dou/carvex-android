# analysis/09 — 生命周期与并发

## 9.1 唯一的状态源：一个字节

endpoint 的 `+0x68` 是"链路是否已连"的唯一标志，只有一个函数写它：

`_iap2_endpoint_linkStateChanged(component, connected)`（`0x1000311f4`）：

```
0x1000311f4  log "Link state changed! (Connected: %d)"
0x100031210  bVar2 = [component+0x68]          ; 旧值
0x100031214  [component+0x68] = connected       ; 新值
0x100031218  uVar1 = 旧值 ^ 1
```

三条分支（`0x10003121c` 之后）：

| 条件 | 含义 | 动作 |
|---|---|---|
| `connected != 0 && 旧值 == 0` | **上升沿** | 见 9.2，7 个调用 |
| `connected == 0 && 旧值 == 1` | **下降沿** | 见 9.3，3 个调用 |
| 其余 | 电平未变 | 什么都不做 |

"电平未变则不动"是显式写的（`(param_2 == 0) || ((uVar1 & 1) == 0)` 的两层判断），所以**重复上报同一个状态是幂等的**。

## 9.2 上升沿：固定顺序

```
0x10003124c  iap2_endpoint_configUSBHost(component)
0x100031250  iap2_sessionControl_init(component)
0x100031254  iap2_sessionControl_start(component)
0x100031258  iap2_sessionFileTransfer_init(component)
0x10003125c  iap2_sessionFileTransfer_start(component)
0x100031260  iap2_sessionLog_init(component)
0x100031264  iap2_sessionLog_start(component)
```

顺序有三层含义：

1. **先 USB 配置，再会话**：`configUSBHost` 在最前，说明有线场景下主机角色要在任何会话动作之前定好。
2. **控制会话最先**：`sessionControl_init` 负责注册 96 个消息处理器（`analysis/06`）。它先跑，后续两个数据面才可能收到消息——因为处理器字典此时才非空。
3. **`init` 与 `start` 成对**：每个数据面都是 init 紧接着 start，没有交错。

七个调用的**返回值全部被忽略**（`0x100031250`–`0x100031264` 之后没有 `cmp`/`cbz`）。所以"启动失败"不会阻止后续步骤，也不会重试；失败只体现为内部日志。

## 9.3 下降沿：三个 cleanup

```
0x10003122c  iap2_sessionControl_cleanup(component)
0x100031230  iap2_sessionFileTransfer_cleanup(component)
0x100031234  iap2_sessionLog_cleanup(component)
```

顺序与上升沿相同（控制在前），不是逆序。**没有**对应的 `configUSBHost` 撤销调用。

## 9.4 "建立完成"的判定

本层**没有**"会话已建立"的标志位。可以判定为"控制通道可用"的充分条件只有三条同时成立：

1. `[component+0x68] == 1`（链路已连，`0x1000311f4` 写）
2. 链路会话表里有类型 0 的行（`analysis/02` 的读侧，表由链路层建）
3. 目标消息 ID 通过门控（`analysis/07`）

第 2 条无法从本层的状态观察，因为表在 link 对象里，且本层没有 API 去问"控制会话的会话号是多少"——`getVersion` 是唯一会顺手查表的函数（`analysis/05`），它返回的是版本而不是会话号。

> **`OPEN-SES-18`**：`start` 的返回值被丢弃，因此**没有证据**表明"start 失败会让链路状态回退"。若 `startFeatureFromDevice` 失败，控制通道会停留在"已连但安全流程未启动"的状态，而外部观察不到。

## 9.5 并发

多会话在本实现里的形态：

| 维度 | 事实 | 证据 |
|---|---|---|
| 每类型一条发送队列 | `link+0x130[0..4]`，容量 255 项、元素 8 字节 | `0x100034174`–`0x1000341a0` |
| 队列表上限 | 类型 0–4，共 5 槽 | 同上 |
| 会话表容量 | 生效 SYN 块内 `0x1b8..0x1cb`，每项 4 字节，**最多 5 项** | `A02.15`；link `0x100103328..330` |
| 表项计数宽度 | 1 字节（`+0x1a4`）→ 上限 255 | `0x1000326c4` `ldrb` |
| 表项查找 | 线性扫描，**取最后一个匹配** | `0x1000326e8` `csel` |

计数字段能表示 255 不等于表有 255 项。旧版从对象尾部推导 44 项错误；`+0x1cc` 后有其他状态/计数，不能当表。客户端须在解析时验证计数、长度、ID/类型唯一性，不能仅依赖读表循环的计数。

EA 面在会话号之外还有一层 **16 位子会话号**（载荷前 2 字节，`analysis/08`），所以 EA 是唯一支持"一会话内多路复用"的数据面。

> **`OPEN-SES-19`**：多会话 profile 的实测使用和发送调度尚未完整核验；SYN 支持最多 5 条以及填充链已确认，不再称“表内容不可见”。
