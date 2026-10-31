# 结论汇总（`A` 编号）

> 每条结论 = 一句可判真假的断言 + 证据位置。`位置` 指向 `analysis/` 的章节；`依据` 一律回落到 `source/asm/airplaysender/` 的指令地址。
> 未确认点不在这里，在 `spec/08-open-items.md` 与 `coverage.json`。

| 结论 | 断言 | 位置 |
|---|---|---|
| `A00.1` | 目标二进制 `AirPlaySender` 大小 4,397,312 B、SHA256 `304b8a4a…63b`、UUID `2d49b39b…febf`、11,443 个函数起点。 | 00 §1 |
| `A00.2` | `__TEXT` 为 `0x251996000`–`0x251c7a000`，`__text` 为 `0x251997a78`–`0x251bdbb08`；本阶段所有代码地址都在 `__text` 内。 | 00 §2 |
| `A00.3` | 同一二进制内共存 TCP 记录帧变体（`_APEndpointStreamScreenCreate`）与 UDP/RTP 变体（`APEndpointStreamScreenUDP*`）。 | 00 §3 |
| `A00.4` | 对 `__cstring`/`__oslogstring`/`__objc_methname` 扫描 `h264`（不分大小写）为 0 命中；视频编码在代码中以 `AVC` 命名。 | 00 §3 |
| `A00.5` | 本阶段精读 23 个函数（11,443 的 0.20 %），为主题定向抽样，不构成全栈覆盖。 | 00 §3 |
| `A01.1` | 屏幕流有两个创建入口：`_APEndpointStreamScreenCreate` @ `0x251b40be8`（TCP）与 `APEndpointStreamScreenUDPCreate`（UDP，字符串 `0x251c02dc8`）。 | 01 §1 |
| `A01.2` | 无 display 参数时流类型写 `0x6e` 到流对象 `+0x58`（`0x251b40fc0`/`0x251b40fc4`）。 | 01 §2 |
| `A01.3` | 带 display 参数时存在 `0x251b40f4c cinc w8, w8, eq` 分支，类型可能为 `0x6f`；比较结果与类型值的对应关系未闭合。 | 01 §2 |
| `A01.4` | CarPlay 侧 `carEndpoint_setupScreenStreams` 在 `0x251aef428` 调用 `_APEndpointStreamScreenCreate`，为每个 display 组字典。 | 01 §3 |
| `A01.5` | 每屏字典包含 `UUID`/`PixelSize`/`PhysicalSize`/`ViewAreas`/`ZoomFactor`/`MaxFPS`/`IsNightMode`/`IsLimitedUI` 等键。 | 01 §3 |
| `A01.6` | SETUP 响应由 `_apsession_setupStreamCreatingResponseInternal` 解析，并对类型做 `0x2519bbfac sub w8, w1, #0x6f` / `0x2519bc340 cmp w21, #0x6e` 检查。 | 01 §4 |
| `A01.7` | UDP 变体在 `_sdpsession_sendSetup`（`0x251a9f364`）引用 `RTP/AVP/UDP`（`0x251c13dc6`，引用点 `0x251a9f414`）。 | 01 §6 |
| `A01.8` | `negotiationData`（`0x251c040b0`）与 UDP 建流请求字符串同簇，说明协商数据随建流传递；blob 结构未证。 | 01 §7 |
| `A02.1` | 屏幕记录固定 128 字节头：帧路径 `calloc(1,0x80)`（`0x2519b0e70`–`0x2519b0e80`），配置路径 `0x251b44068`/`0x251b44074`。 | 02 §1 |
| `A02.2` | 帧记录+0写w23累计长度，不能简化为明文长度（0e88）；+4写类型0（0e8c），额外长度及可选尾段见A06.4。 | 02 §2 |
| `A02.3` | 帧记录 `+0x05` 标志：bit7 取自流对象 `+0x45c`，bit4 取自 `+0x45d`（`0x2519b1038`–`0x2519b1058`）。 | 02 §2 |
| `A02.4` | 帧记录+60..7f为最多16项u16间隔；ticks差经UpTicksToMilliseconds，结果>=0x10000时写0xffff（10b0、10b8），不是4096ms阈值。 | 06 §4 |
| `A02.5` | 配置记录 `+0x04=1`、`+0x06` 基值 `0x12` 并可按 4 个条件置 `+1`/`|4`/`|0x40`/`|8`、`+0x07=1`（`0x251b44080`–`0x251b440d8`）。 | 02 §3 |
| `A02.6` | 配置记录有10个double→float转换，写入+10、14、20、24、28、2c、30、34、38、3c；+18..1f为空隙（4417c..1f0）。 | 06 §5 |
| `A02.7` | 帧头写完后立即调用 `_sbpd_encryptBBuf`（`0x2519b1160`），随后 `[+0x470] += 1`（`0x2519b11c8`–`0x2519b11d0`）。 | 02 §2.2 |
| `A02.8` | 统计分支按storage+3c5为0/非0写type2/5；本函数UserData路径并入type0，长度写头+1c；完整schema/控制位来源未闭合。 | 02 §4；0x2519b07a8..7bc、0x2519b0e38..4c、0x2519b0e8c、0x2519b0f9c |
| `A03.1` | `_sbpd_encryptBBuf(流对象, 头BBuf, 载荷BBuf)`，头与载荷是两个独立 buffer（`0x2519b1150`/`0x2519b115c`）。 | 03 §1 |
| `A03.2` | 加密上下文在流对象 `+0x198`；为空时整个加密步骤跳过（`0x2519b50bc`）。 | 03 §2 |
| `A03.3` | 加密虚调用x3=x5同为载荷指针；+1a0仅决定附加输出大小，成功后新建extraBB并追加（51ac/51b4、51fc、5214）。 | 03 §2 |
| `A03.4` | 包装器分别传头与载荷；相邻FairPlay专题已核接收侧ChaCha的128B网络头AAD、单/双段边界，发送绑定及profile适用性仍需核。 | 03 §4 |
| `A03.5` | 已核type110/111分派在keyholder等门通过后：G=0为CTR、G≠0为ChaCha(flag=0)，不能从CoreUtils类名推出所有视频恒ChaCha或12B nonce。 | 03 §5 |
| `A03.6` | `coreUtilsKeyHolder_CreateEncryptionKeysForStream`（`0x2519bfecc`）用 `"%s%llu"` + `"DataStream-Salt"` 生成 salt 标签，再以 `"DataStream-Input-Encryption-Key"`（`0x1f`）与 `"DataStream-Output-Encryption-Key"`（`0x20`）两次调用 `CreateDerivedKey`（`0x2519bff40`/`0x2519bff68`）。 | 03 §6 |
| `A03.7` | Legacy屏幕派生由Sender直接计算SHA512(name串与16B masterKey拼接)的前16B，不应套用CoreUtils媒体HKDF标签。相邻FairPlay analysis15已核直接调用链。 | 03 §7 |
| `A04.1` | 编码封装类 `APEndpointStreamScreenAVCWrapper` 用 `AVCMediaStreamNegotiator` 协商（字符串 `0x251c0480e`）。 | 04 §3 |
| `A04.2` | 已核avc1/控制byte门下格式描述avcC CFData→缓存→type1 body→本地组装在帧前；NAL表示、参数集内部布局/帧内重复仍待核，不能排除重排。 | 07 §1/2；04 §2 |
| `A04.3` | `presentationMode` 是一等参数：`isConfigPresentForPresentationMode:`、`negotiationDataForPresentationMode:`、`restartWithScreenOptions:negotiatedBlob:`。 | 04 §4 |
| `A04.4` | `hdrMirroringSupported` 与 `convertHDRMode:` 说明 HDR 需协商，模式切换走重启路径。 | 04 §4 |
| `A04.5` | 编码参数（位率/帧率/GOP）存在配置调用，但汇编中未定位立即数，取值未证。 | 04 §5 |
| `A04.6` | +05 bit7来自APInterestingFrame==kCFBooleanTrue；bit4来自NotSync附件输出==0，无/空数组置1；两者不等于NAL IDR证明。 | 07 §3/4；04 §6 |
| `A05.1` | 发送按批：配置记录在前（`local_d8 != 0` 时 `0x2519b0e68` 调 `_sbpd_createConfigBBuf`），帧记录在后。 | 05 §1 |
| `A05.2` | 帧时间戳由流对象 `+0x3d0` 的转换器产生（`0x2519b0ea0`/`0x2519b0f00`），不是裸时钟。 | 05 §2 |
| `A05.3` | 车机命令分发器 `carEndpoint_processEventCreatingResponse`（`0x251c3a202`）支持 `forceKeyFrame`（`0x251c3a28a`），处理函数签名串 `0x251c3a38e`。 | 05 §3 |
| `A05.4` | 清屏有独立路径：采集回调 `screenDidClear:`（`0x251a77da0`）与 UDP 的 `handleClearScreen`（`0x251a761d8`）。 | 05 §4 |
| `A05.5` | 恢复相关组件：`handleFatalError`（`0x251b43140`）、`cleanup`（`0x251b42e34`）、`Suspend`/`Resume`（`0x251b43624`/`0x251b43744`）、`serverDidDisconnect:`（`0x251a77e9c`）。 | 05 §5 |
| `A05.6` | 流对象至少有两个布尔状态 `activated` 与 `resumed`（调试串 `0x251c0388c`）。 | 05 §5 |
| `A05.7` | UDP 变体走 RTP over UDP；RTP 头/payload type/打包模式未读，未证。 | 05 §6 |
| `A06.1` | 包装器要求载荷连续；虚调用原地处理载荷，附加输出单独分配后追加，不保证失败回滚。 | 06 §1 |
| `A06.2` | DataStream的31/32是info原字节长度且不含NUL；输出长度是另一实参，CreateDerivedKey建立CFData并转发provider。 | 06 §2 |
| `A06.3` | 可选尾段在12f0用同一头再次加密；+470是拼装后的u32计数且0844有清零，不能当nonce或送达确认。 | 06 §3 |
| `A06.4` | 头长字段在写入前含额外长度及可选尾段；间隔经ticks→ms转换且阈值65536，不能推导每批最多16帧。 | 06 §4 |
| `A06.5` | 配置记录10个float稀疏写入，+18..1f为空隙，不是连续float[10]。 | 06 §5 |
