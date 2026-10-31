# type-130：24A446 与 Toyota 固件核对

日期：2026-10-31

结论：CarVeX 不应在每次 RECORD 后无条件发送 type-130。24A446 只有在
AirPlay SETUP 响应的 `enabledFeatures` 包含精确字符串 `iAPChannel` 时才创建
RCS；当前 Toyota `libAirPlay.so` 不提供该能力，并且把 type-130 归入不支持的
stream type。

## 1. 24A446 发送端

- `carEndpoint_Activate_block_invoke_2 @0x251ae2228`
  - 从 SETUP 响应读取能力数组。
  - 查找 `iAPChannel`；命中时才设置 endpoint 的 iAP raw 标志。
- `carEndpoint_createiAPChannelIfNeeded @0x251ae844c`
  - 该标志未设置时直接返回，不创建 RCS。
  - 设置后才调用 `carEndpoint_createCommChannelInternal`。
- `carEndpoint_createCommChannelInternal @0x251aec73c`
  - 请求 `wantsDedicatedSocket`。
  - 调用 `APEndpointRemoteControlSessionCreate(..., controlType=2)`。
- `APEndpointRemoteControlSessionCreate @0x251a7d448`
  - `clientUUID` 使用 CFUUID 风格字符串。
  - `channelID` 是 CFString；缺失时按 `0x2761321f0` 的 `%@-RCS-%d`
    生成，格式参数是调用方传入的 endpoint identity。
  - 当前 CarVeX 使用 SETUP 的 `phoneMac`；该值是否逐值等于 24A446 的
    endpoint identity 仍为 `OPEN`。
- `apEndpointRemoteControlSession_ensureAndCopyTransportStreams @0x251a7d9d0`
  - 发送 type `0x82`（130）SETUP。
  - 取得 `streamID` 和 `NetworkPortData`。
  - `dataPort` 非零走 dedicated socket；缺失或零走 shared/event 路径。

### 创建时机

- `carEndpoint_Activate_block_invoke_2 @0x251ae2228`
  - 初始 SETUP 响应完成后读取 `enabledFeatures`。
  - 命中 `iAPChannel` 时在 `0x251ae2ef0` 写 endpoint 的 `+0x90` 标志。
  - 随后才把 activation block 129 投递到 endpoint 队列。
- `___carEndpoint_activateInternal_block_invoke_129 @0x251ae7fc4`
  - `0x251ae81b0` 调用 `carEndpoint_setUpAPAccClientEndpointForIdType`。
- `carEndpoint_setUpAPAccClientEndpointForIdType @0x251ae844c`
  - `0x251ae84a8` 读取 `+0x90`。
  - 标志置位时调用 `carEndpoint_createCommChannelInternal @0x251aec73c`
    创建 RCS；`0x251a7d448` 创建 RCS 时即调用
    `apEndpointRemoteControlSession_ensureAndCopyTransportStreams` 发出 type-130
    SETUP。
- 因此 RCS 属于 endpoint activation 阶段，在初始 SETUP/INFO 后建立，不依赖
  媒体 SETUP 或 RECORD。CarVeX 原先放在视频 RECORD 后，并且无屏路径提前返回，
  两处都与该时序不一致。
- `+0x90` 的直接置位只在上面的初始 SETUP 响应解析中发现；没有证据表明后续
  feature update 会重新开启 type-130。因此 CarVeX 只读取初始
  `enabledFeatures` 是当前固件下的正确边界。

### 发送模式与包头

- `carEndpoint_createCommChannelInternal @0x251aec73c` 配置
  `sendMessageAsIs=true`；实际 iAP 内容因此按原始 Data 发送，不经过 plist 封装。
- `apEndpointRemoteControlSession_sendMessageInternal @0x251a7f870` 在该模式下
  选择 Data/no-reply 分支；没有回调或 reply-output 消费者。
- `_stream_copyFormattedAsyncPackageForBBuf @0x24fda7bbc` 对 no-reply 路径固定写入
  package type `asyn`。
- `_tcppackage_CreateBBufRepresentation @0x24fddf6c8` 证明 32 字节头布局为：
  `total, packageType, group, messageType, replyToken, status, payload`。
- 当前 CarVeX 写 `group=0`、`replyToken=0`。原始 no-reply Data 路径没有显式
  reply-output，`asyn` 可以确认；但 parcel 构造默认值及 group/token 的协商来源
  尚未闭合，因此这两个值仍为 `OPEN`，不能作为固件对齐结论。

## 2. Toyota 接收端

目标：`vendor/carplay/libs/libAirPlay.so`

- `AirPlayReceiverSessionSetup @0x117de8`
  - 读取 SETUP 请求的 `streams` 数组。
  - 读取每项 `type`。
  - 只处理 `type - 100 < 0xc`，即 100..111 的媒体流。
  - 其他类型进入 `### Unsupported stream type: %d`，不会向响应追加该 stream。
  - 因此 type-130 SETUP 可以返回 HTTP 200，但响应没有 `streams`。

Toyota 二进制中没有找到 `iAPChannel` 能力字符串；这与上面的 receiver
stream switch 相吻合。该负结论只针对当前提取的 Toyota `libAirPlay.so`，
不外推到其它车型或版本。

## 3. 现场日志对应

```text
SETUP cseq=11 status=200
iAP tunnel SETUP response keys=
type130 response missing streams
```

随后 runtime iAP2 通过 `iAPSendMessage` event 通道完成识别、认证和
`CONTROL_READY`。同一会话中视频、音频、麦克风、HID、5001 和反馈心跳持续
正常，没有 `DEGRADED` 或 `NO_SYN`。

## 4. 生产修改

- `IapTunnelSetupRequest.enabledBy(enabledFeatures)`：
  - 只接受精确字符串 `iAPChannel`。
  - 缺失、空数组或大小写不同的字符串均不启用 type-130。
- `AirSession.setupRuntimeTunnel`：
  - 在发送 type-130 前检查初始 SETUP 的 `enabledFeatures`。
  - 不满足时记录 `peer did not enable iAPChannel` 并继续 event 通道。
  - 在初始 SETUP、/info 和 event 通道准备后启动；有屏与无屏路径都会执行。
  - 启动后再进入屏幕 SETUP 与媒体 RECORD。
- `IapTunnelSetupRequest.build`：
  - `channelID` 使用固件同类字符串 `<deviceID>-RCS-1`。
  - `clientUUID` 使用 uppercase UUID。

### 验证

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
```

- `protocol-carplay`：1029 项，127 套，0 失败、0 错误。
- `core`：81 项，13 套，0 失败、0 错误。
- `:app:compileXiaomiDebugKotlin`：成功。
- 本次未打包、未安装、未实车验证。

## 5. 保留的 OPEN

- 当前 Toyota 版本是否在任何其它 SETUP/feature 条件下支持 type-130：未发现证据。
- 响应是空 body 还是空 plist：当前都表示没有返回 stream；生产回退语义相同。
- 具有 `iAPChannel` 的其它车机是否接受当前 dedicated rmcl 数据层：仍需对应固件和实车验证。
- RCS activation block 与媒体 stream start 各自运行在多个队列上；已经确认 RCS
  创建不等待媒体 RECORD，但两个队列的精确微秒级先后仍不用于生产判断。
- type-130 的 `group=0` 与 `replyToken=0` 默认来源仍 `OPEN`；当前只确认
  no-reply 路径使用 `asyn`。
- APAcc forwarded Data 是否在 Apple 内部建立一条全新的 iAP2 Link，还是复用
  已有 CoreAccessories link，当前切片不足，保持 `OPEN`。

## 6. 复现

- `FindType130Refs.java`：只读 Ghidra 脚本，导出 Toyota 符号、取流分支和反编译。
- `type130-refs.txt`：本次 Ghidra 输出。
- 24A446 原始函数切片位于
  `firmware/analysis/decompiler-cache/24A446/AirPlaySender/934ec850a9ab7623f1d8/functions/`。
