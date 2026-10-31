# 实测前只读核查（2026-10-31）

范围：首报调用路径、会话隔离、手机资源清理。保留待测版本，不增加生产改动、测试文件或打包。本记录不替代实车验收。

待测NowPlayingUpdate.kt SHA256：`a530d3d33c7eea8606733fc380bb66afc6515334e6d010a07a0235886d174361`。

## 主路径

- AirSession实例独占NowPlayingPublisher；SessionController每次attempt独立创建latestMusic/musicAir。真实快照不是全局对象。
- RuntimeIap在认证识别完成后进入CONTROL_READY，再poll业务消息；AirSession按双方能力集合放行5000/5002/5003。有效START统一进入publisher，默认首报先于已有真实快照，方法同步串行化。
- 后续真实更新同样经publisher和runtime.send → IapLink单线程asyncSender，既有顺序不会因为两次emit而颠倒。
- linkReady调用会清selection，不会复用旧运行期订阅；新AirSession也有独立publisher。但以下旧的bootstrap暂存例外尚未隔离。

## 待修边界：bootstrap订阅暂存（不是本轮修改）

1. NowPlayingUpdate.pendingSubscription为object上的全局volatile，SessionController bootstrap回调直接写入，没有attempt/peer/link epoch。
2. AirSession视频SETUP后直接linkReady(true)，然后读取暂存订阅，调用command后无条件清空，并无条件记录replayed；不检查command返回值。
3. 此时runtime可能还未CONTROL_READY，runtime.send会拒绝首报。新publisher会撤销发送资格，防真实信息越过失败首报，但调用方没有保留重试机会。
4. 若bootstrap收到订阅后失败，未进入该回放点，暂存值没有明确清理点；可能残留到下一attempt。若无display，prepare提前返回，亦绕过此回放点。
5. 直接linkReady(true)不证明runtime身份验证通过；状态回调之后仍可清除订阅。应由对应链路的身份/就绪状态控制，不能用视频SETUP当作iAP业务ready。

以上是静态存在的隔离/交接缺口，不应靠把全局变量改为另一个全局标志解决。后续需先确定蓝牙订阅能否合法迁移到独立runtime Link，再考虑绑定attempt/epoch、失败重试和无视频路径。不能假设沿用蓝牙订阅就是苹果行为。

现场d292b55a/e3e7b3d6：视频SETUP日志11:01:17.741514 UTC，runtime的5000帧11:01:18.765462、CONTROL_READY11:01:18.825681，没有bootstrap subscription replayed记录。原始帧先被接收不等于业务已在认证前消费。该现场主要适用新的runtime首报修复，不能将bootstrap边界直接认定为其根因。

## 待查独立问题：手机资源关闭可能无限等待

- VendorCastHost.close先设置closed=true，再同步remote.stopCast()；AIDL为普通void方法，非oneway。runCatching只捕获异常，不限定等待时间。后续unlink、清引用、scope.cancel和unbind排队均须等待此调用返回。
- Resources.close逐个逆序执行close；已移出注册表锁，但没有对每个资源设置执行上限。一个close不返回，后续资源仍不能继续清理。
- SessionTermination.cleanup直接调用r.close；completion仅在cleanup返回/抛异常后完成。closing=true之后forceClose不会重新进入，故它不能解开一个已堵住的Binder调用。
- SessionController正常disconnect等待cleanup及job结束，disconnecting门保留；此条件可表现为按钮无法再次启动。故障attempt的finally同样等待清理，可能影响自动重试。

d292b55a中四个attempt最后都出现mh2 close开始却无完成。按本地mapping，mh2对应VendorCastHost；没有现场APK哈希绑定，不能把映射作为绝对身份确认，更不能仅凭入口日志断定具体卡在stopCast。

后续若需修改，应先增加分段可定位证据并设计Binder超时后的隔离/幂等清理；不要仅套协程timeout就声称能终止同步Binder。当前不改变待测版本。

## 实车结果（2026-10-31）

用户反馈本次连接不再掉线，仪表盘歌词正常显示。主路径的首报修复得到实车正向验证。

以下原先的分流规则保留给后续稳定性/重连复测。

## 后续复测如何区分

- 音乐播放后控制响应持续、手动断开后重新连接成功：支持初始首报修复了主要触发链。
- 播放稳定，但断开卡住/无法再次点击连接：检查手机资源关闭链，不能直接归咎于Toyota。
- RFCOMM连通但只有ACK无SYN：继续核查旧Toyota会话恢复和蓝牙对象生命周期；本轮没有新增该路径的固件证据。
- 没有歌曲信息，但画面/连接正常：核查订阅/首报回放，不把元数据缺失等同于链路断开。

不清配对、不恢复出厂；保留从连接开始到失败/断开的完整日志。本轮未重新跑测试，因为未改变待测代码。
