# analysis/10 — 函数采样清单与未读声明

## 10.1 总量

| 项 | 值 |
|---|---|
| 镜像内函数 | 8,706 |
| `selection.json` 选入 | 278（含 4 个重复地址） |
| 实际导出汇编 | 274（`source/asm/accessoryd/f_*.s` + `.bin`） |
| 实际反编译 | 274 × 2 文件（`readable/ghidra/accessoryd/f_*.ghidra.c` + `.json`） |
| 采样率 | 274 / 8,706 = **3.15%** |

`A10.1`：反编译有 **2 个失败**（`0x100177d80`、`0x1001783bc`，Ghidra 报
`Cannot properly adjust input varnodes`），这两个函数的结论只依据 `source/asm/` 汇编，
`readable/` 里它们的 `.json` 状态为 `DECOMPILE_FAILED`（`verify.py` 的 C4 会校验这一点）。

## 10.2 分组

| 组 | 数量 | 含义 |
|---|---|---|
| `I` | 15 | 本阶段 HID（特性 11） |
| `N` | 21 | 本阶段 NowPlaying（特性 14） |
| `G` | 15 | 本阶段导航（特性 17） |
| `P` | 9 | 本阶段 AssistiveTouch（特性 3） |
| `L` | 34 | 生命周期（挂起/恢复/断开/销毁） |
| `X` | 59 | 第三阶段种子：会话/路由 |
| `C` | 26 | 第三阶段种子：会话控制 |
| `A` | 25 | 第三阶段种子：认证 |
| `S` | 20 | 第三阶段种子：文件传输 |
| `F` | 18 | 第三阶段种子：特性管理 |
| `Q` | 14 | 第三阶段种子：队列/定时器 |
| `T` | 11 | 第三阶段种子：工具函数 |
| `E` | 8 | 第三阶段种子：endpoint |
| `M` | 3 | 第三阶段种子：消息原语 |

## 10.3 逐条人工核对过的函数

以下函数是**本阶段结论直接依赖**的，逐条读过汇编（Ghidra 仅作辅助）：

| 地址 | 名称 | 用于 |
|---|---|---|
| `0x100130444` | `_iap2_hid_StartHIDMsgHandler` | `A03.1`–`A03.3` |
| `0x100130cf0` | `_iap2_hid_AccessoryHIDReportHandler` | `A03.4` `A03.5` |
| `0x10013101c` | `_iap2_hid_AccessoryHIDGetReportResponseHandler` | `A03.7` |
| `0x1001313dc` | `_iap2_hid_StopHIDMsgHandler` | `A03.6` |
| `0x1001316f4` | `_iap2_hid_sendOutReport` | `A01.3` |
| `0x100131864` | `_iap2_hid_sendGetReport` | `A01.3` |
| `0x100131a14` | `_iap2_hid_sendComponentUpdate` | `A01.3` |
| `0x100043a98` | `___iap2_hid_StartHIDMsgHandler_block_invoke` | `A08.2` |
| `0x100043b48` | `…block_invoke.2` | `A08.2` |
| `0x100043c08` | `___iap2_hid_AccessoryHIDReportHandler_block_invoke` | `A03.4` |
| `0x100043c64` | `___iap2_hid_AccessoryHIDGetReportResponseHandler_block_invoke` | `A03.7` |
| `0x1001499f0` | `__startNowPlayingUpdatesHandler` | `A04.1` `A04.2` `A04.3` |
| `0x10014a93c` | `__stopNowPlayingUpdatesHandler` | `A04.1` |
| `0x10014aa20` | `__setNowPlayingInfoHandler` | `A04.4` |
| `0x1001465c4` | `_iap2_nowPlaying_playbackAttributesUpdateHandler` | `A04.5` |
| `0x10017527c` | `_iap2_navigation_startRouteGuidanceHandler` | `A05.1` `A05.3` `A06.3` |
| `0x10017593c` | `_iap2_navigation_stopRouteGuidanceHandler` | `A05.3` |
| `0x100175c70` | `_iap2_navigation_roadObjectDetectionUpdateHandler` | `A05.4` |
| `0x1001783bc` | `_iap2_navigation_startRoadObjectDetectionHandler` | `A05.1` |
| `0x1001788f4` | `_iap2_navigation_stopRoadObjectDetectionHandler` | `A05.1` |
| `0x100050c2c` | `_iap2_identification_checkRequiredMsgIDs` | `A05.1` `A06.3` |
| `0x10004e73c` | `_iap2_identification_paramName` | `A03.3` |
| `0x10003021c` | `_iAP2LinkDeviceActionSendSuspend` | `A07.1` |
| `0x1000302a0` | `_iAP2LinkDeviceActionSendResume` | `A07.2` |
| `0x100034db4` | `_iAP2LinkHandleSuspend` | `A07.3` |
| `0x100030d4c` | `_iap2_endpoint_destroy` | `A08.4` |
| `0x10014bf24` | `_iap2_assistiveTouch_notifyStatusUpdateHandler` | `A06.3` |

## 10.4 未读声明

- 组 `X/C/A/S/F/Q/T/E/M`（第三阶段种子，共 178 个函数）**本轮未逐条重读**，只在
  `analysis/06` 中引用第三阶段结论（`sess/R-5.x`）；
- 组 `L` 中 34 个函数读了与挂起/恢复/销毁直接相关的 6 个（见 10.3），其余未读；
- 组 `I/N/G/P` 中「平台侧」（`_platform_*`）函数读了签名与调用点，函数体未逐条读，
  涉及字段细节的地方已标 `OPEN-*`。
