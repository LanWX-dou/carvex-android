# 09 抽样函数清单与证据角色

本文件登记**本套文档抽取的全部 96 个函数**，说明每个函数在证据链中的角色，并明确"已引用为条款依据"与"仅作旁证/未展开"的边界。

## 1. 为什么需要这份清单

`bluetoothd` 共 **37,368** 个函数起点（来自 `LC_FUNCTION_STARTS`），本次抽取 **96** 个（0.22%）。若不逐条登记，读者无法判断"某条结论是否建立在未公开的函数上"。因此：

- 每个函数都必须出现在下表中；
- `引用` 列指向 `analysis/NN` 或 `spec NN`，可回溯；
- 未被任何文件引用的函数，明确标为"仅旁证"，其内部逻辑**不构成**任何条款的依据。

## 2. 状态统计

| 状态 | 数量 | 含义 |
|---|---|---|
| `CONFIRMED_BY_ANALYSIS` | 56 | 已在 `analysis/` 中引用，且结论经过汇编复核 |
| `SAMPLED_NOT_CITED` | 40 | 仅生成反编译与汇编，未被任何条款引用 |
| 合计 | 96 | — |

机器可读版本见 `function-index.json`（含每个文件的 SHA256 与 `cited_in` 数组）。

## 3. 清单

| 地址 | 大小 | 分组 | 抽样理由 | 本文档角色 | 引用 |
|---|---|---|---|---|---|
| `0x100035440` | 240 | rfcomm-timers | 时间源：mach_absolute_time × timebase → {u32 微秒, u16 纳秒余数} | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1000609fc` | 116 | rfcomm-timers | 定时器取消 API（重装前先取消旧定时器） | 定时器路径旁证 | — |
| `0x100060ff4` | 252 | rfcomm-timers | 定时器线程：值按毫秒拆成 timespec（/1000 与 %1000×1e6）后 pthread_cond_timedwait | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x10006135c` | 640 | rfcomm-timers | 定时器登记：拒绝 bit15 置位的超时值；表项步长 24，回调存在 +8 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1000615dc` | 180 | rfcomm-timers | 计算到期时刻 now+timeout（16 位）并以 timeout*100 调用平台钩子 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x100061690` | 88 | rfcomm-timers | 平台钩子本体：把 timeout*100 存入 0x100c25cc8 并唤醒定时器线程 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1000b5e68` | 2872 | discovery | LE advertising report event decoding | 广播/发现路径旁证 | — |
| `0x1000c7818` | 7960 | discovery | advertising data dump/formatting | 广播/发现路径旁证 | — |
| `0x1000eb4e8` | 2504 | rfcomm-core | 'MAX buffer size for the RFCOMM Channel' write buffer acco… | RFCOMM 核心旁证 | ana 05, ana 07, spe 05 |
| `0x100137ee8` | 1940 | discovery | page scan / discoverability control (ScanCorePageScan, 'Di… | 广播/发现路径旁证 | ana 01, spe 01 |
| `0x100139490` | 1808 | device-identification | EIR vs SDP freshness decision ('EIR matched ... requesting… | 设备识别旁证 | — |
| `0x100139d70` | 288 | rfcomm-reconnect | 页扫描定时器重设（秒），重连时用 60 s | 重连节奏依据 | analysis/06-rfcomm-disconnect-and-cleanup.md、spec/06-lifecycle-and-boundary.md |
| `0x1001479fc` | 3540 | discovery | scan-core page scan device set bookkeeping | 广播/发现路径旁证 | ana 01 |
| `0x1001a31f4` | 1388 | pairing | classic SMP/BR-EDR pairing request gating | 配对路径旁证（analysis/07 C6） | — |
| `0x100233530` | 848 | pairing | accept/reject/cancel pairing agent commands | 配对路径旁证（analysis/07 C6） | ana 07 |
| `0x100296014` | 312 | rfcomm-client | 'RFCOMM connection failed' connect-result path | 出向连接旁证（spec 03.5） | — |
| `0x100296714` | 616 | connection-state | 'RFCOMM_Disconnect failed - forcing disconnect!' teardown | XPC 命令入口旁证（analysis/07 C2） | ana 06, ana 07 |
| `0x10029ead0` | 148 | connection-state | 'GetContextByRfcommHandle - context not found' | XPC 命令入口旁证（analysis/07 C2） | — |
| `0x1002f1300` | 736 | rfcomm-core | stack RFCOMM registration ('RFCOMM registration failed!') | RFCOMM 核心旁证 | ana 02, spe 02 |
| `0x1002f1798` | 432 | iap2-boundary | OI_RFCOMM_Accept failure path used by profile servers | 边界分层旁证（analysis/07） | — |
| `0x1003010ac` | 412 | iap2-boundary | OBEX server as a second RFCOMM consumer (accept/data/write… | 边界分层旁证（analysis/07） | — |
| `0x100312584` | 1132 | rfcomm-timers | 定时器 init 包装：以第 2 参数接收平台钩子并下传给 0x1003d7f28 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1003c136c` | 152 | rfcomm-core-closure | DLCI lookup in session | RFCOMM 辅助/闭包 | ana 04 |
| `0x1003c1404` | 216 | rfcomm-core-closure | DLCI allocation for incoming link | RFCOMM 辅助/闭包 | ana 02, ana 04, spe 02, spe 04 |
| `0x1003c14dc` | 276 | rfcomm-core-closure | connect: allocate DLCI for outgoing | RFCOMM 辅助/闭包 | ana 04, spe 04 |
| `0x1003c16dc` | 172 | rfcomm-core-closure | link/session error response (sends DM) | RFCOMM 辅助/闭包 | ana 04, ana 06, spe 06 |
| `0x1003c18a4` | 192 | rfcomm-core | 'OI_Rfcomm_GetSessionByCID' | RFCOMM 核心旁证 | — |
| `0x1003c1964` | 208 | rfcomm-core-closure | connect: existing session lookup | RFCOMM 辅助/闭包 | ana 06 |
| `0x1003c1d40` | 364 | rfcomm-core-closure | connect: set max frame size | RFCOMM 辅助/闭包 | ana 04 |
| `0x1003c1eac` | 96 | rfcomm-core-closure | connect: reuse session branch | RFCOMM 辅助/闭包 | ana 06 |
| `0x1003c1f78` | 320 | rfcomm-core-closure | connect: session allocation | RFCOMM 辅助/闭包 | ana 06 |
| `0x1003c20b8` | 244 | rfcomm-core-closure | connect: start SABM | RFCOMM 辅助/闭包 | ana 04, ana 06 |
| `0x1003c2314` | 128 | rfcomm-core-closure | registered-server lookup/notify for incoming DLCI | RFCOMM 辅助/闭包 | ana 00, ana 02, ana 04, spe 02 |
| `0x1003c2394` | 160 | rfcomm-core-closure | accept: link handle -> link record | RFCOMM 辅助/闭包 | ana 06 |
| `0x1003c2624` | 364 | rfcomm-core-closure | connect prologue check | RFCOMM 辅助/闭包 | — |
| `0x1003c2b00` | 620 | rfcomm-core | 'OI_RFCOMM_Connect failed' outgoing connect | RFCOMM 核心旁证 | ana 03, ana 04, ana 06, ana 07, spe 04, spe 06 |
| `0x1003c2d6c` | 132 | rfcomm-core-closure | connect: no-session branch | RFCOMM 辅助/闭包 | ana 06 |
| `0x1003c2df0` | 388 | rfcomm-core | 'OI_RFCOMM_Accept - linkhandle %d not found' incoming accept | RFCOMM 核心旁证 | ana 04 |
| `0x1003c33a8` | 716 | rfcomm-core | 'OI_RFCOMM_createChannelForFastConnect' | RFCOMM 核心旁证 | — |
| `0x1003c3c20` | 908 | rfcomm-core | 'RFCOMM Write failed' / orphaned MBUF on session loss | RFCOMM 核心旁证 | ana 04, ana 05, spe 05 |
| `0x1003c4c88` | 260 | rfcomm-mux-commands | 信用更新后触发发送（PN 设置初始信用后调用） | 复用器命令路径旁证 | — |
| `0x1003c518c` | 188 | rfcomm-timers | RFCOMM 会话定时器启动/重装：登记回调 0x1003c5248 + 超时值 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1003c5334` | 452 | rfcomm-core-closure | frame sender used for UA/DM responses (0x63=UA,0x0f=DM) | RFCOMM 辅助/闭包 | ana 00, ana 04, ana 06, spe 04, spe 06 |
| `0x1003c54f8` | 380 | rfcomm-tx-closure | send frame on session (used by frame builder) | 组帧/发送辅助（04.1、05.5） | ana 04 |
| `0x1003c5884` | 284 | rfcomm-mux-commands | 复用器命令发送助手 (mux, direction, body, len) -> 组帧并发送 | 复用器命令路径旁证 | — |
| `0x1003c59a0` | 720 | rfcomm-core | 'OI_Rfcomm_ReceiveFrame invalid frame length' receive entry | RFCOMM 核心旁证 | ana 00, ana 04, ana 05, ana 06, ana 07, ana 08, spe 04, spe 05, spe 06 |
| `0x1003c5c70` | 528 | rfcomm-core | 'No registered server on DLCI %d, rejecting incoming link' | RFCOMM 核心旁证 | ana 04, ana 07, spe 04 |
| `0x1003c6180` | 632 | rfcomm-core | 'DLCI %d not found' + 'RFCOMM send command failed' | RFCOMM 核心旁证 | — |
| `0x1003c6b60` | 68 | rfcomm-tx-closure | append mux command / FCS (used by frame builder) | 组帧/发送辅助（04.1、05.5） | ana 04, spe 04 |
| `0x1003c6be4` | 52 | rfcomm-tx-closure | FCS verification helper used by RX | 组帧/发送辅助（04.1、05.5） | ana 05 |
| `0x1003c6c18` | 116 | rfcomm-tx-closure | post-send flush / tx kick | 组帧/发送辅助（04.1、05.5） | ana 06 |
| `0x1003c6db8` | 60 | rfcomm-mux-commands | DLCI 状态变化通知（TEST/FCON 路径使用） | 复用器命令路径旁证 | — |
| `0x1003c6f94` | 364 | rfcomm-core | 'OI_RfcommMux_TEST invalid size' | RFCOMM 核心旁证 | — |
| `0x1003c71e8` | 160 | rfcomm-mux-commands | MSC 命令发送器：构造 0xE1/0xE3 + 长度 0x05/0x07 + 地址字节 + 信号字节 | MSC 组帧依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1003c73f0` | 4212 | rfcomm-core | mux command dispatch (PN/RPN/TEST, 'force disconnect the l… | RFCOMM 核心旁证 | ana 00, ana 04, ana 05, ana 06, ana 08, spe 04, spe 06 |
| `0x1003c8464` | 492 | rfcomm-core | 'Could not find link for DLCI (%d)' mux->link resolution | RFCOMM 核心旁证 | ana 04 |
| `0x1003c9720` | 736 | sdp-client | 'OI_STATUS OI_SDP_SearchReq(...)' client PDU builder | SDP 客户端驱动旁证（spec 03） | ana 03, spe 03 |
| `0x1003c9ab8` | 612 | sdp-client | 'OI_STATUS OI_SDP_AttributeReq(...)' client PDU builder | SDP 客户端驱动旁证（spec 03） | ana 03, spe 03 |
| `0x1003c9dd8` | 720 | sdp-client | 'OI_STATUS OI_SDP_SearchAttributeReq(...)' client PDU buil… | SDP 客户端驱动旁证（spec 03） | ana 03, spe 03 |
| `0x1003ca1d8` | 536 | sdp-server | 'OI_STATUS ServiceRecordResponse(...)' response encoder | SDP 服务端旁证（spec 02） | ana 02, spe 02, spe 03 |
| `0x1003cbd74` | 828 | service-registration | remote SDP record table add/update | 服务选择/记录更新旁证（spec 02） | — |
| `0x1003cd684` | 580 | sdp-server | stalled incoming SDP request handling | SDP 服务端旁证（spec 02） | — |
| `0x1003ce304` | 1728 | sdp-server | 'OI_STATUS ServiceSearchRequest(...)' server request handler | SDP 服务端旁证（spec 02） | ana 02, spe 02 |
| `0x1003ce9c4` | 672 | sdp-server | 'OI_STATUS ServiceAttributeRequest(...)' server request ha… | SDP 服务端旁证（spec 02） | ana 02, spe 02 |
| `0x1003cec64` | 820 | sdp-server | 'OI_STATUS ServiceSearchAttributeRequest(...)' server requ… | SDP 服务端旁证（spec 02） | ana 02, spe 02 |
| `0x1003d56fc` | 764 | service-registration | service name table Carplay/WiapGateWay/WiapSink used when … | 服务选择/记录更新旁证（spec 02） | ana 01, spe 01 |
| `0x1003d7a1c` | 68 | rfcomm-timers | 按 key(0x32=50) 取配置块；+0xa 的 16 位字段是 RFCOMM 超时参数 | 定时器路径旁证 | — |
| `0x1003d7f28` | 352 | rfcomm-timers | 定时器模块 init：按配置项分配 24 字节槽表，把平台钩子写入 0x100c39fb8 | 超时/时间基依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1003d8668` | 268 | rfcomm-tx-closure | write frame buffer and send (used by frame builder) | 组帧/发送辅助（04.1、05.5） | ana 04 |
| `0x1003d8e5c` | 424 | rfcomm-core-closure | accept: async completion helper | RFCOMM 辅助/闭包 | — |
| `0x100407e38` | 412 | connection-state | 'handleOpenRFCOMMChannel' XPC open path | XPC 命令入口旁证（analysis/07 C2） | — |
| `0x100407fd4` | 284 | connection-state | 'handleCloseRFCOMMChannel' XPC close path | XPC 命令入口旁证（analysis/07 C2） | — |
| `0x1004080f0` | 468 | connection-state | 'handleRFCOMMPortConfiguration' line settings | XPC 命令入口旁证（analysis/07 C2） | — |
| `0x10040b568` | 2616 | service-registration | 'uint32_t XpcClassicConnection::addServiceDataToLocalSDP' … | 服务选择/记录更新旁证（spec 02） | ana 02, spe 02 |
| `0x10040c934` | 700 | connection-state | channel connected callback ('incoming?: %d, sock: %x') | XPC 命令入口旁证（analysis/07 C2） | ana 03, ana 05, ana 07, ana 08, spe 05, spe 06 |
| `0x10040cbf8` | 392 | connection-state | channel disconnected callback | XPC 命令入口旁证（analysis/07 C2） | — |
| `0x1004f20fc` | 1232 | service-registration | ServiceWiAP/ServiceWiAPSink/ServiceWirelessCarPlay selection | 服务选择/记录更新旁证（spec 02） | — |
| `0x1004f2730` | 1040 | service-registration | ServiceWiAP/ServiceWiAPSink/ServiceWirelessCarPlay selecti… | 服务选择/记录更新旁证（spec 02） | — |
| `0x1005e3ae0` | 11844 | device-identification | CarPlayType / CarPlayEnabled device settings | 设备识别旁证 | — |
| `0x1005e6ce0` | 3372 | rfcomm-client | 'RFCOMM ServiceClass:' + RFCOMM CID mapping | 出向连接旁证（spec 03.5） | ana 03 |
| `0x1005faeec` | 732 | device-identification | Apple EIR 3rd-party/ProxPairing rejection | 设备识别旁证 | — |
| `0x1005fb1c8` | 1652 | device-identification | 'bool BT::Device::setEIRData' - EIR parsing into device re… | 设备识别旁证 | — |
| `0x1005fbae8` | 676 | device-identification | EIR manufacturer data extraction | 设备识别旁证 | — |
| `0x1005fc024` | 984 | rfcomm-client | RFCOMM ServiceClass second site | 出向连接旁证（spec 03.5） | ana 03 |
| `0x1005fcaf8` | 72 | rfcomm-reconnect | 读设备重试计数（u8 @ dev+0x647），用于 5 次上限判定 | 重连节奏依据 | analysis/06-rfcomm-disconnect-and-cleanup.md、spec/06-lifecycle-and-boundary.md |
| `0x1005fcb40` | 444 | rfcomm-reconnect | ScanCorePageScan 退避定时器：固定 300 s（0x45D964B800 ns → dispatch） | 重连节奏依据 | analysis/06-rfcomm-disconnect-and-cleanup.md、spec/06-lifecycle-and-boundary.md |
| `0x1005fcd8c` | 408 | rfcomm-reconnect | 连接请求看门狗：秒参数 × 1e9 → dispatch 定时器 | 重连节奏依据 | analysis/06-rfcomm-disconnect-and-cleanup.md、spec/06-lifecycle-and-boundary.md |
| `0x100631edc` | 1108 | sdp-client | SDP client connect state | SDP 客户端驱动旁证（spec 03） | — |
| `0x10063240c` | 1304 | sdp-client | 'Executing full SDP' state driver | SDP 客户端驱动旁证（spec 03） | — |
| `0x100632af4` | 2008 | sdp-client | 'Found %lu services supported RFCOMM, starting channel que… | SDP 客户端驱动旁证（spec 03） | ana 03, spe 03 |
| `0x100633770` | 656 | sdp-client | SDP client disconnect/retry bookkeeping | SDP 客户端驱动旁证（spec 03） | — |
| `0x1006347c0` | 612 | sdp-client | SDP client parser state machine (attribute/service-class/R… | SDP 客户端驱动旁证（spec 03） | — |
| `0x100634b7c` | 1296 | sdp-client | 'Querying RFCOMM Service' per-record channel extraction | SDP 客户端驱动旁证（spec 03） | ana 03 |
| `0x10063791c` | 1780 | service-registration | SDP query completion / mirroring hash | 服务选择/记录更新旁证（spec 02） | — |
| `0x10063cea4` | 828 | pairing | pairing agent XPC message dispatch | 配对路径旁证（analysis/07 C6） | — |
| `0x1006428ac` | 1548 | rfcomm-reconnect | 看门狗调用方：按条件取 8 s / 16 s 作为 stall 超时 | 重连节奏依据 | analysis/06-rfcomm-disconnect-and-cleanup.md、spec/06-lifecycle-and-boundary.md |
| `0x100653368` | 3748 | discovery | EIR/advertising service list and EIR length budget ('Adver… | 广播/发现路径旁证 | ana 01, spe 01 |
| `0x1007a3ba4` | 868 | rfcomm-client | 'Initiating outgoing Wireless IAP connection request ... r… | 出向连接旁证（spec 03.5） | ana 03, ana 04, ana 07, spe 03, spe 04 |
| `0x1007e106c` | 13496 | discovery | LE CarPlay connection scan interval/RSSI thresholds | 广播/发现路径旁证 | — |
| `0x10087dbf0` | 868 | rfcomm-client | second WiAP connect site (UUID variant path) | 出向连接旁证（spec 03.5） | — |
| `0x10088c824` | 16980 | pairing | classic link key / bonding info read-write | 配对路径旁证（analysis/07 C6） | — |
## 4. 未引用函数的处理原则

对 35 个 `SAMPLED_NOT_CITED` 函数，处理原则如下（**不允许**用它们支撑结论）：

1. 它们的存在只用于证明"该路径确实存在于固件中"，例如 `OI_RfcommMux_TEST invalid size`（`0x1003c6f94`）证明复用器 TEST 命令有独立实现。
2. 它们的**内部逻辑未被人工逐行核对**，因此任何依赖其细节的结论都会标 `OPEN`。
3. 若后续需要补强某条 `OPEN`，优先级如下：

| OPEN 编号 | 需要展开的函数 | 预期收获 |
|---|---|---|
| `OPEN-RF-5`（PN/RPN 字段格式） | **已完成**：`0x1003c73f0` 内联分派 + `0x1003c71e8`（MSC 组帧） | 见 `analysis/04` C8；剩余语义项 5a/5b/5c |
| `OPEN-RF-12`（超时单位） | **已关闭**：`0x1003c6180` → `0x1003c518c` → `0x10006135c` → `0x1000615dc` → `0x100061690` → `0x100060ff4` | 单位 = 100 ms（30 → 3 s），见 `analysis/04` C9.3 |
| `OPEN-SDP-3`（SDP 响应预算） | `0x1003ce304` 的调用点 | MTU 与预算的关系 |
| `OPEN-BND-3`（加密策略） | `0x100296014`、`0x1003010ac` | 是否存在安全前置检查 |
| `OPEN-DISC-2`（EIR 启用位） | `0x1004f20fc`、`0x1004f2730` | service mask 位映射 |

## 5. 已知的抽样盲区

| 盲区 | 说明 |
|---|---|
| 复用器命令族 | PN/RPN/MSC/FCON/FCOFF/TEST 的字段级编码未解出 |
| HCI 层 | 未向上追到 `Write_PageScan_Activity` 等命令的构造 |
| L2CAP 层 | 只确认 RFCOMM 通过 PSM 注册，未展开 L2CAP 的配置流程 |
| 上层框架 | `MobileBluetooth.framework` / CarPlay 侧未取证 |
| 定时器子系统 | 只见到句柄与启动调用，未展开时基 |
| `0x100060ff4` | 252 | rfcomm-timers | 定时器线程：值按毫秒拆成 timespec（/1000 与 %1000×1e6）后 pthread_cond_timedwait | MSC 组帧依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x100061690` | 88 | rfcomm-timers | 平台钩子本体：把 timeout*100 存入 0x100c25cc8 并唤醒定时器线程 | MSC 组帧依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x100312584` | 1132 | rfcomm-timers | 定时器 init 包装：以第 2 参数接收平台钩子并下传给 0x1003d7f28 | MSC 组帧依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |
| `0x1003d7f28` | 352 | rfcomm-timers | 定时器模块 init：按配置项分配 24 字节槽表，把平台钩子写入 0x100c39fb8 | MSC 组帧依据 | analysis/04-rfcomm-mux-link-setup.md、spec/04-rfcomm-link-establishment.md |

### 5.1 Ghidra 函数体与链接器边界的差异（切片约定）

`0x1003c59a0` 是一个已确认的例子：`LC_FUNCTION_STARTS` 在该区间给出 6 个函数起点
（`0x1003c59a0`、`0x1003c5c70`、`0x1003c5e80`、`0x1003c6180`、`0x1003c63f8`、`0x1003c6648`），
而 Ghidra 把整段 `0x1003c59a0..0x1003c6b60` 识别为**一个**函数，反编译体里同时包含
UIH 头解析（`0x1003c6764`–`0x1003c67b8`，属于 `0x1003c6648` 的函数体）等代码。

处理约定（本轮起生效）：

| 字段 | 含义 |
|---|---|
| `address` / `end` | 链接器（`LC_FUNCTION_STARTS`）认定的函数起点与下一个起点 |
| `slice_end` / `slice_size` | **实际导出的汇编切片**终点与字节数，按 Ghidra 反编译体范围 |
| `boundary_note` | 二者不一致时的说明与区间内其它函数起点清单 |

因此"切片比函数长"不是数据错误，而是**反编译体范围与链接器边界不同**的记录方式；
`verify.py` 用 `slice_end`（缺省回退 `end`）校验 `.bin` 与固件字节的一致性。
