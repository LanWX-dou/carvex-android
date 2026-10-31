# analysis/15 — `0x4301` 静态字段映射与平台调用

本节把 `_iap2_CarPlayStartSession`（`0x10016d3ac`）的两级跳表、getter 和最终调用逐项对齐。证据基线是 24A446 `accessoryd`，镜像 SHA-256 为
`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`；函数原始字节 SHA-256 为
`7d5db2d7d7b9c2cebd668e773346c3fbba78a4ec697eb1ca6d877fe1eaa98b04`。Ghidra C 只用于阅读控制流，结论以 `.s`/`.bin` 为准。

## 15.1 跳表与嵌套组

外层表位于 `0x100018db8`，相对分支基址 `0x10016d594` 的 9 个有符号小端 `int32` 偏移解出：

| 外层 ID | 分支地址 | 结果 |
|---:|---:|---|
| 0 | `0x10016d5a0` | 组内 ID 0 的字符串重复追加到 `usbIP` 数组 |
| 1 | `0x10016d78c` | 组内 ID 0/1/2/3/4 |
| 2 | `0x10016d674` | `port`，U32 |
| 3 | `0x10016d690` | `deviceID`，字符串 |
| 4 | `0x10016d658` | `pubKey`，字符串 |
| 5 | `0x10016d914` | `srcVer`，字符串 |
| 6 | `0x10016d930` | `sdkVer`，字符串 |
| 7 | `0x10016d6ac` | 组内 ID 0/1（cluster asset） |
| 8 | `0x10016d94c` | `mutualAuth`，Bool |

外层 ID 1 的嵌套表位于 `0x100018ddc`，分支基址为 `0x10016d7c8`：

| 组内 ID | 分支地址 | 结果 |
|---:|---:|---|
| 0 | `0x10016d7d4` | `ssid`，字符串 |
| 1 | `0x10016d884` | `pass`，字符串 |
| 2 | `0x10016d828` | `channel`，U8 |
| 3 | `0x10016d850` | `wifiIP` 字符串重复追加到数组 |
| 4 | `0x10016d7f0` | `securityType`，U8 |

这些不是把 0–13 当作平面参数 ID；它们是 `GetFirstParam(msg,parent)` / `GetNextParam` 建立的外层组与子参数路径。组指针由 `0x100004a04` 的 `mov x0,x26; mov x1,x20` 传入消息和父参数。

## 15.2 getter 的线格式约束

四个 getter 的原始实现给出以下硬约束：

| getter | 总长度 | 取值 | 证据 |
|---|---:|---|---|
| `iAP2MsgGetDataAsU32` | 8 | 值 4 字节，`rev`，即大端 U32 | `0x100067df0`–`0x100067e18` |
| `iAP2MsgGetDataAsU8` | 5 | `param+4` 的 1 字节 | `0x100067e4c`–`0x100067e70` |
| `iAP2MsgGetDataAsBool` | 5 | `param+4` 必须为 0 或 1 | `0x100067e74`–`0x100067e98` |
| `iAP2MsgGetDataAsString` | ≥5 | 值区最后一字节必须为 `0x00`，返回 `param+4` | `0x100067ee4`–`0x100067f2c` |

后续转换调用 `CFStringCreateWithCString(..., 0x08000100)`，因此实现应发送/接收 NUL 结尾的 UTF-8 C 字符串；`pubKey` 的具体编码（PEM、DER 文本或其他）不能由字段名推断。

## 15.3 字段路径、储存槽与调用顺序

`0x10016db58`–`0x10016db74` 把解析结果按平台日志顺序放入寄存器和调用者栈。标量分支重复出现时，代码会再次写同一储存槽；“重复标量取最后一次”是静态行为，但是否被车机接受仍属运行时问题。

| 路径（外层 / 子参数） | 字段 | 线类型 | handler 储存位置 |
|---|---|---|---|
| `0 / 0`（可重复） | `usbIP` | NUL 结尾 UTF-8 字符串，数组 | `sp+0x90` |
| `1 / 3`（可重复） | `wifiIP` | NUL 结尾 UTF-8 字符串，数组 | `sp+0x78` |
| `1 / 0` | `ssid` | NUL 结尾 UTF-8 字符串 | `sp+0x88` |
| `1 / 1` | `pass` | NUL 结尾 UTF-8 字符串 | `sp+0xa0` |
| `1 / 4` | `securityType` | U8（随后以宽 CFNumber 保存） | `sp+0x98` |
| `1 / 2` | `channel` | U8（随后以宽 CFNumber 保存） | `sp+0xa8` |
| `2` | `port` | U32，大端 | `sp+0x80` |
| `3` | `deviceID` | NUL 结尾 UTF-8 字符串 | `sp+0x68` |
| `4` | `pubKey` | NUL 结尾 UTF-8 字符串 | `sp+0x70` |
| `5` | `srcVer` | NUL 结尾 UTF-8 字符串 | `sp+0x60` |
| `6` | `sdkVer` | NUL 结尾 UTF-8 字符串 | `sp+0x50` |
| `7 / 0` | `assetID` | NUL 结尾 UTF-8 字符串 | `x22` |
| `7 / 1` | `assetVer` | U32，大端 | `x21` |
| `8` | `mutualAuth` | Bool，恰好一个 `0x00`/`0x01` | `sp+0x58` |

最终字段顺序由格式串 `0x1001feabc` 和调用点确认：

```text
usbIP, wifiIP, ssid, pass, securityType, channel, port,
deviceID, pubKey, srcVer, sdkVer, assetID, assetVer, mutualAuth
```

调用点 `0x10016db58`–`0x10016db74` 的 `x1`–`x7` 是前 7 个字段，栈 `+0`、`+8`、`+0x10`、`+0x18`、`+0x20`、`+0x28`、`+0x30` 是后 7 个字段。

## 15.4 `x0` 不是 endpoint 指针

旧文档把最终调用描述成“endpoint + 14 个字段”，这是错误的。handler 在 `0x10016da10`–`0x10016da1c` 执行：

```asm
ldr x8, [sp,#0x48]
ldr x0, [x8,#8]
bl  0x1000b3ccc
mov x19, x0
```

`0x1000b3ccc` 的反编译和汇编遍历已连接的 ExternalAccessory，按 primary-endpoint UUID 比较，命中后读取 `EAConnectionID` 的无符号值；找不到则返回 0。平台函数 `0x100063fd0` 随后把 `param_1 & 0xffffffff` 作为 `ACCCarPlay` 的 connection ID，并将 14 个字段装入属性字典。

handler 调用平台函数后忽略其返回值，随后在 `0x10016db7c` 把 handler 返回值设为 1。字段解析失败会走 `0x10016df6c` 的 0 返回路径；当前证据没有显示一个特定的 `0x4301` 错误响应。

## 15.5 证明边界

- `0x4301` 的静态参数路径、宽度、字节序和平台字典键已闭合；实现方可以按 [spec/14](../spec/14-carplay-start-schema.md) 编解码。
- handler 没有“14 字段全部非空”的统一检查；空消息会初始化空数组/空标量并继续走平台调用。平台层是否拒绝缺字段、Wi-Fi/IP 如何发现、以及后续控制/媒体/输入是否成功，仍是 `OPEN-SES-2`。
- 这段代码是设备侧收到车机请求后的平台交接，不等于车机端对端接受，更不等于完整 CarPlay 已建立。
