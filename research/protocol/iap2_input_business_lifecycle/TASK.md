# iAP2 输入、业务数据与生命周期 — 任务要求（`iap2_input_business_lifecycle`）

> 本文件是第四阶段的落地任务书。原始任务书是 `research/protocol/iap2_input_business_lifecycle.md`（用户提供），
> 本文件在它基础上补齐：与前三个 docset 的边界、实际交付物布局、以及"证据优先"的硬性口径。
>
> 口径：`CONFIRMED` 只表示"在本阶段证据范围内可复核"；消息 ID、参数、门控必须以固件字节 / 抓包为准。
> 拿不到证据的一律登记 `OPEN-INP-*` / `OPEN-NP-*` / `OPEN-NAV-*` / `OPEN-LIFE-*`，不得写成"已确认"。

---

## 0. 阶段定位

前三个阶段已闭合的边界（可引用，引用时带前缀）：

| 阶段 | docset | 本阶段可用的结论 |
|---|---|---|
| 一 | `research/protocol/bluetooth_rfcomm/`（`bt/`） | RFCOMM 通道建立与 `os_channel` 字节流 |
| 二 | `research/protocol/iap2_link_establish/`（`link/`） | 链路 FSM、6 字节消息头、参数 4 字节头、识别/认证消息与门控 |
| 三 | `research/protocol/iap2_control_session/`（`sess/`） | 会话表、`hdr[7]` 会话号、5 类数据面、特性注册（29 项/27 表/96 处理器）、两张准入名单、`0x4301` 启动路径 |

```text
链路 Connected（link/R-6.9）
        ↓
识别 → 认证（link/ R-6.x）
        ↓
控制会话版本门控 + 特性启动（sess/ R-4.x）
        ↓
【本阶段】输入 / 业务 / 生命周期
  ├─ HID：StartHID / AccessoryHIDReport / StopHID / GetReportResponse（+3 条出站）
  ├─ NowPlaying：0x5000 订阅、0x5002 退订、0x5003 设置、0x5001 更新
  ├─ 导航：0x5200 / 0x5203 / 0x0D01（+出站 0x5201 / 0x5202 / 0x5204 / 0x0D02）
  ├─ 触摸（AssistiveTouch）：0x5400 / 0x5401 / 0x5402 / 0x5404（+出站 0x5403）
  └─ 生命周期：挂起 / 恢复 / 断连 / 资源清理
        ↓
车机 UI / 业务功能
```

**本阶段只回答**：按键/触摸/旋钮怎么传、NowPlaying 订阅与更新怎么走、HUD 字段怎么给、
挂起/恢复/断连时状态怎么保持或清理、资源怎么释放。

**不回答**：音频/视频编解码、FairPlay、RTP 时序、AirPlay 控制面、`0x4301` 的字段映射（那是 `sess/OPEN-SES-2`）。

---

## 1. 目标与完成判据

**目标**：产出可复现的输入/业务/生命周期规范，使第三方**设备侧**实现（模拟 iPhone 的一端）能够：

1. 在认证/识别/特性门控满足后，正确接收并处理车机发来的 HID / 触摸 / NowPlaying / 导航消息；
2. 按车机订阅情况，正确发送 NowPlaying 更新与导航更新；
3. 处理挂起、恢复、断连与资源清理，且清理幂等。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求（第 5 节）逐项有固件依据，或明确标 `OPEN-*`；
2. `verify.py` 通过；
3. `STATUS.md` 给出三态统计与采样覆盖率（`n / 8,706`）；
4. 每条规范条款能点回 `analysis/` 的 `A` 编号，再点回 `source/asm/` 的地址与字节；
5. 跨 docset 引用带前缀（`link/`、`sess/`），且能在对方文件中找到。

**本阶段明确做不到的事（必须先写在前面）**：

- 手上**没有**含 HID/触摸/NowPlaying/导航消息的抓包。23G90 那份蓝牙抓包只到 `0x5702/0x4E0D/0x4E0E/0x5703`（Wi‑Fi Sharing/设备信息），
  没有一条本阶段的消息。因此"线上字节长什么样"只有**固件侧编码路径**证据，没有第二来源交叉验证。
- 因此第 5 节第 12 项（差异）与所有"字段单位/量纲"类问题只能是 `OPEN`，不能靠猜。

---

## 2. 素材与目标二进制

| 项 | 值 |
|---|---|
| 路径（构建内） | `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd` |
| 本地路径 | `research/protocol/iap2_input_business_lifecycle/source/firmware/accessoryd` |
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 函数数 | 8,706（LC_FUNCTION_STARTS） |
| 构建 | 24A446 / iOS 27.0.1 / iPhone18,1 |

**次级目标**：`carkitd` / CarPlay 框架只作交叉核对，不据其下结论。

---

## 3. 方法与证据链

1. 固件原始字节 → 2. Capstone 原始汇编 → 3. Ghidra 反编译（`DECOMPILED_UNREVIEWED`）→
4. 人工对照汇编核对（每条结论写指令地址）→ 5. `analysis/` 的 `A` 编号 → 6. `spec/` 的 `R` 编号。

本阶段特有的取证手段（都已落成工具，见第 10 节）：

- **特性表 → 处理器表 → 消息 ID**：`tables.json` + `gen-input-handler-facts.py` 直接把
  "哪个 `msg_id` 由哪个函数处理"读出来，不靠命名猜；
- **参数分派表**：处理器里的 `cmp w0,#N` + `ldrsw` 跳表被解成"参数 ID → 取值函数"，取值函数按
  长度校验分成 U8/U16/数据/字符串；
- **可打印字符串**：处理器引用到的 `os_log` 格式串给出字段名旁证（必须给地址）；
- **符号名**：`symbols.json` 里存在大量真实符号（`_iap2_hid_*`、`_iap2_nowPlaying_*`、
  `_iap2_navigation_*`、`_iap2_assistiveTouch_*`），这是本阶段最强的语义证据——但仍要回到指令核对。

---

## 4. 抽样策略

- 按主题定向采样：HID 特性 11、NowPlaying 特性 14、导航特性 17、AssistiveTouch 特性 3、
  生命周期（挂起/恢复/断开）；
- 采样率如实声明（`n / 8,706`），不得暗示全栈覆盖；
- 被结论依赖但未读的函数，显式标注"未读，结论仅基于调用点"。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **HID 能力** | 车机通过哪几条消息注册 HID 组件？组件标识怎么来？描述符在哪条消息里？ |
| 2 | **按键报告** | 报告从哪条消息进来？参数结构？谁做长度/类型校验？ |
| 3 | **触摸** | 触摸走 HID 还是 AssistiveTouch（0x54xx）？字段与坐标谁定义？ |
| 4 | **NowPlaying 50xx** | 0x5000/0x5002/0x5003/0x5001 的方向、参数、订阅语义、子参数结构？ |
| 5 | **导航 HUD 52xx** | 0x5200/0x5203/0x0D01 与出站 0x5201/0x5202/0x5204/0x0D02 的方向与字段？ |
| 6 | **门控** | 这些消息在两张准入名单里的位置？不满足时行为？ |
| 7 | **消息顺序** | 订阅→更新、开始导航→更新→停止的时序与前置条件？ |
| 8 | **断连** | 谁检测？走了哪些回调？队列/订阅者怎么处理？ |
| 9 | **休眠/恢复** | 谁发起？链路层动作是什么？状态保留还是重置？ |
| 10 | **资源清理** | 释放顺序、幂等性、用户计数（user count）模型？ |
| 11 | **错误与重试** | 非法参数、缺参数、重复消息的处理？ |
| 12 | **版本与差异** | 与 24A446 之外的车机/固件差异；所有无证据点汇总 `OPEN` |

### 5.1 `analysis/` 文件划分（实际）

| 文件 | 内容 |
|---|---|
| `00-method-and-environment.md` | 方法、工具链、可复现命令、抽样策略、与前三阶段的引用约定 |
| `01-input-business-map.md` | 特性表 → 消息 → 处理器总图；方向判定方法；本阶段消息全集 |
| `02-handler-facts.md` | **机器生成**：逐处理器的参数分派表、调用序列、字符串（不接受手工编辑） |
| `03-hid.md` | HID 四条入站 + 三条出站、组件校验、描述符与报告路径 |
| `04-nowplaying.md` | 0x5000/0x5002/0x5003/0x5001、子参数、订阅者与 artwork 文件传输 |
| `05-navigation-hud.md` | 0x5200/0x5203/0x0D01、出站 0x5201/0x5202/0x5204/0x0D02、字段键与状态映射 |
| `06-gating-and-order.md` | 两张名单、`auth==2 ∧ ident==6`、订阅/开始导航的前置 |
| `07-lifecycle.md` | 挂起/恢复消息与链路动作、休眠通知、断连路径 |
| `08-cleanup.md` | detach/销毁顺序、幂等、用户计数 |
| `09-runtime-evidence.md` | 23G90 抓包能证什么/不能证什么；采集计划 |
| `10-function-inventory.md` | 采样清单与未读声明 |
| `A-conclusions.md` | 结论登记表：spec 的 `依据` 只能引用这里的 `A` 编号 |

### 5.2 `spec/` 文件划分（实际）

| 文件 | 条款区间 |
|---|---|
| `00-scope-and-terms.md` | `R-0.x` 范围、术语、方向约定 |
| `01-input-hid.md` | `R-1.x` HID 消息与参数 |
| `02-nowplaying.md` | `R-2.x` NowPlaying 订阅与更新 |
| `03-navigation-hud.md` | `R-3.x` 导航/HUD 消息与字段 |
| `04-touch.md` | `R-4.x` 触摸（AssistiveTouch） |
| `05-gating-and-order.md` | `R-5.x` 门控与顺序 |
| `06-lifecycle.md` | `R-6.x` 挂起/恢复/断连 |
| `07-cleanup.md` | `R-7.x` 清理与幂等 |
| `08-client-guide.md` | `R-8.x` 设备侧施工指南（能实现什么/不能实现什么） |
| `09-conformance-checklist.md` | 核对清单 + 不得声称的事项 |
| `10-open-items.md` | `OPEN-*` 登记与关闭条件 |

---

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 二进制（带哈希）、每函数 `.s` + `.bin` + `index.json`、Mach-O 元数据、Ghidra 请求 |
| `readable/` | 与 `source/` 一一对应的自动反编译，全部带"未人工确认" |
| `analysis/` | 逐主题：地址、调用关系、数据流、每条结论的固件依据/未确认点/实现影响 |
| `spec/` | 平台无关条款（MUST/SHOULD/未定义）、每章"本章依据"表 |
| `runtime/` | 只有佐证，必须声明构建差异 |
| `reference-impl/` | 编解码参考实现 + 自测向量 + 生命周期状态机（可执行，供 `verify.py` 比对） |
| `manifest.json` | 全量文件哈希、12 项状态、`OPEN` 索引 |
| `function-index.json` | 每个函数的地址/大小/哈希/被引用位置 |
| `verify.py` | 自动校验 |
| `STATUS.md` | 三态统计、覆盖率、能否指导实现 |

### 6.1 `verify.py` 至少校验

1. 源二进制 SHA256 与 `manifest.json` / `function-index.json` 一致；
2. 每个 `.bin` 与源二进制对应区间逐字节相同；
3. `.s` / `.ghidra.c` 头部含地址、源哈希、"未人工确认"标记；
4. 文档引用的地址都落在镜像地址窗口内；
5. 用固件常量重新计算消息/参数编码测试向量；
6. 规范常量与 `analysis/` 提取值一致；
7. `source/` 无未登记文件；
8. 跨 docset 引用（`link/`、`sess/`）可解析。

---

## 7. 状态报告要求

1. 12 项覆盖要求逐项状态（已确认 / 部分确认 / OPEN）与证据强度；
2. 采样覆盖率声明；
3. 强制实现决策（缺省值、超时、上限）逐条列出给依据；
4. 任一项 OPEN 时不得写"已完成"。

---

## 8. 严禁事项

1. 不得修改 `source/`；不得把反汇编改写成伪代码充当"原始汇编"。
2. 不得把 Ghidra 输出直接当结论；必须人工对照汇编。
3. 不得引用旧分析、旧伪代码、外部文档、开源实现作为**确认依据**（可作线索，必须标注）。
4. 不得用不同构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、OS API 名称。
6. 不得把"收到消息"写成"业务已生效"。
7. 不得在没抓到帧的情况下声称"线上格式已确认"。

---

## 9. 既有线索

| 线索 | 位置 | 处理 |
|---|---|---|
| 前三个阶段 docset | `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/`、`research/protocol/iap2_control_session/` | **可引用**（带前缀）；只引用 `CONFIRMED`/`MUST` 条款 |
| 23G90 蓝牙抓包 | `research/protocol/iap2_control_session/runtime/` | 仅佐证；不含本阶段消息 |
| 旧 iAP2 分析 / 伪代码 | `firmware/analysis/24A446/iap2-*`、`/mnt/d/ios-carplay/pseudocode` | 只作线索，须重新取证 |
| `carkitd` | 构建内 | 仅交叉核对 |

---

## 10. 工具与环境

| 工具 | 用途 |
|---|---|
| `firmware/tools/scaffold-input-lifecycle.py` | 建立 `source/` 与 `selection.json` |
| `firmware/tools/export-asm.py` | Capstone 原始汇编导出 |
| `firmware/tools/build-ghidra-request.py` + `ghidra-scripts/ExportDecomp.java` | Ghidra 反编译 |
| `firmware/tools/extract-feature-table.py <docset>` | 特性信息表 → `tables.json` |
| `firmware/tools/scan-handler-params.py <docset> <addr>...` | 处理器的参数 ID → 取值函数 |
| `firmware/tools/gen-input-handler-facts.py <docset>` | 生成 `analysis/02-handler-facts.md` |
| `firmware/tools/scan-msgid-refs.py <docset>` / `scan-msgid-sites.py <docset>` | 全镜像消息 ID 引用/发送点扫描 |
| `firmware/tools/gen-function-index.py` / `gen-manifest.py` | 索引与清单 |

Ghidra 12.1.4 + JDK 21（WSL 内执行，工程 `firmware/analysis/24A446/iap2-link/project` 属 root）；
Capstone 5.0.7；Python 3.13。

---

## 11. 本次默认决策

| # | 决策 | 默认 | 理由 |
|---|---|---|---|
| 1 | 是否对照旧文档/旧伪代码 | 不对照，只记录差异 | 与前三个阶段一致 |
| 2 | 抓包 | 复用 23G90（不含本阶段消息），并写清采集计划 | 手上没有第二份 |
| 3 | 触摸归属 | 以固件为准：HID（0x68xx）与 AssistiveTouch（0x54xx）分开写 | 特性表里是两个特性 |
| 4 | 音频/视频 | 不覆盖 | 属后续阶段 |
| 5 | `0x4301` | 不重开，引用 `sess/OPEN-SES-2` | 上一阶段边界 |

---

## 12. 验收方式

```bash
cd D:\carvex-research\research\protocol\iap2_input_business_lifecycle
python3 verify.py
# 期望：failures 0
```

同时检查：`STATUS.md` 12 项与 `manifest.json` 一致；每个 `OPEN` 能在 manifest 找到；
随机抽 3 条条款能沿 `spec → analysis → source/asm` 点回。
