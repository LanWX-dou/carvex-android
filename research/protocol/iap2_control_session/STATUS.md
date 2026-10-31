# STATUS — iap2_control_session

本文件是本阶段的**唯一状态口径**。任何"完成度"表述以本文件与 `source/metadata/coverage.json` 为准；两者不一致时以 `coverage.json` 为准（`verify.py` 的 C8 类会强制一致）。

## 一句话状态

> 会话层的结构、编码、SYN 会话表填充/提交和 `0x4301` 静态 schema 已有指令级依据。表最多 5 项，不是 44 项（`A02.15`）。初始 profile 分配、全部协商分支、`0x4301` 平台必填性/错误响应/下游网络结果仍是 OPEN；统计以 `coverage.json` 为准。23G90 日志补充两次连接的会话号与识别/认证顺序，但不能证明完整分配算法或替代 24A446 实测。

不得表述为"全部确认"。2026-10-26 复核发现并修正了认证参数范围、feature 0/7、OID、AA06 集合门控及验收口径；旧统计反映采样分类，不能据此断言所有规范文字正确或完整 CarPlay 已可实现。

认证样本新增可重复验证：`pwsh -NoProfile -File research/protocol/iap2_control_session/runtime/verify-auth-sample.ps1`。两次交换均通过 P-256/P1363 直接 digest 验签，再哈希及篡改挑战均失败；容器只含一张证书且两次相同。该检查**不验证信任链**、其他认证 profile 或真实客户端互通。

## 能否据此实现一个"能连上车机"的客户端？

**结构可以照写；对话所需的时序与会话号已经有实测依据，但只在 23G90 上验证过。**

| 能力 | 状态 | 依据 |
|---|---|---|
| 拼帧、拆帧、参数编解码、校验边界 | **可以照文档写** | `R-3.x` |
| 会话号路由、四类数据面分发、EA 子会话号 | **可以照文档写** | `R-2.x`、`R-2.10` |
| 两张准入名单、认证/识别双条件、`0xaa06` 特例 | **可以照文档写** | `R-5.1`–`R-5.6` |
| 启动/拆除顺序、缓冲大小、处理器注册规模 | **可以照文档写** | `R-4.x`、`R-6.x` |
| 会话号用几号、谁分配、怎么告知对端 | SYN 条目填充工作块并在连接完成时提交；样本车机提议 2/3，设备沿用 | `A02.15`、`A02.13`；初始 profile 与完整选择规则仍 `OPEN-SES-1` |
| 识别/认证的交换顺序 | **有实测序列**（23G90）| `A05.9`、`A05.10`；24A446 未验 |
| `0x4301`（CarPlay 启动）静态 schema | **可以照文档写**；平台必填性、错误/重试和后续 CarPlay 仍需实机 | `spec/14`、`OPEN-SES-2` |

补法写在 [spec/08](<spec/08-client-implementation-guide.md>)；实测依据见 [runtime/23G90-bt-classic-2026-10-16.md](<runtime/23G90-bt-classic-2026-10-16.md>)。

## 客户端交付路径（L0–L4）

设备侧客户端（模拟 iPhone）按 [spec/12](<spec/12-implementation-levels.md>) 分级验收：

| 等级 | 内容 | 关键判据 |
|---|---|---|
| L0 | 链路 | SYN/SYNACK/ACK 齐全 |
| L1 | 识别 | `0x1d00` 发出、`0x1d01` 解析、`0x1d02` 发出 |
| L2 | 认证 | 七步完成且验签通过 |
| L3 | 会话 | 路由、重组、能力门控、背压/异常测试通过；具体业务按支持的 profile 选择 |
| L4 | CarPlay 启动 | 收到 `0x4301`，按静态 schema 解析 14 字段；平台交接和下游 CarPlay 仍需实机（`OPEN-SES-2`）|

## 交付物

| 目录 | 内容 | 数量 |
|---|---|---|
| `analysis/` | 分析文档 `00`–`15` + `A-conclusions.md`（`14` 为消息对照表，`15` 为 `0x4301` 静态字段映射） | 17 |
| `spec/` | 规范 `00`–`14`（含 `0x4301` schema、客户端指南、启动序列、消息目录、认证、等级、冲突） | 15 |
| `source/firmware/` | 目标镜像（与上一阶段逐字节相同） | 1 |
| `source/metadata/` | 镜像元数据、选函数表、反编译请求、特性表、覆盖表 | 10 |
| `source/asm/accessoryd/` | 每个函数的原始反汇编 + 原始字节 + `index.json` | 399 |
| `readable/ghidra/accessoryd/` | Ghidra 反编译产物（未复核） | 398 |
| 根 | `TASK.md`、`STATUS.md`、`verify.py`、`manifest.json`、`function-index.json` | 5 |
| `runtime/` | 运行时样本、认证/会话复核脚本与 `0x4301` 静态回归脚本 | 6 |

## 12 个覆盖项

| 编号 | 内容 | 状态 | 关键未决 |
|---|---|---|---|
| `CS-01` | 会话对象模型（endpoint / run loop / link） | 已确认 | 建链参数块逐字段 |
| `CS-02` | 会话表几何与字段 | 部分确认 | 填充提交已确认；初始 profile 分配及多会话选择仍 OPEN（`OPEN-SES-1`） |
| `CS-03` | 会话号 = 链路头第 8 字节（收发双向） | 已确认 | — |
| `CS-04` | 四类数据面分发 | 已确认 | 类型 3 无分支；两个数据面未读实现 |
| `CS-05` | 控制会话初始化（65535 缓冲 + 96 处理器） | 已确认 | 建特性调用点参数 |
| `CS-06` | 版本门控、启停顺序与 `0x4301` 静态 schema | 部分确认 | 平台必填性、错误/重试、下游 CarPlay |
| `CS-07` | 消息层 6 字节头 | 已确认 | — |
| `CS-08` | 参数层 4 字节头、parent/prev 遍历 | 已确认 | 非法子项边界/profile 处理、占位长度 |
| `CS-09` | 字节流重组 | 部分确认 | 解析器鲁棒性、一包多消息 |
| `CS-10` | 识别门控（入/出两张白名单） | 已确认 | 集合填充时机 |
| `CS-11` | 拆除与重连 | 部分确认 | 异步同步、资源释放 |
| `CS-12` | 定时器、流控与确认边界 | 部分确认 | 队列满、ACK 回调、入队函数 |

## 证据链

任何一条 `R-x.y` 都能沿三级点回固件字节：

```
spec/0N-*.md 的 R-x.y
   └─ 依据：Axx.y
        └─ analysis/A-conclusions.md 的该行 + analysis/0N-*.md 的章节
             └─ 指令地址（如 0x1000326d4）
                  └─ source/asm/accessoryd/f_<函数>.s 的该行
                       └─ source/asm/accessoryd/f_<函数>.bin（固件原始字节）
                            └─ source/firmware/accessoryd 的对应切片（sha256 锁定）
```

`verify.py` 的 C2 会逐函数比对 `.bin` 与镜像切片；C5 会逐条比对"依据"引用的 `A` 编号是否存在。

## 本阶段最重要的五条结论

1. **会话不是对象，是表项。** 表项 4 字节：会话号、数据面类型、版本、标志（`R-1.3`）。
2. **会话号就是链路头第 8 字节 `hdr[7]`**，收（比较表项）发（写入包头）两侧都有指令证据（`R-2.1`、`R-2.2`）。
3. **版本 = 表项第 3 字节，直接决定先跑识别还是先跑认证**：`== 2` → 识别优先，否则认证优先，缺表时缺省按认证优先（`R-4.4`、`R-4.5`）。
4. **消息头与参数头分别为 6/4 字节**：消息 `40 40 | 总长 | ID`，参数 `总长 | ID | 值`；长度字段均为 2 字节大端。样本存在 `len=4` 的存在性参数，不能笼统声称不存在空参数；GetFirstParam 第二参为 parent，不是 prev；顶层/子项 len=4 可遍历，typed getter 的宽度检查不能代替通用 TLV 规则。
5. **入站与出站是两套准入名单**：入站看 `+0x60` 集合、出站看 `+0x68` 集合；`0xaa06` 不要求认证，但仍要求识别完成与可收集合包含 ID（`R-5.3`、`R-5.6`）。

## 明确没做的事

| 项 | 原因 |
|---|---|
| 未对照任何旧文档/旧伪代码 | 任务书 §11 第 1 条 |
| 未与本阶段之外的实现做对照 | §11 第 2 条 |
| 运行时佐证**只**用 `sysdiagnose` | §11 第 3 条；已知运行时样本为 `22H374`/`23G90`/`21G93`，**不是** 24A446（`OPEN-RUNTIME-1`）|
| 未补认证/识别序列 | §11 第 6 条；只引用其作为门控条件 |
| 未覆盖 CarPlay 音视频 | §11 第 7 条 |
| 未遍历全部 8,706 个函数 | 采样 199 个（2.29%），按主题定向 |

## 复现

```bash
cd D:\carvex-research\research\protocol\iap2_control_session && python3 verify.py
```

期望输出：`failures: 0`。若报 `C1 哈希不一致`，说明文档改过，需要重跑：

```bash
python3 firmware/tools/gen-control-message-table.py research/protocol/iap2_control_session
python3 firmware/tools/gen-function-index.py research/protocol/iap2_control_session
python3 firmware/tools/gen-manifest.py research/protocol/iap2_control_session
```

## 下一步（若要继续）

| 优先 | 目标 | 需要的动作 |
|---|---|---|
| 高 | 关闭 `OPEN-SES-1` 剩余部分 | 核对最初 profile 分配、多会话冲突、跨版本和异常重连；填充/提交已有 `A02.15` |
| 高 | 关闭 `OPEN-SES-2`（`0x4301` 运行时交接/下游结果） | 用真实车机验证字段组合、错误/重试、Wi-Fi/IP、控制、媒体、输入与断线恢复 |
| 中 | 关闭 `OPEN-SES-15`（两个集合的填充时机） | 读 `iap2_identification_*` 的写入路径 |
| 中 | 关闭 `OPEN-SES-16`（文件传输/会话日志数据面） | 反编译 `0x100183b8c`、`0x100136828` 及其依赖 |
| 低 | 运行时佐证升级到 24A446 | 需要一台同构建设备的 `sysdiagnose`（`OPEN-RUNTIME-1`）|
