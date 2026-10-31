# A — 结论登记表

等级：`指令级`（有指令地址且读到原始字节）、`运行期`（只有 23G90 抓包）、`INFERRED`（多事实推出，缺一条直接证据）。

| 编号 | 结论 | 等级 | 依据 |
|---|---|---|---|
| A01.1 | 隧道分三层：传输（BT/USB/AirPlay）→链路→iAP2 消息→中继（`0x5164/0x5264`）→信封（`0x55xx`）；中继与信封的代码在 `mfi4Auth` 会话对象里，不在链路对象里 | 指令级 | `analysis/01` §1.1–1.3；`0x100083ecc`、`0x10008449c`、`0x100022264`、`0x100022398` |
| A01.2 | 中继对象字段：`+0x1c` 最近命令 ID、`+0x1e` 关闭中标志、`+0x58` 动作闸门、`+0x80/+0x88` 能力掩码、`+0xE8+8n` 三个 handler 槽、`+0x140` provider、`+0x150` SOM | 指令级 | `analysis/01` §1.2；`0x1000858a0`、`0x100084da8`、`0x100084bd4`、`0x100084ce8` |
| A01.3 | 消息对：设备只发 `0x5163/0x5164/0x5500/0x5502`，只收 `0x5264/0x5265/0x5266/0x5501/0x5503` | 指令级 | `analysis/01` §1.3；`0x100084fa4`、`0x1000858a0`、`0x100083ecc`、`0x100022264`、`0x100084acc` |
| A01.4 | 中继层不查询传输类型：`processIncomingMessageRelay` 只接收消息对象，没有 `transportType` 分支 | 指令级 | `analysis/01` §1.5；`0x100083ecc` 全文 |
| A02.1 | `0x5500`/`0x5501` = 信封：param0(id 0)=`type`(u8)，param1(id 1)=整块数据；总长 = 15 + n | 指令级 | `analysis/02` §2.1–2.2；`0x100022264` @`0x1000222d4`、`0x1000222f0`、`0x1000222fc` |
| A02.2 | `0x5502` = 无参数请求，固定 6 字节 `40 40 00 06 55 02` | 指令级 | `analysis/02` §2.2；`0x100084acc` @`0x100084b28` |
| A02.3 | `0x5503` 不是信封，而是信息更新消息本身；`unpack` 返回"整条消息"的 `CFData`（`buf=[msg+0x18]`，长 = `GetMsgLen`）| 指令级 | `analysis/02` §2.2；`0x100022398` @`0x100022440`–`0x100022458`、`control/A03.1` |
| A02.4 | 容量：消息缓冲 `0xFFFF`、解析缓冲 `0x1001F`；单条信封 data ≤ 65,520 字节；越界时 `AddDataParam` 返回 0（打包失败，不是截断）| 指令级 | `analysis/02` §2.3；`0x1000222b8`、`0x100022398` @`0x1000223c4`、`0x100067c80`–`0x100067c9c` |
| A02.5 | 多条 param1 是**覆盖**（先 `CFRelease` 再新建），不是拼接 | 指令级 | `analysis/02` §2.2；`0x1000224b8` 循环 + 串 `0x1da562` |
| A03.1 | 出站：`type<3` 且槽位非 0 → `pack(type,data,0)`=`0x5500` → 塞进 `0x5164` 的 param0 → `sendOutgoingData` | 指令级 | `analysis/03` §3.2；`0x100084da8`、`0x100084ef4`、`0x1000858a0` |
| A03.2 | 入站按顶层 msgID 分派：`0x5266`→成功、`0x5265`→失败、`0x5264`→数据、其它→丢弃 | 指令级 | `analysis/03` §3.3；`0x100083ecc` @`0x100083f74`–`0x100083f8c` |
| A03.3 | `0x5266` 的唯一实质动作是立刻再发 `0x5163`；`0x5265` 则 `handle_AuthState(auth,1)` | 指令级 | `analysis/03` §3.4；`0x1000849a4` @`0x1000849f4`、`0x100084a40` @`0x100084a88` |
| A03.4 | 最近命令字段与成功后读请求已证实；全局单条在途未证，停等是参考实现保守策略 | 观察 / 策略 | `analysis/03` §3.4；`0x1000858a0` @`0x1000858fc`、`0x1000849a4` |
| A03.5 | `0x5264` 缺第一个参数：偏好开关为零时不重试，非零时 `usleep(1000)` 后生成 `0x5163`；不能套到所有解包错误 | 指令级 | `analysis/03` §3.5；`0x100084594`、`0x1000847d0`–`0x100084814` |
| A03.6 | 闸门为 0 时，尚未处理的 bit0 优先发 `0x5502`；否则处理 bit2 并 `StartRelayForType(auth,2)`；`& -4` 清 bit0/bit1，保留 bit2；仅 OR 入已处理位 | 指令级 | `analysis/03` §3.6；`0x100084310`–`0x100084474` |
| A04.1 | `type` 取值 0–2，出站与入站都检查 `< 3` | 指令级 | `analysis/04` §4.1；`0x100084e1c`、`0x1000845dc` |
| A04.2 | handler 槽位在 `+0xE8+8*type`，置位函数把 `auth` 自身写入；投递时调 `[slot+0x10]` | 指令级 | `analysis/04` §4.1；`0x100084ce8` @`0x100084d4c`、`0x10008449c` @`0x1000847c8` |
| A04.3 | `0x5503` 参数：id 0–4 = 名称/型号/厂商/序列号/固件版本，id `0xF2` = u64 能力位图 | 指令级（ID）/ INFERRED（键名）| `analysis/04` §4.4；`0x100085034` |
| A04.4 | `StartRelayForType` 只把 `(type)` 转给 `provider(+0x140)` 的 `+0x10`，不构造消息 | 指令级 | `analysis/04` §4.3；`0x100084bd4` @`0x100084c40`–`0x100084c48` |
| A05.1 | `transport=AirPlay` 的链路承载标准 iAP2 帧（`40 40 len msgID params`），会话号 3；与 BT 链路同构 | 运行期（23G90）| `analysis/05` §5.1、`analysis/08` §8.2；`runtime/*.ips` |
| A05.2 | 会话号由 SYN 决定：SYN/SYNACK 参数尾部 `… 0f 00 03 00 02` 与后续全部帧 `session=0x03` 一致 | 运行期（23G90）| `analysis/05` §5.2、`analysis/08` §8.2 |
| A05.3 | `0xFFFA`（开始，设备→车机）、`0xFFFB`（NMEA 数据，车机→设备）、`0xFFFC`（停止，设备→车机）在 AirPlay 链路上出现；设备侧发送点 `0x1001798fc`/`0x100179b3c`，`0xFFFB` 处理器 `0x100179484` | 运行期（23G90）+ 指令级（发送点）| `analysis/08` §8.3–8.4 |
| A05.4 | 抓包里 AirPlay 链路上**没有** `0x55xx` 中继消息 | 运行期（23G90）| `analysis/08` §8.5；`runtime/parse-capture.py` 输出无 `55 00/55 01` |
| A06.1 | 错误路径齐全：`type≥3`、槽位空、内层 ID 未知、长度非法、`0x5503` 重解析失败、空载荷、未知顶层 ID | 指令级 | `analysis/06` §6.1；对应日志串地址 |
| A06.2 | 拆除：`[auth+0x1e]=1` 后所有入口失败；`relay_cleanup` 把三个槽位清零；没有独立的隧道关闭消息 | 指令级 | `analysis/06` §6.3；`0x100083e84`、`0x10008449c` 开头 |
| A06.3 | 信封自身不含加密字段：`pack` 直接把数据 `memcpy` 进 param1，无 nonce/tag 参数；但整条消息的**载荷**会被 mfi4Auth 会话封装（见 A09.5/A09.6）| 指令级 | `analysis/06` §6.4；`0x100022264`、`0x100067c88` |
| A07.1 | 信封层没有分片：没有片序号/总片数/偏移/more 标志；多片只会覆盖 | 指令级 | `analysis/07` §7.1–7.3；`0x100022264`、`0x100022398` |
| A07.2 | 分片与重传在链路层：消息跨包由 `seq/ack/lt/校验` 保证，会话解析器逐字节喂 | 指令级（引用 `control/A08.1`）| `analysis/07` §7.4；`link/R-2.x`、`link/R-4.x` |
| A07.3 | 信封未见信用字段；中继采用保守停等模型；链路层另有队列/重传 | 限定观察 / 策略 | `analysis/07` §7.5；`A03.4`、`A02.1` |
| A08.1 | 23G90 样本第二个连接共 40 帧（22 条非 ACK），全部 iAP2 消息长度字段自洽 | 运行期（23G90）| `analysis/08` §8.2；`runtime/parse-capture.py` |
| A08.2 | `0xFFFA` 参数：`param0=20`、空 `param1/2/4` + `0x8001=250`、`0x8002=250`、`0x8004=20`；`0x8000\|N` 与空 `N` 成对 | 运行期（23G90）| `analysis/08` §8.3 |

| A09.1 | 中继是消息分发的**兜底**：`receiveIncomingData` 依次调 `processIncomingMessage`、`processIncomingMessageExtra`，两者都返回 0 才调 `processIncomingMessageRelay`；全二进制仅此一个调用点 | 指令级 | `analysis/09` §9.1；`0x1000fec30` @`0x1000fee80`、`0x1000feec4`、`0x1000feef0` |
| A09.2 | 合法隧道 `type` 为 0/1/2（`>=3` 走错误路径）；iPhone 只为 `type=2` 装 handler，`type=2` 即 **T56 认证中继** | 指令级 | `analysis/09` §9.2；`0x1000a9bc8` @`0x1000a9bf4`、`0x1000a9c90`、`0x1000a9db4` |
| A09.3 | T56 双方向：出站 router(`+0x38`)→endpoint→`0x5500(type=2)`→`0x5164`；入站槽位→`startRelayForT56_block_invoke`→`acc_manager2_processIncomingDataForConnectionEndpoint` | 指令级 | `analysis/09` §9.3；`0x1000ab3ac` @`0x1000ab474`、`0x1000a935c`、`0x10017a64c` |
| A09.4 | `startRelay` provider 是 ObjC block：`+0x10` 是 invoke（`0x1000a9bc8`），`+0x18` 是 descriptor；不存在 C++ vtable | 指令级 | `analysis/09` §9.4；`0x1000a8428` @`0x1000a8ae4` |
| A09.5 | 载荷**条件式**加密：协议对象 `+0xE0` 为 0 时 `encryptOutgoingData`/`decryptIncomingData` 直通；否则 `0x5163/0x5164`（及 `0x51ff`）走 `encryptPayload(msg,5,6)`，其它 msgID 直通不加密 | 指令级 | `analysis/09` §9.5；`0x1001327d0` @`0x100132808`、`0x1001328c8`、`0x100132900` |
| A09.6 | 加密粒度：6 字节 iAP2 头明文、载荷 AEAD、长度字段改写为 `len+0x10`（16 字节 tag）；算法族为 `ccsigma_seal/open` + `ccsigma_kex_init_ctx`/`derive_session_keys` | 指令级 | `analysis/09` §9.5；`0x100132acc`、`0x100131fbc`、`0x10019f788` |
| A09.7 | 中继对象挂在**每连接**的 protocolRouter 上（`+0x38` = mfi4Auth endpoint），隧道是连接级而非全局 | 指令级 | `analysis/09` §9.6；`0x10017a64c`、`0x10017a774` |

## OPEN 登记

| 编号 | 内容 | 影响 |
|---|---|---|
| `OPEN-TUN-1` | 车机侧收到 `0x5500` 的解析（无对端固件）| 只能按对称假设实现 |
| `OPEN-TUN-2`（收窄：type 空间=0/1/2，2=T56；0/1 语义仍未证，见 A09.2） | `type` 0/1 的语义与启动条件（固件只有 `StartRelayForType(2)`）| 业务数据走哪个 type 需实验 |
| `OPEN-TUN-3`（收窄：合法 type 上界 2，bit1 无对应槽位，见 A09.2） | capabilities 掩码 bit1 与其余位 | 协商时按位图整体回送、不解释未知位 |
| `OPEN-TUN-4`（收窄：中继是分发兜底、不含传输分支，见 A09.1） | 中继是否只在 AirPlay 传输上启用 | 实现上对所有传输都启用最安全 |
| `OPEN-TUN-5` | AirPlay 隧道自身帧格式/MTU/握手（accessoryd 之外）| 需 AirPlay 侧文档或抓包 |
| `OPEN-TUN-6` | `0x5163` 重试上限/超时 | 实现需自定上限 |
| `OPEN-TUN-7` | 首次 `0x5502` 的触发时机 | 遵循已证能力/闸门条件；主动查询安全性未证 |
| `OPEN-TUN-8`（**已关闭**：provider 是 block，`[+0x10]`=invoke，见 A09.4） | handler 对象身份、`[slot+0x10]` 目标、`+0x10/+0x18` 字段语义 | 不影响线格式 |
| `OPEN-TUN-9` | 对端是否真的只发一个 param1 | 本侧按"最后一个生效"实现 |
| `OPEN-TUN-10`（**大幅推进**：条件式载荷加密 + ccsigma AEAD + 16 字节 tag，见 A09.5/A09.6；算法参数仍未证） | 信封/信道之外是否另有 MFi4 SecureTunnel 加解密 | 安全边界不清 |
| `OPEN-TUN-11`（收窄：连接级 router+0x38，选择点不在本镜像，见 A09.7） | 隧道数据落在哪条 iAP2 链路（按会话号还是按端点）| 多链路时需实验 |
| `OPEN-TUN-12` | 没有 24A446 的 AirPlay 运行期样本 | 运行期结论只到 23G90 |
