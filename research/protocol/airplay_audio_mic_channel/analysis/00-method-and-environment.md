# 00 方法与环境

## 0.1 阶段目标

本阶段只回答「AirPlay 音频/麦克风通道」：有几路音频、各自方向与用途、载荷怎么打包、
RED 怎么冗余、解密在哪一步、麦克风怎么上行、怎么混音/闪避、怎么 TEARDOWN。

不回答（见 `research/protocol/airplay_audio_mic_channel.md` §7）：视频、FairPlay 算法、RTP 抖动缓冲与
时钟同步、AirPlay 控制面、iAP2 分片。

## 0.2 证据分级

| 级别 | 含义 | 本文档的判定方式 |
|---|---|---|
| `CONFIRMED` | 本阶段**重新读取原始字节并复核**的结论 | 必须给出可复算的镜像地址；读者可用同一份 dyld 共享缓存复现 |
| `INFERRED` | 沿用前序冻结规则，本阶段未重跑 | 给出前序规则号 + 地址；重跑前不得升级为 `CONFIRMED` |
| `OPEN` | 无证据，登记 `OPEN-*` | 禁止用「常见实现」「公开资料」填补 |

`CONFIRMED` 只表示「在本阶段证据范围内可复核」，**不等于真机互通**。本阶段没有音频抓包
（见 `08-runtime-captures.md`），所以任何「车机会这样回」的断言都是 `INFERRED` 或 `OPEN`。

## 0.3 素材

| 素材 | 路径 | 用法 |
|---|---|---|
| 目标固件 | `firmware/extracted/24A446/dyld/dyld_shared_cache_arm64e*` | AirPlaySender / APTransport 等镜像的唯一原始字节来源 |
| 反汇编缓存 | `firmware/analysis/decompiler-cache/24A446/` | 只作线索；引用前以原始字节复核 |
| 前序冻结规则 | `firmware/analysis/24A446/audio-*/rules.json` 等 | 标 `INFERRED` 留痕，不直接升级 |
| 蓝牙抓包 | `research/protocol/iap2_control_session/runtime/23G90-bt-classic-2026-10-16.md` | 只证明 iAP2/BT 侧；**不含 AirPlay RTP** |
| 公开标准 | RFC 3550（RTP）、RFC 2198（RED）、RFC 8439（ChaCha20-Poly1305） | 只用于解释字段语义，不作为「车机实现」证据 |

## 0.4 复核工具

初版使用一次性脚本读共享缓存（历史命令形状）：

```text
python3 _probe.py hex  0xADDR LEN     # 原始字节
python3 _probe.py dis  0xADDR N       # Capstone 反汇编
python3 _probe.py cstr 0xADDR         # C 字符串
python3 _probe.py cftable 0xADDR N    # CFString 常量槽表（指针 -> CFString -> 文本）
```

地址 → 文件偏移由 `dyld_cache_header`（映射表 + 子缓存）换算，读的是原始缓存，不重写缓存。
当前可复现入口为verify.py以及tools/verify-config-fields.py、tools/verify-format-map.py；
前者C11核原字段/默认值，后者C12执行原格式转换函数和有界调用者块。依赖/固定哈希/仿真边界见analysis10/11。
原指令CPU仿真与本地合成向量、原生平台执行、真实车机结果分开记录。

## 0.5 已复核范围（本轮）

下表为初版重读范围；新增原指令复核以analysis09/10/11及C10–C12为准，不把后续补证继续降为INFERRED：

| 片段 | 地址 | 结论 |
|---|---|---|
| RTP 接收准入 + PT 表 | `0x24fdad414..0x24fdad464`、`0x24fe44bc0` | `A02.1`、`A02.2` |
| 发送侧 PT 标签 | `0x24fdabdf4..0x24fdabf3c` | `A02.2` |
| RED 头位域 | `0x251ace454..0x251ace49c` | `A03.1`、`A03.2` |
| AAD取消息M[2:10]，内部复制后为I[4:12]，不自动对应网络包 | `0x226e68af0..0x226e68b38` | `A04.3`、`A09.1` |
| 10 字节 body 头 helper | `0x226e689e0..0x226e68a14` | `A02.5` |
| 麦克风接收白名单与异步块 | `0x2519c0b88..0x2519c0c78` | `A06.1`、`A06.2` |
| SETUP 音频字段键名表 | `0x2693e7c00..0x2693e7d58` | `A02.3` |
| SETUP 音频字段写入 | `0x2519be828..0x2519be958` | `A02.4`、`A02.6` |
| `audioType=="telephony"` 分支 | `0x27612e7b0`、`0x2519be878..0x2519be89c` | `A02.7` |

## 0.6 没有做的事（避免误读为覆盖）

- 没有执行任何固件代码，没有开 Ghidra 反编译本阶段新函数；
- 没有抓 AirPlay 的 RTP/RTCP，也没有车机侧日志；
- 没有验证 `0x4301`（CarPlay 启动）与音频流的先后关系；
- 没有采样 A 系列以外的镜像（`AirPlaySender` 的 3901 个函数只用到十来个片段）。

旧阶段约12个函数片段为主题抽样；“3901为全量函数数”未建立统一计数口径，不能用于全栈覆盖率。
当前Sender导出metadata为11,443个函数起点，也不是与片段数直接可比的覆盖度。
本轮追加analysis09，复用并重跑RTP原切片/消息坐标回归；无需一次性_probe.py即可复现该部分。
