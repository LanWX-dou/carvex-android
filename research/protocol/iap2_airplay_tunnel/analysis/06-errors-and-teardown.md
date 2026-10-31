# analysis/06 — 错误、拆除与安全边界

## 6.1 错误分类（全部来自固件内日志串）

| 条件 | 日志串（地址）| 出现位置 | 设备侧动作 |
|---|---|---|---|
| `type >= 3`（出站）| `"invalide secureTunnelType (%d)"`（`0x1f1aa2`）| `0x100084e1c` | 不发 |
| `type >= 3`（入站）| `"no secureTunnelHandler for type %d !!!"`（`0x1f1e57`）| `0x1000845dc` | 丢弃 |
| 槽位为空（出站）| `"missing secure tunnel handler"`（`0x1f1bba`）| `0x100084e40` | 不发 |
| 槽位为空（入站）| 同 `0x1f1e57` | 同上 | 丢弃 |
| 内层消息 ID 非 `0x5501/0x5503` | `"unable to unpack nested message!!!"`（`0x1f1d3a`）| `0x10008449c` | 丢弃 |
| 内层消息长度不合法 | `"invalid unpacket message size(%zu) !!!"`（`0x1f1d87`）| 同上 | 丢弃 |
| `0x5503` 重解析失败 | `"failed to parse AccessoryInformationUpdate message!!!"`（`0x1f1f1f`）| `0x1000847ac` | 丢弃 |
| `0x5264` 无 param | `"Has no payload !!!, retry after %d ms"`（`0x1f1c7c`）| `0x100084550` | 见 §6.2 |
| 未知顶层 msgID | `"failed to handle relay remote"`（`0x1f1822`）| `0x100083ecc` | 丢弃 |
| 未知内层 msgID | `"Unrecognized message 0x%04X !!!"`（`0x1da64b`）| `0x100022398` | 返回 0 |
| 中继失败 `0x5265` | —（无专属串）| `0x100084a40` | **认证状态置 1** |

## 6.2 空载荷的两种含义

`0x5264` 没有参数时，代码**分不清**"没有数据"和"数据还没到"，于是：

```text
0x1000845b0  v = userDefaults[MFi4RelayReadRetryDelayMs]
0x1000845c0  if (v != 0) { usleep(1000); 发 0x5163 重读 }
0x1000845d8  else 返回失败（调用方丢弃）
```

- 默认（未设 default）**不重试**；
- 设了 default 也只是"等 1 ms 再要一次"，没有次数上限、没有超时值（`OPEN-TUN-6`）。

## 6.3 拆除

| 事件 | 动作 | 依据 |
|---|---|---|
| 认证会话关闭 | `[auth+0x1e] = 1`；之后所有中继入口直接失败 | `0x10008449c`、`0x100084da8`、`0x1000849a4` 等开头 |
| relay 清理 | 把 `+0xE8` 起的 **3 个槽位清零** | `0x100083e84`（循环 3 次 `str xzr,[x0,#0xe8+8*i]`）|
| 中继失败 | `mfi4Auth_protocol_handle_AuthState(auth, 1)` | `0x100084a88` |
| 链路断开 | 走 iAP2 链路层拆除（`control/R-6.x`），中继层没有独立拆除消息 | 全二进制无 `0x5165/0x5267` 之类 |

**注意**：没有任何"隧道关闭"消息。隧道的生命周期 = 认证会话的生命周期；`0x5503` 也不是关闭，只是信息更新。

## 6.4 安全边界

- **信封本身不加密**：`pack` 直接把 `CFData` 拷进 param1（`0x100067c88` 的 `memcpy`），没有 nonce/tag/长度之外的字段；
- 加密如果存在，只可能在 **MFi / MFi4 认证层**或其上的传输层。线索：`AirPlaySender` 里有 `SecureTunnel-{WaitingForEncryptionCallback, ProcessingEncryptionCallback, …}` 状态机（`0x248b40` 起的字符串），但那不是本镜像，**不作证据**（`OPEN-TUN-10`）；
- 设备侧实现的最低要求：把信封当**不透明字节**处理，不要假设"隧道内已加密"就省掉 MFi 认证。

## 6.5 未确认点

| 编号 | 内容 |
|---|---|
| `OPEN-TUN-6` | 重试上限/超时 |
| `OPEN-TUN-10` | 信封/信道上是否另有加解密层（MFi4 SecureTunnel），其算法与状态 |
