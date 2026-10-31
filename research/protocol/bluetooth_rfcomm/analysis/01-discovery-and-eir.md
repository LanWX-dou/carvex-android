# 01 可发现性、设备标识与 EIR 广播

覆盖需求项：**（1）可发现性 / 设备识别**，并为（2）服务注册提供 UUID 常量来源。

## 1. 目标

回答四个问题：

1. iPhone 侧由谁决定"可被经典蓝牙发现"，是哪一个开关量。
2. 经典蓝牙 EIR 里到底放了什么（结构、顺序、长度上限）。
3. CarPlay / 无线 iAP 相关的 128-bit UUID 具体字节是什么。
4. 这些 UUID 与服务名之间的映射表在哪里。

## 2. 结论

### C1 `FUN_100653368` 是经典 EIR 数据的唯一构造点 `CONFIRMED`

证据：

| 依据 | 内容 |
|---|---|
| 汇编 `0x1006533a4`–`0x1006533ac` | `adrp x19,#0x100c3e000; add x19,x19,#0x2d0` → EIR 缓冲区 `0x100c3e2d0` |
| 汇编 `0x1006533a0` | `ldrsw x1,[x22,#0x408]` → 当前 EIR 长度在 `0x100c3e408` |
| 汇编 `0x1006533b0` | `bl 0x10090a160`（bzero，按当前长度清零） |
| 汇编 `0x1006533c8`–`0x1006533d4` | `add w8,w20,#1; strb w8,[x19]` → `[0x100c3e2d0] = strlen(name)+1`；`mov w9,#9; strb w9,[x19,#1]` → 下一字节 = `0x09` |
| 汇编 `0x1006533e8` | `bl 0x10090ab10`（memcpy）目标 `x19+2`，源 `0x100c1f700` |
| 汇编 `0x1006533f0` | `str w24,[x22,#0x408]` → 长度推进 `strlen(name)+1` |
| 字面量 | 12 条 `Advertising …` 日志点，全部落在本函数：`0x1006535b8` HFP AG、`0x100653648` PBAP Server、`0x1006536d8` A2DP Source、`0x100653768` AVRCP Target、`0x10065383c` PAN-NAP、`0x1006538ec` PAN-U、`0x10065397c` MAP Server、`0x100653ac4` GATT Source、`0x100653b68` LE CarPlay、`0x100653d30` WiAP、`0x100653e20` WiAP Sink and Classic CarPlay、`0x100653f00` CarPlay Gateway |

因此 EIR 的第一个 AD 结构固定为：

```
[len = strlen(本地名)+1][type = 0x09 (Complete Local Name)][本地名 bytes]
```

本地名来自全局缓冲 `0x100c1f700`（不是硬编码字符串），即设备名可被上层改写后重新广播。

### C2 EIR 是"逐条追加"的扁平结构，末尾回填长度 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| 汇编 `0x100653c90`–`0x100653d00` | 追加 32 字节（两个 128-bit UUID）后 `add w8,w8,#0x20; str w8,[x22,#0x408]` |
| 汇编 `0x100653fxx`（C 行 573） | `*(byte*)(len_base + 0x100c3e2d1) = (cVar2 - iVar5) - 3`：对某个 AD 结构回填长度字节 |
| 字面量 | `Service specific EIR data length: %d + constEirLen: %d = %d > %d` |
| C 行 575 | `if (0xef < (int)uVar11)` → 长度超过 `0xEF`(239) 时走错误日志 |

即：构造器维护"当前已用长度"，每追加一段就更新 `0x100c3e408`；某一段（服务 UUID 列表）的长度字节在末尾用 `当前长度 - 起点 - 3` 回填。总长硬上限为 `0xEF + 1 = 240`，超过时记录 `Service specific EIR data length …` 错误。**这是平台无关约束：EIR 服务列表必须分段塞进 240 字节。**

### C3 128-bit UUID 以"大端存储、小端上线"的方式复制 `CONFIRMED`

复制循环（汇编 `0x100653ca0`–`0x100653cc0`，以 WiAP 段为例）：

```
x12 = 0x10093a5c6
x11 = 0xf              ; 15
loop:  x14 = x11 - x9          ; 15,14,...,0
       ldrb w14, [x12, x14]    ; 从高地址往低地址读
       strb w14, [x19, w13]    ; 向 EIR 顺序写
```

读取方向是**递减**，写入方向是**递增**。因此内存中是 UUID 的大端字节序（与 RFC 4122 文本顺序一致），写入 EIR 后变成**小端（LSB first）**——这正是蓝牙 EIR 128-bit UUID 列表要求的字节序。

四条复制点的基址（汇编行号 / 地址）：

| 复制点 | 指令地址 | 源基址 | 覆盖字节范围 | 对应日志 |
|---|---|---|---|---|
| A1 | `0x100653ca0` | `0x10093a5c6` | `0x10093a5c6..0x10093a5d5` | `0x100653d30` Advertising WiAP |
| A2 | `0x100653cdc` | `0x10093a5d6` | `0x10093a5d6..0x10093a5e5` | 同上 |
| B1 | `0x100653d90` | `0x10093a5e6` | `0x10093a5e6..0x10093a5f5` | `0x100653e20` WiAP Sink and Classic CarPlay |
| B2 | `0x100653dcc` | `0x10093a5f6` | `0x10093a5f6..0x10093a605` | 同上 |
| C1 | `0x100653ea8` | `0x10093a606` | `0x10093a606..0x10093a615` | `0x100653f00` CarPlay Gateway |

### C4 广播的 128-bit UUID 具体取值 `CONFIRMED`

把上述内存区间按大端解释（`source/firmware/bluetoothd` 直接读取，`__TEXT.__const`）：

| 段 | UUID | 备注 |
|---|---|---|
| A1 | `00000000-deca-fade-deca-deafdecacafe` | 与 C5 名称表中的 `WiapGateWay` 完全一致 |
| A2 | `02030302-1d19-415f-86f2-22a2106a0a77` | 与 C5 表中 `WiapGateWay_v2` 共享后 12 字节，但前 4 字节不同，见 `OPEN-DISC-1` |
| B1 | `00000000-deca-fade-deca-deafdecacaff` | 与 C5 表中 `WiapSink` 一致（末字节 `0xFF`） |
| B2 | `ec884348-cd41-40a2-9727-575d50bf1fd3` | 与 C5 表中 `Carplay` 一致 |
| C1 | `2d8d2466-e14d-451c-88bc-7301abea291a` | 与 C5 表中 `CarplayGateway` 一致 |

原始字节（大端，可逐字节复核）：

```
A1 00 00 00 00 de ca fa de de ca de af de ca ca fe
A2 02 03 03 02 1d 19 41 5f 86 f2 22 a2 10 6a 0a 77
B1 00 00 00 00 de ca fa de de ca de af de ca ca ff
B2 ec 88 43 48 cd 41 40 a2 97 27 57 5d 50 bf 1f d3
C1 2d 8d 24 66 e1 4d 45 1c 88 bc 73 01 ab ea 29 1a
```

上线顺序（EIR 中实际字节）为上述序列的**逐字节逆序**，例如 A1 上线为：

```
fe ca ca de af de ca de de fa ca de 00 00 00 00
```

四个 UUID 的 version nibble（第 7 字节高 4 位）分别为 `f`(保留)、`4`、`f`(保留)、`4`、`4`；variant 字节（第 9 字节）为 `de`、`86`、`de`、`97`、`88`。前两个 `deca-fade` 系列是人工构造的非 RFC-4122 UUID，属于 Apple 私有标识，不能按 v4 规则解析。

### C5 UUID → 服务名映射表 `FUN_1003d56fc` `CONFIRMED`

`0x1003d56fc` 是 `char* f(const uint8_t uuid[16])`，逐条比较两个 8 字节半部，返回常量服务名。汇编逐条复核（`0x1003d575c`–`0x1003d57b0` 等），全部常量与下表一致：

| 服务名 | UUID |
|---|---|
| `SyncMLServer` | `01000000-0000-1000-8000-0002ee000002` |
| `SyncMLClient` | `02000000-0000-1000-8000-0002ee000002` |
| `D2D` | `00000000-deca-cafe-deca-cafedecacafe` |
| `WiapGateWay` | `00000000-deca-fade-deca-deafdecacafe` |
| `WiapSink` | `00000000-deca-fade-deca-deafdecacaff` |
| `WiapGateWay_v2` | `08ed27c3-1d19-415f-86f2-22a2106a0a77` |
| `WiapSink_v2` | `08ed27c3-1d19-415f-86f2-22a2106a0a78` |
| `AapServer` | `7221ec74-0bad-4d01-8f77-997b2be0722a` |
| `AapService` | `4b6f7c4b-07f4-49de-b0b9-ab4304728f29` |
| `AapClient` | `1ff31936-572e-4b36-a2bf-b2409b1aa6f4` |
| `Magnet` | `04e10d1e-00b1-432a-b764-ddba983af941` |
| `Carplay` | `ec884348-cd41-40a2-9727-575d50bf1fd3` |
| `CarplayGateway` | `2d8d2466-e14d-451c-88bc-7301abea291a` |

末尾还有一条**蓝牙基础 UUID 兜底分支**：

| 依据 | 内容 |
|---|---|
| 汇编 `0x1003d58xx`（C 行 57） | `*(long*)(p+1) != 0x8000008000100000` 或 `p[3] != 0x5f9b34fb` → `"unknown"` |
| 语义 | 若 UUID 形如 `xxxx____-0000-1000-8000-00805f9b34fb`，走 `FUN_1003d59f8` 转成短 UUID 名称 |

注意 `0x5f9b34fb` 是内存中的小端值，对应文本 `fb349b5f` 的反序，即标准蓝牙基础 UUID 尾部 `…-00805F9B34FB`。

#### C5.1 v2 那对 UUID 在内存里是分开存的

`WiapGateWay_v2` / `WiapSink_v2` 的**完整 16 字节字符串在镜像里并不连续**，直接按整串搜会漏掉：

| 片段 | 地址 | 内容 |
|---|---|---|
| 首半部 `08ed27c3-1d19-415f` | `0x100934c30` | 与 v2 接收端共用 |
| 尾半部 `86f222a2-106a-0a77` | `0x10093a1b0`、`0x10093a5de`、`0x1009551a8` | 网关 |
| 尾半部 `86f222a2-106a-0a78` | `0x100934c38`、`0x1009551b8` | 接收端 |

`0x1003d56fc` 正是「先比首半部、再比尾半部」的两段式比较（C5 已复核），所以两个名字都成立。

另有一处**不一致**：EIR 的 UUID 列表（`0x10093a5c6` 起）里排第二的条目是
`02030302-1d19-415f-86f2-22a2106a0a77`，首 4 字节与名称表的 `08ed27c3-…` 不同——
这就是 `OPEN-DISC-1`，至今未解释。


### C6 可发现性的开关是"扫描核心 Page Scan" `PARTIAL`

| 依据 | 内容 |
|---|---|
| 函数 | `0x100137ee8`（`phone_fn_100137ee8`） |
| 字面量 | `ScanCorePageScan`（`0x100a6dfdf`，引用点 `0x100137fc0`）、`ScanCorePageScanDebugEnabled`、`ScanCorePageScanInterval`、`ScanCorePageScanWindow`、`ScanCorePageScanInterlaced`、`ScanCorePageScanDebugElnaMode`、`ScanCorePageScanUseAuxScanParams`、`ScanCorePageScanEnableAuxScan`、`ScanCorePageScanPreemptAuxScan`、`ScanCorePageScanAuxScanDurationInMs` |
| C 行 42 | `*(undefined1 *)(param_1 + 0x78) = 1`（使能标志） |
| C 行 45 | `FUN_100137874()`（构造扫描条件） |
| C 行 72 | `(**(code**)(*plVar6 + 0x48))(plVar6, &name_cfg, &debug_cfg, param_1 + 0x1f9)` → 虚调用下发扫描参数，输出到 `param_1+0x1f9` |
| C 行 82 | `if (*(char*)(param_1+0x1f9) == 1)` → 依据返回值决定后续路径 |

`ScanCorePageScan` 一族配置键表明 iOS 用一组**可调参数**（interval/window/interlaced/aux scan）控制 page scan，即"可发现性"不是布尔开关，而是带占空比与旁路扫描策略的状态机。另一处 `0x1001479fc` 的日志 `Received Scan Core Page Scan Request for event: %s, scanCorePageScanState: %s` 说明它由事件驱动，并带状态名。

`PARTIAL` 的原因：`0x100137ee8` 之后的分支（C 行 91 起，共 313 行）未逐条核对到"最终写 HCI `Write_PageScan_Activity`"的落点；HCI 侧证据只是存在 `OI_HCIMD_WritePageScanActivity` / `writePageScanActivityCb`（`0x10031f498`、`0x10031f688`）等函数，未与 `0x100137ee8` 直接连线。

### C7 经典 EIR 与 LE CarPlay 共存并被显式区分 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| 字面量 `0x100b16548`（引用 `0x100653b68`） | `Advertising LE CarPlay` —— 说明构建经典 EIR 时也会记录 LE CarPlay 的状态 |
| 字面量 `0x100b19c11`（引用 `0x100676558`，函数 `0x100676460`） | `Received LE CarPlay in EIR from %{public}s, ignore it` |
| 字面量 `0x100a6c1e8` / `0x100a6c2c7` / `0x100a6c2e4`（函数 `0x100646ff4`） | `BT_SERVICE_WIRELESS_IAP`、`BT_SERVICE_WIRELESS_IAP_SINK`、`BT_SERVICE_WIRELESS_CARPLAY` |

含义：对端若把 **LE** CarPlay 的标识塞进 **经典** EIR，iPhone 明确"看到并忽略"。因此平台实现不能指望"经典 EIR 里出现 LE UUID 就代表对方支持 LE CarPlay"；两条通道的发现必须分开判定。

## 3. 对实现的约束（进入 spec）

1. EIR 长度必须按 `[len][type][data]` 三字节开销精确计算，总长 ≤ 240。
2. 128-bit UUID 在 EIR 中必须**小端**；同一 UUID 在 SDP 记录中必须**大端**（见 `02`）。两者字节序相反，是最常见的互操作错误来源。
3. 判定"对方是 CarPlay 设备"应使用 `ec884348-cd41-40a2-9727-575d50bf1fd3` / `2d8d2466-e14d-451c-88bc-7301abea291a` / `00000000-deca-fade-deca-deafdecacafe|ff` 这组固定字节，而不是字符串匹配。
4. 本地名是可变数据，不能作为设备类型判据。

## 3.5 运行时佐证（跨构建，不改变上文证据等级）

抓包（`runtime/observations/findings-sdp-hci.md` §4）显示：**CarPlay 族的两个 UUID 在 SDP 报文中以逆序字节出现**：

| UUID | 固件内存（实测） | SDP 线上（抓包） |
|---|---|---|
| `ec884348-cd41-40a2-9727-575d50bf1fd3` | 文本序 | `d31fbf50-5d57-2797-a240-41cd484388ec` |
| `2d8d2466-e14d-451c-88bc-7301abea291a` | 文本序 | `1a29eaab-0173-bc88-1c45-4de166248d2d` |

而 WiAP 族在 SDP 中为**文本序**（`00 00 00 00 de ca fa de …`）。

两种字节序在同一份固件里并存：

- EIR 路径：`0x100653368` 的复制循环**逆序**读取（`03`–`06` 五处站点）→ EIR 一律逆序；
- 名称比较：`0x1003d56fc` 用**文本序**立即数（如 `0x1003d58b8` 构造 `0xa24041cd484388ec`）；
- SDP 路径：WiAP 文本序、CarPlay 逆序（抓包实测，三构建一致）。

因此"CarPlay 族在 SDP 中也逆序"是**运行时候选结论**，不升级为 `CONFIRMED`（原因未知，记 `OPEN-RUN-1`）；但它对实现是硬要求——按文本序匹配会匹配不到真实设备，故已写入 `spec/01` R-1.8a–R-1.8c。

## 4. 未决

| 编号 | 内容 | 原因 |
|---|---|---|
| `OPEN-DISC-1` | EIR A2 段 `02030302-1d19-415f-86f2-22a2106a0a77` 与名称表 `WiapGateWay_v2 08ed27c3-…` 前 4 字节不同的原因 | 内存字节已确认，但无语义证据说明是否刻意区分"EIR 广播用"/"SDP 记录用"两套 UUID |
| `OPEN-DISC-2` | 12 个 `Advertising …` 段各自的**启用位**（service mask 位）完整映射 | 仅确认 WiAP 段前出现 `0x20000`、WiAP Sink+CarPlay 段前出现 `0x40000`；`0x100646ff4` 中 `BT_SERVICE_WIRELESS_*` 与位的对应未逐条核对 |
| `OPEN-DISC-3` | `Advertising  CarPlay Gateway` 的双空格是否为固件笔误 | 字面量 `0x100b1659a` 确为双空格；仅影响日志检索，不影响协议 |
| `OPEN-DISC-4` | page scan 参数默认值与 HCI 落点 | 见 C6，未连线到 HCI 命令 |
| `OPEN-RUN-1` | 为何 CarPlay 族 UUID 在 SDP 报文中走逆序、而 WiAP 族走文本序 | 抓包三构建一致，但固件内未定位到"传入 SDP 组包前是否做字节序转换"的调用点；`0x1003d56fc` 的比较用文本序，说明差异发生在别处 |
