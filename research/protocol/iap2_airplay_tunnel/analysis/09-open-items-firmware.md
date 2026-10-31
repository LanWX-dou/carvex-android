# analysis/09 — 用固件关闭/收窄未决项（定向取证）

> 本文件只回答一件事：**12 个 `OPEN-TUN-*` 里，哪些能靠 24A446 accessoryd 的字节本身推进**，推进到什么程度，哪些在固件里根本不存在答案。
> 方法：先按符号名扫（`secureTunnel|t56|relay|capabilit|encrypt` 等），再用 Capstone 对全部 8,706 个函数起点做 BL/立即数扫描，挑出被漏掉的入口；新增 19 个函数进 `selection.json`（group `O`，总数 227 → 246），导出 `.s/.bin` 与 Ghidra 反编译。
> 每条结论都给了地址；没有地址的一律标**推断**。

---

## 9.0 新增取证的入口（都在 0x1000f0000 与 0x1000a0000 两级）

| 层 | 函数 | 地址 | 作用 |
|---|---|---|---|
| 消息处理器 | `mfi4Auth_protocol_messageHandler_receiveIncomingData` | `0x1000fec30` | 入站总入口：解析 → 解密 → 分派 |
| 消息处理器 | `..._sendOutgoingData` | `0x1000ff070` | 出站出口：加密 → 回调发送 |
| 消息处理器 | `..._handleOutgoingSecureTunnelDataForClient` | `0x1000ff27c` | 出站隧道数据 |
| 协议 | `mfi4Auth_protocol_encryptOutgoingData` | `0x1001327d0` | 按 msgID 决定是否/如何加密 |
| 协议 | `mfi4Auth_protocol_encryptPayload` | `0x100132acc` | 载荷加密（`ccsigma_seal`） |
| 协议 | `mfi4Auth_protocol_decryptIncomingData` / `decryptPayload` | `0x100131fbc` / `0x100132318` | 入站解密 |
| endpoint | `mfi4Auth_endpoint_initSession` | `0x1000a8428` | 装 9 个回调（含 startRelay provider）|
| endpoint | `startRelay` provider 块体 | `0x1000a9bc8` | **type 空间的唯一判决点** |
| endpoint | `acc_endpoint2_setEndpointSecureTunnelDataReceiveTypeHandler` | `0x1000f5cf8` | 装 type 槽位 |
| endpoint | `..._processOutgoingSecureTunnelDataForClient` + invoke | `0x1000a91e4` / `0x1000a935c` | type 从 `block+0x30` 取 |
| router | `acc_protocolRouter_routeOutgoingSecureTunnelDataForClient` | `0x10017a64c` | 连接级路由 |
| router | `acc_protocolRouter_setSecureTunnelDataTypeHandler` | `0x10017a774` | 连接级登记 |
| T56 | `startRelayForT56_block_invoke` | `0x1000ab3ac` | T56 出站回流 |
| T56 | `t56_protocol_checkValidMessageHeaderAndSize` | `0x100040300` | T56 分帧 |

## 9.1 中继是"三条路都认不出"时的兜底（收窄 OPEN-TUN-4）

`0x1000fec30` 的顺序是**写死的**：

```text
0x1000fee80  bl  mfi4Auth_protocol_processIncomingMessage        ; 常规 iAP2 消息
0x1000feec4  bl  mfi4Auth_protocol_processIncomingMessageExtra   ; 扩展消息
0x1000feef0  bl  mfi4Auth_protocol_processIncomingMessageRelay    ; 中继（仅当上面两个都返回 0）
```

只有 `0x1000feef0` 这一条 `bl` 指向 `0x100083ecc`；全 8,706 个函数里没有第二个调用点（BL 全扫，见 §9.7 复现）。

**含义**：`0x5163/0x5164/0x5264/0x5265/0x5266` 不是 iAP2 核心消息，而是"核心与扩展都未识别"之后的独立模块。因此客户端**必须**在消息分发最末端挂中继，且中继只应处理这 5 个 msgID。

## 9.2 type 空间：只有 0/1/2，只有 2 会被真的启用（收窄 OPEN-TUN-2）

`startRelay` provider 的块体 `0x1000a9bc8` 是唯一判决点：

```text
0x1000a9bf4  cmp  w2, #3
0x1000a9bf8  b.hs 0x1000a9e54          ; type >= 3 → 错误路径（不建链）
0x1000a9c90  cmp  w19, #2
0x1000a9c94  b.ne 0x1000a9cd0          ; type != 2 → 另一条（仅日志/忽略）
...
0x1000a9d94  adrp/add x16, 0x1000ab3ac ; 块体 invoke = startRelayForT56_block_invoke
0x1000a9db0  mov  w1, #2
0x1000a9db4  bl   0x1000f5cf8          ; acc_endpoint2_setEndpointSecureTunnelDataReceiveTypeHandler(ep, 2, block)
```

- 合法 type 是 `0/1/2`（`>=3` 直接拒绝），与 `0x5500` 的 `type` 是同一编号空间；
- iPhone 侧**只**为 `type=2` 装槽位，`type=0/1` 走到 `0x1000a9cd0` 分支且不装槽位（该分支只有 `os_log_type_enabled`(0x1000a9d04) 与一次 `0x1001656d0` 调用，未见装槽位或建链）；
- `type=2` 的语义由 `0x1000ab3ac` 定为 **T56**（函数名与 9.3 的调用链一致）。

**仍未证**：`type=0/1` 在**对端**（车机）是什么语义。固件里只有"我们不启用它们"这一事实，没有它们的定义。这一条保持 `OPEN-TUN-2`。

## 9.3 type=2 的闭环：T56 双方向（新结论）

```text
出站：T56 stack → acc_protocolRouter_routeOutgoingSecureTunnelDataForClient (0x10017a64c)
     → [router+0x38] = endpoint → endpoint_processOutgoingSecureTunnelDataForClient (0x1000a91e4)
     → invoke (0x1000a935c): handleOutgoingSecureTunnelDataForClient([ep+8], [block+0x30]=type, [block+0x28]=data)
     → 0x5500(type=2) 装入 0x5164 → sendOutgoingData

入站：0x5264 → 0x5501(type=2) → 槽位 → 0x1000ab3ac
     → acc_manager2_processIncomingDataForConnectionEndpoint([ep+0x20],[ep+0x28],data)  (0x1000ab474)
```

`block+0x30` 是 type（`0x1000a935c` 里 `ldrb w1,[x19,#0x30]` 的等价读法，见 §9.5），`block+0x28` 是数据。T56 自己是一套带 1 字节头 + 类型的协议（`0x100040300` 里日志格式 `"msgType %d(%s), msgHeader 0x%02X, msgDataLen %d"`），**不是** iAP2 帧。

## 9.4 `[slot+0x10]` 是什么：block 的 invoke（关闭 OPEN-TUN-8）

`0x1000a8428` 里：

```text
0x1000a8ae4  bl  mfi4Auth_protocol_setStartRelayHandler(protocol, &local_1d8)
```

`local_1d8` 是一个 `NSConcreteStackBlock` 结构体，Ghidra 给出的布局是 `{isa, flags, invoke, descriptor, captured…}`：

```text
local_1d8 = NSConcreteStackBlock
local_1d0 = flags
local_1c8 = ____mfi4Auth_endpoint_initSession_block_invoke_7   (= 0x1000a9bc8)
local_1c0 = descriptor
local_1b8 = endpoint
```

所以中继对象 `+0x10` 的"vtable"其实是 **block 的 invoke 指针**（`block+0x10`），调用约定是 `invoke(block, type, data)`。同一文件里 9 个 handler 全是这种块（`setOutgoingDataHandler`、`setAuthStateHandler`、`setStartRelayHandler`…）。**OPEN-TUN-8 关闭**：不存在 C++ vtable，`[slot+0x10]` 就是 block invoke，`[slot+0x18]` 是 descriptor。

## 9.5 载荷被 MFi4 会话加密：`ccsigma` AEAD，header 明文（大幅推进 OPEN-TUN-10）

出站链 `0x1000ff070`：

```text
0x1000ff128  bl 0x1001327d0              ; encryptOutgoingData(protocol, msg)
0x1000ff194  blraa x9, x8                ; [protocol+0x100]+0x10 = 真正的发送回调
```

`0x1001327d0`：

```text
0x100132808  ldr w8,[x21,#0xe0]
0x10013280c  cbz w8, 0x100132908         ; +0xE0 == 0 → 直接返回 1（不加密）
0x100132884  bl  iAP2MsgGetMsgID
0x100132888  mov w8, #-0x5112 ; add w8, w20, w8   ; 0x5112..0x5149 家族走位掩码表
0x1001328c0  sub w8, w20, #0x5163
0x1001328c8  cmp w8, #2                  ; (msgID-0x5163) < 2  → 0x5163 / 0x5164
0x1001328f8  mov w2, #5
0x1001328fc  mov w3, #6
0x100132900  bl  0x100132acc             ; encryptPayload(protocol, msg, 5, 6)
```

`0x51ff` 与 `{0x5163,0x5164}` 走同一分支；`0x5112–0x5149` 家族先走位掩码表（`encryptPayload(...,10,0xb)` 或 `(...,3,4)`）；**其它 msgID 在记一条日志后 `return 1` 直通，不加密**。也就是说这是**按 msgID 选择性的载荷加密**，不是整条会话全加密。

`0x100132acc`：

```text
lVar9 = [msg+0x18]                       ; 消息缓冲
uVar3 = iAP2MsgGetMsgLen(msg)
*(u16*)(lVar9+2) = htons(uVar3 + 0x10)   ; 长度字段 +16
buf = malloc(uVar3 - 6)                  ; 只用 6 字节头之后的载荷
... ccsigma_seal(...)                    ; AEAD 封装
```

三条硬事实：

1. **加密条件**：协议对象 `+0xE0` 的 32 位字段为 0 时，`encryptOutgoingData`/`decryptIncomingData` 直接返回成功、不动字节（`0x10013280c`、`0x100131fbc` 同款判定）。即：**会话密钥未建立前，中继消息是明文**。
2. **加密粒度**：6 字节 iAP2 头（`40 40 len msgID`）保持明文，**载荷**被封装，总长度 +16 字节（AEAD tag）。也就是说 `0x5164` 的 msgID 与长度在线上可见，`0x5500` 信封整体在密文里。这修正了 `A06.3`"信封不加密"的表述——准确说法是**信封外层的 iAP2 头不加密，信封本身在载荷密文内**。
3. **算法族**：`ccsigma_seal`(0x10019f788) / `ccsigma_open`(0x10019f8e0)，配套 `ccsigma_kex_init_ctx`(0x100115f68)、`kex_resp_ctx`(0x100115f88)、`derive_session_keys`(0x100115fa8)、`import_peer_verification_key`(0x100115dd8)。即 MFi4 会话是一次**带签名的密钥交换 + AEAD**，不是简单 AES-CBC。

**仍未证**：`ccsigma` 的具体曲线/签名算法/标签格式；`+0xE0` 字段的名字与置位时机；`encryptPayload` 的 `(5, 6)` 两个常量含义（保持 `OPEN-TUN-10`）。

## 9.6 隧道挂在"每条连接的 protocolRouter"上（收窄 OPEN-TUN-11）

```text
0x10017a64c  acc_protocolRouter_routeOutgoingSecureTunnelDataForClient(router, ?, data)
             → [router+0x38] → mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient
0x10017a774  acc_protocolRouter_setSecureTunnelDataTypeHandler(router) → endpoint setter
```

路由器（`acc_protocolRouter_*`）是**每连接一个**的对象；`+0x38` 挂该连接的 mfi4Auth endpoint。所以"隧道走哪条链路"的答案是：**走该 router 所属连接**。至于为什么要选 AirPlay 而不是 BT——发生在 router 之上（`control/` 的传输选择），不在本 docset 的证据范围内，`OPEN-TUN-11` 由"未证"收窄为"已证为连接级、选择点未证"。

## 9.7 复现

```bash
python3 firmware/tools/export-asm.py research/protocol/iap2_airplay_tunnel/source/firmware/accessoryd \
        research/protocol/iap2_airplay_tunnel/source/metadata \
        research/protocol/iap2_airplay_tunnel/source/metadata/selection.json \
        research/protocol/iap2_airplay_tunnel/source/asm/accessoryd
python3 firmware/tools/build-ghidra-request.py research/protocol/iap2_airplay_tunnel
# Ghidra headless：ExportDecomp.java（同 00 号文件）
```

BL 全扫脚本（本次判定"唯一调用点"用的口径）不在仓库里；等价做法：对 `function-starts.json` 的每个起点用 Capstone 反汇编到下一个起点，抓 `bl #0x<target>` 的 `op_str`，与目标地址比较。**注意**：文件偏移必须用 `addr - 0x100000000`（`__TEXT` 段 vmaddr 即文件 0 偏移）；用 `section.fileoff + (addr - section.addr)` 也能得到同一结果，因为该 section 的 `fileoff - addr` 恰好等于 `-0x100000000`，但两者混用会整体偏移 0x5C0 字节（本次踩过）。

## 9.8 12 项此刻的处置

| OPEN | 处置 | 依据 |
|---|---|---|
| `OPEN-TUN-1` 对端解析 | **无法由固件关闭** | 对端在车机；`0x5500` 的接收端不在 iPhone 任何一个二进制里 |
| `OPEN-TUN-2` type 0/1 语义 | **收窄**（见 §9.2）| `0x1000a9bc8` |
| `OPEN-TUN-3` 能力位 bit1 | 收窄：合法 type 上界为 2，bit1 无对应槽位 | `0x1000a9bf8` |
| `OPEN-TUN-4` 是否仅 AirPlay | 收窄：中继是分发兜底，与传输无关 | `0x1000feef0` |
| `OPEN-TUN-5` AirPlay 帧/MTU | 固件内无答案（在 AirPlay 镜像，见 `analysis/05`）| — |
| `OPEN-TUN-6` 重试上限 | 收窄：`MFi4RelayReadRetryDelayMs` 只控延时，无计数常量 | `0x10008449c` |
| `OPEN-TUN-7` 首次 0x5502 时机 | 收窄：由 `+0x80` 新置位触发（`0x1000843d4`），首次时机仍取决于能力下发 | `0x100083ecc` |
| `OPEN-TUN-8` handler 身份 | **关闭**（见 §9.4）| `0x1000a8ae4`、`0x1000a9bc8` |
| `OPEN-TUN-9` 多 param1 | 无法由固件关闭（对端行为）| — |
| `OPEN-TUN-10` SecureTunnel 加解密 | **大幅推进**（见 §9.5）：`ccsigma` AEAD、+16、条件式 | `0x1001327d0`、`0x100132acc` |
| `OPEN-TUN-11` 绑定哪条链路 | 收窄：连接级（router+0x38），选择点不在本镜像 | `0x10017a64c` |
| `OPEN-TUN-12` 缺 24A446 AirPlay 抓包 | 固件不能替代运行期样本 | — |
