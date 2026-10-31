# analysis/14 — 会话阶段消息对照表

本文件由 `firmware/tools/gen-control-message-table.py` 从**固件字节**生成，不接受手工编辑。内容是表格化的事实：哪个 `msg_id` 由哪个函数处理、属于哪个特性、在准入名单里是哪一侧。**不含消息语义推断**。

## 14.1 生成口径

| 项 | 值 |
|---|---|
| 镜像 | `source/firmware/accessoryd` |
| 源哈希 | `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe` |
| 特性信息表 | `__kiAP2FeatureInfoEntries`（29 项，每项 16 字节） |
| 处理器表项 | 16 字节：`u32 msg_id; u32 reserved; u64 handler` |
| 指针解码 | `target = 0x100000000 + (value & 0xFFFFFFFFFF)` |
| 处理器表数 | 27（另有 2 项特性无处理器表） |
| 处理器条目数 | 96 |

## 14.2 表清单

| 特性号 | 处理器表 | 表地址 | 条目数 |
|---|---|---|---|
| 0 | `kiAP2MessageHandlerEntries_AccAuthentication` | `0x1002205d8` | 3 |
| 1 | `kiAP2MessageHandlerEntries_Identification` | `0x10021a7e0` | 3 |
| 2 | `kiAP2MessageHandlerEntries_AppLaunch` | `0x10021d018` | 1 |
| 3 | `kiAP2MessageHandlerEntries_AssistiveTouch` | `0x10021c708` | 4 |
| 4 | `kiAP2MessageHandlerEntries_BLEPairing` | `0x100219870` | 3 |
| 5 | `kiAP2MessageHandlerEntries_BTConnectionStatus` | `0x100220b10` | 3 |
| 6 | `kiAP2MessageHandlerEntries_Communications` | `0x100218740` | 14 |
| 7 | `kiAP2MessageHandlerEntries_DeviceAuthentication` | `0x100218eb0` | 4 |
| 9 | `kiAP2MessageHandlerEntries_DigitalAudio` | `0x10021fc00` | 2 |
| 10 | `kiAP2MessageHandlerEntries_ExternalAccessory` | `0x10021d268` | 1 |
| 11 | `kiAP2MessageHandlerEntries_HID` | `0x10021a0b0` | 4 |
| 12 | `kiAP2MessageHandlerEntries_Location` | `0x10021f770` | 1 |
| 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | `0x10021d608` | 8 |
| 14 | `kiAP2MessageHandlerEntries_NowPlaying` | `0x10021c038` | 3 |
| 15 | `kiAP2MessageHandlerEntries_OOBBTPairing` | `0x10021a4d0` | 2 |
| 16 | `kiAP2MessageHandlerEntries_Power` | `0x10021f158` | 5 |
| 17 | `kiAP2MessageHandlerEntries_Navigation` | `0x10021f620` | 3 |
| 18 | `kiAP2MessageHandlerEntries_Test` | `0x10021e050` | 4 |
| 19 | `kiAP2MessageHandlerEntries_USBHostMode` | `0x10021d310` | 2 |
| 20 | `kiAP2MessageHandlerEntries_Vehicle` | `0x10021e260` | 1 |
| 21 | `kiAP2MessageHandlerEntries_VoiceOver` | `0x100219a30` | 13 |
| 22 | `kiAP2MessageHandlerEntries_WiFiSharing` | `0x10021f2f0` | 2 |
| 23 | `kiAP2MessageHandlerEntries_DestinationSharing` | `0x1002218a0` | 3 |
| 24 | `kiAP2MessageHandlerEntries_AppLinks` | `0x10021ce10` | 3 |
| 25 | `kiAP2MessageHandlerEntries_OOBBTPairing2` | `0x10021e3b0` | 2 |
| 26 | `kiAP2MessageHandlerEntries_CarPlayStartSession` | `0x10021e650` | 1 |
| 28 | `kiAP2MessageHandlerEntries_DigitalCarKey_Matching` | `0x100220698` | 1 |

## 14.3 逐条对照（按 msg_id 升序）

列含义：**入站 / 出站** = 该 `msg_id` 在两张准入名单里的位置（名单转录自 `0x100051054` 与 `0x100005138`，见 `analysis/07`）。`需认证+识别` 表示不无条件放行，必须同时满足认证状态 2、识别状态 6、并出现在对应集合中。

| msg_id | 处理器 | 处理器符号 | 特性 | 处理器表 | 入站 | 出站 |
|---|---|---|---|---|---|---|
| `0x0000` | `0x100166354` | （无符号） | 18 | `kiAP2MessageHandlerEntries_Test` | 无条件 | 无条件 |
| `0x0001` | `0x1001668d4` | （无符号） | 18 | `kiAP2MessageHandlerEntries_Test` | 需认证+识别 | 需认证+识别 |
| `0x0004` | `0x100166550` | （无符号） | 18 | `kiAP2MessageHandlerEntries_Test` | 无条件 | 无条件 |
| `0x0005` | `0x100166758` | （无符号） | 18 | `kiAP2MessageHandlerEntries_Test` | 无条件 | 无条件 |
| `0x00B1` | `0x1001378cc` | （无符号） | 15 | `kiAP2MessageHandlerEntries_OOBBTPairing` | 需认证+识别 | 需认证+识别 |
| `0x00B3` | `0x100137de0` | （无符号） | 15 | `kiAP2MessageHandlerEntries_OOBBTPairing` | 需认证+识别 | 需认证+识别 |
| `0x0B01` | `0x1001695e8` | （无符号） | 25 | `kiAP2MessageHandlerEntries_OOBBTPairing2` | 需认证+识别 | 需认证+识别 |
| `0x0B02` | `0x100169e34` | （无符号） | 25 | `kiAP2MessageHandlerEntries_OOBBTPairing2` | 需认证+识别 | 需认证+识别 |
| `0x0D01` | `0x100175c70` | （无符号） | 17 | `kiAP2MessageHandlerEntries_Navigation` | 需认证+识别 | 需认证+识别 |
| `0x10DA` | `0x10019a738` | （无符号） | 23 | `kiAP2MessageHandlerEntries_DestinationSharing` | 需认证+识别 | 需认证+识别 |
| `0x10DC` | `0x10019aa70` | （无符号） | 23 | `kiAP2MessageHandlerEntries_DestinationSharing` | 需认证+识别 | 需认证+识别 |
| `0x10DD` | `0x10019ac90` | （无符号） | 23 | `kiAP2MessageHandlerEntries_DestinationSharing` | 需认证+识别 | 需认证+识别 |
| `0x1D01` | `0x10013bcc8` | （无符号） | 1 | `kiAP2MessageHandlerEntries_Identification` | 无条件 | 需认证+识别 |
| `0x1D05` | `0x10013b28c` | （无符号） | 1 | `kiAP2MessageHandlerEntries_Identification` | 无条件 | 需认证+识别 |
| `0x1D06` | `0x100050934` | （无符号） | 1 | `kiAP2MessageHandlerEntries_Identification` | 无条件 | 需认证+识别 |
| `0x4154` | `0x10011e6e4` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4156` | `0x10011ec18` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4157` | `0x10011ece4` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4159` | `0x10011f020` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415A` | `0x10011f0e0` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415B` | `0x10011f4bc` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415C` | `0x10011f70c` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415D` | `0x10011f968` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415E` | `0x10011f97c` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x415F` | `0x10011f990` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4160` | `0x10011fb84` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4161` | `0x10011fd54` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4170` | `0x10011ff54` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4172` | `0x10012081c` | （无符号） | 6 | `kiAP2MessageHandlerEntries_Communications` | 需认证+识别 | 需认证+识别 |
| `0x4301` | `0x10016d3ac` | （无符号） | 26 | `kiAP2MessageHandlerEntries_CarPlayStartSession` | 需认证+识别 | 需认证+识别 |
| `0x4302` | `0x1000ed624` | （无符号） | 28 | `kiAP2MessageHandlerEntries_DigitalCarKey_Matching` | 需认证+识别 | 需认证+识别 |
| `0x4C00` | `0x100157e20` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C02` | `0x100157f14` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C03` | `0x100157fa8` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C05` | `0x100158c30` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C06` | `0x100158f18` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C07` | `0x1001591d4` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C08` | `0x1001595f0` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4C09` | `0x100159a3c` | （无符号） | 13 | `kiAP2MessageHandlerEntries_MediaLibrary` | 需认证+识别 | 需认证+识别 |
| `0x4E01` | `0x100189680` | （无符号） | 5 | `kiAP2MessageHandlerEntries_BTConnectionStatus` | 需认证+识别 | 需认证+识别 |
| `0x4E03` | `0x100189c00` | （无符号） | 5 | `kiAP2MessageHandlerEntries_BTConnectionStatus` | 需认证+识别 | 需认证+识别 |
| `0x4E05` | `0x10018a024` | （无符号） | 5 | `kiAP2MessageHandlerEntries_BTConnectionStatus` | 需认证+识别 | 需认证+识别 |
| `0x5000` | `0x1001499f0` | `startNowPlayingUpdatesHandler` | 14 | `kiAP2MessageHandlerEntries_NowPlaying` | 需认证+识别 | 需认证+识别 |
| `0x5002` | `0x10014a93c` | `stopNowPlayingUpdatesHandler` | 14 | `kiAP2MessageHandlerEntries_NowPlaying` | 需认证+识别 | 需认证+识别 |
| `0x5003` | `0x10014aa20` | `setNowPlayingInfoHandler` | 14 | `kiAP2MessageHandlerEntries_NowPlaying` | 需认证+识别 | 需认证+识别 |
| `0x5200` | `0x10017527c` | （无符号） | 17 | `kiAP2MessageHandlerEntries_Navigation` | 需认证+识别 | 需认证+识别 |
| `0x5203` | `0x10017593c` | （无符号） | 17 | `kiAP2MessageHandlerEntries_Navigation` | 需认证+识别 | 需认证+识别 |
| `0x5400` | `0x10014bab4` | （无符号） | 3 | `kiAP2MessageHandlerEntries_AssistiveTouch` | 需认证+识别 | 需认证+识别 |
| `0x5401` | `0x10014bbdc` | （无符号） | 3 | `kiAP2MessageHandlerEntries_AssistiveTouch` | 需认证+识别 | 需认证+识别 |
| `0x5402` | `0x10014bcf4` | （无符号） | 3 | `kiAP2MessageHandlerEntries_AssistiveTouch` | 需认证+识别 | 需认证+识别 |
| `0x5404` | `0x10014be18` | （无符号） | 3 | `kiAP2MessageHandlerEntries_AssistiveTouch` | 需认证+识别 | 需认证+识别 |
| `0x5601` | `0x1000354d0` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5602` | `0x10012bbd4` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5603` | `0x10003573c` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5606` | `0x10012bc78` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5608` | `0x10012bea4` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5609` | `0x10012bf48` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x560B` | `0x10012bfec` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x560D` | `0x10012c2b4` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x560E` | `0x10012c354` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x560F` | `0x10012c608` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5611` | `0x10012c940` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5612` | `0x10012c9e0` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5613` | `0x10012cb20` | （无符号） | 21 | `kiAP2MessageHandlerEntries_VoiceOver` | 需认证+识别 | 需认证+识别 |
| `0x5700` | `0x10017020c` | （无符号） | 22 | `kiAP2MessageHandlerEntries_WiFiSharing` | 需认证+识别 | 需认证+识别 |
| `0x5703` | `0x1001703cc` | （无符号） | 22 | `kiAP2MessageHandlerEntries_WiFiSharing` | 需认证+识别 | 需认证+识别 |
| `0x6800` | `0x100130444` | （无符号） | 11 | `kiAP2MessageHandlerEntries_HID` | 需认证+识别 | 需认证+识别 |
| `0x6802` | `0x100130cf0` | （无符号） | 11 | `kiAP2MessageHandlerEntries_HID` | 需认证+识别 | 需认证+识别 |
| `0x6803` | `0x1001313dc` | （无符号） | 11 | `kiAP2MessageHandlerEntries_HID` | 需认证+识别 | 需认证+识别 |
| `0x6805` | `0x10013101c` | （无符号） | 11 | `kiAP2MessageHandlerEntries_HID` | 需认证+识别 | 需认证+识别 |
| `0x7E00` | `0x100157590` | （无符号） | 19 | `kiAP2MessageHandlerEntries_USBHostMode` | 需认证+识别 | 需认证+识别 |
| `0x7E02` | `0x100157888` | （无符号） | 19 | `kiAP2MessageHandlerEntries_USBHostMode` | 需认证+识别 | 需认证+识别 |
| `0xA101` | `0x1000ad35c` | （无符号） | 20 | `kiAP2MessageHandlerEntries_Vehicle` | 需认证+识别 | 需认证+识别 |
| `0xAA01` | `0x1001850bc` | （无符号） | 0 | `kiAP2MessageHandlerEntries_AccAuthentication` | 无条件 | 需认证+识别 |
| `0xAA03` | `0x100185d6c` | （无符号） | 0 | `kiAP2MessageHandlerEntries_AccAuthentication` | 无条件 | 需认证+识别 |
| `0xAA06` | `0x1001860d4` | （无符号） | 0 | `kiAP2MessageHandlerEntries_AccAuthentication` | 仅需识别 | 需认证+识别 |
| `0xAA10` | `0x100123108` | （无符号） | 7 | `kiAP2MessageHandlerEntries_DeviceAuthentication` | 需认证+识别 | 需认证+识别 |
| `0xAA12` | `0x100123204` | （无符号） | 7 | `kiAP2MessageHandlerEntries_DeviceAuthentication` | 需认证+识别 | 需认证+识别 |
| `0xAA14` | `0x10012356c` | （无符号） | 7 | `kiAP2MessageHandlerEntries_DeviceAuthentication` | 需认证+识别 | 需认证+识别 |
| `0xAA15` | `0x100123690` | （无符号） | 7 | `kiAP2MessageHandlerEntries_DeviceAuthentication` | 需认证+识别 | 需认证+识别 |
| `0xAD00` | `0x100150750` | （无符号） | 24 | `kiAP2MessageHandlerEntries_AppLinks` | 需认证+识别 | 需认证+识别 |
| `0xAD02` | `0x100150ff4` | （无符号） | 24 | `kiAP2MessageHandlerEntries_AppLinks` | 需认证+识别 | 需认证+识别 |
| `0xAD03` | `0x10015115c` | （无符号） | 24 | `kiAP2MessageHandlerEntries_AppLinks` | 需认证+识别 | 需认证+识别 |
| `0xAE00` | `0x1000c2088` | （无符号） | 16 | `kiAP2MessageHandlerEntries_Power` | 需认证+识别 | 需认证+识别 |
| `0xAE02` | `0x1000c2220` | （无符号） | 16 | `kiAP2MessageHandlerEntries_Power` | 需认证+识别 | 需认证+识别 |
| `0xAE03` | `0x1000c1888` | （无符号） | 16 | `kiAP2MessageHandlerEntries_Power` | 需认证+识别 | 需认证+识别 |
| `0xAE05` | `0x1000c1c6c` | （无符号） | 16 | `kiAP2MessageHandlerEntries_Power` | 需认证+识别 | 需认证+识别 |
| `0xAE06` | `0x1000c1848` | （无符号） | 16 | `kiAP2MessageHandlerEntries_Power` | 需认证+识别 | 需认证+识别 |
| `0xB102` | `0x100129a28` | （无符号） | 4 | `kiAP2MessageHandlerEntries_BLEPairing` | 需认证+识别 | 需认证+识别 |
| `0xB103` | `0x100129d14` | （无符号） | 4 | `kiAP2MessageHandlerEntries_BLEPairing` | 需认证+识别 | 需认证+识别 |
| `0xB105` | `0x10012a03c` | （无符号） | 4 | `kiAP2MessageHandlerEntries_BLEPairing` | 需认证+识别 | 需认证+识别 |
| `0xDA00` | `0x1001819f8` | （无符号） | 9 | `kiAP2MessageHandlerEntries_DigitalAudio` | 需认证+识别 | 需认证+识别 |
| `0xDA02` | `0x100181ad4` | （无符号） | 9 | `kiAP2MessageHandlerEntries_DigitalAudio` | 需认证+识别 | 需认证+识别 |
| `0xEA02` | `0x1001539dc` | （无符号） | 2 | `kiAP2MessageHandlerEntries_AppLaunch` | 需认证+识别 | 需认证+识别 |
| `0xEA03` | `0x100154964` | （无符号） | 10 | `kiAP2MessageHandlerEntries_ExternalAccessory` | 需认证+识别 | 需认证+识别 |
| `0xFFFB` | `0x100179484` | （无符号） | 12 | `kiAP2MessageHandlerEntries_Location` | 需认证+识别 | 需认证+识别 |

## 14.4 观察

1. **重复 `msg_id`**：无。
2. **无符号处理器**：93 条。它们存在于 `LC_FUNCTION_STARTS`（真实函数），只是名字被剥掉；不能用名字反推语义。
3. **双向无条件放行**：`0x0000`、`0x0004`、`0x0005`。这些是链路层之上的「始终允许」消息。
4. **仅出站无条件**：无。入站方向对它们要求认证完成。
5. **入站需门控**：87 条（占 96 条的 91%）。多数消息在识别完成前不可达，这解释了为什么「连上链路」与「能发消息」是两件事。

## 14.5 限制

- 本表只回答「哪个函数处理哪个 `msg_id`」，**不回答**参数格式与副作用（`OPEN-SES-2`、`OPEN-MSG-1`）。
- `msg_id` 的编号分组（`0x1Dxx`、`0xAAxx`、`0x43xx`）在二进制里没有枚举名可读，前缀语义不可从固件取证。
- 有 2 项特性（8、27）没有处理器表，因此它们的消息入口不在本表内。

