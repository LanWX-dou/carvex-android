# 10 音频格式字段、条件与默认值原指令审计

范围：24A446 AirPlaySender。CarPlay构造函数 `0x2519bd928..0x2519bfa8c` 与
独立 `_audioStream_resumeInternal`（`0x251bbb188..0x251bbd808`）分别描述，
不能把后者的字段条件未经调用绑定推广到所有CarPlay流。反编译C仅辅助定位，以下以原指令为准。

## 10.1 SETUP audioFormat 是整数

`0x2519be814` 调 `0x2519c4558`，getter在 `0x2519c455c` 从格式对象 `+0x60`
读取64位值，调用方保存到x22。`0x2519be83c..84c` 将键槽 `0x2693e7c18`
和x22传给 `_CFDictionarySetInt64`（索引地址 `0x25810a790`）。
键槽解析为CFString `0x276136ef0`，内容为 `audioFormat`。
辅助函数 `0x2519ae150` 仅将槽内容置x1、字典x28置x0。

因此线上字典的audioFormat是整数格式标识，**不是** `PCM/48000/16/2` 一类字符串。
`audioType` 则由另一个getter `0x2519c454c` 读取 `+0x70`，按对象写入，不能混同。
本结论不定义plist整数的唯一序列化宽度，也不凭getter推定标识的全部位含义。

本地格式名称字面量仍可作为寻找表/构造器的线索，但不能证明：能力数组每项是字符串、
选中后整串回显、缺省位深16、连字符和下划线在线上等价，或单声道项就是麦克风候选。
后续[analysis11](11-format-id-map-audit.md)已补整数→基础ASBD的59行映射及传输/HAL转换，
关闭本节历史映射子问题；完整能力交集与优先级仍属静态待追，不是只差抓包选值。

## 10.2 disableRetransmits 与 redundantAudio

在独立resume函数：

- `0x251bbb830..834` 将 `kCFBooleanTrue` 对象装入x19。
- `0x251bbb928..938` 将storage+0x28与常量 `LowLatencyAudio` 作 `FigCFEqual` 比较，
  不是 `CFDictionaryContainsKey`。常量链为 `0x2680d57f0 → 0x1e0a05408 → 0x1e9ffaa48`。
- 相等才在 `0x251bbb940..950` 写 `disableRetransmits=true`；不相等跳到954，省略键，不写false。
- `redundantAudio` 在 `0x251bbb90c..924` 从storage+0x74读取32位数，**有符号比较≥1**才写整数。

这关闭局部写入类型/条件疑问，不证明缺键时接收端默认，也不证明所有CarPlay路径使用这些键。

## 10.3 burstPeriodMs 的发送端偏好缺省值

CarPlay构造路径 `0x2519be7a8..7c4` 调
`FigGetCFPreferenceNumberWithDefault("jarvisDefaultBurstPeriod", "com.apple.airplay", 200)`，
返回w0符号扩展后存sp+0x28。`0x2519be95c..98c` 仅raw==107时把该整数写到 `burstPeriodMs`。

`0x25810b2f0` 原跳板直接跳入CoreMedia `0x18ee815a0`。
`0x18ee815b4` 读取偏好，`0x18ee815c0` 将值与保留的默认值传给转换函数 `0x18ee81258`。
转换函数 `0x18ee81274` 对NULL跳到 `0x18ee8132c`，取默认值，并在 `0x18ee813a8` 返回。
故**本地偏好缺失→200**已闭合；不是车机收到缺少burstPeriodMs的请求后默认200。
转换器另有CFNumber、字符串和Boolean分支，尚不宣称任意异常偏好都回退200。

## 10.4 spf 为整数，包率向零截断

`0x2519bdf58..68`：

```text
ldr    s1,[x25,#0x14]   ; 将32位整数位模式装入SIMD寄存器
ucvtf  d1,d1            ; 无符号整数转double，非float转double
fdiv   d0,d0,d1
fcvtzu w8,d0            ; 向零截断为无符号整数
udiv   w21,w26,w8       ; 整数除法
```

同结构字段在 `0x2519be8d0` 用 `ldr w2,[x27,#0x14]` 读取后作为整数spf写入字典。
对正有限且转换/除法有效的输入：`pps=trunc(sampleRate/spf)`，
`packetSizeLimitBits=bitrate//pps`。反例：48000/512=93.75→93；96000//93=1032，不能用round得到94。
无效spf、溢出和上游格式有效性检查仍需追，不以这段局部公式定义异常输入策略。

## 10.5 回归边界

`tools/verify-config-fields.py`（C11）核对4段Sender原镜像/cache一致性、2段CoreMedia固定哈希、
49个指令锚点、8个CFString、CFBoolean导出、偏好跳板、5个导入索引标签及截断反例。
读取器和镜像哈希固定；需原 `firmware/extracted/24A446/dyld`、CoreFoundation镜像与Capstone。
导入索引标签检查不等于逐个独立解析原跳板；偏好跳板另有直接核验。
这不是固件执行、编码器运行、plist交换或真实车机互通验证；缺依赖不能记PASS。
