# 运行时观测：SDP 记录里的 iAP2 通道（跨构建）

素材：`D:\carvex-research\sysdiagnose` 三个构建的 `logs/Bluetooth/*.pklg`，共 4 个文件。
**三者都不是 24A446**，只能佐证"形态"，不能确认常量；固件侧依据仍以 `source/firmware/bluetoothd` 为准。

复现：

```
python3 research/protocol/bluetooth_rfcomm/tools/sdp-records-from-pklg.py sysdiagnose/*/logs/Bluetooth/*.pklg
```

工具修正了首轮解析的三处缺陷（`runtime/captures/2026-10-rfcomm-pklg-reanalysis.md` §1）：
ACL 同时接受 type=2/3、按 (handle, 方向) 分组重组、SDP 直接按 L2CAP 动态 CID 取（CID 1 是信令，不是 SDP）。

## 1. 背景：谁查谁

| 方向（抓包记法） | 含义 | 谁在查 |
|---|---|---|
| `TX` | iPhone → 空口 | iPhone 作为 SDP **客户端**发请求，或作为 SDP **服务端**回应车机的查询 |
| `RX` | 空口 → iPhone | 车机（Audi MMI，SDP 服务端实现为 OpenSynergy 栈）发出的请求或回应 |

三个构建里，车机与 iPhone **互为 SDP 服务端**：iPhone 查车机的 `…caff`（`00000000-deca-fade-deca-deafdecacaff`） 记录（据此发起出向 iAP2 连接），
车机也查 iPhone 的 `…cafe`（`00000000-deca-fade-deca-deafdecacafe`） 记录。

## 2. 车机侧（RX）暴露的 iAP2 记录

| 构建 | 记录句柄 | ServiceClassIDList | RFCOMM 通道 | ServiceName（0x0100） | 同响应内其它属性 |
|---|---|---|---|---|---|
| 22H374 | `0x0001000e` | `00000000-deca-fade-deca-deafdecacaff` | **4** | 未返回（请求只问了 1/2/4） | `0x0002` 记录状态 `0x0a13a30d8c` |
| 22H374 | `0x0001000d` | 同上 | **4** | 未返回 | `0x0002` 记录状态 `0x0a13a3c30e` |
| 23G90 | `0x00010007` | 同上 | **1** | `RFCOMM-SPP` | `0x0004` 协议描述符（L2CAP `0x0100` + RFCOMM） |
| 21G93 | `0x00010008` | 同上 | **5** | `iAP2` | `0x0005` 浏览组、`0x0006` 语言基属性 |

观察到的形态：

1. **同一个服务 UUID，通道号三次抓包分别是 4 / 1 / 5** —— 必须从 SDP 读，不能硬编码。
2. ServiceName 是**通用 SPP 风格**的字符串（`RFCOMM-SPP`、`iAP2`），不是 `Wireless iAP`；
   22H374 那次甚至没有返回名字。**靠名字识别 iAP2 不可靠，只能靠 UUID**。
3. 记录属性集最小只有 `{0x0000, 0x0001, 0x0004}`（句柄 / 类 / 协议描述符），没有 `0x0009` 配置描述符。

## 3. iPhone 侧（TX）暴露的 iAP2 记录

| 构建 | ServiceClassIDList | RFCOMM 通道 | ServiceName | 其它属性 |
|---|---|---|---|---|
| 22H374 | `00000000-deca-fade-deca-deafdecacafe` | 未在本次响应中返回 | — | `0x0009`：`0x1101`（SPP）v1.2 |
| 23G90 | `00000000-deca-fade-deca-deafdecacafe` | — | `Wireless iAP` | — |
| 21G93 | `0x1101`（SPP） | — | `Wireless iAP v2` | — |
| 21G93 | `00000000-deca-fade-deca-deafdecacafe` | **1** | `Wireless iAP` | `0x0008` 可用性 `0xff`、`0x0009` `0x1101` v1.2、`0x0005` 浏览组 |

结论：iPhone 用**两条记录**暴露 iAP2——一条是自家 UUID `…cafe`（名字 `Wireless iAP`），
另一条挂在标准 SPP UUID `0x1101` 下（名字 `Wireless iAP v2`）；实际通道在 21G93 的样本里是 **1**。

## 4. 打开后的第一个字节

同一批抓包里，**第一条 UIH 载荷都是 `FF 5A`（iAP2 SYN）**，且方向都是 `RX`（即**车机（配件侧）先发**）：

| 构建 | 首个 UIH 帧方向 | 载荷前 4 字节 |
|---|---|---|
| 22H374 | RX（配件→iPhone） | `FF 5A 00 17` |
| 23G90 | RX（配件→iPhone） | `FF 5A 00 17` |
| 21G93 | RX（配件→iPhone） | `FF 5A 00 1A` |

> 说明：这是"配件作为发起方"的样本，只能说明 SYN 由先开口的一方发出；
> 谁先开口由 iAP2 侧规则决定（见 `spec/09` §9.5 与 link 侧 SYN 条款），不属于 RFCOMM 层语义。

## 5. 对规范的影响

| 结论 | 落到哪 |
|---|---|
| 通道号必须每次从 SDP 读（4/1/5 三值） | `spec/09` R-9.4；与 `spec/03` R-3.16 一致 |
| 识别 iAP2 只能靠 UUID，不能靠名字 | `spec/09` R-9.3 |
| iPhone 侧记录 `…cafe` 与 SPP `0x1101` 都要尝试 | `spec/09` R-9.2 |
| 记录缺失时需要固定通道/配置 | `spec/09` R-9.5/R-9.6 |
| 首个字节由 iAP2 链路层决定，RFCOMM 不强制谁先说 | `spec/09` §9.5 |
