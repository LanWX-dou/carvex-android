# 阶段四任务书：AirPlay FairPlay 与帧加密（CarPlay 车机侧辅助文档）

> 本文件是本阶段（阶段四）的**任务书**，不是结论。结论在 `analysis/`，可执行规则在 `spec/`。
> 上游任务书：`research/protocol/airplay_fairplay_crypto.md`（保持原样，不改）。
> 本 docset 只描述**证据能支撑的部分**；证据不足处一律写 `OPEN-*`，不允许用「业界常识」补齐。

---

## 0. 阶段位置与目标

整体目标（原话，不改）：

> 我的目的是文档能指导实现客户端，客户端能与车机进行连接目前，文档是，否，可行，，不行就完善它

本阶段只解决一个问题：**当客户端（设备侧，模拟 iPhone）要跟车机建立加密媒体通道时，FairPlay 交换与逐帧加密这两层到底怎么做。**

三层里只有第二、三层可能被完整规定：

| 层 | 内容 | 本阶段判定 |
|---|---|---|
| L1 | FairPlay SAP握手本身（核心消息语义、密钥封装） | OPEN-1：本项目未实现，需确认目标profile适用的合法实现/授权接口；外围代码不证明其他实现不可能 |
| L2 | 交换的**传输与编排**：谁发、发几次、带什么字段、什么错误码 | 可完整规定（有指令级证据） |
| L3 | 拿到密钥材料之后：派生、选算法、逐帧格式、nonce/tag/IV 演进 | 可完整规定（有指令级证据） |

阶段四的产出必须让实现者能回答：**我用 MFi 模块拿到哪几段字节、把它们放进哪个消息、按什么顺序发、车机回什么、之后每一帧怎么加密。**

---

## 1. 证据源（唯一允许引用的固件面）

三份 Mach-O 全部来自 24A446（iOS 27.0.1 / iPhone 17 Pro / `iPhone18,1`）共享缓存，均已落在
`source/firmware/`，逐字节取用；哈希与段表在 `source/metadata/`。

| 镜像 | 字节数 | SHA-256 | LC_UUID |
|---|---|---|---|
| `AirPlaySender` | 4,397,312 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` |
| `AirPlayReceiver` | 2,453,520 | `ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a` | `b7bebf3b-dcf2-3395-b106-f449a30fdb1c` |
| `AirPlaySupport` | 1,536,072 | `d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15` | `3dc39c34-98dd-348c-ad18-de6e6dc38173` |

- `AirPlaySender` = 客户端（设备）侧实现，**本阶段的主证据**。
- `AirPlayReceiver` = 本iOS镜像内的接收侧实现，用来做**对偶参考**；不是从目标车机取得的实现，不能证明车机相同分支行为。
- `AirPlaySupport` = 两侧共用的密码学工具（`APSCryptor*`、SHA-512 KDF、AES/ChaCha 原语）。
- 共享缓存符号表（`ipsw dyld stubs`）用于把 `__TEXT_STUBS` 里的外部调用还原成符号名；产物是
  `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`（50 万条，可重生成）。

**不允许**再把下列目录当证据（它们是早期单向静态扫描，未做指令级确认）：
`firmware/analysis/24A446/airplay-static-evidence`、`airplay-first-pairing`、`screen-key-binding`、
`audio-chacha-record`、`audio-nonce-construction`、`security-encryption-tail`、`AirPlaySender-functions.json`。

---

## 2. 覆盖项（12 项，逐项必须有证据或显式 OPEN）

编号与上游任务书 §5 一致，本阶段逐条落地。C 前缀仅供 `verify.py` 检查。

| # | 覆盖项 | 本阶段落点 | 状态字段 |
|---|---|---|---|
| C1 | 证书交换 | `analysis/02-fply-exchange.md`、`spec/02-fairplay-exchange.md` | 有证据 / OPEN-1 |
| C2 | 密钥交换消息 | `analysis/02`、`analysis/03-keyholder.md` | 有证据 |
| C3 | SK 派生 | `analysis/04-kdf-sha512.md`、`spec/04-kdf.md` | 有证据 |
| C4 | AES 模式 | `analysis/05-stream-cryptor-map.md`、`analysis/06-frame-format.md` | 有证据 |
| C5 | 帧加密边界 | `analysis/06-frame-format.md`、`spec/06-frame-crypto-aes.md` | 有证据 |
| C6 | 校验标签 | `analysis/06`、`spec/07-frame-crypto-chacha.md` | 有证据 |
| C7 | 每帧参数 | `analysis/06`（IV/nonce 演进）、`spec/06`、`spec/07` | 有证据 |
| C8 | 密钥刷新 | `analysis/03`（`UpdateMasterAESKeyAfterSharing`）、`spec/03` | 部分 / OPEN-4 |
| C9 | 密钥失效 | `analysis/03`、`spec/08-errors-and-open.md` | 部分 / OPEN-5 |
| C10 | 错误与降级 | `analysis/07-receiver-side.md`、`spec/08` | 有证据 |
| C11 | 安全边界 | `analysis/09-negative-space.md`、`spec/00-scope.md` | 有证据 |
| C12 | 版本与差异 | `analysis/09`、`spec/00` | OPEN / OPEN-14 |

---

## 3. 专题（上游任务书 §5.1 A–D 的落地版）

- **专题 A｜FairPlay 交换的可编排面**：传输层（哪种消息承载 FP blob）、步数、每步请求/响应方向、
  状态字节语义、失败错误码。→ `analysis/02`
- **专题 B｜密钥材料与生命周期**：master key/IV 从哪来（随机）、怎么被 FairPlay 包起来（ekey 加密、
  eiv 明文）、什么时候换（sharing 之后就地替换）。→ `analysis/03`
- **专题 C｜派生与逐帧加密**：SHA-512 KDF 的精确输入输出、流类型到加密器的映射、三种帧格式
  （CBC frame / CTR / ChaCha20-Poly1305）的字节布局与每帧演进。→ `analysis/04`、`05`、`06`
- **专题 D｜反证与边界**：三个镜像里**不存在**的常量（例如 `FPLY` 字面量）、无法解析的链式指针、
  以及因此不能声称的结论。→ `analysis/09`

---

## 4. 方法论要求（沿用前三个 docset 的纪律）

1. 每条结论必须挂**指令地址**（`0x…`）或明确标注 `[23G90]` / `[建议]`。
2. Ghidra 反编译产物一律视为 `DECOMPILED_UNREVIEWED`，只能作为阅读辅助；**结论必须以汇编或字节为准**，
   且关键结论要求「反编译 + 汇编 + 字节」三者能对上（`verify.py` 校 `.bin` 与固件切片一致）。
3. 未命名/被剥名的函数不得用符号名推语义；只能写「真实函数，名字被剥掉」，并用调用点与常量定性。
4. 每条规则（`spec/` 里的 `R-x.y`）必须写 `依据：A…`，且 `A` 编号必须在 `analysis/` 中存在。
5. 任何未被证明的字段/值进 `OPEN-*` 台账（`analysis/08-open-items.md`），并在 `spec/` 引用处标注。
6. 禁止把「能解密一条帧」推广成「覆盖所有流、所有版本」。

---

## 5. 交付物

```
TASK.md                 本文件
STATUS.md               三态计数、采样声明、缺口清单
analysis/00..15         A 编号证据链
analysis/A-conclusions  结论汇总
spec/00..08             R-x.y 可执行规则（每条带依据）
runtime/README.md       抓包与向量使用说明；本阶段抓包缺失的如实声明
runtime/vectors/        独立测试向量（由 reference-impl 生成并复核）
reference-impl/         参考实现（KDF + 三种帧格式 + 负例）
verify.py               C1–C15 可重放校验（检查编号与§2覆盖编号不是同一维度）
manifest.json           文件清单与哈希
function-index.json     已取证函数索引（地址/大小/哈希/用途）
```

---

## 6. 验收判据（本阶段）

- **A1**：12 个覆盖项逐项在 `STATUS.md` 有状态（有证据 / 部分 / OPEN），不得出现「一切已确认」式的总结。
- **A2**：至少一条**真实抓包**能闭合「密钥交换 + 加密帧 + 解密」——**本阶段达不到**，
  工作区没有 AirPlay 媒体抓包（只有 23G90 的 BT-classic iAP2 抓包）。此处必须写「未达成」，
  不得用构造向量冒充抓包。见 `STATUS.md` §缺口。
- **A3**：独立测试向量 ≥ 3 组，每组含输入帧/密钥/IV 或 nonce/输出密文/标签，且可由
  `reference-impl` 复现（`verify.py` C7 自动跑）。
- **A4**：负例 ≥ 3 个（错 key、错 IV/nonce、篡改 tag），每个都有明确失败判据。
- **A5**：`verify.py` 可重复执行，且在缺抓包时**只跳过抓包相关检查并显式报告**，不静默通过。
- **A6**：文档中不得断言「任一实现对所有流、所有版本均可用」；`verify.py` C8 用词表检查。

---

## 7. 明确的非目标

- 不实现 FairPlay SAP 算法（`OPEN-1`）。
- 不覆盖 MFi 认证协处理器的电气/固件接口（属 `research/protocol/iap2_*` 与 MFi 文档范畴）。
- 不修改 `link/bluetooth`、`iap2_*` 的既有文档与代码。
- 不改 `research/protocol/airplay_fairplay_crypto.md`（上游任务书）。

---

## 8. 本阶段两条范围决策（已确认，记录在此以免反复）

1. 以 `AirPlaySender` 为主证据；缺证据处一律 `OPEN`，不用外部资料补。
2. FairPlay算法层写OPEN并标明可用合法实现/授权接口缺口；其余层（传输编排、密钥材料、KDF、帧格式、
   错误码）照常给可执行规范。
