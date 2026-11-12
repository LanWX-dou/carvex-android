# GalaxyPlay 通话订阅、状态编码与麦克风清理

日期：2026-11-11。独立于仪表导航提交。已修复运行期订阅被丢弃、全局订阅共享、显式字段模式错误转换状态，以及麦克风关闭异常后的本地清理。完整通话卡片和双向蜂窝音频仍未接通；未打包、安装或实车测试。

## 实现变化

- PhoneSubscriptions 改为每条 Link 独立实例；bootstrap 与 runtime、两次连接之间不共享 active、字段集或默认模式。非法 START 原子拒绝，STOP/Link 变化清当前实例。
- AirSession 将 4154/4156/4157/4159 接到 RuntimePhoneSubscriptions。只在当前 CONTROL_READY 与实际消息方向声明下接受；通话组要求 4154 入站、4155 出站，通信组要求 4157 入站、4158 出站。STOP 在 Apple 原表中可选，缺 STOP 不阻断 START；未声明的命令不能修改状态。
- 辅助编码器字段只能取调用方选择与该实例实际订阅的交集。显式字段模式保留平台状态/方向值，默认字段模式才使用 legacyStatus/legacyDirection。p9 来自会议标记，不再误用方向。
- 挂断先撤销麦克风代际并清 installed，再关闭输入。关闭抛异常时记录失败，下一次通话仍可创建；会话关闭仍取消未完成工作。该本地清理不等于远端 TEARDOWN 已确认，不增加重试或延时。

## 原始依据

24A446 accessoryd 原镜像 SHA256 为 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe。

| 原地址 | 确认行为 | 对应修正 |
|---|---|---|
| 0x1001b3158 / 0x1001b317c | 每组 START/update 必需，STOP 可选，方向独立 | 当前 Link 能力门 |
| 0x10011e6e4 | 0..12 空字段、未知 ID 跳过、非法载荷整条失败；无参数/仅 p5 设置默认模式 | 实例订阅与原子替换 |
| 0x10011ece4 | 通信字段 0..17，空载荷，失败不替换旧集 | 独立通信订阅 |
| 0x10011ec18 / 0x10011f020 | 分别清 call/communication active 与字段集 | STOP 独立清理 |
| 0x100120cac / 0x100120f0c | feature+8 为默认模式才查 legacy 表，否则 p2 保留原状态 | 显式状态 4 保持 4 |
| 0x100120e28 / 0x100120fcc | p3 的方向采用同一默认/显式分支 | 不总是转换方向 |
| 0x100120ed4 | p9 读取 IsConferenced | 会议布尔标记 |

辅助编码器没有实际电话 provider 调用，平台状态值不能直接套用 Android CALL_STATE 整数。原状态/方向平台来源、姓名/UUID 获取、多通话模型仍需要独立合同；本次不宣称已完成所有 4155 字段语义。

原表和 6 个原始切片的只读复核位于研究仓库 research/connection/tools/inspect_call_subscription_chain.py，结果 PASS；接收端事实和完整边界位于 research/connection/spec/call-subscription-chain-20261111.md。

## 验证与仍缺少的来源

core、protocol-carplay、bridge 单测及五个品牌 Kotlin 编译通过。新增测试覆盖 Link/实例隔离、两组能力独立、可选 STOP、非法替换不改变旧集、新 Link 重新 START、订阅交集、默认/显式状态和方向、会议标记、挂断关闭异常与会话关闭。

PhoneCallMonitor 只观察 OFFHOOK 活动；它含拨号/保持，不能据此制造 ACTIVE 卡片、通话姓名或逐通话 UUID。当前公共 mixing 回调没有已证的完整通话元数据来源，也没有蜂窝下行 PCM 类目。运行期接受订阅后明确记录 no-runtime-call-metadata-provider，仍不发送虚构的 4155/4158。

现有 type100/telephony 实验输入继续要求实际接收能力、解码器、权限及宿主麦克风消费。它只覆盖上行局部路径；没有对方蜂窝下行或宿主 modem/HAL 消费证据，不能声称双向通话正常。

实车验收分别记录实际 4154/4157、订阅接受与 provider 缺口、接听/保持/挂断卡片、上行麦克风、对方下行声音及挂断后音乐恢复。卡片和双向音频尚缺真实生产者，不能用 ACK 或单测关闭。

## 最终本地验证

导航修复独立提交后，本轮运行：

~~~powershell
.\gradlew.bat :core:testDebugUnitTest :protocol-carplay:testDebugUnitTest :bridge:testDebugUnitTest :app:compileXiaomiDebugKotlin :app:compileOppoDebugKotlin :app:compileVivoDebugKotlin :app:compileSamsungDebugKotlin :app:compileHonorDebugKotlin --offline --console=plain
~~~

BUILD SUCCESSFUL，57 秒；五个品牌编译通过。最终 XML：

| 模块 | 测试数 | failures / errors / skipped |
|---|---:|---|
| core | 121 | 0 / 0 / 0 |
| protocol-carplay | 1137 | 0 / 0 / 0 |
| bridge | 59 | 0 / 0 / 0 |

合计 1317 项；无失败、错误或跳过。原 accessoryd 2 个声明表、6 个切片、状态表/字段跳转和 GalaxyPlay 28 个方法/15 份发送源码哈希复核 PASS；文档本地链接与 diff 空白检查通过。原 docset 的历史完整 FAIL 未改写，不由局部复核取代。
