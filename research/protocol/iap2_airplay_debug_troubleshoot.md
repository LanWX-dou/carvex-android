# 错误码、日志与调试卡点 — 任务要求与入口（`iap2_airplay_debug_troubleshoot`）

> 本文件保留原始任务边界；可执行的首版手册已经落在同目录下，本文不是协议规范。
> 目标：产出一份可复用的 AirPlay/iAP2 调试手册：链路错误码、RTSP 错误返回、加密失败、超时场景、抓包过滤规则、常见失败 case 汇总。
>
> 口径：本阶段不定义协议，只定义“如何观测、如何分层、如何定位”。每条结论必须能对应到日志/抓包/错误码。

---

## 0. 阶段定位

```text
Bluetooth / iAP2 Link / Control / AirPlay Control / Crypto / RTP / Media
        ↓
【本阶段】调试与故障定位
  ├─ 错误码分类
  ├─ RTSP 错误返回
  ├─ 加密失败
  ├─ 超时场景
  ├─ 抓包过滤
  └─ 常见失败 case
```

当前首版入口：

- [README](iap2_airplay_debug_troubleshoot/README.md)：角色、使用顺序和运行边界；
- [30 分钟定位模型](iap2_airplay_debug_troubleshoot/spec/01-diagnostic-model.md)；
- [错误域表](iap2_airplay_debug_troubleshoot/spec/02-error-codes.md)、[抓包过滤](iap2_airplay_debug_troubleshoot/spec/03-capture-filters.md)、[日志规范](iap2_airplay_debug_troubleshoot/spec/04-logging.md)；
- [案例库](iap2_airplay_debug_troubleshoot/spec/05-casebook.md)、[清单](iap2_airplay_debug_troubleshoot/spec/06-checklist.md)、[超时与恢复](iap2_airplay_debug_troubleshoot/spec/08-timeouts-recovery.md)；
- [状态与验证口径](iap2_airplay_debug_troubleshoot/STATUS.md)及[未决项](iap2_airplay_debug_troubleshoot/spec/07-open-items.md)。

首版已用 10 个离线合成夹具验证结构与负例；尚无真实车机失败样本，因此不宣称真实互通或“30 分钟”效率已实测。

本阶段只回答：

- 出错时看哪一层、看什么字段；
- 错误码/状态码如何映射到根因；
- 抓包过滤器怎么写；
- 日志打什么、不打什么；
- 常见失败如何复现、如何排除。

**不回答**：协议字段定义、加密算法、媒体解码。

---

## 1. 目标与完成判据

**目标**：让一个工程师在 30 分钟内回答：

1. 失败发生在哪一层？
2. 是链路、配对、加密、RTP、解码还是业务？
3. 下一步抓什么、看什么、改什么？
4. 这是已知 case 还是新问题？

**完成判据**：

1. 12 项覆盖要求逐项有内容；
2. 错误码/状态码有表，含来源与含义；
3. 抓包过滤器可直接复制使用；
4. 常见 case 有“现象 → 证据 → 根因 → 处置”；
5. 每个 case 有最小复现步骤；
6. 不把“猜测”写成“根因”；
7. 日志不包含密钥/证书私钥/用户隐私。

---

## 2. 素材与证据来源

| 素材 | 要求 |
|---|---|
| 失败抓包 | 各层至少一个失败样本 |
| 日志 | 客户端/平台/车机日志（脱敏） |
| 错误码 | iAP2、RTSP、TLS/FairPlay、平台错误 |
| 正常样本 | 用于对照 |
| 已知问题 | 现有 OPEN 项、历史故障 |

---

## 3. 方法与证据链

1. **分层**：Bluetooth → iAP2 Link → Control → AirPlay Control → Crypto → RTP → Media → Business；
2. **定位**：先看“最后一层成功”，再看“第一层失败”；
3. **证据**：固件构建/哈希/指令地址、抓包帧号、日志时间戳、错误码、状态机状态；静态与运行结论分开；
4. **复现**：最小步骤、最少变量；
5. **排除**：正常样本对照、替换变量；
6. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`。

**禁止**：

- 把“没收到响应”直接归因于加密；
- 把“RTSP 500”直接归因于车机；
- 把“只收集日志”当作已经定位根因；缺什么证据须按具体断言判断。缺少抓包不自动否定静态解析、组包、错误分支或状态门结论；未证的真实现场原因才保留 `OPEN` / `INFERRED`；
- 在日志里打印密钥/私钥/完整证书链隐私字段。

---

## 4. 抽样策略

至少覆盖：

1. 蓝牙连不上；
2. iAP2 SYN 失败；
3. 认证失败；
4. Pair-Setup/Verify 失败；
5. RTSP SETUP 失败；
6. FairPlay 解密失败；
7. RTP 丢包/花屏；
8. 断连/重连；
9. 休眠/唤醒。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **错误分层** | 每层有哪些错误？如何判定“最后一层成功”？ |
| 2 | **iAP2 链路错误** | RST、校验、序号、超时、重传失败如何识别？ |
| 3 | **RTSP 错误** | 4xx/5xx、`CSeq` 不匹配、方法不支持如何定位？ |
| 4 | **配对错误** | Pair-Setup/Verify 失败、证书/签名/状态错误？ |
| 5 | **加密失败** | 密钥不匹配、标签失败、IV/序号错误？ |
| 6 | **超时场景** | 各阶段超时值、重试、退避、放弃？ |
| 7 | **抓包过滤** | Bluetooth、mDNS、当前协商出的控制/媒体端点以及 RTP 的过滤器？ |
| 8 | **日志点** | 每层打什么、级别、脱敏、关联 ID？ |
| 9 | **常见 case** | 现象 → 证据 → 根因 → 处置？ |
| 10 | **复现步骤** | 最小变量、可重复？ |
| 11 | **误判排除** | 如何区分“没发/没收到/收到但没处理”？ |
| 12 | **版本差异** | 不同车机/固件/平台的错误表现？ |

### 5.1 重点专题

#### A. 抓包过滤器

至少给出可直接使用的：

```text
# mDNS
udp port 5353

# AirPlay 控制面：从当前会话/SETUP 记录的端点替换，不写死 7000
tcp host <peer-ip> and port <control-port>

# RTP：从 SETUP/媒体协商得到的实际端口替换，不写死范围
udp host <peer-ip> and port <media-port>

# iAP2 over RFCOMM（如可得）
btrfcomm
```

并说明：过滤器会漏什么、如何同时抓多接口、如何保留链路头。`-f`（捕获过滤）与 `-Y`（显示过滤）不可混用；`btrfcomm` 是显示字段过滤器，不能替代 RFCOMM 链路捕获条件。可复制的动态表达式见 [spec/03](iap2_airplay_debug_troubleshoot/spec/03-capture-filters.md)。

#### B. 错误码表

| 层 | 错误码/状态 | 来源 | 含义 | 下一步 |
|---|---|---|---|---|

要求：错误码必须来自实际日志/抓包/文档，不得编造。

#### C. 常见 case 矩阵

| 现象 | 最后一层成功 | 第一层失败 | 证据 | 根因 | 处置 |
|---|---|---|---|---|---|

至少覆盖：连不上、认证失败、配对失败、SETUP 失败、解密失败、花屏、无声音、触摸无响应、断连。

#### D. 日志规范

- 关联 ID：连接 ID / 会话 ID / 流 ID；
- 每层入口/出口；
- 错误码 + 关键字段；
- 脱敏：密钥、私钥、证书隐私、用户数据；
- 级别：ERROR/WARN/INFO/DEBUG。

---

## 6. 当前交付目录

```text
research/protocol/iap2_airplay_debug_troubleshoot.md       # 本任务边界与入口
research/protocol/iap2_airplay_debug_troubleshoot/
  README.md
  analysis/
    00-evidence-index.md
  spec/
    01-diagnostic-model.md
    02-error-codes.md
    03-capture-filters.md
    04-logging.md
    05-casebook.md
    06-checklist.md
    07-open-items.md
    08-timeouts-recovery.md
  runtime/
    README.md
  reference-impl/
    diagnostic.py
    reproduce.py
  tools/
    manifest.py
  coverage.json
  verify.py
  STATUS.md
  manifest.json
```

上述为当前实际交付，不再把旧建议中的analysis01–09或captures/logs目录称作已交付。
私有现场样本尚未归档；目录清单与哈希以 `manifest.json` 为准。

---

## 7. 非目标

- 定义协议字段；
- 实现加解密/编解码；
- 替代各阶段规范；
- 收集用户隐私/密钥。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| 错误码来源不一致 | 误判根因 |
| 抓包点不全 | 只看到一半 |
| 日志脱敏不足 | 泄露密钥/隐私 |
| 车机差异 | 同一现象不同根因 |
| 超时值未证 | 误判“卡死” |
| 只贴日志 | 无法定位 |

---

## 9. 验收清单

- [x] 首版错误分层、错误码、RTSP、加密、超时/恢复、过滤、日志、案例和 OPEN 入口已建立；
- [x] 离线 `verify.py` 与 D01–D10 合成夹具通过（工具缺失/现场样本仍如 STATUS 所列为 SKIP）；
- [x] `STATUS.md` 与 `OPEN` 清单完整；
- [ ] 真实车机成功/失败对照、目标工具现场过滤验证和端到端互通仍待完成。

---

## 10. 一句话

**本阶段不定义协议，只教你“出错时先看哪一层、抓什么包、看什么日志、如何排除误判”；首版已可按目录执行，但真实样本仍是验收前提。**
