# analysis/00 — 方法与环境

本文件记录本阶段的证据链、工具链、可复现命令、抽样策略与已知失真。所有后续文件的结论都按本文件的规则标注。

## 0.1 证据链

```
固件原始 bytes  →  原始 ARM64 汇编（Capstone，不重写）  →  Ghidra 自动反编译（原样保留）
      →  人工对照汇编核对（逐条写地址/字节）  →  analysis  →  spec（平台无关条款）
```

- 原始字节：`source/firmware/accessoryd`（SHA256 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`）。
- 原始汇编：`source/asm/accessoryd/f_<addr>.s`，每文件头部两行固定为镜像名/地址区间/源哈希/工具版本；指令区为 Capstone `CS_ARCH_ARM64` 输出，**未做任何改写**（含 `skipdata=True` 的数据块原样保留为 `.byte` 形式）。
- 原始字节切片：同目录 `f_<addr>.bin`，与固件对应区间逐字节相同（`verify.py` 校验）。
- Ghidra 输出：`readable/ghidra/accessoryd/f_<addr>.ghidra.c`，头部含地址、源哈希、`DECOMPILED_UNREVIEWED`；**只作阅读辅助**。
- Ghidra 与汇编冲突时以汇编为准，并在本文件 0.4 记录差异类型。

## 0.2 目标二进制

| 项 | 值 | 来源 |
|---|---|---|
| 构建内路径 | `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` | IPSW 解包目录 |
| 大小 | 4,330,752 B | `source/metadata/summary.json` |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` | 同上 |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` | `LC_UUID`（`load-commands.json`） |
| LC_ENCRYPTION_INFO | 无 | `summary.json.encryption = null` |
| `LC_FUNCTION_STARTS` 起点数 | 8,706 | `function-starts.json` |
| `LC_SYMTAB` 符号条目 | 52,443（含未定义/重复） | `symbols.json` |

段表（`source/metadata/segments.json`）：

| 段 | vmaddr | vmsize | fileoff | filesize |
|---|---|---|---|---|
| `__PAGEZERO` | `0x0` | `0x100000000` | 0 | 0 |
| `__TEXT` | `0x100000000` | `0x218000` | `0x0` | `0x218000` |
| `__DATA_CONST` | `0x100218000` | `0x14000` | `0x218000` | `0x14000` |
| `__DATA` | `0x10022c000` | `0x14000` | `0x22c000` | `0x14000` |
| `__LINKEDIT` | `0x100240000` | `0x1e4000` | `0x240000` | `0x1e1500` |

**镜像地址窗口**：`0x100000000`–`0x102180000`（`__TEXT` 起点 + 大小）。`verify.py` 用它校验所有被引用地址。

## 0.3 符号表：本阶段最重要的素材差异

与蓝牙阶段（`bluetoothd` 无符号、按字符串与调用关系倒推）不同，本二进制**保留了本地符号表**：

- 8 字节 `nlist_64` 条目，`LC_SYMTAB` 共 52,443 条；
- 其中 17,230 条为 `N_SECT`、33,573 条为 `N_UNDF`（外部引用）、1,638 条为 `N_ABS`；
- 函数名形如 `_iAP2LinkCreate`、`_iAP2PacketCalcChecksum`，共 **803** 条 `iAP2*` 相关条目（去重后 571 个带地址的符号）。

因此本阶段的函数定位策略是：**用符号表确定入口，用汇编确定语义**。

- 符号名本身是固件字节（`__LINKEDIT` 的字符串表），可作为"这是哪个函数"的证据；
- 但符号名**不是**语义证据：字段含义、参数顺序、常量取值一律回到汇编取证；
- 若符号名与汇编行为不一致，以汇编为准并记录冲突。

导出清单见 `source/metadata/selection.json`，落盘结果 114 个函数（`source/asm/accessoryd/index.json`）。

### 0.3.1 采样覆盖率

- 本阶段抽取并导出汇编的函数：**114 / 8,706**（`LC_FUNCTION_STARTS` 口径），占 **1.31%**。
- 其中被 `analysis/` 明确引用并逐条核对的：见 `analysis/13-function-inventory.md` 的 `CONFIRMED_BY_ANALYSIS` 列表。
- **不构成全栈覆盖**：消息处理器表中有 27 张表、共 100+ 个 handler 地址，本阶段只解读了表的**结构与 ID**，未逐个反汇编 handler；标识为 `SAMPLED_NOT_CITED`。

### 0.3.2 函数边界规则

`source/asm/accessoryd/index.json` 中每个函数的 `end` 取"下一个 `LC_FUNCTION_STARTS` 起点"（末函数回退到下一个符号地址），因此：

- `.bin` 区间可能包含函数尾部对齐填充；
- 该规则同时被用于 Ghidra 反编译请求的 `raw_sha256` 校验（区间字节一致才允许输出）。

## 0.4 Ghidra 已知失真（人工核对时逐条修正）

本二进制上与蓝牙阶段相同的失真类型，均已在核对时处理，未处理处不进入 `CONFIRMED`：

| 类型 | 表现 | 处理 |
|---|---|---|
| 参数个数丢失 | 反编译签名少于汇编实际读取的寄存器 | 以汇编的寄存器使用为准，记录到对应 analysis 节 |
| `unaff_x30` / `unaff_x29` | 帧指针与返回地址伪变量 | 忽略 |
| 跳表未展开 | `br x16` 型 switch 显示为间接调用 | 回汇编读跳表（本阶段用到 2 处：帧解析状态机 `0x10000a5d0`、解析器命令分发 `0x1000cf5b8`） |
| 内联展开 | 小的 accessor 被内联，反编译中看不到独立函数 | 以 `source/asm` 的独立函数为准 |
| `blraa`/`blraaz`（指针认证） | 反编译显示为普通调用 | 汇编中保留 `paciza`/`blraaz` 原样 |

本次 Ghidra 版本 12.1.4、JDK 21；导入时**未重新定义函数边界**，仅用符号表与 `LC_FUNCTION_STARTS` 作为入口。

## 0.5 可复现命令

```bash
cd /mnt/d/carvex-research

# 1) 元数据（段表/加载命令/函数起点/符号表）
python3 firmware/tools/macho-meta.py \
  "firmware/extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd" \
  research/protocol/iap2_link_establish/source/metadata

# 2) 表解码（状态机/消息处理器/特性表）
python3 firmware/tools/iap2-tables.py \
  research/protocol/iap2_link_establish/source/firmware/accessoryd \
  research/protocol/iap2_link_establish/source/metadata \
  research/protocol/iap2_link_establish/source/metadata/tables.json

# 3) 原始汇编 + 原始字节
python3 firmware/tools/export-asm.py \
  research/protocol/iap2_link_establish/source/firmware/accessoryd \
  research/protocol/iap2_link_establish/source/metadata \
  research/protocol/iap2_link_establish/source/metadata/selection.json \
  research/protocol/iap2_link_establish/source/asm/accessoryd

# 4) Ghidra 反编译（工程已建，-noanalysis 复用）
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
firmware/tools/ghidra/support/analyzeHeadless \
  firmware/analysis/24A446/iap2-link/project iap2 \
  -process accessoryd -noanalysis \
  -scriptPath firmware/tools/ipsw-research/ghidra \
  -postScript CachePhoneFunctions.java \
  research/protocol/iap2_link_establish/source/metadata/ghidra-request.json \
  research/protocol/iap2_link_establish/readable/ghidra/accessoryd

# 5) 校验
cd research/protocol/iap2_link_establish && python3 verify.py
```

## 0.6 与旧材料的关系

| 旧材料 | 位置 | 本阶段处理 |
|---|---|---|
| 旧 iAP2 分析（35 个目录） | `firmware/analysis/24A446/iap2-*` | **未读入结论**；仅作为"存在这些文件"的事实记录。按任务书决策 #1，本轮不对照旧文档 |
| 旧伪代码 | `/mnt/d/ios-carplay/pseudocode` | 未使用 |
| 协议清单 | `firmware/analysis/24A446/protocol-message-inventory` | 未使用 |
| `accessoryd-functions.json` / `accessoryd.a2s` | `firmware/analysis/24A446/` | 仅用于**发现**候选函数名（线索），所有引用均回到 `source/asm` 重新取证 |

**冲突记录**：本阶段未发现需要显式覆盖的旧结论；若后续对照发现冲突，必须在本节追加一行，不得静默修改。

## 0.7 运行时素材

- 手上 sysdiagnose 的构建为 22H374（iOS 18）、23G90（iOS 26）、21G93（iOS 17），**均不是 24A446**。
- 因此 `runtime/` 只用于**佐证**（如帧头字节序、SDP 请求形状），任何常量都不以运行时素材确认。
- 本阶段 iAP2 链路部分**未取得任何抓包**（见 `OPEN-RUNTIME-1`）。

## 0.8 结论锚点约定

- analysis 内部结论编号：`A<文件号>.<序号>`，例如 `A03.4`。
- spec 条款编号：`R-<章>.<序号>`，例如 `R-2.3`。
- 每条 spec 条款的"本章依据"表必须写出 `A` 编号与至少一个函数地址。
- `verify.py` 校验：spec 中出现的每个 `A` 编号都能在 `analysis/` 中找到；每个被引用的 `0x…` 地址都落在镜像窗口内。

## 0.9 本轮自我修正记录（不得静默覆盖）

任务书要求"与旧文档或旧分析的冲突必须写明"。本 docset 在成稿过程中修正了自己先前的两条判断，记录如下：

| 编号 | 先前判断 | 修正后 | 触发证据 |
|---|---|---|---|
| `C-1` | 传统帧校验按"覆盖 `FF 55`"计算，Detect 得 `0xBC`、DetectNACK 得 `0xB4`，并据此称"与固件常量 0x10/0x08 吻合" | 传统帧校验**不覆盖** `FF 55`：`cksum8(len ‖ payload)`，Detect = `0x10`、DetectNACK = `0x08` | 固件静态模板 `0x1001b3378` = `ff 55 02 00 ee 10`；用两种覆盖方式分别重算，只有"排除 `FF 55`"与两个固件比较常量同时吻合（`analysis/03` A03.15/A03.16） |
| `C-3` | 曾把传统帧载荷末字节写成"固定终止符 `0xEE`"；RequestIdentify 的载荷是 `00 FE`，该概括被自己的向量 V3 否定。已改为"末字节随帧类型变化，语义未取证 → `OPEN-FRM-1`"，并在 `spec/02` `R-2.10`、`analysis/03` `A03.15`、参考实现中同步修正。 |
| `C-2` | Detect 状态表含 `0x04 → SendResetSYNACK`；且认为状态表里"handler 为空"只表示"无动作但仍然迁移" | Detect 表**没有** `0x04` 项；空 handler 条目**不迁移**（命中后只写日志即返回） | `tables.json` 的 Detect 表逐项解码（5 条）；`iAP2FSMHandleEvent` 的 `cbz x8, 0x1000064a0` → `0x10000664c: b 0x100006650`（`analysis/06` A06.4） |

连带影响：`spec/05` 的迁移表因此只列"生效迁移"，另列 5 条"死条目"；`spec/02` 与 `analysis/03`、`analysis/07` 的测试向量与推导全部按 `C-1` 重写。

## 0.10 产物生成链与验收

所有可机械生成的内容都有对应的脚本（`firmware/tools/`），文档只做解释，不手改生成物：

| 产物 | 生成器 | 说明 |
|---|---|---|
| `source/metadata/{summary,segments,sections,load-commands,function-starts,symbols}.json` | `macho-meta.py` | Mach-O 元数据 |
| `source/asm/accessoryd/` | `export-asm.py` | Capstone 反汇编 + 原始字节切片 + 头标记（含"未人工确认"） |
| `source/metadata/tables.json` | `iap2-tables.py` | FSM 表、27 张消息表、参数表/特性表解码 |
| `analysis/12-message-table.md` | `gen-iap2-message-table.py` | 消息对照表（改 `tables.json` 后必须重跑） |
| `source/metadata/ghidra-request.json` | `build-ghidra-request.py` | 反编译请求（地址区间 + 原始字节哈希） |
| `readable/ghidra/accessoryd/` | Ghidra 12.1.4 headless + `ghidra-scripts/ExportDecomp.java` | 114 个函数的原始 C 输出 + 哈希链元数据（幂等，可重跑） |
| `function-index.json` | `gen-function-index.py` | 每个函数的地址/大小/哈希/被引用文档/取证状态 |
| `manifest.json` | `gen-manifest.py` | 全量文件哈希 + 12 项覆盖状态（`source/metadata/coverage.json`）+ OPEN 索引 |
| `spec/08-conformance-checklist.md` 的向量与检查项 | 人工 + `verify.py` 复核 | 测试向量、定时器清单、边界定量、`CL-1..CL-26` |

验收命令：

```bash
cd /mnt/d/carvex-research/research/protocol/iap2_link_establish
python3 verify.py
```

`verify.py` 共 7 类检查、当前 39 个断言（C1 源一致性、C2 汇编切片与 `source/asm` 登记、C3 反编译哈希链、C4 地址窗口、C5 校验向量与帧字面量、C6 常量/动词/覆盖表、C7 manifest 与锚点/未决项）。
