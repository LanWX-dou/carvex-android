# GalaxyPlay / DiPlay 通话按键对接

GalaxyPlay 0.1.212/240 是实际目标，手机为 Android 17；DiPlay 未在车机上开启。
本轮使用 DiPlay `615b32c` 源码核对接收端，并用原 GalaxyPlay APK 独立验证按键事实。

原 `MixingKeyMapper` 把 Telephony usage `0x20` 映射为打开电话页面的
`PHONE=8104`，把 `0x21` Flash 映射为接听的 `CALL=8111`。
GalaxyPlay 的 `answerCall()` 实际发 selector 1，其描述符对应 Hook Switch `0x20`。
因此点击车机接听会请求打开电话页，接听操作没有被正确交给手机宿主。

现在 Hook Switch `0x20` 转为 `CALL=8111`；Drop `0x26` 保持
`END_CALL=8112`。Flash `0x21` 没有已证的 mixing 等价操作，返回不支持。
`requestUI ui:mobilephone:` 仍使用 `PHONE=8104`。不新增宿主或车机型号分支。

原始证据：GalaxyPlay APK SHA256
`f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6`，
`classes5.dex` 的 `CarPlayController.answerCall` code_item `0x0439e8` 与
`endCall` `0x043cec` 分别为 selector 1 和 3；`AirPlayHid.<clinit>`
`0x01cc1c` 的 telephony 数组 payload `0x01d0b4` 与 DiPlay 原描述符逐字节相同。
这验证接收端的按键输入，不用于推断 Apple 发送端状态机。
宿主 keyId 沿用 [mixing 已有证据](../../host-carlife-mixing/README.md)。
完整输入、DEX 方法归属与指令哈希见
[接收端兼容记录](../../../research/connection/spec/receiver-source-interop-20261111.md)。

验证使用真正的接收源码生成描述符和报告，再通过本项目映射：

```powershell
python -X utf8 -B tools/receiver-interop/prepare.py D:/Project/Lanwx/DiPlay
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest --offline --console=plain `
  --no-configuration-cache -I build/receiver-interop/receiver-tests.init.gradle
```

修复前接听/Flash 两项源联测失败。修复后宿主模块 **24 项通过、0 失败、0 跳过**，
包含 2 项接收源码联测和独立的接听/电话页区分测试；协议模块还核对完整的 HID 按下/抬起。
当前没有实车接听、挂断结果。

本轮未改变已正常的音乐链路，也未改变
[上一轮通话订阅与编码修复](2026-11-11-call-subscriptions-chain.md)。
完整拨号/接通/保持、号码与 UUID、蜂窝下行 PCM 及麦克风注入仍缺已证手机数据源。
普通电话状态的 OFFHOOK 包含拨号/保持，不能据此发布精确 ACTIVE。
接收端解析器的状态测试使用人工测试输入，不能证明 Android 17 的生产来源或通话音频已打通。
