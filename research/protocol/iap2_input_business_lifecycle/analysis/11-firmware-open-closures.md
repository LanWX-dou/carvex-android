# analysis/11 — 只用固件关闭/缩小 OPEN 项

本文件是第二轮取证：**不引入任何抓包**，只用 24A446 的字节把上一轮登记的 `OPEN` 逐项处理。
处理结果分三类：`关闭`（限定问题已有固件证据）、`缩小`（已推进但仍缺一环）、`保留`（尚未闭合）。
“尚未闭合”不意味着固件无法回答。后续analysis/12–14修正与补证已同步到本页。

## 11.1 方法

1. 把上一轮"缺证据"的函数补进 `selection.json`（新增组 `O`，30 个地址）；
2. 重新导出汇编 + 反编译（`readable/` 新增 25 份）；
3. 对每个 `OPEN` 追到**平台调用签名或 ObjC 选择器**——本构建里平台层选择器是显式命名的，
   比消息层更有信息量；
4. 需要全镜像统计的（例如"是否还有别的消息 ID"）用整镜像扫描，而不是抽样。

`A11.0`：本轮新增证据全部来自同一份二进制（哈希不变），没有引入外部材料。

## 11.2 关闭的项

| OPEN | 结论 | 依据 |
|---|---|---|
| `OPEN-INP-2`（历史关闭） | `0x6805` 参数 1=报告类型、2=报告 ID、3=报告数据 | analysis/13：跳表→捕获+32/+33→回调w2/w3→平台转发x4/x5→原镜像selector；C17静态回归 |
| `OPEN-NP-2` | 四条 NowPlaying 更新路径发出的**都是 `0x5001`** | 整镜像扫描：`mov w1,#0x5xxx` 只有 4 处，全部是 `0x5001`（`0x100003230`、`0x100012448`、`0x100146ac8`、`0x10014890c`）；共享片段 `0x100012440` 被 `0x10014569c`（媒体项属性）、`0x1001474b4`（队列变化）、`0x100148f40`（初始更新）调用，片段内容为 `mov w1,#0x5001; mov w3,#0xffff; ret` |
| `OPEN-NAV-1` | 必需表失败时局部返回0，无专属回包；不保证外层无日志（A12.6纠错） | `0x1001755c0` 跳 `0x100175908`；参数解析早于该检查 |
| `OPEN-NAV-6` | `required`（表项 +8 字节）语义：0 = 不参与 AND，仅置"任一存在"位；1 = 必须存在 | `0x100050c2c`：`bVar8 \|= present`（输出"任一存在"）、`bVar9 &= (flag ^ 1) \| present`（输出"全部必需都满足"） |
| `OPEN-LIFE-1` | SUS 包**没有载荷**；挂起不携带参数区 | `_iAP2PacketCreateSUSPacket(link, seq)` → `_iAP2PacketCreate(link, 8, seq, 0, 0, 0, 0, 1)`（`0x100103210`），payload 指针与长度都是 0 |
| `OPEN-LIFE-3` | 挂起/恢复构造路径：SUS控制字节 `0x08`，ACK `0x40`；完整8字节基础头及协商校验沿用 `link/`，不是4字节头 | `0x100103210`、`0x100006f8c`及`0x100006e24`；A12.1；仅静态包型关闭，不含订阅保留/真实恢复 |
| `OPEN-LIFE-5` | 销毁顺序：先 `iAP2LinkRunLoopShuttingDown`（`0x100030f9c`），再 `sessionControl_cleanup`（`0x100030fa4`）、`sessionFileTransfer_cleanup`（`0x100030fac`）、`sessionLog_cleanup`（`0x100030fb4`）；上一轮说的"三个未命名调用"其实是两个惰性绑定桩 `0x1001a2260`×2、`0x1001a2180`（`braa` 经 GOT，目标导入未解析） | `0x100030d4c` 的调用序列 |

`A11.1`：`0x6805`字段顺序由analysis/13完整数据流补证。
Ghidra形参名可能由selector推导，不能算第二份独立证据；旧local_c0=1/2/3说法也不成立，
实际参数1/2各有一个出现标记，值经w22/w21捕获。

`A11.2`：NowPlaying"只有一条出站消息"是全镜像统计结论，不是抽样结论。
它的前提是"消息 ID 以 16 位立即数写进 `w1`"——这一点在 4 处发送点都被满足，且没有第 5 处。

## 11.3 缩小的项

| OPEN | 现在的边界 | 仍缺什么 |
|---|---|---|
| `OPEN-INP-1` | `0x6800` 的参数 1/2 分别作为两个独立 type=8 值进入 `registerHIDDescriptor:componentID:dictionary:`（`0x1000b2c6c`）的字典；参数 3（U8）作为另一个字典值 | 两个 16 位字典值的字段名/单位 |
| `OPEN-INP-3` | HID 组件在识别阶段带 `functionType`（组件结构 +16，取值 `< 0xb`，`0x100043704`），且识别日志明确有 `HIDComponent_Function` 参数 | `functionType` 的取值枚举里哪一个代表触摸/数字化仪 |
| `OPEN-NP-3` | A14.3已证三个U32对应播放时间、队列索引、列表窗口起点；参数2=0xffffffff自动选择 | 时间单位、平台有效值/失败反馈 |
| `OPEN-LIFE-2` | 恢复用 ACK 包，帧头 `hdr[5]=link[0xBE]`、`hdr[6]=link[0xBC]`、`hdr[7]=0`（A12.1纠错），无载荷（`0x100006f8c` + `0x1000302a0` 的实参） | 为什么用 ACK 而不是独立的 RES；`link[0xBC]` 的语义 |
| `OPEN-LIFE-4` | 四个域的计数最终都落到 `ACCFeatureServer`（ObjC）：HID 的 increment 在计数变为 1 时启动插件（`0x1000b3068`），decrement 无返回值（`0x1000b3110`） | 计数为 0 时再 decrement 的下溢行为（在 ObjC 实现里） |

`A11.3`：`0x5200` 的参数1–5不是显示能力。**本轮A12.5进一步修正**：它们是空值options标记，
组件列表来自参数0；旧“1–5组件列表”推断撤回。平台调用是
`_platform_navigation_startRouteGuidance(endpoint, componentIdList, options)`
（`0x1000dc778`，日志 `navigation startRouteGuidance: %@, componentIdList=%@, options=%llxh`）。
显示能力（7 个 `displayComponentAdd*`）由**识别消息解析器** `__parseIdentificationParams`
（`0x1000c5704`）在识别阶段设置，7 个调用点分别在 `0x1000c5c78`–`0x1000c5d38`。

`A11.4`：这条结论**修正**了上一轮 `A05.3` 的说法（原写作"参数 1–5 是显示能力"）。
`R-3.4`、`R-3.12` 与 `analysis/05` 相应段落已改写。

## 11.4 原保留项的后续工作（撤回“固件回答不了”的笼统分类）

| OPEN | 已证边界与下一步证据 |
|---|---|
| `OPEN-NP-1` | A14.1已关闭：参数0/1经+8/+10到media/playback计数；不需运行时确认 |
| `OPEN-NP-4` | A14.2已缩小：旧订阅先移除；继续追实际AccessoryNowPlayingClient、PlaybackQueueList清理、队列与容器；ObjC不是静态障碍 |
| `OPEN-NP-5` | A14.3已找到逐字段差异：参数2即时请求有订阅子项门；继续追初始化和消费者 |
| `OPEN-NAV-3` | 继续核逐参数解析、转发和平台消费者可接受集合；车机实际发送哪些是另一层问题 |
| `OPEN-NAV-4` | 继续定位keyForType类方法及键表；未导出切片/符号不等于镜像无实现 |
| `OPEN-NAV-5` | 继续追更新处理器、状态初始化及平台消费；不能笼统说“顺序只能运行验证” |
| `OPEN-INP-3`（枚举部分） | 继续追functionType消费者、描述符与报告路由，不能仅因未见命名表就认定静态不可解 |
| `OPEN-LIFE-6` | 需要第二份构建或第二台车机 |
| `OPEN-INP-ALL` | 真实互通验收缺口；与静态报文格式/字段核实分开，不作所有规则的阻塞前提 |

## 11.5 统计

| 分类 | 数量 | 编号 |
|---|---|---|
| 关闭 | 8 | `OPEN-INP-2`、`OPEN-NP-1`、`OPEN-NP-2`、`OPEN-NAV-1`、`OPEN-NAV-6`、`OPEN-LIFE-1`、`OPEN-LIFE-3`、`OPEN-LIFE-5` |
| 缩小 | 6 | `OPEN-INP-1`、`OPEN-INP-3`、`OPEN-NP-3`、`OPEN-NP-4`、`OPEN-LIFE-2`、`OPEN-LIFE-4` |
| 保留 | 7 | `OPEN-NP-5`、`OPEN-NAV-3`、`OPEN-NAV-4`、`OPEN-NAV-5`、`OPEN-LIFE-6`、`OPEN-INP-ALL`、`OPEN-NAV-2` |

`A11.5`：含A14补证后，21个历史编号为8关闭、6缩小、7保留。
不把剩余13项统称为外部证据缺口；已关闭项按各自审计的限定范围引用。
