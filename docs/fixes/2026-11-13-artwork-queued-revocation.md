# OPSX 2.4 — 封面引用与文件提交门

依据R-2.9；24A446 `0x1001461c0`封面引用、`0x10006c034/6c1b0`文件setup/data。
HostArtworkState已用曲目generation隔离解码完成；本次不更改既有图片字节与空文件清除合同。
原5001封面引用无guard，旧引用排队后仍可发送；file guard在Link提交锁外检查并把取消当成功完成。
artwork guard取得对象锁，也可能与writer/callback锁序倒置。

此次引用改为sendGuarded，引用/setup/data都核对当前transfer及实际owner；guard只读volatile状态，
不取得artwork对象锁。file guard进入sendCsm后在writer分配序号前检查，取消用StaleIapSendException，
RuntimeIap把它作为本地撤销，不degraded真实链路；已提交包保持原可靠传输。
close释放图片/当前transfer，正常stop和Resources清理均调用，晚到callback忽略。

真实RuntimeIap/IapLink测试核对旧引用不提交、新引用/新SETUP匹配、旧file任务不耗序号且不degraded；
新增跨线程持artwork monitor时读取guard测试证明没有锁等待。既有换曲、超时、退订、file控制回归保留。
协议单测/小米编译记录在OPSX execution。DiPlay文件接收仍用实际源码联测复核；没有打包/安装/实车验证。
