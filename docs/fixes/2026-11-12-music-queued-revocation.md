# OPSX 1.2 — 音乐订阅撤销检查覆盖未提交5001

依据：24A446 accessoryd START替换/STOP移除对应endpoint的订阅（`0x1001499f0`、
`0x10014a93c`，R-2.11、生命周期R-6.8/6.14）。未提交任务撤销是本地并发策略，
不改变原可靠传输或推断新的Apple超时。

原AirSession用RuntimeIap.send排队5001，只有链路代际门，STOP后旧任务仍能进入writer。
此次NowPlayingPublisher每次成功START、STOP、linkReady边界递增原子订阅代际，
初始默认消息、缓存快照和增量均携带该代际guard。非法START先验证再替换，不撤销旧订阅。
AirSession使用sendGuarded并合并关闭/源owner条件；writer分配序号前检查，读guard不取得业务锁。
已经提交的整条CSM继续分片、ACK、重传，不在业务撤销时截断。

新增真实RuntimeIap/IapLink串行writer合成测试：STOP、替换、失效、重新ready无START、
非法START保留旧消息、已提交分片完成，核对序号及链路不degraded。
最低协议单测和小米Kotlin编译结果在OPSX执行记录。没有打包/安装/实车验证。
