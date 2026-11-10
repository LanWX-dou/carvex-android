# CarWith 4.0.14 宿主原始 DEX 核对

2026-11-10，用户提供 `D:\home\CarWith_4.0.14-20260801.apk`。已实际读取 APK 原字节并使用 Android SDK build-tools 36.0.0 的 `dexdump -d -n` 反汇编。没有以 JADX 反编译结果或宿主方法名代替行为证据。

APK 为 `com.miui.carlink`，versionCode `104000014`，versionName `4.0.14-20260801`，55,952,823 bytes，SHA256 `c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。包信息来自 `aapt2 dump badging`；DEX 哈希、code item 偏移和原指令哈希见[证据 JSON](../evidence/carwith-4.0.14-host.json)。APK、完整 DEX 与供应商全量反汇编仅保留本地，不入库。

## R03 / G08：歌词展示与真实播放器匹配

本轮直接读取 classes2 `f5.d.q` `0x3350a8`。它没有把播放状态写入 `carlife_vehicle_music_info`，但在歌词展示门开启且文本非空时，把 `oa.c.D()` 结果放进 `song`。原 artist 不包含歌名时，`0x335124..0x335168` 将原歌名 + `-` + 原 artist 写入 `artist`；否则保留原 artist。无歌词文本的分支使用正常歌名与 artist。同一 Intent 包含 album、duration、coverUrl 和 Bitmap cover。

classes4 `oa.c.D` `0x19ae44` 取按播放时刻选择的文本，空时读 `ucar.media.metadata.LYRICS_LINE`，并可能取缓存展示文本；r `0x19a9a0` 读取 `LYRICS_STATUS` 作门。classes2 `f5.d.i` `0x334a3c` → databus.MusicInfo 构造 `0x11c0fc` → getter `0x11bd10/0x11bec0` 闭合 artist/歌名数据流。`za.c.a/e` `0x1bb444/0x1bb524` 可读 UCAR 私有 ARTIST/TITLE，也回退标准元数据和 DISPLAY 字段，不能保证与公开会话始终一致。

原 `MediaSessionSelection` 严格匹配实际 TITLE/ARTIST，对 Lyric / Song-Artist 无法选中实际 Song / Artist。Android `3c92c9d` 已在桥接补完整组合匹配并将其注入平台读取器；与标准规则一起要求唯一候选，连字符组合歧义、缺字段或多个播放器仍未知。新增平台4项与桥接7项回归，本次平台13项/2 suites、桥接48项/9 suites、协议1110项/135 suites无失败/错误/跳过，小米Debug Kotlin编译成功。状态只来自获得授权后实际 MediaSession。见[Android修复](../../../android/docs/fixes/2026-11-10-carwith-lyrics-state.md)。没有从歌词、进度或音频猜播放状态，也未新增图片修复。

这一生产者证据补充了此前频闪记录中“为何展示字段反复变化”的一种已存在路径，但没有把脱敏日志中的每次身份变化绑定到具体歌词分支；实车原因和修复效果仍待验证。此前暂停测试明确未授权，本项不能替代授权或认定其唯一根因。

后续可继续依据 APK 核对：原artist已包含歌名的另一展示分支、覆盖后的元数据与公开会话关系、封面来源的更新链、语音键到录音启停的实际消费，以及 Surface/尺寸/动态FPS的请求回复。导航结束已修；蜂窝上下行和Apple政策绑定仍未闭合，不将这些方向标为已修复。

## G03：已确认宿主生命周期，Apple 映射继续分开核实

下表位置均为 DEX 文件内偏移，code item 的指令正文从偏移加 16 bytes 开始，不是加载虚拟地址。

| 原始位置 | 直接核对的数据流 |
|---|---|
| classes2 `0x1c5c20`，`map.wms.i$x.g(boolean)` | true 且 CarLife 已连接时，`0x1c5c86..0x1c5c88` 将布尔 `isNavi=true` 写入 `mix_notify_start_navi`；false 分支调用下行结束生产者。 |
| classes2 `0x16fb48`，`LauncherDataBusClient.C()` | `0x16fb6a..0x16fb6c` 写布尔 `isNavi=false`；`0x16fb90..0x16fb92` 将整数 `action=3` 写入 `carlife_show_hud_info`；距离和转向置零，道路置空。 |
| classes2 `0x16fc3c`，`E(...)` | 首次 HUD 写 action=1，后续 action=2（`0x16feea..0x16ff00`）。按真实宿主导航活动及 `prefer_hud` 门生成 HUD。 |
| classes2 `0x16f8e4` / `0x16f914` | 结束双通知及正常 HUD 都进入 `j.G(Intent)`；两个结束通知按该 runnable 内顺序调用。 |
| classes6 `0x0a8a60` → `0x0a7ee8` → `0x0a88bc` | 异步调用最终在 `0x0a896e` 转发给 `ICarLifeCastCallback.invokeMethod(Intent)`，与本工程 optionalAction 回调合同相符。 |

Android `175c048` 只落实已证结束事件：删除桥接和发布器缓存，不再将结束包的零距离当作真实路线，不在后来 `5200` 重放旧路线，保留车机订阅。7 项新增回归、协议1110项、桥接41项及小米编译通过。修复说明见[Android记录](../../../android/docs/fixes/2026-11-10-g03-navigation-end.md)。**没有**把宿主 action=1/2/3 复制为 iAP guidanceState，也未验证车机屏幕的结束效果。

距离原字节另已核：

- `classes2 0x16ffc4` 将 `UCarMapInfo.getDistance()/getDistanceUnit()/getOperation()/getWhere()` 送入 E。
- `0x16f3f0` 的 w：string_id `0xc845` 原字符串为“公里”，parseFloat 后乘1000.0再转int；`0xc8e0` 为“米”，直接转int；`0xc8cc` 为“现在”，与null及未识别单位一样返回0。异常返回0。不能将返回0一概解释为抵达。
- E 在 `0x16fe8e..0x16fe9a` 把 w 结果写入 remain_distance；`total_distance` 是实例缓存值，当 where 变化时取当前 remain_distance（`0x16feb2..0x16fee4`），**不是另一个总路线距离生产者**。
- `classes4 0x11c40c` 的 NavigationInfo.i 读取字段 f；结合 `0x11c4d0` 构造和 E 参数搬运，road_name 来自 UCarMapInfo.where，而非独立的当前道路字段。
- `classes5 0x1bf334` 从外部 Bundle 读取 DISTANCE、DISTANCE_UNIT、OPERATION、WHERE。CarWith UI `classes2 0x1948a4` 将距离/单位/动作/where 与方向图标放入同一机动提示组。这支持“机动提示距离”的解释，但外部地图生产者尚未读取；不能仅据字段名或布局确认其所有导航阶段语义。

因此当前活动 HUD 的历史道路/距离适配仍未标为 CONFIRMED。路线距离/下一机动距离的 iAP 单位、真实 guidanceState、机动枚举与车道生产链继续 OPEN。原 accessoryd 字段宽度编码器不会自行证明这些宿主映射。

## G02：共享 PCM 队列已定位，未证明蜂窝上下行

| 原始位置 | 直接核对的行为 |
|---|---|
| classes6 `0x0adf90`，CarlifeAudioListener | 非空 mic PCM 经检测后，`0x0ae002..0x0ae00c` 交给 `h1.a.b().a(bytes, bytes.length)`；该路径没有依据回调格式参数作蜂窝格式协商。 |
| classes `0x48ef6c` / `0x48ee00` | h1.a 把字节写入/读出带锁 LinkedList，并 notify/wait；队列操作本身没有调制解调器注入。 |
| classes `0x4328e0`，PhoneAudioCast.B | 优先调用远程 readAssistantRecorderData；CarLife 分支在 `0x43291c..0x432924` 从同一队列读取。 |
| classes4 `0x10f738` | DataBusService 的 readAssistantRecorderData 转发给 PhoneAudioCast.B。 |
| classes5 `0x1b1fc8`，be.f.d | 同步读取 DataBusClient.readAssistantRecorderData；该类的初始化路径日志为 HuMicRecorder。 |
| classes `0x4384d0` | VoIPService 的 readAssistantRecorderData 也读取同一队列，证明队列被多条路径共享。 |

已定位到 SDK 的读取适配器，不能继续把“未有宿主 APK”列为前提。尚未取得蜂窝 modem/HAL 消费者或专用下行来源，也未把宿主内部 PhoneState/databus 数据证明为当前 mixing 公开接口。普通助手及 VoIP 的队列读取成功不证明蜂窝上行。G02 保持 PARTIAL，没有创建空通话代码提交。

继续读取原指令后，明确区分两条音频路径：

- CarLife listener `0x0adf90` 只把mic写入 h1.a 共享助手队列。
- 原生 databus `classes4 0x10979c` 比较 `STREAM_MICROPHONE`，在匹配时调用 PhoneAudioCast.z；`classes 0x432dc4` 转发 `IPhoneAudioCast.onAudioData`。这条路径不是现有 mixing listener 的直接消费者。
- 自带 VoIPService 的 `0x438558` 在其状态门下也可写 h1.a；另一分支写 h1.e 和 h1.d。`0x438884` 的 startToRecord 调用 h1.d.h；`0x48f254` 将PCM分块写入另一队列，`0x48f2ec` 将该队列数据与输入缓冲混合。尚未据此证明蜂窝modem消费，也没有把不同队列替换为一条“通话上行”。
- mixing 输出 `classes6 0x0a9488` 的 j.A 来自 bh.d$c.b（`0x0a4c04`），bh.d 在 `0x0a4cd8` 注册 i1.a 音频回调并观察录音启动事件。音频类别、底层采集与蜂窝专用下行仍需继续追到实际生产者，不能从通用回调名称推定。

APK中25个arm64原生库已提取到忽略目录；libmicastcore动态符号包含AudioSource等，名称仅用于后续定位，本轮未把符号扫描作为蜂窝路由存在或缺失的证明。没有修改宿主绑定、调用未验证服务或新增PCM注入。

## 原 Apple 缓存缺失的具体边界

用户本轮明确回复：本机没有原始 24A446 IPSW 或 dyld_shared_cache_arm64e。既有提取库和原 accessoryd 仍可读取，不能因此停止所有静态取证。当前真正缺的是跨库 FigStark 资源控制器及原缓存中 GOT/stub 绑定所需字节：`_carEndpoint_handleEventCreatingReply` 成功/失败门已核，实际仲裁外部调用 `0x25810f770` 仍未闭合；音频本地政策的 transport 参数绑定也未闭合。提取镜像中的编码指针不能靠经验解码当作原缓存证明。

## 复核

```powershell
python -B research/connection/tools/inspect_carwith_host.py D:\home\CarWith_4.0.14-20260801.apk
```

本轮 PASS：APK身份、5份 DEX、39处原 code item 指令哈希及3个原距离字符串。它只复核字节位置与身份，不运行供应商代码，也不证明语义、蜂窝声音或车机互通。
