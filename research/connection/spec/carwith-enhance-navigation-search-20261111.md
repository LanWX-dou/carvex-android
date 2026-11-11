# CarWithEnhance 导航记录核查

日期：2026-11-11。用户提供 `ayuanStear/CarWithEnhance`，要求检查是否有当前全程剩余里程问题的相关记录。通过 Git 获取源码到本工作区忽略目录，读取主分支、两个公开分支及它们可达的历史；另作 GitHub Issues 只读查询。未安装或执行 Xposed 模块。

结论：在本次读取范围内，未找到高德全程剩余里程、HUD 导航字段、`NotifyNavigationInfo` 或 CarWith 导航数据出口的直接记录/实现。该项目没有提供可以补上当前 `5201 p7` 来源的线索。

## 已读版本与范围

| 公开分支 | 本次读取 HEAD | 提交日期与主题 |
|---|---|---|
| main | `3c3f15a20e885a42a80011f665d66d3c8d0437bd` | 2026-11-09，v2.4.6 auto precise 60fps |
| codex/panel-first-lyric-realtime | `65dbf15511a6cafc718439371a1fae3090d5fed5` | 2026-11-10，音乐服务连接时的冷启动唤醒 |
| codex/native-lyric-fallback | `4439a0daae928b78f08031a20af005433fe80fed` | 2026-11-11，使用 CarWith 原生歌词/面板路径、增加 LyricSourceHook |

读取三条分支和标签可达的 15 个提交；已取得的标签包括 v2.4.1、v2.4.2、v2.4.4、v2.4.6。GitHub Issues API `state=all&per_page=100` 返回 `[]`。这表示本次公开问题列表为空，不代表作者没有未公开记录或仓库之后不会更新。

源码/文档搜索包括 navigation、HUD、UCarMap、NotifyNavigationInfo、remain_distance、total_distance、route remainder、destinationRemainingDistance，以及导航、里程、剩余距离等；再对另外两条分支与完整已取得历史执行关键字符串搜索。没有检索私有分支或外部聊天记录。

## 容易误读的命中

主分支 `README.md:3` 与 `docs/IMPLEMENTATION.md` 将项目范围列为音乐面板、播放恢复、定制媒体页面、歌词、断连和帧率。`MainHook.java` 挂载 AutoPlay、MediaRoute、MediaTabSelection、LyricProgress、Settings、CarLinkState 等 Hook；CarLife 进程只挂精确帧调度 Hook，没有导航字段 Hook。

`docs/MEDIA-ISSUES-AUDIT.md:204–233` 的 `NavigationRouting.getInstance().go(new EmbeddingNavigationParams(...))` 属于“启动媒体应用”的页面选择：定制音乐页或原生 embedding 页。`CarWithMediaCapabilities.java:106–118` 的 `resolveRoute()` 定位字符串 `startMediaApp isNormalCastMode=` 并判断媒体页面能力。这里的 Navigation/Route 不是地图路线、剩余里程或导航模型。

“地图”命中来自播放器清理的保护应用规则和体验应用过滤；没有地图导航数据获取逻辑。

## 可参考与未解决的部分

可参考的是它在 CarWith 进程内用 Xposed/LSPosed、反射和 DexKit 定位原方法的做法。它已用于媒体服务、页面与歌词，不是现成的导航数据订阅接口，也不能证明某个内存对象中存在可读取的真实全程里程。

如继续采用进程内分析，需要先用原 CarWith/高德 APK 闭合全程里程对象和数据流，再评估如何交给 CarVeX。当前已核的标准 UCar/DataBus 路径仍只有提示距离和空标题，详见[MiAuto → CarWith 标准导航反查](miauto-carwith-navigation-20261111.md)及[高德生产者边界](carwith-amap-route-boundary-20261111.md)。任务 6.3–6.5 和 -1 米全程显示问题仍未完成。

本次仅核查参考项目，不修改手机或车机生产代码。GitHub 页面浏览工具无法取得页面内容；上述结论基于实际 Git checkout 与只读 GitHub API 返回，不是搜索摘要。
