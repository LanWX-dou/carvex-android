# analysis/00 — 方法、环境与可复现性

## 0.1 目标与构建

| 项 | 值 |
|---|---|
| 构建 | iOS 27.0.1，`24A446`，`iPhone18,1`（iPhone 17 Pro）|
| 主二进制 | `accessoryd`（CoreAccessories.framework/Support）|
| 大小 | 4,330,752 B |
| SHA256 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| LC_UUID | `b3f36577-c4a2-3960-85ab-9d801b3f2c73` |
| 镜像窗口 | `0x100000000`–`0x102180000` |
| 函数起点数 | 8,706（`LC_FUNCTION_STARTS`）|
| 符号条目 | 52,443 |

本阶段**不重新提取**二进制：`source/firmware/accessoryd` 与控制会话阶段逐字节相同，`verify.py` C1 会重新算哈希。

## 0.2 工具链

| 步骤 | 命令 | 产物 |
|---|---|---|
| 选函数 | `python3 firmware/tools/scaffold-airplay-tunnel.py`（首轮 227 个）+ 定向追加（group `O`，19 个）| `source/metadata/selection.json`（246 个）|
| 取字节/反汇编 | `python3 firmware/tools/export-asm.py …` | `source/asm/accessoryd/f_*.{s,bin}` + `index.json` |
| 构造反编译请求 | `python3 firmware/tools/build-ghidra-request.py research/protocol/iap2_airplay_tunnel` | `source/metadata/ghidra-request.json` |
| 自动反编译 | `analyzeHeadless firmware/analysis/24A446/iap2-link/project iap2 -process accessoryd -noanalysis -scriptPath firmware/tools/ghidra-scripts -postScript ExportDecomp.java …` | `readable/ghidra/accessoryd/f_*.ghidra.c` |

Ghidra 12.1.4，Java 21，WSL 下运行。反编译输出**只作阅读辅助**：每个 `.c` 文件头都写 `RAW DECOMPILATION — NOT REVIEWED`，任何结论必须回到 `.s` 的指令地址。

## 0.3 地址与字节约定

- 地址一律写 `0x100……`（镜像内虚拟地址），指令地址与 `.s` 中的行首地址一致；
- 指针解码规则：`target = 0x100000000 + (value & 0xFFFFFFFFFF)`；
- 多字节整数：iAP2 线上长度/ID 为**大端**；结构体字段为小端；
- `hdr[7]` = 链路包头第 8 字节 = 会话号（`control/A02.x`）；
- 引用其它 docset 写 `link/R-x.y`、`control/R-x.y`；`verify.py` C7 会解析。

## 0.4 证据分级

| 级别 | 含义 |
|---|---|
| 指令级 | 有指令地址，且读得到原始字节（本阶段绝大多数）|
| 字符串级 | 只有 `os_log` 格式串地址，用于命名/错误分类，不单独支撑语义 |
| 运行期 | 只有抓包字节（23G90），与目标构建不同，必须标 `23G90` |
| INFERRED | 由多个指令级事实推出，但缺一条直接证据 |
| OPEN | 没有证据，登记 `OPEN-TUN-n` |

## 0.5 抽样声明

本阶段导出 **246 / 8,706 ≈ 2.83%** 的函数（首轮 227 + 未决项定向取证 19）；其中在 `analysis/` 里被直接引用、逐指令核对的是 **33 个**（`function-index.json` 中 `CONFIRMED_BY_ANALYSIS` 的行）。其余 213 个只有自动反编译，没有任何结论依赖它们。

定向追加发生在 2026-10-26：按符号名与全 `__text` 的 BL/立即数扫描找出漏掉的入口，只补了 19 个（`analysis/09` §9.0 列表），没有扩大抽样比例。

其余函数（包括链路层、控制会话层）只作为边界引用，结论来自控制会话阶段的既有证据（`control/A*`），本阶段不重复核对。任何"遍历所有引用点"的负结论都写了检索口径（例如"全 `.text` 中 `mov w?, #0xfffa/fffb/fffc` 只有 4 处"）。

## 0.6 本阶段的四个关键函数与入口

| 函数 | 地址 | 作用 |
|---|---|---|
| `_mfi4Auth_util_packIntoTunnelDataiAP2Msg` | `0x100022264` | 把 `CFData` 包成 `0x5500`/`0x5501` |
| `_mfi4Auth_util_unpackFromTunnelDataiAP2Msg` | `0x100022398` | 从 `0x5501`/`0x5503` 取回数据与 `type` |
| `_mfi4Auth_relay_handle_iAP2RelayRemote` | `0x10008449c` | 入站中继：解包 → 按 `type` 分派 |
| `_mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient` | `0x100084da8` | 出站中继：`type<3` → 打包 → 发 `0x5164` |

四个函数的原始汇编都在 `source/asm/accessoryd/`，反编译在 `readable/ghidra/accessoryd/`。

## 0.7 与旧材料的关系

`firmware/analysis/24A446/iap2-*`、`/mnt/d/ios-carplay/pseudocode` 等旧目录只作**检索线索**。本阶段凡是旧结论与本阶段冲突，以本阶段指令级证据为准，并在 `analysis/06` 的冲突表里记一行。

## 0.8 复现命令

```bash
python3 firmware/tools/scaffold-airplay-tunnel.py
python3 firmware/tools/export-asm.py research/protocol/iap2_airplay_tunnel/source/firmware/accessoryd \
  research/protocol/iap2_airplay_tunnel/source/metadata \
  research/protocol/iap2_airplay_tunnel/source/metadata/selection.json \
  research/protocol/iap2_airplay_tunnel/source/asm/accessoryd
python3 firmware/tools/build-ghidra-request.py research/protocol/iap2_airplay_tunnel
# WSL:
firmware/tools/ghidra/support/analyzeHeadless firmware/analysis/24A446/iap2-link/project iap2 \
  -process accessoryd -noanalysis -scriptPath firmware/tools/ghidra-scripts \
  -postScript ExportDecomp.java research/protocol/iap2_airplay_tunnel/source/metadata/ghidra-request.json \
  research/protocol/iap2_airplay_tunnel/readable/ghidra/accessoryd
cd research/protocol/iap2_airplay_tunnel && python3 verify.py
```
