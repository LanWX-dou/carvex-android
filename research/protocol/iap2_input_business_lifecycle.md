# 输入、业务数据与生命周期 — 任务要求（`iap2_input_business_lifecycle`）

> **历史任务书**：本文件是上游任务书，现行版本以 `research/protocol/iap2_input_business_lifecycle/TASK.md` 为准；本文件保留用于追溯，不再单独修订。


> 本文件是**任务书**，不是协议规范。
> 目标：给出 iAP2 输入与业务消息的规范：HID 按键/触摸、NowPlaying（50xx）、导航 HUD（52xx）、断连/休眠/恢复/资源清理。
>
> 口径：`CONFIRMED` 只表示“在本阶段证据范围内可复核”；消息 ID、参数、门控必须以抓包/实现证据为准。

当前交付与审计：[STATUS](iap2_input_business_lifecycle/STATUS.md)、
[本轮原指令纠错](iap2_input_business_lifecycle/analysis/12-lifecycle-and-empty-param-audit.md)。
原任务示意不是协议要求：恢复ACK头偏移、空TLV、消息方向和认证前禁发均以修订spec为准。

---

## 0. 阶段定位

```text
iAP2 控制会话 / AirPlay 会话已建立
        ↓
【本阶段】输入、业务数据、生命周期
  ├─ HID：按键 / 触摸
  ├─ NowPlaying：50xx
  ├─ 导航 HUD：52xx
  ├─ 断连 / 休眠 / 恢复
  └─ 资源清理
        ↓
车机 UI / 业务功能
```

本阶段只回答：

- 车机/设备之间如何传按键、触摸、旋钮；
- NowPlaying 50xx 的消息与状态；
- 导航 HUD 52xx 的消息与字段；
- 断连、休眠、恢复时如何保持/清理状态；
- 资源如何释放、如何重连。

**不回答**：音频/视频编解码、FairPlay、RTP 时序、AirPlay 控制面。

---

## 1. 目标与完成判据

**目标**：产出可复现的输入/业务/生命周期规范，使第三方客户端能：

1. 解析/发送 HID 按键与触摸；
2. 处理 NowPlaying 50xx；
3. 处理导航 HUD 52xx；
4. 正确门控（认证/识别/特性）；
5. 处理断连、休眠、恢复；
6. 幂等清理资源。

**完成判据**：

1. 12 项覆盖要求逐项有证据或 `OPEN`；
2. 至少一份真实抓包含按键/触摸/业务消息；
3. 有消息字段表与状态机；
4. 有断连/休眠/恢复测试；
5. `verify.py` 可回放；
6. 不得把“收到消息”写成“业务已生效”。

---

## 2. 素材与证据来源

| 素材 | 要求 |
|---|---|
| iAP2 抓包 | HID、50xx、52xx、断连/重连 |
| 控制面 | 认证/识别/特性门控 |
| 输入样本 | 按键、触摸、旋钮、手势 |
| 业务样本 | NowPlaying 更新、HUD 更新 |
| 生命周期 | 休眠/唤醒、链路断开、App 退出 |
| 参考 | 既有 iAP2 docset、HID 规范、AirPlay/CarPlay 公开资料 |

---

## 3. 方法与证据链

1. **消息识别**：msg_id、方向、参数组、长度；
2. **HID**：报告描述符、report ID、按键位、触摸坐标/压力；
3. **50xx**：请求/响应/更新、字段、频率；
4. **52xx**：HUD 字段、单位、刷新；
5. **门控**：适用认证/识别完成与方向/特性能力；2/6是已核固件内部枚举，非线上字段；
6. **生命周期**：断连/休眠/恢复的状态迁移；
7. **清理**：队列、定时器、回调、缓冲区；
8. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`。

**禁止**：

- 把 HID 报告当普通字节数组；
- 把 50xx/52xx 的字段名按猜测写死；
- 忽略门控直接发消息；
- 把唤醒等同业务恢复，或无证据强制重置所有状态；
- 清理不幂等。

---

## 4. 抽样策略

至少覆盖：

1. 按键按下/释放/长按；
2. 单点/多点触摸、滑动；
3. NowPlaying 开始/更新/停止；
4. HUD 更新/清除；
5. 断连/重连；
6. 休眠/唤醒。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **HID 能力** | 支持哪些报告？描述符是什么？report ID？ |
| 2 | **按键** | 键值、按下/释放、重复、组合键？ |
| 3 | **触摸** | 坐标、压力、多点、手势、坐标系？ |
| 4 | **NowPlaying 50xx** | 50xx 的消息集、字段、方向、频率？ |
| 5 | **导航 HUD 52xx** | 52xx 的消息集、字段、单位、刷新？ |
| 6 | **门控** | 认证/识别/特性集合条件？不满足时如何？ |
| 7 | **消息顺序** | 请求/响应/更新/确认的时序？ |
| 8 | **断连** | 检测、通知、队列处理、重连？ |
| 9 | **休眠/恢复** | 谁发起？状态保留/重置？定时器？ |
| 10 | **资源清理** | 释放顺序、幂等、泄漏点？ |
| 11 | **错误与重试** | 非法参数、超时、重复消息？ |
| 12 | **版本与差异** | 不同车机/HID/业务差异？ |

### 5.1 重点专题

#### A. HID

必须给出：

- 报告描述符（如可得）；
- report ID 与字段偏移；
- 按键位图/键值；
- 触摸坐标范围、分辨率、触点 ID；
- 发送频率/节流。

#### B. NowPlaying 50xx

必须给出：

- 实际出现的 50xx 消息 ID；
- 每条消息的字段、方向、触发；
- 与 Wi‑Fi Sharing `0x5702/0x5703` 的区别（不要混用）；
- 失败/不支持时的行为。

#### C. 导航 HUD 52xx

必须给出：

- 实际出现的 52xx 消息 ID；
- 字段（距离、转向、道路名、单位）；
- 刷新频率/过期；
- 清除/结束。

#### D. 生命周期

必须给出可检查的生命周期模型；状态数不是线上规范。本地安全参考：

```text
DISCONNECTED → RECONNECTING → NEGOTIATING → [认证/识别/特性门通过] → ACTIVE
ACTIVE → SUSPENDED → RESUMED → [当前有效性检查] → ACTIVE
连接中各阶段 → DETACH/FAIL → DISCONNECTED（拒绝旧代际回调）
```

包括：定时器暂停、队列保留/丢弃、资源释放、幂等重入。

---

## 6. 交付物与目录建议

```text
research/protocol/iap2_input_business_lifecycle.md
research/protocol/iap2_input_business_lifecycle/
  analysis/
    00-method-and-environment.md
    01-hid-descriptor.md
    02-buttons-and-touch.md
    03-nowplaying-50xx.md
    04-navigation-hud-52xx.md
    05-gating-and-order.md
    06-lifecycle.md
    07-cleanup.md
    08-runtime-captures.md
    A-conclusions.md
  spec/
    00-scope-and-terms.md
    01-hid.md
    02-nowplaying.md
    03-navigation-hud.md
    04-gating.md
    05-lifecycle.md
    06-client-guide.md
    07-conformance-checklist.md
    08-open-items.md
  runtime/
    captures/
    replay/
  reference-impl/
    input_codec.py
    lifecycle_fsm.py
    test_vectors.json
  verify.py
  STATUS.md
  manifest.json
```

---

## 7. 非目标

- 音频/视频（`airplay_audio_mic_channel`、`airplay_video_channel`）；
- FairPlay（`airplay_fairplay_crypto`）；
- RTP 时序（`airplay_rtp_timing`）；
- AirPlay 控制面（`airplay_control_plane`）；
- iAP2 隧道分片（`iap2_airplay_tunnel`）。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| HID 描述符未取证 | 按键/触摸解析错 |
| 50xx/52xx 字段未证 | 业务不生效 |
| 门控条件遗漏 | 消息被丢弃 |
| 休眠/恢复状态不清 | 唤醒后黑屏/无响应 |
| 清理不幂等 | 重连崩溃/泄漏 |
| 车机差异 | 一套实现不通用 |

---

## 9. 验收清单

- [ ] 按键/触摸有真实抓包；
- [ ] NowPlaying 50xx 字段表完整；
- [ ] HUD 52xx 字段表完整；
- [ ] 门控与顺序有证据；
- [ ] 断连/休眠/恢复有状态机；
- [ ] 清理幂等有测试；
- [ ] `verify.py` 通过；
- [ ] `STATUS.md` 与 `OPEN` 清单完整；
- [ ] 未把“收到消息”写成“业务已生效”。

---

## 10. 一句话

**本阶段只做“按键/触摸/NowPlaying/HUD 的消息与状态，以及断连/休眠/恢复/清理”；不解释音视频载荷，也不做 AirPlay 控制面。**
