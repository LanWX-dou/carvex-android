# 00 证据链与取证方法

本文件说明「结论从哪来、怎么复现」。所有后续 `A` 编号都依赖本文件定义的工具链与地址约定。

---

## A-01 三份镜像及其地址映射

三份 Mach-O 从 24A446 共享缓存取出，存放在 `source/firmware/`，只读使用。

| 镜像 | 字节数 | SHA-256 | LC_UUID | `__TEXT` 范围 | `__text`（代码段） |
|---|---|---|---|---|---|
| `AirPlaySender` | 4,397,312 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` | `0x251996000`–`0x251c7a000` | `0x251997a78` +2,375,824 |
| `AirPlayReceiver` | 2,453,520 | `ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a` | `b7bebf3b-dcf2-3395-b106-f449a30fdb1c` | `0x25176e000`–`0x25194a000` | `0x25176f8f8` +1,556,044 |
| `AirPlaySupport` | 1,536,072 | `d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15` | `3dc39c34-98dd-348c-ad18-de6e6dc38173` | `0x226e62000`–`0x226f6a000` | `0x226e63850` +836,460 |

要点：

- 三份镜像的 `__TEXT` **不重叠**，且每份镜像内还各自带了一份混淆 FairPlay 核心的副本
  （`AirPlaySender` 在 `0x2519d…`，`AirPlayReceiver` 在 `0x2517d…`）。因此「同一个函数」在两个镜像里有两个地址，
  引用时必须写清是哪个镜像。
- 地址换算：`__TEXT` 段 `fileoff = 0`，故 `文件偏移 = 虚拟地址 - __TEXT.vmaddr`；
  但 `__DATA_CONST` / `__AUTH_CONST` / `__DATA` 等**不是线性映射**，必须按各段自己的 `vmaddr/fileoff` 换算。
  段表见 `source/metadata/<image>/segments.json`。
- `__cstring` 位于 `__TEXT` 内部（例如 AirPlaySender 的 `0x251bdf641` 存 `"%s%llu"`），所以常量的
  直接地址引用可以直接按上面的线性关系读。

## A-02 工具链（全部在 `firmware/tools/`，可重跑）

| 工具 | 作用 | 产物 |
|---|---|---|
| `macho-meta.py` | 解析 Mach-O：段/节/加载命令/`function_starts`/符号表 | `source/metadata/<image>/*.json` |
| `export-asm.py` | 从 selection 导出函数的**原始字节**+Capstone 反汇编+哈希索引 | `source/asm/<image>/{f_*.s,f_*.bin,index.json}` |
| `xref-scan.py` | 线性扫描整个 `__text`，建调用图（`bl`/`b`） | `firmware/analysis/…/xrefs-<image>.json` |
| `xref-query.py` / `slice.py` / `symfind.py` | 查调用者/被调者、任意地址窗口反汇编、按名找符号 | 终端输出 |
| `read-cstr.py` / `cfstr.py` | 按虚拟地址读 C 字符串 / 读 `CFString` 常量结构 | 终端输出 |
| `ptr-walk.py` | 解析缓存链式指针（`arm64e` 形式） | 终端输出 |
| Ghidra 12.1.4（headless） | 反编译（仅作阅读辅助） | `readable/ghidra/<image>/*.ghidra.c` |

复现要点：

- `export-asm.py` 的 `.bin` 是固件切片；`verify.py` C2 会重算 `sha256` 并与 `index.json` 对照，
  同时重新反汇编 `.bin` 与 `.s` 逐行比对。任何一处被改动都会报错。
- Ghidra 产物一律带 `DECOMPILED_UNREVIEWED` 头，**不作为结论依据**，只用于快速定位。
- 结论取值（常量、字符串、结构偏移）一律回到「字节 + 汇编」核对。

## A-03 外部导入怎么解析成符号（本阶段的关键基础设施）

三份镜像**没有** `LC_DYLD_CHAINED_FIXUPS`、**没有** `LC_DYLD_INFO`（bind 信息被剥掉），所以：

1. 自研的 `import-resolve.py` 不适用（会直接报「没有 LC_DYLD_CHAINED_FIXUPS」）。
2. `ipsw dyld symaddr` 对定义符号有效，但对 `__TEXT_STUBS` 桩地址无效；`ipsw dyld a2s` 会把桩地址
   误归属到**无关镜像**的最近符号（实测得到 `HDCloudSyncCoordinator` 之类），**不可信**。
3. 可用路径：`ipsw dyld stubs <DSC>` 输出全量桩表（本机 502,440 条），得到 `桩地址: 符号名`，
   再与反汇编里 `bl #0x…` 的目标求交。产物落在
   `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`（约 35 MB，可重生成，勿入库为证据）。

两个踩过的坑，记下来避免重复：

- 桩表只覆盖 `__TEXT_STUBS`；少数桩指向的 GOT 内容是链式指针而非符号（本次 5 个），
  这些地址解析成 `?`，不得据此猜名字。
- 桩表匹配必须用 LF 换行的地址清单；用 CRLF 清单 `grep -F -f` 会**全部不匹配**（静默 0 命中）。

解析出的关键导入（`AirPlaySender` 侧，供后文引用）：

| 桩地址 | 符号 | 用途 |
|---|---|---|
| `0x25810ac50` | `CMBaseObjectGetDerivedStorage` | 取对象派生存储 |
| `0x258109150` | `CMBaseObjectGetVTable` | 取 vtable（后续 `+0x10` 再取方法表） |
| `0x2580f6ff0` | `CFDataCreate` | 建 CFData |
| `0x258101800` | `CFDataGetBytes` | 取字节 |
| `0x258109260` | `APCUGetFairPlayHWInfoEx` | 取 FairPlay 硬件信息 |
| `0x25810f280` | `FigCreateBlockBufferCopyingMemoryBlock` | 把裸内存包成 `CMBlockBuffer` |
| `0x25810eae0` | `CMBlockBufferGetDataPointer` | 从 `CMBlockBuffer` 取指针 |
| `0x25810e680/690/6a0` | `CC_SHA512_Final/Init/Update` | SHA-512 |
| `0x258101e80` | `RandomBytes` | 随机数 |
| `0x25810d150` | `APSCreateSecureMemAllocator` | 安全内存分配器 |
| `0x25810a1a0` | `ASPrintF` | 格式化（返回长度） |

`AirPlaySupport` 侧另有：`_AES_CTR_Init/Update/Final`、`_AES_CBCFrame_Init/Final`、
`_chacha20_poly1305_init_64x64/_add_aad/_encrypt/_decrypt/_verify`、`_CFDictionaryGetData`、
`_Base64DecodeCopy` 等（见 `firmware/analysis/…/stub-map-all.txt`）。

## A-04 调用图：为什么需要它

单一函数阅读不足以回答「谁在用这套密钥」。`xref-scan.py` 对三份镜像做了 `__text` 全量线性扫描：

| 镜像 | 调用点数 | `__text` 字节 |
|---|---|---|
| `AirPlaySender` | 85,638 | 2,375,824 |
| `AirPlayReceiver` | 27,979 | 1,556,044 |
| `AirPlaySupport` | 26,608 | 836,460 |

局限必须写明：线性扫描**不做控制流恢复**，`blr`/`blraa`（虚表、函数指针）不计入；
因此「没有调用者」只能说明**没有直接调用**，不能说明没被使用。这一条直接影响下文对
`_aprscreen_SetSecurityInfoAES` 之类函数的判断（见 A-18）。

## A-05 采样与复算

- 本 docset 只对**列出的函数**做了逐条阅读（`source/asm/` 下的 36+15+6 个函数），
  其余符号仅用于交叉引用，未逐个阅读。
- 每个结论的复算路径写在相应分析文件的「复算」小节：给出函数地址、关键指令地址、要读的字节。
- 任何「大小」都是「到下一个 `function_starts` 起点的距离」，是上界而非精确长度；
  `export-asm.py` 切出的 `.bin` 就按这个规则切，`.s` 与 `.bin` 一致即自洽。
