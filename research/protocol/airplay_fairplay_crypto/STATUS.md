# STATUS

<!-- counts:8,3,1 -->

三态计数（对应 `TASK.md` §2 的 12 个覆盖项）：

| 状态 | 数量 | 覆盖项 |
|---|---|---|
| 有证据 | 8 | C2 C3 C4 C5 C6 C7 C10 C11 |
| 部分 | 3 | C1 C8 C9 |
| OPEN | 1 | C12 |

---

## 1. 本阶段达成了什么

- **协议外围部分有证据**：内部流消息fp25、状态驱动循环、FP交换与setup安全信息处理已核；
  X-Apple-ET/CSeq请求头和et/ekey/eiv字典键已解析，不把这些调用点当完整网络schema。
- **密钥材料闭合**：master key / master IV 各自 16 字节随机；`ekey` 经 FairPlay 加密、
  `eiv` 字段本身不经 FairPlay 包裹（不等于传输明文）；解出后必须恰好 16 字节；本地字典清理不证明线上一次性。
- **KDF 闭合且可执行**：`SHA512("AirPlayStreamKey"‖dec(i)‖K)[0:16]` 与 IV 同构，名字前缀与
  格式串都在镜像里，参考实现与独立计算一致。Sender Legacy直接实现同一公式（A-46），不必调用Support包装器；目标provider选择仍待核。
- **加密段/记录边界已收窄**：每段ct‖tag16、nonce每次完整验证成功+1；已核屏幕路径AAD为原始128B网络头，
  一条记录可有两段、各自推进nonce。setter不自动清另一模式flag。ChaCha库ABI/真实profile互通仍缺。
- **AES库规则已补证**：CTR128位大端计数器与未用密钥流连续；CBC逐Update重置初始IV、尾部直通。
  两Init固定key16B/IV16B。关闭历史OPEN-9/11，网络调用边界/真实互通未由此证明。
- **错误码闭合**：18 个 `OSStatus` 定位到触发点。
- **键名已闭合**：原cache v5指针、镜像原字节和getter证明X-Apple-ET/CSeq及et/ekey/eiv；OPEN-13关闭。
- **加密器分派条件已补齐**：C14 固定了 `SupportsCoreUtilsPairingAndEncryption` 属性门、keyholder早退、type/G联合分派及provider出参；OPEN-7仅关闭拼写，能力来源和profile仍未闭合。
- **否定结论已收窄**：三镜像未命中FPLY字面量不证明线上不存在FPLY头或不能进一步分析。

## 2. 明确未达成（必须写在这里）

### 2.1 真实抓包闭环：**未达成**

`TASK.md` §6 A2 要求「至少一条真实抓包能闭合密钥交换 + 加密帧 + 解密」。
工作区**没有** AirPlay 媒体抓包，只有 23G90 的 BT-classic iAP2 抓包（不含 `/fp-setup`、
`/setup` 明文，也没有帧级密文/明文对）。

因此：

- `OPEN-3`、`OPEN-10`的真实profile/互通仍未验证；OPEN-13已由静态证据关闭，完整setup schema仍未闭合；
- `verify.py` C10 对此**显式 SKIP**，不静默通过；
- 本 docset **没有**任何「已用抓包验证」的表述。

### 2.2 实施缺口与已关闭历史问题

1. 历史`OPEN-13`的键名问题已关闭；但完整setup层级、必填条件和目标profile仍待验证，不能把安全信息getter返回0当密钥已安装（A-39）。
2. `OPEN-10`：AAD已追到128B网络头，但头的完整发送构造、其它回调路径/profile与跨段密码互通仍待闭合；不再以空/零AAD二选一。

一次密文抓包不保证关闭这些问题：需可读取的控制消息及已知密钥/nonce 的媒体对照，并跨帧验证；具体对端错误码不能由这些静态函数保证。

### 2.3 授权依赖

`OPEN-1`：本项目未实现FairPlay SAP与硬件信息接口；须确认目标profile及可用合法接口，不由此声称任何替代实现必然不可能。

## 3. 采样声明（避免把抽样当穷举）

- 逐条阅读的函数：`AirPlaySender` 36 个、`AirPlayReceiver` 15 个、`AirPlaySupport` 6 个（共 57）。
- 三份镜像合计 `__text` 约 4.77 MB，本次阅读覆盖的字节占比很低；**未做全函数普查**。
- 调用图来自线性扫描（不含 `blraa`/`blr`），因此「无调用者」只代表无直接调用。
- Ghidra 产物全部是 `DECOMPILED_UNREVIEWED`，结论以汇编与字节为准。
- 新增专项原切片5份（Receiver 2、CoreUtils 3），不增加基础57份/Ghidra计数；C11另复核3份已有函数。
- AES专项另有CoreUtils 6份原切片；专项合计11份，不新增Ghidra输出。

## 4. 交付物状态

| 文件 | 状态 |
|---|---|
| `TASK.md` | 完成 |
| `analysis/00`–`15` + `A-conclusions.md` | 当前静态审计记录 |
| `spec/00`–`08` | 完成（40+ 条规则，每条带依据） |
| `reference-impl/fairplay_crypto.py` | 完成（纯标准库，自检通过） |
| `reference-impl/gen_vectors.py` | 完成（可重跑，输出确定） |
| `runtime/vectors/{kdf,chacha,ctr,cbc,negative}.json` | 合成向量（3 + 6 + 2 + 6帧 + 4条）；AES另有2组NIST已知答案 |
| `runtime/README.md` | 完成（含补抓步骤） |
| `verify.py` | C1–C15；C11/C12屏幕与键名回归保留；C13含AES库回归；C14含分派门/参数有限解释；C15含Sender KDF与Receiver整数入参3切片/46锚点；C10仍SKIP不计通过 |
| `manifest.json` / `function-index.json` | 由 `verify.py --write` 生成 |
| 真实抓包 | **缺** |

## 5. 下一步（按性价比排序）

1. 核对/setup完整schema与目标profile；已解析键名无需重新列为未知。台账现11未决、4历史关闭。
2. 取得屏幕原始128B头、完整单/双段body及合法密钥/nonce、明文对照；CBC库规则已核但媒体调用边界与真实多记录互通仍需对照。
3. 继续追踪 `OPEN-15`（派生整数的来源/传递，而不是猜首流0或1）与 `OPEN-3`（ET/profile），结合可读取的控制记录核验。
4. 拿第二份固件做差分 → 关 `OPEN-14`。
