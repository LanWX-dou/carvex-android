# 75 — iAP2握手三项修复批次


后续状态：本章保存75批次的历史实现/测试；扩展重复项勘误已在[77](77-iap2-extension-wait-boundary.md)落实，不再是待修问题。历史哈希/测试数量未覆盖改写。

## 1. 已落地的三项

### 1.1 pending阶段收到新SYN

在已经发出SYNACK但尚未完成纯ACK确认时，收到不同序号的合法SYN现在进入新的协商世代：

- 清理旧的控制会话、接收/发送窗口、半包、ACK队列和epoch观察者；
- 旧SYNACK的ACK不能提交新世代；
- 使用新的本地序号继续回SYNACK，支持序号从255回到0；
- 新SYN不把重传次数清零；proposal计数和SYNACK重发计数分开；
- 新一轮仍受有界的proposal预算约束。

这对应24A446 state4/event2到`SendResetSYNACK`的有界行为。相同序号、完全相同的SYN仍走缓存SYNACK重发；相同序号但内容变化尚未宣称为合法重协商。

### 1.2 SYNACK可靠重传

发送SYNACK后现在安装独立定时器。定时器与收到完全相同SYN触发的重发共用活动阶段预算；成功纯ACK、Detection、fresh SYN、显式关闭或输出失败都会取消旧定时器。定时器失败只报告一次，并关闭链路，避免旧定时器在新世代继续发包。

待确认阶段使用24A446 `Attach/ResetSYNACK`所对应的活动默认重传预算（本批按30次、1000ms建模），**不读取尚未提交的对端提议作为待确认计时器**。协商提交后，数据发送继续使用已确认的本地/对端参数；这两个生命周期没有合并。

这补的是73中“写出SYNACK后静默时只能等待”的缺口，不是首次蓝牙连接后主动发Detection/SYN的策略改变。

### 1.3 扩展集合校验

**勘误（后续76原字节复核）：本项已实现的重复项拒绝条件偏严，尚待修正手机代码。** link 2/3 的SYN扩展目前在回复前校验，实际代码允许空集合，或恰好包含一次`0x54`和一次`0x55`；未知项、单独一项和重复项均拒绝。这里描述的是当前代码行为，不是正确的原生合同。回复仍不自动声明本地未实现的扩展能力。

原函数`0x1000d4ee0`将`0x54`和`0x55`分别置两位，未知项置高位，按**OR**汇总，最终接受零或两位全在的结果。重复且成对的`54 54 55`仍会得到3；此前“Set会错误放过重复项”的结论错误，明确撤回。详见[76 §6](76-iap2-xpc-handoff-hid.md#6-75扩展校验勘误已确认手机端有偏严条件)。整个SYN仍有独立的数量/长度/session检查。

## 2. 代码与测试

生产改动：

- [IapLink.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt)：pending世代、活动SYNACK定时器、预算分离、扩展集合、失败/关闭竞态。

新增/调整测试：

- [IapPendingSynchronizationTest.kt](../../../android/protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/core/IapPendingSynchronizationTest.kt)：新SYN、旧ACK、序号回绕、Detection取消、定时重传、预算、输出失败、关闭、扩展集合和半包输入。
- [IapLinkSynchronizationTest.kt](../../../android/protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/core/IapLinkSynchronizationTest.kt)：调整重复SYN预算为活动默认值，并保留版本/协商回归。

本批定向命令：

```text
gradlew.bat :protocol-carplay:testDebugUnitTest \
  --tests io.github.iamr0s.carvex.carplay.core.IapPendingSynchronizationTest \
  --tests io.github.iamr0s.carvex.carplay.core.IapLinkSynchronizationTest \
  --no-configuration-cache
```

本批历史定向结果：67 tests，0 failures，0 errors，0 skipped；编译成功。包含当时重复项拒绝条件的完整模块回归：116 suites，872 tests，0 failures，0 errors，0 skipped。76复核发现该条件和对应测试预期偏严，因此通过数量不能证明这一项符合苹果；76未修改手机代码，也未重跑这些测试。

## 3. 不要误读的地方

- 这不是APK，也没有打包、安装或连接实体车机。
- 通过的是内存流协议测试，不是苹果代码执行，也不是实车兼容证明。
- pending阶段的30次/1000ms是本批对24A446活动默认参数的实现模型；所有承载、上层超时和跨进程入口仍需后续核对。
- 第二次SYNACK完整重协商、session表完整合同、窗口/profile提供者和Identification仍未全部闭合。

实现后应在同一车机、同一手机构建上分别记录：重复SYN、静默等待、fresh SYN、含54/55扩展、非法扩展和断开重连；日志需能区分epoch、SYNACK重传编号、最终确认与真实车机显示结果。

## 4. 77批次后续勘误

[77](77-iap2-extension-wait-boundary.md) 已完成本节所述扩展门的手机端修正：原生 OR 语义允许 `54/55` 成对重复，当前实现不再用“恰好两个字节”拒绝它们；数量、长度和 session 独立门仍保留。75中关于“重复项均非法”的文字是历史快照，保留以便追溯，不应作为当前代码行为。77还确认普通蓝牙 type=2 的受限模式入口不可达，并将发现的5秒睡眠断言到期分支与iAP2握手等待分开；首次发起策略未改变。
