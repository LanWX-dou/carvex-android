# analysis/04 — NowPlaying（特性 14）

NowPlaying 是"车机订阅、设备推送"的单向业务流：车机用 `0x5000` 订阅要哪些属性，
设备用 `0x5001` 推更新；`0x5002` 退订，`0x5003` 是车机设置播放信息（反向控制）。

## 4.1 消息全集

| msg_id | 方向 | 处理器/发送点 | 符号 | 备注 |
|---|---|---|---|---|
| `0x5000` | 入站 | `0x1001499f0` | `__startNowPlayingUpdatesHandler` | 订阅；带子参数列表 |
| `0x5002` | 入站 | `0x10014a93c` | `__stopNowPlayingUpdatesHandler` | 退订 |
| `0x5003` | 入站 | `0x10014aa20` | `__setNowPlayingInfoHandler` | 车机设置播放信息 |
| `0x5001` | 出站 | `0x1001465c4` | `_iap2_nowPlaying_playbackAttributesUpdateHandler` | 属性更新（组参数） |

`A04.1`：`0x5000` 的日志串证明它是"开始订阅"：
`Start Now Playing Updates!`（`0x1001f0773`）、`nowPlaying addSubscriber: PlaybackQueueList`（`0x1001f0854`）、
`Sending initial now playing update for endpoint: %@`（`0x1001f07da`）。
`0x5002` 的日志串是 `Stop Now Playing Updates!`（`0x1001f08ad`），
`0x5003` 是 `Set Now Playing Info handler!`（`0x1001f090a`）。

## 4.2 `0x5000` 参数结构（订阅）

`0x5000` **没有** `cmp w0,#N` 跳表，用的是比较链（`cmp w27,#2` / `cmp w27,#1` / `cbnz w27`，
地址 `0x100149b68`–`0x100149b78`），所以"参数只有 0/1/2"来自分支结构。

| 参数 ID | 内容 | 结构 | 证据 |
|---|---|---|---|
| `0` | 媒体项属性列表 | 参数值本身是**子参数组**：遍历子参数，将子ID追加到CFArray；不是自动去重的集合 | `0x100149b7c`–`0x100149c18`；A14.1 |
| `1` | 播放属性列表 | 同上的子参数列表；0x11子项另有U32值（A12.4） | `0x100149c28`–`0x100149d5c`；A14.1 |
| `2` | 子参数组（本地转换成位图） | 子参数 ID 被逐位或进一个 32 位掩码：`mov w8,#1; lsl w8,w8,w27; orr w19,w8,w19`（`0x100149dd8`–`0x100149de0`） | 同分支 |
| 其它 | 未识别 | 记日志 `msgParamID: %d`（`0x1001f078e`）后忽略 | `0x100149e08` |

`A04.2`（组结构/对应已确认）：参数0为媒体项属性、1为播放属性、2为本地转位图的子参数组。
A14.1已追完分支→CFArray→feature+8/+10→计数日志实参，关闭历史 `OPEN-NP-1`；
不需要运行时日志或抓包才能确认此映射。单个属性完整业务schema仍需另核。

`A04.3`（纠错）：`0x100067f3c` 的 `cset lo` 返回总长<5；通用TLV已验>=4后即空值参数。
参数0/2子项及参数1大部分子项要求空值；参数1子项0x11用U32，总长8。坏值进入失败路径，非忽略继续。
原先“>=5、任意长度”的结论撤回，完整分支见 A12.4。

## 4.3 `0x5003` 参数结构（设置播放信息）

| 参数 ID | 证据 |
|---|---|
| `0` | `0x10014ab14..24`：U32→w24→block+20→`setPlaybackElapsedTime:`（时间单位仍需追消费者） |
| `1` | `0x10014ab2c..3c`：U32→w23→block+20→`setPlaybackQueueIndex:` |
| `2` | `0x10014ab44..54`：U32→w21→队列列表窗口起点；0xffffffff设置自动选择标志 |

`A04.4`：三个分支都用helper `0x100081e20`读取U32，但后续分别进入时间设置、
队列索引设置和队列列表窗口控制；不是同一条设置路径。
`autoChoosePBQListStartIndex` 属于参数2，值等于0xffffffff时置1。
详见A14.3；`OPEN-NP-3`剩余为时间单位、平台有效值/失败反馈，不再缺字段归属。

## 4.4 `0x5001` 出站（属性更新）

- 构造点：`0x1001465c4`，`iAP2MsgInit(msg, 0x5001, …)`（Ghidra 第 284 行，对应汇编需回 `source/asm/accessoryd/f_1001465c4.s` 核对）；
- 消息用**组参数**（`iAP2MsgAddGroupParam`）承载多类属性，媒体项属性由 `__addMediaItemAttributesToMessage` 填充；
- 发送完成有回调 `__playbackAttributesUpdateSentCB`（名字来自调用点，见同一函数的 `iAP2MsgInit` 参数）。

`A04.5`：另外四条平台侧更新路径（`0x10014569c` 媒体项属性、`0x100145e70` 封面、
`0x1001474b4` 队列变化、`0x10014778c` 队列信息响应）都**没有**在函数体里直接出现 `0x500x` 立即数，
它们**都发 `0x5001`**（整镜像里 `mov w1,#0x5xxx` 只有 4 处，全是 `0x5001`，见 `A11.2`）。
其中 `0x10014569c`、`0x1001474b4`、`0x100148f40` 走同一个共享片段 `0x100012440`
（`mov w1,#0x5001; mov w3,#0xffff; ret`），`0x1001465c4` 直接内联同一个立即数。

## 4.5 封面（artwork）走文件传输，不走消息体

`0x5000` 的字符串里有一组封面相关日志：

| 串地址 | 内容 |
|---|---|
| `0x1001efb1f` | `%s:%d - iAP2MsgInit with cleanupCB - _artworkFileTransferIDSent endpointUUID: %@` |
| `0x1001efb70` | `#Artwork Failed to add file transfer!` |
| `0x1001efb96` | `#Artwork Failed to allocate file transfer buffer ID!` |
| `0x1001f080e` | `#Artwork %d: cancel previous transfer: id=%d(%d) type=%d(%d) state=%d` |

`A04.6`：封面数据通过**文件传输会话**（`sess/` 里的 `_iap2_sessionFileTransfer_*`）传，
消息体里只放传输 ID / 元数据。客户端要实现封面，必须同时实现文件传输，否则只能拿到属性没有图。

## 4.6 订阅者模型

| 函数 | 地址 | 作用 |
|---|---|---|
| `_platform_nowPlaying_addSubscriber` | `0x10008fbd0` | 向sharedClient发送addSubscriber:；容器/计数须追实际类 |
| `_platform_nowPlaying_removeSubscriber` | `0x10008fc20` | 移除订阅者 |
| `_platform_nowPlaying_incrementUserCount` | `0x10008fc70` | 用户计数 +1 |
| `_platform_nowPlaying_decrementUserCount` | `0x10008fcb0` | 用户计数 −1 |
| `_platform_nowPlaying_requestPlaybackQueueListInfo` | `0x10008faf8` | 请求队列信息 |
| `_platform_nowPlaying_cancelRequestPlaybackQueueListInfo` | `0x10008fb78` | 取消请求 |

`A04.7`：成功解析新 `0x5000` 后，`0x100149f64`先移除旧子特性订阅，随后替换属性数组再添加。
旧“未见去重所以可能单纯累加”缺少这段关键证据，撤回。Stop复用移除helper并清空数组。
不过移除helper只有三类，添加侧另有PlaybackQueueList；平台调用为异步提交，
sharedClient动态类为AccessoryNowPlayingClient。完整计数、转发与其它清理链仍属 `OPEN-NP-4`（A14.2）。

## 4.7 门控与顺序

- `0x5000/0x5002/0x5003` 都不在无条件放行名单，必须 `认证==2 ∧ 识别==6 ∧ ID 在入站集合`（`sess/R-5.x`）；
- `0x5003`的参数0/1在本处理器不查Start active位，但这不证明平台必定执行成功；
  参数2即时请求另查feature+51（Start参数1子项0x11的出现位）。顺序语义按字段继续追，不统一要求抓包（A14.3、`OPEN-NP-5`）；
- 出站 `0x5001` 的门控在 `0x100005138`：`0x5001` 不在"无条件出站"名单里，
  即设备发它也需要认证+识别完成。

## 4.8 未决

| 编号 | 内容 | 关闭条件 |
|---|---|---|
| `OPEN-NP-1` | 已关闭：参数0媒体项属性、1播放属性 | A14.1/C18，分支到日志的数据流 |
| `OPEN-NP-2` | 历史关闭：更新消息使用0x5001 | A11.2 |
| `OPEN-NP-3` | 三个U32归属已解；时间单位、平台有效值/失败反馈待核 | A14.3；继续追实际设置方法与消费者 |
| `OPEN-NP-4` | 已缩小：先移除旧订阅再替换；完整计数与队列列表清理未闭合 | A14.2；追AccessoryNowPlayingClient、实际集合、队列与全部清理路径 |
| `OPEN-NP-5` | 设置/订阅顺序的逐字段效果 | A14.3；追状态初始化、active/订阅位及平台方法，不以抓包作静态前提 |
