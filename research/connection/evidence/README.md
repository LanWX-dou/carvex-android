# 证据目录说明

证据 JSON 只保留可复核所需的来源、哈希、地址、长度、方向、字段编号/类型以及脱敏观察。它不应成为秘密材料转储。

## 文件

- `baseline.json`：24A446 IPSW、提取镜像与当前 Android 相关文件的哈希和版本来源。
- `capture-observations.json`：旧版 sysdiagnose PacketLogger 的重组消息、原始偏移与警告。不是24A446运行捕获。
- `runtime-log-observations.json`：旧版 accessoryd 文本日志的脱敏承载/消息/时间观察。
- `bootstrap-evidence.json`：蓝牙/iAP2/网络静态函数与原字节来源。
- `iap2-state-evidence.json`：iAP2 链路状态表、Detection、SYN/SYNACK、计数器和计时器分派的原始证据。
- `iap2-startup-initiation.json`：74章首次握手策略；38个函数哈希、33个函数的缓存比对、蓝牙导入、原dyld接口selector、初始状态与收包回复路径，另列IPC/上层超时等未闭合点；没有新协议运行或车机测试。
- `iap2-link-repair-batch.json`：75章手机端三项握手修复、原固件动作地址、源码哈希和测试状态；不表示真实车机兼容或苹果代码执行。
- `identification-contract-evidence.json`：识别字段注册、核心消费、条件组件、required-success和拒绝格式的局部静态证据。
- `identification-power-transport-evidence.json`：15章power与BT/Wireless嵌套组件的新快照，原函数、注册记录、provider与数据块定位。
- `identification-lifecycle-branches.json`：16章初次识别、授权、取消、更新与清理的22个原函数快照；WSL路径`/mnt/d/`对应Windows`D:/`。
- `identification-feature-message-evidence.json`：17章全局feature注册、消息方向/已处理集合、拒绝和实际启动路径；并不表示所有feature validator已审完。
- `identification-core-branches.json`：18章核心字段8个函数的条件/控制转移清单、35项原switch及当前手机快照；统计不是语义覆盖率。
- `identification-lifecycle-batch2.json`：65章实施后的手机源码/测试与最终测试报告哈希、本地执行结果；不替换15–18修改前快照，不是原固件执行或实车通过证据。
- `identification-core-batch3.json`：66章初次核心字段实施后的5份手机源码/测试、原14函数/34注册记录及最终测试报告快照；仅本地有界实施，不是全feature或实车验证。
- `identification-power-provider-context.json`：19章parent/raw transport的原enum表、Bluetooth与AirPlaySender实际producer、构造/getter及ID9的条件；四源文件与19函数局部证据，不证明所有Android入口对应或ID240平台限额。
- `airplay-evidence.json`：AirPlay/APTransport 静态函数与原字节来源。
- `endpoint-fusion-evidence.json`：网络、地址、接口、AdvertiserInfo 与显示配置的局部汇合，以及 Bonjour 解析入口。局部字段核对不证明完整端点身份、选址规则或网络连接。
- `video-evidence.json`：屏幕流、记录头、加密路径和清理函数来源。
- `video-codec-evidence.json`：avcC、帧附件、MaxFPS、原密码虚表/跳板与新对象初始计数；本地逻辑模型不等于执行原编码器。
- `control-wire-evidence.json`：原请求方法/载荷/CSeq、回复关联与状态/等待边界；当前Android源码只作静态差异证据。
- `disconnect-evidence.json`：整会话/单流关闭、异步失效、Suspend/fatal清理、timeout producer和条件consumer；完整重连未证明。
- `control-response-keys.json`：24A446共享缓存 v5 指针链、CFString 值、getter 跳板和局部消费者的来源哈希。
- `version-header-evidence.json`：原 `X-Apple-ProtocolVersion` provider与当前初始／视频／更新SETUP及info的header存在性对照。
- `iap2-version-capability-evidence.json`：链路和控制版本、识别接受条件、第二次SYNACK及CMD的有界审计；不证明音频因果。
- `airplay-version-capability-evidence.json`：对端版本／能力来源与实际安全route消费、缺失信息及未实现路径。
- `build-profile-audit.json`：独立Toyota库对osBuildVersion的音频AAD、最低构建号和显示分支；历史修复与当前风险分开。

## 复核规则

1. JSON 内的源码、固件、缓存路径和哈希是输入身份，不是结论本身。
2. `raw_matches_source` / `raw_equals_extracted_macho` 只证明缓存切片与当前提取镜像字节相同。
3. `frames`、`messages` 的数量只表示解析器得到的样本，不证明请求/响应因果、认证成功或车机显示。
4. `CAPTURE_OTHER` 的目录版本标签没有被当作当前24A446运行证明。
5. 修改引用输入后，若需描述新现状，应另生成并审阅新快照；不能手改历史哈希。14/23/62及本批之前的JSON现在作为修改前证据保留，后续实施和验证见[63](../spec/63-alignment-batch1.md)，不将其冒充修改后现状。

12/22/24/31分册还可运行 `tools/verify_batch_evidence.py`（相对于本项目根）复核源镜像与函数切片。该只读检查不覆盖全部指针链、反编译语义或实车行为；通过不将PARTIAL升级为完成。

14/23/62相关四份证据可运行 `tools/verify_profile_audit.py` 核对JSON中声明的文件身份及有文件偏移的cache切片；函数语义及现场触发条件仍需独立审阅。
