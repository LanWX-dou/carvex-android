# A — 结论表（analysis → spec 的唯一事实源）

> 规则：每条结论必须有**可复核的证据位置**；没有证据的写 `OPEN` 并给出编号。
> `spec/` 里的每条 `R` 条款必须引用这里的编号（`verify.py` C4 检查）。
> 状态含义：`CONFIRMED` 本阶段材料内可复核；`INFERRED` 由指令形态推断；`OPEN` 未取证。

## A00 方法与镜像

| 编号 | 结论 | 状态 | 证据 | 位置 |
|---|---|---|---|---|
| A00.1 | 主镜像 `APTransport` 属 24A446：1,593,864 B，SHA256 `e277719a…c6844a8d`，LC_UUID `14228b3f-1df6-308b-97c4-b7574dbd7a97`，7,013 个符号，5,367 个函数起点 | CONFIRMED | `macho-meta.py` 输出 | `firmware/analysis/24A446/airplay-mdns/meta/APTransport/summary.json` |
| A00.2 | 四个取证工具（strings/xrefs/annotate/strxrefs）可复跑，地址换算与符号表同坐标 | CONFIRMED | 工具源码与本次全部地址 | `firmware/tools/macho-strings.py`、`macho-xrefs.py`、`annotate-func.py`、`macho-strxrefs.py` |
| A00.3 | 该镜像的 `__DATA_CONST` 指针是 dyld chained fixups，按原始 64 位指针搜索目标地址会 0 命中 | CONFIRMED | 对 `0x24fe5019f`、`0x24fe507fd`、`0x24fe500a4` 直接搜 `struct.pack("<Q", …)` 均无结果 | `analysis/00` §0.4.1 |
| A00.4 | 本阶段无网络：`web_fetch` 对 rfc-editor.org / datatracker.ietf.org 均报“非公网地址” | CONFIRMED | 两次工具调用错误信息 | `analysis/00` §0.5 |

## A01 传输、宣告与浏览

| 编号 | 结论 | 状态 | 证据 | 位置 |
|---|---|---|---|---|
| A01.1 | `APTransport` 内含 5 个服务类型字符串：`_airplay._tcp.` `0x24fe5019f`、`_airplay-alt._tcp.` `0x24fe507e1`、`_airplay-p2p._tcp.` `0x24fe508a9`、`_raop._tcp.` `0x24fe507fd`、`_sideplay._tcp.` `0x24fe50168` | CONFIRMED | `macho-strings.py` 输出 | `analysis/01` §1.5 |
| A01.2 | `_APBonjourBrowserSetModeInternal`（`0x24fd900f0`–`0x24fd908ac`）在 `0x24fd90434` 引用 `_airplay-alt._tcp.`，`0x24fd9049c`/`0x24fd906f0` 引用 `_airplay-p2p._tcp.`，`0x24fd9054c`/`0x24fd9056c` 引用 `_raop._tcp.`，并调用 `_APBonjourBrowserStartBonjourBrowser`（`0x24fd90918`） | CONFIRMED | `annotate-func.py` 逐条指令 | `analysis/01` §1.5 |
| A01.3 | 浏览器模式名共 8 个：`APBonjourBrowserBonjourGeneralAirPlay`/`AltAirPlay`/`LocalAirPlay`/`GeneralRAOP`/`LocalRAOP`/`AirPlayAWDLPartial`/`AirPlayOpenNAN`/`AirPlaySecureNANPartial`，位于 `0x24fe501ae`–`0x24fe502c5` | CONFIRMED | `macho-strings.py` | `analysis/01` §1.5 |
| A01.4 | 系统 `mDNSResponder` 不在 24A446 提取集合内，因此 Probe/Announce 的发送主体与节奏在本阶段无代码证据 | CONFIRMED（否定） | `firmware/extracted/24A446/binaries/` 目录清单 | `analysis/01` §1.5 |
| A01.5 | `_APBonjourBrowserCreate` 在 `0x24fdce420`–`0x24fdce478` 按 `w21 & 1` 选择服务类型：默认分支（`==0`）为 `_airplay._tcp.`（`0x24fe5019f`）+ `local.`（`0x24fe49e7f`）+ 模式名 `APBonjourBrowserBonjourGeneralAirPlay`（`0x24fe501ae`）；另一分支为 `_sideplay._tcp.`（`0x24fe50168`）+ `APBonjourBrowserBonjourGeneralSidePlay`（`0x24fe50178`），并另存常量 `0x0800000000000000` | CONFIRMED | Ghidra `Xrefs.java` 数据引用 `0x24fdce464` + `annotate-func.py` 的 `tst/csel/stp` 序列 | `analysis/01` §1.5 |

| A01.7 | `_carplay-ctrl._tcp`（`0x24fe6c193`，无尾点）被 `_APCarPlayControlServerAddInterface`（`0x24fe01f6c`）、`____APCarPlayControlServerControl_block_invoke_2`（`0x24fe02714`）、`.cold.1`（`0x24fe38ce0`）与 `_OUTLINED_FUNCTION_4`（`0x24fd91e14`）引用，说明手机侧存在 CarPlay 控制服务并把该服务类型与接口绑定；是否真经 mDNS 注册未证 | INFERRED | `macho-strxrefs.py` 的 `adrp+add` 表 | `analysis/01` §1.5.1 |
| A01.9 | `-[APAssistedModeBrowser startBonjourBrowser]`（`0x24fdfde98`–`0x24fdfdf64`）用**动态** `bonjourServiceName`/`bonjourProtocol` 属性、域 `local.`、接口 `awdl0` 创建浏览器（`0x2500ee8a0`），并带超时（`0x24fdfe1d0`）；因此 assisted 路径的 service 类型不是写死的 `_airplay._tcp` | CONFIRMED | `annotate-func.py` 逐指令（参数与字符串地址） | `analysis/01` §1.5.2 |

## A02 报文格式与 TXT

| 编号 | 结论 | 状态 | 证据 | 位置 |
|---|---|---|---|---|
| A02.1 | 参考实现可解析 DNS 头、question、四类记录（answer/authority/additional）、名称压缩指针（仅允许指向前的偏移）、SRV/A/AAAA/PTR/TXT/NSEC/OPT | CONFIRMED（自测） | `mdns_discovery.py` + 10 条向量全过 | `reference-impl/test_vectors.json` |
| A02.2 | TXT 长度前缀；区分无值/空值；原始重复项保留，业务 ASCII 不区分大小写 first-wins；二进制原字节保留，hex 仅展示 | CONFIRMED（自测） | RFC 6763 §6.4/6.5、合成向量与 C10 独立反例 | `analysis/02` §2.5 |
| A02.3 | `APTransport` 内含 TXT 键字符串：`model` `0x24fe4b473`、`features` `0x24fe4f2f0`、`serialNumber` `0x24fe4f340`、`btaddr` `0x24fe4f72d`、`deviceid` `0x24fe4f734`、`flags` `0x24fe4f80a`、`protovers` `0x24fe4f860`、`srcvers` `0x24fe4f870`，以及 `fex`/`pi`/`gid`/`vv`/`psi`/`manufacturer` 与 RAOP 侧 `am`/`et`/`ft`/`md`/`ov`/`sf`/`tp`/`vs` | CONFIRMED | `macho-strxrefs.py` 的键→函数表 | `analysis/03-txt-and-features.md` |
| A02.4 | `-[APBonjourCacheManager _deviceFound:altPairedInfo:recheck:event:]` 依次读 `fex`（`0x24fd99748`）、`features`（`0x24fd99778`，缓冲区长度 `0x10`）、`psi`（`0x24fd997d4`）、`serialNumber`（`0x24fd99834`）、`manufacturer`（`0x24fd9984c`）、`flags`（`0x24fd99a00`），并对 `features` 值调用 `0x2500ee040(值, 0x37)` 与 `0x2500ee040(值, 0x38)`（bit55/bit56），`bit56` 结果存入 `w24` | CONFIRMED | `annotate-func.py` 指令序列 | `analysis/03-txt-and-features.md` |
| A02.5 | `fex` 存在时优先取 `fex`（`CFDictionaryGetValue` 桩 `0x2500ee8c0` → `CFGetTypeID` 桩 `0x2500ee000`）；否则把 `features` 字符串经未命名桩 `0x2500ee910`（含长度 `0x10`）转成 64 位整数（`0x2500edff0` → `0x2500edfe0`） | INFERRED | 调用形态与参数；桩名被剥离，无法给出符号名 | `analysis/03-txt-and-features.md` |
| A02.6 | `features` 的文本由 `__APAdvertiserInfoGetTXTRecordNumberCString`（`0x24fd940a0`–`0x24fd940ec`）生成：`lsr x8,x0,#0x20` 后，高 32 位为 0 用 `"0x%X"`（`0x24fe4fc8c`），否则用 `"0x%X,0x%X"`（`0x24fe4fc82`），`stp x0,x8` 使参数为低 32 位、高 32 位；结果在 `0x24fd93544` 被取出、`0x24fd9354c` 以 `features` 为键写入 TXT | CONFIRMED | `annotate-func.py`（逐指令） | `analysis/03` §3.2.1 |
| A02.7 | 64 位 `features` 分 legacy（低 32）/extended（高 32）两半：属性常量 `kAPAdvertiserInfoProperty_FeaturesLegacy` `0x269375540`、`_FeaturesEx` `0x269375548`，写函数 `__APAdvertiserInfoSetLegacyFeatures` `0x24fd9a6e4`、`__APAdvertiserInfoSetFeaturesEx` `0x24fd99f1c`；据此索引 55/56 是 extended 半第 23/24 位 | INFERRED | 符号表 + 反汇编；两半语义未见文档 | `analysis/03` §3.2.3 |
| A02.8 | `fex` 与 `features` 是两个独立 TXT 键：构造器在 `0x24fd93510` 以 `fex` 为键、`0x24fd9351c` 调 `__APAdvertiserInfoAddStringToTXTRecord` 写入**字符串**；`features` 的解析走 `_APAdvertiserInfoCreateAPSFeaturesFromTXTRecordEx`（`0x24fd9ac78`） | CONFIRMED | `annotate-func.py` + 符号表 | `analysis/03` §3.2.4 |

## A04/A05 地址、事件与选择

| 编号 | 结论 | 状态 | 证据 | 位置 |
|---|---|---|---|---|
| A04.1 | `__APBonjourBrowserCreateEventInfoDictionary` 存在（`0x24fd99e88`–`0x24fd99f1c`，148 B，函数体内无字符串引用）；候选事件键 `IPAddress` `0x24fe52561`、`Port` `0x24fe523fa`、`InterfaceName` `0x24fe4628c` 在 `__cstring` 存在但 **Ghidra 引用数均为 0**，键名无法确认 | INFERRED | `macho-strings.py` + Ghidra `Xrefs.java`（count=0） | `analysis/04` §4.1 |
| A04.2 | 浏览可绑定接口：`awdl0` 被 `_APTSessionHealthReporterReportNetworkStatus`（`0x24fdc3c58`）、`-[APAssistedModeBrowser startBonjourBrowser]`（`0x24fdfdf14`）、`__APBonjourBrowserTickleDetailedMode`（`0x24fe1c3e8`）引用；`nan0` 被 `__APBonjourBrowserReconfirmDevice`（`0x24fe1c20c`）引用；`SetModeInternal` 另引用两者的 `__const` 副本（`0x24fd90480`/`0x24fd90620`） | CONFIRMED | Ghidra `Xrefs.java` 参数引用 + `annotate-func.py` | `analysis/04` §4.2 |
| A04.6 | `local.`（`0x24fe49e7f`）被 `_APCarPlayControlServerAddInterface`（`0x24fe01f80`）与 `_BonjourDiscoveryDelegateStart`（`0x24fd928d0`）引用，说明手机侧也在 `local.` 域宣告/浏览 CarPlay 控制服务 | CONFIRMED | Ghidra `Xrefs.java` | `analysis/04` §4.2 |
| A04.3 | SRV 的 target 是主机名，地址必须来自该主机的 A/AAAA；一个 target 可有多条地址且全部保留 | CONFIRMED（自测） | 参考实现 + `full-chain`/`multi-instance`/`ipv6-linklocal-only` 向量 | `analysis/04` §4.3 |
| A04.4 | IPv6 link-local（`fe80::/10`）不带 scope/接口不可连接；参考实现标 `link_local=true` 并要求接口 | CONFIRMED（自测） | `ipv6-linklocal-only` 向量 | `analysis/04` §4.3 |
| A04.5 | 没有找到 iOS 在多条地址之间选择的逻辑；`APTransportConnection` 属后续阶段 | OPEN | 字符串与函数扫描未见选择器 | `analysis/04` §4.5、`OPEN-MDNS-16` |
| A04.7 | `AirPlaySender` 存在 link-local 转换路径：日志串 `[%{ptr}] <APUGL> Converting addresses if IPv6 link local: %@`（`0x251c1e186`）；`APTransport` 另有 `_APConnectivityHelperStartIPv6AddressListener`（`0x24fe5b6ae`）等函数名串 | INFERRED | 字符串级证据，转换算法未见 | `analysis/04` §4.3.1 |
| A04.8 | `APTransport` 分别监听 IPv4/IPv6 地址变化（`IPv4Addresses` `0x24fe580cc`、`IPv6Addresses` `0x24fe580be`、`IPv6 Address changed (for interface %@): %@ = %@` `0x24fe5b7f1`），并存在 `enableForceIPv4Addressing` 偏好键（`0x24fe4ca2a`，用途未证） | INFERRED | 字符串级证据 | `analysis/04` §4.3.1 |
| A05.1 | 参考实现 `rank_candidates`：IPv4 +3、同网段 +2、IPv6 全局 +2、link-local +1；缺 SRV 或缺地址时 `usable=false` 且不参与打分；每条候选带 `reasons` | CONFIRMED（自测） | `mdns_discovery.py` + `multi-instance-one-unresolvable` 向量 | `analysis/04` §4.4 |
| A05.2 | 参考实现的发现层只产出候选、不自动连接；连接由调用方发起 | CONFIRMED（自测） | `rank_candidates` 返回值结构 | `analysis/04` §4.4 |

## A09 运行期材料

| 编号 | 结论 | 状态 | 证据 | 位置 |
|---|---|---|---|---|
| A09.1 | 工作区内没有任何 Wi-Fi mDNS 抓包（`.pcap/.pcapng/.cap` 共 0 个） | CONFIRMED（否定） | 递归文件搜索 | `analysis/09` §9.1 |
| A09.2 | 现有 sysdiagnose（21G93）的 139 个 summary 日志里 `airplay` 0 命中，且无 mDNS 命名文件 | CONFIRMED（否定） | `findstr` + 目录清单 | `analysis/09` §9.1 |
| A09.3 | 因缺抓包，车机的服务类型、实例名、端口、TXT 取值、TTL 行为、IPv6 可用性共 7 类结论必须保持 OPEN | OPEN | 任务书完成判据 2 未满足 | `analysis/09` §9.4 |

## 待补

`A03.x`（TXT 键逐个语义）、`A06.x`（客户端流程）在本阶段后续增量中补；`A04`/`A05` 已在本轮加入。
