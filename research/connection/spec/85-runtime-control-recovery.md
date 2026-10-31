# 85 — Runtime iAP 控制事务与失联清理

日期：2026-10-30。基线：iPhone18,1 / 24A446。状态：`PARTIAL`。


## 1. 现场证据：控制通道已经静默，却仍维持会话

输入：`C:\Users\iamr0s\.codex\attachments\7d27230c-86b0-4af7-85f1-77106445a0c5\已粘贴的文本.txt`。

SHA-256：`a2dcb2a14a1dfaa1e1a4876bdbe26f078fa806cf1545382f61a84ae17fa50999`。以下时间均为日志 UTC，不是本地时间。

| 会话 | 最后成功与紧随事件 | 后续观察 |
|---|---|---|
| `1bb6518b` | 05:46:08，seq20 的 `0x5001` 有 iAP ACK、RTSP cseq45 有200；随后 seq21 的 `0x5001` 无后续控制收包 | 05:46:39 runtime iAP ACK 超时后仍保留视频；05:49:35 控制接收年龄206334ms，未应答单向请求达64，最终 Wi-Fi lost |
| `d15cbf16` | 05:52:22，seq86/cseq40 的 `0x5001` 有 ACK+200；feedback cseq41 有200；随后 seq87/cseq42 无后续控制收包 | 05:52:53 runtime iAP ACK 超时后仍保留视频；05:56:00 控制接收年龄217420ms，未应答单向请求达64，最终 Wi-Fi lost |

日志同时显示本地视频和媒体发送计数增长。它只能排除“所有本地发送线程都停止”，不能证明车机实际显示、触摸或播放正常。

两次都在 `0x5001` 后进入静默是值得追查的关联，但不是字段错误、车机缺陷或加密错序的证明。不得据此删歌曲信息、跳过 ACK、换传输方向或退回已修复的音频算法。

## 2. 原固件闭合的调用链

证据：[runtime-control-evidence.json](../evidence/runtime-control-evidence.json)。工具 [inspect_runtime_control.py](../tools/inspect_runtime_control.py) 把8个函数切片与原 Mach-O 逐字节比较，另核对4处重定位指针与6条关键指令。它没有执行苹果代码，也不是分支覆盖测试。

### 2.1 iAPSendMessage：控制通道，等待结果，不等于读取 body

1. `___carEndpoint_setUpAPAccClientEndpointForIdType_block_invoke @0x251babc44`：普通分支构造 data 参数，`0x251babdc4` 传 `inSendAsync=0`，`0x251babdcc` 调用 `carEndpoint_sendCommandInternal @0x251ae8e90`。另一 RCS 分支仍独立存在。
2. dispatch block `@0x251baaa94` 读取属性 `TransportControlStream`。属性槽 `0x2693e7aa8`、CFString及原字符串均已核对，不依赖反编译器的符号命名猜测。
3. `inSendAsync=0` 分支在 `0x251baacfc` 取 type vtable `+0x38`。`0x251af5a74` helper 设置 stream、`comm`、request buffer；`0x251baad98` 将 **reply 输出指针**设为NULL。
4. 普通 APTransport stream 的 type vtable 是 `0x275fa2d28`，`+0x38` 槽 `0x275fa2d60` 指向 `_stream_SendMessageCreatingReply @0x24fda68f8`。
5. 此 helper 仍安排事务并等待完成。NULL输出只是不取回reply body，**不等于只写不等结果**。timeout分支安排stream失效，详见[22](22-control-wire-contract.md) §6。


RTSP 200与 iAP2 ACK 是两层确认：前者不替代后者。手机保持独立reader/event worker与runtime iAP处理，不在收包回调内同步等待自己要接收的回复。

### 2.2 普通反馈心跳：有回复、有失败路径

`_standardKeepAliveController_sendKeepAliveCallback @0x24fda3f70` 的普通分支调用同一 type vtable `+0x38`，内部type=`keep`，提供reply输出指针。`keep`映射 `POST /feedback`，见[22](22-control-wire-contract.md)。成功会处理响应，失败会安排failed回调；`@0x24fe001e8` 在resumed条件成立时发布Failed通知及status。

`_standardKeepAliveController_timerFiredCallback @0x24fda45bc` 检查已有pending发送：在途时不再无条件排另一请求。此函数中的10秒stall通知、180秒通知抑制不是统一断链超时。

`lkee`分支、SETUP的UDP低功耗保活、屏幕数据口保活均不能与普通 `/feedback` 混为一谈，本批未改它们。

## 3. 手机端实际修改

| 位置 | 修改 | 边界 |
|---|---|---|
| `CarPlayControlRequests.sendIap`、AirSession runtime writer | 普通iAP命令改为等待RTSP完成、检查2xx，独立IO writer顺序消费下一条 | 不改5001字段，不用200冒充iAP ACK；单个命令非2xx只拒绝该命令并使runtime降级，不直接判整个control失联 |
| `CarPlayControlRequests.keepAlive` | 普通心跳等待回复；最多一个heartbeat在途；错过的2017ms timer tick跳过、不补发积压 | 是本地协程调度实现，不声称还原Apple所有队列/计时精度；反馈非2xx使旧control失效 |
| `RtspClient` 异步request | 每个请求捕获deadline，覆盖写锁排队、socket写入与等回复；超时原子标记终局、唤醒所有pending、拒绝后续写入 | 延用现有运行期10秒与建立阶段临时预算；不把它们说成所有固件分支的精确实际timeout，详见[24](24-disconnect-reconnect.md) |
| 控制socket owner | 失效后直接close旧socket，解阻read/write；随后通知会话层清理 | 不拿record/write锁来关闭socket，避免超时处理被同一堵塞写锁卡住；不对新会话socket操作 |
| AirSession failure | 多个等待者/reader观察到同一个终局失败时，只提交一次会话失败 | 清理TEARDOWN对已失效client立即失败，不再向死连接重复等10秒 |

普通request仍按CSeq独立关联，不接受无关响应来确认心跳。其他请求的并发策略、整个Apple native semaphore/HTTP引擎、取消/跨队列顺序及无CSeq接收兼容未在本批完整复刻。同步认证阶段依旧由socket读取预算管理，不偷换为本批异步deadline实现。

`RuntimeIap` 单独ACK超时的降级策略未改；只有控制事务实际失败才终止控制会话，不能把两种失败混为一谈。

## 4. 本轮验证

- 先加两个定向测试，在旧实现上均失败：请求已超时，却仍有 `readerRunning=true` 并允许后续写入。随后实现修复，两项转为通过。
- 新增共9项测试：静默超时、无关CSeq不能确认、iAP等待时event仍能应答、心跳最多一个在途、成功回复和取消、反馈错误/命令拒绝区分、唤醒其他pending、旧/新连接隔离、堵塞写入被deadline解阻。
- `:protocol-carplay:testDebugUnitTest`：993项，0失败、0错误。
- `:core:testDebugUnitTest --rerun`：76项，0失败、0错误。总计1069项。
- `:app:compileXiaomiDebugKotlin`：成功；没有执行assemble或install。已有nullable/冗余空安全与Gradle弃用警告未在本批扩改。
- 静态证据检查：8函数、4指针、6指令一致；不是原固件运行测试。

中间新增测试文件曾有一处泛型默认参数的空格语法错误，修正后定向与完整回归均通过。没有以编译失败结果计作验证通过。

## 5. 下一次实测与未解决项

用户自行打包后，在同一车机正常连接，播放音乐并切歌，触发导航/助手，保留出现问题直到退出的完整日志。无需先强停App或切蓝牙，以免丢掉本次连接的终止路径。

若再次失联，预期能看到明确的 `RTSP ... cseq=... no response in 10000ms`、失败来源与随后的资源关闭，而不是继续维持三分钟。**及时断线是本批失败处理验收，不等于卡顿根因已消失。**

仍待证实：为何该车机在第二条5001后停止回复、实际线上包与字段接受条件、Android进程强停后的恢复、车机端实际视频/音频/触摸表现和重新连接是否成功。若仍失败，下一步应以新日志的首个失败事务选择有针对性的固件字段/时序分支，不回到盲目更换音频参数。
