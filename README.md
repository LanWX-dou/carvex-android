# CarVeX — 车机互联协议研究与实现

[中文](README.md) | [English](README.en.md)

> 目标是打通各类车机互联协议与各类手机之间的连接，包括 CarPlay、HiCar、CarLife、ICCOA、CarWith、CAR+ 等；**CarPlay 是当前首个按 iPhone 固件逐字段复现的协议**。
>
> 状态：研究预览。CarPlay 路径最完整；其他协议是扩展方向，未实现的部分保持 `OPEN`。不声称真实车机互通。

## 为什么做这件事

时代仿佛越开越阔，也越收越紧。各家以协议为藩篱，以生态为绳缆，口称开放，实则圈地；用户被高高捧起，又常被用完即弃，如祭祀中的刍狗。

我们想把互通重新落回协议本身：不靠某家的配置表，不把用户拴进某个生态，而是按协议栈、协商字段和能力位，让手机与车机尽可能广泛地连接。

> “这些墙很有意思。起初你恨它，后来你习惯它；日子够久，你会发现自己离不开它。这就叫体制化。”
>
> —— 瑞德，《肖申克的救赎》

## 捐赠

如果这个项目对你有帮助，欢迎自愿捐赠以示感谢。捐赠不构成任何支持承诺。

<p align="center">
  <img src="assets/donation/alipay.jpg" width="200" alt="支付宝">
  <img src="assets/donation/wxpay.jpg" width="200" alt="微信支付">
  <img src="assets/donation/binance.jpg" width="200" alt="Binance Pay">
</p>

<p align="center">支付宝 · 微信支付 · Binance Pay</p>

## 这是什么

本项目不是单一的 CarPlay 研究，而是面向多协议车机互联：目标是让 Android 手机与支持 CarPlay、HiCar、CarLife、ICCOA 以及 CarWith、CAR+ 等生态的车机建立连接。CarPlay 是第一个按 iPhone 固件复现的协议；其他协议按同一套模块边界逐步接入。

根仓库通过 Git submodule 引用两个独立仓库：

1. `carvex-research`（本目录，根仓库 `iamr0s/carvex-carplay-research`）：研究文档与连接分析。
2. `android/`（git submodule，仓库 `iamr0s/carvex-android`）：**CarVeX**，多协议车机互联的 Android 实现，当前以 CarPlay 为主。
3. `firmware/`（git submodule，仓库 `iamr0s/carvex-ios-firmware`）：CarPlay 固件证据、提取物、反编译文本与分析工具；原始 IPSW 和车机固件不入库。

`research/` 分为两部分：`research/protocol/` 是手机端协议研究，`research/connection/` 是连接生命周期与失败恢复。

设计目标：以协议栈框架和协商字段驱动，不靠按车型或配置表切换状态机来适配车机。CarPlay 作为第一个协议，尽量逐字段、逐时序复现 iPhone 固件，并在有证据的前提下做兼容性增强；其他协议按同样的模块边界接入。Android 侧采用分模组设计，协议实现、平台适配、会话编排和宿主接入彼此解耦；新增 HiCar、CarLife、ICCOA 等协议时新增独立 protocol 模块，而不是改写现有 CarPlay 实现。宿主/投屏侧同样分模组，小米 CarWith、OPPO CAR+ 等生态通过 `host-*` 适配器接入，不改动协议栈。

当前已展开的 CarPlay 研究链路：

```text
Bluetooth RFCOMM
  -> iAP2 link
  -> Identification / Authentication
  -> Wi-Fi handoff
  -> AirPlay control
  -> RTSP SETUP
  -> video / audio / microphone
  -> normal teardown and reconnect
```

## 状态与边界

- 这是研究型工作区，不是完成品。本地测试只证明被检查的条件，不证明与真实车机互通。
- 状态机和事件由协议栈框架与协商字段推导，不依赖按车型或配置表切换的状态机。
- `CONFIRMED`、`INFERRED`、`OPEN` 严格分开；证据不足时保持 `OPEN`，不用经验补全。
- CarPlay 是当前主要实现；HiCar、CarLife、ICCOA 等尚未实现，只保留模块边界，未完成部分保持 `OPEN`。
- 不修改车机固件，也不修改第三方接收端软件。
- 本项目与 Apple、百度及任何手机、汽车、车机厂商均无隶属关系。CarPlay 是 Apple Inc. 的商标。

## 仓库结构

| 路径 | Git 引用 | 用途 |
|---|---|---|
| 根目录 | 根仓库 `iamr0s/carvex-carplay-research` | 研究文档、连接分析、项目说明和 README 捐赠码 |
| `android/` | submodule `iamr0s/carvex-android` | **CarVeX**：多协议车机互联的 Android 实现，当前以 CarPlay 为主 |
| `firmware/` | submodule `iamr0s/carvex-ios-firmware` | CarPlay 固件证据、提取物、反编译文本与分析工具 |
| `research/protocol/` | 随根仓库 | 多协议研究 docset，当前以 CarPlay/iPhone 发送端为主 |
| `research/connection/` | 随根仓库 | 连接生命周期、失败恢复与跨阶段时序 |
| `docs/` | 随根仓库 | 项目级架构、流程、状态与决策记录 |
| `assets/donation/` | 随根仓库 | README 使用的捐赠二维码 |
| `firmware/ipsw/` | `carvex-ios-firmware` | 仅 `SOURCE.md` 与校验和；IPSW 通过下载入口获取 |
| `firmware/extracted/` | `carvex-ios-firmware` | 从 IPSW 提取的 Mach-O、组件和头文件 |
| `firmware/analysis/` | `carvex-ios-firmware` | 汇总、关键 JSON 与汇编；按函数切片和 Ghidra 缓存不入库 |
| `firmware/tools/`、`firmware/setup/` | `carvex-ios-firmware` | 解包、反汇编、符号、验证工具与环境配置 |
| `local-backups/` | 不提交 | 协议或文档修改前的本机快照 |

## CarPlay 证据链路

```text
firmware/ipsw
  -> firmware/extracted
  -> firmware/analysis
  -> research/protocol/ 与 research/connection/
  -> android/
```

原始固件是权威来源。解包与分析产物必须能由原始文件重复生成。旧笔记、函数名、
selector 和自动反编译输出只能作为索引，不能当作协议证明。

## 证据规则

- 协议行为必须追溯到原始固件字节与指令。
- `CONFIRMED`、`INFERRED`、`OPEN` 严格分开。只有 `CONFIRMED` 可以关闭协议项；
  `INFERRED` 的修改必须继续显式保留未确定部分。
- 第三方实现只能提出候选假设，不能成为依据。
- 没有匹配的设备侧证据，不得声称真实互通。
- 不修改车机固件或外部接收端软件。

## 快速开始

固件 docset，在 WSL/Linux 中：

```bash
cd /mnt/d/carvex-research
python3 -m pip install -r requirements.txt
python3 -B firmware/tools/verify-all.py
```

单个或部分 docset：

```bash
python3 -B firmware/tools/verify-all.py --only iap2_link_establish iap2_control_session
cd research/protocol/bluetooth_rfcomm && python3 -B verify.py
```

Android 构建，在 Windows 中：

```powershell
cd D:\carvex-research\android
.\gradlew.bat :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin
```

Android 构建使用 `android/.signing/` 中随仓库公开的签名材料，详见
[`android/README.md`](android/README.md#构建) 与
[`android/AGENT.md`](android/AGENT.md)。缺少签名材料会在配置阶段直接失败，
这是有意设计，不做静默降级。

## 文档导航

| 文档 | 用途 |
|---|---|
| [`AGENT.md`](AGENT.md) | 强制流程、证据规则、调试与验证工作流 |
| [`android/AGENT.md`](android/AGENT.md) | Android 专属模块、签名、flavor 与测试规则 |
| [`docs/README.md`](docs/README.md) | 项目文档索引 |
| [`docs/architecture.md`](docs/architecture.md) | 工作区分层与归属边界 |
| [`docs/workflows.md`](docs/workflows.md) | 研究与 Android 修改流程 |
| [`docs/status.md`](docs/status.md) | 当前结构与优先事项 |
| [`research/protocol/README.md`](research/protocol/README.md) | docset 结构与覆盖范围 |
| [`research/connection/README.md`](research/connection/README.md) | 最新连接研究、证据与开放项 |
| [`android/README.md`](android/README.md) | 应用功能、构建、签名、品牌与状态 |

持久的架构或流程决策写入 `docs/decisions/`，按编号归档。协议规范放在 `research/`，
不写进本 README。

## 许可

GNU General Public License v3.0，详见 [`LICENSE`](LICENSE)。

本项目与 Apple、百度及任何手机、汽车、车机厂商无隶属关系。CarPlay 是 Apple Inc. 的商标。
