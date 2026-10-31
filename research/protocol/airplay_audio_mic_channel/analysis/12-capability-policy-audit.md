# 12 能力条目匹配、回退与过滤

目标：解释能力集合怎样进入上一章的逐位格式对象构造，不以抓包代替可读的分支。
本章核对Sender `APCarPlayAudioFormatsCopyFormatsForAudioType`
（`0x251adc3c0..0x251adc910`）原指令、Create相关写入及两个CoreUtils getter。
它返回候选集合，不是最终选定单个audioFormat的全部算法。

## 12.1 输入形状与getter边界

- formats对象+0x10持有能力字典。`0x251adc40c..424` 按CFArray类型取 `audioFormats`。
  顶层错误由显式error出参检查；每项在 `0x251adc470..490` 按CFDictionary类型读取，错误停止。
- 每项 `type` 由CFDictionaryGetInt64读取并检查error；`0x251adc4ac` 用w19/w0比较，
  即本局部比较低32位。不能将该宽度收窄事实推广成允许客户端随意构造超范围raw类型。
- type匹配后，按CFString类型取 `audioType`，但error指针为NULL（`0x251adc4c8`）。
  `CFDictionaryGetTypedValue` 原跳板直接到CoreUtils `0x18be38df0..0x18be38e58`：
  缺键或类型不匹配返回NULL；类型错误原码-0x1a64只在error非NULL时写出。
  因此本调用点**缺audioType和错类型audioType都落到NULL分支**，不等于整个CF解析器普遍忽略错误。
- 选中的audioInputFormats/audioOutputFormats用CFDictionaryGetInt64读取且error=NULL。
  getter原 `0x18be373d8..0x18be37434` 对缺键返回0；非空值另转交整数转换器，
  本章不规定任意坏类型、字符串数字或溢出的转换结果。
- 匹配项存在audioOutputFormatsExtended时要求CFArray并检查错误；错误仍失败。
  本章尚未闭合该数组元素的完整schema，不能将它当另一个64位mask。

CFString原值：audioFormats=`0x2761398b0`、audioOutputFormatsExtended=`0x2761398d0`、
type=`0x27612fb30`、audioType=`0x276136f30`。getter片段固定SHA并独立核直接跳板，
不是只依赖Ghidra类型推断。

## 12.2 首个匹配、先前default、厂商门

按数组下标递增扫描，只处理type匹配项：

1. audioType typed getter返回NULL，或CFStringCompare(request, entry, 0)==0：
   立即使用R-11.5按**请求audioType**选键读mask，并处理该项extended数组；此后不继续扫描。
   即使读到mask=0，也不寻找后续精确匹配项。
2. 不满足上述匹配、但entry audioType与default经FigCFEqual相等：
   按default选键读取mask并覆盖“先前default”暂存值。是覆盖，不是OR，值0也覆盖旧值。
3. 所选mask为0或遍历结束仍未匹配时，只有先前default mask非0才检查厂商。
   `0x251adc62c..658` 取顶层manufacturer字符串，用CFStringHasPrefix(value, "Apple")判断。
   前缀成立才使用暂存default并设fallback byte=1；不成立则mask=0。
4. 命中未指定audioType的条目本身设fallback byte=1；有明确audioType匹配为0。
   遍历完没有匹配且未启用default回退时，该局部byte为0，不是“没找到匹配就为1”。
   此byte是函数第六个输出所表达的路径标记，不是已经确认的线上字段。

后果：早出现的无audioType项可遮住晚出现的精确项；回退只看到扫描停止前的default。
请求本身是default时，第一条default会作为精确项停止，不适用“所有default取最后一个”。
“Apple”是字面前缀检查而非任意厂商通用回退；不等于存在品牌字符串就猜出兼容策略。

## 12.3 基础过滤与对象字段来源

mask进入 `0x251adc6a8`；object+0x1c/+0x1f按byte零/非零选掩码：

| +1c | +1f | 保留mask |
|---|---|---|
| 非0 | 任意 | 0xf7fe0f8ffffc0000 |
| 0 | 0 | 0x0001f0400003fffc |
| 0 | 非0 | 0x0041f04000c3fffc |

基础AND后为0走 `0x251adc838`、`0x251adc8f8`，本地错误-0x1a31（-6705）。
这些不是线上协商字段：Create `0x251adcc30` 从构造器第三参数低byte写+1c，
`0x251adcc38` 从第五参数低byte写+1f。具体业务命名/调用者选值仍需继续绑定，
不能凭掩码外观直接将它们命名为Wi-Fi/USB或对端“支持压缩”。

## 12.4 后置过滤不能与基础零检查合并

基础AND非0后：

- object+0x1e非0且请求audioType等于telephony时，AND `0x0000080014000114`。
  +1e有Create限制策略写入（`0x251add478/4c4`）；完整品牌/参数选择链未在本章闭合。
- raw==103且APSSettingsGetIntWithDefault("carplayForce44kForBuffered",0)返回非0时：
  若mask输出指针（第四参数）非NULL，清bit23；若该指针NULL，不清该局部mask。
  这不是raw107的burstPeriodMs偏好，不能混用。
- 同一raw103条件下，若extended输出指针及已复制数组均非NULL：复制为可变数组，
  建立数值23（不是1<<23），循环调用FigCFArrayRemoveLastElementOfValue直至返回0。
  数值23与bit23的并列处理已核，完整extended编码语义仍需继续追。

**后置过滤没有再次检查mask是否为0**。`0x251adc794..7b4` 可写0到mask输出，
继续成功收尾；不能把所有AND合并后统一拒空并声称这就是原函数。
例如基础通过的bit22，在telephony限制中可被清空；raw103偏好也可清掉唯一的bit23。
独立客户端可以在进入单格式选择前安全拒绝空候选，但应明确这是上层前置条件，
而不是伪称本函数返回了-6705。原函数返回成功不代表已有可用codec或完成SETUP。

## 12.5 反例与验证范围

`tools/verify-capability-policy.py`（C13）：

- 固定Sender镜像/cache的完整Copy/Create区间；两段CoreUtils getter哈希、2个直接stub；
  35个指令锚点、7个CFString与8个导入索引标签（不冒称每个导入均独立解析）。
- Unicorn执行924次原掩码块，覆盖零/单个位/全1输入，门byte取0/1/255，
  比较结果非0的不同值，以及mask输出指针NULL/非NULL。
  基础块仅在调用前/错误分支边界停止，不替换指令或修改寄存器；后两块显式给定上游比较/偏好结果。
- 8个已规范化能力序列的**本地模型反例**验证顺序、零值遮蔽、default覆盖与厂商门。
  不执行完整CF容器、字符串比较、扩展数组、设置服务或完整协商，不能将模型叫原生解析测试。

依赖原cache、Capstone及上一轮隔离安装的Unicorn；缺依赖按失败处理。
剩余：完整数值转换/extended schema、构造器政策的业务绑定、repackage交集及最终格式选择。
本轮不是简单删OPEN，而是将OPEN-CODEC-1中可复核的匹配/过滤子规则实质缩小。
