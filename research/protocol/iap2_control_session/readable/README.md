# readable — 反编译产物（未复核）

本目录是 Ghidra 12.1.4 headless 对 `source/asm/accessoryd/*.bin` 的**自动反编译输出**，用于阅读加速，**不是证据**。

## 约定

- 文件名 `f_<地址>.ghidra.c` / `f_<地址>.json`，地址为 16 进制、不带 `0x`。
- 每个 `.c` 首部固定包含：原始地址、原始代码 SHA256、源镜像 SHA256，以及一行免责声明。
- 每个 `.json` 记录同一次导出的元信息（函数名、入口、导出时间、脚本版本）。

## 使用规则

| 允许 | 不允许 |
|---|---|
| 用它快速定位分支、字符串、调用关系 | 用它的类型/签名当结论 |
| 用它对照 `.s` 逐条核对 | 引用它的变量名当字段名 |
| 用它发现"这里有故事"再去读汇编 | 用它证明任何协议行为 |

## 已知失真

本镜像里大量函数被编译器折叠成 `_OUTLINED_FUNCTION_*` 片段（无符号名、无独立参数约定）。Ghidra 遇到这些片段会**丢失参数传递关系**，表现为：

- 调用点参数显示为空（例如 `iap2_CarPlayStartSession` 里的 `iAP2MsgSend*` 调用）；
- 变量被标成 `extraout_x8`、`uVar1` 之类；
- 控制流出现不可能的 `SBORROW`/`csel` 组合。

凡 `analysis/` 里标为 `OPEN` 且原因写作"被 outlined 片段打散"的，指的就是这种情况。**这类函数必须读 `.s`，不能读 `.c`。**

## 规模

| 项 | 值 |
|---|---|
| 反编译函数数 | 199（与 `source/metadata/selection.json` 一一对应）|
| 文件数 | 199 × 2 |
| 生成器 | `firmware/tools/ghidra-scripts/ExportDecomp.java` |
| 工程 | `firmware/analysis/24A446/iap2-link/project`（程序 `accessoryd`）|
| 运行环境 | WSL（工程由 root 创建，Windows 侧打开会报 `NotOwnerException`）|

`verify.py` 的 C3 类检查会确认：每个导出函数都有 `.c` 与 `.json`，且 `.c` 头部地址与请求一致。
