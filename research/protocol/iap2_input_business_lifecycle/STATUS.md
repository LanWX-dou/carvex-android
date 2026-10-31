# STATUS — iap2_input_business_lifecycle

更新：2026-10-26。目标是设备/iPhone端，不是车机接收器。
目标镜像24A446/accessoryd，4,330,752B，SHA256：
`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

## 当前能支持的范围

已对局部处理器、消息方向和生命周期进行实质纠错，但不是完整互通规范。
299/8706（3.43%）是定向切片率，不是语义覆盖率。93条R编号；
coverage的12项仍为2已确认、9部分确认、1 OPEN，不因测试通过自动升级。
21个历史OPEN：8关闭、6缩小、7保留；关闭范围必须结合原证据读，
尤其SUS/ACK包型关闭不包含真实恢复、订阅保留。

## 本轮原指令纠错

详见 [analysis/12](analysis/12-lifecycle-and-empty-param-audit.md)。

- 恢复ACK：控制字节0x40；完整帧头偏移5/6为序号/确认号，7为0。旧6/7写法错误。
- HandleSuspend/Resume事件0x1b/0x1c；主动发送通知7/8是另一层，不混用。
- `0x100067f3c`的cset lo表示总长<5；合法TLV下即4字节空参数，旧>=5结论反了。
- NowPlaying参数0/2子项、参数1多数子项为空；参数1子项0x11为U32/8B。
- 导航参数0为可重复U16组件项，1–5为空值options标记，不是变长子组；非空/重复标记失败。
- required=0仍参与any；all由返回值给出，any写出参。0x5204另检查出站门；局部返回0不代表全栈无日志。
- 识别由设备1d00、车机1d01、设备1d02推进；版本决定识别/认证先后。
  不再要求设备上报全部ID，集合完整填充链仍待核；状态2/6仅为固件内部枚举。
- 设备不能为恢复自行发车机订阅消息0x5000；恢复有效性未证时不放行业务。
- 参考状态机默认DISCONNECTED；链路就绪进入NEGOTIATING，READY明确三项门。
  RESUME不直接开启定时器；epoch拒绝旧连接/旧挂起周期回调。
- 全域清理与资源所有权是本地安全不变量；统一入口、不同状态数量或非引用计数架构均可。

## 验证

HID追加复核见 [analysis/13](analysis/13-hid-dataflow-audit.md)：两个U16是独立字典值，
Start描述符与识别组件身份分开；6805字段顺序以跳表/block/selector数据流补证；
Stop仅清状态位并保留字典项，公共组件校验不证明Start前置门。
`OPEN-INP-2`保留为历史关闭编号，不删除审计轨迹或把真实互通一起算作关闭。

NowPlaying追加复核见 [analysis/14](analysis/14-nowplaying-dataflow-audit.md)：
参数0媒体项属性、1播放属性，关闭OPEN-NP-1；5003时间/队列索引/窗口起点三条去向已解，
0xffffffff自动窗口哨兵与订阅子项门已核。Start先移除旧订阅再替换数组，
但PlaybackQueueList清理与实际客户端计数未闭合（OPEN-NP-4缩小）。
撤回“ObjC/顺序必须运行确认”的笼统分类，继续静态追消费者；不以缺抓包否定已证格式。

```powershell
python -B firmware/tools/gen-lifecycle-manifest.py research/protocol/iap2_input_business_lifecycle
python -B research/protocol/iap2_input_business_lifecycle/verify.py
```

C1–C18：结构、索引与哈希；7组编码向量及4个长度案例；空TLV/U32/整数越界/未知类型反例；
C14执行22条迁移、16种READY门组合、旧epoch与失败/取消/断开行为；
C16固定镜像SHA、重反汇编12个完整切片、检查31个指令锚点及6个跳表入口。
C17另核5个HID完整切片、4个原镜像区间、42个锚点、9个跳表入口与selector字符串。
C18另核3个NowPlaying完整切片、76个锚点、6个真实导入绑定、7个block指针、
8个selector及订阅键/动态类/计数日志字符串。
这些检查不执行真实认证、平台副作用或网络握手，不证明全部字段语义。

## 仍需推进

1. 核对识别集合填充链与方向转换；导航options业务含义及具体profile要求。
2. 深入HID描述符、触摸编码、NowPlaying字段/订阅计数、平台引用计数边界；
   静态能核的问题继续读代码，不统一推给抓包。
3. 停车台架采集输入、媒体订阅、导航、挂起恢复/断开重连，按实际覆盖关闭OPEN；
   不承诺“一份抓包能关闭大半”。
4. 真实仿iPhone客户端的投屏、音频、输入、恢复仍未验证；现有23G90日志不含本组业务消息。

原始反编译文件保持机器输出标记，结论须点回审计与汇编，不把整份C声称为已人工确认。
