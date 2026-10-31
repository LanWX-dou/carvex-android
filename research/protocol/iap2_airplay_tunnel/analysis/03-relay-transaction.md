# analysis/03 — 中继事务：`0x5163/0x5164` 与 `0x5264/0x5265/0x5266`

隧道不是在 iAP2 链路上裸奔，而是装在 MFi 认证会话的**中继请求**里。本文件把这条事务的每一步钉死。

## 3.1 请求族

| ID | 方向 | 参数 | 指令 |
|---|---|---|---|
| `0x5163` | 设备 → 车机 | 无 | `0x100084fa4` `iAP2MsgInitWithSom(msg, som, 0x5163, …)` |
| `0x5164` | 设备 → 车机 | param0 = 整条内层消息 | `0x1000858a0` `mov w23,#0x5164` |
| `0x5264` | 车机 → 设备 | param0 = `0x5501`/`0x5503` 字节 | `0x100083ecc` @`0x100083f8c` |
| `0x5265` | 车机 → 设备 | —（失败）| 同上 @`0x100083f80` |
| `0x5266` | 车机 → 设备 | —（成功）| 同上 @`0x100083f74` |

`0x5163` 与 `0x5164` 只差一位：**`0x5163` = "请把你手上的数据再发一次"，`0x5164` = "这是我发出的数据"**。两者都把 `[auth+0x1c]`（最近命令）改成自己的 ID，供日志 `"cmd:0x%x rsp:0x%x"`（串 `0x1f17f2`）使用。

## 3.2 设备发一条隧道数据（出站）

`_mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient(auth, type, data)` @`0x100084da8`：

```text
0x100084dc4  if (auth == NULL) fail
0x100084dcc..0x100084dd4  if (auth->shuttingDown(+0x1e) == 1) fail
0x100084e14  if (data_object == NULL) fail   ; 指针检查，不是数据长度检查
0x100084e24..0x100084e28  if (type >= 3) → "invalide secureTunnelType (%d)" fail
0x100084e40  if (auth->handler[type] (+0xE8+8*type) == 0) → "missing internal tunnel handler" fail
0x100084e54  mfi4Auth_relay_initMessage_..._TypeData(auth, &out, type, data)
0x100084e64  mfi4Auth_protocol_messageHandler_sendOutgoingData(auth, out)
```

`initMessage_..._TypeData`（`0x100084ef4`）做两步：

```text
0x100084f1c  inner = packIntoTunnelDataiAP2Msg(type, data, 0)     ; → 0x5500
0x100084f30  initMessage_DeviceiAP2RelayRemote(auth, &out, inner) ; → 0x5164(param0=inner)
0x100084f44  [auth+0x1c] = 0x5164
```

## 3.3 设备收一条隧道数据（入站）

`processIncomingMessageRelay` @`0x100083ecc` 先按 msgID 分派（`0x100083f60`–`0x100083fa0`）：

| msgID | 动作 |
|---|---|
| `0x5266` | `mfi4Auth_relay_handle_iAP2RelaySucceeded`（`0x1000849a4`）|
| `0x5265` | `mfi4Auth_relay_handle_iAP2RelayFailed`（`0x100084a40`）|
| `0x5264` | `mfi4Auth_relay_handle_iAP2RelayRemote`（`0x10008449c`）|
| 其它 | 日志 `"failed to handle relay remote"` / 未知消息 |

`0x5264` 的处理（`0x10008449c`）：

```text
0x100084590  p = iAP2MsgGetFirstParam(msg, NULL)   ; 第二参数是父参数，不是 ID
0x100084594  if (p == NULL) → 无参数分支（见 3.5）
0x1000845a0  bytes = iAP2MsgGetDataAsData(p, &kind)
0x1000845ac  n = iAP2MsgGetParamValueLen(p)
0x1000845c4  NSData(dataWithBytes:length:)
0x100084688  unpackFromTunnelDataiAP2Msg(nsdata, &type, &innerMsgID)
0x100084694..0x1000846a0  if (unpackedData.length <= 5) → 拒绝
0x100084700..0x10008470c  if (innerMsgID == 0x5503) → 信息更新
0x100084710..0x100084724  else if (innerMsgID == 0x5501 && type < 3) → 槽位检查
0x100084790..0x1000847a8  handler[+0xE8+8*type] 调用
```

> `0x5503` 分支走的是**信息更新**（更新 capabilities），`0x5501` 分支走**业务数据**（交给注册的 type handler）。两条分支都在 `A06.1` 的错误表里有对应日志。

## 3.4 成功即拉下一条；并发约束仍未证

- `handle_iAP2RelaySucceeded` 的唯一实质动作是：**立刻再发一条 `0x5163`（RequestiAP2RelayRead）**，把"下一条待发数据"要过来（`0x1000849f4`–`0x100084a00`）；
- 可据此建立保守的单条在途模型：发 `0x5164` → 等 `0x5266`/`0x5265` → 再发 `0x5163` → 等 `0x5264`；
- 但“最近命令”只保存一项与信封无窗口字段，不足以证明禁止所有并发调用。完整入队/调度闸门和对端行为尚未闭合，停等是参考实现策略（`A03.4`），不是已证实的跨版本协议限制。

`handle_iAP2RelayFailed` 只做一件事：`mfi4Auth_protocol_handle_AuthState(auth, 1)`（`0x100084a88`），即把认证状态打成 1。**中继失败不是"丢一条数据"，而是整条认证会话失败**。

## 3.5 空载荷 → 短延时重读

`0x5264` 没有第一个参数时（`0x100084594` 分支）：

```text
0x1000847dc  v = acc_userDefaults_boolForKey(kCFACCUserDefaultsKey_MFi4RelayReadRetryDelayMs)
0x1000847e0  if (v == 0) → 返回失败
0x1000847fc..0x10008480c  usleep(1000); initMessage_RequestiAP2RelayRead(auth, out)
```

即：偏好读取结果为零时不重试；非零时等 1 ms 再构造 `0x5163`。此分支没有次数上限常量；偏好未设置时的实际默认值和上层超时仍需核实（`OPEN-TUN-6`）。不能把重读推广到已有首参数但内层格式错误、缺少 param1 或解包结果太短的路径。

## 3.6 能力协商（`0x5502`/`0x5503`）

`processIncomingMessageRelay` 在 `param_3 == 0`（或首参缺失）时走协商分支（`0x1000840e0`–`0x1000844ac`）：

```text
newMask   = [auth+0x80]            ; 本次算出的掩码
processed = [auth+0x88]            ; 已生效掩码
if ([auth+0x58] == 0 && newMask != 0 && newMask != processed):
    if ((newMask & 1) == 0 || (processed & 1) != 0):        ; bit0 不是"新置位"
        rest = newMask & 0xFFFFFFFFFFFFFFFC   ; ands x21,x24,#-4 @0x1000843dc
        if (rest != 0 && (newMask>>2 & 1) && !(processed>>2 & 1)):
            [auth+0x88] |= 4
            StartRelayForType(auth, 2, out)                 ; type=2 的 relay
    else:                                                   ; bit0 新置位
        [auth+0x88] |= 1
        [auth+0x58]  = 0xF
        initMessage_..._RequestAccessoryInfoUpdate(auth, out)  ; → 0x5502
```

可读出的规则（注意这是该固件分支的优先级，而不是“同一次更新必同时执行两个动作”）：

1. **bit0 = 配件信息更新中继**：bit0 由 0→1 时，设备主动发 `0x5502` 拉一次 `0x5503`；
2. **bit2 = T56 中继**：仅当 bit0 没有在同一次调用中走“信息更新”分支时，bit2 尚未处理才启动 `type=2` 的 relay。`ands ...,#-4` 清 bit0/bit1，保留 bit2；bit2 置位即已满足 `rest != 0`，不要求额外未知位。`processed` 只 OR 入已处理位，不能整字赋为 newMask；
3. **bit1 被有意忽略**：`newMask & 0xFFFFFFFFFFFFFFFC` 把 bit0/bit1 一起清掉，注释层面没有解释，只能登记 `OPEN-TUN-3`；
4. `+0x58` 是"动作已排"的闸门，置 `0xF` 后同一次协商不重复发。

## 3.7 未确认点

| 编号 | 内容 |
|---|---|
| `OPEN-TUN-6` | `0x5163` 重试的次数/超时（代码里只有 1 ms 延时，没有上限）|
| `OPEN-TUN-3` | capabilities bit1 的语义（被 `& 0xFFFFFFFFFFFFFFFC` 掩掉）|
| `OPEN-TUN-7` | 首次 `0x5502` 的触发时机（是否必须等车机先发一条 `0x5264`）|
| `OPEN-TUN-4` | 中继是否只在 AirPlay 传输上启用（代码不查 transport）|
