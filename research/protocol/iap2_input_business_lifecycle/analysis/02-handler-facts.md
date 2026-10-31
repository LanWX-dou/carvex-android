# analysis/02 — 输入/业务处理器事实表（机器生成）

本文件由 `firmware/tools/gen-input-handler-facts.py` 从固件字节生成，**不接受手工编辑**。
它只记录可机械复核的事实：参数 ID 上界、跳表地址、每个参数 ID 的取值函数、
函数体内的调用序列、引用的 C 字符串、调用的 selector。**不含字段语义推断**。

## `0x6800` — `0x100130444`（HID）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_hid_StartHIDMsgHandler` |
| 区间 | `0x100130444`–`0x100130cf0` |
| 参数 ID 上界 | `#4`（`cmp w0,#4` + `b.hi`） |
| 跳表 | `0x100018774` |
| 门控调用 | 按特性号取特性对象（门控前置） |

| 参数 ID | case | 取值函数 | 类型/说明 |
|---|---|---|---|
| `0` | `0x100130538` | `0x100067e1c` | U16（校验总长=6） |
| `1` | `0x1001305c8` | `0x100067e1c` | U16（校验总长=6） |
| `2` | `0x1001305a4` | `0x100067e1c` | U16（校验总长=6） |
| `3` | `0x1001305b8` | `0x100067e4c` | U8（校验总长=5） |
| `4` | `0x100130560` | `0x100067720` | 取值长度（总长-4） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001e1160` | `Unrecognized paramID:0x%04X` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100003360` `_iap2_feature_getFeature`
- `0x100003510` `_OUTLINED_FUNCTION_12`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100003f58` `_OUTLINED_FUNCTION_21`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1000438d0` `__validateHIDComponent`
- `0x100067720` `_iAP2MsgGetParamValueLen`
- `0x100003f58` `_OUTLINED_FUNCTION_21`
- `0x100067f30` `_iAP2MsgGetDataAsData`
- `0x1001a1820` （无符号）
- `0x1001a1510` （无符号）
- `0x100003f58` `_OUTLINED_FUNCTION_21`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x100003f58` `_OUTLINED_FUNCTION_21`
- `0x100067e4c` `_iAP2MsgGetDataAsU8`
- `0x100003f58` `_OUTLINED_FUNCTION_21`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x100004884` `_OUTLINED_FUNCTION_11`
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fe0` （无符号）
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`
- `0x1000165c0` `_OUTLINED_FUNCTION_16`

</details>

## `0x6802` — `0x100130cf0`（HID）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_hid_AccessoryHIDReportHandler` |
| 区间 | `0x100130cf0`–`0x10013101c` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001e1160` | `Unrecognized paramID:0x%04X` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100003510` `_OUTLINED_FUNCTION_12`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1000438d0` `__validateHIDComponent`
- `0x100067720` `_iAP2MsgGetParamValueLen`
- `0x100067f30` `_iAP2MsgGetDataAsData`
- `0x1001a1820` （无符号）
- `0x1001a1510` （无符号）
- `0x100004884` `_OUTLINED_FUNCTION_11`
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fe0` （无符号）
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）
- `0x1001a1830` （无符号）
- `0x1001a1830` （无符号）
- `0x100031a20` `_acc_manager2_performPlatformWorkAsync`
- `0x10000fdb0` `_logObjectForModule`
- `0x100001a54` `_OUTLINED_FUNCTION_24`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10000fdb0` `_logObjectForModule`
- `0x100001a54` `_OUTLINED_FUNCTION_24`
- `0x1001a1820` （无符号）
- `0x100003510` `_OUTLINED_FUNCTION_12`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10001638c` `_OUTLINED_FUNCTION_26`
- `0x1001a1fc0` （无符号）

</details>

## `0x6805` — `0x10013101c`（HID）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_hid_AccessoryHIDGetReportResponseHandler` |
| 区间 | `0x10013101c`–`0x1001313dc` |
| 参数 ID 上界 | `#3`（`cmp w0,#3` + `b.hi`） |
| 跳表 | `0x100018788` |
| 门控调用 | 无 |

| 参数 ID | case | 取值函数 | 类型/说明 |
|---|---|---|---|
| `0` | `0x1001310e4` | `0x100067e1c` | U16（校验总长=6） |
| `1` | `0x100131170` | `0x100067e4c` | U8（校验总长=5） |
| `2` | `0x10013110c` | `0x100067e4c` | U8（校验总长=5） |
| `3` | `0x10013112c` | `0x100067720` | 取值长度（总长-4） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001e1160` | `Unrecognized paramID:0x%04X` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100011d74` `_OUTLINED_FUNCTION_32`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1000438d0` `__validateHIDComponent`
- `0x100011d74` `_OUTLINED_FUNCTION_32`
- `0x100067e4c` `_iAP2MsgGetDataAsU8`
- `0x100067720` `_iAP2MsgGetParamValueLen`
- `0x100011d74` `_OUTLINED_FUNCTION_32`
- `0x100067f30` `_iAP2MsgGetDataAsData`
- `0x1001a1820` （无符号）
- `0x1001a1510` （无符号）
- `0x100011d74` `_OUTLINED_FUNCTION_32`
- `0x100067e4c` `_iAP2MsgGetDataAsU8`
- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x100004884` `_OUTLINED_FUNCTION_11`
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fe0` （无符号）
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）
- `0x1001a1830` （无符号）
- `0x1001a1830` （无符号）
- `0x100031a20` `_acc_manager2_performPlatformWorkAsync`
- `0x10000fdb0` `_logObjectForModule`
- `0x100001a54` `_OUTLINED_FUNCTION_24`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x1000035b8` `_OUTLINED_FUNCTION_1`
- `0x10000fdb0` `_logObjectForModule`
- `0x100001a54` `_OUTLINED_FUNCTION_24`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x1000035b8` `_OUTLINED_FUNCTION_1`
- `0x10000fdb0` `_logObjectForModule`
- `0x100001a54` `_OUTLINED_FUNCTION_24`

</details>

## `0x6803` — `0x1001313dc`（HID）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_hid_StopHIDMsgHandler` |
| 区间 | `0x1001313dc`–`0x1001316f4` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 按特性号取特性对象（门控前置） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001e1160` | `Unrecognized paramID:0x%04X` |
| `0x1001e120a` | `StopHID message received, but keeping HID interface registered. (connectionUUID: %@, endpointUUID: %@, componentID: %d)` |
| `0x1001e1282` | `Could not find HID component! (connectionUUID: %@, endpointUUID: %@, componentID: %d)` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1001a2830` （无符号）
- `0x1001a1fe0` （无符号）
- `0x100003f04` `_OUTLINED_FUNCTION_12`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x1001a2830` （无符号）
- `0x10000ea8c` `_OUTLINED_FUNCTION_27`
- `0x100015510` `_OUTLINED_FUNCTION_13`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1000129e0` `_OUTLINED_FUNCTION_23`
- `0x100003360` `_iap2_feature_getFeature`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x1001a17a0` （无符号）
- `0x1001a1690` （无符号）
- `0x1001a1820` （无符号）
- `0x100012e10` `_OUTLINED_FUNCTION_7`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x1001a2830` （无符号）
- `0x10000ea8c` `_OUTLINED_FUNCTION_27`
- `0x100015510` `_OUTLINED_FUNCTION_13`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fc0` （无符号）
- `0x10000fdb0` `_logObjectForModule`
- `0x1001a2830` （无符号）
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10001638c` `_OUTLINED_FUNCTION_26`
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）
- `0x10000a164` `_OUTLINED_FUNCTION_5`
- `0x1001a2140` （无符号）

</details>

## `0x5000` — `0x1001499f0`（NowPlaying）

| 项 | 值 |
|---|---|
| 符号 | `__startNowPlayingUpdatesHandler` |
| 区间 | `0x1001499f0`–`0x10014a93c` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 按特性号取特性对象（门控前置） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f0773` | `Start Now Playing Updates!` |
| `0x1001f078e` | `msgParamID: %d` |
| `0x1001f079d` | `msgSubParamID: %d` |
| `0x1001dbebd` | `Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param` |
| `0x1001dc247` | `Subparam ID: %d parse error in Param ID: %d for Msg ID: 0x%04X - ignoring message` |
| `0x1001f07af` | `mediaAttrCount: %ld` |
| `0x1001f07c3` | `playbackAttrCount: %ld` |
| `0x1001f07da` | `Sending initial now playing update for endpoint: %@` |
| `0x1001d162e` | `_sendInitialNowPlayingUpdate` |
| `0x1001efb1f` | `%s:%d - iAP2MsgInit with cleanupCB - _artworkFileTransferIDSent endpointUUID: %@` |
| `0x1001efa3a` | `%s: no parameters added! cleaning up pOutMsg` |
| `0x1001f0854` | `nowPlaying addSubscriber: PlaybackQueueList` |
| `0x1001f0880` | `call _checkMoveWindowAndRequestPBQList: true` |
| `0x1001efb70` | `#Artwork Failed to add file transfer!` |
| `0x1001efb96` | `#Artwork Failed to allocate file transfer buffer ID!` |
| `0x1001f080e` | `#Artwork %d: cancel previous transfer: id=%d(%d) type=%d(%d) state=%d` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100003360` `_iap2_feature_getFeature`
- `0x100001b20` `_OUTLINED_FUNCTION_24`
- `0x100015f64` `_OUTLINED_FUNCTION_2`
- `0x1000095e0` `_OUTLINED_FUNCTION_18`
- `0x100014160` `_OUTLINED_FUNCTION_75`
- `0x100012ee0` `_OUTLINED_FUNCTION_7`
- `0x1000163a8` `_OUTLINED_FUNCTION_26`
- `0x10000ca78` `_OUTLINED_FUNCTION_42`
- `0x1001a1fb0` （无符号）
- `0x1001a1440` （无符号）
- `0x1001a1440` （无符号）
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x1000044bc` `_OUTLINED_FUNCTION_11`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x10000a288` `_OUTLINED_FUNCTION_5`
- `0x100015f64` `_OUTLINED_FUNCTION_2`
- `0x1001a2830` （无符号）
- `0x100005874` `_OUTLINED_FUNCTION_62`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fb0` （无符号）
- `0x100004ba8` `_OUTLINED_FUNCTION_40`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x10000a288` `_OUTLINED_FUNCTION_5`
- `0x100015f64` `_OUTLINED_FUNCTION_2`
- `0x1000018b4` `_OUTLINED_FUNCTION_20`
- `0x1001a2830` （无符号）
- `0x100005874` `_OUTLINED_FUNCTION_62`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10001295c` `_OUTLINED_FUNCTION_71`
- `0x1001a1fb0` （无符号）
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x1001a13f0` （无符号）
- `0x100004ba8` `_OUTLINED_FUNCTION_40`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x100017620` `_OUTLINED_FUNCTION_0`
- `0x1001a2140` （无符号）
- `0x100004ba8` `_OUTLINED_FUNCTION_40`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100067710` `_iAP2MsgGetParamID`

</details>

## `0x5002` — `0x10014a93c`（NowPlaying）

| 项 | 值 |
|---|---|
| 符号 | `__stopNowPlayingUpdatesHandler` |
| 区间 | `0x10014a93c`–`0x10014aa20` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 按特性号取特性对象（门控前置） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f08ad` | `Stop Now Playing Updates!` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100003360` `_iap2_feature_getFeature`
- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x10000a288` `_OUTLINED_FUNCTION_5`
- `0x100015f64` `_OUTLINED_FUNCTION_2`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x1000018b4` `_OUTLINED_FUNCTION_20`
- `0x1001a2830` （无符号）
- `0x10000952c` `_OUTLINED_FUNCTION_4`
- `0x100009360` `_OUTLINED_FUNCTION_44`
- `0x10000ca78` `_OUTLINED_FUNCTION_42`
- `0x1001a1fb0` （无符号）
- `0x10014ae38` `__pauseElapsedTimeTimer`
- `0x10014995c` `__removeSubscribersForSubFeatures`
- `0x1001a1820` （无符号）
- `0x1001a1820` （无符号）
- `0x100017620` `_OUTLINED_FUNCTION_0`
- `0x1001a2140` （无符号）

</details>

## `0x5003` — `0x10014aa20`（NowPlaying）

| 项 | 值 |
|---|---|
| 符号 | `__setNowPlayingInfoHandler` |
| 区间 | `0x10014aa20`–`0x10014ae38` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 按特性号取特性对象（门控前置） |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f090a` | `Set Now Playing Info handler!` |
| `0x1001f0928` | `_setNowPlayingInfoHandler: autoChoosePBQListStartIndex=%d` |
| `0x1001f0962` | `_setNowPlayingInfoHandler: call _checkMoveWindowAndRequestPBQList: false` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x100001b20` `_OUTLINED_FUNCTION_24`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x1000018b4` `_OUTLINED_FUNCTION_20`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10000ca78` `_OUTLINED_FUNCTION_42`
- `0x1001a1fb0` （无符号）
- `0x100005908` `_OUTLINED_FUNCTION_54`
- `0x100003360` `_iap2_feature_getFeature`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100081e20` `_OUTLINED_FUNCTION_77`
- `0x100081e20` `_OUTLINED_FUNCTION_77`
- `0x100081e20` `_OUTLINED_FUNCTION_77`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x100031a20` `_acc_manager2_performPlatformWorkAsync`
- `0x100031a20` `_acc_manager2_performPlatformWorkAsync`
- `0x10000e248` `_OUTLINED_FUNCTION_38`
- `0x100011f34` `_OUTLINED_FUNCTION_64`
- `0x1000023c8` `_OUTLINED_FUNCTION_26`
- `0x10000431c` `_OUTLINED_FUNCTION_53`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fb0` （无符号）
- `0x10000e248` `_OUTLINED_FUNCTION_38`
- `0x100011f34` `_OUTLINED_FUNCTION_64`
- `0x1000023c8` `_OUTLINED_FUNCTION_26`
- `0x10000431c` `_OUTLINED_FUNCTION_53`
- `0x1001a2830` （无符号）
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x10000ca78` `_OUTLINED_FUNCTION_42`
- `0x1001a1fb0` （无符号）
- `0x1000817c0` `__checkMoveWindowAndRequestPBQList`
- `0x1000102b4` `_logObjectForModule`
- `0x100003f80` `_OUTLINED_FUNCTION_7`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1000102b4` `_logObjectForModule`
- `0x100003f80` `_OUTLINED_FUNCTION_7`

</details>

## `0x5200` — `0x10017527c`（Navigation）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_navigation_startRouteGuidanceHandler` |
| 区间 | `0x10017527c`–`0x10017593c` |
| 参数 ID 上界 | `#5`（`cmp w0,#5` + `b.hi`） |
| 跳表 | `0x100018e40` |
| 门控调用 | 按特性号取特性对象（门控前置）、出站识别/认证门控 |

| 参数 ID | case | 取值函数 | 类型/说明 |
|---|---|---|---|
| `0` | `0x1001753c0` | `0x100067e1c` | U16（校验总长=6） |
| `1` | `0x100175450` | `0x100067f3c` | _iAP2MsgIsDataVoid |
| `2` | `0x100175420` | `0x100067f3c` | _iAP2MsgIsDataVoid |
| `3` | `0x100175438` | `0x100067f3c` | _iAP2MsgIsDataVoid |
| `4` | `0x100175408` | `0x100067f3c` | _iAP2MsgIsDataVoid |
| `5` | `0x100175468` | `0x100067f3c` | _iAP2MsgIsDataVoid |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x100202688` | `iAP2Navigation StartRouteGuidance Handler %@` |
| `0x1001dbebd` | `Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param` |
| `0x1002026b5` | `iAP2Navigation StartRouteGuidance: %@` |
| `0x1002026db` | `iAP2Navigation StartRouteGuidance: for componentList=%@` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |
| `0x1001f7528` | `Too many params Param ID: %d for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x1000095e0` `_OUTLINED_FUNCTION_18`
- `0x1001a2830` （无符号）
- `0x1000c5f34` `_OUTLINED_FUNCTION_70`
- `0x100003474` `_OUTLINED_FUNCTION_6`
- `0x1001a1fe0` （无符号）
- `0x100003f10` `_OUTLINED_FUNCTION_17`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x1001a1440` （无符号）
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100016548` `_OUTLINED_FUNCTION_80`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1001a17a0` （无符号）
- `0x1001a13f0` （无符号）
- `0x1001a1820` （无符号）
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x100067f3c` `_iAP2MsgIsDataVoid`
- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x1000166fc` `_OUTLINED_FUNCTION_16`
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x100016920` `_OUTLINED_FUNCTION_73`
- `0x100003f10` `_OUTLINED_FUNCTION_17`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x1000c5ee8` `_OUTLINED_FUNCTION_28`
- `0x10000bf50` `_OUTLINED_FUNCTION_12`
- `0x1001a1fb0` （无符号）
- `0x1000c5ed4` `_OUTLINED_FUNCTION_8`
- `0x1001a2140` （无符号）
- `0x100001a38` `_OUTLINED_FUNCTION_18`
- `0x1000166fc` `_OUTLINED_FUNCTION_16`
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x1000023c8` `_OUTLINED_FUNCTION_26`
- `0x100001890` `_OUTLINED_FUNCTION_36`
- `0x1000c5f34` `_OUTLINED_FUNCTION_70`

</details>

## `0x5203` — `0x10017593c`（Navigation）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_navigation_stopRouteGuidanceHandler` |
| 区间 | `0x10017593c`–`0x100175c70` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x100202713` | `iAP2Navigation StopRouteGuidance Handler %@` |
| `0x1001dbebd` | `Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param` |
| `0x10020273f` | `iAP2Navigation StopRouteGuidance: %@` |
| `0x100202764` | `iAP2Navigation StopRouteGuidance: for componentList=%@` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100003300` `_OUTLINED_FUNCTION_90`
- `0x100001d68` `_OUTLINED_FUNCTION_89`
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100011918` `_OUTLINED_FUNCTION_15`
- `0x1001a2830` （无符号）
- `0x100004a1c` `_OUTLINED_FUNCTION_11`
- `0x1000115c0` `_OUTLINED_FUNCTION_44`
- `0x1001a1fe0` （无符号）
- `0x100003f10` `_OUTLINED_FUNCTION_17`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100005868` `_OUTLINED_FUNCTION_39`
- `0x1001a1440` （无符号）
- `0x1000095e0` `_OUTLINED_FUNCTION_18`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x100001d68` `_OUTLINED_FUNCTION_89`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1001a17a0` （无符号）
- `0x100016aec` `_OUTLINED_FUNCTION_30`
- `0x1001a13f0` （无符号）
- `0x1001a1820` （无符号）
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x100016920` `_OUTLINED_FUNCTION_73`
- `0x100003f10` `_OUTLINED_FUNCTION_17`
- `0x100067824` `_iAP2MsgGetNextParam`
- `0x100004b44` `_iAP2MsgGetMsgID`
- `0x10000bf50` `_OUTLINED_FUNCTION_12`
- `0x1001a1fb0` （无符号）
- `0x1000c5ed4` `_OUTLINED_FUNCTION_8`
- `0x1001a2140` （无符号）
- `0x100001d68` `_OUTLINED_FUNCTION_89`
- `0x10000e968` `_OUTLINED_FUNCTION_9`
- `0x1000023c8` `_OUTLINED_FUNCTION_26`
- `0x100001890` `_OUTLINED_FUNCTION_36`
- `0x100004a1c` `_OUTLINED_FUNCTION_11`
- `0x10000eb08` `_OUTLINED_FUNCTION_27`
- `0x1001a1fe0` （无符号）
- `0x1000c5f78` `_OUTLINED_FUNCTION_94`
- `0x1000c5f0c` `_OUTLINED_FUNCTION_66`
- `0x100001d68` `_OUTLINED_FUNCTION_89`

</details>

## `0x0D01` — `0x100175c70`（Navigation）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_navigation_roadObjectDetectionUpdateHandler` |
| 区间 | `0x100175c70`–`0x1001763bc` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x10020279b` | `iAP2Navigation RoadObjectDetectionUpdate Handler %@` |
| `0x1002027cf` | `iAP2Navigation RoadObjectDetectionUpdate Handler %@, process paramID=%d` |
| `0x1001dbebd` | `Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param` |
| `0x100202817` | `iAP2Navigation RoadObjectDetectionUpdate: %@` |
| `0x100202844` | `iAP2Navigation RoadObjectDetectionUpdate: %@ componentIdList: %@ updateInfo: %@` |
| `0x100202894` | `iAP2Navigation RoadObjectDetectionUpdate Handler %@, EXIT result=%d` |
| `0x1001dbe7e` | `Param ID: %d parse error for Msg ID: 0x%04X - ignoring message` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x10000e26c` `_OUTLINED_FUNCTION_38`
- `0x1000093d4` `_OUTLINED_FUNCTION_34`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100011918` `_OUTLINED_FUNCTION_15`
- `0x1001a2830` （无符号）
- `0x100004a1c` `_OUTLINED_FUNCTION_11`
- `0x1000115c0` `_OUTLINED_FUNCTION_44`
- `0x1001a1fe0` （无符号）
- `0x100003f10` `_OUTLINED_FUNCTION_17`
- `0x100067738` `_iAP2MsgGetFirstParam`
- `0x100067710` `_iAP2MsgGetParamID`
- `0x10000e26c` `_OUTLINED_FUNCTION_38`
- `0x1000093d4` `_OUTLINED_FUNCTION_34`
- `0x100016920` `_OUTLINED_FUNCTION_73`
- `0x100012a3c` `_OUTLINED_FUNCTION_26`
- `0x1000c5f40` `_OUTLINED_FUNCTION_77`
- `0x10000bf50` `_OUTLINED_FUNCTION_12`
- `0x1001a1fb0` （无符号）
- `0x100016548` `_OUTLINED_FUNCTION_80`
- `0x100067e1c` `_iAP2MsgGetDataAsU16`
- `0x1000dd52c` `_platform_navigation_createObjectDetectionInfoDict`
- `0x1000dd5b0` `_platform_navigation_objectDetectionInfoAddComponentID`
- `0x10001207c` `_OUTLINED_FUNCTION_43`
- `0x1000c49e4` `__parseRoadSignParameter`
- `0x1000dd52c` `_platform_navigation_createObjectDetectionInfoDict`
- `0x100016aec` `_OUTLINED_FUNCTION_30`
- `0x1000dd784` `_platform_navigation_objectDetectionInfoAddRoadSign`
- `0x1001a1820` （无符号）
- `0x100016548` `_OUTLINED_FUNCTION_80`
- `0x100067e9c` `_iAP2MsgGetDataAsI32`
- `0x1000018b4` `_OUTLINED_FUNCTION_20`
- `0x1000dd550` `_platform_navigation_objectDetectionInfoGetItem`
- `0x1000dd52c` `_platform_navigation_createObjectDetectionInfoDict`
- `0x1000dd6a4` `_platform_navigation_objectDetectionInfoSetEgoSpeed`
- `0x100067fa4` `_iAP2MsgGetDataAsArrayI32`
- `0x1000dd550` `_platform_navigation_objectDetectionInfoGetItem`
- `0x1000dd52c` `_platform_navigation_createObjectDetectionInfoDict`
- `0x1000dd714` `_platform_navigation_objectDetectionInfoSetEgoYawRate`
- `0x100016548` `_OUTLINED_FUNCTION_80`
- `0x100067dc4` `_iAP2MsgGetDataAsU64`

</details>

## `0x5400` — `0x10014bab4`（AssistiveTouch）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_assistiveTouch_startAssistiveTouchHandler` |
| 区间 | `0x10014bab4`–`0x10014bbdc` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f14a0` | `StartAssistiveTouch %@` |
| `0x1001f14b7` | `StartAssistiveTouch: %@ started %d->%d pEndpoint=%p assistiveTouch=%p` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100009504` `_OUTLINED_FUNCTION_4`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100001998` `_OUTLINED_FUNCTION_31`
- `0x100009458` `_OUTLINED_FUNCTION_2`
- `0x100009478` `_OUTLINED_FUNCTION_4`
- `0x1001a1fe0` （无符号）
- `0x100004d44` `_OUTLINED_FUNCTION_14`
- `0x100011b80` `_OUTLINED_FUNCTION_17`
- `0x100016618` `_OUTLINED_FUNCTION_16`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x100003370` `_OUTLINED_FUNCTION_15`
- `0x100003238` `_OUTLINED_FUNCTION_15`
- `0x1000034f8` `_OUTLINED_FUNCTION_1`
- `0x10001765c` `_OUTLINED_FUNCTION_0`
- `0x100012ef0` `_OUTLINED_FUNCTION_7`
- `0x100036ce0` `_platform_assistiveTouch_setState`
- `0x100014c78` `_OUTLINED_FUNCTION_3`
- `0x100014c78` `_OUTLINED_FUNCTION_3`

</details>

## `0x5401` — `0x10014bbdc`（AssistiveTouch）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_assistiveTouch_stopAssistiveTouchHandler` |
| 区间 | `0x10014bbdc`–`0x10014bcf4` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f14fd` | `StopAssistiveTouch %@` |
| `0x1001f1513` | `StopAssistiveTouch: %@ started %d->%d pEndpoint=%p assistiveTouch=%p` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100009504` `_OUTLINED_FUNCTION_4`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100001998` `_OUTLINED_FUNCTION_31`
- `0x100009458` `_OUTLINED_FUNCTION_2`
- `0x100009478` `_OUTLINED_FUNCTION_4`
- `0x1001a1fe0` （无符号）
- `0x100004d44` `_OUTLINED_FUNCTION_14`
- `0x100011b80` `_OUTLINED_FUNCTION_17`
- `0x100016618` `_OUTLINED_FUNCTION_16`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x100003370` `_OUTLINED_FUNCTION_15`
- `0x100003238` `_OUTLINED_FUNCTION_15`
- `0x1000034f8` `_OUTLINED_FUNCTION_1`
- `0x10001765c` `_OUTLINED_FUNCTION_0`
- `0x100012ef0` `_OUTLINED_FUNCTION_7`
- `0x100036ce0` `_platform_assistiveTouch_setState`
- `0x100014c78` `_OUTLINED_FUNCTION_3`
- `0x100014c78` `_OUTLINED_FUNCTION_3`

</details>

## `0x5402` — `0x10014bcf4`（AssistiveTouch）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_assistiveTouch_startAssistiveTouchUpdateHandler` |
| 区间 | `0x10014bcf4`–`0x10014be18` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f1558` | `StartAssistiveTouchUpdate %@` |
| `0x1001f1575` | `StartAssistiveTouchUpdate: %@ infoRequested %d->%d pEndpoint=%p assistiveTouch=%p` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100009504` `_OUTLINED_FUNCTION_4`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100001998` `_OUTLINED_FUNCTION_31`
- `0x100009458` `_OUTLINED_FUNCTION_2`
- `0x100009478` `_OUTLINED_FUNCTION_4`
- `0x1001a1fe0` （无符号）
- `0x100004d44` `_OUTLINED_FUNCTION_14`
- `0x100011b80` `_OUTLINED_FUNCTION_17`
- `0x100016618` `_OUTLINED_FUNCTION_16`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x100003370` `_OUTLINED_FUNCTION_15`
- `0x100003238` `_OUTLINED_FUNCTION_15`
- `0x1000034f8` `_OUTLINED_FUNCTION_1`
- `0x10001765c` `_OUTLINED_FUNCTION_0`
- `0x100012ef0` `_OUTLINED_FUNCTION_7`
- `0x100036dd4` `_platform_assistiveTouch_requestStatus`
- `0x100014c78` `_OUTLINED_FUNCTION_3`
- `0x100014c78` `_OUTLINED_FUNCTION_3`

</details>

## `0x5404` — `0x10014be18`（AssistiveTouch）

| 项 | 值 |
|---|---|
| 符号 | `_iap2_assistiveTouch_stopAssistiveTouchUpdateHandler` |
| 区间 | `0x10014be18`–`0x10014bf24` |
| 参数分派 | 未见 `cmp w0,#N` + 跳表形态 |
| 门控调用 | 无 |

引用的可打印字符串：

| 地址 | 内容 |
|---|---|
| `0x1001f15c7` | `StopAssistiveTouchUpdate %@` |
| `0x1001f15e3` | `StopAssistiveTouchUpdate: %@ infoRequested %d->%d pEndpoint=%p assistiveTouch=%p` |

<details><summary>调用序列（按地址顺序，前 40 条）</summary>

- `0x100009504` `_OUTLINED_FUNCTION_4`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x1000034c0` `_OUTLINED_FUNCTION_27`
- `0x100001998` `_OUTLINED_FUNCTION_31`
- `0x100009458` `_OUTLINED_FUNCTION_2`
- `0x100009478` `_OUTLINED_FUNCTION_4`
- `0x1001a1fe0` （无符号）
- `0x100004d44` `_OUTLINED_FUNCTION_14`
- `0x100011b80` `_OUTLINED_FUNCTION_17`
- `0x100016618` `_OUTLINED_FUNCTION_16`
- `0x10000e8a0` `_OUTLINED_FUNCTION_9`
- `0x100003370` `_OUTLINED_FUNCTION_15`
- `0x100003238` `_OUTLINED_FUNCTION_15`
- `0x1000034f8` `_OUTLINED_FUNCTION_1`
- `0x10001765c` `_OUTLINED_FUNCTION_0`
- `0x100012ef0` `_OUTLINED_FUNCTION_7`
- `0x100014c78` `_OUTLINED_FUNCTION_3`
- `0x100014c78` `_OUTLINED_FUNCTION_3`

</details>

