# reference/ — 速查与术语

## 1. 术语

| 术语 | 说明 |
|---|---|
| iAP2 | iPod Accessory Protocol 2，Apple 配件与设备之间的应用层协议；本 docset 只覆盖其链路层建立阶段 |
| link | 一条 iAP2 连接对象（0x268 字节） |
| runloop | 驱动 link 的事件泵（0x60 字节 + link 缓冲） |
| transport | 平台 I/O（RFCOMM / socket / USB），由平台提供 |
| SOF | 帧起始字节，iAP2 为 `FF 5A` |
| 传统帧 | 以 `FF 55` 开头的 iAP 控制帧（Detect / DetectNACK / RequestIdentify） |
| SYN / SYNACK | 链路参数协商帧 |
| IDPS | Identification 阶段（识别消息族） |
| MFi4 | 认证协议族；本 docset 只记录其符号与状态名 |
| EAK | 扩展确认（指出缺失序号） |
| 无重传模式 | SYN 的四个重传字段全 0（`R-3.8`） |

## 2. 常用地址（构建 24A446）

| 对象 | 地址 |
|---|---|
| 帧格式/校验 | `iAP2PacketCalcChecksum` `0x100008ae8`、`iAP2PacketCreate` `0x100006e24` |
| SYN | `iAP2PacketCreateSYNPacket` `0x100102fdc`、`iAP2PacketParseSYNData` `0x100103230` |
| 状态机 | `iAP2FSMHandleEvent` `0x10000639c`、状态表 `0x100219600` |
| 链路 | `iAP2LinkCreate` `0x100033fd0`、`iAP2LinkRunLoopCreate` `0x1000cae54` |
| 发送 | `__iAP2LinkSendPacketCommon` `0x100007914` |
| Detect | 常量 `0x1001b3378`、判定 `0x100102e20` |
| SYN 缺省 | 常量 `0x1001b3348`（`01 01 1e 00`） |
| 空操作动作 | `iAP2LinkActionNone` `0x100031c50` |

## 3. 符号参考

`reference/iAP2-symbols.tsv`：1,347 条 `iAP2*` / `acc_protocolParser*` / `mfi4Auth*` / `iap2_*` 符号（地址 + 名字），由 `source/metadata/symbols.json` 过滤生成。

**使用注意**：符号名来自固件的 `LC_SYMTAB`，是字节证据，但名字本身**不是**协议定义；语义必须由 `analysis/` 的汇编证据支持。

## 4. 帧速查

```
iAP2 帧
FF 5A | len_hi len_lo | ctrl | seq | lt | extra | hdr_cksum | payload | payload_cksum
 0  1 |   2     3     |  4   |  5  | 6  |  7    | 8 (1|2)  |   ...   |   1|2

传统帧
FF 55 | len | payload[len] (末字节 0xEE) | cksum8
```

控制位：`80` SYN、`40` ACK、`20` EAK、`10` RST、`08` SUS。

## 5. 状态编号

`0 Init / 1 Detached / 2 Detect / 3 Idle / 4 Pending / 5 Connected / 6 Suspend / 7 Failed`
