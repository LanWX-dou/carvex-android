# 00 方法与环境记录

本文件记录本套文档的取证方法、工具链、可复现命令、抽样范围，以及**工具环境中的路径冲突**。所有结论性内容见 `01`–`07` 各专题分析文件。

## 1. 证据链定义

本套文档只接受以下链条，缺一环即降级：

```
固件原始 bytes (source/firmware/*)
  → 原始 ARM64 汇编 (source/asm/bluetoothd/f_<addr>.s，Capstone 反汇编，不重写)
  → Ghidra 自动反编译 (readable/ghidra/bluetoothd/f_<addr>.ghidra.c，原样保留)
  → 人工对照汇编逐条核对 (本目录 01–07)
  → analysis 记录：证据、差异、影响、OPEN
  → spec/ 平台无关协议规范
```

`source/` 与 `readable/` 一律不改写、不插注释、不转伪代码。人工结论**只**写在 `analysis/` 和 `spec/`。

## 2. 固件身份

| 项 | 值 |
|---|---|
| 设备 | iPhone 17 Pro（`iPhone18,1`） |
| iOS | 27.0.1 |
| build | `24A446` |
| IPSW | `D:\ios-carplay\iPhone18,1_27.0.1_24A446_Restore.ipsw`（11.85 GB） |
| 主取证二进制 | `/usr/sbin/bluetoothd` |
| 大小 | 13,092,096 B |
| SHA256 | `cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1` |
| 架构 | arm64e thin Mach-O |
| 函数起点数 | 37,368（LC_FUNCTION_STARTS） |

辅助二进制（仅用于说明角色边界，不作协议取证）：

| 文件 | 大小 | 角色 |
|---|---|---|
| `/usr/libexec/bluetoothuserd` | 764,272 B | BLE 广播 / 用户态代理 |
| `Platform-Bluetooth`（CoreAccessories 插件） | 132,232 B | 仅状态组件 `ACCBluetoothStatusComponent`，**不承载 SDP/RFCOMM** |

`bluetoothd` 是 iOS 上唯一承载 Classic Bluetooth 协议栈（Apple "OpenInterface" 栈）的进程，因此 SDP/RFCOMM 的协议行为只在本二进制中取证。

## 3. 工具链

| 工具 | 位置 | 版本 | 用途 |
|---|---|---|---|
| WSL | 发行版 `Ubuntu-24.04` | — | 全部解包/反汇编/反编译 |
| Ghidra | `D:\carvex-research\firmware\tools\ghidra` | 12.1.4 | headless 自动反编译 |
| JDK | `/usr/lib/jvm/java-21-openjdk-amd64` | 21 | Ghidra 运行时 |
| Capstone | pip `capstone` | 5.0.7 | 原始汇编导出（`skipdata=True`） |
| ipsw | `/usr/local/bin/ipsw` | 3.1.739 | Mach-O / dyld cache 信息 |
| Python | `/usr/bin/python3` | 3.12.3 | 仅用于抽取、索引、哈希、校验 |

WSL 资源配置：`C:\Users\iamr0s\.wslconfig` 设 `memory=28GB processors=12 swap=8GB`；实际生效 **15 GB / 12 cores**（宿主上限）。全部分析在该配额内完成。

## 4. 已执行命令（可复现）

```bash
# 1) 抽取函数（要求地址必须是 LC_FUNCTION_STARTS 起点，否则拒绝）
python3 /mnt/d/carvex-research/firmware/tools/bt-research/extract-functions.py \
  --binary   /mnt/d/carvex-research/research/protocol/bluetooth_rfcomm/source/firmware/bluetoothd \
  --selection /mnt/d/carvex-research/firmware/analysis/24A446/bt-rfcomm/selection-all.json \
  --asm-out   /mnt/d/carvex-research/research/protocol/bluetooth_rfcomm/source/asm/bluetoothd \
  --request-out /mnt/d/carvex-research/firmware/analysis/24A446/bt-rfcomm/ghidra-request.json
# → bluetoothd: 101 functions, 101 selected rows

# 2) 复用既有 Ghidra 工程做 headless 反编译（-noanalysis，禁止重新分析改变函数边界）
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
/mnt/d/carvex-research/firmware/tools/ghidra/support/analyzeHeadless \
  /mnt/d/carvex-research/firmware/analysis/decompiler-cache/24A446/bluetoothd/c98ecfbc6d67966e54f7/projects \
  phone_bluetoothd -process bluetoothd -noanalysis \
  -scriptPath /mnt/d/carvex-research/firmware/tools/ipsw-research/ghidra \
  -postScript CachePhoneFunctions.java \
  /mnt/d/carvex-research/firmware/analysis/24A446/bt-rfcomm/ghidra-request.json \
  /mnt/d/carvex-research/research/protocol/bluetooth_rfcomm/readable/ghidra/bluetoothd \
  -log /mnt/d/carvex-research/firmware/analysis/24A446/bt-rfcomm/headless.log \
  -scriptlog /mnt/d/carvex-research/firmware/analysis/24A446/bt-rfcomm/export.log
# → PHONE_CACHE finished completed=62 failed=0（第一批）
# → PHONE_CACHE finished completed=15 failed=0（闭包补充）
# → PHONE_CACHE finished completed=5 failed=0（发送组帧补充）
# → 合计 completed=101 failed=0（含复用器命令族 4 个、定时器/时间基 10 个、重连 5 个）
```

`CachePhoneFunctions.java` 在反编译前强制校验 `raw_sha256` 与原始 bytes 相等，不一致即拒绝输出；每个 `.ghidra.c` 头部写入函数地址、代码 SHA256、源文件 SHA256 和 `DECOMPILED_UNREVIEWED` 标记。

## 5. 抽样范围声明（重要）

- 全二进制 37,368 个函数起点，本套文档实际人工核对 **101 个函数**，来自 13 个功能组 + 2 个闭包补充组（`rfcomm-core-closure`、`rfcomm-tx-closure`、`rfcomm-mux-commands`、`rfcomm-timers`，均在 `selection-all.json`）。逐函数登记见 `09-function-inventory.md`。
- 抽样是**目标导向**的：以 RFCOMM/SDP 字符串交叉引用（`scan/` 下 5 份 xref 结果：discovery 1420 引用/625 函数、sdp 588/169、rfcomm 151/80、pairing 1048/634、carplay-service 180/93）为入口，再按调用关系取 1 跳闭包。
- 因此本套文档**不主张**"覆盖了 bluetoothd 的全部 RFCOMM 行为"；未抽到的函数在 `manifest.json` 的 `coverage` 字段与 `09-function-inventory.md` 中显式声明为未覆盖。
- 被排除的大函数：`0x1000efc38` 是状态码→字符串巨型表函数（含 33 条 RFCOMM、41 条 SDP 字面量），不含协议逻辑，不纳入分析。

## 6. 状态口径

| 标记 | 含义 |
|---|---|
| `CONFIRMED` | 反编译 C 与原始汇编逐条一致，且关键常量/结构偏移可在汇编立即数或引用中复核 |
| `PARTIAL` | 主路径一致，但间接调用目标、结构体字段语义或参数个数由反编译器推断，未全部复核 |
| `OPEN` | 无固件证据，或证据不足以支撑结论 |

**反编译器结论一律不作为证据本体**。本套文档中凡出现 `FUN_xxxx` 签名、结构体字段名、参数个数，如果未经汇编核对，一律按 `PARTIAL` 处理并在"未决"中点名。

## 7. 已知反编译失真（必须随结论一起读）

Ghidra 在本二进制上出现以下已知失真，人工核对时逐条修正，未修正处不进入 `CONFIRMED`：

1. **参数个数丢失**：`FUN_1003c2314` 反编译为 2 参数（`undefined8 FUN_1003c2314(undefined8, uint)`），但调用点 `0x1003c5df0`–`0x1003c5dfc` 明置 `x0=session+6, x1=DLCI>>3, x2=[rec+0x10], x3=[rec+8]`，实际至少 4 参数。
2. **寄存器/全局错乱**：`f_1003c59a0`（`OI_Rfcomm_ReceiveFrame`）中出现 `unaff_x30`、`bRam000000000000000d`、`uRam00000000000000a4` 等无基址全局，且同一段 SABM 处理被重复内联两次；此类位置只按汇编采信。
3. **内联展开**：`0x1003c73f0`（mux 命令分发）把 `Mux_ReceivePN/RPN/TEST` 全部内联，`0x1003c5334` 把组帧与 FCS 计算内联，反编译体量远大于源码结构。
4. **不可达块删除**：多处 `WARNING: Removing unreachable block`，涉及错误分支尾部，核对时以汇编为准。
5. **objc 注入**：`_objc_retain/release` 被替换为 injection 桩，objc 调用参数语义 (`FUN_10091xxxx`) 未复原。

## 8. 工具环境路径冲突（记录，不静默修正）

用户提供的环境描述文件与实际不符，**按"记录冲突、不覆盖"处理**：

| 文件 | 文件内声明 | 实际存在 | 处理 |
|---|---|---|---|
| `\setup\decompiler-environment.json` | Ghidra 在 `D:\ios-carplay\tools\ghidra` | 不存在；实际 `D:\carvex-research\firmware\tools\ghidra` | 记录差异；本次使用实际路径 |
| `\setup\ghidra-env.sh` | 全部路径以 `/mnt/d/ios-carplay/...` 为前缀 | 该目录不存在 | 记录差异；未修改原文件 |
| `/tools/ipsw-research/batch-phone-decompile.py` | 期望目标位于 `extracted/24A446/components/` | `bluetoothd` 不在该目录 | 记录差异；改用 `extract-functions.py` + 既有工程 `-process bluetoothd -noanalysis` |

`setup/` 下原始文件保持原样未改，差异写在本文件与 `manifest.json` 的 `environment_conflicts` 字段中。

## 9. 与旧文档 / 既有程序的关系（用户基线）

- 用户决策：**本轮不对照旧文档**（"不对照旧文档"），因此需求第 11 项（与旧文档差异）记为 `N/A-BY-DECISION`，仅在 `08-conflicts-and-baselines.md` 保留模板与占位。
- 用户决策：**本轮不比程序**（"先把静态的做出来"），需求第 12 项（与既有程序差异）记为 `N/A-BY-DECISION`，同上。
- 旧文档中若有与本套结论冲突之处，规则是**并列陈述 + 标 OPEN**，不删除、不覆盖。当前无对照输入，故该节为空模板。

## 10. 未决

- `OPEN-ENV-1`：`decompiler-environment.json` / `ghidra-env.sh` 的原始作者意图（是否曾计划在 `D:\ios-carplay` 建立工作区）无证据可判。
- `OPEN-ENV-2`：轮询/定时器时基单位（RFCOMM 超时以 tick 计）未在本次抽样中定位到常量化定义，见 `06`。
