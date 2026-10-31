# 抓包：捕获过滤与显示过滤分开

依据E-TSHARK/E-BPF/E-DUMPCAP/E-BT/E-TCP/E-RTSP-FILTER。本版没有在本机执行过滤器编译，
verify会报告SKIP；下列语法已核官方资料。先在目标工具版本上验证，再正式采集。

## 可复制表达式

| 目的 | 捕获过滤（BPF，`-f`） | 显示过滤（Wireshark/TShark `-Y`） |
|---|---|---|
| mDNS端口流量 | `udp port 5353` | `udp.port == 5353` |
| 初始IP排查（受控台架，范围较宽） | `ip or ip6 or arp` | `ip or ipv6 or arp` |
| 蓝牙RFCOMM | 不提供通用BPF；需HCI/btsnoop等合适捕获源 | `btrfcomm` |
| TCP复位 | 不建议预先只抓复位帧 | `tcp.flags.reset == 1` |
| 已解码RTSP | 不使用`rtsp`作BPF | `rtsp` |
| TCP重传线索 | 不建议预先只抓重传 | `tcp.analysis.retransmission` |

`rtsp`/`rtp`显示为空不等于没有控制/媒体：内容可能已加密、未选解码器，或并不是该协议格式。
端口5353也只是端口选择，不保证每个载荷都是合法mDNS。

## 根据本次协商生成端点过滤

`reference-impl/diagnostic.py` 的`filters(peer, tcp_ports, udp_ports)`只生成表达式，
不打开设备；参数必须取自当前连接发现/协商结果。无默认7000或6000–7000。
TCP列表应含控制/屏幕/事件等实际TCP端点，UDP列表含实际音频/麦克风/时钟端点；
方向和端口映射分开登记，不能将一条音频端口规则推广全媒体。

```powershell
# 此例仅演示语法，地址/端口是假数据，务必替换为本次协商值
python -B research/protocol/iap2_airplay_debug_troubleshoot/reference-impl/diagnostic.py --peer 192.0.2.10 --tcp 7123 49152 --udp 51000 51001
```

输出同时含mDNS端口与该peer双向端口，括号避免`or/and`优先级歧义。
IPv6 link-local的scope由实际捕获接口确定；地址字符串不塞入`%接口`来猜BPF语法。
端口过滤会漏其他端点、地址切换和部分分片；首次未知故障可在受控环境短时宽抓，
事后收窄。不要对公共网络无边界采集。

## Windows/多接口操作模板（需用户选择真实接口）

```powershell
tshark -D
dumpcap -D
# 将下面接口号替换为上面的真实编号；新文件名，避免覆盖已有证据
dumpcap -i 1 -i 2 -s 0 -a duration:60 -w case-new.pcapng
tshark -r case-new.pcapng -Y 'udp.port == 5353'
tshark -r case-new.pcapng -Y 'tcp.flags.reset == 1'
```

以上多接口模板在台架短时不加捕获过滤，60秒是本地采集长度，不是协议超时。
pcapng保留接口信息；同时保存工具版本、链路类型、时钟源与drop统计。
只需单接口时仅保留一个`-i`；选择错误接口会丢失IPv6 scope或切网后的流量。
`-s 0`不代表抓包无隐私风险。捕获文件可能包含屏幕、媒体、标识符和配对材料，不能直接上传。

蓝牙不一定出现在Windows捕获接口列表。若只有RFCOMM应用字节流日志，
明确“未观察HCI/RFCOMM帧头”，不凭该日志诊断底层PN/MSC/FCS；不要人为添加假链路头。

## 正式采集前验证

先检查 `tshark -v`、`tshark -G protocols`，再对一份获授权的已存在pcap运行显示过滤；
检查选出/未选出帧号是否符合预期。BPF可用`dumpcap -i <真实接口> -d -f '<表达式>'`
编译检查（打印代码，不启动采集）。`<...>`为占位，不能原样粘贴。
pcap链路类型不同则分别验证，不能将以太网测试结果当作HCI可用证明。
任何过滤器验证失败都保留stderr与工具版本，不把空输出当成功捕获。
