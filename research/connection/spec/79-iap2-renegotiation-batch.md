# 79 — 手机端 pending SYNACK 再次协商实现


## 1. 已实施

生产修改仅在[`IapLink.kt`](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:445)的握手协商区域；该文件其他区域与本轮开始时逐字比较一致。保留仓库内原有未提交修改，没有重置、提交或批量格式化。

| 环节 | 新行为 |
|---|---|
| 当前提议 | `SynchronizationWork`分开保存本地实际回复与最新peer参数，active字段另存 |
| 第二及后续SYNACK | 通过形状、ACK关联、完整解析与能力门后，在当前work上逐字段合并，生成新PSN的SYNACK，保持pending |
| 收敛字段 | link版本、retry/ACK timeout、retries、maxCumAck逐轮取min；不是每轮回到最初提议 |
| 接收能力 | 本地方window/接收MTU仍受本地配置约束；peer window/MTU更新为最新声明，TX MTU另外受本地TX上限约束 |
| session/扩展 | 接纳最新的受支持control ID/version，但只回复control；扩展声明仍为空，不承诺额外服务/54、55业务 |
| 完成 | 只有正确关联最新本方PSN、对端PSN及纯ACK形状的确认才提交；generation/session、链路与报文版本不在中间提议时启用 |
| 重复 | 当前已接纳输入的精确重复，在新ACK关联检查前识别，重发相同待确认SYNACK，不生成新PSN |
| 新纯SYN | 重建本地work、更新epoch；继续使用本次提议/重发预算 |
| 超时 | 新提议取消旧timer并安装新timer，仍使用pending默认1000ms/30次；未确认的20ms或零重传参数不提前控制timer |
| 预算 | 新提议与重复/timer重发计数独立，第二SYNACK不补充任何预算 |

修复了78复现的“车机接受我们自己提出的1000ms、10ms、maxCumAck0、control-only，反而被误拒绝”路径。相同参数的第二SYNACK也按所审device状态4的event4/6继续SYNACK，不直接发纯ACK并ready。

session只在最终确认后发布；所选control version继续由现有`IapStartupPolicy`供后续启动消费。ready标志`negotiatedControlSession`最后写入，避免其他消费者先看到session、后看到未更新的active参数。

## 2. 有意保留的边界

- **可靠与noRetransmit之间的中途切换**：明确报`SYNC_MODE_CHANGE_UNSUPPORTED`，不把普通可靠合并套到原生event7等分支。首次noRetransmit及同模式再次协商保留，最终确认前仍重传SYNACK；本地方window策略未宣称完整原生一致。
- **同PSN但帧内容变化**：不是精确重发，明确报`SYNC_SAME_PSN_CHANGED`。不是声称原生所有此类组合均断链。
- **不合法输入**：继续严格长度、数量、重复ID/type、版本及feature集合检查，不移植原生修正器的全部容错或截断解析行为。
- **本地能力模板**：没有把window改成127，没有把超时改成65535/32767，没有增加未实现的session服务；不同平台的真实能力仍需单独对齐。
- **任务范围**：不改第一次Detection/SYN发起策略，不改已连接态所有异常SYNACK的处理，不扩展XPC/电源追踪，不增加车型开关。

因此这是78有界可实施部分，不是“已经完整复刻iPhone所有链路分支”。后续仍需全Identification比较及真实车辆验证。

## 3. 测试和旧预期纠正

新增[`IapRenegotiationTest.kt`](../../../android/protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/core/IapRenegotiationTest.kt)22项测试，覆盖：

- 接受本方counterproposal、同一epoch内多轮合并、latest peer限制、仅确认后发布session与schema；
- link3→2、2→1以及不从2升3；已建立link2重连期间继续用旧framing、确认后切换新framing；
- 新session/control version生效后的实际收包；未实现额外session/feature不被承诺；
- 精确重复第二SYNACK、timer只重发当前回复、新提议与重发预算独立且不重置；
- 对端PSN回绕、本地PSN255→0（调用既有私有恢复入口的显式sequence实参，无生产test hook）；
- 错误旧ACK、data代替确认、错peer PSN、非法参数、同PSN变更、可靠模式切换保护；
- Detection、close、输出异常，以及最新peer MTU不突破本地TX能力。

旧`IapLinkSynchronizationTest`、`IapPendingSynchronizationTest`的几项预期同步纠正：第二SYNACK不再直接ready；合法字段变化不再一概拒绝；MTU在确认后采用最新peer值并受本地上限限制，而非永远取历史最低值。不是删测试来隐藏回归，非法输入和模式切换负例在新增测试继续覆盖。

测试历史：先仅新增测试，在原生产代码上运行`acceptsOurCounterproposalWithoutPrematureCommit`，1项失败（没有收到期望下一轮SYNACK）；修改后首批新增测试通过；随后补充边界测试，并完成5个类的定向108项、0 failures/errors/skipped。

完整协议模块回归：117个XML suite、897项、0 failures / 0 errors / 0 skipped。运行命令为`:protocol-carplay:testDebugUnitTest --no-configuration-cache`，没有运行assemble/package/install；生产与测试Kotlin编译同时成功。


## 4. 用户复测

可自行构建手机App，先测试原本能连接的车，确认没有连接回归；再测原先停在iAP2的车。无需新增开关或车型配置。

保留从本次蓝牙连接建立到失败/显示画面的完整日志，重点看：

1. `iAP sync proposal #...`：是否出现第2轮及后续轮次，PSN和参数怎样变化；
2. `iAP synchronized ... proposals=... epoch=...`：是否最终收到确认并生效；
3. 如失败，区分`Unassociated SYN ACK`、`SYNC_MODE_CHANGE_UNSUPPORTED`、`SYNC_SAME_PSN_CHANGED`、提议预算或重发预算耗尽。

本批日志只记录协议参数和阶段，不增加凭据/认证材料日志。不要把单边`synchronized`当作已完成Identification、网络或车机显示。

## 5. 历史证据保持不变

78的JSON与16个差异探针保留修改前快照，不改预期伪装历史结论。它的`--check-implementations`会因本批手机源码更新而不再通过；只读原固件复核仍可独立运行。79新增证据记录修改后文件和测试结果，不覆盖78。
