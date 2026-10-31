# analysis/13 — 函数清单与取证状态

对应任务书第 5 节第 13 项（函数级清单）。本文件给出**分类统计**与**被引用函数表**；全部 94 个导出函数的逐条记录（地址、大小、SHA256、汇编文件、被哪份文档引用）在 `function-index.json`。

## 13.1 导出规模

| 项 | 数量 | 说明 |
|---|---|---|
| `LC_FUNCTION_STARTS` 函数起点 | 8,706 | 全二进制 |
| 本阶段导出汇编的函数 | 126 | `source/asm/accessoryd/` |
| 其中在 `analysis/`、`spec/` 中被地址引用 | 见 13.3 | 由 `function-index.json` 的 `cited_by` 统计 |
| 只导出未引用（`SAMPLED_NOT_CITED`） | 其余 | 仍保留汇编与反编译，供后续阶段复核 |

采样率：**143 / 8,706 ≈ 1.64%**。这是"按链路建立阶段选点"的定向采样，不代表全二进制覆盖；任何"未在本阶段出现"的行为都按 `OPEN` 处理。

## 13.2 分类统计

按符号前缀统计（客观口径，脚本可复算）：

| 前缀 | 数量 | 覆盖内容 |
|---|---|---|
| `iAP2Link*` | 63 | 链路对象、生命周期、动作、序号/确认 |
| `iAP2Packet*` | 24 | 帧构造、解析、校验、SYN 编码 |
| `iap2_*` | 12 | 识别/认证/会话消息处理函数 |
| `__parseIdentification*` / `cbIdentification*` | 5 | 识别参数分派与 transport component 解析 |
| `acc_auth_protocol_*` | 3 | 挑战生成/挑战响应验证/证书链校验 |
| `mfi4Auth_*` | 13 | 认证隧道封装/解包/解析、协议会话与消息处理 |
| `acc_protocolParser_*` | 4 | 解析器胶水（create/reset/destroy/run） |
| `iAP2FSM*` | 3 | 状态机创建/执行/大小 |
| 其它 | 1 | `iAP2TimeGetCurTimeMs`（时间基准） |
| **合计** | **143** | |

## 13.3 被引用的核心函数

下表只列 `analysis/` 中**逐条给出汇编证据**的函数；`status` 含义：

- `CONFIRMED_BY_ANALYSIS`：文件内有至少一条 `A` 结论直接引用其指令；
- `READ_PARTIAL`：读过入口与部分分支，但未覆盖全部路径；
- `ENTRY_ONLY`：只确认入口与签名，未读实现。

| 函数 | 地址 | status | 引用处 |
|---|---|---|---|
| `iAP2PacketCalcChecksum` | `0x100008ae8` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.5/A03.6 |
| `iAP2PacketSetHdrChecksum` | `0x1000071f4` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.3 |
| `iAP2PacketGetHdrChecksum` | `0x100008e80` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.3 |
| `iAP2PacketCreate` | `0x100006e24` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.1 |
| `iAP2PacketGenerateBuffer` | `0x1000088b8` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.4 |
| `iAP2PacketParseBuffer` | `0x10000a5d0` | READ_PARTIAL | `analysis/03` A03.12/A03.13、`analysis/07` A07.5 |
| `iAP2PacketGetPayloadLen` | `0x100006120` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.2 |
| `iAP2LinkCurPckHdrSize` | `0x100005f4c` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.1 |
| `iAP2LinkCurPckChksumSize` | `0x100005f38` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.1 |
| `iAP2LinkGetMaxPayloadSize` | `0x1000070fc` | CONFIRMED_BY_ANALYSIS | `analysis/03` A03.10 |
| `iAP2PacketCheckDetect` | `0x100102e20` | CONFIRMED_BY_ANALYSIS | `analysis/07` A07.1 |
| `iAP2PacketCheckDetectNACK` | `0x100102ea0` | CONFIRMED_BY_ANALYSIS | `analysis/07` A07.2 |
| `iAP2PacketCheckRequestIdentify` | `0x100102f58` | CONFIRMED_BY_ANALYSIS | `analysis/07` A07.3 |
| `iAP2LinkSetDefaultSYNParam` | `0x1000328b0` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.2 |
| `iAP2PacketCreateSYNPacket` | `0x100102fdc` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.4 |
| `iAP2PacketParseSYNData` | `0x100103230` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.3/A04.5/A04.6 |
| `iAP2LinkIsValidSynParam` | `0x1000328dc` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.7/A04.9 |
| `iAP2LinkIsNoRetransmit` | `0x100008590` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.8 |
| `iAP2LinkCheckNegotiation` | `0x100035154` | CONFIRMED_BY_ANALYSIS | `analysis/04` A04.11 |
| `iAP2FSMHandleEvent` | `0x10000639c` | CONFIRMED_BY_ANALYSIS | `analysis/06` A06.1/A06.6/A06.7 |
| `iAP2FSMGetBuffSize` | `0x10006baa4` | CONFIRMED_BY_ANALYSIS | `analysis/06` A06.2 |
| `iAP2FSMCreate` | `0x10006baac` | ENTRY_ONLY | `analysis/06` A06.3 |
| `iAP2LinkCreate` | `0x100033fd0` | CONFIRMED_BY_ANALYSIS | `analysis/02` A02.2、`analysis/04` A04.1 |
| `iAP2LinkGetBuffSize` | `0x100033ed8` | ENTRY_ONLY | `analysis/02` A02.1 |
| `iAP2LinkRunLoopCreate` | `0x1000cae54` | CONFIRMED_BY_ANALYSIS | `analysis/02` A02.1 |
| `iAP2LinkRunLoopRunOnce` | `0x100008698` | CONFIRMED_BY_ANALYSIS | `analysis/02` A02.3 |
| `iAP2LinkRunLoopGetResetEventMask` | `0x10000638c` | ENTRY_ONLY | `analysis/02` A02.3 |
| `iAP2LinkAttached` | `0x100034a7c` | CONFIRMED_BY_ANALYSIS | `analysis/02` A02.4 |
| `iAP2LinkDetached` | `0x100034bbc` | CONFIRMED_BY_ANALYSIS | `analysis/11` A11.1 |
| `iAP2LinkStart` | `0x100034a70` | CONFIRMED_BY_ANALYSIS | `analysis/02` A02.5 |
| `iAP2LinkSetUseiAP2LinkRunLoop` | `0x100035144` | CONFIRMED_BY_ANALYSIS | `analysis/02` 表 |
| `__iAP2LinkSendPacketCommon` | `0x100007914` | READ_PARTIAL | `analysis/01` A01.3/A01.4 |
| `iAP2LinkSendPacket` | `0x100031ef0` | CONFIRMED_BY_ANALYSIS | `analysis/01` A01.3 |
| `iAP2LinkSendPacketCB` | `0x100008a44` | ENTRY_ONLY | `analysis/01` A01.5 |
| `iAP2LinkSendPacketWaitCB` | `0x10019c120` | CONFIRMED_BY_ANALYSIS | `analysis/01` A01.5 |
| `iAP2LinkSendDetectCB` | `0x10019c124` | ENTRY_ONLY | `analysis/07` A07.8 |
| `iAP2LinkDataReadyCB` | `0x10019bfac` | READ_PARTIAL | `analysis/01` A01.2、`analysis/10` A10.1 |
| `iAP2LinkConnectedCB` | `0x100103970` | CONFIRMED_BY_ANALYSIS | `analysis/01` A01.1 |
| `iAP2LinkGetSessionInfo` | `0x100032828` | ENTRY_ONLY | `analysis/10` A10.1 |
| `iAP2LinkGetNewSeqNum` | `0x100034424` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.2 |
| `iAP2PacketCalcSeqGap` | `0x1000084b8` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.1 |
| `__iAP2LinkComparePacketSeq` | `0x1000353f8` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.3 |
| `iAP2PacketIsSeqACKd` | `0x10000b5c0` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.4 |
| `iAP2LinkResetSeqAck` | `0x1000346c8` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.6、`analysis/11` A11.4 |
| `iAP2LinkResetSend` | `0x100034464` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.5、`analysis/11` A11.4 |
| `iAP2LinkActionHandleACK` | `0x10000bc04` | CONFIRMED_BY_ANALYSIS | `analysis/05` A05.7 |
| `iAP2LinkActionDetach` | `0x100031c7c` | ENTRY_ONLY | `analysis/06` 表、`analysis/11` 表 |
| `iAP2LinkDeviceActionSendDetect` | `0x10002fac8` | CONFIRMED_BY_ANALYSIS | `analysis/07` A07.7/A07.8 |
| `iAP2LinkDeviceActionSendResetSYNACK` | `0x10002f920` | READ_PARTIAL | `analysis/07` A07.9 |
| `iAP2LinkDeviceActionSendRST` | `0x10002fb54` | READ_PARTIAL | `analysis/07` A07.10、`analysis/11` A11.8 |
| `iAP2LinkDeviceActionHandleMaxRetries` | `0x100030054` | ENTRY_ONLY | `analysis/11` A11.6 |
| `iAP2LinkActionResendData` | `0x1000323f8` | ENTRY_ONLY | `analysis/05` A05.9 |
| `iAP2LinkActionResendMissing` | `0x100031ef8` | ENTRY_ONLY | `analysis/05` A05.9 |
| `iAP2PacketGetMissingSeqFromEAK` | `0x1001033bc` | ENTRY_ONLY | `analysis/05` A05.8 |
| `iAP2TimeGetCurTimeMs` | `0x1000024e4` | ENTRY_ONLY | `analysis/05` A05.2、`analysis/01` A01.4 |
| `iAP2TimeCallbackAfter` | `0x100007ce8` | ENTRY_ONLY | `analysis/01` A01.4 |
| `iAP2TimeCancelTimer` | `0x1000066e0` | ENTRY_ONLY | `analysis/01` A01.3 |
| `iAP2LinkDelete` | `0x1000347b0` | ENTRY_ONLY | `analysis/11` A11.7 |
| `iAP2LinkHandleSuspend` | `0x100034db4` | ENTRY_ONLY | `analysis/11` A11.7 |
| `iAP2LinkHandleResume` | `0x100034e68` | ENTRY_ONLY | `analysis/11` A11.7 |
| `acc_protocolParser_iAP2_create` | `0x10017b5fc` | CONFIRMED_BY_ANALYSIS | `analysis/01` A01.7 表 |
| `acc_protocolParser_iAP2_run` | `0x1000cf5b8` | READ_PARTIAL | `analysis/01` A01.6 |
| `iap2_identification_identificationInfoHandler` | `0x10013bcc8` | READ_PARTIAL | `analysis/08` A08.2 |
| `iap2_identification_identificationInfoUpdateHandler` | `0x100050934` | ENTRY_ONLY | `analysis/08` A08.3 |
| `iap2_identification_cancelIdentificationHandler` | `0x10013b28c` | ENTRY_ONLY | `analysis/08` A08.3 |
| `__parseIdentificationParams` | `0x1000512e8` | CONFIRMED_BY_ANALYSIS | `analysis/08` A08.4/A08.7/A08.8 |
| `iap2_identification_parseTransportComponent` | `0x1000500a8` | READ_PARTIAL | `analysis/08` A08.5 |
| `cbIdentificationInfoSerialTransportComponentParams` | `0x10004f254` | CONFIRMED_BY_ANALYSIS | `analysis/08` A08.6 |
| `mfi4Auth_util_packIntoTunnelDataiAP2Msg` | `0x100022264` | CONFIRMED_BY_ANALYSIS | `analysis/09` A09.3 |
| `mfi4Auth_util_parseMessage` | `0x1000221a8` | CONFIRMED_BY_ANALYSIS | `analysis/09` A09.4 |
| `mfi4Auth_util_unpackFromTunnelDataiAP2Msg` | `0x100022398` | READ_PARTIAL | `analysis/09` A09.4 |
| `mfi4Auth_protocol_parse` | `0x1000d3094` | ENTRY_ONLY | `analysis/09` `OPEN-AUTH-4` |
| `iap2_deviceAuthentication_RequestDeviceCertificate` | `0x100123108` | CONFIRMED_BY_ANALYSIS | `analysis/09` A09.7 |
| `iap2_deviceAuthentication_RequestDeviceChallengeResponse` | `0x100123204` | READ_PARTIAL | `analysis/09` A09.5 |
| `iap2_deviceAuthentication_DeviceAuthenticationFailed` | `0x10012356c` | CONFIRMED_BY_ANALYSIS | `analysis/09` A09.6 |
| `iap2_deviceAuthentication_DeviceAuthenticationSucceeded` | `0x100123690` | CONFIRMED_BY_ANALYSIS | `analysis/09` A09.6 |
| `iap2_accAuthentication_certificate` | `0x1001850bc` | READ_PARTIAL | `analysis/09` A09.5 |
| `iap2_accAuthentication_challengeResponse` | `0x100185d6c` | READ_PARTIAL | `analysis/09` A09.5 |
| `iap2_accAuthentication_certSerial` | `0x1001860d4` | READ_PARTIAL | `analysis/09` A09.5 |
| `__parseIdentificationParamsPower` | `0x1000c07a8` | SAMPLED_NOT_CITED | 待后续阶段 |
| `__parseIdentificationSupportedEAProtocol` | `0x10009fba8` | SAMPLED_NOT_CITED | 待后续阶段 |
| `__parseIdentificationPreferredBundleSeedID` | `0x1000a02d0` | SAMPLED_NOT_CITED | 待后续阶段 |

## 13.4 未在本文档中引用的导出函数

`source/metadata/selection.json` 中 `SAMPLED_NOT_CITED` 的函数（25 个）仍保留：

- `.s`：原始汇编；
- `.bin`：原始字节；
- `.ghidra.c`：Ghidra 反编译（`DECOMPILED_UNREVIEWED`）。

它们的作用是让后续阶段（会话、消息层、USB、认证细节）可以直接接着读，而不必重新定位入口。

## 13.5 取证状态的含义

| 状态 | 定义 |
|---|---|
| `CONFIRMED_BY_ANALYSIS` | 文档中以 `A` 结论引用其指令，且结论为"已确认" |
| `READ_PARTIAL` | 读了入口与部分分支，结论中标 `OPEN` 的部分未覆盖 |
| `ENTRY_ONLY` | 只用作地图（地址/签名），未读实现 |
| `SAMPLED_NOT_CITED` | 已导出但本阶段未引用 |
