# 19 · Identification Power provider 的真实承载上下文


结论：已见 iPhone Bluetooth iAP 构造路径使用 **parent type2 / endpoint rawKind2**，AirPlaySender 使用 **parent type5 / rawKind4**。将这两种上下文代入 accessoryd 的 ID9 provider，均返回原始限额数值 **100**；500 特例对应 **parent type3，即 Smart Connector**，不是 USB、Bluetooth 或“所有有线”。平台 ID240/mode4 仍然 OPEN。

## 1. 证据和复查范围

[证据快照](../evidence/identification-power-provider-context.json)绑定四个原文件 SHA-256、19 个完整函数区间及其字节 SHA-256、两个 enum 字符串表的原始字节哈希、选定指针/字符串和 import 解析结果。[只读工具](../tools/inspect_identification_power_context.py)重新读取原始 Mach-O；对于 AirPlaySender/CoreAccessories 的四个函数，另与原 dyld cache 对应地址逐字节比对。19 个函数全部可完整解码，不代表所有业务分支或全部调用者已经审完。

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_identification_power_context.py --verify D:\carvex-research\research\connection\evidence\identification-power-provider-context.json
```

`--audit`只输出当前快照；`--asm --inspect 0xVA`输出原指令；跨镜像用`--image <原文件绝对路径>`。工具不写文件、不执行固件。证据中路径相对 `D:/carvex-research/firmware`。原反编译缓存仅帮助定位，不以错误恢复的 C 参数个数代替 ARM64 实参。

本章补齐[第15章](15-identification-power-transport-branches.md)的部分 producer OPEN；不重做完整 Power/组件/Identification 生命周期审计。固件静态分支不是实车故障归因，也不是全车型兼容性保证。

## 2. 三个数字域必须继续分开

accessoryd `getTypeStringFromType@0x1000fad70`引用导入槽`0x10022b420`；Mach-O indirect symbol 表将其准确绑定为`_kACCConnection_Type_Strings`。endpoint 字符串函数`0x1000f5c18`引用`0x10022b438`，绑定为`_kACCEndpoint_TransportType_Strings`。不能把两个导入槽用本地 rebase 规则强行解成地址。

CoreAccessories 对应表位于原 dyld VA `0x26c2c8b08`和`0x26c2c8e30`。本轮按 dyld v5 slide metadata 解指针后读取原字符串：

| 数字域 | 值 | 原始字符串 | 本轮意义 |
|---|---:|---|---|
| parent connection type | 2 | Bluetooth | 已有 bluetoothd producer 交叉确认 |
| parent connection type | 3 | Smart Connector | ID9 返回500的唯一相等分支 |
| parent connection type | 5 | IP | 已有 AirPlaySender producer 交叉确认 |
| parent connection type | 6 | USB | 不能拿此名称把 type3 改叫USB |
| endpoint raw transport | 0 | USB Device Mode | ID8=1的拒绝承载之一 |
| endpoint raw transport | 2 | Bluetooth Classic | 已见 Bluetooth iAP endpoint |
| endpoint raw transport | 3 | Bluetooth LE | 仅核对名字；本轮未审BLE producer |
| endpoint raw transport | 4 | AirPlay | 已见 AirPlaySender endpoint |
| endpoint raw transport | 8 | USB Host Mode | ID8=1的另一拒绝承载 |

parent 无效值 getter 返回11（Unknown），endpoint 无效值 getter 返回19（Unknown）。component type 是第三个域，例如 Identification 外层17对应内部组件type3；这不等于 Smart Connector，也不等于 endpoint Bluetooth LE。

## 3. 构造与 getter：类型不是解析器从字符串猜出的

| 原函数/指令 | 已核对的分支与数据流 | 限制 |
|---|---|---|
| `ACCTransportPluginManager createConnectionWithType:andIdentifier:@0x1000cd970`；manager `0x1000f6094` | 调用者提供的 type 原样向下传递；注册失败有销毁路径 | 不是按本地socket种类重新选type |
| connection `createWithUUID@0x100191698` | 接受type0..9，越界返回NULL；`0x10019187c`把原type写入`connection+8` | UUID生成、注册等失败可使对象不存在；本轮未证明所有创建路径可达 |
| `createEndpoint_internal@0x10019288c` | parent非NULL、transport<=17、protocol<=18等条件满足才向构造器转发 | transport与protocol是独立参数 |
| endpoint `createWithUUID@0x10018a96c` | parent必需；`0x10018ac2c`保存parent到`endpoint+0`；`0x10018ac64`把transport/protocol写入`+0x18/+0x1c` | protocol层初始化、UUID冲突等失败有销毁路径；未推断parent type |
| `getParentConnection@0x10018f128` | NULL endpoint返回NULL；否则直接读`endpoint+0` | 不从组件列表找parent |
| `getType_internal@0x1001939fc` | NULL返回11；非NULL先断言connection dispatch queue，再读`+8`，0..9原样返回，否则11 | outlined helper `0x100016a64`保存对象并读取`+0x90`队列；不能在错误队列调用后假装正常返回 |
| `getTransportType@0x10018f134` | NULL返回19；`+0x18`为0..17时原样返回，否则19 | 与parent type getter不同 |

这些事实说明必须维护带来源的 transport context；一个`isBluetooth`布尔值或名字相似的枚举不能替代所有上下文。它们也不表示 Android 必须复制 Apple 内部对象布局。

## 4. Bluetooth iAP 的实际 producer

原`bluetoothd`无符号函数`0x1007a4520..0x1007a48d0`包含`[iAP CONNECTED] CONNUUID: %@ and ENDPOINTUUID: %@`日志（字符串VA `0x100b46706`）。关键原指令：

```text
0x1007a45c0  mov w0, #2
0x1007a45c4  mov x1, x24
0x1007a45c8  bl  0x100909f00   // indirect symbol: _acc_transportClient_createConnection
0x1007a45cc  mov x22, x0
...
0x1007a462c  mov x0, x22       // 刚创建的connection UUID
0x1007a4630  mov w1, #2        // endpoint transport
0x1007a4634  mov w2, #0        // protocol参数，非parent type
0x1007a4638  mov x3, #0
0x1007a463c  mov w5, #1
0x1007a4640  bl  0x100909f10   // indirect symbol: _acc_transportClient_createEndpoint
```

创建前对象查询返回NULL，在`0x1007a4570`直接走退出；connection创建返回NULL，在`0x1007a45dc`转错误清理，不调用endpoint创建；endpoint创建返回NULL，在`0x1007a4658`转错误清理，只有成功路径进入连接登记与上述日志。故这里不是“看到一个常量2就认定所有蓝牙连接均如此”。本轮证明的是这条 iAP 创建路径，不覆盖 BLE、所有重连/旁路 producer。

stub 名称由原 Mach-O 的`LC_DYSYMTAB` indirect symbol 与`LC_SYMTAB`字符串表关联得到，已保存在 JSON，不仅来自 Ghidra 命名。CoreAccessories `acc_transportClient_createConnection@0x204415440`和`createEndpoint@0x204415740`分别把C参数中的type/transport转为ObjC参数继续传递；不会在这两个wrapper中改成type3。

## 5. AirPlaySender 的实际 producer

`___APAccTransportClientConnectionOpen_block_invoke_3@0x251af5e58`：已有connection句柄时`0x251af5e7c`直接退出；否则准备identifier，再取/解析`acc_transportClient_createConnection`动态函数地址。原字符串在`0x251bff4b1`。函数指针非NULL后：

```text
0x251af5f64  mov w0, #5
0x251af5f68  mov x1, x20
0x251af5f6c  blraaz x23
0x251af5f74  str x0, [x8, #0x18]
0x251af5f78  cbz x0, #0x251af6020
```

`___APAccTransportClientEndpointActivate_block_invoke@0x251af6b08`检查生命周期状态、已有endpoint和handler准备结果；原动态函数名`acc_transportClient_createEndpoint`在`0x251bff4d6`，指针非NULL才调用：

```text
0x251af6c4c  add x4, sp, #0x10
0x251af6c50  mov x0, x21       // connection UUID
0x251af6c54  mov w1, #4        // transport = AirPlay
0x251af6c58  mov x2, x20       // protocol由上层传入，不在此写死
0x251af6c5c  mov x3, #0
0x251af6c60  mov w5, #1
0x251af6c64  blraaz x23
```

创建失败进入错误处理；成功且请求证书匹配检查时还走独立property设置分支，失败仍会清理endpoint。没有证明所有创建后的连接均完成鉴权或可投视频。本轮仅确认参数生产者与失败门槛，不扩展分析证书机制。

因此 **AirPlay逻辑endpoint的rawKind4** 不能无条件替换为 **所有TCP socket的kind4**。Android某个TCP承载究竟对应AirPlay iAP channel、原生iAP2-over-IP或其它桥接，需要该连接真实来源的证据。

## 6. 对ID8/ID9的直接影响与null边界

`__maximumCurrentAvailableFromDevice@0x1000c0758`完整局部决策仍为：session/root endpoint/parent任一NULL返回100；非NULL时查parent type，`==3`返回500，其他返回100。这个provider没有测量实时电流。本章仍将100/500记为原始数值，不增加所有线上字段单位的独立规范证明。

| 已核实上下文 | ID9 provider | ID8=1的raw0/8否决 | `isWireless` |
|---|---:|---|---|
| Bluetooth iAP：parent2/raw2 | 100 | 不命中 | true：parent2分支 |
| AirPlaySender：parent5/raw4 | 100 | 不命中 | true：raw4分支 |
| parent3（raw未指定） | 500 | 仍由raw决定 | 不能仅据parent3判断 |
| NULL parent | 100 | ID8仍需自己的root/raw上下文 | false，见下文 |

“不命中ID8否决”仅表示这一局部条件通过，**不是整条Identification可接受**。ID8仍要求精确U8宽度；ID9要求精确U16BE宽度且值<=provider。合法9的101在前两条上下文会超限；100不会因这一限额条件失败。超过限额追加9空reject项，宽度失败局部不追加9，维持第15章已确认的非对称错误形状。

补充第15章的`isWireless@0x10018f17c`边界：必须先有endpoint和parent；parent NULL时`0x10018f198`跳到返回0，**不会再检查rawKind4**。只有parent存在时，`parent type2 OR rawKind4`成立才返回true。不要把伪造“无parent/raw4”当成完整Apple无线上下文。

## 7. 实施边界与仍OPEN事项

本批手机代码范围仍只有已批准的core字段工作；**本章Power上下文尚未接入Android运行时**，不能宣称8/9已跟随实承载校验。

后续可使用两个明确的候选profile：已确认Bluetooth iAP对应`parent2/raw2`、已确认AirPlay iAP endpoint对应`parent5/raw4`。应用前必须由会话来源赋值并记录上下文，不能由车机品牌、任意TCP、组件active位或字段名字选择。测试至少覆盖99/100/101、499/500/501、NULL/有效parent、raw0/2/4/8以及8/9的错误宽度和重复顺序。

仍OPEN：

1. Android各入口与这两条Apple producer的具体对应及重连/切换生命周期；本轮没有证明所有连接生产者。
2. ID240的真实平台power plugin、mode4动态限额及失败行为。**不能复用ID9的100/500，也不能以默认0填空。**
3. Power所有AE消息消费者、feature重置、组件后续选择规则、CF字符串运行时语义等第15章其它OPEN。
4. 同一实车输入的iPhone/Android抓包对照；静态校验补齐不等于车辆兼容性已验证，也不证明历史音频卡顿由Power字段引起。

本轮推进的是“参数从哪里来、数字属于哪个域、两条已见承载走哪个限额分支”。没有声称复刻全部iPhone CarPlay或所有分支已闭合。
