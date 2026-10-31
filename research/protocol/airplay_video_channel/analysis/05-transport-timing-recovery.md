# 05 传输、时序与恢复

> 本文件回答第 9、10、11 项覆盖要求：帧怎么排、时间戳怎么来、车机怎么要关键帧、断流怎么恢复。
> 传输层的"谁连谁"只能是 `INFERRED`（`APTransport` 未纳入 `source/`）。

## 05.1 发送循环：一次处理一批

`_screenstream_dequeueAndProcessSampleBuffer`（`0x2519b0014`）不是"一帧一次"，而是：

1. 使用流对象的时间戳数组[+3e8]与长度[+458]构造间隔字段；不能据数组直接认定一次消费多少访问单元；
2. 先（可选）发一条**配置记录**：`local_d8 != 0` 时调用 `_sbpd_createConfigBBuf`（`0x2519b0e5c` `cbz w28` → `0x2519b0e68` `bl #0x251b43fcc`）；
3. 构造128B头并调用加密包装器；可选第二段再次调用，然后组装记录；
4. 头里的 `+0x60` 数组记录这批帧之间的间隔（`02.2.1`）。

**已核范围**：存在配置时在帧之前组装；精确发送时机、重复配置是否允许与访问单元聚合关系仍需追。

## 05.2 时间戳

| 步骤 | 指令 | 说明 |
|---|---|---|
| 取时间上下文 | `0x2519b0ea0` `ldr x21, [x20, #0x3d0]` | 流对象 +0x3d0 是一个时间转换对象 |
| 验证 vtable | `0x2519b0eb8` `autda`；`0x2519b0ec4` `movk x8, #0xea2e, lsl #48` | 带 PAC 的间接调用 |
| 调用转换 | `0x2519b0f00` `blraa x9, x8`；入参 `x1 = [+0x3d8] + [+0x3b8]`（`0x2519b0ef4`） | 输入是一个 64 位时间值，输出 16 字节（`q0`） |
| 写入头 | `0x2519b0f8c` `str x9, [x25, #8]`；`0x2519b0f90` `str x8, [x25, #0x28]` | 高/低 64 位分别落 `+0x08` 与 `+0x28` |
| 第二路 | `0x2519b1010` `blraa`（入参 `[+0x3e8]`） | 结果写 `+0x20`/`+0x58` |

**已证**：若干头字段由转换器调用生成，+10另取storage+3e0，不能把全部u64都称作同一转换器的时间值。
**未证**：时间基准（NTP/媒体时间/主机时钟）、单位、以及+0x10的语义；+0x1c的尾段长度证据已补在06.4（`OPEN-VID-9`）。

## 05.3 关键帧请求（车机 → 手机）

车机的命令入口是 `carEndpoint_processEventCreatingResponse`（字符串 `0x251c3a202`）。同一字符串簇列出它支持的命令（`0x251c3a28a` 起）：

```text
forceKeyFrame
hidSendReport
changeModes
iAPSendMessage
requestSiri
requestUI
updateViewArea
setLimitedUI
setNightMode
setVideoPlaybackAllowed
videoPlayerBackButtonEvent
updateVehicleInformation
```

其中 `forceKeyFrame` 的处理函数符号被剥掉，只留日志串：

| 字符串 | 地址 |
|---|---|
| `forceKeyFrame`（命令名） | `0x251c3a28a` |
| `OSStatus carEndpoint_forceKeyFrame(FigEndpointRef, CFDictionaryRef)` | `0x251c3a38e` |
| `[%{ptr}] Force Key Frame, params: %@` | `0x251c3a3d2` |

**已证**：存在"车机请求关键帧"的命令名与处理函数签名；处理函数接收一个参数字典。
**未证**：参数里有没有"目标帧号/原因"、处理后多久内必须出 IDR（`OPEN-VID-7`）。

## 05.4 清屏

| 路径 | 地址 | 说明 |
|---|---|---|
| 采集层清屏回调 | `screenCapture:screenDidClear:` @ `0x251a77da0` | 编码侧通知"画面清空" |
| UDP 变体清屏 | `_screenstreamudp_handleClearScreen` @ `0x251a761d8` | 对应 `handleClearScreen` 字符串 `0x251c046be` |

这些入口证明存在清屏处理路径，不独自证明线上命令格式、是否发黑图或是否重置解码参考；副作用与对端约束仍需核验。

## 05.5 断流与致命错误

| 组件 | 地址 | 已证行为 |
|---|---|---|
| `_screenstream_handleFatalError` | `0x251b43140` | 处理致命错误（带 `cleanup` block） |
| `_screenstream_cleanup` | `0x251b42e34` | 清理流对象 |
| `_screenstream_Suspend` | `0x251b43624` | 挂起（对端暂停） |
| `_screenstream_Resume` | `0x251b43744` | 恢复 |
| `serverDidDisconnect:` | `0x251a77e9c` | 对端断开 |
| 发送失败日志 | 帧函数内`"send data failed, stream disconnected"` | 仅证明该日志文本存在，不能外推所有socket错误必断流 |

状态位可从调试串读出：`<APEndpointStreamScreenUDP %p '%@', activated: %s resumed: %s >`（`0x251c0388c`）——流对象至少有两个布尔状态：**activated**、**resumed**。

**未证**：断流检测的阈值（超时/连续失败次数）、重连退避、重连后是否自动重发配置记录（`OPEN-VID-10`）。

## 05.6 UDP 变体的载荷

UDP 变体的传输串是 `RTP/AVP/UDP`（`0x251c13dc6`，引用点 `0x251a9f414`）。
**已证**：它使用 RTP over UDP 的 SDP 描述。
**未证**：RTP 头字段、payload type、SSRC、以及 H.264 的打包模式（单 NAL/FU-A/STAP-A）——本阶段未读 `screenstreamudp` 的打包函数（`OPEN-VID-3`）。

## 05.7 恢复状态机（推断，非规范）

据上述组件可拼出**候选**状态机（`INFERRED`，阈值未知）：

```text
IDLE
  └─ SETUP 成功 → CONFIGURED
        └─ 首帧/配置记录发出 → STREAMING
              ├─ 收到 forceKeyFrame → 等 IDR → STREAMING
              ├─ 需重建的错误/对端断开 → DEGRADED → (重连) → SETUP
              └─ 挂起 → SUSPENDED → 恢复 → STREAMING
```

规范只写"必须能处理哪些事件"（`spec/05`），不把这张图写成时序。

## 05.8 性能相关（可证部分）

- 头内最多16个间隔槽，不等于一批最多16帧；
- ticks差转换成毫秒后≥65536写0xffff；
- 可选第二段另调用加密，拼装成功后构造计数加1；
- `MaxFPS` 来自显示描述（`01.3`），不是常量。

码率/分辨率上限、CPU/GPU 占用：**无证据**（`OPEN-VID-12`）。

## 本章依据

| 结论 | 说明 |
|---|---|
| `A05.1` | 批量发送：配置记录在前、帧在后 |
| `A05.2` | 时间戳来自流对象 +0x3d0 的转换器 |
| `A05.3` | 车机命令 `forceKeyFrame` 存在 |
| `A05.4` | 清屏是独立路径 |
| `A05.5` | 致命错误/挂起/恢复/断开组件 |
| `A05.6` | UDP 变体为 RTP/AVP/UDP，打包未证 |
| `A05.7` | 恢复状态机候选（推断） |
