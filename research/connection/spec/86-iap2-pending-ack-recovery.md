# 初始 iAP2 握手：错误 ACK 的同链路恢复


## 1. 日志中的两类失败不能合并

附件 `51bc0fbc-6bd2-4cb5-aa32-c58a1b765715/已粘贴的文本.txt` SHA256 为 `a2dcb2a14a1dfaa1e1a4876bdbe26f078fa806cf1545382f61a84ae17fa50999`，与此前 `7d27230c-86b0-4af7-85f1-77106445a0c5` 附件一致，不是本次修复后的复测。

本批针对 attempt `7f019410`（下列时间均为 UTC）：

| 时间 | 报文/结果 | 含义 |
|---|---|---|
| 05:45:36.949412 | RX `80/105/0/0/13` | 真实 SYN 已到达 |
| 05:45:36.949793 | TX `c0/27/105/0/13` | 本方提议的初始 PSN 为27 |
| 05:45:36.996597 | RX `40/105/16/0/0` | 对端 ACK 为16，unsigned gap为11 |
| 05:45:36.997196 | `Unassociated SYN ACK` | 旧代码立即失败，随后关闭 BluetoothSocket |

SYN body 为 `0105080005dc00491e030a0002`。日志只证明 ACK 与当前提议不匹配，不能证明 ACK16 的来源或车机内部状态。

另有七次只有 `40/1/16/0/0`、没有 SYN、最终 `NO_SYN` 的失败：`070da178`、`85d42998`、`fdc1adb3`、`cad30f56`、`201ee382`、`bbde96dd`、`23273c32`。本批不改变其处理，也不声称解决该根因。参考[84 — 强停后重连审计](84-iap2-force-stop-reconnect-audit.md)。用户确认存在手动强停/重开，不能据“应用已启动”推断自动崩溃。`273a5a62` 则握手成功后进入另一类 Wi-Fi lost 失败，亦非本批对象。

## 2. 24A446 的对应路径

基线 iPhone18,1 / 24A446，accessoryd SHA256：`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

| 原函数 | 本批核对的条件/效果 |
|---|---|
| `_iAP2LinkHandleReadyPacket @0x10000ada0`，特别是 `0x10000afdc..0x10000b00c` | ACK位、send-valid、有效可靠模式下计算 `(lastTx - ack) & 255`；超出有效 peer window 投 event19 |
| `_iAP2LinkSetDefaultSYNParam @0x1000328b0` | Attach 后有效窗口为1；对端刚提出的 window5 尚未提交，不能拿它作为 pending 的有效窗口 |
| `_iAP2LinkDeviceActionSendRST @0x10002fb54` | state4/event19 → state3；清序号/ACK及队列、恢复默认有效参数和本地协商工作参数，输出零序号 RST |
| `_iAP2LinkResetSeqAck @0x1000346c8` | `resetCounters=false` 保留提议/重传计数和 packet version，不补充预算 |
| `_iAP2LinkDeviceActionSendSYNACK @0x10002fcd4` | 复位后新 SYN 可重新生成初始 PSN；RST 的 PSN0 不等于下一 SYNACK 必须用0 |

原输出为 `ff5a0009100000008e`，即 flags=0x10、seq/ack/session均0、空载荷。本局部没有 ConnectedCB(0) 或关闭传输；迟到旧 ACK 不进入 ready，新 SYN 与正确最终 ACK 可使 state3 → 4 → 5。

### 可复跑证据及限制

[探针](../tools/probe_iap2_pending_ack.py)复用既有 `firmware/tools/ipsw-research/native-supervisor24.py`。默认只读；`--write` 仅写本目录[证据 JSON](../evidence/iap2-pending-ack-recovery.json)。记录源镜像、runner 和7个原函数切片哈希。

- 75项：link版本1/2/3 × 初始PSN0/1/27/254/255 × unsigned gap0/1/2/11/255。
- 另外3项：各版本尚未生效的零重传提议；有效默认可靠参数仍触发相同复位。
- 包含精确日志 PSN27/ACK16，不只覆盖同差值的随机序号。tick为显式替身，初始PSN仍由原提供者及发送函数产生。
- gap>1 断言 event19、零RST、清队列/账本、计数保留、无断开回调；再注入迟到ACK、新SYN和正确ACK，验证局部恢复。

共78项通过。执行的是有界原指令，平台队列、分配器、timer、tick、transport、callback使用替身，入包元数据为已校验帧的合成输入。**不是完整 iPhone 蓝牙运行、不是车机互通测试，也不是全分支覆盖。**

## 3. 手机实现与明确保留的差异

生产变更仅位于手机 `protocol-carplay/.../core/IapLink.kt` 的 `exchangeSynchronization`：

1. 只在 `generation==0`、已有待确认 SYNACK、`flags==0x40`、session0、空载荷、peer PSN等于当前提议对应的peer PSN、unsigned gap>1时恢复。
2. 撤销旧提议、定时器、session及epoch，发送零RST，继续用同一个传输和同一个输入读取者等新SYN。
3. 复用 `SynchronizationBudget`，不重置提议或重传次数；旧epoch的finally/timer不允许清理或写入新一轮。
4. 迟到旧ACK不确认旧提议；只有新握手的正确最终ACK才发布控制session/schema并增加generation。
5. 新SYN未到达时继续使用既有有界pre-SYN期限。该期限是本地安全策略，**不是从固件恢复的超时值**。写RST失败、非法新SYN、用户关闭仍分别走失败/取消路径。

原指令局部的 gap1 会进入ready，本批不启用该放宽，仍保留严格ACK归属失败；其他包型、已连接后的重新同步也不泛化。初始序号仍用手机既有随机生成方式，不冒充固件tick提供者。这里是指定异常分支对齐，不是完整固件等价。

尚未收到任何SYN时的孤立ACK仍只等待；不因此主动发SYN/RST，不延长原7秒总等待，不切换蓝牙方向、不清配对。恢复路径的有界重试并不保证真实车机会发送新SYN。

## 4. 回归与复测

先在旧实现上运行两项复现测试，均因收不到RST/立即 `Unassociated SYN ACK` 失败，修改后通过。新增测试最终共12项，覆盖恢复成功、无新SYN超时、gap边界、各版本/零重传提议、旧timer、提议及重传预算不补充、写失败、非法新SYN、主动关闭、其他包型和连接后边界。

旧 `IapPreSynTest` 和 `IapLinkSynchronizationTest` 中要求窗口外ACK立即断开的预期改为RST后仍未ready，保留禁止错误确认的断言；`IapRenegotiationTest` 的私有入口反射调用补上新参数。第一次全量运行暴露后两项旧测试未同步，未通过改生产逻辑迎合它们。

最终完整协议回归1005项 / 125 suites通过，失败、错误、跳过均0；core 76项 / 12 suites维持通过，本批任务为UP-TO-DATE。小米端Kotlin编译本批已实际执行成功，最终复跑复用产物。完整记录见 `D:/carvex-research/android/docs/iap2-pending-ack-recovery-2026-10-30.md`。运行命令：

```text
wsl python3 -B /mnt/d/carvex-research/research/connection/tools/probe_iap2_pending_ack.py
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
wsl python3 -B /mnt/d/carvex-research/research/connection/tools/validate_docset.py
```

用户自行打包后只需保持现有配对测试连接和App内断开重连；失败时保存完整日志。若命中本分支，应出现 `pending ACK outside active window`、零RST、新SYN及 `iAP synchronized`；只有前两项而没有新SYN仍不能算恢复成功。七次ACK-only问题继续OPEN，不宣称偶发连不上已全部解决。
