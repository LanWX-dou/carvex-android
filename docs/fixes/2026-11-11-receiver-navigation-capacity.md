# 接收端导航机动缓存容量

GalaxyPlay 0.1.212 是实车目标；DiPlay `615b32c` 源码用于接收合同联测。
本轮没有运行或修改接收端，也没有实车结果。

`NavigationPublisher` 原先只把 Identification p30/p6 的正数容量当作启用条件，
却按 `maneuverGeneration & 0xffff` 不断分配索引。DiPlay 的
`BydHudRouteState.parseManeuverUpdate` 以 U16 索引保存定义、直到 `clear()` 才清空。
接收端容量为 8 时，第 9 个新机动就超过已声明的存储范围。

现在读取每个实际订阅组件的正数 p6，并按最小容量复用索引。该容量字段的 Apple
原证据是 24A446 accessoryd `0x1000c5704`，状态与机动枚举继续使用
[上一轮数值核心](2026-11-11-navigation-cluster-chain.md)的原表。
这属于本客户端尊重协商存储上限的策略，不把 DiPlay 代码当作 Apple 索引分配算法。
多组件、缺失/重复/零容量仍保留原有门控。

仅有一个存储槽时先发 NotActive reset，再发定义和引用/距离，以免新定义立即覆盖
当前引用，而距离仍是上一机动。未知箭头、缺失距离与结束清屏保留已证行为。
道路/ETA/车道来源未闭合，不新增虚构数据。多槽复用时定义与引用是分开的报文，
瞬时显示和实车效果仍待验收。

可选联测直接编译外部源码的原始 Kotlin 解析器；供应商源码只暂存到忽略的
`build/receiver-interop/`，不进入生产 APK：

```powershell
python -X utf8 -B tools/receiver-interop/prepare.py D:/Project/Lanwx/DiPlay
.\gradlew.bat :protocol-carplay:testDebugUnitTest --tests '*ReceiverProtocolContractTest' `
  --tests '*Navigation*Test' --offline --console=plain --no-configuration-cache `
  -I build/receiver-interop/receiver-tests.init.gradle
```

修复前实际联测复现导航容量和单槽混用两项失败。修复后 **56 项通过、0 失败、0 跳过**，
包含实际解析器的 100 个连续机动、八种已审箭头、距离更新、未知值与结束 reset，以及
最小多组件容量、U16 边界、START/STOP/重订阅和旧队列撤销。
完整输入哈希及最终全量验证见
[接收端兼容记录](../../../research/connection/spec/receiver-source-interop-20261111.md)。
