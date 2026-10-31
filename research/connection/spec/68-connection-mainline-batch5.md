# 68 — 连接主线第五批：扩展能力与无线 SETUP 请求


## 1. 本批落地范围

| 原代码差异 | 本批手机行为 | 证据与边界 |
|---|---|---|
| Bonjour只读取64位`features` | 优先解析`fex`为变长、字节内低位优先的位图；只有fex缺失才读legacy features | 原解码容错、来源与F80见[28](28-feature-source-branches.md)；1024字符上限是本地资源边界 |
| 缺失、解析失败、高位能力都可能丢成null/低64位 | 保留source/problem/full bitset，经ReceiverMetadata→BootstrapSecurity→SecurityInputs进入实际安全路由 | 畸形显式报SECURITY_INPUT_MALFORMED；已知F80报PAIRING_MECHANISM_UNSUPPORTED，不开放尚未实现的交换 |
| 无条件写通用`timingProtocol=NTP`、`isScreenMirroringSession=false` | 无线kind5构造器不再添加这些字段 | [29](29-control-setup-request-branches.md)：common prefix后kind5提前结束；内存中NTP不等于线上必发timingProtocol |
| 固定`features=[]` | 无提供者结果时不发；接口保留显式空数组与缺失的区别 | 普通ensureStarted输入为NULL；专用Stage1可由调用者透传数组，上游内容仍OPEN |
| timing端口与任意固定字段混写 | 只带当前真实已绑定、未关闭的timing socket端口；零/null不带 | 对应原时钟成功启动→PortLocal→session+0xc0非零的presence；原时钟完整算法未复刻 |
| 屏幕SETUP手写两份对象，追加固定timestampInfo | 日志与发送共用`CarPlaySetupRequests.screen`；本普通路径不自动追加timestampInfo | [32](32-screen-setup-request-branches.md)：kind5跳过自动生成；不声称额外options永远无法带同名键 |
| 屏幕`latencyMs=100` | 改成无线缺省75ms | `_APSCarPlayScreenLatencyMs`无线默认75、USB默认25，可被苹果偏好覆盖；不是测得的画面/声音实际延迟 |
| 单屏无UUID也可继续发送 | 已选中display缺UUID时在SETUP前明确失败，不随机伪造或借aux分支补值 | 普通screen_initDisplayInfo原缺失路径报-16760；不代表辅助屏幕全部实现 |

`CarPlaySetupRequests`已由AirSession真实调用；不是只添加一个未使用的测试模型。控制字段、屏幕字段均经过实际`AirPlaySetupSession`/`RtspClient`序列化测试，检查捕获的RTSP body。测试不再只对一份测试内手写字典做plist往返。

## 2. 身份与条件字段仍不能声称完全一致

- 本批保留`sourceVersion=320.17`与`osBuildVersion=21A329`已有兼容组合。24A446控制生产者的版本字面量为`980.77.1.2`，所以当前**仍不是完整24A446身份复刻**。版本与实际支持集合、加密/AAD必须一起核对，不能改字符串就算完成。
- Android真实model/osName/osVersion继续保留；原固件common prefix确有osName/osVersion，来自系统版本字典，不是non-kind5专属字段。
- `sessionCorrelationUUID`提供者是`APSCopyBootUUID`→`kern.bootsessionuuid`，不是sessionUUID。本地尚未接入等效启动周期提供者，暂不发送，不用每次连接随机值冒充。
- `keepAliveLowPower`仅APTransport的`TransportType==2`时写true。该属性不能与session kind5、iAP2 raw kind4/2混为一谈；Android映射未闭合，真实调用不凭“无线”添加此键。
- builder支持上述已审条件输入，但当前AirSession没有接入它们的提供者。接口存在不等于生产路径已完成。
- 当前sessionUUID、streamConnectionID仍用既有本地生成策略；原transport UUID、屏幕UUID前8字节转换与完整cryptor生命周期尚未全部等价。streamConnectionID不在本批盲改。

## 3. 扩展能力不是完整认证实现

完整位图用于保留证据及阻止误选。F80可表示且可识别，不等于已经实现MFiMutualAuth。现有CU/HAP策略、AA/SAP信任与签名材料门槛没有被绕过。

新事务已有4301/startReady也不能忽略已知F80或畸形能力；仍先检查已存在的上下文/网络前置。已绑定verify continuation优先级保留，尚未ready的iAP入口仍等待参数，缺失Bonjour能力也不凭空改成明确不支持。具体路由仍是有界本地实现，不是全套苹果AuthenticationType状态机。

EndpointInfo的FeaturesEx表示和固件来源被分别记录，但本批实际生产接入点是Bonjour fex；不能据此宣称认证前公开info、认证后info更新与所有override已闭合。4301/Bonjour/邀请的完整身份融合仍需要继续查。

## 4. 验证记录


| 检查 | 实际结果 |
|---|---|
| protocol-carplay全部单测 | 838项/114组，0失败、0错误、0跳过 |
| core全部单测 | 79项/12组，0失败、0错误、0跳过 |
| 合计 | 917项；相对上批890净增27，不重复累计定向运行 |
| 小米Kotlin编译 | 成功；最后一次增量检查UP-TO-DATE |
| git diff --check | 通过；既有CRLF提示不是空白错误 |
| 三份固件证据重核 | 主任务均PASS：features 4镜像/9函数；control SETUP 15函数及keys/imports/anchors；screen 16函数/9跳板/13键/36检查点/5绑定 |

净增27项为扩展能力17项、控制builder7项、SETUP实际wire/缺UUID3项。原屏幕手写字典测试已改为调用真实生产builder。最终完整命令：

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest --rerun :app:compileXiaomiDebugKotlin --no-configuration-cache
```

本地编译仍有现存NSD废弃API等警告；没有把BUILD SUCCESSFUL解释成无警告或实车通过。证据完整性检查也不等于全部原函数语义覆盖。

## 5. 下一段工作

优先继续补**4301、Bonjour和邀请如何选择同一车辆/控制端点，以及端点属性如何进入认证事务**，包括已有网络、首次连接和再次连接三条入口。随后再接已查明但Android缺提供者的字段，并闭合实际密码事务与资源许可顺序。

G3/G4/G5/G7/G8/G9仍为PARTIAL；静态分支、报文字段和本地测试都不能替代车机首帧、持续显示、重连验证。本批没有实车运行结果，也不是“只差用户测一下”。
