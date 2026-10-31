# iAP2 控制会话阶段 — 任务要求（`iap2_control_session`）

> 本文件是第三阶段的任务书，结构与 `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/` 一致。
> 目标：在同一份固件构建（24A446 / iOS 27.0.1 / iPhone18,1）上，用同样的严格证据链，产出 **iAP2 会话层（session / control session）** 的平台无关规范。

---

## 0. 阶段定位（与上一阶段的衔接）

`iap2_link_establish` 已确认的边界事实（可直接引用，引用时标注 `link/REQ`）：

- 链路 FSM 有 8 个状态，**`Connected`（状态 5）是"链路可用"的唯一判定**；进入前链路层会丢弃找不到会话的数据（`R-6.9`、`A10.1`）；
- 接收路径已经存在**会话解复用**：`iAP2LinkDataReadyCB` → `iAP2LinkGetSessionInfo(link, service)` → 查不到会话即丢弃 → 否则投递（`A01.2`、`A10.1`）；
- 存在按服务号取会话的对外函数：`iAP2LinkGetSessionForService`（`0x100005740`）、`iAP2LinkGetSessionInfo`（`0x100032828`）；
- 链路对象持有两个链（`link+0x120`、`link+0x128`），语义未定（`OPEN-SES-1`）；
- 会话发送已有符号：`iap2_sessionControl_sendOutgoingMessage`（`0x100005130`）、`iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK`（`0x10002a9bc`）、`iap2_sessionControl_cleanup`（`0x10002a934`/`0x10002a980`）；
- 会话启动消息唯一：`0x4301` → `0x10016d3ac`（`R-6.8`）；静态嵌套 schema 已由跳表/getter/调用点闭合，运行时平台必填性、错误响应与下游 CarPlay 结果仍属 `OPEN-SES-2`；
- 消息/参数编码：识别与普通 `0xAAxx` 认证都用 `iAP2Msg*` 的消息 + 参数编码；`0x5500/0x5501` 是中继封装，不能套到普通认证消息（修正旧任务背景，见 link `R-6.6`）。

因此本阶段从"**链路 Connected 之后，会话如何被建立、绑定、路由、维持、拆除**"这一点接上。

## 1. 目标与完成判据

**目标**：给出 iAP2 会话层（含控制会话建立）的完整、可复现、逐条可追溯到固件字节的规范，使第三方平台能在自己的链路层之上实现"会话可用"。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求（第 5 节）逐项有固件/汇编依据，或明确标 `OPEN`；
2. `verify.py` 通过（源哈希、`.bin` 与固件切片逐字节一致、头部标记、测试向量重算、常量一致、跨 docset 条款可解析）；
3. `STATUS.md` 给出"已确认/部分确认/OPEN"三态统计与采样覆盖率；
4. 任何一条规范条款都能点回 `analysis/` 的具体结论，该结论能点回 `source/asm/` 的地址与字节；
5. 引用上一阶段的条款时必须带 docset 前缀（如 `link/R-6.9`），且能在上一阶段文件中找到。

## 2. 素材与目标二进制

主目标（与上一阶段同一份二进制，不重新提取）：

| 项 | 值 |
|---|---|
| 路径（构建内） | `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 本地路径 | `firmware/extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 函数数（LC_FUNCTION_STARTS） | **8,706** |
| 符号表条目 | 52,443 |

可复用资产（复制到新 docset，**不修改**）：

- 上一阶段的 `source/firmware/accessoryd`（哈希一致）；
- 上一阶段的 `source/metadata/*.json`（段表、符号、函数起点）；
- 上一阶段的 `readable/` 与 `source/asm/` 中的 114 个函数（作为种子，新阶段按需扩充）；
- 工具：`firmware/tools/{macho-meta,export-asm,build-ghidra-request,gen-function-index,gen-manifest}.py` 与 `ghidra-scripts/ExportDecomp.java`。

**次级目标**：若证据指向 `carkitd` / CarPlay 框架，只作**交叉核对**，不得据其下结论（记入 §9 线索表）。

## 3. 方法与证据链（与上两阶段相同）

1. **固件原始字节**：先用 Mach-O 元数据定位函数区间，取原始字节并算 SHA256；
2. **原始 ARM64 汇编**：Capstone 导出，不改写；
3. **Ghidra 自动反编译**：只作阅读辅助，标 `DECOMPILED_UNREVIEWED`；
4. **人工对照汇编核对**：每条结论必须写出指令地址；
5. **analysis**：`A` 编号结论 + 未确认点 + 实现影响；
6. **spec**：`R` 编号条款（MUST / SHOULD / 未定义）+ 测试向量 + 一致性清单。

会话层特有要求：

- **参数级**：会话消息必须给出"参数组 / 参数 ID / 类型"表，类型以实际调用的 `iAP2MsgGet*` / `iAP2MsgAdd*` 为准；
- **日志交叉**：允许用固件内的 `os_log` 格式串作为字段命名的旁证，但必须给出字符串地址；
- **多路复用键**：必须说明"服务号"的宽度、来源与冲突处理。

## 4. 抽样策略

- 抽样必须**按主题定向**：会话对象、路由表、控制通道建立、消息编码、超时/心跳、拆除；
- 采样率如实声明（`n / 8,706`），不得暗示全栈覆盖；
- 每个未采样的、被结论依赖的函数，必须显式标注"未读，结论仅基于调用点"。

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **会话对象模型** | 会话对象多大？字段有哪些？由谁分配/释放？与 link、transport、endpoint 的关系？ |
| 2 | **会话表与路由** | 服务号如何映射到会话？`link+0x120`/`+0x128` 两链分别是什么？冲突/重复服务号如何处理？ |
| 3 | **控制会话建立** | `0x4301` 的载荷结构、发起方、应答；建立成功/失败如何判定？ |
| 4 | **消息编码** | 会话消息用哪套消息/参数编码？参数组语义、类型集合、长度字段宽度、最大载荷？ |
| 5 | **会话级序号/确认** | 序号是链路级共享还是会话级独立？ACK/重传寄存器在哪个对象上？ |
| 6 | **会话状态机** | 会话是否有独立状态机？状态取值、迁移条件、非法事件处理？无则明确"无"。 |
| 7 | **阶段门控与顺序** | 识别/认证/会话三者的先后与门控条件（含 `iAP2Feature 7` 之类的特性开关）；不满足时如何拒绝？ |
| 8 | **多会话并发** | 同时存在多个会话时如何区分、排序、限流？有无会话数上限？ |
| 9 | **超时与心跳** | 会话级定时器有哪些？单位、缺省值、超时后的动作？ |
| 10 | **拆除与释放** | 会话关闭/链路断开/对端消失三种情况的释放顺序与幂等性？ |
| 11 | **错误与重连** | 会话级错误如何上报？是否自动重连？重连后会话表如何重建？ |
| 12 | **差异与未知** | 与上一阶段结论的衔接点；所有无证据点汇总为 `OPEN` |

### 5.1 `analysis/` 文件划分（实际）

> **与初版计划的偏差**：初版按"功能"切分（对象 / 路由 / 启动 / 编码 / 流控 / 状态 / 门控 / 并发 / 超时 / 拆除 / 重连），
> 实际按**证据链顺序**切分：对象 → 路由 → 编码 → 建立 → 门控 → 收包流水线 → 生命周期 → 发包 → 定时器 → 拆除。
> 这样每个文件对应一条可独立复核的链，而不是一个功能名。功能覆盖没有减少，见下表"覆盖的初版条目"列。

| 文件 | 内容 | 覆盖的初版条目 |
|---|---|---|
| `00-method-and-environment.md` | 方法、工具链、可复现命令、抽样策略、与上一阶段的引用约定 | 方法 |
| `01-session-object-model.md` | endpoint / run loop / link 三者布局与持有关系、会话=表项、5 条队列、全局处理器表 | 1、3 |
| `02-session-table-and-routing.md` | 会话表几何、`hdr[7]` 双向、四类数据面分发、两个查询方向、冲突规则 | 2、3、9 |
| `03-message-framing.md` | 消息 6 字节头、长度回填、逐字节重组、无消息级校验和 | 4、5 |
| `04-param-encoding.md` | 参数 4 字节头、值长、最小长度、嵌套、遍历边界 | 4 |
| `05-control-session-establishment.md` | 65535 缓冲、初始化三件事、版本门控（识别优先/认证优先）、`0x4301` | 3、6、7 |
| `06-feature-registry-and-handlers.md` | 29 项特性、27 张表、96 个处理器、奇偶门控、幂等注册 | 6、7、9 |
| `07-identification-gate.md` | 入站/出站两张白名单、认证+识别双条件、集合 `+0x60`/`+0x68` | 7 |
| `08-control-channel-pipeline.md` | 逐字节喂解析器、四个出口、三个失败日志、EA 子会话号 | 4、5、6 |
| `09-lifecycle-and-concurrency.md` | 唯一状态标志、上下沿调用顺序、并发形态与 5 项上限（复核纠正旧 44 项推导） | 6、9、10 |
| `10-send-path.md` | 两个发送入口、公共门控、装配消息、类型 0 会话号、可靠性归属 | 5、6 |
| `11-timers-and-flow-control.md` | 全链路单定时器、默认参数、会话层无定时器、5×255 队列 | 5、9、10 |
| `12-teardown-and-reconnect.md` | 拆除路径、资源释放对照表、五处复位清表、重连差异 | 10、11 |
| `13-function-inventory.md` | 199 个函数的取证状态、采样偏差声明 | 12、13 |
| `14-message-table.md` | 由脚本生成的 `msg_id → 处理器 → 特性 → 入/出站` 对照表（96 条） | 12（消息表） |
| `A-conclusions.md` | 结论登记表：spec 的 `依据` 只允许引用这里的 `A` 编号 | 全部（支撑件） |

### 5.2 `spec/` 文件划分（实际）

| 文件 | 条款区间 |
|---|---|
| `00-scope-and-terms.md` | `R-0.x` 范围与术语 |
| `01-session-object-model.md` | `R-1.x` 对象与表 |
| `02-routing-and-dispatch.md` | `R-2.x` 会话号与分发 |
| `03-message-and-param-encoding.md` | `R-3.x` 消息头、字节流、参数头 |
| `04-control-session-establishment.md` | `R-4.x` 初始化、版本门控、特性 |
| `05-gating-and-lifecycle.md` | `R-5.x` 两张名单、上下沿 |
| `06-teardown-timers-and-reconnect.md` | `R-6.x` 拆除、定时器边界、重连 |
| `07-conformance-checklist.md` | 50 项核对清单 + 不得声称的事项 |
| `08-client-implementation-guide.md` | `R-7.x` 客户端施工指南：能实现什么 / 不能实现什么 / 三个探测实验 |
| `09-device-side-startup.md` | `R-8.x` 设备侧启动序列（方向/前置/期望/失败分支）+ 版本门控 |
| `10-message-catalog.md` | `R-9.x` 消息目录：ID/方向/参数/门控/示例字节 + `0x4301` 未决 |
| `11-device-authentication.md` | `R-10.x` 设备侧认证七步、参数格式、证书链与签名校验 |
| `12-implementation-levels.md` | `R-11.x` L0–L4 等级与通过判据 |
| `13-cross-docset-conflicts.md` | `R-12.x` 与 link 的 4 条冲突、优先级规则、变更请求 |

### 5.3 其他补充要求

- **消息表**：必须给出"消息 ID → 名称 → 方向 → 所属阶段"对照表，每行有地址/常量证据，否则 `OPEN`；
- **超时单位**：每个定时器给出"滴答 → 单位 → 缺省值"的推导链，推不出就 `OPEN`；
- **边界定量**：会话数上限、每会话缓冲上限、单条消息最大载荷必须有数值或明确 `OPEN`；
- **跨阶段条款**：引用链路层结论时统一写 `link/R-x.y`，引用识别/认证写 `link/R-6.x`。

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 原始二进制（带哈希）、每函数 `.s` + `.bin` + `index.json`、Mach-O 元数据、Ghidra 请求 |
| `readable/` | 与 `source/` 一一对应的自动反编译，0 失败，全部带"未人工确认" |
| `analysis/` | 逐主题：地址、调用关系、数据流、每条结论的固件依据/未确认点/实现影响；与旧材料冲突必须写明 |
| `spec/` | 平台无关条款（MUST/SHOULD/未定义 编号）、每章"本章依据"表、测试向量、一致性清单 |
| `runtime/` | 如有观测，只作佐证并声明构建差异 |
| `reference/` | 可选（术语、地址速查） |
| `manifest.json` | 全量文件哈希、12 项状态、OPEN 索引（id + 所在文件） |
| `function-index.json` | 每个函数的地址/大小/哈希/被引用位置 |
| `verify.py` | 自动校验（见 6.1） |
| `STATUS.md` | 状态报告：三态统计、覆盖率、能否指导其他平台实现 |

### 6.1 `verify.py` 至少校验

1. 源二进制 SHA256 与 `manifest.json` / `function-index.json` 一致；
2. 每个 `.bin` 与源二进制对应区间**逐字节**相同；
3. `.s` / `.ghidra.c` 头部含正确地址、源哈希、"未人工确认"标记；
4. 文档引用的地址都落在镜像地址窗口内；
5. 用固件内常量/表**重新计算**消息编码测试向量（含长度字段宽度、参数类型字节），与规范一致；
6. 规范中的常量（消息 ID、服务号、字段缺省值）与 `analysis/` 提取值一致；
7. `source/` 无未登记文件；
8. **跨 docset**：`link/R-*` 引用在上一阶段存在，且本阶段未改写其含义。

## 7. 状态报告要求（`STATUS.md`）

1. 12 项覆盖要求的逐项状态：**已确认 / 部分确认 / OPEN**，以及证据强度（"固件+汇编" > "固件+数据流" > "运行时候选"）；
2. **采样覆盖率**声明（`n / 8,706`），并明确"不构成全栈覆盖"；
3. 所有强制实现决策（会话数上限、消息最大载荷、超时缺省值、路由键宽度）逐条列出，给出规范默认值与依据；
4. **不得**在任一项仍为 OPEN 时宣称"已完成"，只能写"部分完成 + 剩余项清单"。

## 8. 严禁事项

1. 不得修改 `source/` 下任何文件；不得把反汇编结果改写为伪代码充当"原始汇编"。
2. 不得把 Ghidra 反编译输出直接当作结论依据；不得省略"人工对照汇编核对"。
3. 不得引用旧分析、旧伪代码、外部文档、开源实现作为**确认依据**（可作线索，必须标注）。
4. 不得用不同构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、操作系统 API。
6. 不得静默覆盖与旧材料冲突的结论——冲突必须显式记录。
7. 不得在未取证的情况下把"上一阶段的推断"当成本阶段的前提（`link/R-6.6.2` 之类 `INFERRED` 条款只能作参考）。

## 9. 既有线索的处理

| 线索 | 位置 | 处理方式 |
|---|---|---|
| 上一阶段 docset | `research/protocol/iap2_link_establish/` | **可引用**（带 `link/` 前缀）；只引用其 `CONFIRMED`/`SHOULD` 条款，`OPEN` 不得作为前提 |
| 既有 iAP2 分析 | `firmware/analysis/24A446/iap2-*` | 只作线索；每条结论重新取证 |
| 既有伪代码 | `/mnt/d/ios-carplay/pseudocode` | 同上 |
| 协议清单 | `firmware/analysis/24A446/protocol-message-inventory` | 同上 |
| `carkitd` / CarPlay 框架 | `firmware/extracted/24A446/...` | 仅交叉核对，不据其下结论 |
| sysdiagnose 日志 | `D:\carvex-research\sysdiagnose` | 仅佐证；构建非 24A446 |

## 10. 工具与环境

| 工具 | 版本/路径 | 用途 |
|---|---|---|
| Ghidra | 12.1.4（`firmware/tools/ghidra/support/analyzeHeadless`） | headless 反编译；脚本 `firmware/tools/ghidra-scripts/ExportDecomp.java` 可直接复用 |
| JDK | 21 | Ghidra 依赖 |
| Capstone | 5.0.7 | 汇编导出（`export-asm.py`） |
| Python | 3.12.3 | 工具链与校验 |

IPSW 已解出（`firmware/extracted/24A446`），无需重新提取。

## 11. 需你确认的决策（默认值已选，可直接改）

| # | 决策 | 默认 | 理由 |
|---|---|---|---|
| 1 | 是否对照旧文档/旧伪代码 | **不对照**（只记录差异） | 与上两阶段一致，避免污染证据链 |
| 2 | 是否比对本仓库外的现有程序 | **本轮不比** | 同上 |
| 3 | 运行时素材使用 | **只用 `D:\carvex-research\sysdiagnose` 作佐证** | 手上没有 24A446 抓包 |
| 4 | 传输范围 | 沿用上一阶段结论（RFCOMM/`os_channel`），USB 无证据则 `OPEN` | 与蓝牙阶段衔接 |
| 5 | 消息表深度 | **只覆盖会话/控制通道相关阶段**，业务消息标 `OPEN` | 控制范围 |
| 6 | 认证序列是否补完 | **不补**；只引用其门控结论，`OPEN-AUTH-*` 留在上一阶段 | 避免阶段膨胀 |
| 7 | 是否覆盖 CarPlay 音视频流 | **不覆盖** | 属后续 media 阶段 |

## 12. 验收方式

```bash
cd D:\carvex-research\research\protocol\iap2_control_session
python3 verify.py
# 期望：失败 0；检查项总数写进 STATUS.md 与 manifest.json
```

验收时同时检查：

- `STATUS.md` 第 1 节 12 项状态与 `manifest.json` 的 `items` 完全一致；
- 每个 `OPEN` 都能在 `manifest.json` 找到 `id` 与所在文件；
- 随机抽 3 条规范条款，能沿 `spec → analysis → source/asm` 逐级点回；
- 随机抽 2 条 `link/R-*` 引用，能在 `research/protocol/iap2_link_establish/spec/` 找到原文。
