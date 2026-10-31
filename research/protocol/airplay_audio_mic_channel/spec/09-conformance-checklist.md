# 09 一致性检查表

#### R-9.1 每条断言必须能追溯到条款或 OPEN
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`verify.py` C2/C3、`analysis/00-method-and-environment.md` §0.2

验收报告里每一行必须是下列之一：

- `R-x.y` + 判定（通过/不通过/未测）；
- `OPEN-xxx-n` + 阻塞原因；
- 明确写「本端策略，非协议要求」。

「应该没问题」「和某开源实现一致」都不接受。

#### R-9.2 判定口径
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`research/protocol/airplay_audio_mic_channel.md` §1

| 判定 | 含义 |
|---|---|
| 通过（静态） | 固定镜像/原指令和数据流支持限定路径规则；不表示真实运行成功 |
| 通过（合成） | 用 `test_vectors.json` 或本端构造的包，断言成立 |
| 通过（抓包） | 用真实 pcap 回放，断言成立 |
| 通过（真车） | 与目标车机联调，抓包 + 日志双证据 |
| 未测 | 没跑；不得当「通过」 |
| 阻塞 | 依赖的 `OPEN-*` 未关闭 |

#### R-9.3 必须项（L0–L2）
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`R-1.2`、`R-3.3`、`R-4.2`、`R-8.1`

- [ ] 首字节 `0x7F`/`0xC0` 被拒；`0xE4` 被接受为 PT 100
- [ ] PT 101/105 被拒（`PT_NOT_RECEIVABLE`）
- [ ] RED单/双/四块、缺终止符和截断检查正确；冗余length总和不能超过明文数据区，主块取余量
- [ ] 块 seq 回绕（`outer=2`, 4 块 → `FFFF,0,1,2`）正确
- [ ] 时间戳回绕（`outer=1`, `delta=5` → `FFFFFFFC`）正确
- [ ] 记录切片：`ciphertext/tag/nonce` 长度与偏移正确，空密文被拒
- [ ] AAD入口为消息M[2:10]；标准RTP检查与内部M编解码分开，未假定网络→M映射
- [ ] CSRC/扩展/填充边界与负span均有负例；显式选择本地尾布局，不自动降级
- [ ] 未将未经认证密文按RED块切出并送解码器
- [ ] SETUP 请求含 `R-2.2` 要求的字段，且不含多余条件字段
- [ ] audioFormat为整数ID，不使用本地CODEC/rate字符串；ID→codec/ASBD有独立映射依据
- [ ] 按spec11检查多位集合拒绝、bit63保留、失败不改输出；区分ASBD bits和可选out bits
- [ ] 基础/传输/HAL描述分离：PCM flags OR2/清2，压缩HAL转换不覆盖传输F/packet
- [ ] spf按整数处理，有效正有限输入的pps向零截断；48000/512反例得到93
- [ ] 不把本机burst偏好缺失默认200混为接收端缺键默认；区分两种SETUP构造上下文
- [ ] SETUP 回复 `type` 不匹配时失败（不静默接受）

#### R-9.4 必须项（L3 麦克风）
级别：MUST ｜ 证据：CONFIRMED ｜ 依据：`R-6.1`、`R-6.2`、`R-6.3`

- [ ] SETUP 发之前，本机端口已 bind 成功且值非 0
- [ ] 请求含 `input=true` 与 `dataPort=<本机端口>`
- [ ] 回调对 `gen`/`gred`/`auxo`/`axrd` 直接丢弃
- [ ] `main/mred/oovc/ovrd` 均能入队（即使暂未解密）
- [ ] handler 创建失败时该流失败退出，不继续
- [ ] 暂存溢出行为已定义并可观测

#### R-9.5 必须项（L4 收尾）
级别：MUST ｜ 证据：INFERRED ｜ 依据：`R-7.2`、`R-7.3`、`R-7.4`

- [ ] 停流发出 `tdwn`，载荷含 `streams[0].type`
- [ ] 重复 teardown 不再发送且不崩
- [ ] 断链场景不把状态写成「车机已确认」
- [ ] 重连后核验streamID与密钥有效性，不盲复用失效状态或对同key无条件清零nonce

#### R-9.6 未测项必须显式标注
级别：MUST NOT ｜ 证据：CONFIRMED ｜ 依据：`A08.1`、`OPEN-RUNTIME-1`

本阶段没有音频抓包，「真车」一栏全部是未测。验收报告不得整表填「通过」，
也不得用「多项已通过」暗示真车验证。

#### R-9.7 回归频率
级别：SHOULD ｜ 证据：CONFIRMED ｜ 依据：`reference-impl/gen_test_vectors.py`

改 `reference-impl/` 任一文件后必须：重新生成向量 → 跑 `verify.py` → 把 `test_vectors.json`
的 diff 贴进变更说明。`verify.py` 失败时不得提交。
