# 16 — Identification 生命周期分支、取消、更新与重连边界

日期：2026-10-29。基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`BOUNDED_STATIC_AUDIT`，不是固件执行、车机互操作或完整重连证明。

本章承接 [12 — Identification contract](12-identification-contract.md)，只补生命周期分支：初次 `1D00/1D01/1D02/1D03`、异步授权、`1D05` 取消、`1D06` 更新、清理和世代边界。原 `accessoryd` 的当前 Mach-O 为逐字节来源；已有逐函数证据见 [identification-contract-evidence.json](../evidence/identification-contract-evidence.json)，本章22个函数/缓存原字节与8份手机源文件的稳定快照见 [identification-lifecycle-branches.json](../evidence/identification-lifecycle-branches.json)。可用只读工具 [inspect_identification_lifecycle.py](../tools/inspect_identification_lifecycle.py) 的 `--compact` 复核快照，`--inspect VA:length` 查看原字节反汇编。工具输出是字节来源/反汇编记录，不是覆盖率或运行结果。本章审计没有执行原始代码、CF/授权服务、手机 APK、车机或 Gradle。

快照由WSL中的Python生成，JSON路径前缀`/mnt/d/`对应Windows的`D:/`，不是另一个固件基线。请在WSL重跑上述工具；Windows端校验外部路径时先作这项映射。

## 1. 先分清三种状态命名空间

固件的 identification state（0、1、2、3、4、6）和手机 `PeerNegotiationController` 的 `IDLE/STARTED/ACCEPTED/REJECTED` 不是同一组数字；也不能把 `RuntimeIapState.CONTROL_READY` 当作固件 state6。下表只列本章实际需要的关系：

| 状态/事件 | 原 `accessoryd` 局部含义 | 手机生产路径对应 |
|---|---|---|
| 0 → 1 | `0x1000511d0` 构造无参数 `1D00`；发送返回 bit0 才写1 | `Bootstrap.negotiateRuntime`/主 `Bootstrap` 的 `send(0x1d00)`，带 link generation/epoch 检查 |
| 1 或 3 | `1D01` 可进入；3 是拒绝后仍可再次提交的识别入口 | `PeerNegotiationController.STARTED` 只在当前协商尝试中使用，没有生产调用把拒绝后的同一 link 再置回 STARTED |
| 2 | 接受路径已写入 state2，正在/已经提交 `1D02`；发送失败时本函数停在2 | `identificationAccepted` 前后的控制器状态，不是“已发到车机”的证据 |
| 6 | 识别信息发布到 endpoint；允许 `1D06` 增量更新和后续业务门槛 | `PeerNegotiationController` 的 `accepted` 加 authentication complete；二者仍是手机自己的状态 |
| 4 | `1D05` 取消时，若当前为1/3则写4并显示“不支持”通知 | 手机目前在协商循环内把收到的 `1D05` 作为 `IOException` 终止协商 |

## 2. 原固件的初次事务：失败不会都等价于断链

原始控制流可以压缩为以下分支（函数地址是 `accessoryd` 中的真实 VA）：

```text
1D00（state=0）
  └─ send bit0=1 → state=1
      └─ 1D01（只接受 state=1 或3）
          ├─ ForEach 参数返回非零（未知参数或任一回调失败）
          │    → 授权回调 → 检查失败分支 → 1D03
          ├─ required/transport/feature/message-set 检查失败
          │    → 授权回调 → 检查失败分支 → 1D03
          └─ 检查通过 → 平台/用户授权
               ├─ 授权结果非允许 → 本次 completion 直接返回，不在此处发1D02
               ├─ 允许且 checkResult=0 → state=2 → 无参数1D02
               │    ├─ 发送 bit0=1 → state=6，并发布 accessory info
               │    └─ 发送失败 → 留在 state=2（本函数不改成3）
               └─ 允许但 checkResult≠0 → 1D03
```

`0x1000511d0` 的 `1D00` 只在 state0 起作用；`0x10013bcc8` 的入口条件是 `state & ~2 == 1`，即 state1/3。关键更正：参数遍历返回非零时不会“记录未知 ID 后继续接受”。`0x10013be78` 的分支把非零 ForEach 结果送到拒绝授权上下文；未知字段、字段回调错误和其他遍历错误都不能因为字段位于消息末尾就当作可忽略。此前手机注释中“unregistered parameters recorded, not rejected”的表述与这个原分支不一致，应只保留为当前手机行为说明，不能写成苹果行为。

`0x100050dcc` 的第一条指令按授权结果分支：非允许结果直接返回；允许后才看捕获的检查结果。成功路径先写 state2、构造并提交无参数 `1D02`，`sendOutgoingMessage` 返回值 bit0=1 才写 state6。state6 后还会按当前识别/feature 条件触发连接事件；这不是 AA、网络或 AirPlay 成功证明。成功/失败之后才做 captured info 与当前安装 info 的比较，该比较是 rejection scratch 的释放保护，不是完整旧回调世代隔离。

`0x10013b540` 的拒绝 sender 使用与 `1D02` 不同的返回判据：有 reject-message 指针时，原实现按非零发送结果作为成功分支；成功时清除转移的拒绝字段指针并写 state3，失败时在进入后续 cleanup 前保留指针/状态。还有一个容易遗漏的分支：`info+0x98` 为NULL时**不调用send**，直接写state3并走feature cleanup；所以仅看到state3也不能反推线上已经出现`1D03`。session/info为NULL时返回-1；正常state3路径返回0，send返回0的路径最终返回1。两类有效上下文路径均调用 feature rejection cleanup，其内部回调可能进一步改变对象，不能把“本sender未清指针”写成最终永不释放。不要将两个发送结果简化为同一布尔含义，也不要把本地 reason 当成线上额外 reason 字节。

## 3. 异步授权：入口、捕获物和未闭合项

识别授权 hook 为 `0x10011e1f0`。它先读取 AA state：

- AA state=0：直接通过 outlined helper `0x10000946c` 调用 completion，传入值1；这是该 hook 的直接允许分支，不能推导平台策略/证书验证已经通过。
- AA state 非0：复制证书序列字符串，调用 `__requestAuthorization@0x10011dfd8`，完成后释放复制的序列。
- `__requestAuthorization` 检查 session/root/root有效，再调用 `endpointRequiresUserAuthorization`；不要求时直接 completion(1)。要求时 retain endpoint UUID、非NULL证书序列/名称，并构造异步 block；无线分支的 providesPower=false，有线分支读取当前限额是否非零。这不是重新验证证书链。
- `0x10002ab44` 记录开始时间并调用 `_requestAuthorizationForCertSerial`。完成 block `0x10002acd4` 的许可结果为0时只走日志/释放 UUID 分支，并**不在这条路径转调 identification completion(0)**；非零结果才继续按 endpoint UUID 查当前 connection，查不到则不回调。这不同于“每个授权拒绝必触发1D03”。
- `0x10002af18` 通过 manager 找到的当前 endpoint 参数检查：endpoint非NULL、`+0x38`非NULL、raw type `+0x1c==4`。其内部 `+0x38`对象的`+0x18`非NULL时，按 connection/endpoint 再派发 `performBlockForEndpoint_asyncWithCleanup`；为NULL时调用原 completion(0)。异步工作 block `0x10002b02c` 再检查 endpoint存在、`+0x38`存在、raw type4，才调用原 completion(1)；清理 block `0x10002b084` 释放 retain 的 endpoint 标识。这些是原实际检查，不把 raw type4自行翻译成未经本章证明的承载名称。

这些 endpoint 重查是生命周期保护，不能只盯 captured-info 比较就宣称“苹果完全没有旧回调保护”；但它们也未证明跨连接UUID复用、取消及 Identification state/对象的完整关联。`0x10002acd4` 还含授权耗时 `>=0x2ef` 时调用 resetLightningBus helper 的分支，本章不把它当无线重试定时器，也未闭合该平台 helper 的实际作用。平台授权服务最终回调线程、取消 API、endpoint 释放竞态、completion 是否总能回调仍 OPEN。`0x100050dcc` 的 result=0 早返也不能解释成“自动拒绝”或“自动重试”；不得用手机10秒/30秒 deadline反推苹果固件定时器。

## 4. `1D03` 之后的清理和再次提交

`0x10004dd50` 的发布边界是确定的：state1/3 调 `_acc_endpoint2_clearAccessoryInfo`，state6 从当前 info 组装并 `_acc_endpoint2_setAccessoryInfo`；每次状态变化再通知 session-control。`0x10013b414` 会遍历 feature entries，对存在的 feature 数据调用其清理回调；`0x10004df7c`/`0x100050338` 释放识别对象、拒绝 scratch、CF 字符串/集合和转移缓冲。

因此“1D03 已成功发送”只证明原实现进入 state3/清理分支的局部条件；state3 允许同一个 session 再进入 `1D01`。本局部没有固定重试次数、重试间隔、总 deadline 或“必须新建 RFCOMM”的证据。`1D05` 与 `1D03` 也不同：取消并不是字段拒绝，不构造拒绝 TLV。

## 5. `1D05`：取消不是普通拒绝

原入口 `_iap2_identification_cancelIdentificationHandler@0x10013b28c` 记录“Identification cancelled by accessory”。只有当前 state 为1或3时才写 state4、构造并展示 accessory-not-supported 通知；通知和标识的 CF 引用在适用位置释放。state6 等其他状态不走这次 state4 转移。该函数不发送 `1D03`，也没有本函数内的重试；不能由释放通知对象推断它已清空识别 feature 或取消异步授权。

手机 `Bootstrap.kt` 当前将 `0x1d05` 放在 unconditional inbound 集合，收到后统一 `throw IOException("Accessory rejected")`；`SessionController` 把这个异常分类为 terminal，释放本次资源，不在同一 control link 上等待新的 `1D01`。这比原固件的“仅 state1/3 变4、无拒绝包”更粗；尤其在手机已认为识别 accepted 后收到迟到 `1D05`，手机会终止，而原 cancel handler 本身不会把 state6 改为4。这里是生产路径差异，不是建议把车机端或固件改掉。

## 6. `1D06`：原实现是 state6-only 的增量合并

原更新入口 `_iap2_identification_identificationInfoUpdateHandler@0x100050934` 首先要求 state==6；否则跳过处理。state6 时创建临时 info，`ForEach` 使用 `_iap2_identification_cbIdentificationInfoUpdateParams@0x100050458`：

| 更新参数 | 原局部行为 |
|---:|---|
| 0–5 | 读取 NUL 字符串，写入临时对象对应字段；之后只对非 NULL 字段替换旧值 |
| 6 | 记录“language updates no longer supported”，不写字段 |
| 其他 | 记录 unhandled paramID；回调本身返回0，但这不把未知字段变成初次 `1D01` 的成功证明 |

遍历成功后 `_iap2_identification_updateIdentificationInfo@0x100050744` 按字段指针**非NULL**逐项替换旧 CFString，再调用 `_acc_endpoint2_setAccessoryInfo`；没有 `1D02`、`1D03` 或重新认证。非NULL不等于字符串非空；本章未把空字符串或真实CF转换结果当已运行验证。该 helper 还包含 `+0x40` 的合并分支，但当前 `1D06` callback不生产该字段；不能据此声称 `1D06` 支持初次识别参数34/PPID。非NULL临时对象在正常处理尾部释放；该路径保留未出现在本次 update 中的旧字段，和“把更新当全新完整 IdentificationInfo”不同。

更新的失败边界也应保留：ForEach非零时跳过merge、记录后走临时结构清理；callback重复字段直接覆盖临时指针，不能照搬初次识别的重复释放策略。原handler在分配返回NULL后，日志分支仍汇合到读取临时对象`+0xe8`的指令；这一极端路径未执行、不宣称内存安全或必然导致实际崩溃。返回值末尾按“进入时state是否不等于6”生成，不能用返回0判定字段实际合并成功。

手机当前 `Bootstrap.kt` 的 `0x1d06` 分支与此不同：它调用初次识别使用的 `IapIdentifyInfo.parse(fields)`，强制要求参数6/7消息列表；0–5字符串则可缺省为 null。成功后整体替换 `identified` 和消息集合，并再次调用 `identificationAccepted`；失败只记录并丢弃。因此仅更新名字的合法形状会缺6/7而被丢掉；反过来带6/7的所谓更新会重写消息集合，而这不是原更新消费者的含义。已有 `identificationUpdateAfterAcceptanceIsAppliedWithoutRestartingTheSession` 测试在等待5703期间送的是完整初次识别形状；该专项审计只读测试，没有自行运行。主代理本轮重跑结果见 [64 — Identification deep review](64-identification-deep-review.md)，测试通过不证明测试预期就是正确的苹果行为，也不能证明局部更新或 runtime 交接后行为。另一个生产边界是：`negotiateRuntime` 在 transactions.ready 后可提前返回；`RuntimeIap` 的 `AirSession.message` 当前只处理 Now Playing 命令，Bluetooth 交接后的 `SessionController` 轮询也只特判5703，其余字段仅记录 unsupported。因此，协商完成后的真实 `1D06` 更新并没有一个已证的完整生产处理链。

## 7. 世代、发送失败与清理边界对照

### 原固件能证明的保护

- `1D01` handler 在发送/状态变化后才做 captured info 指针比较；这是局部 cleanup guard。
- rejection success/failure 对 `info+0x98/+0xa0` 的清除不同，说明发送结果影响所有权。
- `releaseIdentInfo` 会清理 CF/集合和 feature reject message；不能因此宣称异步 completion 已被取消。

### 手机当前生产路径能证明的保护

- `Bootstrap` 捕获 `link.generation` 与 `link.linkEpoch`，普通 `send`、poll 前后均检查；`RuntimeIap` 在协商后保存 authorized generation/epoch，发送和收包继续检查。
- `RuntimeIap.fail` 清空授权世代、进入 DEGRADED、关闭 link/input；`SessionController.attempt` 的 `finally` 关闭本轮 Resources。外层 `SessionController` 只对非 terminal 异常延迟重试：**接收** `1D03/1D05` 生成的 `Accessory rejected ...` 是 terminal，`TransportException(IDENTIFICATION_REJECTED)` 也为 terminal；不能泛称所有本地发送 `1D03` 都是 terminal。当前 missing-required 分支抛的是另一条普通 IOException，可能进入外层新 attempt；参数解析的 IllegalArgumentException 则为 terminal。无论哪种，Bootstrap 的 catch 都重抛，不留在同 link 等待修正后的 `1D01`。
- 当前 `1D01` 缺失 required 分支仍有一处 `link.sendRaw(IapWire.csmRaw(0x1d03, body))` 未传 `expectedGeneration`；后续异常会结束协商。其它 reject raw send 使用 expectedGeneration。该差异是可定位的手机实现问题，不是原固件语义。

### 不应误报为生产重连的代码

`PeerNegotiationController.fallbackAfterReconnect()` 和 `rejectedOnce()` 目前只有声明与测试调用；仓库没有主会话调用它们。因此它们是未接入的策略 helper，不能作为“已经实现重连回退/拒绝后过滤并重试”的证据。

## 8. 分支对照表：当前手机应如何读日志

| 观测 | 原分支的最小解释 | 当前手机生产路径的实际解释 | 仍缺证据 |
|---|---|---|---|
| `1D00` tx 后无 `1D01` | 对端未回、session/条件未满足或承载问题 | generation-guarded send 已提交；不等于车机收到 | seq/ack、同一 link 的对端状态 |
| `1D01` 含 unknown/callback fail | ForEach 非零，走授权后拒绝路径 | 当前代码可能只记录未注册 ID；完整 `IapIdentifyInfo.parse` 不复刻该拒绝分支 | 原平台授权最终结果、实机抓包 |
| `1D02` tx，未见 state6 后续 | 可能发送失败留 state2，或后续状态未观测 | 手机 `send` 返回只代表本地提交；控制器 ready 还要求 AA/ident | wire ACK、车机继续消息 |
| 本地 `1D03` tx 后再次 `1D01` | 原 state3 允许 | 手机发送拒绝后重抛：可能 terminal 或新 attempt，但不在原协商循环继续等待 | 若要兼容，需单独设计并验证，不从 helper 推断 |
| `1D05` | 原仅 state1/3→state4，非拒绝 TLV | 手机统一抛 terminal IOException | 收到时手机 Peer 状态、是否迟到 |
| state6 后局部 `1D06` | 原按字段指针非NULL增量合并，无 `1D02` | 手机按完整 parse；runtime/交接后暂无完整更新消费者 | 更新字段集合、下一条车机消息 |
| 新 link / link epoch | 原本轮证据未发现显式 generation token | 手机 generation+epoch guard；仍有 missing-required raw send 漏点 | 原跨连接 callback 取消和内核队列语义 |

## 9. 本章收口

已关闭的局部事实：原 `1D00`/`1D01`/授权/`1D02`/`1D03` 分支条件；unknown/ForEach 非零的拒绝方向；`1D03` 后 state3 再入 `1D01` 的可能性；`1D05` state1/3-only 取消；state6-only、指针非NULL逐字段合并的 `1D06`；feature/对象/reject scratch 清理入口；以及当前手机实际 generation/epoch、terminal reject 与未接入 helper 的路径。整份函数切片字节核对不等于每个依赖和回调语义已关闭。

仍 OPEN：平台授权服务实际 completion/取消与线程生命周期、全部 feature cleanup 语义、原固件跨 link 的旧回调隔离、真实重复 `1D01`/`1D06` 抓包、手机局部更新和拒绝后同 link 重试的兼容性。本文不宣称“从蓝牙到投屏已跑通”，也不把静态字节验证当作实车 PASS。
