# AirPlay mDNS 发现阶段 — 任务要求（`airplay_mdns_discovery`）

> **历史任务书**：本文件是上游任务书，现行版本以 `research/protocol/airplay_mdns_discovery/TASK.md` 为准；本文件保留用于追溯，不再单独修订。


> 本文件是**任务书**，不是协议规范，也不预设字段语义。
> 目标：沿与前三个阶段相同的证据标准，产出 **AirPlay mDNS / DNS-SD 发现** 的平台无关规范，供“设备侧客户端（模拟 iPhone）”发现车机的 AirPlay 服务。
>
> 口径：`CONFIRMED` 只表示“在本阶段证据范围内可复核”，不表示 Apple 官方规范；`INFERRED` 必须标推断；无证据一律 `OPEN`。

---

## 0. 阶段定位（与前后阶段的衔接）

```text
Bluetooth Classic
  └─ RFCOMM → iAP2 Link → Control Session
        └─ 0x4301：Wi-Fi SSID / 密码 / wifiIP / port 等
              ↓
        设备加入车机 Wi-Fi
              ↓
        【本阶段】mDNS / DNS-SD 发现 AirPlay 服务
              ↓
        AirPlay 配对 / 加密 / 会话 / 媒体（不在本阶段）
```

本阶段只回答：

- 车机在 Wi-Fi 上**宣告了什么**；
- 这些宣告的 **DNS 记录结构**是什么；
- TXT 里的**字段与能力位**分别表示什么；
- 如何从服务实例解析到**可连接的地址与端口**；
- 在多车、多服务、IPv4/IPv6、缓存/过期时**如何选择**。

**不回答**：AirPlay 配对、加密、媒体传输、CarPlay 投屏、蓝牙 iAP2、A2DP、音频编码。

> 重要边界：mDNS 发现成功 ≠ AirPlay 可连接，更 ≠ CarPlay 可用。发现只是“找到候选服务”。

---

## 1. 目标与完成判据

**目标**：给出可复现、逐条可追溯的 AirPlay mDNS 发现规范，使第三方客户端能在自己的 Wi-Fi 栈之上完成：

1. 浏览车机宣告的 AirPlay 服务；
2. 解析 PTR / SRV / TXT / A / AAAA；
3. 解析 TXT 字段与 `features` 能力位；
4. 解析出候选地址与端口；
5. 在多个候选之间做出可解释的选择；
6. 明确哪些字段/位/行为仍是 `OPEN`。

**完成判据（全部满足才算完成）**：

1. 12 项覆盖要求（第 5 节）逐项有抓包/标准/实现依据，或明确标 `OPEN`；
2. 至少一份真实车机的 Wi-Fi mDNS 抓包，能回放出完整服务图；
3. `verify.py` 通过（抓包哈希、DNS 解码、字段表、能力位表、地址选择用例）；
4. `STATUS.md` 给出 `CONFIRMED / INFERRED / OPEN` 统计与样本覆盖；
5. 每条 `R` 条款能点回 `analysis/` 的 `A` 结论，`A` 能点回抓包帧号/字节或标准条款；
6. 所有未知 TXT 键、未知 `features` 位、版本差异均登记为 `OPEN`，不得静默忽略；
7. 不得把“抓到一个车机”写成“所有车机/所有 AirPlay 版本”。

---

## 2. 素材与证据来源

### 2.1 主素材

| 素材 | 要求 |
|---|---|
| Wi-Fi mDNS 抓包 | 车机与设备同一 Wi-Fi；至少覆盖一次完整启动/连接周期 |
| 抓包位置 | 设备侧或 AP 侧镜像；保留 Ethernet/Wi-Fi 头、UDP 5353、IPv4/IPv6 |
| 车机样本 | 至少 1 台真实车机；尽量 2 台以上，覆盖不同 AirPlay 版本 |
| 服务类型 | 至少覆盖车机实际宣告的 `_airplay._tcp`；如同时有 `_raop._tcp` 一并记录 |
| 时序 | 冷启动、休眠/唤醒、服务消失（TTL=0）、重新宣告 |
| 网络 | IPv4 与 IPv6（含 link-local）分别记录；双栈时记录地址选择 |

### 2.2 参考材料

- RFC 6762（mDNS）、RFC 6763（DNS-SD）；
- Apple Bonjour / DNS-SD 文档；
- AirPlay / AirPlay 2 的公开字段说明（只作对照，不替代抓包）；
- MFi / CarPlay 授权材料（如可得）；
- 现有 `research/protocol/bluetooth_rfcomm`、`research/protocol/iap2_link_establish`、`research/protocol/iap2_control_session` 的边界结论；
- 目标固件/框架符号（如 `AirPlaySupport`、`carkitd`、Bonjour 相关）仅作**交叉核对**，不得单独下结论。

### 2.3 工具

- `tcpdump` / `tshark` / Wireshark；
- Python：`dnspython`、`scapy` 或自写 DNS 解码器；
- 抓包回放器 + 断言脚本；
- 真实 mDNS 查询器（Avahi/Bonjour/自写）用于对照，但**以抓包为准**。

---

## 3. 方法与证据链

1. **抓包**：保留原始 pcap，计算 SHA256；记录接口、信道、时间、抓包点。
2. **DNS 解码**：解析 header、question、answer / authority / additional；处理名称压缩、截断、EDNS0。
3. **服务图重建**：
   ```text
   PTR  _airplay._tcp.local → <instance>
   SRV  <instance> → <target-host>:<port>
   TXT  <instance> → key=value...
   A    <target-host> → IPv4
   AAAA <target-host> → IPv6
   ```
4. **字段表**：每个 TXT 键给出出现次数、值样例、编码、长度、版本差异、未知项。
5. **能力位表**：`features` 等位图逐位列出，必须有抓包或行为证据；不得按“常见含义”猜。
6. **地址选择**：列出所有 A/AAAA，给出优先级、可达性、IPv6 link-local scope、回退规则。
7. **对照实验**：至少一次真实客户端发现（或 pcap 回放）验证解析结果。
8. **结论分级**：`CONFIRMED` / `INFERRED` / `OPEN`；每条结论附证据位置。

**禁止**：

- 只凭 TXT 键名推断语义；
- 只凭一个车机样本推广到所有车机；
- 把 mDNS 发现成功写成 AirPlay 会话成功；
- 把 `features` 的某一位直接写成“CarPlay 支持”而不做行为验证。

---

## 4. 抽样与观测策略

- 抓包必须**按场景定向**：冷启动宣告、查询/响应、缓存刷新、服务消失、双栈、多车共存。
- 每个场景记录：时间、源/目的地址、接口、TTL、cache-flush、QU 位、响应类型。
- 至少覆盖：
  1. 车机启动后的首次 Announce；
  2. 设备 Browse 查询与车机 Response；
  3. 正常解析 PTR → SRV → TXT → A/AAAA 的完整链；
  4. TTL 递减/刷新；
  5. Goodbye（TTL=0）或服务消失；
  6. IPv4-only、IPv6-only、双栈各至少一次（若环境允许）。
- 采样率如实声明：`n 个服务实例 / m 个抓包`，不得暗示全市场覆盖。

---

## 5. 覆盖要求（12 项）

| # | 要求 | 必须回答的问题 |
|---|---|---|
| 1 | **mDNS 传输与宣告** | 组播地址/端口、TTL、ID、Probe/Announce/Goodbye、cache-flush、known-answer、QU 位、截断与重传是什么？ |
| 2 | **DNS 报文格式** | header/question/answer/authority/additional 如何布局？名称压缩、EDNS0、多问题、截断如何处理？ |
| 3 | **服务类型与浏览** | 车机宣告哪些服务类型？`_airplay._tcp`、`_raop._tcp`、是否存在 `_carplay._tcp` 或其他？PTR 如何浏览？实例名如何转义？ |
| 4 | **SRV 解析** | target、port、priority、weight 的语义？target 是否 `.local`？多条 SRV 如何取舍？端口是否固定？ |
| 5 | **TXT 编码** | 长度前缀 key=value 的边界、空值、重复键、大小写、二进制值、最大长度、未知键如何处理？ |
| 6 | **AirPlay TXT 字段** | 每个实际出现的键是什么含义、什么编码、什么版本？候选键（需逐项取证，不得先验认定）：`features`、`flags`、`model`、`srcvers`、`pk`、`pi`、`gid`、`serialNumber`、`deviceid`、`vv`、`rhd`、`sf`、`md`、`am`、`et`、`ft`、`tp`、`vs`、`ov`、`cs`、`fex` |
| 7 | **设备能力位** | `features` 是几位？十六进制如何分高低 32 位？每一位的含义、是否必需、与 AirPlay/CarPlay 的关系？`flags` 与 `features` 是否不同？ |
| 8 | **地址解析** | A/AAAA 如何取？IPv6 link-local scope 如何处理？IPv4/IPv6 优先级、多个地址、不可达回退、端口与地址的配对关系？ |
| 9 | **服务选择** | 多车/多服务/多实例如何去重、排序、选择？是否要求用户确认？如何避免自动连到错误设备？ |
| 10 | **缓存与生命周期** | TTL、刷新、过期、Goodbye、重新宣告、网络切换、休眠代理（sleep proxy）如何处理？ |
| 11 | **安全边界** | mDNS 无认证、可伪造；TXT `pk`/`pi` 能否作为信任依据？如何防冒充、缓存投毒、错误自动连接？ |
| 12 | **版本与差异** | AirPlay 1/2、CarPlay 与普通 AirPlay、不同车机/固件的字段差异？哪些结论只适用于样本？ |

### 5.1 重点专题

#### A. mDNS 宣告

需要确认并写成规范：

- IPv4 `224.0.0.251:5353`、IPv6 `ff02::fb:5353`；
- 是否使用 DNS ID 0、QR/AA 位、OPCODE；
- Probe（冲突检测）与 Announce（宣告）的次数/间隔；
- cache-flush 位在哪些记录上置位；
- TTL 取值与 Goodbye（TTL=0）；
- 是否响应 unicast query、是否使用 QU 位；
- 多接口/多地址时每个接口如何宣告。

#### B. TXT 记录字段解析

必须给出：

- 线格式：每条 `key=value` 前 1 字节长度；无 NUL 结尾；
- 键大小写、重复键、空值、超长值、非 UTF-8 值；
- 未知键：保留原始字节，不丢弃、不猜测；
- 字段表：键名、出现场景、编码、长度、示例、版本差异、证据帧号；
- 对 `pk`、`pi`、`gid` 等安全相关字段，明确“可用于什么、不可用于什么”。

#### C. 设备能力位

必须产出**逐位表**：

| 位 | mask | 含义 | 证据 | 适用版本 | 状态 |
|---|---|---|---|---|---|

要求：

- `features` 的字符串形式、进制、高低位顺序必须由抓包确认；
- 不得把 `flags`、`sf`、`ft` 等不同字段混成一个位图；
- 每个“支持某能力”的结论必须有行为验证或 Apple 文档依据；
- 无法验证的位写 `OPEN`，不得按常见 AirPlay 位表硬套。

#### D. 服务探测

需要给出：

- Browse 的 PTR 查询名与期望响应；
- 实例名到 SRV/TXT 的关联；
- 多实例、同名冲突、实例改名；
- 车机不响应、响应延迟、部分记录缺失时的行为；
- 何时重试、重试几次、何时放弃。

#### E. 地址解析

需要给出：

- `SRV.target` → A/AAAA 的解析流程；
- `.local` 名称只走 mDNS，不走单播 DNS；
- IPv6 link-local 的 scope id / 接口选择；
- 多 A/AAAA 的排序与回退；
- 地址与 SRV port 的绑定；
- 地址不可达时的重选策略。

---

## 6. 交付物与目录建议

```text
research/protocol/airplay_mdns_discovery.md          # 本任务书
research/protocol/airplay_mdns_discovery/            # 后续 docset（建议）
  analysis/
    00-method-and-environment.md
    01-mdns-transport-and-announce.md
    02-dns-message-format.md
    03-service-types-and-browse.md
    04-srv-and-txt.md
    05-features-and-flags.md
    06-address-resolution.md
    07-selection-and-cache.md
    08-security-boundary.md
    09-runtime-captures.md
    A-conclusions.md
  spec/
    00-scope-and-terms.md
    01-mdns-transport.md
    02-service-discovery.md
    03-txt-schema.md
    04-features-bits.md
    05-address-resolution.md
    06-client-guide.md
    07-conformance-checklist.md
    08-open-items.md
  runtime/
    captures/                          # pcap + decoded JSON + SHA256
    replay/                            # 回放与断言
  reference-impl/
    mdns_discovery.py                  # 解析/选择参考实现
    test_vectors.json
  verify.py
  STATUS.md
  manifest.json
```

要求：

- `reference-impl` 只做**解析与选择**，不实现 AirPlay 配对/媒体；
- `test_vectors.json` 至少覆盖：正常 PTR/SRV/TXT/A/AAAA、缺 TXT、重复键、未知键、IPv6 link-local、多实例、TTL=0；
- `verify.py` 必须能从 pcap 重放出服务图，并与期望 JSON 比对。

---

## 7. 不得声称 / 非目标

以下内容**不属于本阶段**，不得写成已完成：

- AirPlay 配对、加密、密钥交换；
- AirPlay 音频/视频/镜像媒体传输；
- CarPlay 投屏、触摸、音频、输入；
- 蓝牙 iAP2、A2DP、AVRCP；
- “发现到服务”等于“可以连接”；
- “TXT 有某字段”等于“车机支持某能力”；
- 仅凭一个车机样本推断所有车机。

---

## 8. 已知风险与待决

| 风险/待决 | 影响 |
|---|---|
| mDNS 无认证、可伪造 | 可能连到冒充设备；必须用户确认/配对，不得自动信任 |
| TXT `pk`/`pi` 的信任边界不清 | 不能把发现阶段的公钥当已认证身份 |
| IPv6 link-local scope | 地址可用但连接失败；需接口/scope 处理 |
| 多车/多服务同名 | 选择错误设备 |
| Bonjour sleep proxy / 网络隔离 | 服务可见但不可达 |
| 服务类型不确定 | `_airplay._tcp` / `_raop._tcp` / 其他，必须以抓包为准 |
| 版本差异 | `features` 位表可能随 AirPlay 版本变化 |
| 无 24A446 Wi-Fi 抓包 | 现有证据可能来自其他构建/车机，不能替代目标构建 |
| 目标平台 mDNS 栈差异 | 系统解析器行为与自写解析器不同，需实测 |

---

## 9. 验收清单

- [ ] 真实车机 mDNS pcap 已归档，含 SHA256 与抓包环境说明；
- [ ] 能从 pcap 重建 `PTR → SRV → TXT → A/AAAA` 服务图；
- [ ] 所有实际出现的 TXT 键有字段表；未知键保留；
- [ ] `features`/`flags` 有逐位表，未验证位标 `OPEN`；
- [ ] IPv4、IPv6、link-local、多地址、多实例至少各有测试用例；
- [ ] 服务选择有明确规则，不自动连第一个；
- [ ] 安全边界写明：mDNS 发现不等于身份认证；
- [ ] `verify.py` 通过；
- [ ] `STATUS.md` 统计与 `OPEN` 清单完整；
- [ ] 未把“发现成功”写成“AirPlay/CarPlay 可用”。

---

## 10. 一句话

**本阶段只做“在 Wi-Fi 上找到车机的 AirPlay 服务，并把它解析成可连接的地址/端口/能力”；配对、媒体、CarPlay 和蓝牙 iAP2 都不在本阶段。**
