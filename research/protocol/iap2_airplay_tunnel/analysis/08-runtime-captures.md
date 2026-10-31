# analysis/08 — 运行期样本：23G90 的 AirPlay 链路

## 8.1 样本身份

| 项 | 值 |
|---|---|
| 文件 | `runtime/accessoryd-packets-2026-10-16-221117.log.ips` |
| 大小 | 25,059 B |
| SHA256 | `7283f8a1d50c6c920198587f816c86aec996b7d749e84be7db771f5a7595dadd` |
| 构建 | **23G90**（非 24A446）|
| 连接 1 | `Bluetooth Classic`，UUID `E63B0109`，会话 2 |
| 连接 2 | **`AirPlay`**，UUID `D927805C-1FAC-47C6-B156-FF3818CEBC3D`，会话 3 |

样本与控制会话阶段是同一份文件（逐字节相同），本阶段只取第二个连接。

## 8.2 第二个连接的逐帧（去掉纯 ACK）

| # | 方向 | ctl | seq | ses | len | 内容 |
|---|---|---|---|---|---|---|
| 1 | Acc | `0xEE` | 0x10 | 00 | 6 | 链路握手 |
| 2 | Acc | `0x80` | 0x2a | 00 | 23 | SYN `01 01 10 00 03 e8 01 f4 0f 00 03 00 02` |
| 3 | iPod | `0xC0` | 0xeb | 00 | 23 | SYNACK `01 7f ff ff 03 e8 01 f4 0f 00 03 00 02` |
| 4 | iPod | `0x40` | 0xec | **03** | 16 | `0x1D00` |
| 5 | Acc | `0x40` | 0x2b | **03** | 323 | `0x1D01`（313 B，参数 0–9、0xC–0xD、0x11、0x14、0x16、0x18）|
| 6 | iPod | `0x40` | 0xed | 03 | 16 | `0x1D02` |
| 7 | iPod | `0x40` | 0xee | 03 | 20 | `0xAA00` + 空参数 `00 04 00 00` |
| 8 | Acc | `0x40` | 0x2c | 03 | 52 | `0xAA06`（32 B ASCII `4C36…DDCB`）|
| 9 | iPod | `0x40` | 0xef | 03 | 16 | `0xAA00`（无参数）|
| 10 | Acc | `0x40` | 0x2d | 03 | 627 | `0xAA01`（617 B PKCS#7）|
| 11 | iPod | `0x40` | 0xf0 | 03 | 52 | `0xAA02`（32 B 挑战）|
| 12 | Acc | `0x40` | 0x2e | 03 | 84 | `0xAA03`（64 B 签名）|
| 13 | iPod | `0x40` | 0xf1 | 03 | 16 | `0xAA05` |
| 14 | iPod | `0x40` | 0xf2 | 03 | 60 | **`0xFFFA`**（见 §8.3）|
| 15 | Acc | `0x40` | 0x2f | 03 | 57 | `0xFFFB` = `$PASCD,154.496,C,P,0,1,0.00,0.000*6E\0` |
| 16 | Acc | `0x40` | 0x30 | 03 | 87 | `0xFFFB` = `$GPGGA,…*64\0` |
| 17 | Acc | `0x40` | 0x31 | 03 | 96 | `0xFFFB` = `$GPRMC,…*50\0` |
| 18 | Acc | `0x40` | 0x32 | 03 | 57 | `0xFFFB`（`$PASCD…*62`）|
| 19 | Acc | `0x40` | 0x33 | 03 | 87 | `0xFFFB`（`$GPGGA…*65`）|
| 20 | Acc | `0x40` | 0x34 | 03 | 96 | `0xFFFB`（`$GPRMC…*51`）|
| 21 | iPod | `0x40` | 0xf3 | 03 | 16 | **`0xFFFC`** |
| 22 | Acc | — | 0x34 | 00 | 9 | 最终 ACK |

所有帧的 `payload(len,chk)` 与 `hdrChk` 都与抓包原值一致；表中省略了 12 个纯 ACK 帧（`len=9`、`len=0`）。

## 8.3 `0xFFFA` 的参数

```text
40 40 00 32 ff fa
  00 08 00 00 00 00 00 14        ; param 0  = u32 20
  00 04 00 01                    ; param 1  = 空
  00 08 80 01 00 00 00 fa        ; param 0x8001 = 250
  00 04 00 02                    ; param 2  = 空
  00 08 80 02 00 00 00 fa        ; param 0x8002 = 250
  00 04 00 04                    ; param 4  = 空
  00 08 80 04 00 00 00 14        ; param 0x8004 = 20
```

- 总长 0x32 = 50，参数区 44 = 8+4+8+4+8+4+8；
- `0x8000 | N` 与"空 param N"成对出现，形态上像"声明 param N，再给它的值"；
- 250/250/20 三个数值与 GPS 刷新间隔（毫秒）量级吻合，但**没有**一条指令或日志把 `0x8001` 绑定到"间隔"，所以只能记 `INFERRED`（`A05.3`）；
- 这条消息由**设备**发出，发送点：`0x1001798fc`（`mov w1,#0xfffa`），同函数族里 `0x100179b3c` 发 `0xFFFC`（`mov w1,#0xfffc`）。`0xFFFB` 的处理器是 `0x100179484`，挂在特性 12 的处理器表（`kiAP2MessageHandlerEntries_Location`，见 `research/protocol/iap2_control_session/analysis/14-message-table.md`）。

## 8.4 `0xFFFB` 的载荷形态

| 帧 | param 长度 | 值长度 | 内容 |
|---|---|---|---|
| 15/18 | 0x29=41 | 37 | `$PASCD,…*6E\0` |
| 16/19 | 0x47=71 | 67 | `$GPGGA,…*64\0` |
| 17/20 | 0x50=80 | 76 | `$GPRMC,…*50\0` |

值以 `$`（`0x24`）开头、以 `00` 结尾，是 NMEA-0183 句子的常见形态（含结尾 NUL）。本阶段不解释 NMEA 语义，只把它当作"**隧道/传输上的业务字节**"的样本。

## 8.5 这份样本证明/不证明什么

| 命题 | 结论 |
|---|---|
| AirPlay 传输上跑的是标准 iAP2 帧 | **证明**（帧头、长度、参数逐字节可解析）|
| 会话号由 SYN 协商得到（本例 3）| **证明**（SYN 尾部 `03 00 02` + 全部业务帧 `session=03`）|
| 识别/认证顺序与 BT 链路一致 | **证明**（1D00→1D01→1D02→AA00…）|
| AirPlay 链路上出现过 `0x55xx` 中继 | **未观测**（整段没有 `55 00/55 01`）|
| AirPlay 隧道有独立分片头 | **不能证明**（也未见任何非 iAP2 字节）|
| 24A446 行为相同 | **不能证明**（构建不同，`OPEN-TUN-12`）|
| 该链路的 MTU | **不能证明**（最大消息 617 B）|

## 8.6 复现

```bash
sha256sum research/protocol/iap2_airplay_tunnel/runtime/accessoryd-packets-2026-10-16-221117.log.ips
# 7283f8a1d50c6c920198587f816c86aec996b7d749e84be7db771f5a7595dadd
python3 research/protocol/iap2_airplay_tunnel/runtime/parse-capture.py   # 打印 §8.2 的表
```
