# 65 — 手机端第二批：Identification 生命周期与运行时更新

日期：2026-10-29。目标基线仍为 `iPhone18,1 / iOS 27.0.1 / 24A446`。依据[64深度审阅](64-identification-deep-review.md)、[16生命周期](16-identification-lifecycle-branches.md)、[18核心字段](18-identification-core-field-branches.md)，本批将**初次识别、拒绝后纠正、取消、增量更新**拆开并接入手机真实接收路径。不是完整Identification字段校验，也不是所有车辆兼容完成。


## 1. 已实施的状态边界

下列状态名是Android本地模型，**不是苹果原状态数值**。发送返回代表当前本地链路操作完成，不是车机业务已接受，更不是视频就绪。

| 事件 | 修改后的手机处理 | 验证/限制 |
|---|---|---|
| 发起识别 | 先STARTING，当前世代1D00发送成功才STARTED | 仅收到1D01不会从IDLE制造识别事务 |
| 初次/纠正1D01 | 只在STARTED或RETRY_PENDING解析 | ACCEPTED等状态迟到的1D01不重跑/不替换 |
| 候选合法 | 先ACCEPTING，再发1D02；成功后提交身份和能力 | 发送失败不会被参数catch捕获并误发1D03；未发布的候选丢弃 |
| 候选不合法 | 只处理已知参数错误，成功发1D03后RETRY_PENDING | 可在同一link再次收到纠正1D01；AA已成功时不重启AA |
| 拒绝输出 | 普通拒绝项使用空的同ID TLV；整条拒绝可为空body | 没有线上reason字节；所有路径复用generation/deadline保护的send，不再存在漏保护的raw发送 |
| 拒绝后等待 | 保留原识别deadline，不重发1D00、不续期 | 仍是原有本地默认10秒预算；测试只能缩短，不宣称苹果采用此计时器 |
| 收到1D05 | 仅STARTED/RETRY_PENDING变CANCELLED并结束本次协商；不发1D03 | ACCEPTED、IDLE等不撤销已接受身份；终止当前Android协商是本地策略，不等于完整苹果通知/UI生命周期 |
| 收到对端1D03 | 保留现有本地终止策略 | 与本机成功发送1D03后的同link纠正不是一回事 |

原固件引用入口：1D01 `0x10013bcc8`、接受 `0x100050dcc`、拒绝 `0x10013b540`、取消 `0x10013b28c`。原授权异步回调、拒绝scratch为空时不发送的分支和完整feature cleanup仍未复制；本批不据局部状态相似宣称整个原事务等价。

## 2. 1D06不再使用初次识别解析器

新增 `IapIdentificationUpdate` 和连接绑定的 `AcceptedIdentification`：

- 只有接受1D02后的对象可接收更新；AA是否已经完成与这条身份更新门分开，更新本身不制造认证成功。
- 按线上顺序处理0–5。缺失保留原值；`00`可更新为空串；合法重复取最后值。任一已知字段缺末尾NUL/零字节值使整次更新丢弃，后续合法重复不能掩盖先前错误。
- `41 00 42`拒绝；`41 00 42 00`允许CString framing并沿用现有文本转换；不自行增加“必须非空”或“禁止中间NUL”。
- 6/7、12/13、34及其他更新字段不改初次能力声明；当前回调只生产0–5身份。未知更新字段与未知初次字段不是同一规则。
- 更新不发1D02/1D03，不重新认证、不重启业务。初次`rawParameters`作为原消息证据保留，不伪造一份合并后的原始报文。
- 身份快照原子发布，格式错误不留下部分更新；日志只写字段号/状态，不输出身份值或坏字节。
- 同步`invalidate()`与更新串行；关闭后即使generation/epoch仍相同，也不能继续处理。旧generation/epoch在解析前拒绝。

原更新入口/回调/merge为 `0x100050934 / 0x100050458 / 0x100050744`。末尾NUL来自getter `0x100067ee4`。JVM UTF-8转换仍不等于完整CF转换/Unicode/NULL行为；内存分配失败与原生资源缺陷不照搬。

## 3. 真实调用路径与清理

1. `Bootstrap.negotiateSession`：在等待认证/网络交接期间使用同一个accepted对象，更新不替换6/7；异常退出使对象失效。
2. `WifiBootstrap.identification`：携带本轮绑定，`SessionController`交接后的蓝牙poll实际消费1D06以及迟到1D01/1D05。重新发现端点不丢失该对象；新连接重新协商，不从previous bootstrap继承认证/身份。
3. `RuntimeIap`：运行时独立协商返回本link对象，核对generation、epoch、关闭/降级状态后才提交，再通知`AirSession`能力就绪。旧绑定或关闭后晚返回的结果失效，不能重新发布能力。运行时poll在NowPlaying等业务回调之前消费Identification消息。
4. 蓝牙epoch失效、资源释放、源链路脱离，以及Runtime关闭/降级，都使身份句柄失效。

交叉审阅修正了本批引入的两个竞态：蓝牙检查不能把session已清空改写成丢失EOF原因的普通错误；源链路脱离必须先发布`sourceDetached`，再使身份句柄失效，避免并发旧命令将正常脱离误报为整段失败。另将AirSession能力发布移入运行时成功提交边界，避免关闭后协商结果再次写回旧能力。蓝牙真实系统回调和交接竞态尚无设备执行证据；这里分别使用源码复核、已有handoff单测及编译检查，不宣称Android全链路并发已穷尽。

## 4. 测试预期与结果

测试发送函数不再自动补齐被故意省略的字段。正常初次消息改用显式0–9/12/13夹具，8/9使用字节/BE16形状；这只是该合成输入，不把100写成所有承载的provider常量。删除“8/9是未知字符串、苹果也忽略”的错误预期，原完整1D06夹具改为局部身份更新。

| 测试组 | 项数 | 本批涉及的断言 |
|---|---:|---|
| IapIdentificationUpdateTest | 10 | 0–5、缺失/空、重复、末NUL、错误原子性、忽略其他更新字段 |
| AcceptedIdentificationTest | 9 | 能力不变、无身份日志泄漏、旧绑定、迟到取消/识别、失效并发 |
| PeerNegotiationControllerTest | 19 | 发送待完成/成功、拒绝可纠正、取消条件、认证独立 |
| BootstrapNegotiationTest | 45 | 真实合成字节流上的拒绝字节、同link纠正、AA保持、发送失败、epoch变化、deadline不续期、更新/取消 |
| RuntimeIapTest | 11 | 真实SYN/ACK/CSM进入生产runtime接收器，更新无应用应答、普通消息转发、关闭/降级/协商晚返回、状态发布顺序 |

上述94项为最终全量协议测试的子集，不能额外相加。Runtime新增fixture明确合成AA/Identification结果，验证接收器和生命周期，不是执行真实AA、苹果原代码或真实车机。

第一轮定向87项通过（当时Runtime只有4项旧测试）。最终全量：`protocol-carplay`103组/713项，`core`12组/79项，共**792项，0失败、0错误、0跳过**。相较63记录增加48项；数量不表示苹果全分支覆盖。测试交叉审阅发现一条关闭顺序断言只在fail返回后观察，已加强为DEGRADED/CLOSED回调当场记录失效状态后重跑。

`app:compileXiaomiDebugKotlin`成功，包含bridge编译；未请求assemble/bundle/install。已有nullable/冗余断言、弃用特性等警告未扩大范围清理。命令：

```powershell
$env:JAVA_HOME='C:\Program Files\Android\Android Studio1\jbr'
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --no-configuration-cache
```

最终源码和测试报告身份另存[本批快照](../evidence/identification-lifecycle-batch2.json)，不覆盖15–18旧审计哈希。工作树在本批前已有大量修改，整个HEAD diff（尤其音频、UI、日志）不是本批变更清单。

## 5. 下一批边界：初次字段合同仍未完成

本批先修生命周期，使后续收紧解析时能正确拒绝/纠正；**没有把初次1D01完整校验一并冒充完成**：

- `IapIdentifyInfo.parse`仍是原初次解析器，重复标量/消息列表及语言集合规则尚未对齐。
- Bootstrap初次required仍为原有0–7/12/13出现检查，缺8/9成功集合、provider/承载上下文。12/13出现并不代表内容已经验证。
- 真未知初次字段、全局注册分派、全部feature validator及消息归属/方向拒绝仍未接入。已删除错误“苹果统一忽略”的注释，日志改为明确feature validation deferred。
- 必须继续按15/17/18建立有序解析、成功集合、重复/空值与真实provider规则，不能只加8/9到列表或固定100/500。
- 源版本仍是过渡组合；认证/SAP未实现门槛未删除。没有新增车型白名单、修改车机或声称所有车均可连接。
- G4及后续G5–G12仍为PARTIAL/OPEN；实车首帧、持续画面、重新连接仍`NOT_RUN`。

下一步应针对初次字段合同落实下一批，并沿相同真假分支/错误副作用标准继续网络、AirPlay及视频阶段。
