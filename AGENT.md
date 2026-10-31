# AGENT.md

[中文](AGENT.md) | [English](AGENT.en.md)

本文件面向后续接手本项目的代理和开发者。任何协议实现、排障或代码修改都必须先阅读本文件。涉及 Android 时，同时阅读 [`android/AGENT.md`](android/AGENT.md)。

## 0. 阅读顺序

1. 本文件。
2. 涉及 Android 代码或构建时，读 [`android/AGENT.md`](android/AGENT.md)。
3. 受影响 docset 的 `README.md` 与相关 `spec/` 章节。
4. `docs/architecture.md`、`docs/workflows.md`、`docs/status.md`。

不要先看当前 Android 实现。它是候选实现，不是证据。

## 1. 项目目标与基线

项目目标不是只研究 CarPlay，而是建立手机与车机之间的多协议互联层，覆盖 CarPlay、
HiCar、CarLife、ICCOA 以及 CarWith、CAR+ 等生态。CarPlay 是当前首个、也是证据链
最完整的协议；不同协议按各自证据推进，不能互相套用结论。

对 CarPlay 路径，核心规则是：

> 以原始 iPhone IPSW 固件为唯一发送端行为基准，尽可能逐字段、逐时序、逐状态地复刻
> 固件行为，使实现能够与支持 CarPlay 的车机互操作。

CarPlay 基线固件：

```text
firmware/ipsw/iPhone18,1_27.0.1_24A446_Restore.ipsw
```

版本必须从 IPSW 的 `BuildManifest.plist` 读取，不能靠文件名推断。

当前 CarPlay 研究链路：

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

实现策略：

- 以固件复现为主；兼容性增强必须有固件或设备证据，不能变成按车型/配置表切换的分支。
- 目标是在不依赖车型配置文件的情况下，通过协议栈框架、协商字段和能力位适配广泛车机。
- Android 采用分模组设计；新增协议应新增 `protocol-*` 模块并实现 `protocol-api`，通过 `bridge`、`platform-android` 和 `host-*` 接入，不修改 CarPlay 主路径。
- 宿主/投屏实现也通过独立 `host-*` 适配器接入；新增小米 CarWith、OPPO CAR+ 等生态不修改协议模块。

## 2. 仓库与研究目录

根仓库通过 git submodule 引用 `android/` 和 `firmware/`：

| 目录 | 引用 | 内容 |
|---|---|---|
| `carvex-research/`（本目录） | `iamr0s/carvex-carplay-research` | 研究文档、连接分析、项目级说明和 README 捐赠码 |
| `android/` | submodule `iamr0s/carvex-android` | **CarVeX**：多协议车机互联的 Android 实现，当前以 CarPlay 为主；包含协议栈、会话编排和五品牌宿主 |
| `firmware/` | submodule `iamr0s/carvex-ios-firmware` | CarPlay 固件证据、提取物、反编译文本、分析工具和 setup；原始 IPSW 与车机固件不入库 |

`research/` 有两个入口：

- `research/protocol/`：多协议研究 docset。当前以 CarPlay/iPhone 发送端为主，按协议层拆分（RFCOMM、iAP2、Identification/Authentication、Wi-Fi handoff、AirPlay、FairPlay、video、audio/mic、input、RTP timing 等）；其他协议按同样结构新增。
- `research/connection/`：连接生命周期、失败恢复、跨阶段时序和实车差异。

目录：

```text
D:\carvex-research\
├─ AGENT.md / AGENT.en.md        工作区规则
├─ README.md / README.en.md      入口
├─ assets/donation/              README 捐赠码
├─ docs/                         架构、流程、状态、决策
├─ research/
│  ├─ protocol/                  手机端协议研究 docset
│  └─ connection/                连接生命周期与失败恢复
├─ firmware/                     git submodule carvex-ios-firmware
└─ android/                      git submodule carvex-android，CarVeX 实现
```

### `docs/`

只放项目级说明，不存放协议规范正文。

```text
docs/
├─ README.md
├─ architecture.md
├─ workflows.md
├─ status.md
└─ decisions/
```

### `research/protocol/`

手机端协议研究。正式、可验证的 docset，单个 docset 通常包含：

```text
research/protocol/<docset>/
├─ spec/         规范性协议正文
├─ analysis/     逐函数分析和推理
├─ source/       原始字节和汇编切片
├─ readable/     自动反编译输出
├─ runtime/      抓包、日志和运行样本
├─ tools/        本 docset 专用工具
└─ verify.py     结构与证据验证
```

现有 docset 覆盖：Bluetooth RFCOMM、iAP2 link、Identification / Authentication /
control session、Wi-Fi bootstrap、mDNS、AirPlay control、FairPlay、iAP2 tunnel、
Video、Audio / microphone、Input / business lifecycle、RTP timing、跨层排障。

### `research/connection/`

以连接生命周期、失败恢复和跨阶段时序为中心的专项研究。入口是其 `README.md`，
其中记录最新证据状态；章节链接位于 `research/connection/spec/`。

### `firmware/`

git submodule `carvex-ios-firmware`。入库内容：

- `ipsw/SOURCE.md`、`SHA256SUMS.partial`：原始 IPSW 的来源、大小和 SHA256。
- `extracted/24A446/binaries`、`components`、`headers`：从 IPSW 提取的关键二进制和头文件。
- `analysis` 顶层的汇总、关键 JSON、汇编与专项分析；按函数拆分的切片保留本地。
- `tools` 与 `setup` 中的脚本和配置。

不入库：原始 `*.ipsw`、`extracted/*/images`、`extracted/*/dyld`、`headunits/`、
Ghidra 工程/缓存、下载归档。原始 IPSW 通过 README 中的下载入口和 SHA256 获取，
不随仓库分发。

### `android/`

**CarVeX**，多协议车机互联的 Android 实现，当前以 CarPlay 为主。它是 git submodule
`iamr0s/carvex-android`，必须能单独构建。模块职责与构建规则见
[`android/AGENT.md`](android/AGENT.md)。

## 3. 协议依据：CarPlay 以固件为准，其他协议分别取证

对 CarPlay 路径，不能根据已有 Android 代码、旧文档、字符串名称、selector 名称、
自动反编译输出或其他产品实现来反推 Apple 行为。

其他协议（HiCar、CarLife、ICCOA、CarWith、CAR+ 等）不能套用 iPhone 固件结论；
各自以对应的手机端实现、公开规范、抓包和车机行为为准，并保持同样的证据分级。

### 证据等级

- `CONFIRMED`：原固件字节、汇编或调用链已经闭合。
- `INFERRED`：有证据支持，但仍有未读取的分支或边界。
- `OPEN`：证据不足，禁止凭经验补全。

### 允许作为证据

- IPSW 中的原始 Mach-O、dyld cache 和系统组件。
- 对原始字节的反汇编。
- 与目标行为对应的函数地址、控制流和数据流。
- 车机固件中的接收、ACK、状态机、锁和清理路径。
- 与固件版本绑定的运行日志和抓包。

### 只能作为索引

- 旧 Markdown 文档。
- 函数名、selector、字符串和自动反编译 C。
- Android 当前实现。
- 其他产品的行为。

自动反编译输出只能辅助阅读。影响字段、顺序、超时、状态转换或错误分支时，必须回到
原始字节和汇编。

### 状态机来自协议栈，不来自配置

要实现的是一个不依赖车型或配置表的状态机：状态、事件、转移条件、超时和清理路径都
从固件的协议栈与框架路径推导，包括消息分派、回调、定时器和错误分支。

配置只能提供运行输入，例如身份、地址、证书、编解码参数和传输能力。配置不能：

- 按车型或配置选择另一套状态机；
- 跳过声明、认证、会话同步或清理；
- 改变状态转移顺序、事件归属或超时语义；
- 把“某车型能连”当作分支条件。

车型差异必须通过协商字段、能力位和实际消息表达，而不是配置分支。未知或未闭合的
路径保持 `OPEN`。

## 4. 修改协议代码的规则

修改前必须：

1. 运行 `git status`，检查现有未提交改动。
2. 将要修改的每个文件备份到 `local-backups/<YYYY-MM-DD>-<主题>/`。
3. 不回滚、不覆盖、不格式化用户无关的已有修改。

每次生产修改必须说明：

1. 对应的 IPSW 二进制地址或代码分支。
2. 当前实现为什么不同。
3. 新实现如何与固件对齐。
4. 使用哪些测试验证。
5. 是否经过实车验证。

禁止：

- 按车型或按车机型号硬编码分支。
- 盲试固定延迟。
- 无条件重发。
- 跳过声明或认证检查。
- 用第三方实现替代固件证据。
- 在没有证据时关闭 `OPEN` 项。
- 基于对 Apple 行为的猜测新增功能。

签名密钥库与口令在 Android 仓库中按设计公开；除此之外，不要提交 `local.properties`、设备私有数据或其他凭据。
`android/app/src/main/assets/` 下的三张捐赠二维码是有意内置的应用资源；
删除或改名必须同时更新应用、两份 README 和 `LocalVideoDisplay.kt`。

## 5. 调试流程

### 5.1 先定位第一个断点阶段

按顺序检查：

```text
BLUETOOTH
  -> DETECT
  -> SYN / SYNACK / ACK
  -> AUTH
  -> IDENTIFICATION
  -> WIFI HANDOFF
  -> ENDPOINT DISCOVERY
  -> AIRPLAY CONTROL
  -> RTSP SETUP
  -> VIDEO / AUDIO / INPUT
```

不要只看最后一条异常。找到第一个偏离固件预期的消息、状态或线程。

### 5.2 日志必须包含

- APK versionCode 和构建类型
- session ID
- 目标蓝牙地址
- 连接发起方向
- 实际协商的 link/control 版本
- 完整 session 表
- SYN/SYNACK/ACK 序号
- 最后发送成功消息
- 下一条预期消息
- 首个超时或资源关闭点
- 实际使用的 Network、接口和地址来源

### 5.3 调试命令

Android 连接日志：

```powershell
adb devices
adb logcat -c
adb logcat -v time > carvex-log.txt
```

蓝牙状态：

```powershell
adb shell dumpsys bluetooth_manager > bluetooth-state.txt
```

网络状态：

```powershell
adb shell dumpsys connectivity > connectivity-state.txt
adb shell ip addr
adb shell ip route
```

### 5.4 日志判断规则

- 链路 ACK 不等于业务消息已被接受。
- `1D00` ACK 不等于车机会发送 `1D01`。
- RFCOMM 连接成功不等于 iAP 服务已经建立。
- 收到 SYN 不等于链路同步完成。
- 收到 `5703` 不等于 Wi-Fi 已连接。
- 收到 `4301` 不等于 AirPlay 端点可达。
- 收到 SETUP 200 不等于首帧成功。

## 6. 研究与验证命令

### 6.1 外部工具链

仓库不是完全自包含。移动目录后，以下系统级依赖和本机配置仍需重新准备。

| 工具 / 依赖 | 用途 | 是否随仓库移动 |
|---|---|---|
| Git | 版本、源码哈希、Gradle 版本号 | 否 |
| Python 3.10+ | 固件研究、验证器和工具脚本 | 否 |
| `capstone==5.0.7` | ARM64 反汇编验证 | 否 |
| `unicorn==2.1.4` | 有界 ARM64 执行验证 | 否 |
| `cryptography==41.0.7` | 验证器加密辅助 | 否 |
| `lzfse>=0.3.0` | sysdiagnose logarchive 解析（可选） | 否 |
| WSL2 Ubuntu 24.04 | 固件工具和 Python 验证环境 | 否 |
| Java 21 JDK | Ghidra 12.1.4 | 否 |
| Android Studio JBR / JDK 17+ | Gradle / Kotlin 编译 | 否 |
| Android SDK 37 + build-tools 36.0.0 | `compileSdk 37` 与打包 | 否 |
| `adb` | 设备日志、蓝牙和网络状态 | 否 |
| Gradle Wrapper | Android 构建 | 是；仍依赖 Java |
| Ghidra 12.1.4 | 固件反编译 | 是；位于 `firmware/tools/ghidra` |
| `ipsw` CLI | IPSW、dyld、Mach-O 查询 | 归档在仓库；当前 WSL 安装在 `/usr/local/bin` |
| `apfs-fuse` / `apfsutil` | APFS 镜像访问 | 否；由 `install-linux-tools.sh` 构建安装 |
| `ffmpeg`、`tshark`、`tcpdump` | 音视频样本与抓包验证 | 否；可选，缺失时报告 SKIP |

本机配置，不应作为仓库内容迁移：

- `android/local.properties` 中的 `sdk.dir`
- `JAVA_HOME`
- `ANDROID_HOME` / `ANDROID_SDK_ROOT`
- `GHIDRA_HOME`
- `GHIDRA_ANALYZE_HEADLESS`

安装 Python 依赖：

```powershell
cd D:\carvex-research
python -m pip install -r requirements.txt
```

WSL 工具链安装：

```bash
cd /mnt/d/carvex-research/firmware/setup
sudo bash install-linux-tools.sh
```

加载 Ghidra 环境：

```bash
source /mnt/d/carvex-research/firmware/setup/ghidra-env.sh
```

移动项目目录后必须重新检查：`local.properties`、Android SDK 路径、Java 版本、WSL 路径、
`ipsw` 是否在 `PATH`、Ghidra 路径、Python 包版本。

### 6.2 固件 docset

完整验证：

```powershell
cd D:\carvex-research
python -B firmware/tools/verify-all.py
```

单个或部分 docset：

```powershell
python -B firmware/tools/verify-all.py --only bluetooth_rfcomm
python -B firmware/tools/verify-all.py --only iap2_link_establish iap2_control_session
```

直接运行 docset 验证器：

```powershell
cd D:\carvex-research\research\protocol\bluetooth_rfcomm
python -B verify.py
```

`verify-all.py` 会区分 `PASS`、`SKIP`、`FAIL`。`SKIP` 表示缺少依赖，不是通过；
不得把跳过的证据检查报告成已验证。

### 6.3 Android

```powershell
cd D:\carvex-research\android
.\gradlew.bat :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin
```

改动相关模块时追加：

```powershell
.\gradlew.bat :core:testDebugUnitTest :bridge:testDebugUnitTest
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest
```

CI 还会运行 `:pcm-core:test`、`:host-api:test`、五个 flavor 的单测、`lintRelease` 和
`assembleRelease`。本地验证至少要覆盖所有被改动行为的模块。

## 7. 实车测试流程

1. 确认当前代码已达到可验证阶段。
2. 先提交代码，确保测试版本可追溯。
3. 用户自行打包和安装，除非用户明确要求代打包。
4. 一次只验证一个假设。
5. 从连接开始保留完整日志，不只保留末尾异常。
6. 记录是否手动断开、车机是否残留旧会话、是否重开车机。
7. 不因一次成功就关闭兼容性问题。

实车结果分为：

```text
PASS      完整达到预期阶段
PARTIAL   到达部分阶段，存在明确第一断点
FAIL      未达到目标阶段
OPEN      证据不足
```

## 8. 当前重点

当前连接实现需要继续以固件为准核对：

- RFCOMM 方向仲裁。
- SYN/SYNACK session 表协商。
- iAP2 Identification 启动条件。
- 控制 CSM 的 session 路由。
- Wi-Fi handoff 和迟到端点。
- 正常断开、资源清理和重连代际隔离。

多协议扩展只保留 `protocol-*` / `host-*` 模块边界；HiCar、CarLife、ICCOA 等未实现前，
不得在代码、UI 或文档中宣称已支持。

任何“其他实现可以连接”的现象只能用于提出候选假设，不能直接成为生产修改依据。

## 9. 文档维护

- 入口文档是四对：`README.md` / `README.en.md`、`AGENT.md` / `AGENT.en.md`、
  `android/README.md` / `README.en.md`、`android/AGENT.md` / `AGENT.en.md`。
  中文文件为主；任何规则变化必须在同一次修改中同步两种语言，不能只改一边。
- `README.md` 用于入门，`AGENT.md` 是规范文件。协议结论放在 `research/`，不要写进
  README。
- 路径、命令、模块、flavor、包名或签名规则变化时，同步更新两个仓库的 README 与 AGENT
  （中英各一份）。
- 持久的架构或流程决策写入 `docs/decisions/NNNN-title.md`，包含背景、决策、后果和
  证据链接。新增文档类型时更新 `docs/README.md`。
- 保持单一事实来源。不要把完整协议规范复制进 `docs/` 或 README，链接到对应 docset。
- 根仓库、`android/` 和 `firmware/` 各自维护 `assets/donation/` 目录，供本仓库 README 引用；
  `android/` 另在 `app/src/main/assets/` 内置一份供 `LocalVideoDisplay.kt` 使用。
  不得跨仓库引用图片。改名或删除必须同步更新副本和所有 README。捐赠不得成为任何功能的门槛。
