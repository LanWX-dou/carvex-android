# 24 — 断开、部分流关闭与重新连接的生命周期

日期：2026-10-29。基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`PARTIAL`；本章关闭若干有界静态分支，不宣称完整恢复策略或实车重连已通过。

证据：[disconnect-evidence.json](../evidence/disconnect-evidence.json)。本轮重新把 22 个缓存函数的原始字节与提取 Mach-O 对应地址逐字节比较，并从原共享缓存读取 3 个函数、字段字符串及超时初始值；未执行原函数、未抓包、未连接车机。缓存字节一致不保证反编译类型正确；有截断警告的清理函数以指定汇编范围核对。

## 1. 首先分清三个动作

| 动作 | 原代码中的边界 | 不可混淆 |
|---|---|---|
| 线上 TEARDOWN | 当前控制 stream 上发送内部 `tdwn` 操作，由控制封装转为 RTSP TEARDOWN | “开始清理”不代表请求已经写出，更不代表车机收到 |
| 本地 stream/session 失效 | 移除回调、清会话中的 stream 槽、投递失效工作并释放关联对象 | 本地函数返回 0 不必然有线上事务 |
| 持久身份/配对记录变更 | 本章没有审到足以关闭其策略的 provider/store 调用链 | 释放 pairing client/key holder 不是删除蓝牙 bond 或持久配对记录 |

已审调用点至少存在整会话、指定 stream 数组、屏幕 Suspend 和 fatal cleanup 四类路径；不得统一成“无论何时断开都发送同一包，然后删掉全部身份”。

## 2. 整会话停止：消息与九问合同

`___apsession_EnsureStopped_block_invoke @ 0x251b5e7c4` 的完整退出分支与共享连接的部分退出分支不同。[LC02]

| 问题 | 已证实内容与边界 |
|---|---|
| 1. 前置 | session 尚未 invalid；函数检查当前连接状态。options 缺失、未启用 connection sharing，或选择内部 teardown type=2 时走本章所述整会话分支。不是仅由 kind=5 决定。 |
| 2. 发起方/通道 | 手机发送端在当前控制 stream 上发起；没有控制 stream 时发送 helper 可直接返回 0。 |
| 3. 请求/响应 | 整会话向 helper 传 `streamDescArray=NULL`、内部 type=2；字典不放 `streams`。收到成功且有回复字典时可取 `teardownMetricsPayload`。控制封装和响应错误判定见 [22](22-control-wire-contract.md)。 |
| 4. 字段/缺省 | `teardownType` 只在 session storage `+0x10` 非零时写入；来源是创建选项 `UseConnectionSharing` 的非零整数结果。未启用时不是写 `teardownType=0`，而是不放该键。[LC01/LC06] |
| 5. 定值/动态 | `tdwn=0x7464776e` 为内部操作码；type=2 是该整会话调用分支的参数，不是所有 TEARDOWN 固定必填。URL、控制连接、CSeq 均由当前会话提供，不复制旧连接。 |
| 6. 接受/拒绝 | 本地先清 stream registry，再检查 connected；connected 时才调用发送 helper。helper 错误会进入返回错误分支；不能把 registry 已清当作车机确认。 |
| 7. 成功证据 | 分别记录本地选择整会话分支、请求写出、对应响应被接受、本地控制/事件/数据停止。没有控制 stream 或已不 connected 的返回成功属于本地无操作，不是 peer ACK。 |
| 8. 超时/重试/清理 | 此函数仅在发送 helper 返回成功后、整会话分支内调用 disconnectControlStream；发送错误并不在该函数中无条件继续到 disconnect。更外层错误处理和强制清理必须另追，不能伪称此函数保障失败后全部释放。超时见 §6。 |
| 9. 下一事件 | 本地断开与资源释放；若用户/平台发起下一次连接，再独立验证其入口、安全与显示。这里没有一个“收到 TEARDOWN 回复就自动重连”的状态转移。 |

关键汇编锚点：`0x251b5ea1c–ea3c` 清 registry 并选 NULL/type2；`0x251b5ec9c–ecc4` 检查 connected、发送、检查返回码、条件 disconnect；`0x251b5edec` 为发送失败分支。

### 2.1 TEARDOWN 字典不是同一种固定模板

`_apsession_sendTeardownWithStreamDescArray @ 0x2519ce5c4`：[LC01]

| 输入/字段 | 类型与来源 | presence/缺省规则 |
|---|---|---|
| `streams` | 调用者提供的 stream descriptor 数组 | 指针非 NULL 才插入；非 NULL 空数组仍是空数组，不等于不带字段 |
| descriptor `type` | 单流入口用指定 stream type 覆写为整数 | 不靠 streamConnectionID 反推类型 |
| descriptor `streamID` | 可选 descriptor/注册表的本次 ID | 单流入口缺 options 时用于 registry 查询的 ID 为0；这只证明局部回退，不代表可自行给所有流补0 |
| `teardownType` | 调用参数的有符号32位值扩展后写整数 | 只有 `UseConnectionSharing` 对应槽非零才写；不是 kind=5 自动必有 |
| `teardownMetricsPayload` | 回复对象，局部代码未强制指定内容类型 | 仅 NULL-array 请求成功且有回复时保存；本章不把其内容当释放确认协议 |

原共享缓存确认的精确键：`streams@0x27612ff50`、`teardownType@0x27612ff70`、`teardownMetricsPayload@0x27612ff90`、`UseConnectionSharing@0x276136b70`。没有 control stream 的 `0x2519ce60c → 0x2519ce840` 路径直接返回 0，没有调用发送接口。

`streamDescArray=NULL` 本身只证明不放 `streams`，不能单独等同整会话关闭：helper 在该分支仍独立检查内部 type 是否为2（`0x2519ce64c–ce654`）。§2 所述整会话 `EnsureStopped` 分支具体传入 NULL/type2；共享连接分支和是否断开还需分别检查调用者条件。

## 3. 部分流关闭：注册表变化先于发送

单流 `_apsession_teardownStreamInternal @ 0x2519cce10` 的局部顺序：[LC03/LC07]

1. 检查 invalid、`(type, streamID)` 是否在 registry、控制 stream 是否存在。
2. 复制 options 字典或新建空字典，覆写 `type`，放入单项数组。
3. 取 streamID，调用 `_apsession_unregisterStream`。
4. 调用 TEARDOWN helper，参数为该数组和内部 teardown type=0。
5. 发送出错时记录错误，随后仍走 keepalive 模式重评；**该函数最后返回的是 keepalive 重评结果，不是必然保留的 TEARDOWN 发送结果**。

第5点由汇编 `0x2519cd038–cd068`、错误跳转 `0x2519cd090–cd094` 确认。单看调用返回0可能掩盖此前发送失败，不能用作 peer 已关闭流的证明。

批量 `___apsession_TeardownStreams_block_invoke @ 0x251b5eefc` 则先枚举 descriptor，各取 type/streamID 并注销，然后检查 connected，决定是否发送。[LC04/LC05] 注销函数 `0x251a61c48` 以 `%lu-%llu` 形成键，移除这一项；不是删除“所有相同类型的流”。全量同类型多流、未知ID、重复关闭及失败回滚仍需各自证明。

| 九问 | 部分流合同 |
|---|---|
| 前置/发起方/通道 | 当前 session 与本次 registry 项；手机经原控制 stream 发出，不新建一个独立控制连接 |
| 格式/类型/来源 | 非 NULL descriptor 数组；type 整数、本次 streamID及options；值来自流对象/注册表，不是固定车机样本 |
| 必填/缺省/定值 | 单流调用覆写type；缺options的局部ID0回退与车机是否接受分别记录；请求内部type0并不强制在线出现teardownType |
| 接受/拒绝 | registry命中、控制存在、发送及响应结果必须分开；没有本轮证据证明注销失败会自动回滚或重新注册 |
| 成功证据 | 指定流的线上响应与本地停止分别可关联；其余流继续工作的证据独立取得 |
| 超时/退出 | 不把单流函数最终返回0当发送成功；全生命周期与重试次数仍OPEN |
| 下一事件 | 剩余流继续、keepalive模式重评，或外层继续关闭会话；不能把部分流关闭等同整会话断开 |

共享连接的 type=1 分支含内部日志“downgrading from AP to RC-only”及 NewSessionUsage/EndpointDescription 输入检查；它不是本章无线全停止的默认路径，也不把内部枚举名直接作为所有车机线上语义。

## 4. 控制/事件 stream 的本地失效与晚回调边界

`disconnectControlStream @ 0x251a56e44` 先停止需要停止的 sender network clock，再调用 `ensureDisconnected @ 0x251b5b9d8`，随后释放 session 内 `+0x138/+0x140/+0x148/+0x150` 对象以及部分 info/setup 状态。[LC08/LC09] 这些是临时对象生命周期，不是持久配对记录删除的证明。

`invalidateAndClearTransportStreams @ 0x251a56168` 的可证顺序：[LC10/LC11]

| 层 | 事实 | 尚未证明 |
|---|---|---|
| 监听器 | 移除旧 transport session 的 disconnected 和 keepalive-response 通知注册 | 已排队的每个通知都会被撤销 |
| 活跃槽 | 把 control `+0xf8`、event `+0x100`、另一stream `+0x110` 转移到局部失效 context，并清空会话槽 | 此刻物理 socket 已关完 |
| 队列 | 把该 context 投递到 session 的 invalidation queue；清连接状态位及关联对象 | 整个系统有统一 attempt generation 或排空确认协议 |
| 失效工作 | `0x251a5692c` 依次处理 context中三个stream：清回调参数、调用对象失效方法、release；最后release保留的session | 所有关联 OS 回调/发送缓冲都已同步取消 |
| 通知 | ensureDisconnected 在先前连接状态符合条件时发布 Disconnected | 收到该本地通知等于车机确认TEARDOWN |

`0x251a5692c` 的 C 在 authenticated tailcall 处被误截断；原汇编 `0x251a56a48–a54`、`0x251a56b50–b5c`、`0x251a56c58–c80` 确认逐一 release 后继续下一项，不能依残缺 C 解释为“只处理一个 stream 就停”。

因此，禁止把旧分析中 LOCAL 的“统一 attempt ID、旧对象保留到owner销毁、cleanup ACK、最多8次”等规则写成苹果固件行为。它们可作为我们未来实现的测试方案，但不是本章恢复出的常量或线上协议。

## 5. 屏幕 Suspend 与 fatal cleanup 的不同

| 路径 | 已确认局部顺序 | 是否请求 per-screen session TEARDOWN |
|---|---|---|
| Suspend | `0x251bd642c` 检查对象状态；stopStatsTimer → 调用生产侧暂停方法 → teardownTransportStream(stream,0) → 清/处理样本队列 → resumed=false | 在有效 transport/session 等条件下，第二参数0允许调用session teardown |
| Fatal error | `0x251b43140` 分别投递错误通知和 dissociate 工作；`0x251b43370` 调 `0x251bd62c8`；后者必要时 cleanup，再标 invalid | cleanup `0x251b42e34` 调 teardownTransportStream(stream,1)，跳过该 per-screen 线上调用 |
| 本地 teardown | `0x251bd5e48` 先移除取数据回调；对transport执行失效；按第二参数条件调用session；释放transport并清缓存/cryptor关联区 | 不是每次都发；配置/统计的部分值会在清理块前保存、清理后恢复 |

这里已经闭合 `teardownTransportStream` 布尔参数的两条具体生产者，不再笼统说它完全未知；但不能外推到所有退出原因。[LC12–LC17] Fatal cleanup 后更上层是否关闭整个 AirPlay 会话仍需追踪，不能说整个系统绝不会发送 TEARDOWN。

`stopStatsTimer @ 0x251b42fd4` 的原汇编是对现有timer传入 `(-1,0,0)` 后尾调用，不是直接把 timer 槽置空或释放；它停止定时触发的具体dispatch API绑定未在本章重做。不把“停timer”写成“所有timer对象均销毁”。[LC18]

### 异常恢复九问

1. **进入条件**：实际错误/取消已归属到旧stream或session，而不是仅车机UI变成“连接中”。
2. **发起方/承载**：错误可由发送端生产/transport引发；本地队列清理不依赖能向已断网络发送请求。
3. **消息**：上述fatal屏幕路径可跳过per-screen TEARDOWN；控制级或其它上层消息另查。
4. **字段/状态**：清活跃stream槽与对象invalid位；保留旧错误、关联ID和必要诊断，不复用旧“ready”标记。
5. **动态输入**：下一次网络接口、地址/端口、流ID和加密上下文须重新关联；原配对存在不保证临时会话有效。
6. **接受/拒绝**：本轮未证明通用跨队列generation判据；单个invalid位只证明该对象的局部检查。
7. **成功证据**：旧会话不再产出/写入；新会话独立完成协商并实际显示变化画面，不要求取得无法访问的车机内部日志。
8. **超时/清理**：原生重连调度、退避次数、旧队列排空及Wi-Fi/bond策略仍OPEN；不能将下节消息等待值当恢复预算。
9. **下一事件**：由当前平台状态选择重新发现、控制邀请或重建会话的入口；首次/正常退出重连/异常恢复分别验收。

其中“重新关联、不得复用ready、旧会话不再写入”是验收要求，不是宣称已经在原固件找到一套统一owner框架。

## 6. 超时：producer 已找到，但不能写成“全程60秒”

这是本轮新增、能影响定位的静态事实。单位与等待消费者见 [22 — 控制消息封装](22-control-wire-contract.md)。

| 层/地址 | 已复核结果 | 边界 |
|---|---|---|
| `_APSenderSessionMessageSendTimeout @ 0x251ab0f14` | 返回全局32位值；原缓存 `0x26e7da508` 初值 `3c000000`，即60 | 是provider默认，不是所有会话、请求或阶段固定60秒 |
| once initializer `0x251ab0f4c` | 读 `senderMessageTimeoutSecs`；低32位有符号比较结果至少1才覆盖全局 | 偏好读取仅once；极值/实际偏好未运行验证 |
| kind=5控制创建 `0x251a5b22c` | `0x251a5cfd0–cfe0` 检查kind5，直接给10；非kind5才调用上述provider；随后属性setter | **无线主线kind5控制创建点不是默认60，而是10这个输入值**；不能据此宣称每次实际请求都必在10秒超时 |
| event创建 `0x251a5dec0` | 调provider，把返回值交同类属性setter | 事件通道用60默认/已接受偏好；不是复制控制通道10 |
| 属性key | `0x2680fc070 → 0x269378088 → 0x275fa82a0`，精确CFString为 `PackageSendTimeout` | 原符号常称 MessageSendTimeout，符号名与实际字符串必须分开 |
| 数字setter | 跳板 `0x258109dc0 → 0x226e64e74`，`APSSetFBOPropertyInt64` 构造数值对象并调用对象SetProperty | 本轮未独立重绑具体stream vtable到下述consumer，需保留此边界 |
| APTransport consumer `0x24fdaf4a8` | 比较同一 `PackageSendTimeout` 字符串，先交底层connection对应属性；只有返回 `0xffffce10` 时才转为0…UINT32范围整数并写stream `+0xb0` | connection直接接受属性时不走本地fallback；不能把provider值无条件等同wrapper读出的 `+0xb0` |
| reply waiter | 从stream `+0xb0` 取等待值，换算为纳秒deadline；0的无限等待见22 | 与下层package发送超时、socket连接、总attempt和重连预算不同 |

还有一个明确的覆盖调用点：type103的单流teardown前，对现存的非空控制/event对象尝试设置provider值，但调用后不检查setter返回结果。[LC03 `0x2519ccf10–ccf78`，其中setter调用为 `0x2519ccf48`、`0x2519ccf70`] 本章不展开音频；这里只证明生命周期中存在覆盖调用，不证明属性设置成功，也不能在创建时读出10就断言以后永不变化。

超时排障至少分别记录：调用层、属性来源、是否覆盖、connection是否消费还是fallback、实际wait值、请求写入完成与响应时间。没有本次运行证据时写“静态默认/调用输入”，不写“本次车辆等了60秒”。

## 7. 重新连接的验收与故障定位

当前只证明若干资源局部退出与条件字段，**未证明**自动重连入口、全链路退避/预算、持久身份复用决策，以及所有晚到回调都无法污染新尝试。

| 表象 | 最后成功事件 | 下一预期 | 缺失/失败可能在哪层 | 区分证据 |
|---|---|---|---|---|
| 点退出后仍停在CarPlay | 本地EnsureStopped开始 | TEARDOWN实际写出/回复或强制清理 | 无control而helper返回0；写入失败；回复等待；外层未继续清理 | 本次control身份、请求CSeq、字节完成、返回值来源、失效队列进展 |
| 单个屏幕关闭后重开失败 | registry已注销 | 原流停/新流SETUP | 注销先于send；线上失败未回滚；新ID关联错误 | registry键、发送状态、keepalive最终返回不得混淆、下一次SETUP |
| 视频错误后没有TEARDOWN | fatal callback已进 | 本地dissociate/cleanup | 可能是正常skip-per-screen路径，不可直接认定漏发 | skip参数producer、错误发生时间、上层整会话关闭情况 |
| 第二次连上但旧画面/立即断 | 上次已显示 | 新attempt配置/新帧/显示 | 旧回调、旧端口、旧密钥状态、旧样本队列 | 分别标记旧新会话与对象；验证旧发送停止和新首帧 |
| 等待时长不同 | 属性已设置 | 对应消息响应/超时 | kind5控制10、event默认60、生命周期覆盖、底层消费与fallback差异 | 调用地址/属性值/owner/实际deadline，而非只看UI计时 |

对照 [50](50-test-matrix.md) 的 T01/T02/T03/T09/N12/N13/N14。记录普通车机屏幕录像即可证明本次显示/更新；不能用源码静态退出分支证明重连已经成功，也不要求修改车机来制造内部日志。

## 8. 本轮关闭范围与仍开放的问题

- `AP-U07` **部分关闭**：整会话/数组TEARDOWN的presence、connection sharing门槛、无control本地成功、注销先于发送、控制/事件局部失效队列已核对。全错误出口、重试、跨队列race、peer/store生命周期仍OPEN。
- `V-OPEN-06` **部分关闭**：屏幕Suspend与fatal cleanup对skip参数的两条生产链已闭合；所有退出原因、OS取消完成及重连仍OPEN。
- `AP-U04` **部分关闭**：timeout provider默认60、kind5控制输入10、event输入provider，以及PackageSendTimeout的条件fallback已证；不是全栈超时表。
- `B-OPEN-07` / `G12` **仍未验收**：本章没有首次、再次、异常断线的真实无线端到端时间线或持续显示证据。


