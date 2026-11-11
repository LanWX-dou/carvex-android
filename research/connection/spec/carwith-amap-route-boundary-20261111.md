# CarWith 车载高德界面的全程里程出口核查

日期：2026-11-11。用户确认 GalaxyPlay 显示的是 **CarWith 的车载高德界面**，画面已有全程剩余距离和导航信息；目标是从 CarWith 取得导航数据并交给 GalaxyPlay。仪表机动距离 245 米已显示，全程剩余里程为 -1 米，高德约 19 公里。本轮继续核查 CarWith 的结构化出口，没有更改手机或车机 APK，也没有修复全程里程。

## 输入与复核

用户提供 `D:/home/高德地图_17.02.0.2010.apk`。Android SDK 36.0.0 aapt 读取 manifest：`com.autonavi.minimap`、versionName `17.02.0.2010`、versionCode `170200`、targetSdk 35。文件 177,749,534 bytes、8 个 DEX；SHA256 `768d62ee138771c0f1d1a08c68151a0e41f66bda2ada1c559e07ebb09b65857c`。本地 ASCII 副本与用户原件哈希一致。该版本来自用户提供的 APK，不代表公开发行的最新版本。

CarWith 原 APK 沿用已核 `4.0.14-20260801`、SHA256 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。本轮匹配两份 APK 的 19 个方法归属、签名和原指令哈希，并直接验证标题 null 和查询 null 指令。完整原 APK、反汇编和未审素材仅留在忽略的本地目录。

[证据 JSON](../evidence/carwith-amap-route-boundary-20261111.json)；只读复核：

```powershell
python -X utf8 -B research/connection/tools/inspect_carwith_route_boundary.py `
  --amap local-backups/2026-11-11-amap-route-source/amap.apk `
  --carwith D:/home/CarWith_4.0.14-20260801.apk
```

## 进入 CarWith 的原数据

CONFIRMED 指以下原 APK 的局部指令与调用链；实际投屏会话是否走每个分支尚需运行日志确认。

| 原方法 | 已核数据与条件 |
|---|---|
| 高德 classes4 `AjxModuleCarProjection.getIAjxModuleCar` `0x27c038` | carMode=2 且平台非 hihonor 时选择 `mv`；不能把另一平台的模块数据套入 CarWith |
| 同类 `notifyOngoingCard` `0x27d8e0` → `mv.notifyOngoingCard` `0x5ab8c0` | naviInfo 读取 distance/unit；naviManeuver 加载图标；nextAction 读取 actionName/nextRouteName。所审分支没有读取全程剩余距离 |
| `ew6.d` `0x3f6d08` | 活动、图标/距离/操作/道路齐全时，通过 UCarMapConnector 发送当前提示；断开时存在排队分支 |
| 高德 classes8 `gv6.a` `0x35eed8` | 构造方向图标、提示距离/单位、操作、道路和路口图；`0x35ef42..0x35ef5c` 将 TITLE_1 和 TITLE_2 都写为 null |
| `UCarMapConnector.f` `0x2d5614` → Binder proxy `showNavInfo` `0x482204` | 用上述 Bundle 调用 `IUCarMapService.showNavInfo`，第二个 Bundle 参数为空 |
| CarWith classes5 `IUCarMapServiceStub.showNavInfo` `0x1c06f0` → `UCarMapInfo.fromBundle` `0x1bf334` | 按 Binder 调用 UID 确认地图包，补 pkg 后转换字段，再调用已注册地图 listener；所审 showNavInfo 没有从第二个 Bundle 补全全程里程 |
| CarWith classes2 `map.m$a.a` `0x1af960` | 接收 UCarMapInfo，读方向图标、提示距离/单位、操作、道路、TITLE_1/TITLE_2，直接交给 LauncherDataBusClient.E |

因此在这条已闭合的导航提示路径上，空扩展标题已在进入 CarWith 前产生。画面中的完整路线显示可确认用户所见的渲染结果；仍须独立核实 CarWith 能交给 CarVeX 的结构化字段。

## 从 CarWith 取得数据的候选出口

| 出口 | 本轮结果 |
|---|---|
| mixing `carlife_show_hud_info` | `LauncherDataBusClient.E` `0x16fc3c` 只发送 action、turn_icon_data、navi_turn、remain_distance、road_name、total_distance。remain_distance 是当前提示距离，total_distance 是 where 变化时缓存的提示参考。没有独立全程剩余里程，也没有两个标题 |
| DataBus `sendNavigationInfoToCar` | E 将空标题归一化为 `""`，构造 NavigationInfo；G `0x170050` → classes4 service stub `0x10f6bc` → `ControlChannel.sendNavigationInfo` `0x10efc0`。后者将现有距离/单位、操作、道路、标题等写入 NotifyNavigationInfo 并通过可用控制通道发送。它没有生成另一份路线里程；接入此通道仍会得到空标题 |
| UCarMapService `getValue` | CarWith classes5 `0x1c02b0` 的实现直接返回 null。接口名存在不能作为能够查询全程里程的依据 |
| `BMapBridge.getNavigationInfo` | CarWith classes8 `0x1593dc` 依赖本进程的 bridge 实例；构造器 `0x1594b8` 反射加载 `net.carman.baidumap.bridge.BMapBridgeImpl`。这是百度地图 bridge 的合同，未闭合到高德车载投屏，也未证明有可供 CarVeX 读取的 Binder 出口 |

高德原 DEX 中的 route_remain_dist/route_remain_length 搜索命中也涉及其他模块/平台；字符串存在不能证明它们已经进入上述 CarWith 合同。没有用这些孤立字段名新增解析、轮询或跨进程 hook。

## 当前断点与下一步

1. 已拿到正确高德 APK，已确认用户使用 CarWith 车载高德界面，当前卡点不再是缺少 APK/版本。
2. 现有 CarWith HUD 取得的是当前机动提示；DataBus 的两项标题在这版高德标准 UCar 路径上为空，getValue 也没有实现有效查询。尚未找到可以从 CarWith 交给 CarVeX 的真实全程里程出口。
3. 用户不能连接手机，随后提供本地 MiAuto receiver 源码作为离线反查入口。已进一步闭合[MiAuto → ICCOA 标准接收 → CarWith 消息 11 发送链](miauto-carwith-navigation-20261111.md)：两份原 APK 的九字段 protobuf schema 一致，字段 7/8 是标题，字段 9 是应用 ID，没有独立全程里程。MiAuto 的运行 SDK 未入库，原厂 SDK 是单独版本的接收证据。仍须核对实际投屏是否有另一条事件、接口或渲染侧出口；运行日志是后续验证手段，不能把本地接收源码反查略过。本轮未读取新设备日志或执行供应商代码。
4. 找到有效来源后，还必须接通当前数值 publisher 尚未发布的 `5201 p7`。必须保留能力/订阅和绑定隔离，验证单位、缺值清理、重新规划、结束及重连；不能用 245 米、缓存 total_distance 或固定 19 公里补值。

本轮验证为静态输入与字节复核 PASS。真实全程里程来源、完整发布及仪表现场结果继续 OPEN/FAIL，不能把新增研究记录算作修复完成。原有导航与音乐生产代码未改动。
