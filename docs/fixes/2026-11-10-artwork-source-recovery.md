# 封面来源加载失败后的恢复

2026-11-10，关联 R01。封面来源一次加载失败后，下一条同曲、同来源的宿主通知被永久去重，图片无法恢复。本次只修正桥接加载缓存，不更改 Apple 图片传输协议或宿主麦克风选择。

## 原字节依据与本端差异

CarWith 4.0.14 APK SHA256：`c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e`。classes2 `f5.d.q` code item `0x3350a8` 中，`0x335194..0x3351b2` 同时将 MusicInfo.h 的地址和 oa.c.H 的 Bitmap 写进 `coverUrl` / `cover`。classes4 `oa.c.F0` `0x19c0d8` 按 URI 缓存去重；`ra.d.e` `0x1a5c64` 的 URI 分支交给图片加载器、Bitmap 分支交给异步处理；`ra.d.c` `0x1a5b08` 比较处理后图片的内容再发布。位置均为 DEX 文件内偏移，指令正文在 code item 加16 bytes处。

这些字节证明宿主有地址和图片两种来源、独立图片更新与去重。它们没有规定本端的失败重试次数或间隔。桥接的 `HostArtworkState.begin()` 缓存了当前曲目与来源，`complete(request, null)` 却没有撤销该缓存；后续真实宿主通知与缓存相同就无法再进入加载。这是本端失败结果被误记作已处理来源的缺陷。

## 修复

只有当前代际的加载失败才使来源缓存失效。下次宿主更新可再次加载；本次没有定时重试或主动重发。加载中重复通知仍共享请求，成功后的相同来源仍去重。新曲失败仍清除上一曲图片；同曲刷新失败仍保留已有图片；代际隔离、断开保护及 JPEG 内容去重继续生效。

## 验证与边界

新增3项回归：新曲失败后同源通知恢复并拒绝旧请求、同曲刷新重试不清空/不重复发布、迟到失败不破坏新曲成功缓存。封面状态共11项，桥接51项/9 suites无失败、错误或跳过。

```powershell
.\gradlew.bat :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

桥接测试及小米 Debug Kotlin 编译实际执行成功；协议测试任务为 UP-TO-DATE，沿用已有1110项/135 suites、零失败/错误/跳过的结果。whitespace检查通过。

未实车验证，不能据此关闭 R01 频闪。歌词更新仍可能改变图片请求代际；相同地址不保证跨歌曲永远返回同一图片，因此没有按地址忽略所有标题变化。字节来源的32位哈希及宿主旧图晚到的身份判断另记研究边界。详细取证见研究仓库 `research/connection/spec/carwith-artwork-voice-20261110.md`。没有打包、安装或推送。
