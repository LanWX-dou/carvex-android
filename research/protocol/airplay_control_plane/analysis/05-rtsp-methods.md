# 05 · RTSP 方法集与 4CC 映射

> 覆盖要求 #6。核心证据是 `APTransportPackageHTTPGetHTTPMessage`（`0x24fda58ec`，4,000 B）里的
> 一个大开关：以 **big-endian 4CC** 为键，决定 `(方法, 路径, Content-Type)`。

## 5.1 机制

- 键来自包对象的 `[plVar3+8]`（32 位），比较用 `mov/movk` 拼立即数后 `cmp w21, w8`；
  例如 `0x24fda5e30: mov w9,#0x7570 / 0x24fda5e34: movk w9,#0x7374,lsl#16` = `0x73747570` = `"stup"`。
- 立即数按 **大端 4CC** 解读：`0x73747570` = `s t u p`（`s`=0x73 在高字节）。
- 命中后写入三个寄存器：`x23`=方法串、`x24`=路径串（部分类型由包对象自带的 URL 提供，`0x24fda6300` 处取）、`x22`=Content-Type 串。
- 未命中走 `0x24fda679c`：记日志并返回错误，不发出任何请求（`A05.1`）。

## 5.2 映射表

「抽检」列：`✓` = 已在汇编里核对到 `cmp` 立即数 + 目标块字符串（`stup` `0x24fda5e38`→`0x24fe6d2ca`；
`pave` `0x24fda5cac`→`0x24fe6d412`；`flsh` `0x24fda5d7c`→`0x24fe6d322`；`info` `0x24fda5cdc`→`GET /info`）；
空白 = 反编译开关体读数，未逐条指令核对（`OPEN-AP-8`）。

| 4CC | 方法 | 路径 | Content-Type | cmp 地址 | 抽检 |
|---|---|---|---|---|---|
| `info` | `GET` | `/info` | — | `0x24fda5cdc` | ✓ |
| `stup` | `SETUP` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5e38` | ✓ |
| `ssdp` | `SETUP` | 包内 URL | — | `0x24fda5eec` | |
| `rcrd` | `RECORD` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5f58` | ✓ |
| `tdwn` | `TEARDOWN` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5c24` | |
| `tsdp` | `TEARDOWN` | 包内 URL | — | `0x24fda5fc4` | |
| `flsh` | `FLUSH` | 包内 URL | — | `0x24fda5d7c` | ✓ |
| `fshb` | `FLUSHBUFFERED` | 包内 URL | `application/x-apple-binary-plist` | — | |
| `sepe` | `SETPEERS` | `/peer-list-changed` | — | `0x24fda5d2c` | |
| `sepx` | `SETPEERSX` | `/peer-list-changed-x` | — | — | |
| `strt` | `SETRATE` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5e28` | |
| `srat` | `SETRATEANCHORTIME` | 包内 URL | `application/x-apple-binary-plist` | — | |
| `anch` | `GETANCHOR` | 包内 URL | `application/x-apple-binary-plist` | — | |
| `annc` | `ANNOUNCE` | 包内 URL | `application/sdp` | `0x24fda59b0` | |
| `pnfo` | `GET` | `/playback-info` | — | `0x24fda5a20` | |
| `play` | `POST` | `/play` | `application/x-apple-binary-plist` | — | |
| `stop` | `POST` | `/stop` | — | — | |
| `comm` | `POST` | `/command` | `application/x-apple-binary-plist` | — | |
| `actn` | `POST` | `/action` | `application/x-apple-binary-plist` | `0x24fda5c54` | |
| `conf` | `POST` | `/configure` | `application/x-apple-binary-plist` | `0x24fda5d64` | |
| `keep` | `POST` | `/feedback` | `application/x-apple-binary-plist` | — | |
| `pave` | `POST` | `/pair-verify` | `application/octet-stream` | `0x24fda5cac` | ✓ |
| `psul` | `POST` | `/pair-setup` | `application/octet-stream` | `0x24fda5db8` | |
| `pspl` | `POST` | `/pair-setup-pin` | `application/x-apple-binary-plist` | `0x24fda5da8` | |
| `ppst` | `POST` | `/pair-pin-start` | — | `0x24fda5e84` | |
| `paut` | `POST` | `/authorize` | `text/parameters` | `0x24fda5c9c` | |
| `paap` | `POST` | `/pair-add` | `application/x-apple-binary-plist` | `0x24fda5bd4` | |
| `parp` | `POST` | `/pair-remove` | `application/x-apple-binary-plist` | `0x24fda5f94` | |
| `espp` | `POST` | `/ensure-pair-pin` | — | `0x24fda5d74` | |
| `mfi ` | `POST` | `/auth-setup` | `application/octet-stream` | `0x24fda5de8` | |
| `mfim` | `POST` | `/auth-setup` | `application/octet-stream` | `0x24fda5df8` | |
| `fp25` | `POST` | `/fp-setup` | `application/octet-stream` | `0x24fda5b40` | |
| `asup` | `POST` | `/auth-setup` | `application/x-apple-binary-plist` | — | |
| `auth` | `OPTIONS` | `*` | — | `0x24fda5e54` | |
| `lkee` | `OPTIONS` | `*` | — | `0x24fda5a80` | |
| `sppr` | `PUT` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5ae8` | |
| `loud` | `LOUDNESSNORMALIZATION` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5eb4` | |
| `magc` | `SETMAGICCOOKIE` | 包内 URL | `application/x-apple-binary-plist` | — | |
| `gvol`/`svol`/`prog` | `GET_PARAMETER`/`SET_PARAMETER` | 包内 URL | `text/parameters` | — | |
| `text` | `SET_PARAMETER` | 包内 URL | `application/x-dmap-tagged` | — | |
| `jpeg`/`png `/`none` | `SET_PARAMETER` | 包内 URL | `image/jpeg`/`image/png`/`image/none` | `0x24fda5cec` | |
| `seek` | `POST` | 包内 URL | `application/x-apple-binary-plist` | `0x24fda5d1c` | |

「包内 URL」= 路径不来自开关，而由 `APTransportPackageHTTPSetURL`（`0x24fda6c70`）事先写入包对象，
开关只决定方法与类型（`0x24fda6300` 处的 `func_0x0002500eeae0(*plVar3,&local_f8)` 取出该 URL）。

## 5.3 客户端必须实现的最小集

按本阶段目标（连上车机并推进到 `SETUP`/`type=130` 交接），客户端至少要能发：

1. `GET /info`（读能力）；
2. `POST /pair-setup`、`POST /pair-verify`（见 02/03 章）；
3. `POST /fp-setup`（FairPlay，`X-Apple-ET`）；
4. `SETUP`（含 `streams`，见 06 章）；
5. `RECORD`（启动）；
6. `TEARDOWN` / `FLUSH`（收尾）；
7. `POST /feedback`（保活/统计，可选）。

`SETUP` 的 URL 是「包内 URL」，因此**不能**硬编码为 `/stream` 之外的某值——真实路径由实现决定，
对端按 URL 匹配（`OPEN-AP-9`：车机是否要求固定 URL）。

## 5.4 与头字段的联动

`0x24fda58ec` 在方法/路径确定后追加：

| 条件 | 头 |
|---|---|
| 类型为 `stup` 或 `info` | `X-Apple-ProtocolVersion: %u`（`0x24fda647e` 区） |
| 类型为 `play` | `X-Transmit-Date: %s` |
| 类型为 `fp25` | `X-Apple-ET: %u` |
| 包对象第 4 字段非空 | `X-Apple-StreamID: %llu` |

`A05.2`：`X-Apple-StreamID` 是**按流**加的头，不是全局头；`SETUP` 之前没有流 ID，因此该头在 `SETUP` 请求里不会出现（推断，依据是 `plVar3[4]` 在流创建后才被写入，见 06 章）。

## 5.5 OPEN

| id | 问题 |
|---|---|
| `OPEN-AP-8` | 表中未抽检行需逐条核对（尤其 `sepe/sepx`、`fshb`、`srat`、`comm`） |
| `OPEN-AP-9` | `SETUP` 的 URL 是否必须为固定值（对端匹配规则） |
| `OPEN-AP-10` | `GET_PARAMETER`/`SET_PARAMETER` 的 `text/parameters` 具体键名 |
| `OPEN-AP-11` | 未命中 4CC 时的错误码（`0x24fda679c` 返回的 OSStatus） |
