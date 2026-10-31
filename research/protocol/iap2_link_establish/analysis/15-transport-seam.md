# analysis/15 — 传输接缝（iAP2 侧）

对应本轮专项："蓝牙 → iAP2"接缝的 iAP2 半边。只回答"谁创建 link、传什么上限、谁消费数据"；RFCOMM/os_channel 细节引用蓝牙 docset，不复述。

## 15.1 谁创建 link、用什么参数（部分确认）

`A15.1`（已确认）**创建点在 `iap2_endpoint_create`（`0x100129350`）**，它把一个传输对象与 iAP2 端点绑定：

```
0x1001294a4: mov w0, #0x7f
0x1001294a8: mov w1, #0xffff
0x1001294ac: bl  #0x1000cae1c            ; 计算缓冲区大小(0x7f, 0xffff)
0x1001294c8: mov x0, x21                 ; &endpoint+0x30
0x1001294cc: mov x1, x19                 ; endpoint（传输对象）
0x1001294d0: mov w2, #1
0x1001294d4: mov w3, #0
0x1001294d8: mov w4, #0x7f
0x1001294dc: mov w5, #0xffff
0x1001294e0: bl  #0x1000cae38            ; iAP2LinkRunLoopCreateWithDefaults
```

`A15.2`（已确认）`0x1000cae38` 只是参数右移一格的包装（`x7←x6, x6←x5, …, x3←x0, w0←1`），随后尾调 `iAP2LinkRunLoopCreate`（`0x1000cae54`）；后者把 `x1` 存进 `runloop[0x10]`（传输对象）并调 `iAP2LinkCreate`（`0x100033fd0`），**`x6` 原样作为建链参数**。由 `A15.1` 得 `x6 = 0xFFFF`。

`A15.3`（已确认）**`link[0xc0]` = low16(x6) = `0xFFFF`**，寄存器链闭合：

```
0x100033ffc: mov x25, x6          ; iAP2LinkCreate 入口保存第 6 参数
0x1000340ac: strh w25, [x19, #0xc0]   ; 取低 16 位写入 link+0xc0
```

依据：`f_100033fd0.s` 第 0x100033ffc 行与 0x1000340ac 行（本文件为固件字节反汇编，可直接核对）。`OPEN-INIT-2` 因此**部分关闭**：`[0xc0]` 的取值已证，建链入口与参数已证；`iAP2LinkCreate` 首调语义的其余部分（返回码含义、是否允许二次创建、内部初始化覆盖面）仍未证。

## 15.2 上限与分片

`A15.4`（已确认）**iAP2 建链时的最大包参数是 `0xFFFF`，不是 N1（1007）也不是 os_channel 单块（2570）**。即 iAP2 层假定可以交出远大于传输单块上限的帧。

`A15.5`（已确认）`link[0xc0]`（`0xFFFF`）与 SYN 缺省 `max_packet`（`0xFFFF`）**数值一致，但不是同一来源**：前者是 `iap2_endpoint_create` 传给 `iAP2LinkCreate` 的**本地建链参数**，后者是链路协商字段（`A04.3`）。两者相等属默认配置，不是同源关系。

`A15.5a`（未证）**有效发送上限还受其他约束**：SYN 协商结果（`+0x16c` 一族字段）与接收方包长上限可能再收紧实际可用值；本轮未证明它们的联动关系 → `OPEN-FRAME-7`。

因此：**"iAP2 帧能否大于 N1" 的答案是能**；切割发生在传输层（RFCOMM/os_channel 的块），iAP2 链路层不做分片。接收侧依赖逐字节解析器跨块重组（`iAP2MsgParserConsumeByte` 流式消费，`A09.4`）。

## 15.3 数据流方向

`A15.6`（已确认）`iAP2LinkDataReadyCB`（`0x10019bfac`）在 `0x10003271c` 被调用，位于 `iAP2LinkActionHandleData`（`0x100032670`，已导出：`source/asm/accessoryd/f_100032670.s` + `readable/ghidra/accessoryd/f_100032670.ghidra.c`）内——即**已解析出数据之后**交给会话/应用，属消费侧，不是喂字节的入口。

`A15.6a`（冲突记录，已解决）`analysis/01` 的旧结论 `A01.8` 曾写"`iAP2LinkDataReadyCB` 的调用者是传输适配层"，与本条冲突。冲突原因：旧结论基于"数据就绪 = 传输喂数据"的命名直觉，未导出调用者。现按字节证据改成：调用者是 `iAP2LinkActionHandleData`（消费侧），传输适配层的作用点是 `acc_protocolParser_iAP2_run` / `iAP2PacketParseBuffer`（`A01.8` 已同步修改）。

`A15.7`（未确认）**喂字节的入口仍未定位**：在 `accessoryd` 中检索 `os_channel` / `kCBMsgArgSocket` / `dlci` / `RFCOMM` / `BluetoothManager` 均 0 命中；`AccessoryiAP2Shim`（234,336 B）同样 0 命中。`iAP2LinkRunLoopCreate` 在 `accessoryd` 内无直接 `bl` 调用者（唯一入口是 `A15.2` 的包装）——**调用方未定位，不排除外部注入**（也可能是间接调用/函数指针），此处不作结论 → `OPEN-TX-1` 保留。

## 15.4 未决项变化

| ID | 变化 |
|---|---|
| `OPEN-TX-1` | 仍开，问题改为**谁调用 `acc_protocolParser_iAP2_run` / `iAP2PacketParseBuffer`**；已排除 `accessoryd` 与 `AccessoryiAP2Shim` 内的 fd/os_channel 读取代码 |
| `OPEN-INIT-2` | **部分关闭**：建链入口 `iap2_endpoint_create`、参数 `0xFFFF`、`link[0xc0]` 写入（`0x100033ffc`→`0x1000340ac`）均已逐条核对；首调语义其余部分（返回码、可否二次创建、初始化覆盖面）未证 |
| `OPEN-FRAME-7` | 新增：`link[0xc0]` 与 SYN `+0x16c` 一族、接收包长上限的联动关系未证 |
| `OPEN-FRAME-4` | 后续复核已找到块复制：CheckNegotiation 保存对端包长到工作块，NotifyConnection 提交至 +0x1a6；见 A04.13。上限联动仍属 OPEN-FRAME-7 |
