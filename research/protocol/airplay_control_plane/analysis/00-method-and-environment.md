# 00 · 方法与运行环境

> 本文定义本阶段"什么算证据"。后面每一章的结论都按这里的口径编号。

## 0.1 阶段边界

本阶段回答"设备（模拟 iPhone）如何与车机建立 AirPlay 控制通道并把它推进到可交接状态"：

1. TCP 控制连接怎么建（端口来源、连接、保持、断开）；
2. RTSP/1.0 消息在线上的字节布局（请求行、头、`CSeq`、`Content-Length`、body）；
3. Pair-Setup / Pair-Verify 两条消息的字段、编码、密码学操作与状态机；
4. 控制面加密会话如何派生密钥、从哪条消息开始生效；
5. RTSP 方法集与 `SETUP` 的 `streams`/`type` 参数；
6. `type=130` 隧道的发起、字段位置与交接点。

**不回答**：FairPlay 帧级密钥、RTP/RTCP 时序、音视频编解码、`type=130` 隧道内部的 iAP2 语义（分别属后续阶段）。

## 0.2 三类证据

| 级别 | 含义 | 记法 |
|---|---|---|
| `CONFIRMED` | 能在本 docset 的原始字节 + 指令上复核：给出镜像、地址、指令 | `A` 结论 + 地址 |
| `INFERRED` | 由多条已确认事实推出，但没有直接指令证明该结论 | 必须写"推断"并列出前提 |
| `OPEN` | 证据不足；登记为 `OPEN-AP-n` | 不得写成规范 |

符号名（`SetupClientExchange` 等）只用于**定位**。符号存在说明"这里有个函数"，不说明它做什么；结论必须落到指令。

## 0.3 镜像与哈希

本阶段首次跨三个镜像取证。三者同属 24A446 / iPhone18,1，均未加密、均保留符号表。

| 镜像 | 本地路径 | 大小 (B) | SHA256 | LC_UUID | 函数起点 | 符号 |
|---|---|---|---|---|---|---|
| `AirPlaySender` | `source/firmware/AirPlaySender` | 4,397,312 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` | 11,443 | 14,277 |
| `APTransport` | `source/firmware/APTransport` | 1,593,864 | `e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d` | `14228b3f-1df6-308b-97c4-b7574dbd7a97` | 5,367 | 7,013 |
| `CoreUtils` | `source/firmware/CoreUtils` | 2,232,432 | `3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083` | `364444ca-d8b8-3a37-98b3-3b012ab1a517` | 5,789 | 9,783 |

地址窗口（`__TEXT` 起点，来自各镜像 `segments.json`）：

| 镜像 | `__TEXT` vmaddr | 大小 |
|---|---|---|
| `AirPlaySender` | `0x251996000` | `0x2e4000` |
| `APTransport` | `0x24fd8b000` | `0xf0000` |
| `CoreUtils` | `0x18be31000` | `0x150000` |

三个镜像都是 dyld 共享缓存里的 dylib，地址即缓存内地址；`.bin` 切片按 `__TEXT` 的 `fileoff`（均为 0）与 `vmaddr` 换算。

## 0.4 抽样

| 镜像 | 采样函数 | 占函数起点 |
|---|---|---|
| `AirPlaySender` | 20 | 0.17 % |
| `APTransport` | 16 | 0.30 % |
| `CoreUtils` | 30 | 0.52 % |
| 合计 | 66 | 0.29 % |

抽样按主题定向（RTSP 帧 / 配对 / 密钥派生 / 连接与加密切换 / 流与 SETUP）。**这不是全栈覆盖**：66 个函数里任何一个的 callee 只要没有单独导出，就属于"未读"，相关结论必须写明"仅基于调用点"。函数清单与状态见 `11-function-inventory.md`。

## 0.5 工具链

| 步骤 | 工具 | 产出 |
|---|---|---|
| 元数据 | `firmware/tools/macho-meta.py` | `source/metadata/<镜像>/{summary,segments,symbols,function-starts}.json` |
| 选函数 | `tools/…`（手工 + `selection.json`） | `source/metadata/<镜像>/selection.json` |
| 汇编/字节 | `firmware/tools/export-asm.py` | `source/asm/<镜像>/f_<addr>.{s,bin}` + `index.json` |
| 反编译 | Ghidra 12.1.4 headless + `firmware/tools/ghidra-scripts/ExportDecomp.java` | `readable/ghidra/<镜像>/f_<addr>.ghidra.c` |
| 字符串定址 | `tools/dump-addr.py`（地址→ASCII） | 地址 ↔ 字符串 |
| 函数内字符串 | `tools/asm-strings.py`（解析 `.s` 里的 ADRP+ADD） | 指令地址 ↔ 字符串 |
| 交叉引用 | `tools/find-xrefs.py` | ADRP(+ADD/LDR) 引用点 |
| 4CC 表提取 | `tools/extract-4cc-table.py` | 类型 → (方法, 路径, Content-Type) |

可复现命令（Windows 侧）：

```powershell
python3 firmware/tools/macho-meta.py <镜像路径> research/protocol/airplay_control_plane/source/metadata/<镜像>
python3 firmware/tools/export-asm.py research/protocol/airplay_control_plane/source/firmware/<镜像> `
    research/protocol/airplay_control_plane/source/metadata/<镜像> `
    research/protocol/airplay_control_plane/source/metadata/<镜像>/selection.json `
    research/protocol/airplay_control_plane/source/asm/<镜像>
```

Ghidra（WSL root，一次导入三个镜像）：

```bash
bash /mnt/d/carvex-research/research/protocol/airplay_control_plane/tools/import-ghidra.sh
```

导出反编译（每个镜像一次）：

```bash
./firmware/tools/ghidra/support/analyzeHeadless \
  firmware/analysis/24A446/airplay-control/project airplay -process <镜像> -noanalysis \
  -scriptPath firmware/tools/ghidra-scripts -postScript ExportDecomp.java \
  research/protocol/airplay_control_plane/source/metadata/<镜像>/ghidra-request.json \
  research/protocol/airplay_control_plane/readable/ghidra/<镜像>
```

## 0.6 运行时候选证据的边界

本阶段**没有** 24A446 的 AirPlay 控制面抓包（pcap）。

现有的运行期材料只有 23G90（iOS 26.x）的蓝牙 iAP2 抓包与 sysdiagnose，它们能证明"控制面之前"发生的事（`0x1D00/0x1D01/0x1D02`、`0xAA00/0xAA01/0xAA02/0xAA03/0xAA05/0xAA06`），**不能**证明 AirPlay 控制面的任何字段、端口或状态码。因此：

- 第 10 章只登记"有哪些运行期材料、它们覆盖到哪、缺什么"；
- 任何"车机实际接受/拒绝"的问题一律 `OPEN`，不得用 23G90 的 iAP2 行为外推。

## 0.7 与旧材料的隔离

`D:\ios-carplay\docs\wireless-phone-host\` 下有同构建（24A446）的旧分析。它只用来**缩短定位时间**：旧文给出候选地址，本 docset 从原始字节重新确认。旧文的行号、结论、分级都不直接引用；若本 docset 的结论与旧文冲突，以本 docset 的字节为准并在对应 `A` 结论里记"旧文不同"。

## 0.8 更正日志

- `C-1`：初次扫描用 `(follow & 0xFFC003FF) == 0x91000000` 匹配 `ADD` 立即数，导致所有字符串交叉引用都查不到——该掩码把 `Rn/Rd` 也包进去了。已改为 `(follow & 0xFF800000) == 0x91000000` 并单独判断 `Rn`，见 `tools/find-xrefs.py`。这是工具 bug，不是固件事实。
