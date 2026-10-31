# 12 — iAP2 识别字段、接受/拒绝与再次提交

日期：2026-10-29。基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`PARTIAL`，用于补充 B-OPEN-03，不代表完整识别规范或实车已通过。

后续深度复核见[64](64-identification-deep-review.md)及15–18分册：补充电源provider、嵌套组件、未知字段早停的最终消费者、1D05取消和1D06增量更新。旧证据快照保留；仍不能称完整Identification或全分支覆盖。

本轮重读原 `accessoryd`，将 22 个关键函数的缓存字节与 Mach-O 按地址映射逐字节比较，并重新读取字段注册表及原参数名称跳转表。来源、偏移、长度、SHA-256 和各结论范围见 [identification-contract-evidence.json](../evidence/identification-contract-evidence.json)。旧分析仅用于寻找入口；旧模拟器的 PASS 不作为本轮运行证据。没有执行固件、CF 系统实现或车机。

## 1. 主线与四个消息

以下 state 数字都是手机进程内的原值，不是线上消息字段；与 [11](11-iap2-state-machine.md) 的 link FSM 数字不在同一命名空间。

| 消息 | 发起方 → 接收方 | 当前入口和条件 | 本轮可证格式/结果 | 不能推出 |
|---|---|---|---|---|
| `0x1D00` StartIdentification | 手机 → 配件 | `0x1000511d0` 只在 identification state=0 构造 | 本函数无附加参数；发送结果 bit0=1 才写 state=1 | 已完成对端识别；固定超时/重试次数 |
| `0x1D01` IdentificationInfo | 配件 → 手机 | `0x10013bcc8` 要求非空 session/root，且 `(state & ~2)==1`，即仅 state=1 或3 | 创建/安装新 info，按注册回调解析、检查必需字段/承载组件/feature/消息集，再交授权回调 | handler 同步返回1不等于已经发送 `1D02`，更不等于认证或网络成功 |
| `0x1D02` IdentificationAccepted | 手机 → 配件 | `0x100050dcc`：授权回调非零且已捕获的校验结果=0 | 先写 state=2，构造无附加参数的 `1D02`；发送结果 bit0=1 才写 state=6，否则停在2 | 本地提交成功不证明配件收到；state6不替代 AA、Wi-Fi 或 AirPlay |
| `0x1D03` IdentificationRejected | 手机 → 配件 | 字段/feature/消息集失败形成 rejection scratch，经适用授权回调进入 `0x10013b540` | 普通字段拒绝为同 ID 的空 TLV；消息列表拒绝见 §5；发送返回非零才清转移指针并写 state=3 | 不能把所有失败都变成断链，也不能在 body 添加臆造的 reason 字节 |

当前 iAP2 control session 是承载。承载建立、session 选择和配件认证另见 [10](10-bluetooth-iap2-network.md)。不能给上述四条强加“识别永远早于认证”的全局排序。

### 1.1 一次 IdentificationInfo 的局部处理链

```text
state=1/3、session/root有效
  → 建立并安装本次 info / rejection scratch
  → 逐参数回调（未知ID或回调失败会中止本次遍历）
  → required-success set 检查
  → 当前承载需要的组件检查
  → feature validator 与声明消息集检查
  → 平台/用户授权回调
      ├─ 回调值0：本回调不发包、不改state；后续策略另查
      ├─ 校验成功：state2 → 提交1D02 → bit0成功才state6
      └─ 校验失败：提交1D03 → 非零成功才state3
```

这只画主处理路径，未把所有分配失败、队列取消与跨 session 回调串成完整生命周期。`0x10013bcc8` 在调用授权 hook 后可直接返回“checkAll==0”；若授权是异步，该返回发生在最终决定之前。

## 2. 注册表：必需是“解析成功”，不是“出现过”

`0x10006a3e4` 遍历 `0x10021b550` 的29个 feature entry。描述符的 `+0x18` 指向参数记录，`+0x20` 是记录数；每条24字节记录为 ID、回调指针和 `required` 字节等。本轮直接读得34条注册记录、11个不同回调。

required 字节为1的 ID 为 **0–9、12、13**。其含义是：`0x10013aed0` 调用已注册回调，只有回调返回值 bit0=1 且该 ID 属于 required 数组，才把它加入 `info+0x78` 成功集合。`0x10013bc5c` 检查的是这个集合；缺少成员时加入该字段的拒绝 TLV，并置 `info+0x90`。

计数器不是成功集合。核心回调 `0x1000512e8` 在某字段子解析失败后也可能增加出现次数；因此“12个 required ID 都在抓包里”不足以证明校验通过。required=0 也不代表所有场景都可省略：承载和 feature validator 还可加条件要求。

## 3. 关键字段合同

ID 均为 `1D01` 外层参数 ID。名字由原 `paramName@0x10004e73c` 的跳转表与字符串恢复；名字只帮助定位，类型/条件仍以消费者为准。表中字符串、声明列表和组件均由配件提供，不能复制另一辆车的身份、地址或能力作为默认值。

| ID | 原诊断名称 | 线值与来源 | 缺失/重复/有效性边界 |
|---:|---|---|---|
| 0 | AccName | 末尾 NUL 字符串 → `info+8` | required；重复释放并替换旧值；不是追加 |
| 1 | AccModel | 同类字符串 → `+0x10` | 同上 |
| 2 | AccManufacturer | 同类字符串 → `+0x18` | 同上 |
| 3 | AccSerialNumber | 同类字符串 → `+0x20` | 同上；日志仅留脱敏标识/存在性 |
| 4 | AccFirmwareVersion | 同类字符串 → `+0x28` | 同上；对端声明，不是手机固件版本 |
| 5 | AccHardwareVersion | 同类字符串 → `+0x30` | 同上 |
| 6 | MessagesSentByAccessory | 偶数字节的 BE16 message-ID 序列 → `+0x60` 集合 | required；**配件发送、手机接收**方向；重复列表替换，集合去重；空列表不等于满足 feature 消息要求 |
| 7 | MessagesRcvdFromDevice | 偶数字节的 BE16 message-ID 序列 → `+0x68` 集合 | required；**手机发送、配件接收**方向；重复与空列表同上 |
| 8 | PowerSourceType | U8，由 `0x1000c07a8` 消费 | required；原函数对值1与 raw transport kind0/8有特殊拒绝条件；不能外推为所有无线设备统一值 |
| 9 | MaximumCurrentDrawnFromDevice | U16 getter，BE 线值 | required；不得超过当前 provider 返回的 maximum available；单位/全部平台限额尚 OPEN，不填固定0或固定毫安数 |
| 12 | CurrentLanguage | 末尾 NUL 字符串 → `+0x50` | required；重复替换；未从该局部恢复全语言码语义 |
| 13 | SupportedLanguage | 每次一个末尾 NUL 字符串，加入 `+0x58` 集合 | required；重复相同值的 CFSetContains 分支拒绝，内部诊断原因4；实际 CF 比较语义未运行 |
| 17 | BluetoothTransportComponent | 嵌套参数，经 core 转给 Bluetooth 组件回调 | 注册 required=0，但 raw transport kind2/3要求该组件；完整嵌套合同仍 OPEN |
| 24 | WirelessCarPlayTransportComponent | 嵌套参数，经 core 转给 WirelessCarPlay 组件回调 | 注册 required=0，但 raw transport kind4要求该组件；声明不等于网络已关联 |
| 34 | PPID | 末尾 NUL 字符串 → `+0x40` | 注册 required=0；重复替换；不由名称推断格式或跨会话稳定性 |

### 3.1 字符串边界：不能把本地限制当苹果规则

`GetDataAsString@0x100067ee4` 只在该局部确认：TLV 总长至少5字节、最后一个声明值字节为 NUL，返回 `param+4`。它依赖上层提供有效范围，本身不证明底层缓冲区足够。其后 `CopyDataAsCFString@0x1000f2bac` 调用 `CFStringCreateWithCString(..., 0x08000100)`。

这个 framing helper 没有拒绝中间 NUL，也没有“非空、只许可打印 ASCII、最长255字节”的检查；这些不能从旧本地实现抄成苹果限制。另一方面，framing 通过不证明任意内容都有效：真实 CF 转换、Unicode、空转换结果、后续字段语义仍需验证。`processStringParam@0x10004f0d4` 可在 status=0 时储存 NULL 转换结果；不能据此建议实现接受所有坏字符串。

### 3.2 消息列表方向和准入

`processMessagesSet@0x10013adf0` 检查值长度为偶数，以 BE16 加入新集合，再释放/替换旧集合；奇数长度返回错误 `0x16`，添加相应外层字段拒绝，保留旧集合。该 `0x16` 是内部返回码，不是线上附加字段。

方向由真实消费者交叉核对：`isIdentifiedForIncomingMessageID@0x100051054` 查询 `info+0x60`，`isIdentifiedForOutgoingMessageID@0x100005138` 查询 `info+0x68`。普通业务门槛还要求 authentication state=2、identification state=6；引导消息有例外。`AA06` 有独立条件分支，不应被“全部消息需先认证”规则阻断。

feature 检查建立允许集合，再核对配件声明的消息是否可接受。不能把“手机认识这个 message ID”误当“当前配件已声明且当前 feature 允许”。全 feature validator 的组合关系未在本轮闭合。

### 3.3 其余注册项的边界

本轮没有把34条注册记录都升级成完整字段规范。已恢复但未完整审计的注册项还包括：10/11（EA）、14/15/16（Serial/USB transport）、18/23/29（HID）、19（Reserved）、20/21（VehicleInfo/Status）、22（LocationInfo）、25（MaximumSiphoningCurrent）、26（BLE transport）、30/33（原名称函数返回 Unknown）、38（VehicleDigitalCarKeyInfo）、240/241（power回调）。完整 ID/回调/required 位见 JSON。

其中 ID19虽已注册，core 实际明确走拒绝分支；“有注册项”不等于接受值。USB组件单列，不当作无线必填。HID/车辆信息这里只记录其识别可能参与 feature 校验，不扩展触摸、音频或业务实现。

## 4. 承载组件的条件必需

`checkRequiredTransportComponentParam@0x10013b920` 对 `(*session)+0x18` 的 raw kind 与组件计数作以下局部检查：

| 原 kind 值 | 需要外层字段 | 字段原名称 |
|---:|---:|---|
| 0 | 15 | USBDeviceTransportComponent |
| 2或3 | 17 | BluetoothTransportComponent |
| 4 | 24 | WirelessCarPlayTransportComponent |
| 6 | 14 | SerialTransportComponent |
| 8 | 16 | USBHostTransportComponent |

所需字段计数必须可访问且非零，否则加入字段拒绝并置错误标记。该表不是从 UI 显示推导的承载枚举；必须先确认实际 endpoint kind。蓝牙承载与之后 IP 承载可以有独立 identification，不要把两条链路的字段/计数合并。

“组件被声明”和“该物理网络/接口实际可用”是不同事实。嵌套组件的 ID、名称、active 标志、地址、去重及跨组件约束仍需单独消费者审计，本章不能提供整段可重放 `1D01` 模板。

## 5. `1D03`：线上拒绝与本地原因必须分开

### 5.1 普通字段拒绝

`addRejectParam@0x10004e91c` 调用 `iAP2MsgAddVoidParam(rejectMessage, 0, fieldID & 0xffff)`。因此普通拒绝项是：参数长度4（包括长度和ID）、原字段ID、无值。其 `reason` 参数仅进入 `rejectName` 和 CF 诊断字符串，不作为 reason payload 写入该 TLV。

例如“必需字符串解析失败”和“必需字段缺失”可留下不同本地原因，但不能单凭一个空字段 TLV 恢复唯一原因。排障必须关联本地解析结果、required-success set、阶段与同次消息，不能把空 TLV解释为字段值0。

### 5.2 声明消息列表拒绝

`0x10004ecec` 为方向0/1设置各自标志；只在内部 reason=1 且 messageID不等于 `0x00ff` 时，向对应缓冲追加 BE16 messageID。其它原因或 sentinel 走诊断分支，不凭空添加数字。随后 `0x10004edcc` 仅在标志**恰为1**且原字段出现计数非零时输出：

- 方向0 → 外层参数6，body 为拒绝的 BE16 ID 序列；
- 方向1 → 外层参数7，同类 body；
- body 可以为空；这个空 body 不是“没有拒绝”，也不是 `1D02`。

这里 body 是 message-ID 数据序列，不是每个ID再包一层 TLV。反复调用 finalizer 是否产生重复项及容量不足行为，不能由本章当作已完整处理。

### 5.3 提交判据并不完全一致

原 `1D02` 路径在 `0x100050e30` 使用 `tbz w0,#0`；原拒绝 sender 在 `0x10013b614` 使用 `cbz w0`。所以 accept 检查低位、reject 检查非零，不能在审计时把二者简化为相同布尔规则。实际发送适配器允许哪些返回值仍须另外恢复；此差异不意味着实现应伪造发送结果。

拒绝发送成功后清除/转移 `info+0x98/+0xa0`，写 state3；发送返回0时保留这些指针并跳过state3。两条路径都继续调用 rejection cleanup dispatcher。全 feature 清理结果和物理发包完成不由这一个函数证明。

## 6. 平台授权不是配件证书验证

`authorizationHook_identification@0x10011e1f0` 查看当前 AA 状态：为0时走直接完成分支；非零时取证书序列标识并交 `requestAuthorization`。该 hook 的完成结果被识别流程当作平台/用户允许，不是重新做证书链或签名验证。

`0x100050dcc` 回调值0直接返回；不能据此声称此时一定发 `1D03` 或立即断链。回调允许且检查成功才尝试接受消息。AA 的真实性、CarPlay 用户授权、identification 字段接受、业务声明和 AirPlay Pair-Verify 仍须各自取证。

回调中“captured info 与当前 info 相同”的检查在发送及state变更之后，用来保护后续 rejection scratch 释放；不能把它写成已经完整防止旧回调推动新session的世代保护。完整取消、超时与异步所有权仍 OPEN。

## 7. 再次提交、清理与九问收口

`1D03` 成功进入 state3，而 `1D01` handler接受state1/3，所以该局部允许拒绝后再次提交识别信息。不能由此要求每次拒绝都重建 RFCOMM/Link，也不能推出无限重试、固定重试间隔或总deadline。`setIdentificationState@0x10004dd50` 在state1/3清除已发布 accessory info；state6则把当前识别信息发布到 endpoint。这是身份发布边界，不是网络就绪。

| 九问 | 本章答案与边界 |
|---|---|
| 进入前状态 | 当前link/control session有效；1D00的局部state0、1D01的state1/3；平台授权与AA分开 |
| 谁主动/承载 | 手机发1D00/1D02/1D03，配件发1D01；当前control session，动态承载关联见10/11 |
| 请求响应格式 | 1D00/1D02此生产路径无附加参数；1D01注册TLV；1D03空字段或6/7消息列表；外层iAP2可靠传输另层 |
| 类型/单位/必需/缺省 | §2–4；required-success set、条件组件、动态provider；未知单位/全部语义不补零值 |
| 固定与动态 | 消息ID、注册ID和局部wire宽度固定于本版本；身份/版本/语言/能力/provider值来自当前配件与会话 |
| 接受/拒绝/等待 | 参数回调、必需集合、组件、feature/消息集、授权与发送结果逐层；同步return不等于最终接受 |
| 成功证据 | 同次link上的1D02提交与对端继续处理证据；AA、声明业务门槛另证；不能直接推进网络/投屏通过 |
| 超时/重试/清理 | 已证拒绝→state3可再次收1D01，state1/3清发布身份；全timer、重试budget、feature清理和旧回调隔离仍OPEN |
| 下一预期 | 拒绝后按适用策略等待再次1D01或清理；接受后按AA/session/feature状态继续，不能硬编码立即发5702或4300 |

## 8. “停在 iAP2”的具体定位

| 最后事实 | 下一预期 | 可区分的失败 | 最少证据 |
|---|---|---|---|
| 1D00已提交 | 同link收到1D01 | 对端未收、错误session、对端尚待条件 | link世代、方向、消息长度及seq/ack，不只打印send成功 |
| 收到1D01 | 进入参数遍历 | state非1/3、session/root无效 | 原state与入口拒绝原因 |
| 字段均出现 | required-success集合完整 | 某callback失败、未知ID导致早停 | 每字段ID/长度/回调结果及集合差异，不记录身份明文 |
| required通过 | 承载/feature/消息集通过 | 当前kind缺组件、声明方向反了、不支持的消息组合 | 当前kind、组件ID、6/7声明列表和validator结果 |
| 校验通过 | 平台授权回调及1D02 | 授权仍等待/拒绝、发送失败留state2 | callback关联、许可结果、发送返回和后续state |
| 1D03已提交 | 再次识别或有据清理 | 把空TLV错误解析为reason字节、无条件断链 | 原拒绝body、同attempt本地原因与state3后的实际事件 |
| state6 | AA/业务门槛及适用启动流程 | 只识别成功、AA未成、未声明能力 | 分离的auth state、消息准入、feature启动事件 |

## 9. 完成边界

本轮关闭了有界的静态事实：34项注册和12项required成功语义；字段名称与核心字符串/消息列表的消费；条件组件表；1D02/1D03的发送门槛和局部再次提交关系。`B-OPEN-03` 只能改为**部分关闭**。

仍缺：34项全部值约束/嵌套组件与所有feature组合、真实CF转换与provider结果、异步授权和取消、全部重试预算、`1D05/1D06`更新识别流程、同版本真实接受/拒绝/重识别抓包。G4不能因本章静态核验而整段关闭，更不能据此关闭G6/G11/G12。
