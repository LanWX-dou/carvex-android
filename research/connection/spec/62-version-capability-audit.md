# 62 — 版本／能力声明与实际行为一致性审计

后续说明：以下是修改前的只读审计记录。用户随后授权修改手机端，第一批实现及验证见[63](63-alignment-batch1.md)；本章与JSON的原源码哈希保持历史快照，不改写为新源码来冒充同一输入。


苹果发送端基线仍为 iPhone18,1 / iOS 27.0.1 / 24A446。Toyota 接收库是独立样本，不代表所有 Toyota，更不代表奥迪。当前源码不等于用户手机上安装的 APK。第三方宣称支持某车型不能替代这些证据。

**目标约束：按24A446复刻，而不是将现有兼容组合固化为标准。** 当前 `21A329/320.17` 只作为现状记录和历史回归基线；最终应追到24A446的身份提供者、实际消息和相应行为。24A446的条件分支、旧对端处理也属于复刻范围，不能拿一条成功会话替代全部规则。不同版本命名空间各按原提供者／协商处理，不把iAP2版本、协议版本头、sourceVersion全部填成24A446；缺证据的目标字段保持OPEN，不能借当前代码补空白。本轮未获代码修复授权，不实施迁移。

## 1. 结论标签与优先级

- `PROVEN-SOURCE`：当前源码里可明确指出的行为或自相矛盾；不是实车故障归因。
- `PROVEN-STATIC`：指定固件镜像中的有界分支；不证明目标车辆执行它。
- `RISK-CONDITIONAL`：触发条件成立时有风险，条件是否出现在真实车机仍缺证。
- `HISTORICAL-REPAIRED`：旧不一致在当前源码已修；不得重复报为现存问题。
- `OPEN`：字段来源、消费、调用路径或实际结果尚缺证。

优先级表示后续验证顺序，不是严重性定论；先复核和做有界离线验证，再决定是否需要手机修改及车型复测。本轮不会为发现的每个差异增加车型白名单。

### 本批优先级摘要

| 优先项 | 已确认事实 | 为什么值得查／不能外推什么 |
|---|---|---|
| iAP2版本支持集合 | 链路可回发并提交control version>2；Bootstrap随后只允许1/2 | 协商承诺与上层支持不一致；只有实际对端提出该值才触发，不能据此改成永远回1 |
| AirPlay认证覆盖 | 当前formal或缺shared-secret路径进入尚未实现的SAP schema门槛 | 是实际功能边界，不是版本字符串能修复；禁止删除安全门槛伪装成功 |
| 协议版本头 | 初始／视频SETUP缺头，更新SETUP及info带1；苹果stup/info统一取provider | 高价值、明确发送差异；目标车机是否因缺头失败仍需消费者／运行证据 |
| 4301能力交接 | srcVer/sdkVer不进内建连接状态，mutualAuth仅日志；扩展能力消费不完整 | 有输入但未证明按24A446选择分支；需要补源到selector，不凭字段名猜映射 |
| 第二次SYNACK | 解析新提案后主要只采MTU/seq，仍提交第一份版本与session | 第二份参数变化时可能双方理解不一致；具体同时开链行为及触发证据需独立验证 |
| Identification接受 | 当前8/9未作required，12/13主要检查出现，承载组件未在该接受路径校验 | 已证比24A446宽，不等于一定造成拒绝；可能提前宣告接受不完整能力，需具体负例 |
| 构建号接入门槛 | 所审Toyota库成功取得minimum build且客户端较旧时SETUP失败 | 新的条件风险；最低值未取得，不能声称21A329已被某辆车拒绝 |

详见 [14 — iAP2](14-iap2-version-capability-audit.md)、[23 — AirPlay](23-airplay-version-capability-audit.md)。世代日志／features进制注释差异优先级低于真实功能缺口；目前没有把它们认定为实车根因。

## 2. AirPlay 协议版本头：已经确认的发送差异

证据：[version-header-evidence.json](../evidence/version-header-evidence.json)，复核脚本 `tools/inspect_version_headers.py`（默认且仅只读，JSON 输出到 stdout）。

### VH-01：SETUP 与 `/info` 的版本声明不完整一致

| 请求 | 当前手机源码构造 | 24A446 已审路由 |
|---|---|---|
| 初始控制 SETUP | `AirSession.kt:517` 不传协议版本头 | 内部 `stup` 追加 `X-Apple-ProtocolVersion` |
| 初始拒绝后的 `/setup` 回退 | `:521` 同样未传 | 本轮没有把这个回退路径说成苹果行为 |
| 视频流 SETUP | `:659` 不传 | 同一 `stup` 封装有该头 |
| 更新控制 SETUP | `:230–232` 显式传 `1` | `stup` 使用统一 provider |
| GET `/info` | `:528` 显式传 `1` | `info` 使用同一 provider |

`Rtsp.kt:161–162/198–199` 的异步／同步路径只统一加入 CSeq、User-Agent、Content-Type、可选 Session，再合入调用者 extra；并不为上述缺省调用补版本头。`RtspWire.write` 不能凭空得出声明值。

原 `APTransportPackageHTTPGetHTTPMessage@0x24fda58ec` 在 `0x24fda633c–0x24fda6380` 检查 `stup/info`，取 provider 结果，以 `%u` 写 header。本轮将4000字节原函数缓存与提取 Mach-O、原共享缓存逐字节核对。

**分类：`PROVEN-SOURCE` + `PROVEN-STATIC`，高价值待验证。** 这证明发送条件与苹果不同，不证明缺该头必然断开。接收端可能拒绝、默认某个值、保留旧值或不使用；必须追具体消费者，不能把缺头直接写成已知车型故障根因。后来的 `/info` 带1也不能无证据地解释为“会补救此前 SETUP”。

### VH-02：原提供者不是 iOS 大版本，也不是读取车机的版本再照抄

本轮闭合原先未解析的跳板：

`0x2500ee660 → AirPlaySupport _APSSystemGetUserVersion@0x226ed0894`。

在其一次初始化之后，函数读取一个 u32：

- 无符号值小于3时原样返回，即0、1或2；
- 其余值返回1。负值的低32位在这个无符号判断中也进入回退；
- once block `0x226ed0950` 向 reader 传入 `UserVersion`、`com.apple.airplay`、`w2=-1`，把返回的 `w0` 保存到该槽。

这证明 provider 的选择范围与本地输入来源。底层 reader 目标已解到 `0x18ee815a0`，但其实现、所有读取错误和实际用户偏好未审计；不能因原缓存初始值是 `0xffffffff`，就跳过 once 调用断言所有运行都发1。也没有证据要求 Android 模仿该系统偏好接口。

**结论：不能只给全部请求盲补某个“最新版本”。** 应先定义本实现支持的完整协议行为，再一致声明，并核对接收端的相应分支。原函数在该点没有拿 `/info sourceVersion` 作为输入。

## 3. 别把不同版本命名空间合成一个数

| 字段 | 谁提供／方向 | 本轮可以说什么 | 不能说什么 |
|---|---|---|---|
| iAP2 link version | SYN/SYNACK 的链路协商 | 决定链路解析／相关模式，见 iAP2 专项审计 | 不是 iOS 版本，不能与控制 session 版本混为一谈 |
| iAP2 control-session version | session descriptor 里的独立字节 | 会进入认证和启动决策 | 链路接受了某版本不等于上层支持 |
| AccFirmwareVersion / AccHardwareVersion | `1D01` 配件→手机 | 配件身份字符串，见 [12](12-identification-contract.md) | 不是让手机填写 iPhone 构建号的槽 |
| `4301 srcVer/sdkVer` | 车机→手机 | 是启动端点的对端输入，见 [10](10-bluetooth-iap2-network.md) | 不能用手机的本地 sourceVersion 覆盖 |
| 本地 `sourceVersion` / Bonjour `srcvers` / User-Agent | 手机→车机 | 当前共享 `320.17`；三个出口字符串一致 | 不证明已经实现这个版本的完整行为，不能直接改980.77.1.2就称复刻 |
| `osBuildVersion` | 初始 SETUP 手机→车机 | 当前兼容声明 `21A329`，不同于真实 Android Build.ID | 不只是展示文本；不能独立于音频／显示／接收准入判断修改 |
| `X-Apple-ProtocolVersion` | 手机请求头 | 苹果已审 `stup/info` 统一从 provider 获取 | 不等于 RTSP/1.0、Bonjour protovers、对端 sourceVersion 或 iAP2 version |
| `features`、`featuresEx`、SETUP 功能数组 | 必须分别标明消息、方向、类型 | 位掩码、扩展能力对象、功能请求数组不可仅按同名合并 | 空数组不自动意味着“什么都不支持”；没置位、缺字段和未实现也不同 |

## 4. 构建号审计：历史已修与新增条件风险

证据：[build-profile-audit.json](../evidence/build-profile-audit.json)。对象为本地Toyota `libAirPlay.so`，SHA256 `ecc9213489e4705b65ecae3869d6a701392023f1f934a9c325005bf51be62370`；未确认与用户车机同版本。

### BP-01：旧音频声明不一致不能重复报错

原比较函数 `0x17d20` 及main/alt接收点 `0x1af74–0x1af94` 使用严格 `Compare("13A1", build)<0` 选择RTP `[4,12)` 的8字节AAD，否则选 `[0,12)` 的12字节AAD；等于阈值不是现代分支。当前声明21A329与输出 `MediaAudioPackets.kt:26/67` 的8字节方式一致。分类为 `HISTORICAL-REPAIRED`（仅这项局部不一致），不证明完整24A446复刻或全部音频链路正确。

### BP-02：同一个字段还参与是否允许SETUP

`AirPlayReceiverSessionSetup@0x17de8` 在 `0x182b0` 调 `AirPlayGetMinimumClientOSBuildVersion@0xd01c`。提供者先查server配置字典的 `clientOSBuildVersionMin`，失败再走同步属性回调；本轮已定位到server property入口，但平台最终值未闭合。

- 取得最低构建号失败：`0x182b8` 跳过比较，不是无条件拒绝。
- 取得成功且 `Compare(minimum,current)>0`：`0x18308` 设内部错误 `-6715`，进入错误回调、teardown并返回。
- 这个内部错误不是已经确定的线上RTSP状态；映射未在本轮追完。

分类 `PROVEN-STATIC` + `RISK-CONDITIONAL`。证明构建号可能影响连接准入，但未取得实际最低值；不能宣布21A329一定太旧，也不能凭空设定所有车的最低版本。目标仍是完整24A446 profile，不是为过门槛随意填更大字符串。

### BP-03：构建号改变显示响应

`AirPlayCopyServerInfo@0xdc0c` 的 `0xdd78` 比较客户端构建号与18A0：低于阈值才进入legacy显示转换，为缺失safeArea的 `displays[].viewAreas[]` 根据宽高／原点补值。21A329跳过。当前 `DisplayCapabilities.kt:24–43` 没有消费viewAreas/safeArea；这是已证实的跨功能影响，不是已复现视频故障。

### BP-04：输入端兼容尝试不等于完整统一profile

当前车麦 `AudioRtpInput.kt:33–44/56–74` 每包优先试chosen组合，失败仍试其他AAD／布局／可用key组合，包含空AAD；仅认证成功才发布。命中可改变chosen且仅首次日志，不是固定后永不切换。此为本地兼容策略，尚未证明等价于24A446；不能据车麦可解密推断输出声明全部正确。本轮不改此策略。

同库的 `/info` handler确实解析 `X-Apple-ProtocolVersion`，但本轮没有闭合缺失／不同值导致拒绝的分支。因此VH-01仍是构造差异，不升级为现场根因。

## 5. 最小验证方案（本轮尚未执行）

1. **版本头构造**：对当前真实请求构造器截获初始／更新／视频 SETUP 与 `/info` 的序列化结果，检查字段存在和值。不能只断言手写字典。
2. **接收端条件**：追已有只读接收库对缺头、0、1、2、畸形值的消费，区分请求级与会话级状态；没有证据时保持 OPEN。
3. **iAP2 支持集合**：协商选择、线上回发、提交状态、上层支持集合必须一致；未知版本不能先被宣布支持再在下一层无上下文拒绝。
4. **来源与能力保留**：将4301、Bonjour、`/info`各自的版本／能力保留来源标签，证明真实 selector 使用的是哪份，而非用一条“以能力为准”日志代替。
5. **构建号 profile**：保持当前已工作的音频行为，先列出声明构建号的接收者和条件；只有完整 profile 一致后，才讨论是否改变声明。不能用逐个试大数字替代实现。

后续设备测试只需针对最有解释力的条件取样。现有一般连接／首帧／重连测试仍见 [50](50-test-matrix.md)，其 `NOT_RUN` 状态不因本轮静态审计改变。

## 6. 本批边界

本轮不会声称已经解释奥迪或所有车机失败，也不声称 iAP2 版本导致了此前音频卡顿。正确的归因链是：同一次连接的实际输入→分支条件→当前执行行为→对端结果。源码明确差异可以先列出来；现场根因必须再补这一条链。
