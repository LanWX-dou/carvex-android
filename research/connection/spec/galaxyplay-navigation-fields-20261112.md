# GalaxyPlay 导航字段续查

日期：2026-11-12。目标为 CarWith → CarVeX → GalaxyPlay 0.1.212，不继续 MiAuto 调查。本次新增可复核的原字节记录和诊断，未启用道路、全程公里/分钟或车道。

## 原始输入与复核入口

[证据 JSON](../evidence/galaxyplay-navigation-fields-20261112.json)固定三份 APK 的 SHA256、16 个 DEX 方法的归属/签名/指令哈希，以及两份 Apple 原镜像、四个符号地址和 12 个局部切片哈希。[复核器](../tools/inspect_galaxyplay_navigation_fields.py)只使用 Python 标准库，不依赖临时反编译输出，不运行供应商代码。

```powershell
python -X utf8 -B research/connection/tools/inspect_galaxyplay_navigation_fields.py D:/home/CarWith_4.0.23-20261016.apk D:/home/高德地图_17.02.0.2010.apk D:/home/GalaxyPlay.apk
```

独立复跑结果 PASS。它确认原输入与所审字节身份，不自动证明完整控制流、文本单位或实车显示。原导航 docset 的完整验证仍为历史 FAIL（2,145 项），没有修改其 manifest。

## 道路生产者与公开回调

高德 17.02.0.2010 classes4 `mv.notifyOngoingCard` 的 code_item 为 `0x5ab8c0`。它读取 `actionName` / `nextRouteName`，在 `0x5aba16` 调用 `ew6.e(String,String)`。原 DEX 解析确认该方法入口是 **`0x3f6e04`**，纠正续接记录原来的 `0x3f6de0`。`ew6.e` 将两个字符串分别存入 `gv6.d` / `gv6.e` 字段，再调用 `ew6.d`；`gv6.e` 是字段，不是方法。classes8 `gv6.a` `0x35eed8` 构建 Bundle WHERE，TITLE_1/TITLE_2 仍为 null。

CarWith 4.0.23 classes2 `map.m$a.a` `0x1bb4b0` 先检查来包地图身份是否匹配当前地图包，再调用 LauncherDataBusClient。`G` `0x17af64` 读取 UCar WHERE，`F` `0x17abdc` 仍只发布六项 HUD extras：action、turn_icon_data、navi_turn、remain_distance、road_name、total_distance。包名保留在内部调用链，未加入所审 HUD Intent。

classes4 `NavigationInfo.<init>` `0x122648` 保存 WHERE；`i` `0x122584` 直接返回该字段。因此高德 nextRouteName 到 HUD road_name 的局部链路已核，但 CarVeX 的 HUD 输入仍不能独立识别原地图。不同地图的道路角色未统一闭合，不能把所有 road_name 无条件映射为 currentRoad 或 afterRoad。

进一步检查了当前 mixing 公共查询：classes6 `CarLifeCastManagerImpl.invokeMethod` `0x0a65c4` → `k.r` `0x0a751c`。完整 r 分支处理设备 ID、视频格式、主题、断开与音频，没有地图身份或路线概览查询。`k.s` `0x0a7e14` 直接转发 Intent 给回调；classes.dex `e2/d$a.invokeMethod` `0x46ef90` 返回 null。这个出口没有补出真实全程距离/时间；不能以其他 EasyConn 类的同名字段替代当前链路。

## Apple 文本编码与显示消费者

原 accessoryd SHA256 为 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。`0x1000041bc` 的文本追加器选 CF UTF-8 编码 `0x08000100`，计编码字节并加一个 NUL；该局部 wire 格式与显示长度计数是两个不同问题。Identification `0x1000c5704` 读取 p30 下的 U16 能力，p2/p3/p4/p5/p6/p7/p8 分别对应当前路名、目的地、转向后路名、机动描述、机动容量、车道描述和车道容量。setter 只证实存储，不足以关闭长度消费合同。

此次在原 `CarKitNavigation` 镜像（SHA256 `df991f16ab607f32f090612463e8f1a18c96c3f14407dace74053b645f3f2e47`）找到并核对原符号/指令：

| 原入口 | 地址 |
|---|---|
| CP_variantFittingCurrentRoadName: | `0x22b03d15c` |
| CP_variantFittingPostManeuverRoadName: | `0x22b03ffa8` |
| CP_variant:fittingMaxLength: | `0x22b03d3d8` |
| stringByEllipsingPastMaxLength: | `0x22b040144` |

这些分支取组件限制并比较文本长度结果，随后选择候选/缩略文字。关键调用目标 `0x2300018e0`、`0x2300407a0`、`0x230040a30` / `0x230040a70` 位于本提取镜像未映射的 shared-cache stubs。本地原 dyld cache 与 IPSW 均缺失，不能继续解析真实调用目标。长度单位、NUL 是否计入、零值/缺失默认值与 Unicode 截断规则保持 OPEN；OpenSpec 2.5/5.3 尚未完成。

路线 26 项与机动 13 项原跳表、车道两层 key 选择入口已另固定局部字节哈希；没有把局部 chained-pointer 读取当通用解码器，也没有声称完成三类字段键和消费者审计，2.1 保持未勾选。

## GalaxyPlay 接收与合并

GalaxyPlay classes2 `text` `0x0245e4` 先截首个 NUL，UTF-8 解码并 trim，最多取 256 个 UTF-16 code units。`updateManeuver` `0x024858` 用 p4 更新机动 road：缺字段/null 保留旧 road，显式空字符串替换旧值；所审 p2 不补 road。`reset` `0x024810` 清 road、机动表及距离/时间。`updateRoute` `0x0249f0` 的 p7 与 p10 接收边界沿用[数值核心审计](navigation-numeric-core-20261111.md)。

本版未声明/分派 5204。车道同时缺当前宿主生产者与目标接收支持，不能强发。路线概览也仍缺来源，不能用机动距离、缓存 total_distance 或固定分钟补齐。

## 实现、验证与继续条件

[Android 诊断记录](../../../android/docs/fixes/2026-11-12-navigation-delivery-diagnostics.md)说明宿主输入→快照→规划→排队→writer 检查→完成的关联、字段脱敏与本地回归。诊断不改变导航 wire 字段或订阅合同；仪表业务接受和显示仍无新增实车证据。

继续道路字段需要：可达回调中独立地图身份/角色，或证明所有受支持来源的同一道路语义；同时补齐原 Apple 文本长度消费。继续全程公里/分钟需要当前 CarWith 公共链路的真实路线生产者与单位。继续车道需要真实来源及目标接收声明。完整状态/单位/options/通用顺序和实车任务仍按[任务清单](../../../openspec/changes/replan-carplay-navigation-cluster/tasks.md)保留 OPEN。
