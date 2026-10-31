# 结论汇总：这份文档能不能指导客户端连上车机

直接回答用户的问题：**这份材料可以指导外围编排、字段校验和候选帧实现，但不能单靠它完成第一帧互操作。**
FairPlay SAP仍缺可用实现/授权接口；键名已闭合，但完整setup schema、目标库ABI/参数和真实媒体对照仍待补齐。
屏幕AAD已追到128B网络头（限定接收路径），不是不可复制的内部结构；见A-34–A-36。

---

## 一、按层判决

| 层 | 内容 | 判决 | 依据 |
|---|---|---|---|
| L1 | FairPlay SAP握手算法与密钥封装 | 本项目未实现；需适用的合法接口/实现，不从未命中字面量推导不可能实现 | A-07、`OPEN-1` |
| L2 | 交换编排（谁发、几次、状态字节、错误码） | **可实现** | A-08、A-10、A-25 |
| L2′ | 请求头与安全信息字典 | X-Apple-ET/CSeq、et/ekey/eiv拼写已核；完整层级/profile未证 | A-37–A-39；历史OPEN-13关闭 |
| L3a | 密钥派生（SHA-512 KDF，名字+整数+截断） | Sender Legacy与Receiver均有公式证据；目标provider选择和整数完整来源待核 | A-16、A-17、A-18、A-46 |
| L3b | 流类型 → 加密器分派 | **可实现（须同时满足属性G、keyholder和type门）**；语义名待实测 | A-19、A-43–A-45、`OPEN-8` |
| L3c | AES-CTR状态 | 128位大端计数器和跨Update余量已核；媒体profile/密钥来源仍需核 | A-41/A-42 |
| L3d | ChaCha屏幕段/记录边界 | 原始128B头AAD、可选双段已核；目标库与profile互通未证 | A-23、A-34/A-35、`OPEN-10` |
| L3e | AES-CBCFrame | 初始IV逐Update重置、整块CBC/余尾直通已核；调用边界不能由TCP分片猜 | A-40；历史OPEN-11关闭 |

## 二、十二项覆盖项的结论与状态

| # | 覆盖项 | 结论 | 状态 |
|---|---|---|---|
| C1 | 证书交换 | 交换的**承载与轮次**可写（`"fp25"` 流消息，状态字节驱动，`Mib5yocT` 类型 3）；证书内容与校验属闭源核心 | 证据 + `OPEN-1` |
| C2 | 密钥交换消息 | 已核Legacy master key由本机RandomBytes(16)生成；ekey封装key，eiv不单独FairPlay封装；不推导整个传输明文或每流必填 | 证据（A-12/A-39） |
| C3 | SK 派生 | `SHA512("AirPlayStreamKey"‖dec(i)‖K)[0:16]` 与 `SHA512("AirPlayStreamIV"‖dec(i)‖K)[0:16]` | 证据（A-16/A-17） |
| C4 | AES 模式 | 分派受属性G、keyholder和type共同控制；G=0的部分type走CBC/CTR，G≠0可走ChaCha；屏幕解密优先ChaCha，setter不清对方flag | 证据（A-19/A-20/A-21/A-36/A-43–A-45） |
| C5 | 加密边界 | ChaCha每段ct+tag16；CTR连续密钥流；CBCFrame按Update整块前缀加密、余尾直通 | A-23/A-40/A-41 |
| C6 | 校验标签 | 16 字节 Poly1305 tag 位于帧尾；验签失败不推进 nonce | 证据（A-23） |
| C7 | 每段参数 | ChaCha成功设置后nonce为0，逐成功段+1；CTR保留计数器和余量；CBC逐Update重置初始IV | A-35/A-36/A-40/A-41 |
| C8 | 密钥刷新 | 入口 `UpdateMasterAESKeyAfterSharing`，仅 authType==4 时就地替换 16 字节 master key | 部分（`OPEN-4`/`OPEN-5`） |
| C9 | 密钥失效 | 本地 master 缓冲替换、正常收尾删除字典字段已证；不证明对端同步失效或线上一次性 | 部分（`OPEN-5`） |
| C10 | 错误与降级 | 18 个 `OSStatus` 已归类（字段错 / 状态错 / 顺序错 / 加密器错） | 证据（A-25） |
| C11 | 安全边界 | 120/130等路径留下NULL出参；本分派未调用GetNull，不能单凭NULL断言线上明文；密钥材料清零；`jEHf8Xzsv8K`释放中间blob | 证据（A-19/A-15/A-44） |
| C12 | 版本与差异 | 仅 24A446；无跨版本差分 | `OPEN-14` |

## 三、与目标的差距（要连上车机还缺什么）

按优先级：

1. **完整setup schema/profile**。历史OPEN-13键名问题已关闭，但未证所有流必填三键；
   getter失败或et=1存在返回0却不安装新密钥的早退。需可读取的控制记录或继续审计调用者。
2. **屏幕头构造与真实互通**（`OPEN-10`）。AAD原始128B头及可选双段已有静态证据，
   完整字段/profile和密码库语义仍需发送链或已知密钥/nonce、明文对照；仅密文抓包不够。
3. **FairPlay可用实现与授权接口**（`OPEN-1`）。本项目未交付SAP实现及其硬件信息接口；
   应确认目标profile所需凭证与合法接口，不能把现有调用点当作已实现握手，也不能由此证明其他实现必然不可能。
4. 其余 OPEN 仍需分别满足登记的关闭条件；一次样本不能自动证明密钥刷新、其它加密模式或跨版本差异。

## 四、可以直接开工的部分

`reference-impl/fairplay_crypto.py` 已给出：

- KDF（含名字拼串与截断），带两组自检向量；
- ChaCha20-Poly1305 帧封装/解封装（8 字节计数器 + 尾部 tag）；
- AES-CTR 帧流；
- CBCFrame加密端（重置IV、尾部直通）；两种AES模式有NIST已知答案，CTR有跨调用切分测试；
- 负例（错 key / 错 nonce / 改 tag）。

`python3 research/protocol/airplay_fairplay_crypto/verify.py` 会重跑这些向量并与 `runtime/vectors/*.json` 对照。

## 五、一句话

**文档已经把“有指令证据的外围行为”“候选实现”和“必须由授权/抓包补齐的互操作条件”分开；它不是完整 CarPlay/FairPlay 合规规范。**
实现者仍需把 OPEN 项作为上线前置条件，而不能把合成向量通过等同于车机互通。
