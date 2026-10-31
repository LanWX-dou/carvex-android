# 77 — iAP2扩展校验修正与无数据等待边界


## 1. 本批结论

1. **75 的扩展门已纠正。**原生 `iAP2LinkCommandIsFeatureSetValid@0x1000d4ee0` 对 `0x54`、`0x55` 做 OR 汇总，不做出现次数检查。因此 link 2/3 的扩展数组现在接受空数组，或集合恰好包含 `0x54` 与 `0x55`；`54 54 55`、`55 54 55` 等重复但成对的输入也接受。缺任一操作码、含未知操作码仍拒绝。数量上限、扩展后 session 数量、session 列表长度和 descriptor 校验仍独立生效。
3. **普通蓝牙 type=2 不进入本次受限模式入口。**`_acc_policies_isTransportSupervised` 同时要求 connection type=1 及对应 transport 位；`_acc_endpoint2_isTransportRestricted` 对有效的 type=2/transport=2 因此为假。不能用它解释这条链路的 SYN 等待或卡住。
4. **发现的 5 秒定时器属于睡眠断言生命周期。**它在可到期的电源/充电分支中由 `ACCPlatformSleepAssertionManager` 安装，触发后走 `removeExpiredSleepAssertionForUUID:` 和 `expiredOnly=true` 的清理；在已审调用链中没有 Detection、SYN 或 SYNACK 调用。它不是 `detectTimeout=5000` 的固件等价物。
5. **publish 后的连接/端点 attached 通知确实有客户端转发边界。**`ACCConnectionInfoServer` 更新内部列表后，经 client filter 与 clientUID 门调用 XPC remote proxy，连接 type 和端点 transport/protocol 参数保持传递。该边界之后的业务客户端、全局等待预算和所有入口尚未闭合，不能据此宣称上层一定不会超时。

## 2. 手机端修正

后续范围澄清：[78](78-iap2-syn-negotiation-audit.md)区分了`IsFeatureSetValid`谓词与进入特定状态动作后的`ValidateFeatureSets`修正。本章接受/拒绝表说明该谓词及当前Android解析规则，不代表苹果所有状态下的最终处置；78没有改动本章已实施的手机规则。

### 2.1 规则

原函数的静态语义为：`54 → bit0`、`55 → bit1`、未知值置高位，随后 OR 汇总；只有 mask=0 或 mask=3 接受。对应到当前解析器：

| link 2/3 扩展 | 结果 | 说明 |
|---|---|---|
| 空 | 接受 | 无声明扩展 |
| `54 55`、`55 54` | 接受 | 两个已知操作码 |
| `54 54 55`、`55 54 55`、最多5字节且集合仍为两项 | 接受 | 原生 OR 忽略重复 |
| 只有 `54` 或只有 `55` | 拒绝 | 缺少另一位 |
| 含未知值 | 拒绝 | 高位标志被置上 |

代码位置：[`IapLink.kt`](../../../android/protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/IapLink.kt:176)。实现使用 `featureList.toSet()` 只用于集合判定，不把集合大小当作线上数量；本地回复仍不主动声明未实现的扩展。

独立保护仍保留：扩展数量不超过 5、扩展后必须有 session count、session 数量为 1..5、列表长度必须精确匹配，descriptor 的 ID/type 不能重复且必须有唯一 control session。新增的重复项测试还覆盖了数量 6、截断扩展和截断 session，确保放宽集合语义不会绕过长度门。

### 2.2 回归结果

- 定向：`IapPendingSynchronizationTest` + `IapLinkSynchronizationTest`，70 项，0 failures / 0 errors / 0 skipped。
- 完整模块：`:protocol-carplay:testDebugUnitTest --no-configuration-cache`，116 个 XML suite、875 项，0 failures / 0 errors / 0 skipped。
- 先补测试、后改生产条件：修正前选取4项测试，4项失败；其中3项因合法重复扩展被拒而收不到回复，1项在到达session长度门前错误地报扩展集合非法。修正后上述定向/完整回归通过。
- 当前文件 SHA-256：`IapLink.kt` = `f993647344aca7134d70a99e7a12bfa5f0eeac9a51cb9901af5fae2a8aa8da43`；`IapPendingSynchronizationTest.kt` = `64c4c51dcf59115f9f8e8ecc2fe8018956d0f8173730dd8db166aab8e3e35086`。

这些是 Android 内存流测试与源码完整性结果，不是苹果代码执行，也不是车机互通结果；没有打包、安装或修改车机端。

## 3. 固件边界审计

### 3.1 受限模式排除

`_acc_policies_isTransportSupervised@0x1000e2efc` 要求 transport≤8、`(1 << transport) & 0x1c3 != 0`，且 connection type=1。指定 type=2 / transport=2 两个条件均不满足。`_acc_endpoint2_isTransportRestricted@0x10018b5f8` 对空端点/空连接返回真；对有效连接则还要求 `getSupervisedTransportsRestricted_internal` 为真并通过上述supervised门，因此此BT输入返回假，无需猜测restricted flag的当前值。

端点构造 `0x10018a96c` 在supervised且非restricted时才调用 `acc_restrictedMode_accessoryAttached@0x1000f4bd8`；指定BT输入因supervised为假跳过。后者的 `ACMKernelControl` 调用虽已取到，但不属于本次普通蓝牙构造的可达路径；这不等于所有系统受限模式入口都已排除。

### 3.2 睡眠断言不是 iAP2 等待

`_platform_sleepAssertion_connectionTypeAllowsAssertion@0x1000e62b8` 在非 ATV 情况只显式接受 type 1、3、4、6；其他类型（包括 2）回退到 `isWatch` 检查，最后还与 `__shouldAllowSleepAssertions` 相与。因此普通非 Watch iPhone 的 type=2 不通过这个 endpoint-create 断言门。

能通过其他调用者进入的睡眠断言链为：

```text
platform_sleepAssertion_create_withInfo
  → ACCPlatformSleepAssertionManager sharedManager
  → addSleepAssertionForUUID:withConnectionType:
  → _addSleepAssertionForUUID:withConnectionType:
  → dispatch source timer
```

可到期分支在 `0x1000e5064..506c` 组装的间隔是 `0x12a05f200 ns = 5 s`，随后 `dispatch_time(now, 5 s)@0x1000e50f8`、`dispatch_source_set_timer@0x1000e510c` 安装一次性 timer。到期 handler `0x1000e52dc` 先将start/interval设回-1（停用），再调用 `removeExpiredSleepAssertionForUUID:@0x1000e5914`，其明确传 `expiredOnly=true`。

随后同步队列 block `0x1000e56c8` 移除对应timer记录；`expiredOnly=true` 时跳过从 `sleepAssertionUUIDs` 移除UUID，保留跟踪。UUID集合为空才清理电源通知；最后调用插件 `destroySleepAssertionForUUID:`。这不能简写成“到期删除连接”或“清空所有UUID”。插件的更深实现没有在本批展开，因此只说明调用边界，不推断最终电源行为。

### 3.3 attached 通知的下一跳

连接通知：

```text
accessoryConnectionAttached:type:info:properties:
  → 更新 accessories / 复制 clientConnections
  → updateFilteredListForClient:
  → accessoryConnectionFiltered:forClient:
  → XPCConnection.remoteObjectProxyWithErrorHandler:
  → accessoryConnectionAttached:type:info:properties:
```

端点通知结构相同，并保留 `transportType` 与 `protocol`：

```text
accessoryEndpointAttached:transportType:protocol:properties:forConnection:
  → endpoints 字典/数组更新
  → updateFilteredListForClient:
  → accessoryEndpointFiltered:forConnection:forClient:
  → XPC remote proxy
  → accessoryEndpointAttached:transportType:protocol:properties:forConnection:
```

`forClient` 在filter返回false、clientUID非空时才取得 `XPCConnection` 和remote proxy；并未在此证明XPC连接实际健康。端点主入口 `0x1000131cc` 先把protocol保存到栈，再于 `0x10001340c` 原样取回；`forClient@0x100013a68` 的x3/x4保存到x24/x23，在 `0x100013c28/2c` 恢复传出。连接type也在 `0x10000e534 → 0x10000e688` 保留。

这证明了条件转发和参数保留，不证明每个客户端都收到，更不证明收到后安装了哪一个iAP2/SYN预算。filter更新内部、所有业务receiver/handler注册和其他provider仍是开放边界；错误回调的常规路径已取到，但未以未展开的共享cold日志块作为“绝无其他副作用”的证据。

## 4. 当前仍不能下的结论

- 不能把 5 秒睡眠断言到期解释成“5 秒没有 SYN 就断开”。
- 不能据此决定首次应主动发送 Detection+SYN；该策略仍按[74](74-iap2-startup-initiation.md)保持 `PARTIAL`。
- 不能声称所有无输入超时、所有 XPC 客户端、所有 profile/session provider 已查完；本批只闭合到 attached notification 的下一跳。
- 不能声称因此支持更多车型；真实蓝牙 socket、车机接收和首帧仍需独立 attempt 证据。

## 5. 证据与下一步


本批独立复核工具为 [`verify_iap2_wait_boundary.py`](../tools/verify_iap2_wait_boundary.py)，不要把旧工具的 `verify`（固定检查76证据）误当成77校验。此证据记录24个函数：21个本批边界函数、2个复查的构造入口、1个重复复核的feature validator。

最终复核通过：1份源镜像、24个函数字节/边界/哈希及24个既有函数缓存一致；两份手机文件哈希、116个suite/875项XML统计一致。文档完整性检查通过：47份Markdown、39份JSON。这些是完整性检查，不是新增协议语义或实车验收。

```text
wsl -e python3 -B /mnt/d/carvex-research/research/connection/tools/verify_iap2_wait_boundary.py --check-android
python D:\carvex-research\research\connection\tools\validate_docset.py
```

下一批应沿 attached XPC 客户端和其他端点 provider 继续找“等待预算”的真正 owner，并单独处理第二次 SYNACK 的完整重协商；在取得新证据前不调整首次握手发起策略。

