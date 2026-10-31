# 12 能力候选集合的匹配与过滤

本章是24A446已核函数的限定规则，不是完整协商算法；最终单个格式选择仍属OPEN-CODEC-1。
证据：[analysis12](../analysis/12-capability-policy-audit.md)。

#### R-12.1 条目形状与错误检查
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A12.1`

能力字典中的audioFormats按数组解析，每项按字典解析；type由整数getter读取并检查错误。
type匹配后读取可选audioType字符串；能力值audioInputFormats/audioOutputFormats为整数集合，
不是格式名称字符串数组。读取哪个键依R-11.5。

本原路径对audioType缺失/错类型都得到NULL，并进入未指定类型分支；
对audioOutputFormatsExtended存在时却明确要求数组、检查错误，不能将两者混为通用容错。
独立实现若主动拒绝错类型audioType，应记录为更严格的本端输入策略。
整数getter的全部类型转换/溢出语义未在此定义，不能从CF函数名假定只接受某种plist数字宽度。

#### R-12.2 按顺序匹配，不能改成全数组最优匹配
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A12.2`

扫描同raw type条目，首个无audioType（typed getter为NULL）或精确audioType匹配项即停止，
即使该项mask为0。不能先遍历所有条目寻找精确项，也不能合并多个匹配项的能力。
扫描期间遇到不匹配请求的default项，保存其mask；后来的default覆盖旧值，0也覆盖。

所选mask=0或无匹配时，仅当先前default mask非0且manufacturer以Apple开头，才回退到该mask。
不继续读取停止点后面的default，也不对其它厂商自动套用回退。
原fallback输出byte：命中未指定audioType的条目或启用该default回退时为1，明确匹配为0；
遍历无匹配且未启用回退时局部值为0。该byte不是线上字段，失败时也不保证提交给出参。

#### R-12.3 基础mask过滤
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A12.3`

按formats对象内部byte选择保留集合：+1c非0用0xf7fe0f8ffffc0000；
+1c=0且+1f=0用0x0001f0400003fffc；+1c=0且+1f非0用0x0041f04000c3fffc。
候选与其AND后为0，本函数返回本地-6705。
这两byte来自构造器参数，不是独立客户端必须照抄的对象布局或可以自行发送的协议字段；
必须先绑定适用策略输入，不能为方便而固定选某个mask。

#### R-12.4 后置限制与零集合
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`A12.4`

基础非0后，+1e非0且telephony相等时再AND 0x0000080014000114。
raw103且carplayForce44kForBuffered设置非0时，mask输出指针存在才清bit23；
另按条件从extended数组移除数值23。数组完整schema未闭合，不凭此推定全部元素含义。

这些后置步骤**没有第二次零检查**，本函数可能成功输出mask=0。
后续必须区分“获取候选成功”和“选到了可用格式”；拒绝空候选可作为上层策略，
不要伪造本函数失败码，也不能据返回0直接宣称SETUP/播放可用。

#### R-12.5 实现与测试边界
级别：SHOULD ｜ 证据：INFERRED ｜ 依据：`A12.2`、`A12.4`、`OPEN-CODEC-1`

至少保留以下反例测试：

- 未指定audioType项在前、精确项在后：前者遮住后者。
- 精确匹配项mask=0：不继续找后面的非0精确项。
- 两个先前default：后者覆盖前者，即使后者为0。
- Apple前缀成立与不成立；default只出现在停止点后时不可用。
- 基础AND后空集合与后置过滤后空集合：错误路径不同。

先按本章取得候选，再结合codec可用性、repackage交集和最终选择规则生成单个ID，按spec11查表。
尚未闭合的最终选择不能用“取最低位”或“等用户抓包”替代。
