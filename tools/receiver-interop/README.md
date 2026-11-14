# 可选接收源码联测

以外部 DiPlay 干净 Git checkout 的原 Kotlin 代码解析 CarVeX 输出；GalaxyPlay
仍为实际车机目标。默认构建不依赖外部源码，工具不写入、运行或安装外部项目。
供应商文件只暂存到忽略的 `build/receiver-interop/`，不进入生产 APK 或仓库。

准备与复现（从 Android 仓库运行，使用本项目的 JDK/SDK 环境）：

```powershell
python -X utf8 -B tools/receiver-interop/prepare.py D:/Project/Lanwx/DiPlay
.\gradlew.bat :protocol-carplay:testDebugUnitTest :host-carlife-mixing:testDebugUnitTest `
  --offline --console=plain --no-configuration-cache `
  -I build/receiver-interop/receiver-tests.init.gradle
python -X utf8 -B tools/receiver-interop/verify_results.py
```

`--offline` 要求本机已缓存项目依赖。准备只生成输入和临时 Gradle init；不会自动运行
Gradle。`--no-configuration-cache` 保证该临时测试配置不与默认构建混用。init 只扩展
两个库的 `test.kotlin` 源目录；后续普通 Gradle 命令不使用 init，就没有接收代码依赖。

输入包含 14 个完整 Kotlin 生产文件、实际 worker 测试，以及通话卡片/状态解析器和音频声明函数两份截取。
截取 body 保持原字节，只精简 Android imports、暴露原私有函数供测试，提取音频常量。
缺文件、缺截取边界或外部 checkout 不干净时明确失败，不替换为模拟解析器。
原文件、原 body、测试模板 SHA256 和双方提交号写入 `build/receiver-interop/manifest.json`。
schema 2 还登记所有暂存源码、测试及 init 的实际字节哈希；结果检查拒绝准备后被修改的输入。

协议模块 21 项覆盖订阅、CSM 碎片、八种基础箭头、距离/剩余时间更新与reset、100 个连续机动缓存、
单槽逐报文显示、多组件/U16边界、重算/新路线、中文音乐增量、播放状态/封面文件、
音乐/路线/车道隔离、道路文本与展示到期、通话状态解析、实际音频声明与 HID 按下/抬起。
另复制并执行 DiPlay 的 7 个 worker 并发测试，检查旧 owner/link、阻塞、失败、队列满与清理。
宿主模块 2 项使用原 telephony 描述符验证接听/挂断及 Flash 不支持。
通话状态为人工测试输入；音频项检查协商选择，不录制声音，不证明蜂窝 PCM 或 modem 消费。

结果工具逐个核对预期的 21+2 个合同及 7 个原 worker 测试确实出现在 JUnit XML，并拒绝失败、错误、
跳过或缺失的测试。它读取已有报告，包括 Gradle 有效缓存报告；不会独立证明报告新鲜度。
必须先确认上述 Gradle 命令成功。`--output <path>` 可保存无原始业务载荷的 JSON 摘要。
完整回归命令及输入/报告哈希见
[本轮执行与验收记录](../../../openspec/changes/align-business-lifecycle-and-push-fields/execution.md)。
在完整回归成功后，`--full` 还核对 core/bridge/host-api/PCM、五个 app flavor 和小米 Release lint。
它同时检查两个修改模块的 Debug/Release Kotlin 输出，确认没有接收源码或联测类进入生产编译。

源码测试不能证明 GalaxyPlay 与新版 DiPlay 完全相同，也不能证明实际车机显示。
GalaxyPlay 原 APK 的方法归属和按键原字节由研究仓库的独立验证工具核对。
