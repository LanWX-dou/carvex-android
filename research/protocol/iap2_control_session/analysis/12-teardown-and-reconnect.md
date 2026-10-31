# analysis/12 — 拆除与重连

## 12.1 拆除的触发

只有一条路径：`linkStateChanged(component, 0)` 且旧值为 1（`analysis/09`）。没有"会话超时拆除"，也没有"消息级关闭会话"。

```
0x10003122c  iap2_sessionControl_cleanup(component)
0x100031230  iap2_sessionFileTransfer_cleanup(component)
0x100031234  iap2_sessionLog_cleanup(component)
```

## 12.2 控制会话的清理

`_iap2_sessionControl_cleanup`（`0x10011d1c4`）：

```
0x10011d1c4  要求 component != 0、*component != 0、**component != 0，否则返回 0
0x10011d1e0  w = acc_endpoint2_getTransportType()
0x10011d1e4  if (w == 8)  → 异步平台任务（栈块 ___iap2_sessionControl_cleanup_block_invoke）
0x10011d1f8  acc_endpoint2_externalAccessory_removeEAAccessoryForPrimaryEndpoint(component[1])
             iap2_endpoint_setInitialized(...)
0x10011d210  if (isIdentifiedForWirelessCarPlay(component)) → 另一个异步平台任务
             iap2_features_destroyFeatures()      ; 经 outlined 片段调用两次
0x10011d224  if (component[0x19] != 0) { free(component[0x19]); component[0x19] = 0; }
```

要点：

1. **缓冲确实被释放并清零**：`0x10011d224`–`0x10011d238` 对 `+0xc8`（= `component[0x19]`，`0x19*8 = 0xc8`）做 `free` + 置 0。所以重连时 `init` 会重新 `malloc(0xffff)`（`analysis/05` 的幂等分支）。
2. **EA 配件被移除**：`removeEAAccessoryForPrimaryEndpoint(component[1])`，`component[1]` 是 endpoint 的第二个指针字段（`analysis/01` 的 CFString 之一）。这说明"外部配件"对象在断连时被显式注销。
3. **特性被销毁但处理器字典不动**：`destroyFeatures` 清的是 endpoint 的 29 个特性槽（`+0xd0`），不是全局消息字典。字典的 96 条映射在整个进程生命周期内**只注册一次**（`analysis/06`）。
4. **异步分支**：传输类型 8 与"无线 CarPlay 已识别"两种情况下清理会切到平台工作队列异步执行。这带来一个**顺序不确定性**：`free(+0xc8)` 与异步块之间没有显式同步证据 → `OPEN-SES-26`。

## 12.3 重连

链路重新连接时的复位发生在链路层，本阶段能看到五处把会话表清空的点：

| 地址 | 所在函数 | 时机 |
|---|---|---|
| `0x1000341ec` | `iAP2LinkCreate` | 新建链路 |
| `0x1000344e0` | `iAP2LinkResetSend` | 发送侧复位 |
| `0x100034aa8` | `iAP2LinkAttached` | 附着 |
| `0x100034b54` | `iAP2LinkSendRST` | 发 RST |
| `0x100034c08` | `iAP2LinkDetached` | 分离 |

五处写入值相同（`0xFFFF0100`），即"项数归零"。**因此每次链路层复位后，会话表都回到空**，会话必须重新登记。这与"控制会话对象不会跨连接存活"是同一个设计：会话是链路的下属数据，链路复位就全清。

重连时的会话层动作链：

```
link 复位（表清空）
  → linkStateChanged(0)（若旧值为 1）→ 三个 cleanup → 释放 +0xc8
  → linkStateChanged(1)（上升沿）→ 七个 init/start → 重新 malloc +0xc8
  → 处理器注册被幂等标志挡掉（只记一行日志）
```

所以**重连比首次连接少做一件重活**：96 条处理器不再灌入字典。

> **`OPEN-SES-27`（部分闭合）**：建表/提交动作见 `A02.15`。重连必须以新一轮协商为准；各种异常重连分支是否均重置工作块、profile 是否沿用，仍需完整路径和实测，不能假设会话号不变。
> **`OPEN-SES-28`**：`iap2_endpoint_destroy`（`0x100030d4c`，已导出）未读，因此 endpoint 销毁时是否释放 run loop、解析器（65567 字节）、以及三个 CFString 未取证。

## 12.4 拆除的完整性

| 资源 | 分配点 | 释放点 | 结论 |
|---|---|---|---|
| 控制缓冲 `+0xc8`（65535 B） | `0x10011d180` | `0x10011d228`（`free`） | 已确认成对 |
| 特性槽（29 × 8 B） | `createFeatures` | `destroyFeatures` | 已确认成对（调用点） |
| 消息处理器字典（96 条） | `registerMessageHandlers` | **无** | 进程级常驻，非泄漏 |
| 解析器（65567 B） | `0x1001295e0` | 未确认 | → `OPEN-SES-28` |
| 链路对象（0x268 + 缓冲） | `iAP2LinkCreate` | 未确认 | → `OPEN-SES-28` |
| endpoint（0x1d8） | `calloc` `0x10012935c` | `iap2_endpoint_destroy` | 未读 |

**注意**：`cleanup` 不释放 endpoint 本身，也不释放链路。这两者属于"配件拔出/进程退出"路径，比"链路断开"更晚、更重。
