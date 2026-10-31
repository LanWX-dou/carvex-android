# 22 — 控制报文封装、响应归属与等待边界

基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`PARTIAL`。本章补充 [20](20-airplay-session.md) 的控制链路，讨论选择了 HTTP/RTSP transport 后的本地生产/消费合同，不将它推广到所有 transport 或所有车型。

证据：[control-wire-evidence.json](../evidence/control-wire-evidence.json)。本轮把 17 个函数缓存逐字节与对应 Mach-O 的 VA 区间比较，并直接读取 7 个字符串常量；范围及 SHA-256 均在 JSON 中。没有执行原函数、建立网络连接或取得新的实车捕获。旧分析中的模拟测试只作为定位线索，未当作本轮运行证据。

## 1. 必须分开的四件事

1. **本地构造成功**：方法、URL、header、body 已组成对象。
2. **本地发送/等待完成**：队列接受发送，随后 waiter 被唤醒或超时。
3. **协议响应成功**：响应归于当前事务，status、body 和该方法的字段校验通过。
4. **业务效果成立**：SETUP 后按条件建好事件/视频通道；RECORD 后确实有帧；车机实际显示。

前一层不能直接代替后一层。本章的错误码、对象偏移和内部 4CC 都不是可直接写到线上的 CarPlay 字段。

## 2. 请求方法、URL 与载荷

`_APTransportPackageHTTPGetHTTPMessage @ 0x24fda58ec` 按内部消息类型选择方法、URL 和 MIME，再以 `RTSP/1.0` 初始化请求。以下是连接范围内已重读的分支，**不是每次会话必须依次发送的清单**。[CW02]

| 内部类型 | 线上方法 | 请求目标来源 | 选定 MIME | 范围 |
|---|---|---|---|---|
| `stup` | `SETUP` | package URL / 当前 connection 上下文 | `application/x-apple-binary-plist` | 控制/流 SETUP 的调用者仍须提供正确上下文 |
| `rcrd` | `RECORD` | 同上 | `application/x-apple-binary-plist` | 受 [20](20-airplay-session.md) 的启动条件约束 |
| `tdwn` | `TEARDOWN` | 同上 | `application/x-apple-binary-plist` | 是否有 body 取决于调用者；不等于异常时必能发出 |
| `info` | `GET` | 字面量 `/info` | `application/x-apple-binary-plist` | 不据 GET 方法推断绝对无 body |
| `keep` | `POST` | 字面量 `/feedback` | `application/x-apple-binary-plist` | 周期和启用条件另追生产者 |
| `comm` | `POST` | 字面量 `/command` | `application/x-apple-binary-plist` | 本章不展开触摸或音频命令 |
| `pase` / `psul` | `POST` | `/pair-setup` | 前者 plist、后者 octet-stream | 相同路径不代表相同认证载荷 |
| `pave` | `POST` | `/pair-verify` | `application/octet-stream` | 选择/密码学合同见安全分支，未在本章闭合 |
| `asup` / `mfi ` / `mfim` | `POST` | `/auth-setup` | 前者 plist、后两者 octet-stream | 内部类型不是 SETUP `et` |
| `fp25` | `POST` | `/fp-setup` | `application/octet-stream` | 不证明普通无线 CarPlay 必选此分支 |

发送函数先把 connection `+0x118` 的 URL 放入 package，再构造消息。因此某类请求使用“当前 URL”有直接证据，但该 URL 的完整上游生成、地址编码、首次/重连变更仍未闭合。不能用固定 `/setup`、`/stream` 或固定 session 路径补齐。[CW01/CW02]

### 2.1 Header 字段

| 字段 | 类型/来源 | 存在条件与缺省边界 | 证据 |
|---|---|---|---|
| `CSeq` | 无符号十进制字符串；connection 内部 u32 计数 | 此发送路径写入；使用旧值，随后保存递增值，见 §3 | CW01，原字符串 `CSeq` / `%u` |
| `Content-Length` | 十进制字节数；body 实际长度 | **调用 SetBody 且其主体分配成功时**请求写入，包括长度0；没有调用 SetBody 的请求不能直接套此存在规则 | CW10 |
| `Content-Type` | MIME 字符串 | SetBody 的 MIME 参数非 NULL 才写；方法映射选择了 MIME 不等于一定调用了 SetBody | CW02/CW10 |
| `X-Apple-ProtocolVersion` | `%u`，由 `APSSystemGetUserVersion` 返回 | `stup` / `info` 分支写；provider值域及当前手机缺头差异见 [62](62-version-capability-audit.md)，不无条件写成常量1 | CW02、VH-01/02 |
| `X-Apple-StreamID` | `%llu`，package 中的标识 | 对应槽非零才写，不是 CSeq，也不是视频数据端口 | CW02 |
| `User-Agent` | 当前 connection 的字符串 | 非空时写；值生产者另追，不擅自换成任意 iPhone 身份 | CW01 |
| `DACP-ID` / `Active-Remote` | `%llX` / `%u`，当前对象属性 | 受内部状态条件控制；不是所有无线连接的必填项 | CW01 |

`_APTransportStreamSendPlistMessageCreatingPlistReply @ 0x24fdaf86c` 仅在请求对象非 NULL 时以 `CFPropertyList` format=200 序列化并转为 block buffer。NULL 请求与“空字典编码后的一段 bytes”不同，不可互换。格式化失败、buffer 构造失败和真正发送失败分开返回。[CW03]

## 3. CSeq：旧值上网，不猜首值

关键指令在 `0x24fda555c–0x24fda5580`：[CW01]

```text
old = load_u32(connection + 0x110)
store_u32(connection + 0x110, old + 1)
format_header("CSeq", "%u", old)
```

以上是对原指令的说明，不是可运行的发送器。`w8` 保存旧值，`w9` 加一后写回；varargs 传入的是保存到栈上的旧 `x8`。只看反编译 C 中先出现的递增语句，会误认为 header 使用新值。

- 这一操作为 u32 加法；计数回绕不提供会话身份或防重放保证。
- 本章尚未证明 allocator/构造器为此槽赋的第一个值，不规定首包为0或1。
- 不能以 CSeq 值相同就把两个不同 connection 的消息合并为同一请求；必须同时保存 attempt、connection、方向和方法。
- 不把 socket 重试写入剩余字节、HTTP引擎内部重发、上层再次调用发送器合并为一种“重试”；它们的 header/CSeq 生命周期需要分别审计。

本节更正 [20](20-airplay-session.md) 初稿中“发送前加一”易引起的线上值歧义；原始字节与汇编优先于缺失 varargs 的反编译文本。

## 4. Header 与 body 的边界

### 4.1 发送构造

`HTTPMessageSetBody @ 0x18be4da90`：[CW10]

1. 若 message `+0x2134` 已有错误，直接返回，不重新分配/写 body。
2. 用所给字节长度设置 body storage；失败时保留错误。
3. 源指针非 NULL 且不同于目标 storage 时复制该长度的字节。
4. 请求设置 `Content-Length`（原格式串为 `%zu`）；MIME 非 NULL 时设置 `Content-Type`。

该函数局部主体成功不独立证明后续 header commit、发送队列或网络成功；尤其 header setter 的返回值不能仅凭最终0返回推断都被逐项传播。

`HTTPClientSendMessage @ 0x18be4f198` 在入队前调用 `HTTPHeader_Commit`，再把 header 指针/长度和非空 body 的指针/长度设为 iovec。文本 header 的 commit 追加 `CRLF`，在其后放本地 NUL；长度只增加2，因此这个终止 NUL 不因该操作成为线上 header 的一部分。成功后保存 sealed 状态，第二次 commit 不应解释为再追加一次空行。`$` 开头四字节 interleaved header 有另一分支，不拿它描述普通 RTSP 文本请求。[CW11/CW12]

### 4.2 接收拆包

`HTTPReadHeader @ 0x18be49f60` 在 8192 字节 header buffer 中逐步累计，识别空行边界，再交给 header parser；它保存多读到的字节指针和长度，供后续 body/消息处理。一次 socket read 不是一条响应，header/body 分两次到达不是错误，下一段数据不能被静默丢弃。[CW13]

`HTTPMessageReadMessageEx @ 0x18be49060` 的固定长度内存 body 路径累计到 expected length 才返回完成，否则返回本地继续等待状态 `0x23`。该值不是线上 RTSP status。代码另查 `Transfer-Encoding` 并有 `chunked` 分支；这只证明通用 reader 的分支存在，不证明某辆车必须用 chunked，也未关闭重复/冲突 Content-Length、TE优先级和全部 trailer 合同。[CW14]

8192是此 header scanner 的容量，不是所有 plist/body 的通用上限。另一 file-body 路径出现的1 MiB是 scratch buffer 选择，不应改写为“CarPlay最大控制报文1 MiB”。

## 5. 响应归属与真正成功

### 5.1 不是只看一个 CSeq

发送前 HTTPMessage 保存原 request package（`+0x25e0`）、保留的 connection holder（`+0x25c8`）以及 callback（`+0x25f0`）。`_httpconnection_httpResponseReceived @ 0x24fda4b28` 取回这些对象；只有在 connection 未失效、status为100…599、原request类型为内部 `sync` 的分支中构造 response package并标记 `rply`。缺少sync条件会跳过这一构造分支。[CW01/CW04；`0x24fda4db4–dc0`]

replyToken由setter把高/低32位保存在HTTPMessage `+0x25d0/+0x25d8`，getter重组；`_httppackage_createWithHTTPMessage @ 0x24fda1e78` 的 `0x24fda1efc–1f00` 将这16字节存储复制到回复对象。callback随后复制的groupID是另一关联字段，不是这段replyToken的来源。[CW15/CW16/CW17]

`___stream_handleEventFromConnection_block_invoke @ 0x24fda2b9c` 内的 package接收逻辑在 `rply` 分支比较 package token 与当前 stream，匹配后才保存完成状态/body并 signal waiter。[CW09]

这是**已审范围内的对象关联合同**。不能推导“苹果全栈不检查CSeq”，也不能推导“所有迟到/重连响应一定安全”。底层 HTTP 引擎的分派、连接替换、对象复用、取消排序与更早过滤仍须分别追证。旧分析中仅靠检索未出现 CSeq 就推断全局没有校验的强结论，不被本章采用。

### 5.2 三道不同门槛

| 层 | 已证判据 | 不代表什么 |
|---|---|---|
| response callback | 原 status 满足 `status - 100 < 500`（无符号）走正常 response 分派，即100…599 | 不是200…299成功判据；404也可进入该分支 |
| `GetErrorFromHeader @ 0x24fda6e0c` | 200…299映射为0；其它值返回 `status + 200000` 的本地错误 | 不是改写线上status；不代表body正确 |
| plist wrapper | 调用者请求输出且返回buffer存在时，解码结果必须是dictionary | 无buffer时局部返回0不自动证明SETUP成功；方法消费者仍须校验字段 |

例如 `SETUP 200` + 可解 plist 仍须检查相应响应字段、流数组/type、端口与后续连接，不能直接把 G8/G9/G11 一起标为成功。[CW03/CW04/CW05；20；30]

## 6. 等待、超时与并发归属

`_stream_SendMessageCreatingReply @ 0x24fda68f8` 的局部行为：[CW06/CW07/CW08]

- 发送前检查 stream 是否失效、所选连接是否可用。
- 安排请求的 block 检查 stream `+0xa8` 是否已有 waiter；已有时返回本地错误 `-0x1a35`，不覆盖旧 waiter。这是该 helper 的在途限制，不证明所有 transport API 全局只能一个请求。
- waiter timeout 从 stream `+0xb0` 读取。非零时以秒数乘 `1,000,000,000` 构造 deadline；0分支无限等待。不能把0理解为“立即超时”。
- wait 未正常完成的分支映射为 `-0x1a42`；完成路径否则取保存的状态。仅成功且调用者有输出指针时转移 reply buffer，再清已存槽位；已有 waiter 被释放/清空。
- 返回 `-0x1a42` 时另外调度 stream invalidate。完整跨队列竞态不在本局部复核范围内。

默认值/偏好覆盖的生产者与断开路径见 [24](24-disconnect-reconnect.md)：kind5控制创建点传入10，event创建点使用默认60或已接受偏好；精确属性键为 `PackageSendTimeout`。consumer先交底层connection，只有特定不支持结果才fallback写stream `+0xb0`，具体vtable/底层消费仍有未闭合项。因此不能把创建点参数无条件等同每次waiter的实际deadline，也不能把单请求等待、socket connect、Wi-Fi关联、保活和整个attempt共用一个“60秒”。

## 7. 九问落地合同

| 问题 | 控制请求的有界答案 |
|---|---|
| 进入前状态 | 当前有效控制stream/connection、所需安全上下文、选定方法/URL/body；不以蓝牙bond代替 |
| 发起方/链路 | 此处是手机→车机的控制transport；手机监听邀请/事件入口另分角色 |
| 请求/响应 | 方法/目标/RTSP版本/header/body；响应status/body及本方法字段消费 |
| 字段类型/单位 | §2/§3的文本header与字节长度；§6 timeout是秒，非body/timestamp单位 |
| 固定/动态 | 方法与部分path为字面量；CSeq、URL、stream身份、body及上下文来自当前对象；不复制他车值 |
| 接受/拒绝 | 本章恢复手机发送构造与回复消费者；**车机完整请求接受条件仍需接收侧证据** |
| 成功证据 | 完整消息边界、当前请求关联、状态映射、body/字段校验，再验证下游效果 |
| 超时/重试/清理 | 按owner记录waiter、deadline、取消和invalidate；不能凭重试次数猜故障 |
| 下一事件 | 本方法规定的下一步：SETUP后的条件通道/信息/流协商，RECORD后的帧，TEARDOWN后的清理；无统一“收到200就下一包” |

## 8. 故障定位与未关闭项

| 表象 | 最后成功 | 缺失/失败 | 区分证据 |
|---|---|---|---|
| 一直等响应 | 请求已入队 | 完整header/body或waiter完成 | 实际write字节、read累计、声明length、timeout owner；避免把队列成功当已上网 |
| 收到status后仍卡住 | header可解析 | body未达到长度、解析失败或token不符 | 当前connection/request上下文、body expected/received、wrapper错误 |
| 第二请求失败 | 第一waiter仍在 | helper拒绝已有waiter | stream+waiter身份和生命周期，不伪造车机拒绝 |
| 响应后断开 | status100…599被分派 | 非2xx、本地body/字段消费错误或timeout | 分别记录线上status与本地error域、首个错误与invalidate顺序 |
| 重连响应串线 | 新连接已创建 | 旧请求/回调被错误关联 | 新旧connection/stream/token/attempt分离；CSeq不能单独区分 |

仍 OPEN：完整 URL 生产者、首个 CSeq 的初始化与所有重连/重试路径、底层响应CSeq校验、所有header冲突/类型异常、各安全载荷的完整线格式、请求默认预算覆盖范围、取消与迟到响应全链，以及目标车机的真实接受/显示结果。
