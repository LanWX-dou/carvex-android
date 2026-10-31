# A 结论汇总

每条结论给出：级别、可复算依据（地址或前序规则号）。`CONFIRMED` 表示本阶段重读过原始字节，
`INFERRED` 表示沿用前序冻结规则、本阶段未重跑，`OPEN` 表示无证据。

| ID | 结论 | 级别 | 依据 |
|---|---|---|---|
| A01.1 | SETUP 的 raw stream type 与包内 PT 是两套编号，不能互换 | CONFIRMED | `0x24fdad414..0x24fdad464`（PT 表）对比 SS-03（raw 枚举） |
| A01.2 | 接收侧只接受 PT {96,97,100,104,106,107,108,109}；101/105 仅发送 | CONFIRMED | `0x24fdad448` 掩码 `0x3d13`、`0x24fe44bc0` 名表 |
| A01.3 | 所述名字表包含音频、屏幕110/111与Playback120；它不是音频raw白名单，方向也不能由表本身推出 | CONFIRMED（表范围） | A01.6及FairPlay analysis14 |
| A01.4 | 同一 `raw100` 既可作媒体音（无 input）也可作麦克风（input=true） | INFERRED | MA-02、MR04、`0x2519be8f4..0x2519be91c` |
| A01.5 | `raw102` 在既定调用上下文映射到 `gen`(96)，属二次映射 | INFERRED | RL-02 |
| A01.6 | raw type → 名字表在 `0x2693e5da0`（索引 = type-96，25 槽）；108/109 = 带冗余的 aux/AVVC，110/111 = 屏幕流，120 = Playback；同一张表被 teardown 日志复用 | CONFIRMED | `0x2519c4564..0x2519c4594`、`0x251beecdd..0x251beed82`、`0x251beecbf` |
| A02.1 | 准入算法：首字节 0x80..0xBF、PT=第二字节低7位、PT∈96..109 且位掩码允许 | CONFIRMED | `0x24fdad41c..0x24fdad454` |
| A02.2 | PT 名表在 `0x24fe44bc0`（16 项 ×4B，索引 PT-96）；发送侧标签常量在 `0x24fdabdf4..` | CONFIRMED | 两地址原始字节 |
| A02.3 | SETUP 音频字段键名表在 `0x2693e7c00..0x2693e7d58`（CFString 常量槽） | CONFIRMED | `cftable 0x2693e7c00 44` 逐槽解出 |
| A02.4 | 音频字段按所述条件写入；高精度时间标志为true，RED标志须通过sp+5c门，不能说两个supports均无条件true | CONFIRMED | 0x2519be7ec..0x2519be958、A02.14 |
| A02.5 | 音频消息头为10B：seq BE16与两个BE32；消息M复制到内部I+2，不独自证明12B线上头 | CONFIRMED | A09.1、RTP analysis11原切片 |
| A02.6 | 本机 `dataPort>0` 时写入 `input=true` 与 `dataPort` 两个字段 | CONFIRMED | `0x2519be8f4..0x2519be91c` |
| A02.7 | `audioType=="telephony"` 且与 100 比较相等时追加 `vocoderInfo`（`w20` 未证是 raw type） | CONFIRMED | `0x27612e7b0`、`0x2519be878..0x2519be89c` |
| A02.8 | 加密记录尾 24 字节 = tag16 + nonce8（另有 16 字节档） | INFERRED | CR-01（`0x226e645f8`） |
| A02.9 | `audioType` 取值含 main/telephony/speechRecognition/default/alert/media | INFERRED | MA-06（仅 `telephony` 本阶段复核） |
| A02.10 | SETUP audioFormat取格式对象+0x60，以整数写入；本地CODEC/rate名称不是线上schema；基础映射及调用者转换已由A11.1/A11.4补齐 | CONFIRMED（类型/来源） | analysis10 §10.1、analysis11；0x2519be814..84c、0x2519c4558 |
| A02.11 | 码率与包大小上限只对支持 VBR 的格式生效；RED 支持是运行期判定 | CONFIRMED（字符串/路径） | `0x251bef139`、`0x251be40c4`、`0x251be44b9`、`0x251bef332` |
| A02.12 | 车机实际选哪个 `audioFormat`、帧长、码率来源仍未证 | OPEN | `OPEN-CODEC-1`、`OPEN-CODEC-2` |
| A02.13 | 有效正有限输入下pps=trunc(rate/spf)、packetSizeLimitBits=bitrate//pps；spf为整数；码率阶梯≤24k→48000、≤32k→64000、>32k→96000、raw102→256000；lpcm跳过码率设置 | CONFIRMED（局部算法） | analysis10 §10.4；0x2519bdec4..0x2519bdfbc |
| A02.14 | `supportsHighAccuracyTimestamps` 恒 true；`supportsRTPPacketRedundancy` 仅当 `[sp+0x5c]!=0`；`streamStartTimestamp` 与 `burstPeriodMs` **只在 raw==107（OutOfBandAVVCAudio）时**写入 | CONFIRMED | `0x2519be920..0x2519be98c`（`cmp w20,#0x6b`） |
| A02.15 | 独立resume路径：redundantAudio有符号≥1才写整数；对象+0x28等于LowLatencyAudio才写disableRetransmits=true，否则省略；CarPlay路径raw107的burstPeriodMs本地偏好缺失取200 | CONFIRMED（局部条件/默认） | analysis10 §10.2/10.3；0x251bbb90c..950、0x2519be7a8..7c4；接收默认/profile仍OPEN |
| A02.16 | `[sp+0x5c]` 这一个值同时决定「SETUP 里声明 supportsRTPPacketRedundancy」和「RED 深度 +1」，两者同源 | CONFIRMED | `0x2519be944..0x2519be958` 与 `0x2519bec48` |
| A02.17 | 能力键 `audioInputFormats`/`audioOutputFormats`/`audioOutputFormatsExtended`，以及 `CarPlayAudioFormats`、车机特例串 `BMW`/`NBTEvo` 都在固件里 | CONFIRMED | `0x251c36a29`、`0x251c36a3b`、`0x251c36707`、`0x251bedc87..0x251bedd8f` |
| A03.1 | RED 冗余头 4 字节：F=bit31、PT=bit30..24、delta=bit23..10、length=bit9..0 | CONFIRMED | `0x251ace454..0x251ace47c` |
| A03.2 | F=1 前进 4 字节，F=0 前进 1 字节并结束（主块头 1 字节） | CONFIRMED | `0x251ace484..0x251ace494` |
| A03.3 | 描述符总长 = 4*blocks-3 | INFERRED | RED-04（`0x2519c0934` 的 span 计算） |
| A03.4 | 块 seq = (outerSeq+index-(blocks-1))&0xFFFF；ts = outerTs-delta | INFERRED | RED-03、MR02（`0x251ace49c`） |
| A03.5 | 接收侧 RED 生效 PT：97/104/105/108/109，96 仅 maxPackets>1；与准入掩码在 105 上冲突 | INFERRED | RED-02 |
| A03.6 | 媒体路径 `maxPackets = 1 + (车机支持RED && 本流要RED)`，即深度只有 1 或 2；创建调用传 `(1, maxPackets)` | CONFIRMED | `0x2519bec3c..0x2519bec70`（`cinc w20,w8,ne`、`bl 0x2519c9460`） |
| A04.1 | 解密切片用 N-24 当密文长、tag 在密文尾、nonce 在最后 8 字节 | INFERRED | CR-01（`0x226e660ec`） |
| A04.2 | CoreUtils媒体接口salt为DataStream-Salt加整数，info分别31/32B不含NUL，key输出长度另外传入；实际音频方向/provider待绑定 | CONFIRMED（ABI）/ OPEN（profile） | 视频analysis06、控制面analysis15 |
| A04.3 | AAD入口为消息M[2:10]的8B，在已核内部复制后对应I[4:12]；不是任意网络packet[4:12] | CONFIRMED | 0x226e68b08..24、A09.1 |
| A04.4 | 认证失败不提交输出长度、不递增计数器；原实现可能已写输出缓冲 | INFERRED | CR-04 |
| A04.5 | 叶子层无 nonce 重放保护 | INFERRED | MR03（`0x226e660ec`） |
| A04.6 | CR-01的16/24B mode分支须与provider绑定；raw100 G非0的两个flag1构造不能推出所有音频恒24B | INFERRED（叶子布局）/ CONFIRMED（分派边界） | A09.3、FairPlay analysis14 |
| A05.1 | stream 对象槽：+0x90 format、+0xa0 sink、+0xa8 source、+0x178/+0x1c0 活动对象、+0x180/+0x1d0 两把密钥 | INFERRED | `microphone-rx` transaction.md |
| A05.2 | 输入暂存队列容量 20；就绪门 +0x170 / 暂存门 +0x198 四态表 | INFERRED | `0x2519c0f08`、`0x2519bdcf8..0x2519bde44` |
| A05.3 | sink 配置走 class+0x10(ASBD) 与 class+0x18()，两步都要求返回 0 | INFERRED | `0x2519bdcf8..0x2519bde44` |
| A05.4 | 混音/闪避/优先级无任何证据 | OPEN | 未见按 audioType 仲裁的分支 |
| A05.5 | 为让流呈「输入+输出」形态，固件会补一条哑输入流 | CONFIRMED（字符串） | `0x251bef21d` |
| A06.1 | 麦克风收包白名单 = {main,mred,oovc,ovrd}，其它立即返回 | CONFIRMED | `0x2519c0b88..0x2519c0c08` |
| A06.2 | 放行后 retain 并用 dispatch_async 投递到 `+0x168` 队列的块 `0x2519c0f08` | CONFIRMED | `0x2519c0c0c..0x2519c0c74` |
| A06.3 | 麦克风传输 ID 为 `minp`(0x6d696e70)、QoS3、UDP listener | INFERRED | `0x2519c8dac`、`0x24fda8e4c`、`0x24fdb1ec8` |
| A06.4 | 先建 listener/读 LocalNetworkPort 再发 SETUP；handler 创建返回值未检查 | INFERRED | `0x2519be194..0x2519be3f8` |
| A06.5 | InputKey 存 `+0x180` 并作为处理函数参数用于 mic 解密 | INFERRED | `0x2519c11d8..0x2519c11e4` |
| A06.6 | 存在telephony/speech状态限制日志；不能仅凭字符串推出所有语音全局互斥 | CONFIRMED（字符串）/ OPEN（迁移条件） | 0x251bef033、0x251bef021 |
| A07.1 | 单流 teardown = `tdwn` + streams 数组 + 可选 `teardownType` | INFERRED | TD-03（`0x2519ce5c4`） |
| A07.2 | 先本地注销再发送；sender 失败只记日志，整体可返回 0 | INFERRED | TD-02（`0x2519cce10`） |
| A07.3 | 整会话收尾用同一命令、无 streams、teardownType=2 | INFERRED | TD-05 |
| A07.4 | 幂等只覆盖本进程内重复调用，不覆盖重复发送/并发断链 | INFERRED | `0x2519cce10`、TD-01 |
| A08.1 | 本阶段没有任何 AirPlay 音频抓包 | CONFIRMED | `runtime/` 为空、全库无 pcap（见 08 §8.1） |
| A08.2 | 23G90 是 BT Classic iAP2，无法用于音频结论 | CONFIRMED | 该抓包帧头 `40 40`、无 UDP/RTP |
| A08.3 | `suspendInternal` 在 `+0xb8==0` 早退，前置失败不一定走完整清理 | INFERRED | `0x2519cd2d0` |

| A09.1 | M头10B、AAD M[2:10]、M→I+2均有原指令证据；网络适配未闭合 | CONFIRMED | analysis09 §9.1、相邻RTP原字节回归 |
| A09.2 | g无元素为0，有正常终止元素为4C-3；密码输入M[10+g:T]，不等于固定网络12B头/24B尾 | CONFIRMED（消息坐标） | analysis09 §9.2 |
| A09.3 | 算法受type/G/keyholder门共同决定，不从raw100两次构造推出所有音频恒24B | CONFIRMED（分派） | analysis09 §9.3、FairPlay analysis14 |

| A11.1 | 原APAudioFormatToASBD识别59个单个位ID，输出完整40B ASBD及可选bits；失败-6735且不改输出 | CONFIRMED（叶子映射/原指令执行） | analysis11 §11.1/11.5；spec11全表；C12共4286例 |
| A11.2 | repackage对能力集合逐位调用转换器，ID写格式对象+60，传输/HAL描述分存+10/+38；不是最终选最低位的证明 | CONFIRMED（局部数据流） | 0x251ade020..058、0x251ade704..764 |
| A11.3 | raw107及raw100的default/telephony/speechRecognition取audioInputFormats，其余取audioOutputFormats；不定义网络方向 | CONFIRMED（分支/常量） | 0x251adc910..9ac、analysis11 §11.4 |
| A11.4 | lpcm传输flags OR2、HAL清2；压缩格式保留传输描述另建PCM HAL，bits取第三输出 | CONFIRMED（转换块） | 0x251ade09c..174；C12执行59例，analysis11 §11.3 |

| A12.1 | audioFormats数组/条目字典/type读取检查错误；audioType typed getter以NULL error调用，缺键/错类型均返回NULL；extended存在时必须为数组 | CONFIRMED（局部schema/getter） | analysis12 §12.1；2段CoreUtils哈希与直接stub；C13 |
| A12.2 | 首个未指定或精确audioType项停止扫描，mask0不续扫；先前default覆盖非OR，仅Apple前缀允许回退 | CONFIRMED（顺序/回退） | 0x251adc470..6a8；analysis12 §12.2；8例本地模型非原解析执行 |
| A12.3 | +1c/+1f门选择三种基础mask，AND后0返回本地-6705；字段来自Create第三/第五参数低byte | CONFIRMED（掩码/参数来源） | 0x251adc6a8..6c4、808..83c；0x251adcc30/38；C13原块594例 |
| A12.4 | telephony及raw103偏好后置过滤无再次零检查，可成功输出mask0；raw103清bit23受输出指针门约束 | CONFIRMED（局部后置分支） | 0x251adc6c4..7b8；analysis12 §12.4；C13原块330例 |

## A.9 覆盖要求对照（12 项）

| # | 覆盖要求 | 状态 | 依据 | OPEN |
|---:|---|---|---|---|
| 1 | 音频流类型 | 部分确认 | A01.1、A01.2、A01.3 | `OPEN-AUD-1` |
| 2 | 编解码 | 部分确认 | A02.10、A02.11、A11.1–A11.4、A12.1–A12.4 | `OPEN-CODEC-1`、`OPEN-CODEC-2` |
| 3 | RTP 打包 | 部分确认 | A02.1、A02.2、A02.5、A02.8 | `OPEN-CRYPT-1` |
| 4 | RED | 部分确认 | A03.1、A03.2、A03.3、A03.4 | `OPEN-RED-1`、`OPEN-RED-2` |
| 5 | 解密 | 部分确认 | A04.1、A04.2、A04.3、A04.4 | `OPEN-CRYPT-1` |
| 6 | 媒体播放 | 部分确认 | A05.1、A05.2、A05.3 | `OPEN-PLAY-1` |
| 7 | 导航提示音 | OPEN | A05.4 | `OPEN-AUD-1` |
| 8 | 麦克风上行 | 部分确认 | A06.1、A06.2、A06.3、A06.4、A06.5 | `OPEN-MIC-1`、`OPEN-MIC-3` |
| 9 | 混音/闪避 | OPEN | A05.4 | `OPEN-PLAY-2` |
| 10 | 同步 | OPEN | A02.4 | `OPEN-PLAY-3` |
| 11 | TEARDOWN | 部分确认 | A07.1、A07.2、A07.3、A07.4 | `OPEN-TEAR-1`、`OPEN-TEAR-2` |
| 12 | 错误与版本 | 部分确认 | A08.1、A08.2、A08.3 | `OPEN-RUNTIME-1`、`OPEN-CODEC-3` |

计数：0 已确认 / 9 部分确认 / 3 OPEN。

## A.10 读这份汇总时要记住

- 静态字节能证明「设备侧怎么写、怎么切」，不能证明「车机怎么收」。所以 `CONFIRMED` 集中在
  结构层，业务层几乎全是 `INFERRED`/`OPEN`。
- 本阶段重读的「硬边界」变成四处：准入掩码（`A01.2`）、AAD（`A04.3`）、raw type 名字表
  （`A01.6`）、`audioFormat`整数类型（`A02.10`）。新增analysis10/C11核默认值及局部运算。
  消息坐标和条件性分派已有独立原字节回归，具体音频provider/profile与真实认证仍未闭合。
- 覆盖项尚无整体确认，是因为每项仍有具体静态/实现缺口；缺运行样本不妨碍确认局部协议规则，
  也不能把所有剩余问题归结为未知的车机选值。
