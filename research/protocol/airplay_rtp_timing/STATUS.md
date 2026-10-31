# STATUS — `airplay_rtp_timing`

> 更新时间：2026-10-26（第二轮）。
> 本文件是**进度与证据强度**的声明，不是规范；规范见 `spec/`。

---

## 1. 12 项覆盖状态

| 编号 | 要求 | 状态 | 说明 |
|---|---|---|---|
| RT-01 | RTP 头 | 部分确认 | 12 字节固定头、序列号 `+2`、时间戳 `+4`、PT `+1` 有指令证据；第 0 字节语义、SSRC、marker、padding、CSRC 无证据（`OPEN-RTP-2`、`OPEN-RTP-3`） |
| RT-02 | 扩展头 | 部分确认 | 元素两态 1/4 字节、位布局、自终结、存在性门已确认；通用扫描按实际长度推进，`12+4i` 仅是 indexed helper；Compose双游标及L10数据长度来源已核；外层映射、跨profile语义与长度上限未证（`OPEN-RTP-4`、`OPEN-RTP-5`） |
| RT-03 | 载荷类型 | 部分确认 | 四字符码→PT 8 项表、合并模式改写、接收门集合已确认；编解码器对应与可否协商未证（`OPEN-RTP-6`、`OPEN-RTP-9`） |
| RT-04 | 序列号 | 部分确认 | 16 位大端、回绕、按子包递增已确认；重复/乱序判定未证（`OPEN-RTP-8`） |
| RT-05 | 时间戳 | 部分确认 | 32 位大端、子包时间戳 = 包头 − 14 位差值、末子包不减；接口层是 double、写入时 `fcvtzu` 截断（`A01.8`、`A02.5`、`A05.5`）；单位与回绕未证（`OPEN-CLK-3`、`OPEN-CLK-5`） |
| RT-06 | SSRC/流标识 | OPEN | `pkt+8..11` 有复制，缺生成/验证/会话绑定语义（`OPEN-RTP-2`） |
| RT-07 | NTP 同步 | 部分确认 | 零时间戳提供者几何（64 字节记录、原子索引、double 更新间隔）、24 字节"当前 RTP 时间"输出与 `==2` 状态门、局部首次零结果刷新重算一次、第二次不再检查（`A05.1`–`A05.4`、`A10.3`）；SR/漂移/平滑未证（`OPEN-CLK-4`、`OPEN-RUN-2`） |
| RT-08 | 抖动缓冲（发送缓冲） | 部分确认 | 预留 12 字节头、容量 1460、提交只写时间戳与长度、零长度丢弃、独占获取、读取按帧计算（`A06.1`–`A06.6`）；水位/溢出/池大小未证（`OPEN-JIT-1`–`OPEN-JIT-3`） |
| RT-09 | 丢包处理 | 部分确认 | 维护内部槽位序列号、期望值`(last+1)&0xffff`、不等可走日志但不证明丢包（`A08.1`–`A08.4`）；恢复手段未证（`OPEN-RTP-12`） |
| RT-10 | 统计 | OPEN | 未取证（`OPEN-RUN-2`） |
| RT-11 | 流量控速 | OPEN | 唯一线索是合并数 `obj+0x1c` 与缓冲容量 1460（`OPEN-RTP-7`、`OPEN-JIT-1`） |
| RT-12 | 异常与版本 | OPEN | 仅有内部拷贝长度1481门与缓冲错误码等边界；`+0x5c0` 读写坐标系仍 OPEN（`OPEN-RTP-1`、`OPEN-RTP-8`、`OPEN-RUN-1`） |

合计：**0 已确认 / 8 部分确认 / 4 OPEN**（与 `source/metadata/coverage.json` 一致，`verify.py` C8 校验）。

## 2. 采样覆盖率

| 项 | 值 |
|---|---|
| 基础导出函数 | 22；新增专项audit导出9份（Sender4、Support5） |
| 函数总数（LC_FUNCTION_STARTS） | 11,443 |
| 采样率 | **0.19 %**（定向抽样，不是随机抽样） |
| 已逐条核对指令的函数 | 16（`ComposeRTPPacketWithBBuf`、`ReadExtendedHeader`、`GetExtendedHeaderOfPacket`、`GetSeqNumOfPacket`、`GetNextPacket`、`ReadNewMessage`、`Create`、`getRTPPayloadType`、`GetZeroTimeStamp`、`GetUpdateInterval`、`endpoint_getCurrentRTPTime`、`jitterBuffer_AcquireBuffer`、`jitterBuffer_CommitBuffer`、`jitterBuffer_ReadPackets`、`carAudioStreamHandleDataReady`（装配调用点部分）、`carAudioStream_processOneInputDataMessage`（装配调用点部分）） |

**不构成全栈覆盖。** 未读的函数不参与任何结论；被结论依赖但未读的调用者已在正文标注"未读"。

## 3. 本轮已交付

| 交付物 | 状态 |
|---|---|
| `TASK.md` | 完成（12 项覆盖要求原样继承，新增"无抓包"处置与抓包配方要求） |
| `analysis/00`–`03`、`05`–`11` + `A-conclusions.md` | 已有分析与后续复核；不是全部语义完成的声明 |
| `spec/00`–`09` | 完成（`R-0.x`、`R-1.1`–`R-1.16`、`R-2.1`–`R-2.8`、`R-3.1`–`R-3.9`、`R-4.1`–`R-4.6`、`R-5.x`、`R-6.x`（后两章为缺口章节，仅"未定义"条款）、`R-7.x`、`R-8.x`） |
| `source/`（二进制、元数据、22个基础函数及9份专项audit函数的 `.s`/`.bin`、Ghidra 请求） | 完成 |
| `readable/`（15 个函数的 Ghidra 反编译） | 完成（标 `DECOMPILED_UNREVIEWED`） |
| `reference-impl/rtp_parser.py` + `test_vectors.json` | 完成（自检通过，向量与 `spec/01` 一致） |
| `runtime/captures/README.md`、`runtime/captures/INDEX.md`、`runtime/replay/README.md` | 完成（抓包配方、索引模板、回放计划） |
| `verify.py` | C1–C14；含消息API/调用链/计数闭环，执行输出含15个检查结果 |
| `manifest.json`、`function-index.json` | 完成（由 `firmware/tools/gen-manifest-rtp.py`、`gen-function-index-rtp.py` 生成） |

## 4. 本轮未交付（下一轮）

| 缺口 | 影响 |
|---|---|
| `spec/05`–`spec/06`（统计/控速） | RT-10、RT-11 无条款 |
| `readable/` 仍只覆盖 15 个函数 | 新增 5 个函数（含两个调用者）只有汇编 |
| 音频数据基址B到最终网络包的映射（`OPEN-RTP-10`）、第二条装配路径（`OPEN-RTP-11`） | 发送侧布局无法最终闭合 |
| 零时间戳记录的写入点、`obj+0x50`/`obj+0x98` 赋值者 | `OPEN-CLK-4`、`OPEN-JIT-2`、`OPEN-JIT-3` 无法关闭 |
| 无真实媒体抓包 | `OPEN-RUN-1` 及 4 个 `OPEN-RTP-*` 无法关闭 |

## 5. 能否据此实现（结论）

| 能力 | 结论 |
|---|---|
| 解析一个 AirPlay 媒体包（固定头 + 元素区 + 载荷切分） | **部分可以**：固定头、元素扫描和 PT 门可照写；载荷几何/`+0x5c0` 需按读路径实现并保留 OPEN |
| 生成一个可被本构建接受的媒体包 | **尚不能保证**：可生成合成字段向量；最终线序、第 0 字节、SSRC、加密与协商仍未闭合 |
| 判断"这包有没有元素区" | **可以**：`R-1.9` 的 PT 集合是唯一判据 |
| 缓冲的获取/提交/读取状态机 | **部分可以**：正常路径与参数已核；零提交/错误后的池所有权仍为OPEN-JIT-4，不能保证全部回到空闲 |
| 时钟接口（谁提供时间、何时可用、失败怎么办） | **部分可以**：`spec/02` 给出几何与状态门；换算算法与单位未证 |
| 序列连续性比较 | **可以复现局部比较**：不等不能单独证明网络丢包，重复/乱序/恢复仍缺 |
| 时钟同步 / 抖动缓冲水位 / 控速 / 丢包恢复 | **不可以**：对应覆盖项仍为 `OPEN` 或部分确认 |
| 判定"能正确播放" | **不可以**：本阶段只到"能解析/能打包"，解码与渲染不在范围 |

## 6. 复现

```bash
cd D:\carvex-research
python3 firmware\tools\gen-function-index-rtp.py docs\airplay_rtp_timing
python3 firmware\tools\gen-manifest-rtp.py docs\airplay_rtp_timing
cd docs\airplay_rtp_timing
python3 verify.py
```

期望输出：`failures: 0`。

## 7. 未决项

共**22个未决项、1个已关闭历史项**：未决`OPEN-RTP-1`–`OPEN-RTP-13`、`OPEN-CLK-3`–`OPEN-CLK-5`、`OPEN-JIT-1`–`OPEN-JIT-4`、`OPEN-RUN-1`、`OPEN-RUN-2`；历史`OPEN-RTP-14`已由正常计数写入链关闭，详见`spec/08-open-items.md`。

## 8. 本次语义复核补充

`f_2519c0934.s` 的元素分支还会经过 `0x2519c09d8`：最终解密长度是 `L-(4C-3)-12`，不是 `L-(4C-3)`；无元素分支为 `L-12`。参考算术与原 `.s` 的 8 例有限指令复算已交叉检查，不代表执行完整固件或密码库。另已修正 bit1 未置位返回错误、缺对象返回但未解密、末子包不减时间戳并不证明 D14 为零。1481 比较针对块缓冲拷贝长度，不可当完整线上 MTU。

后续 `analysis/10` 修正内部API与线上规则混淆：ReadPackets八参数且第5参为0，乘积仅低32位；
Commit零提交/错误不显式清持有字段，不能要求调用者free或保证立即重新Acquire；池生命周期新增OPEN-JIT-4。
时钟默认对象语义未解析、第二次换算无再次检查；序列不连续不能单独证明网络丢包，日志门改为原指令0x1e。
内部double/64B布局/一次局部重算不作为独立客户端必须复制的架构。新增C12原切片与分支回归，最新执行含13个检查结果。

Compose复核（analysis/07）：x3是输出包装对象；两条游标分别写连续元素与连续载荷，末尾为当前音频数据而非RTP头。4n+11/10是内部长度出参，不是整包长。C13验证两份原切片、20个锚点、8个局部布局案例和L10截断反例。参考夹具补1B终止元素，缺终止/截断/扫描上限改为拒绝；PT=0x60的模式由调用者传入。相关防御性检查是客户端策略，不声称原固件全部具备。最新全套输出含14个检查结果。

消息API与第二调用者复核（analysis/11）：音频消息头10B，B=M+10、复制到接收I+2后对应I+12；内部两字节差已解释，不再假设I等于网络包。音频AAD入口是M[2:10]共8B；两发送路径均跳过10+g头/元素，h为附加输出预留，具体provider算法仍缺。正常扫描C=n+1，关闭历史OPEN-RTP-14；剩余22项。C14新增9份专项原切片、58个锚点、6个导入符号、12组调用/计数案例及超限路径；最新全套15个检查结果。复现需同仓库相邻FairPlay docset的AirPlaySupport镜像/元数据及原dsc-stubs.txt（均由C14校验），不声称本目录可独立验证这些外部依赖。
