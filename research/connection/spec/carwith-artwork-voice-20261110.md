# CarWith 封面更新与语音控制核对

2026-11-10，继续读取用户提供的 CarWith 4.0.14-20260801 APK 原 DEX。来源身份见[宿主证据](carwith-4.0.14-host-evidence.md)，最新[字节记录](../evidence/carwith-4.0.14-host.json)扩展至6份DEX、101处code item，另直接解析语音键的 packed-switch。封面轮为91处，语音修复轮新增10处。APK与全量供应商反汇编仅保留本地。

下文位置均为 DEX 文件内偏移；code item 指令正文从偏移加16 bytes开始。宿主行为独立核对，不作为 Apple 资源仲裁、音频类型或增强 Siri 的协议依据。没有新的实车日志。

## 封面生产、处理与更新

| 原位置 | 本次直接核对的行为 |
|---|---|
| classes2 `f5.d.q` `0x3350a8` | `0x335194..0x3351b2` 将 MusicInfo.h 的地址写入 coverUrl，将 oa.c.H 的 Bitmap 写入 cover；同一音乐 Intent 的 song 也可能是歌词。 |
| classes4 `oa.c.H` `0x19a848` / `g` `0x19b540` | H 读字段m；g写m。`oa.c$c.a` `0x1996bc` 从ra.b读取 URI、主图及处理后的图，`0x1996f6..0x1996fe` 经g写入m，随后通知qa.b.C。 |
| classes4 `oa.c.F0` `0x19c0d8` | 从元数据取URI；`0x19c130..0x19c144` 与缓存URI相同则返回。新URI构造图片请求；无URI时取有效Bitmap，末尾交给ra.d.e。URI去重与歌词展示文字分开。 |
| classes4 `ra.d.e` `0x1a5c64` / `d` `0x1a5bf0` | URI走Glide Bitmap加载，Bitmap走异步处理；d取消未完成Future，再提交新任务。f `0x1a5cdc`取消未完成处理任务。不能将此路径解释成定时重试。 |
| classes4 `ra.d.c` `0x1a5b08` | 处理输入Bitmap后，在请求比较门和旧图有效时调用p.b；相同则回收新图并返回。不同则产生主图、派生图并异步回调。 |
| classes `common.utils.p.b` `0x44e254` | 先比较对象、宽高，再逐像素比较；回收图或像素不同返回false。不是只按URL或短哈希判断图内容。 |
| classes `common.utils.p.a` `0x44e174` | 按100×参数的质量压成JPEG、重新解码，再按参数缩放。ra.d.c传0.5f，结果经ra.b.f、oa.c$c.a进入m，即HUD cover的来源之一。此变换不构成本端必须使用同样质量/尺寸的Apple合同。 |
| classes4 `qa.b.C` `0x1a20b4` | 按来源取观察者列表，并向每项调用ma.d.s(uri, bitmap, bitmap)。这一层是内部图片观察通知，不能仅从方法名认定每次都会对外发送HUD。 |
| classes2 `f5.d.s` `0x335218` | 另一路先从oa.c.J的Bitmap生成bytes，成功写MusicInfo.w；无有效bytes才从oa.c.K的URI写MusicInfo.x。与q直接写HUD cover区分。 |

`oa.c.s` `0x19b7b0` 的无图片清理受虚方法d0门控制；本次读取的基类d0 `0x19aa24`恒false，不能宣称所有元数据缺图都会清理缓存。t `0x19b820`才是取消处理和清理j/k/m/l的实际入口；子类覆盖与完整换曲清理门另核。

## 已实施的封面恢复修复

Android `05fee8f`：`HostArtworkState.complete(request, null)` 原来保留来源身份，下一条同曲、同来源的真实宿主更新被永久抑制。现仅在当前代际加载失败时撤销来源缓存，使后续宿主事件可再次加载。加载中重复事件仍合并；成功来源、JPEG内容去重、过期请求与断开隔离继续生效。

新曲失败仍清除上一曲图片，同曲刷新失败保留当前图。没有定时重试或主动重发；这是本端失败缓存修复，没有将宿主内部加载器的行为直接复制为Apple协议。见[Android说明](../../../android/docs/fixes/2026-11-10-artwork-source-recovery.md)。

3项新增回归覆盖失败恢复、保持同曲图和过期失败隔离。桥接51项/9 suites、封面状态11项均无失败/错误/跳过，小米Debug Kotlin编译实际执行成功；协议任务UP-TO-DATE，沿用1110项/135 suites、零失败/错误/跳过结果。

R01频闪仍未关闭：歌词文字变化可以触发本端图片代际更新，慢加载可能被取消；宿主旧图与新文字也可能在不同时间到达。尚未将原设备日志的每次变化绑定到歌词或图片失败，不把本次恢复修复称为完整频闪根因修复。

其余边界：字节来源仍以32位contentHashCode作身份，碰撞可能抑制不同内容；URI相同不保证跨曲永远返回同一图片。需要可靠歌曲/来源身份和对应事件后，才能减少无意义重载而不让新曲接收旧图。本次未为这些候选创建额外生产修改。

## 语音键到助手任务

| 原位置 | 直接核对的分支 |
|---|---|
| classes6 `CarlifeHw.onKeyEvent` `0x0a98e8` | `0x0a9932..0x0a9940` 对UP直接返回true。原packed-switch的8107目标`0x0a9a50`，调用c1.g().o；8108目标`0x0a9a40`，调用c1.g().l，分别返回true。语音分支提前返回，不经过普通键的延迟/启动窗口。 |
| classes `c1.o` `0x45668c` / `l` `0x456634` | 分别调用已注册c1$a.b / c。callback为空时无动作，按键入口仍会返回true。 |
| classes2 `HomeActivity.M1` `0x1a6758` / `onDestroy` `0x1a7200` | `0x1a677a`注册HomeActivity$f；`0x1a7298`释放。 |
| classes2 `HomeActivity$f.b` `0x1a538c` | 小爱准备门未就绪则提示加载中并返回；就绪时调用voiceassistant.a.m，action为ACTION_DOCKER_VOICE_ICON_START_VOICE_ASSIST。 |
| classes2 `HomeActivity$f.c` `0x1a5340` | 同一准备门未就绪直接返回；就绪时调用a.m，action为ACTION_FORCE_STOP_VOICE_ASSIST。 |
| classes7 `voiceassistant.a.m` `0x0e682c` | 显式启动本包VoiceService，带fromTV=false、isCloseMic=false、queryOrigin=VoiceButtonAtDocker、disableVad=false、need_tts=true。强制停止action另通知内部a$g.onStop观察者。 |
| classes7 `VoiceService.processIntentInternal` `0x0ead0c` | START分支创建xh.a，停止原任务后调用wh.a.d；STOP分支调用stopEngine(true,true,0)。onCreate `0x0eac1c`从execute.j.B取得实际任务实例。 |
| classes7 `stopEngine` `0x0eaeb4` / `execute.j.a` `0x0f3ad4` / `d` `0x0f3fa4` | STOP转发内部停止及任务a；START转发任务d。任务通过Handler发布工作，START另发送what=1消息。以上调用不是识别成功或正在监听的回执。 |
| classes7 `execute.j$f.run` `0x0f3298` / `x` `0x0f38bc` / `K` `0x0f3ffc` | run构造Recognize事件，经x调用K；K在`0x0f4300`调用ASR入口i.T0，随后在`0x0f4306`写内部j=true。已核这些局部分支，不将内部标志当公开助手状态，i.T0到实际producer的完整SDK路径另核。 |
| classes7 `execute.j.w` `0x0f38a4` / `J` `0x0f3f28` / `j$a.run` `0x0f2dd0` | w转J，J调用i.S0；停止工作run取消现有execute任务，调用j.t并清掉当前xh.a。以上仍是宿主内部任务路径。 |
| classes6 `CarlifeConnService.g` `0x0a7888` | 正常初始化分支先`0x0a792e`登记audio listener，再`0x0a7956`登记key listener。此顺序不证明助手ready或已选择共享队列。 |

当前本端8107/8108的DOWN/UP投递符合这一入口。UP不是语音结束，不能将协议action3直接解释成宿主STOP。`VoiceButtonToggle`仍仅保存本地已接受请求；静态证据确认了宿主返回true也可能因callback缺失或小爱准备门而没有实际启动。因此不把downAccepted升级成助手运行确认。

## 麦克风选择的读取与消费

classes `e2.d.c` `0x476c98` 查询carlife_vr_use_phone_mic，读is_use_phone_mic；b `0x476bfc`查询carlife_vr_hu_wake_up_enable，读hu_wake_up_enable，缺回复默认false。

读取入口已经确定：classes6 `carlife.j.q` `0x0a7fd0` 收到 **carlife_notify_vehicle_channel** 时，`0x0a8066` 调用e2.a.u，之后才解析params/vehicle_channel。本次扫描原DEX的直接u调用只有这个位置，不能据此认定每次语音键都会重新查询。

`e2.a.u` `0x47660c`读取ucar_settings_data_bg中的carlife_is_use_phone_mic整数偏好。令P为is_use_phone_mic、W为hu_wake_up_enable：t=!P；默认枚举a时s=(!W || P)，枚举b时s=true，枚举c时s=P。o `0x4761c4`读t，p `0x4761dc`读s；经o1.a.c/d `0x519cd8/0x519d28`进入消费。s还可由o1.a.g `0x519e64`进入setter改变，因此不是不可更新的永久缓存。

本轮直接核对枚举`e2.a$a.<clinit>` `0x476018`：a=NONE/0、b=TRUE/1、c=FALSE/2。setter `e2.a.L` `0x4769d0`写s，并将true保存为b.ordinal、false保存为c.ordinal。classes2 `SettingsIndexAdapter.p0` `0x1fcbe0`在o1.a.c为false时提示不支持车机mic并返回；通过后在`0x1fcc40`调用o1.a.g更新选择，再同步两个radio状态。用户偏好有真实修改入口，本端不能用一条能力查询覆盖它。

classes5 `be.h.b` `0x1b2620` 在普通分支按o1.a.d选择：true创建be.g，false创建be.f；参数3/4有另外分支。g.d `0x1b20bc`直接AudioRecord.read，f.d `0x1b1fc8`调用DataBusClient.readAssistantRecorderData。后者的CarLife共享助手队列已在[宿主证据](carwith-4.0.14-host-evidence.md#g02共享-pcm-队列已定位未证明蜂窝上下行)核对，不构成蜂窝modem上行。

本端hu_wake_up_enable恒false，is_use_phone_mic取决于实际listener和协商输入是否就绪。**若进入上述初始化且采用默认枚举a，W=false会使s=true，即普通选择走AudioRecord；单独让P=false仍不会改变这个结果。** 但基类构造`0x476570`初始s=false、t=true，当前notifyVehicleChannel只保留入口、没有已接通调用，不能声称本次实车一定已执行u或命中该偏好。

继续OPEN：真实宿主初始化/偏好路径、准备门和开始录音时刻与协商输入ready的关系、listener实际收到PCM后的助手消费。未虚构vehicle_channel，未把“流已声明”冒充就绪，未改唤醒声明或自动刷新宿主配置。

## 音频状态不能作为识别自然结束

classes `i1.a.q/s` `0x495838/0x49597c`在相关状态门下启动/停止TTS输出short6和VR输出short3；`h1.j$d.a` `0x490714`实际读取的是输出录音源。TTS开始在`0x4907d2`调用h(0)、`0x4907e0`发布j(2,1)；VR输出开始在`0x490854`发布j(3,1)，停止在`0x490afa`发布j(3,0)。这是输出录音状态，不是麦克风识别完成证明。

两条公开回调独立：bh.d$c.a `0x0a4be4`传递category/state到系统音频回调；notifyAudioState `0x0a4ba4`经j.x `0x0a93a8`传递无类别整数到ICarLifeCastCallback。i1.a.h `0x495648`的notifyAudioState路径没有识别实例身份，PhoneAudioCast.q `0x432b24`与上述TTS开始都可产生此状态，不能把0/1当作助手运行/结束。

当前语音自然结束后本地requestedActive可能残留，导致下一次切换先发STOP，这是待核风险。内部onStopEngine/助手观察者到公开mixing接口的完整回传尚未闭合；没有宣称宿主绝无该回调，也没有用输出静音、category3停止或notifyAudioState猜结束。G07普通语音边界补证，增强Siri触发时间、历史/Aux及Apple语音资源状态仍OPEN。前一封面轮没有语音生产修复；本轮仅修复下述本端启动准备顺序。

## 已实施的语音启动准备修复

Android `8148ed5`：原协议动作先异步请求speech SETUP，随后立即排队发8107。CarWith语音DOWN会开始实际助手任务，本端没有保证队列输入已安装；手动8107此前不经过这条准备，切换到STOP也会提前请求SETUP。

现协议切换与手动键共用有序工作协程。START先保留请求、等待会话SETUP发布准备入口；有实际车端输入声明时复用speech请求，等待对应完成对象，再检查输入已安装、会话未结束且无电话占用，最后发DOWN/UP。完成对象在启动准备协程前发布，避免仅等待类别mutex可能先于worker取得锁。准备失败不发START、不改变本地requestedActive；断开撤销等待请求，取消/异常释放保留状态。STOP跳过准备，仍遵守队列顺序，不会超车或取消前项RTSP事务。

车端未声明输入能力时保留宿主自行选择手机输入的既有行为。输入有声明但准备失败时本次START被拒绝；本端尚不能读取宿主的明确手机mic偏好，无法区分该情形是否应继续启动。未改宿主query答复、W声明或偏好，未伪造vehicle_channel，未改变Apple SETUP或资源政策。安装ready和宿主DOWN接受都不等于助手实际消费PCM。

新增6项协程回归验证等待/不超车、失败后仍可START、手动和切换STOP跳过准备、断开拒绝迟到启动、取消释放请求、DOWN拒绝不提交状态。本轮core112项/19 suites、bridge51项/9 suites、protocol1110项/135 suites及小米Debug Kotlin编译实际执行通过，失败/错误/跳过均0。见[Android说明](../../../android/docs/fixes/2026-11-10-carwith-voice-preparation.md)。G07仍PARTIAL，录音源、自然结束及增强语音边界保留。

## 复核与实车范围

`python -B research/connection/tools/inspect_carwith_host.py D:\home\CarWith_4.0.14-20260801.apk`最新通过APK身份、6份DEX、101处指令哈希、3个距离字符串和原语音switch目标复核。它只验证原字节身份及位置，不运行宿主、助手或车机；完整code item哈希不等于每条SDK分支语义已闭合。

实车应分别验证：临时不可读封面恢复、连续歌词/换曲图片稳定；START日志中输入ready先于8107 DOWN，准备失败无START；8108停止、小爱未就绪、电话占用/断开等待和自然结束后再次发起；麦克风偏好、查询结果、协商输入与宿主实际PCM消费。尚未打包、安装、推送或实车验证。
