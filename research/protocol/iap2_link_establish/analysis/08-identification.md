# analysis/08 — 识别阶段（载荷级）

对应任务书第 5 节第 8 项。本轮新增 9 个识别相关函数的汇编与反编译，因此第 8 项从"消息级"推进到"载荷级"。

## 8.1 消息集

`A08.1`（已确认）识别阶段共 3 条 iAP2 消息（表 `0x10021a7e0`）：

| `msg_id` | handler | 符号 |
|---|---|---|
| `0x1D01` | `0x10013bcc8` | `iap2_identification_identificationInfoHandler` |
| `0x1D06` | `0x100050934` | `iap2_identification_identificationInfoUpdateHandler` |
| `0x1D05` | `0x10013b28c` | `iap2_identification_cancelIdentificationHandler` |

`A08.2`（已确认）`0x1D01` 的处理顺序（`0x10013bcc8`）：

1. 取识别状态 `iap2_identification_getState`；
2. 状态允许时 `createIdentificationInfo()` 建识别信息对象；
3. `iAP2MsgForEachParamDo(msg, 0, iap2_identification_cbIdentificationInfoParams, info)` —— **逐参数**回调，参数组固定为 **0**；
4. 回调结束后 `checkIdentificationInfoForRequiredTransportParam()` → `checkIdentificationInfoAll()` 做必需项校验；
5. 通过才进入授权钩子；失败则 `createRejectMessage()` 回拒绝消息。

依据：`f_10013bcc8.s` / `.ghidra.c` 第 54–204 行。这解释了"识别失败"为何是**消息级拒绝**而不是链路错误。

`A08.3`（已确认）`0x1D06` 是"更新"语义：同样 `ForEachParamDo(..., 0, ..., info)`，成功后 `updateIdentificationInfo()`；`0x1D05` 把识别状态置为 `4`（取消）。三条消息都不改变链路状态机。

依据：同源文件；`0x10013b28c` 中 `setIdentificationState(link, 4)`。

## 8.2 参数 ID 与类型（`__parseIdentificationParams`）

`A08.4`（已确认）**识别参数由同一个分发器解析**：`__parseIdentificationParams`（`0x1000512e8`）。它以 `iAP2MsgGetParamID(param)` 取值：

```
if (id > 0x22) → 未处理路径：日志 + addRejectParam(info, id, 1)
switch (id) { ... }
```

即 **合法 ID 上限是 `0x22`（34）**，与 `analysis/12` 识别参数表的 34 条项数一致。

各 ID 的取值方式由实际调用的 getter 决定：

| ID | getter / 处理 | 目标 | 说明 |
|---|---|---|---|
| `0x00` | `processStringParam` | `info+0x08` | 字符串字段（default 分支） |
| `0x01`–`0x05` | `processStringParam` | `info+0x10 …+0x30` | 字符串字段 |
| `0x06` | `iAP2MsgGetDataAsData` + `processMessagesSet(…,1)` | — | 消息集合（方向位 1） |
| `0x07` | 同上，方向位 0 | — | 消息集合 |
| `0x08`–`0x0b` | — | — | **未处理** → 拒绝（reason 1） |
| `0x0c` | `processStringParam` | `info+0x50` | |
| `0x0d` | `processStringParam` + `CFSet` | `info+0x58` | 集合；重复值 → 拒绝（reason 4） |
| `0x0e` | `parseTransportComponent(…,0,cbSerial…)` | — | 串行 |
| `0x0f` | `…(…,1,cbUSBDevice…)` | — | USB Device |
| `0x10` | `…(…,2,cbUSBHost…)` | — | USB Host |
| `0x11` | `…(…,3,cbBluetooth…)` | — | 蓝牙 |
| `0x12` | — | — | 未处理 → 拒绝 |
| `0x13` | 直接 `addRejectParam(info,0x13,1)` | — | **显式拒绝** |
| `0x14`–`0x17` | — | — | 未处理 → 拒绝 |
| `0x18` | `…(…,4,cbWirelessCarPlay…)` | — | 无线 CarPlay |
| `0x19` | — | — | 未处理 → 拒绝 |
| `0x1a` | `…(…,5,cbBluetoothLE…)` | — | 蓝牙 LE |
| `0x1b`–`0x21` | — | — | 未处理 → 拒绝 |
| `0x22` | `processStringParam` | `info+0x40` | |

依据：`f_1000512e8.s` 的 switch 调度与 `f_1000512e8.ghidra.c` 第 40–250 行；拒绝路径见各 `__addRejectParam` 调用点。

`A08.5`（已确认）**transport component 的编号是固件常量**，不是顺序约定：串行 0、USB Device 1、USB Host 2、蓝牙 3、无线 CarPlay 4、蓝牙 LE 5。每个 component 再用 `iAP2MsgForEachParamDo(msg, 该参数, cb, component)` 做**嵌套逐参数**解析。

依据：`0x1000515e4` 前后 5 处 `pcVar11 = _cbIdentificationInfo*TransportComponentParams` 与 `uVar10 = 0..5`。

`A08.6`（已确认）component 内部子参数（串行为例，`cbIdentificationInfoSerialTransportComponentParams` `0x10004f254`）：

| 子 ID | getter | 含义 |
|---|---|---|
| `0x00` | `iAP2MsgGetDataAsU16` | component 标识（u16） |
| `0x01` | `iAP2MsgCopyDataAsCFString` | 名称字符串 |
| `0x02` | `iAP2MsgIsDataVoid` | 存在性标志（空 → 1，非空 → 拒绝 `0xff`） |
| 其它 | — | 拒绝 |

依据：`f_10004f254.ghidra.c` 的 `if (uVar2 == 2) / == 1 / == 0` 三段。

## 8.3 必需项与拒绝原因

`A08.7`（已确认）识别信息对象内有"参数计数数组"，每次成功解析后按 `id` 自增：`counts[id] += 1`（经 `info+0xe8` 间接寻址）。

依据：`0x1000515ec`–`0x10005160c`。

`A08.8`（已确认）拒绝原因码至少三种，由 `addRejectParam(info, id, reason)` 第三参数给出：

| reason | 触发 | 证据 |
|---|---|---|
| `1` | ID 未处理 / 越界（`> 0x22`） | `0x100051698`、`case 0x13` |
| `4` | `0x0d` 集合出现重复值 | `0x10005146c` 附近 |
| `8` | 字符串参数解析失败 | `0x0d` 分支失败路径 |

`A08.9`（未确认 / `OPEN-ID-2`）`checkIdentificationInfoForRequiredTransportParam` 与 `checkIdentificationInfoAll` 的"必需集合"未逐位读出，"哪些参数必需"仍无清单。

## 8.4 与消息表的对应

`A08.10`（已确认）识别参数表 34 条覆盖 `0x00`–`0x22`；而 `0x1D01` 的解析器**实际接受的是 8.2 表列出的 18 个**，其余走拒绝路径。两者不矛盾：表是静态注册表，`__parseIdentificationParams` 是这条消息的**入参白名单**。

依据：`analysis/12` 的 34 条 + `A08.4`。

## 8.5 未决项

| ID | 内容 |
|---|---|
| `OPEN-ID-1` | 识别消息发送顺序（谁先发 `0x1D01`/`0x1D06`） |
| `OPEN-ID-2` | 必需参数集合与超时 |
| `OPEN-ID-3` | 其余 4 份 `__parseIdentificationParams` 是否等价 |
| `OPEN-ID-4` | `0x1D01`/`0x1D05`/`0x1D06` 的角色差异 |
| `OPEN-ID-5` | `0x06`/`0x07` 的"消息集合"编码（`processMessagesSet` 未读） |
