# analysis/14 — NowPlaying 参数与订阅数据流补证

对象：24A446/accessoryd；SHA256
`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。
本节来自原镜像指令、导入表和字符串，不需要抓包才能成立。
`tools/verify-nowplaying-audit.py` / C18 固定这些局部证据；不执行平台服务。

## A14.1 参数0是媒体项属性，参数1是播放属性

`0x1001499f0` 的比较链 `0x100149b68..b78` 分别选择参数2、1、0及未知项。
沿两个分支追踪到日志实参，得到以下完整对应：

| 线上组ID | 子ID写入 | 提交到feature | 日志取数与字符串 | 结论 |
|---|---|---|---|---|
| 0 | `0x100149bf8..c00`：w27→w1，x22→x0，CFArrayAppendValue | `0x100149f74`：x22→+8 | `0x10014a00c..034`：+8→CFArrayGetCount→sp+54；x3=`0x1001f07af` `mediaAttrCount: %ld` | 媒体项属性ID数组 |
| 1 | `0x100149d2c..d34`：w28→w1，x21→x0，CFArrayAppendValue | `0x100149f8c`：x21→+10 | `0x10014a064..08c`：+10→CFArrayGetCount→sp+54；x3=`0x1001f07c3` `playbackAttrCount: %ld` | 播放属性ID数组 |

`0x1001a13f0/1440/1460` 经原 Mach-O 间接符号表分别解析为
CFArrayAppendValue / CFArrayCreateMutable / CFArrayGetCount，不能把它们误称为自动去重的集合。
日志是否在运行时开启不影响静态实参与格式串的对应。
**历史 `OPEN-NP-1` 已关闭**，旧“ObjC格式化后还必须运行确认”结论撤回。
参数2仍是线上子参数组，只有本地表示是32位掩码（A12.4）。

## A14.2 Start是替换旧属性，不是无条件累加

解析成功后，`0x100149f60..f64` 先对旧feature调用 `0x10014995c`，
然后释放旧+8/+10数组并写入新数组（`0x100149f68..f8c`）。
`0x10014995c..9f0` 完整函数按旧数组内容投递移除操作：

| 条件/操作 | 全局block | invoke | 平台订阅键 |
|---|---|---|---|
| 旧媒体数组非NULL且count≥1：移除 | `0x10021bf98` | `0x100081c08` | MediaItemAttributes |
| 旧媒体数组非NULL且helper `0x1000815ac`为真：移除 | `0x10021bfd8` | `0x100081c18` | MediaItemArtwork |
| 旧播放数组非NULL且count≥1：移除 | `0x10021c018` | `0x100081c28` | PlaybackAttributes |
| 新播放数组count≥1：添加 | `0x10021c088` | `0x100081c38` | PlaybackAttributes |
| 新播放数组包含0x0f或0x11：添加 | `0x10021c0c8` | `0x100081cc8` | PlaybackQueueList |
| 新媒体数组count≥1：添加 | `0x10021c108` | `0x100081cd8` | MediaItemAttributes |
| 新媒体数组非NULL且helper为真：添加 | `0x10021c148` | `0x100081d0c` | MediaItemArtwork |

helper `0x1000815ac` 要求feature及+10非NULL，再检查+8数组是否包含属性0x1a；
数组创建失败/NULL路径不能从正常订阅路径类推。键的原始常量槽为
`0x1002199b0/9b8/9c0/9c8`，分别指向上述四个CFString。

移除block尾调 `0x10008fc20`，添加block调用 `0x10008fbd0`。
添加媒体/封面/播放属性后还分别调用 `0x10008f458/70c/850`，
所以即使最终计数相同，也不能宣称重复Start无任何平台副作用。
`0x100031a20` 在 `0x100031aa0` 调用真实导入 `dispatch_async`；
这是**排队提交**，不能写成处理器返回时远端订阅已完成。

Stop处理器 `0x10014a93c` 在 `0x10014a9c8` 复用移除函数，随后清active位并释放、置NULL两个数组
（`0x10014a9cc..9f8`）。顺序重复Stop在这些数组上不再重复投递上述三类移除，
但此局部事实不等于所有清理副作用和并发路径都幂等。

### 尚未关闭的边界

移除helper仅有三类block，**没有与PlaybackQueueList添加对应的第四类移除**。
这不是全系统泄漏的证明；必须继续核对平台客户端如何表示该订阅及其它清理路径。
不能仅凭“先remove后add”就关闭 `OPEN-NP-4`。

`0x10008fbd0/fc20` 调sharedClient后发 `addSubscriber:` / `removeSubscriber:`；
`0x10008fcf0` 的初始化通过 NSClassFromString 读取CFString `0x100225d18`，
类名为 **AccessoryNowPlayingClient**（字符地址 `0x1001d2110`）。
因此不能直接把同镜像的 `ACCFeatureServer` 方法当成已经绑定的NowPlaying接收者。
其 `0x1000aef18/af034` 确实操作 `subFeatureSubscribers` 的
`addObject:` / `removeObject:`，日志使用 `countForObject:`，随后发送更新列表；
这些方法体可静态读，但类继承/转发绑定及实际容器仍须继续核实。
`OPEN-NP-4` 改为“已缩小”，不是“ObjC不能静态分析”。

## A14.3 `0x5003` 三个U32的去向

`0x100081e20..e3c` 将错误出参设到fp-54，并尾调 `0x100067df0`（U32 getter）。
各分支在暂存后检查错误；解析循环结束才提交动作，未知ID跳到下一参数。

| 参数 | 暂存/出现位 | 消费路径 | 已证含义 |
|---|---|---|---|
| 0 | `0x10014ab14..24`：w24/w26 | block `0x100081d40` 读+20→`0x10008f35c`→selector `setPlaybackElapsedTime:` | 设置已播放时间；此处未证明时间单位 |
| 1 | `0x10014ab2c..3c`：w23/w28 | block `0x100081d48` 读+20→`0x10008f3fc`→selector `setPlaybackQueueIndex:` | 设置播放队列索引，不是队列列表窗口起点 |
| 2 | `0x10014ab44..54`：w21/w27 | `0x10014ac2c..34` 写feature+53；`0x10014acfc` 传x1给 `0x1000817c0` | 队列列表请求窗口起点覆盖值；0xffffffff启用自动选择 |

参数0/1捕获分别在 `sp+58`（block基址sp+38）、`sp+30`（block基址sp+10），
恰为各block+20。平台包装器用 `numberWithLong:` 装箱后传值，不能把返回1视为播放器已完成操作。

参数2的 `cmn w21,#1; cset w8,eq; strb w8,[x20,#0x53]`
证明autoChoose标志属于**参数2且仅在值为0xffffffff时置1**，不是任意非零布尔。
随后仅当feature+51==1才调用窗口请求helper（`0x10014ac9c..ad08`）；
该位由Start参数1子项0x11的出现标记设置（`0x100149d18..1c`、`0x100149fac..fb4`）。
helper再根据窗口大小、当前曲目索引/数量归一化起点（`0x100081a60..acc`），
所以收到一个U32并不等于无条件从该数值直接发起请求。

`OPEN-NP-3` 的“三个字段属于谁”已解；仍保留已缩小状态以继续核实时间单位、
平台设置的有效值/失败反馈。`OPEN-NP-5` 也应继续追状态与消费者：
0/1并不以Start active位作本处理器前置门，而2的即时请求有上述订阅子项门；
不能把所有顺序问题统一留给抓包。

## 实现边界

独立设备端应按0/1两个属性域解析订阅，并在成功解析后替换该endpoint的订阅配置。
采用集合去重、抑制重复通知或避免重复平台引用属于本地实现策略；不得冒称本固件保证。
静态映射不依赖目标车机采集；目标车机是否选择这些属性、真实播放器响应及跨版本兼容，另作运行验收。
