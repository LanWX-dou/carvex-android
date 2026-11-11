# GalaxyPlay 0.1.212 通话链路修复与剩余来源缺口

日期：2026-11-11。导航先独立提交为 Android `2daaf82`。通话本轮修复运行期订阅、连接隔离、辅助状态编码及麦克风关闭异常；完整通话卡片和双向蜂窝音频仍 OPEN。音乐由用户确认正常，保持现有行为。

通话 Android 独立提交：`9c866b3abcf5ae30155e5d499ecd10457e586b4e`。core 121、protocol-carplay 1,137、bridge 59 项测试全部通过，合计 1,317 项；五个品牌 Kotlin 编译通过。18 份文档的 139 个本地链接和空白检查通过。

## 原 Apple 订阅与编码分支

基线为 24A446 原 accessoryd，SHA256 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。所审 6 个切片、声明表、状态表与字段跳转记录在[证据 JSON](../evidence/call-subscription-chain-20261111.json)。

| 表 | START | update | STOP | 必需与方向 |
|---|---|---|---|---|
| `0x1001b3158` | 4154 | 4155 | 4156 | START 入站/update 出站必需，STOP 入站可选 |
| `0x1001b317c` | 4157 | 4158 | 4159 | START 入站/update 出站必需，STOP 入站可选 |

每项原表为 12 bytes，直接读出消息 ID、方向和 required，不从名字判断 optional。新 runtime 门按当前 CONTROL_READY、实际声明及对应组授权；没有 STOP 声明仍可 START，未声明命令不改变当前状态。

startCallStateUpdatesHandler（`0x10011e6e4`）：`0x10011e82c..0x10011e85c` 对 ID 0..12 校验空载荷并区分 p5；超出范围先跳过。载荷非空跳到失败，不写旧字段集。无参数或只有 p5 在 `0x10011e904..0x10011e940` 追加默认 0..4，`0x10011e980` 将默认模式写 feature+8。新显式 START 替换字段集和模式。

通信 START（`0x10011ece4`）在 `0x10011ee2c..0x10011ee48` 对 0..17 采用相同空载荷校验。STOP（`0x10011ec18/0x10011f020`）独立清除 call/communications flags 与字段集；原 handler 不检查业务参数，不新增猜测性的 STOP 字段规则。

callStateUpdateHandler（`0x1001208f8`）先检查 feature+0x0a 已订阅，再初始化 4155 并逐个选定字段编码。p2 跳转目标为 `0x100120cac`：

- feature+8=1 时，用 status-1 且边界 <6 读取 `0x1001b3248` 的原表 3,3,1,1,2,1；其他状态走 0。
- feature+8 不是 1 时，`0x100120f0c` 保留原状态，`0x100120fb8..0x100120fc8` 写 p2 U8。
- p3 在 `0x100120e28` 检查同一模式；默认模式把方向 1→0、2→1、其它→2，显式模式经 `0x100120fcc` 保留原值写 p3。
- p9 跳至 `0x100120ed4`，读取的是 IsConferenced，写布尔 U8；不是再次编码方向。

因此旧辅助函数对所有订阅执行 legacy 转换是实现错误。例如本版 GalaxyPlay 请求的显式字段集包含 0/1/2/3/4/11，源状态整数 4 应保持 4，而不是 1。修复依据原 Apple 条件分支；GalaxyPlay 的 ACTIVE=4 只用于接收兼容对照，不替代平台电话来源证据。

## 实施与可验证范围

PhoneSubscriptions 从全局对象改为 Link 实例。bootstrap 与 runtime 各自管理；runtime Link 变化清订阅，重新 START 后才接受对应模式。辅助编码只能使用实例实际字段和调用方选择的交集。AirSession 接入四条订阅命令，接受订阅后单独记录 provider 不可用。

CallMicrophoneSession 在挂断/关闭时先撤销代际并清 installed，关闭抛异常仍允许下一通话创建、会话取消及清理。失败仅记录，不作为远端 TEARDOWN 成功，也不触发盲重试。它是本地资源管理修正，不增加未证的 Apple 时间行为。

代码及验证说明见[Android 实施记录](../../../android/docs/fixes/2026-11-11-call-subscriptions-chain.md)。相关模块测试覆盖隔离/重连、字段模式、能力和 STOP、非法替换、订阅交集及关闭异常。原字节复核：

```powershell
python -X utf8 -B research/connection/tools/inspect_call_subscription_chain.py
python -X utf8 -B research/connection/tools/inspect_galaxyplay_receiver.py D:/home/GalaxyPlay.apk --check-android
```

## 未接通部分

当前 PhoneCallMonitor 仅给出聚合 OFFHOOK 活动，包含拨号/保持；不能直接翻译为对方已接听、逐通话状态、姓名、方向或 UUID。已审公共 CarWith mixing 回调未证明提供这些元数据。4155 原平台字典的全部枚举、空 UUID/多通话字段边界也未由本次关闭；不会发送虚构卡片。

现存 type100/telephony 是实验性车机麦克风上行，未建立蜂窝下行 PCM 生产者。助手共享队列不能证明电话 modem/HAL 使用它；对方声音或上行消费需要真实设备证据。完整元数据和双向音频仍 OPEN，分别需要可调用的宿主来源及运行日志。接收端细节见[GalaxyPlay 核查](galaxyplay-receiver-audit-20261111.md)。没有打包、安装或实车测试。
