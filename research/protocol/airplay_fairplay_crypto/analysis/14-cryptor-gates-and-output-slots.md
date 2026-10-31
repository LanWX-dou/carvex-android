# 14 分派表的属性门、对象门与两个输出槽

证据：已有Sender `f_2519bbf24.s/.bin/.ghidra.c`和Support `f_226f2f54c.s/.bin`；
本轮未增加固件切片或改写反编译C。旧稿有多处地址错配和遗漏条件，以本节替代旧A-19表。

## A-43 属性名已定位，不是任意客户端开关

`0x2519bc010..01c`读取槽`0x2693e7270`并保存CFString到sp+0x40；
`0x2519bca90..aa0`再次读取会话storage+0x30对象的该属性，getter返回值存x22，下称G。
实际getter调用为`0x2519bca9c`，不是旧稿的bca44（那里是CFRelease）。

原镜像符号槽：`_kAPEndpointDescriptionProperty_SupportsCoreUtilsPairingAndEncryption`。
原dyld v5解码：

| 层级 | 地址 | 原始指针/内容 | 解析结果 |
|---|---|---|---|
| 全局槽 | 0x2693e7270 | 0x00100000f6135310 | CFString 0x276135310 |
| CFString+16 | 0x276135320 | 0x00200000d1c1a294 | 字符串0x251c1a294 |
| CFString+24 | 0x276135328 | 长度37 | `SupportsCoreUtilsPairingAndEncryption` |

两个pointer slot均核对原cache v5 slide的value_add=0x180000000及导出Sender原字节，
字符串本体在固定SHA的Sender镜像。历史OPEN-7的**属性拼写**已关闭。
该对象是内部端点描述，属性从何种线上能力转换、目标profile何时置位仍需继续核验。
不能要求独立客户端发送同名线上字段，也不能把它变成“失败后自行切换”的选项。

## A-44 type与G共同决定对象创建

type由`0x2519bca6c ldr w23,[x19,#8]`读取。A/B是两个输出指针：
`0x2519bca70 ldp x26,x25,[x19,#0x20]`；局部对象分别放sp+0x78和sp+0x70，初始均0。
下表假定已经取得keyholder，相关虚方法存在且返回成功，构造器成功。

| type | G=0 | G≠0 | 派生/构造证据 |
|---|---|---|---|
| 96/102/103 | A=CBC、B=NULL | A=ChaCha(flag=1)、B=NULL | provider+0x10→bceac CBC；provider+0x38→bcc8c ChaCha |
| 100 | A/B=NULL | A、B各一个ChaCha，flag均1 | provider+0x38一次请求两个结果；bcf88、bcfa0构造 |
| 101 | A/B=NULL | A=ChaCha(flag=1)、B=NULL | bcbac派生、bcbcc构造 |
| 106 | A/B=NULL | A=ChaCha(flag=1)、B=NULL | bd020派生、bd040构造 |
| 107 | A/B=NULL | A=NULL、B=ChaCha(flag=1) | bcd4c派生、bcd6c构造 |
| 110/111 | A=CTR、B=NULL | A=ChaCha(flag=0)、B=NULL | provider+0x28→bd118 CTR；provider+0x38→bce20 ChaCha |
| 120/130 | A/B=NULL | A/B=NULL | 直接到bd120公共输出路径 |
| 其他（含104/105/108/109/112） | 进入Bad type | 进入Bad type | bd054；仅指到达此分派的输入 |

旧稿“110/111总是CTR”“100/101/106/107总是ChaCha”“100的两个对象是主备且同帧序号”均撤回。
本函数没有证明主备、容灾或序号关系；A/B只是出参槽，不是可推导的网络方向。
这里返回NULL也不是调用`APSCryptorGetNull`，更不证明外层传输明文。

ChaCha构造flag按原w2记录。Support构造器在`0x226f2f570/5d4`将它作为字节存到storage+0；
仅此不能将0/1命名为方向、认证开关或媒体类型，需继续看使用者。

## A-45 keyholder门与provider出参

`0x2519bcaac..acc`从storage+0x150取得并保留取键对象H（下称keyholder），先于类型分派：

- G≠0：H为空→`bd50c..518`返回`0xfffee773`，包括本来不建对象的120/130。
- G=0：若storage+0x40字节非零且H为空，提前成功：若A输出指针存在则仅写A=NULL；
  B输出位置不写（`bcb18→bd208`）。这里不进行type验证。
- 其他路径仍要求H非空再进行上表分派；因此不能把“未知type必报错”推广到整个函数所有早退。
- +0x40的来源/业务含义未证；这不是认证绕过或合法明文协商的证明，不允许据此设计降级。

provider class+0x38方法的寄存器参数为：
`(x0=H, x1=connection值, x2=32, x3=K3Out或NULL, x4=32, x5=K5Out或NULL)`。
connection值从sp+0x60读取，不是由该调用点证明的“流序号0/1”。
Ghidra可能把PAC修饰的寄存器当额外参数，不能照抄其伪签名。

| 类型组 | K3Out | K5Out | 后续对象 |
|---|---|---|---|
| 96/101/102/103/106/110/111 | NULL | fp-0x90 | K5供A |
| 107 | sp+0x80 | NULL | K3供B |
| 100 | sp+0x80 | fp-0x90 | K5供A，K3供B |

输出是后续构造器使用的CFData对象，不是凭这个接口证明“在一个裸64B缓冲里取前后两半”。
两个size形参即使对应output=NULL仍为32，不能由size=32判定必有两个实际输出。
G=0的CBC获取方法+0x10收两个CFData出参（key/iv）；CTR方法+0x28另收connection值及key/iv出参。
具体provider的材料来源、角色方向与HKDF标签需逐个绑定；不从属性名称直接推断。

## 回归范围

C14 `verify_cryptor_dispatch.py`：2份现有原切片、36个锚点、属性v5原字节、4个导入符号；
8320个type/G/H/+0x40/A指针组合的局部分支解释、18个provider参数片段案例。
vtable/PAC、provider内部、构造器返回以及外部对象生存期不在有限解释器内；
通过表示分支/参数与原指令一致，不是完整函数执行或车机能力测试。
