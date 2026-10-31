# iPhone 经典蓝牙 / SDP / RFCOMM 协议文档集

本目录是从 **iPhone 固件原始字节**出发，经"原始汇编 → 自动反编译 → 人工对照汇编核对 → 分析记录 → 平台无关规范"五级证据链产出的文档集。目标是让**另一套平台**能按本目录的规范实现与 iPhone 的经典蓝牙发现、SDP 查询、RFCOMM 连接与数据收发互操作。

## 1. 从哪里开始读

| 你的目的 | 读这些 |
|---|---|
| 只想实现协议 | `spec/00` → `spec/01`…`spec/06` → `spec/08`（交接契约） → `spec/07` 逐项自测 |
| 设备侧客户端连车机（§9.2–§9.6）/ 车机侧监听（§9.7） | 直接读 `spec/09`（主动连：SDP 查通道 → SABM/PN/MSC；监听：注册通道 → UA/PN 应答），不要照抄 `spec/08` 的 XPC/fd 契约 |
| 想核对某条结论的依据 | 各 `spec/NN` 末尾的"附录 A：本章依据"→ 对应 `analysis/NN` → 再查 `source/asm/` |
| 想知道哪些还没证据 | `STATUS.md` 的 OPEN 清单，`analysis/NN` 各章第 4 节 |
| 想复现反编译 | `analysis/00-method-and-environment.md` 的可复现命令 |
| 想验文档没被篡改 | `python3 verify.py` |

## 2. 目录职责（严格分工，不可混用）

| 目录 | 内容 | 规则 |
|---|---|---|
| `source/firmware/` | 固件原始二进制 | **只读**。哈希登记于 `manifest.json`；任何改动都会被 `verify.py` 发现 |
| `source/asm/bluetoothd/` | 每个函数的原始 ARM64 汇编 + 原始字节 + `index.json` | **只放反汇编器原样输出**，不做改写、不插入伪代码 |
| `source/metadata/` | 导出信息（段表、符号、函数起点） | 只读登记 |
| `readable/ghidra/bluetoothd/` | Ghidra 自动反编译结果（`.ghidra.c` + `.json`） | 可改格式，**必须**保留原函数地址、源哈希、"未人工确认"标记 |
| `analysis/` | 逐函数/逐主题的证据、差异、影响、OPEN | 每条结论必须给固件/汇编依据；无依据一律 `OPEN` |
| `spec/` | 平台无关规范 | 不得出现具体语言/框架/库绑定 |
| `runtime/` | 运行时日志、抓包 | **只能佐证**，不能替代固件证据；首轮观测见 `runtime/observations/findings-sdp-hci.md` |
| `reference/` | 外部参考（可选） | 不参与证据链 |
| `reference/handoff-facts-for-iap2.md` | 交给 iAP2 side 的蓝牙侧事实清单（15 条） | 由 `analysis/07` C1/C2/C8 派生 |
| `runtime/observations/sdp-records-iap2.md` | 抓包里 iPhone/车机的 iAP2 SDP 记录（通道 4/1/5） | 运行时，跨构建，非 24A446 |

## 3. 证据链约定

```
固件原始 bytes  →  原始 ARM64 汇编  →  Ghidra 自动反编译  →  人工对照汇编核对
      →  analysis 记录（依据/已确认/未确认/实现影响/OPEN）  →  spec 平台无关条款
```

每一级的可信度标记：

| 标记 | 含义 |
|---|---|
| `CONFIRMED` | 已对照原始汇编逐条核对，结论可复算 |
| `PARTIAL` | 结论的主要部分已核对，存在未展开的分支或未定的常量语义 |
| `OPEN` | 无固件证据，或证据不足以下结论；**不得**据此实现 |
| `N/A-BY-DECISION` | 用户明确选择不做该项（见 `analysis/08`） |

`readable/` 里的反编译代码**永远**是未确认材料：Ghidra 的输出在本套文档中被发现有 5 类系统性偏差（`analysis/00` 第 6 节），所有引用都回到汇编复核过。

## 4. 覆盖范围与抽样声明

- 目标二进制：`bluetoothd`（13,092,096 字节，SHA256 `cfd94854…208c1`），**37,368** 个函数起点。
- 本套文档抽取 **101** 个函数（0.27%），全部登记于 `analysis/09-function-inventory.md` 与 `function-index.json`。
- 抽样是有目标的：覆盖"发现 / 识别 / 服务注册 / SDP 服务端 / SDP 客户端 / RFCOMM 复用器 / 数据通道 / 断链 / 上层边界"。
- **不构成**"已分析全部蓝牙协议栈"的声明。未抽样区域见 `analysis/09` 第 5 节。

## 5. 校验

```bash
cd bluetooth_rfcomm
python3 verify.py          # 2173 项检查：哈希、字节一致性、头部标记、测试向量、常量
```

`verify.py` 会做这些事：

1. 源固件 SHA256 与 `manifest.json`/`function-index.json` 一致；
2. 每个函数的 `.bin` 与源固件对应区间**逐字节**相同；
3. 每个 `.s` / `.ghidra.c` 头部含正确地址、源哈希与"未人工确认"标记；
4. 文档引用的地址都落在镜像地址窗口内；
5. 用固件里的 FCS 表**重新计算** `spec/07` 的测试向量，必须与文档一致；
6. EIR 的 5 个 128-bit UUID 常量与文档表格逐字节一致；
7. `source/` 目录没有出现未登记文件。

## 6. 文件清单

| 文件 | 作用 |
|---|---|
| `manifest.json` | 全量文件哈希、覆盖统计、12 项需求的确认状态、37 个 OPEN 项索引（含所在文件） |
| `function-index.json` | 101 个函数的地址/大小/分组/哈希/被引用位置 |
| `verify.py` | 自校验脚本 |
| `STATUS.md` | 状态报告：已确认 / 部分确认 / OPEN / 结论 |

## 7. 使用限制

1. 本套文档描述的是**该固件版本（24A446）的行为**。其他 iOS 版本的常量与状态机可能变化。
2. `spec/` 中的 `应当（SHOULD）` 条款允许实现选择，但必须在自己的实现文档里写明选择（`spec/07` 第 7.8 节列出 7 个必记选择点）。
3. iAP2 报文格式**不在本套文档范围内**（该层不在此固件内，见 `analysis/07` C3）。
