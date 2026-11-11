# GalaxyPlay 接收端：音乐、仪表导航与通话链路核查

日期：2026-11-11。输入为用户提供的 `D:/home/GalaxyPlay.apk`，包名 `com.shilapi.galaxyplay`，版本 `0.1.212` / versionCode `240`，23,629,025 bytes，SHA256：

```text
f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6
```

包身份由 Android SDK `aapt dump badging` 读取；APK 含 18 个 DEX。本文使用 SDK dexdump 的原指令、控制流和方法调用，关键 code_item 的方法归属及指令哈希另行从 DEX 表直接验证。APK 与完整供应商反汇编不入库。

最新修复状态：用户已确认音乐链路正常，本轮保留其行为。仪表导航数值核心已启用，接通基础转向、机动距离和结束 reset；通话信息及双向音频仍有缺口，后续独立处理。静态审计与下述原断点不代表修复后的实车显示已通过。没有运行、安装或修改车机 APK。

## 检查结论

| 链路 | 当前结果 | 确定依据 / 待验收边界 |
|---|---|---|
| 音乐文字、时长、进度、播放状态 | 静态合同匹配；整体 PARTIAL | `5000` 订阅和 `5001` 嵌套字段相符；宿主真实播放状态仍依赖播放器访问和输入 |
| 音乐音频及封面 | 静态存在双方路径；运行 OPEN | 需核实际 `audioFormats`、SETUP、音频包、文件传输及接收端输出，不以类存在或 ACK 代替播放 |
| 仪表导航路线与箭头 | 数值核心已修复，实车 OPEN | 原断点为生产阻断/缺定义；现已启用 `5202` 定义、`5201` 状态/引用/距离及结束 reset |
| 导航车道 | OPEN | 本次核查的导航/仪表入口只分派 `5201/5202`；目录有 `5204` 定义不能证明仪表使用它 |
| 通话姓名、状态、卡片 | 当前未接通 | 接收端解析 `4155`；CarVeX runtime 无通话元数据 provider，也无生产 `callStateUpdate` 调用 |
| 通话音频 | 双向链路不完整；麦克风回传待验收 | `100/telephony` 上行请求与接收入口局部匹配；蜂窝下行 PCM 来源/路由没有接通 |

这里的 CONFIRMED 表示本版接收端原 DEX 或当前发送代码的局部事实；它不将第三方行为提升为 Apple 协议。INFERRED 表示由这些分支得到的互通影响；实车结果及未读分支保持 OPEN。

## 实际业务分派

CONFIRMED：`classes5.dex` 的 `CarPlayController.onRouteFrame` code_item `0x04b370` 调用 `CarPlayNavigationInput.accept`（`0x04b384`），随后调用 `BydNavigationOutputs.onFrame$shared`（`0x04b3a4`），再调用 `CarPlayPlaybackStatus.acceptUpdate`（`0x04b3ce`）。变化后再通知 nowPlaying/playback listener。它证明解析器位于业务链内，不能只从消息目录推断支持。

`classes2.dex` `BydNavigationOutputs.onFrame$shared` code_item `0x01a184`：

- `5001` 分派到 `BydClusterSong.onFrame`；
- `4155` 分派到 `BydCarPlayCall.onFrame`；
- `5201/5202` 分派到 overlay、standalone 或 HUD/cluster worker；
- `outputsEnabled=false` 时直接返回。没有在此分派 `5204`。

这些车机端设置和厂商输出路径仅用于解释接收行为，不应在手机协议层添加按车型的分支。

## 音乐字段与输出

CONFIRMED：`classes11.dex` `Iap2ControlMessages.subscriptions` code_item `0x002774` 构造 `5000` 的两组订阅。组 0 的 lambda `0x002930` 请求 `1/4/6/12/26`；组 1 的 lambda `0x0029ec` 请求 `0/1/7`。这是已审构造器的请求值，不能冒充当前实车会话已经发送并接受的订阅。

`classes6.dex` `CarPlayPlaybackStatus.acceptUpdate` code_item `0x01f8d8` 与当前 `NowPlayingUpdate.fields` 对照：

| `5001` 路径 | 接收方法 | 当前发送字段 |
|---|---|---|
| 组 0 / p1 | String | title |
| 组 0 / p4 | U32 | durationMs |
| 组 0 / p6 | String | album |
| 组 0 / p12 | String | artist |
| 组 0 / p26 | U8 | artwork transfer ID，由独立 artwork publisher 发布 |
| 组 1 / p0 | U8 | playback status |
| 组 1 / p1 | U32 | elapsedMs |
| 组 1 / p7 | String | appName |

解析器保留缺失字段的旧值，发生变化才生成新模型。`updatedStatus` code_item `0x01f83c` 只有状态值 1 被视为普通播放；`ClusterSongState.accept` code_item `0x02584c` 还将 3/4 视为播放。两者对于快进/快退的展示不同，属于接收端行为。

`BydClusterSong.onFrame` code_item `0x014564` 要求有效 context、内容变化以及 `BydOutputSettings.clusterSong(context)`；`clusterSongOnChange` 决定换曲提示或持续显示方式。设置关闭时，正确的 `5001` 也不能证明仪表会显示。

封面链独立于文字：`CarPlayController.artworkTransferHandler$lambda$62` code_item `0x046990` 在当前 diagnosticRun 且 controller 未关闭时，将 transfer ID 和 bytes 交给 artwork listener；模型同时持有组 0 / p26 的 U8 ID。CarVeX 已有独立文件传输实现；本次未复跑完整接收端传输及图片关联，封面最终展示 OPEN。

音频方面，`classes5.dex` `CarPlayMediaEngine.onAudio` code_item `0x02e9cc` 从 SETUP 流读取 `audioType/audioFormat`，交给 `AudioStreamCodec.fromFormatBits`（`0x027cec`）。所审选择器有 AAC-LC、OPUS 和 PCM 分支；未识别位会进入 PCM 回退，不应解释为支持 AAC-ELD。当前手机按实际 receiver capabilities 选格式；是否选到双方支持且本机可编解码的格式，需要当前会话的 info/SETUP 和音频日志。

## 仪表导航原断点与修复

CONFIRMED：`CarPlayNavigationInput.accept` code_item `0x023cb4` 只接收 `5201/5202`。路线解析 `updateRoute` code_item `0x0249f0`：

- p1 通过 width=1 读取状态；本版遇到数值 0 或 2 跳到 `reset`。Apple 原状态表另已闭合 0=NotActive、2=Arrived；本版消费效果由此 DEX 分支验证。
- `0x024b00..0x024b18`：如果此前 inactive、本消息缺 p1、也缺 p13，直接返回，不处理道路/距离。
- p13 非空时以 U16 读取第一机动索引，可读取第二个不同索引，设置 active；机动切换时清 segment 缓存。
- p3 更新 road；p10 的 U32 更新 segment；p7 的 U32 更新 remainingMeters；p6/p5 通过 width=8 读取剩余时间/到达值。字段名和宽度是接收端事实，不据此补 Apple 单位。

`updateManeuver` code_item `0x024858` 需要 p1 U16 索引；以 p3 U8 类型、p8 U8 side、p4 文本合并机动定义。`snapshot` code_item `0x024070` 从 map 按路线的 index/secondIndex 查机动；仅发送道路和距离没有对应机动，不能组成完整箭头。

`snapshot` 还在更新超过原常量 `0x6fc23ac00` 纳秒时 reset，并对空机动列表使用 `0xb2d05e00` 纳秒的观察窗口，分别为本版 30 秒与 3 秒的局部行为。这不是发送端定时重发依据。

INFERRED：旧 HUD→`currentRoad/distanceRemaining` 发送代码即使记录 `5201` 已写，也不足以激活此接收端的仪表导航。初始重构删除了这两项未证映射并阻断 wire 编码。本次已追宿主原图标分类器、Apple 原状态/类型表及组件容量，启用基础数值核心；已发状态与机动定义/引用不等于仪表已实际显示。

已审订阅构造器另外构造 `5200` p0 U16=`42`、p1/p2 空标记（`0x002806..0x002818`）。不能硬编码组件 42 到手机；实际组件和显示能力必须从当前 Link 的 Identification/START 读取。Apple 状态/基础机动枚举已闭合；未证文本/通用时序仍按 [导航实施边界](../../../android/docs/fixes/2026-11-11-navigation-cluster-chain.md) 继续取证。

## 通话元数据与双向音频

CONFIRMED：订阅构造器请求 `4154` 的 `0/1/2/3/4/11`。`CarPlayCallState.accept` code_item `0x021b70` 要求 `4155` 且 p2 状态存在；读取 p0 remoteId、p1 displayName、p4 UUID 后维护 calls map。`BydCarPlayCall.onFrame` code_item `0x011e3c` 在解析变化、有 context 且 `carPlayCalls(context)` 启用后，将卡片交给 writer。

发送端目前有 `PhoneSubscriptions` 的订阅记录和纯编码辅助函数，但 `AirSession` runtime 对通话消息明确记录 `no-runtime-call-metadata-provider`；全源码调用检查没有生产 `callStateUpdate` 调用。因此接收端卡片不能从当前 CarVeX 得到完整姓名/接听/保持/挂断状态。bootstrap 接受过订阅不能代替 runtime 上报。

现存辅助编码器还使用 `legacyStatus` 转换，例如输入 4 输出 1；接收端本版的局部定义将 1 作为 SENDING、4 作为 ACTIVE。辅助函数输入枚举与实际电话 provider 的含义仍需独立闭合，不能把 Android/宿主整数直接套入它。本次没有启用或按接收端定义修改 Apple 通话编码。

麦克风是另一条链路，局部请求相符：

- 手机 `createCallMicrophone` 使用 `type=100/audioType=telephony`、协商 format、streamConnectionID 和本地 dataPort，解密回传后交给 `HostAudioBridge.microphone`。
- 接收端 `CarPlayMediaEngine.microphoneConfig` code_item `0x02e608` 要求 microphoneEnabled、type=100、telephony 或 speechrecognition、合法目标 dataPort、remote address 及输入 key。
- `dataStreamKey` code_item `0x02e464` 使用 sharedSecret、`DataStream-Salt` 加 streamConnectionID 的十进制文本，以及输入 encryption key label 派生密钥；这一局部输入与手机请求相符。
- `AndroidMediaSink.onMicrophoneStarted` code_item `0x01228c` 创建并启动 `MicrophoneUplink`；`start` code_item `0x026c40` 为 telephony 选择音源 7，检查 AudioRecord buffer/启动；`capture` code_item `0x027a24` 读取 AudioRecord 并编码/发包。运行权限、真实路由、非零语音和手机宿主消费均未验收。

蜂窝下行没有形成闭合路径：`CarPlayAudioPlan.telephony` 明确为 input-only、category=0，未指定宿主下行 PCM 来源。`SessionController` 通话期间停止 category=3 的 speechRecognition 请求，并抑制部分媒体请求；它没有建立独立 telephony 下行流。不能拿语音助手音频或音乐类目代替蜂窝下行。对方声音可能走系统其他路由，但那需要设备运行证据，不能认定为此 CarPlay 双向链路已实现。

## 复核入口与验收

[证据 JSON](../evidence/galaxyplay-0.1.212-receiver.json) 记录 5 个 DEX 的 28 个 code_item、方法签名/归属、指令哈希和 12 份当前发送源码哈希。只读复核：

```powershell
python -X utf8 -B research/connection/tools/inspect_galaxyplay_receiver.py D:/home/GalaxyPlay.apk --check-android
```

脚本 PASS 只表示所审原字节和代码快照一致，不执行供应商代码，不证明显示/音频或 Apple 等价。导航重构的本地测试及五个 flavor 编译另见 [检查记录](../../../openspec/changes/replan-carplay-navigation-cluster/validation.md)。

后续按匹配提交/构建保留双方从连接开始的完整日志，分别记录：实际 Identification/`5000/5200/4154`，`5001` 内容和播放器状态，音频 SETUP/双方包计数，封面 ID/文件完成，接收端输出设置及仪表显示。通话需分别确认接听/挂断卡片、对方下行声音、车机麦克风上行、权限/宿主消费、挂断后的音乐恢复。导航在来源与 Apple 字段合同闭合并启用生产编码后，再验收机动索引/定义、距离、终态和 STOP→START/重连。当前未接通项不能以一次 ACK 或静态解析通过关闭。

## 本次导航提交的证据补充

实际 Identification 构造器 classes3 code_item 0x01e3fc，以及导航 lambda 0x01e914 已复核：p30 导航组件内 p0=42、p2/p4=64、p6=8。手机从实际 Link 字段与 START 读取这些值，不硬编码样本。

本次 5202→5201 以及缺值时 reset→定义→引用由接收端 map 合并/清除路径支持；Apple 原枚举和参数表独立核查。宿主 navi_turn 来自模板图标分类器，不能照抄原整数。完整原地址、资源像素核查、指令/图标哈希、字段与通用 Apple 边界见[数值核心核查](navigation-numeric-core-20261111.md)。
