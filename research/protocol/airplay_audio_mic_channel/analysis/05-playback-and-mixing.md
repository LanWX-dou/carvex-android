# 05 播放、混音与闪避

## 5.1 播放侧对象

每条音频流在 AirPlaySender 侧有一个 stream 对象，属性槽（`INFERRED`，见
`firmware/analysis/24A446/microphone-rx/input-contract-worker/transaction.md`）：

| 槽 | 内容 |
|---|---|
| `+0x90` | 选中的 `AudioFormatInfo` |
| `+0x98` | 附加信息（如 `vocoderInfo`） |
| `+0xa0` | `AudioSink`：**消费**车机送来的麦克风数据的 sink |
| `+0xa8` | `AudioSource`：**生产**设备送出的媒体音 |
| `+0x178` | 活动 sink 对象 |
| `+0x1c0` | 活动 source 对象 |
| `+0x1d0` | OutputKey 加密器（媒体音） |
| `+0x180` | InputKey 解密器（麦克风） |

注意方向：`AudioSink` 名字是「设备侧的 sink」，它吃的是**车机发来的**音频；麦克风上行因此
落在 sink 上，而媒体播放在 source 上（`A05.1`）。

## 5.2 缓冲与延迟

- SETUP 的 `audioLatencyMs` 取自格式描述对象首字（`[x23]`，`0x2519be850`）；
  `spf` 取自 `[x27+0x14]`（`0x2519be8d0`）。两个来源对象是否同一个 formatInfo 未证。
- 有 sink 时把「选中 latency 的首字段」写进 sink 的 `BufferDurationMS`，再调
  `class+0x10(sink, ASBD)` 配置格式、`class+0x18(sink)` 做无参准备，两步都必须返回 0
  （`INFERRED`，`0x2519bdcf8..0x2519bde44`，`A05.2`）。
- 输入侧另有容量 **20** 的 `CMSimpleQueue`（`+0x1a0`）用于早到包暂存（见 06）。
- 这两个数值（延迟、深度 20）是固件里的实现取值，不是协议常量；换实现可以不同，
  但**不能**因此假设车机接受任意延迟（`OPEN-PLAY-1`）。

## 5.3 就绪门

接收回调把包投递到队列后，由异步块按两个标志决定行为（`INFERRED`，`0x2519c0f08`）：

| `+0x170` 已就绪 | `+0x198` 暂存中 | 行为 |
|---:|---:|---|
| 0 | 0 | 丢弃，不进入处理函数 |
| 0 | 1 | 暂存进容量 20 的队列 |
| 1 | 1 | 先 FIFO 排空暂存，再处理当前包 |
| 1 | 0 | 直接处理当前包 |

「就绪」与 SETUP 完成不是同一件事：`+0xb8` 是整个 resume 的完成标志，和这个输入门是两套
（`INFERRED`）。所以**收到 SETUP 回复不代表可以播放**，要等流层就绪。

## 5.4 混音、闪避、优先级

本阶段**没有证据**：固件片段里没有出现按 `audioType` 排序、压低（ducking）、抢占的逻辑，
也没有多流同时播放的仲裁表。能看到的只有：

- 多条流可以各自 SETUP、各自有 sink/source（`A05.3`）；
- `audioType` 的取值里有 `alert`/`telephony` 这类语义标签（`A02.9`，`INFERRED`）。

所以：**导航提示音与媒体音怎么共存，未证**（`OPEN-PLAY-2`、`OPEN-AUD-1`）。
实现侧只能先做「单流播放 + 多流并存不互相打断」，并把闪避登记为待验证。

## 5.5 重采样与输出设备

`sink class+0x10` 拿到的 ASBD 是「选中格式」，说明格式转换发生在 sink 内部或下游；
采样率转换、声道映射、物理设备选择都不在本阶段证据内（`OPEN-PLAY-1`）。

## 5.6 音视频同步

音画同步、麦克风/扬声器往返延迟、`supportsHighAccuracyTimestamps` 的实际用法，
按阶段划分属于 `airplay_rtp_timing`，本文件只记录「该标志恒为 true」（`A02.4`）并转介
`OPEN-PLAY-3`。
