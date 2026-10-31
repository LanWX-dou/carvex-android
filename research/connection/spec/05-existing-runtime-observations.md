# 已有真实记录的重新读取

本章是 `CAPTURE_OTHER` / `LOG_OTHER`，不是24A446运行规范。结果由 [collect_inputs.py](../tools/collect_inputs.py) 重新读取原文件产生，未以旧消息清单作为解析输入。解析算法本身复用了已有脚本，未声称是独立的第二套算法。

## 1. PacketLogger覆盖

| 目录版本标签 | 原文件 | 完整控制消息数 | 必须保留的限制 |
|---|---|---:|---|
| 22H374 | `bluetoothd-hci-2026_10_14-19_48_35.pklg` | 32 | 本解析器无警告不等于全无线流程无遗漏 |
| 22H374 | `bluetoothd-hci-latest.pklg` | 16 | 同上 |
| 23G90 | `bluetoothd-hci-latest.pklg` | 15 | 没有IP视频或显示观察 |
| 21G93 | `bluetoothd-hci-latest.pklg` | 32 | `sequence_gap=4`，`data_without_syn=1`；不能用缺失消息证明不需要该消息 |

合计95条完整消息。每条保留文件哈希、控制消息哈希、原记录偏移/长度、连接、方向、link epoch、session、字段编号与长度。详见 [capture-observations.json](../evidence/capture-observations.json)。数目只衡量解析覆盖，不是95项协议通过。

## 2. 23G90：蓝牙断开后，目标承载出现新iAP会话

原文件：`D:\carvex-research\sysdiagnose\sysdiagnose_2026.10.16_22-11-51+0800_iPhone-OS_iPhone_23G90\crashes_and_spins\accessoryd-packets-2026-10-16-221117.log.ips`。

本次仅抽取方向、消息号、时间和承载标签，不复制身份、网络凭据或认证正文。

| 原行号 | 相对秒数 | 原日志承载 / session | 原事件 |
|---:|---:|---|---|
| 7 / 9 / 11 | 0.131023 / 0.588876 / 0.596245 | Bluetooth Classic / 0x02 | iPod→1d00，Acc→1d01，iPod→1d02 |
| 13–25 | 0.638104–1.704895 | Bluetooth Classic / 0x02 | aa00、aa06、aa00、aa01、aa02、aa03、aa05的实际顺序 |
| 27 / 33 / 35 | 1.866420 / 3.263052 / 16.923698 | Bluetooth Classic / 0x02 | 两次iPod→5702，随后Acc→5703 |
| 37 | 21.237789 | Bluetooth Classic | DETACH |
| 38 | 21.255274 | AirPlay | ATTACH |
| 40 | 21.255873 | AirPlay | DETECT事件 |
| 44 / 46 / 48 | 21.284225 / 21.461878 / 21.462919 | AirPlay / 0x03 | 新的1d00、1d01、1d02 |
| 50–62 | 21.481756–22.034729 | AirPlay / 0x03 | 再次出现aa00、aa06、aa00、aa01、aa02、aa03、aa05 |

可得出的结论：这个日志样本中，蓝牙源与标签为AirPlay的目标承载具有不同session并各有识别/认证消息；“蓝牙断开”不能单独代表整次连接失败；源链路完成不等于目标无需建立自己的状态。

不可得出的结论：每台车都必须以这个顺序运行；24A446具有同一固定session ID；这里的AirPlay承载到底使用哪个IP流封装；车机已显示画面；任何一次捕获到签名就构成完整信任链验证。

两次5702间隔及5703的等待时长只是这一次观察，不是协议定时器规定。上述“先后”也不是未分析调用路径的因果证明。

## 3. 下一份最有价值的运行证据

优先补一份有明确版本和车机的从连接前开始、覆盖最终显示及断线重连的双端时间线。若只能取手机日志，必须另有车机实际画面的观察，并把接收/解密/解码不可见部分标明，不强求修改车机才能采证。

原始凭据保留在本机原记录内；文档只引用必要偏移与脱敏结构。当前不要求用户重做已经完成的音频测试。
