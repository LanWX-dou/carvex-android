# spec/02 — 帧格式与校验

## 2.1 帧结构

`R-2.1`（MUST / CONFIRMED）iAP2 帧由四段组成，顺序固定：

```
+--------+--------+----------------+-----------+--------+----------+
| SOF(2) | 长度(2)| 控制(1) 序号(1) | 其余头(2) | 头校验 | 载荷 | 载荷校验 |
+--------+--------+----------------+-----------+--------+----------+
  offset 0   2        4        5          6,7      8      9|10
```

- 头部固定部分 = 8 字节；
- 头部校验宽度 = 1（8 位校验）或 2（16 位校验）；
- 头部总长 = 8 + 校验宽度 = **9 或 10**；
- 有载荷时，载荷校验宽度与头部校验宽度相同；**无载荷帧只有头部及头校验**，总长为 9 或 10，不追加空载荷校验。

依据：`A03.1`（`iAP2PacketCreate` `0x100006e24`）、`A03.3`（`iAP2PacketGetHdrChecksum` `0x100008e80`、`iAP2LinkCurPckHdrSize` `0x100005f4c`、`iAP2LinkCurPckChksumSize` `0x100005f38`）。

`R-2.2`（MUST / CONFIRMED）SOF 为 `FF 5A`；长度字段为**整帧长度**（含 SOF、头校验、载荷、载荷校验），**大端**编码（`hdr[2]=高字节`、`hdr[3]=低字节`）。

依据：`A03.1`、`A03.2`（`iAP2PacketGetPayloadLen` `0x100006120` 以"总长 − 头长 − 校验宽"求载荷长）。

`R-2.3`（MUST / CONFIRMED）控制字段是位掩码：

| 位 | 值 | 含义 |
|---|---|---|
| bit7 | `0x80` | SYN |
| bit6 | `0x40` | ACK |
| bit5 | `0x20` | EAK（扩展确认） |
| bit4 | `0x10` | RST |
| bit3 | `0x08` | SUS（挂起） |

`SYN|ACK = 0xC0`、`ACK|EAK = 0x60`。bit2–bit0 语义未确认（`OPEN-FRAME-3`）。

依据：`A03.8`（各构造函数立即数：`0x100103168`/`0x100103174`/`0x100006fa0`/`0x1001031e0`/`0x1001031f4`/`0x100103214`）。

`R-2.4`（MUST / CONFIRMED）序号占 1 字节（`hdr[5]`），8 位模 256（见 `R-4.1`）。

`R-2.5`（MUST / CONFIRMED）带 ACK 位（bit6）的帧在**发送时**把 `hdr[6]` 覆写为链路本地字节：

```
if (hdr[4] & 0x40) { hdr[6] = link->hdr6_byte; link->flags |= 0x08; }
```

依据：`A01.3`（`__iAP2LinkSendPacketCommon` `0x10000796c`–`0x100007998`）。`hdr[7]` 的接收语义已由 control `R-2.1` 确认为会话号；`hdr[6]` 在恢复路径写作 `link[0xBC]`（input `R-6.5`，INFERRED），其完整语义仍归 `OPEN-FRAME-6`，不得据此推广到所有帧。

## 2.2 校验和

`R-2.6`（MUST / CONFIRMED）存在两种校验算法，由链路选择：

**类型 0 — 8 位两补数**

```
cksum8(data[0..n-1]) = (-(Σ data[i])) & 0xFF        // n == 0 时返回 0
```

**类型 1 — 16 位分块两补数**

```
cksum16(data[0..n-1]):
    if n == 0: return 0
    sum1 = 0xFF; sum2 = 0xFF
    for each block of at most 20 bytes, in order:
        for b in block:
            sum1 = (sum1 + b) & 0xFFFFFFFF
            sum2 = (sum2 + sum1) & 0xFFFFFFFF
        sum1 = (sum1 & 0xFF) + ((sum1 >> 8) & 0xFF)
        sum2 = (sum2 & 0xFF) + ((sum2 >> 8) & 0xFF)
    sum1 = (sum1 & 0xFF) + (sum1 >> 8)
    return (-(((sum2 + (sum2 << 8)) & 0x3FF00) | sum1)) & 0xFFFF
```

依据：`A03.5`、`A03.6`（`iAP2PacketCalcChecksum` `0x100008ae8`：8 位分支 `0x100008bdc`–`0x100008bf0`，16 位分支 `0x100008b20`–`0x100008b88`，`len==0` 分支 `0x100008b14`）。

`R-2.7`（MUST / CONFIRMED）头部校验覆盖**全部 8 个头部字节（含 `FF 5A`）**；载荷校验覆盖载荷全部字节。校验值**大端**写入（16 位时 `rev16` 后 `strh`）。

依据：`A03.3`（`0x100007244`）、`A03.4`（`iAP2PacketGenerateBuffer` `0x100008928` 以 `(hdr, 8)` 调 `CalcChecksum`）。

`R-2.8`（MUST / CONFIRMED）链路创建时 `link[0xd5]=1`，默认是 **8 位**校验。`iAP2LinkCurPckChksumSize` 只在该字段为 2 时返回宽度 2；`0x1000071e4` 将它转换为算法参数（字段 == 2 → 算法 1，否则算法 0）。不能把链路字段的 1 直接当作 CalcChecksum 的算法 1。连接通知动作 `0x1000300e0..ec` 将旧值保存到 `0xd6`，把生效 SYN version 写到 `0xd5`（`A04.13`）；重连/重置与解析器兼容分支仍需分别遵守 FSM，不能刚收到 SYN 就提前切换。

依据：`A03.7`（`0x1000340d8`、`0x100005f38`、`0x100005f4c`、`0x1000071e4`）。

`R-2.9`（MUST / CONFIRMED）单帧最大载荷：

```
maxPayload = min(link.maxRecvPacket, link.maxPacketParam, sessionLimit)
             - (checksumIs16Bit ? 12 : 10)
```

依据：`A03.10`（`iAP2LinkGetMaxPayloadSize` `0x1000070fc`）。

## 2.3 传统 iAP 控制帧

`R-2.10`（MUST / CONFIRMED）传统帧结构与 iAP2 帧**不同**：

```
FF 55 <len:1> <payload[len]> <cksum:1>
cksum = (-(len + Σ payload)) & 0xFF      // 不含 FF 55
```

`len` 之后的字节不是"terminator + 命令"的固定布局：Detect 的 `payload = 00 EE`、DetectNACK 的 `payload = 00 02 04 EE`、RequestIdentify 的 `payload = 00 FE`。三者第 1 字节都是 `0x00`，**末字节分别为 `0xEE` / `0xEE` / `0xFE`**，其语义未取证 → `OPEN-FRM-1`。实现必须按字节模板逐字节发送，不得按"固定终止符"推导。

依据：`A03.15`、`A07.4b`。

`R-2.11`（MUST / CONFIRMED）三类链路建立期传统帧：

| 帧 | 字节 |
|---|---|
| Detect | `FF 55 02 00 EE 10` |
| DetectNACK | `FF 55 04 00 02 04 EE 08` |
| RequestIdentify | `FF 55 02 00 FE 00`（末字节按 `R-2.10` 计算；固件只比较前 5 字节） |

依据：`A07.1`–`A07.4`、`A03.16`（静态模板 `0x1001b3378`）。

## 2.4 校验范围的对齐要求

`R-2.12`（MUST / CONFIRMED）实现方**不得**用同一个校验入口同时处理两种帧：iAP2 帧的校验范围包含同步字节，传统帧不包含。建议接口形状：

```
checksum(data, len, type)          // 纯算术，见 R-2.6
iap2_hdr_checksum  = checksum(hdr, 8, type)
legacy_checksum    = checksum(&frame[2], 1 + len, 0)
```

依据：`A03.15`、`R-2.7`。

## 2.5 测试向量

`verify.py` 会用 `R-2.6`/`R-2.10` 的算法重算下表并比对。

| # | 输入 | 类型 | 期望 | 来源 |
|---|---|---|---|---|
| V1 | `02 00 EE` | 8 位 | `0x10` | Detect 帧（固件常量 `0x1001b3378` + 比较 `0x100102e8c`） |
| V2 | `04 00 02 04 EE` | 8 位 | `0x08` | DetectNACK（比较 `0x100102f44`） |
| V3 | `02 00 FE` | 8 位 | `0x00` | RequestIdentify（按规则计算） |
| V4 | `FF 5A 00 09 80 00 00 00` | 16 位 | `0x581D` | 仅算术向量；长度 9 不是合法 16 位帧 |
| V5 | `FF 5A 00 09 C0 00 00 00` | 16 位 | `0x57DC` | 仅算术向量；不是可发送的 SYNACK |
| V6 | （空） | 16 位 | `0x0000` | `len == 0` 分支 `0x100008b14` |

## 2.6 未决项

| ID | 内容 |
|---|---|
| `OPEN-FRM-1` | 传统帧载荷末字节语义（`0xEE` vs `0xFE`） |
| `OPEN-FRAME-1` | 载荷校验在 8 位模式下的写入宽度（推断与头校验一致） |
| `OPEN-FRAME-2` | `link[0x48]` 计数用途 |
| `OPEN-FRAME-3` | 控制字段 bit2–bit0 |
| `OPEN-FRAME-4` | 写入来源已确认（A04.13）；其他上限联动见 OPEN-FRAME-7 |
| `OPEN-FRAME-5` | 逐字节解析状态机的完整字段映射 |
| `OPEN-FRAME-6` | `hdr[6]` / `hdr[7]` 语义 |
| `OPEN-IDPS-1` | RequestIdentify 末字节未被固件校验（本规范按规则取值） |
## 本章依据

| 条款 | 分析结论 | 关键地址 |
|---|---|---|
| `R-2.1` | `A03.1`、`A03.3` | — |
| `R-2.2` | `A03.1`、`A03.2` | — |
| `R-2.3` | `A03.8` | — |
| `R-2.5` | `A01.3` | — |
| `R-2.6` | `A03.5`、`A03.6` | — |
| `R-2.7` | `A03.3`、`A03.4` | — |
| `R-2.8` | `A03.7` | — |
| `R-2.9` | `A03.10` | — |
| `R-2.10` | `A03.15`、`A07.4b` | — |
| `R-2.11` | `A03.16`、`A07.1`、`A07.4` | — |
| `R-2.12` | `A03.15` | — |

> 上表由条款正文的 `A` 编号与地址自动汇总；逐条依据见各条款下方的"依据"行。
