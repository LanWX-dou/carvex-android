# 29 — 24A446 control SETUP 请求：共同字段与 kind5 早退分支

本章基准为 iPhone18,1 / 24A446；只静态读取原始 dyld、提取的 Mach-O、相邻汇编及反编译缓存，不执行固件、不修改车机。它补充 [27 — SETUP 响应分支](27-setup-response-branches.md)，不以旧文档或 Android 当前实现反推固件行为。

## 结论与边界

`_apsession_appendControlSetupRequest@0x251a59708` 不是“所有 AirPlay 字段全部发给 CarPlay”。共同前缀之后，kind5 有专门尾部并直接跳到清理；**kind5 不经过 `timingProtocol`、PTP peer、combined-get-info/qualifier 的通用尾部**。但 `timingPort`、`osName`、`osVersion` 在该判断之前，不能一并删除。

本章闭合了请求 producer、两个 features 输入入口、时钟端口获取和 boot correlation provider。没有闭合 CarPlay 上层 features 数组的元素生产者、全部网络时钟实现、TransportType=2 的最终物理承载标签，不能宣称所有 iPhone 分支已经复刻。

## 1. 调用链及新字典

`_apsession_requestControlSetupWithResponse@0x251a59338` 新建空字典，放入 `updateSessionRequest` 布尔，再调用 `appendControlSetupRequest(session, dictionary, features)`；成功后发 control SETUP。此 wrapper 没有在 append 之前另写 timing 字段。

`_apsession_ensureControlStreamSetup@0x251b5cfe0` 在 `session+0x81` 已设置时直接返回，否则以 `update=false` 调该 wrapper。响应解析仍见第27章，不在此重复。

## 2. kind5 的共同前缀

下表“省略”是键不存在，不等同于 false、0、空串或空数组。`+偏移` 均是恢复的内部 session 布局，不是线上帧偏移。

|字段|原 producer 条件与值|实现注意|
|---|---|---|
|`updateSessionRequest`|wrapper 输入布尔；append也读取它决定后续行为|初始SETUP为false，更新入口不同|
|`deviceID`|kind5先查询 CFString `k5lVWbXuiZHLA17KGiVUAA` 的偏好值；有值则使用，否则调用本地6字节ID provider并格式化|这串是查询键，不是写死的设备ID|
|`sessionCorrelationUUID`|kind<6且kind!=3；调用 `APSCopyBootUUID`，通过nullable字典setter写入|kind5包含；失败时省略，详见§5|
|`et` / `ekey` / `eiv`|key holder `+0x150` 存在，且endpoint不支持CoreUtils pairing/encryption时进入|不是全部会话固定et=0；详见§3|
|`macAddress`|从真实control transport stream的`LocalMACAddress`取值，6字节格式化|不是从对端MAC猜测|
|`model` / `name` / `osBuildVersion`|各本地系统provider|需要与兼容身份策略分开记录|
|`sessionUUID`|从transport session的`UUID`属性取UUID，转为字符串|不同于boot correlation UUID|
|`sourceVersion`|此版本固件原始字面量 `980.77.1.2`|不能只换字符串就宣称支持对应能力|
|`statsCollectionEnabled`|始终写布尔，来自`+0x58`|false与省略不等价|
|`highFreqStatsCollectionEnabled`|仅`+0x59 != 0`时写true|false时省略|
|`timingPort`|仅`+0xc0 != 0`时写数值|实际网络时钟的PortLocal，详见§4|
|`isRemoteControlOnly`|仅kind1/6/7/8|kind5省略|
|`isScreenMirroringSession`|仅kind4/9，写true|kind5省略，不写false|
|`isAuxiliaryScreenSession`|仅上述mirroring分支内且`+0x162 != 0`|kind5省略|
|`isSharedConnection`|仅`+0x10 != 0`时写true|非共享时省略|
|`diagnosticsAndUsage`|仅系统getDiagnosticLogSubmissionEnabled()为true时写true|由系统策略产生|
|`internalBuild`|与上一项同一分支，值由内部构建provider决定|不是无条件身份字段|
|`osName` / `osVersion`|共同前缀调用`__CFCopySystemVersionDictionary`，分别取`ProductName`/`ProductVersion`，nullable写入|**不受diagnostics/非kind5条件限制**；缺值省略|

关键指令：`0x251a59ed8` 在diagnostics关闭时直接跳到 `0x251a59f10`；`0x251a59f54`/`0x251a59f68` 写osName/osVersion；kind5判断在之后的 `0x251a59f78..f84`。将osName/osVersion误归为non5会漏字段。

共同前缀还要求transport session `+0xf0`、control stream `+0xf8`存在；LocalMACAddress和transport UUID的属性取得失败有错误退出。不能为了凑出请求字典，消除这些provider/错误门槛。

## 3. 加密字段 gate

`0x251a599b8` key holder为空跳过整个块；`0x251a599bc` CoreUtils支持为真也跳过。进入后按holder内部类型选择wire `et`：类型8→16、4→32、1→2，其余/缺getter→0。此映射不是endpoint feature bit映射。

`ekey`、`eiv`要在holder密钥getter和准备操作成功后才添加；失败走错误清理，不降级为随便填0。这里只闭合共同prefix的存在条件与映射；holder如何创建、认证后选择哪种类型、密钥生命周期仍不在本章完成声明内。

## 4. timingPort 与 timingProtocol 必须分开

### 4.1 constructor

`APSenderSessionAirPlayCreate@0x251a53780` 在kind1/6/7/8直接选择内部时钟协议`None`。kind5不在此mask内，要求调用方提供network clock；空对象走创建失败。

它从clock的CMBaseObject读取`NetworkClock_Type`，和`NetworkClockType_PTP`相等则内部`+0x280=PTP`，否则`NTP`，retain clock到`+0x290`，设置`+0xe6`。这是内部配置，不代表该字符串一定发在线上。

### 4.2 启动与实际端口

Stage1在`0x2519c60a8`调用`APSenderSessionShouldEstablishNetworkClockLink@0x251b5b358`。返回真才启动clock；false路径设内部协议`None`并释放clock。predicate先排除kind1/6/7/8；其余路径默认建立，只有特定PTP/shared-receiver-clock/cluster条件可以跳过冗余链接。它不是“kind5一律无时钟”。

`_apsession_ensureSenderNetworkClockStarted@0x251a58ddc`：已启动标志`+0x82`置位则不重复启动；否则要求`+0x290`存在，调用clock provider start，成功后设置标志并注册peer-list通知；读取其 `PortLocal`，在 `0x251a5908c` 保存32位值到`+0xc0`。随后按内部协议判断是否继续PTP相关配置，启动/配置失败会清理clock。

`PortLocal`的导入链是 `0x268104060 → 0x268a95300 → CFString 0x273d51100`。SETUP共同prefix在 `0x251a59d90..da4`检查非零后才写 `timingPort`。Android若确已绑定自己的NTP UDP端口，应使用真实端口；不能因为kind5不发timingProtocol而删除timingPort，也不能宣称任意固定端口是固件同款。

### 4.3 kind5早退

`0x251a59f7c` compare5，`0x251a59f84`只有非5才跳通用尾部。kind5读取transport session的`TransportType`；属性取得出错则失败。成功且等于2时写`keepAliveLowPower=true`，其他值不写；随后处理features，`0x251a59fe8`无条件跳`0x251a5a36c`清理。

因此kind5此producer不写：`modelCode`、`udid`、`timingProtocol`、`timingPeerInfo`、`timingPeerList`、`asyncPTPClockConfig`、`combinedGetInfoWithControlSetup`、`qualifier`，以及同一通用尾部的group/其他非CarPlay字段。对于qualifier，“有此通用代码”不等于kind5执行了它。

TransportType属性在APTransport `session_CopyProperty` → `0x24fda839c` → `session_getSessionTransportType@0x24fe11400`，从control connection的`NetTransportType`转换：1/2原值；4→3、8→4、16→5、32→6、64→7、128→8，其余0。因此当前只可断言“session TransportType==2”产生该键；**本章尚未证明2的最终物理承载标签**，不能凭网络/无线字样无条件加keepAliveLowPower。

## 5. sessionCorrelationUUID 是启动周期 UUID

`0x251a59970 → stub 0x258109610 → AirPlaySupport 0x226e65c24`，原始Mach-O符号表将后者绑定为`_APSCopyBootUUID`。

该函数分配37字节缓冲区，通过`sysctlbyname`读取原始C字符串 `kern.bootsessionuuid`，再创建CFString。producer不检查此getter的状态，而使用`FigCFDictionarySetValue@0x18efab8e0`；该helper在value为NULL时直接返回，所以getter失败时键省略。

这不是每次连接随机UUID，不是transport `sessionUUID`，也不是设备永久ID。Android的boot级等效provider尚需实现与权限/生命周期验证；在闭合前不能用随机会话UUID冒充。

## 6. features 值来自哪里

`0x251a59fcc`取append的原始param3；NULL则省略；非NULL则直接写array。该函数不检查数组是否为空，不合成默认空数组，也不把receiver位掩码转成array。

Stage1 `0x2519c5858`的输入是上下文对象：`+0=session`、`+8=features`、`+0x10=另一输入`、`+0x18=响应输出槽`。`0x2519c61ac`载入`ctx+8`，在`0x2519c61c8`传给ensureControlStreamSetup，再原样传给request/append。

两个已审阅入口：

- 普通`ensureStartedInternal@0x2519c4688`初始化ctx+8=0，所以该入口不发features。
- `PerformStage1StartTransaction@0x251a587a0`只在kind5调Stage1，并将调用方param2原样存ctx+8；调用方提供非NULL空数组时才会真正出现`features=[]`。

更新入口`0x251a61ab0`以features=NULL、update=true调request。**CarPlay更高层到底提供哪些元素仍OPEN**；删除无依据的固定空数组是存在性修正，不代表已经重建完整上层features清单。

## 7. Android落地的安全边界

能据本章直接实施：kind5省略固定`isScreenMirroringSession=false`、省略通用`timingProtocol=NTP`、不凭空创建`features=[]`；保留已启动的真实timingPort；按照provider值与存在性处理osName/osVersion，不把它们误删为non5字段。

仍须单列差异：Android当前兼容声明`sourceVersion=320.17`、`osBuildVersion=21A329`不是24A446原值；真实Android的系统名字/版本也不等同iPhone系统身份。不能本轮只换成新字符串却不验证整个能力/认证矩阵。认证gate、keepAliveLowPower的承载映射、boot UUID provider、上层features数组不能通过猜值补齐。

## 8. 可复核证据与验证

[只读检查器](../tools/inspect_control_setup_request.py) 对15个原函数做原dyld/提取Mach-O一致性、完整ARM64指令解码、已存在cache片段一致性检查；解析26个CFString、8条属性导入链、20个关键指令锚点，以及4个原始符号provider。未创建额外固件缓存。

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_control_setup_request.py --verify D:\carvex-research\research\connection\evidence\control-setup-request.json
```

[证据快照](../evidence/control-setup-request.json) 中函数hash用于定位复核，不代表函数所有可达provider都已审阅，更不代表真车成功。原反编译Stage1 `0x2519c5858`失败，本章直接沿原汇编恢复其features参数流，没有把失败的反编译视为已证明结果。
