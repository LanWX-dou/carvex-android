# 67 — 连接主线第四批：网络交接、能力选路与 SETUP


**本批补齐下表范围，不代表蓝牙到首帧所有分支已经完成。** 尤其完整认证、网络身份融合和 SETUP 请求条件仍有实现缺口，不能把这些都归结为“只差实车测试”。

## 1. 实际修改

| 阶段 | 已接入手机的行为 | 原证据／实现边界 |
|---|---|---|
| 4301 输入 | 全部已知字段按线顺序校验；标量末次有效值覆盖、IP累加；首错不被后续有效值或本地缺项掩盖 | [25](25-network-handoff-branches.md)；不宣称完整CF字符串等价 |
| 5703 输入 | CString要求末NUL；部分配置不再提前交接导致缺凭据终止；同一等待预算不续期 | 语法有原依据，Android可用性与预算是本地策略 |
| 网络复用 | 复用路径和新连接回调共用接口／本地地址就绪检查 | 不把本地地址就绪当车机服务可达；未恢复所有OS回调 |
| 控制端点 | iAP2地址与其端口、Bonjour地址与其SRV端口分别绑定，再按tuple去重；不再跨来源拼接地址和端口 | bootstrap优先顺序保留为LOCAL_DESIGN，不称苹果优先级 |
| 安全能力 | 表达CU=F38/F46/F43/F48任一；discovery仅有其它CU位时明确报未实现机制，不再误归SAP | [26](26-airplay-security-branches.md)；没有扩张HomeKit授权，没有删除SAP/证书门槛 |
| 控制SETUP | 初始／更新标识、响应解析和错误检查集中到真实调用的`AirPlaySetupSession`；拒绝后不再盲试`/setup` | [27](27-setup-response-branches.md)局部发送无此fallback；不是所有上层transport重试的结论 |
| 内嵌info | 字典成功接收后保存会话snapshot，显示／音频／HID使用同一份；不再固定独立GET；缺失／非字典仍GET | 空字典合法；本地snapshot不等于完整苹果endpoint副作用；注入消费者错误有独立测试 |
| skipRecord | 非零置位；同会话更新的零／缺失不清除；仅未Started且未skip时发送无正文RECORD；失败不标Started | 原getter、状态guard已核查；新对象隔离是本地生命周期设计 |
| 可选端口 | eventPort缺失／零／转换失败不建事件socket，仍执行控制面的模式/HID/feedback；keepAlivePort独立 | 非零超范围拒绝为本地socket边界，不伪装成原getter检查 |
| enabledFeatures | 缺失允许；存在时要求数组；不在此处猜测元素含义 | 无线kind5原类型门；未实现所有后续feature消费 |
| 视频SETUP | 恰好一个字典、type匹配、数据端口可用才继续；不再从多项中挑首个匹配；不再拒绝后重发根路径 | 本地额外拒绝64位窄化别名；完整请求presence与cryptor链未闭合 |
| 会话URL | 使用已连接对端的数字地址，去除hostname／前导slash；IPv6按已核压缩／mapped／compatible分支，省scope／方括号／端口 | 原此生产点是非通用URI格式；socket仍保留scope；本地仍随机u64，未复刻原UUID→token提供者 |
| 准备失败清理 | 视频SETUP成功即持有拆流责任；畸形正文、数据连接失败、RECORD失败也由Resources清理；迟到2xx仍对旧连接尝试TEARDOWN | 本地所有权实现，先注销再发送；网络已断时best-effort不保证对端收到 |

`AirSession`实际调用新SETUP helper，正常`closeVideo()`也委托同一个清理对象，不是只添加未接入的测试模型。准备失败时即使还没有创建VideoEncoder，也会尝试拆流；资源按逆注册顺序清理，在控制socket关闭前执行该helper。取消后只使用该对象绑定的旧client，不向新会话补发。

`SetupPlistInteger`区分转换返回值与错误：skipRecord忽略转换错误，端口检查错误。已实现当前二进制plist常用整数／real／Bool／Data／ASCII字符串分支，包括NaN、饱和、二／八／十／十六进制、尾随前缀与64位回绕。CFDate、非ASCII MacRoman及整个CF系统不在该有界实现中；没有全局放宽Plist解析器。

## 2. 手机源码范围与历史工作保护

本批涉及19个生产／测试文件，具体绝对路径及当前SHA256见[connection-mainline-batch4.json](../evidence/connection-mainline-batch4.json)。其中主要入口：

- `protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt`
- `Bootstrap.kt`、新`StartSessionSyntax.kt`、新`NetworkLinkReadiness.kt`、新`ControlEndpointCandidates.kt`
- 新`core/AirPlaySetupSession.kt`、新`core/AirPlaySecurityCapabilities.kt`及现有`SecurityRouting.kt`、`WifiAnnouncement.kt`

上述相对路径均位于手机仓库，不是固件文件。原工作树已有大量音频、设置、日志和前三批改动；整个`git diff`不能当本批改动范围。保留已修音频、`sourceVersion=320.17`与`osBuildVersion=21A329`过渡声明，未盲改成24A446身份，也未去掉formal安全门槛。

## 3. 实际验证

| 检查 | 结果 |
|---|---|
| protocol-carplay完整单测 | **811项／110组，0失败、0错误、0跳过**；最后一次实际执行 |
| core完整单测 | **79项／12组，0失败、0错误、0跳过**；显式`--rerun` |
| 小米Kotlin编译 | 成功；本批修改AirSession后实际执行过，最终增量检查UP-TO-DATE |
| 总计 | **890项**，相对上一批820项净增70；定向测试是子集，不重复相加 |
| git diff --check | 通过；既有CRLF转换提示不是空白错误 |
| 三份原证据复核 | 主任务重跑均PASS：网络2镜像/7函数，安全5来源/15函数/9槽/5跳板，SETUP20函数及键/vtable/整数分派/socket符号 |

新增70项：网络23、安全10、端点候选5、SETUP状态／报文／清理27、CF数值2、URL3。原函数来源核验不等于原ARM函数执行，也不等于真实车机互通。

第一轮149项定向测试失败1项：新fixture错误使用`IapWire.be32(-1)`构造U32，已改`0xffffffffL`，未删断言。后续完整回归全部通过。独立审阅指出“编码器创建前的prepare失败无人拆流”和“关闭后的迟到2xx丢失清理责任”；已补实现与确定性回归测试，最终审阅未发现本批范围内新的阻断项。

最后完整命令（手机仓库工作目录，JDK为Android Studio1/jbr）：

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest --rerun :app:compileXiaomiDebugKotlin --no-configuration-cache
```

证据JSON保存19个源码／测试哈希与122份JUnit XML哈希和计数。未执行APK/AAB打包、安装、真实网络切换、实车首帧／持续显示／重连。

## 4. 明确仍未补齐

1. **蓝牙／iAP2**：全部首次配对／反向发起、重协商／计时器、AA信任与继承、Identification全部feature合同；前三批只实现其有界子集。
2. **网络交接**：security类型到平台认证的完整映射、4301／Bonjour／邀请身份融合、复用Network的完整onLost生命周期、旧Android的指定网络发现入口。配置解析通过不是联网完成。
3. **AirPlay安全**：FeaturesEx变长表示及F80、完整CU／统一MFi／SAP事务、证书／签名验证与持久配对提交。当前安全模型仍是子集，明确拒绝未知机制不等于实现它。
4. **SETUP请求与视频**：无线kind5完整timing／features／字段presence、合并info请求的生产条件、verification附带info消费、完整屏幕流请求及资源许可顺序、streamID／cryptor全生命周期。
5. **端到端**：对应新构建的首帧、持续显示、首次／再次／异常重连尚未实车验收。已有用户成功反馈不被否定，但不能替代这一批新行为的验证。

因此G3/G4/G5/G7/G8/G9仍为PARTIAL，G6/G11/G12也没有因本地测试升级为完成。下一批应继续追网络身份融合与扩展能力来源，并落实无线kind5的SETUP请求presence；不能继续以“只差用户测一下”掩盖尚未实现的分支。
