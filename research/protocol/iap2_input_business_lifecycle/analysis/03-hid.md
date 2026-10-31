# analysis/03 — HID（特性 11）

HID 是本阶段唯一**双向**的输入通道：车机把按键/旋钮上报进来（入站），设备可以主动要报告、
下发输出报告、更新组件状态（出站）。本文件把四条入站与三条出站按"参数 → 校验 → 平台动作"写清楚。

## 3.1 消息全集

| msg_id | 方向 | 处理器/发送点 | 符号 | 平台动作 |
|---|---|---|---|---|
| `0x6800` | 入站 | `0x100130444` | `_iap2_hid_StartHIDMsgHandler` | `_platform_hid_register_descriptor`（`0x1000b2c6c`） |
| `0x6802` | 入站 | `0x100130cf0` | `_iap2_hid_AccessoryHIDReportHandler` | `_platform_hid_in_report`（`0x1000b2d60`） |
| `0x6803` | 入站 | `0x1001313dc` | `_iap2_hid_StopHIDMsgHandler` | 清组件状态位，保留字典项和接口 |
| `0x6805` | 入站 | `0x10013101c` | `_iap2_hid_AccessoryHIDGetReportResponseHandler` | `_platform_hid_get_report_response`（`0x1000b2dbc`） |
| `0x6801` | 出站 | `0x1001316f4` | `_iap2_hid_sendOutReport` | 车机侧 out report |
| `0x6804` | 出站 | `0x100131864` | `_iap2_hid_sendGetReport` | 车机侧 get report |
| `0x6807` | 出站 | `0x100131a14` | `_iap2_hid_sendComponentUpdate` | 车机侧组件使能/更新 |

`A03.1`：StartHID先取特性11，再检查msg_id；其它处理器并非相同顺序，
Report/GetReportResponse在解析组件ID时调用组件校验，Stop在解析之后查特性和字典。
不能把StartHID入口推广为四条消息共同前置序列。
证据：`0x100130494`（`mov w1,#0xb`）+ `0x100130498`（`bl` 特性查找）、
`0x1001304b8`（`mov w8,#0x6800`）+ `0x1001304bc`（`cmp`/`b.ne`）。

## 3.2 `0x6800` StartHID：参数表

| 参数 ID | 类型 | 校验 | 去向 | 证据 |
|---|---|---|---|---|
| `0` | U16（总长必须 6） | `iAP2MsgGetDataAsU16` | 组件 ID；用它在特性字典里查组件 | 跳表 `0x100018774`，case `0x100130538`；`0x100067e1c` 校验 `len==6` |
| `1` | U16（总长 6） | 同上 | 写入临时 4B 槽的高 16 位，随后作为独立的 `CFNumber`（type=8）字典值 | case `0x1001305c8`；`local_7c+2`；构造 `0x100130760` |
| `2` | U16（总长 6） | 同上 | 写入同一临时槽的低 16 位，随后作为另一独立的 `CFNumber`（type=8）字典值 | case `0x1001305a4`；`local_7c`；构造 `0x100130774` |
| `3` | U8（总长 5） | `iAP2MsgGetDataAsU8`（`0x100067e4c` 校验 `len==5`） | CFNumber 类型 7（8 位） | case `0x1001305b8` |
| `4` | 变长数据（通用TLV总长≥4；getter不强制非空，平台描述符有效性另验） | `iAP2MsgGetParamValueLen` + 原始指针 | `CFDataCreate` → 描述符 | case `0x100130560`；`0x100067f30` 返回 `param+4` |

`A03.2`（部分确认）：参数 0/3/4 的去向有指令证据（组件 ID、8 位字段、描述符数据块）。
参数 1/2 先分别写入同一 4B 临时槽的高/低 16 位，再由两次
`CFNumberCreate(type=8, &local_7c+2)` / `CFNumberCreate(type=8, &local_7c)` 取出，作为
**两个独立字典值**传给平台注册；因此旧的“拼成一个 32 位字段”表述撤回。它们在线上/平台字典中的字段名仍未证（`OPEN-INP-1`），不能把临时槽误写成一个可发送的 U32。

`A03.3`：必须分开识别阶段的组件身份/功能与StartHID携带的报告描述符。
Start注册字典的数值键由 `0x1000165c0` 包装CFNumberCreate产生；参数1/2配键1/2，
参数3配键7，参数4的描述符CFData配键9。识别属性查询提供另一些字典值，不是这些键的来源。
HID专用键用于其它平台接口，不能用其存在推导“描述符已在识别阶段登记”。见analysis/13。

## 3.3 `0x6802` AccessoryHIDReport：车机上报输入报告

| 参数 ID | 类型 | 去向 | 证据 |
|---|---|---|---|
| `0` | U16 | `_validateHIDComponent` → 组件句柄 | `0x100130d88`–`0x100130dac`（`cmp w0,#1` 分支前的取参） |
| `1` | 变长数据 | `CFDataCreate` → `_platform_hid_in_report` | `0x100130cf0` 体内取值长度 + 数据指针 |

`A03.4`：这是**按键/旋钮数据真正进来的那条消息**。处理器只做"组件校验 + 拷贝成 CFData + 异步投递"，
**不解释报告内容**：报告解释需要StartHID参数4提供的描述符和组件功能信息。
`A03.5`：该处理器没有 `cmp w0,#N` 跳表，只有 `cmp w0,#1` 的两分支比较链（`0x100130d90`），
所以"参数只有 0 和 1"是分支结构证据，不是编号空间证据。

## 3.4 `0x6803` StopHID

| 参数 ID | 类型 | 行为 | 证据 |
|---|---|---|---|
| `0` | U16 | 按组件 ID 查字典，清+18/+1a；保留字典项和接口 | `0x1001315dc/5e0`；串 `0x1001e120a` |

`A03.6`：`0x6803` 的日志串是
`StopHID message received, but keeping HID interface registered. (connectionUUID: %@, endpointUUID: %@, componentID: %d)`
（`0x1001e120a`）；找不到组件时另一条：
`Could not find HID component! (…)`（`0x1001e1282`）。
**"停组件"≠"关接口"**，客户端实现时不要以为收到 0x6803 就该断开 HID 通道。

## 3.5 `0x6805` AccessoryHIDGetReportResponse

| 参数 ID | 类型 | 去向 | 证据 |
|---|---|---|---|
| `0` | U16 | 组件 ID | 跳表 `0x100018788`，case `0x1001310e4` |
| `1` | U8 | `reportType`（回调w2） | case `0x100131170`；`_iAP2MsgGetDataAsU8` |
| `2` | U8 | `reportID`（回调w3） | case `0x10013110c` |
| `3` | 变长数据 | 报告内容 → `_platform_hid_get_report_response` | case `0x10013112c` |

`A03.7`（已确认）：参数 0/1/2/3 的解析结果在 block 中按固定槽位保存；参数 1/2
分别是 U8 的 `reportType`/`reportID`，参数 3 是报告数据。analysis/13逐条核对
跳表→block捕获→回调寄存器→平台转发→原镜像selector字符串，补强A11.1历史关闭依据。
反编译形参名不是独立证据；仍保留 `OPEN-INP-2` 历史编号以追踪关闭范围。

## 3.6 三条出站

| msg_id | 发送点 | 构造参数（从 `iAP2MsgInit` 调用点可见） |
|---|---|---|
| `0x6801` | `0x1001316f4` | 组件 ID + 报告数据；用于设备主动下发 out report |
| `0x6804` | `0x100131864` | 组件 ID + reportType + reportID；请求车机回 `0x6805` |
| `0x6807` | `0x100131a14` | 组件 ID + `ComponentEnabled`（布尔）；启停组件 |

`A03.8`：`0x6804` 与 `0x6805` 是一对：设备发 `0x6804` 请求，车机用 `0x6805` 应答，
应答里的 `reportType`/`reportID` 与请求对应（键名证据同上）。

## 3.7 门控与顺序

- 四条入站都不在"无条件放行"名单里（`0x100051054` 的白名单只有
  `0x0000/0x0004/0x0005/0x1D01/0x1D05/0x1D06/0xAA01/0xAA03`），因此**必须**满足
  `认证==2 ∧ 识别==6 ∧ 该 ID 在入站集合里`（见 `sess/R-5.x`）；
- 公共校验检查识别组件身份/类型/功能，不检查Start/enable状态位，不能据此证明报告必被Start前置门拦截；
- 本地输入注入应等待有效描述符和启用状态，但这是客户端安全策略，不是该helper已实现的线上门控（analysis/13）。

## 3.8 未决

| 编号 | 内容 | 关闭条件 |
|---|---|---|
| `OPEN-INP-1` | `0x6800` 参数 1、2 两个独立 16 位字典值的字段名/单位 | 抓到一条真实 `0x6800` 帧，或追完 `0x1001306xx` 区块的字典键配对 |
| `OPEN-INP-3` | 触摸是否只走 `0x54xx`，或另有 HID 触摸报告组件 | 抓包含触摸事件，或读 `_hidComponentFunctionType`（`0x100043704`）全部分支 |
