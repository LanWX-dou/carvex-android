# STATUS — iAP2 链路建立阶段（构建 24A446）

**结论一句话**：`accessoryd` 中 iAP2 链路建立阶段的帧格式、校验、SYN 协商、序号/确认、8 状态机、Detect 控制帧与消息表已完成"固件 → 汇编 → 规范"的可复核闭环；识别/认证/会话启动只到**消息级**（哪个 `msg_id` 由哪个函数处理），其载荷与顺序仍为 `OPEN`。

## 1. 交付物

```
research/protocol/iap2_link_establish/
  TASK.md                     本阶段任务书（未修改）
  source/
    firmware/accessoryd       目标二进制副本（SHA256 校验）
    metadata/                 段表、符号、函数起点、选点表、表解码、Ghidra 请求
    asm/accessoryd/           143 个函数的原始汇编 + 原始字节切片 + index.json
  readable/
    ghidra/accessoryd/        143 个函数的 Ghidra 原始 C 输出（DECOMPILED_UNREVIEWED）
    README.md                 使用规则与哈希链说明
  analysis/                   16 份分析（00–15），含 A 编号结论
  spec/                       10 份平台无关规范（00–09），含 R 编号条款
  reference-impl/             非规范性参考实现（帧/校验/SYN/序号）+ 26 项自检
  runtime/observations.md     运行时素材与边界（无 24A446 抓包）
  reference/                  术语、地址速查、1,347 条符号
  function-index.json         143 个函数的地址/哈希/被引用文档/取证状态
  manifest.json               全部文件的大小与 SHA256 + 未决项登记
  verify.py                   8 类验收检查（含参考实现自检）
```

## 2. 三态统计

| 维度 | 数量 |
|---|---|
| `spec/` 条款总数 | 102 |
| ├ `CONFIRMED`（固件字节直接证明） | 85 |
| ├ `INFERRED`（结构/符号推断） | 3 |
| └ `OPEN`（未证明，不得依赖） | 14 |
| `analysis/` 带状态的结论锚点 | 107 |
| 未决项（`OPEN-*`） | 65 |

条款分布：`R-1` 17 条、`R-2` 12 条、`R-3` 10 条、`R-4` 12 条、`R-5` 11 条、`R-6` 22 条、`R-7` 13 条、`R-8` 3 条、`R-9` 2 条，合计 **102** 条。

### 12 项覆盖要求的状态

| # | 要求 | 状态 | 证据强度 | 未决项 |
|---|---|---|---|---|
| 1 | 传输绑定 | 部分确认 | firmware+asm | `OPEN-TX-1`, `OPEN-TX-2`, `OPEN-TX-3`, `OPEN-TX-4` |
| 2 | 链路层初始化 | 部分确认 | firmware+asm | `OPEN-INIT-1`, `OPEN-INIT-2`, `OPEN-INIT-3`, `OPEN-INIT-4` |
| 3 | 帧格式 | 已确认 | firmware+asm | `OPEN-FRAME-1`, `OPEN-FRAME-3`, `OPEN-FRAME-5`, `OPEN-FRAME-6` |
| 4 | SYN 协商 | 部分确认 | firmware+asm | `OPEN-SYN-1`, `OPEN-SYN-2`, `OPEN-SYN-4`, `OPEN-SYN-5` |
| 5 | 序号/确认/重传 | 部分确认 | firmware+asm | `OPEN-SEQ-1`, `OPEN-SEQ-2`, `OPEN-SEQ-3`, `OPEN-SEQ-5` |
| 6 | 链路状态机 | 已确认 | firmware+asm | `OPEN-FSM-1`, `OPEN-FSM-2`, `OPEN-FSM-3`, `OPEN-FSM-4` |
| 7 | IDPS 阶段 | 部分确认 | firmware+asm | `OPEN-IDPS-1`, `OPEN-IDPS-2`, `OPEN-IDPS-3`, `OPEN-IDPS-4` |
| 8 | 识别阶段 | 部分确认 | firmware+asm | `OPEN-ID-1`, `OPEN-ID-2`, `OPEN-ID-4`, `OPEN-ID-5` |
| 9 | 认证阶段 | 部分确认 | firmware+asm | `OPEN-AUTH-1`, `OPEN-AUTH-2`, `OPEN-AUTH-3`, `OPEN-AUTH-5` |
| 10 | 会话启动边界 | 部分确认 | firmware+asm | `OPEN-SES-1`, `OPEN-SES-2`, `OPEN-SES-3`, `OPEN-SES-4` |
| 11 | 异常与清理 | 部分确认 | firmware+asm | `OPEN-ERR-1`, `OPEN-ERR-2`, `OPEN-ERR-3`, `OPEN-ERR-4` |
| 12 | 差异与未知 | 部分确认 | firmware+asm | `OPEN-RUNTIME-1` |

## 3. 采样口径

- 目标二进制函数起点：**8,706**（`LC_FUNCTION_STARTS`）。
- 本阶段导出并核对的函数：**143**，占 **1.64%**。
- 这是"按链路建立阶段选点"的定向采样：`iAP2Link*` 62、`iAP2Packet*` 24、`mfi4Auth_*` 26、`iap2_*` 11、识别解析器 5、`acc_protocolParser_*` 4、`acc_auth_protocol_*` 3、`iAP2FSM*` 3、`iAP2Time*` 1。
- **不构成全二进制覆盖**；任何未在本阶段出现的代码路径都按 `OPEN` 处理。

## 4. 本次新增的关键结论（可复核）

1. **帧头 8 字节 + 校验 1/2 字节**，长度字段为**整帧长度、大端**（`R-2.1`/`R-2.2`）。
2. **两种校验**：8 位字节和两补数、16 位 20 字节分块 sum1/sum2 两补数；创建默认 8 位。链路字段 1 经 `0x1000071e4` 映射为算法 0；不能直接当算法 1（`R-2.6`–`R-2.8`）。无载荷帧不追加载荷校验。
3. **校验范围不同**：iAP2 含 `FF 5A`，传统帧不含 `FF 55`（`R-2.12`），并给出两帧独立吻合的推导（`A03.15`）。
4. **Detect 帧是静态常量** `FF 55 02 00 EE 10`（`0x1001b3378`），DetectNACK/RequestIdentify 由其规则推出（`R-2.11`）。
5. **SYN 参数 7 元组缺省**：`1/1/30/0/0xFFFF/1000/10`，其中 `+0x06=1000` 经发送路径证明是 **ACK 定时器超时（毫秒，定时器 id 0xC）**（`R-3.3`）。
6. **SYN 线格式与结构顺序不同**（载荷 2–7 为三组大端 16 位，8/9 才是 MaxRetrans/MaxCumAck）（`R-3.4`）。
7. **状态机为空 handler 不迁移**：表里 5 条空 handler 条目是"死条目"，命中后只写日志（`A06.4`、`R-5.4`），这修正了"所有表项都生效"的直觉。
8. **链式迁移**：迁移后用同一事件在新状态再跑一次（`R-5.7`）。
9. **窗口缺省 1**、最大接收包长缺省 `0xFFFF`（`0xFFFF0100` 常量，`A05.3b`）。
10. **初始序号由毫秒时钟派生**，可选加 `0x47 + link[0xbe]` 偏移（`R-4.2`）。

11. **识别参数是白名单**：`0x1D01` 由 `__parseIdentificationParams` 按参数 ID 分派，上限 `0x22`；其中只有 18 个 ID 被接受，其余（含 `0x13`）直接进拒绝路径（`R-6.3`）。
12. **transport component 编号是常量**：串行 0 / USB Device 1 / USB Host 2 / 蓝牙 3 / 无线 CarPlay 4 / 蓝牙 LE 5，每个内部再按子参数（U16 标识、名称字符串、存在性标志）解析（`R-6.3.1`）。
13. **普通认证消息直接携带参数**：`0xAA01/03/06/11/13` 不嵌套 `0x5500/0x5501`；后者属于中继路径。AccAuthentication 查询 feature 0，DeviceAuthentication 查询 feature 7（`R-6.6`、`R-6.6.1`）。23G90 的七步观测见 control `spec/11`，其他认证路径不得直接套用。


### 4.1 能否据此实现一个客户端

可以，但边界必须说清楚（详见 `spec/09`）：

| 能力 | 现状 | 依据 |
|---|---|---|
| 帧编解码、校验 | **可实现**，26 项向量可自检 | `spec/02`、`reference-impl/` |
| SYN 协商、序号/ACK/重传 | **可实现**（定时器参数需按对端调） | `spec/03`、`spec/04` |
| 8 状态机 | **可实现**（5 条惰性条目须照抄） | `spec/05` |
| 识别消息 | **可实现**（必需集合未定，需按对端反馈补） | `spec/06` `R-6.3`、`OPEN-ID-2` |
| 认证 | 普通认证参数与部分平台调用已确认；完整信任链、设备自身认证和其他 profile 仍未闭合。不能概括为“只缺 MFi 凭证” | `R-6.6`、`OPEN-AUTH-5`；control `spec/11` |
| 会话/控制通道 | 不在本阶段 | 另立阶段 |

14. **认证协议与算法层已成形**：13 条协议消息（含双向 Request/处理对）、挑战由系统随机源生成、证书链与签名验证委托平台、X.509 解析在二进制内、隧道载荷对称加解密（`R-6.6.2`、`R-6.6.3`）。消息**顺序**仍是推断（`R-6.6.4`）。

15. **认证时序已缩小到分支级**：`authType` = 0/1/2 三条分支、每条消息的应答关系（`RequestAuthCert→AuthCert`、`AuthCert→RequestAuthCert+AuthenticationSucceeded` 等）、缺省超时 10 s（`R-6.6.6`–`R-6.6.8`）。剩余未证的是"完整时序由谁推进"（`OPEN-AUTH-1`）。

16. **失败回退是类型阶梯，不是重传**：`+0x90` 位图记录已尝试的认证类型（低 4 位 + 高 2 位，最多 6 种），失败即换类型重开 `RequestAuthSetup`，全试完才上报失败（`R-6.6.9`）。状态值 `1` 失败 / `2` 成功（`R-6.6.10`）。

## 5. 未决项总表

| 组 | ID | 内容 | 首见 |
|---|---|---|---|
| AUTH | `OPEN-AUTH-1` | 认证消息的**发送顺序**与进入条件（谁先发 `0xAA10` 还是 `0xAA01`） | `analysis/09-authentication.md` |
| AUTH | `OPEN-AUTH-2` | `0x5500` 与 `0x5501` 的区别（封装函数的 flag 来源） | `analysis/09-authentication.md` |
| AUTH | `OPEN-AUTH-3` | 认证失败/超时后是否重试、重试几次 | `analysis/09-authentication.md` |
| AUTH | `OPEN-AUTH-4` | `mfi4Auth_protocol_parse` 的报文类型集合（只读了入口） | `analysis/09-authentication.md` |
| AUTH | `OPEN-AUTH-5` | 证书链校验与签名验证的具体算法（密码学，不在本阶段） | `analysis/09-authentication.md` |
| AUTH | `OPEN-AUTH-6` | NVM/中继子协议是否参与链路建立 | 新增 | `analysis/14-authentication-protocol.md` |
| AUTH | `OPEN-AUTH-7` | 认证状态回调取值 | **关闭**：1 失败 / 2 成功，见 `A14.17` | `analysis/14-authentication-protocol.md` |
| BUF | `OPEN-BUF-1` | `iAP2LinkGetBuffSize` 的缓冲区上限 | `spec/08-conformance-checklist.md` |
| ERR | `OPEN-ERR-1` | `HandleMaxRetries` 的判定与事件 `0x14` 的对应 | `analysis/11-errors-and-teardown.md` |
| ERR | `OPEN-ERR-2` | `iAP2LinkDelete` 的析构顺序与定时器/链表清理 | `analysis/11-errors-and-teardown.md` |
| ERR | `OPEN-ERR-3` | Suspend/Resume 对已排队数据与定时器的处理 | `analysis/11-errors-and-teardown.md` |
| ERR | `OPEN-ERR-4` | 链路层是否向上层报告错误码（未见独立错误回调） | `analysis/11-errors-and-teardown.md` |
| FRAME | `OPEN-FRAME-1` | 载荷校验写入宽度（1 或 2）无独立函数证据，仅有 `CurPckChksumSize` 与返回宽度推断 | `analysis/03-framing-and-checksum.md` |
| FRAME | `OPEN-FRAME-2` | `link[0x48]` 计数用途 | `analysis/03-framing-and-checksum.md` |
| FRAME | `OPEN-FRAME-3` | 控制字段 bit0–bit2 语义 | `analysis/03-framing-and-checksum.md` |
| FRAME | `OPEN-FRAME-4` | 写入来源已补证：对端 SYN 包长经工作块提交；上限联动归 OPEN-FRAME-7 | `analysis/04` A04.13 |
| FRAME | `OPEN-FRAME-5` | 逐字节解析状态机 18 个状态的完整字段映射 | `analysis/03-framing-and-checksum.md` |
| FRAME | `OPEN-FRAME-6` | `lt` 字节（hdr[6]）与 `extra` 字节（hdr[7]）的语义 | `analysis/03-framing-and-checksum.md` |
| FRAME | `OPEN-FRAME-7` | 新增：`link[0xc0]` 与 SYN `+0x16c` 一族、接收包长上限的联动关系未证 | `analysis/15-transport-seam.md` |
| FRM | `OPEN-FRM-1` | 传统帧载荷末字节（`0xEE` / `0xFE`）的语义 | `analysis/03-framing-and-checksum.md` |
| FSM | `OPEN-FSM-1` | 各状态事件表中全零条目的语义（容量 vs 有效条目） | `analysis/06-link-state-machine.md` |
| FSM | `OPEN-FSM-2` | 事件号 → 名称的完整映射（无名称表） | `analysis/06-link-state-machine.md` |
| FSM | `OPEN-FSM-3` | 事件 `0x04` / `0x06` / `0x15` / `0x19` 的精确触发点（需要 handler 与调用者交叉取证） | `analysis/06-link-state-machine.md` |
| FSM | `OPEN-FSM-4` | 状态 0（Init）只有 1 条事件，初始化流程的其余步骤不在状态机内（见 `analysis/02`） | `analysis/06-link-state-machine.md` |
| ID | `OPEN-ID-1` | 识别消息发送顺序（谁先发 `0x1D01`/`0x1D06`） | `analysis/08-identification.md` |
| ID | `OPEN-ID-2` | 必需参数集合与超时 | `analysis/08-identification.md` |
| ID | `OPEN-ID-3` | 其余 4 份 `__parseIdentificationParams` 是否等价 | `analysis/08-identification.md` |
| ID | `OPEN-ID-4` | `0x1D01`/`0x1D05`/`0x1D06` 的角色差异 | `analysis/08-identification.md` |
| ID | `OPEN-ID-5` | `0x06`/`0x07` 的"消息集合"编码（`processMessagesSet` 未读） | `analysis/08-identification.md` |
| IDPS | `OPEN-IDPS-1` | RequestIdentify 帧尾校验字节的值 | `analysis/07-idps.md` |
| IDPS | `OPEN-IDPS-2` | 传统帧分支（`0x10000abe4`）的完整解析状态 | `analysis/07-idps.md` |
| IDPS | `OPEN-IDPS-3` | `link[0x1d0]`（与 11 比较）的语义 | `analysis/07-idps.md` |
| IDPS | `OPEN-IDPS-4` | Detect / RequestIdentify 的触发者与重试策略 | `analysis/07-idps.md` |
| INIT | `OPEN-INIT-1` | 运行循环的驱动源（线程/队列/定时器） | `analysis/02-link-init-and-runloop.md` |
| INIT | `OPEN-INIT-2` | `0x1001a20b0`（`iAP2LinkCreate` 首调）的确切语义 | `analysis/02-link-init-and-runloop.md` |
| INIT | `OPEN-INIT-3` | `iAP2LinkGetBuffSize`（`0x100033ed8`）各分量的分解（只确认返回值被用于计算包区起点） | `analysis/02-link-init-and-runloop.md` |
| INIT | `OPEN-INIT-4` | `iAP2LinkRunLoopInitImplementation`（`0x100103954`）的实现体（本轮导出为空桩或跳转，未取证） | `analysis/02-link-init-and-runloop.md` |
| MSG | `OPEN-MSG-1` | 各 handler 的参数与副作用 | `analysis/12-message-table.md` |
| MSG | `OPEN-MSG-2` | `msg_id` 前缀分组的语义 | `analysis/12-message-table.md` |
| MSG | `OPEN-MSG-3` | 无符号 handler（如 Identification 的 3 个）的实际行为 | `analysis/12-message-table.md` |
| MSG | `OPEN-MSG-4` | `0x1D00`/`0x1D02`、`0xAA00`–`0xAA05` 的编号与方向来自 control docset，本 docset 未单独取证 | `spec/09-client-implementation-guide.md` |
| SEQ | `OPEN-SEQ-1` | EAK 载荷中缺失序号的编码 | `analysis/05-seq-ack-retransmit.md` |
| SEQ | `OPEN-SEQ-2` | 重传三函数（ResendData / ResendMissing / HandleMaxRetries）的完整分支与触发点 | `analysis/05-seq-ack-retransmit.md` |
| SEQ | `OPEN-SEQ-3` | 重复帧与乱序帧的判定/丢弃路径 | `analysis/05-seq-ack-retransmit.md` |
| SEQ | `OPEN-SEQ-4` | 来源已补证：对端 MOP 经工作块提交；全部窗口迁移仍需验证 | `analysis/04` A04.13 |
| SEQ | `OPEN-SEQ-5` | ACK 的"累积确认"语义是否由 seq 字段单独承载（帧头只有 1 个序号字节） | `analysis/05-seq-ack-retransmit.md` |
| SES | `OPEN-SES-1` | `link+0x120`/`+0x128` 两个链表的角色（收发包 vs 会话） | `analysis/10-session-boundary.md` |
| SES | `OPEN-SES-2` | `0x4301` 运行时平台必填性、错误/重试、所有 profile 的发起方与下游 CarPlay 结果（静态 schema 已在 control/spec/14 闭合） | `analysis/10-session-boundary.md` |
| SES | `OPEN-SES-3` | "会话已启动"的状态位与 `Connected` 的对应关系 | `analysis/10-session-boundary.md` |
| SES | `OPEN-SES-4` | 多会话并发时的路由键（服务号 vs 会话 ID） | `analysis/10-session-boundary.md` |
| SYN | `OPEN-SYN-1` | 结构 `+0x04` 两个字节的语义（疑为最大包长） | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-2` | 协商失败的完整处置路径 | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-3` | `version` 允许的最大值（`cmp w8,#4` 的上下文未完全展开） | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-4` | 扩展字节 `payload[11..11+k]` 的语义（只确认长度与复制位置） | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-5` | 特性条目 `e[1]` 取值 0..4 的具体含义（与特性 ID 的映射） | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-6` | `+0x06`（ACK 超时）合法性下限 `>19` 的原因 | `analysis/04-syn-negotiation.md` |
| SYN | `OPEN-SYN-7` | RST\|SYN（0x90）触发条件未取证（与 ACK 下限问题消歧） | `spec/09-client-implementation-guide.md` |
| TMR | `OPEN-TMR-1` | 累积确认超时的单位与调用点 | `spec/08-conformance-checklist.md` |
| TMR | `OPEN-TMR-2` | SYN 重发超时值 | `spec/08-conformance-checklist.md` |
| TMR | `OPEN-TMR-3` | 重传定时器时长 | `spec/08-conformance-checklist.md` |
| TX | `OPEN-TX-1` | 传输适配层（RFCOMM / `os_channel` / USB）到解析器的具体函数与注册点 | `analysis/01-transport-binding.md` |
| TX | `OPEN-TX-2` | `acc_protocolParser_iAP2_run` 的 11 个命令码中与"打开/写入/关闭"的对应关系 | `analysis/01-transport-binding.md` |
| TX | `OPEN-TX-3` | 运行循环 Attached 位的置位者（谁在传输就绪时置位） | `analysis/01-transport-binding.md` |
| TX | `OPEN-TX-4` | `link[0xbc]`（写入 `hdr[6]` 的字节）的赋值来源 | `analysis/01-transport-binding.md` |

另有 `OPEN-RUNTIME-1`（无 24A446 运行时抓包，见 `analysis/00-method-and-environment.md`），因此 `runtime/` 不参与任何条款的升级。

## 6. 验收

```bash
cd research/protocol/iap2_link_establish
python3 verify.py
```

`verify.py` 的 7 类检查：

| 类 | 内容 |
|---|---|
| C1 | 源二进制大小/哈希、`function-index` 与 `summary` 一致 |
| C2 | 143 个 `.bin` 与固件切片逐字节相同；`.s` 头部含地址区间与源哈希 |
| C3 | 143 个 `.ghidra.c` 存在、带未复核横幅、`loaded_code_sha256` 等于 `raw_sha256` |
| C4 | 文档中所有 `0x1…` 地址落在镜像窗口；`analysis/13` 引用的地址都在 `function-index` |
| C5 | 6 组校验和测试向量重算一致；Detect 常量与算法自洽 |
| C6 | SYN 缺省、控制位、状态数/事件数、消息 ID 与固件字节/表一致 |
| C7 | manifest 完整（无缺失/多余/哈希漂移）、A 锚点可解析、R 编号唯一、未决项登记齐全 |

上次运行结果见 §8。

## 7. 已知限制与风险

| 风险 | 说明 | 缓解 |
|---|---|---|
| 采样率低（1.60%） | 只覆盖链路建立与识别/认证消息处理相关函数 | 所有未覆盖行为标 `OPEN`；`source/asm` 保留入口供后续阶段续读 |
| 无 24A446 抓包 | 运行时素材都是别的构建 | `runtime/` 只作佐证；`CONFIRMED` 全部来自固件字节 |
| 消息层部分取证 | 27 张表的 handler 只到地址级；识别/认证已到参数级 | `R-6.3`/`R-6.6` 只声明已证部分；`OPEN-MSG-1` |
| 认证序列未取证 | 隧道封装与参数已确认，但消息顺序/重试未证明 | `R-6.6.2` 标 `INFERRED`；`OPEN-AUTH-1`/`OPEN-AUTH-3` |
| 传输适配未知 | RFCOMM/`os_channel` → 解析器的注册点未定位 | `OPEN-TX-1`；接口形状已在 `R-1.1`/`R-1.8` 固定 |
| 旧材料未对照 | 按任务书决策 #1，本轮不读旧分析 | 冲突记录机制见 `analysis/00` §0.6 |

## 8. 验证记录

2026-10-26 复核：修正默认 8 位校验、16 位算法进位、无载荷不带尾校验、ACK 差值方向和 SYN 条目编解码；确认 SYN 两个 50 字节块及 5 项会话表的提交链。`verify.py` 40 项通过，引用实现 352 项通过；日志回放仅比较 23G90 已解析字段，非真实车机端到端测试。

- 生成器：`firmware/tools/{macho-meta,export-asm,iap2-tables,gen-iap2-message-table,gen-function-index,gen-manifest}.py`
- Ghidra：12.1.4 / JDK 21，`-process accessoryd -noanalysis` 复用已分析工程
- `verify.py` 最近一次结果见提交时输出（应打印 `ALL CHECKS PASSED`）

## 9. 后续阶段修订（不改写已发布条款含义）

| 本文件条款 | 修订来源 | 说明 |
|---|---|---|
| `R-6.11` / `OPEN-SES-3` | `research/protocol/iap2_control_session` `R-5.14` | "会话已启动"没有独立状态位；本阶段保持原措辞，只加指针 |
| `OPEN-SES-1` / `OPEN-SES-4` | `research/protocol/iap2_control_session` `R-1.5` | `link+0x120/+0x128` 两链的语义已由 control 阶段回答 |
| `OPEN-FRAME-6`（`hdr[7]`） | `research/protocol/iap2_control_session` `R-2.1` | `extra` 字节语义已由 control 阶段回答 |
| `CL-13`（分片） | 本阶段 `A15.4` | 改为"帧长上限由建链参数限制，本层不做分片"，见 `R-1.13` |
| 传输接缝 | 本阶段 `analysis/15`、`spec/01 §1.6` | 新增 `R-1.11`–`R-1.16` |

