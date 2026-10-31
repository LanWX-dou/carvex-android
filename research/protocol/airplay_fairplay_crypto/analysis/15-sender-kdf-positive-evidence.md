# 15 Sender Legacy KDF：从否定推论回到直接证据

## A-46 Sender已实现同一公式；整数来源不是“首流0或1”

本节复核已有两份Sender `.s/.bin/.ghidra.c`：`f_251aa97a0`与`f_251aa9a60`，
并核Receiver `f_2518d4338`的局部调用链。不增加固件切片或改写Ghidra产物。

`0x251aa97c4`保存函数入参x1，`97dc`和`9800`分别将前缀与该整数作为ASPrintF栈上传参。
原字节中的前缀为 `AirPlayStreamKey` / `AirPlayStreamIV`，格式串为 `%s%llu`。
这是Darwin ARM64可变参数传递，Ghidra只显示两个固定参数的伪调用不能作为缺失整数的证据。

`0x251aa9824`、`0x251aa983c`两次直接BL到 `0x251aa9a60`，分别派生key和IV。
helper在 `9ae0`调用CC_SHA512_Init，`9ae8..9af0`先Update(name,nameLen)，
`9af8..9b00`再Update(storage+0x10,16)，`9b10` Final；`9b1c..9b20`复制摘要前16B到CFData。
导入桩与镜像原字节均支持这些调用，不是只靠函数名字推断算法。

因此Sender Legacy已含 `SHA512(name || masterKey16)[:16]` 的实现。
旧A-31因未调用Support包装器而推“发送端不用该KDF”错误；上一修订仅改成“可能使用”也弱于现有正面证据。
仍未证明任意目标CarPlay会话一定选择Legacy provider，不能把该公式强加给CoreUtils/ChaCha。

Receiver另有清楚的整数传值链：`0x2518d5af4..5b04`以x22字典、键对象 `0x276119dd0`、
NULL错误出参调用CFDictionaryGetInt64；零返回跳离此路径，非零保存x19。
在 `5b14`等fallback分支到 `5c1c`时，`5c2c`将x19传入ForScreen的第三参数；
`5c20/5c24`分别准备两个输出缓冲，`5c30`才是BL（旧A-18误把此地址标为准备输出参数）。
这至少证明这里不是“把本地首流编号配置成0或1”的规则。
键名解析、完整发送/接收映射与实际provider绑定仍待核验，保留OPEN-15，不凭字面名称猜ID语义。

C15 `verify_sender_kdf.py`复核固定SHA镜像、三份原切片、重反汇编、调用参数锚点、字符串及导入符号；
C6仍负责算法向量。C15不执行CF对象、虚调用、密码库或网络，不能代替真实握手测试。
