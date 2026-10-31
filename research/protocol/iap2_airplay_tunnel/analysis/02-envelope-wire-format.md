# analysis/02 — 信封线格式（`0x5500`/`0x5501`/`0x5502`/`0x5503`）

四个 ID 共用一个消息外壳：`40 40 | len(2,BE) | msgID(2,BE) | params`（`control/R-3.1`）。差别只在参数区。

## 2.1 打包函数

`_mfi4Auth_util_packIntoTunnelDataiAP2Msg(type, data, flag)` @`0x100022264`：

```text
0x1000222b8  mov  w0, #0xffff        ; 消息缓冲上限 65535
0x1000222d4  mov  w8, #0x5500        ; flag==0 → 0x5500
0x1000222e0  mov  w3, #0xffff        ; 缓冲长度
...
0x1000222f0  bl   iAP2MsgAddU8Param(msg, 0, 0, type)      ; param0 = type
0x1000222fc  bl   iAP2MsgAddDataParam(msg, 0, 1, data, len) ; param1 = 整块数据
```

- `flag != 0` 时 ID 取 `0x5501`（`0x1000222d8` 附近的选择）；
- **本构建唯一调用点**（`0x100084ef4`）传 `flag=0`，所以设备只会发出 `0x5500`。

## 2.2 线路布局

### `0x5500`（设备 → 车机，隧道数据）

| 偏移 | 宽度 | 值 | 说明 |
|---|---|---|---|
| 0 | 2 | `40 40` | SOM |
| 2 | 2 | `15 + n`（BE）| 总长 = 6 + 5 + (4+n) |
| 4 | 2 | `55 00` | msgID |
| 6 | 2 | `00 05` | param0 长度 = 5 |
| 8 | 2 | `00 00` | param0 ID = 0 |
| 10 | 1 | `t` | **type**，0–2 |
| 11 | 2 | `4 + n`（BE）| param1 长度（含 4 字节头）|
| 13 | 2 | `00 01` | param1 ID = 1 |
| 15 | n | data | 隧道数据（原始字节，不解释）|

### `0x5501`（车机 → 设备，隧道数据）

结构同上，仅 msgID 为 `55 01`。解析器对 param 的遍历是**通用**的：

```text
0x1000224a4  bl  iAP2MsgGetFirstParam(msg, 0)
0x1000224b8  loop:
0x1000224c4      id = iAP2MsgGetParamID(p)
0x1000224c8      if (id == 1) { data = GetDataAsData(p); len = GetParamValueLen(p); CFDataCreate(...) }
0x1000224d4      if (id == 0) { type = GetDataAsU8(p) }
0x1000224e4      p = iAP2MsgGetNextParam(msg, 0, p)
```

**关键行为（负结论）**：`id==1` 出现多次时，代码先 `CFRelease` 旧值再建新值，日志是 `"Already have unpackedMessage %ld bytes !!!, release and create new one"`（串 `0x1da562`）。即**后出现的 param1 覆盖前一个，不拼接**。所以信封层没有"多片重组"语义（`A07.1`）。

### `0x5502`（设备 → 车机，请求配件信息）

无参数，总长 6：`40 40 00 06 55 02`（`0x100084acc`：`iAP2MsgInit(msg, 0x5502, buf, 0xffff, 0, 0)`）。

### `0x5503`（车机 → 设备，配件信息更新）

不是"信封+数据"，而是**信息更新消息本身**：param 直接挂在 `0x5503` 下。

| param ID | 类型 | 内容 | 指令依据 |
|---|---|---|---|
| 0 | 字符串 | 名称（name）| `0x100085034` 分支表 |
| 1 | 字符串 | 型号（model）|
| 2 | 字符串 | 厂商（manufacturer）|
| 3 | 字符串 | 序列号（serial number）|
| 4 | 字符串 | 固件版本（firmware revision）|
| `0xF2` | u64 | 能力位图（capabilities）|

`unpack` 对 `0x5503` 的处理是"把**整条消息**（从 `msg+0x18` 起、长度 `GetMsgLen`）变成 `CFData` 返回"：

```text
0x100022440  mov  w8, #0x5503
0x100022448  ldr  x10, [x7, #0x18]        ; buf = 消息起点
0x10002244c  bl   iAP2MsgGetMsgLen
0x100022458  bl   CFDataCreate(alloc, buf, len)
```

调用方（`0x10008449c` @`0x100084704`）拿到 `msgID==0x5503` 后，再把这段 `CFData` 当消息重新解析，交给 `__mfi4Auth_relay_handle_AccessoryInformationUpdate`（`0x100085034`）。

> **注意**：`msg+0x18` 是消息缓冲区**起点**（`control/A03.x`：`[msg+0x18]=buf`，`GetMsgLen = rev16(buf[2])`），所以 `CFData` 含 `40 40` 头，长度是整条消息。这一点决定了"内层消息必须以 `40 40` 开头"，否则重解析失败（错误串 `"failed to parse AccessoryInformationUpdate message!!!"`，`0x1f1f1f`）。

## 2.3 长度与容量

| 项 | 值 | 依据 |
|---|---|---|
| 消息缓冲上限 | `0xFFFF` | `0x1000222b8`、`0x100084b0c` |
| 解析缓冲 | `0x1001F`（65,567）| `0x100022398` `calloc(1,0x1001f)` |
| 参数长度字段 | 16 位 | `control/R-3.3` |
| 单条内层信封最大 data | `0xFFFF − 15 = 65,520` | 6 头 + 5 param0 + 4 param1 头 |
| 包进 `0x5164` 的未加密 relay 最大 data | `0xFFFF − 25 = 65,510` | 外层再增加 6 头 + 4 param0 头 |
| 包进 MFi4 安全 relay 的保守最大 data | `65,510 − 16 = 65,494` | `ccsigma` 给外层 payload 增加 16 字节，最终仍受链路 MTU 限制 |
| 超限行为 | `iAP2MsgAddDataParam` 返回 0，打包失败 | `0x100067c8c`–`0x100067c9c` 越界即 `x22=0` |

`iAP2MsgAddDataParam` 的越界判定（`0x100067c80`–`0x100067c9c`）：

```text
w8 = len + 4
x9 = [msg+0x18]        ; 缓冲起点
x21 = [msg+0x20]       ; 写游标
x10 = x21 + w8
x9  = x10 - x9
w10 = [msg+0x10]       ; 缓冲上限
cmp x9, x10 ; csel x22, xzr, x21, gt   ; 超限 → 返回 0
```

## 2.4 空参数与缺参数

- `0x5501` 可以完全没有 param1：此时 `unpack` 返回 0，调用方走"无载荷"分支，日志 `"Has no payload !!!, retry after %d ms"`（`0x1f1c7c`），并在 `usleep(1000)` 后发 `0x5502` 重新请求（`0x10008449c` @`0x1000845e8`–`0x100084600`）；
- `0x5501` 缺 param0 时 `type` 保持初值 0（`0x1000224d4` 前的 `local_d0=0`）；
- 参数长度为 4 的"空值参数"是合法 TLV（`control/A03.8`），本阶段沿用该规则，不特判。

## 2.5 示例（构造，非抓包）

`type=2`、data=`de ad be ef`：

```text
40 40 00 13 55 00 00 05 00 00 02 00 08 00 01 de ad be ef
```

（总长 0x13 = 19 = 6+5+8。）

`0x5503` 全空（只有头）：

```text
40 40 00 06 55 03
```

这两个向量在 `reference-impl/test_vectors.json` 里，并由 `verify.py` C9 复算。

## 2.6 未确认点

| 编号 | 内容 |
|---|---|
| `OPEN-TUN-1` | 车机收到 `0x5500` 后的解析（无对端固件）|
| `OPEN-TUN-9` | `0x5501` 出现多个 param1 时对端是否真的只发一个（本侧是覆盖语义）|
