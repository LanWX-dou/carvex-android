# 规划、实施与接收端检查记录

日期：2026-11-11，后续新增 2026-11-12 版本适配与投递诊断验证。已实施导航契约、relay、订阅和投递撤销，并审计用户提供的 GalaxyPlay 接收端原 DEX。生产导航数值核心已启用；未构建 APK、安装或进行实车测试。

## 2026-11-12 续接与投递诊断

完成 8.1，当前 25/38：宿主输入与拒绝归属、快照字段/证据、规划/排队、writer 有效性检查和异步完成沿同一冻结批次关联，保留 session、binding、route/revision、Link/subscription/delivery 与机动代际。日志不打印道路/目的地/来源 route ID，writer 日志异常不影响当前或过期发送判断。当前字段与订阅 wire 合同未改。

所有 Gradle 命令使用用户指定的 `--gradle-user-home D:\Java\gradle`。新缓存的初次离线检查缺 Kotlin 依赖，经审批在线补齐后执行宿主/bridge/协议测试和小米编译，BUILD SUCCESSFUL（2m 50s），1,231 项全部通过。最终增加 writer 日志异常保护与第四项回归，只重跑受影响的协议测试和小米编译，BUILD SUCCESSFUL（1m 3s）。最终 XML 宿主 25、bridge 61、协议 1,146，合计 **1,232** 项，0 失败/错误/跳过；宿主测试沿用 Gradle 判定有效的 up-to-date XML，bridge 在本轮前一条成功命令执行，协议为最终重跑结果。小米编译在最终命令使用有效 up-to-date 结果。

21 份文档的 189 个本地链接、根/Android diff 空白检查和 OpenSpec 严格校验均 PASS（1 个变更，0 issues）。

新增复核器独立读取三份原 APK、16 个 DEX 方法归属/签名/指令哈希与两份 Apple 原镜像、四个符号、12 个局部切片，PASS。纠正高德 ew6.e 原入口为 `0x3f6e04`。CarWith 公共查询未补出地图身份/路线概览；CarKitNavigation 的长度消费者仍依赖本地缺失的原 shared-cache 目标。没有把局部字节复核变成完整语义证明，2.1/2.5/5.3、道路/全程/车道来源和实车项仍 OPEN；原 docset 2,145 项 FAIL 保留。

详见[诊断实施记录](../../../android/docs/fixes/2026-11-12-navigation-delivery-diagnostics.md)、[字段审计](../../../research/connection/spec/galaxyplay-navigation-fields-20261112.md)和[本轮验证 JSON](../../../research/connection/evidence/navigation-diagnostics-validation-20261112.json)。备份在 local-backups/2026-11-12-carvex-navigation-diagnostics/，包含 SessionController 原文件和 manifest。未构建 APK、安装、提交/推送或新增实车验收。

## 2026-11-12 CarWith 4.0.23 来源适配

日志 7 的两个已订阅会话有 132 条新版宿主导航输入，全部 rejected，规范化/导航发送均为零；新原 APK 的 9 个方法归属/签名/指令哈希及 18 个与旧版相同的模板复核 PASS。已新增明确版本与 H02 证据、拒绝原因及 2 项宿主回归。变更前基线 Android 为 `deada9d0e465599c460e5d2704db5ef5f80f45a1`。

离线执行 `:host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin` 为 BUILD SUCCESSFUL（1m 17s）。宿主 25 / bridge 60 / 协议 1,143 项 debug XML 共 1,228 项，无失败/错误/跳过。宿主/协议测试和小米编译实际执行，bridge 使用有效 up-to-date 结果。沙箱锁文件失败后已获准使用本机 Gradle 缓存。ADB 只读检查无连接设备，未打包/安装，修复后仪表输出保持 OPEN。

详见[新版审计](../../../research/connection/spec/carwith-navigation-upgrade-20261112.md)、[验证 JSON](../../../research/connection/evidence/carwith-navigation-upgrade-validation-20261112.json)。道路文本/角色、全程距离/时间和车道来源/接收能力仍未闭合，原任务保持 24/38。

## 初始规划与基础重构（历史记录）

- `openspec.cmd validate replan-carplay-navigation-cluster --strict --json`：PASS，1 个变更通过，0 个问题。
- 文档本地链接与行尾空白检查：PASS；范围扩大到规划产物、决策、Android 中英 README、实施记录和接收端审计。最后一次共检查 15 份文档、126 个本地链接，0 个错误。
- 已完成 19/38 项；剩余 19 项包含 Apple/宿主字段语义、显示容量、生产编码和实车验收。合成编码器测试只证明基础投递机制，不证明仪表功能完成。

## 有限原字节复核

本机原 accessoryd 为 4,330,752 bytes，SHA256 与 docset 基线一致：`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

直接解析 Mach-O segment 映射后读取原始字节，结果：

- 导航必需表 `0x1001b40e0` 的 5 个 12-byte 表项与已有审计一致：`5200/5203` 入站，`5201/5202` 出站必需，`5204` 出站可选。
- 6 个限定指令字与预期编码一致：START 的 U16 读取调用 `0x1001753c4`、空标记检查调用 `0x100175454`、必需表长度 `0x1001755b8`、可选 `5204` 查询 ID `0x1001755e0`、STOP 的 U16 读取调用 `0x100175a4c`、路线状态数值比较 `0x10000443c`。

这只验证所列字节、地址和局部编码，不代表完整控制流、枚举语义、单位、options 消费者或实车行为闭合。

后续实施阶段复跑 CarWith `4.0.14-20260801` 的 H01 校验：原 APK 身份、101 处 code_item、距离字符串及语音 switch 目标 PASS。仅 Boolean true/false 和整数 action=3 的本地生命周期进入导航契约，HUD 道路/距离/转向仍为未证观察值。没有用接收端数值补 Apple 枚举。

## 现有 docset 验证未通过

命令：在 `research/protocol/iap2_input_business_lifecycle/` 运行 `python -X utf8 -B verify.py`。结果：FAIL，退出码 1，共 2,145 条失败；这是未修改的现有 docset 基线问题。

| 检查 | 失败数 | 观察 |
|---|---:|---|
| C2 | 299 | 对应 `.bin` 原始函数切片缺失 |
| C4 | 299 | Ghidra C 文本哈希与元数据不符 |
| C15 | 299 | 同一批 `.bin` 缺失导致引用检查失败 |
| C16/C17/C18 | 各 1 | 初轮子验证失败，Python 缺少 Capstone；后续只在本地备份工具目录准备依赖，完整 docset 未重新通过 |
| C12 | 1,245 | manifest 文件缺失/哈希不符 |

抽样定位哈希不符的边界：

- `spec/03-navigation-hud.md` 与 `source/asm/accessoryd/f_10017527c.s` 的原文件字节哈希不符，但只将 CRLF 转为 LF 后即与 manifest 一致。
- `source/metadata/summary.json` 在相同 LF 归一化后仍与 manifest 不符，所以不能把所有问题归因于 Windows 换行。

本次没有改写源镜像、恢复缺失切片、更新 manifest 或削弱验证器。上述问题已纳入 P0 的证据基线复核任务；完整 docset 验证结果保持 FAIL。

## 基础重构 Android 验证（历史记录）

用户授权后的修改前基线：根提交 `d86d47855b96e8a632268483579d791a324d4f2b`，Android 提交 `e23dd7ba2bec67990edcf69ef59282cba0122ada`。既有文件已备份到 `local-backups/2026-11-11-carvex-navigation-implementation/files/`；接收端审计和文档更新另备份到 `local-backups/2026-11-11-galaxyplay-receiver/files/`。没有覆盖无关 firmware 改动或创建提交。

最终执行并成功的命令（离线，使用已有 Gradle 缓存）：

```powershell
cd android
.\gradlew.bat :host-api:test :host-carlife-mixing:testDebugUnitTest `
 :protocol-carplay:testDebugUnitTest :bridge:testDebugUnitTest `
 :app:compileXiaomiDebugKotlin :app:compileOppoDebugKotlin `
 :app:compileVivoDebugKotlin :app:compileSamsungDebugKotlin `
 :app:compileHonorDebugKotlin --offline --console=plain
```

结果：BUILD SUCCESSFUL，约 55 秒。五个 flavor Kotlin 编译通过。读取最终 debug 测试 XML 得到：

| 模块 | 测试数 | failures / errors / skipped |
|---|---:|---|
| host-api | 3 | 0 / 0 / 0 |
| host-carlife-mixing | 19 | 0 / 0 / 0 |
| bridge | 58 | 0 / 0 / 0 |
| protocol-carplay | 1,122 | 0 / 0 / 0 |

上述 debug XML 合计 1,202 项。覆盖新增的宿主版本/严格类型、relay 合并/复制/清除、双结束、旧绑定/路线/sequence、当前订阅、非法 TLV、空组件、optional 能力、批次拒绝及排队撤销。真实 IapLink 队列测试证实：旧 token 在分配序号前取消不降级 Link；已提交的分片继续完整发送；真实承载拒绝仍降级。真实 Apple 字段/容量语义与车机显示没有被这些测试覆盖。

Android 的 `git diff --check` 通过。根 README 使用既有 CRLF，普通检查会将新行的 CR 报为尾部空白；最终使用 `git -c core.whitespace=cr-at-eol diff --check --ignore-submodules` 检查并保留原换行风格，未修改 Git 配置。审计完成后没有再改 Android 生产代码，因此未重复已有全套 Gradle 检查。

## 初次 GalaxyPlay 复核（修复前记录）

`GalaxyPlay.apk` SHA256 `f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6`，版本 `0.1.212` / 240。`inspect_galaxyplay_receiver.py D:/home/GalaxyPlay.apk --check-android`：PASS，5 个 DEX 的 26 个方法归属/指令哈希及 8 份发送源码哈希通过。

详见 [接收端审计](../../../research/connection/spec/galaxyplay-receiver-audit-20261111.md) 与 [证据 JSON](../../../research/connection/evidence/galaxyplay-0.1.212-receiver.json)。静态结论：音乐基本字段格式匹配；旧导航道路/距离不能独立激活接收端，当前生产导航仍阻断；runtime 通话元数据缺 provider，音频只有独立的实验上行路径，蜂窝下行未接通。校验脚本不执行供应商代码、不验证双方音频/显示，也不证明 Apple 等价。

## GalaxyPlay 核查后的修复验证

导航 Android 独立提交：`2daaf8200e58693ac9ea71c1dc2120f43fb825d4`。OpenSpec 24/38 项完成；其余为完整字段/通用协议边界、可选车道、日志完善与实车验收，保持未归档。

原 Apple 状态/类型表、参数跳转表与编码切片、CarWith 图标分类方法归属和原图标哈希均由新增数值核心复核器独立读取 PASS。GalaxyPlay 5 个 DEX 的 28 个方法归属/指令哈希和 12 份发送源码快照 PASS。复核脚本不执行供应商代码，也不证明通用 Apple 单位/时序或实车显示。旧 docset 的完整 FAIL 不因此消失。

修复前工作已另外备份至 local-backups/2026-11-11-galaxyplay-navigation-fix/files/。修复后再次执行上列四模块测试与五个 flavor 编译命令，BUILD SUCCESSFUL，56 秒。最终 XML：

| 模块 | 测试数 | failures / errors / skipped |
|---|---:|---|
| host-api | 3 | 0 / 0 / 0 |
| host-carlife-mixing | 21 | 0 / 0 / 0 |
| bridge | 59 | 0 / 0 / 0 |
| protocol-carplay | 1129 | 0 / 0 / 0 |

合计 1212 项。新增基础转向与异常距离、机动代际、真实生产编码定义/引用/距离、未知值清除、组件容量/重复/错误类型与重订阅/结束测试。旧日志断言更新为实际来源证据缺失条件，保留禁止伪造消息的验证。

启用范围与证据详见[数值核心](../../../research/connection/spec/navigation-numeric-core-20261111.md)及[实施记录](../../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md)。音乐用户确认正常；通话下一条独立处理。仪表输出、道路/ETA/车道、取消/抵达细分、通用 Apple 米数/完整更新顺序和上游无标识乱序仍 OPEN。未打包、安装或实车测试。
