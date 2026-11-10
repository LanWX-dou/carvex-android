# CarWith 歌词展示导致播放器状态匹配失败

2026-11-10。本项属于仪表音乐/方控状态来源的局部修复，关联研究台账 R03、G08。不是 G08 持续 seek 消费的完成证明。

## 原字节依据

用户提供的 CarWith 4.0.14 APK SHA256 为 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。原 SDK dexdump 指令显示：

- classes4 `oa.c.D` code item `0x19ae44` 读取按播放时刻选择的文本，空时读取 `ucar.media.metadata.LYRICS_LINE`，并可能使用缓存展示文本；`0x19a9a0` 的 r 读取 `LYRICS_STATUS` 作门。
- classes2 `f5.d.q` `0x3350a8` 在上述门和非空文本下，将 D 结果写进 `song`。`0x335124..0x335168` 比较原 artist 是否包含原歌名；不包含时写入原歌名 + `-` + 原 artist。
- q 的正常分支 `0x3350f8..0x33510e` 则直接写原歌名与 artist；同一 Intent 还包含 album、duration、coverUrl 和 Bitmap cover，末尾通过 j.G 转发 callback.invokeMethod。
- `f5.d.i` `0x334a3c`、databus.MusicInfo 构造 `0x11c0fc` 及 getter `0x11bd10/0x11bec0` 闭合原 artist/歌名的数据流；`za.c.a/e` `0x1bb444/0x1bb524` 可读取 UCAR 私有元数据，并回退到标准 ARTIST/TITLE 等字段。私有覆盖值与公开媒体会话不一致时不保证匹配。

以上是 DEX 文件内 code item 偏移，指令从偏移加16 bytes开始，不是虚拟地址。来源与39处原指令身份复核见研究仓库 `research/connection/spec/carwith-4.0.14-host-evidence.md`。

## 差异与修复

当前严格匹配把宿主的 `song` 当成实际歌名，并要求 artist 一致。例：实际会话为 Song / Artist，CarWith 发来 Lyric / Song-Artist，严格匹配无法选中；即使已经取得通知访问，也无法从该候选读取播放状态。

桥接为音乐 Intent 提供额外匹配：把每个候选的完整歌名和歌手重组为 `歌名-歌手`，与宿主 artist 完整比较。没有拆分连字符、模糊搜索、按歌手单独选择或选择“唯一活跃播放器”。原严格匹配和附加匹配一起计数，只有一个候选时允许读取真实状态；同一候选命中两条规则只计一次，多个候选或连字符组合歧义仍未知。

平台模块只接受可选的元数据匹配函数，不包含厂商规则。只有音乐 Intent 设置该函数，直接 MusicInfo 更新恢复标准规则；进度 Intent 不设置目标。没有更改5001编码、宿主按键映射、歌曲显示或图片缓存。原歌词变化导致封面身份改变的路径与此前频闪有关，但本项不新增图片修复。

## 验证与边界

新增平台4项和桥接7项回归，覆盖歌词连续变化、普通元数据、名称中的连字符、部分标签拒绝、重复播放器、两条规则交叉歧义，以及非音乐/进度输入隔离。

```powershell
.\gradlew.bat :platform-android:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

本次平台13项/2 suites、桥接48项/9 suites、协议1110项/135 suites均无失败、错误或跳过，小米Debug Kotlin编译成功；whitespace检查通过。原APK身份、5份DEX及39处code item指令哈希独立复核通过，这不是运行供应商代码或实车验证。

通知访问授权仍是获取真实状态的前提。未提供新设备日志，不能将此静态缺陷认定为此前未授权测试的唯一原因。原 artist 本来已包含歌名而没有生成完整组合、UCAR私有元数据覆盖、状态缺失及歧义仍可能无法匹配。

实车应在授权后覆盖普通展示/歌词展示、播放/暂停、同名多个播放器、换曲和退出。未打包、安装、推送或实车验证。
