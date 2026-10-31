# analysis/05 — 控制会话的建立

"控制会话建立"在本实现里分成三步，顺序固定：**初始化（分配缓冲/装处理器）→ 查版本 → 按版本选安全流程起点**。三步都在链路 `Connected` 上升沿被调用（`analysis/09`）。

## 5.1 初始化

`_iap2_sessionControl_init`（`0x10011d148`）：

```
0x10011d148  cbz x0 → 直接返回 0
0x10011d164  x8 = [component+0xc8]
0x10011d168  cbz x8 → 分配
0x10011d174  w0 = 0xffff
0x10011d178  w1 = 0x4c7b7cb3            ; malloc 第二参数（类型标记）
0x10011d180  bl  malloc
0x10011d184  [component+0xc8] = x0      ; ★ 控制通道缓冲 65535 B
0x10011d188  w21 = (x0 != 0)            ; 分配成功标志
0x10011d190  bl  #0x10006a1d0           ; iap2_features_registerMessageHandlers
0x10011d198  bl  #0x10006a3e4           ; iap2_features_registerIdentificationParamHandlers
0x10011d1a0  bl  #0x10000946c           ; （outlined 片段）
0x10011d1a4  bl  #0x10013e49c           ; iap2_features_createFeatures
0x10011d1b0  返回 w21 & 上述各步返回值
```

要点：

- **缓冲大小 65535 恰好等于单条消息上限**（`analysis/03` 的 `iAP2MsgParserInit(0xffff, …)`）。这不是巧合：`+0xc8` 就是用来装"一条完整消息"的，所以它必须 ≥ 最大消息长。
- 重复调用安全：`+0xc8` 非空则跳过分配（`0x10011d168`）。断连后 `cleanup` 会把它释放并清零（`analysis/12`），所以重连时会重新分配。
- 初始化**不碰会话表**，也不产出发送/接收动作；它是纯本地准备。

## 5.2 查版本

`_iap2_sessionControl_getVersion`（`0x10011d4b8`）：

```
0x10011d4b8  cbz x0 → 0
0x10011d4bc  x8  = [component+0x28]      ; run loop
0x10011d4c0  cbz x8 → 0
0x10011d4d4  x19 = [x8+0x18]             ; ★ link
0x10011d4d8  cbz x19 → 0
0x10011d4dc  bl  #0x10002b140            ; （outlined 片段：得到服务/类型）
0x10011d4e0  bl  #0x100005740            ; iAP2LinkGetSessionForService(link, 类型)
0x10011d4e4  x1 = x0                     ; 会话号
0x10011d4e8  x0 = x19                    ; link
0x10011d4ec  bl  #0x100032828            ; iAP2LinkGetSessionInfo(link, 会话号)
0x10011d4f0  cbz x0 → 返回 0
0x10011d4f4  ldrb w0,[x0,#2]             ; ★ 版本 = 表项[2]
```

所以**控制会话的"版本"不是协议协商出来的，而是会话表里那一行的一个字节**。表由链路层建立（`OPEN-SES-1`），控制会话只是读它。

推论（重要）：如果表里没有控制会话那一行，`getVersion` 返回 0，`start` 走 `version != 2` 分支，即**默认按"认证优先"启动**。也就是说"版本 2"是一个需要显式配置的特例，不是默认。

> **`OPEN-SES-12`**：`0x10002b140` 是 outlined 片段（符号名 `_OUTLINED_FUNCTION_8`），它算出的"类型"常量没有直接落地成指令立即数，因此**控制会话用哪个类型值去查表**只能从 `analysis/10` 的发送侧旁证（常量 0），不能从 `getVersion` 直接读出。

## 5.3 启动：版本决定先跑哪套安全流程

`_iap2_sessionControl_start`（`0x10011d310`）：

```
0x10011d334  w20 = getVersion(component)
0x10011d388–0x10011d3b4  log "Starting control session (version = %d)..."   ; 0x1001db5fb
0x10011d3cc  cmp w20,#2
0x10011d3d0  b.ne 0x10011d3e0
```

两条分支各自打一行日志、各自设定一个 0/1 参数，然后调用同一个函数：

| 条件 | 日志字符串 | 参数 | 证据 |
|---|---|---|---|
| 版本 **== 2** | `"Control session version = 2, starting Identification..."` | `w1 = 1` | 串 `0x1001db626`；`0x10011d410`–`0x10011d428` |
| 版本 **!= 2** | `"Control session version != 2, starting Authentication..."` | `w1 = 0` | 串 `0x1001db65e`；`0x10011d43c`–`0x10011d468` |

```
0x10011d46c  x0 = component ; w1 = 上述 0/1
0x10011d470  bl  #0x10013ec58          ; iap2_features_startFeatureFromDevice(component, mode)
0x10011d488  return 该返回值
```

**版本 2 = 识别优先，其他 = 认证优先。** 这是本阶段最有价值的一条行为结论：会话表里的一个字节直接决定了两套安全流程的先后顺序。

两个字符串本身就是证据（`0x1001db626` / `0x1001db65e`），不需要靠符号名推测。

## 5.4 `0x4301` 与 CarPlay 启动

处理器注册表里 `0x4301` 唯一映射到 `_iap2_CarPlayStartSession`（`0x10016d3ac`，特性 26 的处理器表 `0x10021e650`，`tables.json`）。它的入口行为：

```
0x10016d3ac  要求 msgID == 0x4301                        ; 0x10016d4xx 的 cmp
             读 [ [component] + 0x18 ] = 传输类型号       ; 0x10016d3xx
             查表 DAT_1001b3fe0[类型号] （仅当类型号 < 9）; 越界则 0
             platform_CarPlay_sendConnectionEvent(4, 值)
             log "iap2_CarPlayStartSession: Received message 0x%x"
             遍历 组 0 的参数：iAP2MsgGetFirstParam(msg, 0) / iAP2MsgGetNextParam
                 按参数 ID 分派，部分参数再嵌套遍历子参数
             最终：platform_CarPlay_startSession(...)
```

最终调用的实参列表可以从它自己的日志格式串读出来（`0x10016d3ac` 内引用）：

```
"iap2_CarPlayStartSession: call platform_CarPlay_startSession, usbIP %@, wifiIP %@,
 ssid %@, pass %@, securityType %@, channel %@, port %@, deviceID %@, pubKey %@,
 srcVer %@, sdkVer %@, assetID %@, assetVer %@, mutualAuth %@"
```

所以 `0x4301` 携带的是 **CarPlay 无线/有线启动参数**：USB IP、WiFi IP、SSID、口令、安全类型、信道、端口、设备 ID、公钥、源版本、SDK 版本、资产 ID、资产版本、双向认证标志。这与"控制会话建立"的关系是：CarPlay 传输面的参数由控制会话承载，但**音视频链路本身不在本阶段范围内**（任务书 `TASK.md` §11 第 7 条）。

逐条读原始跳表和分支后，字段路径、getter 宽度、字节序和储存槽已经闭合；详表与地址见 `analysis/15-carplay-start-static-mapping.md`。旧的“映射完全未知”结论不再适用。`OPEN-SES-2` 现在只保留给运行时接收/平台必填性、错误响应以及 Wi-Fi/IP、控制、媒体和输入的端到端结果。

## 5.5 顺序小结

```
链路 Connected 上升沿
  → sessionControl_init      分配 65535 缓冲；装 96 个处理器；建特性
  → sessionControl_start     读版本 → 版本2 ? 识别优先 : 认证优先
  → （之后才是数据面可用：表里有行 + 门控通过）
```

"建立"完成不等于"可发消息"：发出站消息还要过识别门控（`analysis/07`）与会话表查询（`analysis/10`）。
