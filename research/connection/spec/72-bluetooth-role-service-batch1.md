# 蓝牙第一批：手机角色与服务候选

日期：2026-10-30。用户授权后实施，仅修改 `D:\carvex-research\android` 手机端的蓝牙角色、服务候选与诊断。依据 [69 — 固件角色与连接方向](69-bluetooth-role-direction-audit.md)、[71 — Android可实现性](71-android-bluetooth-feasibility.md)。


## 1. 改动范围

| 文件（相对手机工程） | 本批变更 |
|---|---|
| `protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt` | 普通手机角色监听、缓存观察与有界候选探测、准确日志；取消/权限错误不作为换服务重试理由 |
| `protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/WiapBluetoothPolicy.kt` | 新增纯策略：角色UUID、缓存提示分类、候选顺序及生产实际调用的监听注册顺序 |
| `protocol-carplay/src/test/java/io/github/iamr0s/carvex/carplay/core/WiapBluetoothPolicyTest.kt` | 新增18项测试，包含64种UUID子集组合及注册失败分支 |


## 2. 手机角色：去掉无依据的混合发布

| 角色/服务 | 本地发布UUID | 主动连接远端UUID |
|---|---|---|
| 普通 WiAP legacy | `00000000-deca-fade-deca-deafdecacafe` | `00000000-deca-fade-deca-deafdecacaff` |
| 普通 WiAP v2 | `02030302-1d19-415f-86f2-22a2106a0a77` | `02030302-1d19-415f-86f2-22a2106a0a78` |

移除原来额外以本地 Sink 名义发布的 `…caff/…0a78` 监听。69的固件证据表明普通与Sink是由 `enableSink` 条件选择的角色，不能把同时发布两组解释为完整复刻。

注册顺序仍为 legacy 成功后尝试 v2。legacy 注册发生 `IOException` 时：仅监听模式直接失败；允许主动连接的模式保留主动路径，不转而单独注册v2。v2注册发生 `IOException` 保留legacy监听。权限等非IO异常不吞掉。资源仍归原有 `Resources` 管理。

保留原有服务名 `Wireless iAP` / `Wireless iAP v2`，未把它们宣称为24A446完整服务名证据。公共API成功只记录“监听API成功”，不宣称已从外部查询到SDP发布结果。

## 3. 服务证据：缓存提示不是完整SDP

策略输入为 `device.uuids` 的快照；分类为不可用、空、无WiAP提示、legacy提示、v2提示、双提示。没有生成 `ABSENT_CONFIRMED` 或 `PRESENT_VALID` 等公共接口无法证明的记录状态。

表中仅指**远端 accessory UUID**；本地手机UUID不算远端提示。

| 缓存观察 | 修改前主动候选 | 修改后主动候选 |
|---|---|---|
| null / 空列表 | v2 → legacy | v2 → legacy |
| 非空但仅HFP/A2DP等无关UUID | legacy | v2 → legacy |
| 仅legacy提示（可含无关UUID） | legacy | legacy → v2 |
| 仅v2提示 | v2 | v2 → legacy |
| legacy和v2都有提示 | v2 | v2 → legacy |
| 仅监听模式，任何缓存 | 不主动连接 | 不主动连接 |

每个候选分别记 `UUID_CACHE_HINT` 或 `PROBE_ON_UNKNOWN`。缓存命中仅说明有提示，不保证服务仍存在、channel可用或记录完整。去重并固定本轮快照，外部列表后续变化不改变已生成计划。

“→”表示首候选未建立选中连接后才可能继续；已有入站赢家、停止、取消或权限错误不会为了遍历列表而继续。主动候选串行、各最多一次，没有引入两个UUID并发拨号。

本批未添加显式 `fetchUuidsWithSdp`、广播等待或新扫描；SDK socket连接底层仍会查询UUID对应服务。不能把没有显式刷新写成“连接时完全不做SDP”。

### 与固件仍有意区分的部分

69所核固件局部分支是先查v2的attribute4，查找失败才转legacy；已找到之后的channel解析/连接失败不走该函数的legacy分支。公共SDK没有提供等价完整结果，因此本批是 `sdk_uuid_hint_probe` 有界兼容探测，不是固件精确fallback。

仅legacy提示时优先legacy是保留既有快路径的Android策略，并非声称苹果也按缓存这样排序。缓存非空也不再删除另一种候选，因为它不能证明另一服务不存在。

保留原有每次主动20秒、入站60秒、整体65秒预算；这些不是苹果固件常量。对旧逻辑只尝试一种服务的失败场景，本批可能多一次至多20秒的主动尝试，受整体预算约束；不能承诺连接更快。成功、取消及失败恢复的真实耗时仍需实测。

## 4. 没有在本批解决的部分

- [71 §11](71-android-bluetooth-feasibility.md) 的 BT-LIM-01～04继续开放：共享RFCOMM通道、定制SDP profile属性、接纳前拒绝、完整SDP查询结果。
- 仍是两个普通UUID各建一个公共SDK监听，不是苹果同channel两条记录。日志标记 `sdpTopology=independent_channels`。
- 未补普通WiAP的 `0x0009=0x1101/0x0102`；日志标记 `customProfileDescriptor=unavailable`。
- 仍保留原有“先建立者胜出”的双向连接机制，尚未引入串行状态所有者、pending-outgoing门控或generation仲裁。`preAcceptAdmission=unavailable` 也不是接纳前行为已修好。
- 未新增强断HFP/A2DP策略，未实现新的主动发起/重试规则。
- 未改变iAP2、网络、AirPlay或音频阶段，也未通过提高版本声明冒充新能力。


## 5. 验证结果与异常记录

最终结果：`protocol-carplay` 115个测试套件、856项；`core` 12个套件、79项，合计935项，失败/错误/跳过均为0。18项新蓝牙测试包含在856中，64种组合是其中一项测试的内部枚举，不能重复计数。

新测试覆盖：准确UUID方向、null/空/无关缓存、本地UUID不冒充远端、单/双提示、重复与输入顺序、输入快照、仅监听、64组合候选性质、生产注册辅助函数顺序、legacy失败、v2失败、致命注册错误传播。它们不执行真实Android SDP、socket竞争或车机连接。

命令（手机工程目录）：

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests io.github.iamr0s.carvex.carplay.core.WiapBluetoothPolicyTest --no-configuration-cache
.\gradlew.bat :protocol-carplay:testDebugUnitTest --rerun :core:testDebugUnitTest --rerun :app:compileXiaomiDebugKotlin --no-configuration-cache
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests io.github.iamr0s.carvex.carplay.core.WireTest --tests io.github.iamr0s.carvex.carplay.core.WiapBluetoothPolicyTest --rerun --no-configuration-cache
.\gradlew.bat :protocol-carplay:testDebugUnitTest --rerun :core:testDebugUnitTest --rerun :app:compileXiaomiDebugKotlin --no-configuration-cache
```

按执行顺序：

1. 新蓝牙测试18项通过。
2. 首次上述两模块完整回归：原有 `WireTest.linkRetransmitsSameSequenceAndDefersMessages` 一项超时，报 `SocketTimeoutException: iAP ACK timeout seq=175`，位置为 `WireTest.kt:129` → `IapLink.sendCsm`；新蓝牙测试通过，core 79项通过，小米Kotlin编译成功。
3. 未改代码，定向复跑 `WireTest` 与新蓝牙测试，通过。
4. 仍未改代码，再跑完整两模块回归与编译，935项通过，编译任务为up-to-date；构建成功。

该重传测试使用内存管道和100ms的SYN重传参数，不调用本批蓝牙策略。存在时序敏感的迹象，但未证明这次超时的唯一根因；没有放宽测试、修改链路代码或将该异常记作“已修复”。第一次失败XML已被复跑覆盖，未伪称另有归档；证据清单记录最终报告哈希。

`git diff --check` 通过；既有CRLF提示不是编译或测试失败。文档检查只验证链接与JSON结构，不验证互通。

## 6. 下一批与实机验收

下一批应在单独范围内处理连接状态所有者：主动尝试预留、入站事件、取消/迟到完成、资源释放与重复交付，补竞争测试。实施前仍须区分苹果接纳前门控和Android接纳后关闭，并继续核对上层发起/重试条件；不能直接照抄一个拒绝条件导致两端互相断开。

本批实机验证保留首次连接、再次连接、失败恢复三类：确认日志只有普通手机角色，检查候选依据及实际选中方向；必要时由独立SDP客户端核对实际属性与channel，不修改车机程序。应用单边日志只证明本地观察，不能证明双方持有同一连接或首帧已经显示。
