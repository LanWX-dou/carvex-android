# 当前手机实现与研究基线的差异

本章比较实际工作树，不采信注释中的“与固件一致”作为证明。源码根为 `D:\carvex-research\android`，关键文件哈希见 [baseline.json](../evidence/baseline.json)。只做审计，没有修复或移植任何差异。

**差异不自动等于缺陷。** 原24A446存在某分支，不代表当前车机一定需要；当前已经工作的组合也不证明字段选择正确。先把路径条件、消费者行为和运行样本对应起来，再决定手机端修改。

新增优先级审计见 [62 — 版本／能力声明与实际行为](62-version-capability-audit.md)。其中iAP2版本准入与业务支持、4301能力交接、协议版本头缺省和构建号接收门槛按实际条件分开，不能将下表“身份组合不同”直接解释为只需修改字符串。

## 1. 连接策略差异

| 项目 | 当前手机实现（ANDROID_NOW） | 原固件证据或缺口 | 对诊断的意义 |
|---|---|---|---|
| 首次蓝牙配对 | `Bootstrap.kt:128` 只从 `bondedDevices` 选目标，未配对直接报错 | 本轮未闭合原iPhone首次系统配对及用户授权全流程 | 现有App成功连已配对车，不能作为从未配对开始的覆盖证明 |
| RFCOMM多方向 | `Bootstrap.kt:134–260` 注册多个listener，出向按v2/legacy选择，先成功socket胜出并释放另一个 | 蓝牙服务角色及精确SDP映射见bootstrap章；部分原始映射尚待核实 | 查实际选中socket，不只查“Bluetooth connected” |
| 超时 | `SessionController.kt:541/548/552/610/612/640/649` 分别设置90s、25s、90s、45s、20s、90s、15s的局部阶段预算 | 这些是当前App控制值，未证实等于苹果原定时器 | UI阶段文字、外层预算与底层socket超时要区分；不能搬进规范作为MUST |
| 交接策略 | `SessionController.kt:577–583` 150s handoff，`requiresTargetIap=false` | 23G90原日志实际出现目标AirPlay承载上的新iAP识别/认证；不代表所有路径都必须 | 当前“目标就绪”定义并不等于全部车机的目标iAP事务已完成 |
| 发现/邀请分支 | `AirSession.kt:298–352` 缓存metadata分支等待invitation，其他分支在discovery失败时可用4301端点；最终354行仍统一打印“invitation validated” | 原入口和条件见AirPlay章，不能从一条统一日志推出所有前置都完成 | 现有成功日志在部分路径表述过强；审计实际分支和逐项状态 |
| 控制端口 | `AirSession.kt:366` `metadata.port ?: bootstrap.port` | 4301与服务发现端点如何仲裁的完整原路径仍需核实 | 同时记录两来源与真正连接的端口，不以注释保证选择正确 |

## 2. AirPlay消息与能力差异

| 项目 | 当前手机实现 | 24A446本轮原证据 | 结论 |
|---|---|---|---|
| 身份组合 | `CarPlaySourceIdentity.kt` 使用sourceVersion `320.17`，兼容osBuild `21A329`，实际Android型号/osName/osVersion | 原SETUP producer所用sourceVersion为 `980.77.1.2`；详见AirPlay章 | 明确不是完整复刻一台24A446 iPhone；不得为“好看”只改版本字符串 |
| SETUP路径回退 | `AirSession.kt:517–525` connection URL拒绝后按条件重试`/setup` | 未在本轮证实这段重试与原行为完全一致 | 手机兼容策略，不能上升为统一协议流程 |
| 独立/info | `AirSession.kt:527–539` 初始SETUP后固定请求`GET /info` | `_apsession_requestControlSetupWithResponse(0x251a59338)`可消费SETUP内嵌GetInfo；verification也可提供 | 本轮证实存在原分支差异；不代表这就是任何车型失败的根因 |
| RECORD | `AirSession.kt:692` 有屏路径固定发送 | Stage2 `0x2519c69f0`依据started与skipRecord等条件 | 不能在文档中把每次RECORD都列成必经 |
| eventPort | `AirSession.kt:747` 缺失或不在1..65535直接失败 | 原ensureEventStreamCreated允许port=0时不建立该独立stream并返回成功 | 需结合具体会话路径验证；不可一律要求每个SETUP回复都带事件端口 |
| 视频流回复数量 | `AirSession.kt:685` 查找第一个type110条目 | 原`0x2519bbf24`消费该请求的回复时要求streams恰为1且type相等 | 当前检查较宽；不能以其接受多个条目证明苹果也接受 |
| 视频SETUP日志 | `AirSession.kt:619–645/659` 先构造并打印含uuid/latencyMs的字典，实际候选使用`measuredStream`，含type/streamConnectionID/timestampInfo | 字段含义及原生产条件见video章 | 排障要以实际序列化body为准；不能用“video SETUP keys”一行代替发出字段 |
| 视频keepalive | `AirSession.kt:697–704` 每1s尝试type2无正文record | 原record存在不等于本轮已证实其固定1s周期 | 当前本地周期策略，不能写成苹果规定 |

## 3. 成功状态不能夸大

### 3.1 控制帧与响应分派的新增对照

新增源码快照为 `core/Rtsp.kt`，以及同次重新核对的 `AirSession.kt`，哈希见 [control-wire-evidence.json](../evidence/control-wire-evidence.json)。这仍是静态源码，不证明测试APK构建或实际车型行为。

| 项目 | 当前源码 | 24A446对照与边界 |
|---|---|---|
| CSeq起始/回绕 | `Rtsp.kt:106–112`，从0的AtomicInteger产生首个1，达到正整数阈值后回1 | [22](22-control-wire-contract.md) 原发送器发送旧u32再保存递增值；首个原值未闭合。两者生命周期不相同，但不凭首值差异认定故障 |
| 同步响应归属 | `Rtsp.kt:202–234`，忽略已识别的旧oneWay响应；其它缺CSeq/不匹配响应继续消费 | 注释中的“固件只写不读且不回填”不是本轮全栈已证事实；22只恢复对象/token局部关系，全部底层过滤仍OPEN |
| 异步响应归属 | `Rtsp.kt:285–295`，用数字CSeq查pending；无匹配则记unmatched，不交给waiter | `AirSession.kt:513`在初始控制SETUP前启动reader，因此SETUP之后不能用上述同步容错解释行为。缺失/不匹配CSeq可能表现为已有响应却waiter超时，需具体日志才能认定现场原因 |
| Header framing | `Rtsp.kt:54–67`要求CRLFCRLF、header小于16384、拒绝重复字段及所有Transfer-Encoding、body上限4MiB | 原局部header scanner容量8192且识别LF空行，通用reader有chunked路径；这些是解析策略差异，不能推定目标车机会使用LF/chunked，也不建议盲目放宽安全校验 |
| 空body发送 | `Rtsp.kt:76–79`始终追加Content-Length；请求也始终带传入Content-Type | 原SetBody分支写长度/条件MIME，但某些无body路径不调用SetBody；不要称所有苹果请求都一定带相同header集合 |
| 建连控制等待 | `AirSession.kt:61/516/530`在初始SETUP和独立info阶段使用60,000ms，随后改10,000ms | [24](24-disconnect-reconnect.md) 原kind5控制创建传入10、event用provider默认60/覆盖，并有底层消费/fallback。当前源码“固件量级”注释不证明这两套条件等价；不能只把数字改成10即称复刻完成 |

### 3.2 显示验收

`SessionController.kt:693–696` 在第一个视频帧写入通道后更新为STREAMING，同时文案明确“车机画面、触摸和持续运行尚待实机确认”。因此本项目把它归为**发送端检查点**，不是最终显示验收。

`SessionController.kt:650–655` 没有可用display时可继续无视频会话。这可能有其他功能价值，但不满足本阶段“到视频可投”的目标，不能作为成功替代品。

## 4. 修改前应满足什么

