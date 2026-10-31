# 06 · SETUP 与流参数

> 覆盖要求 #7（`SETUP` 的 `streams`/`type` 参数）。键名和有限类型分派已核，
> 字段适用条件/完整协商及 `type=130` 是否隧道仍需证据。

## 6.1 方法侧（已闭合）

| 项 | 值 | 证据 |
|---|---|---|
| 4CC | `stup` | `0x24fda5e38`（`cmp w21,0x73747570`） |
| 方法 | `SETUP` | `0x24fda6190` → `0x24fe6d2ca` |
| 路径 | 包内 URL（由 `APTransportPackageHTTPSetURL` 写入） | `0x24fda6300` 处取 URL |
| Content-Type | `application/x-apple-binary-plist` | 目标块 `x22` 赋值 |
| 附加头 | `X-Apple-ProtocolVersion: %u` | 反编译 `f_24fda58ec` 第 482 行 |
| 附带头（有流 ID 时） | `X-Apple-StreamID: %llu` | 同上第 499 行 |

`A06.1`：`SETUP` 的 body 是 **binary plist**，不是 TLV；这一点与 `/pair-setup` 相反。
`A06.2`：`X-Apple-ProtocolVersion` 只对 `stup` 和 `info` 加，说明它是"会话级能力声明"而非每请求都带。

## 6.2 流描述符（部分）

`APSenderSessionCreateStreamDescriptor`（`0x251ab1780`，`AirPlaySender`）创建单个流的描述字典：

```text
0x251ab17ac  adrp x8,#0x2680d3000 ; ldr x8,[x8,#0x150]  ; 取全局字典/池
0x251ab17d8  mov  w2, w23                                ; 流类型
0x251ab17e0  add  x1, x1, #0xb30                         ; 键（CFString 常量，见 0x27612fb30）
0x251ab17f8  mov  x2, x20                                ; 第三入参的整数值（streamID）
```

`A06.3`：常量 `0x27612fb30`、`0x276132150` 后续已解码为 `type`、`streamID`（`A12.1`）。
stub `0x25810a790` 为 `_CFDictionarySetInt64`，所以第二值不是附加字典。
第一入参 type 为0时，`0x251ab179c` 跳到 NULL 输出并成功返回；非零时写 type，
仅第二入参低32位非零（`0x251ab17e8`）才把第三入参写为 streamID。
该内部构造器的可选字段不能扩写成所有线上消息都必须/都不需要 streamID。
stub 来源为 `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`；函数与原字节回归见 C12。

## 6.3 `streams` 数组与 `type` 字段

AirPlay 的 `SETUP` body 里 `streams` 是一个数组，每个元素至少含 `type`（整数）与端口/控制参数。
第 1 轮没有定位到 `type` 的写入点；第 2 批补入 `apsession_setupStreamCreatingResponseInternal`（`0x2519bbf24`）
后，`type` 的比较链与键名已在 `12` 章解出（`A12.2`、`A12.4`）：

- 键名就是 `type`（`0x251bf5fb9`），另有 `streamID`、`controlPort`、`dataPort` 等 19 个键；
- `type` 的已核分派链处理 96/100/101/102/103/106/107/110/111/120/130；112 进入错误分支，不能把比较边界当合法值（见 `12.4` 完整分组筛选）；
- `0x82`（130）与 `0x78`（120）同跳 `0x2519bd120`，该分支不创建 cryptor（`A12.5`）。

`A06.4`（保留）：`type=130` **是否等于"走 iAP2 隧道"**仍不能从现有证据推出——只能确认它是 SDK 认识的合法
流类型值。该语义问题转为 `OPEN-AP-41`。

## 6.4 OPEN

| id | 问题 | 下一步 |
|---|---|---|
| `OPEN-AP-25` | `type` 取值表与 `130`（部分闭合：枚举已知，语义未定） | 见 `OPEN-AP-41` |
| `OPEN-AP-26` | 每流的端口/加密参数如何协商 | 键名已知（`A12.2`），协商顺序未读 |
| `OPEN-AP-41` | 已核 type 分支的业务语义、完整类型表 | 调用方逐指令 + 抓包 |
