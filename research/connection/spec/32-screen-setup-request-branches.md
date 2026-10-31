# 32 — Screen SETUP 请求生产者：CarPlay 与通用镜像分支

基线：iPhone18,1 / iOS 27.0.1 / 24A446。状态：`PARTIAL`。本章审查普通 CarPlay screen 的请求字典生产者，不代表整个连接链、全部显示类型或所有车机已经与 iPhone 等价。补充 [30 视频主线](30-video-first-frame.md)、[31 编码及密码合同](31-video-codec-contract.md)。机器证据为 [32-screen-setup-request.json](../evidence/32-screen-setup-request.json)。


## 1. 对手机实现最直接的结论

- 普通 CarPlay 的 `latencyMs` 确实是线上 stream 字段，不是仅内部属性。无线默认为 **75 ms**，USB 默认25 ms，均可由本机设置覆盖；**100不是该24A446路径的默认值**。
- 普通选定显示的 `uuid` 从显示描述中的 `uuid` 取出；没有自动造一个替代值。显示初始化最后发现其为空时返回 `-16760`，不继续建立一个无UUID的同等屏幕流。
- stream type110/111 的单流 SETUP helper 在 session kind=5 时**跳过自动生成** `timestampInfo`，而不是给它填固定五项时间戳。注意这不是“所有kind5请求都绝无timestampInfo”：输入 options 已有的键仍会保留。
- 原实现产生动态 `streamConnectionID`。类型110/111会用 UUID 的前8字节构成整数并写入请求，而不是照抄调用者传来的ID。
- 这些证据支持修正手机请求构造与测试，**没有证明它们是某辆车连接失败或卡顿的唯一原因**。

## 2. 字典生产顺序与分支

```text
选定 endpoint/display + screen 初始化
  → Resume 创建 stream options，写 latencyMs
  → 有session且IsCarPlay：写 uuid，再加入 ExtraStreamOptions
  → session 单流 SETUP helper 复制 options
  → 写 type；110/111生成 streamConnectionID
  → 仅kind≠5时尝试自动添加 timestampInfo
  → root.streams=[stream] → 内部 stup 请求
```

| 位置与条件 | 已证行为 | 未覆盖/不可外推 |
|---|---|---|
| `Resume @ 0x251bd65d8`，`0x251bd66bc–66d4` | 创建options，取screen storage `+0x49c`，经 `FigCFDictionarySetInt32` 写 `latencyMs`。 | 字典/后续资源失败不能当成成功发包。 |
| `0x251bd66d8–66e4`：session `+0x30`存在，且IsCarPlay `+0x183!=0` | 从 `+0x138`写 `uuid`；如果 `+0x78`存在则合入额外选项。 | 无session分支使用已有transport路径；不是同一个SETUP生产入口。 |
| `0x251bd6790–67e0`：非CarPlay且demo标志存在 | 可加入 `DemoDeviceInfo`。 | 不能把demo键作为普通CarPlay必需项。 |
| `0x251bd67e4–6854` | 取storage `+0x58`作为stream type，options作为实参，调用session虚表setup方法。 | 其它session实现/transport完整分派没有在本章全枚举。 |
| `_apsession_setupStreamCreatingResponseInternal @ 0x2519bbf24`，`0x2519bc0b8–0d4` | 若control SETUP尚未完成，先将control请求字段加入root。 | 这不意味着每次screen SETUP都重复control字段。 |
| `0x2519bc0f8–14c` | 有options则 `CFDictionaryCreateMutableCopy`；否则创建空字典。随后写 `type`。 | 不是重建只保留固定四键的白名单字典。 |
| `0x2519bc158–174`、`21c–25c` | 类型110/111生成connection ID；kind5跳过自动timestamp生产。 | 其它音频type有不同分支，不应从screen规则推出音频规则。 |
| `0x2519bc314–33c` | kind不等于5时，调用timestamp生产者；非空才写 `timestampInfo`，为空则省略。 | 非kind5也不是无条件存在此键。 |
| `0x2519bc1b0–1d0`、`2b4–2c8` | 将单stream放入数组、写root的 `streams`，作为 `stup` 请求正文。 | 返回/网络发送/车机接受/视频首帧是不同成功条件。 |

## 3. latencyMs：75/25是默认，不是永不改变的常量

`APEndpointStreamScreenCreate @ 0x251b40be8` 的初始化段先读取endpoint `IsConnectedOverUSB`→storage `+0x185`，读取 `IsCarPlay`→`+0x183`。在 `0x251b4121c–41238`：

| 条件 | 提供值的函数 | 默认与覆盖 |
|---|---|---|
| IsCarPlay且非USB | `APSCarPlayScreenLatencyMs(false) @ 0x226e64870` | `screenLatencyMs`，默认75（`0x4b`）。 |
| IsCarPlay且USB | 同函数true分支 | `screenLatencyCarPlayUSBMs`，默认25（`0x19`）。 |
| 非CarPlay | 另一provider，由control connection interface latency hint输入 | 本章未恢复完整默认/策略，不借用75或25。 |

原始跳板 `0x25810d090 → 0x226e64870` 已绑定AirPlaySupport导出名。该函数向 `APSSettingsGetIntWithOverrideAndDefault @ 0x226e63f48` 传setting key、空显式override字典和上述fallback。helper尝试读取设置、转换整数，读取/转换失败保留fallback。故应说“没有本地覆盖时的默认值”，不能说“所有iPhone实际会话都固定75”。

返回值在 `0x251b41238` 存入 `+0x49c`。`Resume`经原跳板 `0x25810b140 → FigCFDictionarySetInt32 @ 0x18ee7d728` 写入 `latencyMs`；对应CFNumber创建路径使用32位输入。`_screenstream_copyOutputLatency @ 0x251b434e4` 将该值用1000为分母转成时间，补充毫秒单位证据。

`+0x4a0` 是另外的media-presentation latency状态，初始化为另一provider与 `+0x49c` 的较大值；不能把它误认成此处SETUP写出的数值。后续interface hint偏好段 `0x251b41fac–41fbc` 仅在非CarPlay时重新计算 `+0x49c`。

## 4. uuid：显示对象与线上键已接通，但aux路径独立

普通显示路径为：

1. `screenstream_initDisplayInfo @ 0x251b443cc` 在 `0x251b447dc–4480c` 检查 `+0x182`（IsAuxScreenStream）。为0时请求属性 `kAPEndpointDisplayDescriptionProperty_UUID`，输出到storage `+0x138`；属性调用返回非零则退出。
2. `APEndpointDisplayDescriptionCopyProperty @ 0x251a9bcf0` 委派其block `0x251a9be54`。block在 `0x251a9bea0–bec0` 将内部 `UUID` 属性匹配到保存的displayInfo字典中的小写键 **`uuid`**，在 `0x251a9bf74–bf84`执行get、retain、写出。此分支不生成缺省UUID。
3. getter可以“成功但输出空”。初始化尾部 `0x251b44d8c–44d90`再次检查；空值进入 `screenstream_initDisplayInfo.cold.11 @ 0x251bd94ec`，日志为 `endpoint display has no UUID, bailing out`，`0x251bd9564–9568`写错误 **`-0x4178 = -16760`**。
4. 成功进入普通CarPlay Resume后，`0x251bd66e8–66f8`直接把该UUID写入options的 `uuid`。

Aux标志非零时，`0x251b44810–44818`走另一UUID提供者 `0x25810ef90 → 0x19702228c`。本章没有恢复其完整契约。不能拿aux分支为“普通display缺uuid时随机补值”辩护。

上述getter未在此处实施CFString语法验证；手机端要求非空字符串属于本机模型/输入验证，不能声称每项字符串校验都来自这些指令。源display字典中全部字段的类型检查、完整display选择/aux/type111策略仍另行审查。

## 5. ExtraStreamOptions与timestampInfo的边界

`screenstream_SetProperty @ 0x2519b4600` 匹配内部属性 **`ExtraStreamOptions`**（CFString `0x27613b530`）；要求非空且类型为CFDictionary，保留到storage `+0x78`，非法类型返回 `-16760`。这是内部属性入口，不表示对端 `/info` 任意同名键都会被信任。

CarPlay Resume先写 `latencyMs` 和 `uuid`，再对extras逐项执行block `0x251b43fc4`。该block尾调用 `0x258101810 → CFDictionaryAddValue @ 0x18061fff0`，不是SetValue，因此已存在的上述两键不会被extras覆盖。

随后单流helper复制options，写type/connectionID。kind5分支 `0x2519bc24c–25c`跳过自动timestamp生成，但不会删掉options已有的其它键。因此准确规则是：

- 当前普通screen builder没有ExtraStreamOptions来源时，不应自行注入通用 `timestampInfo`。
- 原固件仍可能从经过上层设置的extras携带其它字段；本章没有审完所有extras生产者。
- kind≠5才调用 `0x25810f7c0 → 0x196f5bca4`并在非空时写 `timestampInfo`。本章验证了原跳板目标，没有把该producer的全payload/schema假定为已恢复。

## 6. streamConnectionID与仍保留的实现差异

类型110/111的helper在 `0x2519bc224–248` 调用 `UUIDGet @ 0x18be501d4`生成16字节UUID，将前8字节从内存载入后用ARM64 `REV`转换，调用 `CFDictionarySetInt64 @ 0x18be4320c`写 `streamConnectionID`。UUIDGet内 `0x18be501f0–5020c`设置UUID版本/variant位。本段未看到63bit mask或强制非零。

手机当前原有ID策略是随机Long再限制为正63bit，且ID进入密码salt/legacy密码对象。本轮保留这一策略，标记 **OPEN/APP_ONLY**；不能为追求外观相似而只删mask，却不验证负值/U64的plist编码、十进制字符串和KDF消费关系。调用生命周期（何时重新生成、重试复用、恢复）也需要与密码对象一起审。

这与本轮screen字段修正是两个不同问题。生产builder应接受同一会话使用的ID，并确保日志与真正发送的字典一致，不新增第二个无关ID。

## 7. 本轮可验收范围及不得顺带改变的身份

手机实施侧应使用一个生产builder生成screen request：type110、同一connection ID、无线默认75ms、选定display UUID；无普通display UUID时在发送screen SETUP之前报错，不伪造。测试应调用该生产builder，经 `AirPlaySetupSession.screen` 和真实RTSP编码捕获线上正文，断言字段和值，并覆盖缺UUID。只在测试内手写四键字典再做plist往返，无法发现生产构造仍保留100或旧timestamp数组。

本章不支持把 `sourceVersion=320.17` / `User-Agent=AirPlay/320.17` / `osBuildVersion=21A329`立即改成24A446对应字符串。这些是当前兼容子集声明，已有音频接收端版本分支会受build影响；完整跨层身份/能力/密码矩阵没有在这次screen审计中闭环。继续保留并显式标注过渡态，比宣称“已完整复刻iPhone”准确。详见 [23 版本能力审计](23-airplay-version-capability-audit.md)。

静态验证命令：

```powershell
python -B D:\carvex-research\research\connection\tools\inspect_screen_setup_request.py --verify D:\carvex-research\research\connection\evidence\32-screen-setup-request.json
python -B D:\carvex-research\research\connection\tools\validate_docset.py
```

前者验证来源字节、指令与快照一致；后者只验证文档/JSON/链接完整性。二者都不是实车通过、全部分支等价、认证成功或视频首帧证据。
