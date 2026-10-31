# STATUS — airplay_video_channel

当前为**部分完成**。目标是指导设备侧向CarPlay车机发送视频，尚无本阶段真实车机媒体抓包，不能保证投屏互通。

## 已核与本轮纠错

- analysis07/C11核实avc1门下avcC CFData进入type1配置body，变化触发构造并在本地组装于帧前；不推广所有profile/NAL格式。
- +05 bit7来自APInterestingFrame，不再猜成关键帧；bit4来自NotSync附件读取结果，仍不等于NAL IDR证明。
- NotSync getter原函数已核：首个合法CFBoolean即停止（false也停止），无合法值bit4=1；不是all/any归并。
- 包装器原地处理连续载荷，独立缓冲仅用于附加输出；NULL cryptor的局部no-op不是明文降级许可。
- DataStream派生的31/32是info标签字节长度，不含NUL；输出密钥长度另传。CoreUtils与Legacy派生不可混用。
- type110/111在keyholder等门通过后按内部属性选择CTR或ChaCha(flag=0)，不是视频恒ChaCha。
- 记录可有第二次加密调用；+470是构造计数且有清零路径，不是已证密码nonce或送达计数。
- 帧间隔阈值更正为65536ms，且先做ticks→ms转换；16槽不能推出一批最多16帧。
- 长度字段不能直接填明文长度；配置10个float的+18..1f有空隙，不能连续打包。
- 已核接收侧128B头AAD与N/E分段证据已从FairPlay专题接入，未外推成所有profile。
- 统计头type2/5按storage+3c5的零/非零分支已核；本函数UserData并入type0、附加长度写+1c，
  不能按构造器名字猜独立类型。完整schema/控制位来源仍待核（analysis02 §4）。

详见 [analysis06](analysis/06-wrapper-and-header-audit.md)、[加密规范](spec/03-encryption.md)及[实施指南](spec/07-client-implementation-guide.md)。

## 十二项覆盖

| # | 要求 | 状态 | 主要未决 |
|---|---|---|---|
| 1 | 建流 | 部分确认 | 类型/显示语义、完整SETUP、传输选择 |
| 2 | 视频封装 | OPEN | Annex-B/AVCC、NAL及参数集路径 |
| 3 | 128B记录 | 部分确认 | 未知字段/其它记录类型语义 |
| 4 | 访问单元/时间戳 | 部分确认 | 聚合责任、时间基准 |
| 5 | 加密位置与顺序 | 部分确认 | profile、发送cryptor绑定、nonce与附加输出 |
| 6 | SPS/PPS | OPEN | avcC→type1通路/变化触发已核；内部布局、帧内重复及完整profile仍缺 |
| 7 | 关键帧 | 部分确认 | bit7/bit4附件来源已核；实际IDR/forceKeyFrame因果链待核 |
| 8 | 解码约束 | 部分确认 | 协商blob与参数来源 |
| 9 | 显示与同步 | 部分确认 | 几何字段业务语义、时间同步 |
| 10 | 重连 | 部分确认 | 触发条件、密码状态失效与重建 |
| 11 | 错误分类 | OPEN | 原始错误与协议响应、现象的关联 |
| 12 | 版本与性能 | OPEN | 码率/帧率/GOP与profile限制 |

覆盖台账仍为0已确认/8部分确认/4 OPEN、14个未决项；纠错不是提高完成度的理由。

## 证据及验证边界

本目录保留23个Sender函数原切片与23个Ghidra导出，为11,443函数的定向抽样，不是全栈精读。
跨目录依赖为FairPlay的分派、KDF、屏幕AAD与控制面的provider派生证据。
9篇analysis（00–07及A表），9篇spec；计数及文件哈希以manifest为准。

C1–C9检查结构/引用/原切片等；新增C10对五份原切片重反汇编并核对包装器、标签、记录字段锚点。
C10现核65个锚点，另检查统计控制byte的256种局部分支结果；OPEN-VID-2缩小但未整体关闭。
C11核3段Sender/cache原代码一致性、47锚点、4个CFString、CFBoolean导出及12个导入索引标签。
新增NotSync完整getter与2个ABI helper固定哈希、19锚点、6个直接跳板/导出名、341组局部附件序列。
需要原dyld cache、固定CoreFoundation/CoreMedia镜像及Capstone；缺依赖不能算PASS。
12个导入索引标签核对不等于所有跳板目标均已独立解析；NotSync相关6个跳板另有直接核验。
这些不是密码原语执行、完整固件仿真或车机互通测试。

```powershell
python -B research/protocol/airplay_video_channel/tools/manifest.py
python -B research/protocol/airplay_video_channel/verify.py
```

C10需要Capstone 5.0.7。跨目录密码证据需另外运行相邻专题verify；本目录通过不代表这些依赖全部重测。

## 后续工作

继续追avcC/参数集与关键帧状态、长度额外项来源、wrapper实际cryptor绑定、SETUP字段及显示/传输选择。
只有静态证据和profile级真实通信验收相互支持，才能声称可指导完整兼容实现。
