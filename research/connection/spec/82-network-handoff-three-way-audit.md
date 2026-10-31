# 82 — 网络交接三方核对：先联网、启动邀请与迟到端点


后续状态：[83 — 手机端异步网络交接](83-network-handoff-implementation.md)已实施本章建议的有界编排。本章“当前源码”均指82审计时的修改前快照；证据JSON及旧源码哈希保持不变，其整体验证不能在修改后的手机工作树上继续要求源码哈希一致。原固件静态结论与未闭合项仍保留。

## 1. 结论与优先级

当前最值得修的是**手机端异步交接没有贯通**，不是增加车型配置，也不是简单缩短超时。

1. 5703 解析层已经提供平台回调，但实际连接入口没有传入回调；声明了两条路径的车机先给5703时，我们仍可能等4301到原30秒预算才开始联网。
2. 5703-only 路径先等待车机 `_airplay._tcp`，拿到端点后才构造 AirSession、发布手机 `_carplay-ctrl._tcp`。如果车机等手机服务/邀请才开放其服务，这个顺序形成互等，前面的30秒即使去掉也不解决它。
3. 初次Bootstrap返回后，蓝牙消费者不处理迟到4301；合法部分4301的观察回调同样没有实际消费者。
4. 已有网络可以复用，但只能在本轮Bootstrap成功以后到达复用代码；没有“旧SSID直接等同本轮已授权网络”的分支，这个安全边界应保留。

以上前三项是**当前源码可确认的结构缺口**；“哪辆车具体因它失败”仍需要关联时间线，不能冒称已复现实车故障。25章已指出异步/邀请链未完整；本章把它定位到实际入口与调用顺序，不把旧解析层修正说成从未存在。

## 2. 比较口径

- 我们：`D:\carvex-research\android` 的当前工作树，不用HEAD替代已有修改。
- 固件：原24A446镜像函数/原dyld字节复核。能定位局部分支，不等于完整跨进程时序已经闭合。
- “首次/重连”是测试场景，不等于5703/4301两种消息。首次也可能直接4301，重连也可能重新给5703。


## 3. 四类路径与关键差异

|---|---|---|---|
| 声明5702/5703及4300/4301；5703先到 | 记录配置；请求过4301则继续等待原handoff deadline，未先启动Android联网 | 解析5703即回调主控启动联网；随后发4300，给4301短窗口 | 5703独立异步交平台已证，不能把4301作为它的普遍前置 |
| 只有可用5703路径，无直接端点 | 可较早返回Bootstrap；联网后先等车机_airplay，再发布手机ctrl | 广播早于端点解析，联网后重新发布；等待邀请/发现，另有网关兜底 | 手机ctrl服务与邀请入口存在；全5703→发布时机未闭合，但我们当前先发现后发布存在条件互等 |
| 完整4301直接给凭据与端点 | 本轮校验后联网；AirSession发布/发现；发现失败可走4301地址 | 完整地址+端口时跳过邀请等待，直接后续配对 | 固件4301独立交平台。不能让下一批修复强迫所有直接4301路径都等待邀请 |
| 空/部分4301 | 语法正确可调用observer；生产observer为空，不能生成本地端点则继续等 | 可能保留无端点状态；晚到消息再热更新/重试 | 原4301允许缺字段交平台；不代表所有缺项都应无条件继承旧会话 |
| 已连相同SSID且本轮有有效配置 | Bootstrap之后检查activeNetwork、SSID、接口/地址，复用 | 凭据回调中检查boundSSID及currentNetwork，可跳过重复加入 | 我们并非完全不支持复用；缺口在更早的交接与lease生命周期，不是简单删SSID验证 |
| 本轮无凭据、进程记得旧SSID | previous参数未被wifiConfig使用；不能靠旧配置越过本轮Bootstrap | knownCarSsid可构造空地址/端口的credentiallessEndpoint；也有空SSID保持BT等待分支 | 原helper存在SSID、UUID、时间和地址等门；没有证据支持“只记得SSID就允许本轮连接” |
| Bootstrap返回后的4301 | 落入unsupported日志，不更新候选 | pump持续处理；取消/推流/配对中/空闲分支分别处理 | 原handler是消息输入入口，不是一次性配置结果；完整迟到/重启策略仍需平台状态与世代保护 |
| 对端请求5700 | 有provider接口，生产未接；没有快照/授权则不发5701 | 本批所审Iap2SenderSession没有5700/5701专用消费路径 | 固件有锁屏、未联网提示及共享授权分支；它是设备Wi-Fi共享，不能当车机热点5703的反向填空 |


## 4. 我们的实际依赖顺序

```text
SessionController.runner.negotiate（未接Wi-Fi/Start callbacks）
  ├─ 同时请求两组、5703先到：继续等4301或原handoff deadline
  └─ 产生可用WifiBootstrap
       → openNetwork（此时才加入或复用Wi-Fi）
       → 若没有endpoint：ReceiverDiscovery.await(_airplay)
       → openSession → AirSession.prepare
       → publish(_carplay-ctrl) + 邀请监听
```

条件互等：车机“先发现手机ctrl才开放_airplay”；手机“先发现_airplay才发布ctrl”。这是明确可推导的依赖环，**不是我们已观察到所有车机都遵循该顺序**。

精确定位（均在当前手机工作树）：

- `bridge/.../session/SessionController.kt:552–559` 只传NowPlaying callback；`:630–638` 联网与无端点预发现；`:642/660` 才创建/prepare AirSession。
- `protocol-carplay/.../carplay/CarPlayRunner.kt:50–74` 暴露并转发三个nullable callback，默认null。
- `Bootstrap.kt:399–405` 按声明路由发5702/4300；`:423–447` 等待/5703-only退路；`:631–723` provider与观察入口。
- `AirSession.kt:294–297` prepare内publish，然后发现；已缓存metadata分支还会等待invitation；`:922–969` 实际监听/NSD注册与邀请校验。
- `SessionController.kt:621–623` 后续BT只消费Identification、重复5703，其余TLV记unsupported。不是“BT链路没读数据”，而是读到了却没分派4301。
- `Bootstrap.kt:876–879` previous参数未用于构造新会话；`:919–935` 只在activeNetwork同SSID且本地地址就绪时复用。复用路径不新注册onLost，仍是25章的开放项。

另一个重构约束：当前邀请peerMatch依赖4301/Bonjour地址集合。**只把publish调用向前挪、但仍要求先有端点才能收邀请，可能把同一互等藏到校验条件里。**需要独立的邀请候选输入，绑定选中网络与本轮上下文，后续再与端点/安全身份汇合；不能为绕过互等而无条件接受任意局域网邀请。


### 可参考的事件分离

- `iap2/Iap2SenderSession.kt:337–345`：5703回调先于等待4301。
- `SessionController.kt:452–481`：主动/被动BT入口都接Wi-Fi与late-endpoint回调。
- `SessionController.kt:570–572,794–819,1041,2271`：启动时发布、凭据到达时联网、网络绑定后重新广播。
- `Iap2SenderSession.kt:499–568`：保活消息泵继续消费4301，先于日志限流。
- `SessionController.kt:1964–2002`：取消后不复活、推流中不重启、配对中更新候选、空闲时再发起。不能据此证明它已覆盖我们需要的全部generation/epoch竞态。
- `net/CarPlayCtrlAdvertiser.kt:124–208`：重注册服务时保留监听socket和端口，避免把已广播的端口先关掉。

### 不直接复制

1. `ReceiverProfile.kt:106–130` 的总清单数量>=10及UNKNOWN试探，不是固件规则。
2. `Iap2SenderSession.kt:363–366` 无条件发4300，也不能替代平台availability状态。
3. `SessionController.kt:1897–1903` 的网关+7000回退缺少本批原生依据；服务发布端口与车机控制端口更不能混用。
5. 它的广播器network参数用于重注册状态比较，所审`start()`并未把Network放入NSD ServiceInfo；我们已有API33+指定Network及逐socket绑定，不能退化成依赖全局任意网络。
6. 不复制其认证/签名绕过、车型记忆、固定版本或日志中输出原始4301的做法。

## 6. 固件定向核对结果

### F01：5703的独立平台路径，以及不能省略的门

`0x1001703cc`解析5703后，在`0x100170670`取得wireless-CarPlay identification结果，并在`0x10017071c`安排platform work。block `0x1000c3180`将参数与该布尔值传给`0x100098754`；后者将snapshot置nil进入`0x10009875c`。

`0x10009875c`不是无条件联网：

- 插件对象不存在不调用消费方法。
- `0x1000989ac`检查wireless identification布尔值。
- 查connection UUID，使用给定snapshot或创建snapshot；不存在则退出。
- `0x1000989ec–9f0`要求`connectionType == 2`。
- 放入legacy connection ID后，`0x100098a38`调用`handleAccessoryWiFiInformationForWirelessCarPlay:`。

这些局部门没有“必须已有4301”条件。不能只摘“异步”两个字，省掉识别、连接来源和平台可用性。

WiFiSharing `0x2431186ac`进一步检查SSID为nil，以及“口令对象存在但security=0”；符合禁止条件不设置参数。security>=3进入诊断/映射0的路径，完整枚举与OS后续处理仍OPEN。此函数存在配置交接，不证明Wi-Fi已关联或ctrl已发布。

### F02：平台availability不是固定true的一次性问候

新核到server入口`0x100053b08`：按对象presence把wiredAvailable、usbIdentifier、wirelessAvailable、bluetoothIdentifier、themeAssetsAvailable放入字典，调用`0x100063e3c`。后者保留参数并异步调`0x100063f84`，该block分派内部handler ID `0x834`。

已有4300编码入口`0x10016e004`再次核对：wiredAvailable或wirelessAvailable**对象存在**才构造报文；false也是对象存在，标识可选。它不是“至少一个布尔值为真”才发送。完整client生产者、handler注册/所有触发条件、首次与变化时序仍需追踪，不能据本批宣称所有上游已闭合。

特别区分：`wirelessCarPlayAvailabilityDidChangeHandler @0x10016ca08`是4E0D/transport identifiers路线，不可因名字相近当成4300唯一生产者。

### F03：稀疏清单并未给出任意试探许可

`RequestAccessoryWiFiConfigurationInformation @0x100170bb0`在`0x100170be4`调用required-message检查；失败直接返回，成功才初始化5702。81已核消息组合表。本轮没有找到“清单短于某长度便跳过门”的证据，保留我们的完整声明组策略。

### F04：5700是有授权的独立provider路线

`0x10017020c → async block0x1000c3134 → 0x1000980e4`。

平台函数检查设备锁定、插件及当前Wi-Fi连接；未联网走连接提示，已联网走共享Allow/Ignore提示，锁定走解锁提示。`0x1001708e8`是5701序列化入口，状态与可选凭据受条件控制。本批未穷尽所有提示回调/状态枚举，不填造“成功”或返回车机刚给我们的热点密码。Android无法从普通接口取得任意已保存Wi-Fi密码时，应明确能力边界。

### F05：邀请与网络/会话汇合

- APTransport `0x24fe01ea4`在指定interface构造`_carplay-ctrl._tcp`/`local.`发布，并异步处理；它本身不要求调用者已经取到车机AirPlay端点。谁在何时调用它仍属于上游问题。
- `0x24fe387fc`核URL组件、用`%llu`扫描Receiver-Device-ID并调上层；不是只判断header存在。测试忽略开关可回200而不启动，不能用HTTP200等同完成。
- AirPlaySender `0x251a95354`接受connect并异步投递带deviceID的任务。当前原生链与Android只设一个`invited`布尔值并不完全等价。
- `0x24fd9c6b8`保留SSID、UUID、时间、接口和地址等条件，再构造内部StartSessionEvent；`:wirelessIPv6Addresses`、`:pairedVehicleIdentifier`等selector已从原dyld stub核对。不能用它证明“任意旧SSID可恢复”。本批不重新宣称整个helper所有分支/上游provider都已闭合。
- `0x100063fd0`继续证明4301按presence交平台；`0x24fd9842c`是Bonjour元数据构造入口，不是手机ctrl服务发布函数。

## 7. 建议下一批实施范围（本批未改生产）

优先做**一个按attempt/generation归属的网络交接协调器**，而非一组车型开关：

1. 接通5703事件：认证/Identification准入成功后，可用配置立即异步启动选定网络的加入或复用，不能阻塞iAP读循环；部分/错误配置继续保持已有语法与预算边界。
2. 把ctrl监听/发布从依赖完整endpoint的AirSession中拆出，在选定网络就绪后启动；与端点发现、4301等待并行，端口在本次网络lease内保持稳定。
3. 保留一个iAP业务消费者，初次及后续4301统一进协调器；不得同时有两个poll读同一队列。候选更新、重复消息、取消、世代变更和连接重启分开处理。
4. 完整4301仍可走直接端点；邀请和Bonjour是独立候选事件，不把任意一个强设为所有路径必经条件。地址/端口保留同一来源，不混拼。
5. 复用网络不复用认证结论：同SSID只算网络线索；仍绑定当前attempt/peer上下文、监听失网，旧回调不得复活新会话。

暂不实施：未声明5702、缓存SSID自动授权、固定7000、全部availability状态复制、5700假provider、完整security枚举改写。先补能明确消除本地依赖环的范围，再追精确平台策略。

至少需要离线覆盖：5703先到且4301等网络、仅5703且车机服务等邀请、完整4301无邀请、邀请早于发现、迟到4301、重复配置不重绑、部分配置修正、当前网络丢失、取消后迟到、epoch变化、旧SSID不同车辆、未声明消息。编排测试必须经过实际入口，不能只证明nullable callback在孤立单测可调用。

## 8. 本批验证及保留边界


复核命令（WSL）：

```text
python3 -B /mnt/d/carvex-research/research/connection/tools/inspect_network_handoff_comparison.py --verify /mnt/d/carvex-research/research/connection/evidence/network-handoff-three-way-audit.json
```

本批已实际执行：上述核验`ok=true`（20函数/4336指令/12快照）；`validate_docset.py`通过（52 Markdown/44 JSON）。后者只检查文件、JSON及相对链接完整性。

本批未跑新Gradle测试、未执行Android联网、未新增实车验收；81的1007项是上一批实现验证，不能冒充本批异步编排已通过。G5/G7继续PARTIAL，G6及真实持续连接仍待运行证据。
