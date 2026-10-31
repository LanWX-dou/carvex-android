# 63 — 手机实现对齐：第一批修改与验证

日期：2026-10-29。目标仍为 **iPhone18,1 / iOS 27.0.1 / 24A446**。本批在用户授权后修改 `D:\carvex-research\android`，不是对24A446完整复刻的完成声明。


## 1. 与前一批审计的关系

[14](14-iap2-version-capability-audit.md)、[23](23-airplay-version-capability-audit.md)、[62](62-version-capability-audit.md) 以及其证据 JSON 是**修改前快照**。它们记录的源码哈希、行号和差异不得直接作为本批修改后的现状。

本批不覆盖旧 JSON 的输入哈希，也不通过改哈希让历史审计器对新源码显示通过。`verify_profile_audit.py` 如果报告手机源码哈希变化，须按快照差异解释；原固件证据没有因此改变。本批验证依据是当前源码、实际序列化报文测试、完整测试报告和编译结果。

## 2. 已实施内容

| 项目 | 本批实现 | 证据边界 |
|---|---|---|
| iAP2 control-session 版本 | 链路在输出 SYNACK 前复用 `IapStartupPolicy`；仅接受本实现已支持的1/2，不再先回发未知版本再由 Bootstrap 拒绝 | 本地支持边界；不是将所有车机降级到1，也不是苹果全部版本范围 |
| 第二份 SYNACK | 除 MTU 外，已解析的参数和 session 集合须与第一份提案一致；MTU 只能收紧。变化提案不输出最终 ACK、不提交 | 本地有界拒绝策略；完整重协商及未知扩展语义仍未实现，不宣称苹果也按此规则拒绝 |
| AirPlay 请求头 | 同步、异步、单向发送共用构造器；所有 SETUP 和精确 `GET /info` 一致加入 `X-Apple-ProtocolVersion: 1` | 对齐已审 `stup/info` 的统一提供者结构；值1保持当前实现声明，不宣称已支持苹果provider的全部0/1/2 |
| 版本头冲突 | 同名大小写不同且值相同的extra合并；冲突值及非目标请求显式注入在写出前拒绝 | 本地一致性保护；其他extra既有语义不改。带query或绝对URL的info未擅自映射 |
| 4301来源保存 | 新增 `StartSessionPeerInfo`，保存字段5/6/8，即srcVer、sdkVer、mutualAuth；与Bonjour、手机本地身份分开 | 保留声明不等于使用它完成安全路线选择；未根据mutualAuth自动改变信任或认证 |
| 4301解析 | 按线上顺序处理；合法重复标量末值覆盖，任何先出现的非法值立即拒绝本消息；Bool区分缺失/false/true，拒绝其他值和宽度 | 字符串要求最后字节NUL，之后仍使用现有文本解码；未完整复刻CF字符串转换/非法UTF-8语义 |
| 端点快照 | 先构造完整endpoint，再生成WifiBootstrap/startSession，保留多地址及4301声明；发现新端点时仍保留原startSession来源 | 不把重新发现的Bonjour属性写入原4301，不从旧连接继承版本或认证成功 |
| 诊断 | 记录实际选出的security route；世代标签明确仅诊断，删除“/info wins”式无实际重选的断言；4301拒绝日志含字段编号/类型/长度 | 不输出4301任意版本字符串或凭据，不把日志当作安全流程已实现 |

4301相关原定位：`accessoryd 0x10016d3ac`，字符串getter `0x100067ee4`，Bool getter `0x100067e74`。协议头provider及原跳板见[62 §2](62-version-capability-audit.md#2-airplay-协议版本头已经确认的发送差异)和 `evidence/version-header-evidence.json`。

## 3. 手机源码范围

本批生产代码涉及：

- `core/IapLink.kt`、`core/IapStartupPolicy.kt`：握手支持边界及第二SYNACK一致性。
- `core/Rtsp.kt`、`core/CarPlaySourceIdentity.kt`：统一控制协议头。
- `StartSessionPeerInfo.kt`（新增）、`StartSessionFields.kt`、`Bootstrap.kt`：解析、来源保存、完整端点快照及脱敏拒绝原因。
- `AirSession.kt`：移除重复的手写版本头、准确记录实际安全路线。

以上相对路径均位于 `protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/`。对应新增/扩展测试位于同模块 `src/test/java` 下的 `IapLinkSynchronizationTest`、`IapStartupPolicyTest`、`RtspClientTest`、`CarPlaySourceIdentityTest`、`BootstrapConfigTest`、`BootstrapSecurityTest`、`BootstrapNegotiationTest`；未修改的 `IapLinkRestartTest` 也纳入回归。

工作树在本批之前已有大量未提交修改；相对HEAD的整个diff并不等于本批内容，尤其不能把已有音频修复归入或撤销。

## 4. 实际验证结果

| 检查 | 结果 |
|---|---|
| 8组定向单测 | 152项，0失败、0错误、0跳过 |
| `:protocol-carplay:testDebugUnitTest` 全量 | 101组、665项，0失败、0错误、0跳过；本批实际执行 |
| `:core:testDebugUnitTest --rerun` | 12组、79项，0失败、0错误、0跳过；显式重跑，不只引用UP-TO-DATE |
| `:app:compileXiaomiDebugKotlin` | 成功；实际执行Kotlin编译，不是APK打包 |
| `git diff --check` | 通过；Git另提示部分已有文件的CRLF/LF转换，不是空白错误 |

定向152项是全量665项的子集，不能相加宣称额外覆盖。两个模块全量共 **744项**。报告读取自各模块 `build/test-results/testDebugUnitTest/TEST-*.xml`；最终报告时间为本日UTC 04:41，对应台北12:41。

首次定向运行有1项失败：4301畸形Bool被拒绝、后续有效消息能完成交接，但拒绝日志只写异常类，漏了具体原因。补充脱敏字段编号、错误枚举、长度后重跑全部通过；不是删除断言或忽略失败。

执行命令（工作目录为手机项目）：

```powershell
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests '*IapLinkSynchronizationTest' --tests '*IapStartupPolicyTest' --tests '*IapLinkRestartTest' --tests '*BootstrapConfigTest' --tests '*BootstrapSecurityTest' --tests '*BootstrapNegotiationTest' --tests '*RtspClientTest' --tests '*CarPlaySourceIdentityTest' --no-configuration-cache
.\gradlew.bat :protocol-carplay:testDebugUnitTest :core:testDebugUnitTest :app:compileXiaomiDebugKotlin --no-configuration-cache
.\gradlew.bat :core:testDebugUnitTest --rerun --no-configuration-cache
```

编译仍报告nullable/冗余非空断言、Android弃用API及Gradle弃用特性等警告；本批没有将警告当成构建失败，也没有扩大范围清理无关代码。

## 5. 尚未完成与下一步

- 当前 `sourceVersion=320.17`、`osBuildVersion=21A329` **未迁移**，仅是保留现有音频行为的过渡兼容组合，不能成为24A446目标标准。
- Identification 的required 8/9、12/13具体内容和承载组件合同仍待补齐；本批没有仅为收紧而仓促修改动态提供者。
- formal/SAP等未实现路径仍保留安全门槛；保存mutualAuth不等于完成其原消费链，也没有删除认证检查。
- 尚未闭合24A446完整身份提供者、能力条件与所有失败/重协商路径。
- 后续先补Identification接受合同及其负例，继续核实真实版本/能力消费者，再做成套身份迁移；不逐个试大版本号或加车型白名单。
- [50测试矩阵](50-test-matrix.md) 的实车项目保持 `NOT_RUN`。本批无法据此宣布奥迪、Toyota或所有车机连接问题已解决。
