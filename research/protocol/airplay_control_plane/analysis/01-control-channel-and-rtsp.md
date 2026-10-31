# 01 · 控制通道与 RTSP 帧

> 本章回答覆盖要求 #1（控制通道建立）与 #2（RTSP 消息格式）。
> 证据全部来自 `APTransport`、`CoreUtils` 两个镜像的指令与字符串；涉及运行期/对端接受度的部分标 `OPEN`。

## 1.1 连接对象与状态门

控制通道是一个由 `APTransportConnectionHTTPCreate`（`0x24fdc7034`）创建的连接对象；发送路径在做任何组帧之前先检查状态字：

```text
0x24fda5504  ldr  w8, [x21, #0x6c]     ; conn->state
0x24fda5508  cmp  w8, #5
0x24fda550c  b.ne 0x24fda58b4          ; 非 5 -> 直接返回错误（w24=1）
```

即：**只有状态 5 才允许发请求**（`A01.1`）。状态 5 对应"连接已建立"属推断（`INFERRED`）：同一函数在状态 5 之外还要求 `[conn+0x108]` 非空（`0x24fda5510`），否则也走错误分支。

**端口来源**：本 docset 的三个镜像里没有"7000"字面常量参与控制连接创建；端口随服务发现/SRV 或 `0x4301` 下发（`cs/R-4.10` 的映射仍未闭合）。因此规范只写"端口由发现结果给出"，不写死 7000（`OPEN-AP-1`）。

**TLS**：`APTransportConnectionHTTPCreate` 的构造代码里没有 TLS/SSL/HTTPS 字样；控制面的机密性由应用层 AEAD 提供（见 `04-encrypted-session.md`）。"控制端口是否也可能接受 TLS"无证据（`OPEN-AP-2`）。

## 1.2 请求行

请求行不是由调用方拼字符串，而是由 `HTTPHeader_InitRequestV`（`0x18be4dc0c`）用固定格式串生成：

```text
0x18be4dc58  adrp x8, #0x18bf69000
0x18be4dc5c  add  x8, x8, #0xc87        ; -> 0x18bf69c87  "%s%n %n%V%n %s\r\n"
...
0x18be4dc68  mov  w1, #0x2000            ; 头部区容量 8 KiB
0x18be4dc6c  mov  x2, x8                 ; 格式串
0x18be4dc70  bl   #0x18be383ac           ; VSNPrintF 变体
```

- 格式串 `"%s%n %n%V%n %s\r\n"`（`0x18bf69c87`）中的 `%n` 不产出字节，只把已写长度写回指针，用于记录方法与 URL 在头缓冲中的偏移（`0x18be4dc8c`–`0x18be4dca4` 把这些偏移换算成 `header+0x2030`/`+0x2038` 的指针/长度）；
- 版本串缺省为 `"HTTP/1.1"`（`0x18bf6ab3a`，`0x18be4dc3c` 的 `csel`）；
- `APTransport` 在组请求行时显式传入 `"RTSP/1.0"`（`0x24fe4d357`，调用点 `0x24fda6318`/`0x24fda632c`）。

因此线上请求行的形状是 `方法 SP URL SP 版本 CRLF`（`A01.2`，`INFERRED`：`%V` 是 CoreUtils 的字符串转换扩展，`"%s: %V"`（`0x18bf69cb3`）证明它按字符串输出；但三个占位符与三个实参的**精确对应**没有单条指令可直接读出）。

**8 KiB 上限**：`mov w1,#0x2000` 是头部区容量（`0x18be4dc68`），超长请求行/头会被截断或报错，客户端不应构造超过 8 KiB 的头部区（`A01.3`）。

## 1.3 头字段

发送路径 `httpconnection_sendPackageInternal`（`0x24fda5468`）在请求行之后按固定顺序追加：

| 头 | 生成点 | 值来源 | 条件 |
|---|---|---|---|
| `CSeq: %u` | `0x24fda555c`–`0x24fda5580` | `conn+0x110` 的 32 位计数器，**先取值、后自增** | 总是 |
| `DACP-ID: %llX` | `0x24fda558c`–`0x24fda55a8` | `conn+0x148`（64 位） | `conn+0x150 != 0` |
| `Active-Remote: %u` | `0x24fda55ac`–`0x24fda55c8` | `conn+0x150`（32 位） | 同上 |
| `User-Agent: %s` | `0x24fda55cc`–`0x24fda55ec` | `conn+0x20` 字符串 | 非空 |

字符串常量：`CSeq` `0x24fe4db34`、`%u` `0x24fe4db39`、`DACP-ID` `0x24fe4db3c`、`%llX` `0x24fe4db44`、`Active-Remote` `0x24fe4db49`、`User-Agent` `0x24fe4db57`、`%s` `0x24fe46051`（`A01.4`）。

**`CSeq` 的语义**是"每连接独立、单调递增、从当前值开始用"：`0x24fda555c` 读旧值、`0x24fda5564` 写回 `+1`、`0x24fda5570` 把**旧值**压栈作为格式参数。重连后新连接从新对象开始，不继承旧连接（`A01.5`）。初值是多少、是否回绕，静态代码不给（`OPEN-AP-3`）。

按类型附加的头（都在组帧函数 `0x24fda58ec` 内）：

| 头 | 触发类型 | 格式 | 证据 |
|---|---|---|---|
| `X-Apple-ProtocolVersion: %u` | `stup`（SETUP）与 `info` | `%u` | 反编译 `f_24fda58ec` 第 482 行；类型常量 `0x73747570`/`0x696e666f` |
| `X-Transmit-Date: %s` | `play` | `%s` | 同上第 491 行 |
| `X-Apple-ET: %u` | `fp25`（fairplay setup） | `%u` | 同上第 494 行 |
| `X-Apple-StreamID: %llu` | 包对象第 4 字段非空 | `%llu` | 同上第 499 行 |

`X-Apple-ProtocolVersion` 的字符串常量在 `0x24fe6d592`（`A01.6`）。它的取值语义（版本号本身、是否随 `info` 响应协商）不在本阶段闭合（`OPEN-AP-4`）。

## 1.4 正文与长度

正文长度由 `HTTPMessageSetBody`（`0x18be4da90`）统一写入：

```text
0x18be4db14  adrp x1,#0x18bf69000 / add #0xce1   -> "Content-Length"
0x18be4db20  adrp x2,#0x18bf69000 / add #0xb12   -> "%zu"
0x18be4db28  bl #0x18be4d44c                     ; HTTPHeader_SetField(header, "Content-Length", "%zu", len)
0x18be4db2c  cbz x20, 0x18be4db4c                 ; x20 = contentType
0x18be4db34  ... "Content-Type" 0x18bf69b05
0x18be4db40  ... "%s" 0x18bf7051e
```

结论（`A01.7`）：

- `Content-Length` **总是**写，值为字节数的十进制（`%zu`），不依赖 body 是否存在；
- `Content-Type` **只在调用方给出非空类型时**写，值为原样字符串；
- 没有 `Transfer-Encoding: chunked` 的发送路径证据（发送端只写显式长度）；接收端解析器**接受** chunked（见 1.6）。

## 1.5 响应

响应侧由 `HTTPMessageReadMessageEx`（`0x18be49060`）解析，头字段读取用 `HTTPMessageGetHeaderField`（`0x18be4c03c`，36 字节，仅参数转发）。状态行（`RTSP/1.0 200 OK`）的具体解析路径在本轮未逐指令核对（`OPEN-AP-5`）；已确认的是错误处理的存在：`"### Bad content length: %llu vs %zu"`（`0x18bf69498`，引用点 `0x18be49930`）。

## 1.6 报文边界的解析器约束

`HTTPMessageReadMessageEx` 支持两种正文边界：

| 机制 | 证据 | 约束 |
|---|---|---|
| 显式 `Content-Length` | 同上错误串 | 声明长度与实际可读字节不一致时报错 |
| `Transfer-Encoding: chunked` | `0x18be49458`（`Transfer-Encoding`）/`0x18be494a4`（`chunked`） | 有 chunk 头解析；块长度回绕/超限会报错（`"### Bad chunk wrap: %zu vs %zu"` `0x18bf6950f`、`"### Chunked body too large: %zu vs %zu"` `0x18bf6952e`） |

对客户端的含义：**可以只实现"显式长度"**，但必须能容忍对端返回 chunked（若对端这么做，客户端不能把 chunk 长度行当正文）。`A01.8` 的另一半——"24A446 客户端自己是否发 chunked"——没有证据（`OPEN-AP-6`）。

## 1.7 方法/路径表的存在

组帧函数 `APTransportPackageHTTPGetHTTPMessage`（`0x24fda58ec`，4,000 B）以 **big-endian 4CC** 为键，把内部消息类型映射为 `(方法, URL, Content-Type)`。字符串表在 `0x24fe6d2ca`–`0x24fe6d517`，包含：

```text
SETUP TEARDOWN RECORD SET_PARAMETER GET_PARAMETER FLUSH FLUSHBUFFERED OPTIONS
ANNOUNCE PUT SETMAGICCOOKIE LOUDNESSNORMALIZATION GETANCHOR SETRATE
SETRATEANCHORTIME SETPEERS SETPEERSX
/event /command /info /fp-setup /auth-setup /feedback /pair-add /pair-remove
/pair-list /ensure-pair-pin /pair-pin-start /pair-setup /pair-setup-pin
/pair-verify /configure /peer-list-changed /peer-list-changed-x /audioMode
/action /authorize /playback-info /play /logs /rateandanchortime /stop
```

以及内容类型 `text/parameters`、`application/octet-stream`、`application/x-apple-binary-plist`、`application/x-dmap-tagged`、`application/sdp`、`image/none`、`image/jpeg`、`image/png`。

逐条映射见 `05-rtsp-methods.md`（`A05.x`）。本章只确认：**方法名不是数字 ID，路径也不是由类型直接当数字用**（`A01.9`）。

## 1.8 本章 OPEN

| id | 问题 | 影响 |
|---|---|---|
| `OPEN-AP-1` | 控制端口是否有默认值（7000）或只来自 SRV/`0x4301` | 连接目标 |
| `OPEN-AP-2` | 控制端口是否也接受 TLS | 传输安全模型 |
| `OPEN-AP-3` | `CSeq` 初值与回绕 | 重放/去重 |
| `OPEN-AP-4` | `X-Apple-ProtocolVersion` 的取值与协商 | 版本门控 |
| `OPEN-AP-5` | 响应状态行逐字段解析 | 错误分类 |
| `OPEN-AP-6` | 发送端是否使用 chunked | 互操作 |
| `OPEN-AP-7` | 头字段大小写/顺序是否被对端校验 | 互操作 |
