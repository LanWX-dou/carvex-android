# 66 — 手机端第三批：初次Identification核心字段

日期：2026-10-29。目标仍为 `iPhone18,1 / iOS 27.0.1 / 24A446`。承接[65生命周期实施](65-identification-lifecycle-batch2.md)，本批落实初次`1D01`中已经核实的核心字段、注册分类与拒绝次序；**没有完成全Identification接受合同**。


## 1. 已实施规则

| 输入/条件 | 新手机处理 | 已验证边界 |
|---|---|---|
| 初次0–5、12、34 | 按线上顺序解析，合法重复用最后值替换 | 不全局放宽`IapFields` singleton访问器 |
| CString值 | 长度至少1且末字节NUL | `00`为空串；`41 00 42`拒绝；`41 00 42 00`允许framing并读到首NUL |
| 初次6/7 | 偶数长度BE16列表；列表内部去重；重复字段替换整个列表 | 空列表可替换旧列表，不是合并；方向6/7保持独立 |
| 初次13 | 不同语言累积；相同已解析值再次出现拒绝 | 当前JVM字符串相等不是全部CF Unicode相等语义的证明 |
| 任一已实现字段失败 | 在首错停止，不再处理后值或required缺项 | 后来的合法重复不能修复早先错误；失败candidate不提交 |
| 核心required | 遍历成功后检查0–7、12、13的成功集合 | 当前仅核心子集；没有把Power8/9的出现伪装成成功解析 |
| malformed13 CString | 返回两个连续空13拒绝TLV | 原processStringParam与case13各追加一次；不能统一去重 |
| 重复有效语言13 | 返回一个空13拒绝TLV | 与CString framing失败分支不同 |
| 真未知初次字段 | 按锁定24A446注册画像拒绝，无论在首/中/末 | 不是所有未来固件的永久全集；不把更新1D06规则套入初次识别 |
| 已注册19 | 原core明确拒绝，返回一个空19 TLV | “已注册”不代表一定接受 |
| 其他已注册feature字段 | 保留raw，明确记录deferred，不标记成功校验 | 电源、承载组件、其他feature值及组合尚未接入 |

新增保存 `IdentifyInfo.currentLanguage / supportedLanguages / ppid`。语言/消息集合采用稳定首次出现顺序只是本地展示/测试便利；不声称原CF集合具有此枚举顺序。`rawParameters`保留初次消息全部顺序、重复项和独立字节副本。

`1D06`仍只更新0–5，新增的语言和PPID字段不会被其覆盖；即使更新里12/13形态坏、34值不同，也不把它当初次识别再解析。新增测试通过真实合成字节流验证这条分工。

## 2. 原始证据与输出次序

来源仍为原accessoryd，SHA256 `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。关键函数：

- 核心switch `0x1000512e8`、CString framing `0x100067ee4`、字符串处理 `0x10004f0d4`。
- 6/7集合处理 `0x10013adf0`、全局callback分派 `0x10013aed0`、ForEach `0x10006782c`、初始handler `0x10013bcc8`。
- 注册器 `0x10006a3e4`、required追加 `0x10013c788`、缺项检查 `0x10013bc5c`。
- 拒绝追加 `0x10004e91c` → AddVoid `0x100067ce0` → InitParam `0x100003a68`，普通同ID空TLV不去重。

[只读工具](../tools/inspect_identification_core_batch3.py)重新读取14个函数切片，并比对存在的原缓存；重新遍历29个feature描述符取得34项参数注册。完整注册集合为 **0–26、29、30、33、34、38、240、241**。注册初始化有descriptor/table/count等门，不见按车型/承载筛选这些字段的分支；有条件的后续validator仍是另一层。

完整required按注册顺序为 **0–7、12、13、8、9**，不是数值排序。本批只实现前10项。缺项检查在遍历全部成功后执行；首错不能再拼上未执行的缺项结果。

malformed13的正常scratch追加路径产生 `00 04 00 0D 00 04 00 0D`；相同有效语言重复产生 `00 04 00 0D`。线上没有附加内部reason字节。`Bootstrap`保留异常携带的拒绝列表，包括重复项，复用上一批世代保护的发送及同link纠正机制。

原标量先清旧指针再解析，本地仅在隔离candidate内更新并在整条成功后发布，不复制原生释放/分配副作用。CF转换NULL、非法UTF-8和Unicode等价仍未执行；现有JVM转换明确保留为实现差异，不凭本地测试宣布与CF完全一致。

## 3. 手机改动范围

- `core/.../sessioncore/Connection.kt`：增加语言及PPID字段，保留构造默认值。
- `protocol-carplay/.../sessioncore/IapIdentifyInfo.kt`：有序初次解析、核心成功集合、注册分类、可保留重复拒绝项的错误结果。
- `protocol-carplay/.../carplay/Bootstrap.kt`：去掉解析前的raw出现检查，解析后检查核心缺项；输出精确拒绝列表，保留所有发送成功/失败及重试事务边界。
- 对应两份测试：`IapIdentifyInfoTest.kt`、`BootstrapNegotiationTest.kt`。

既有dirty worktree保留；上述5个文件相对HEAD的全部差异也可能包含上一批，不能把整个工作树归为本轮改动。

## 4. 实际验证

| 检查 | 本轮结果 |
|---|---|
| IapIdentifyInfoTest | 20项：含逐标量边界、每个核心必需字段缺失、列表重复/空/奇长、语言重复、未知字段位置与错误次序 |
| BootstrapNegotiationTest | 55项（本轮新增10）：精确拒绝字节、candidate不泄漏、同link多次拒绝后纠正、无额外认证/识别重启、初次/更新分工 |
| 定向4组 | 94项，0失败/错误/跳过；包含更新10项及accepted对象9项 |
| protocol-carplay全量 | 103组、741项，0失败/错误/跳过，实际执行 |
| core全量 | 12组、79项，0失败/错误/跳过，实际执行 |
| app:compileXiaomiDebugKotlin | 成功；bridge及小米Kotlin编译实际执行，不是打包 |
| git diff --check | 通过；保留已有CRLF归一化提示 |

全量合计 **820项**，比上一批增加28项（parser净增18，wire新增10）。定向94项是其中子集，不可重复相加。独立原始oracle复核和修改后源码/测试审阅未发现本批范围内阻断项；这不表示所有字段/feature、原生分配失败、平台授权或实车分支都覆盖。

```powershell
$env:JAVA_HOME='C:\Program Files\Android\Android Studio1\jbr'
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests '*IapIdentifyInfoTest' --tests '*BootstrapNegotiationTest' --tests '*IapIdentificationUpdateTest' --tests '*AcceptedIdentificationTest' --no-configuration-cache
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --no-configuration-cache
```

测试为合成配件/本地逻辑，不是24A446原进程执行或实车抓包。输入代码、原始切片与最终报告哈希见[第三批快照](../evidence/identification-core-batch3.json)；旧证据JSON不覆写为新源码哈希。

## 5. 电源上下文调查与下一步

本轮另沿Power8/9的真实生产者调查，详见[19 — 电源provider上下文](19-identification-power-provider-context.md)。区分parent connection type、endpoint raw transport kind和组件类型，不能凭“BT/TCP/USB”字符串混用数值。ID240的mode4插件限额不是ID9的100/500选择。

本批**没有将8/9校验或完整feature组合接入生产**。下一批应把已证的实际蓝牙/AirPlay来源绑定为明确上下文，再处理Power宽度、范围、重复和失败输出，补全required-success；随后接入组件及消息方向/组合validator。不能只在required列表加8/9，也不能“识别消息ID”就声明功能已实现。

G4仍PARTIAL；网络、AirPlay认证/SETUP、视频首帧及重连继续按分支审阅。未执行车机复测、未改变版本号、未取消安全门槛，不能据本地820项通过宣布任何具体车型连接问题已解决。
