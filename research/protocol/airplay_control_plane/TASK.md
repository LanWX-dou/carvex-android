# AirPlay 控制面阶段 — 任务要求（`airplay_control_plane`）

> 本文件是第四阶段的任务书（docset 内版本），上游任务书是 `research/protocol/airplay_control_plane.md`。
> 目标：在 mDNS 发现之后，用与前三阶段相同的严格证据链，产出 **AirPlay 控制通道（TCP + RTSP + 配对 + 加密会话 + SETUP/`type=130` 隧道交接）** 的平台无关规范。
>
> 口径：`CONFIRMED` 只表示"在本阶段证据范围内可复核"，不表示 Apple 官方规范；`INFERRED` 必须标推断；无证据一律 `OPEN`。

---

## 0. 阶段定位（与前后阶段的衔接）

```text
Bluetooth Classic → iAP2 Link → Control Session → 0x4301（Wi-Fi 凭据/wifiIP/port）
                                                       ↓
                              mDNS 发现（airplay_mdns_discovery）
                                                       ↓
【本阶段】AirPlay 控制通道：TCP 端口（来源：SRV 或 `0x4301`；**7000 仅为样本观测值，不得写死**）→ Pair-Setup/Verify → 加密会话
          → RTSP 方法集 → SETUP（含 type=130 隧道）→ 交接
                                                       ↓
                        RTP 媒体 / FairPlay 帧加密 / iAP2 隧道（后续阶段）
```

与前序 docset 的关系：

- `iap2_control_session`：`0x4301` 给出 Wi-Fi 凭据与端口，是本阶段的前置；其 `OPEN-SES-2`（参数 ID→字段映射）仍未闭合，**不得**把 `0x4301` 的字段当作已确认输入；
- `iap2_link_establish`：只有本阶段把 `type=130` 隧道交给 iAP2 之后，链路层才出现；本阶段只写到"交接点"，不写隧道内 iAP2 语义；
- `airplay_mdns_discovery`（任务书）：提供 `_airplay._tcp` 实例、SRV 端口、TXT `features`/`pk`/`deviceid`；本阶段**只用其输出**，不重复取证 mDNS。

## 1. 目标与完成判据

**目标**：给出可复现、逐条可追溯的 AirPlay 控制面规范，使第三方客户端能完成：

1. 连接车机 AirPlay 控制端口（TCP，端口来源：SRV 或 `0x4301`）；
2. 完成 Pair-Setup / Pair-Verify（TLV8 / SRP / Curve25519 / Ed25519，按固件实际方言）；
3. 建立控制面加密会话（AEAD 记录层，密钥/上下文/计数器分离）；
4. 发出/解析 RTSP 请求与响应（方法、路径、`CSeq`、`Content-Length`、body 编码）；
5. 解析 `SETUP` 的 `streams`/`type`/端口，识别 `type=130` 隧道；
6. 把隧道交接给 iAP2（只写到交接点），并给出失败、超时、重试分支。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求（第 5 节）逐项有固件/汇编依据，或明确标 `OPEN`；
2. `verify.py` 通过（镜像哈希、`.bin` 与镜像切片逐字节一致、头部标记、A/R 编号、OPEN 登记、跨 docset 引用）；
3. `STATUS.md` 给出"已确认/部分确认/OPEN"三态统计与采样覆盖率；
4. 任一 `R` 条款能点回 `analysis/` 的 `A` 结论，`A` 能点回 `source/asm/` 的地址与字节；
5. 引用前序阶段条款时带前缀（`link/R-x.y`、`cs/R-x.y`），且能在对应 docset 找到；
6. 未取证字段（尤其 `type=130` 载荷语义、加密前后的消息差异、真实车机接受度）一律 `OPEN`。

## 2. 素材与目标二进制

**本阶段首次采用多镜像证据链**（前三阶段只用一个 `accessoryd`）。三个镜像同属 24A446 / iPhone18,1：

| 角色 | 镜像 | 大小 (B) | SHA256（前 16 位） | LC_UUID | 函数起点 | 符号 |
|---|---|---|---|---|---|---|
| AirPlay 发送端（客户端主逻辑） | `AirPlaySender` | 4,397,312 | `304b8a4a688028f5` | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` | 11,443 | 14,277 |
| 传输/HTTP 引擎 | `APTransport` | 1,593,864 | `e277719a95de2583` | `14228b3f-1df6-308b-97c4-b7574dbd7a97` | 5,367 | 7,013 |
| 通用库（HTTP 消息、配对、SRP、TLV8、AEAD） | `CoreUtils` | 2,232,432 | `3968b52b962def4a` | `364444ca-d8b8-3a37-98b3-3b012ab1a517` | 5,789 | 9,783 |

定位（构建内）：

- `/System/Library/PrivateFrameworks/AirPlaySender.framework/AirPlaySender`
- `/System/Library/PrivateFrameworks/APTransport.framework/APTransport`
- `/System/Library/PrivateFrameworks/CoreUtils.framework/CoreUtils`

**为什么是这三个**：`AirPlaySender` 是客户端（发送端）编排层；`APTransport` 是 RTSP/HTTP 连接与包编解码；`CoreUtils` 是配对会话（`SetupClientExchange`/`VerifyClientExchange`）、SRP、TLV8、ChaCha20-Poly1305 的实现处。三者都以**符号表完好**的形式存在，函数名可直接作为定位入口，但**符号名不等于语义**——语义仍以指令为准。

**不作为主证据**：`carkitd`、`CarPlay`、`airplayd`、`AirPlayReceiver`、`MFAAuthentication`、`Security`、`libcorecrypto`。只在交叉核对时引用，且不得据其下结论。

## 3. 方法与证据链（与前三阶段相同）

1. **原始字节**：`macho-meta.py` 导出段表/符号/函数起点；原始镜像按 SHA256 固定；
2. **原始 ARM64 汇编**：`export-asm.py`（Capstone 5.0.7）按函数起点切出 `.s` + `.bin`，不改写；
3. **Ghidra 反编译**：只作阅读辅助，输出标 `RAW_DECOMPILER_OUTPUT_UNREVIEWED`；
4. **人工对照汇编核对**：每条结论写出**指令地址**；只引用符号名不算证据；
5. **analysis**：`A` 编号结论 + 未确认点 + 实现影响；
6. **spec**：`R` 编号条款（MUST / SHOULD / 未定义）+ 测试向量 + 一致性清单。

本阶段特有要求：

- **方向**：所有条款必须写明"设备→车机"还是"车机→设备"；同一方法在两侧语义不同的，分条写；
- **字节级**：状态行/请求行、头字段、TLV 类型/长度、AEAD 记录边界必须给字节样例或精确布局；
- **加密边界**：控制面 AEAD、媒体帧 AEAD、隧道内载荷是**三个不同层次**，不得混写；
- **`type=130`**：只写"由谁发起、在哪个字段、值是多少、交接后字节归谁"；载荷内部语义属后续阶段。

## 4. 抽样策略

- 抽样**按主题定向**：RTSP 帧、配对两条消息、密钥派生、连接/加密切换、SETUP 与流登记、隧道交接；
- 采样率如实声明（`n / 11,443` 等），不得暗示全栈覆盖；
- 被结论依赖但未读的函数，必须显式标注"未读，结论仅基于调用点"；
- 每个镜像的采样单独计数。

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **控制通道建立** | TCP 端口来源？是否 TLS？连接时序、保持、断开？ |
| 2 | **RTSP 消息格式** | 请求行/状态行、headers、大小写、`CSeq`、`Content-Length`、body 类型与编码？ |
| 3 | **Pair-Setup** | 方法名、路径、字段、编码、密码学操作、成功/失败响应？ |
| 4 | **Pair-Verify** | 字段、挑战/签名、公钥、证书、状态机、失败分支？ |
| 5 | **加密会话** | 会话密钥如何产生/标识？哪些消息加密？加密边界在哪？ |
| 6 | **RTSP 方法集** | 实际出现哪些方法？各自请求/响应字段与副作用？ |
| 7 | **SETUP 传输参数** | `streams`/`type`/端口/协议；`type=130` 的位置与含义？ |
| 8 | **type=130 隧道交接** | 谁发起？携带什么？交接后控制面/隧道各自负责什么？ |
| 9 | **错误与状态码** | RTSP 状态码、配对错误、加密失败如何表示？客户端如何分类？ |
| 10 | **超时与重试** | 各阶段超时、重试次数、退避、何时放弃？ |
| 11 | **安全边界** | 配对是否认证车机？中间人、重放、降级如何处理？ |
| 12 | **版本与差异** | AirPlay 1/2、CarPlay、不同车机的字段/方法差异？ |

## 6. 交付物与目录（实际）

```text
research/protocol/airplay_control_plane/
  analysis/
    00-method-and-environment.md
    01-control-channel-and-rtsp.md
    02-pair-setup.md
    03-pair-verify.md
    04-encrypted-session.md
    05-rtsp-methods.md
    06-setup-and-type130.md
    07-tunnel-handoff.md
    08-errors-timeouts.md
    09-security.md
    10-runtime-captures.md
    11-function-inventory.md
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
  source/
    firmware/{AirPlaySender,APTransport,CoreUtils}
    metadata/<镜像>/{summary,segments,symbols,function-starts,selection,ghidra-request}.json
    asm/<镜像>/{f_<addr>.s,f_<addr>.bin,index.json}
  readable/ghidra/<镜像>/f_<addr>.ghidra.c + .json
  runtime/            # 观测（本阶段只有 23G90 蓝牙抓包，不含 AirPlay 控制面）
  reference-impl/     # 解析器/状态机参考实现（不含密钥材料）
  tools/              # 本 docset 新增脚本（find-xrefs、导入、清单）
  verify.py
  STATUS.md
  manifest.json
```

## 7. 状态报告要求（`STATUS.md`）

1. 12 项覆盖要求的逐项状态：**已确认 / 部分确认 / OPEN**，以及证据强度（"指令+字节" > "符号+调用点" > "运行时候选"）；
2. **采样覆盖率**：每个镜像的 `n / 函数总数`，并声明"不构成全栈覆盖"；
3. 强制实现决策（端口缺省、超时、重试、密钥长度/标签、计数器宽度）逐条列默认值与依据；
4. **不得**在任一项仍为 OPEN 时宣称"已完成"，只能写"部分完成 + 剩余项清单"。

## 8. 严禁事项

1. 不得修改 `source/firmware/` 下任何镜像；不得把反汇编改写为伪代码充当"原始汇编"。
2. 不得把 Ghidra 输出直接当结论；不得省略人工对照汇编。
3. 不得引用旧分析、旧伪代码、外部文档、开源实现作为**确认依据**（可作线索，必须标注）。
4. 不得用其它构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、操作系统 API（`appendHeader` 之类实现名只能出现在 `analysis/`）。
6. 不得把"配对成功"写成"媒体可播放"；不得把"控制面 SETUP 成功"写成"CarPlay 可用"。

## 9. 既有线索的处理

| 线索 | 位置 | 处理方式 |
|---|---|---|
| 旧 AirPlay 静态分析 | `D:\ios-carplay\docs\wireless-phone-host\` | **只作线索**；每条结论在本 docset 重新取证 |
| 旧反编译缓存 | `D:\ios-carplay\analysis\` | 同上，不引用行号 |
| `firmware/analysis/24A446/*` | 本仓库其它阶段 | 只作交叉核对；引用须标 `INFERRED` |
| 23G90 sysdiagnose / 蓝牙抓包 | `research/protocol/iap2_control_session/runtime/` | 只证明"控制面之前的 iAP2 阶段"，不含 AirPlay 控制面 |

## 10. 工具与环境

| 工具 | 版本/路径 | 用途 |
|---|---|---|
| Capstone | 5.0.7 | 汇编导出（`firmware/tools/export-asm.py`） |
| Ghidra | 12.1.4（`firmware/tools/ghidra/support/analyzeHeadless`） | headless 反编译（WSL root） |
| JDK | 21 | Ghidra 依赖 |
| Python | 3.12/3.13 | 工具链与校验 |

## 11. 验收方式

```bash
cd D:\carvex-research\research\protocol\airplay_control_plane
python3 verify.py
# 期望：失败 0
```

验收时同时检查：

- `STATUS.md` 第 1 节 12 项状态与 `manifest.json` 的 `items` 一致；
- 每个 `OPEN` 能在 `manifest.json`/`coverage.json` 找到 `id` 与所在文件；
- 随机抽 3 条 `R` 条款，能沿 `spec → analysis → source/asm` 逐级点回；
- 随机抽 2 条前序引用（`link/R-*`、`cs/R-*`），能在对应 docset 找到原文。

## 12. 一句话

**本阶段只做"连上控制通道、完成配对与加密会话、用 RTSP SETUP 把流/隧道协商出来"；帧加密、RTP、音视频和 iAP2 分片都不在本阶段。**
