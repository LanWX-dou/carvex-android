# spec/06 — 挂起、恢复与断开

本章分开固件事实与本地安全策略；内部状态名、事件号和参考模型都不是线上字段。

## 6.1 三类事件

`R-6.1` [本地安全策略] MUST 区分链路挂起/恢复、平台休眠/唤醒和断开。
挂起不自动证明订阅仍有效；平台休眠不保证链路状态不变。唤醒先检查连接与会话，再决定恢复或重连。
依据：A07.1、A07.4、A07.5、A12.3。

## 6.2 挂起

`R-6.2` [24A446事实] 已核设备主动挂起路径构造 SUS（控制字节 `0x08`），无载荷；
MUST NOT 编码成 16 位业务消息，头和校验沿用链路 docset。
依据：A07.1、A12.1。

`R-6.3` [本地安全策略] 接受挂起后 MUST 关闭业务发送门并暂停业务定时器，
但不能停掉链路 ACK、重传、恢复任务。可缓存会话/订阅/组件，但缓存不等于恢复授权；
积压消息按过期时间和语义丢弃/合并，不自动重放。
依据：A07.3、A12.3。

`R-6.4` [本地安全策略] SHOULD 串行化生命周期事件并检查状态；FSM 是一种实现方式，不是唯一架构。
固件 HandleSuspend/Resume 投递事件 `0x1b/0x1c`，不是旧文档的事件 2。
依据：A07.3、A12.2。

## 6.3 恢复

`R-6.5` [24A446事实] 已核设备主动恢复路径构造 ACK（控制字节 `0x40`），无载荷。
以 `FF 5A` 为偏移 0：`hdr[5]=link[0xBE]`、`hdr[6]=link[0xBC]`、`hdr[7]=0`。
`hdr[6]` 的完整语义仍见 `link/spec/02` 的 OPEN-FRAME-6；本节只描述恢复路径的实际构造，不把它推广到所有帧。
MUST NOT 把内部确认号写进会话号位置。收到任意 ACK 不等于恢复完成；
对端恢复识别和完整时序仍见 `OPEN-LIFE-2`。
依据：A07.2、A12.1。

`R-6.6` [本地安全策略] MUST 重查当前会话与该业务域有效性。
`0x5000` 是车机→设备订阅，设备 MUST NOT 为恢复订阅自行发送它。
若已证明原订阅仍有效，可按原订阅发 `0x5001`；否则等待车机重新订阅。
没有证据要求所有恢复都必须重注册 HID 或重做认证。
依据：A04.1、A04.5、A12.3。

## 6.4 系统休眠

`R-6.7` [本地安全策略] 若使用平台通知，注册/注销 MUST 配对，销毁前撤销通知，
防止晚到回调访问已释放资源。平台唤醒不等于链路恢复；不强制照搬 iOS endpoint 架构。
依据：A07.4、A08.4、A12.3。

## 6.5 断开

`R-6.8` [本地安全策略] 断开后 MUST 关闭业务门，停止更新并使当前会话的队列、
订阅和组件绑定失效。可保留无发送授权的应用缓存，但不可直接复用于新连接。
依据：A07.5、A08.3、A12.3。

`R-6.9` [本地安全策略] MUST 覆盖所有已启用域的清理，可由统一入口协调或逐域回调。
先阻止新工作、取消或排空旧回调，再释放其资源；不能从固件逐域回调推出“禁止总入口”。
依据：A07.5、A08.3、A12.3。

`R-6.10` [证据边界] `OPEN-LIFE-3` 的历史关闭仅涵盖 SUS/ACK 包型和无载荷，
不涵盖订阅保留、重连顺序或真实车机观察。
依据：A09.1、A11.5、A12.1、A12.3。

## 6.6 本地参考状态机

`R-6.11` [本地安全策略] 默认 DISCONNECTED；链路建立进入 NEGOTIATING。
真实会话层确认认证、识别和该业务域门均通过后才进入 ACTIVE。状态名/数量不是协议要求。
feature_ready 包含方向能力、特性可用性及适用消息的订阅/组件条件，不要求实现所有 CarPlay 特性。
实际发送仍须逐消息检查。
依据：A06.1、A06.2、A06.3、A12.3。

`R-6.12` [本地安全策略] 下表是参考代码的事件边，不是固件迁移全集。
READY 额外检查三项显式布尔门；每个事件检查 epoch。拒绝事件不得改变状态。

| 当前状态 | 事件 | 新状态 | 说明 |
|---|---|---|---|
| `DISCONNECTED` | `RECONNECT` | `RECONNECTING` | 新连接代际 |
| `RECONNECTING` | `ESTABLISHED` | `NEGOTIATING` | 仅链路就绪 |
| `NEGOTIATING` | `READY` | `ACTIVE` | 三项门通过 |
| `ACTIVE` | `SUSPEND` | `SUSPENDED` | 关闭业务，作废旧回调票据 |
| `SUSPENDED` | `RESUME` | `RESUMED` | 仍不放行业务 |
| `RESUMED` | `READY` | `ACTIVE` | 当前有效性检查通过 |
| `RESUMED` | `SUSPEND` | `SUSPENDED` | 再次挂起 |
| `SUSPENDED` | `SUSPEND` | `SUSPENDED` | 幂等 |
| `RECONNECTING` | `RECONNECT` | `RECONNECTING` | 幂等，不启动第二条连接 |
| `DISCONNECTED` | `DETACH` | `DISCONNECTED` | 幂等 |
| `RECONNECTING` | `DETACH` | `DISCONNECTED` | 建链中断开 |
| `NEGOTIATING` | `DETACH` | `DISCONNECTED` | 握手中断开 |
| `ACTIVE` | `DETACH` | `DISCONNECTED` | 业务中断开 |
| `SUSPENDED` | `DETACH` | `DISCONNECTED` | 挂起中断开 |
| `RESUMED` | `DETACH` | `DISCONNECTED` | 检查中断开 |
| `RECONNECTING` | `FAIL` | `DISCONNECTED` | 建链失败 |
| `NEGOTIATING` | `FAIL` | `DISCONNECTED` | 握手失败 |
| `ACTIVE` | `FAIL` | `DISCONNECTED` | 会话门失效时的本地停止策略 |
| `SUSPENDED` | `FAIL` | `DISCONNECTED` | 会话失效 |
| `RESUMED` | `FAIL` | `DISCONNECTED` | 无法恢复 |
| `RECONNECTING` | `CANCEL` | `DISCONNECTED` | 取消连接 |
| `NEGOTIATING` | `CANCEL` | `DISCONNECTED` | 取消握手 |

依据：A12.3（本地设计，非固件事件表）。

`R-6.13` [本地安全策略] SUSPENDED/RESUMED/NEGOTIATING 均 MUST 关闭业务门。
RESUME 本身不重启业务定时器，也不产生订阅或 HID 注册消息。
依据：A12.3。

`R-6.14` [本地安全策略] 新连接、有效断开、新挂起周期推进本地 epoch；
回调 MUST 携带启动工作时取得的票据，旧票据拒绝且无副作用。
epoch 不是线上序号，也不替代任务取消与资源释放；真实实现需串行化检查与提交以防竞态。
依据：A12.3。

`R-6.15` [本地安全策略] READY 必须来自实际门控结果，不能由超时、任意 ACK 或
直接设置布尔变量来跳过认证。挂起后可确认原会话仍有效；断开重连需按协商 profile 重新推进，
不能复用旧完成回调。
依据：A06.1、A12.3。

`R-6.16` [文档维护] 本地迁移表 MUST 与代码一致，且 C14 MUST 执行行为测试：
初始关闭、链路就绪/恢复未放行、缺任一 READY 门、旧 epoch、失败/取消/断开。
合成测试不证明真实认证或互通。
依据：A12.3。
