# 07 avcC配置记录与帧标志原指令审计

范围：24A446 AirPlaySender `_screenstream_dequeueAndProcessSampleBuffer`
（`0x2519b0014..0x2519b15a4`）、配置构造器 `0x251b43fcc..0x251b44300`，
以及附件helper `0x251b44f90..0x251b44fa8`。以下为局部静态路径，不推广到所有profile/UDP/HEVC。

## 07.1 从格式描述取avcC并缓存

1. `0x2519b0070..74` 将storage+0x208地址保存sp+0x70。
2. `0x2519b04cc..04fc` 取sample格式描述和media subtype；subtype等于avc1（0x61766331）
   且storage+0x3c8==0时进入 `0x2519b061c` 分支。
3. `0x2519b061c..0660` 调CMFormatDescriptionGetExtension取
   `SampleDescriptionExtensionAtoms`。键的原cache指针链：
   `0x2680d44d0 → 0x1e09fd170 → 0x1e9fe5188`。结果为字典时取
   CFString `0x27613fe10`（avcC）；另有 `0x2519b0888..08a8` 的数组路径取index0，
   不能把所有扩展形状都简化成字典。
4. `0x2519b08b8..08e0` 检查CFData类型，并以FigCFEqual比较旧缓存。
   新CFData不相等时，经 `0x2519b0974..0994` 更新storage+0x208，retain新值/release旧值，w19=0。
   缺值、错类型或相等不触发这条替换路径，不能写成每帧无条件重发配置。
5. `0x2519b099c..0a08` 另有尺寸比较；配置改变时也经 `0x2519b131c` 跳到0a08设w28=1。
   `0x2519b0e5c..6c` 按w28调用配置构造器。

## 07.2 缓存CFData是type1记录body

配置构造器x20指向上述storage+0x208：`0x251b43ff8` 读缓存CFData，
`0x251b44008` 取长度，`0x251b44014..24` 用同一CFData创建无拷贝CMBlockBuffer。
`0x251b44060/44080` 将记录type写为1；`0x251b44264..278` 将非空body追加到配置头。
因此已证该avc1/avcC分支的CFData进入**独立type1配置记录body**，不是仅凭avcC名字猜测。

调用方fp-0x98存配置buffer、fp-0xa0存帧头buffer。
`0x2519b1178..11a4` 有配置时把帧头buffer追加到配置buffer之后；
`0x2519b11ac..11bc` 再追加编码数据。这证明本地组装顺序，不等于socket已送达。
配置缓存为空时构造器另读[x20+8]格式描述并调用 `0x25810e0d0`，该替代路径未在此闭合。

已关闭的是“这个分支avcC有没有进配置记录”的疑问；尚需静态追：
avcC内部SPS/PPS提取/长度、帧内是否重复参数集、NAL长度表示及转换、profile门和UDP路径。
不能仅从avcC存在推出所有帧AVCC、NAL长度固定4或所有模式均用此配置布局。

## 07.3 +05 bit7来自APInterestingFrame

`0x2519b0b34..44` 从sample取附件；键槽 `0x2693e7898 → 0x276136590`
解析为 **APInterestingFrame**。helper `0x251b44f90..fa8` 设置sample与NULL modeOut，
尾调用CMGetAttachment。返回对象与kCFBooleanTrue对象指针比较，相等才写storage+0x45c=1。
常量链 `0x2680d3198 → 0x1e053a5a0 → 0x1e8e94158`，中间导出名独立核为_kCFBooleanTrue。
`0x2519b1038..1048` 将该byte转为头+05的0x80。

所以bit7是此路径的APInterestingFrame派生标志，**不是已证关键帧/IDR位**。
不能把强制关键帧请求、函数日志中的KeyFrame字样、附件值或NAL IDR互相替代。

## 07.4 +05 bit4来自NotSync附件读取结果

`0x2519b0a10..0a8c` 调CMSampleBufferGetSampleAttachmentsArray(sample,0)。
数组不存在或为空时直接写storage+0x45d=1。
非空数组的局部输出byte初始化0；循环取附件字典，键链
`0x2680d4600 → 0x1e09fd800 → 0x1e9fe6608` 为 **NotSync**。
每次调用FigCFDictionaryGetBooleanIfPresent，返回非零即退出循环，否则继续，直至末项。
最后以输出byte==0写storage+0x45d；`0x2519b104c..1058` 将非零值映射头+05 bit4（0x10）。

### getter细节已补证：首个合法CFBoolean即停止

原 `0x25810b040` 跳板直接指向CoreMedia `0x18efac1c8..0x18efac28c`，
导出名为 `_FigCFDictionaryGetBooleanIfPresent`，函数边界由function-starts独立核对。
其outlined helper `0x18ee830b4` 保存x2→x19（输出byte地址）、x1→x21（键）、x0→x22（字典），
尾调用CFGetTypeID；`0x18ee4eb40` 恢复字典/键参数给查找调用。

- NULL字典返回0；非字典、NULL键或输出地址走诊断分支后返回0。
- `0x18efac210` 调CFDictionaryGetValueIfPresent；缺键返回0，不写输出byte。
- `0x18efac218..22c` 比较值类型与CFBooleanGetTypeID；非CFBoolean返回0，不写输出byte。
- 合法布尔经 `0x18efac234..23c` 调CFBooleanGetValue、写输出byte，**固定返回1**。
  即NotSync=false也返回1，调用方立即退出，不继续找后面的true。

因此有效附件序列的规则是：忽略缺键/非布尔项，取第一个合法CFBoolean NotSync，
bit4=not(value)；若没有这样的值，初始输出0保留，bit4=1。
例：`[false,true]→1`、`[true,false]→0`、`[缺键,非布尔,true]→0`、无/空数组→1。
数字0/1并不通过CFBoolean类型检查；这不是对整个数组做all/any。
该规则描述本地附件处理，不是要求网络接收端宽容任意损坏样本。

上述5个CF调用的实际跳板均直接解析到CoreFoundation导出名，不只核索引标签。
此标志仍是附件派生同步标志，不是NAL IDR证明；附件生产者、
forceKeyFrame的请求→编码器→实际帧因果链仍为OPEN-VID-7。

## 07.5 回归与边界

C11 `tools/verify-codec-config.py` 对上述3段Sender与原cache逐字节核对，
固定镜像/读取器哈希，检查47个指令锚点、4个CFString、CFBoolean导出及12个导入索引标签。
另核完整CoreMedia getter与2个ABI helper固定哈希、19锚点、6个直接跳板/导出名，
并检查341组长度0–4的局部附件序列及整数0/1反例（模型不是CF原生执行）。
需原dyld cache、固定CoreFoundation/CoreMedia镜像与Capstone；缺依赖不能记PASS。
导入索引标签来自dsc-stubs索引，不冒称所有目标跳板都已独立解析。
NotSync相关6个跳板例外，另做直接核验。它不是编码器/固件执行或真实码流解码，不关闭完整OPEN-VID-3/6/7。
