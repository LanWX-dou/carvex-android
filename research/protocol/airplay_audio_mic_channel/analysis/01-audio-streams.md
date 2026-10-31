# 01 音频流：类型、方向、端口

## 1.1 结论先行

AirPlay 音频在**同一条 AirPlay 连接**上以多条 RTP 流承载，流的身份由 SETUP 的
`streams` 数组逐项协商；包内身份由 RTP payload type（PT）区分，PT 与内部消息名一一对应。
**PT 不是 SETUP 的 raw stream type**，两套编号不能互换（`A01.5`）。

## 1.2 两套编号

| 层 | 取值 | 含义 | 证据 |
|---|---|---|---|
| SETUP raw stream type | 96/100/101/102/103/106/107/110/111/120/130 | 一次 SETUP 请求里 `streams[i].type` 的整数 | `INFERRED`（SS-03、SRR02） |
| 包内 payload type | 96/97/100/101/104/105/106/107/108/109 | RTP 第二字节低 7 位 | `CONFIRMED`（`0x24fdad430`、`0x24fe44bc0`） |

内部名（4 字节 FourCC，小端存放在 `0x24fe44bc0` 起 16 项 × 4 字节表中）：

| PT | 内部名 | 接收准入 | 发送侧可达 | 备注 |
|---:|---|---|---|---|
| 96 | `gen` | 是（仅 `maxPackets>1` 时按 RED 解析） | 是 | 通用/screen 侧也用 |
| 97 | `gred` | 是 | 是 | 通用 RED |
| 100 | `main` | 是 | 是 | 主音频（媒体音与麦克风都走它） |
| 101 | `alt ` | **否** | 是 | 掩码 bit5 未置位 |
| 104 | `mred` | 是 | 是 | main 的 RED |
| 105 | `ared` | **否** | 是 | 掩码 bit9 未置位 |
| 106 | `auxo` | 是 | 是 | 语义未证 |
| 107 | `oovc` | 是 | 是 | 语义未证 |
| 108 | `axrd` | 是 | 是 | 语义未证 |
| 109 | `ovrd` | 是 | 是 | 语义未证 |

复核方式（可复算）：`0x24fdad438` 把 `pt-0x60` 与 `#0xe` 比较，`0x24fdad448` 载入
`0x3d13` 右移 `pt-0x60` 位做准入判定，`0x24fdad458` 用同一索引从 `0x24fe44bc0` 取 4 字节名。
`0x3d13` 的置位集合 = {0,1,4,8,10,11,12,13}，加 96 正好是上表「接收准入=是」的八个值。
**接收集合比发送集合小**：101/105 只出现在发送侧，客户端不能假设「对称准入」（`A01.2`）。

## 1.3 方向

| 通道 | 方向 | 承载 | 证据 |
|---|---|---|---|
| 媒体音（音乐/播客/通话下行） | 设备 → 车机 | `raw100`（+RED 时 `104`） | `INFERRED`（MA-02） |
| 备用/替代音（`alt`） | 设备 → 车机 | `raw101` | `INFERRED`（MA-02、SS-03） |
| 麦克风 | 车机 → 设备 | `raw100` 的 **input** 方向 + `minp` 传输 | `INFERRED`（MR04、`0x2519c8dac`） |
| 导航提示音 | 未证 | 可能是独立 `raw` 或 `audioType` 子类型 | `OPEN-AUD-1` |

方向不是靠 PT 决定的：同一个 `raw100` 在 SETUP 里带 `input=true` 就是麦克风方向，
不带就是扬声器方向；`dataPort` 的语义随之反向（`A01.4`、`A06.4`）。

## 1.4 端口与传输

- `controlPort` / `dataPort` 是 SETUP 每流的字段，键名已从常量表读出（`A02.3`）：
  `0x2693e7c68` = `controlPort`、`0x2693e7c78` = `dataPort`。
- 麦克风方向的 `dataPort` 写的是**本机监听端口**（`LocalNetworkPort`），不是车机端口；
  写入点是 `0x2519be8f4..0x2519be91c`（`A02.6`）。
- 传输标识 `minp`（`0x6d696e70`）是 **transport stream ID**，不是音频消息类型
  （`A06.3`，`INFERRED`，依据 `0x2519c8dac`）。
- 实际端口的数值属于运行期协商结果，本阶段无抓包：`OPEN-PORT-1`。

## 1.5 未闭合

- `OPEN-AUD-1`：导航提示音到底是独立 `raw` 流、独立 `audioType`，还是媒体流内的混音。
- `OPEN-AUD-2`：`106 auxo`、`107 oovc`、`108 axrd`、`109 ovrd` 的业务语义；固件只给出名字与准入。
- `OPEN-PORT-1`：`controlPort`/`dataPort` 的真实取值、是否随车机变化。

## 1.6 补证：raw type 名字表（本轮新增，取代 1.3 的 `INFERRED` 枚举）

`0x2519c459c` 之前的比较逻辑：

```text
0x2519c4564  ldr  w10,[x0,#8]        ; raw type
0x2519c4570  sub  w11,w10,#0x60
0x2519c4574  cmp  w11,#0x18          ; 96..119
0x2519c457c  mov  w12,#0xfcf1
0x2519c4580  movk w12,#0x100,lsl#16  ; 掩码 0x100fcf1
0x2519c4584  lsr  w12,w12,w11
0x2519c4588  tbz  w12,#0,fail
0x2519c458c  adrp x10,0x2693e5000
0x2519c4590  add  x10,x10,#0xda0     ; 名字表
0x2519c4594  ldr  x10,[x10,w11,uxtw #3]
```

掩码 `0x100fcf1` 的置位是 `{0,4,5,6,7,10,11,12,13,14,15,24}`，而表 `0x2693e5da0` 里
**恰好只有这些槽非空**——两处互相印证，不是猜的：

| raw | 槽 | 名字 | 地址 |
|---:|---:|---|---|
| 96 | 0 | GeneralAudio | `0x251beecdd` |
| 100 | 4 | MainAudio | `0x251beecea` |
| 101 | 5 | AltAudio | `0x251beecf4` |
| 102 | 6 | MainHighAudio | `0x251beecfd` |
| 103 | 7 | BufferedAudio | `0x251beed0b` |
| 106 | 10 | AuxAudio | `0x251beed19` |
| 107 | 11 | OutOfBandAVVCAudio | `0x251beed22` |
| 108 | 12 | AuxAudioWithRedundancy | `0x251beed35` |
| 109 | 13 | OutOfBandAVVCAudioWithRedundancy | `0x251beed4c` |
| 110 | 14 | MainScreen | `0x251beed6d` |
| 111 | 15 | AltScreen | `0x251beed78` |
| 120 | 24 | Playback | `0x251beed82` |

新增事实：108/109 是「带冗余的 aux / out-of-band AVVC」，110/111 是屏幕流，120 是 Playback。
这解释了为什么 PT 表里 108=`axrd`、109=`ovrd` 自带「redundant」含义（`A01.6`）。
同一张表被 `carAudioStream_teardownTransportStreams` 的日志复用（`0x251beecbf` 的
`Tearing down %s`），所以它是**流类型名**而不是包类型名。

