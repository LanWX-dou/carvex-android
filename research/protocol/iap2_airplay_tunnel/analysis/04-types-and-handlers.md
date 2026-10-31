# analysis/04 — type、handler 与能力位图

## 4.1 三个 type

隧道数据带一个 **u8 `type`**（信封 param0），取值范围 **0–2**，双向都检查上界：

| 位置 | 指令 | 日志串 |
|---|---|---|
| 出站 | `0x100084e1c` `cmp w?, #3; b.hs` | `"invalide secureTunnelType (%d)"`（`0x1f1aa2`）|
| 入站 | `0x1000845dc` 之后 `local_35 < 3` | `"no secureTunnelHandler for type %d !!!"`（`0x1f1e57`）|

三个槽位在 `mfi4Auth` 会话 `+0xE8 + 8*type`（`0x100084da8`、`0x10008449c`）。槽位非 0 才允许收发；置位函数：

```text
0x100084ce8  mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler(auth, type):
0x100084d4c      if (type < 3) [auth + 0xE8 + 8*type] = auth;
```

即槽位里放的是**本协议对象自身**（一个"该 type 已归本层处理"的标记），不是函数指针。投递时调用 `(*(*(slot) + 0x10))(slot, endpoint, data)`（`0x1000847c8`），目标方法未解析 → `OPEN-TUN-8`。

## 4.2 `type` 与能力位的对应（已证两条）

`processIncomingMessageRelay` 的协商分支（`0x100083ecc` @`0x1000840e0`–`0x1000844ac`）把 `mask` 的位与"启动哪种 relay"绑在一起：

| 位 | 代码 | 结论 |
|---|---|---|
| bit0 (`0x1`) | `[auth+0x88] |= 1` 后发 `0x5502` | bit0 = 配件信息更新中继（`0x5503` 通道）|
| bit2 (`0x4`) | `[auth+0x88] |= 4` 后 `StartRelayForType(auth, 2)` | bit2 = **type 2** 的 relay（T56）|
| bit1 (`0x2`) | 被 `mask & 0xFFFFFFFFFFFFFFFC` 掩掉，无分支 | 语义未证 → `OPEN-TUN-3` |

`ForceT56RelaySupport`（user default）把 bit2 强置 1，`DisableT56Support` 强清 bit2（`0x100083f9c`–`0x1000840e0` 的 `|= 4` / `&= ~4`）。这两个 default 只影响**调试开关**，不改变线上格式。

**推论（INFERRED）**：type 0/1 分别对应 bit0/bit1 这两类数据（信息更新之外的业务数据），但固件里没有 `StartRelayForType(0/1)` 的调用点，只有 `StartRelayForType(2)`（`0x10008447c`）。因此 type 0/1 的"谁来启动、传什么"属于 `OPEN-TUN-2`。

## 4.3 `StartRelayForType` 只做一层转发

```text
0x100084bd4  mfi4Auth_relay_StartRelayForType(auth, type, out):
0x100084c30      if (type >= 3) → 错误日志，返回 0
0x100084c38      log "%s: secureTunnelType %d"（串 0x1f1a75）
0x100084c40      provider = [auth + 0x140]
0x100084c48      if (provider) return (*(provider+0x10))(provider, *auth, type)
```

- `+0x140` 是"handler 提供者"，其 `+0x10` 是 `startRelay(type)`（未解析目标，`OPEN-TUN-8`）；
- 该函数**不**构造任何消息、不写线上字节——真正发消息的是 `initMessage_..._TypeData`。

## 4.4 `0x5503` 的参数字段

`__mfi4Auth_relay_handle_AccessoryInformationUpdate`（`0x100085034`）遍历 `0x5503` 的参数，按 param ID 落进一个 `NSMutableDictionary`：

| param ID | 键（由日志串与分支顺序命名）| 日志证据 |
|---|---|---|
| 0 | name | `0x100085034` 分支 0 |
| 1 | model | 分支 1 |
| 2 | manufacturer | 分支 2 |
| 3 | serialNumber | 分支 3 |
| 4 | firmwareRevision | 分支 4 |
| `0xF2` | capabilities（u64）| `0x100085034` 的 `0xF2` 比较 |

> 字段名来自**分支顺序**与后续 `"paramID %04X, nmeaSentenceRef = nil!"` 之外的日志；本阶段没有找到把这五个键写进日志的格式串，所以"name/model/manufacturer/serial/firmware"是**按 iAP2 识别信息字段序命名的推断**（`OPEN-TUN-12` 之外的命名问题，见 `A04.3` 的说明）。**线上只要求 param ID 正确，键名不影响互操作。**

`0xF2` 是唯一确定宽度的能力字段：`GetDataAsU64`（`0x100085034` 中 `0xF2` 分支），与 `[auth+0x80]` 的 u64 掩码同型。

## 4.5 handler 注册链（符号级）

```text
mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler  0x1000ff1d0
  └─ mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler                    0x100084ce8   写 +0xE8 槽
       └─ (调用方另有) mfi4Auth_endpoint_setEndpointSecureTunnelDataReceiveTypeHandler 0x1000a93b0
            └─ acc_endpoint2_setEndpointSecureTunnelDataReceiveTypeHandler       0x1000f5cf8
```

这条链只说明"哪一层把 type 登记进来"，不改变线上语义；每一层的实现未逐指令核对（`OPEN-TUN-8` 的延伸）。

## 4.6 未确认点

| 编号 | 内容 |
|---|---|
| `OPEN-TUN-2` | type 0/1 的语义与启动条件（只有 type 2 有 `StartRelayForType` 调用点）|
| `OPEN-TUN-3` | bit1 及掩码其余位 |
| `OPEN-TUN-8` | handler 对象身份、`[slot+0x10]` 目标、`+0x10/+0x18` 字段语义 |
