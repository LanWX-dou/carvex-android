# 仪表导航数值核心：原始证据与 GalaxyPlay 兼容边界

日期：2026-11-11。用户指定 GalaxyPlay 0.1.212 为接收端并授权修复。Apple 状态、机动枚举、参数键和宽度以 24A446 原镜像为准；米数消费、定义与引用合并、清屏效果以本版 GalaxyPlay 原 DEX 为兼容依据。后者不证明通用 Apple 更新顺序或所有车机行为。没有实车验收。

## 宿主转向与距离

CarWith APK 版本为 4.0.14-20260801，SHA256 为 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。

`classes2.dex` 的 LauncherDataBusClient.E（code_item `0x16fc3c`）在 `0x16fe2a` 调用 map.l.d，在 `0x16fe80` 将结果写入 navi_turn。这条路径使用 Bitmap 图标分类器，不是直接读取 UCarMapInfo.OPERATION。

分类器 map.l.d（`0x1aedb4`）按地图包选模板，以置信度至少 0.8 返回组码；空图、未匹配与异常返回 0。map.l 的静态初始化器（`0x1af2fc`）构造资源后缀与组码对。l$a 构造器（`0x1aeacc`）将第二个参数写到字段 a，方法 b（`0x1aeab4`）读出该组码；方法 a（`0x1aea9c`）返回资源后缀。已从原 APK 的 resources.arsc 解析资源名到混淆 PNG 路径，并实际查看像素：

| navi_turn 组码 | 原模板举例 | 本次规范化 |
|---|---|---|
| 2 | 高德 2/3/5 的右侧斜向箭头 | SLIGHT_RIGHT |
| 3 | 高德 6/7/12、百度 1/2 的右转箭头 | RIGHT |
| 4 | 高德 4 的左侧斜向分岔 | SLIGHT_LEFT |
| 5 | 高德 8/19、百度 12 的掉头 | U_TURN |
| 7 | 高德 9/10/11/13、百度 7 的左转 | LEFT |
| 8 | 高德 18 的斜向左转 | LEFT，保留基础方向，不声称精确角度 |
| 其他 | 含直行/隧道、信息、环岛和终点等组 | unknown，不制造箭头 |

组内模板可能带分岔/支路；本次仅提供基础方向，不恢复精确车道、道路几何或完整地图操作枚举。

LauncherDataBusClient.w（`0x16f3f0`）把距离文本的米/公里分支转成米整数；“现在”、未知单位和异常返回 0。E 将转换结果放进 remain_distance，而 total_distance 是提示的缓存参考距离。因此只发布严格 Int、正数且未饱和的 remain_distance 到“下一机动距离”；零、负数、Int.MAX_VALUE 和错误类型全部 unknown，不能据零判断抵达。road_name 的当前路/转向后道路角色、外部地图更新阶段、真正 routeId/sequence 仍 OPEN。

## Apple 原表与参数

原镜像哈希与所审字节哈希保存在 [数值核心证据](../evidence/navigation-numeric-core-20261111.json)。

- CarPlay NSStringFromCPGuidanceState（`0x247b00444`）经边界 <7 索引 `0x2690da898` 原 CFString 表：0 NotActive、1 Active、2 Arrived、3 Loading、4 Locating、5 Rerouting、6 ProceedToRoute。accessoryd 转换器 `0x100004428` 对 <7 原值输出 U8，其他为 0xff。
- NSStringFromCPManeuverType（`0x247b3a190`）经 <54 索引 `0x2690da6a8`：1 LeftTurn、2 RightTurn、3 StraightAhead、4 UTurn、47/48 SharpLeft/RightTurn、49/50 SlightLeft/RightTurn。accessoryd `0x1000c5008` 对 <54 原值输出 U8，其他为 0xff。不能使用 Kotlin ordinal 或 CarWith 原组码。
- Route keyForType（`0x100003b28`）的有符号相对跳转表 `0x100003d60`：p1→`0x100003b68` RouteGuidanceState；p10→`0x100003bb0` DistanceRemainingToNextManeuver；p13→`0x100003ba4` RouteGuidanceManeuverCurrentList。路线原编码器为 `0x1000027f4`，分别使用 U8、U32 与 U16 列表。
- Maneuver keyForType（`0x1000de30c`）的跳转表 `0x100018f98`：p1→`0x1000de34c` Index；p3→`0x1000de388` ManeuverType。编码器 `0x1001777c0` 使用 U16 索引与经转换的 U8 类型。
- Identification 解析 `0x1000c5704`：顶层 p30 导航组件，内层 p0 U16 组件 ID、p6 U16 机动容量；`0x1000c5c78..0x1000c5d38` 接入组件能力消费者。本次要求各实际订阅组件有唯一合法声明且容量 >0。只发布一个当前机动；未知容量不当作无限。文本计数/NUL、缺失默认与车道合同继续 OPEN。

CFString 原表含 dyld 非认证 rebase 指针；复核器检查 auth/bind 位并验证解码目标落入原 Mach-O 文件映射，再读取表和字符串。没有根据孤立字符串搜索猜枚举数值。

## GalaxyPlay 的兼容依据与发送行为

原 APK 身份及方法归属见 [接收端核查](galaxyplay-receiver-audit-20261111.md)。实际 Identification 构造器为 classes3 的 `0x01e3fc`，导航 lambda 为 `0x01e914`：顶层 p30、组件 p0=42、p1=RouteGuidance、p2/p4=64、p6=8。这些是本版样本值，生产代码不硬编码它们。

classes2 的 updateManeuver（`0x024858`）按 p1 索引合并 p3 类型；updateRoute（`0x0249f0`）接受 p1 Active 或 p13 引用激活，并用 p10 U32 更新 segment；snapshot（`0x024070`）按引用从 map 取箭头，并把 segment 作为米距离输出。reset（`0x024810`）清 map 和 segment；updateRoute 的状态 0/2 分支调用 reset。

本次每个有效 HUD 批次自包含：5202 定义后跟 5201 Active、同一 U16 引用及正距离。距离更新复用机动代际；替换机动或新路线增加代际，wire 索引取低 16 位，每次重发该索引定义和明确距离。未知距离先 NotActive reset，再定义、引用；未知转向先 reset，再报告 Active 且无伪造引用。Ended/Invalidated 仅发 NotActive，保持订阅，不伪装 Arrived，也不主动发 5203。

清除顺序依据这个接收端的 map reset/merge；不宣称已闭合 Apple 所有首报/增量顺序。没有按车型的分支、固定等待或导航重发定时器。接收端自身 30 秒失活窗口不作为手机盲重发依据。

## 复核与剩余边界

```powershell
python -X utf8 -B research/connection/tools/inspect_navigation_numeric_core.py D:/home/CarWith_4.0.14-20260801.apk
python -X utf8 -B research/connection/tools/inspect_galaxyplay_receiver.py D:/home/GalaxyPlay.apk --check-android
```

原字节复核 PASS 证明版本与所审位置一致，不能替代控制流审阅、供应商运行或仪表显示测试。通用 Apple 米数/更新顺序、道路/ETA/车道、取消与抵达细分、上游无标识迟到包均继续 OPEN。代码及本地测试见 [实施记录](../../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md) 与 [验证记录](../../../openspec/changes/replan-carplay-navigation-cluster/validation.md)。
