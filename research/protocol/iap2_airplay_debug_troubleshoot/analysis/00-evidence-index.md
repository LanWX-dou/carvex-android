# 证据索引与使用边界

复核日期：2026-10-26。不复制或改写原镜像、汇编、反编译C和抓包。
本目录不是 Apple 官方 CarPlay 规范。

## 分类

- STATIC：限定构建/函数路径的静态事实。
- STANDARD：公开标准或工具语法；不代表车机实现。
- SYNTHETIC：本地人工构造输入与输出；不代表真车失败样本。
- POLICY：本地诊断/安全策略；不冒充线上强制要求。
- OPEN：缺证据；不能从相同症状认定相同根因。

CONFIRMED 必须附上上述范围，不能单独写“已确认”。INFERRED 只描述假设和待排除项。

## 固件与仓库证据

| ID | 类型 | 路径/锚点 | 允许支持的结论 |
|---|---|---|---|
| E-LINK | STATIC | [帧与校验](../../iap2_link_establish/spec/02-framing-and-checksum.md)、[ACK/重传](../../iap2_link_establish/spec/04-seq-ack-retransmit.md) | 帧边界、校验宽度、模256序号；不是完整故障恢复策略 |
| E-AUTH | 样本23G90 | [设备认证](../../iap2_control_session/spec/11-device-authentication.md)、相邻runtime/verify-auth-sample.ps1 | 两次样本签名输入与方向；不验证完整信任链 |
| E-GATE | STATIC | [生命周期审计](../../iap2_input_business_lifecycle/analysis/12-lifecycle-and-empty-param-audit.md) | 24A446空TLV、方向、ACK偏移；epoch模型为POLICY |
| E-NOWPLAY | STATIC | [NowPlaying数据流](../../iap2_input_business_lifecycle/analysis/14-nowplaying-dataflow-audit.md) | 属性分组、三个设置字段去向、旧订阅替换与队列窗口门；不是完整计数幂等或播放器成功证据 |
| E-RECORD | STATIC | [记录类型补证](../../airplay_video_channel/analysis/02-screen-record-format.md) §4 | 统计2/5条件与本UserData路径并入type0；完整schema/接收状态仍待核 |
| E-VERIFY | STATIC | [Pair-Verify审计](../../airplay_control_plane/analysis/14-pair-verify-key-schedule.md) | TLV7状态不等于HTTP/RTSP状态；ACL与验签错误分支不可泛化 |
| E-DERIVE | STATIC | [派生门](../../airplay_control_plane/analysis/15-keyholder-role-and-hkdf.md)、CoreUtils `0x18be5021c` | type/state门及局部返回 -0x1a4f/-0x1a35；不是RTSP错误映射 |
| E-VIDEO | STATIC | [视频包装器](../../airplay_video_channel/analysis/06-wrapper-and-header-audit.md)、Sender `0x2519b508c` | 不连续payload触发 -0x4178；不是网络端口或验签错误 |
| E-SCREEN | STATIC | [屏幕AAD/分段](../../airplay_fairplay_crypto/analysis/11-screen-aad-and-record-boundaries.md) | 已核路径128B头AAD、每成功段推进nonce；不能混用音频8B |
| E-AUDIO | STATIC | [音频坐标](../../airplay_audio_mic_channel/analysis/09-message-coordinate-audit.md) | M头10B、AAD=M[2:10]；M与网络RTP映射仍缺 |
| E-CONFIG | STATIC | [音频字段](../../airplay_audio_mic_channel/analysis/10-config-field-audit.md)、[avcC与附件](../../airplay_video_channel/analysis/07-codec-config-and-flags.md)；两组C11 | audioFormat整数、spf截断、局部偏好默认/条件；avcC→type1与bit7/bit4附件来源；不是完整codec映射/IDR或互通证明 |
| E-FORMAT | STATIC / 原指令CPU仿真 | [整数映射与转换](../../airplay_audio_mic_channel/analysis/11-format-id-map-audit.md)、[59行格式表](../../airplay_audio_mic_channel/spec/11-format-id-map.md)；C12 | 基础ASBD/可选bits、传输/HAL变换与局部能力键；4286次原叶子+59次转换块，不证明完整协商/codec或真实播放 |
| E-CAPABILITY | STATIC / 原指令CPU仿真 / 本地模型 | [能力选择](../../airplay_audio_mic_channel/analysis/12-capability-policy-audit.md)、[限定规范](../../airplay_audio_mic_channel/spec/12-capability-selection.md)；C13 | 顺序遮蔽、先前default/Apple前缀回退、基础/后置零结果区别；924次原掩码块与8个顺序模型，不是完整CF解析/协商执行 |
| E-CONTROL | STATIC | [控制记录](../../airplay_control_plane/analysis/13-record-aad-nonce-and-key-direction.md) | 部分写续发同一密文，不重新加密推进nonce |

本轮直接重读 `f_2519b508c.s` 的52c4返回和 `f_18be5021c.s` 的240..328门控，
并复用相邻docset重反汇编校验。阅读C仅辅助，不用伪签名猜ABI。
本目录verify检查所依赖文件哈希与关键锚点；相邻完整verify另跑，不把局部锚点称完整语义证明。

## 外部一手资料（本轮已打开核对）

| ID | 来源 | 用途/边界 |
|---|---|---|
| E-RTSP | [RFC2326 §7、§11、§12.17](https://www.rfc-editor.org/rfc/rfc2326.html) | RTSP/1.0状态类别、CSeq关联；不是CarPlay扩展状态表，不称其为最新RTSP版本 |
| E-TSHARK | [TShark手册](https://www.wireshark.org/research/protocol/man-pages/tshark.html) | -f捕获/-Y显示、-D接口、-d显式解码；解码不等于认证成功 |
| E-BPF | [pcap-filter手册](https://www.wireshark.org/research/protocol/man-pages/pcap-filter.html) | host/port/proto过滤语法；不适用于所有链路类型 |
| E-DUMPCAP | [dumpcap手册](https://www.wireshark.org/research/protocol/man-pages/dumpcap.html) | 多接口pcapng、捕获长度/环形与停止条件；不保证当前平台暴露蓝牙接口 |
| E-BT | [btrfcomm字段表](https://www.wireshark.org/research/protocol/dfref/b/btrfcomm.html) | btrfcomm为显示协议名，不是BPF关键字 |
| E-TCP | [TCP字段表](https://www.wireshark.org/research/protocol/dfref/t/tcp.html) | tcp.stream、flags、analysis过滤；分析标记不是链路丢包的独立证明 |
| E-RTSP-FILTER | [RTSP字段表](https://www.wireshark.org/research/protocol/dfref/r/rtsp.html) | rtsp显示过滤仅对已解码内容有效 |

工具语法已按官方资料核对；当前环境未找到tshark/dumpcap/tcpdump，故本机编译过滤器为SKIP，
不是PASS。不得安装/启动采集来掩盖这一缺口。目标平台按spec/03完成验证后登记版本和结果。
