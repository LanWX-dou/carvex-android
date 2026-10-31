# analysis/00 — 方法与取证环境

本阶段（`iap2_control_session`）分析对象、工具链与证据链规则与 `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/` 完全一致。本文件只记录**本阶段**实际用到的参数与偏差，不重复前两阶段的方法论述。

## 0.1 目标镜像

| 项 | 值 |
|---|---|
| 二进制 | `accessoryd`（`/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd`） |
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 构建 | 24A446 / iOS 27.0.1 / `iPhone18,1` |
| 函数起点数 | 8,706 |
| 符号表条目 | 52,443 |
| 镜像窗口 | `0x100000000`–`0x102180000` |
| 指针还原 | `target = 0x100000000 + (value & 0xFFFFFFFFFF)` |

与上一阶段是同一份二进制、同一个 SHA256；本阶段的 `source/firmware/accessoryd` 由上一阶段逐字节复制而来，`verify.py` 会重新算哈希。

## 0.2 工具链

| 工具 | 版本/位置 | 用途 |
|---|---|---|
| Capstone | 5.0.7（`CS_ARCH_ARM64`） | 原始反汇编（不改写） |
| Ghidra | 12.1.4 headless | 自动反编译（只作阅读辅助） |
| JDK | 21 | Ghidra 运行时 |
| Python | 3.12 | 元数据抽取、生成、校验 |

本阶段新增的取证脚本（都在 `firmware/tools/`）：

| 脚本 | 作用 |
|---|---|
| `scaffold-control-session.py` | 建立 docset 骨架、复制同一镜像、生成 `selection.json` |
| `build-callgraph.py` | 全 `__text` 线性扫描，抽直接 `bl`/`b` 边，生成调用图 |
| `xrefs.py` | 按地址查调用者/被调用者（导航用，不作证据） |
| `find-mem-offset.py` | 全 `__text` 搜"某个结构偏移"的读写点（**发现会话表的关键工具**） |
| `extract-feature-table.py` | 抽取 `__kiAP2FeatureInfoEntries`（29 项）到 `tables.json` |
| `grep-symbols.py` | 按正则筛符号表 |

复用上一阶段的：`macho-meta.py`、`export-asm.py`、`build-ghidra-request.py`、`ghidra-scripts/ExportDecomp.java`、`gen-function-index.py`、`gen-manifest.py`。

## 0.3 证据链与强度分级

每一条结论必须能沿 **spec → analysis → `source/asm/<addr>.s` → `source/firmware/accessoryd` 的字节区间** 逐级点回。强度用三个词：

| 词 | 含义 |
|---|---|
| `已确认` | 有指令级证据，且反例检查过（例如"没有别的写入点"） |
| `部分确认` | 结构/机制有指令证据，但某个字段或某条分支未取证 |
| `OPEN` | 未取证，登记 `OPEN-*` 编号 |

**符号名不构成证据**。本阶段大量函数被剥名（例如 `0x10000946c` 只是 `_OUTLINED_FUNCTION_44`），凡引用符号名处，都以同地址的指令为准。

## 0.4 采样与覆盖声明

| 项 | 值 |
|---|---|
| 导出函数数 | **199** |
| 函数起点总数 | 8,706 |
| 采样率 | **199 / 8,706 = 2.29%** |
| 组 | `X`（会话核心/路由/编码）、`C`（控制会话）、以及上一阶段 114 个种子（`A E F L M Q S T`） |

采样是**按主题定向**的（会话对象、路由表、控制通道、消息编码、门控、拆除），不代表全栈覆盖。凡结论依赖但未导出的函数，都在 `analysis/13` 里显式标注"未读"。

上一阶段 114 个函数被**重新导出**（同一镜像、同一字节），因此本阶段的引用不依赖 `link/` 的缓存文件。

**关于 199 这个数字**：`selection.json` 里的选函数条目数是 199，其中不含重复符号。构建过程中曾出现 202 条的情况，原因是符号表在同一地址上有**两组名字**（`iAP2LinkAttached` 与 `_iAP2LinkAttached` 等 3 组），选函数表和新增表各登记了一次，导致同一地址被导出两遍、把"导出函数数"虚高到 202。修正方式：选函数表按 `符号名去掉前导下划线` 去重，导出器再按地址去重（`export-asm.py` 的 `used` 集合）。因此 **199 = 199 个不同地址 = 199 个 `.s`/`.bin` = 199 份反编译**，四个数字一致。

## 0.5 与上一阶段的关系

本阶段的边界从 `link/R-6.9`（链路 `Connected` 才允许会话）之后开始，引用上一阶段条款时一律写 `link/R-x.y` 前缀，`verify.py` 会去 `research/protocol/iap2_link_establish/spec/` 验证该编号存在。

上一阶段遗留的、被本阶段**部分解答**的未决点：

| 上一阶段编号 | 上一阶段内容 | 本阶段结论 |
|---|---|---|
| `link/OPEN-SES-1` | `link+0x120`/`+0x128` 两条链的角色 | `+0x120`/`+0x128` 是两条 8 字节元素表（容量 = 建链参数 `bufSize`），**不是**会话表；会话表在 `+0x1a4`/`+0x1b8`。仍余"两表各自的用途"未定，见 `OPEN-SES-4` |
| `link/OPEN-FRAME-6` | `hdr[6]`（lt）/`hdr[7]`（extra）语义 | `hdr[7]` = **会话号**，收发两侧都有指令证据（见 `analysis/02`）；`hdr[6]` 仍未定 |

## 0.6 更正日志

与本阶段直接相关的两处更正（都在本 docset 内，不改上一阶段文件）：

- `C-1`：最初把 `link+0x1a4` 当作"发送窗口"，因此误判"会话表永空"。实际 `iAP2LinkGetSessionInfo`（`0x100032828`）用 `ldrb w9,[x0,#0x1a4]` 作**循环次数**、`add x8,x8,#0x1b8` 作基址，步长 4 —— 它是会话表项数。建链时写入 `0xFFFF0100`，低字节 `0x00` 即"初始 0 项"。
- `C-2`：`iap2_endpoint_create`（`0x100129350`）里的 `str xzr,[x19,#0x1b8]` 一度被当作"会话表被清零"。实际该对象是 **endpoint**（`calloc(1,0x1d8)`），`0x1b8` 是它的第 29 个特性槽之后的一个指针字段，与 link 的会话表只是偏移巧合。

## 0.7 生成器与可复现命令

```bash
# 1) 骨架 + 选函数
python3 firmware/tools/scaffold-control-session.py

# 2) 原始汇编（Capstone）
python3 firmware/tools/export-asm.py \
  research/protocol/iap2_control_session/source/firmware/accessoryd \
  research/protocol/iap2_control_session/source/metadata \
  research/protocol/iap2_control_session/source/metadata/selection.json \
  research/protocol/iap2_control_session/source/asm/accessoryd

# 3) 反编译请求 + 导出（WSL 内跑 Ghidra，项目复用上一阶段）
python3 firmware/tools/build-ghidra-request.py research/protocol/iap2_control_session
./firmware/tools/ghidra/support/analyzeHeadless \
  firmware/analysis/24A446/iap2-link/project iap2 -process accessoryd -noanalysis \
  -scriptPath firmware/tools/ghidra-scripts -postScript ExportDecomp.java \
  research/protocol/iap2_control_session/source/metadata/ghidra-request.json \
  research/protocol/iap2_control_session/readable/ghidra/accessoryd

# 4) 表抽取
python3 firmware/tools/extract-feature-table.py

# 5) 索引 + 清单 + 校验
python3 firmware/tools/gen-function-index.py research/protocol/iap2_control_session
python3 firmware/tools/gen-manifest.py research/protocol/iap2_control_session
cd research/protocol/iap2_control_session && python3 verify.py
```

## 0.8 运行环境说明

Ghidra 的工程仓库（`firmware/analysis/24A446/iap2-link/project`）由上一阶段的 WSL root 用户创建，Windows 侧打开会报 `NotOwnerException: Project is owned by root`。因此第 3 步必须在 WSL 内执行；这是工程归属问题，与镜像无关。
