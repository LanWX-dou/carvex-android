# 音频与麦克风 — 任务要求（`airplay_audio_mic_channel`）

> **历史任务书**：本文件是上游任务书，现行版本以 `research/protocol/airplay_audio_mic_channel/TASK.md` 为准；本文件保留用于追溯，不再单独修订。


> 本文件是**任务书**，不是协议规范。
> 主体是仿iPhone的设备端：向车机发送媒体/导航音，接收车机麦克风。采集/播放对端可用于验证，不能倒置产品方向。
> 目标：给出 AirPlay 音频通道的端到端规范：媒体音、导航提示音、麦克风上行、RED、加密、TEARDOWN。
>
> 口径：`CONFIRMED` 只表示“在本阶段证据范围内可复核”。字段、默认值、算法和状态门优先追固件原指令；真实车机选值与互通结果另作运行验证，不能把静态待追项统一推给抓包。

---

## 0. 阶段定位

```text
AirPlay 控制面 / RTP 时序 / FairPlay 解密
  └─ 音频流、麦克风流已协商
        ↓
【本阶段】音频与麦克风
  ├─ 媒体音
  ├─ 导航提示音
  ├─ 麦克风上行
  ├─ RED 冗余
  ├─ 解密
  └─ TEARDOWN
        ↓
车机扬声器 / 麦克风阵列
```

本阶段只回答：

- 有哪几路音频，各自方向/用途；
- 编解码与 RTP 打包；
- RED 如何冗余/恢复；
- 解密在什么位置；
- 麦克风如何采集/编码/上行；
- 混音/闪避/优先级；
- TEARDOWN 如何收尾。

**不回答**：视频、FairPlay 算法、RTP 抖动缓冲、控制面、iAP2 分片。

---

## 1. 目标与完成判据

**目标**：产出可复现的音频/麦克风规范，使第三方客户端能：

1. 生成/编码并发送媒体音，使车机持续播放；
2. 发送导航提示音，按适用profile处理独立流或混音；
3. 接收车机采集/编码的麦克风流，认证解码后供本设备语音/通话业务；
4. 正确处理 RED 冗余；
5. 解密、同步、闪避；
6. 正确 TEARDOWN。

**完成判据**：

1. 12 项覆盖要求逐项有证据或 `OPEN`；
2. 至少一路媒体音可稳定播放；
3. 至少一路车机麦克风上行可由本设备认证解码并交业务消费；
4. 有 RED 丢包恢复测试；
5. 有闪避/混音测试；
6. `verify.py` 可回放；
7. 不得把“有声音”写成“音频通道完全正确”。

---

## 2. 素材与证据来源

| 素材 | 要求 |
|---|---|
| 音频 pcap | RTP 音频流、RED 包、时间戳 |
| 控制面 | SETUP 中的音频/麦克风参数 |
| 麦克风样本 | 采集/编码/上行 |
| 导航提示 | 独立流或混音标记（如可得） |
| 参考 | RFC 2198（RED）、音频编解码标准、AirPlay 公开资料 |

---

## 3. 方法与证据链

1. **流识别**：SSRC/payload type/端口/方向；
2. **编解码**：AAC/ALAC/其他（以证据为准），采样率/声道/帧长；
3. **RTP**：timestamp/marker/seq；
4. **RED**：冗余块头、主块/冗余块、恢复顺序；
5. **解密**：解密位置与范围；
6. **播放**：缓冲、重采样、混音、闪避；
7. **麦克风**：采集格式、编码、上行 RTP；
8. **TEARDOWN**：停流、释放、重连；
9. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`。

**禁止**：

- 假设所有音频都是 AAC；
- 忽略 RED 的冗余块；
- 把导航提示音当普通媒体音混在一起；
- 不区分车机采集端与设备接收端的回声/增益职责，或将未证本地DSP策略写成协议要求；
- 把“有声音”当成“同步正确”。

---

## 4. 抽样策略

至少覆盖：

1. 媒体音单流；
2. 导航提示音（独立/混音）；
3. 麦克风上行；
4. RED 正常/丢包；
5. 多路音频同时；
6. TEARDOWN/重连。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **音频流类型** | 媒体音/提示音/麦克风如何区分？方向？ |
| 2 | **编解码** | 编码、采样率、声道、帧长、码率？ |
| 3 | **RTP 打包** | payload type、timestamp、marker、分片？ |
| 4 | **RED** | 冗余块格式、深度、恢复顺序？ |
| 5 | **解密** | 解密覆盖范围、顺序、失败处理？ |
| 6 | **媒体播放** | 缓冲、重采样、输出设备？ |
| 7 | **导航提示音** | 独立流还是混音？优先级/闪避？ |
| 8 | **麦克风上行** | 采集格式、编码、RTP、增益/回声？ |
| 9 | **混音/闪避** | 多路同时播放时如何混？谁优先？ |
| 10 | **同步** | 音视频同步、麦克风/扬声器延迟？ |
| 11 | **TEARDOWN** | 停流顺序、资源释放、重连？ |
| 12 | **错误与版本** | 丢包、解码失败、不同车机差异？ |

### 5.1 重点专题

#### A. 音频流类型

必须给出：

- 媒体音：设备 → 车机；
- 导航提示音：设备 → 车机，是否独立 SSRC/流；
- 麦克风：车机 → 设备（上行）；
- 每路的 payload type/端口/方向。

#### B. RED

必须给出：

- RED 块头字段；
- 主块与冗余块的时间戳偏移；
- 丢失主块时如何用冗余恢复；
- 冗余深度与带宽权衡；
- 与解密/解码的顺序。

#### C. 麦克风上行

必须给出：

- 采集采样率/位深/声道；
- 编码器/帧长；
- RTP 时间戳；
- 增益/降噪/回声消除（如实现）；
- 车机对麦克风采集/发送的门控，以及本设备接收/解码/业务消费条件。

#### D. TEARDOWN

必须给出：

- 停流消息/顺序；
- 播放器/采集器释放；
- 与链路断开/重连的区别；
- 幂等性。

---

## 6. 交付物与目录建议

```text
research/protocol/airplay_audio_mic_channel.md
research/protocol/airplay_audio_mic_channel/
  analysis/
    00-method-and-environment.md
    01-audio-streams.md
    02-codecs-and-rtp.md
    03-red.md
    04-decryption.md
    05-playback-and-mixing.md
    06-microphone-uplink.md
    07-teardown.md
    08-runtime-captures.md
    A-conclusions.md
  spec/
    00-scope-and-terms.md
    01-audio-streams.md
    02-codecs.md
    03-red.md
    04-playback-mixing.md
    05-microphone.md
    06-teardown.md
    07-client-guide.md
    08-conformance-checklist.md
    09-open-items.md
  runtime/
    captures/
    replay/
  reference-impl/
    audio_depacketizer.py
    red_decoder.py
    test_vectors.json
  verify.py
  STATUS.md
  manifest.json
```

---

## 7. 非目标

- 视频（`airplay_video_channel`）；
- FairPlay 算法（`airplay_fairplay_crypto`）；
- RTP 抖动缓冲（`airplay_rtp_timing`）；
- 控制面（`airplay_control_plane`）；
- iAP2 分片（`iap2_airplay_tunnel`）。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| 编解码未定 | 无法解码 |
| RED 深度/格式未证 | 丢包恢复失败 |
| 导航提示音路由不清 | 提示音被音乐盖住 |
| 麦克风编码/门控不清 | 车机不启用采集或本设备无法消费上行 |
| 音视频同步 | 口型/提示延迟 |
| TEARDOWN 顺序 | 爆音/资源泄漏 |

---

## 9. 验收清单

- [ ] 媒体音可稳定播放；
- [ ] 导航提示音可识别/混音；
- [ ] 麦克风可上行；
- [ ] RED 丢包恢复有测试；
- [ ] 解密顺序有证据；
- [ ] 混音/闪避有测试；
- [ ] TEARDOWN 可重复；
- [ ] `verify.py` 通过；
- [ ] `STATUS.md` 与 `OPEN` 清单完整；
- [ ] 未把“有声音”写成“通道完全正确”。

---

## 10. 一句话

**本阶段只做“媒体音、提示音、麦克风上行、RED、解密、混音/闪避、TEARDOWN”；视频、FairPlay 算法和 RTP 时序不在本阶段。**
