# 03 RED 冗余

## 3.1 何时有 RED

所述SETUP路径在sp+5c非零时声明supportsRTPPacketRedundancy=true（A02.14），其上游条件待核。
声明只代表能力，**不证明一定启用**。包是否带 RED 由 PT 决定：

| PT | 名字 | 是否带 RED 描述符 | 依据 |
|---:|---|---|---|
| 97 | gred | 是 | `INFERRED` RED-02 |
| 104 | mred | 是 | `INFERRED` RED-02 |
| 105 | ared | 是（但接收准入本来就拒） | `INFERRED` RED-02，与 `A01.2` 冲突，见 3.6 |
| 108 | axrd | 是 | `INFERRED` RED-02 |
| 109 | ovrd | 是 | `INFERRED` RED-02 |
| 96 | gen | 仅 `maxPackets>1` 时 | `INFERRED` RED-02 |
| 100 | main | 否 | `INFERRED` RED-02 |

`maxPackets` 是会话/传输对象的内部状态，本阶段没有找到它的赋值点（`0x2519c0c90` 附近的比较
只被读到）。所以「什么时候从 main(100) 切成 mred(104)」仍属 `OPEN-RED-1`。

## 3.2 描述符格式（本阶段复核）

RFC 2198 风格：**冗余块头 4 字节，主块头 1 字节**。反汇编 `0x251ace454`：

```text
0x251ace454  ldrsb w9,[x0]
0x251ace458  and   w8,w9,#0xff        ; 输出字节0 = 头字节低8位（含 F 位）
0x251ace45c  str   w8,[x1]
0x251ace460  tbz   w9,#0x1f, done     ; bit7=0 -> 主块，结束
0x251ace464  ldr   w9,[x0]            ; 4 字节头按大端
0x251ace468  rev   w9,w9
0x251ace46c  lsr   w10,w9,#2
0x251ace470  and   w10,w10,#0x3fff00  ; = ((W>>10)&0x3fff) << 8   -> delta
0x251ace474  orr   w9,w10,w9,lsl#22   ; = (W & 0x3ff) << 22       -> length
0x251ace478  orr   w8,w9,w8
0x251ace47c  str   w8,[x1]
0x251ace480  cbz   x2,done
0x251ace484  tst   w8,#0x80
0x251ace488  mov   w8,#4
0x251ace48c  csinc x8,x8,xzr,ne       ; F=1 -> 前进4；F=0 -> 前进1
0x251ace490  add   x9,x0,x8
0x251ace494  str   x9,[x2]
```

于是单个 4 字节头（大端 W）的位域为：

| 字段 | 位 | 值域 | 说明 |
|---|---|---:|---|
| F | bit31（= 首字节 bit7） | 1 bit | 1=冗余块头，0=主块头 |
| PT | bit30..24（首字节低 7 位） | 7 bit | 块内 payload type |
| timestamp delta | bit23..10 | 14 bit | `(W>>10)&0x3fff` |
| block length | bit9..0 | 10 bit | `W&0x3ff` |

主块头只有 1 字节：F=0 + 7 位 PT。因此块数 n 的**描述符总长 = 4*(n-1)+1 = 4n-3**
（`A03.3`，`INFERRED` RED-04 的同式）。

## 3.3 负载布局

```text
[M的10B消息头][冗余块头 ×(n-1)][主块头 ×1][数据区][provider附加输出（若有）]
```

元素位于数据之前；旧RED-02的“RTP12”坐标已由analysis09校正为内部I+12与M+10，
不能当真实网络头。具体密码输出须绑定provider后去除，不假定所有音频恒24B尾。

## 3.4 序列号与时间戳还原

对第 i 块（0 基，i = n-1 为主块）：

```text
seq_i  = (outerSeq + i - (n-1)) & 0xFFFF
ts_i   = outerTs                       , 主块
       = (outerTs - delta_i) & 0xFFFFFFFF , 冗余块
```

依据 `INFERRED` RED-03 / MR02（`0x251ace49c` 的 `ldr x8,[x0,#0xa8]` 分支计算
`outerSeq+index-totalBlocks+1`）。n=2 时冗余块恰好是 `primary-1`，与 MR02 一致（`A03.4`）。

## 3.5 解码步骤（参考实现口径）

1. 从消息M+10的元素区开始定位描述符；F=1读4B，F=0读1B并结束；无元素分支g=0。
2. 块数 `n = len(headers)`；没有显式块数字段，靠 F 链终止。
3. 对适用profile先完成认证/解密，再校验：`sum(冗余块 length) ≤ 明文数据区大小`；主块长度 = 数据区大小 − 该和（主块头不含
   长度，RED-02 原文 "primary takes remainder"）。超出即整包拒绝。
4. 按 3.4 推导每块 seq/ts，按 3.3 切数据。
5. 明文块交给解码/恢复策略；不能把未经认证密文直接分块发布。

`reference-impl/red_decoder.py` 实现上述五步，`test_vectors.json` 覆盖：两块、四块回绕、
时间戳回绕、字段极大值、零长块、头截断、长度不符、超块数上限。**注意**：允许 0 长块是
语法层结论，不代表 codec 接受空帧。

## 3.6 已知矛盾与未闭合

- **矛盾**：RED-02 说接收侧对 105(`ared`) 也启用扩展布局，但 `A01.2` 的准入掩码把 105 拒了。
  两者是新旧两处检查，本阶段无法判定哪一处是活路径。本文件的实现按「掩码先拒」处理，
  并在 `OPEN-RED-1` 里记录该冲突。
- `OPEN-RED-1`：冗余深度（`maxPackets`）的取值与切换条件、105 的接收可达性。
- `OPEN-RED-2`：发送侧「先加密再冗余」还是「先冗余再加密」——RED 描述符明文这一点是清楚的，
  但冗余块里装的是密文还是明文没有证据。
- 完整RED密码布局仍须绑定具体provider，不能在未证时规定每块独立或每网络包恰一条密码记录（`OPEN-CRYPT-1`）。
