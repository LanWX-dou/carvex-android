# AirPlay RTP 传输与时序阶段 — 任务要求（`airplay_rtp_timing`）

> 本文件是第四阶段的任务书，结构与 `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/`、`research/protocol/iap2_control_session/` 一致。
> 上游任务书：`research/protocol/airplay_rtp_timing.md`（12 项覆盖要求原样继承，见 §5）。
> 目标：在同一份固件构建（24A446 / iOS 27.0.1 / iPhone18,1）上，用同样的严格证据链，产出 **AirPlay 媒体面 RTP 传输与时序** 的平台无关规范。

---

## 0. 阶段定位（与前面阶段的衔接）

前三阶段确认的边界事实（可引用，引用时带 docset 前缀）：

- 蓝牙经典 RFCOMM 承载 iAP2，链路 8 状态 FSM、`Connected` 是唯一可用判定（`iap2_link_establish/R-6.x`）；
- 会话层：消息 6 字节头、参数 4 字节头、会话表 `link+0x1b8`、控制会话建立 `0x4301` 入站（`iap2_control_session/R-3.x`、`iap2_control_session/R-4.12`）；
- `0x4301` 的 14 个字段里含 `usbIP/wifiIP/ssid/pass/securityType/channel/port/deviceID/pubKey/srcVer/sdkVer/assetID/assetVer/mutualAuth`（`iap2_control_session/R-9.x`），也就是**媒体面在此之前才开始**。

因此本阶段从"**控制会话与 AirPlay 会话协商出流之后，包在线上长什么样、时钟怎么对、缓冲/丢包/控速怎么设计**"这一点接上。

```text
控制面（RTSP SETUP 协商出流、端口、传输方式）        ← 非本阶段
      ↓
【本阶段】RTP 传输与时序
  ├─ RTP/扩展头字节布局
  ├─ payload type 与流类型映射
  ├─ 时钟：零时刻 / RTP 时基 / 网络时钟
  ├─ 抖动缓冲（水位、迟到、上溢/下溢）
  ├─ 丢包/乱序/重复统计
  └─ 发送节奏（打包数、控速）
      ↓
FairPlay/SRTP 解密、H.264/AAC 解码                  ← 非本阶段
```

**不回答**：FairPlay 密钥与解密流程、H.264/AAC 解码、RTSP 控制面字段全集、iAP2 隧道分片。

## 1. 目标与完成判据

**目标**：给出可复现、逐条可追溯到固件字节的 RTP 传输与时序规范，使第三方平台能：

1. 解析并生成 RTP 包与扩展头；
2. 用固件的时钟口径建立"发送/接收时基 ↔ 播放时刻"的关系；
3. 设计可配置的抖动缓冲；
4. 统计丢包、乱序、重复、迟到；
5. 按时间戳与打包数控制发送节奏；
6. 明确异常与边界，并把无证据点登记为 `OPEN`。

**完成判据（全部满足才算完成）**：

1. §5 的 12 项覆盖要求逐项有固件/汇编依据，或明确标 `OPEN`；
2. `verify.py` 通过（源哈希、`.bin` 与固件切片逐字节一致、头部标记、地址窗口、测试向量重算、`OPEN` 登记与引用闭环、跨 docset 条款可解析）；
3. `STATUS.md` 给出三态统计与采样覆盖率声明；
4. 任何一条 `spec/` 条款都能点回 `analysis/` 的 `A` 编号，该编号能点回 `source/asm/` 的指令地址；
5. 明确写出"**没有真实媒体抓包**"这一事实及其后果（见 §2.2），不得把固件推断写成实测。

## 2. 素材与目标二进制

### 2.1 主目标（本阶段新增，不重新提取 IPSW）

| 项 | 值 |
|---|---|
| 路径（构建内） | `/System/Library/PrivateFrameworks/AirPlaySender.framework/AirPlaySender` |
| 本地路径 | `firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender` |
| 大小 | 4,397,312 B |
| SHA256 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` |
| LC_UUID | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` |
| 函数数（LC_FUNCTION_STARTS） | **11,443** |
| 符号表条目 | 16,928（可用符号 14,277） |
| `__TEXT,__text` | `0x251997a78`–`0x251bdbb08`（大小 2,375,824 B） |

选择理由：该二进制**带真实符号**（`APSRTPPacketHandler*`、`jitterBuffer_*`、`APAudioZeroTimeStampProvider*`、`carAudioStream_getRTPPayloadType` 等），是发送侧（手机→车机）媒体面实现所在，正好对应用户要实现的一端。

### 2.2 关键事实：本仓库**没有**真实媒体抓包

| 已有 | 没有 |
|---|---|
| 3 份 sysdiagnose（22H374 / 23G90 / 21G93），含 `.pklg`（蓝牙 HCI）与 WiFi 状态 | **任何 `pcap`/`pcapng`/RTP/RTCP 媒体抓包** |
| 23G90 蓝牙经典链路的 iAP2 报文转录（`runtime/`，见第三阶段） | Wi-Fi / 有线媒体面的抓包 |

后果与处置：

1. 上游任务书 §1 完成判据 2"至少一份真实媒体抓包，含 RTP/RTCP"**无法满足**，登记为 `OPEN-RUN-1`；
2. 规范中的字节布局一律以**固件指令**为证据（不是"RFC 3550 说应该这样"）；
3. RFC 3550 只作**术语与字段命名参考**，引用时标 `[RFC3550]`，**不得**作为本构建的行为证据；
4. `runtime/` 提供**可直接执行的抓包配方**（`runtime/captures/README.md`），把"缺什么、怎么补"写成可操作步骤，而不是含糊的"待验证"。

### 2.3 次级目标

| 二进制 | 大小 | SHA256 | 用途 |
|---|---|---|---|
| `APTransport` | 1,593,864 B | `e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d` | 传输层（UDP/TCP/QUIC 连接类型常量）交叉核对 |
| `AirPlayReceiver` | 2,453,520 B | 见 `source/metadata/` | **仅**用于接收侧对照，不据其下结论 |

次级目标只允许作交叉核对，结论必须回到 AirPlaySender 的指令地址。

## 3. 方法与证据链（与前三个阶段相同）

1. **固件原始字节**：`macho-meta.py` 定位段/节/函数起点，取原始字节并算 SHA256；
2. **原始 ARM64 汇编**：`export-asm.py`（Capstone 5.0.7）导出，不改写；
3. **Ghidra 自动反编译**：`analyzeHeadless` + `ExportDecomp.java`，只作阅读辅助，标 `DECOMPILED_UNREVIEWED`；
4. **人工对照汇编核对**：每条结论写出指令地址；反编译与汇编冲突时**以汇编为准**；
5. **analysis**：`A` 编号结论 + 未确认点 + 实现影响；
6. **spec**：`R` 编号条款（MUST / SHOULD / 未定义）+ 测试向量 + 一致性清单。

媒体面特有要求：

- **位级布局**：字段必须给出"字节偏移 + 位区间 + 字节序"，并给出**打包/解包两个方向**的指令证据（只有一侧证据时标 `INFERRED`）；
- **符号使用**：带符号的函数可以直接用符号名叙述；符号被剥掉的函数只能写"该地址的真实函数"，**不得**用相邻符号名推测语义；
- **常量来源**：payload type、对象大小、队列容量必须给出来源指令或符号地址；
- **不得**用外部开源实现（shairport-sync 等）反推本构建行为，只能作"外部实现差异"备注且标明未验证。

## 4. 抽样策略

抽样必须**按主题定向**：RTP 头装配、扩展头解析、payload type、时钟锚点、抖动缓冲、丢包/重传、发送节奏。

- 采样率如实声明（已导出 `n / 11,443`），不得暗示全栈覆盖；
- 每个被结论依赖但未读的函数，必须显式标注"未读，结论仅基于调用点"；
- 本阶段的抽样以**符号名清单**（`source/metadata/AirPlaySender/rtp-symbols.txt`，316 条命中）为先验，再按语义簇取函数，避免"随机抽样"造成的遗漏。

## 5. 覆盖要求（12 项，承接上游任务书）

| # | 要求 | 必须回答的问题 | 本阶段对应 analysis |
|---|---|---|---|
| 1 | **RTP 头** | 字段布局、版本、padding、extension、CSRC、marker？ | `01-rtp-header.md` |
| 2 | **扩展头** | profile/length、元素格式、多扩展、填充？ | `01-rtp-header.md`、`02-extended-header.md` |
| 3 | **载荷类型** | payload type 与编解码/流的映射？动态类型如何协商？ | `03-payload-types.md` |
| 4 | **序列号** | 宽度、回绕、重复/乱序判定？ | `04-sequence-and-loss.md` |
| 5 | **时间戳** | 时钟频率、回绕、与 NTP 的关系？ | `05-clock-and-timestamps.md` |
| 6 | **SSRC/流标识** | 多流如何区分？冲突/切换？ | `01-rtp-header.md`、`03-payload-types.md` |
| 7 | **NTP 同步** | 用 SR/其他消息？偏移/延迟如何计算？ | `05-clock-and-timestamps.md` |
| 8 | **抖动缓冲** | 目标延迟、水位、上溢/下溢、动态调整？ | `06-jitter-buffer.md` |
| 9 | **丢包处理** | 丢包检测、concealment、重传/不重传？ | `04-sequence-and-loss.md` |
| 10 | **统计** | 丢包率、乱序率、重复率、迟到率的定义与窗口？ | `04-sequence-and-loss.md`、`06-jitter-buffer.md` |
| 11 | **流量控速** | 发送节奏、令牌桶、拥塞/背压？ | `07-pacing.md` |
| 12 | **异常与版本** | 超时、断流、时钟跳变、不同车机差异？ | `08-anomalies.md` |

### 5.1 `analysis/` 文件划分（约定，实际以目录为准）

| 文件 | 内容 |
|---|---|
| `00-method-and-environment.md` | 方法、工具链、可复现命令、抽样策略、证据分级 |
| `01-rtp-header.md` | 12 字节固定头、序列号/时间戳/SSRC 偏移、头长公式 |
| `02-extended-header.md` | 扩展元素 1/4 字节两态、位域、打包与解包 |
| `03-payload-types.md` | 4CC → payload type 表、buffered 变体映射 |
| `04-sequence-and-loss.md` | 序列号队列、丢包/乱序/重复判定 |
| `05-clock-and-timestamps.md` | 零时刻提供者、RTP 时基、网络时钟 |
| `06-jitter-buffer.md` | 缓冲接口、水位、迟到丢弃、统计属性 |
| `07-pacing.md` | 打包数、发送节奏、背压 |
| `08-anomalies.md` | 断流、时钟跳变、错误码 |
| `A-conclusions.md` | 结论登记表：`spec` 的 `依据` 只允许引用这里的 `A` 编号 |

### 5.2 `spec/` 文件划分（约定）

| 文件 | 条款区间 |
|---|---|
| `00-scope-and-terms.md` | `R-0.x` 范围与术语 |
| `01-rtp-format.md` | `R-1.x` 固定头与扩展头 |
| `02-clock-sync.md` | `R-2.x` 时基与播放时刻 |
| `03-jitter-buffer.md` | `R-3.x` 缓冲设计 |
| `04-loss-stats.md` | `R-4.x` 丢包与统计 |
| `05-pacing.md` | `R-5.x` 发送节奏 |
| `06-client-guide.md` | `R-6.x` 客户端施工指南 + 探测实验 |
| `07-conformance-checklist.md` | 一致性清单 + 不得声称的事项 |
| `08-open-items.md` | `OPEN` 索引与关闭条件 |

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 原始二进制引用与哈希、每函数 `.s` + `.bin` + `index.json`、Mach-O 元数据、Ghidra 请求 |
| `readable/` | 与 `source/asm/` 一一对应的自动反编译，全部带"未人工确认" |
| `analysis/` | 逐主题：地址、数据流、每条结论的固件依据/未确认点/实现影响 |
| `spec/` | 平台无关条款（编号唯一）、每章"本章依据"表、测试向量、一致性清单 |
| `runtime/` | 抓包配方与回放工具（**没有**真实抓包，见 §2.2） |
| `reference-impl/` | 解析器 + 抖动缓冲参考实现 + 测试向量（必须能被 `verify.py` 重算） |
| `manifest.json` | 全量文件哈希、12 项状态、`OPEN` 索引 |
| `function-index.json` | 每个导出函数的地址/大小/哈希/被引用位置 |
| `verify.py` | 自动校验（见 6.1） |
| `STATUS.md` | 三态统计、采样覆盖率、能否指导实现的结论 |

### 6.1 `verify.py` 至少校验

1. 源二进制 SHA256 与 `manifest.json` 一致；
2. 每个 `.bin` 与源二进制对应区间**逐字节**相同；
3. `.s` 头部含正确地址区间、源哈希、"未人工确认"标记；
4. 文档引用的地址都落在镜像窗口内（按 `source/metadata/AirPlaySender/segments.json` 的段区间计算）；
5. 用固件常量**重新计算**测试向量（扩展元素位域、打包数→头长、payload type 表），与 `spec/` 一致；
6. `spec/` 条款编号唯一、每条有 `依据：`、被引用的 `A` 编号在 `analysis/A-conclusions.md` 存在；
7. 每个 `OPEN-*` 既在 `spec/08-open-items.md` 登记、又在正文被引用；
8. `reference-impl/` 的向量文件能被重新计算且与 `spec/` 数值一致。

## 7. 状态报告要求（`STATUS.md`）

1. 12 项覆盖要求逐项状态：**已确认 / 部分确认 / OPEN**，以及证据强度；
2. 采样覆盖率声明（`n / 11,443`），并明确"不构成全栈覆盖"；
3. 强制实现决策（打包数上限、头长公式、扩展元素两态、PT 表、时钟口径）逐条列出规范默认值与依据；
4. **不得**在任一项仍为 `OPEN` 时宣称"已完成"，只能写"部分完成 + 剩余项清单"。

## 8. 严禁事项

1. 不得修改 `source/` 下任何文件；不得把反汇编改写为伪代码充当"原始汇编"。
2. 不得把 Ghidra 反编译输出直接当作结论依据；不得省略"人工对照汇编核对"。
3. 不得引用旧分析、旧伪代码、外部文档、开源实现作为**确认依据**（可作线索，必须标注）。
4. 不得用不同构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、操作系统 API。
6. 不得静默覆盖与旧材料冲突的结论——冲突必须显式记录。
7. 不得把"能收包/能解析"写成"能正确播放"。

## 9. 工具与环境

| 工具 | 版本/路径 | 用途 |
|---|---|---|
| Ghidra | 12.1.4（`firmware/tools/ghidra/support/analyzeHeadless`，WSL 下运行） | headless 反编译 |
| JDK | 21 | Ghidra 依赖 |
| Capstone | 5.0.7 | 汇编导出（`export-asm.py`） |
| Python | 3.13.3 | 工具链与校验 |

## 10. 验收方式

```bash
cd D:\carvex-research\research\protocol\airplay_rtp_timing
python3 verify.py
# 期望：失败 0；检查项总数写进 STATUS.md 与 manifest.json
```

验收时同时检查：

- `STATUS.md` 第 1 节 12 项状态与 `manifest.json` 的 `coverage` 完全一致；
- 每个 `OPEN` 都能在 `manifest.json` 找到 `id` 与所在文件；
- 随机抽 3 条规范条款，能沿 `spec → analysis → source/asm` 逐级点回；
- 随机抽 1 条跨 docset 引用，能在对应 docset 的 `spec/` 找到原文。
