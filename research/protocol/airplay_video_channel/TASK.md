# AirPlay 视频通道（发送方向）— 任务要求（`airplay_video_channel`）

> 本文件是第四阶段的任务书，结构与 `research/protocol/bluetooth_rfcomm/`、`research/protocol/iap2_link_establish/`、`research/protocol/iap2_control_session/` 一致。
> 目标：在同一份固件构建（24A446 / iOS 27.0.1 / iPhone18,1）上，用同样的严格证据链，产出 **AirPlay 视频通道（屏幕流，发送方向）** 的平台无关规范。

---

## 0. 阶段定位

```text
bluetooth_rfcomm      —— 蓝牙经典 RFCOMM 承载
iap2_link_establish   —— iAP2 链路
iap2_control_session  —— iAP2 会话层 / 控制会话 / 0x4301 启动 CarPlay
        ↓  控制面完成、AirPlay 会话已建立
【本阶段】airplay_video_channel —— 屏幕流：建流、记录格式、加密、载荷、时序、恢复
```

**客户端方向（本阶段的根本前提）**：客户端 = **设备侧**（模拟 iPhone），车机 = accessory = AirPlay **接收端**。
因此本阶段的"视频"是**手机编码后发给车机显示**的屏幕流，客户端是**发送端**，不是接收端。

### 0.1 与旧任务书（`research/protocol/airplay_video_channel.md`）的偏差

旧任务书按"接收端"口径写了 12 项覆盖要求（含"解码""显示"）。本阶段做两处修正，并在全文中保持：

| 旧口径 | 本阶段口径 | 原因 |
|---|---|---|
| 解密 RTP 载荷后解码显示 | **加密并发送**帧；"解码"只作为**对端解码器的输入约束** | 客户端是发送端 |
| 访问单元 = 解码器输入 | 访问单元 = **编码器输出**，以时间戳/关键帧标志组织 | 同上 |

12 项覆盖要求本身不删减，只把"必须回答的问题"改写成发送端要回答的问题（见 §5）。

## 1. 目标与完成判据

**目标**：给出视频（屏幕）通道的完整、可复现、逐条可追溯到固件字节的规范，使第三方实现能在自己的 AirPlay 会话之上：

1. 建立一块屏幕的媒体流（选类型、选传输、发 SETUP、解析响应）；
2. 按固件定义的 128 字节记录头封装屏幕帧；
3. 按正确顺序加密（头与载荷分别处理）；
4. 组织访问单元与时间戳，让对端解码器可解；
5. 响应车机的关键帧请求、清屏、断流；
6. 在断流/重连后恢复画面。

**完成判据**：

1. 12 项覆盖要求逐项有固件/汇编依据，或明确标 `OPEN`；
2. `verify.py` 通过（哈希、字节切片、头部标记、地址窗口、常量重算、跨 docset 引用、OPEN 登记、12 项自洽）；
3. `STATUS.md` 给出三态统计与采样声明；
4. 每条 `spec/` 条款能点回 `analysis/` 的 `A` 编号，再点回 `source/asm/` 的地址；
5. **不得**把"记录格式可证"写成"画面可证"：本阶段没有任何 24A446 视频抓包。

## 2. 素材与目标二进制

| 项 | 值 |
|---|---|
| 路径（构建内） | `/System/Library/PrivateFrameworks/AirPlaySender.framework/AirPlaySender` |
| 本地路径 | `firmware/extracted/24A446/binaries/AirPlaySender/AirPlaySender` |
| 大小 | 4,397,312 B |
| SHA256 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` |
| LC_UUID | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` |
| 函数起点（LC_FUNCTION_STARTS） | 11,443 |
| 符号数 | 14,277 |

**为什么是 AirPlaySender**：屏幕流对象（`APEndpointStreamScreen*`）、128 字节记录头（`sbpd_*`）、加密包装（`_sbpd_encryptBBuf`）、AVC 封装（`APEndpointStreamScreenAVCWrapper`）、车机命令分发（`carEndpoint_processEventCreatingResponse`）全在这一个二进制里。

**运行时素材**：`D:\carvex-research\sysdiagnose`（23G90）只作旁证；本阶段**没有**视频抓包，凡需要真实码流/真实协商结果的结论一律 `OPEN`。

## 3. 方法与证据链

1. 固件原始字节 → Mach-O 元数据定位函数区间 → 取原始字节并算哈希；
2. Capstone 导出原始 ARM64 汇编（不改写）；
3. Ghidra 反编译只作阅读辅助，标 `DECOMPILED_UNREVIEWED`；
4. 人工对照汇编核对，每条结论写指令地址；
5. `analysis/`：`A` 编号结论 + 未确认点 + 实现影响；
6. `spec/`：`R` 编号条款（MUST / SHOULD / 未定义）+ 测试向量 + 一致性清单。

视频通道特有要求：

- **按记录类型分**：帧记录、配置记录、用户数据/统计记录分开写，不得混成一个"包格式"；
- **头与载荷分开**：头是明文还是密文、是否进 AAD，必须给出调用点；
- **时间戳必须写清基准**：帧时间戳来自哪次转换、单位、上限；
- **关键帧必须写清来源**：编码器标记、头标志位、车机命令三者谁决定。

## 4. 抽样策略

- 定向抽样：屏幕流创建 → SETUP → 记录头 → 加密 → AVC 封装 → 恢复；
- 采样率如实声明（`n / 11,443`），不得暗示全栈覆盖；
- 被结论依赖但未读的函数，显式标"未读，结论仅基于调用点"。

## 5. 覆盖要求（12 项，发送端口径）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **视频流建立** | 屏幕流类型是 110/111 中的哪个？TCP 还是 UDP 变体？SETUP 请求/响应各要什么字段？ |
| 2 | **视频封装** | 载荷里是 Annex-B 还是 AVCC？SPS/PPS 在带内还是带外？ |
| 3 | **记录/载荷格式** | 128 字节头各字段？长度字段宽度？记录类型有几种？ |
| 4 | **访问单元** | 一帧如何由记录承载？时间戳/帧间隔数组怎么填？ |
| 5 | **加密位置与顺序** | 头与载荷分别怎么处理？AAD 是什么？计数器怎么走？ |
| 6 | **SPS/PPS** | 何时发？变化怎么办？由谁产生？ |
| 7 | **关键帧** | 谁是 IDR？头标志位含义？车机如何请求关键帧？ |
| 8 | **对端解码约束** | 编码配置（码率/帧率/HDR/呈现模式）里哪些必须与对端协商？ |
| 9 | **显示与同步** | 几何（像素/物理/视图区）怎么传？呈现时间基准？ |
| 10 | **重连** | 断流怎么检测？重连后要重发什么？ |
| 11 | **错误分类** | 黑屏/花屏/卡顿分别对应哪条路径失败？ |
| 12 | **版本与性能** | 编码参数、HDR 模式、多屏差异？哪些可证、哪些 `OPEN`？ |

## 6. 交付物

| 交付物 | 要求 |
|---|---|
| `source/` | 原始二进制（带哈希）、每函数 `.s` + `.bin` + `index.json`、Mach-O 元数据 |
| `readable/` | 与 `source/` 一一对应的自动反编译，标"未人工确认" |
| `analysis/` | 逐主题：地址、调用关系、数据流、依据/未确认点/实现影响 |
| `spec/` | 平台无关条款、每章"本章依据"表、一致性清单 |
| `runtime/` | 只有旁证时说明"非 24A446、未解析出视频事件" |
| `manifest.json` | 全量哈希、12 项状态、OPEN 索引 |
| `verify.py` | 自动校验（见 §6.1） |
| `STATUS.md` | 三态统计、覆盖率、能否指导实现 |

### 6.1 `verify.py` 至少校验

1. 源二进制 SHA256 与 `coverage.json` / `manifest.json` 一致；
2. 每个 `.bin` 与源二进制对应区间逐字节相同；
3. `.s` / `.ghidra.c` 头部含正确地址、源哈希、"未人工确认"标记；
4. 文档引用的地址落在 `__TEXT` 窗口内；
5. 规范中的常量（记录类型、0x80、0x12、0x6e/0x6f、0x10/0x80 标志）与 `analysis/` 一致；
6. `ctrl/R-*`、`link/R-*` 引用在对应 docset 中存在；
7. 每个 `OPEN-VID-n` 登记在 `coverage.json` 且被至少一个覆盖项引用；
8. 12 项状态与 `summary` 自洽；未出现无据的"全部确认"。

## 7. 状态报告要求（`STATUS.md`）

1. 12 项逐项状态：已确认 / 部分确认 / OPEN，证据强度分级；
2. 采样声明（`n / 11,443`）；
3. 强制实现决策逐条列出（记录类型取值、头长度、默认码率候选）；
4. 任一项仍为 OPEN 时只能写"部分完成 + 剩余清单"。

## 8. 严禁事项

1. 不得修改 `source/` 下任何文件；不得改写反汇编。
2. 不得把 Ghidra 反编译输出当结论依据。
3. 不得引用旧分析、旧伪代码、开源实现作为确认依据（可作线索，必须标注）。
4. 不得用不同构建的日志/抓包确认常量。
5. 不得在 `spec/` 出现具体语言、库、框架、操作系统 API。
6. 不得把"解出一帧"写成"投屏可用"。
7. 不得把 UDP 变体（RTP）与 TCP 变体（记录帧）混成一条路径。

## 9. 既有线索的处理

| 线索 | 位置 | 处理方式 |
|---|---|---|
| 上一阶段 docset | `research/protocol/iap2_control_session/` | 可引用（`ctrl/` 前缀） |
| 链路阶段 docset | `research/protocol/iap2_link_establish/` | 可引用（`link/` 前缀） |
| 既有 AirPlay 分析 | `firmware/analysis/24A446/screen-*`、`AirPlaySender-*.ghidra.c` | 只作线索与种子；结论重新取证 |
| 旧任务书 | `research/protocol/airplay_video_channel.md` | 只作范围参考 |
| sysdiagnose 23G90 | `D:\carvex-research\sysdiagnose` | 仅旁证；构建不同 |

## 10. 工具与环境

| 工具 | 版本/路径 | 用途 |
|---|---|---|
| Capstone | 5.0.7 | 汇编导出 |
| Ghidra | 12.1.4 | 反编译（只作辅助） |
| Python | 3.12+ | 工具链与校验 |
| 反编译缓存 | `firmware/analysis/decompiler-cache/24A446/AirPlaySender/934ec850a9ab7623f1d8/` | 同一二进制、源哈希已复核 |

## 11. 验收方式

```bash
cd D:\carvex-research\research\protocol\airplay_video_channel
python3 verify.py
# 期望：failures 0；检查项总数写进 STATUS.md 与 manifest.json
```
