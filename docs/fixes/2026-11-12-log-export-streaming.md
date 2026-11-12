# 10 万行日志文件导出修复

日期：2026-11-12。

此前文件导出通过 `logText()` 重新读取全部落盘记录，与内存记录合并、去重、排序，再拼成完整字符串并生成完整 UTF-8 字节数组。大日志导出时同时保留多份历史及文本，存在显著的内存峰值和闪退风险。本次未取得设备崩溃堆栈，原因依据导出代码定位。

文件导出改为 `DeviceViewModel.exportLogs(uri)` → `BridgeStore.exportTo(output)` → `DiagnosticLogExport.writeTo(output)`。在 IO dispatcher 打开并截断目标文档、逐行写入 UTF-8、刷新和关闭。使用既有追加缓冲区的固定长度快照，不复制全部记录，也不重新读取、排序或编码整段历史。保留诊断头、全部行、重复记录、中文、表情、长行尾部及既有脱敏结果，按记录顺序输出。

导出先等待启动时的历史恢复，再取得快照，包含尚在落盘队列里的记录。快照取得前的清空只导出新一代日志；取得后的追加和清空不改变正在导出的快照。逐行检查协程取消，写入、刷新、关闭异常会传到页面并提示失败；导出过程中禁用重复点击。

验证结果：核心 127 项与小米应用 53 项单元测试全部通过，共 180 项，0 失败/错误/跳过；小米 Debug Kotlin 编译通过。随后将日志相关测试的 JVM 堆限制为 64 MB，17 项全部通过。10 万行流式测试按需生成超过 100 MB 的中文/表情日志，逐字节 SHA-256 校验内容与顺序、检查提前开始写入及单次字节写入不超过 8 KiB；另覆盖长行、重复行、快照、取消及写入/刷新失败。既有历史保留测试提升到实际缓存 10 万条记录。

复现命令（使用本机现有缓存，不改全局环境）：

```powershell
.\gradlew.bat :core:testDebugUnitTest :app:testXiaomiDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain --gradle-user-home C:\Users\admin\.gradle
.\gradlew.bat :core:testDebugUnitTest --tests '*DiagnosticLog*Test' --offline --console=plain --gradle-user-home C:\Users\admin\.gradle -I tools/log-export/export-memory.init.gradle
```

64 MB 是流式导出回归测试的堆限制，不代表 Android 应用保存任意大小完整内存历史时的总内存上限。真实设备的文档提供方与原闪退场景仍待复测。
