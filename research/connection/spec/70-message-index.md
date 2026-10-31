# 连接消息与记录索引（有界版）

这不是“所有 CarPlay 消息的完整标准表”。它只列本轮已经有原函数、原始记录或当前实现可核对的连接/视频相关对象。字段未闭合时写 `OPEN`，不拿参数编号、名称或一次捕获填补缺口。

证据级别：`S/ASM24`=24A446 原函数/指令；`CAPTURE_OTHER`=旧版本原始记录；`ANDROID_NOW`=当前 Android 源码快照；`OPEN`=尚未证明。

## 1. 链路和 iAP2 外层

| 对象/消息 | 方向 | 承载 | 已知结构/字段 | 生产/消费与成功含义 | 证据与边界 |
|---|---|---|---|---|---|
| Detection | 原发送回调；运行时发起方向 OPEN | 当前 iAP2 承载字节流 | `FF550200EE10`，发送长度6；完整角色、重发和世代规则 OPEN | 局部事件 `0x17` 选择 SendDetect；attach 本身不直接发送 | `S/ASM24` [11](11-iap2-state-machine.md)；后邻长度/填充不属于载荷，不把 Detection 当每承载必经 |
| SYN/SYNACK | 双向 | RFCOMM/iAP2 | 基本载荷布局、版本分支、seq/ack及局部计时器已核对；完整profile/session约束 OPEN | 协商块提交和Connected回调是本地检查点，仍需同链路运行证据 | `S/ASM24 B02/B03`、[11](11-iap2-state-machine.md)；SendSYNACK与ResendSYNACK计数分开 |
| iAP2 record header | 双向 | RFCOMM/iAP2 | flags、seq、ack、session、payload长度及校验；完整端序/所有控制bit OPEN | 由链路层重组后交业务层 | `S/ASM24 B02`；PacketLogger消息表只保留脱敏长度/偏移 |
| `0x1D00` | 手机→车机 | 当前控制 session | 识别请求；payload字段完整schema OPEN | 发送成功后本地进入识别中间状态 | `S/ASM24 B04`；不等于识别已接受 |
| `0x1D01` | 车机→手机 | 当前控制 session | 34注册项，12项required检查成功回调集合；所有嵌套/feature组合仍OPEN | 仅identification state1/3接收；字段出现不等于通过 | `S/ASM24 B23`、[12](12-identification-contract.md)；运行观察另标版本 |
| `0x1D02` | 手机→车机 | 当前控制 session | 识别接受/回应；完整TLV OPEN | 发送成功才使 identification state=6 | `S/ASM24 B05`；本地状态不替代车机收到 |
| `0x1D03` | 手机→车机 | 当前控制 session | 普通拒绝为同字段ID空TLV；参数6/7可带BE16拒绝消息列表，不附臆造reason字节 | 局部提交成功→state3可再次收1D01；不是所有失败都必须断链 | `S/ASM24` [12](12-identification-contract.md)；完整更新/取消仍OPEN |

## 2. 配件认证消息

| 对象/消息 | 方向 | 已知字段/条件 | 成功/拒绝判据 | 证据与限制 |
|---|---|---|---|---|
| `0xAA00` | 手机→车机 | 认证开始；session version/继承状态可能改变参数 | 进入当前认证路线，不等于已验证 | `S/ASM24 B07`；不能断言每次都重做 |
| `0xAA01` | 车机→手机 | 证书数据进入证书处理器 | 解析成功不是信任链通过 | `S/ASM24 B23`；禁止导出证书正文 |
| `0xAA02` | 手机→车机 | 当前nonce bytes及长度非零 | 以当前认证上下文发送；不能复用旧nonce | `S/ASM24 B08`；算法/长度全表 OPEN |
| `0xAA03` | 车机→手机 | 签名响应；与保存证书、当前nonce绑定 | 验签结果决定后续，不是“有签名就成功” | `S/ASM24 B10`；抓包只记哈希/长度 |
| `0xAA04` / `0xAA05` | 手机→车机 | 失败/成功完成消息 | 本地auth state=1/2；对端是否收到需独立证据 | `S/ASM24 B09`；不能手工跳到state2 |
| 业务准入门 | — | auth state=2、identification state=6、消息已由车机声明 | 三条件满足才进入普通业务 | `S/ASM24 B06`；引导消息有例外 |

## 3. 无线可用性、网络和会话启动

| 对象/消息 | 方向 | 已知字段 | 不是它的含义 | 证据 |
|---|---|---|---|---|
| `0x4300` | 手机→车机 | 嵌套组：wired/wireless/theme availability及条件标识 | 不是“无线连接已完成” | `S/ASM24 B14`；需能力/平台对象存在 |
| `0x4301` | 车机→手机 | 组0 usbIP；组1 ssid/pass/channel/wifiIP/security；port、deviceID、pubKey、srcVer、sdkVer、asset、mutualAuth等；嵌套TLV | 不是手机可随意仿造的回应；字段组合下游仍OPEN | `S/ASM24 B12/B17–B20`；方向必须保持 |
| `0x5702` | 手机→车机 | 本函数发送无附加参数；须先通过声明的message-ID门 | 不是收到后就有网络 | `S/ASM24 B15`；条件消息 |
| `0x5703` | 车机→手机 | BSSID Data（本handler不强制6字节）、SSID/passphrase、securityType U8、channel U8；ID5/6未消费 | 只代表配置交给平台；不含AirPlay IP/port、不代表关联成功 | `S/ASM24 B16/B21`；凭据不写入日志 |
| Wi-Fi平台交接 | 手机平台内部 | SSID/安全类型/接口/地址/路由 | 不能用iAP2 handler return=1替代系统关联 | `S/ASM24 B16/B21`；完整下游 OPEN |
| 内部 StartSessionEvent | APTransport helper 内部 | 网络/接口、会话提供者地址、端口、AdvertiserInfo、可选SessionHostInfo、display configuration | 不是线上消息，不证明已connect；helper完整角色绑定仍OPEN | [21](21-endpoint-fusion.md)；不能由字段名推断手机/车机方向 |

## 4. AirPlay控制对象

| 方法/对象 | 方向 | 已知结构/条件 | 当前文档判据 |
|---|---|---|---|
| `_carplay-ctrl._tcp`发布/`connect`邀请 | 车机→手机（邀请） | URL命令与`AirPlay-Receiver-Device-ID` header；方法/ID/回调成功需分开 | HTTP 200不等于后续控制TCP已经建立；`S/ASM24 AP-01–03` |
| 配对/验证路由 | 双向 | `/pair-setup`、`/pair-verify`等独立路径；能力选择 | 不以路由名推断密码学机制；`S/ASM24 AP-04/AP-07–10` |
| 独立认证路由 | 双向 | `/auth-setup`、`/fp-setup`及其它类型有不同载荷形态 | `AuthenticationType`是内部选择，不直接等于SETUP `et`；`S/ASM24 AP-04/AP-07/AP-24/25` |
| `SETUP`（控制） | 手机→车机 | binary plist；可含身份、update、timing、features、条件加密字段；sourceVersion由版本生产者决定 | 200及body可解析仍不等于控制/事件/视频就绪；`S/ASM24 AP-12–14` |
| `GET /info` /内嵌`info` | 手机→车机或响应内 | 可能独立、验证阶段附带或SETUP响应内嵌；字段消费按条件 | 不得强制所有路径独立GET；`S/ASM24 AP-11/AP-12/AP-19` |
| `eventPort` | 车机→手机响应字段 | 非零时建立事件连接；零/缺失可走不建独立事件流分支 | 非零连接失败与无事件路径分别报告；`S/ASM24 AP-14/AP-15` |
| `RECORD` | 手机→车机 | 4CC `rcrd`映射；Stage2按启动位和原始响应键 `skipRecord`（通过 `CFDictionaryGetInt64`）条件 | 不是固定必经消息；键名/局部读取已由原共享缓存复核，但全生产者/跨会话语义仍OPEN；`S/ASM24 AP-04/AP-16`、`evidence/control-response-keys.json` |
| `TEARDOWN` | 手机→车机 | `streams`仅非NULL数组才带；`teardownType`受UseConnectionSharing控制；无control可本地return0 | 注销/最终返回不等peer ACK；正常/单流/Suspend/fatal分开，见[24](24-disconnect-reconnect.md) |
| CSeq / 响应关联 | 手机控制请求及当前响应 | u32旧值以十进制写CSeq；内部递增；对象上下文/token另参与响应归属 | 首值、所有重连与底层CSeq过滤仍OPEN；100…599是响应分派，不是成功，2xx与body/字段另校验；[22](22-control-wire-contract.md) |

## 5. 屏幕流和视频记录

| 对象 | 方向/承载 | 已知结构 | 成功证据 |
|---|---|---|---|
| 屏幕 stream SETUP | 手机控制→车机控制 | 一次调用的响应`streams`恰一项且返回type等于请求type；ID/端口动态 | 响应结构有效并建立独立数据transport；`S/ASM24 AP-21/V02–V04` |
| `NetworkPortData` | 车机响应→手机本地transport创建 | 数据端口来自当前响应；不能与控制端口混用 | 实际数据socket已连；`S/ASM24 V03/V04` |
| 配置记录 | 手机→车机视频数据 | 128字节头，type=1；特定avc1路径正文来自avcC；本配置构造器不无条件添加帧tag | 配置实际写出且对应同一流；`S/ASM24 V05/V06`、[31](31-video-codec-contract.md) |
| 帧记录 | 手机→车机视频数据 | 128字节头，type=0；先配置后帧的局部顺序；cryptor按能力选路 | 车机接收/解密/解码及实际显示，不能仅凭构造/写出；`S/ASM24 V05/V07/V08` |
| 同步附件/现代cryptor | 手机本地生产→帧头/加密 | bit4来自首个合法NotSync布尔值反值；新对象计数0，完整128B头AAD，flag0附加16B | bit4不证明IDR；尾段可能另消耗nonce；不外推legacy/UDP，见[31](31-video-codec-contract.md) |
| 首帧/持续显示 | 车机外部结果 | 本索引无 wire message ID | 车机画面出现本次唯一内容且持续变化；当前 OPEN |

## 6. 已观察但非24A446规范的旧记录

以下仅是 `CAPTURE_OTHER` / `LOG_OTHER`：

| 记录 | 观察 |
|---|---|
| 21G93/22H374/23G90 PacketLogger | 95条完整控制消息，方向、偏移、长度、哈希见 `evidence/capture-observations.json`；21G93保留sequence gap警告 |
| 23G90 accessoryd 文本 | Bluetooth Classic 先出现1d00/1d01/1d02、AA事务、5702/5703；随后BT DETACH，AirPlay承载ATTACH并再次出现1d00/1d01/1d02、AA事务，详见 `05-existing-runtime-observations.md` |
| 负证据限制 | 这些记录没有证明24A446、IP视频、车机解码或画面显示；缺失消息可能由捕获边界/过滤造成 |

## 7. 面向实现的消息处理检查

每条线上消息处理器至少保存：连接世代、承载、方向、消息ID、原始长度、解析状态、声明能力、前置状态、响应/错误及下一预期状态。未知参数保留原始长度和安全哈希，不把它静默转成零值；拒绝时记录消费者实际理由，不只记录“解析失败”。

完整字段闭合前，禁止把本表直接生成代码常量、自动重放脚本或车机兼容保证。
