# 全程距离与时间候选诊断

2026-11-14。用户要求给本轮找到的候选补充日志，供后续实车分析。

## 日志覆盖

在已有完整 `navigation event=raw-*` 捕获上增加候选索引。字段值仍保留真实类型、原始路径、文本 UTF-16/Base64 分段及二进制摘要；未改导航解码或 `5201/5202` 发布。

候选包括：

- `destinationRemainingDistance/destinationRemainingTime`。
- `ucar.map.bundle.TITLE_1/TITLE_2`，以及 `TITLE_1/TITLE_2/title1/title2` 别名。
- `remainDistance/remainTime` 与骑行模型的 `remainDistanceStr/remainTimeStr`。
- `arriveTime/arriveTimeZone`、`roadRemainingDistance/roadRemainingTime`。
- `remain_distance/total_distance/remain_time/total_time`，其中两个旧距离字段继续标为机动/机动参考量。
- 转发为 Intent action 或数据键时的 `onRemainInfoUpdate/onViaListRemainInfoUpdate/onRemainDistanceUpdate/onRemainTimeUpdate`。数组参数完整进入原始字段日志，参数顺序和单位不推断。

每个匹配的 `raw-field` 增加 `candidate` 和 `unit`。既有目的地输入试验标为 `meters-user-trial/seconds-user-trial`，其他未经确认的单位为 `unverified`。即使数值负、类型错误或值为 null，仍记录原值供分析。

每次捕获在 `raw-end` 前增加 `raw-candidate-summary`，沿用同一 source/binding/capture：

- `observed`：候选名、实际路径及 `present/null/error/action-only` 状态。
- `notObserved`：本次展开输入中未观察到的候选，不表示零或上游实际缺值。
- `opaquePaths`：原始 Parcel、序列化内容、未展开对象或读取错误所在路径。遇到这些路径时不能只根据 `notObserved` 断言字段没有在原始载荷中。

每个宿主绑定增加 `raw-candidate-observer`，标出 `channel=mixing-intent`、`nativeMapBundle=not-attached` 与 `easyconnNaviCallbacks=not-registered`。

## 嵌套输入

继续展开 Bundle、Map、列表及数组，另增加 JSONObject/JSONArray 的结构视图。64 Ki 字符以内的 JSON 文本保留原文后再生成 `<json>` 视图，较大文本仍完整分段捕获，不自动解析。

仅对已经送到本回调的四种已审对象调用公开 getter：`UCarMapInfo`、`BMapBridge.NavigationInfo`、`BikeNaviInfo`、EasyConn `HUDINFO`。原 Parcel/序列化视图保留在 `<raw>`；单个 getter 或序列化失败分别记录异常类型。不会创建 SDK 对象、读取其它进程、注册 SDK 导航回调或反射未知对象的 getter。

非标准 action 如果携带候选键、已审对象、嵌套容器或小型 JSON 候选，也进入诊断。候选发现限制为 128 个检查节点，列表/对象数组最多检查前 128 项；已识别导航 action 的原始捕获仍保存完整载荷。

CarWith 内部 `showNavInfo/fromBundle` 与 EasyConn 的实际回调不属于 CarVeX 当前 mixing AIDL 的可观测入口。这次增加的是收到候选时的完整记录和未接入边界日志，不代表已接通原生实时来源。

## 后续分析

导出后查找 `raw-candidate-observer`、`raw-candidate-summary` 及带 `candidate` 的 `raw-field`。先确认绑定版本与通道，再按 source/binding/capture 关联值、路径和类型。`TITLE_1/TITLE_2` 先对照地图屏显；回调数组先确认参数次序；目的地试验单位仍需实测。

回归覆盖显式零与 null/缺失区分、嵌套文本/数值/回调数组、已审对象 getter 与原序列化失败、未知 getter不调用、JSON 原文保留及导航解码不变、循环引用、日志 sink 失败及未接入来源状态。

最终执行 `:host-carlife-mixing:testDebugUnitTest :app:assembleXiaomiDebug --offline --console=plain --no-configuration-cache`，BUILD SUCCESSFUL（6 秒，161 tasks：9 executed / 152 up-to-date）。宿主测试本轮实际执行，JUnit XML 共 41 项，失败/错误/跳过均 0；5 项为新增候选诊断回归。首轮同任务亦通过（1 分 57 秒），其后补充嵌套候选发现及文本展开防重入并重新验证。

生成 `app/build/outputs/apk/xiaomi/debug/CarVex_xiaomi_debug_20052.apk`，76,084,977 字节；SHA256 `3f8c7c4fa372b37f2e8a898ab9a98d91febc776dcf9e1a2ca5e3c132fad95dec`。版本仍由当前 Git 提交计数派生为 20052，Debug 与 Release 按项目配置使用同一签名。检查 APK DEX 含新增诊断标记，生产编译 JAR 不包含测试用 `com.ucar.map` 类，`git diff --check` 通过。

机器验证结果保存在 `build/reports/navigation-candidate-logging.json`。本轮没有安装或实车观察。
