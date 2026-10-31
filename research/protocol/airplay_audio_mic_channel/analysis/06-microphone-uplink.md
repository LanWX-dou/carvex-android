# 06 麦克风上行

## 6.1 端到端链路

```text
选中 AudioFormatInfo ─┬─> SETUP: {type:100, input:true, dataPort:<本机监听口>, audioType, audioFormat, audioLatencyMs}
                      └─> sink 格式配置 class+0x10 / 准备 class+0x18

本机 UDP listener（minp） ← 车机发来的 RTP 包
        │
        ▼
回调 0x2519c0b88（白名单 |主|mred|oovc|ovrd|）
        │  dispatch_async(queue +0x168, 块 0x2519c0f08)
        ▼
就绪/暂存门（+0x170 / +0x198）→ 容量 20 的暂存队列
        ▼
处理函数 0x2519c1234（RED 拆分 → InputKey 解密(+0x180) → sink 消费）
```

方向是**车机 → 设备**；SETUP 的 `dataPort` 在 input 方向上是「我愿意在这个端口收」
（`A01.4`、`A06.4`）。

## 6.2 协商字段（本阶段复核）

本机 `dataPort>0` 时才写 `input=true` 与 `dataPort`：

```text
0x2519be8f4  cmp   w22,#1
0x2519be8f8  b.lt  skip
0x2519be8fc  adrp  x8,0x2693e7000
0x2519be900  add   x8,x8,#0xc40      ; "input"
0x2519be904  bl    #0x2519ae150     ; 取常量
0x2519be908  mov   x2,x21           ; kCFBooleanTrue
0x2519be90c  bl    #0x2580f7000     ; dict set
0x2519be910  ldr   x1,[x27]         ; "dataPort"
0x2519be914  mov   w2,w22
0x2519be918  mov   x0,x28
0x2519be91c  bl    #0x25810a790     ; dict set int
```

`input` 常量的取值来自全局单例 `0x2680d30198` 解引用（`x21`），与
`supportsHighAccuracyTimestamps`/`supportsRTPPacketRedundancy` 用的是同一个 true 值
（`0x2519be920..0x2519be958`，`A02.4`）。

## 6.3 接收白名单（本阶段复核）

`0x2519c0b88` 是 transport 收包回调。它只放行四个 32 位消息标签：

```text
0x2519c0bc0  mov  w8,#0x7662 ; movk w8,#0x6f6f,lsl#16   ; 0x6f6f7662 二分枢轴
0x2519c0bc8  cmp  w21,w8 ; b.gt -> 0x2519c0bec
0x2519c0bd0  mov  w8,#0x696e ; movk #0x6d61,lsl#16      ; "main"
0x2519c0be0  mov  w8,#0x6564 ; movk #0x6d72,lsl#16      ; "mred"
0x2519c0bec  mov  w8,#0x7264 ; movk #0x6f76,lsl#16      ; "ovrd"
0x2519c0bfc  mov  w8,#0x7663 ; movk #0x6f6f,lsl#16      ; "oovc"
0x2519c0c04  cmp  w21,w8 ; b.ne  0x2519c0c78            ; 其它直接返回
```

放行集合 = `{main(0x6d61696e), mred(0x6d726564), oovc(0x6f6f7663), ovrd(0x6f767264)}`
（`A06.1`）。注意 **`gen`/`gred`/`auxo`/`axrd` 不在白名单**：麦克风方向不接受这些，
即使全局准入掩码允许（`A01.2` 与本节是两个独立的门）。

## 6.4 投递与暂存

放行后：retain 消息 → 取 `[stream+0x168]` 队列 → 构造块（invoke `0x2519c0f08`）→
`0x2580f4bb0`（dispatch_async）（`A06.2`）。块内按 5.3 的门表处理。

暂存语义的两个已证细节（`INFERRED`，`input-contract-worker/transaction.md`）：

- 暂存队列只存**消息本体**，不存每包的 FourCC；排空时把当前回调的 type 传给每个 pending 包。
- enqueue 失败只记日志；其额外 retain 是否回收在该出口未证。

这两点直接影响实现：本地队列若随包保存 type，或溢出即释放，属于**本地增强**，
不能写成「固件原规则」。

## 6.5 传输与端口

- 传输 ID `minp`（`0x6d696e70`，即 ASCII "minp"），QoS 3，UDP listener
  （`INFERRED`，`0x2519c8dac`、`0x24fda8e4c`、`0x24fdb1ec8`）。
- 顺序是「先建 listener → 读 `LocalNetworkPort` → 再发 SETUP」（`INFERRED`，`0x2519be194..0x2519be3f8`）。
- handler 由 `APSRTPPacketHandlerCreate(allocator, 2, 2, NULL, &handler)` 创建（模式 2 = 带 SeqQ）；
  调用点 `0x2519be3e4` 之后**没有检查返回值**（`INFERRED`）。实现必须自己把分配失败当失败处理。
- 回调安装是 `transport class+0x18`，context 是当前 CarPlay stream（`INFERRED`，`0x2519c0b88`）。

## 6.6 解密与消费

`InputKey` 派生后存 `+0x180`，作为处理函数 `processOne` 的 x3 传入
（`INFERRED`，`0x2519c11d8..0x2519c11e4`）。也就是说麦克风包走的是**同一套**
RED/解密路径（见 03、04），只是密钥方向相反。

## 6.7 未闭合

- `OPEN-MIC-1`：采集端采样率/位深/声道、编码器与帧长。SETUP audioFormat整数类型已核（analysis10）；
  整数→基础格式映射与传输/HAL转换已见analysis11；完整能力交集及方向选择继续静态追踪，
  不以缺mic包为停止条件。真实选值另验。
- `OPEN-MIC-2`：增益、降噪、回声消除是否由设备侧做（固件里没看到相关分支）。
- `OPEN-MIC-3`：车机对 mic 流的门控（什么时候允许上行、静音/打断语义）。
