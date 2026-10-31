# 02 FP 交换：编排（可移植部分）与黑箱（不可移植部分）

一句话结论：**交换的「怎么发、发几次、带什么字段、失败怎么判」全部可写；交换消息内部的字节语义不可写。**

---

## A-08 发送侧编排：`_fpAuthentication_AuthenticateEndpoint`（`0x251ace728`）

### 结构（按指令顺序）

```
0x251ace7b8  APCUGetFairPlayHWInfoEx(&hwInfo, 0, 0)          ; 取硬件信息（96 字节区，见下）
0x251ace7c8  IPaI1oem5iL(*ctx)                               ; 若已有上下文，先销毁
0x251ace7d8  cp2g1b9ro(&ctx, &hwInfo)                        ; 建 FairPlay 上下文
loop:
0x251ace858  FigCreateBlockBufferCopyingMemoryBlock(alloc, out, outLen, &bb)  ; 把上一步输出包成 CMBlockBuffer
0x251ace868  jEHf8Xzsv8K(out)                                ; 立刻释放明文输出
0x251ace87c  CMBaseObjectGetVTable(stream)                   ; stream = storage[+0x8]
0x251ace890  x9 = [vtable+0x10][+0x38]                       ; 发送方法
0x251ace8d0  w1 = 0x3235 ; 0x251ace8d4 movk w1, #0x6670, lsl #16   ; 操作码 = 0x66703235 = "fp25"
0x251ace8dc  blraa x9                                        ; (stream, 0x66703235, bb, &respBB)
0x251ace8f8  CMBlockBufferGetDataPointer(respBB, 0, &len, 0, &ptr)
0x251ace918  w0 = 3                                          ; 类型常量固定 3
0x251ace91c  Mib5yocT(3, &hwInfo, ctx, ptr, len, &out, &outLen, &state)
0x251ace818  state==0 → 结束；state==1 → 回到 loop；其他 → 错误
```

### 可写进规范的确定事实

1. **承载消息是流消息（stream message），操作码 `0x66703235`**，ASCII 为 `"fp25"`。
   载荷是 `CMBlockBuffer`（长度由 FairPlay 核心给出），不是 HTTP body，也不是 plist。
2. **握手轮数由状态驱动，不固定为3次**：`Mib5yocT` 的第一个参数是常量 `3`（`0x251ace918`），
   状态字节 `state` 只有 `0`（完成）与 `1`（继续）两种合法值。
   > 注意：`3` 是**类型/角色参数**，不是「三次」。次数由 state 驱动；实测路径是每次循环发一帧、收一帧。
   > 是否恰好三轮属于**运行时行为**，固件只能证明「循环直到 state==0」——写规范时必须这样表述。
3. **失败处理**：`state ∉ {0,1}` → 错误码 `0xfffee786`，日志点 `0x251c2ed34`（行号 `0xc2`）；
   发送/收包失败 → `0xfffee785` 一类；同时 `IPaI1oem5iL(ctx)` 销毁上下文（`0x251ace988`）。
4. **硬件信息**：`APCUGetFairPlayHWInfoEx` 的结果既进上下文创建（`0x251ace7d8`），
   又每次循环作为参数传给 `Mib5yocT`（`0x251ace918` 的 x1 = `sp+0x30`）。
   调用点未证明该接口内部具体使用MFi协处理器还是其他来源；本项目未提供等价实现，保留OPEN-1。
5. **上下文生命周期**：一个 endpoint 一个 `ctx`（`storage[+0]`），重认证会先销毁（`0x251ace7c8`）。

### 明确不可写

- `Mib5yocT` 内部如何构造/解析消息、`_U4HBs` 的密钥封装算法、`APCUGetFairPlayHWInfoEx` 的取值来源。
  三者都在闭源模块内，`analysis/09` 给出反证（连 `FPLY` 字面量都不在这三个镜像里）。

## A-09 发送侧密钥封装：`_fpAuthentication_CreateEncryptedKey`（`0x251acea60`）

```
storage = CMBaseObjectGetDerivedStorage(self)
CFDataGetBytes(key16CF, {0,0x10}, stackbuf16)          ; 入参必须是 16 字节
U4HBs(ctx = *storage, stackbuf16, 0x10, &out, &outLen) ; 用 FairPlay 上下文加密
若 out == NULL → 0xfffee785
密文 = CFDataCreate(alloc, out, outLen)                ; 作为 ekey 交给上层
jEHf8Xzsv8K(out)                                       ; 释放中间 blob
把 stackbuf16 清零
```

可写事实：

- 输入**恰好 16 字节**（`CFDataGetBytes(..., {0,0x10}, ...)`，长度不匹配会走错误分支）。
- 输出长度**不固定**（由 `U4HBs` 给出 `outLen`，随后原样放进 `CFData`）；规范里不能写「ekey 固定 16 字节」。
- 这个函数**只加密、不写消息**：消息编排在上层（`/setup` 的流字典，见 A-24/A-25）。

## A-10 接收侧对偶：`/fp-setup` 处理（`0x2518a50b4`）

接收侧把同一个核心用同样的方式驱动，这给了我们**协议常量的第二份、独立证据**：

```
0x2518a5414  cmp w24, #8        → 相等：FP 类型 = 2   （0x2518a5434: mov w8, #2）
0x2518a541c  cmp w24, #0x20     → 相等：FP 类型 = 3   （0x2518a5428: mov w8, #3）
0x2518a5420  b.ne 0x2518a558c   → 其他值：错误 0xfffee704（日志 "### Bad ET: %d"）
0x2518a5438  str w8, [x21, #0x100]      ; 类型存进会话
0x2518a543c..545c  按+0x128状态及ctx是否非NULL决定清旧上下文/沿用/新建
0x2518a54e8  Mib5yocT(type, &hwInfo, ctx, inPtr, inLen, &outPtr, &outLen, &state)
0x2518a5518..5534  state==0置完成标志；state==1继续响应；0xFF错误；其他非零不走正常响应
0x2518a554c  createBinaryDataResponse("application/octet-stream", outPtr, outLen, respDict)
```

由此得到两个**可写进规范**的常量：

| 外部可见值（"ET"） | FairPlay 核心类型 | 证据 |
|---|---|---|
| 8 | 2 | `0x2518a5414` / `0x2518a5434` |
| 32 (0x20) | 3 | `0x2518a541c` / `0x2518a5428` |
| 其他 | 拒绝，`0xfffee704` | `0x2518a5420` → `0x2518a558c` |

并且：接收侧的响应是**二进制**（`application/octet-stream`），长度由核心给出——与发送侧的
「`CMBlockBuffer` 载荷」互为印证。也就是说 FP 消息在链路上是**不透明定长/变长字节块**，
不能仅由上层不解析推出载荷内部没有自描述头（详见`09-negative-space.md`）。

> 分歧点（必须标注）：发送侧固定用类型 `3`；接收侧按 ET 在 `2`/`3` 之间选。
> 只能说明已核发送函数固定传3，不能推广为全部iOS路径，也未证明type2仅为旧客户端。
> A-38补充：接收侧X-Apple-ET getter失败还有CSeq分支。目标profile选择与发送责任仍为OPEN-3。

## 复算

1. `source/asm/AirPlaySender/f_251ace728.s` 第 60–140 行：`0x251ace8d0` 起的 `mov/movk` 与 `blraa`。
2. `source/asm/AirPlayReceiver/f_2518a50b4.s`：`0x2518a5414`、`0x2518a541c`、`0x2518a5434`、`0x2518a5428`；上表限ET getter成功，失败分支见A-38。
3. 常量字符串：`python3 firmware/tools/read-cstr.py research/protocol/airplay_fairplay_crypto/source/firmware/AirPlayReceiver research/protocol/airplay_fairplay_crypto/source/metadata/receiver 0x251c2ed34` 一类可读出日志格式串。
