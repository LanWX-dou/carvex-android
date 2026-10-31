# Toyota 运行期控制静默：固件核对记录

状态：OPEN。2026-10-30。按用户要求暂停历史回归溯源，以 iPhone 24A446 与本地 Toyota 原二进制为依据。本轮没有修改手机代码或任何车机文件。

## 已复核的路径

### iPhone

输入：`docs/iap2_input_business_lifecycle/source/firmware/accessoryd`；TEXT vmaddr=0x100000000、fileoff=0。下述地址由原始字节反汇编核对。

- `0x10014569c` 媒体属性更新：检查上下文、feature active，构造消息；`0x1001457ac` 调用 `0x100145934` 填充属性；只有填充成功分支才在 `0x1001457bc` 调用发送 helper。
- 消息安装 `0x100145870`（`__mediaItemAttributesUpdateSentCB`）回调。该回调存在 feature 检查、日志及资源释放分支。当前读到的函数体没有可据以证明“必须延迟第二条”或“发送完成才允许下一次媒体更新”的逻辑。不能把回调存在等同于业务节流。
- 普通 iAP 控制请求等待事务结果的传输层证据已有于 `85-runtime-control-recovery.md`。本轮不把该文档当作全部发送队列、并发和 ACK 语义已闭合的证明。

### Toyota

输入限于 `firmware/headunits/toyota/extract/vendor/carplay/` 下 `AppleCarPlay`、`libs/libiAP2.so`、`libs/libCarPlayInterface.so`，没有混用系统另一份 libiap2。

- `libiAP2.so` 的 `parseNowPlayingMediaItem` 在 `0x32610..0x32670` 解码 duration，换算后存储，并调用 event 5。该分支没有“值未变则跳过”的比较。
- `AppleCarPlay` 的 `iAP2OverCarPlaySetup @0x40e340` 构造回调表，包含 `0x40ad80` 媒体项回调。
- `0x40ad80` 分别读取 title、album、artist、duration；在 `0x40ae18` 调用 `handleNowPlayingUpdateMediaItemAttributes`。不是只收到 duration 就能断言整条消息处理完成。
- `libCarPlayInterface.so:0x17190` 经 PLT `0xbd80`（GOT `0x31258`）进入 `iap2_emit_handle_now_playing_update_media_item_attributes @0x11970`。
- `0x11970` 参数整理后跳转 `0xc0f0`，对应 `g_signal_emit_by_name`（GOT `0x31410`）。这是本地信号发射路径；不能据此认定它等待远端进程应答，也不能仅凭同步调用认定死锁。

## 对手机实现和现场的约束

1. 现场多次第二条5001后控制收包停止，是定位入口，不是已证根因。
2. 尚无依据删除 duration、禁用歌曲信息、增加发送延迟或判定 Toyota 拒绝第二条。
3. RTSP 200、iAP ACK、Toyota 业务回调完成是不同事件，不可互相替代。
4. 本地 Toyota 固件与现场 sourceVersion 相同不足以证明二进制一致；结论应表述为本地样本行为。

## 下一处必须闭合

- Toyota：AirPlay iAPSendMessage 接收入口 → iAP 输入/处理队列 → ACK 发出 → 业务回调 → RTSP 应答，核查线程、锁和通知接收端。已定位 `CIpodDevice::recvThread @0x20010`、`procThread @0x1fa78`，尚未完成调用链。
- iPhone：媒体平台更新 → 5001 消息调度 → iAP ACK/重传 → 普通控制事务，核查并发和下一条发送条件；不能从单个完成回调推断全局策略。
- 对照我们这两条路径找出可证明的行为差异，再决定手机端改动。当前不宣称已经解释全部自动断开与蓝牙 ACK-only 重连失败。

## 后续只读核对：无线入口与共享队列锁

以下由本地 Toyota 原二进制直接反汇编，PLT 调用以 ELF 重定位表解析，不依赖旧文档命名。

1. `AppleCarPlay:0x407470..0x407480` 比较 iAPSendMessage（常量对象0x40ef10，其字符串0x40ef18）。匹配后 `0x407520..0x407548` 取 data 的字节指针、长度并调用 `0x40df50`。该分支须等待此调用返回，随后才返回控制回调；这里尚未追完 AirPlay 库的实际 RTSP response write。
2. `0x40df90..0x40df98` 调用导出的 `sendWiFiData`，经 `CIpodLib::sendWiFiData @0x3d800` 查设备，进入 `CIpodDevice::sendWiFiData @0x1ff18`。
3. 普通数据分支 `0x1ff5c..0x1ff98` 分配并复制 IpodPacket，标记 false，调用 `packetAdd @0x1fc30`。不是直接在控制回调里解析5001，也不是绕过队列的另一条 Wi-Fi 路径。
4. `packetAdd` 在 `0x1fc50` 对 device+0xe0 调用 pthread_mutex_lock，入队后 `0x1fc78` 解锁，再 sem_post。
5. `procThread @0x1fa78` 在 `0x1fae8` 获取同一个 device+0xe0 锁，`0x1fb24` 调用 packetProc，直到处理、删除队列项之后的 `0x1fb68` 才解锁。故业务处理期间，新的无线数据入队可能等待这个锁。
6. `CIpodDevice::packetProc @0x1fa50` 经协议对象vtable+0x20分发。`CIpodIap2::packetProc @0x38370` 的普通数据分支到 `0x37d60`；session非零时在 `0x37e14` 先调用 sendAckPacket，在 `0x38194..0x381b0` 才识别5001并调用 nowPlayingUpdate。

### 可解释的现象与尚缺的证明

这条已确认的结构允许如下情况：第一条数据已入队、处理线程已发ACK，但仍在业务处理；第二条控制请求在入队锁上等待。若第一条的后续处理不返回，第二条控制回调也无法返回。因此不能把“第二条无应答”直接定位成“第二条字段有错”。

这只是由代码证明的阻塞传播条件，**未证明现场第一条业务处理确实不返回**，也未证明所有控制请求由同一串行执行上下文处理。还需追 nowPlayingUpdate 内的实际停顿原因及 AirPlay 控制调用者。不能据此修改车机锁、给手机加任意延迟或宣称根因已找到。

iPhone 侧本轮复读了 carEndpoint_sendCommandInternal 的队列提交及普通等待结果分支；没有获得足以证明苹果有额外5001业务完成确认或固定发送间隔的证据。手机当前 iAPSendMessage 接收处理以 runtime.accept 入队成功返回200，同样不代表业务完成。

## 关键进展：首条媒体更新的自我等待条件已闭合

本地 Toyota libiAP2 SHA256：`f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f`。

### 初始化与回调形成循环依赖

- 构造函数 `CIpodIap2 @0x360a8`：`0x36104` 设置 x20=this+0x5c0；`0x36268`（原字节9fc20639）向 x20+0x1b0 写0，即 this+0x770 初始为0。同时 persistentID=0，title/album/artist均为空字符串。
- `nowPlayingUpdate @0x32df8` 先保存旧 persistentID/title/artist/album；解析完字段后逐项比较。任一变化则 `0x330c8` 同步发 event3。
- event3 的跳表项（表0x43500，基址0x207dc，带符号16位偏移乘4）指向0x20e20，加载 observer+0x18，最终同步调用此前已核对的 AppleCarPlay 媒体回调0x40ad80。
- 媒体回调的第一个查询为 getPlayingTrackTitle。经导出函数0x3dd18、CIpodLib::getPlayingTrackTitle @0x3cde0、设备协议分发，到 CIpodIap2::getPlayingTrackTitle @0x27e00。
- 标题读取在 `0x27e14..0x27e28` 循环等待 this+0x770 非零，每轮 usleep(2000)，无超时分支。album、artist、duration的读取也检查同一标志。
- 然而设置 this+0x770=1 的位置是 `0x330d0..0x330d4`，在 event3 返回之后。

因此在初始标志0且首条5001改变上述媒体属性时，处理线程在自己的同步回调中等自己尚未执行的置位动作。这是本地固件可从控制流证明的自我等待条件，不再只是“任意业务回调可能阻塞”的泛泛假设。处理线程同时持有输入队列锁，解释后一条无线控制请求为何可能卡在入队。

duration字段在解析中发送的是event5，不是上述event3；不能把duration本身误称为已证唯一触发字段。

### iPhone 24A446：有内容的默认首报，不是空CSM

- Start处理器 `0x1001499f0` 在 `0x10014a0fc` 调用 `0x10008f588` 构造媒体默认字典，在 `0x10014a104` 调用 `0x10008f978` 构造播放默认字典。
- 媒体字典的键来自0x10021c3f8起的16个槽。解码原Mach-O链式指针后得到 PersistentID、Title、PlaybackDurationMS、AlbumTitle、AlbumTrackNum等，以及Artist、Genre、Composer等。
- 值由函数体直接放入字典：Title/AlbumTitle/Artist对应0x1002223b8的空CFString；PersistentID/PlaybackDurationMS对应0x10022a168的常量数字对象（类型编码I，值0）。这里只将已核对字段列为事实，不能笼统说所有播放属性也全为0。
- 有媒体订阅时 `0x10014a53c..0x10014a55c` 把上述默认字典交给真实媒体编码器0x100145934；播放订阅另调用0x100146d84；`0x10014a218..0x10014a228` 在编码字段数非零时提交消息。
- 所以正确对齐方向是按订阅编码初始默认字段，然后发送实际更新；不是无条件发空5001，也不是捏造真实歌曲状态。重新订阅、已有缓存快照和不支持属性的分支需在实现前覆盖。

### 我们的明确差异及现场对应

NowPlayingPublisher当前snapshot从全null Track开始；收到5000时若fields(snapshot,selection)为空则不发送。它缺少苹果上述独立的默认首报，首个真实歌名可能直接成为该链路第一条5001。

附件d292b55a中e3e7b3d6：11:01:18.765462 UTC收到5000；到11:01:28.602155才出现首条TX5001，此前收到含title/artist/album/duration的音乐Intent；11:01:28.761363第二条后静默。这与已证静态触发条件吻合。日志只记字段存在性，不记文字正文；不能声称已读取现场全部字段值，现场固件二进制也未绑定本地样本。

结论：已找到手机缺失的iPhone初始化行为，以及能解释现象的Toyota条件性自我等待机制。尚未修改生产代码、未执行Toyota原固件、未实车验证；不能据此宣称所有ACK-only重连故障均已解释。

附：旧analysis/11将0x100148f40简称“初始更新”不宜继续当证据使用；本轮检查该函数含elapsed更新和定时状态，真正Start内默认首报以0x10014a0fc起的调用链为准。没有改写原研究缓存。

## 与后续偶发连不上的关联：全局锁扩大影响范围

按用户要求先记录、不修复，继续追本地 Toyota 原字节。

### 已证锁关系

- `CIpodLib::getPlayingTrackTitle @0x3cde0` 在 `0x3ce00` 调用 CIpodSync::lock，随后才查询标题；`0x3ce2c` 才解锁。故前述标题无限等待不仅保留 device+0xe0 队列锁，还保留全局锁。
- `CIpodSync::lock @0x3f098` / unlock @0x3f0a8 使用 GOT 0x6ff48；ELF重定位明确指向 `CIpodSync::s_Lock @0x71490`。不是仅凭同名函数猜测同一把锁。
- `CIpodLib::disconnect @0x3c9a0` 的 `0x3c9c0` 先获取该全局锁，之后才检查设备存在、pop设备、将调用方handle设为-1。若标题查询永不返回，disconnect不能走到这些清理步骤。
- `CIpodLib::connect @0x3c820` 的 `0x3c848` 同样先获取全局锁，之后才检查/创建设备、创建处理线程或开始connectIap2。故影响可以跨设备对象传播，不限于卡住的Wi-Fi队列。
- AppleCarPlay 的 `AirPlaySessionFinalized @0x40e5a0` 在回调后检查多个transport handle，调用0x40a380。该函数对应分支在0x40a3fc、0x40a4e8、0x40a558调用iap2Disconnect（PLT0x404e70）。这是会话结束与上述清理入口的静态联系；未证明现场一定已执行到Finalized。

### 为什么不能把蓝牙还能收到ACK当作反证

蓝牙RFCOMM连通不是iAP业务重新初始化。`CIpodLib::ipod_BT_spp_data_pro @0x3d7b0` 查已有设备并交给该设备输入方法，没有先获取CIpodSync全局锁；其普通数据入队只取对应设备的队列锁。因此在Wi-Fi对象卡住且全局锁不释放的条件下，另一个已有蓝牙对象仍可能处理输入，而新建/删除iAP对象被堵住。

这解释了“底层蓝牙仍能活动”和“上层会话无法重建”可以同时存在，但**未闭合现场那一帧ACK的具体生成来源**，不声称已证明旧Bluetooth对象一定被复用。

### 日志时序对应（附件d292b55a）

以下转换为Asia/Taipei本地时间2026-10-30：

- 19:01:28 首条实际歌曲5001得到ACK，第二条后静默。
- 19:01:38 控制请求超时，手机开始故障清理。
- 19:01:56、19:02:40、19:03:01 三次后续尝试，在Detect之后都收到 `40/109/16/0/0`，随后NO_SYN。

重复的ACK值是残留状态的线索，不是车机内存对象身份的证明。该时间序列支持“运行期卡住后，后续重连受损”的关联，不能倒推出所有早期独立连接失败都由同一原因造成。

### 当前判断与下一边界

本地固件已证：首条媒体变化自我等待 → 持有队列锁及全局锁 → 后续数据入队、断开清理、新iAP连接入口可被阻塞。现场后续NO_SYN具有时间关联，因此两类故障可能是同一触发链的前后表现，可信度高于仅凭日志猜测。

仍缺：现场固件绑定/线程栈、新旧Bluetooth对象生命周期，以及手机自身资源关闭未完成的独立影响。ACK-only生成路径已在后续原二进制追踪中定位为 `sendAckPacket`，并找到旧 `CIpodDevice[0xac]` 将 Detection 误解析为 `ack=0x10` 的分支；完整证据与仍为 OPEN 的清理原因见 `toyota-ack-only-producer-20261031.md`。该轮研究本身不宣称所有偶发连接失败都会因首报修复消失；后续实车结果见下节。

## 2026-10-31 手机端实施更新

前述“不改代码”为此前研究轮次状态。本日经用户同意，已修改手机NowPlayingPublisher：独立默认首报优先于缓存真实快照，首报入队失败禁止真实更新越过；按订阅顺序输出并保留重复项。没有Toyota专属分支、人工延迟或空CSM补丁。

补核0x10008f978播放字典键值；0x10022bcd0的链式绑定序号0x33a在原Mach-O imports表中为___kCFBooleanFalse。实现采用已支持媒体/播放属性的0、空字符串、false默认值，按订阅过滤，不把默认值混入真实播放器缓存。

改动、测试与备份见手机项目 `docs/nowplaying-initial-state-2026-10-31.md`。完整协议单测与小米Kotlin编译已通过。

## 2026-10-31 实车结果

用户反馈：当前版本在 Toyota 上可以稳定连接，歌曲信息更新期间不再掉线，手动断开后能够重新连接，且仪表盘可以正常显示歌词。该结果为修复提供了正向实车证据：先发协议默认首报、随后发送真实歌曲信息，避免了此前由首条真实媒体变化触发的控制通道停滞。

仍未验证所有历史 ACK-only 重连和清理阻塞路径；不以本结果关闭这些独立OPEN项。
