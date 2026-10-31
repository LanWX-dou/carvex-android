# 76 — protocol=0跨进程交接、发布分支与蓝牙HID回调


后续状态：本章保存76批次只读审计时的状态；第6节扩展重复项勘误已在[77](77-iap2-extension-wait-boundary.md)落实手机端修正，受限模式/电源/通知边界也有后续进展，见第8节。历史函数哈希和测试记录保持原样。

## 1. 本轮能得出的结论

1. **指定蓝牙成功路径的protocol=0，在CoreAccessories客户端、XPC服务端和端点构造之间原样传递。**没有发现中途把0改成4的分支；构造保留未知协议，已核对的收包路径负责后续识别。这是有条件的静态调用链结论，不是运行时抓包，也不排除未审尽的上层策略。
2. **74中未解析的属性回调是Bluetooth HID功能通知。**已定位属性键、单例构造、虚表槽及实际函数。它不是iAP2版本协商，也不是“连接后无输入就主动发Detection”的已证实入口。
3. **不能宣布所有上层超时已经查完。**publish会向平台连接信息服务发通知；端点构造还有受限模式/电源策略。相关下游的全部副作用和预算尚未闭合。
4. **纠正75的一个错误：54/55重复项并非一律非法。**原函数按OR汇总集合。手机端现有“数量必须为2”的条件偏严，本轮仅记录，未改生产代码。


## 2. 客户端与服务端确实是同一条XPC服务路径

不是仅凭相似函数名拼接：

- `ACCTransportClient.serverConnection@0x204400494`创建NSXPC连接，Mach service字符串为`com.apple.accessories.transport-server`；设置remote接口为`ACCTransportXPCServerProtocol`，exported接口为`ACCTransportXPCClientProtocol`，exported object为自身，然后resume。
- 对应service字符串从原dyld的CFString `0x27207ebc0`解析；两个protocol指针槽为`0x26827f270/278`，其原缓存对象名称为上述两个协议。
- `ACCTransportServer.init@0x1000247c8`传给父类的service字符串同样是`com.apple.accessories.transport-server`（CFString `0x100222738`）。
- 服务端`exportedInterface@0x10002576c`与`remoteObjectInterface@0x100025780`使用同名的server/client协议，顺序与客户端互补。
- `ACCXPCServerBase.listener:shouldAcceptNewConnection:@0x1000aff7c`先检查接纳结果、非空接口和非空exported object，随后设置接口/对象并resume。`createExportedObjectForConnection:@0x100025794`构造`ACCTransportServerRemote`；类RO指针与`initWithClientInfo:`调用均已对照。

这里闭合的是服务身份、接口、对象与方法的静态对应。没有执行NSXPC序列化，也没有证明任意进程都被允许使用此接口；接纳策略/进程权限不是Android需要复刻的线上字段。

## 3. protocol逐跳传递与失败门

下表中的0、2、4都是苹果内部枚举，不是线上SYN版本号。

| 跳点 | 原地址 | 参数及条件 |
|---|---|---|
| 蓝牙成功block | `0x1007a4520`，74已有证据 | connection type=2；endpoint transport=2、protocol=0、identifier=null、publish=1 |
| C封装→ObjC客户端 | `0x204415740` | 保留transport/protocol，调用带publish参数的createEndpoint方法 |
| ObjC客户端→同步XPC代理 | `0x20441b138` | protocol由x3保存到x24，再于`0x20441b320`作为x3传给XPC方法；没有重写为4 |
| 服务端remote | `0x10007e82c` | 先检查connectionUUID属于该client；不属于则回复false/null，不创建；通过则x3→x23→C参数x2 |
| manager→connection | `0x1000f6244`、block `0x10018f90c` | 捕获transport/protocol到block的`+0x38/+0x3c`，在manager同步队列取回连接后转交 |
| connection入口 | `0x1000f97b8`、block `0x1000f98a4` | 检查非空连接、protocol≤18、transport≤17及连接对象有效；0满足范围；同步队列中原样转交 |
| connection内部→endpoint | `0x10019288c` | protocol保存在x21；`0x1001929c4`复制到x3，调用`0x10018a96c`；失败返回空端点 |
| endpoint构造 | `0x10018a96c` | transport/protocol存`+0x18/+0x1c`；`0x10018acc0`遇protocol=0跳过协议层初始化 |

`ACCTransportPluginManager.createEndpoint…@0x1000cdf60`也调用同一个manager函数，但它是另一路入口，**不是上述XPC remote与manager之间必经的一跳**。不能把两条入口误拼成串联调用。

客户端的reply block `0x20441b4e8`保存返回的endpoint UUID；有输出handler和有效UUID才登记handler；publish标志与有效UUID同时满足才调用publish。创建失败、连接归属失败和有效创建必须分开看待。

构造后还可进入`acc_policies_isTransportSupervised`、`acc_endpoint2_isTransportRestricted`、`acc_restrictedMode_accessoryAttached`；connection构造尾部也有sleep-assertion策略。这些路径没有被本轮逐层审尽，不能把“参数未被改写”扩展成“任何系统策略都不影响连接”。

## 4. publish不等于开始主动iAP2握手

已追到：

```text
ACCTransportClient.publishConnectionWithUUID @20441d540
  → XPC publishConnectionWithUUID:withReply:
  → ACCTransportServerRemote @10007f564（connection归属门）
  → acc_manager2_publishConnection @1000f648c
  → block @10018f9a8 → acc_connection2_publish @100192038
  → 异步连接队列 → publish_internal @1000f8d44
  → dictionary applier @10001182c → acc_endpoint2_publish @10018bdcc
```

关键条件：

- connection的publish内部先检查连接资源、销毁状态与是否首次发布，再遍历端点；另有EA端点集合更新和connection type=6的适配器属性分支。蓝牙type=2不能直接套用type=6分支。
- endpoint的协议专属发布分派先计算`protocol-7`，使用无符号范围门检查0…11。**protocol=0在此直接落到公共分支，不调用这些已知协议的publish函数。**
- 后续“protocol=5且connection type=6”的EA属性路径也不适用于该unknown/BT输入。
- 公共路径仍会发布analytics及连接/端点attached通知，设置published位。`0x1000168bc`设置`+0x59=1`并判断protocol是否为1；protocol=0不走其protocol=1专用通知。
- `0x1000fd738 → 0x10014f944`通知`accessoryConnectionAttached:type:info:properties:`；`0x1000f5f14 → 0x10014fa74`通知`accessoryEndpointAttached:transportType:protocol:properties:forConnection:`，后者仍传原transport/protocol。

这排除了“publish这个名字本身就表示开始主动SYN”的推断，却**没有排除通知接收者安装预算、关闭连接、更新属性等行为**。本轮不把所有协议的publish分支都标为已审完；只对本次transport=2/protocol=0输入下的可达性作限定判断。

## 5. 属性回调解析：不是版本，而是HIDFunction

### 5.1 注册了两个不同的回调

`bluetoothd@0x1007a4934`的两个导入由Mach-O间接符号表确认：

- `0x100909f70`：`acc_transportClient_setConnectionAuthStatusDidChangeHandler`，block对象`0x100bca6b8`的invoke为`0x1007a49b8`。
- `0x100909f80`：`acc_transportClient_setEndpointPropertiesDidChangeHandler`，invoke为`0x1007a4c04`。

dispatch_once是一次性注册，不是周期重试计时器。

### 5.2 属性回调的输入含义与全部前置门

CoreAccessories桥接`0x20441520c`明确将回调参数排成：`endpointUUID, currentProperties, previousProperties, connectionUUID`。

因此，进入`0x1007a4d78`时，**x4是connectionUUID，不是endpointUUID**。该值用于查找连接对应的蓝牙对象及调用`acc_transportClient_isConnectionAuthenticated@0x100909f30`。不要因为回调名称含endpoint就把两个UUID混为一个。

已核对的门：端点可查到 → current属性非空 → 连接对应蓝牙对象存在 → 连接已认证 → previous属性尚无可读取的HIDFunction → current属性有可读取的HIDFunction。任一不满足均不调用后续虚表。

`0x1007a5628`从GOT槽`0x100bfc008`取得键；间接符号表确认该键是`kCFACCProperties_Endpoint_Bluetooth_HIDFunction`。读取用CFDictionaryGetValue及CFNumberGetValue(type=9)，成功后取低字节。这里检查的是**此前是否已有可读取属性**，不是通用的“新旧数值不相等”。

### 5.3 虚表+0xf0已找到实际目标

```text
global 100c1f460
  ← once函数1000bf330
  ← block 100bca7e8 / invoke1007a5a78
  ← ctor1006bb6b8 → 1006bb62c（名称字符串“HidService”）
  ← vptr = 100bc26a0 + 0x10
  ← vptr + 0xf0，即槽100bc27a0
  → 1006bc160
```

原槽的认证指针已从镜像重读，而不是按附近符号猜测。目标函数先调用`0x1005ec9a8`，将“已知”、auth布尔值和HIDFunction字节存入设备对象的`+0x49b/+0x49c/+0x4a4`；再检查该设备的`0x20`服务位，成立才转入`0x1006ad698`通知路径。

后者仍有一个虚表`+0x18`调用（`0x1006ad6fc`），其所有可能接收者尚未解析。因此已闭合的是“HID属性消费及第一层目标”，不是整个HID业务的全部副作用。

### 5.4 认证先后次序也有对应路径

另一个auth回调走`0x1007a49b8 → 0x1007a4a68`：根据connection找蓝牙对象，再取得endpointUUID及其属性；有HIDFunction时调用同一个`HidService +0xf0`，但auth参数来自本次回调，不是固定true。

这解释了两个入口的不同职责：属性随后到达时检查当前认证；认证状态变化时消费已有属性。不能遗漏后一条，也不能把认证状态通知当成收到iAP2 SYN的事件。认证状态生产者和状态枚举全生命周期未在本轮关闭。

## 6. 75扩展校验勘误：已确认手机端有偏严条件

重新从原accessoryd读取`iAP2LinkCommandIsFeatureSetValid@0x1000d4ee0`，100字节的SHA-256为`4a3ccf0061c756fa983b7ba7c7bb3fbda808e1befbba2f8b61ac4cd33931e4e6`，与既有`.bin`一致：

- `0x54 → 1`，`0x55 → 2`，未知值`→ 0x80000000`。
- `0x1000d4f10`是`ORR`，不是计数、加法或唯一性检查。
- 拒绝高位；低两位为0或3时接受。

| 扩展字节（十六进制） | 此函数结果 | 原因 |
|---|---|---|
| 空 | 接受 | mask=0 |
| 54 55 | 接受 | mask=3 |
| 54 54 55 / 55 54 55 | 接受 | OR后仍为3 |
| 54 54 | 拒绝 | 缺55，mask=1 |
| 54 55 56 | 拒绝 | 未知项置高位 |

上表是逐指令语义推导，**不是执行苹果函数或新增的实测向量**；整个SYN还受长度、扩展数量、session等独立校验约束。

75此前“必须各出现一次、Set会错误放过重复项”的解释错误，现明确撤回。[IapLink.kt第176行](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:176)仍要求`featureList.size==2`；本轮只读复查SHA与75一致，没有修改。

下一次获准改手机代码时应恢复集合语义，并补正上述重复且成对的测试预期。75的872项通过仍是历史事实，但其中这一预期不能作为苹果一致性证明；没有证据将此偏严门归因为用户先前某次车型故障。

## 7. 验证与下一步

证据：[iap2-xpc-handoff-hid.json](../evidence/iap2-xpc-handoff-hid.json)。工具：[inspect_iap2_handoff.py](../tools/inspect_iap2_handoff.py)，只读原镜像/缓存并输出JSON。

记录60个不同函数的边界/哈希：accessoryd 39、bluetoothd 15、CoreAccessories 6；其中41个函数存在既有`.bin`并与镜像一致；CoreAccessories六个函数另与原共享缓存字节一致。数量表示本批读取范围，不表示全分支覆盖率。原共享缓存只校验所读函数/selector/对象片段，不冒充整个dyld重新哈希。

未执行苹果程序、未新增手机协议测试、未连蓝牙/车机、未打包。文件/链接/JSON检查不验证协议语义。

最终复核结果：`verify`通过（3份源镜像、60个函数、41个既有缓存函数、6个原dyld函数字节）；`validate_docset.py`通过（46份Markdown、38份JSON）。

复核示例：

```text
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_handoff.py function --component CoreAccessories --address 0x20441b138
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_handoff.py imports --component bluetoothd --address 0x100bfc008 --address 0x100909f30
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_handoff.py function --component accessoryd --address 0x1000d4ee0
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_iap2_handoff.py verify
```

剩余研究优先级：

1. 沿本章两种attached通知的接收者、受限模式和sleep-assertion入口，查清无输入预算由谁安装、超时后是主动探测还是退出；不要根据函数名替它决定。
2. 继续其他端点provider及取消/重连分支；HID后续观察者单独记录，避免把HID业务当iAP2握手主线。
3. 单独实施75扩展门勘误后，再继续profile/session参数生命周期与第二SYNACK协商；Identification完整三方比较仍待后续。

此时可关闭的是指定XPC参数交接和HID首层回调归属；上层预算、全入口策略、端到端互通继续PARTIAL/OPEN，无新增车型兼容性承诺。

## 8. 77批次跟进

[77](77-iap2-extension-wait-boundary.md) 已按本章第6节的建议修正手机端扩展集合门，并补齐重复项/长度回归；因此“本轮只记录、未改生产代码”是76的历史状态，当前代码状态以77及其证据为准。77继续确认：普通蓝牙 type=2 不走本章提到的受限模式入口；电源保持的5秒定时器是睡眠断言到期清理，不是SYN等待定时器。publish attached通知已追到XPC client filter/remote proxy边界，但上层预算和全部receiver仍未闭合。
