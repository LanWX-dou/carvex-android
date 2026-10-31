# iAP2 Link 建立阶段 — 任务要求（`iap2_link_establish`）

> 本文件是下一阶段的任务书，结构与 `research/protocol/bluetooth_rfcomm/`（蓝牙阶段）一致。
> 目标：在**同一份固件构建（24A446 / iOS 27.0.1 / iPhone18,1）**上，用同样的严格证据链，产出 iAP2 链路建立阶段的平台无关规范。

---

## 0. 阶段定位（与蓝牙阶段的衔接）

蓝牙阶段已确认的边界事实：

- `/usr/sbin/bluetoothd` 内 `iap2` 字符串计数为 **0**；
- RFCOMM 数据帧以上层回调交付：`(**(code**)(*(dlci+0x28)+8))(dlci[8], ptr, len)`，同时存在 `os_channel` 文件描述符（`kCBMsgArgSocket`）；
- 单次交付长度上限 `0xA0A`（2570）。

因此 iAP2 链路的实现**不在** `bluetoothd` 内，本阶段必须换目标二进制，并从"帧如何进入链路层"这一点接上蓝牙阶段的出口。

## 1. 目标与完成判据

**目标**：给出 iAP2 链路建立阶段的完整、可复现、逐条可追溯到固件字节的协议规范，使第三方平台能独立实现"从传输就绪到链路可用"的全过程。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求（第 5 节）逐项有固件/汇编依据，或明确标 `OPEN`；
2. `verify.py` 通过（源哈希、`.bin` 与固件切片逐字节一致、头部标记、测试向量重算、常量一致）；
3. `STATUS.md` 给出"已确认/部分确认/OPEN"三态统计与采样覆盖率；
4. 任何一条规范条款都能点回 `analysis/` 的具体结论，该结论能点回 `source/asm/` 的地址与字节。

## 2. 素材与目标二进制（已实测，可直接用）

主目标：

| 项 | 值 |
|---|---|
| 路径（构建内） | `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 本地路径 | `firmware/extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 函数数（LC_FUNCTION_STARTS） | **8,706** |
| 段 | `__PAGEZERO` / `__TEXT` 2,195,456 / `__DATA_CONST` / `__DATA` / `__LINKEDIT` |
| 加密 | 无 `LC_ENCRYPTION_INFO`（未加密，可直接分析） |

次目标（交叉验证 / 补证）：

| 二进制 | 大小 | SHA256 前缀 | 函数数 | 用途 |
|---|---|---|---|---|
| `IAP.framework/Support/iapd` | 1,440,608 B | `96c0a38a…` | 4,278 | iAP（旧协议）与 iAP2 交界、消息名/常量对照 |
| `CoreAccessories.framework/CoreAccessories` | — | — | — | 框架层导出接口 |
| `AccessoryiAP2Shim` | 234,336 B | — | — | iAP2 适配层 |
| `AccessoryCommunications` | 141,168 B | — | — | 配件通信通道 |

已在 `accessoryd` 中观测到的类型编码串（**仅为线索，未复核**，必须重新取证后才能引用）：

```
iAP2LinkRunLoop_st
iAP2PacketSYNData_st = CCCCSSSCCS[5C][5C]C[5C][5{?=CCCB}]
iAP2Packet_st
iAP2MsgParser_st
iAP2Msg_t_st = *III**^?^vB^?*[29^v]^vB^vd
```

这些是 Objective-C 类型编码，说明链路层结构与"SYN 协商数据"结构确实存在于该二进制内；但**字段含义、顺序、取值范围都必须从汇编重新取证**，不得照抄编码串猜测。

## 3. 证据链规则（与蓝牙阶段完全一致）

```
固件原始 bytes → 原始 ARM64 汇编 → Ghidra 自动反编译 → 人工对照汇编核对
     → analysis（证据/差异/影响/OPEN）→ spec（平台无关条款）
```

硬性要求：

1. **每条结论**必须在 `analysis/` 给出：函数地址、原始字节、汇编片段（可含反编译片段但**不作为依据**）、"已确认 / 未确认"标记。
2. **Ghidra 输出不是证据**：只作阅读辅助。凡与汇编冲突，以汇编为准，并在 analysis 记录差异（已知的反编译失真类型：参数个数丢失、`unaff_x30`、跳表未展开、内联展开）。
3. 未取到证据的内容**一律标 `OPEN`**，并在 `manifest.json` 汇总（`id` + 所在文件）。
4. 旧的既有分析（`firmware/analysis/24A446/iap2-*`，共 35 个目录）与任何伪代码目录**只能作线索**：引用时必须标"线索，未复核"，且必须回到 `source/asm/` 重新取证。
5. 运行时素材（sysdiagnose、日志、抓包）**只能佐证**，不得替代固件证据；且当前手上的 sysdiagnose 构建（22H374/23G90/21G93）**都不是 24A446**。

## 4. 目录规则

```
research/protocol/iap2_link_establish/
├── source/          # 只放原始 bytes、原始汇编、导出信息；不可修改
│   ├── firmware/    # accessoryd 等，带 sha256
│   ├── asm/         # 每函数 .s + .bin + index.json，头部含地址/源哈希/工具版本
│   └── metadata/    # Mach-O 段表、加载命令、函数起点统计
├── readable/        # 只有自动反编译输出；可改格式，必须保留地址/源哈希/"未人工确认"
├── analysis/        # 逐函数/逐主题：地址、调用关系、数据流、每条结论的依据与影响
├── spec/            # 平台无关规范；禁止任何语言/框架/库绑定
├── runtime/         # 日志/抓包，仅佐证
├── reference/       # 可选
├── manifest.json    # 全量文件哈希、覆盖统计、OPEN 索引
├── function-index.json
├── verify.py
└── STATUS.md        # 状态报告
```

命名与头部约定沿用蓝牙阶段：

- `source/asm/<image>/f_<addr>.s`、`f_<addr>.bin`；
- `.s` 头部固定两行：`; <image> 0x…-0x…; source SHA256 …; original firmware bytes`、`; disassembly: Capstone <ver> …; no rewriting`；
- `readable/**/f_<addr>.ghidra.c` 头部含地址、源哈希、`DECOMPILED_UNREVIEWED`。

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **传输绑定** | iAP2 链路从哪种传输取帧（RFCOMM / `os_channel` / USB）？如何在代码里注册回调？与蓝牙阶段出口如何对接？ |
| 2 | **链路层初始化** | 链路对象如何创建、初始化顺序、运行循环（线程/队列）由谁驱动？ |
| 3 | **帧格式** | 帧头字节、长度字段位置与字节序、控制字段位定义、序号字段、校验和算法与覆盖范围；给出字节级测试向量 |
| 4 | **SYN 协商** | SYN 包字段（协议版本、最大重传、ACK 超时、最大包长、校验类型等）的顺序、宽度、取值范围；协商失败如何处置 |
| 5 | **序号/确认/重传** | 序号回绕、ACK 语义、重传触发条件、重传次数上限、重复帧处理 |
| 6 | **链路状态机** | 状态取值、迁移条件、守卫（guard）、非法事件处理；给出迁移表 |
| 7 | **IDPS 阶段** | 谁发起、报文序列、状态查询与结果判定、与后续阶段的门控关系 |
| 8 | **识别阶段** | RequestIdentify / Identify 的报文结构、参数集合、必需项与顺序、超时 |
| 9 | **认证阶段** | 进入条件、认证消息序列、失败/拒绝路径、与识别阶段的先后关系 |
| 10 | **会话启动边界** | 链路建立完成后由什么触发 CarPlay 会话启动？"链路可用"的判定条件是什么？ |
| 11 | **异常与清理** | 校验失败、序号错、超时、RST/NACK、对端断开：各自的状态迁移与释放顺序 |
| 12 | **差异与未知** | 实现与公开 iAP2 文档/常见实现的差异；所有无证据点汇总为 `OPEN` |

### 5.1 建议的 `analysis/` 文件划分（可按证据调整，但不得缺项）

| 文件 | 内容 |
|---|---|
| `00-method-and-environment.md` | 方法、工具链、可复现命令、抽样策略 |
| `01-transport-binding.md` | 传输绑定、回调注册、与蓝牙阶段出口的对接 |
| `02-link-init-and-runloop.md` | 链路对象创建、运行循环、缓冲与队列 |
| `03-framing-and-checksum.md` | 帧格式、长度/控制/序号、校验和算法与向量 |
| `04-syn-negotiation.md` | SYN 包字段、协商流程、失败处置 |
| `05-seq-ack-retransmit.md` | 序号、确认、重传、重复帧 |
| `06-link-state-machine.md` | 状态取值与迁移表、守卫条件 |
| `07-idps.md` | IDPS 阶段序列与门控 |
| `08-identification.md` | 识别报文、参数集合、超时 |
| `09-authentication.md` | 认证序列、失败路径 |
| `10-session-boundary.md` | "链路可用"判定与 CarPlay 会话启动触发 |
| `11-errors-and-teardown.md` | 异常、复位、清理顺序 |
| `12-message-table.md` | 消息 ID 对照表（含 `OPEN` 标注） |
| `13-function-inventory.md` | 抽样函数清单与引用状态（`CONFIRMED_BY_ANALYSIS` / `SAMPLED_NOT_CITED`） |

### 5.2 建议的 `spec/` 文件划分

`00-scope-and-conventions.md`、`01-transport-and-link-init.md`、`02-framing-and-checksum.md`、`03-syn-and-negotiation.md`、`04-sequencing-and-retransmission.md`、`05-identification-and-authentication.md`、`06-boundary-and-lifecycle.md`、`07-conformance-checklist.md`（含帧级测试向量与一致性检查项）。

### 5.3 其他补充要求

- **消息表**：给出"消息 ID → 名称 → 方向 → 所属阶段"的对照表，每行必须有地址/常量证据，否则标 `OPEN`；
- **超时单位**：所有定时器必须给出"滴答 → 单位 → 缺省值"的推导链，推导不出就 `OPEN`；
- **边界定量**：链路层单帧最大载荷、缓冲区上限、分片策略必须有数值。

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 原始二进制（带哈希）、每函数 `.s` + `.bin` + `index.json`、Mach-O 元数据 |
| `readable/` | 与 `source/` 一一对应的自动反编译，0 失败，全部带"未人工确认" |
| `analysis/` | 逐函数/逐主题：地址、调用关系、数据流、每条结论的固件依据/未确认点/实现影响；与旧文档或旧分析的冲突必须**写明**，不得静默覆盖 |
| `spec/` | 平台无关条款（MUST/SHOULD/MAY 编号）、每章末尾"本章依据"表、帧级测试向量、一致性检查清单 |
| `runtime/` | 如有观测，只作佐证并声明构建差异 |
| `reference/` | 可选 |
| `manifest.json` | 全量文件哈希、12 项状态、OPEN 索引（id + 所在文件） |
| `function-index.json` | 每个函数的地址/大小/分组/哈希/被引用位置 |
| `verify.py` | 自动校验（见 6.1） |
| `STATUS.md` | 状态报告：已确认/部分确认/OPEN、覆盖率、能否指导其他平台实现 |

### 6.1 `verify.py` 至少校验

1. 源二进制 SHA256 与 `manifest.json` / `function-index.json` 一致；
2. 每个 `.bin` 与源二进制对应区间**逐字节**相同；
3. `.s` / `.ghidra.c` 头部含正确地址、源哈希、"未人工确认"标记；
4. 文档引用的地址都落在镜像地址窗口内；
5. 用固件内常量/表**重新计算**帧校验和测试向量，与规范一致；
6. 规范中的常量（消息 ID、UUID、字段缺省值）与 `analysis/` 提取值一致；
7. `source/` 无未登记文件。

## 7. 状态报告要求（`STATUS.md`）

必须包含：

1. 12 项覆盖要求的逐项状态：**已确认 / 部分确认 / OPEN**，以及证据强度（"固件+汇编" > "固件+数据流" > "运行时候选"）；
2. **采样覆盖率**声明：抽取了多少函数 / 二进制函数总数（如 `n / 8,706`），并明确"不构成全栈覆盖"；
3. 所有强制实现决策（例如校验和覆盖范围、超时单位、序号初值）逐条列出，给出规范默认值与依据；
4. **不得**在任一项仍为 OPEN 时宣称"已完成"，只能写"部分完成 + 剩余项清单"。

## 8. 严禁事项

1. 不得修改 `source/` 下任何文件；不得把反汇编结果改写为伪代码充当"原始汇编"。
2. 不得把 Ghidra 反编译输出直接当作结论依据；不得省略"人工对照汇编核对"这一步。
3. 不得引用旧分析、旧伪代码、外部文档、开源实现作为**确认依据**（可作线索或对照，但必须标注）。
4. 不得用不同构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、操作系统 API。
6. 不得静默覆盖与旧材料冲突的结论——冲突必须显式记录。

## 9. 既有线索的处理

| 线索 | 位置 | 处理方式 |
|---|---|---|
| 既有 iAP2 分析（35 个目录） | `firmware/analysis/24A446/iap2-*` | 只作线索；每条结论重新取证；引用时标"线索，未复核" |
| 既有伪代码 | `/mnt/d/ios-carplay/pseudocode` | 同上 |
| 既有协议清单 | `firmware/analysis/24A446/protocol-message-inventory` | 同上 |
| sysdiagnose 日志/抓包 | `D:\carvex-research\sysdiagnose` | 仅佐证；构建非 24A446 |

## 10. 工具与环境

| 工具 | 版本/路径 | 用途 |
|---|---|---|
| Ghidra | 12.1.4 | headless 反编译（允许使用 24–32 GB 内存） |
| JDK | 21（`/usr/lib/jvm/java-21-openjdk-amd64`） | Ghidra 依赖 |
| Capstone | 5.0.7（`md.skipdata = True`） | 汇编导出 |
| `ipsw` | 3.1.739 | IPSW / dyld 缓存处理 |
| Python | 3.12.3 | 工具链与校验 |

IPSW：`D:\ios-carplay\iPhone18,1_27.0.1_24A446_Restore.ipsw`（已解出 `firmware/extracted/24A446`，无需重新提取）。

## 11. 需你确认的决策（默认值已选，可直接改）

| # | 决策 | 默认 | 理由 |
|---|---|---|---|
| 1 | 是否对照旧文档/旧伪代码 | **不对照**（只记录差异，不据其修改结论） | 与蓝牙阶段一致，避免污染证据链 |
| 2 | 是否比对本仓库外的现有程序 | **本轮不比** | 同上 |
| 3 | 运行时素材使用 | **只用 `D:\carvex-research\sysdiagnose` 作佐证** | 手上没有 24A446 的抓包 |
| 4 | 传输范围 | **以 RFCOMM/`os_channel` 为主**，USB 若无证据则 `OPEN` | 与蓝牙阶段衔接 |
| 5 | 消息表深度 | **只覆盖链路建立相关阶段**，业务消息标 `OPEN` | 控制范围，避免不可完成 |

## 12. 验收方式

```bash
cd D:\carvex-research\research\protocol\iap2_link_establish
python3 verify.py
# 期望：失败 0；检查项总数写进 STATUS.md 与 manifest.json
```

验收时同时检查：

- `STATUS.md` 第 1 节 12 项状态与 `manifest.json` 的 `items` 完全一致；
- 每个 `OPEN` 都能在 `manifest.json` 找到 `id` 与所在文件；
- 随机抽 3 条规范条款，能沿 `spec → analysis → source/asm` 逐级点回。
