# 00 — 方法与环境

> 本文件定义本阶段（`airplay_rtp_timing`）的取证方法与可复现命令。所有 `analysis/` 结论、`spec/` 条款都必须能沿本文的链回到固件字节。

---

## 0.1 一句话

**目标是"包长什么样、时钟怎么对、缓冲怎么算"，不是"视频能不能播"。** 每一条字节级结论都要能指到一条 ARM64 指令地址；指不到就写 `OPEN`。

## 0.2 证据分级

| 级别 | 含义 | 使用规则 |
|---|---|---|
| `CONFIRMED` | 指令序列直接证明（写入的偏移、常量、分支条件） | 可直接进 `spec/` 作 MUST |
| `INFERRED` | 指令证明"做了什么"，但"为什么"靠上下文推断 | 进 `spec/` 必须写 `SHOULD` 或标注推断 |
| `OPEN` | 无证据或证据不足 | 只能进 `spec/08-open-items.md` 与正文的"未定义"条款 |
| `[RFC3550]` | 仅为术语/字段命名参考 | **不得**作为本构建行为证据 |
| `DECOMPILED_UNREVIEWED` | Ghidra 输出 | 只能作阅读辅助；与汇编冲突时以汇编为准 |

## 0.3 目标二进制

| 项 | 值 |
|---|---|
| 构建 | `24A446`（iOS 27.0.1，`iPhone18,1`） |
| 主目标 | `/System/Library/PrivateFrameworks/AirPlaySender.framework/AirPlaySender` |
| 本地路径 | `firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender` |
| 大小 | 4,397,312 B |
| SHA256 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` |
| LC_UUID | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` |
| LC_FUNCTION_STARTS | 11,443 |
| 符号表 | 16,928 条原始项 / 14,277 条可用项 |

段布局（`source/metadata/AirPlaySender/segments.json`，由 `macho-meta.py` 解出）：

| 段 | 起始 | 结束 |
|---|---|---|
| `__TEXT` | `0x251996000` | `0x251c7a000` |
| `__TEXT,__text` | `0x251997a78` | `0x251bdbb08` |
| `__DATA_CONST` | `0x2693e4770` | `0x2693f0770` |
| `__DATA` | `0x26e7d9040` | `0x26e7f5040` |
| `__AUTH` | `0x2719e6ec8` | `0x2719eaec8` |
| `__AUTH_CONST` | `0x276124870` | `0x276144870` |
| `__DATA_DIRTY` | `0x27097a750` | `0x27097e750` |

**地址窗口规则**：文中出现的任何 `0x25…`/`0x26…`/`0x27…` 地址必须落在上表某一区间内，由 `verify.py` 第 4 项检查。

次级目标（只作交叉核对，不据其下结论）：

| 二进制 | 大小 | SHA256 |
|---|---|---|
| `APTransport` | 1,593,864 B | `e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d` |
| `AirPlayReceiver` | 2,453,520 B | `source/metadata/AirPlayReceiver/summary.json` |

## 0.4 为什么选 AirPlaySender

1. 它**带真实符号**：`APSRTPPacketHandlerComposeRTPPacketWithBBuf`、`APSRTPPacketHandlerReadExtendedHeader`、`jitterBuffer_*`、`APAudioZeroTimeStampProvider*`、`carAudioStream_getRTPPayloadType` 等 316 条与 RTP/时序相关的符号可直接作函数语义锚点（清单：`source/metadata/AirPlaySender/rtp-symbols.txt`）。
2. 它是**发送侧**（手机 → 车机）实现，与本项目要交付的客户端同侧。
3. 属性 `CFBundle` 之外还有完整 `__objc_methname`，可用于交叉确认属性名（如 `kAPSenderSessionStreamKey_DisableRetransmits`）。

**符号使用纪律**：有符号的函数直接用符号名叙述；**被剥掉符号的函数只能写"地址 `0x…` 处的真实函数"**，不得用相邻符号名推断语义（与前一阶段 `A05.x` 的纪律一致）。

## 0.5 工具链与可复现命令

所有命令在仓库根目录 `D:\carvex-research` 执行。

```powershell
# 1) Mach-O 元数据（段表/函数起点/符号/哈希）
python3 firmware\tools\macho-meta.py ^
  "firmware\extracted\24A446\binaries\AirPlaySender\AirPlaySender" ^
  docs\airplay_rtp_timing\source\metadata\AirPlaySender

# 1b) 符号关键字过滤（脚本内已固定二进制与符号表路径，重定向到 rtp-symbols.txt）
python3 firmware\tools\filter-symbols-rtp.py > docs\airplay_rtp_timing\source\metadata\AirPlaySender\rtp-symbols.txt

# 2) 按符号选函数，导出原始汇编 + 原始字节python3 firmware\tools\export-asm.py ^
  "firmware\extracted\24A446\binaries\AirPlaySender\AirPlaySender" ^
  docs\airplay_rtp_timing\source\metadata\AirPlaySender ^
  docs\airplay_rtp_timing\source\metadata\AirPlaySender\selection.json ^
  docs\airplay_rtp_timing\source\asm\AirPlaySender

# 3) Ghidra 反编译（只作阅读辅助；WSL 下运行）
wsl bash /mnt/d/carvex-research/firmware/tools/run-ghidra-airplay-rtp.sh

# 4) 元数据 → manifest → 校验
python3 firmware\tools\gen-function-index.py docs\airplay_rtp_timing   # 若脚本可用
python3 firmware\tools\gen-manifest-rtp.py docs\airplay_rtp_timing
cd docs\airplay_rtp_timing; python3 verify.py
```

| 工具 | 版本 | 角色 |
|---|---|---|
| `macho-meta.py` | 仓库内 | 段/节/加载命令/函数起点/符号 |
| `filter-symbols-rtp.py` | 仓库内 | 按 RTP/时序关键字过滤符号，产出 `rtp-symbols.txt` |
| `export-asm.py` | Capstone 5.0.7 | 原始 ARM64 汇编 + 原始字节（不改写） |
| `analyzeHeadless` + `ExportDecomp.java` | Ghidra 12.1.4 | 反编译，标 `DECOMPILED_UNREVIEWED` |
| `gen-manifest-rtp.py` | 仓库内 | 全量文件哈希 + `OPEN` 索引 |
| `gen-function-index-rtp.py` | 仓库内 | 每函数地址/大小/哈希/被引用位置 |
| `verify.py` | 本 docset | 自动校验 10 类不变量 |

## 0.6 抽样策略与声明

- **先验清单**：按 RTP/时序关键字扫符号，得 316 条命中（`rtp-symbols.txt`），再按语义簇取函数，避免随机抽样漏掉整簇；
- 本阶段导出 **20 个函数**（`source/asm/AirPlaySender/index.json`，含装配函数的两条调用路径所在函数）；
- 采样率：`20 / 11,443 ≈ 0.17 %`（后续轮次按主题扩充并同步更新本数字与 `manifest.json`）；
- **不构成全栈覆盖**。任何"全部消息/全部路径已确认"的表述都是错的。

已导出但**尚未参与任何结论**的函数（`function-index.json` 的 `cited_by` 为空，共 6 个）：

`_APSRTPPacketHandlerCreate`、`_APSRTPPacketHandlerReturnComposedBBuf`、`_jitterBuffer_SetProperty`、`_jitterBuffer_CopyProperty`、`_APAudioSinkJitterBufferCreate`、`_carAudioStream_processOneInputDataMessage`。

其中 `_APSRTPPacketHandlerCreate` 的对象布局（对象大小 `0x6a8`、模式位 `+0x18`、合并数 `+0x1c`、队列 `+0x68`/`+0x680`）已在 `A01.5`、`A02.1`、`A02.6` 中作为"合并数来源"被间接使用，尚未展开成独立小节；其余 5 个在正文引用前**不得**据其符号名下任何结论。

## 0.7 证据缺口（本阶段的结构性限制）

| 缺口 | 影响 | 登记 |
|---|---|---|
| 仓库内**没有**任何 `pcap`/`pcapng` 媒体抓包 | 线上字节只能由固件装配逻辑推出，缺少"实测比对" | `OPEN-RUN-1` |
| 没有 24A446 的运行期日志 | 无法用日志确认运行期取值（如实际 payload type 协商结果） | `OPEN-RUN-2` |
| 控制面（RTSP SETUP）不在本阶段 | payload type / 端口 / 传输方式的**协商结果**只能引用控制面阶段结论，暂时空缺 | `OPEN-RTP-9` |

抓包配方写在 `runtime/captures/README.md`：写明要抓什么、过滤条件、如何判定成功，做到"补证据有明确动作"，而不是"待验证"。

## 0.8 编号与引用约定

- `A` 编号：`analysis/A-conclusions.md` 登记，形如 `A01.3`（`A01` = `01-rtp-header.md`）；
- `R` 编号：`spec/` 条款，形如 `R-1.4`，全 docset 唯一；
- `OPEN` 编号：`OPEN-RTP-n`（线上格式）、`OPEN-CLK-n`（时钟）、`OPEN-JIT-n`（缓冲）、`OPEN-LOS-n`（丢包）、`OPEN-PAC-n`（控速）、`OPEN-RUN-n`（运行期/抓包）；
- 跨 docset 引用必须带前缀，且前缀必须是本仓库已存在的 docset 目录名（如 `iap2_link_establish/R-6.9`、`iap2_control_session/R-4.12`），由 `verify.py` 第 6 项解析。
