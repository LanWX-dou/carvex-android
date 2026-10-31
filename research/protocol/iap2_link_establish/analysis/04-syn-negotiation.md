# analysis/04 — SYN 协商

对应任务书第 5 节第 4 项。

证据函数：

| 函数 | 地址 | 作用 |
|---|---|---|
| `iAP2LinkSetDefaultSYNParam` | `0x1000328b0` | 写缺省 SYN 参数 |
| `iAP2PacketCreateSYNPacket` | `0x100102fdc` | 构造 SYN 载荷 |
| `iAP2PacketParseSYNData` | `0x100103230` | 解析对端 SYN 载荷 |
| `iAP2LinkIsValidSynParam` | `0x1000328dc` | 参数合法性总校验 |
| `__iAP2LinkIsValidSynParamMaxOutstandingPackets` | `0x100033114` | 单字段校验 |
| `__iAP2LinkIsValidSynParamMaxRetransmissions` | `0x100033284` | 单字段校验 |
| `__iAP2LinkIsValidSynParamMaxCumAck` | `0x100033338` | 单字段校验 |
| `__iAP2LinkIsValidSynParamCumAckTimeout` | `0x1000331d4` | 单字段校验 |
| `iAP2LinkIsNoRetransmit` | `0x100008590` | "对端未要求重传"判定 |
| `iAP2LinkCheckNegotiation` | `0x100035154` | 协商结论 |
| `iAP2LinkDeviceActionSendSYNACK` | `0x10002fcd4` | 回 SYNACK |
| `iAP2LinkDeviceActionResendSYNACK` | `0x10002feb0` | 重发 SYNACK |

## 4.1 参数结构（内存布局）

`A04.1`（已确认，复核修正）链路对象内嵌两份 50 字节 SYN 参数结构：工作块 `0x168..0x199` 与生效块 `0x19a..0x1cb`。创建时先复制调用方参数到工作块，再初始化生效块；旧文“强制覆盖调用方参数”混淆了目的地址。

```
0x1000341a4: str  x21, [x19, #0x160]      ; 调用方传入的参数结构指针
0x1000341a8: add  x8, x19, #0x168
0x1000341ac: ldp  q0, q1, [x21]           ; 复制 0x32 字节
0x1000341b0: ldr  q2, [x21, #0x20]
0x1000341b4: ldrh w9, [x21, #0x30]
0x1000341b8: strh w9, [x19, #0x198]
0x1000341bc: stp  q1, q2, [x8, #0x10]
0x1000341c0: str  q0, [x8]
; 然后在另一块 +0x19a 写缺省值：
0x1000341c4: add  x8, x19, #0x19a
0x1000341c8: add  x9, x19, #0x19e
0x1000341cc: mov  w10, #0x3e8ffff
0x1000341d0: str  w10, [x9]               ; [0x19e]=0xFFFF, [0x1a0]=0x03E8
0x1000341d4: mov  w9, #0xa
0x1000341d8: strh w9, [x19, #0x1a2]       ; [0x1a2]=10
0x1000341dc: adrp x9, #0x1001b3000
0x1000341e0: ldr  d0, [x9, #0x348]        ; 常量 0x1001b3348
0x1000341e4: str  s0, [x8]                ; [0x19a..0x19d]
0x1000341e8: mov  w8, #-0xff00
0x1000341ec: str  w8, [x19, #0x1a4]       ; [0x1a4]=00, [0x1a5]=01, [0x1a6]=FF, [0x1a7]=FF
```

常量 `0x1001b3348` 的原始字节（`source/firmware/accessoryd` 偏移 `0x1b3348`）：

```
01 01 1e 00
```

于是缺省结构为：

| 偏移 | 宽度 | 缺省值 | 字段 | 证据 |
|---|---|---|---|---|
| `+0x00` | 1 | `0x01` | 协议版本（SYN 载荷第 0 字节） | 常量 + A04.3 |
| `+0x01` | 1 | `0x01` | MaxOutstandingPackets | `0x100033128` 读 `[syn+1]` |
| `+0x02` | 1 | `0x1e`(30) | MaxRetransmissions | `0x10003329c` 读 `[syn+2]` |
| `+0x03` | 1 | `0x00` | MaxCumAck | `0x10003334c` 读 `[syn+3]` |
| `+0x04` | 2 | `0xffff` | （未命名，须 > 23） | `0x100032970` |
| `+0x06` | 2 | `0x03e8`(1000) | ACK 定时超时（毫秒，定时器 id `0xC`，须 > 19） | `0x100032b44`；发送路径 `0x100007a58` 直接读该字段作超时 |
| `+0x08` | 2 | `0x000a`(10) | CumAckTimeout | `0x1000331ec` |
| `+0x0a` | 1 | `0x00` | 特性条目数（构造时填充） | `0x1001039c8` |
| `+0x0b` | 1 | `0x01` | （未命名） | 常量 |
| `+0x0c` | 2 | `0xffff` | （未命名） | 常量 |
| `+0x18` | 1 | — | 扩展字段字节数 | A04.3 |
| `+0x19` | n | — | 扩展字段 | A04.3 |
| `+0x1e` | 4×n | — | 特性条目（最多 5 条） | A04.3 |

`A04.2`（已确认）`iAP2LinkSetDefaultSYNParam`（`0x1000328b0`）写的是同一套缺省值（供其它调用方复用）：

```
0x1000328b4: mov  w8, #0x3e8ffff
0x1000328b8: str  w8, [x0, #4]
0x1000328bc: mov  w8, #0xa
0x1000328c0: strh w8, [x0, #8]
0x1000328c4: adrp x8, #0x1001b3000
0x1000328c8: ldr  d0, [x8, #0x348]
0x1000328cc: str  s0, [x0]
0x1000328d0: mov  w8, #-0xff00
0x1000328d4: stur w8, [x0, #0xa]
```

## 4.2 线格式（SYN 载荷）

`A04.3`（已确认）SYN 载荷最短 10 字节；`iAP2PacketParseSYNData(payload x0, len w1, out x2)` 的返回值为 `len > 9`：

```
0x100103230: subs w8, w1, #0xa
0x100103234: b.lo 0x1001033b0        ; len < 10 → 直接判定失败
...
0x1001033b0: cmp  w1, #9
0x1001033b4: cset w0, hi
```

字段顺序（解析侧，写侧对称，见 A04.4）：

| 载荷偏移 | 宽度 | 字节序 | 目标结构偏移 | 证据 |
|---|---|---|---|---|
| 0 | 1 | — | `+0x00` | `0x100103238` → `[x2]` |
| 1 | 1 | — | `+0x01` | `0x100103240` → `[x2+1]` |
| 2–3 | 2 | 大端 | `+0x04` | `0x100103248`–`0x10010325c` |
| 4–5 | 2 | 大端 | `+0x06` | `0x100103260`–`0x100103274` |
| 6–7 | 2 | 大端 | `+0x08` | `0x100103278`–`0x10010328c` |
| 8 | 1 | — | `+0x02` | `0x100103290` |
| 9 | 1 | — | `+0x03` | `0x100103298` |
| 10 | 1 | — | `+0x0a` | A04.5 |

注意：**结构内 `+0x02/+0x03` 在线上的位置是 8/9**，而线上 2–7 是三组大端 16 位字。字段的物理顺序与结构顺序不同，实现时必须按线格式写。

`A04.4`（已确认）写侧 `iAP2PacketCreateSYNPacket` 与解析侧逐字段对称：

```
0x10010304c: ldrb w8, [x22]       ; d[0]
0x100103050: ldrb w9, [x22, #1]   ; d[1]
0x100103054: ldrh w10, [x22, #4]  ; d[4] (u16)
0x100103058: ldrh w11, [x22, #6]
0x10010305c: ldrh w12, [x22, #8]
0x100103060: ldrh w13, [x22, #2]  ; d[2] (u16)
0x10010306c: strb w8, [sp, #9]    ; payload[0]
0x100103070: strb w9, [sp, #0xa]  ; payload[1]
0x100103074: lsr  w9, w10, #8
0x100103078: strb w9, [sp, #0xb]  ; payload[2] = d[4] 高字节
0x10010307c: strb w10, [sp, #0xc] ; payload[3] = d[4] 低字节
...（d[6] → payload[4..5]，d[8] → payload[6..7]）
0x100103098: sturh w13, [sp, #0x11]  ; payload[8..9] = d[2]，小端
```

`payload[8..9]` 用 `sturh` 小端写入，即 `payload[8] = d[2] 低字节`、`payload[9] = d[3]`（`d[2]` 的两个字节被当作两个独立字节字段），与解析侧 `out[2]=payload[8]`、`out[3]=payload[9]` 一致。

`A04.5`（已确认）版本相关尾部：

- `version == 0`：总长 10 字节，无尾部；
- `version == 1`：`out[0x18] = 0`，特性条目数由**剩余长度 / 3** 推出（`len*0xAAAAAAAB >> 33`，即 `len/3`）；
- `version >= 2`：`payload[10]` = 扩展字节数 `k`（上限 5），`payload[11..11+k]` 为扩展字节；随后 `payload[11+k]` = 特性条目数 `n`（上限 5）；条目从 `12+k` 开始，每条 3 字节。

证据（解析侧）：

```
0x1001032a0: cbz  w10, 0x1001032c8        ; version 0
0x1001032a4: cmp  w10, #1
0x1001032a8: b.ne 0x1001032d0             ; version >= 2
0x1001032ac: mov  w9, #0xaaab
0x1001032b0: movk w9, #0xaaaa, lsl #16
0x1001032b4: umull x8, w8, w9             ; w8 = len-10
0x1001032b8: lsr  x10, x8, #0x21          ; ⇒ len/3
0x1001032bc: strb wzr, [x2, #0x18]
0x1001032c0: mov  w8, #0xa
```

```
0x1001032d0: ldrb w9, [x0, #0xa]          ; k
0x1001032d4: cmp  w9, #5
0x1001032dc: csel w8, w9, w10, lo         ; min(k,5)
0x1001032e0: strb w8, [x2, #0x18]
...（复制 k 字节到 out+0x19）
0x10010330c: add  x9, x8, #0xb
0x100103310: ldrb w10, [x0, x9]           ; n = payload[11+k]
0x100103314: add  w8, w8, #0xc
```

`A04.6`（已确认）特性条目每条 3 字节，展开成 4 字节结构：

| 线上字节 | 结构字段 | 掩码/移位 |
|---|---|---|
| `e[0]` | `+0` | — |
| `e[1]` | `+1` = `e[1] & 0x7F`；`+3` = `e[1] >> 7` | `0x100103378` / `0x100103380` |
| `e[2]` | `+2` | — |

条目数的循环上限为 `min(n, 5)`：

```
0x100103328: cmp  w11, #5
0x100103330: csel w10, w11, w12, lo       ; w12 = 5
```

## 4.3 合法性规则

`A04.7`（已确认）逐字段规则（`iAP2LinkIsValidSynParam` 与其 4 个子校验）：

| 字段 | 规则 | 证据 |
|---|---|---|
| version | 调用参数 minVersion 必须为 1..3，且 `minVersion <= version < 4`；不等于 `0..4` | `0x10003290c`–`0x100032930` |
| MaxOutstandingPackets | `1..127`（有符号字节比较）；无重传模式另允许 0 | `0x100033128`–`0x100033144` |
| MaxRetransmissions | `1..30`（`(v-1) < 0x1E` 无符号） | `0x10003329c`–`0x10003330c` |
| MaxCumAck | `>= 0` 且 `<= MaxOutstandingPackets` | `0x10003334c`–`0x100033360` |
| CumAckTimeout | `10..32767`（有符号 16 位） | `0x1000331ec`–`0x100033258` |
| `+0x04` | `> 23` | `0x100032970`–`0x100032978` |
| `+0x06` | `> 19`（仅当对端启用重传参数时） | `0x100032b44`–`0x100032b4c` |

```
; CumAckTimeout > 9
0x1000331ec: ldrsh w21, [x19, #8]!
0x1000331f0: cmp   w21, #9
0x1000331f4: b.gt  0x100033254
0x100033254: cmp   w21, #9
0x100033258: cset  w0, gt
```

```
; MaxRetransmissions ∈ 1..30
0x10003329c: ldrb w8, [x19, #2]!
0x1000332a0: sub  w21, w8, #1
0x1000332a4: cmp  w21, #0x1e
0x1000332a8: b.lo 0x100033308
0x100033308: cmp  w21, #0x1e
0x10003330c: cset w0, lo
```

```
; MaxCumAck <= MaxOutstandingPackets
0x10003334c: ldrsb w8, [x19, #3]!
0x100033354: and   w8, w8, #0xff
0x100033358: ldrb  w9, [x0, #1]
0x10003335c: cmp   w8, w9
0x100033360: b.ls  0x1000333b4         ; ok
```

`A04.8`（已确认）"对端未要求重传"的判定是四个重传相关字段全为 0：

```
; iAP2LinkIsNoRetransmit(syn)
0x1000085ac: ldrh w8, [x20, #6]!
0x1000085b0: cbnz w8, 0x1000085cc     ; +6 != 0 → 不是 no-retransmit
0x1000085b4: ldrh w8, [x19, #8]
0x1000085b8: cbnz w8, 0x1000085cc     ; +8 != 0
0x1000085bc: ldrb w8, [x19, #2]
0x1000085c0: cbnz w8, 0x1000085cc     ; +2 != 0
0x1000085c4: ldrb w8, [x19, #3]
0x1000085c8: cbz  w8, 0x100008654     ; +3 == 0 → return 1
```

当 `IsNoRetransmit(syn)` 为真时，`iAP2LinkIsValidSynParam` 跳过 `+0x06/CumAckTimeout/MaxRetransmissions/MaxCumAck` 的校验（`0x100032984: tbz w0,#0,0x100032b40`）。

`A04.9`（已确认）特性条目的额外约束（`iAP2LinkIsValidSynParam` 后段）：

```
0x100032a30: cbz  w9, 0x100032c04     ; e[0] == 0 → 非法
0x100032a38: cmp  w9, #4
0x100032a3c: b.hi 0x100032c04         ; e[1] > 4 → 非法
0x100032a40: ldrb w9, [x22, #3]
0x100032a44: tbnz w9, #0, 0x100032c04 ; e[3] bit0 = 1 → 非法
```

并且要求**至少一条**条目满足 `e[1] == 0`（控制类型）：

```
0x100032ab8: cmp  w9, #0
0x100032abc: csinc w23, w23, wzr, ne
0x100032ad0: cbz  w23, 0x100032c04
0x100032ad4: mov  w0, #1
```

`csinc …, ne` 在 NE 成立时保留 w23，在 EQ 时取 `wzr+1`。旧文把条件读反了。另有 `0x1000329c4` 拒绝零条目，`0x100032a04..a18` 拒绝重复 ID 或重复类型，`0x100032a80..ab4` 在调用方提供上下限表时按类型检查第三字节版本范围。低 7 位类型在解析时已与 flag 拆开，不能把结构里的类型字段称为未屏蔽的原始字节。

`A04.10`（`+0x06` 已确认 / `+0x04` 未确认）

- `+0x06`：**ACK 定时器超时时长**，单位毫秒。证据在发送路径 `__iAP2LinkSendPacketCommon`：

  ```
  0x100007a44: add  x0, x19, #0x19a
  0x100007a48: bl   0x100008590        ; IsNoRetransmit
  0x100007a54: ldr  x0, [x19, #0xc8]   ; 定时器对象
  0x100007a58: ldrh w2, [x19, #0x1a0]  ; SYN[+0x06] = 超时
  0x100007a5c: mov  w1, #0xc           ; 定时器 id 0xC
  0x100007a60: bl   0x100007ce8        ; iAP2TimeCallbackAfter
  ```

  缺省 1000 ms；合法性下限 `>19`（`0x100032b44`）的原因未取证 → `OPEN-SYN-6`。

- `+0x04`：缺省 `0xFFFF`，要求 `>23`。语义仍无直接证据（疑为最大包长），**不作规范结论** → `OPEN-SYN-1`。

## 4.4 协商结论

`A04.11`（已确认）`iAP2LinkCheckNegotiation(link, peer_syn)`：

1. 若 `link[0xb8] == 1`（设备模式）：调用 `iAP2LinkValidateSynParam`，失败则向 FSM 发事件 3（`iAP2LinkEventNotify`）；
2. 否则若 `link[0xd4]` bit6 置位（设备角色）：同样校验；
3. 若**本地**是 no-retransmit 而**对端**不是，则本地把 `+0x01=1, +0x02=30, +0x03=0, +0x04=0xFFFF, +0x06=1000, +0x08=10` 写回（即接受对端的重传能力，但本地按最小窗口 1 执行）：

```
0x1000351c0: add  x0, x20, #0x168
0x1000351c4: bl   0x100008590        ; 本地 no-retransmit?
0x1000351cc: mov  x0, x19
0x1000351d0: bl   0x100008590        ; 对端 no-retransmit?
0x1000351d8: add  x8, x20, #0x169
0x1000351dc: mov  w9, #0x1e01
0x1000351e0: strh w9, [x8]           ; MOP=1, MR=30
0x1000351e4: mov  w8, #0x3e8ffff
0x1000351e8: str  w8, [x20, #0x16c]  ; maxPkt=0xFFFF, [6]=1000
0x1000351ec: mov  w8, #0xa
0x1000351f0: strh w8, [x20, #0x170]  ; CumAckTimeout=10
0x1000351f4: strb wzr, [x20, #0x16b] ; MCA=0
```

4. 随后比较版本：本地较高时降级（`0x1000351f8`–`0x1000352cc`）。`0x1000352d0..31c` 将 MR/MCA/ACK/CumAck 超时按对端值取较小值。
5. 对端 no-retransmit 时将其 MOP 写到本地 `+0x169`；总是保存对端 MOP 到 `+0x173`、包长到 `+0x174`（`0x100035320..340`）。设备模式还复制扩展字节。
6. `0x100035380..394` 将对端 `syn+0xa` 写到 `link+0x172`，再复制 `4*n` 字节 `peer+0x1e → link+0x186`。这正是工作块里的会话表，不能说 SYN 字段与会话表无关。

`A04.13`（已确认）`iAP2LinkDeviceActionNotifyConnection`（`0x10003009c`）在 `0x1000300c0..dc` 将 `link+0x168` 的 50 字节整体提交到 `link+0x19a`：两次向量复制共 48 字节，另复制尾部半字 `+0x198 → +0x1ca`。所以生效计数在 `+0x1a4`、5 个 4 字节条目在 `+0x1b8..0x1cb`。随后 `0x1000300e0..ec` 保存旧校验模式到 `+0xd6`、将生效 version 写入 `+0xd5`，再上报连接。证据为同名原始 `.s` 与 Ghidra C；C 中折叠尾部不作为额外证据。最初 profile 分配者、多会话协商全部分支仍需另核对。

`A04.12`（未确认 / `OPEN-SYN-2`）协商**失败**后的完整处置（是否发 RST、是否回退到"无重传"模式、FSM 迁移到哪个状态）需要继续追踪 `iAP2LinkEventNotify`（`0x1000321a8`）与 `iAP2LinkDeviceActionSendRST` 的调用点，本阶段只确认"失败会向 FSM 发事件 3"。

## 4.5 未确认点汇总

| ID | 内容 |
|---|---|
| `OPEN-SYN-1` | 结构 `+0x04` 两个字节的语义（疑为最大包长） |
| `OPEN-SYN-6` | `+0x06`（ACK 超时）合法性下限 `>19` 的原因 |
| `OPEN-SYN-2` | 协商失败的完整处置路径 |
| `OPEN-SYN-3` | 校验范围已确认 minVersion..3；各 profile 版本选择仍待核对 |
| `OPEN-SYN-4` | 扩展字节 `payload[11..11+k]` 的语义（只确认长度与复制位置） |
| `OPEN-SYN-5` | control R-2.10 已给会话类型 0/1/2/4；类型 3 未明，不能与认证 feature ID 混淆 |
