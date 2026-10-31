# runtime/ — 运行时素材与边界

## 1. 可用素材

| 素材 | 构建 | 与目标构建的关系 | 用途 |
|---|---|---|---|
| sysdiagnose（多份） | 22H374（iOS 18）、23G90（iOS 26）、21G93（iOS 17） | **均不是 24A446（iOS 27.0.1）** | 仅作形状/字节序佐证 |
| 本阶段抓包 | 无 | — | — |

**结论**：本阶段没有任何 24A446 的 iAP2 链路抓包，因此 `runtime/` **不能**把任何条款升级为 `CONFIRMED`；所有 `CONFIRMED` 都来自固件字节。

## 2. 已确认的运行时事实（跨构建，仅佐证）

| 事实 | 来源 | 与本 docset 的关系 |
|---|---|---|
| 蓝牙 RFCOMM 数据回调形状 `(**(code**)(*(dlci+0x28)+8))(dlci[8], ptr, len)` | 蓝牙阶段（`research/protocol/bluetooth_rfcomm/`） | 说明传输层回调是"函数指针表 + 上下文"的形式，与 `spec/01` 的 runloop/transport 分层相容 |
| `os_channel` 文件描述符（`kCBMsgArgSocket`） | 同上 | 可能是 iAP2 的底层 I/O 之一，但未在 `accessoryd` 中找到直接引用（`OPEN-TX-1`） |
| `bluetoothd` 中 `iap2` 字符串计数为 0 | 同上 | 佐证 iAP2 链路层由 `accessoryd` 拥有，而非 `bluetoothd` |

## 3. 未取得的东西（明确记录）

- 24A446 上的 iAP2 SYN/SYNACK 实际字节；
- 24A446 上的 Detect/DetectNACK/RequestIdentify 实际字节；
- 任何一条链路的 `link[0xbc]`（写入 `hdr[6]`）的实际取值；
- EAK 载荷样例（`OPEN-SEQ-1`）。

## 4. 如果后续拿到 24A446 抓包

建议的验证顺序（每条都能直接对照本 docset 的条款）：

1. 帧头：`FF 5A` + 大端长度 + 控制位（`R-2.1`–`R-2.3`）；
2. 校验：用 `spec/02` 的 `cksum16` 重算，应等于帧内校验字段（`R-2.6`）；
3. SYN 载荷：按 `R-3.4` 的偏移表逐字段解，与 `R-3.1` 的缺省值比对；
4. Detect 帧：应为 `FF 55 02 00 EE 10`（`R-2.11`）；
5. 序号：连续两帧的 `hdr[5]` 差应为 1（模 256，`R-4.1`）；
6. ACK 帧：`hdr[6]` 应在同一条链路上保持不变（`R-2.5`）。

任何一条对不上，都应在 `analysis/` 中新增一条冲突记录，而不是修改结论。
