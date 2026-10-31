# 09 音频消息坐标与密码路径纠错

本轮重新读取现有Sender/Support原切片，并运行相邻RTP专题的原字节回归。
范围为24A446静态调用链，没有真实音频抓包或密码原语执行。

## 9.1 M、I、网络包是三个不同概念（A09.1）

原切片在`../airplay_rtp_timing/source/asm-audit/`与`source/asm/`，镜像SHA固定为：

- Sender：`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`
- Support：`d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15`

GetAudioDataHeader（0x226e689e0）在68a08..10以offset0/length10复制消息头，
68a20、68a30分别转换16位及两份32位字段。GetAudioAADPointer（0x226e68af0）
在68b08以offset2取消息指针，68b20/24返回长度8。

ReadNewMessage（0x2519c0c90）在c0d24取得M的数据指针，在c0d40/44复制到I+2；
c0d4c将独立参数PT写到I+1，c0d54..60存L=消息总长T+2。I+0未在这里写入。

| 字段 | 消息M | 内部缓冲I |
|---|---|---|
| seq BE16 | 0..1 | 2..3 |
| timestamp BE32 | 2..5 | 4..7 |
| 第二BE32 | 6..9 | 8..11 |
| 元素/音频数据 | 10起 | 12起 |
| AAD入口范围 | 2..9 | 4..11 |

这只闭合内部坐标，不能直接将I称完整线上RTP包。标准RTP另有CSRC、扩展头、padding，
即使某入口接受首字节0x80..BF，也不代表解析器可以一律把payload放在12。
当前参考实现把标准RTP诊断解析与M消息编解码分开，网络↔M桥接保持未实现、未证。

## 9.2 元素与加密输入（A09.2）

正常RED计数以1开始，每个4B冗余元素加1，遇1B主元素终止：C=n+1，g=4C-3=4n+1。
无元素分支虽也可存C=1，但不应用g公式。完整连续消息的解密起点/长度为M+10+g、T-10-g；
对应内部I+12+g、L-12-g。调用者及58个锚点详见相邻RTP analysis11及verify_audio_message.py。

发送侧槽+8返回附加输出长度h；主路径和转码后处理跳过10B头及g字节元素，
只处理音频数据并预留h。该局部证据不能推广为每种profile固定tag16+nonce8。
描述符可以先读，但冗余length和主块余量的音频数据拆分应在对应认证/解密后进行。
此前参考代码将未经认证密文切成块并给出“full联动通过”，现已拆为描述符定位与明文块解析两类测试。

## 9.3 不从raw100两次构造推导所有音频（A09.3）

依赖FairPlay analysis14的type/G/keyholder联合分派证据：raw100在G≠0时创建两个flag=1对象，
而96/102/103在G=0时走CBC。其它NULL返回也不证明线上明文许可。
所以旧“音频恒24B、只实现24B”不成立。CR-01的mode分支仍须与实际provider绑定后使用。

DataStream info长度分别31/32B，不是两条32B标签；输出key长度是独立实参。
视频analysis06已核该ABI/原字符串，控制面analysis15已核CoreUtils provider的HKDF-SHA512门。
本专题仍缺实际音频profile的provider/方向/整数ID来源、nonce库调用及外层网络映射。

## 9.4 可执行回归与限制

本集C10调用相邻RTP的verify_audio_message.py，固定SHA、完整切片/重反汇编、58个锚点、
6个导入、12个调用者/计数案例及超限路径；本目录不复制或改写原切片。
本集C7合成向量另验证标准RTP变长头、M的10B编码/AAD、显式尾布局、负span与RED边界。
所有输出均未经密码认证；这些测试没有执行网络握手或真实编解码，不能关闭真实互通项。
