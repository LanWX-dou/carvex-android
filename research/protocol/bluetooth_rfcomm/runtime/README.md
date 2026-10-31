# runtime/ —— 运行时观测（只能佐证，不能替代固件证据）

## 1. 本目录的规则

1. **定位**：运行时日志、抓包、sysdiagnose 只用于**佐证**静态结论，或用于发现"静态分析漏掉的分支"。
2. **不得**用运行时观测推翻或替代 `source/` + `analysis/` 的固件证据；两者冲突时以固件为准，并把冲突记为新的 `OPEN`。
3. 任何从运行时得出的结论，都必须在 `analysis/` 中标注为"运行时候选"，并回到固件重新取证后**才能**升级为 `CONFIRMED`。
4. 每个观测文件必须登记来源、设备、构建号、采集时间。

## 2. 当前状态

**已做首轮观测（SDP / HCI 抓包），结论见 `observations/findings-sdp-hci.md`。**

| 观测项 | 状态 | 结果 |
|---|---|---|
| `logs/Bluetooth/*.pklg` HCI 抓包（三构建） | 已完成（**已修正**） | 解出 4 类 SDP 真实报文；RFCOMM 帧**并非 0**——早期工具漏掉 TX 方向且按 handle 混方向重组，修正后 4 个文件共解出 **126 / 44 / 173 / 194** 帧，含 PN、MSC 与 iAP2 载荷。详见 `captures/2026-10-rfcomm-pklg-reanalysis.md` |
| `system_logs.logarchive` tracev3 关键字扫描 | 已完成（方法无效） | bluetoothd 的 RFCOMM/SDP 格式串 **0 命中**，原因是 os_log 消息串/参数非明文，本方法无法还原（`OPEN-RUN-2`） |

因此 `spec/` 中的强制条款**仍然全部**以固件证据为准；运行时观测只带来了三处补充：

1. `spec/01` 新增 R-1.8a–R-1.8c：CarPlay 族 UUID 在 SDP 中为**逆序**（三构建一致）；
2. `spec/02` 补 `0x0002` 属性并给出实测记录属性集 `{0x0000,0x0001,0x0002,0x0004}`；
3. `spec/03` 增补 R-3.11a/b 与 §3.7 实测请求形态，强化"通道号必须从 SDP 读取"（实测出现 1/4/5）。

## 3. 可用素材（已存在，但均非目标构建）

素材路径：`D:\carvex-research\sysdiagnose`

| 构建 | 系统 | 与目标固件的关系 |
|---|---|---|
| `22H374` | iOS 18 | **不同构建**，只能作跨版本佐证 |
| `23G90` | iOS 26 | 同上 |
| `21G93` | iOS 17 | 同上 |

**关键限制**：本套文档的固件证据全部来自 **24A446**（iOS 27.0.1，iPhone18,1）。上表三个构建**都不是** 24A446，因此：

- 可以用于观察"日志格式、状态名、错误码是否跨版本稳定"；
- **不得**用于确认任何数值常量（N1、信用窗口、超时值、UUID 字节）；
- 若发现某常量在不同构建中不同，必须记为 `OPEN` 并在目标构建上重新取证。

## 4. 已有工具

| 工具 | 路径 | 用途 |
|---|---|---|
| `scan-tracev3-keys.py` | `firmware/tools/scan-tracev3-keys.py` | 在 tracev3 里按任意关键字批量搜索（未压缩段 + lzfse 分块） |
| `scan-tracev3.py` | `firmware/tools/scan-tracev3.py` | 早期版本，关键字写死 |
| `peek-tracev3-string.py` | `firmware/tools/peek-tracev3-string.py` | 按固定子串提取 tracev3 上下文 |
| `pklg-rfcomm.py` | `firmware/tools/pklg-rfcomm.py` | 解析 `.pklg`（HCI 抓包），重组 ACL/L2CAP，找 PSM=3 并校验 RFCOMM 帧 FCS。**已修正三处缺陷**：纳入 ACL 类型 2、按 `(方向, handle)` 分组重组、无连接请求时用帧头特征判定 RFCOMM。另注：抓包末字节**不是**线上 FCS，而是 `FCS(地址, 控制)` 占位值，故该校验只用于自检，不用于佐证 FCS |
| `check-pklg-trailer.py` | `firmware/tools/check-pklg-trailer.py` | 验证抓包末字节 = `FCS(地址, 控制)`（带信息字段帧 313/313，`0/27` 组多值），用于证明该字段不是线上 FCS |
| `dump-sdp-records.py` | `firmware/tools/dump-sdp-records.py` | 解析 `.pklg` 并解码 SDP 请求/响应（数据元素树） |

## 5. 观测优先级（剩余项，待执行）

已完成：SDP/记录形态、通道号、字节序。剩余项都需要**目标构建 24A446** 的素材，或用完整 tracev3 解析器解开参数：

| 优先级 | 观测目标 | 可佐证的条款 | 状态 |
|---|---|---|---|
| 1 | `RFCOMM Channel connected: result: … frameSize: …` 的实际数值 | `spec/04` R-4.22、`spec/05` R-5.23 | 部分佐证：已从抓包得到 PN 的 N1 实测值（256/667/990/999/1007/1018/2027），但该日志行本身未捕获（抓包无 24A446 素材） |
| 2 | `Initiating outgoing Wireless IAP connection request … on rfcomm channel %d` 的通道号 | `spec/03` R-3.16 | **已通过 SDP 记录间接佐证**：通道号 4/1/5（非固定） |
| 3 | 会话/通道状态迁移序列（日志中的状态名） | `spec/06` 全章、`OPEN-RF-14` | 未执行（tracev3 参数无法解码，`OPEN-RUN-2`） |
| 4 | DISC 之后对端回复 DM 还是 UA | `spec/06` R-6.6（关键互通点） | 未执行（4 个抓包未覆盖 DISC↔DM 配对，仅零星 DISC/DM） |
| 5 | 超时相关日志的时间差 | `OPEN-RF-12`（定时器单位）**已由静态证据关闭**（=100 ms，30→3 s） | 无需执行；如需实测可对照 CF-75 |
| 6 | `No registered server on DLCI %d` 是否出现 | `spec/04` R-4.16 | 未执行（同上） |

## 6. 文件命名约定（新增观测时）

```
runtime/observations/<build>-<yyyymmdd>-<主题>.md     说明与结论
runtime/observations/<build>-<yyyymmdd>-<主题>.txt    原始提取（不得编辑）
```

每个 `.md` 必须包含：设备型号、构建号、采集时间、提取命令、原始行、能佐证/否证的条款编号。
