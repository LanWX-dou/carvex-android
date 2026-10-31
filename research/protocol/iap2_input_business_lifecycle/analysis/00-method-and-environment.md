# analysis/00 — 方法与取证环境

## 0.1 目标

在**同一份固件构建**（24A446 / iOS 27.0.1 / iPhone18,1）上，用与前三个阶段相同的证据链，
产出 iAP2 **输入 / 业务 / 生命周期**的可复核结论：固件字节 → 原始汇编 → 反编译（辅助）→
人工核对 → `analysis/` 的 `A` 编号 → `spec/` 的 `R` 编号。

## 0.2 证据强度分级

| 级别 | 含义 |
|---|---|
| `已确认` | 指令级证据，且反例搜索过（"没有别的写点"） |
| `部分确认` | 结构/参数有指令证据，但某个字段或分支未取证 |
| `OPEN` | 未取证，登记 `OPEN-INP-*` / `OPEN-NP-*` / `OPEN-NAV-*` / `OPEN-LIFE-*` |

**反编译输出不作证据**：`readable/` 下所有 `.ghidra.c` 只是阅读辅助，头部固定写
`RAW GHIDRA DECOMPILATION — NOT REVIEWED`；结论必须落到 `source/asm/` 的地址。

## 0.3 采样与覆盖

| 项 | 值 |
|---|---|
| 本阶段导出函数 | **274** |
| 镜像内函数总数 | 8,706 |
| 采样率 | **274 / 8,706 = 3.15%** |
| 反编译文件 | 274 × 2（`.ghidra.c` + `.json`） |
| 种子 | 第三阶段 199 个函数（同一二进制、同一字节，重新导出） |
| 本阶段新增 | 79 个（其中 4 个地址已在种子里，按地址去重） |

采样是**按主题定向**的：HID（特性 11）、NowPlaying（14）、导航（17）、AssistiveTouch（3）、
生命周期（挂起/恢复/断开/清理）。这不是全栈覆盖，也不能当全栈覆盖引用。

## 0.4 可复现命令

```bash
# 1) 目录 + 选函数（种子=第三阶段，新增=本阶段）
python3 firmware/tools/scaffold-input-lifecycle.py

# 2) 原始汇编（Capstone 5.0.7）
python3 firmware/tools/export-asm.py \
  research/protocol/iap2_input_business_lifecycle/source/firmware/accessoryd \
  research/protocol/iap2_input_business_lifecycle/source/metadata \
  research/protocol/iap2_input_business_lifecycle/source/metadata/selection.json \
  research/protocol/iap2_input_business_lifecycle/source/asm/accessoryd

# 3) 特性信息表
python3 firmware/tools/extract-feature-table.py research/protocol/iap2_input_business_lifecycle

# 4) 反编译请求 + Ghidra（WSL，工程属 root）
python3 firmware/tools/build-ghidra-request.py research/protocol/iap2_input_business_lifecycle
./firmware/tools/ghidra/support/analyzeHeadless \
  firmware/analysis/24A446/iap2-link/project iap2 -process accessoryd -noanalysis \
  -scriptPath firmware/tools/ghidra-scripts -postScript ExportDecomp.java \
  research/protocol/iap2_input_business_lifecycle/source/metadata/ghidra-request.json \
  research/protocol/iap2_input_business_lifecycle/readable/ghidra/accessoryd

# 5) 处理器事实表（机器生成）
python3 firmware/tools/gen-input-handler-facts.py research/protocol/iap2_input_business_lifecycle

# 6) 索引 / 清单 / 校验
python3 firmware/tools/gen-function-index.py research/protocol/iap2_input_business_lifecycle
python3 firmware/tools/gen-manifest.py research/protocol/iap2_input_business_lifecycle
cd research/protocol/iap2_input_business_lifecycle && python3 verify.py
```

## 0.5 工具的三个坑（都踩过）

1. **符号表一名多址**：同一地址在 `symbols.json` 里有空名条目与真名条目共存
   （例如 `0x100130444` 同时有 `""` 与 `_iap2_hid_StartHIDMsgHandler`）。
   取名时必须跳过空串，否则会把有名字的函数误报成"无符号"。
2. **Ghidra 的 `PHONE_CACHE` 会跳过已导出项**：第二次运行时日志出现
   `done valid=29 skipped=245`，不是失败；判断导出是否完整要看 `readable/` 文件数，
   不要看日志里的 `valid`。
3. **参数跳表的基址是 `adr` 指令自身地址**：`case = adr_pc + int32(表项)`，
   不是"表的地址 + 偏移"。用错会让所有 case 落到函数外，表现为"case 不在本函数体内"。

## 0.6 与前三阶段的关系

- 引用链路层写 `link/R-x.y`，引用控制会话写 `sess/R-x.y`；
- 本阶段**不重新定义**消息头、参数头、会话分发、两张准入名单，只引用；
- 本阶段新增的分发层级是"特性处理器内部的参数 ID 分派"（见 `analysis/02`）；
- 第三阶段遗留的 `sess/OPEN-SES-2`（`0x4301` 字段映射）不在本阶段处理范围。

## 0.7 与旧材料的关系

`firmware/analysis/24A446/iap2-*` 与 `/mnt/d/ios-carplay/pseudocode` 只作线索；
本阶段的每条结论都重新在 `source/asm/` 上取证，不把旧结论当证据。冲突时以本阶段指令为准并记录。
