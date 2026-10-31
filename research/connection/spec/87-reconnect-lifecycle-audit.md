# 87 — ACK-only 与手动断开的生命周期核查


## 1. 范围与结论

接续[86的初始握手错误ACK恢复](86-iap2-pending-ack-recovery.md)，核查七次尚未收到SYN的ACK-only失败；用户本轮另补充“上次手动断开后，车机CarPlay图标仍亮”。这一观察与旧日志中哪次断开精确对应尚未标定，不能自行绑定到某个attempt，更不能沿用“都是强停造成”的结论。

本批结论分开：

- **ACK-only根因未定。** 成功与失败均有手机主动RFCOMM实例，未发现手机故意复用旧IapLink对象；当前日志不足以证明底层句柄/远端协议状态完成复位。
- **手动断开存在明确的实现缺口。** 当前手机没有已审固件的整会话TEARDOWN分支，主要拆单个流再关本地连接；部分音频拆流为异步工作，资源清理不会等待它们全部确认。
- 此缺口值得优先修，但没有证据把“图标仍亮→下一轮缺SYN”直接判成已证因果，也没有证明修它能恢复Android强停场景。

## 2. 成功/失败首包对照

源附件为 `51bc0fbc-6bd2-4cb5-aa32-c58a1b765715/已粘贴的文本.txt`，SHA256 `a2dcb2a14a1dfaa1e1a4876bdbe26f078fa806cf1545382f61a84ae17fa50999`。本批未获得新的实车日志。

| 观察 | 证据 | 对假设的约束 |
|---|---|---|
| 成功和ACK-only都选phone主动方向 | a23f8475、262ad5f0、8ad4898d、273a5a62与七个失败attempt | 不能仅凭主动方向解释失败；所选日志没有第二方向已连接提示，不等于HCI已排除竞争 |
| 成功也可能经过2秒Detection兜底 | a23f8475先发Detection，后收到Detection/SYN并成功 | 不能断言“主动Detection必导致失败” |
| 七次失败只收到同一帧 | `40/1/16/0/0`，日志时间距兜底Detection约29.6–138.3ms | 帧被有效解析并进入pre-SYN等待；这是时序相关，不证明它是Detection的协议响应 |
| 前一轮明确归属蓝牙bootstrap的最后RX | 262ad5f0在PAIR之前RX `40/1/235/10/180`（4301），TX `40/235/1/0/0` | peer seq1与后来的seq1相同，但ACK235与ACK16不同；不能叫作原封不动重放的旧ACK |
| API关闭有返回，后续仍ACK-only | 七次失败中BluetoothSocket.close完成日志可见；随后多次重连仍失败 | API返回不证明对端端点/系统ACL已重建；单纯重复创建Java对象没有解决观察到的状态 |
| 手动取消后也有恢复 | d5db4abf等待中手动断开，之后8ad4898d握手成功 | 中间平台/车机操作不完整，不能据此推广等待某个固定秒数即可恢复 |

当前日志还有一个归属限制：蓝牙iAP与AirPlay Runtime iAP使用同attempt前缀；部分 `Bootstrap` trace仍固定标RFCOMM。AirPlay开始后的所有 `iAP frame` 不能都当成蓝牙包。例如1bb6518b中后续正常ACK16属于已发PSN16的运行时控制交互，不是另一个ACK-only失败。

`DeviceViewModel.kt` 的初始化会输出“应用已启动”，不是Application进程启动专用日志；不能拿这行作为PID变更/崩溃证据。

## 3. 24A446蓝牙连接/输入/销毁按句柄归属

本批重读原镜像和完整指定函数切片，对照汇编与反编译；selector从原镜像桩解析，不只按反编译名字推测。

| 地址（bluetoothd） | 核对结果 |
|---|---|
| `0x1007a3680` | 建立 `com.apple.bluetooth.IAP` dispatch queue，属性参数NULL；保存到对象+0x200。另有connectionUUID→handle与handle→UUID对象映射（+0x208/+0x210） |
| `0x1007a4240 → 0x1007a4520` | 成功回调投递到上述queue；查当前handle对应设备，建立新的CoreAccessories connection/endpoint，写入两个映射；endpoint protocol=0 |
| `0x1007a511c → 0x1007a5200` | 收包携带handle并复制数据，投递到同一queue；以handle查对象，再取endpointUUID交processIncomingData |
| `0x1007a4e4c → 0x1007a4fa8` | 断开回调先处理profile断开结果，随后同queue中按handle取connectionUUID，调用destroyConnection，移除两侧映射；查无对象则跳过销毁块 |
| `0x10062cd3c` / `0x10062d114` | 已有handle查找与断开结果中的集合/映射移除；本批不把通用profile结果处理扩大为完整CarPlay停止合同 |

这是指定事件的归属和串行处理设计，不是“苹果绝不发生迟到回调”的证明；底层重用handle、队列生产顺序、OS进程死亡和远端设备行为未运行验证。手机每attempt创建新socket/reader、单个service/controller的入口门和流关闭可读到，但没有Apple内部handle与endpointUUID的同层可观察信息。

没有从这条路径找到“新端点收到孤立ACK就发送SYN/RST”的依据。保持[84](84-iap2-force-stop-reconnect-audit.md)边界，不把蓝牙句柄销毁混作线上RST。

## 4. 手动断开缺口：整会话停止不同于拆流

### 4.1 当前手机

- `SessionController.disconnect` 先cancel会话job，然后 `Resources.close()`、join。日志 `native stop not requested` 是手机自己写的描述，不是车机返回状态。
- `AirPlaySetupSession.close/closeScreen` 仅为已分配屏幕发 `TEARDOWN {streams:[屏幕descriptor]}`。没有记录或发送整场会话停止的分支。
- `AirSession` 音频 `releaseStream` 通过 `scope.launch { finishClose(...) }` 异步发 `TEARDOWN {streams:[音频descriptor]}`。`Resources.close()`只等待close回调返回，不自动join这些任务；其后控制socket/RTSP client仍会被关闭。
- `Resources.close()`并发调用中第二个调用可提前返回。因此“session resources released”不是所有关闭动作已完成的栅栏。不能简单给整个close加锁，否则可能阻塞解除read/write等待所需的socket关闭。

这是当前源代码的路径核对，不根据日志bodyBytes长度猜测plist字段，也不假装已验证日志APK与当前全部源码逐字一致。

### 4.2 旧日志的可见结果

a23f8475在UTC 05:41:45.693记录User disconnect。TEARDOWN CSeq46、47、48获得200；CSeq50在05:41:45.760发送，05:41:45.873因SocketException失败，没有匹配回复。之后BluetoothSocket.close返回。存在“清理请求尚未确认，控制连接已关闭”的实例，但不能据此判定车机是否已实际收到/执行CSeq50。

该次之后262ad5f0仍成功同步，所以这个缺口也不是“每次正常断开都必然无法重连”的充分条件。用户本轮的图标观察不能未经时间关联就冒充该次日志的车机结果。

### 4.3 原固件的整会话分支

重新核对原AirPlaySender及原dyld切片：

- `EnsureStopped @0x251b5e7c4`：未启用connection sharing或选择全停止时，清stream registry；`0x251b5ea34–ea3c`选择NULL stream数组、内部type2；connected时调用发送helper。helper成功后才到 `disconnectControlStream`；发送错误走独立错误出口。
- `sendTeardownWithStreamDescArray @0x2519ce5c4`：NULL数组意味着**不放streams键**，不等于空数组；`+0x10`共享连接开关非零才放 `teardownType`。普通未共享连接不能无条件加 `teardownType=2`。
- 所审路径是当前控制连接上的TEARDOWN事务，不是关闭一个屏幕，也不是删除蓝牙配对。完整字段及错误出口见[24](24-disconnect-reconnect.md)。本批没有声称已闭合所有上层强制退出路径。

## 5. 建议的下一批实现与验收

优先补**正常手动断开的整会话停止**，不是改首次SYN发起策略：

1. 独立区分用户正常停止、传输已失败、Android强停。能通信的正常停止路径先阻止新的SETUP/控制业务，停生产者，再通过当前control发一次无streams的整会话TEARDOWN。
2. 在响应或有界失败处理完成前保留所需control/event资源；然后确保本地socket及任务关闭完成才允许下一attempt。不能依靠资源析构次序碰巧满足，也不能因没有响应而永久卡住断开。
3. 整会话停止期间避免异步单流拆除、音频所有权通知和晚到SETUP与它竞争；单独关闭音频/屏幕时仍保留既有部分TEARDOWN语义。
4. 补充可归属的日志：停止原因、whole-session/partial、请求与对应响应/失败、控制与蓝牙关闭完成、独立iAP link ID/transport。不要记录密钥、Wi-Fi凭据或完整认证载荷。
5. 单测需覆盖整/部分字段差异、成功与无响应、重复停止、停止中SETUP回复、异步拆流/关闭竞争、正常停止后再次连接；实车验收分别记录App断开、车机退出/图标变化、新attempt握手结果。

不能把这个正常停止路径当作Android force-stop一定能执行的保证。本批仍是研究结论，未实施上述改动。

## 6. 可复核材料

[工具](../tools/inspect_reconnect_lifecycle.py)默认只读；`--write`仅更新[证据](../evidence/reconnect-lifecycle-audit.json)。已运行通过：9个bluetoothd原函数、2个AirPlaySender原函数（另与原dyld比对）、9份手机源码哈希、7个ACK-only向量与一次手动断开的TEARDOWN事务元数据。

该PASS仅表示文件/字节完整性及指定日志提取断言通过，不代表运行了苹果固件、Android生命周期单测或实车测试。本批未运行新的手机回归；86的1005项历史结果不重复计数。

```text
wsl python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_reconnect_lifecycle.py
wsl python3 -B /mnt/d/carvex-research/research/connection/tools/validate_docset.py
```
