# 09 外接客户端如何打开 RFCOMM 通道

**适用对象**：**设备侧客户端**（模拟 iPhone），通过蓝牙经典 RFCOMM 连到车机；主路径 §9.2–§9.6 就是
「查车机的 SDP 记录 → 主动连」。车机侧监听方见 §9.7。
它拿不到 iOS 进程内的 XPC/fd 接口，因此 `spec/08` 的 `kCBMsgArgSocket`、`socketpair`、`kCBMsgArgMTU`
**一律不适用**。推荐使用操作系统 RFCOMM 字节流 socket：SABM/PN/MSC、信用、FCS 与 DISC 由系统栈处理。本章这些帧级条款只适用于自研原始 RFCOMM 栈；不得把控制帧写入已打开的 socket 作为应用载荷。

**两种角色都成立**：主路径是设备侧客户端**主动连出去**（§9.2–§9.6，发起方）；可选角色是**车机侧监听**
（§9.7，等 iPhone 连进来）。同一设备可以只做其中一种，也可以同时具备两种能力（R-9.33）。

**不适用范围**：本章不定义 iAP2 报文格式、SYN 语义与 Detect 内容（属 iAP2 侧）；
RFCOMM 只保证"打开一条字节流通道"，其余由上层决定（见 §9.5 的对齐说明）。

状态标记：`CONFIRMED` = 固件字节/汇编支撑；`INFERRED` = 由上条推出或**跨构建运行时三方一致**的形态；
`OPEN` = 证据不足，已登记 manifest。

## 9.1 五步总览

```
A. 主动连（发起方，§9.2–§9.6）
   1. SDP：查对端服务记录 → 取 RFCOMM 通道号（不要硬编码）
   2. 打开：平台 RFCOMM connect（栈负责 L2CAP、SABM/UA、PN/MSC、信用）
   3. 读写：字节流；参考 iOS 队列可按 ≤ min(N1,2570) 切块，外部客户端以自身 API 上限和 N1 为准；不假设帧边界
   4. 首字节：默认等对方先发；超时后按 iAP2 侧规则主动 detect
   5. 关闭/重连：DISC↔UA/DM；重连要重新走 SDP

B. 监听（监听方，§9.7）
   1. 注册通道 → 把通道号写进 SDP（或按部署约定固定）
   2. 平台 accept（栈负责各控制帧及协商）
   3. 读写：与 A 完全相同的字节流规则
   4. 首字节：同样默认等；对端先发就正常收，超时按 iAP2 侧规则
   5. 关闭：收到 DISC 回 UA 并释放 DLCI，但**保留**监听
```

## 9.2 第 1 步：SDP 查服务记录

**R-9.1**（`CONFIRMED`，运行时三构建）设备侧客户端**必须**优先按**车机侧接收端**的服务类 UUID
`00000000-deca-fade-deca-deafdecacaff`（Wireless iAP Sink）做 `ServiceSearchAttribute`
查询，属性集至少取 `{0x0000, 0x0001, 0x0004, 0x0100}`（句柄 / 类 / 协议描述符 / 名字）。
对端若是**网关侧**（例如再连一台 iPhone），改用网关 UUID `00000000-deca-fade-deca-deafdecacafe`。

> **UUID 缩写约定**（全文统一，规范分组一律 8-4-4-4-12）：
> `…caff` = `00000000-deca-fade-deca-deafdecacaff`（接收端 / 车机侧）；
> `…cafe` = `00000000-deca-fade-deca-deafdecacafe`（网关侧 / 设备侧）。

**R-9.2**（`INFERRED`）SPP UUID `0x1101` 本身不能证明服务承载 iAP2。只有设备专属 profile 或已验证的服务记录关联明确指定时才可选用，不能仅凭名字或 WiAP 查询失败就自动连接任意 SPP 服务。

**R-9.3**（`CONFIRMED`）识别服务**只能**靠 UUID，**不得**靠 ServiceName 字符串：
车机侧同一条 `…caff` 记录的 ServiceName 在三次抓包里分别是 `RFCOMM-SPP`、`iAP2`、未返回。
按名字匹配会在真实设备上失配。

**R-9.4**（`CONFIRMED`）通道号**必须**从 `ProtocolDescriptorList`（0x0004）里取：
`[L2CAP(0x0100)] + [RFCOMM(0x0003), 通道号]`，通道号是**单字节**参数。
**不得**把通道号写死：同一服务 UUID 在抓包里出现过 **4 / 1 / 5** 三个值。

**R-9.5**（`INFERRED`）查不到匹配记录/有效通道时返回 `NO_SDP_RECORD`；不能据此断言设备完全不支持 iAP2。固定通道仅限明确配置并验证过的目标 profile，不得盲扫候选通道或跨设备套用上次通道。

**R-9.6**（`INFERRED`）SDP 查询**必须**有超时（建议 5 s；这是 SDP 层超时，**不属于** §9.5 的 `T_*` 三件套）与最多 2 次重试；
结果**可以**缓存（键 = 设备地址 + 服务 UUID），但**必须**带失效条件
（换设备、连接失败、用户手动清除），不得跨设备复用。

> 车机侧的反向证据（供实现方理解"为什么不能写死"）：车机自己用同一条 `…caff` 记录向 iPhone
> 暴露 iAP2 通道，三次抓包通道号 4 / 1 / 5，属性集最小只有 `{0x0000,0x0001,0x0004}`。
> 详见 `runtime/observations/sdp-records-iap2.md`。

### 9.2.1 两代服务：legacy 与 v2

**R-9.6a**（`CONFIRMED`）**必须**同时支持两代服务 UUID，且**每代各自从自己的 SDP 记录取通道号**，**不得**假设两代共用同一通道：

| 代 | 网关 UUID | 接收端 UUID | 观测到的通道 |
|---|---|---|---|
| legacy | `00000000-deca-fade-deca-deafdecacafe`（网关 / 设备侧） | `00000000-deca-fade-deca-deafdecacaff`（接收端 / 车机侧） | 车机侧 **4/1/5**；iPhone 侧 **1**（21G93） |
| v2 | `08ed27c3-1d19-415f-86f2-22a2106a0a77`（网关） | `08ed27c3-1d19-415f-86f2-22a2106a0a78`（接收端） | **未观测到**（抓包里 v2 UUID 出现 0 次） |

固件在选择用哪一代时打的是 `New WiAP UUID` / `Old WiAP UUID` 两条日志，随后把**对端记录里的通道号**连同
`N1=1007`、信用窗口 `15105` 一起交给连接函数（`0x1007a3ba4` → `0x1003c2b00(…, channel, 0x3ef, 0x3b01, …)`）。
v2 的实际通道号属 `OPEN-CLI-3`：若对端只暴露 v2 记录且通道未知，按 R-9.5 报告缺少有效服务记录；不能猜通道。

## 9.3 第 2 步：打开通道并协商参数

**R-9.7**（`CONFIRMED`，栈级）新复用器先建立 L2CAP PSM `0x0003` 和 DLCI 0 SABM/UA，再按状态机打开目标数据 DLCI、完成所需 PN/MSC。不能把 SDP 服务通道号当作 L2CAP PSM。SABM 的线上控制为 `0x3F`，UA 为 `0x73`；DM `0x1F` 表示拒绝。等待须有界；平台 socket 调用者使用 connect/错误返回，不自行注入这些帧。PN 与数据 DLCI SABM 的完整跨状态先后顺序尚未闭合，图示不能当作唯一允许顺序。

**R-9.8**（`CONFIRMED`）DLCI = `(D | (channel << 1)) ^ 1`，D 是复用器角色。新出向复用器在 `0x1003c1dd4`–`0x1003c1dd8` 写 D=1，因此本地主动建立复用器连接远端服务用偶数 DLCI。复用现有复用器须沿用角色；地址 = `1 | (CR << 1) | (DLCI << 2)`，CR 按 R-4.14，不是直接 OR 数字 1 代替 bit1。

**R-9.9**（`CONFIRMED`，栈级）信用流控协商使用 PN 命令 `0x83`、响应 `0x81`，8 字节载荷按 R-4.28。WiAP 调用参数 N1=1007、内部窗口=15105 得到内部容量 15，不能把 15 当作 PN 的 3 位初始信用。发送初始信用必须在 0–7，按接收容量配置；接收器取 `value & 7`，不是饱和到 7。帧类型/信用流控协商不能随意填“缺省”后忽略；完整发送分支仍需按目标 profile 验证。

**R-9.10**（`CONFIRMED`）PN 的 DLCI 字节用裸 DLCI（`DLCI & 0x3F`），MSC/RPN 用地址字段（`(DLCI<<2)|3`）。按各自布局解析，不做双编码猜测。接收 PN 后生效 N1 取 `min(本地, 对端)`，未知 DLCI 不得重映射到另一通道。

**R-9.11**（`CONFIRMED`，栈级）MSC 命令 `0xE3`、响应 `0xE1`，地址字节为 `(DLCI<<2)|3`。信号由调用者传入；无附加信号字节时组帧器执行 `signal|1`，可选第三字节为 `(extra<<4)|3`。样本中 `0x8D` 是观测值，不是所有固件路径恒定值；不能把 bit0 当 RTC。信号位语义与实际流控行为应按 RFCOMM profile 实现，不能只保存后忽略。

**R-9.12**（`INFERRED`）打开阶段**必须**区分三类失败并各自上报：
`NO_SDP_RECORD`（查不到）、`REJECTED`（SABM 收到 DM）、`TIMEOUT`（UA 未到）；
三者的重连策略不同（见 R-9.23），不得合并成一个"连接失败"。

## 9.4 第 3 步：字节流读写

**R-9.13**（`CONFIRMED`）通道打开后，客户端看到的是**字节流**：RFCOMM 不向客户端暴露帧边界
（与 `spec/08` R-8.9/R-8.10 同一结论，本章从客户端视角复述）。

**R-9.14**（`INFERRED`）若复刻本固件的写队列，适配层可采用 ≤ `min(N1, 2570)` 的保守写块；
`2570` 是该 iOS 内部路径的缓冲上限，不是 RFCOMM 或所有平台 `write()` API 的通用上限。外部客户端必须以实际 API/对端 PN 协商为准，并自行处理部分写；RFCOMM 不替上层重组应用消息。

**R-9.15**（`CONFIRMED`）发送**必须**串行：一块完成再提交下一块，并等待完成事件
（`spec/05` R-5.20）；**部分写**按 `spec/05` R-5.22 处理（只消费前 k 字节，余下重算）。

**R-9.16**（`INFERRED`）接收**必须**用"读多少处理多少"的循环，**不得**假设一次 `read` 等于一帧或一报文；
上层需要按报文自身长度字段攒包（iAP2 自带长度与可靠性；本层不重传，见 `spec/08` R-8.24）。

## 9.5 第 4 步：打开后第一个字节的时序

**R-9.17**（跨层约定，`INFERRED`）默认策略是**等**：通道打开后客户端**不**立即发送任何字节，
先等对端的第一条 iAP2 包（`0xFF 0x5A` 开头的 SYN 或等价起始包）；等待窗口是
**`T_first_byte` = 2 s**（与 control docset `09-device-side-startup.md` §8.8 的定时器表同一组值），
收到字节只代表有输入，必须继续重组并校验 Detect/SYN/SYNACK/ACK；在链路 Connected 前不得发送控制会话业务。

**R-9.18**（跨层约定，`INFERRED`）**回退策略**：`T_first_byte` 超时且通道仍健康时，客户端**可以**主动发送
iAP2 侧的 Detect/起始包（具体字节与语义由 iAP2 侧定义：link 侧是 `FF 55 02 00 EE 10`，
抓包里可见的起始字节是 `FF 5A`），然后等 **`T_detect` = 5 s** 收 SYN；仍无应答**必须**归类为
`NO_SYN` 并断开重连。整个「RFCOMM 打开 → 进入 Connected」不得超过 **`T_link` = 30 s**。

> **定时器分层（唯一来源在 control docset）**：`T_first_byte` = 2 s、`T_detect` = 5 s、`T_link` = 30 s；
> 三个值都是 `[建议]`，**不是固件常量**。定义与引用关系见 `iap2_control_session/spec/09-device-side-startup.md` §8.8；
> link `spec/09` §9.10 的「`Detect` 等待对端 SYN」行也取同一值（5 s）。

**R-9.19**（`CONFIRMED`）**RFCOMM 层不规定谁先说**：SABM/UA 完成后通道即双向可用，
"谁发第一个字节"是 iAP2 链路层的规则（本 docset 不定义 SYN/Detect 的内容与语义）。

> **与 link 侧对齐**：iAP2 侧规则为"默认等、可 fallback 主动"（本文 R-9.17/R-9.18 与之一致）。
> **运行时旁证**：三次抓包里第一条 UIH 载荷都是 `FF 5A`，且都由**车机（配件侧）先发**
> （`runtime/observations/sdp-records-iap2.md` §4）——说明"先开口"在实际互通中常见，
> 但本规范不把它上升为强制，以免与 link 侧规则冲突。

## 9.6 第 5 步：关闭与重连

**R-9.20**（`CONFIRMED`）正常关闭**必须**发 **DISC**（基值 `0x43`，P/F=1 时线上 `0x53`）并等待 UA 或 DM；
超时后直接释放本地 DLCI 并上报断开超时（`spec/06` R-6.1–R-6.3）。

**R-9.21**（`CONFIRMED`）收到对端 **DISC** 时**必须**回 **UA** 并按状态机释放资源（`spec/06` R-6.6）；
重复 DISC 幂等。

**R-9.22**（`INFERRED`）平台 RFCOMM socket 使用平台的 shutdown/close；由栈执行协议关闭。自研原始栈则按 DISC→UA/超时流程回收 DLCI，再释放底层资源。两种 API 层次不能混用，尤其不能往 socket 写 DISC 字节。

**R-9.23**（`CONFIRMED`）重连节奏**必须**是"固定等待 + 硬上限"：参考实现为 5 次尝试、
页扫描 60 s、退避 300 s、看门狗 8/16 s（`spec/06` R-6.22/R-6.23）；
**不得**假设存在指数退避（`spec/06` R-6.24）。`REJECTED` 与 `NO_SDP_RECORD` **不得**自动高频重试。

**R-9.24**（`CONFIRMED`）每次重连**必须**重新做 SDP（或使用带失效条件的缓存）取通道号，
**不得**沿用上次的通道号假设（`spec/06` R-6.20；实测 4/1/5）。

## 9.7 监听方（车机侧/可选角色）：等对端连进来

**R-9.25**（`CONFIRMED`）监听方**必须**先在本地注册 RFCOMM 服务并拿到通道号
（`0x1002f1300` 注册入口、`0x1003c2314` 按通道号查表），再把该通道号写进自己的 SDP 记录
（UUID `…caff` = `00000000-deca-fade-deca-deafdecacaff`，见 §9.2 的车机侧样本）；
否则对端只能靠**固定通道/配置**（R-9.5 的反向情形）。

**R-9.26**（`CONFIRMED`）收到 SABM **必须**逐项校验：EA=1、P/F=1、C/R 表示"发起方命令"、地址 `< 0xF8`、
`DLCI ≠ 1`、会话就绪；EA/P/F/C/R 失败静默丢弃，状态/地址拒绝分支可回 DM（`0x1003c5c70` 的五道拒收，`spec/04`）。

**R-9.27**（`CONFIRMED`）校验通过**必须**回 **UA**（`0x63`），并把 DLCI 绑定到查表得到的服务实例；
会话未就绪或通道号未注册时**必须**回 **DM**（`0x0F`），**不得**回 UA 后再断开。

**R-9.28**（`CONFIRMED`）收到 **PN**（`0x83`）**必须**回 **PN 响应**（`0x81`）：生效 N1 取
`min(本端配置, 对端声明)`；信用计数按对端声明值设置，本端上限**必须**在实现文档里写明
（参考实现只认低 3 位，即 ≤ 7，`0x1003c7678`；接收值按 `value & 7` 处理，不是饱和）。
PN 的 DLCI 按 `spec/04` R-4.29a 的裸 DLCI 布局解析。

**R-9.29**（`CONFIRMED`）收到 **MSC**（`0xE1`/`0xE3`）**必须**校验数据区（`(DLCI<<2)|3` + 信号字节），
数据区 < 2 字节时**必须**丢弃并计数（不得崩溃，`spec/04` R-4.31）；RTC/FC 信号**必须**被记录，
但**不得**因取值异常断链（`0x8D` 只是现有样本值）。

**R-9.30**（`CONFIRMED`）收到 **DISC**（`0x43`）**必须**回 **UA** 并按状态机释放该 DLCI（`spec/06` R-6.6），
但**必须保留**监听本身（不得注销服务、不得关闭 L2CAP 监听通道）。

**R-9.31**（`CONFIRMED`）监听方**必须**接受"任意时刻到来"的连接：会话忙、DLCI 用尽、通道号未注册时
**必须**用 DM 拒绝（`0x1003c5c70`），**不得**半开（回了 UA 却不投递数据）。

**R-9.32**（`INFERRED`）监听方**必须**限制并发（每会话 DLCI 数、每设备通道数）并写进配置；
超限时用 DM 拒绝并记录诊断计数。

**R-9.33**（`INFERRED`）**同一设备可以同时是发起方与监听方**，但**同一对端地址同一时刻只应有一条
iAP2 会话**：两条会话会抢同一个上层服务实例。角色选择按配置（`listen` / `connect` / `auto`）；
`auto` 时**建议**先监听一段可配置窗口（默认 5 s；与 §9.5 的 `T_*` 三件套无关），超时后再主动连。

**R-9.34**（`INFERRED`）监听方的字节流规则与发起方相同；若采用本固件参考队列，可按 `≤ min(N1,2570)` 切块，但该 2570 不得当作所有平台 API 的硬上限。两种角色都必须串行发送、不假设帧边界（R-9.13–R-9.16）。

**R-9.35**（`CONFIRMED`）监听方**必须**对每个 DLCI 维护独立的状态机与信用计数：
同一会话里多个 DLCI 的 PN/MSC/信用**不得**互相污染（`0x1003c5c70` 按 DLCI 查表）。

> 运行时旁证：三次抓包里车机侧都在 SDP 里暴露 `…caff` 记录（通道 4/1/5），
> 并且是**车机（配件侧）先发 SYN**（`runtime/observations/sdp-records-iap2.md` §2/§4）——
> 说明"监听 + 先开口"在真实互通中很常见，但 R-9.17/R-9.18 仍按 link 侧规则执行。

## 9.8 最小伪代码（平台 RFCOMM 字节流 API）

下面是事件循环骨架，不是已验证可直接运行的客户端；`link` 必须实现 link docset 的解析、校验、状态机及重传。socket 可写不等于链路 Connected。

```text
record = sdp_find(peer, configured_sink_uuid)  // 默认 legacy …caff
if no valid record/channel: report NO_SDP_RECORD; stop
socket = platform_rfcomm_connect(peer, record.channel, connect_deadline)
link = DeviceSideLink(profile, T_first_byte=2s, T_detect=5s, T_link=30s)
link.transport_open(now)                     // 默认等待；定时器始终运行
tx_queue = empty

while not cancelled and not link.failed:
    events = poll(socket, readable=true, writable=tx_queue.nonempty,
                  deadline=link.next_deadline())
    if events.readable:
        bytes = socket.read()
        if EOF/error: break
        link.feed(bytes, now)                // 可分片/合并；必须验证完整握手
    link.tick(now)                           // 首包/Detect/握手/重传超时
    tx_queue.append(link.take_output())      // 仅 link 允许的握手或业务输出
    if link.connected:
        control.advance_gated_startup(link)  // 识别、认证、能力门控
    if events.writable and tx_queue.nonempty:
        n = socket.write(tx_queue.front)
        if would_block: continue
        if error: break
        tx_queue.consume(n)                  // 只移除实际成功写出的字节

link.transport_closed()
platform_shutdown_and_close(socket)         // 不写 PN/MSC/DISC 原始字节
```

监听模式使用对应 profile 的 SDP UUID 与平台 listen/accept，再对接受到的 socket 运行同一循环。仿 iPhone 若支持入向连接，应注册设备侧 gateway …cafe；§9.7 的 …caff 是车机角色，不能照抄。

## 9.9 一致性判据

1. 让对端（车机）不返回 SDP 记录时，客户端报 `NO_SDP_RECORD` 而不是"连接超时"（R-9.5/R-9.12）。
2. 把通道号从 1 改到 5 仍能连上（R-9.4：通道号来自 SDP）。
3. 对端拒绝 SABM（回 DM）时，客户端在有限次数内停止并报 `REJECTED`（R-9.7/R-9.23）。
4. PN 后生效 N1 = 双方较小值；信用计数 = 对端声明值（R-9.10）。
5. 写 3000 字节：按实际平台 API 限制串行发送，正确处理部分写（R-9.14/R-9.15）。
6. 通道打开后客户端不发任何字节，仍能收到对端 SYN 并完成初始化（R-9.17）。
7. 等待窗口超时后发 Detect，收到并验证应答后继续握手，Connected 后才进入业务收发；两次超时后断开（R-9.18）。
8. 关闭顺序正确：对端看到的是 DISC/UA 而不是链路异常（R-9.22）。
9. 重连时重新做 SDP，日志里能看到新的通道号（R-9.24）。
10. 监听模式：对端连入 → 收到 SABM → 回 UA → PN 应答 → 数据可用（R-9.25–R-9.28）。
11. 未注册的通道号收到 SABM → 回 DM，且不产生半开会话（R-9.27/R-9.31）。
12. 收到 DISC → 回 UA → DLCI 释放，**监听仍在**（R-9.30）。

## 9.10 证据边界（本章哪些结论是固件、哪些不是）

| 结论 | 等级 | 依据 |
|---|---|---|
| 主动连（A 路径）的每一步：取通道号、建链、PN、MSC、发送队列、2570 | `CONFIRMED` | `0x1007a3ba4`（引用点 `0x1007a3d34`）、`0x1003c2b00`、`0x1003c7644` 系、`0x1003c3c20`、`0x1000eb4e8` |
| 监听（B 路径）的 RFCOMM 机构：服务注册、按通道查表、入向 SABM 五道拒收、DISC→UA | `CONFIRMED` | `0x1002f1300`、`0x1003c2314`、`0x1003c5c70`、`0x1003c59a0` |
| "iPhone 为 iAP2 注册 SDP 记录并监听某通道" | `INFERRED` | 只有字符串（`0x100b46435`/`0x100b6eb82`，引用点 `0x1008f5fb8`/`0x100905330` **非抽样**）+ 运行时记录 `…cafe` |
| 记录里的通道由已注册的 RFCOMM 服务端承载 | `OPEN`（`OPEN-CLI-2`） | 无直接证据 |
| 通道号 4/1/5、名字 `RFCOMM-SPP`/`iAP2`、首字节 `FF 5A` 由配件先发 | 运行时（跨构建，非 24A446） | `runtime/observations/sdp-records-iap2.md` |
| 两代 UUID 与「各取自己记录的通道」 | `CONFIRMED` | `0x1007a3ba4`（`New/Old WiAP UUID` 日志 + `0x3ef`/`0x3b01` 实参）、`analysis/01` C5/C5.1 |
| v2 的实际通道号 | `OPEN`（`OPEN-CLI-3`） | 抓包中 v2 UUID 出现 0 次 |

> 完整对照见 `analysis/07` C9；复现命令见该节。

## 附录 A：本章依据

| 编号 | 结论 | 依据 |
|---|---|---|
| X9-01 | iPhone 用 `…cafe` + 名字 `Wireless iAP` 暴露 iAP2 记录 | `23G90` 抓包 TX 响应；`runtime/observations/sdp-records-iap2.md` §3 |
| X9-02 | 21G93 样本中该记录 PDL 通道 = 1，且同时存在 SPP `0x1101` 记录 | 同上 §3 |
| X9-03 | 车机侧同 UUID 记录通道 4/1/5、名字 `RFCOMM-SPP`/`iAP2`/空 | 同上 §2 |
| X9-04 | 首个 UIH 载荷均为 `FF 5A` 且由车机（配件侧）先发 | 同上 §4 |
| X9-05 | 打开通道：SABM 校验条件（EA/P/F/C/R/地址/DLCI≠1/会话就绪） | `0x1003c5c70`（`spec/04` R-4.x） |
| X9-06 | PN 数据区布局与 `&7` 信用上限 | `0x1003c7644`…`0x1003c7678`（`spec/04` L-14） |
| X9-07 | MSC 数据区布局；样本信号 `0x8D`，非全局固定 | `analysis/05` C6、`spec/04` R-4.30 |
| X9-08 | 单块上限 2570 | `0x1000eb4e8` C 行 72、87–90（`spec/05` T-08） |
| X9-09 | N1 上报语义 = 最大信息字段 | `0x10040c934` C 行 62–83、`spec/08` R-8.13 |
| X9-10 | 重连节奏：5 次 / 60 s / 300 s / 8–16 s | `analysis/06` C8、`spec/06` R-6.22 |
| X9-11 | 监听方注册入口与按通道号查表 | `0x1002f1300`、`0x1003c2314`（`spec/02`） |
| X9-12 | 入向 SABM 五道拒收与 DM | `0x1003c5c70`（`spec/04`） |
| X9-13 | PN 应答与信用上限 `& 7` | `0x1003c7678`（`spec/04` L-14） |
| X9-14 | 车机侧监听并暴露 `…caff`（通道 4/1/5） | `runtime/observations/sdp-records-iap2.md` §2 |
