# 接收导航输出owner与扩展字段边界（OPSX 4）

手机基线 `7ac992c`，DiPlay基线 `5436f91d`；具体修正提交与本轮报告见
[执行记录](../../../openspec/changes/align-business-lifecycle-and-push-fields/execution.md)。
本项修改接收端本地输出所有权，沿用已有wire合同，没有新增Apple字段或SUS恢复行为。

DiPlay原worker只检查入队时accepting，clear只删除队列；已经出队及旧调用方重启后提交的任务没有owner保护。
现在controller向BydNavigationOutputs传入身份，旧controller不能提交或清理新输出；
无线generation/实际channel、USB实际channel形成无锁source guard，入站和worker执行前分别检查。
Bluetooth业务保持到runtime tunnel确认ready；分配tunnel对象本身不替代认证完成。

worker按owner和原子generation撤销queued/init/clear/failure；旧失败回调不停止新代际。
溢出、初始化或帧执行失败都会撤销待处理增量流，清理后由实际start恢复。
厂商调用已进入时不能强制撤回：它返回后，旧结果被clear，新initialize再执行。
生命周期方法不等待厂商调用；worker不获取controller/publisher锁。
输出模式变化释放不再使用的worker。

7个原worker测试扩展覆盖上述阻塞/owner/source/失败/overflow边界；
另有两个实际输出overlay分派测试，检查旧controller及旧link不能修改/清理新卡。
receiver-interop直接复制这些原worker源码和测试，并新增多域/非法输入/文本/展示过期合同。
其成功不证明厂商硬件已完成显示。

扩展调查见[边界表](../../../openspec/changes/align-business-lifecycle-and-push-fields/extension-boundaries.md)：
afterRoad保持已确认角色；文字最大长度计量、真实ETA/剩余时间/lane provider与全程距离试验仍OPEN。
测试中的lane值是人工输入，没有启用生产5204。
实际实车状态仍OPEN；完整编译/测试的最终命令与范围见执行记录。

2026-11-14接收端修正提交`ad4ccbfb`的shared/common/home生产编译通过；
common 1730、home 11项测试均无失败/跳过，三个应用lint无错误并成功构建Debug。
shared 1807项中3个既有符号链接用例缺Windows权限、2个环境用例跳过，完整CI仍FAIL。
手机最终串行回归成功：协议1195、bridge65、宿主36，failure/error/skipped均0；
20+2接收合同和7个原worker测试齐全。两个Debug生产Kotlin输出无接收或联测类。
暂存输入篡改反例被结果工具拒绝，原字节已恢复并复核。
