# 交给 iAP2 side 的事实清单（蓝牙侧单方面结论）

用途：link 侧可以直接把"事实"列写成自己的 `R-1.x`，**不需要**再回推 RFCOMM。
本清单**只陈述蓝牙侧事实**，不含任何 iAP2 条款；标「待对方确认」的必须由 link 侧自证后才能成为条款。

状态：`CONFIRMED` = 固件字节/汇编直接支撑；`INFERRED` = 由上条 + 结构约束推出；`OPEN` = 证据不足。

| 编号 | 事实（一句话） | 证据 | 状态 | 待对方确认 |
|---|---|---|---|---|
| F-01 | 进程内客户端收到的是**逐帧回调** `(uint16 dlci, uint8* data, uint32 len)`，每收一个通过校验的 UIH 帧调用一次 | `0x1003c59a0` C 行 348–349 | `CONFIRMED` | — |
| F-02 | 跨进程客户端**只能**用 fd：回调是进程内函数指针，无法跨进程传递 | 同上（直接 `call` 无序列化）+ `0x10040c934` | `CONFIRMED` | — |
| F-03 | fd 以 XPC 键 **`kCBMsgArgSocket`** 随"通道已连接"消息交付，同消息还带 `kCBMsgArgMTU`/`kCBMsgArgRFCOMMChannelID`/`kCBMsgArgIsIncoming`/`kCBMsgArgServiceUUID`/`kCBMsgArgDeviceUUID` | `0x10040c934` C 行 62–83 | `CONFIRMED` | — |
| F-04 | 该 fd 是 `socketpair` 的一端，另一端由协议栈用于双向中继（与 `os_channel` 绑定） | 串表 `0x100acbb3d`（socket pair）、`0x100acbfa5`（os_channel 绑定）、`0x100acc42f`/`0x100acc74f`（双向中继） | `CONFIRMED` | — |
| F-05 | fd 是**字节流**：没有每帧长度前缀、没有控制消息、没有 `MSG_EOR`；`read()` 的切分与 RFCOMM 帧边界无对应关系 | 由 F-04 直接推出；`analysis/07` C2/C8 | `INFERRED`（强） | 是否接受"无帧边界"，由 link 侧确认 |
| F-06 | 回调通路的 `data` 指针**仅在回调执行期间有效**，需要保留必须立即拷贝（调用后槽位即被 `advance_slot` 归还） | `0x1000eb4e8` C 行 406–413 | `INFERRED` | — |
| F-07 | 同一 DLCI 上回调**串行且保序**：单循环 取槽→投递→推进，无并发回调；回调内不得阻塞 | `0x1000eb4e8` C 行 229–413 | `INFERRED` | — |
| F-08 | `kCBMsgArgMTU` 的语义是 **N1（最大信息字段长度）**，不是 L2CAP MTU；无线 iAP 实测 **1007** | `0x10040c934` C 行 62–83；`0x1003c2b00`（N1 为连接参数） | `CONFIRMED` | — |
| F-09 | 单次发送/接收块上限 = `min(N1, 2570)`；**超过必须由上层分块**，本层不替上层拆包 | `0x1000eb4e8` C 行 72、87–90 | `CONFIRMED` | — |
| F-10 | 发送**串行排队**，每块产生完成事件 `(DLCI, 块标识, 状态)`；部分写=只消费前 k 字节，余下重新按 N1 分块 | `0x1003c3c20`；`spec/05` R-5.20–R-5.22 | `CONFIRMED` | — |
| F-11 | 本层**不重组、不重传、不排序、不确认**；长度不符的帧被**静默整帧丢弃**，不通知是哪一帧 | `0x1003c59a0` C 行 187（精确长度校验）；`spec/05` R-5.24/R-5.25 | `CONFIRMED` | **已关闭**：link 侧确认 iAP2 自带 **16 位长度 + 8 位序号 + ACK/重传**（2026-10）——本层**不重组、不重传**，上层**必须**自带长度与可靠性 |
| F-12 | 通道关闭对上层可见为：fd 侧 `read()` 返回 0（EOF）或读写错误，**EOF 只是触发信号，detach 是随后显式执行的动作**；回调侧为原因错误码 + 不再触发 | `0x1003c16dc` C 行 33–35；串表 `0x100acc896`/`0x100acc8c1` | `CONFIRMED` / `INFERRED` | **已对齐** iAP2 docset 的 `R-1.14`（EOF=触发、detach=显式动作；link 侧编号与本 docset 的 `R-1.x` 各自独立）；fd 侧具体 `errno` 仍待运行时确认 |
| F-13 | 旧链路句柄在会话销毁后失效，用旧句柄操作返回"句柄无效" | 日志 `OI_RFCOMM_Accept - linkhandle %d not found`、`OBEX server RFCOMM disconnect on bogus link handle %x` | `CONFIRMED` | — |
| F-14 | 通道号来自 SDP 结果且**不保证稳定**（跨环境实测 4 / 1 / 5），每次连接必须重取，缓存需带失效条件 | `0x1007a3ba4`；`spec/03` R-3.16 | `CONFIRMED` | — |
| F-15 | bluetoothd 内**没有任何 iAP2 实现**（全二进制 `iap2` 字符串计数 = 0），报文本层不解析 | `analysis/07` C3 | `CONFIRMED` | — |

## 派生给 link 侧的最小义务（不是条款，只是事实的推论）

1. 若用 fd：必须自己按报文自身长度切分，不得依赖 `read()` 边界（F-05/F-11）。
2. 若用回调：必须在回调内拷贝，且回调内不得阻塞（F-06/F-07）。
3. 必须接受 `min(N1,2570)` 分块，并处理部分写（F-09/F-10）。
4. 必须自带完整性机制（F-11），并在 fd EOF/错误时**触发 detach**（F-12：EOF 是触发信号，detach 是随后显式执行的动作）。
