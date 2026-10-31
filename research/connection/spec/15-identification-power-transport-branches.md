# 15 · Identification 电源与传输组件分支审计


重点结论：8/9有required注册，但其值仍有独立条件；9的provider在本样本选择100/500，240则走平台插件；17/24必须解析嵌套组件并检查计数/唯一ID；BT/Wireless的active不是这些局部分支的无条件必需字段。当前手机仍只解析0–7，本章不得用旧说明或注释替代原始证据。

## 1. 样本、方法与范围

原镜像：[accessoryd](../../../firmware/extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd)，SHA-256 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

[本轮证据](../evidence/identification-power-transport-evidence.json)记录41个函数地址/原文件偏移/字节哈希，全部重新映射原Mach-O并与缓存`.bin`逐字节核对。另重读7条注册记录、power函数表、初值和6条消息规则。JSON中的文件哈希把当前源码/汇编/反编译绑定到此次审计。[只读复查脚本](../tools/inspect_identification_power_transport.py)只打印JSON，使用`python -B`执行。旧JSON仅用于找到镜像和函数位置，不作为本章结论证明。

下文简写 `@VA` 都属于这个原镜像；汇编缓存目录为 `D:/carvex-research/firmware/analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions/`，文件名 `f_<VA不含0x>.s`。函数副本匹配不等于所有反编译类型都正确。本章重点核对业务分支；日志级别/冷日志分支、全部分配器失败、插件实际实现、异步取消和实车输入均非完整覆盖。

三种不同数字必须区分：endpoint raw transport kind（`endpoint+0x18`）、parent connection type（getter返回值）、component type（17→3，24→4）。本轮不把它们混成一个枚举。

## 2. 原始注册与标量读取

| 参数ID | 原始记录VA | callback | required字节 | 宽度/消费 |
|---|---|---|---|---|
| 8 | `0x10021f1a8` | `0x1000c07a8` | 1 | U8，写power feature+4 |
| 9 | `0x10021f1c0` | 同上 | 1 | U16 BE，写+0x0c，限额校验 |
| 240 / F0 | `0x10021f1d8` | 同上 | 0 | U16 BE，写+0x10，平台限额校验 |
| 241 / F1 | `0x10021f1f0` | 同上 | 0 | U8，写+8，值0/1触发feature标记 |
| 25 / 19 | `0x10021f208` | 同上 | 0 | U16 BE；此callback只记日志，不保存此值 |
| 17 / 11 | `0x10021a948` | `0x1000512e8` | 0 | 转BT组件callback `0x10004f870`，component type3 |
| 24 / 18 | `0x10021a960` | `0x1000512e8` | 0 | 转Wireless组件callback `0x10004fa38`，component type4 |

标量getter：`U8@0x100067e4c`只接受外层TLV总长5，`U16@0x100067e1c`只接受总长6并交换字节序；不满足时status=1、返回0。这个返回0是错误路径占位，不等于“合法声明值0”。nested active使用`IsDataVoid@0x100067f3c`，局部条件为总长<5；在合法TLV总长至少4的前提下就是空value，不应照搬成接受损坏的短TLV。

required成功集合由`0x10013aed0`在callback返回bit0=1后加入，`0x10013bc5c`检查缺失成功成员。故8/9不能只判是否出现。缺失只会在参数遍历成功后执行required检查；前面解析失败时不能假定仍会收集全部缺失项。

## 3. Power解析：逐业务分支

入口 `__parseIdentificationParamsPower@0x1000c07a8` 先取feature16，缺少则尝试创建，再取；仍无feature返回失败。`__createFeature@0x1000c2e00`在session非空时calloc 0x28，原数据 `0x1001b4050` 给出四个U32初值：`+4=3,+8=2,+0x0c=0,+0x10=0`。初值不是已成功识别；缺8/9仍须拒绝。calloc失败可返回NULL；完整跨feature创建失败处理仍OPEN。

| 分支 | VA / 条件 | 条件成立 | 条件不成立 | 当前手机差异 / OPEN |
|---|---|---|---|---|
| P08-LEN | `0x1000c0978..0988`，U8 status==0 | 进入值/承载检查 | 走`0x1000c0b3c..b7c`，追加外层8空拒绝项，内部reason10；callback失败 | 当前不读取8；无类型检查 |
| P08-TRANSPORT | `0x1000c0a50..a78`，值==1且`(rawKind & 0xfffffff7)==0`，即rawKind0或8 | 追加8拒绝项，内部reason13，status13 | `0x1000c0ba4`把U8值写+4，成功 | 本局部未把值限定为0/1；2..255也可保存，不可无依据编造枚举范围 |
| P09-LEN | `0x1000c088c..089c`，U16成功 | 查询provider | status失败直接到b80返回false，**此局部不追加9拒绝项** | 当前不读取9；失败形状不能与8强行统一 |
| P09-LIMIT | `0x1000c08a4..08c0`，值<=provider | c14写+0x0c，成功 | 追加9空项，内部reason6，status6 | provider详见§4；不能“8/9出现就发1D02” |
| P25-LEN | `0x1000c08fc..0938`，U16成功 | a40/bc4记录maximumSiphoningCurrent，未见持久字段赋值，成功 | b08追加25空项，reason10，失败 | 当前只留raw；本局部没有范围/限额比较，不能编造保存位置或统一上限 |
| P240-LEN | `0x1000c093c..094c`，U16成功 | 查询平台provider | 直接b80失败，**此局部不追加240项** | 当前未解析；不是9相同provider |
| P240-LIMIT | `0x1000c0954..0974`，值<=平台返回限额 | c0c写+0x10，成功 | 追加240空项，reason6，失败 | mode4平台实现/具体硬件值OPEN |
| P241-LEN | `0x1000c0824..0830,0x1000c0a1c`，U8成功 | a84写+8 | b70追加241空项，reason10，失败 | 当前未解析；不能把失败时getter返回0当正常值 |
| P241-VALUE | `0x1000c0a88..ad8`，值<=1 | 调`setIdentifiedForFeature(session,16)`，成功 | 值2..255仍保存并成功，不在此处标记feature | 不是“所有>1均拒”；后续checkAll会重建feature集合，不能把这处标记当最终授权 |
| P-OTHER | `0x1000c0804..0888`非上述5个ID | 无匹配时status初始0→局部返回成功 | 不适用 | 注册分派只给对应字段；不能利用局部default证明任意线上ID合法 |

### 3.1 重复字段、顺序和缺失

Power callback没有像组件那样的每ID计数/重复检查。连续合法8/9/240/241会覆盖同一feature槽；25每次检查宽度并记录日志。不能把`IapFields[id]`的“重复singleton一律抛错”当成iPhone事实。

这不是说任何重复整条都接受：`ForEachParamDo@0x10006782c`每次调用callback后取下个字段，callback非零则停止；后面的字段不能修复前面的错误。`0x10013aed0`把注册callback false转成遍历失败，主handler `0x10013bcc8`在遍历非零时跳过required/feature正常检查并进入拒绝处理。

两种反例必须单测：合法9后非法9不会因required集合已有9而成功；非法9后合法9通常到不了后一个callback。8/9缺失而其余遍历成功时，required校验追加相应空字段拒绝项。25/240/241的required=0不保证它们声明后可以不校验，也不证明所有power业务依赖都可省。

## 4. 两种限额provider与power跨字段门槛

### 4.1 ID9的本样本限额已缩小为100/500

`__maximumCurrentAvailableFromDevice@0x1000c0758` 的完整局部决策：

| 条件VA | 真分支 | 假分支 |
|---|---|---|
| c0768：session非NULL；c0770：root endpoint非NULL | 调`getParentConnection@0x10018f128` | c0794返回100 |
| c077c：parent非NULL | 调`getType_internal@0x1001939fc` | 返回100 |
| c0784：parent connection type==3 | c078c选择500 | 选择100 |

100/500是该函数返回的原始数值，不能把parent type3误写成endpoint kind3，不能外推为所有固件/所有供电能力。ID9这里不是每次读真实硬件电流；这些getter本轮只定位调用，没有完整追到所有连接type生产者。若实施，需给真实endpoint/parent上下文建模，不能只看“BT/TCP”字符串选一个数。字段9单位本轮没有独立规范文字证明；不把数值名称自动升级为全部线单位合同。

### 4.2 ID240仍有真实平台边界

`platform_power_getUltraHighPowerModeCurrentLimit@0x10002a650`：以session+8的endpoint UUID调用`copyConnectionUUIDFromEndpointUUID@0x10003182c`，取得power plugin `0x10001234c`，向ObjC selector `accessoryPowerModeCurrentLimitInmA:forConnectionUUID:`（stub `0x1001a4300`）传mode=4，再把返回值截取低16位。

UUID helper至少2个token取第一个，>2记录后仍取第一个；token不足/失败返回NULL。平台函数在这个调用点没有NULL UUID的独立失败分支。插件具体对象、mode4硬件限额、nil receiver/NULL UUID的实际值和副作用未运行，不能补成固定100/500/0。`InmA`名称支持该平台接口以mA命名，但不替代所有power字段的单位证明。

### 4.3 只把字段解析正确仍不足以识别power feature

原数据`0x1001b4060`有6条12字节规则：`AE00(direction0,required1)`、`AE01(1,1)`、`AE02(0,1)`、`AE03(0,0)`、`AE05(0,0)`、`AE06(0,0)`；direction0查配件发送集合，direction1查配件接收集合。

`checkRequiredMsgIDs@0x100050c2c`分别计算“任一项声明”和“所有required项声明”；`checkIdentificationMsgIDs@0x100050af4`在任一项被声明时记录可接受消息，并把缺少required项记入拒绝消息集合。`power_checkIdentificationInfo@0x1000c0c70`在任一项声明且该组检查成功后：

- feature存在且`PowerSourceType==0 OR isWireless!=0`时检查AE03/AE06。AE03存在先拒，wireless原因13、非wireless原因14；AE03不存在再查AE06，存在则原因11。
- feature不存在或`PowerSourceType!=0 AND !wireless`跳过这两个局部否决；组检查仍成功才标记feature16。
- 组无声明不因这段自动标记；部分声明缺必需消息仍失败。`isWireless@0x10018f17c`在有效root条件下为parent connection type2或endpoint rawKind4，不是仅凭某个组件active位。

这些消息拒绝走ID6/7消息列表机制，不是把reason13等附加到普通字段TLV。本轮没有闭合power运行时全部AE处理或其它feature组合；不称power完整实现。

## 5. 17/24嵌套字段：callback与成功后的验证分开

`core@0x1000512e8`把17/24传给`parseTransportComponent@0x1000500a8`；后者分配0x50零初始化对象，type存+0x14、初始化7个子参数计数槽于+0x48，调用嵌套`ForEachParamDo`。组件id存+0，name指针+8，active字节+0x10，BT地址+0x18；这些是反编译恢复的内部布局，不是线上字段偏移。

### 5.1 Bluetooth callback `0x10004f870`

| 子ID | VA / 条件 | 真分支 | 假分支 | 重复/缺失边界 |
|---|---|---|---|---|
| 0 | f94c，U16 getter成功 | 把id写组件+0 | 返回非零状态 | 后续要求出现恰1次；本局部不要求id非零 |
| 1 | f8b4，CFString helper status0 | f9f4写+8 | helper有对象则release，返回非零 | 后续要求恰1次且最终指针非NULL；重复成功赋值前未见release旧值，不能复刻这种潜在资源缺陷 |
| 2 | f968，IsDataVoid非零 | active=1 | f9e0 active=0xff，status1 | 后续至多1次；**BT这个局部不要求必须出现**，缺时calloc保持0 |
| 3 | f8e4，data成功且地址非NULL，`(valueLen & 0xff)==6` | f914复制前6字节到+0x18 | f9e8 status1 | 后续要求恰1次；本局部不校验全0/广播/与实际配对地址一致 |
| 其它 | f928未知分支 | 只记日志，status仍0 | 无该处拒绝分支 | 若id<7仍增加计数；>=7不计数；不能据此保证跨层全接受 |

**长度异常必须如实保留**：`f908`为`and w8,w0,#0xff`，不是反编译随便把U16写成char。局部可接受长度262、518等低字节为6的value并仅复制前6字节。完整消息边界仍由迭代器控制。本章不建议故意复制这种宽容；若未来采用严格6字节，应明确标注安全收紧而非宣称与Apple逐字节相同。

### 5.2 Wireless callback `0x10004fa38`

| 子ID | VA / 条件 | 真分支 | 假分支 | 计数/副作用边界 |
|---|---|---|---|---|
| 0 | fae4，U16成功 | 写组件id | 返回非零 | 后续恰1次 |
| 1 | fb3c，CFString status0 | fc1c写+8 | release返回对象、失败 | 后续恰1次且指针非NULL |
| 2 | fa84，void | active=1 | fc00置0xff并status1 | 后续至多1次，**不无条件必填** |
| 4 | fb00，void | +0x37=1 | fb70清0，status1 | addTransport未限制该计数只能1；其最终值影响info flags |
| 5 | fb58，void | +0x38=1 | fc0c清0，status1 | 重复合法void不被本局部次数检查拒绝；传播受子4条件控制 |
| 6 | fab4，CFString成功且对象非NULL | release旧+0x40，再保存新值 | 失败时release临时对象；status0但对象NULL只记日志，不主动把status改1 | 与子1不同；重复合法值替换，缺少不在addTransport局部必需 |
| 3及其它未知 | fb18 | 日志，status保持0 | 无该处拒绝分支 | id<7计数；不要给子3臆造网络地址含义 |

字符串helper `0x100067ee4 / 0x1000f2bac`要求总长>=5且末尾NUL，再以UTF-8 CF转换；转换NULL并不必然改变status。组件name最终非NULL由addTransport检查兜底；子6的NULL路径不同。具体CF对非法UTF-8/内嵌NUL、空字符串的行为未运行；不能统一替换成任意Java字符串解码器后称完全相同。

## 6. 嵌套次数、active、组件冲突与副作用

计数在BT f9f8和Wireless fc58收尾增加，**即使对应子解析失败也可能计数**；但非零callback令迭代停止，后续addTransport不会执行。计数不是成功集合。

`addTransportComponent@0x10004fedc`的BT/Wireless相关分支：

| 检查VA | 满足条件 | 不满足条件 / 返回 |
|---|---|---|
| fef0..ff14：counter容量覆盖0/1且count0/count1非零 | 继续 | reason2（缺少） |
| ff18..ff44：count0<=1、count1==1、count2<=1 | 继续 | reason5（重复）；连同前项即0/1各恰1次 |
| ff5c..ff80：type3或5 | 额外要求count3==1 | 缺3返回2，重复3返回5；type4不走这个要求 |
| ffe0：name非NULL | 继续 | 返回8 |
| ffe8：active!=0xff | 继续 | 返回10 |
| fff4..5003c：字典存在/创建成功且CFNumber id key成功 | 继续查key | 返回17；已创建key会release |
| 50040..50098：key不存在 | 插入原组件指针，返回0 | key已存在返回3，不覆盖旧组件 |

同一字典按组件id键判冲突，未把type拼进key；所以不同种类使用同一个id也不能在此并存。多个不同id同类组件不被这个函数按type数量拒绝。BT/Wireless没有在addTransport把active设为强制出现；Serial/USB分支另按实际承载附加active要求，不能迁移到17/24。

### 6.1 parseTransport不是完全事务化写入

嵌套遍历成功后，`0x100050148..01d0` **在addTransport之前**传播flags：子4对应+0x37==1时，info+0x80置1，type4另使info+0x81置1；此条件下子5对应+0x38==1又使info+0x83置1，并release/替换info+0x88为对子6字符串的retain。子5单独出现而子4没置位，不走该传播。

之后若id冲突/重复等addTransport失败，局部释放组件，但这段未见回滚已写info flags或info+0x88。应记录为固件局部副作用顺序，不把它自动翻译成手机必须保留半成功能力；主识别失败会阻止正常接受。若设计手机事务化parser，可把这种差异明确作为避免失败状态泄漏的实现边界，而不是偷偷把失败当成功。

### 6.2 当前承载要求外层组件，与active不是同一关

`checkRequiredTransportComponentParam@0x10013b920`检查endpoint rawKind和外层字段计数：kind2/3要求17，kind4要求24；不匹配该kind则该项返回0。匹配且计数缺失/未覆盖时添加外层空拒绝TLV、置info+0x90=1、返回1。此处用外层出现计数；正常路径先要求嵌套callback/遍历成功，不能仅复制计数判断而绕过前序。

`rawKind2/3要求17`不等于“必须active=1”；`kind4要求24`也不等于网络已建立、CarPlay许可已完成。全组件消费者与active之后如何影响端点选择/桥接，本轮没有全部追完。

## 7. 失败输出与cleanup：不能凭原因号编线上字段

### 7.1 输出合同

- 普通power reject使用`addRejectParam@0x10004ea3c→0x10004e91c`：向reject scratch添加同外层ID的空TLV；内部原因6/10/13仅用于日志/诊断。
- 嵌套遍历失败：`0x100050130..0144`调用`addRejectGroup`，内部reason10；addTransport失败则带其reason2/3/5/8/10/17。
- `addRejectGroup@0x10004ea7c`在eabc调用AddVoidParam，线上仍是**外层17或24的空TLV**；组件id和内部reason被格式化进本地诊断字符串，不产生“外层→子id→reason”嵌套结构。
- ID9/240宽度错误在power局部不追加字段；`ForEach`失败跳过required成功集合遍历，因此不能保证最后一定有9/240拒绝项。合法失败可能只让已有reject scratch（甚至空参数区）被提交。不要补入猜测reason字节。
- 主handler `0x10013bcc8`关联授权回调；失败callback `0x100050da8→0x10013cad8`仅在回调允许时进入`identificationRejected@0x10013b540`。回调0直接返回，不可宣称此处必定断链或发1D03。
- reject发送非零才清info+0x98/+0xa0并设state3；发送0保留指针、不设state3，之后都经过拒绝处理hook。成功accept则是`0x100050dcc`要求validation0且允许，先state2，发送bit0=1才state6。不能把“本地提交”“对端收到”“网络已通”合并。

### 7.2 对象所有权与清理分支

| 位置 | 条件/动作 | 限制 |
|---|---|---|
| parseTransport `0x100050200..0244` | 嵌套/添加失败：释放counter底层数组；release name+8和字符串+0x40；free counter对象；free组件 | 成功则不在这里free，所有权转给字典维护；分配NULL的全路径没有完整保护审计 |
| addTransport `0x10005009c` | 创建的CFNumber key在插入/冲突后release | 字典的value callbacks为0，不能假设字典自动析构组件 |
| releaseIdentInfo `0x10004e118..01d4` | 枚举组件：free counter数组/对象、可选+0x20缓冲，release +8/+0x40；按id移除字典；free组件 | 此处覆盖已插入的组件，不修复重复子1覆盖旧name的潜在失联引用 |
| releaseIdentInfo `0x10004e1ec..0248` | release字典、info+0x88、其它集合；free外层计数器；releaseRejectMessage | 本轮不是整个函数所有平台/stack-check异常的完全审计 |
| setIdentificationInfo `0x10013ab84` | 替换前release旧IdentInfo，再free旧info；安装新info | 不会由此自动清除独立power feature16内的状态；拒绝→重识别的power状态完整生命周期仍OPEN |
| power destroy `0x1000c2e50` | feature指针有值时，若session存在先retain endpoint等上下文、排平台异步工作；再free feature并清指针 | callback `0x1000c2f4c`按sleep字段!=2的捕获条件调用setPowerDuringSleep(false)，总是stopPowerUpdates并release捕获引用；何时所有失败路径调用destroy尚未闭合 |

清理顺序只支持“失败不能泄漏/误提交能力”的工程要求，不能据此保证固件没有内存问题，也不能把原生潜在泄漏复刻进托管实现。

## 8. 当前手机精确差异

审查时源码哈希在本轮JSON，未运行安装APK验证。相关当前位置：

- [IapIdentifyInfo.kt:14](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/sessioncore/IapIdentifyInfo.kt:14)：只对0–5调用字符串解析、6/7调用BE16消息集解析，其余复制为rawParameters。**8/9/25/240/241和17/24在本轮快照均没有值校验、计数合同、provider或组件registry。**
- [Bootstrap.kt:494](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/Bootstrap.kt:494)：required仍不含8/9，known不含power5字段，17/24虽列known但未解析。第518行可在局部CarPlay声明通过后发1D02；没有本章承载/power门槛。
- [Wire.kt:7](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/Wire.kt:7)：`IapFields[id]`拒绝多次singleton；原raw ordered支持保留重复。新增parser不能对所有字段一律走这个getter，否则power最后有效值、Wireless子4/5重复和子6替换等行为会被改变。
- Bootstrap第520行捕获带parameterId异常时会发同ID空TLV，否则空1D03，再throw退出；已有编码形状可复用，但本章显示不是每个错误都自然对应一个拒绝字段，不能用一个异常类替代完整结果集合/授权/可重试状态机。

这些是静态未实现/不一致，不说明用户车辆已发送非法power/transport声明，也不把它们认定为音频问题原因。实际合法车机给出的字段若都通过固件，补校验的目标是准确处理协议，而非盲目增加拒绝来“修兼容”。

## 9. 下一步安全实施边界与拟议向量

可以先实施的确定部分：保留ordered输入，给8/9等成功/失败结果与原始ID；实现严格U8/U16宽度、8的rawKind条件；建立嵌套BT/Wireless结构、0/1/2/3次数和全局组件ID冲突；外层required-success、kind条件必须在接受前检查。新增parser先在隔离数据结构完成，失败不发布能力。未知平台上下文明确UNKNOWN，不能伪造iPhone父连接或把240 provider置0凑通。

应分开批准的差异：BT地址严格6字节（安全收紧，相比原局部低8位判断）、损坏TLV最小长度保护、托管对象替换时不复制原生泄漏。未经补证不要补发power更新、改系统充电策略、启用sleep供电或根据子4/5名字猜新业务。

以下只是拟议回归向量，**没有执行**：

| 向量 | 需要检查的结果 |
|---|---|
| 8宽度0/1/2；值1×rawKind0/2/3/4/8；值255 | getter失败与承载拒绝分开；不得错误限制全部枚举 |
| 9=99/100/101以及499/500/501×parent type3/其它/null | provider分支准确；超限追加9，宽度失败不臆造统一错误形状 |
| 240宽度错误、provider=L时L-1/L/L+1、provider未知 | provider不复用9；未知上下文不默认为可接受 |
| 25合法任意U16/非法宽度；241=0/1/2/255 | 25无已证保存槽；241仅0/1局部feature标记，其余不被误拒 |
| 同字段合法→合法/合法→非法/非法→合法 | 覆盖顺序、首错终止、required成功集合不是最终成功 |
| 17缺0/1/3，重复0/1/2/3，缺active | 缺少/重复原因与active可省明确；失败输出外层17空TLV |
| 17地址len5/6/7/262 | 标记Apple局部与安全收紧差异；不声称262是规范要求 |
| 24缺active、重复4/5、重复6、子3未知、子6CF NULL | 不做统一singleton；无未知含义注入；flags仅在正确条件传播 |
| 17与24同id、同类不同id；子4已解析但随后id冲突 | global id冲突；失败不发布半成功flags |
| 原端点kind2/3缺17、kind4缺24；字段有但子解析失败 | 不能靠外层出现次数绕过成功解析 |
| reject发送失败/成功，授权回调拒绝/延迟，随后再识别 | 对象生命周期和状态分离；不盲目断链或复用旧power结果 |

## 10. 仍OPEN：不得称逐分支全审

1. 平台power plugin mode4真实实现、UUID失败/无插件行为、parent connection type所有生产者与Android上下文对应。
2. power单位与所有业务枚举的独立规范证明、全部AE运行时消费者和重识别时feature16重置策略。
3. BT地址与实际已认证/已配对端点的绑定；所有component消费者、active对桥接/端点选择的后续条件。
4. CF字符串运行时语义、分配失败与损坏TLV迭代器所有边界、原生潜在泄漏的真实可达性。
5. 异步授权撤销/旧回调、平台工作取消、1D05/1D06更新识别完整合同，以及真实24A446相同输入的接受/拒绝抓包。

本章只把以上局部业务分支从“未审”推进到有源地址、有真/假行为、有当前差异的静态记录；没有声称能据此完成整个CarPlay连接链，也没有改动任何生产实现。
