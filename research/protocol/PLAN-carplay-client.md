# CarPlay 手机侧客户端 — 工作计划与交接（2026-10-27）


本文件记录本轮讨论形成的范围、决策与阶段计划。新会话先读本文件 + `CLAUDE.md` + `README.md` + `STRUCTURE.md`，不依赖聊天历史。

## 1. 目标与角色

- **交付**：指导“手机侧（模拟 iPhone）”实现的文档与验收方法。
- **角色**：手机 = 设备侧客户端；车机 = 预期对端。车机镜像只作对照样本，不作为实现目标。
- **不做**：不声称已互通；不把车机行为当成手机规范；不在没有证据时关闭 `OPEN`。

## 2. 输入与位置

| 输入 | 建议位置 | 说明 |
|---|---|---|
| iPhone IPSW（24A446） | `firmware/ipsw/` | 附 `SOURCE.md`：来源、版本、SHA256 |
| 车机镜像 | `firmware/headunits/<厂商_车型>/` | 每台附 `SOURCE.md`：车型、年款、版本、格式、SHA256 |
| 现有 13 套 docset | `research/protocol/` | 作为待核对的结论库，不直接当事实 |
| 目标车机 / 抓包 / 认证材料 | 待定 | 决定 E 阶段能否进行 |

## 3. 已定决策

1. **不全量重跑**：重跑同一管线只能证明产物未变；用独立方法定向重推，或从 IPSW/车机镜像重新提取比对。
2. **IPSW 是“手机行为全集”的来源**：消息集、状态机、协商与回退、默认值、边界处理。
3. **车机镜像是样本，不是全集**：用于验证解析器、发现厂商差异、做回归与兼容矩阵。
4. **目标是行为等价**：遇到未见过的车机，按 iPhone 的默认分支、拒绝与降级规则行动。
5. **保留 OPEN**：静态能证的标 `CONFIRMED`/`INFERRED`；动态选择与真实互通留 `OPEN`。
6. **不改写前人结论**：保留 `A`/`R` 编号；冲突走 `C-x` 记录，新增独立审计层。
7. **文档形态**：新建 `research/protocol/carplay_client/` 分章维护，另生成一份单文件汇总。

## 4. 阶段与完成标准

| 阶段 | 内容 | 完成标准 | 产物 |
|---|---|---|---|
| A 基线 | IPSW 与车机镜像的哈希、构建/设备校验、解包、CarPlay 相关组件盘点；与现有副本比对 | 能回答“底座是否可追溯、提取是否一致”；差异有清单 | `firmware/**/SOURCE.md`、`research/protocol/audit-2026-10-27/` |
| B 对端矩阵 | 每台车机：SDP / RFCOMM / iAP2 消息集 / 认证 / `0x4301` / Wi-Fi / mDNS / RTSP / 媒体 / 输入 | 每格有证据路径与状态；跨车型差异成表 | `research/protocol/headunit_peers/` |
| C 双侧对账 | 手机文档说 X，车机代码做 Y；冲突逐条记录并重推 | 差异清单闭环：修正、降级或保留 OPEN | `research/protocol/audit-2026-10-27/` |
| D 实现指南 | 手机侧分章规范：架构、字节布局、状态机、消息表、参考代码、验收判据 | L0–L3 可照做；L4/媒体/输入标注停止条件 | `research/protocol/carplay_client/` + 汇总 |
| E 台架 | 真实车机 + wire log + pcap + 合法 FairPlay/MFi | 至少一次“握手 → setup → 首帧 → 输入 → 重连”记录 | 验收报告 |

## 5. 各阶段的第一步

### A
1. 算 IPSW 与镜像 SHA256，核对 build/device/版本。
2. 用 `ipsw` 提取 `accessoryd`、`AirPlaySender`、`AirPlaySupport`、`CarKit` 等；与 `firmware/extracted` 和 docset 副本比对。
3. 识别每份车机镜像格式（squashfs / ext4 / UBI / QNX / Android），记录所需工具。
4. 盘点 CarPlay 相关组件（AirPlay receiver、iAP2 accessory stack、mDNS、RTSP、codec、HID）。

### B
先做手机行为清单（消息、状态机、协商、默认值），再做车机画像；不要从车机反推手机规范。

### C
只审被实现依赖的结论；抽样 20–30 条高风险项，优先“纯文字 CONFIRMED”。

### D
按 `STRUCTURE.md` 建新 docset：`TASK.md`、`STATUS.md`、`spec/`、`analysis/`、`verify.py`、`manifest.json`，并登记到 `research/protocol/README.md`。

## 6. 环境

- WSL Ubuntu 24.04，venv：`/root/.venvs/carplay-phone`（capstone 5.0.7、unicorn 2.1.4）。
- Ghidra 12.1.4 + Java 21：`firmware/tools/ghidra`。
- `ipsw` CLI：`/usr/local/bin/ipsw`。
- 已装：`unsquashfs`、`7z`、`file`、`tar`、`unzip`、`debugfs`；缺 `binwalk`、`simg2img`、`qemu-img`、UBI/QNX 工具，按镜像格式再装。
- 磁盘：D 盘约 120 GB 可用；建议一次处理一台镜像。

## 7. 会话划分

- **本会话**：范围、结构、信任策略（已完成）。
- **每个阶段一个新会话**，使用全新上下文（不要继承本对话），开场让新会话先读：
  1. `CLAUDE.md`
  2. `research/protocol/README.md`
  3. `research/protocol/STRUCTURE.md`
  4. 本文件
  5. 对应 docset 的 `STATUS.md`
- 阶段之间用仓库文件和 `research/protocol/audit-2026-10-27/` 交接，不靠聊天记忆。

## 8. 约束

- 不绕过车机镜像的加密/签名；无法解包的分区记录为限制。
- 不把 FairPlay/MFi 私有材料写入仓库或日志。
- 不修改 `source/`、`readable/` 后不重建 manifest。
- 不把“静态代码存在该分支”写成“该车机会走该分支”。
- 任何“完整实现文档”的说法都必须附带验收等级与 OPEN 清单。
