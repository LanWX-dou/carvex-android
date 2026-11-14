# 导航订阅、容量与关闭合同（OPSX 3）

起点手机 `f2a0283`、接收 `5436f91d`；两端既有提交不重写。

依据：24A446 accessoryd `10017527c` START、`10017593c` STOP、`1001777c0`机动编码；
原镜像和完整切片由本轮 `verify_protocol.py` C16/C18及九消息核对通过。
显示声明沿用已核 `1000c5704` p30/p0组件、p6容量。
关闭为[本地资源所有权要求](../../../research/protocol/iap2_input_business_lifecycle/spec/07-cleanup.md) R-7.4/7.5，
不宣称已实现完整 Apple SUS/Resume 或精细组件 STOP。

原实现的 AirSession 释放只 detach 导航发布器；迟到 linkReady/attach/START 可重新建立其本地授权。
新增幂等永久 close：撤销原子 delivery token、源回调、订阅及能力；所有后续准入拒绝。
正常 stop 立即 close，资源释放重复 close 安全。writer guard仍只读原子token/无锁快照；
已提交CSM依原可靠传输完成，新owner由新发布器独立订阅。

现有方向必需表、空选项/非法替换、无组件门、单槽reset/定义/引用、最小容量复用保持原实现。
新增显示能力替换撤销及旧batch失败不影响新batch回归。
实际 DiPlay parser 新增双组件0/65535、最小容量3/100次机动、65534/65535/Long.MAX_VALUE代际与引用；
新增重算未知机动、重建、未知原因结束及新路线清除合同。
真实接收器未按组件分离缓存，测试只验证原parser消费与实际wire组件列表，不宣称多物理显示屏验证。

本轮协议/bridge/宿主回归和小米 Kotlin 编译成功，90 tasks：10 executed/80 up-to-date。
实际接收合同17+2完整执行/存在，failure/error/skipped均0；摘要在根工作区
`local-backups/2026-11-14-align-business/phase-3-receiver-results.json`。
生产Debug Kotlin输出不含接收源码。未打包、安装或实车验证。
