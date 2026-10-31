# analysis/13 — 函数清单与取证状态

本阶段导出 **199** 个函数（占 8,706 个起点的 2.29%）。完整枚举在 `function-index.json`（每个地址、符号、组、是否导出、是否被引用）与 `source/metadata/selection.json`。本文件只列**与会话层结论直接相关**的函数及其取证状态。

状态含义：`已读` = 逐指令或完整反编译核对过；`部分` = 读过入口/关键分支；`未读` = 仅导出，未核对。

## 13.1 会话对象与生命周期

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x100129350` | `iap2_endpoint_create` | 已读 | 分配 endpoint（0x1d8）、建 run loop/解析器 |
| `0x100030d4c` | `iap2_endpoint_destroy` | 未读 | endpoint 销毁（`OPEN-SES-28`） |
| `0x1000311f4` | `iap2_endpoint_linkStateChanged` | 已读 | 唯一状态源，上升/下降沿 |
| `0x1001295e0` | `iap2_endpoint_setInitialized` | 部分 | 初始化标志 |
| `0x10012961c` | `iap2_endpoint_isInitialized` | 部分 | 同上 |
| `0x100129634` | `iap2_endpoint_configUSBHost` | 未读 | 上升沿第一个调用 |
| `0x100129738` | `iap2_endpoint_getMaxSendPayloadSize` | 未读 | 发送载荷上限 |
| `0x100129784` | `iap2_endpoint_getMaxSendPayloadSizeWithOverride` | 未读 | 同上（可覆盖） |
| `0x1001298b0` | `iap2_endpoint_getLinkMaxCumAck` | 未读 | 暴露链路 CumAck 参数 |
| `0x100009c3c` | `iap2_endpoint_processIncomingData` | 未读 | endpoint 收数据（上层入口） |
| `0x1000059a0` | `iap2_endpoint_sendOutgoingData` | 未读 | endpoint 发数据（上层入口） |

## 13.2 控制会话

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x10011d148` | `iap2_sessionControl_init` | 已读 | 建 65535 缓冲、装处理器、建特性 |
| `0x10011d310` | `iap2_sessionControl_start` | 已读 | 版本门控 → 识别/认证优先 |
| `0x10011d4b8` | `iap2_sessionControl_getVersion` | 已读 | 读会话表项 `[2]` |
| `0x10011d518` | `iap2_sessionControl_parseIncomingMessage` | 已读 | 逐字节解析 + 门控 + 分派 |
| `0x10011d1c4` | `iap2_sessionControl_cleanup` | 已读 | 释放缓冲、销特性、移 EA 配件 |
| `0x100005130` | `iap2_sessionControl_sendOutgoingMessage` | 已读 | 尾调用 `__sendOutgoingMessage(…,0)` |
| `0x10002a9bc` | `iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK` | 已读 | 尾调用 `…(…,1)` |
| `0x10011d7e4` | `iap2_sessionControl_accAuthenticationStateChanged` | 未读 | 认证状态变化钩子 |
| `0x10011da74` | `iap2_sessionControl_identificationStateChanged` | 未读 | 识别状态变化钩子 |
| `0x10011dde0` | `iap2_sessionControl_authorizationHook_authentication` | 未读 | 授权钩子 |
| `0x10011e1f0` | `iap2_sessionControl_authorizationHook_identification` | 未读 | 授权钩子 |

## 13.3 路由与分发

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x10006b878` | `iap2_sessionRouter_processSessionData` | 已读 | 按类型分发（0/1/2/4） |
| `0x100032670` | `iAP2LinkActionHandleData` | 已读 | 收包 → `hdr[7]` → 表项 |
| `0x10019bfac` | `iAP2LinkDataReadyCB` | 已读 | 再查表 → 交给路由器 |
| `0x100032828` | `iAP2LinkGetSessionInfo` | 已读 | 会话号 → 表项 |
| `0x100005740` | `iAP2LinkGetSessionForService` | 已读 | 类型 → 会话号 |
| `0x10000733c` | `iAP2LinkQueueSendDataPacketInternal` | 已读 | 写 `hdr[7]`、选队列 |
| `0x100006868` | `iAP2LinkQueueSendDataWithSentCallback` | 已读 | 同上（带回调） |
| `0x1000084d0` | `iAP2LinkGetSessSendPckListCount` | 已读 | `+0x130[type]` 队列计数 |
| `0x100033fd0` | `iAP2LinkCreate` | 已读 | 建链路、建表、建 5 条队列、建定时器 |
| `0x100034a7c` | `iAP2LinkAttached` | 部分 | 清表后附着 |
| `0x100034b54` | `iAP2LinkSendRST` | 部分 | 清表 |
| `0x100034c08` | `iAP2LinkDetached` | 部分 | 清表 |
| `0x1000344e0` | `iAP2LinkResetSend` | 部分 | 清表 |

## 13.4 消息与参数编码

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x100003424` | `iAP2MsgInit` | 已读 | 6 字节消息头 |
| `0x100004b44` | `iAP2MsgGetMsgID` | 已读 | `+4` 大端 |
| `0x100005274` | `iAP2MsgGetMsgLen` | 已读 | `+2` 大端 |
| `0x100067694` | `iAP2MsgGetSom` | 已读 | `0x4040` |
| `0x1000053a4` | `iAP2MsgCalcMessageLen` | 已读 | 累加参数长度、回填 |
| `0x100067710` | `iAP2MsgGetParamID` | 已读 | `+2` 大端 |
| `0x100067738` | `iAP2MsgGetFirstParam` | 已读 | 第二参 parent；顶层 +6 / 子项 parent+4；允许 len=4 的项 |
| `0x100067824` → `0x100005448` | `iAP2MsgGetNextParam` / `…WithError` | 部分 | parent/prev 语义与关键边界已读，异常处理见 analysis/04 |
| `0x100067720` | `iAP2MsgGetParamValueLen` | 未读 | 值长度 |
| `0x100003a68` | `iAP2MsgInitParam` | 未读 | 写参数头（`OPEN-SES-11`） |
| `0x1000042b4` | `iAP2MsgAddU8Param` | 未读 | 追加参数 |
| `0x10008eb48` | `iAP2MsgParserInit` | 未读 | 解析器（`OPEN-SES-8`） |
| `0x10008eb68` | `iAP2MsgParserConsumeByte` | 部分 | 逐字节（返回完成的消息） |
| `0x1000088a4` | `iAP2MsgCleanup` | 部分 | 清理消息对象 |

## 13.5 发送与确认

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x100004f14` | `__sendOutgoingMessage` | 已读 | 出站门控 + 两条发送分支 |
| `0x10000530c` | `iAP2MsgSendControl` | 已读 | 装配 + 交给链路 |
| `0x1000055e4` | `iAP2MsgSendCtlDataWithSentCallback` | 已读 | 查类型 0 会话号 |
| `0x100005738` | （未命名） | 未读 | 发送前处理（`OPEN-SES-20`） |
| `0x100005bd0` | `__iAP2LinkDataSentCB` | 未读 | 链路发送入口（`OPEN-SES-22`） |
| `0x1000a0520` | `iAP2MsgSendControlAndCallbackOnAck` | 未读 | ACK 回调（`OPEN-SES-21`） |
| `0x100006758` | `iAP2LinkRunLoopQueueSendDataWithSentCallback` | 部分 | 入队 |

## 13.6 特性与处理器

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x10006a1d0` | `iap2_features_registerMessageHandlers` | 已读 | 96 条灌入全局字典 |
| `0x10006a3e4` | `iap2_features_registerIdentificationParamHandlers` | 未读 | 识别参数处理器 |
| `0x10013e49c` | `iap2_features_createFeatures` | 已读 | 奇偶门控建特性 |
| `0x10013ec58` | `iap2_features_startFeatureFromDevice` | 未读 | 启动特性（`OPEN-SES-13`） |
| `0x10006a610` | `iap2_features_destroyFeatures` | 未读 | 销特性 |
| `0x10012e4c4` | `iap2_messageHandlers_setHandler` | 部分 | 字典写 |
| `0x10012e644` | `iap2_messageHandlers_getHandler` | 已读 | 字典读 |

## 13.7 门控

| 地址 | 符号 | 状态 | 作用 |
|---|---|---|---|
| `0x100051054` | `iap2_identification_isIdentifiedForIncomingMessageID` | 已读 | 入站白名单 + 认证/识别 |
| `0x100005138` | `iap2_identification_isIdentifiedForOutgoingMessageID` | 已读 | 出站白名单 + 认证/识别 |
| `0x10013c0ec` | `iap2_identification_isIdentifiedForFeature` | 未读 | 特性门控 |
| `0x10013c148` | `iap2_identification_isIdentifiedForCarPlay` | 未读 | CarPlay 门控 |
| `0x10013c1a0` | `iap2_identification_isIdentifiedForWirelessCarPlay` | 部分 | 清理时用到 |
| `0x1000052a4` | `iap2_identification_getState` | 部分 | 状态（6 = 识别完成） |
| `0x1000052e0` | `iap2_accAuthentication_getState` | 部分 | 状态（2 = 认证完成） |
| `0x100051238` | （未命名） | 未读 | 取识别信息（`OPEN-SES-14`） |

## 13.8 其它数据面

| 地址 | 符号 | 状态 |
|---|---|---|
| `0x100183b8c` | `iap2_sessionFileTransfer_handleDatagram` | 未读（`OPEN-SES-16`） |
| `0x100136828` | `iap2_sessionLog_parseIncomingMessage` | 未读（`OPEN-SES-16`） |
| `0x10016d3ac` | `iap2_CarPlayStartSession` | 部分（`OPEN-SES-2`） |

## 13.9 采样偏差声明

本阶段**没有**做的事：

- 没有遍历全部 8,706 个函数（只取 199，2.29%）；
- 没有分析 `bluetoothd` / `carkitd`（`accessoryd` 拥有 iAP2 会话层，其它进程不在范围）；
- 没有去混淆 outlined 片段（`_OUTLINED_FUNCTION_*`）——凡依赖它们的结论都已降级为 `OPEN`；
- 没有读任何旧文档或旧伪代码，没有与本阶段之外的实现做对照（`TASK.md` §11 第 1、2 条）。
