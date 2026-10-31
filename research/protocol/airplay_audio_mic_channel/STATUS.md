# STATUS

## 结论

当前为**部分完成**：方向是设备→车机媒体/导航音，车机→设备麦克风。
本轮已修正消息坐标和参考实现，不能声称“结构无缺口”或“音频通道已通”。

覆盖：0 已确认 / 9 部分确认 / 3 OPEN。20项未决仍保留，详见spec10。

## 本轮落实

- analysis12/spec12补充能力条目顺序、先前default覆盖及Apple前缀回退；不是合并所有匹配条目。
- C13核三种基础mask及后置过滤；后置清空可成功返回，不能将返回0等同于可用codec。
- analysis11/spec11补齐59个整数ID→基础ASBD的完整表；C12以4286次原ARM64叶子执行重新核验。
- 原Sender逐位调用、格式对象+60→SETUP绑定已核；另执行59次原调用者转换，区分基础/传输/HAL描述。
- 局部audioInputFormats/audioOutputFormats选择分支已核；没有把59项全当成车机能力或已实现codec。
- analysis10/C11核实SETUP audioFormat为整数，撤回字符串回显/缺省位深/伪ASBD算法。
- 核实spf整数与pps向零截断；LowLatencyAudio相等才写disableRetransmits=true。
- 核实raw107的burstPeriodMs本地偏好缺失默认200；不推广成车机缺键默认。
- 区分10B音频消息M、内部缓冲I和网络RTP；AAD入口是M[2:10]，不是无条件packet[4:12]。
- 明确无元素g=0；正常RED的g=4C-3，不误用无RED时的C=1。
- 撤回“所有音频恒24B”；算法受type/G/keyholder约束，NULL本层对象不是明文许可。
- DataStream的31/32是info标签长度，不含NUL；KDF/provider输入门复用已核专题。
- 标准RTP诊断解析器正确检查CSRC、扩展和padding，消息解析器不假冒网络适配。
- 增加设备侧build_message，显式区分元素解析、密码输入切片和认证后明文块解析。
- 撤回麦克风“参数(2,2)证明深度恒2”与“日志证明全部语音互斥”的过强结论。
- 任务书和实施指南不再将设备端写成车机接收播放器。

## 可复现验证

```powershell
python -B research/protocol/airplay_audio_mic_channel/reference-impl/gen_test_vectors.py
python -B firmware/tools/gen-audio-manifest.py research/protocol/airplay_audio_mic_channel
python -B research/protocol/airplay_audio_mic_channel/verify.py
```

C1–C9检查结构、引用、台账、清单及33条合成向量。
新增C10运行相邻RTP的固定镜像/原切片回归：9份audit切片及已有切片、58个锚点、
6个导入、12个调用者/计数案例和超限路径。需Capstone；缺依赖时不能算通过。
新增C11核4段Sender/cache一致性、2段CoreMedia固定哈希、49锚点、8个CFString、
CFBoolean导出、偏好跳板及5个导入索引标签，并验证截断反例。
需原dyld cache、固定CoreFoundation镜像及Capstone；缺任何依赖不能记PASS。
导入索引标签不代表所有原跳板均已独立解析；仅偏好跳板另作直接核验。
新增C12固定Support函数/常量页与原cache、核直接stub与22个Sender锚点；
4286次无hook原叶子执行+59次有界调用者转换、完整输出页哨兵及59行文档表一致性。
需Unicorn 2.1.4（本机隔离安装在firmware/tools/ipsw-research/.audit-deps）；安装/范围见analysis11。
这是原指令CPU仿真，不是原生音频服务、编码器或对端协商执行；缺依赖不能跳过后报通过。
新增C13固定Copy/Create原区间、2段getter哈希/直接stub、35锚点、7 CFStrings与8导入标签；
924次原掩码块执行与8个顺序模型反例。模型不是完整CF parser执行，比较/偏好结果为显式输入。
同样依赖原cache、Capstone及隔离Unicorn；缺依赖按失败处理。

旧split_record/aad_for的“网络12B头+24B尾”接口已撤回；新接口见spec08。
参考实现不执行认证、加解密、音频编解码或socket，不包含网络↔M适配。
合成full案例只联动描述符定位与消息切片，不将密文视为音频块。

## 尚缺哪些实现证据

| 范围 | 剩余缺口 |
|---|---|
| 网络与消息 | 完整收发适配、分片/扩展与端口绑定，不能从内部I形状猜网络头 |
| 密码 | 目标profile/provider、方向键、整数ID、nonce/尾格式与RED绑定 |
| 编解码 | 59行映射、传输/HAL转换及顺序匹配/局部过滤已核；数值转换、extended元素、构造器策略绑定、repackage交集/最终选择、运行期属性与codec附加配置仍缺 |
| 媒体发送 | 第一条可播放流、持续时序/RED/背压与实际车机播放 |
| 麦克风 | 车机采集格式、本设备解码、启停门控、语音/通话切换 |
| 多流/恢复 | 混音/闪避、时钟、资源依赖、teardown及重连确认 |
| 运行证据 | `OPEN-RUNTIME-1`：无本阶段AirPlay音频抓包，不能引用BT iAP2样本代替 |

部分旧编解码/生命周期规则仍需继续逐指令审核，本轮不宣称整个音频专题语义完成。
spec10已把每项取证拆为静态规则与目标运行结果；撤回必须先拿两份抓包才能推进CODEC/PORT/MIC的前提。
20项仍未整体关闭；整数映射子问题已实质关闭，CODEC-1/2缩小。新增的是原指令仿真证据，没有真实音频互通证据。
原指令补证见 [analysis09](analysis/09-message-coordinate-audit.md)，方向与实施见 [spec08](spec/08-client-guide.md)。
