# 81 — Identification：承载组件、能力分层与消息组合校验


## 1. 本次实际完成

- 解析并校验外层17（Bluetooth）和24（Wireless CarPlay）；蓝牙入口要求17，AirPlay iAP入口要求24。上下文由本地入口指定，不从品牌、列表长度、active或TCP本身猜测。
- 拆开Identification接受条件、CarPlay组件能力证据、网络交接消息路径。删除原来“6中有4301或5703就算CarPlay资格”的混合判断；也没有另造“必须有无线flag才允许43/57”的硬门。
- 在1D02之前校验feature22/26对应的三组消息。缺半组、反向声明和被跳过组中的未记账消息，按有界固件逻辑产生1D03。
- 保留v1先认证/v2先识别、同链路修正、原截止时间、发送失败处理和generation/epoch保护。1D06仍只能更新0–5，不改组件、feature或交接路径。

这解决的是明确的协议实现差异；不是“已经支持更多车型”或“Identification全部复刻完毕”的证明。

## 2. 组件分支与明确差异

依据[15](15-identification-power-transport-branches.md)、[19](19-identification-power-provider-context.md)及本轮原镜像复核：

| 输入/条件 | 现在的手机行为 |
|---|---|
| 子0/1 | 各恰好一次；0为BE16，组件ID=0合法；1要求末尾NUL，空CString允许 |
| 子2 active | 可省略、至多一次、存在时必须void；不把active视为承载上下文或授权 |
| 17子3地址 | 恰好一次、严格6字节；不附加全0/广播/配对地址匹配限制 |
| 24子4/5 | void，允许合法重复；子5传播受子4条件约束 |
| 24子6 | 可省略，合法重复后值替换；后续满足4/5条件的组件可用null覆盖旧值 |
| 24子3 / 17子4–6 / 其他未知子字段 | 不赋予猜测含义，保留外层原始值 |
| 重复组件ID | 已解析17/24之间跨类型冲突也拒绝；同类型不同ID可共存 |
| 嵌套格式/子字段失败 | 拒绝外层17或24空TLV，不附带自造子字段原因 |
| 核心字段和当前承载同时缺失 | 完成全部成功回调后，一起收集缺项；此前若已有坏字段仍首错停止 |

**不是逐字节相同的部分：**苹果BT地址局部判断是`(length & 255)==6`；手机明确采用严格6字节的安全收紧。JVM UTF-8与CF转换/NULL行为仍未证等价。失败候选不发布半成功flags，不复制原生局部先改flag后发现组件冲突的副作用。

14/15/16/26组件仍deferred，未完成它们与17/24的全局ID冲突检查；存在这些未解析组件而17/24未提供CarPlay证据时，整体能力记为`UNRESOLVED`，不冒称确定没有CarPlay能力。

## 3. 消息组合与拒绝内容

| 组 | 字段6：配件能发 | 字段7：配件能收 |
|---|---|---|
| feature22第一组 | 5700 | 5701 |
| feature22第二组 | 5703 | 5702 |
| feature26 | 4301 | 4300 |

每组全无不构成该组错误；声明任意一半就要求另一半。第一Wi-Fi组失败后跳过第二组，但继续检查CarPlay组，最后再查这六个已知ID的消息归属。

1D03中，缺失必需消息只置对应方向的拒绝标记，产生空6/7；已声明但未被该方向组处理的ID写入6/7的BE16列表。没有线上reason字节，也不写“缺失的消息ID”。例如：

- 只有6含4301：拒绝体`00 04 00 07`。
- 6含4300、7含4301（完全反向）：`00 06 00 06 43 00 00 06 00 07 43 01`。
- 6含5700/5703、7含5702/4300：第一组失败、第二组跳过，缺失项只置标记，最终`00 06 00 06 57 03 00 06 00 07 57 02`。

拒绝TLV方向顺序为6再7；多个未记账ID的内部次序采用本地稳定集合次序，不宣称复刻CFSet遍历次序。其他feature的消息尚未全面实现，**不能因此把所有其他ID都视为非法**；00FF等也不被本批局部归属检查擅自定性。

有效Identification可以没有本地支持的交接消息组。蓝牙路径会正常接受并完成独立认证，但不会试探发送未声明的5702/4300，也不会伪造网络成功；现有等待预算到期归类为本地交接能力不支持。AirPlay运行时已经在目标链路上，不要求再次具备蓝牙交接路径。

## 4. 修改位置与验证

生产入口：

- [Connection.kt](../../../android/core/src/main/java/io/github/iamr0s/carvex/sessioncore/Connection.kt)：组件、能力证据和交接路径的独立数据模型。
- [IapIdentifyInfo.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfo.kt)、[IapIdentificationTransport.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentificationTransport.kt)：有序回调、嵌套结构、组件ID及required集合。
- [IapIdentificationValidation.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentificationValidation.kt)：22/26组检查、有限消息归属与拒绝内容。
- [Bootstrap.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt)、[AcceptedIdentification.kt](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/AcceptedIdentification.kt)：接受前实际调用、发送成功后的发布、固定初始能力及路径消费。

新增2个测试文件，扩展现有Bootstrap线端测试；共新增31个测试方法。结果：

- 先加7个组件边界测试：旧实现7项均失败，确认原先缺校验。
- 首次定向114项中3项失败：旧数字钥匙/AA用例声明了单边4301；已在对应用例明确补4300并消费正常请求，未在公共发送helper里偷偷修补坏输入。
- 随后8个套件、161项定向测试通过；之后加入“核心和承载同时缺失”断言，并由最终全量覆盖。
- 最终协议模块 **928项/119套件**、core **79项/12套件**，合计 **1007项**，0失败/错误/跳过。
- `:app:compileXiaomiDebugKotlin`成功。没有执行assemble、APK bundle或install。

验证包括空/重复/错误宽度、未知子字段、5/6/7/262字节BT地址、组件冲突、flags条件传播、三组缺半边/反向/短路、同链路修正、v1认证保持、错误候选不能提前授权5703、缺路径不误报Identification错误、运行时24要求及更新不可改能力。测试使用合成内存流及合成证书签名，不代表生产AA信任成立。

原镜像18个完整函数共1799条指令与15段表数据复核；[证据JSON](../evidence/identification-components-message-batch.json)保存修改前/后源码哈希、函数字节/指令和测试统计。[核验工具](../tools/verify_identification_components_batch.py)只读验证字节、源码及现有JUnit报告，不执行苹果代码或证明语义/互通。

## 5. 尚未完成与下一步

8/9等电源provider、其他承载组件、完整29-feature接受合同、CF字符串、原生授权服务和实际车型互通仍未完成。原4300的本地availability生产方式及4E0C兼容例外也未在本批改变。

