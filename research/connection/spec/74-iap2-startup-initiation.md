# 74 — 第五项差异：蓝牙连接后谁先发Detection/SYN


## 1. 结论与边界

后续进展：[76](76-iap2-xpc-handoff-hid.md)已补指定XPC服务/对象/参数交接，确认protocol=0原样进入端点；属性回调首层目标已解析为HidService/Bluetooth_HIDFunction。以下保留本批研究时边界；所有上层超时及通知下游仍未关闭，不能将76误读为完整入口已经完成。


本批找到的24A446蓝牙入口和accessoryd局部状态机支持**接收驱动的启动方式**：蓝牙成功回调传入protocol=0；协议未知的端点先识别收到的数据；选中iAP2后，Start/Attach本身不发Detection或SYN；收到Detection有明确回发路径。


证据边界：已闭合的是下列指定函数的参数、分支、状态表与收包事件生产链；尚未逐跳闭合CoreAccessories跨进程服务交接、所有端点提供者和上层超时。不能外推为“所有iPhone入口都绝不主动”“整个系统没有超时”或“双方等待已被证明是某车型故障原因”。

## 2. 三种策略不能合并

|---|---|---|---|
| RFCOMM建立后尚未收到数据 | 默认等待，允许直接SYN | `start()`立即发Detection和本地SYN | 蓝牙创建端点时传protocol=0；accessoryd的protocol=0构造路径跳过协议层初始化 |
| 等待首字节超时 | 默认2秒后兜底发一次Detection | 已经主动发包，并用tick重复 | 未找到与我们2秒兜底等价的上层策略；不因此删除或推广它 |
| 收到合法Detection | 当前手机处理并等待后续SYN，细节见73 | 启动/推进自身协商策略 | 已核对收包→status19→event23→回发固定6字节 |
| 已发SYNACK，对端不确认 | 当前握手层缺定时重发 | 采纳参数后的tick可能发裸ACK | 73已定位state4/event12→ResendSYNACK；与首次主动发包是独立问题 |

当前源码行为沿用73的审阅，13个相关文件哈希本批复查均未变化。这里不重跑或重复计入73的9个行为向量。RFCOMM由谁主动建立，与iAP2由谁发SYN不是同一层的角色。

## 3. 蓝牙成功回调确实传入“协议未知”

### 3.1 bluetoothd的调用参数

`0x1007a4240`的连接成功路径分派block `0x1007a4520`。后者包含：

- `0x1007a45c0`附近设置connection type=2，调用`0x100909f00`。
- `0x1007a4628–0x1007a4640`设置endpoint transport=2、protocol=0、identifier=null、publish=1及输出回调，然后调用`0x100909f10`。
- `0x1007a4690`附近记录`[iAP CONNECTED]`；日志本身不是iAP2协商完成标记。

两个跳板经原Mach-O的间接符号表确认，分别是`_acc_transportClient_createConnection`与`_acc_transportClient_createEndpoint`，不是根据相邻函数名猜测。这里的2/0是内部API枚举，不能写入线上SYN当作版本字段。

### 3.2 CoreAccessories封装没有把protocol=0改成4

`_acc_transportClient_createEndpoint@0x204415740`保存C调用的transport和protocol，分别作为Objective-C调用的x2/x3传出。原共享缓存的`0x20806b980`跳板指向`0x1f74b559c`，其selector为：

```text
createEndpointWithTransportType:andProtocol:andIdentifier:
andDataOutHandler:forConnectionWithUUID:publishConnection:
```

这不是仅靠导出的头文件解释参数：292字节封装与原dyld缓存一致，selector跳板及字符串也从原缓存重读。缓存文件、偏移和切片哈希在证据JSON中。

**仍需分开看待的边界：**上述客户端封装与下节accessoryd服务端入口不是一个直接BL调用。本批未逐跳审完中间Objective-C实现、IPC序列化/接收及全部覆盖条件，因此不把这段描述成已经运行验证的端到端交接。

### 3.3 已检查的旁路及未闭合点

输出回调`0x1007a48d0`取得上层给出的数据地址/长度并交给发送队列；`0x1007a5360`将已有数据交给RFCOMM发送。所查函数没有自行构造首次Detection/SYN。

连接block的`dispatch_once`目标`0x1007a4934`注册端点属性回调，不是一个已证实的握手重试计时器。属性回调`0x1007a4c04 → 0x1007a4d78`检查属性变化，调用`0x1007a5628`提取值，最后到虚表`+0xf0`。本批没有解析该间接目标及其全部副作用，故不能宣布所有旁路都已排除。连接错误处理中的数值20000也没有被当成“20秒握手超时”。

## 4. accessoryd先识别实际输入，再建立iAP2

`_acc_endpoint2_createWithUUID@0x10018a96c`将transport/protocol存入端点`+0x18/+0x1c`。`0x10018acbc–0x10018acd4`检查protocol，**为0时跳过**`acc_protocolRouter_initProtocolLayer`。

`_acc_endpoint2_processIncomingData@0x10018e334`区分：

1. 已知protocol：路由输入数据。
2. protocol=0：在`0x10018e5a0`附近调用`acc_protocolParser_detectProtocol`，检测结果仍为0则继续等待数据。
3. 检测成功：保存协议和累积输入，在`0x10018e638–0x10018e65c`初始化协议层、转交原输入、销毁自动识别对象。

自动识别不是仅调用一个名为“iAP2”的解析器：

- `0x100139034`创建protocol3与4两个识别器；`0x100139348`在非空输入上追加数据并运行FSM；`0x10004cce8`按字节调度。
- Detection走`acc_protocolParser_iAP1_run@0x1000b845c`里的特殊分支。校验后，`0x1000b8a4c–0x1000b8a64`检查lingo=0、command=0xee，把结果设为protocol4；对应日志为`iAP2 detected! (detect packet)`。
- 直接FF5A数据另由`acc_protocolParser_iAP2_run@0x1000cf5b8`完成头/载荷校验后识别为protocol4。自动识别为iAP2不意味着该报文已通过后续SYN语义校验。
- `acc_protocolRouter_initProtocolLayer@0x10017a0f0`的protocol4表项到`0x10017a1c4`，调用`iap2_endpoint_create@0x100129350`。

本批纠正了一个定位风险：`acc_protocolParser_iAP2_run`只是协议自动识别器之一，不能把它当成整套iAP2链路解析；漏看iAP1识别器的特殊分支，就会漏掉首次Detection入口。

## 5. Start/Attach不等于主动发Detection或SYN

`iap2_endpoint_create → RunLoopCreateDevice(0x1000cae38) → RunLoopCreate(0x1000cae54) → LinkCreate(0x100033fd0)`选择device FSM并执行`LinkStart(0x100034a70)`。端点随后调用`RunLoopAttached(0x1000cb158)`，设置attachment事件位并唤醒runloop；`RunOnce(0x100008698)`调用`LinkAttached(0x100034a7c)`。

原device状态表基址`0x100219600`中的相关转换为：

| 当前状态 | 输入 | 动作 | 下一状态 |
|---|---|---|---|
| 0 | event0 / Start | `ActionNone@0x100031c50` | 1 |
| 1 | event1 / Attached | `Attach@0x10002f8dc` | 2 |
| 2 | event23 / 收到Detection | `SendDetect@0x10002fac8` | 3 |
| 2 | event2 / 合法新SYN路径 | `SendResetSYNACK@0x10002f920` | 4 |
| 3 | event23 / 再收到Detection | `SendDetect@0x10002fac8` | 3 |
| 3 | event11或12 | null动作 | 3 |

Start与Attach动作本身设置状态/参数并结束当前事件处理，没有调用Detection/SYN发送或创建首次周期发包计时器。因此，“有SendDetect函数”和“调用了LinkStart”都不能单独证明蓝牙一连就主动发送。

state2可直接处理合法SYN，不要求一定先经过Detection回复。反过来，state3收到重复Detection可以再次回发，这是**由重复输入驱动**，不是已证明的自主周期重发。

表中的state/event数字是内部索引，不是线上字段。JSON保留空/保留表项，不把读取记录数当作分支覆盖率。

## 6. Detection回复的生产链已找到

协议层建立后，累积输入经`routeIncomingData@0x10000995c → iap2_endpoint_processIncomingData@0x100009c3c`交给block `0x100009cf8`：

1. `0x100009e38`调用`PacketParseBuffer@0x10000a5d0`。
2. 该解析器在对应legacy检测分支调用`PacketCheckDetect@0x100102e20`；识别成功将packet status设为19。
3. block在`0x100009f84`调用`RunLoopHandleReadyPacket@0x10000b308`，经`RunLoopSignal@0x100007728`转入`RunOnce`；有实际packet时走直接RunOnce分支。
4. `RunOnce`在`0x1000087dc`调用`LinkHandleReadyPacket@0x10000ada0`；其status>18分支用status+4产生FSM事件，因此19对应event23。
5. state2/3的event23调用`SendDetect`，再到`LinkSendDetectCB@0x10019c124`，输出常量`ff 55 02 00 ee 10`。

这闭合了“收到Detection为什么会回发Detection”的指定局部调用链。它没有证明所有event23只能来自此处，也不等于跨进程、跨队列、断开/取消竞态已全部审完。

## 7. 顺带定位到本地profile提供者，但不直接照抄值

`iap2_endpoint_create`在`0x100129454–0x1001294e0`准备传给CreateDevice的本地参数块，常量`0x1001b32c0`起始为`03 7f 1e 7f`，其中本地window为127；并设置MTU/时间值、会话类型版本支持表和扩展项。

这是比“通用默认window=1”更上游的实际端点构造证据，推进了73的profile来源问题。但**本地能力上限、协商工作块、等待确认时活动参数、最后线上的SYNACK字段不是一个概念**。本批不据此把手机窗口改127，也不照抄内部超时极值或宣称实现了全部会话/扩展。

## 8. 已做验证与尚未完成


本批实际完成：

- 从三份镜像读取38个指定函数并记录哈希；其中33个函数有既有`.bin`缓存，全部与镜像一致，另5个直接读取原镜像。
- 重读device初始state0–3相关表项、常量及指定函数的直接B/BL引用。
- 通过原间接符号表核对2个bluetoothd导入；从原dyld缓存核对CoreAccessories封装、selector跳板和selector字符串。共享缓存哈希覆盖这些切片，不冒充整个缓存的重新校验。
- 未执行苹果原函数、未跑新的合成协议向量、未连接蓝牙/车机；上一批测试不能重复计为本批新测试。

复核命令（WSL，工作目录不影响路径解析）：

```text
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_startup.py
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_startup.py --component bluetoothd --address 0x1007a4520 --assembly
```

下一步应优先核对的剩余边界：

1. CoreAccessories客户端selector→IPC服务→端点构造的逐跳参数传递及覆盖条件，确认protocol=0在该路径始终如何消费。
2. 蓝牙端点属性回调的虚表目标、无输入时的上层预算/退出与其他端点提供者，不能把“所查Start/Attach没有计时器”扩成“系统没有计时器”。
3. 实际本地profile进入工作/活动块的生命周期，再处理已确认的pending新SYN恢复与SYNACK重传缺口。

