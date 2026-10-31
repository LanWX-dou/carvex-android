# 01 视频流标识与建流

> 本文件回答第 1 项覆盖要求：屏幕流是哪个类型、TCP 还是 UDP、SETUP 要交换什么。
> 结论全部来自 `AirPlaySender` 的建流与 SETUP 路径；涉及 `APTransport` 的部分一律标 `INFERRED`（另一二进制，未纳入本阶段 `source/`）。

## 01.1 两个变体

| 变体 | 创建入口 | 证据 |
|---|---|---|
| TCP（记录帧） | `_APEndpointStreamScreenCreate` @ `0x251b40be8` | 符号表；`0x251b40fc4` 写类型 |
| UDP（RTP） | `APEndpointStreamScreenUDPCreate` | 字符串 `0x251c02dc8`；类名 `0x251c02dae`；`screenStreamUDP` `0x251c03970` |

两者是**不同的流对象**：TCP 变体的发送路径是 `screenstream_*` + `sbpd_*`；UDP 变体是 `screenstreamudp_*` + `sdpsession_sendSetup`（见 `01.6`）。
**客户端必须先确定用哪一个**；本阶段只能证明"UDP 存在且由 endpoint 能力位控制"，不能证明 CarPlay 默认选哪个（`OPEN-VID-14`）。

## 01.2 类型编号与显示选择

在 `_APEndpointStreamScreenCreate`（`0x251b40be8`）里：

| 事实 | 指令 | 说明 |
|---|---|---|
| 无 display 参数时类型 = `0x6e`（110） | `0x251b40fc0` `mov w8, #0x6e`；`0x251b40fc4` `str w8, [x19, #0x58]` | 类型写在**流对象 +0x58**（32 位） |
| 带 display 参数时另有一条 +1 分支 | `0x251b40f48` `mov w8, #0x6e`；`0x251b40f4c` `cinc w8, w8, eq` | 结果可能为 `0x6f`（111） |

`cinc …, eq` 说明 `0x6f` 由**某个比较结果**决定，而不是常量。反编译显示该比较是"请求的 display UUID vs 该 endpoint 的第一个 display 的 UUID"；**但 0 结果对应 0x6e 还是 0x6f，本轮没有闭合**（比较函数未读）。因此：

- `0x6e`是无display入参路径的默认类型；“所有主屏必用110”未由此证明；
- `0x6f` = 另一屏类型：`BYTES` 可证存在，**语义（主/副）不闭合** → `OPEN-VID-1`。

## 01.3 每屏描述：CarPlay 侧建流前收集的键

`carEndpoint_setupScreenStreams`（`0x251aeda20`）在建流前，从 endpoint 的 **DisplayDescriptionArray** 为每个 display 组装字典，再调用 `_APEndpointStreamScreenCreate`（调用点 `0x251aef428` `bl #0x251b40be8`）。字典键（字符串与 getter 调用成对出现，地址见 `source/asm/airplaysender/f_251aeda20.s`）：

| 键 | 用途（据调用形状） |
|---|---|
| `UUID` | 显示标识；决定类型分支与多屏去重 |
| `PixelSize` | 像素尺寸 |
| `PhysicalSize` | 物理尺寸（毫米） |
| `ViewAreas` | 视图区数组 |
| `ZoomFactor` | 缩放因子 |
| `MaxFPS` | 该显示允许的最大帧率 |
| `IsNightMode` | 夜间模式 |
| `IsLimitedUI` / `LimitedUIElements` | 受限 UI 标志与元素集 |
| `SupportsKnobInput` / `SupportsTouchpadInput` / `SupportsLowFidelityTouch` / `SupportsHighFidelityTouch` | 输入能力（与本阶段无关，建流时一并带入） |
| `SupportsCornerMasks` | 圆角遮罩能力 |
| `PrimaryInputDevice` / `ApplicationURL` / `InitialApplicationURL` / `OverrideCanvasSize` | 输入设备、应用 URL、画布覆盖 |

这些键是发送端内部字典，不是已证线上必填集合；线上对应及获取阶段需逐项追，不能统称均来自SETUP。
**实现影响**：客户端必须先从对端拿到显示描述（分辨率/物理尺寸/最大帧率），再决定编码尺寸与几何；不能硬编码 1920×1080。

## 01.4 SETUP：发起与响应

| 阶段 | 函数 | 已证事实 |
|---|---|---|
| 发起 | `_endpoint_setupStreams` @ `0x251b371ac`；单屏 `_endpoint_setupScreenStream` @ `0x251b3db28` | 按流对象逐个发起；屏幕流走同一入口 |
| 响应 | `_apsession_setupStreamCreatingResponseInternal` @ `0x2519bbf24` | 响应里按 `streams` 数组回填；类型检查 `0x2519bbfac` `sub w8, w1, #0x6f`、`0x2519bc340` `cmp w21, #0x6e` |

类型范围比较只证明按type分支，不能证明响应type与请求type相等校验；该绑定关系需继续追。端口方向仍见01.5的跨镜像证据边界。
**未闭合**：SETUP 请求体的完整字段清单（`OPEN-VID-1` 的另一半）——TCP 变体的请求由 `APTransport` 的通用流描述生成，本阶段只读到响应侧与调用点。

## 01.5 端口与方向（`INFERRED`，跨二进制）

`APTransport`（另一二进制，未纳入 `source/`）中，屏幕流的连接属性为：

- 数据连接使用 `_kAPTransportConnectionTCPUnbufferedOption_*` 与 `APTransportConnectionTCPUnbufferedCreate`；
- `_kAPTransportConnectionOption_IsListener` 在发送端路径被置为**非监听**；
- 端口来自 `_kAPTransportConnectionProperty_RemoteNetworkPort`（对应 SETUP 响应里的数据端口）。

**结论（`INFERRED`）**：TCP 变体下，**发送端主动连接**对端给出的数据端口，是 TCP 客户端；监听端在对端。
本阶段没有把 `APTransport` 纳入 `source/`，因此该结论在 spec 里只能是 `SHOULD / INFERRED`，不能写成 `CONFIRMED`。

## 01.6 UDP 变体：SDP 与 `RTP/AVP/UDP`

`_sdpsession_sendSetup`（`0x251a9f364`）在构造 SETUP 时引用字符串 `RTP/AVP/UDP`（`0x251c13dc6`，引用点 `0x251a9f414` `add x9, x9, #0xdc6`）。

配套字符串（同一 `__cstring` 区域，`0x251c04000`–`0x251c04a00`）：

| 字符串 | 地址 | 含义 |
|---|---|---|
| `screenstreamudp_createSetupRequest` | `0x251c0404b` | UDP 变体自建 SETUP 请求 |
| `screenstreamudp_handleSetupResponse` | `0x251c04186` | UDP 变体自解析响应 |
| `negotiationData` | `0x251c040b0` | 协商数据键（见 `01.7`） |
| `hasUDPMirroringSupport` | `0x251c448ad` | endpoint 能力位 |
| `HasUDPMirroringSupport` | `0x251c19f76` | 同一能力位的另一处拼写 |
| `enableUDPConnectionNW` | `0x251c4a8a2` | 开关名（用途未读） |

即：**UDP 变体自己发 SETUP、自己解响应，传输串是 `RTP/AVP/UDP`**；TCP 变体走 `APTransport` 的通用流机制。两条路径的 SETUP 字段集合可能不同，不能互相套用。

## 01.7 协商数据（`negotiationData`）

`APEndpointStreamScreenAVCWrapper` 的启动/重启接口都带 `negotiatedBlob` 参数：

- `startWithNWConnectionClientID:negotiatedBlob:screenOptions:completion:`（`0x251a76ae4`）
- `restartWithScreenOptions:negotiatedBlob:`（`0x251a77208`）
- `negotiationDataForPresentationMode:`（`0x251a779d8`）

字符串 `negotiationData`（`0x251c040b0`）位于 UDP 建流请求的字符串簇内，说明**协商结果要进建流请求**。
**未闭合**：blob 的二进制结构、是否必填、空 blob 时对端行为 → `OPEN-VID-8`。

## 01.8 建流失败路径

| 情况 | 处理 | 证据 |
|---|---|---|
| display 数组为空/取不到 | 返回错误，不建流 | `_APEndpointStreamScreenCreate` 的 `cold_22` 分支 |
| display UUID 取不到 | 返回错误 | `cold_3` 分支 |
| 流对象分配失败 | 返回错误 | `cold_1`/`cold_24` 分支 |
| 响应/请求类型绑定 | 未闭合；原稿将类型分派误当相等校验 | `0x2519bbfac`附近只有类型比较证据 |

**实现影响**：客户端遇到"无显示描述"应直接失败并上报，而不是用默认分辨率猜。

## 本章依据

| 结论 | 说明 |
|---|---|
| `A01.1` | TCP/UDP 两个屏幕流变体与各自创建入口 |
| `A01.2` | 无display参数路径向+0x58写0x6e；不能独自证明所有主屏类型 |
| `A01.3` | 每屏描述键集合 |
| `A01.4` | CarPlay 建流调用点与 SETUP 响应类型检查 |
| `A01.5` | 端口/方向：发送端为 TCP 客户端（`INFERRED`，APTransport） |
| `A01.6` | UDP 变体使用 `RTP/AVP/UDP` 与自建 SETUP |
| `A01.7` | `negotiationData` 随建流传递 |
| `A01.8` | 建流失败分支 |
