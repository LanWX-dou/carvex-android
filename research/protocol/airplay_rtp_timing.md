# AirPlay RTP 传输与时序 — 任务要求（`airplay_rtp_timing`）

> **历史任务书**：本文件是上游任务书，现行版本以 `research/protocol/airplay_rtp_timing/TASK.md` 为准；本文件保留用于追溯，不再单独修订。


> 本文件是**任务书**，不是协议规范。
> 目标：给出 AirPlay 媒体 RTP 的传输与时序规范：RTP 扩展头、NTP 时钟同步、抖动缓冲、丢包统计、流量控速。
>
> 口径：`CONFIRMED` 只表示“在本阶段证据范围内可复核”；传输方式、扩展头、时钟字段必须以抓包/实现证据为准。

---

## 0. 阶段定位

```text
AirPlay 控制面（airplay_control_plane）
  └─ RTSP SETUP 协商出流、端口、传输方式
        ↓
【本阶段】RTP 传输与时序
  ├─ RTP/RTCP 包
  ├─ 扩展头
  ├─ NTP 时钟同步
  ├─ 抖动缓冲
  ├─ 丢包统计
  └─ 流量控速
        ↓
FairPlay 解密、视频/音频解码（后续阶段）
```

本阶段只回答：

- RTP 包长什么样、扩展头怎么解析；
- 发送端/接收端时钟如何对齐；
- 抖动缓冲如何设计；
- 丢包/乱序/重复如何统计与处理；
- 发送节奏如何控制。

**不回答**：FairPlay 解密、H.264/AAC 解码、AirPlay 控制面、iAP2 隧道分片。

---

## 1. 目标与完成判据

**目标**：产出可复现的 RTP 时序规范，使第三方客户端能：

1. 解析 RTP/RTCP 包与扩展头；
2. 用 NTP/RTCP 建立时钟关系；
3. 设计可配置的抖动缓冲；
4. 统计丢包、乱序、重复、迟到；
5. 按时间戳/带宽控速发送；
6. 明确异常与边界。

**完成判据**：

1. 12 项覆盖要求逐项有证据或 `OPEN`；
2. 至少一份真实媒体抓包，含 RTP/RTCP；
3. 有抖动/丢包/乱序的可重复测试；
4. 有 NTP 对齐的计算样例；
5. `verify.py` 可回放；
6. 不得把“能收包”写成“能正确播放”。

---

## 2. 素材与证据来源

| 素材 | 要求 |
|---|---|
| 媒体 pcap | RTP/RTCP，含时间戳、序列号、SSRC |
| 控制面抓包 | SETUP 中的传输/端口/时钟参数 |
| 多流样本 | 视频 + 音频，或至少两路 |
| 网络异常 | 丢包、乱序、重复、抖动、延迟 |
| 参考 | RFC 3550（RTP/RTCP）、AirPlay 公开资料 |

---

## 3. 方法与证据链

1. **RTP 解析**：版本、填充、扩展、CSRC、marker、payload type、seq、timestamp、SSRC；
2. **扩展头**：profile、length、元素、填充；
3. **RTCP**：SR/RR/SDES/BYE/XR（以实际出现为准）；
4. **时钟**：NTP 秒/分数、RTP 时间戳、采样率、偏移；
5. **缓冲**：到达时间、播放时间、目标延迟、水位；
6. **统计**：期望包数、收到、丢失、重复、乱序、迟到；
7. **控速**：发送间隔、令牌桶/信用、拥塞信号；
8. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`。

**禁止**：

- 把 RTP 时间戳当墙钟；
- 用到达时间直接当播放时间；
- 忽略 SSRC/流 ID 混流；
- 把丢包统计写成“解码失败原因”。

---

## 4. 抽样策略

至少覆盖：

1. 正常网络；
2. 人为丢包 1%/5%；
3. 乱序/重复；
4. 抖动/延迟；
5. 视频/音频同时；
6. 长时间运行（时钟漂移）。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **RTP 头** | 字段布局、版本、padding、extension、CSRC、marker？ |
| 2 | **扩展头** | profile/length、元素格式、多扩展、填充？ |
| 3 | **载荷类型** | payload type 与编解码/流的映射？动态类型如何协商？ |
| 4 | **序列号** | 宽度、回绕、重复/乱序判定？ |
| 5 | **时间戳** | 时钟频率、回绕、与 NTP 的关系？ |
| 6 | **SSRC/流标识** | 多流如何区分？冲突/切换？ |
| 7 | **NTP 同步** | 用 SR/其他消息？偏移/延迟如何计算？ |
| 8 | **抖动缓冲** | 目标延迟、水位、上溢/下溢、动态调整？ |
| 9 | **丢包处理** | 丢包检测、 concealment、重传/不重传？ |
| 10 | **统计** | 丢包率、乱序率、重复率、迟到率的定义与窗口？ |
| 11 | **流量控速** | 发送节奏、令牌桶、拥塞/背压？ |
| 12 | **异常与版本** | 超时、断流、时钟跳变、不同车机差异？ |

### 5.1 重点专题

#### A. RTP 扩展头

必须给出：

- 扩展是否出现、在哪些流；
- profile 值、length 单位；
- 元素 ID/Length/Data 的边界；
- 未知扩展如何处理；
- 扩展是否参与加密/标签。

#### B. NTP 时钟同步

必须给出：

```text
车机时钟（NTP） ↔ 设备时钟
RTP 时间戳 ↔ 采样率 ↔ 播放时间
```

包括：SR 的 NTP/RTP 对应、往返延迟、偏移平滑、时钟跳变。

#### C. 抖动缓冲

必须给出：

- 目标延迟与最大延迟；
- 水位上下限；
- 迟到帧丢弃阈值；
- 动态调整策略；
- 与音视频同步的关系。

---

## 6. 交付物与目录建议

```text
research/protocol/airplay_rtp_timing.md
research/protocol/airplay_rtp_timing/
  analysis/
    00-method-and-environment.md
    01-rtp-header.md
    02-extension-header.md
    03-rtcp-and-ntp.md
    04-jitter-buffer.md
    05-loss-and-reorder.md
    06-pacing.md
    07-runtime-captures.md
    A-conclusions.md
  spec/
    00-scope-and-terms.md
    01-rtp-format.md
    02-clock-sync.md
    03-jitter-buffer.md
    04-loss-stats.md
    05-pacing.md
    06-client-guide.md
    07-conformance-checklist.md
    08-open-items.md
  runtime/
    captures/
    replay/
  reference-impl/
    rtp_parser.py
    jitter_buffer.py
    test_vectors.json
  verify.py
  STATUS.md
  manifest.json
```

测试向量至少包含：正常序列、丢包、乱序、重复、时间戳回绕、时钟跳变、缓冲上溢/下溢。

---

## 7. 非目标

- FairPlay 解密（`airplay_fairplay_crypto`）；
- H.264/AAC 解码（`airplay_video_channel`、`airplay_audio_mic_channel`）；
- AirPlay 控制面（`airplay_control_plane`）；
- iAP2 隧道分片（`iap2_airplay_tunnel`）。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| RTP 传输方式（UDP/TCP/隧道）未定 | 抓包/实现不同 |
| 扩展头语义未证 | 解析错位 |
| NTP 同步消息未定 | 音画不同步 |
| 抖动缓冲策略无样本 | 卡顿/延迟 |
| 丢包是否重传未定 | 花屏/静音 |
| 时钟漂移 | 长时间播放失步 |

---

## 9. 验收清单

- [ ] 真实 RTP/RTCP 抓包已归档；
- [ ] RTP 头/扩展头字段表完整；
- [ ] NTP 对齐有计算样例；
- [ ] 抖动缓冲有水位与调整策略；
- [ ] 丢包/乱序/重复统计有定义；
- [ ] 控速有测试；
- [ ] `verify.py` 通过；
- [ ] `STATUS.md` 与 `OPEN` 清单完整；
- [ ] 未把“收包”写成“可播放”。

---

## 10. 一句话

**本阶段只做“RTP 包怎么读、时钟怎么对、抖动/丢包怎么处理、发送怎么控速”；不解释载荷里的视频/音频，也不做解密。**
