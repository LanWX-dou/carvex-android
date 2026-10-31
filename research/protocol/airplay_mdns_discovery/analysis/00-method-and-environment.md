# 00 — 方法与证据边界

> 本文件说明：本阶段**用了什么证据**、**证据如何分级**、**哪些结论不能下**。
> 任务书是 [`../TASK.md`](../TASK.md)；未决项登记在 [`../spec/08-open-items.md`](../spec/08-open-items.md) 与 `source/metadata/coverage.json`。

## 0.1 一句话边界

本阶段能证明：**24A446 的 iOS 客户端在 AirPlay 发现里浏览哪些服务类型、读哪些 TXT 键、把 `features` 当 64 位位图用哪两位、以及 DNS/mDNS 报文与 TXT 的线格式**。
本阶段**不能**证明：**某一台真实车机实际宣告的实例名、端口、TXT 取值**——工作区里没有任何 Wi-Fi mDNS 抓包（见 [`09-runtime-captures.md`](09-runtime-captures.md)）。因此凡是“车机会宣告 X”的句子，一律不是 `CONFIRMED`。

## 0.2 镜像与目标

| 项 | 值 |
|---|---|
| 构建 | `24A446`（iOS 27.0.1，`iPhone18,1`） |
| 主镜像 | `firmware/extracted/24A446/binaries/APTransport/APTransport` |
| 大小 | 1,593,864 B |
| SHA256 | `e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d` |
| LC_UUID | `14228b3f-1df6-308b-97c4-b7574dbd7a97` |
| `__TEXT` | vmaddr `0x24fd8b000`，vmsize `983040`（`0xF0000`） |
| `__text` | `0x24fd8c530` + 747,500 B，即 `0x24fd8c530`–`0x24fe42f1c` |
| 符号 | 7,013 个（未剥离；含 ObjC 方法名） |
| `LC_FUNCTION_STARTS` | 5,367 个起点 |

对比镜像（只用来交叉核对名称，不作为本阶段主证据）：

| 镜像 | 用途 |
|---|---|
| `binaries/AirPlaySupport/AirPlaySupport` | 也含 `_airplay._tcp`（1 处） |
| `binaries/CoreUtils/CoreUtils` | 含 `_airplay._tcp.` / `_raop._tcp.` |
| `binaries/AirPlayReceiver/AirPlayReceiver` | 接收侧（car 角色），仅用于理解双向 |
| `binaries/AirPlaySender/AirPlaySender` | 发送侧服务名与 `discoverybroker` |

`APTransport` 是 iOS 的 AirPlay 传输层框架，**同时被发送侧与接收侧使用**；因此“它在浏览”只能说明这条代码路径存在，**不能**说明无线 CarPlay 的每一次连接都走它。

## 0.3 证据分级

| 级别 | 含义 | 本阶段用法 |
|---|---|---|
| `CONFIRMED` | 本阶段材料内可复核：字节/指令地址/文件哈希 | 只用于 24A446 的静态事实 |
| `INFERRED` | 由指令形态推断，但没有直接字符串/分支证明 | 必须写“推断” |
| `标准` | 公开标准（RFC 6762/6763）条文 | **本阶段未能联网取回原文**，只按通行条文引用，见 §0.5 |
| `OPEN` | 无证据 | 必须登记 `OPEN-MDNS-n` |

禁止：把 `INFERRED` 写成 `CONFIRMED`；把“某构建里存在这条路径”写成“车机一定这样”；把 `features` 的某一位写成“支持 CarPlay”（没有行为验证）。

## 0.4 工具链（可复跑）

四个小工具是本阶段新写的，源码在 `firmware/tools/`，都只读文件、不联网：

```bash
# 1) 列字符串及其虚拟地址（按段表换算，与符号表同坐标）
python3 firmware/tools/macho-strings.py <binary> [regex]

# 2) 找指向某地址的 adrp+add 引用，并给所在函数
python3 firmware/tools/macho-xrefs.py <binary> <addr> --symbols <metadata>/symbols.json

# 3) 反汇编一个函数，并把 adrp+add 的字符串目标、bl 的符号名就地标注
python3 firmware/tools/annotate-func.py <binary> <metadata-dir> <symbol|0xaddr>

# 4) 扫描整个 __text，列出“哪个函数引用了哪个字符串”
python3 firmware/tools/macho-strxrefs.py <binary> <metadata-dir> [regex]
```

元数据由既有工具生成：

```bash
python3 firmware/tools/macho-meta.py \
  firmware/extracted/24A446/binaries/APTransport/APTransport \
  firmware/analysis/24A446/airplay-mdns/meta/APTransport
```

Ghidra 12.1.4 在 WSL 下跑（Java 21），脚本 `firmware/tools/ghidra-scripts/Xrefs.java` 用来补“数据指针表”里的引用——`adrp+add` 扫描看不到的引用（例如 `__DATA_CONST` 里的指针数组）由它回答。

### 0.4.1 为什么需要两套 xref

`adrp+add` 扫描只覆盖“代码里直接取字符串地址”。本镜像的 `__DATA_CONST` 指针是 **dyld chained fixups** 编码，原始字节不等于目标地址，所以“原始 64 位指针搜索”会得到 0 命中（实测：对 `0x24fe5019f` 搜 `struct.pack("<Q", ...)` 无结果）。这类引用只能靠 Ghidra 的引用数据库，见 [`01-mdns-transport-and-announce.md`](01-mdns-transport-and-announce.md)。

## 0.5 关于 RFC 引用

本阶段**没有网络**（`web_fetch` 对 `rfc-editor.org` / `datatracker.ietf.org` 均返回“解析到非公网地址”）。因此：

- 规范里的标准条文以 `RFC 6762 §x`、`RFC 6763 §x` 形式**离线引用**，不复制原文；
- 这些条文的取值（组播地址、端口、TTL、Probe/Announce 次数）在参考实现与测试向量里被实际使用，**可被测试复现**，但不等于“对照 RFC 原文逐字核对过”；
- 若与 RFC 原文冲突，以 RFC 原文为准——这是本阶段已知的方法缺口，记在 `STATUS.md`。

## 0.6 采样声明

- 主镜像 1 个构建、1 个框架；未做全量反编译（`__text` 747,500 B，本阶段只导出并人工看过其中十余个函数）。
- Ghidra 全量分析只用来回答“某字符串被谁引用”，不据此声称覆盖全部发现路径。
- 没有第二台车机、没有第二份固件、没有 pcap；所有“跨车机/跨版本”的说法都是 `OPEN`。

## 0.7 目录与阅读顺序

```
TASK.md                 任务书（原样）
analysis/00             本文件
analysis/01             mDNS 传输与宣告（静态证据 + 标准条文）
analysis/02             DNS 报文格式（与参考实现一一对应）
analysis/03             TXT 键与 features 位
analysis/04             地址解析与事件模型
analysis/06             每个 OPEN 能否只靠固件解决（可行性表）
analysis/09             抓包现状（缺席说明 + 抓包 SOP）
analysis/A-conclusions.md  结论表（每条带证据与位置）
spec/00                 范围与术语
spec/01                 mDNS 传输规则
spec/02                 浏览与实例名
spec/03                 TXT 规则
spec/04                 features 位规则
spec/05                 地址选择
spec/06                 客户端实现指南
spec/07                 验收清单（L0/L1/L2）
spec/08                 OPEN 清单
spec/09                 版本与差异（只能写“不得假设”）
spec/10                 缓存与安全（不得自动信任）
reference-impl/         纯标准库解析器 + 合成测试向量 + metadata（字段表/位表）
runtime/                captures（空）+ replay（TSV → packets → 回放）
verify.py               自校验
STATUS.md               唯一状态口径
```
