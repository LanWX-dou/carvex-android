# GalaxyPlay 导航续接记录

最新动作：用户确认右转规划正确，要求打印全部导航信息，实车测试后判断。已增加[完整原始输入日志](../../../android/docs/fixes/2026-11-12-navigation-full-input.md)和[字段/图像提取器](../tools/extract_navigation_raw.py)：全部实际 extras、嵌套值、原类型与完整文字/图标字节都可核对。新增五项回归后宿主 30 项通过，小米编译通过；协议 1,146 项有效 up-to-date。后续等待新日志，不从日志 8 的摘要补造原始内容；全程字段/车道合同与完整实车项保持 OPEN。

Android 已独立提交 `36c1fa4`，由提交数派生的代码版本为 **20035**；提交后小米 Kotlin 编译再次通过。用户自行构建安装，清旧日志后采集新一轮完整导航回调。原始数据及还原图像保持本地，生产规划沿用用户已确认的右转行为。

保存日期：2026-11-12，最新输入已更新为日志 8。用户确认已显示“前方 258 米右转”、总距离和时间，车道仍缺失；结果为 PARTIAL。25 条新版来源事件成功解码，45 条导航消息完成本地发送。当前来源没有车道，runtime 接收声明与已审 GalaxyPlay 解析不支持 `5204`；全程距离/时间的显示来源仍 OPEN，本日志没有相应出站字段。最新证据见[日志 8 反馈](navigation-log8-feedback-20261112.md)。本轮只更新研究记录，没有生产代码变更；OpenSpec 保持 25/38。

## 用户目标和约束

- 接通 CarWith → CarVeX → GalaxyPlay 的下一次转向箭头、多少公里进入什么路、前方路口车道箭头、剩余公里和分钟。日志 8 反馈确认转向提示、总距离和时间已显示，车道仍未显示；道路名称本次未报告。
- 主要目标是 GalaxyPlay；用户明确不再调查 MiAuto。
- 最新输入是 `D:/home/device-log (8).txt`；新版 CarWith APK 已放到 `D:/home`。日志 7 保留为修复前来源拒绝证据。
- 用户把 IDEA 的 Gradle 基础目录改为 **`D:/Java/gradle`**。当前终端与用户/系统 `GRADLE_USER_HOME` 均未设置。下一次验证通过命令参数明确使用此目录，不要改全局环境变量。

## 已保存的实现与验证

以下实施、构建与“尚无实车反馈”描述属于日志 8 之前的阶段记录；当前显示状态以本文首段和[日志 8 反馈](navigation-log8-feedback-20261112.md)为准。

前一轮已修复 CarWith `4.0.23-20261016` 被只接受 `4.0.14-20260801` 的版本门拒绝的问题。两个已订阅 GalaxyPlay 会话的 132 条新版导航事件全部被拒绝，当前修复针对这个第一断点。

`android/host-carlife-mixing` 中的 `CarWithNavigation.kt` 已加入独立 H02 原 APK 证据和严格类型解码，保留 H01。对应测试新增新版生命周期、递减机动距离、异常类型、未知版本及未知转向覆盖。详细结果见[新版审计](carwith-navigation-upgrade-20261112.md)和[Android 实施记录](../../../android/docs/fixes/2026-11-12-carwith-navigation-version.md)。

前一轮实际执行并通过：

```powershell
cd D:\Project\Lanwx\carvex-carplay-research\android
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

XML 共 1,228 项测试，0 失败/错误/跳过，小米 Kotlin 编译成功。这是此前的结果，重启后续接已重新验证，见本文末尾。新 APK 原字节核查通过 9 个方法与 18 个模板；121 个本地 Markdown 链接、空白检查和 OpenSpec 严格校验通过。设备查询无连接设备，修复后的仪表显示未验收。

现有改动全部保留在工作区，尚未提交。根仓库基线 `036827a4a9c8ab453a9fa7cbd2e4dc56efdc5079`；Android 基线 `deada9d0e465599c460e5d2704db5ef5f80f45a1`。`firmware/` 原有无关改动必须保留。

## 本轮新核对到的原始链路

本节是局部原 APK/镜像指令审阅，不代表完整字段合同已经闭合。

### CarWith 4.0.23

原 APK SHA256 `c897a45d92c84f06e670fc4edd323824093a093f67d8e7d7b058fee2a737d06c`。

- classes2 `LauncherDataBusClient.F` `0x17abdc` 的 HUD 仍只发 action、turn_icon_data、navi_turn、remain_distance、road_name、total_distance。包名在其入参中，但所审 HUD Intent 没有携带这个包名。
- classes2 `LauncherDataBusClient.G` `0x17af64` 将 `UCarMapInfo.getWhere` 作为道路参数传给 F；F 再调用 `NavigationInfo.i` 取得 HUD 的 road_name。
- classes4 `NavigationInfo.<init>` `0x122648` 把第四个字符串（WHERE）存入字段 f；`NavigationInfo.i` `0x122584` 直接返回 f。这个分支没有拼接操作文字或生成全程里程。
- classes5 `IUCarMapServiceStub.showNavInfo` `0x1ba0bc`、`UCarMapInfo.fromBundle` `0x1b8be4`、`getWhere` `0x1b8e3c` 已定位并保存原指令；`getValue` `0x1b9c7c` 原指令仍直接返回 null。
- 全 DEX 的路线字段扫描找到 classes8 的剩余里程/车道接口，但归属 `net.easyconn.carman.bridge.BMapBridge` 或 `ECP_P2C_PHONE_HUDINFO`，尚未闭合到高德 → 当前 mixing 回调。不能根据字段名把它们接为真实来源。
- classes2 分类器 `map.l.d` `0x1ba904` 明确根据高德/百度包名选模板。HUD 只保留分类结果；不能单靠 raw navi_turn 推断 originating map package。

### 高德道路文字

已审高德 `17.02.0.2010` 原 APK 的 `mv.notifyOngoingCard` `0x5ab8c0`：nextAction.actionName/nextRouteName → `ew6.e` `0x3f6e04` → `gv6.e` 字段 → Bundle WHERE（原 DEX 归属纠正旧地址 `0x3f6de0`）。之前已审的 `gv6.a` `0x35eed8` 仍把 TITLE_1/TITLE_2 写为 null。

因此高德的 nextRouteName 可追到 CarWith road_name；但 CarVeX 当前 HUD 输入没有地图包名，也没有独立的当前道路/转向后道路身份。不要把所有地图的 road_name 无条件写进 currentRoad 或 afterRoad。下一步需要闭合来源归属或更完整的公开回调，不能用宿主 APK 版本冒充地图身份。

### Apple 24A446 的文本与显示能力

从原 `accessoryd` 镜像重新反汇编，镜像 SHA256 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

- 路线编码器 `0x1000027f4`：p3 的分支 `0x100002af8..0x100002b10` 调用文本追加器 `0x1000041bc`；p5/p6 调用 U64 追加器 `0x100004574`。U64 单位/时间基准尚未完成审阅，不能仅因宽度已知就发送 seconds/epoch。
- 机动编码器 `0x1001777c0`：p2 分支 `0x100177a74..0x100177a8c` 与 p4 分支 `0x100177ad4..0x100177aec` 调用同一文本追加器。
- 文本追加器 `0x1000041bc` 选择 CF UTF-8 编码 `0x08000100`，统计编码后长度并加 1，写入带终止符的字符串 payload；还检查消息缓冲容量。空 CFString 也走此分支。续接已将文本追加器等局部切片固定为[可复核证据 JSON](../evidence/galaxyplay-navigation-fields-20261112.json)，显示计数仍是独立 OPEN。
- Identification `0x1000c5704` 的 p30 子项经 U16 原读取器 `0x100067e1c` 接入能力对象。明确映射：子项 p2 → `0x1000dd220`（MaxCurrentRoadNameLength）；p3 → `0x1000dd28c`（MaxDestinationNameLength）；p4 → `0x1000dd2f8`（MaxAfterManeuverRoadNameLength）；p5 → `0x1000dd364`（ManeuverDescriptionLength）；p6 → `0x1000dd3d0`（GuidanceManeuverCapacity）；p7 → `0x1000dd43c`（LaneGuidanceDescriptionLength）；p8 → `0x1000dd4a8`（LaneGuidanceCapacity）。
- 上述 setter 指令原样存储 U16 及对应键。长度单位、是否计 NUL、缺失/零默认值和下游消费者仍需完成审阅；不能宣称 OpenSpec 2.5/5.3 全部完成。

注意：当前原镜像 CFString 引用存在 chained pointer。本轮所审槽按 `0x100000000 + (raw & 0xffffffff)` 解到已映射 CFString，再解字符串指针；这是这几个地址的局部阅读手段，不要当作通用指针解码器。

### GalaxyPlay 0.1.212

原 APK SHA256 `f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6`，仍是用户指定目标。

- classes2 `CarPlayNavigationInput.updateManeuver` `0x024858`：p1 U16 索引、p3 U8 类型、p8 U8 side；p4 经 text 解析合并为该机动 road。所审分支不使用 p2 描述文字来补 road。
- `text` `0x0245e4` 按首个 NUL 截断，UTF-8 解码、trim、最多取 256 个 UTF-16 code units。明确的空字符串是非 null；缺字段/null 会沿用旧字段，续接确认 missing/null 保留旧 road、显式空字符串替换；reset 清 road、机动表及距离/时间，完整通用索引生命周期仍需另审。
- 前轮已审 `updateRoute` `0x0249f0`：p3 道路文字、p10 机动米距离、p7 全程米距离；reset `0x024810` 清旧合并数据。当前 publisher 已支持有独立字段证据的 p7，但 CarWith 没给真实全程值。
- Identification 样本 p30/p0=42、p2/p4=64、p6=8；这些值须使用真实协商输入，不得硬编码。对应 p2 是当前道路上限，p4 是转向后道路上限。
- 本版已审入口与日志没有声明/分派 5204。车道结构缺上游来源，也缺本版接收支持，不能强发或把转向图标当车道数组。

## 本地材料与工具

新增调查和本轮开始前的 8 份文件备份均保存在忽略目录：

```text
local-backups/2026-11-12-galaxyplay-navigation-fields/
  before/                       本轮开始前的源代码、测试、README、OpenSpec 备份
  classes4.dex / classes5.dex / classes8.dex
  classes4.disasm.txt / classes5.disasm.txt
  apple-1000027f4.txt / apple-100003b28.txt / apple-1000041bc.txt
  apple-100004650.txt / apple-100067e1c.txt / apple-1000c5704.txt
  apple-1000dd160.txt / apple-1000de30c.txt / apple-1001777c0.txt
  method-1b8be4.txt / method-1b9c7c.txt / method-1ba0bc.txt
```

`map-callback.txt` 是临时筛选输出，会被最后一个命中覆盖，不要把它当成仅含 G 的切片。classes4/5 完整 dexdump 已结束，没有遗留运行中的命令。

现有 Python 没有全局安装 capstone。本轮复用了 `local-backups/2026-11-11-carvex-navigation-implementation/python-deps` 中的 capstone；脚本加入该路径后从 `inspect_navigation_numeric_core.Image` 读取原 Mach-O 字节。无需重复安装依赖。

此前 CarWith classes2 的完整反汇编位于 `local-backups/2026-11-12-carwith-navigation-version/classes2.disasm.txt`，其中存在非标准 UTF-8 字节；临时检索用 `read_text(encoding='utf8', errors='replace')`，生产证据哈希必须从原 DEX 读取。PowerShell 默认文本编码会乱码，读取文档请显式 `-Encoding UTF8`。

## 续接验证与当前下一步

第一轮使用新缓存在线补齐缺失依赖后，宿主/bridge/协议测试和小米编译 BUILD SUCCESSFUL（2m 50s），XML 25/61/1,145，合计 1,231 项全部通过。随后补充 writer 日志异常保护与第四项回归，只重跑受影响的协议测试和小米编译，BUILD SUCCESSFUL（1m 3s）。最终合计 1,232 项：宿主 25 项有效 up-to-date、bridge 本轮执行 61 项、协议最终重跑 1,146 项。结果与源码哈希保存在[本轮验证 JSON](../evidence/navigation-diagnostics-validation-20261112.json)，不混用前一轮的 1,228 项。所有命令显式传 `--gradle-user-home D:\Java\gradle`；未改全局变量。

新增原字节复核器独立复跑 PASS：三份原 APK、16 个方法、两份 Apple 镜像、四个符号和 12 份局部切片。不需要临时 Capstone 或反编译文件。备份位于 `local-backups/2026-11-12-carvex-navigation-diagnostics/before/`，原 SessionController 备份已补进 manifest。

当前阻断与继续条件：

1. 道路：CarWith 内部匹配当前地图包，但 HUD 没传原地图身份。新公开 invokeMethod 查询未找到地图身份/路线概览。继续需要可达的来源身份/角色证据；不能无条件启用 road_name。
2. 文本限制：找到 CarKitNavigation 原消费者，但关键调用目标位于提取镜像未映射的 shared-cache stub。当前原 dyld cache/IPSW 缺失，长度单位/NUL/默认/截断仍 OPEN；恢复原缓存后解析真实目标。
3. 全程公里/分钟：继续查当前宿主公共链路真实路线生产者；不以 total_distance 或机动距离补值。
4. 车道：当前源与 GalaxyPlay 0.1.212 的 5204 接收支持均缺，不能强发或改第三方 APK。
5. 原字段跳表/消费者审计和实车项仍按[OpenSpec 清单](../../../openspec/changes/replan-carplay-navigation-cluster/tasks.md)保持未勾选。诊断完善只完成 8.1；仪表业务接受/显示尚无新的验收。

下一次需要构建时继续使用：

```powershell
cd D:\Project\Lanwx\carvex-carplay-research\android
.\gradlew.bat --gradle-user-home D:\Java\gradle :host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

Gradle 缓存写权限受限时沿工具审批流程处理，不能绕回旧缓存。保留新版版本适配和 firmware 无关改动；不继续 MiAuto 调查。

## 日志 8 后的继续条件

车道有两个已核缺口：当前 CarWith HUD 没有真实车道结构；当前 GalaxyPlay runtime Identification 没有 `5204`，已审原 APK 解析也仅接收 `5201/5202`。需要真实来源与接收支持同时补齐后继续 7.2/7.3，不能仅在发送端强发。转向图标不作为车道数组来源。

总距离和时间已由用户确认显示；其实际值和更新来源未在本日志中核到，不能把现场显示继续写成失败，也不能据此完成全程字段生产者合同。8.4/8.5 保留完整生命周期和重连验收缺口。本轮原 GalaxyPlay APK 的 5 个 DEX / 28 个方法复核 PASS；未改生产代码，未新增 Gradle 验证或第三方 APK 修改。
