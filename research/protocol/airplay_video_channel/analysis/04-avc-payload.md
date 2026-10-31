# 04 视频载荷（AVC）

> 本文件回答第 2、6、7、8 项覆盖要求中"载荷是什么、谁编码、协商什么"的部分。
> AirPlaySender消费已编码CMSampleBuffer；NAL重排、参数集和具体字节封装仍未完全追清。抽样未发现不能证明整个二进制不存在，以下区分调用/原字节证据与名字线索。

## 04.1 编码封装对象

`APEndpointStreamScreenAVCWrapper`（类，`initWithClientPID:hdrMode:presentationMode:hdrMirroringSupported:eventHandlers:error:` @ `0x251a76260`）负责：

| 方法 | 地址 | 已证作用 |
|---|---|---|
| `initScreeenCaptureWithScreenOptions:` | `0x251a7671c` | 按屏幕选项初始化采集 |
| `setCaptureSourceIDForStreamConfig:` | `0x251a76954` | 把采集源 ID 写进流配置 |
| `createVideoStreamConfig:withDirection:screenOptions:previousConfig:` | `0x251a773c4` | 生成视频流配置（方向、选项、上一版配置） |
| `getVideoResolutionFromOptions:width:height:` | `0x251a77178` | 从选项解析宽高 |
| `initializeNegotiatorWithMode:presentationMode:hdrMirroringSupported:` | `0x251a76374` | 初始化 AVC 协商器 |
| `negotiationDataForPresentationMode:` | `0x251a779d8` | 取某呈现模式的协商数据 |
| `isConfigPresentForPresentationMode:` | `0x251a779f0` | 该模式是否已有配置 |
| `restartWithScreenOptions:negotiatedBlob:` | `0x251a77208` | 用新 blob 重启 |
| `startWithNWConnectionClientID:negotiatedBlob:screenOptions:completion:` | `0x251a76ae4` | 启动（带连接 ID 与 blob） |
| `convertHDRMode:` | `0x251a77118` | HDR 模式转换 |
| `screenCapture:didStart:withError:` / `didStop` / `screenDidClear:` | `0x251a77d00` / `0x251a77c60` / `0x251a77da0` | 采集回调 |
| `serverDidDisconnect:` | `0x251a77e9c` | 对端断开 |
| `handleFailureWithError:reason:` | `0x251a77a10` | 失败处理 |

## 04.2 载荷是"已编码帧"

`_screenstream_dequeueAndProcessSampleBuffer` 的入参是 `CMSampleBufferRef`（同函数内的构造器字符串 `sbpd_createFrameBBuf(SBufProcessingData *, CMSampleBufferRef, CMBlockBufferRef *)`、`sbpd_createStatsBBuf(..., CMSampleBufferRef, ...)`）。
头+0并不只是sample数据长度，还计入额外长度和可选尾段（06.4）；不能仅凭此调用形状排除NAL处理。

**因此**：

- 本记录包装器尚未闭合FU-A/STAP-A或Annex-B转换；UDP变体须另行追踪；
- 但**不能**据此推断"没有参数集通路"：同一字符串簇里有 `avcC`（`0x251c67871`），`sbpd_updateCodecConfig`（`0x251c67876`）与 `sbpd_createFrameHeaderBBuf`（`0x251c67aa6`）等构造器名也在其中；`sbpd_updateKeyFrameStatus` 的名字串（`0x251c67974`）在帧函数内被当作日志/断言文本引用（`0x2519b0ae0` + `bl #0x258101eb0`），这只证明名字出现，**不证明调用关系**；[跨镜像] 接收端 `AirPlayReceiver` 另有 `sbufsink_UpdateH264VideoConfig` / `fwsink_updateH264VideoConfig` 与 `avcC`（`0x25191e192`）、`HEVC`（`0x25191ade9`）。
- 新补证：avc1且storage+3c8==0分支从格式描述扩展取avcC CFData，缓存变化触发type1配置记录，并在本地组装于帧记录前。见[analysis07](07-codec-config-and-flags.md)。NAL长度表示、参数集内容/帧内重复与其它profile仍待核，OPEN-VID-3/6缩小而非整体关闭。

## 04.3 协商：AVCMediaStreamNegotiator

字符串证据：

| 字符串 | 地址 | 含义 |
|---|---|---|
| `AVCMediaStreamNegotiator` | `0x251c0480e` | 协商器类名 |
| `AVCMediaStreamNegotiatorHDRMode` | `0x251c047ce` | 取 HDR 模式的类方法名 |
| `NSString *getAVCMediaStreamNegotiatorHDRMode(void)` | `0x251c0477f` | 同上（签名串） |
| `negotiationData` | `0x251c040b0` | 协商结果键 |

流程（据调用形状，`INFERRED`）：

```text
initializeNegotiatorWithMode:presentationMode:hdrMirroringSupported:
    → 生成/选择协商器
negotiationDataForPresentationMode:            → 取出 blob
startWithNWConnectionClientID:negotiatedBlob:  → 带 blob 启动编码
```

**未闭合**：blob 的二进制格式、是否即 SDP、空 blob 是否允许（`OPEN-VID-8`）。

## 04.4 呈现模式与 HDR

- `presentationMode` 是**一等参数**：同一显示可以有多个呈现配置（`isConfigPresentForPresentationMode:`）；
- `hdrMirroringSupported` 决定是否走 HDR 协商（`convertHDRMode:`）；
- restart接口提供带新blob重启的入口；所有模式变化是否必走该入口需核调用者，不能只从名字定规则。

**实现建议**：模式变化后重新确认参数集和协商结果是否仍有效；触发重协商/重发的确切条件尚待核。

## 04.5 编码参数

`createVideoStreamConfig:withDirection:screenOptions:previousConfig:`（`0x251a773c4`）对配置对象做多次 setter 调用，反编译可见若干数值（位率类、帧率类、GOP 类）与一个"方向"参数；**本轮没有在汇编中定位到这些数值的立即数**（它们经 `CFNumber`/常量对象传入），因此：

| 参数 | 状态 |
|---|---|
| 位率 | 存在配置调用，具体值未取证（`OPEN-VID-12`） |
| 帧率 | 同上；另有 `MaxFPS` 来自显示描述（`01.3`） |
| GOP/关键帧间隔 | 同上 |
| 方向 | 函数签名有 `withDirection:`，取值未读 |

## 04.6 关键帧

- 编码侧：`sbpd_updateKeyFrameStatus(SBufProcessingData *, CMSampleBufferRef)`（字符串`0x251c67974`）仅作为待追踪的状态处理线索，不由名字证明调用及副作用；
- 记录头：+05 bit7由APInterestingFrame附件==kCFBooleanTrue写storage+45c后生成；不是已证关键帧位。
- +05 bit4由NotSync附件循环读取后的输出byte==0派生；无/空附件数组时置位，不能据此推定NAL为IDR；
- 车机侧：`forceKeyFrame` 命令（见 `05.4`）。

两个byte写入来源已由原指令闭合（analysis07 §07.3/07.4）；forceKeyFrame到编码器实际IDR的因果链
仍未闭合（OPEN-VID-7）。撤回bit7候选关键帧说法。

## 04.7 未证清单（本文件相关）

| 问题 | 编号 |
|---|---|
| NAL表示、avcC内部参数集布局/帧内重复；本avcC→type1通路已核 | `OPEN-VID-3`、`OPEN-VID-6` |
| 协商 blob 结构 | `OPEN-VID-8` |
| 附件来源已核；与编码器实际随机访问帧/forceKeyFrame的对应 | `OPEN-VID-7` |
| 编码参数取值 | `OPEN-VID-12` |

## 本章依据

| 结论 | 说明 |
|---|---|
| `A04.1` | AVC 封装类与关键方法表 |
| `A04.2` | 消费编码sample；已核avcC→type1，不能据抽样排除NAL重排 |
| `A04.3` | AVCMediaStreamNegotiator 与 negotiationData |
| `A04.4` | 呈现模式/HDR参与配置；完整重协商触发条件待核 |
| `A04.5` | 编码参数存在但未取证 |
| `A04.6` | bit7来自APInterestingFrame，bit4来自NotSync输出；不是NAL IDR证明 |
