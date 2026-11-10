# G11：Android 网络回调与短暂 L2 断链边界

2026-11-10，本轮已取得可读取的 Android 原 SDK 源码，替代前次在线获取失败的状态。未修改生产网络策略，G11 仍为 OPEN。

读取 `D:\Android\Sdk\sources\android-36\android\net\ConnectivityManager.java`，API36 / Extension17 / sources revision1，SHA256 `9221bfc0177a0cf90ba8891f463f27daf0a30678fb9d425740bd2bed986375b6`。本机没有 API37 sources；API36 的说明及当前[官方 NetworkCallback 文档](https://developer.android.com/reference/android/net/ConnectivityManager.NetworkCallback)用于核实平台接口含义，不作为当前设备 ROM 行为或 Apple 状态机依据。

| 已读源码位置 | 已确认的接口边界 |
|---|---|
| 4278–4298，onLost | 网络断开或不再满足请求/观察条件都可能触发，不能从一个回调推出物理 Wi-Fi 去关联。 |
| 同段，registerNetworkCallback | 逐个报告不再满足条件的网络；本工程复用路径使用此接口，且只处理与原 active 相等的 Network。 |
| 同段，requestNetwork | 关注请求当前选择的网络；最后一个网络失效且无其他匹配时报告丢失。本工程 specifier 路径使用此接口。 |
| 4968–4975，requestNetwork | 更优网络出现后 onAvailable 改为报告新网络，并停止观察旧网络，除非旧网络后来重新成为最优。 |
| 4261–4294，onLosing/onLost | 不保证先有优雅切换通知，也不建议在回调中同步查询 LinkProperties/Capabilities 判定刚收到的状态，以免读取到不同时间的快照。 |

当前 `Bootstrap.kt` 复用路径收到匹配 Network 的 onLost 后失败；specifier 路径在选中 Network 丢失后拒绝等待或结束已交付会话，网络被替换时也结束会话。两个路径已有取消/注册释放与代际检查。协议会话把 socket 绑定至选中 Network，没有实现跨 Network 迁移。

这些接口说明既未承诺旧 socket 在 onLost 后继续可用，也没有定义“短暂 L2 抖动”是否会撤销当前 Network。因而当前尚不能将 onLost 全部忽略、添加固定宽限时间、在回调中同步查询并据此重绑，或把当前立即失败策略直接称为已证明的根因。

仍需目标设备 Android/ROM 的网络代理事件、Network身份与socket I/O关联：区分物理重关联、请求条件变化、租约撤销、Network替换与真实TCP错误；证明同一Network及旧socket可保留的条件，再与原Apple的失败预算对齐。未执行干扰/切换实测，也未新增空生产代码或把资料核对算作修复。
