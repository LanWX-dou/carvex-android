# OPSX 1.4 — 音乐缓存与发布 owner 关闭

依据R-6.8/6.9/6.14与R-7.4/7.5/7.7，本地清理策略：先禁止新业务、撤销未提交工作，再释放资源。
原HostMusicRelay没有close，保留AirSession回调与快照；Publisher可以被晚到ready重新打开。
此次relay注册到会话Resources，close清除回调与缓存，late update/attach忽略，detach只保留无授权快照。
publisher.close永久关门、递增guard并清快照；AirSession正常stop及资源释放均调用它。
桥接释放musicAir/图片引用，关闭中的AirSession拒绝新增图片事件。
现有navigation relay、scope、artwork事件channel与loader已由各自资源owner关闭，未改变认证或TEARDOWN顺序。

新增测试覆盖detach后只缓存、下一publisher等待自己START、重复close和late callback拒绝，
真实writer核对close后旧5001取消且late ready/START不能恢复。协议/bridge单测和小米编译见OPSX记录。
文件引用/文件writer更细的在途撤销另属2.4；未声称本项完成真实SUS/Resume。没有打包/安装/实车验证。
