# STATUS · airplay_control_plane

- 文档集版本：**第 2 轮基础上的持续静态复核**（2026-10-26）
- 目标构建：`24A446` / `iPhone18,1`（iOS 27.0.1）
- 验收命令：`cd research/protocol/airplay_control_plane && python3 verify.py`

## 1. 两轮做了什么

第 1 轮（55 函数）：控制面组帧、4CC → 方法/路径表、Pair-Setup/Pair-Verify 的 TLV 与 HKDF 标签、
三类密钥上下文、阶段骨架、错误面、安全边界。

第 2 轮（66 函数，`analysis/12`）只做三件事，全部是固件侧、不依赖抓包：

1. **解开 CFString 常量**（`A12.1`）：24A446 镜像没有 `LC_DYLD_CHAINED_FIXUPS`，槽位是 arm64e
   认证/重定位值；用 `(slot & 0x7FFFFFFF) | (hi<<32)` 两跳解码，三个独立锚点验证，49/49 命中、0 歧义。
   工具：`tools/decode-keys.py`。
2. **拿到 `streams[]` 与连接子字典的真实键名**（`A12.2`、`A12.3`）：`type`、`streamID`、
   `streamConnectionID`、`controlPort`、`dataPort`、`seed`、`shk`、`sr`、`spf`、`ct` 等 20 个，
   连接键 9 个。
3. **解出加密记录读路径格式**（`A12.6`）：`u16` 小端长度 + 该长度的密文 + `16` 字节认证标签；读路径比较 `0x4000`。写路径另有约 1 KiB 聚合缓冲，不能把 16384 宣称为所有方向统一上限。
   读路径 `0x18be49a24`/`0x18be49a30`/`0x18be49a78`，写路径 `0x18be4d740`/`0x18be4d83c`。

顺带确认 `type` 是**枚举**而非布尔（`A12.4`）：比较链 `0x2519bcad4`–`0x2519bcb38` 覆盖
96、100、101、102、103、106、107、110、111、120、130；112 与 108/109 在已核分派进入错误分支，不是合法值。
这不是完整 SDK 类型表或车机接受能力表。`0x82`(130) 与 `0x78`(120) 同跳 `0x2519bd120`，
该分支只写回参数、不创建 cryptor（`A12.5`）。

## 2. 覆盖状态（12 项）

| # | 要求 | 状态 | 变化 |
|---|---|---|---|
| 1 | 控制通道建立 | PARTIAL | — |
| 2 | RTSP 消息格式 | PARTIAL | — |
| 3 | Pair-Setup | PARTIAL | — |
| 4 | Pair-Verify | PARTIAL | — |
| 5 | 加密会话 | PARTIAL | 记录格式/AAD/nonce与CoreUtils provider角色/标签链已核；目标调用者、切换与恢复仍缺 |
| 6 | RTSP 方法集 | PARTIAL | — |
| 7 | SETUP 传输参数 | PARTIAL | **OPEN → PARTIAL** |
| 8 | `type=130` 交接 | PARTIAL | **OPEN → PARTIAL** |
| 9 | 错误与状态码 | PARTIAL | — |
| 10 | 超时与重试 | OPEN | — |
| 11 | 安全边界 | PARTIAL | — |
| 12 | 版本与差异 | OPEN | — |

`CONFIRMED` 仍为 0：已核 type 分派不等于完整枚举；"130 是不是隧道"没有证据，只能算 PARTIAL。

## 3. 关闭与新增的 OPEN

- 关闭：`OPEN-AP-21`（记录格式）、`OPEN-AP-24`（键名）。
- 部分闭合：`OPEN-AP-25`（枚举已知，语义未定）。
- 本构建静态关闭：`OPEN-AP-38`（长度两字节是 AAD）、`OPEN-AP-39`（独立 nonce64 状态及推进）。
- 部分关闭：`OPEN-AP-22`/`40` CoreUtils provider的派生输入、状态门、IsServer及标签方向链已核，目标调用者选择仍缺；`OPEN-AP-43` 包装器 nonce 分派已核，替代库适配未闭合。
- `OPEN-AP-17` 本路径Curve25519 API已静态闭合；`OPEN-AP-19` 常规M2签名输入已核，其它profile仍缺。
- `OPEN-AP-41` 类型业务语义仍未关闭。

## 4. 下一轮优先项（仍是固件内可做的）

1. `OPEN-AP-22`/`23`：追目标CarPlay调用者选择的provider/派生输入分支与加密切换；
2. `OPEN-AP-40`：追目标连接构造时如何设置IsServer；本provider的flag来源与Read/Write输出绑定已核；
3. `OPEN-AP-41`：追 `type` 的调用方（`_endpoint_setupStreams` `0x251b371ac`、`_apsession_CreateTransportStream` `0x251a58098`）；
4. `OPEN-AP-8`：4CC 表剩余行逐条核对；
5. `OPEN-AP-1`/`31`/`32`：端口常量与超时值。

## 5. 已知限制

- 原抽样 66 / 22,599 个函数（0.29 %）；本次另增 9 个 CoreUtils 密码函数的原始字节/汇编至 `source/asm-audit/`，没有新增 Ghidra C，也未修改原始证据；
- `readable/ghidra/` 66 个反编译文件仅 3 份经人工比对（`stup`/`pave`/`flsh` 分支），其余按"反编译读数"标注；
- 键名解码规则是**经验规则**（三个锚点验证一致），`tools/decode-keys.py` 会把歧义计数打印出来；
- 仍无 AirPlay 控制面抓包（`OPEN-AP-37`），凡涉及"车机实际怎么回"的结论都不得写死。

## 6. 本次语义复核补充

- 对照 `_SetupClientExchange` 原 `.s` 修正消息表：Setup M1 基础字段为 0/6，公钥与证明在 SRP state=3；SPAKE2 子协议 M1 不能混同外层 M1。
- 修正 M5：HKDF 输出是签名输入前缀，不是长期身份私钥或 HMAC 密钥；类型 10 的签名长度为 64。
- `A13.4` 已确认包装器对 8 字节 nonce 直接调用 init_64x64，没有右补零步骤；其它调用分支/替代库仍由 `OPEN-AP-43` 限定。
- 加密切换、Setup/Verify 是否每次执行、SETUP/RECORD 全序与失败恢复均按证据限定，不将保守客户端策略写成强制线上规则。
- `A13.1`–`A13.5` 已确认 AAD 及 pad16/LE64 长度编排、独立 nonce64、部分写续发缓存、Configure 本地方向，以及读16384/写1024边界；tag/长度错误不混同，验签前不得发布明文。
- `verify.py` 含 C9 Setup 锚点、C10 九个新增切片及30个密码调用锚点/常量/结构模型、C11 类型分派的原字节/反汇编及260个有限解释案例。它们不执行完整固件、SRP、签名或网络握手。
- `analysis/14` 修正Verify关键用途：ECDH标签生成M1临时私钥材料，Encrypt标签从共享秘密派生TLV加密密钥；ResumeSessionID标签派生8B恢复ID，不是M4解密密钥。常规M2签名顺序与条件错误分支已核。
- 流描述符第二键是条件写入的整数streamID，不是附加字典。新增C12核对Verify/描述符两份原切片、42个指令锚点、6个标签常量；总验收为C1–C12。
- `analysis/15` 补CoreUtils key holder静态调用链；另新增2份AirPlaySender原始汇编切片（审计目录共11个新增函数，原66份C不变）。C13核对8份切片、29个锚点、CFString/虚表/标签及324个派生门案例；最新验收为C1–C13。
