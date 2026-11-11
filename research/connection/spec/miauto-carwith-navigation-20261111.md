# 从 MiAuto 反查 CarWith 导航出口

日期：2026-11-11。目标仍是 CarWith → CarVeX → GalaxyPlay 的全程剩余里程：用户已看到 245 米转向提示，仪表全程显示 -1 米，高德车载界面约 19 公里。本轮按用户指定直接读取 `D:/Project/Lanwx/MiAuto`，未修改该 checkout，也未连接手机。

已反查到标准导航出口和接收链，尚未取得真实全程里程来源。本次字段证据不能算作修复完成。

## 输入与证据范围

MiAuto HEAD 为 `8ee36108ab74a58cbb0ef5c305e813a5f2fd8f41`。本地工作树检查无改动。`app/libs/README.md` 明确区分签名桩与实际运行 SDK；本地没有 `app/libs/icar-sdk.dex`，只有 `compileOnly` 的 `app/stubs/icar-sdk-stubs.jar`，SHA256 `224fc1f5014f50a8f1670eb42f3c80625a2978ba5299fde2480a3c49eee2c242`。

因此，MiAuto 源码可确认应用如何注册/接收导航；接口桩可确认字段签名，不能给出实际 protobuf 数值或证明协议运行分支。桩中的 `*_FIELD_NUMBER` 已被剥掉 final 和 ConstantValue，不能把桩默认值当字段编号。

为核对原字节，使用此前已有的两份 APK：

| 输入 | 标识与角色 |
|---|---|
| CarWith | `com.miui.carlink`，`4.0.14-20260801`，SHA256 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`；手机生产者 |
| 原厂手车互联 | `com.geely.linkhmi`，`1.0.20260610G(48)` / versionCode 72，SHA256 `043866ed5e719fd1617ef57f4060c0fd7030e02df70433c5f5d0f518bf1946af`；另一版本实际 ICCOA 接收 SDK |

原厂 SDK **不是** MiAuto 缺失的运行 dex。两份原 APK 的标准导航 schema 一致，并不证明全部版本或自定义通道一致。完整 APK、SDK 字节、反汇编只保存在忽略的本地目录；入库证据只保留经审的签名、字段值、地址和哈希。

[证据 JSON](../evidence/miauto-carwith-navigation-20261111.json)及[只读复核器](../tools/inspect_miauto_carwith_navigation.py)：

```powershell
python -X utf8 -B research/connection/tools/inspect_miauto_carwith_navigation.py `
  --miauto D:/Project/Lanwx/MiAuto `
  --carwith D:/home/CarWith_4.0.14-20260801.apk `
  --factory 'D:/home/手车互联_1.0.20260610G(48).apk'
```

## MiAuto 的接收位置

当前源码 `app/src/main/java/com/miauto/app/IccoaManager.java` 在 320、413 行注册 `adapter.registerPhoneDataListener(phoneDataListener)`；667 行的 `onNavigationInfoReceived(phoneId, info)` 原样调用 `listener.onNavigation(info)`。

`app/src/main/java/com/andrerinas/openheadunit/connection/IcocaBridge.kt` 的 49–52 行保存 `StateFlow<UCarCommon.NavigationInfo?>`；192–193 行仅将收到对象赋给 `_navigation.value`。当前 main 源码搜索未找到该 ICCOA flow 到仪表/HUD 的消费映射。保留的 Android Auto 导航 protobuf、`AapNavigation*` 等属于另一协议，不能据其全程字段推导 CarWith 出口。旧文档中的完成描述也不能覆盖当前源码的边界。

投屏画面有独立入口：`IccoaManager.java:514` 调用 `adapter.startCast(surface, videoW, videoH)`。导航信息回调与投屏 Surface 是两个 API。用户所见的车载高德界面确认投屏内容已经到达；取得可单独写入仪表的全程数字，仍需结构化出口的字段和来源证据。

## 反推出的手机发送链

以下地址均为原 DEX code_item；发送与接收不是同一份 SDK：

| 步骤 | 原方法与数据流 |
|---|---|
| CarWith 地图事件 | 已闭合的高德 UCar → `LauncherDataBusClient.E` / G；原生产者空标题与 HUD 距离语义见[前轮核查](carwith-amap-route-boundary-20261111.md) |
| 手机 Binder 出口 | CarWith classes4 `DataBusService$DataBusServiceStub.sendNavigationInfoToCar` `0x10f6bc` → `ControlChannel.sendNavigationInfo` `0x10efc0` |
| 手机消息构造 | `sendNavigationInfo` 把 NavigationInfo 原有字段写入 NotifyNavigationInfo；`da.j.B` `0x16bcdc` 设置 SourceDevice.PHONE，method ID **11**，构造控制消息 |
| 接收消息分发 | 原厂 classes3 `l0.r` `0x218954` 的 packed switch 将 ID **11** 跳到 `l0.l` 的调用分支；不是按 title1 或另一个“剩余里程”事件分发 |
| 接收解析 | `l0.l` `0x2185a0` → `t2.H` `0x220214`，后者检查 ID 11 并 `NotifyNavigationInfo.parseFrom(ByteBuffer)` |
| SDK 对象转换 | `l0.l` 逐项读取导航字段，调用 `UCarCommon.NavigationInfo.<init>` `0x1fc088`，再通知 `l0$v` listener |
| 应用 listener | `UCarAdapter$d.a` `0x1f3bf8` → adapter 静态桥 `0x1f7038` → `b` `0x1f821c`，Handler 投递 lambda `run` `0x1f32f0` → 静态桥 `0x1f69a8` → `a` `0x1f798c` 遍历 `IPhoneDataListener.onNavigationInfoReceived` |

这条链闭合了 MiAuto 接收 API 对应的 CarWith 手机标准发送接口。车机 SDK 的 listener 不能直接作为手机 mixing host 的回调注册点；将此消息接入 CarVeX 还需要手机侧可达的订阅/IPC 边界。

## 原字节确认的九个字段

CarWith classes4 `NotifyNavigationInfo.dynamicMethod` `0x144120` 与原厂 classes3 对应方法 `0x1e9e18` 的 protobuf metadata 字符串逐 codepoint 一致；两边 class_data/static_values 的字段编号也一致。

| protobuf 字段编号 | 名称 | 类型 | 已核含义/来源 |
|---|---|---|---|
| 1 | isNavigating | bool | 导航活动状态 |
| 2 | directionIcon | bytes | 提示图标 |
| 3 | distance | string | 来自 UCar 的当前导航提示距离；不提升为全程剩余里程 |
| 4 | distanceUnit | string | 上述提示距离单位 |
| 5 | operation | string | 提示操作文字 |
| 6 | where | string | 提示道路/地点文字；更细道路角色未闭合 |
| 7 | title1 | string | 通用标题；本版高德标准生产路径写 null，CarWith 转成空字符串 |
| 8 | title2 | string | 同上 |
| 9 | id | int32 | 原厂转换为 NavigationInfo 的 appId；MiAuto 桩未暴露该扩展 getter |

没有独立的 `routeRemainingDistance` / `routeRemainingTime` 字段。MiAuto 桩有前八项对应 getter；实际原厂 SDK 多出的 appId 也不提供全程距离。

**ICCOA 字段 7 是标题字符串；CarPlay `5201 p7` 是另一个协议的路线参数。编号相同不能直接透传。** 高德原 APK `gv6.a` 的两个标题显式为空，前轮已逐指令确认；改收 ICCOA 标准消息仍不能从它们恢复约 19 公里。

## 扩展候选与下一步边界

已审原厂控制消息分发器 `l0.r` 没有另一个导航处理分支；MiAuto `IPhoneDataListener` 桩也没有自定义路线回调。`ControlIndex` 里 `notifyNavigationInfo` 的字段 11 是同一导航 message 的声明；实际已追到的发送/接收使用 method ID 11 加独立 payload，不能误当另一个全程导航 envelope。

在 CarWith 其余 DEX 中检查的距离名字有不同归属：classes3 `leftLength` 属于 protobuf 字节串长度；classes5 `REMAIN_DISTANCE` / `getLeftDistance` 属于小爱 Maps 搜索/位置分享模型；classes8 `destinationRemainingDistance` 属于 Easyconn HUD 消息模型。其存在不能证明 CarWith 的高德 UCar 会话给这些模型供值，也不能证明它们能交给当前 host。此前 `BMapBridge` 的百度实现与空 `getValue` 查询结论仍有效。本轮没有将这些名字接成兜底。

仍需闭合：CarWith 车载高德会话是否有另一条 IPC/事件、渲染侧数据或扩展 payload，包含带单位的真实全程剩余距离；该出口是否可被当前手机 host 读取。MiAuto 当前公开接收接口已完成反查，尚未提供这个缺失来源，不能据此新增猜测解析。

找到可用来源后，再接入 host/relay 和 capability/subscription gated `5201 p7`，验证单位、缺值清理、重规划、结束、重连。原 Apple 全程参数的宽度/编码分支仍需相应原字节证据；不以 ICCOA 接收合同替代它。任务 6.3–6.5 保持未完成。

本轮复核原 APK、MiAuto 源码/桩及消息字段 PASS；没有修改 Android 生产导航、构建 APK、安装或取得新的实车结果。全程剩余里程问题仍未修复。
