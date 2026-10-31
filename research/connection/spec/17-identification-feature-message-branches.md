# 17 — Identification：feature、声明消息与启动门槛


## 1. 范围与结论

初始`1D01`的接受链不是“必需字段出现、消息号认识”：

`注册字段回调成功 → required-success/承载检查 → feature校验 → 声明消息归属核查 → 平台授权 → 提交1D02成功 → state6`。

随后仍有认证、feature启动和平台事件门槛。[专属JSON](../evidence/identification-feature-message-evidence.json)保存**24项语义分支的输入、真假结果、副作用、当前源码对应与OPEN**，以及33个函数原始字节匹配、Capstone 5.0.7重解码、29项注册记录、3组消息数组及5份源码哈希。[复核工具](../tools/inspect_identification_feature_messages.py)只读输出，可用`--summary`。

原始accessoryd SHA-256：`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。从Mach-O映射重读并比较完整缓存机器码，关键分支对照原指令；没有运行苹果原进程、CF或真实车机。**本章深入覆盖公共管线和feature22/26，不代表已审完29项feature。**

## 2. 五类状态不能混为“能力支持”

| 位置 | 真实含义 |
|---|---|
| 字段6 / info+60 | accessory发送、手机接收的声明 |
| 字段7 / info+68 | accessory接收、手机发送的声明 |
| info+c0/c8 | 两方向已处理ID；accept和reject都会写，不能称“已许可” |
| info+70 | validator标记的identified features |
| info+78 | required字段回调成功集合，不只是出现集合 |

运行时普通消息门槛读6/7及AA/Identification状态，不读c0/c8。所以前置校验不能省略。

## 3. 24项分支索引与关键结果

以下为摘要；每项完整真假条件及源码快照在JSON同名`FM-*`记录。地址均为原映像VA。

| 分支 | VA | 已核结果 |
|---|---|---|
| FM-01/02 | `10013af84/af9c` | 无注册handler加reason1并返1；handler失败bit0=0也返1。成功才走required记账并返0 |
| FM-03/04 | `1000678a4/78a8`、`10013be78` | 迭代器保留失败callback返回，末项亦然；next错误返-1。主处理器只有返回0才进入required/checkAll |
| FM-05/06 | `10013bc10`、`10004e3dc/e46c` | checkAll创建/清+70；逐feature callback状态OR汇总，不因前项失败停止。无validator只日志，不自行拒绝 |
| FM-07/08 | `100050c2c`、`100050b58/bdc` | 分别算anyPresent与allRequired；整组未声明不请求feature，部分声明触发缺required reason2 |
| FM-09/10 | `10004eec8`、`10013b76c/b864` | accept/reject均记accounted；所有validator之后仍未处理的声明ID按方向reason1拒绝 |
| FM-11 | `10013adf0/ae60` | 偶数BE16列表建集合；内部去重、空列表语法可成功；重复合法外层6/7后值替换，奇长失败保留旧集合 |
| FM-12/14 | `10004ed40/ed7c/ee0c/ee38` | 非00FF且reason1才追加ID字节；方向flag=1且原字段计数非0才输出6/7拒绝TLV，可为空 |
| FM-13 | `10013bb90–bbbc` | feature失败仍查消息列表；两者OR非0才执行双方向finalizer |
| FM-15/16 | `1000b3350`、`100170dc0/ddc` | 4300/4301成对才mark26；WiFi先查5700/5701，再查5702/5703，第一组失败会跳过第二组 |
| FM-17/18 | `100050dcc/e30`、`10013b614/b624` | 授权非0且校验0才提交1D02，发送bit0成功才state6；1D03发送失败不设state3，但仍走拒绝处理 |
| FM-19/20/21 | `10011dd10/dda8`、`10013eb10/ed34` | Ident6后AA0启动认证、AA2启动普通features；普通feature要求state6及+70成员、starter非NULL |
| FM-22/23/24 | `100170bb0`、`10016e1b8`、`1000051a8/100051150` | 5702重查完整组；4300依赖平台availability对象；普通4300/5702与4301/5703还要求AA2、Ident6及正确方向声明 |

未知外层字段位于开头、中间或最后都阻止该初始消息进入checkAll；位置只改变此前已发生的解析副作用。不能只看`addRejectParam`就断言“记录不等于拒绝”。授权回调仍可能不许可，因此也不能断言一定观察到线上1D03。

当前注释举的`08/09/14`并非未知外层ID：8/9注册给Power，20（0x14）给Vehicle。核心switch没有处理，不等于全局没有注册。`4301`的未知字段可以走日志后继续，但不同消息不能共享这一推论。核心字段详见[18](18-identification-core-field-branches.md)，电源/承载见[15](15-identification-power-transport-branches.md)，事务见[16](16-identification-lifecycle-branches.md)。

## 4. 成对声明与拒绝编码

原数组每记录12字节：ID@+0、direction@+4、required@+8。重读的三组全部required1：

| 数组VA / feature | 字段6 | 字段7 |
|---|---|---|
| `1001b3fc8` / 26 | 4301 | 4300 |
| `1001b40a8` / 22 | 5700 | 5701 |
| `1001b40c0` / 22 | 5703 | 5702 |

全无只表示该组未请求，不证明整个Identification可接受；单边返2；全反向不按本组记账，之后可能被通用归属核查reason1拒绝。WiFi第一组失败会使第二组未检查，所以“5702/5703完整”不保证feature22通过。

以下是给定局部路径的编码推导，非真机抓包，且假定外层6/7都出现、没有其他错误往同方向buffer追加：

- 仅6含4301、7为空：缺4300用reason2，不写4300字节，可形成`00 04 00 07`。
- 未被validator处理的普通ID ABCD在6中：reason1形成`00 06 00 06 AB CD`。
- ID恰为00FF仍可导致失败，但append helper抑制其ID字节，可形成空字段6拒绝TLV。

reason是本地诊断，不是线上reason字节；00FF不是自动获准ID。列表内部重复已被集合折叠，但拒绝append helper本身无全局去重；不能宣称所有拒绝条目永不重复。长度低16位截取、构造器容量及异常CF行为仍OPEN。

## 5. 接受不等于立即发4300

feature26的starter指针为NULL。Ident6+AA2调用普通feature启动循环，也不会由该starter自动发4300。可核入口`iap2_CarPlayAvailability @10016e004`依赖平台字典；wiredAvailable/wirelessAvailable至少一个**对象指针存在**才构造4300，false对象也算存在，标识可选。真实producer和更新时序仍OPEN。

feature22也可能只因5700/5701成立而存在，所以5702发送函数仍复查5702/5703完整。普通消息准入成功、4301字段解析成功、平台handoff、网络就绪、AirPlay与首帧均是不同事实。state3也不单独证明实际发过1D03：pending拒绝对象为空可直接设state3。

## 6. 当前实现差异及收口

源码根`D:/carvex-research/android`，快照哈希见JSON，不等于安装APK。

| 当前定位 | 差异 |
|---|---|
| Bootstrap.kt:489–511 | unknown只记录；required查出现；IapIdentifyInfo只解析部分字段，缺完整注册feature管线 |
| Wire.kt:8–11 / IapIdentifyInfo.kt | 重复外层6/7直接拒绝；Apple合法后值替换；偶数列表无归属校验 |
| Bootstrap.kt:517–519、405–416 | 单边4301或5703可先接受，之后仅skip不完整pair；Apple在Identification期间拒绝对应部分组 |
| Bootstrap.kt:414 | 固定无线true+phoneMac，不等于原平台availability消费者 |
| Bootstrap.kt:520–532 | 通用/字段拒绝后throw，不覆盖完整feature列表拒绝、授权及再次识别 |
| PeerNegotiationController.kt:92–101 | auth/ident分离的ready局部相似，但不能弥补接受前校验缺失 |

本批未修这些生产行为，也未证明它们就是某车型失败的唯一原因。还需：其余feature全部validator/跨组约束、CF/provider运行结果、授权取消及更新识别生命周期、availability生产者、边界构造器和真实同版本抓包。已有本地测试通过不代表其oracle符合24A446。

后续回归至少覆盖未知字段首/中/尾、callback失败、空/奇长/重复列表、三组全无/完整/单边/反向、WiFi第一组失败、未知ID/00FF、授权false、发送失败及Ident6但AA未2；同时断言返回、是否继续、集合副作用、拒绝字节和真实提交状态。G4及后续网络/视频验收仍不能因此整段关闭。
