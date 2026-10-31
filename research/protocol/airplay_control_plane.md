# AirPlay 控制面 — 任务要求（`airplay_control_plane`）

> **历史任务书**：本文件是上游任务书，现行版本以 `research/protocol/airplay_control_plane/TASK.md` 为准；本文件保留用于追溯，不再单独修订。


> 本文件是**任务书**，不是协议规范，也不预设字段语义。
> 目标：在 mDNS 发现之后，产出 AirPlay 控制通道的平台无关规范：Pair-Setup / Pair-Verify、加密会话、RTSP SETUP、以及 `type=130` 隧道交接。
>
> 口径：`CONFIRMED` 只表示“在本阶段证据范围内可复核”，不表示 Apple 官方规范；`INFERRED` 必须标推断；无证据一律 `OPEN`。

---

## 0. 阶段定位

```text
mDNS 发现（airplay_mdns_discovery）
  └─ 得到 AirPlay 服务实例、地址、端口、TXT 能力
        ↓
【本阶段】TCP 控制通道
  ├─ Pair-Setup / Pair-Verify
  ├─ 加密会话
  ├─ RTSP 协商
  └─ SETUP：媒体流 / type=130 隧道
        ↓
RTP 媒体、FairPlay 帧加密、iAP2 隧道、视频/音频（后续阶段）
```

本阶段只回答：

- 控制通道怎么建立；
- 配对两条消息（Setup / Verify）的字段、密码学操作与状态；
- 加密会话如何开始、如何标识；
- RTSP 请求/响应与 `SETUP` 的传输参数；
- `type=130` 隧道如何交接给下一层。

**不回答**：FairPlay 帧级密钥派生与 AES 细节、RTP 时序、H.264/AAC 解码、iAP2 隧道分片、输入/业务消息。

---

## 1. 目标与完成判据

**目标**：给出可复现、逐条可追溯的 AirPlay 控制面规范，使第三方客户端能完成：

1. 连接车机 AirPlay 控制端口；
2. 完成 Pair-Setup / Pair-Verify；
3. 建立加密会话；
4. 发出/解析 RTSP 请求与响应；
5. 解析 `SETUP` 的传输参数与 `type=130` 隧道；
6. 明确失败、超时、重试与版本差异。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求逐项有抓包/标准/实现依据，或明确标 `OPEN`；
2. 至少一份真实车机的 AirPlay 控制面抓包（TCP + RTSP + 配对）；
3. 配对字段、加密会话标识、`SETUP` 参数均有字节级样例；
4. `verify.py` 能回放一次完整控制面握手；
5. 每条 `R` 条款能点回 `analysis/` 的 `A` 结论，`A` 能点回抓包帧号/字节；
6. 未知字段、未知 RTSP 方法、未知状态码登记为 `OPEN`；
7. 不得把“配对成功”写成“媒体可播放”。

---

## 2. 素材与证据来源

| 素材 | 要求 |
|---|---|
| 控制面 pcap | 车机与设备同一 Wi-Fi；含 TCP 三次握手、RTSP、Pair-Setup/Verify |
| mDNS 结果 | 来自 `airplay_mdns_discovery` 的服务实例、地址、端口 |
| 配对样本 | 至少一次首次配对 + 一次已配对重连；如可得，一次配对失败 |
| 加密样本 | 加密会话开始前后各至少一条 RTSP 消息 |
| 隧道样本 | `SETUP` 中 `type=130` 的请求/响应；后续 iAP2 交接 |
| 版本 | 至少 1 台车机；尽量覆盖不同 AirPlay 版本 |
| 参考 | AirPlay 公开资料、RTSP 相关 RFC、Apple Bonjour/TXT 资料；只作对照 |

---

## 3. 方法与证据链

1. **TCP 流重组**：按四元组重组，标出每个 RTSP 消息边界；
2. **RTSP 解码**：请求行/状态行、headers、`CSeq`、`Content-Length`、body 编码（文本/二进制 plist/其他）；
3. **配对状态机**：Pair-Setup → Pair-Verify → 加密会话；记录每步输入/输出/失败分支；
4. **密码学标注**：只写“使用了什么操作、输入输出是什么”，不把算法细节写成结论，除非有独立证据；
5. **SETUP 解析**：`Transport` 参数、流 ID、`type=130` 字段位置、响应中的端口/密钥；
6. **隧道交接**：控制面消息如何触发 iAP2 隧道；交接前后各自的字节归属；
7. **对照实验**：pcap 回放 + 真实客户端连接；
8. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`。

**禁止**：

- 把 Pair-Setup 的字段名按“常见 AirPlay”直接套用；
- 把 TLS/加密会话的存在当成配对成功；
- 把 `type=130` 的语义按猜测写成规范；
- 只凭一条抓包推断所有车机。

---

## 4. 抽样策略

至少覆盖：

1. 首次配对：无配对记录 → Pair-Setup → Pair-Verify → 加密；
2. 已配对重连：跳过或复用 Pair-Setup；
3. 配对失败/拒绝；
4. RTSP `OPTIONS` / `ANNOUNCE` / `SETUP` / `RECORD` / `TEARDOWN`（以实际出现为准）；
5. `SETUP` 普通媒体流 vs `type=130` 隧道；
6. 加密会话前后的消息差异；
7. 超时/断连/重连。

如实声明样本数：`n 次配对 / m 条 RTSP 消息 / k 台车机`。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **控制通道建立** | TCP 端口来源？是否 TLS？连接时序、保持、断开？ |
| 2 | **RTSP 消息格式** | 请求行/状态行、headers、大小写、`CSeq`、`Content-Length`、body 类型与编码？ |
| 3 | **Pair-Setup** | 方法名、路径、字段、编码、密码学操作、成功/失败响应？ |
| 4 | **Pair-Verify** | 字段、挑战/签名、公钥、证书、状态机、失败分支？ |
| 5 | **加密会话** | 会话密钥如何产生/标识？哪些消息加密？加密边界在哪？ |
| 6 | **RTSP 方法集** | 实际出现哪些方法？各自请求/响应字段与副作用？ |
| 7 | **SETUP 传输参数** | `Transport` 的字段、流 ID、端口、协议、`type=130` 的位置与含义？ |
| 8 | **type=130 隧道交接** | 谁发起？携带什么？交接后控制面/隧道各自负责什么？ |
| 9 | **错误与状态码** | RTSP 状态码、配对错误、加密失败如何表示？客户端如何分类？ |
| 10 | **超时与重试** | 各阶段超时、重试次数、退避、何时放弃？ |
| 11 | **安全边界** | 配对是否认证车机？中间人、重放、降级如何处理？ |
| 12 | **版本与差异** | AirPlay 1/2、CarPlay、不同车机的字段/方法差异？ |

### 5.1 重点专题

#### A. Pair-Setup / Pair-Verify

必须给出：

- 消息方向、方法、路径、Content-Type；
- 每个字段的名称、类型、长度、编码；
- 密码学输入/输出（公钥、盐、证明、签名等）——只写可证据化的部分；
- 成功/失败响应与状态码；
- 已配对重连是否复用、复用哪些状态。

#### B. 加密会话

必须区分：

- 控制面消息加密；
- 媒体帧加密（FairPlay，另立阶段）；
- 隧道内载荷加密（另立阶段）。

不得把三者混成一个“加密会话”。

#### C. RTSP SETUP 与 type=130

必须给出：

- `SETUP` 请求的完整 header/body；
- `Transport` 参数的解析规则；
- `type=130` 出现在哪个字段、什么值、与普通流 ID 的关系；
- 响应中的端口/密钥/会话 ID；
- 隧道交接的触发条件与状态迁移。

---

## 6. 交付物与目录建议

```text
research/protocol/airplay_control_plane.md
research/protocol/airplay_control_plane/
  analysis/
    00-method-and-environment.md
    01-tcp-and-rtsp.md
    02-pair-setup.md
    03-pair-verify.md
    04-encrypted-session.md
    05-rtsp-methods.md
    06-setup-and-type130.md
    07-tunnel-handoff.md
    08-errors-timeouts.md
    09-security.md
    10-runtime-captures.md
    A-conclusions.md
  spec/
    00-scope-and-terms.md
    01-control-channel.md
    02-pairing.md
    03-encrypted-session.md
    04-rtsp.md
    05-setup-and-tunnel.md
    06-client-guide.md
    07-conformance-checklist.md
    08-open-items.md
  runtime/
    captures/
    replay/
  reference-impl/
    rtsp_parser.py
    pair_state_machine.py
    test_vectors.json
  verify.py
  STATUS.md
  manifest.json
```

---

## 7. 非目标

- FairPlay 帧级密钥派生、AES、标签（`airplay_fairplay_crypto`）；
- RTP/RTCP 时序（`airplay_rtp_timing`）；
- 视频/音频解码（`airplay_video_channel`、`airplay_audio_mic_channel`）；
- iAP2 隧道分片/复用（`iap2_airplay_tunnel`）；
- 输入/业务/生命周期（`iap2_input_business_lifecycle`）；
- “配对成功 = 可以投屏/播放”。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| Pair-Setup/Verify 字段名可能随版本变化 | 不能硬编码 |
| 加密会话边界不清 | 可能把控制面/媒体/隧道加密混在一起 |
| `type=130` 语义未证 | 隧道交接可能实现错 |
| 已配对重连路径不同 | 每次重连都走完整配对会慢/失败 |
| 证书/公钥信任 | 配对成功不等于车机可信 |
| 无真实车机抓包 | 只能写“待验证” |

---

## 9. 验收清单

- [ ] 真实车机控制面 pcap 已归档，含 SHA256；
- [ ] 一次完整 Pair-Setup / Pair-Verify 可回放；
- [ ] 加密会话开始/结束有字节级证据；
- [ ] RTSP 方法、状态码、body 编码有字段表；
- [ ] `SETUP` 与 `type=130` 有完整请求/响应样例；
- [ ] 隧道交接状态机有图/表；
- [ ] 失败/超时/重试有分支；
- [ ] `verify.py` 通过；
- [ ] `STATUS.md` 与 `OPEN` 清单完整；
- [ ] 未把控制面成功写成媒体可用。

---

## 10. 一句话

**本阶段只做“连上控制通道、完成配对与加密会话、用 RTSP SETUP 把流/隧道协商出来”；帧加密、RTP、音视频和 iAP2 分片都不在本阶段。**
