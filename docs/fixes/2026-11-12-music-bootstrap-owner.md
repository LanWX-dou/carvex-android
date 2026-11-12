# OPSX 1.1 — 蓝牙音乐订阅不跨 endpoint 交接

原依据：24A446 accessoryd 5000/5002 handler `0x1001499f0` / `0x10014a93c`，
新 START 替换对应 endpoint 订阅；R-2.11/2.12 与生命周期清理。原字节复核记录见研究仓库
`openspec/changes/align-business-lifecycle-and-push-fields/protocol-contract.md`。

原 SessionController 在 Bluetooth bootstrap 将命令写入全局 pendingSubscription 并返回true；
搜索全源码没有读取者。AirSession 用独立 Link、AIRPLAY_IAP identification和认证代际，
该全局字段不能授予新端点发送权限。此次删除全局字段和虚假成功callback；没有同Link发布器
时沿既有Bootstrap未支持日志路径处理，后续runtime仅由实际START授权。普通音乐快照缓存不携带订阅。

新增合成配件在真实ByteStream/Link/CSM边界发送START→STOP→START→5003→Wi-Fi handoff，
断言四条命令逐条未支持、没有5001输出且认证/handoff正常完成。它只验证本地owner隔离策略，
不证明Apple所有早期订阅路径或实车显示。最低协议单测、bridge单测和小米Kotlin编译结果登记在OPSX执行记录。
没有打包、安装或实车验证；Bluetooth music publisher仍未实现，未声称支持。
