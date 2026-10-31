# analysis/03 — 帧格式与校验和

对应任务书第 5 节第 3 项。本文件是整份文档的字节级基础：帧头布局、长度、控制字段、序号字段、校验和算法与测试向量。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2PacketCreate` | `0x100006e24` | 通用建帧（写头部 8 字节 + 校验） |
| `iAP2PacketGenerateBuffer` | `0x1000088b8` | 发送前重算头部长度、写 SOF、算校验 |
| `iAP2PacketParseBuffer` | `0x10000a5d0` | 逐字节接收状态机 |
| `iAP2PacketCalcChecksum` | `0x100008ae8` | 校验和算法（8 位 / 16 位两种） |
| `iAP2PacketSetHdrChecksum` | `0x1000071f4` | 写头部校验（1 或 2 字节） |
| `iAP2PacketGetHdrChecksum` | `0x100008e80` | 读头部校验（返回指针 + 宽度） |
| `iAP2LinkCurPckHdrSize` | `0x100005f4c` | 头部长度 9 / 10 |
| `iAP2LinkCurPckChksumSize` | `0x100005f38` | 校验字段宽度 1 / 2 |
| `iAP2PacketGetPayloadLen` | `0x100006120` | 载荷长度 = 总长 − 头 − 校验 |
| `iAP2LinkGetMaxPayloadSize` | `0x1000070fc` | 单帧最大载荷 |

## 3.1 帧头固定 8 字节 + 校验字段 1 或 2 字节

`A03.1`（已确认）头部固定部分为 **8 字节**，其后紧跟头部校验字段；头部总长 = 8 + 校验宽度。

证据 `iAP2PacketCreate`（`0x100006e24`）写头部的完整序列：

```
0x100006eb0: add  w9, w19, w27      ; w19 = 有载荷时的校验宽度，否则 0；w27 = 含头校验的 9/10
0x100006eb4: add  w9, w9, w28       ; w28 = 载荷长度
0x100006eb8: strh w9, [x21, #0x36]  ; 总长写到包对象 offset 0x36
0x100006ebc: mov  w10, #0x5aff
0x100006ec0: strh w10, [x8]         ; hdr[0..1] = FF 5A（小端存 → 字节序 FF,5A）
0x100006ec4: lsr  w10, w9, #8
0x100006ec8: strb w10, [x8, #2]     ; hdr[2] = 长度高字节
0x100006ecc: strb w9,  [x8, #3]     ; hdr[3] = 长度低字节
0x100006ed0: strb w26, [x8, #4]     ; hdr[4] = 参数 w1（控制字段）
0x100006ed4: strb w25, [x8, #5]     ; hdr[5] = 参数 w2（序号）
0x100006ed8: strb w24, [x8, #6]     ; hdr[6] = 参数 w3（lt 字节）
0x100006edc: strb w22, [x8, #7]     ; hdr[7] = 参数 w6（extra 字节）
```

其中 `w27` 来自 `iAP2LinkCurPckHdrSize`，`w19` 来自 `iAP2LinkCurPckChksumSize`：

```
; iAP2LinkCurPckHdrSize
0x100005f4c: ldrb  w8, [x0, #0xd5]   ; link->checksum_type
0x100005f50: cmp   w8, #2
0x100005f54: mov   w8, #9
0x100005f58: cinc  w0, w8, eq        ; type==2 → 10, 否则 9
```

```
; iAP2LinkCurPckChksumSize
0x100005f38: ldrb  w8, [x0, #0xd5]
0x100005f3c: cmp   w8, #2
0x100005f40: mov   w8, #1
0x100005f44: cinc  w0, w8, eq        ; type==2 → 2, 否则 1
```

结论：头部固定 8 字节，加上 1 或 2 字节头部校验。`0x100006e74` 在载荷长为 0 时跳过校验宽度调用，因此无载荷帧总长是头长 9/10，不含尾校验；`0x10000894c` 同样在零载荷时跳过尾校验生成。23G90 日志中的纯 ACK 长度 9 与此一致。

`A03.2`（已确认）**总长字段覆盖整帧**（头固定部分 + 头校验 + 载荷 + 载荷校验）：`w9 = 载荷长度 + 头部长度 + 校验宽度`，`iAP2PacketGetPayloadLen` 反向相减：

```
; iAP2PacketGetPayloadLen(packet)
0x100006134: mov  x19, x0
0x100006138: ldr  x20, [x0]          ; x20 = packet->link
0x100006140: bl   0x100005f4c         ; hdrSize
0x100006144: mov  x21, x0
0x100006148: bl   0x100005f38         ; chksumSize
0x100006150: ldrh w8, [x19, #0x36]    ; 总长
0x100006154: add  w9, w0, w21         ; chksumSize + hdrSize
0x100006158: subs w8, w8, w9
0x10000615c: csel w8, w8, wzr, hi     ; 下溢则 0
```

## 3.2 线格式（本阶段确认的部分）

```
偏移  宽度  字段            证据
0     2     FF 5A           A03.1（0x100006ec0）
2     2     总长（大端）     A03.1（0x100006ec4/0x100006ec8）
4     1     控制字段         A03.1（0x100006ed0）
5     1     序号             A03.1（0x100006ed4）；另见 0x100035414 `ldrb w0,[x8,#5]`
6     1     lt 字节          A03.1（0x100006ed8）
7     1     extra 字节       A03.1（0x100006edc）
8    1|2    头部校验         A03.3
9|10  n     载荷             A03.2
…    1|2    载荷校验         A03.4
```

`A03.3`（已确认）头部校验写在 `hdr + 8`，宽度由 `(packet[0x3d] >> 12) & 3` 决定：

```
; iAP2PacketGetHdrChecksum(packet)
0x100008e80: ldr   x8, [x0, #0x40]     ; hdr = packet->hdr
0x100008e84: ldurh w9, [x0, #0x3d]     ; flags
0x100008e88: ubfx  w1, w9, #0xc, #2    ; 宽度 = bits[13:12]
0x100008e8c: add   x0, x8, #8          ; 指针 = hdr + 8
```

```
; iAP2PacketSetHdrChecksum(packet, type, value)
0x100007208: ldr  x8, [x0, #0x40]      ; hdr
0x10000721c: strb w2, [x8, #8]         ; type==0 → 1 字节
0x100007244: rev16 w9, w2
0x100007248: strh w9, [x8, #8]         ; type==1 → 2 字节（大端）
```

`A03.4`（已确认）载荷校验在载荷之后，长度为载荷长，写入 `packet->payload + payloadLen`（`iAP2PacketGenerateBuffer` 尾部）：

```
0x100008950: mov  x0, x22          ; x22 = packet->payload
0x100008954: mov  x1, x21          ; 载荷长度
0x100008958: mov  x2, x20          ; 校验类型
0x10000895c: bl   0x100008ae8      ; CalcChecksum(payload, len, type)
0x100008960: mov  x1, x0
0x100008964: strh w21, [x19, #0x34]; 记录载荷长度
0x10000896c: bl   0x100008d48      ; SetPayloadChecksum
```

> 注意：`iAP2PacketSetPayloadChecksum`（`0x100008d48`）、`iAP2PacketGetPayloadChecksum`、`iAP2PacketGetChecksum` 在符号表中**没有独立入口**（被内联），因此载荷校验的具体写入宽度只能由 `CalcChecksum` 返回值宽度（16 位）与 `CurPckChksumSize` 一致推断 —— 这一处标 `OPEN-FRAME-1`。

## 3.3 校验和算法（两种，按 link 的 checksum type 选择）

`iAP2PacketCalcChecksum(ptr x0, len w1, type w2)`（`0x100008ae8`）。

`A03.5`（已确认）**type == 0：8 位字节和的两补数**。

```
0x100008bd4: mov   w8, #0
0x100008bd8: add   x9, x19, w20, uxtw
0x100008bdc: ldrb  w10, [x19], #1
0x100008be0: add   w8, w10, w8
0x100008be4: cmp   x19, x9
0x100008be8: b.ne  0x100008bdc
0x100008bec: neg   w8, w8
0x100008bf0: and   w8, w8, #0xff
```

即 `cksum8 = (-(Σ byte)) & 0xFF`。

`A03.6`（已确认）**type == 1：按 20 字节分块的 sum1/sum2 累加，折叠后取 16 位两补数**。

```
0x100008b20: mov  w8, #0xff        ; sum2 初值 0xFF
0x100008b24: mov  w10, #0x14       ; 块长 20
0x100008b28: mov  w9, #0xff        ; sum1 初值 0xFF
; 每块：
0x100008b2c: cmp   w20, #0x14
0x100008b30: csel  w11, w20, w10, lo   ; n = min(remain, 20)
0x100008b40: ldrb  w14, [x13], #1
0x100008b44: add   w9, w9, w14          ; sum1 += byte
0x100008b48: add   w8, w9, w8           ; sum2 += sum1
...（循环 n 次）
0x100008b54: add   x19, x19, w11, uxtw  ; 指针前进 n
0x100008b58: ubfx  w12, w9, #8, #8
0x100008b5c: add   w9, w12, w9, uxtb    ; sum1 = (sum1>>8) + (sum1 & 0xFF)
0x100008b60: ubfx  w12, w8, #8, #8
0x100008b64: add   w8, w12, w8, uxtb    ; sum2 = (sum2>>8) + (sum2 & 0xFF)
0x100008b68: subs  w20, w20, w11
0x100008b6c: b.ne  0x100008b2c
; 收尾：
0x100008b70: lsr   w10, w9, #8
0x100008b74: add   w9, w10, w9, uxtb    ; 再折叠一次
0x100008b78: add   w8, w8, w8, lsl #8   ; sum2 移到高字节
0x100008b7c: and   w8, w8, #0x3ff00
0x100008b80: orr   w8, w8, w9
0x100008b84: neg   w8, w8
0x100008b88: b     0x100008d20          ; 返回 w8 & 0xFFFF
```

等价的规范描述（见 `spec/02-framing-and-checksum.md`）：

```
sum1 = 0xFF; sum2 = 0xFF
对数据按 20 字节分块（末块可短）：
    对块内每个字节 b: sum1 += b; sum2 += sum1
    sum1 = (sum1 & 0xFF) + ((sum1 >> 8) & 0xFF)
    sum2 = (sum2 & 0xFF) + ((sum2 >> 8) & 0xFF)
sum1 = (sum1 & 0xFF) + (sum1 >> 8)
cksum16 = (-(((sum2 + (sum2 << 8)) & 0x3FF00) | sum1)) & 0xFFFF
```

`A03.7`（已确认，2026-10-26 更正）**创建默认使用 8 位（算法 0）**。link 字段值和算法编号由一个转换函数相连，旧版遗漏转换而误称默认 16 位：

```
; iAP2LinkCreate
0x1000340d4: mov  w8, #1
0x1000340d8: strb w8, [x19, #0xd5]    ; link->checksum_type = 1
```

从原镜像偏移 `0x71e4..0x71f4` 可重复解码（不是改写原始 source 导出）：

```text
0x1000071e4: ldrb w8,[x0,#0xd5]
0x1000071e8: cmp  w8,#2
0x1000071ec: cset w0,eq
0x1000071f0: ret
```

`GenerateBuffer` 在 `0x1000088e4` 调它取得算法参数。字段 1 → 算法 0/宽度 1，字段 2 → 算法 1/宽度 2。`CalcChecksum` 对其他算法编号走错误分支，不是“所有非 0 都走 16 位”。包 flags bits[13:12] 保存算法 0/1；SetHdrChecksum 同步调整的是 `packet+0x48` 的载荷指针，不是链路计数器：

```
; iAP2PacketSetHdrChecksum 维护 packet 的载荷指针
0x100007220: ldurh w8, [x0, #0x3d]
0x100007224: and   w9, w8, #0x3000
0x100007228: cmp   w9, #0x1000
0x100007230: ldr   x9, [x0, #0x48]    ; packet->payload
0x100007234: sub   x9, x9, #1
```

> `OPEN-FRAME-2` 旧说法混淆了对象。此处已确认是 packet 载荷指针。连接提交时的模式写入见 `A04.13`（`0x1000300e0..ec`）；其他复位/兼容分支尚需完整核验。16 位算法末步必须保留 `sum2 + (sum2<<8)` 的进位，旧简化式对部分输入不等价。

## 3.4 控制字段取值

`A03.8`（已确认）控制字段是位掩码，观察到的常量来自各构造函数的立即数：

| 值 | 含义 | 证据 |
|---|---|---|
| `0x80` | SYN | `iAP2PacketCreateSYNPacket` `0x100103174`（无附加参数时） |
| `0xC0` | SYN + ACK | 同上 `0x100103168`（有附加参数时） |
| `0x40` | ACK | `iAP2PacketCreateACKPacket` `0x100006fa0` |
| `0x60` | ACK + EAK | `iAP2PacketCreateEAKPacket` `0x1001031e0` |
| `0x10` | RST | `iAP2PacketCreateRSTPacket` `0x1001031f4` |
| `0x08` | SUS | `iAP2PacketCreateSUSPacket` `0x100103214` |

`iAP2PacketCreateSYNPacket` 的两个分支：

```
0x100103160: cbz  x21, 0x100103170
0x100103164: ldrb w3, [x21]        ; lt 字节 = 参数结构首字节
0x100103168: mov  w1, #0xc0        ; 控制 = 0xC0
0x10010316c: b    0x100103178
0x100103170: mov  w3, #0
0x100103174: mov  w1, #0x80        ; 控制 = 0x80
```

因此位定义：`bit7=SYN, bit6=ACK, bit5=EAK, bit4=RST, bit3=SUS`。

`A03.9`（未确认 / `OPEN-FRAME-3`）控制字段其余位（bit0–bit2）与"载荷校验存在位"没有取到写入证据。

## 3.5 单帧最大载荷

`A03.10`（已确认）`maxPayload = min(link[0x1a6], link[0xc0]) − (12 | 10)`，12 对应 16 位校验、10 对应 8 位：

```
; iAP2LinkGetMaxPayloadSize(link, session)
0x100007100: ldrh w8, [x0, #0x1a6]
0x100007104: ldrh w9, [x0, #0xc0]
0x100007108: cmp  w8, w9
0x10000710c: csel w8, w8, w9, lo       ; min
0x100007114: ldr  w9, [x1, #0x28]      ; session 上限（若有）
0x100007118: cmp  w9, w8
0x10000711c: csel w8, w9, w8, lo
0x100007120: ldrb w9, [x0, #0xd5]      ; checksum type
0x100007124: cmp  w9, #2
0x100007128: mov  w9, #-0xa
0x10000712c: mov  w10, #-0xc
0x100007130: csel w9, w10, w9, eq      ; type==2 → -12，否则 -10
0x100007134: add  w0, w9, w8
```

`+12 = 8（头固定）+ 2（头校验）+ 2（载荷校验）`；`+10 = 8 + 1 + 1`，与 3.1 的头部长度一致，可交叉验证。

`link[0xc0]` 在 `iAP2LinkCreate` 中由参数 `x6` 写入（`0x1000340ac: strh w25,[x19,#0xc0]`）。`link[0x1a6]` 的来源已补证：对端 SYN `+4` 经 `0x10003533c..340` 写工作块 `+0x174`，连接动作再复制至生效块 `+0x1a6`（`A04.13`）。`OPEN-FRAME-4` 的写入点部分关闭。

## 3.6 收发两个方向共用同一构造

`A03.11`（已确认）`iAP2PacketCreate` 的最后一个参数 `w7` 只决定从**发送池**还是**接收池**取包，帧格式相同：

```
0x100006e84: cbz  w20, 0x100006e98
0x100006e88: add  x1, sp, #0xc
0x100006e8c: bl   0x10000626c      ; iAP2PacketCreateEmptySendPacket
0x100006e90: b    0x100006ea0
0x100006e98: bl   0x10000a488      ; iAP2PacketCreateEmptyRecvPacket
```

## 3.7 接收解析是"逐字节状态机"

`A03.12`（已确认）`iAP2PacketParseBuffer` 以 `packet[0x3d] & 0xFF` 为状态做 18 路跳转（`0x10000a668`–`0x10000a694`，跳表 `0x10000ad30`），状态 0 读取首字节并分流：

```
0x10000a698: str   wzr, [x24, #0x34]
0x10000a69c: strh  wzr, [x24, #0x38]
0x10000a6a0: str   wzr, [x24, #0x2c]
0x10000a6a4: ldrb  w8, [x25]
0x10000a6a8: cmp   w8, #0x55
0x10000a6ac: b.eq  0x10000abe4      ; 0x55 → 传统 iAP 帧分支
0x10000a6b0: cmp   w8, #0xff
0x10000a6b4: b.ne  0x10000aca8      ; 其它 → 错误分支
0x10000a6b8: strb  w8, [x23]        ; hdr[0] = 0xFF
0x10000a6bc: mov   w8, #1
0x10000a6c0: strb  w8, [x24, #0x3d] ; 状态 = 1
```

其中一个状态在收齐头部后把状态置 0x11：

```
0x10000a6ec: ldrh  w9, [x24, #0x36]
0x10000a6f0: sub   w9, w9, #2
0x10000a6f4: cmp   w8, w9
0x10000a6f8: b.ne  0x10000acb0
0x10000a6fc: mov   w8, #0x11
0x10000a700: strb  w8, [x24, #0x3d]
```

- 状态数与逐字节语义的**完整映射**（哪个状态对应哪个字段）需要通读 1,888 字节的汇编，本阶段未做穷尽 → `OPEN-FRAME-5`。
- 已确认的是：解析器按 `hdr[0x2c]` 递增写头部缓冲、按 `v0.2s` 累加字节参与校验、并在收齐后与 `CalcChecksum` 比较。

`A03.13`（已确认）长度字段存在性检查使用大端：解析出的 16 位值直接与总长比较，未做字节交换，而写头部时是 `hdr[2]=hi, hdr[3]=lo` —— 二者一致，**长度为大端**。

## 3.8 与"传统 iAP 帧"共存

`A03.14`（已确认）0x55 分支把同一个缓冲解释为 iPod Accessory Protocol 帧 `FF 55 <len> <cmd> … EE <cksum>`。判定函数（见 `analysis/07-idps.md`）直接匹配这些字节：

```
; iAP2PacketCheckDetect，hdr = packet[0x40]
0x100102e48: ... cmp w11,#0x55   ; [0] 或 [1] = 0x55
0x100102e58: cmp w11,#2      ; 长度 = 0x02
0x100102e68: cbnz w11        ; 命令字节 = 0x00
0x100102e7c: cmp w10,#0xee   ; 结束字节
0x100102e8c: cmp w8,#0x10    ; 校验字节 = 0x10
```

`A03.15`（已确认）传统 iAP 帧的校验和**不覆盖同步字节 `FF 55`**，只覆盖从长度字节到载荷末字节（含）：

```
传统帧：FF 55 <len:1> <payload[len]> <cksum:1>
cksum  = (-(len + Σ payload)) & 0xFF
```

推导证据（两帧独立吻合）：

| 帧 | 参与校验的字节 | 和 | 校验值 |
|---|---|---|---|
| Detect `FF 55 02 00 EE 10` | `02 00 EE` | `0xF0` | `0x10` ✔（固件 `0x100102e8c` 比较 `0x10`） |
| RequestIdentify `FF 55 02 00 FE 00` | `02 00 FE` | `0x00` | `0x00` ✔ |
| DetectNACK `FF 55 04 00 02 04 EE 08` | `04 00 02 04 EE` | `0xF8` | `0x08` ✔（固件 `0x100102f44` 比较 `0x08`） |

若按"覆盖 `FF 55`"计算，Detect 得 `0xBC`、DetectNACK 得 `0xB4`，与固件常量不符 —— 因此**排除**该解释。

与之对照，iAP2 帧的头部校验**覆盖** `FF 5A`：`iAP2PacketGenerateBuffer` 以 `(hdr, 8)` 调用 `CalcChecksum`（`0x100008928`–`0x100008934`），头部 8 字节含同步字节。**两种帧的校验范围不同，这是必须显式处理的差异。**

`A03.16`（已确认）固件中存在传统帧的静态模板：`source/firmware/accessoryd` 偏移 `0x1b3378`（VA `0x1001b3378`）起的 6 字节为

```
ff 55 02 00 ee 10
```

即 Detect 帧整帧被固化为常量，与 `iAP2PacketCheckDetect` 的逐字节比较完全一致。

## 3.9 测试向量

按 A03.5 / A03.6 的算法算出（`verify.py` 会重算并比对）：

| # | 数据 | 类型 | 期望值 | 来源 |
|---|---|---|---|---|
| V1 | `02 00 EE`（Detect 帧去掉 `FF 55` 与校验） | 8 位 | `0x10` | 固件常量：帧模板 `0x1001b3378` + 比较 `0x100102e8c` |
| V2 | `04 00 02 04 EE`（DetectNACK 同上） | 8 位 | `0x08` | 固件常量：比较 `0x100102f44` |
| V3 | `FF 5A 00 09 80 00 00 00`（8 字节头，SYN） | 16 位 | `0x581D` | 由 A03.6 计算 |
| V4 | 空数据（len=0） | 16 位 | `0x0000`（`len==0` 直接返回 0，`0x100008b14`） | 固件分支 |

> V3/V4 的期望值写在 `spec/02-framing-and-checksum.md` 的向量表中；`verify.py` 用本文件的算法实现独立重算。

## 3.10 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-FRM-1` | 传统帧载荷末字节（`0xEE` / `0xFE`）的语义 |
| `OPEN-FRAME-1` | 载荷校验写入宽度（1 或 2）无独立函数证据，仅有 `CurPckChksumSize` 与返回宽度推断 |
| `OPEN-FRAME-2` | `link[0x48]` 计数用途 |
| `OPEN-FRAME-3` | 控制字段 bit0–bit2 语义 |
| `OPEN-FRAME-4` | 写入来源已确认：对端 SYN 包长→工作块→连接提交（A04.13）；与其他上限联动见 OPEN-FRAME-7 |
| `OPEN-FRAME-5` | 逐字节解析状态机 18 个状态的完整字段映射 |
| `OPEN-FRAME-6` | `lt` 字节（hdr[6]）与 `extra` 字节（hdr[7]）的语义 |
