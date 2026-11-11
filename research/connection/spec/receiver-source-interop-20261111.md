# GalaxyPlay 目标与 DiPlay 源码交叉对接

日期：2026-11-11。实际接收端是 **GalaxyPlay 0.1.212 / versionCode 240**。
用户确认音乐正常，手机系统为 Android 17；DiPlay 未在车机上开启。
本轮完成导航容量与接听键两项修复，并通过可选接收源码联测及全量回归。
完整通话元数据、蜂窝双向音频和实际仪表输出尚未验收，不能宣称完全实车兼容。

## 输入与证据范围

| 输入 | 固定身份 | 用途 |
|---|---|---|
| `D:/home/GalaxyPlay.apk` | SHA256 `f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6` | 实际目标的原 DEX 方法、订阅、字段及 HID 按键 |
| `D:/Project/Lanwx/DiPlay` | 干净 Git commit `615b32ce0b40cd0b99ce94ba23a512001553684f` | 原接收 Kotlin 解析器、描述符和声明函数交叉核对 |
| CarVeX Android | 导航 `a922ef3`；通话 `24d768c` | 生产修复独立提交；回归时两项均在 HEAD 中 |
| Apple 24A446 | 既有原镜像、表和汇编切片 | 发送端参数、状态、机动枚举、声明方向的独立依据 |

外部 APK、DiPlay 源码、完整 DEX 反汇编不入库。本轮没有修改、启动或安装接收端。
[来源 JSON](../evidence/receiver-source-interop-20261111.json) 保存 22 个原源码 SHA256、
2 个原截取 body SHA256、GalaxyPlay 7 个 DEX 方法归属及指令哈希。
[全量回归 JSON](../evidence/receiver-interop-tests-20261111.json) 另保存实际使用的 14 个
源文件、2 个 body、测试模板、两份修改生产文件以及 JUnit XML 哈希。

本文的 CONFIRMED 仅指注明来源的局部事实：原接收 APK 输入、源解析器输出、或 Apple
原固件合同。DiPlay 是交叉核对对象，不将其实现提升为 Apple 规范或 GalaxyPlay 实车结果。
完整旧目标审计见 [GalaxyPlay 原 APK 核查](galaxyplay-receiver-audit-20261111.md)。
旧审计的发送代码哈希保留历史快照；本轮使用新增记录绑定已修改文件。

## 对接矩阵

| 链路 | 已核对的接收路径与结果 | 本项目状态 / 验收边界 |
|---|---|---|
| 蓝牙 → iAP2 → Wi-Fi | DiPlay `Iap2WirelessControlClient` 保留 Identification/MFi/订阅/Wi-Fi 控制流程 | 保持本项目当前蓝牙启动路径。无新的握手、认证或网络修改；实际重连仍须日志验收 |
| 运行期 iAP 通道 | DiPlay `AirPlayIapTunnelStream` 入站取隧道字节，出站使用 `sendIapMessage`；`onRouteFrame` 分派业务 | 上轮已修当前 Link 的 START/STOP。原 CSM framer 本轮执行全部碎片长度；不是完整隧道网络联测 |
| 视频与触摸 | DiPlay `AirPlaySession` 分派 110/111；实际 `AirPlayHid` touch descriptor/report 可被本项目解码 | 生产视频不改。测试只验证触摸下/抬及坐标；视频首帧、尺寸/旋转/多屏仍需目标实测 |
| 音乐文字/状态/进度 | 原 `Iap2ControlMessages` 请求 `5000`；`CarPlayPlaybackStatus` 实际消费 `5001` 中文和增量字段 | 用户确认正常；本轮保留音乐行为。联测通过播放/暂停、保留字段和清空文字 |
| 音乐封面 | 原目标按 transfer ID 关联文件；联测验证 p26 的 ID 更新 | 完整传输与实际图片展示不由此 ID 测试证明；保留已有封面实现及用户结果 |
| 音乐/导航音频 | 执行原 `audioFormats` 函数，44.1/48 kHz、通话自身采样率、禁麦及无公共格式均检查本项目选择 | AAC-LC 媒体、替代提示和协商麦克风格式匹配；这是选择合同，声音播放/编码质量与车机设备路由待验收 |
| 仪表导航 | 原 `BydHudRouteState` 消费 `5202` 定义及 `5201` 引用/距离/reset；100 个机动保持缓存 ≤8 | 本轮修复容量上限和单槽混用。八种已证箭头通过；实际车机仪表显示 OPEN |
| 接听/挂断 | GalaxyPlay/DiPlay 原 telephony descriptor 一致；原 selector 1→Hook Switch、3→Drop | 本轮接听映射修复为宿主 CALL；挂断保持 END_CALL；Flash 无等价操作而拒绝 |
| 通话卡片 | 原 `CarPlayCallState` 接收 `4155`；测试显式字段下的拨号、响铃、ACTIVE/HELD 数值和结束 | parser PASS；测试输入不是生产电话 provider。精确状态、姓名/号码、UUID 与多通话来源仍 OPEN |
| 通话麦克风 | 原声明与本项目 `CallMicrophonePlan` 可选择共同输入；原目标存在 `100/telephony` 麦克风入口 | 上行局部路径及关闭清理已在此前接入；非零语音、宿主消费及蜂窝 modem 注入未验收 |
| 蜂窝下行 | 当前 `CarPlayAudioPlan.telephony` 为 input-only；mixing 公共回调无已证独立蜂窝下行来源 | 仍未接通。不能用音乐或助手 PCM 代替对方通话音频 |
| 车道/道路/ETA | 新版 DiPlay `CarPlayGlance.onFrame` 有 `5204` 分派及 lane parser；GalaxyPlay 原已审仪表入口没有该分派 | 手机车道/道路/ETA 来源与 Apple 完整字段合同仍缺，不启用虚构上报；新版支持不能代替原目标支持证明 |

Android 17 由用户提供；目前 `PhoneCallMonitor` 仍仅观察粗粒度电话活动。
`HostCallbacks` 没有已证的逐通话元数据回调，runtime 接受订阅后明确记录
`no-runtime-call-metadata-provider`。OFFHOOK 包含拨号/保持，不按它伪造 ACTIVE 或 UUID。
通话生产来源的既有审计见 [通话订阅记录](call-subscription-chain-20261111.md) 和
[CarWith 宿主来源边界](carwith-4.0.14-host-evidence.md)。

## 独立修复

导航提交 **`a922ef3`**：读取当前订阅组件的 p30/p6 正容量，按最小容量取模复用 U16
机动索引。原实现只把容量当作启用布尔值，索引持续增加；容量 8 时第九个新机动越界。
单槽先 NotActive reset，再定义和引用/距离，防止新定义覆盖当前引用时保留旧距离。
多槽的定义和引用仍是分开报文；中间瞬态、丢包或队列部分提交不能由最终快照测试保证。
未知转向、缺失距离和结束清屏沿用既有行为。

容量字段的 Apple 原地址为 accessoryd `0x1000c5704`；状态和机动枚举沿用
[数值核心原始核查](navigation-numeric-core-20261111.md)。取模是本客户端尊重已协商
上限的实现策略，不宣称是 Apple 原索引分配算法。详见
[导航修复说明](../../../android/docs/fixes/2026-11-11-receiver-navigation-capacity.md)。

通话提交 **`24d768c`**：usage `0x20` 从电话页面 `PHONE=8104` 改为接听 `CALL=8111`；
Drop `0x26` 保持 `END_CALL=8112`；没有已证宿主等价操作的 Flash `0x21` 不再误映射接听。
`requestUI ui:mobilephone:` 仍是打开电话页面。
宿主常量沿用四品牌已核 mixing 表；原 CarWith `voice_key_switch` 的
8104/8111/8112 分支记录见 [宿主原证据 JSON](../evidence/carwith-4.0.14-host.json)。

GalaxyPlay `classes5.dex` 从表解析的方法及 code_item：
`AirPlayHid.<clinit> 0x01cc1c`、`descriptor 0x01c5a4`、
`telephonyHidDevice 0x01cbb0`、`telephonyReport 0x01c7a8`、
`AirPlaySession.sendTelephony 0x025cd4`、`CarPlayController.answerCall 0x0439e8`、
`endCall 0x043cec`。telephony 数组 payload `0x01d0b4` 与 DiPlay 逐字节相同，
原接听/挂断 selector 分别为 1/3。联测另外通过 HID 按下与抬起；详见
[通话按键修复](../../../android/docs/fixes/2026-11-11-receiver-call-keys.md)。

## 实际验证

修复前源联测复现四项失败：导航缓存超过声明容量、单槽箭头/旧距离混用、
Hook Switch 错开电话页、Flash 错接听。导航修复后定向 56 项通过；通话修复后
宿主 24 项通过。最终组合回归 **BUILD SUCCESSFUL，1 分 37 秒**：

| 模块 | JUnit 项数 | failures / errors / skipped |
|---|---:|---|
| protocol-carplay（含 10 源联测） | 1149 | 0 / 0 / 0 |
| host-carlife-mixing（含 2 源联测） | 24 | 0 / 0 / 0 |
| core | 121 | 0 / 0 / 0 |
| bridge | 59 | 0 / 0 / 0 |
| host-api | 3 | 0 / 0 / 0 |
| pcm-core | 6 | 0 / 0 / 0 |
| app xiaomi / oppo / vivo / samsung / honor | 每个 53，共 265 | 全部 0 / 0 / 0 |
| 合计 | **1627** | **0 / 0 / 0** |

五个 flavor 的 Debug Kotlin 编译均通过，小米 Release lint **0 错误、31 警告**。
保留既有 lint、测试、签名及构建规则。荣耀通过编译只说明可构建，不证明宿主可用。
Gradle 本轮执行 120 项 task、缓存 12 项、up-to-date 317 项；XML 检查逐个确认 10+2
源联测存在且无 skip，不把检查器本身当作新一轮执行或实车结果。
两个修改模块的 Debug/Release Kotlin 生产输出也已检查，四份输出均无接收源码或联测类。

## 复现

根仓库只读原输入核验：

```powershell
python -X utf8 -B research/connection/tools/inspect_receiver_source_interop.py `
  D:/Project/Lanwx/DiPlay D:/home/GalaxyPlay.apk
python -X utf8 -B research/connection/tools/inspect_galaxyplay_receiver.py D:/home/GalaxyPlay.apk
```

从 `android/` 运行完整回归（按本机实际配置 JDK/SDK，依赖需已缓存）：

```powershell
$env:ANDROID_HOME='D:\Android\Sdk'
$env:JAVA_HOME='D:\Java\jbr-17.0.9'
python -X utf8 -B tools/receiver-interop/prepare.py D:/Project/Lanwx/DiPlay
.\gradlew.bat :protocol-carplay:testDebugUnitTest :host-carlife-mixing:testDebugUnitTest `
  :core:testDebugUnitTest :bridge:testDebugUnitTest :pcm-core:test :host-api:test `
  :app:testXiaomiDebugUnitTest :app:testOppoDebugUnitTest :app:testVivoDebugUnitTest `
  :app:testSamsungDebugUnitTest :app:testHonorDebugUnitTest `
  :app:compileXiaomiDebugKotlin :app:compileOppoDebugKotlin :app:compileVivoDebugKotlin `
  :app:compileSamsungDebugKotlin :app:compileHonorDebugKotlin :app:lintXiaomiRelease `
  --offline --console=plain --no-configuration-cache `
  -I build/receiver-interop/receiver-tests.init.gradle
python -X utf8 -B tools/receiver-interop/verify_results.py --full
```

供应商源码仅暂存到忽略的 `android/build/receiver-interop/`，临时 init 只加入测试
Kotlin 源目录，默认生产构建无外部源码依赖。工具详见
[联测说明](../../../android/tools/receiver-interop/README.md)。
本轮没有打包或安装新 APK；旧 Release 20028 不包含本轮导航容量与通话键修复。

## GalaxyPlay 实车验收仍待完成

| 场景 | 必须观察的实际结果 |
|---|---|
| 新连接与重连 | 记录当前构建、Android 17 手机/宿主版本、原目标 APK、Identification 和运行期 START；旧订阅与旧队列不串入新会话 |
| 仪表导航 | GalaxyPlay 实际输出开关、八种转向、距离更新、连续超过 8 个机动、重算和停止后清屏；同时观察索引复用中间瞬态 |
| 音乐回归 | 正常播放/暂停/换曲、方控、中文/进度和封面；通话/提示结束后的音乐恢复 |
| 通话控制 | 来电点接听转到手机真实接听；拒接和已接通挂断完成；电话页面操作仍仅打开页面 |
| 通话卡片 | 先取得真实逐通话 provider，再验拨号、响铃、接通/保持、号码/姓名、UUID、多通话和结束清卡 |
| 双向蜂窝音频 | 独立证明对方下行 PCM 来源/路由及车机播放、非零车机麦克风上行及手机宿主/modem 消费、权限和挂断清理 |

验收需保留从连接开始的匹配设备日志及实际输出；不以 ACK、SETUP 200 或本地 parser
PASS 关闭缺少生产来源的通话链路。OpenSpec 的实车项继续未勾选。
