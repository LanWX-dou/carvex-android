# 00 方法与环境

> 本文件只定义**怎么取证**、**证据在哪**、**采了多少**。协议结论在 `01`–`05`，汇总在 `A-conclusions.md`。

## 00.1 目标二进制

| 项 | 值 | 来源 |
|---|---|---|
| 文件 | `AirPlaySender` | `source/firmware/AirPlaySender` |
| 构建内路径 | `/System/Library/PrivateFrameworks/AirPlaySender.framework/AirPlaySender` | 提取清单 |
| 大小 | 4,397,312 B | `source/metadata/summary.json` |
| SHA256 | `304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f` | 本阶段重算 |
| LC_UUID | `2d49b39b-fb65-366b-9ab5-6995e5e0febf` | `summary.json` |
| `__TEXT` | `0x251996000`–`0x251c7a000` | `segments.json` |
| `__text` | `0x251997a78`–`0x251bdbb08` | `sections.json` |
| 函数起点 | 11,443 | LC_FUNCTION_STARTS |
| 符号数 | 14,277 | `symbols.json` |

## 00.2 证据分级

| 级别 | 含义 | 允许出现在 |
|---|---|---|
| `BYTES` | 固件原始字节 + 指令地址可直接复核 | `R-*` 的 `CONFIRMED` |
| `FLOW` | 调用点/参数传递可复核，但被调函数未读或语义未定 | `R-*` 的 `INFERRED` |
| `OBS` | 字符串/日志/符号名等旁证，不能单独支撑语义 | 只能作为线索 |
| `OPEN` | 本阶段证据不足 | `spec/08` 与 `coverage.json` |

**硬规则**：Ghidra 反编译文本（`readable/`）永远不是依据；引用它时必须同时给出 `source/asm/` 的指令地址。

## 00.3 抽样与覆盖率

本阶段精读 23 个函数（`source/metadata/selection.json`），集中在该二进制的五个子系统：

| 子系统 | 函数数 | 代表地址 |
|---|---|---|
| 屏幕流对象与建流 | 4 | `0x251b40be8`、`0x251aeda20`、`0x251b371ac`、`0x251b3db28` |
| SETUP 请求/响应 | 2 | `0x2519bbf24`、`0x251a9f364` |
| 记录头/配置/加密 | 8 | `0x2519b0014`、`0x251b43fcc`、`0x2519b508c`、`0x2519bffc8`、`0x2519bfecc`、`0x251a356c8`、`0x251aa97a0`、`0x251a9fcec` |
| AVC 封装与协商 | 4 | `0x251a773c4`、`0x251a77178`、`0x251a76374`、`0x251a779d8` |
| 控制/恢复 | 5 | `0x251b438e8`、`0x251b43140`、`0x251b42e34`、`0x251a761d8`、`0x251b443cc` |

采样率 **23 / 11,443 ≈ 0.20 %**。这是**主题定向抽样**，不构成全栈覆盖；凡结论依赖未读函数，正文显式标注"未读，结论仅基于调用点"。

## 00.4 工具链

| 步骤 | 命令 | 产物 |
|---|---|---|
| 取元数据 | `python3 firmware/tools/macho-meta.py <bin> <outdir>` | `summary/sections/segments/symbols/function-starts` |
| 导出汇编 | `python3 firmware/tools/export-asm.py <bin> <meta> source/metadata/selection.json source/asm/airplaysender` | `f_<addr>.s/.bin` + `index.json` |
| 建清单 | `python3 tools/manifest.py` | `manifest.json` |
| 自校验 | `python3 verify.py` | 通过/失败 |

`export-asm.py` 的区间规则：`end = 下一个 LC_FUNCTION_STARTS 起点`；因此 `.bin` 恰好是"该函数到下一个函数起点"的原始切片，`verify.py` 会逐字节比对。

## 00.5 术语

| 术语 | 本阶段含义 |
|---|---|
| 屏幕流 / screen stream | 承载屏幕画面的一条媒体流；CarPlay 的主画面走它 |
| 记录 / record | 屏幕流上的一个自描述单元：128 字节头 + 载荷 |
| 帧记录 | 记录类型 0：一帧编码数据 |
| 配置记录 | 记录类型 1：几何/变换/时间基准等显示配置 |
| 关键帧 / IDR | 可独立解码的帧；本阶段只证明"存在关键帧标志与请求命令"，不证明码流内 NAL 类型 |
| 协商数据 / negotiation blob | AVC 媒体流协商器生成的二进制串，随建流传递 |
| 呈现模式 / presentation mode | 同一显示可有多种呈现配置（例如 HDR/非 HDR） |

## 00.6 与既有材料的关系

| 材料 | 用法 |
|---|---|
| `firmware/analysis/24A446/screen-*`、`AirPlaySender-*.ghidra.c` | **线索**：给了候选函数与字段名；本阶段逐条重新取证后才引用 |
| `firmware/analysis/decompiler-cache/24A446/AirPlaySender/934ec850a9ab7623f1d8/` | 反编译缓存；已用源哈希 `304b8a4a…` 复核与目标二进制一致 |
| `research/protocol/airplay_video_channel.md`（旧任务书） | 范围参考；接收端口径已在本阶段 §0.1 修正 |
| `sysdiagnose/…23G90` | 仅旁证；构建不同，不能确认 24A446 常量 |

## 00.7 本阶段明确不做的

1. 不做 AirPlay 控制面（RTSP/HTTP 请求响应）本身；
2. 不做音频、麦克风、输入事件；
3. 不做 FairPlay 算法与密钥体系（只写"视频帧加密的调用位置与输入输出形状"）；
4. 不做对端解码器实现，只写它对输入的约束；
5. 不引入任何外部实现作为证据。

## 本章依据

| 结论 | 说明 |
|---|---|
| `A00.1` | 二进制身份（大小/哈希/UUID/函数数） |
| `A00.2` | 地址窗口：`__TEXT`/`__text` 边界 |
| `A00.3` | 两个屏幕流变体在同一二进制内共存 |
| `A00.4` | 代码中不出现 `h264` 字面量，视频编码以 `AVC` 命名 |
| `A00.5` | 采样 18/11,443 的主题定向性质 |
