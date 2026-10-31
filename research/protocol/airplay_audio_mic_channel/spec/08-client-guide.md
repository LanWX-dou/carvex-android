# 08 设备侧客户端实现指南

#### R-8.1 以设备端角色分层
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A01.1`、`A06.1`、`A09.1`

媒体/导航音由设备编码后发给车机；车机麦克风由设备接收、认证解码并交语音业务。
不能把L2写成“本设备接收媒体并播放”、把麦克风写成本设备采集送给车机。

建议顺序：离线消息/RED编解码→适用认证与控制会话→媒体发送→麦克风接收→多流/同步/恢复。
各层的静态、合成和真实车机测试分别记录；结构自检不是网络可用判据。

#### R-8.2 分开网络与内部消息
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A09.1`、`A09.2`

参考实现API：

- parse_header(packet)：标准RTP诊断解析，处理CSRC/扩展/填充；不证明Apple支持所有这些组合。
- build_message / parse_message_header：10B内部M消息头，供发送端构造与回归。
- aad_for_message(M)：M[2:10]，不是任意packet[4:12]。
- parse_descriptors：只读元素前缀，输出仍未经认证。
- split_message_record(M, element_span, trailer_layout=...)：显式本地尾布局；不解密。
- parse_red(clear_payload, seq, ts)：仅拆已认证或明确合成的明文RED块。

网络↔M适配仍待核，不能在M前加两个猜测字节就宣称能发CarPlay音频。

#### R-8.3 SETUP与能力绑定
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A02.3`、`A02.4`、`A02.14`

选定真实端点、方向、type及能力交集；字段写入条件见spec02。
能力条目的顺序匹配、Apple前缀default回退及局部过滤见spec12；不能合并所有同类条目，
不能从候选获取函数返回0直接推定mask非0。构造器策略输入与最终选择仍需继续绑定。
按spec11将选中单个整数ID映射到基础描述，再应用传输/HAL转换；不能传候选集合，
不能把表中59项全声明成已实现能力，也不能把HAL帧长替换传输帧长。
supportsRTPPacketRedundancy不是无条件true；声明支持也不等于每包必带冗余。
目前不提供带猜测audioType/格式/端口的“最小可用请求”。应记录完整请求/响应并核验流身份；
本地构造成功不等于对端可播放。

#### R-8.4 媒体发送
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A09.2`、`A09.3`、`A02.12`

为每条流配置适用编码器/帧长/时钟，生成消息头与可选元素、编码数据，
按所选provider进行加密后处理及附加输出，再经已核网络适配发送。
关联消息长度、元素区、音频区、附加输出及发送结果，不能用本地解码播放替代发送验收。
独立接收器解码是交叉验证工具；最终需要车机持续播放、时间同步及错误恢复证据。

#### R-8.5 麦克风接收
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A06.1`、`A06.4`、`A06.5`

适用input transport路径先建监听并取得本机端口，再按条件写input/dataPort，
等待协商及有效会话状态；收到车机数据后做网络适配、流类型门控、认证、块拆分和解码。
将PCM交给本设备语音/通话业务，而不是默认播放到本机扬声器或发回车机。
能力键选择函数已核为R-11.5；它不单独定义端点方向，仍需和具体业务/收发路径绑定。

#### R-8.6 收尾与恢复
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A07.1`、`A07.4`

测试正常停流、直接断链、部分SETUP失败、重复teardown与重连。
区分本地清理、tdwn发送、对端确认及密码上下文失效；不把本地返回0当对端已释放。
重连后重新验证状态有效性，不盲复用旧key也不无条件重置同key下nonce。

#### R-8.7 参考实现验证
级别：MAY ｜ 证据：CONFIRMED ｜ 依据：`reference-impl/`

在仓库根执行：

```powershell
python -B research/protocol/airplay_audio_mic_channel/reference-impl/gen_test_vectors.py
python -B firmware/tools/gen-audio-manifest.py research/protocol/airplay_audio_mic_channel
python -B research/protocol/airplay_audio_mic_channel/verify.py
```

向量是合成字节/结构边界测试，没有密钥、认证、编码器或socket。
旧split_record/aad_for网络偏移接口已撤回，避免继续将10B消息与网络头混用。

#### R-8.8 不以有声音代替完整验收
级别：MUST NOT ｜ 证据：CONFIRMED ｜ 依据：`A08.1`、`A09.1`

验收须区分设备→车机媒体、车机→设备麦克风、多流、RED、时序、密码状态及停流恢复。
每项注明静态、合成或真车；没有真实媒体样本时不能声称音频通道已通。

#### R-8.9 日志
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A04.4`、`A07.4`

记录流/方向、选定profile、raw type和PT的分别取值、消息长度、元素长度、附加输出长度、
包序号缺口、认证结果、状态迁移和teardown阶段；避免输出原始密钥/共享秘密。
