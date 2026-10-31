# 11 整数格式映射、调用者转换与能力键

24A446：本轮重新读取当前原cache/提取镜像，并在Unicorn中执行原ARM64叶子函数。
旧 `firmware/analysis/24A446/carplay-audio-transaction` 仅用于定位与独立预期对照，
不是直接沿用历史PASS。未改原bin、汇编、Ghidra C或冻结报告。

## 11.1 APAudioFormatToASBD 全函数

AirPlaySupport `0x226ee09d8..0x226ee144c`：导出名、function-starts边界与提取镜像均已核。
镜像SHA256 `d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15`；
完整函数原字节SHA256 `50b1f8a4a243419597d4d3420e501841bd54268781a6ecb40ca5d28be19d990f`；
常量页 `0x226f30000..0x226f31000` SHA256
`56afbab3d862199ebe55cb900aba7aff896e7eafb2d95d9a0480f5d7e0d3c840`。

ABI：x0=64位格式ID，x1=可写40B ASBD，x2=可选4B bits输出（可NULL）。
函数没有外部调用；比较树逐一匹配59个单个位值，其余走错误出口。
其中bit63通过有符号分支中的精确比较匹配，不可因符号位而丢弃。

ASBD内存布局为little-endian double + 8个u32：

| 偏移 | 字段 |
|---|---|
| +00 | mSampleRate（double） |
| +08 | mFormatID（FourCC数值） |
| +0c | mFormatFlags |
| +10 | mBytesPerPacket |
| +14 | mFramesPerPacket |
| +18 | mBytesPerFrame |
| +1c | mChannelsPerFrame |
| +20 | mBitsPerChannel |
| +24 | mReserved=0 |

`0x226ee11e4..11f0` 写40B ASBD；x2非NULL时后段另确定bits并写入。
不要把第三输出与mBitsPerChannel合并：例如bit19的ALAC ASBD bits=0、flags=3、
F/packet=352，另报bits=24；bit23的aac空格格式ASBD bits=0、F/packet=1024，另报bits=16。
失败出口 `0x226ee143c` 返回w8中的0xffffe5b1（-6735），不写输出。
未证有效格式下允许NULL x1；本轮只用有效目的区，不把无效指针行为纳入客户端契约。

59行完整映射在[spec11](../spec/11-format-id-map.md)。它不来自名称字符串解析，
也不表示59种格式均被CarPlay车机声明/选中或已实现编解码器。

## 11.2 Sender调用绑定：能力集合逐位生成格式对象

`carPlayAudioFormat_repackageFormatsForStream` 原范围 `0x251addd00..0x251adebd4`：

1. `0x251ade020` 令x20=1；`0x251ade030..38` 用x20与候选集合相与，为0跳过。
2. `0x251ade04c..58` 以x20为x0、栈上40B描述为x1、bits为x2调用 `0x25810c7c0`。
   原跳板为ADRP/ADD/BR，直接目标就是AirPlaySupport `0x226ee09d8`。
3. 成功后有下节的描述转换；`0x251ade704..70c` 将传输描述复制到格式对象+0x10..+0x37。
   `0x251ade710..720` 将HAL描述复制到+0x38..+0x5f，随后同一stp将x20写入+0x60。
4. `0x251ade75c..764` x20左移一位，循环共64个位。+0x60由analysis10的getter读取，
   SETUP以整数写入audioFormat。候选集合与最终单个格式ID因此是两个层次。

这已将原转换函数与SETUP字段来源连接起来，不是孤立工具函数存在性证据。
候选条目的顺序匹配、default回退与局部过滤已补在analysis12；repackage交集、排序与最终选中哪个对象仍须继续追；
不能把遍历低位到高位解释为最终总选最低位。

## 11.3 必须区分基础、传输与HAL描述

原调用者 `0x251ade09c..174` 在转换成功后继续处理：

- 若FourCC==lpcm：`0x251ade0a8..b0` 将基础描述flags OR 0x02，作为传输描述。
  `0x251ade0dc..f4` 复制到HAL区后清除flags的0x02，其余40B字段不改。
- 若非lpcm：传输描述保持转换结果；HAL描述改成lpcm，采样率/声道来自基础描述，
  bits来自转换器第三输出。令 `bytesPerSample=(bits+7)>>3`，
  B/packet=B/frame=bytesPerSample*channels，F/packet=1，reserved=0。
  bits按8对齐时flags=0x0c，否则0x14（`0x251ade110..15c`）。
- `0x251ade170` 在HAL区+0x28/+0x30另外写两份采样率double；该数组条目跨度56B，
  只有前40B作为HAL ASBD复制进格式对象，不能把56B整体误认为线上协议载荷。

例：bit15基础lpcm/48000/2ch/16bit flags=12，传输flags=14，HAL flags=12。
bit46基础lpcm/48000/2ch/32bit flags=1，传输flags=3，HAL flags=1。
bit23基础aac空格/48000/2ch，传输F/packet=1024，HAL转成lpcm/16bit、4B/frame、1F/packet。
本章固定数值转换，不把不同codec的flags任意套成同一语义，也不证明所有网络PCM字节处理已闭合。

## 11.4 能力键选择

Sender `0x251adc910..0x251adc9ac` 原分支及原CFString已核：

- w0==107直接返回audioInputFormats；
- w0==100时，audioType经CFEqual与default、telephony、speechRecognition依次比较，
  任一相等返回audioInputFormats；
- 其它返回audioOutputFormats。

常量分别为 `0x2761319f0`、`0x27612e7b0`、`0x27612e830`、
`0x276139970`、`0x276139990`，均由原cache读取内容，不靠地址名字猜测。
CFEqual在本轮C12只核导入索引标签与静态分支，未用指针相等替代真实CF字符串比较运行。
此规则不定义网络方向、密钥方向或完整raw枚举。

## 11.5 可复现验证

`tools/verify-format-map.py`（C12）：

- 固定Support镜像、完整函数、常量页；与原cache逐字节一致，直接stub目标与导出名匹配。
- 2143个输入：全部64个单个位、全部2016个两位组合、0、全1及密集低位掩码，去重后计数。
  每个输入分别在x2有效/NULL时运行，共4286次；比较返回、完整ASBD、可选bits及整个输出页哨兵。
- 原叶子直接在Unicorn执行，没有指令替换、PAC替换或外部API hook；只映射代码/常量/隔离输出内存，
  每次限4096条指令并必须返回哨兵地址。不执行编码器、操作系统音频服务或网络协商。
- 对59个合法输出再执行调用者的原 `0x251ade09c..174` 块，核传输/HAL变换及全部内存边界。
  限定初始codec状态w19=0，不冒称执行完整repackage的过滤/一致性/分配/错误日志路径。
- 22个Sender锚点、5个CFString；59行文档表与原执行逐字节对应的预期完全一致，禁止额外/重复行。

依赖：Capstone、Unicorn 2.1.4、原dyld cache、固定Support/Sender镜像和历史描述表固定哈希。
本机Unicorn安装在 `firmware/tools/ipsw-research/.audit-deps`，不改系统包；
可复现安装：`python -m pip install --target firmware/tools/ipsw-research/.audit-deps unicorn==2.1.4`。
缺依赖应失败而非SKIP/PASS；不能直接运行旧probe脚本覆盖已冻结报告。

本轮关闭OPEN-CODEC-1内“整数→基础ASBD映射”子问题，缩小CODEC-2的帧长/位深来源；
完整能力解析/选择、codec附加配置、运行期属性/端口/网络封装仍未完成，保留原大项。
