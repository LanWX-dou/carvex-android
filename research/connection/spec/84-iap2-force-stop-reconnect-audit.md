# 84 — 强停后 ACK-only 重连审计

日期：2026-10-30。基线：iPhone18,1 / 24A446。状态：`PARTIAL`。

## 1. 输入及本次结论修正

用户提供的两份日志：

- `C:/Users/iamr0s/.codex/attachments/ed148566-8569-403d-b2d0-dd081a93d2e7/已粘贴的文本.txt`
- `C:/Users/iamr0s/.codex/attachments/8975b77b-dbd9-4787-ae21-f52968373607/已粘贴的文本.txt`

两者逐字相同，SHA-256 均为
`195d45e36da4179464705818a674f8d1b154e44559ef433e6a3046ac4716a5db`。
第二份不是独立的新复测。日志包含旧版失败和修复后会话，不可混在一起统计。
用户明确回答：第二次成功投屏后到后续失败之间，手动强制停止或重开过 App。
这个回答不能细分是 Android force-stop、杀进程还是 Activity 重开，但足以说明不能把这段缺失的清理日志直接判作自动崩溃。
`[ui] 应用已启动` 也不是 PID 变化或进程死亡的证据（成功握手期间同样出现）。

关键时刻使用日志原始 UTC：

| 会话/时间 | 观察 | 能说明什么 |
|---|---|---|
| a23f8475，05:41:27 | RFCOMM outbound phone，真实 SYN，iAP synchronized；之后网络/SETUP/视频发送 | 不是只把 ACK 容错了，正常握手确实可以推进 |
| a23f8475，05:41:45.693 | User disconnect；部分流 TEARDOWN；05:41:45.883 BluetoothSocket.close 返回 | 有一次明确的 App 内主动断开；并非所有资源/远端状态都已证实释放 |
| 262ad5f0，05:41:52.804 | 再次收到 SYN 并同步；之后 SETUP 和视频发送 | 该主动断开之后有成功再次连接的实例，不支持“每次重连都缺 SYN” |
| 262ad5f0，05:42:03.958 以后 | 控制收包停止增长，5001 重发及 feedback 不再收到响应；视频和麦克风仍有计数 | 控制通道停止响应是独立观察，不等于视频线程死锁，也未证明由5001内容引起 |
| 070da178 / 85d42998 / fdc1adb3 | 新建尝试均 outbound phone；2秒后发Detection，收到40/1/16/0/0；7秒NO_SYN | 只有空ACK，无真实SYN；这些失败未进入认证、网络或音视频 |

不能把“强停后发生 ACK-only”的时序直接当成因果证明，也不能断言车机坏了。可能的残留涉及车机协议状态、手机系统蓝牙承载及尚未审完的恢复入口。
当前没有双端/HCI证据区分这些候选。

## 2. 手机端生命周期只读核对

核对 `Bootstrap.bluetooth`、`SessionController.attempt/disconnect/close`、`IapLink.close`、`Resources`：

- 每次 attempt 创建新 `Resources`，每次蓝牙入口创建新 listener、winner/activeOutbound变量及候选 `BluetoothSocket`，选定后创建新 `IapLink`。未找到故意复用旧socket/IapLink对象的路径。
- RFCOMM选择后关闭其余listener并取消/join worker；取消尝试时释放选定socket。单边源码和API返回并不能证明车机或系统ACL状态也已复位。
- 所有选中会话都走 `initiator=phone`；本日志没有 `other direction also connected`，因而尚无双向竞争的现场证据。
- `IapLink.close` 撤销握手/ACK timer、清协商槽/发送账本并关闭流。不能为新链接继承旧session、窗口或认证，去把孤立ACK解释成最终确认。
- `lastBootstrap` 是先前网络材料，不把新 `IapLink` 直接置为已同步；ACK-only故障发生在读取这些网络结果之前。

另外记录两个代码风险，**不当作本次ACK-only根因，也未顺手修改**：

1. `Resources.close()` 抢到清理权的线程才逐项释放；并发第二次调用会立刻返回。于是 `session resources released` 可早于实际 socket.close 日志（fdc1adb3即如此）。它目前不是可靠的“清理完成栅栏”。下一轮若修，应先复现并发清理/重入/取消，不能简单给close加锁，否则可能把socket解阻也锁住。
2. 当前AirPlay清理以逐流TEARDOWN为主，曾有一个语音流的清理响应因控制socket关闭而未确认。固件整会话停止与部分流停止不同，见[24](24-disconnect-reconnect.md)。但后续仍成功连接，且Android强停可能不执行任何用户态清理；不能宣称补整会话TEARDOWN就能修复强停恢复。

## 3. 原固件局部验证：detach不是线上reset报文

工具：[probe_iap2_detach.py](../tools/probe_iap2_detach.py)。源accessoryd SHA-256：
`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

本轮直接读取原镜像反汇编，并执行原指令：

- `iAP2LinkDetached @ 0x100034bbc`：向FSM投递event14，再初始化active SYN默认参数。
- `iAP2LinkActionDetach @ 0x100031c7c`：本地disconnected回调；不是SendRST。
- `iAP2LinkAttached @ 0x100034a7c` / `DeviceActionAttach @ 0x10002f8dc`：默认参数初始化并进入等待状态；不是无条件发送SYN。
- `iAP2LinkRunLoopRunOnce @ 0x100008698` 的原汇编确认attach/detach分别由runloop事件位分发。这里没有证明Android强停如何映射到苹果平台的事件生产者。

探针8项通过：

1. 从实际构造的state2、3、4、5分别Detach→Attach：到state1再state2，产生disconnected回调，不额外发任何包。
2. 新端点参数下，分别在Detection前/后注入日志里的seq1或seq99、ack16、session0、空payload ACK：不发RST，不发布Connected，不交付数据。随后真实SYN及匹配最终ACK可正常到state5。

首次运行有一项**探针断言写错**：它要求全部历史callback为空，但Detection本身已能产生connected=0回调。改为检查ACK前后callback相同且无connected=1，未改变生产实现或模拟原指令结果；最终8项完整运行通过。

执行方法：

```text
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/probe_iap2_detach.py
```

限制：分配器、队列、timer、transport及callback有明确替身；端点profile构造切片执行原指令，零分配和LinkCreate复制为显式初始化；入包是已校验元数据。未执行完整bluetoothd断连/IPC链、OS进程死亡恢复，也未实车验证。
因此结论仅为：**这些已查分支不支持“收到孤立ACK就主动SYN/RST”的补丁**，不是“固件任何分支都不可能发”。

## 4. 下一步最小复测（无需新包）

车辆停稳后，用现有版本、保留配对和设置：

1. 在ACK-only状态下，手动关闭再开启**手机蓝牙**，等蓝牙恢复后连接一次。此操作会暂时中断手机其他蓝牙设备，不删除配对、不重置车机。
2. 若恢复，使用App内“断开”后再连接一次；暂不强停，以获得正常释放路径对照。
3. 导出含这两次新时间戳的完整日志，记录是否真正显示画面。

若步骤1恢复，缩小到“承载/对端状态需重新建立”的恢复路径，但还不能区分责任方；不应直接实现每次连接自动开关蓝牙。
若仍只有ACK，则继续查RFCOMM/HCI实际建链与首包，或取得同车iPhone正常恢复的对照；不要延长等待、伪造SYN参数或清配对掩盖分支。

手机端7秒NO_SYN仍是应用安全预算，不是已证明的iPhone全局等待时限。本轮未改它，也没有运行/冒称新的Android测试结果。
