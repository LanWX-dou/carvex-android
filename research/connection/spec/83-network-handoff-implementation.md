# 83 — 手机端异步网络交接实现


## 1. 已实施的变化

此前“拿到网络配置仍等待4301”“先发现车机服务才发布手机服务”“Bootstrap后丢弃迟到4301”三处结构缺口，已接到实际生产入口，不是只新增未调用的回调。

```text
当前链路认证 + Identification成功
  → 可用5703，或同一4301内完整的网络参数
  → Bootstrap返回（不要求此时已有车机端点）
  → 接受本轮认证/身份快照；启动唯一后续iAP消费者
  → 加入/复用选定Wi-Fi
  → 启动手机ctrl监听与发布
  → 当前完整4301，或并行等待迟到4301 / Bonjour端点
  → 原子提交端点；同一publication交给AirSession
  → 后续安全路线、控制会话与视频流程
```

邀请是独立的候选事件，不生成车机端口，不构成认证成功。网络未就绪前不发布到任意默认网络。

| 实际入口/文件 | 实施内容 |
|---|---|
| `SessionController` → `CarPlayRunner.negotiate` → `Bootstrap` | 传入本轮 `IapNetworkHandoff`；可用配置立即交接。生产路径不再耗尽旧30秒窗口才联网；未传协调器的旧接口保留原行为 |
| `IapNetworkHandoff` | 初次和后续5703/4301归属于当前generation/epoch及有效Identification；后续消息还须已声明。冲突不改绑网络，关闭后不复活 |
| `NetworkHandoffPipeline` / `CarPlayRunner.prepareNetwork` | join成功后先启动publish，再选端点；Bonjour失败/自身超时不取消已声明的迟到4301路线；安全错误不走退路；父协程取消保持取消语义 |
| `CarPlayControlPublication` | 从AirSession拆出监听/NSD资源；选定Network就绪即启动，AirSession复用同一实例和端口，不切换第二套监听器 |
| `ControlInvitationPolicy` | 精确方法/路径、空body、十进制无符号64位ID；已有候选时精确地址匹配，否则仅接受本地选定接口前缀内的非自身候选。ID仅保留为候选数据 |
| `AirSession.prepare` | 缓存Bonjour元数据不再额外强制等邀请；直接4301仍可在元数据发现失败后继续，不把邀请设为统一前置；公钥冲突不被发现退路吞掉 |
| `Bootstrap.network` | 同SSID仍只复用本轮已授权配置下的网络lease；增加复用网络丢失监控与注册后地址复查；完成/取消/关闭用单次完成保护 |
| `CallbackRegistration` / `ReceiverDiscovery` | 注册前拥有清理责任，串行化注册/关闭；发现任务胜负确定后清理，迟到NSD回调不复活旧结果 |


## 2. 明确保留的边界

1. **不是完整24A446复刻。** 本批借鉴已证的独立输入/异步交接，修正本地依赖顺序；没有新增固件全分支审阅，也没有重建全部Apple平台服务。
2. 空/部分消息仍可保持等待，但必须在**同一消息**中取得可用网络参数。本批不把缺字段4301与旧会话/5703任意拼接，不根据旧SSID自动授权，不猜网关或7000端口。
3. 5703、4301的security枚举映射仍OPEN。本地沿用Android既有0/open、2/3/WPA2、4/WPA3配置；同SSID/口令下2与3可作为同一Android联网方式补入端点，保留先选定的security，不据此断言Apple两套枚举等价。其他冲突要求新attempt。
4. 迟到4301只在端点提交前更新候选。提交后不热切换控制socket，不自行启动重连。完整首次/重连身份融合、availability变化生产者和5700授权provider仍OPEN。
5. 未知端点的邀请按选定接口地址前缀约束，是**本地有界策略**，不是Apple完整身份绑定。严格纯十进制ID检查也不等于C `%llu` 全部输入语义。HTTP200不代表认证、网络或视频成功。
6. 25秒端点预算、15秒Bonjour预算及现有Android网络预算是本地政策，不称为苹果原生时间。完整4301不强等邀请，但仍可能等现有元数据发现预算。
7. API33+使用Network范围的NSD；更老系统的无端点发现限制未解除。公共Android API的发布行为、同SSID实际网络归属、失网/权限/VPN等仍须设备验证。
8. 没有修改版本声明、音频/视频编码或认证信任来源。实验性签名一致性不升级为Apple信任链认证。

## 3. 本批验证

已实际执行：

```text
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests '*NetworkHandoffTest' --tests '*ControlInvitationPolicyTest' --tests '*CallbackRegistrationTest' --tests '*BootstrapNegotiationTest' --console=plain
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
```

- 定向首次109项中3项失败：新测试调用 `IapLink.poll(2000)`，违反该接口最多500ms的约束。改为有界循环轮询后109项全通过；没有修改生产poll限制来迁就测试。
- 随后增加Identification失效保护测试；最终协议模块 **970项 / 122套**，核心模块 **79项 / 12套**，共 **1049项**，failure/error/skipped均为0。本批新增42项；core任务复用未变化的Gradle结果，协议测试实际重跑。
- 小米端Kotlin编译成功，`git diff --check`通过；既有编译警告和弃用提示不等于零警告构建。未执行APK/AAB打包或安装。
- 最终四个定向测试类在完整结果中合计110项，其中实际内存iAP链路测试覆盖双声明5703先到、4301先到、同消息部分端点配置、已排队4301、早到/未声明/格式错误输入的准入与纠正。
- 生产使用的纯编排类测试覆盖先发布后发现、发现依赖发布、联网中迟到、取消败方发现、发现自身超时、父级取消、安全失败、关闭/epoch变化、冲突、提交后冻结；邀请策略及注册/关闭竞态另有单测。

**验证限制：**实际Android `NsdManager`、Wi-Fi回调和 `SessionController` 整体没有在JVM测试中运行。测试使用真实Bootstrap/IapLink和生产编排类，但平台操作由假实现注入；不是端到端Android测试，更不是实车通过。失网监控已接线，不代表已观察到每个系统回调次序。

只读复核当前快照及XML：

```text
powershell -NoProfile -File D:\carvex-research\research\connection\tools\verify_network_handoff_implementation.ps1 -CheckTests
```

它检查文件哈希、测试结果完整性及数量，不运行Apple代码或Android联网，也不证明协议语义正确。

## 4. 历史证据与下一步

82的原固件函数证据和修改前源码哈希保留不变。本批实现后，其旧源码验证不应再期望与当前手机工作树一致；不能覆盖旧哈希来掩盖变化。原生依据沿用82所列有界结论，本批不把旧20函数复核冒充新一次固件执行。

下一步先用用户自行构建的版本做连接验证：普通连接一次，主动断开再连一次，保留目标Wi-Fi后再连一次。每次关注同一attempt内“网络配置就绪→Wi-Fi ready→ctrl发布→4301/Bonjour选中端点→控制/首帧”的先后；日志不应包含口令。失败时先按停点定位，不追加车型开关。

G5/G7仍为PARTIAL，G6和实际首帧/重连验收不因离线测试自动关闭。若本批顺序问题已排除，再针对4300 availability与网络/车辆身份融合的具体未闭合分支继续核对24A446。
