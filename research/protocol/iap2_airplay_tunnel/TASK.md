# iAP2 隧道封装阶段 — 任务要求（`iap2_airplay_tunnel`）

> 本文件是第四阶段的任务书，结构沿用 `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/`、`research/protocol/iap2_control_session/`。
> 目标：在同一份固件构建（24A446 / iOS 27.0.1 / iPhone18,1）上，用同样的证据链，产出 **iAP2 隧道（tunnel）与 AirPlay 传输交接** 的平台无关规范。

---

## 0. 阶段定位（与前三阶段的衔接）

已确认、可直接引用的边界（引用时带前缀）：

- 链路层：包格式 `FF 5A | len | ctrl | seq | lt | session | hdrChk | payload | payloadChk`，8 状态 FSM，`Connected` 才可用（`link/R-2.x`、`link/R-5.x`）；
- 会话层：消息 6 字节头 `40 40 | len | msgID | params`，参数 4 字节头 `len | id | value`；会话表 4 字节表项；`0x4301` 入站（车机→设备），**静态**参数 ID→字段映射已由 `control/spec/14` 闭合；平台必填性、错误/重试与下游交接仍 `OPEN-SES-2`（`control/R-3.x`、`control/R-4.12`）；
- 识别/认证：`0x1D00/01/02`、`0xAA00/01/02/03/05/06` 顺序与门控（`control/R-9.x`、`control/R-10.x`）。

本阶段从"**链路与会话都建立之后，iAP2 消息如何被塞进另一条隧道、以及 AirPlay 作为传输时字节如何走**"接上。

### 0.1 与原始任务书的方向差异（必须先读）

`research/protocol/iap2_airplay_tunnel.md`（初版任务书）假设方向是"**AirPlay 字节流封装进 iAP2**"（分片、流复用、通道标记、iAP2 信用映射）。

本阶段在 24A446 与 23G90 抓包上核对的结论是：

| 假设 | 实际证据 | 结论 |
|---|---|---|
| AirPlay 媒体字节被切成 iAP2 消息 | 抓包里没有携带 RTSP/RTP 字节的 iAP2 消息；AirPlay 链路本身是 `transport=AirPlay` 的 iAP2 链路，帧格式与 BT 链路逐字节同构 | **未成立** |
| iAP2 走 AirPlay 隧道（AirPlay 作为传输） | 23G90 第二个连接 `hdr[7]=0x03`、`transport=AirPlay`，`40 40 …` 消息原样出现（`A05.1`） | **成立（运行期）** |
| iAP2 消息可被再包一层 iAP2 消息（隧道信封） | `0x5500/0x5501/0x5502/0x5503` + 外层 `0x5164/0x5264`，pack/unpack 函数与指令级证据齐全（`A01.1`、`A02.1`） | **成立（静态+函数级）** |

因此本阶段实际交付两件事，而不是原任务书的"分片/复用/信用"三件套：

1. **iAP2 中继隧道信封**：`0x51xx/0x52xx` 外层消息里承载 `0x55xx` 信封的设备侧规范（这是真正"iAP2 在 iAP2 里"的部分，可分片/可重组/可判错）；
2. **AirPlay 作为 iAP2 传输**：设备侧在 AirPlay 链路上要做什么、能证明什么、不能证明什么（帧不分片、无隧道级流控、AirPlay 帧格式在 accessoryd 之外）。

原任务书的 12 项覆盖要求逐项给出"已答 / 改问 / OPEN"，见 §5。

## 1. 目标与完成判据

**目标**：给出可复现的隧道规范，使第三方设备侧客户端能：

1. 识别并解析 `0x55xx` 隧道信封（含 `0x5503` 的原样消息形态）；
2. 正确构造 `0x5164` 中继请求并处理 `0x5264/0x5265/0x5266` 响应；
3. 按 `type` 与 `capabilitiesMask` 做能力协商与分派；
4. 在 AirPlay 传输上按与 BT 相同的 iAP2 帧规则收发，并知道哪些行为没有证据；
5. 明确"隧道层不分片、不分片也不做信用"这一负结论，不把链路层重传当成隧道层功能。

**完成判据**：

1. `analysis/` 每条结论有指令地址或抓包字节；
2. `spec/` 每条条款有 `依据：`，指向 `A` 编号；
3. 12 项覆盖要求逐项有结论或 `OPEN`；
4. `reference-impl/tunnel_codec.py` 能编码/解码信封并通过全部测试向量；
5. `verify.py` 通过（源哈希、切片一致、条款唯一、`OPEN` 登记完整、向量重算）。

## 2. 素材与目标二进制

| 项 | 值 |
|---|---|
| 主目标 | `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 函数数 | 8,706（LC_FUNCTION_STARTS） |
| 运行期样本 | `runtime/accessoryd-packets-2026-10-16-221117.log.ips` + `runtime/parse-capture.py`（23G90，**非** 24A446；说明见 `runtime/README.md`） |
| 次级线索（**不作证据**） | `AirPlaySender` 的 `APAccTransportClientEndpointSecureTunnelDataSend`、`mfiMutualAuth_*SecureTunnel*`（另一镜像，仅记入 §9） |

## 3. 方法与证据链

1. 原始字节：Mach-O 元数据定位函数区间 → `source/asm/accessoryd/f_<addr>.bin`；
2. Capstone 反汇编（不改写）；
3. Ghidra 自动反编译，标 `RAW_DECOMPILER_OUTPUT_UNREVIEWED`，只作阅读辅助；
4. 人工对照汇编核对，每条结论写出指令地址；
5. `A` 编号结论 → `R` 编号条款 → 测试向量；
6. 负结论（"没有分片""没有信用"）必须给出**穷举式**证据（遍历所有引用点），不能只写"没看到"。

## 4. 抽样策略

- 定向抽样：隧道信封 pack/unpack、中继请求/响应、type 分派、capabilities、错误路径、AirPlay 抓包；
- 采样率如实声明（`n / 8,706`）；
- 未读函数不得被结论依赖；若依赖调用点，必须写明"未读，仅调用点"。

## 5. 覆盖要求（12 项，逐项对账）

| # | 原要求 | 本阶段处置 | 结论位置 |
|---|---|---|---|
| 1 | 隧道建立 | **改问**：中继何时启动、由谁发起；type=2 = T56 已证 | `A04.2`、`A09.2`、`OPEN-TUN-7` |
| 2 | 封装头 | **已答**：`0x55xx` 信封 + 外层 `0x5164` 头 | `A02.1`、`A03.1` |
| 3 | 字节分片 | **负结论**：信封层不分片；分片在链路层 | `A07.1` |
| 4 | 流复用 | **改问**：type∈{0,1,2}（≥3 非法）、2=T56 + capabilities 位图 | `A04.1`、`A09.2` |
| 5 | 排序与重组 | **负结论**：信封无序号；重组=整条消息，靠链路层 | `A02.3`、`A07.1` |
| 6 | 流控适配 | 部分：信封无信用/窗口；完整并发限制未证 | `A03.4`、`A07.3` |
| 7 | 背压 | **改问**：链路层队列满时的行为（`control/R-6.x`） | `A07.3` |
| 8 | 错误处理 | **已答**：`type≥3` 拒绝（`0x1000a9bf8`）、未知消息、空载荷重试 | `A06.1`、`A09.2`、`A03.3` |
| 9 | 拆除 | **已答**：`cleanup` + shutting-down 标志 | `A06.2` |
| 10 | 并发与公平 | 部分：最近命令字段不证明停等；参考实现采用保守策略 | `A03.4` |
| 11 | 安全边界 | **部分**：6 字节 iAP2 头明文；载荷在密钥就绪后被 `ccsigma` AEAD 封装（+16 tag）| `A06.3`、`A09.5`、`A09.6`、`OPEN-TUN-10` |
| 12 | 版本与差异 | **部分**：24A446 与 23G90 差异、AirPlay 传输差异 | `A05.1`、`OPEN-TUN-5` |

### 5.1 2026-10-26 固件定向取证（只动 accessoryd）

| 结果 | OPEN | 证据 |
|---|---|---|
| 关闭 | `OPEN-TUN-8` | `0x1000a8ae4`、`0x1000a9bc8`（provider 是 block，`+0x10`=invoke）|
| 大幅推进 | `OPEN-TUN-10` | `0x1001327d0`、`0x100132acc`（`ccsigma_seal`、长度 +0x10）|
| 收窄 | `OPEN-TUN-2`/-3/-4/-11 | `0x1000a9bc8`、`0x1000feef0`、`0x10017a64c` |

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 二进制（带哈希）、每函数 `.s`+`.bin`+`index.json`、Mach-O 元数据、Ghidra 请求 |
| `readable/` | 与 `source/` 一一对应的自动反编译，带"未人工确认"横幅 |
| `analysis/` | 00–09 + `A-conclusions.md`；每条结论有地址、未确认点、实现影响 |
| `spec/` | 00–07；条款编号唯一，每章"本章依据"表 |
| `reference-impl/` | `tunnel_codec.py` + `test_vectors.json`（正常/边界/非法/未知 type/超长/空载荷）+ `relay_session.py`（停等状态机与自检） |
| `runtime/` | 23G90 抓包副本 + 解析说明，声明构建差异 |
| `manifest.json` | 全量文件哈希、12 项状态、`OPEN` 索引 |
| `verify.py` | 自动校验（见 §7） |
| `STATUS.md` | 三态统计、覆盖率、能否指导实现 |

## 7. `verify.py` 校验项

| 编号 | 校验 |
|---|---|
| C1 | `source/firmware/accessoryd` 的 SHA256 等于声明值 |
| C2 | 每个 `.bin` 与固件对应切片逐字节一致，且 `index.json` 的 `raw_sha256` 正确 |
| C3 | 每个 `.s` 头部含源哈希与 Capstone 声明；`readable/` 每个 `.c` 含 `RAW GHIDRA DECOMPILATION` 横幅 |
| C4 | `spec/` 条款编号唯一、格式合法、每条有 `依据：` |
| C5 | `依据` 引用的 `A` 编号都在 `analysis/A-conclusions.md` 注册 |
| C6 | `OPEN-TUN-*` 在 `source/metadata/coverage.json` 注册且被 ≥1 项覆盖引用 |
| C7 | 跨 docset 引用（`link/R-x.y`、`control/R-x.y`）可在对应 docset 找到 |
| C8 | 12 项覆盖状态与 `summary` 一致；禁止无条件"全部确认" |
| C9 | `test_vectors.json` 全部能被 `tunnel_codec.py` 复算通过；`relay_session.py` 的停等自检通过 |
| C10 | `manifest.json` 与磁盘文件一致（数量与哈希） |

## 8. 非目标

- AirPlay 控制面（RTSP/Pair-Setup）、FairPlay、RTP 时序、编解码；
- AirPlay 传输插件本身的实现（不在 accessoryd 内，见 `OPEN-TUN-5`）；
- 输入/业务/生命周期。

## 9. 线索表（不作证据）

| 线索 | 地址/符号 | 为什么不用 |
|---|---|---|
| AirPlay 发送端隧道 API | `AirPlaySender`：`APAccTransportClientEndpointSecureTunnelDataSend`（`0x251af79ec`）、`mfiMutualAuth_*SecureTunnel*` | 另一镜像，未纳入本阶段 `source/` |
| AirPlay 与 mfi 状态机 | `SecureTunnel-{WaitingForEncryptionCallback,…}` 字符串 | 同上，只说明"隧道数据会被 MFi 层加解密" |
| 旧分析目录 | `firmware/analysis/24A446/iap2-*` | 旧结论，未逐条复核，只能当检索线索 |
