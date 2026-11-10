# G01–G11 按优先级实施记录

日期：2026-11-10。按用户要求逐项修复，每项代码独立提交并同步证据与研究仓库引用。
基线Android `2cbfdd3`，研究仓库 `319f335`。不打包或推送；实车结果另行记录。

顺序采用原续查建议：P0为G04、G01、G02；P1为G03、G05、G08、G11；P2为G06、G07、G09、G10。
优先级排序不允许跳过证据或用空实现关闭问题。某项存在不可实现的外部前提时，记录其具体边界并继续其他可独立工作。

| 顺序 | 缺口 | 当前实施状态 |
|---|---|---|
| 1 | G04 / P0 | `dbf1c99` 已修正有序候选读取、零集合遮蔽、default覆盖、Apple前缀门和扩展保存；14项新增回归、协议1099项与桥接27项通过，小米编译通过。最终单格式选择/政策绑定/扩展schema仍OPEN。 |
| 2 | G01 / P0 | `be8fd40` 已修正拒绝资源事务后仍发布空modesChanged的问题；5项新增回归、协议1104项及小米编译通过。优先级/约束枚举已核，实际仲裁消费者、临时借用与应用状态联动仍OPEN；不把字段解析当作仲裁实现。 |
| 3 | G02 / P0 | 已取得CarWith原APK并追通mic共享队列→readAssistantRecorderData→SDK读取适配器，仍未证明蜂窝modem/HAL消费者、专用下行及逐通电话快照。见[宿主证据](carwith-4.0.14-host-evidence.md)。不把OFFHOOK或普通助手队列当蜂窝接通/上行。 |
| 4 | G03 / P1 | `175c048` 已核并落实isNavi=false/action3的结束缓存清理；7项新增回归、协议1110项/桥接41项及小米编译通过。原宿主距离转换已核，但活动道路/距离的iAP语义、guidanceState/机动/车道仍OPEN，见[宿主证据](carwith-4.0.14-host-evidence.md)。 |
| 5 | G05 / P1 | `75ec5b2` 已修正100/101控制传输及controlPort/spf存在性，3项新增回归、协议1107项与小米编译通过；延迟首字段已追到本地政策对象，不从接收端微秒值换算；政策绑定及采集时钟仍OPEN。 |
| 6 | G08 / P1 | `de453e0` 已补标准系统快进/快退键及实际DOWN/UP、并行按住计数与断开清理；10项新增桥接回归、桥接37项及小米编译通过。目标应用持续seek及UP停止效果仍OPEN，不能把投递当播放确认。 |
| 7 | G11 / P1 | 已区分现有代码的网络复用观察与specifier请求路径，两处onLost仍立即失败。L2到网络租约事件的映射尚无证据；本轮Android在线源码获取连接超时，不添加猜测等待或自动重绑。 |
| 8 | G06 / P2 | 宿主只有实时onAudioStreamReady，缺可提前传输的数据源与媒体时间线控制；生产路由只有100/101/102。增强缓冲的CarPlay流选择和清除/重入队合同仍OPEN，不能把实时PCM暂存当此能力。 |
| 9 | G07 / P2 | 宿主仅有通用麦克风PCM/语音动作，无历史触发时刻或Aux消费者。原107时间戳/突发字段有独立分支，单位/宿主映射与增强Siri声明未闭合，不新增空历史缓冲或猜测时间换算。 |
| 10 | G09 / P2 | 已核当前原始配置证据仅闭合avc1/avcC分支；bit42不是HEVC封装合同。需继续闭合HEVC格式描述序列化、接收选择及编码样本，当前不发送猜测hvcC/帧正文。 |
| 11 | G10 / P2 | 已核宿主/Screen/编码与媒体socket单实例，focusOffer无位置消费者；每屏身份/Surface/动态区域及触摸同步合同缺失，当前不将候选列表循环当多屏实现。 |

G04实施说明见[Android记录](../../../android/docs/fixes/2026-11-10-g04-audio-candidates.md)。
原始规则及缺口关闭条件继续以[统一台账](90-open-items.md#34-官方资料续查后的实现缺口2026-11-10)为准。

G01、G05、G08的具体差异、证据边界和回归分别见
[资源通知](../../../android/docs/fixes/2026-11-10-g01-mode-notification.md)、
[输出控制传输](../../../android/docs/fixes/2026-11-10-g05-output-control.md)、
[媒体按键边沿](../../../android/docs/fixes/2026-11-10-g08-media-key-edges.md)。
累计共有5项局部代码修复；未将任何一个完整缺口标为关闭，也未为没有实现的项目创建空代码提交。

## 后续实施需要补齐的具体输入

| 缺口 | 本轮核对的入口 | 尚需补齐 |
|---|---|---|
| G01剩余 | 原请求解析0x251afaf28/0x251afb2e0与完整状态提交0x2519b97ec | 原资源政策消费者及appState仲裁；不能只复制优先级枚举。 |
| G02 | Host-api CastHost、现有ISystemAudioCallback/IRemoteAudioListener及PhoneCallMonitor | 专用蜂窝上下行消费者、逐通电话生命周期来源、4155/4158发布门；通用listener不能证明调制解调器上行。 |
| G03 | CarWith原DEX生产者、SessionController及NavigationGuidance | 生命周期及米制转换已核；尚需外部地图完整语义、iAP单位/状态映射、navi_turn与机动/车道生产链；原iAP编码器不能证明宿主枚举相同。 |
| G05剩余 | GetLatencyInfo 0x2519bbf0c、repackage 0x251ade434..0x251ade474 | 本地政策构造参数/选择绑定及真实采集时间映射；SETUP首字段不是接收端微秒延迟除以1000。 |
| G08剩余 | 系统媒体键投递和HID边沿回归 | 目标应用begin/end seek消费者或实机按住/释放/取消结果；AudioManager无播放成功回执。 |
| G11 | Bootstrap复用monitor与specifier callback | Android版本对应的callback/网络撤销语义、L2/租约/socket关联记录、可保留socket的条件；区分静态策略与运行验证。 |
| G06/G07 | 实时宿主PCM契约及原音频类型/107字段分支 | 可提前读取的内容与时间线控制；车端增强Siri声明、触发时间和历史/Aux消费合同。 |
| G09 | 原avc1/模式门0x2519b04cc..0x2519b04fc与配置构造0x251b43ff8..0x251b44024 | HEVC独立配置/帧生产路径和对端接收合同；AVC证据不能覆盖该分支。 |
| G10 | DisplayCapabilities.select、单Screen与单host Surface、deviceOfferFocus | 每屏能力和内容来源、身份/会话关联、区域变更/触摸/焦点消费者。 |

用户已提供CarWith `4.0.14-20260801` APK；来源/哈希及18处原DEX字节定位见[宿主证据](carwith-4.0.14-host-evidence.md)。用户另明确确认本机没有原始24A446 IPSW或dyld cache；保留跨库资源政策/绑定边界，继续读取已有提取物。
缺口中属于原固件静态调用链的部分仍须继续取证，不能将“没有抓包”当作这些静态问题的阻塞理由。
最新本地结果：协议1110项、桥接41项无失败/错误/跳过，小米Debug Kotlin编译通过；原APK字节身份与定位复核通过。
研究全目录 `validate_docset.py` 仍报告既有3份JSON非法转义、历史带行号路径及根目录/spec布局不一致，未将其报告为通过；本次新增证据JSON独立解析/复核通过，新增引用目标均存在，whitespace检查通过。
未打包、推送或进行实车测试。
