# 27 — 控制 SETUP 响应、信息完成状态与会话 URL 分支

日期：2026-10-29。目标：iPhone18,1 / iOS 27.0.1 / 24A446。本章为新增有界静态复核，不代表全 AirPlay/SETUP、认证或实车连接已完成。没有执行苹果原函数；只读固件、缓存和手机代码。

证据：[setup-response-branches.json](../evidence/setup-response-branches.json)。[只读复核器](../tools/inspect_setup_response_branches.py)重新读取3个原镜像、20个完整函数范围，与原 dyld 字节逐一比较，并检查现存缓存片段；另重新解析响应键、endpoint vtable、整数扫描分派和内核 socket API 符号。完整字节来源验证不等于全部函数语义覆盖。

## 1. 本轮修正的关键理解

1. `skipRecord`不是每个响应重新赋值的普通 Boolean：getter结果非零只会置位；缺失/零不清除同一 session 已置位的状态。
2. 是否省略独立 GET `/info`，取决于信息是否**成功消费并设置完成位**，不只是看到一个名为`info`的键。已核 AirPlayDescription 实现接受空字典；不能额外要求字典必须含`displays`。
3. `eventPort`读取失败不会令这层 SETUP 失败，也不是该 helper 主动清零输出：它保留调用者输出原值，清掉读取错误。已审 Stage1 先把输出初始化为0，因此本路径最终省略事件连接。
4. 原 session URL 生产点使用**已连接 socket 的对端地址**，不是本地地址或`InetAddress.toString()`。该点的 IPv6 格式化实际不含 scope、端口或方括号；不得把通用 URI 规范当成已证实苹果线上格式。

## 2. 控制 SETUP 请求与响应顺序

原函数`_apsession_requestControlSetupWithResponse@0x251a59338`：

| 条件 | 结果 | 原定位 |
|---|---|---|
| 无 control stream | 返回错误，不构造请求 | `0x251a59384–388 → 0x251a596c8` |
| 请求字典分配或append失败 | 退出并清理，不发送 | `0x251a593ac–3f0`及冷出口 |
| 初始/更新参数 | `updateSessionRequest`写false/true，均用同一个helper | `0x251a593b8–3dc` |
| 发送/等待失败 | 原错误退出，不处理响应字段 | `0x251a59460–478 → 0x251a596fc` |
| 发送成功 | 先处理内嵌info，再处理skipRecord，然后交出响应 | `0x251a594e0–67c` |

此函数只调用一次`stup`发送，没有`/setup`或`/`重试。已审路由函数`APTransport@0x24fda58ec`使用调用者 URL。这个局部无回退事实不等于证明所有上层都没有其他 transport 重试；本项目自定义 URL fallback 不能因此标成苹果标准。

## 3. 内嵌 info：类型门、消费、GET guard

### 3.1 SETUP本层

`0x251a594e0–508`使用`CFDictionaryGetTypedValue`，期望CFDictionary，error指针为NULL。原键指针链`0x268104150 → 0x268a95be8 → 0x273d53220`解出`info`。

| 输入 | 本层行为 |
|---|---|
| 没有info / info不是字典 | getter返回NULL；不调用信息处理器，继续SETUP |
| info为字典（含空字典） | 调`processGetInfoResponse(session, protected=1, displayFlag, info)` |
| 信息处理器失败 | 只记日志；仍处理skipRecord，SETUP请求helper最终可返回成功 |
| 信息处理器成功 | protected-info完成位可置1，后续按该位判断是否需要GET |

不能把内嵌信息失败等同整个SETUP立刻失败，也不能在失败后标记信息已完成。

### 3.2 消费者与完成位

`_apsession_processGetInfoResponse@0x251a5a840`先要求control存在，处理身份一致性和可选display capabilities，再调用endpoint虚表的`class+0x20`更新函数；该调用失败不置完成位。成功后`0x251a5adc4–dd0`按protected参数置`session+0x85`或public的`+0x84`。

本轮进一步从原 dyld v5 指针解析：

- AirPlayDescription vtable`0x2761280c0`的class指针槽`0x2761280d0 → 0x276128138`。
- class的`+0x20`槽`0x276128158 → _airPlayDescription_SetEndpointInfo@0x251afe62c`。
- 此实现的根参数NULL/非字典检查在`0x251afe6d0–6e8`，返回`0xfffee7b9`。
- 字典进入保存/更新；内部部分字段、音频格式、广告信息转换错误可记录并汇入cleanup；正常字典路径最终`0x251afeee0`设置`w0=0`。

因此在这个具体endpoint实现中，空字典不是缺必填字段失败，内部某个可选字段错误也不必然传为整个info处理失败。此结论没有宣称所有endpoint类的同槽行为相同，也没有把所有内部副作用复刻到Android。

Stage2`0x2519c6b78/6b88`读`+0x85`；已完成则跳过ensure-protected-info获取，未完成则调用`_apsession_fetchInfo(..., protected=1, txtAirPlay=0, displayFlag, ...)`。独立GET失败会沿Stage2错误清理；与SETUP内嵌处理“错误只日志”不同。

`disconnectControlStream@0x251a56e44`明确清`+0x85/+0x81/+0x83`并释放相关对象；不在此处清public-info `+0x84`。不能把这些内存偏移当线上字段。

## 4. skipRecord与Started

原键指针链`0x268104158 → 0x268a95bf0 → 0x273d53260`解出`skipRecord`。读取处`0x251a5960c–624`调用`CFDictionaryGetInt64(..., error=NULL)`；非零才在锁内`0x251a5965c`写`session+0xdd=1`。不存在零值写回分支。

| 已有skip位 | 本次getter结果 | 后续skip位 |
|---|---|---|
| 0 | 0（包括missing返回0） | 0 |
| 0 | 非零 | 1 |
| 1 | 0/missing | 1 |
| 1 | 非零 | 1 |

初始/更新SETUP共用helper，因此不能让后续缺键更新清除skip位。成功消费info与skip位是不同状态。

Stage2先读取Started`+0xda`和skip`+0xdd`：已经Started不重复启动；未Started且skip为0才发送RECORD；skip为1无需发RECORD也会置Started。RECORD返回错误不置Started。定位：`0x2519c6b24–644`、该函数`apsession_ensureSessionStarted`展开段及`0x2519c763c`后锁内置位。

`disconnectControlStream`未直接清`+0xdd`。搜索缓存得到的另一`+0xdd`写入属于`carEndpoint_updateVideoPlaybackAllowed`的不同对象，不能误判为session清理。session全部构造/销毁/复用入口仍OPEN；Android每个AirSession新建本地状态是实现生命周期设计，不是已经证明原对象复用规则。

## 5. CF数值转换不是只接受Number

`CFDictionaryGetInt64@0x18be373d8`缺字典/缺键返回0并在有error指针时写`-0x1a47`；有值进入`CFGetInt64@0x18be37434`。本轮复核该转换全部类型分派及原汇编：

| CF值类型 | 已核行为 | 限制 |
|---|---|---|
| 整数CFNumber | CFNumberGetValue(type4)写64位槽，调用返回值未检查 | 不宣称任意超大/unsigned CFNumber完全等价于JVM Long |
| 浮点CFNumber | 范围内FCVTZS向0截断；超范围饱和到MIN/MAX并置`-0x1a36` | NaN经过无序比较分支进入FCVTZS，得到0且本函数status=0；不是实际原函数执行结果 |
| CFBoolean | 真1、假0 | 与字符串独立分支 |
| CFString | 转128字节MacRoman C缓冲；不区分大小写识别true/yes/y/on/1及false/no/n/off/0，否则`SNScanF("%lli")` | 下节补齐此格式的进制/溢出/尾随；所有非ASCII字符转换仍未闭合，不能假定Java strict decimal等价 |
| CFData | 长度0..8；按大端累积64位；长度>8错误 | 8字节高位保留，非“最多signed正数” |
| CFDate | CFAbsoluteTime经FCVTZS | 日期表示/NaN边界未做运行验证 |
| CFNull | 0成功 | 不同于缺键的missing状态 |
| 其他类型（数组/字典等） | 0，type错误`-0x1a64` | skipRecord因无error指针只看到0 |

`skipRecord`忽略错误，故浮点溢出返回的非零饱和值仍置skip；eventPort的调用者检查error，不能共用“非零就是成功”的判断。手机若仅实现有限类型，应明确本地支持边界而不是声称CF全等价。

### 5.1 `%lli`实际扫描规则

`SNScanF@0x18be41338`转调`VSNScanF@0x18be41994`。本轮从原函数直接反汇编，而非套用标准C库假设；原跳表槽`0x18be42708`的`i`条目指向`0x18be41cb4`（自动进制模式）。`ll`在格式解析中成为`0x4c`长度标记，最后`0x18be4220c`执行64位存储。

- 跳过前导空白，允许可选正负号。
- `0x/0X`后存在十六进制数字时选16进制（`0x18be41ef8–f28`）。
- `0b/0B`后存在0或1时选2进制（`0x18be41f2c–f6c`）。这不是可省略的分支。
- **只有**开头0且第二字节为0..7，才跳过首个0并选8进制（`0x18be41f70–fb0`）；否则10进制。所以`08→8`、`09→9`，不是0；`078→7`则停在8。
- 遇到非当前进制数字就停，有已消费数字即成功，不要求吃完整文本；例如`12tail→12`。无有效数字不产生一次成功转换。
- 64位累积是`mul`/`add`（`0x18be42150–154`），没有overflow错误分支；按2^64自然回绕，最后可选取负并写64位（`0x18be42178–180`、`0x18be4220c`）。例如十进制`18446744073709551616→0`、`18446744073709551617→1`；不是饱和也不是严格拒绝。

上述只闭合CFGetInt64实际使用的`%lli`及ASCII数字路径，不是对VSNScanF全部格式的完成声明。若实现使用LongOrNull而拒绝超范围文本，便仍与这个原路径不同。

## 6. eventPort、keepAlivePort与enabledFeatures

`ensureControlStreamSetup@0x251b5cfe0`首先检查`session+0x81`；已经setup则返回，不重新发初始SETUP。

| 字段/条件 | 行为 | 定位 |
|---|---|---|
| eventPort读取成功 | 将getter64位返回的低32位写到调用者int | `0x251b5d0a4–0c4` |
| eventPort缺失/读取错误 | 不写输出，清error继续 | `0x251b5d0bc–0c8` |
| keepAlivePort | 同上，独立输出和错误清理 | `0x251b5d0cc–0ec` |
| kind!=5 | 不走本处enabledFeatures检查 | `0x251b5d1c0–1c8` |
| kind5，enabledFeatures缺键 | 仅missing错误`-0x1a47`清掉继续 | `0x251b5d1e8–1fc` |
| kind5，enabledFeatures为数组 | 保留数组；此处不逐元素校验 | `0x251b5d1cc–20c` |
| kind5，enabledFeatures类型错误 | 错误退出，不写setup完成位 | `0x251b5d200 → 2d0` |
| uiPreloaded读取错误 | 不写stats，清error继续 | `0x251b5d210–268` |
| 所有阻断检查成功 | setup完成位`+0x81=1` | `0x251b5d26c–270` |

Stage1`0x2519c5888`以64位零同时初始化两个port int槽；`0x2519c61b0–1c8`传它们给helper，`0x2519c62c8–2d0`把event输出传给event creator。因此这个调用路径缺失或坏类型端口会保持0。

`ensureEventStreamCreated@0x251a5dec0`参数0直接成功退出，不创建event stream；非零才获取transport/key context并尝试事件连接。原本处没有1..65535保护：超范围值可先截为32位。Android为避免socket目标别名/非法端口而拒绝超范围非零值属于本地边界保护，不冒充苹果该getter的限制。

## 7. 单流SETUP回复

`setupStreamCreatingResponseInternal@0x2519bbf24`在控制事务成功后先检查取消，然后要求：

1. `streams`为CFArray；类型错误/缺失失败。
2. 数组元素数恰好1；0或2以上失败。
3. 唯一元素为CFDictionary；否则失败。
4. `type`经CFDictionaryGetInt64成功取得，低32位与请求内部type比较；不匹配失败。
5. `streamID`读取错误在指定模式可从当前注册表生成；其它模式并非一律硬失败，随后清error。

上述为原C约405–469行及邻接汇编复核；不能把“随便找第一个type匹配元素”当同样处理。本函数后段还有transport/cryptor/dataPort消费，本轮没有补齐所有数据端口消费者、模式选择或密钥生命周期。Android额外防止宽整数截断伪装type，是本地防护差异，应单列。

## 8. URL地址角色、IPv6格式和fallback边界

`httpconnection_handleConnectionEstablished@0x24fdc8e50`：

- `0x24fdc8fc8`调用stub`0x2500b5dd0 → pointer0x271bf4d80 → 0x237f019a0`，写connection`+0x88`。
- `0x24fdc8fe0`调用stub`0x2500b7b10 → pointer0x271bf4d78 → 0x237f06a1c`，写connection`+0xa4`。
- 原dyld imagesText及libsystem_kernel LC_SYMTAB分别解析为`_getsockname`和`_getpeername`，不是按变量名推测角色。

`httpConnection_setupHTTPClient@0x24fdc93c0`把`+0xa4`交`SockAddrToString(flags=3)`，再在`0x24fdc9434–448`以`rtsp://%s/%llu`构造URL；后半数字来自现有连接UUID对象经字节逆序取64位，不应固定复制别的会话。

`SockAddrToString@0x18be588b0`：flags bit0不输出端口，bit1不输出IPv6 scope。其调用`IPv6AddressToCString@0x18be40c9c`时port=-1、scope=0；该函数只有port>0或-2才加方括号，因此此生产点不输出IPv6方括号。IPv6输出采用压缩文本，不含Java对象可能带有的hostname/前导slash。

IPv6正文细节也由原汇编复核：各16位组使用小写hex且去前导零；`0x18be40e20–e48`从首组正向扫描，初始最佳长度1，只在严格更长时替换，故只压缩至少2组的最长零段，等长取最先段。全零为`::`，loopback为`::1`。前10字节零/随后`ffff`的mapped地址输出`::ffff:a.b.c.d`；前12字节零且末32位>1的compatible地址输出`::a.b.c.d`（例如`::2`输入产生`::0.0.0.2`）。特殊判断在`0x18be41054–0x18be41124`，点分输出从`0x18be41150`开始。JVM的`hostAddress`并非天然与以上格式完全一致。

必须分开：socket连接仍需正确的scope/interface；URL文字省scope不等于连接可以省scope。若Android选择RFC形式的`[IPv6]`，应记录为本地URI规范化，不声称完全字节复刻。最小已证修正是使用纯数字对端地址，不把`InetAddress.toString()`当线上host。

## 9. 验证与仍未关闭

本轮执行：

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_setup_response_branches.py --verify D:\carvex-research\research\connection\evidence\setup-response-branches.json
```

结果：20个原函数范围、3个源镜像、响应键、endpoint vtable指针、整数扫描跳表和socket符号与快照相同。未运行Gradle、未打包、未实车测试；生产改动与测试结果由对应实施报告单独给出。

仍OPEN：完整SETUP请求presence/timing、所有endpoint实现与info副作用、CF全部字符转换/大整数类型与其他SNScanF格式、skipRecord所有对象复用/重连清理、视频完整数据端口/加密生命周期、所有上层URL/transport fallback、实际网络和首帧/持续显示。不能因本章增加而把G8/G9/G10整体标为完成。
