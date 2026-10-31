# 08 · 未闭合项

所有 `OPEN-AP-n` 在此登记。关闭条件 = 有本 docset 内的指令/字节证据或一份真实抓包。

| id | 问题 | 关闭条件 |
|---|---|---|
| `OPEN-AP-1` | 控制端口是否默认 7000 | 找到常量或抓包 |
| `OPEN-AP-2` | 是否接受 TLS | 连接路径逐指令核对 |
| `OPEN-AP-3` | `CSeq` 初值/回绕 | 连接对象初始化 |
| `OPEN-AP-4` | `X-Apple-ProtocolVersion` 取值 | `info` 响应/常量 |
| `OPEN-AP-5` | 状态行解析 | `HTTPMessageReadMessageEx` 逐段 |
| `OPEN-AP-6` | 发送端是否 chunked | 发送路径核对 |
| `OPEN-AP-7` | 头大小写/顺序是否校验 | 对端抓包 |
| `OPEN-AP-8` | 4CC 表未抽检行 | 逐条指令核对 |
| `OPEN-AP-9` | `SETUP` URL 是否固定 | 抓包 |
| `OPEN-AP-10` | `text/parameters` 键名 | 字符串/抓包 |
| `OPEN-AP-11` | 未知类型错误码名 | 符号表/文档 |
| `OPEN-AP-12` | SRP/SPAKE2 选择依据 | flag 解析 |
| `OPEN-AP-13` | M1 TLV `0` 语义 | 协议状态机 |
| `OPEN-AP-14` | M1 TLV `0x19` 语义 | 同上 |
| `OPEN-AP-15` | 是否强制 PIN | 车机抓包 |
| `OPEN-AP-16` | 凭证落盘方式 | 钥匙串路径 |
| `OPEN-AP-17` | 临时密钥曲线/API | **本路径静态闭合**（`A14.1`：Curve25519及32B输入输出，HKDF-SHA512标签用途已核）；替代库与其它profile需另验 |
| `OPEN-AP-18` | 是否走 MFi 分支 | CarPlay 抓包 |
| `OPEN-AP-19` | M2 签名串联顺序 | **常规peer分支闭合**（`A14.2`：peer临时公钥||peerID||local临时公钥，TLV10签名64B）；callback/AppleID及profile适用性仍需核验 |
| `OPEN-AP-20` | 恢复会话条件 | 状态机 |
| `OPEN-AP-21` | 加密记录基本格式 | **读路径已闭合**（`A12.6`：`u16 LE 长度` + 密文 + 16 B 标签；读侧比较 16384）；写侧聚合上限与统一线上上限仍按 `R-3.6` 保留边界 |
| `OPEN-AP-22` | 会话密钥 HKDF 组合 | **CoreUtils provider静态链已核**（`A15.3`：type/state门、共享秘密32B或可变长材料、HKDF-SHA512与传入标签）；目标profile/provider/输入分支选择仍需调用者证据 |
| `OPEN-AP-23` | 加密起始消息 | 抓包 |
| `OPEN-AP-24` | 流描述符键名 | **已闭合**（`A12.1`–`A12.3`：键名表已解出并验证） |
| `OPEN-AP-25` | `type` 取值表与 `130` | **部分闭合**（`A12.4`：已核分派处理 96/100/101/102/103/106/107/110/111/120/130，112 不在其中；完整枚举/语义见 `OPEN-AP-41`） |
| `OPEN-AP-26` | 每流端口协商 | 同上 |
| `OPEN-AP-27` | `SETUP` URL 固定性 | 同 `OPEN-AP-9` |
| `OPEN-AP-28` | 阶段全序与重试 | 阶段函数分析 |
| `OPEN-AP-29` | 事件通道建立时机 | 抓包 |
| `OPEN-AP-30` | `RECORD` 前置条件 | 抓包 |
| `OPEN-AP-31` | 请求超时值 | 选项字典 |
| `OPEN-AP-32` | 重连条件/次数 | 阶段函数 |
| `OPEN-AP-33` | `0xFFFFBEFD` 错误名 | 符号表 |
| `OPEN-AP-34` | MFi 证书是否强制 | 抓包 |
| `OPEN-AP-35` | 长期密钥存储保护 | 平台文档 |
| `OPEN-AP-36` | 车机证书用途校验 | 逐指令 |
| `OPEN-AP-37` | 缺 AirPlay 控制面抓包 | 取得抓包 |
| `OPEN-AP-38` | 长度前缀是否作为 AAD 参与认证 | **本构建静态闭合**（`A13.1`：两字节 LE16 原样入 Poly1305，含 pad16 与长度尾部）；不代表车机互通 |
| `OPEN-AP-39` | 控制记录 nonce 编码与推进 | **本构建静态闭合**（`A13.2`：独立 nonce64，已核 APTransport 配置初值零；读验证后、写生成后推进）；不是基准拼另一计数器 |
| `OPEN-AP-40` | 密钥槽方向及上游角色/HKDF 标签对应 | **CoreUtils provider链已核**（`A15.1`/`2`：flag为IsServer；K_A/K_B对应Read/Write，IsServer非零交换）；目标CarPlay调用者/provider/角色选择仍缺，不能推广到所有通道 |
| `OPEN-AP-41` | `type` 各值语义（130 是否隧道） | 调用方/抓包 |
| `OPEN-AP-42` | 加密记录认证失败后的断开、重连与是否可恢复 | 失败路径逐指令 + 控制面抓包 |
| `OPEN-AP-43` | 配对 nonce 包装分派与替代库适配 | **包装器分派子项闭合**（`A13.4`：8 字节直接 init_64x64，12 字节才 init_96x32，无右补零）；其它调用分支与替代库仍需独立向量/会话对照 |
| `OPEN-AP-44` | `POST /feedback` 保活间隔 | 控制面抓包/日志；`OPEN-AP-31` 只覆盖请求超时，不等于保活间隔 |
| `OPEN-AP-45` | `GET /info` 响应字段/schema 与能力位映射 | 从 `APTransport`/`AirPlaySender` 的 `/info` 响应解析路径还原；当前只证方法/4CC，不证响应正文 |
