# analysis/02 — 链路层初始化与运行循环

对应任务书第 5 节第 2 项。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2LinkGetBuffSize` | `0x100033ed8` | 链路对象所需缓冲大小 |
| `iAP2LinkCreate` | `0x100033fd0` | 创建链路对象（0x268 字节） |
| `iAP2LinkRunLoopCreate` | `0x1000cae54` | 创建运行循环 + 内嵌链路 |
| `iAP2LinkRunLoopCreateDevice` | `0x1000cae38` | 设备侧包装（`w0=1`） |
| `iAP2LinkRunLoopInitImplementation` | `0x100103954` | 实现初始化 |
| `iAP2LinkRunLoopRunOnce` | `0x100008698` | 运行循环单步 |
| `iAP2LinkRunLoopSignal` | `0x100007728` | 唤醒（`dispatch_async` 到内部队列） |
| `iAP2LinkRunLoopGetResetEventMask` | `0x10000638c` | 取待处理事件位掩码并清零 |
| `iAP2LinkAttached` | `0x100034a7c` | 传输 attach 时复位并投事件 1 |
| `iAP2LinkStart` | `0x100034a70` | 投 FSM 事件 0 |
| `iAP2LinkSetUseiAP2LinkRunLoop` | `0x100035144` | 打开运行循环标志（`link[0xd4] \|= 0x10`） |
| `iAP2LinkHandleTimeout` | `0x100034f24` | 把超时转换成 FSM 事件 |

## 2.1 两层对象：runloop 与 link

`A02.1`（已确认）运行循环对象 0x60 字节，其中 `+0x60` 起是链路对象缓冲区；链路对象固定 0x268 字节：

```
; iAP2LinkRunLoopCreate(mode x0, transport x1, .., x7 = 缓冲)
0x1000cae68: cbz  x7, 0x1000caeec        ; 缓冲不可为空
0x1000cae78: movi v0.2d, #0
0x1000cae7c: stp  q0, q0, [x7]            ; 清 0x60 字节
0x1000cae80: stp  q0, q0, [x7, #0x40]
0x1000cae84: stp  q0, q0, [x7, #0x20]
0x1000cae88: str  x7, [x7]                ; runloop->self
0x1000cae8c: add  x22, x7, #0x60
0x1000cae90: str  x1, [x7, #0x10]         ; runloop->transport
0x1000cae94: mov  x1, x7
0x1000cae98: mov  x7, x22                 ; link 缓冲 = runloop+0x60
0x1000cae9c: bl   0x100033fd0             ; iAP2LinkCreate
0x1000caea0: str  x0, [x19, #0x18]        ; runloop->link
0x1000caeac: bl   0x100033ed8             ; iAP2LinkGetBuffSize
0x1000caebc: add  x8, x22, w8, uxtw
0x1000caec0: str  x8, [x19, #8]           ; runloop->packet_area
0x1000caecc: bl   0x100034a70             ; iAP2LinkStart
0x1000caed4: bl   0x100103954             ; InitImplementation
```

链路对象内部再分配（`iAP2LinkCreate`）：

```
0x100034018: mov  x0, x7
0x10003401c: mov  w1, #0x268
0x100034020: bl   0x1001a20b0            ; 见注
0x100034024: str  x19, [x19]             ; link->self
0x100034044: add  x23, x19, #0x268       ; 后续子缓冲起点
```

> 注：`0x1001a20b0` 不在本阶段选点内（无符号名，实际语义未逐条核对；按 `(x0=x7, w1=0x268)` 的调用形状疑似分配包装）；链路对象大小 0x268 由 `iAP2LinkGetBuffSize` 与 `add x23,x19,#0x268` 两处一致给出。

`A02.2`（已确认）链路对象的关键偏移（后续文件反复引用）：

| 偏移 | 含义 | 证据 |
|---|---|---|
| `+0x00` | 自指针 | `0x100034024` |
| `+0x08` | FSM | `0x100034088` / `0x100034a70` |
| `+0xb0` | 拥有者（= runloop） | `0x1000340a8`；`iAP2LinkConnectedCB` 中 `[0xb0]→[0x10]` |
| `+0xb8` | 模式（x0 参数） | `0x1000340a4` |
| `+0xbc` | 发送时写入 `hdr[6]` 的字节 | `0x100007978` |
| `+0xc0` | 最大包长参数（u16） | `0x1000340ac` |
| `+0xc2` | 定时器重装值（初值 0xFF） | `0x1000340cc` |
| `+0xc8` | 定时器对象 | `0x100034110` |
| `+0xd4` | 标志字节 | bit6=设备角色、bit2/bit3=运行循环相关、bit4=使用 runloop |
| `+0xd5` | 校验类型（初值 1） | `0x1000340d8` |
| `+0xd7` | x2 参数 | `0x1000340dc` |
| `+0x120`/`+0x128` | 收/发包链表 | `0x100034130` / `0x100034154` |
| `+0x130..0x158` | 5 个发送链表 | `0x100034184` |
| `+0x168` | SYN 参数结构（见 `analysis/04`） | `0x1000341a8` |
| `+0x1a5` | 确认窗口 | `0x10003543c` |
| `+0x204`/`+0x20c` | 累计字节数 / 发送包计数 | `0x100007958` / `0x100007968` |
| `+0x254` | RTT 统计（计数 + 累计） | `0x1000079b0` |

## 2.3 运行循环的驱动方式

`A02.3`（已确认）`iAP2LinkRunLoopRunOnce(runloop, x1, x2)` 每调用一次处理一轮事件位，返回 0 表示已关闭、非 0 表示继续：

```
0x1000086b8: ldrb w8, [x0, #0x2c]
0x1000086bc: tbz  w8, #0, 0x1000086c8   ; bit0 = 关闭中
0x1000086c0: mov  w0, #0
0x1000086d4: bl   0x10000638c           ; mask = 事件位
0x1000086dc: ldr  x0, [x19, #0x18]      ; link
0x1000086e4: tbnz w20, #0, 0x1000086fc  ; bit0 → Attached
0x1000086e8: tbnz w20, #1, 0x100008704  ; bit1 → Detached
0x1000086ec: tbnz w20, #2, 0x100008710  ; bit2 → HandleSuspend
0x1000086f0: tbnz w20, #3, 0x10000871c  ; bit3 → HandleResume
0x1000086f4: tbnz w20, #0xc, 0x100008728; bit12 → Renegotiate
```

位的语义（同名函数即证据）：

| 位 | 动作 |
|---|---|
| `0x0001` | `iAP2LinkAttached`（`0x1000086fc`） |
| `0x0002` | `iAP2LinkDetached`（`0x100008704`） |
| `0x0004` | `iAP2LinkHandleSuspend`（`0x100008714`） |
| `0x0008` | `iAP2LinkHandleResume`（`0x100008720`） |
| `0x1000` | `iAP2LinkRenegotiate`（`0x100008744`，参数低 7 位/高位拆分） |

`A02.4`（已确认）`iAP2LinkAttached` 先复原 SYN 缺省参数，再向 FSM 投事件 1：

```
0x100034a80: add  x8, x0, #0x19a
0x100034a8c: mov  w10, #0x3e8ffff
0x100034a90: str  w10, [x9]
0x100034a94: mov  w9, #0xa
0x100034a98: strh w9, [x0, #0x1a2]
0x100034a9c: ldr  d0, [x9, #0x348]
0x100034aa0: str  s0, [x8]
0x100034aa4: mov  w8, #-0xff00
0x100034aa8: str  w8, [x0, #0x1a4]
0x100034aac: ldr  x0, [x0, #8]
0x100034ab0: mov  w1, #1
0x100034ab4: b    0x10000639c          ; FSM 事件 1（Detached → Detect）
```

`A02.5`（已确认）`iAP2LinkStart(link)` = 向 FSM 投事件 0（`Init → Detached`）：

```
0x100034a70: ldr  x0, [x0, #8]
0x100034a74: mov  w1, #0
0x100034a78: b    0x10000639c
```

`A02.6`（已确认）超时也走 FSM：`iAP2LinkHandleTimeout(link, x1, event w2)` 直接把 `x2` 当作事件号投递。

`A02.7`（未确认 / `OPEN-INIT-1`）运行循环的**宿主线程/队列**未在本轮取证：`iAP2LinkRunLoopSignal`（`0x100007728`）内部有一个 `_block_invoke`（`0x1000084dc`），说明它用 GCD 队列唤醒；但"谁周期性调用 `RunOnce`"（定时器源、队列还是外部驱动）未定位。`acc_protocolParser_iAP2_run`（`0x1000cf5b8`）的命令分发与 `RunOnce` 之间缺少直接调用证据。

## 2.8 与传输层的边界

- 运行循环保存 transport 指针（`runloop+0x10`），链路通过 `link+0xb0 → +0x10` 取到它（见 `analysis/01`）。
- 传输 attach/detach 通过 `RunOnce` 的 bit0/bit1 进入，而不是直接调用链路函数 —— 这意味着实现者必须先建立"事件位"这一层，否则无法复现固件的时序。

## 2.9 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-INIT-1` | 运行循环的驱动源（线程/队列/定时器） |
| `OPEN-INIT-2` | `0x1001a20b0`（`iAP2LinkCreate` 首调）的确切语义 |
| `OPEN-INIT-3` | `iAP2LinkGetBuffSize`（`0x100033ed8`）各分量的分解（只确认返回值被用于计算包区起点） |
| `OPEN-INIT-4` | `iAP2LinkRunLoopInitImplementation`（`0x100103954`）的实现体（本轮导出为空桩或跳转，未取证） |
