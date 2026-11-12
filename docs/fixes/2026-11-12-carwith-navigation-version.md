# CarWith 4.0.23 导航版本适配

日期：2026-11-12。日志 7 的新版 CarWith 来源被仅接受 4.0.14 的解析器拒绝；两个已订阅会话共 132 条导航输入均为 rejected，没有规范化或导航出站消息。具体日志位置与原 APK 合同见[研究审计](../../../research/connection/spec/carwith-navigation-upgrade-20261112.md)。

`CarWithNavigation` 新增明确的 `4.0.23-20261016` 来源证据：开始/结束分别为 classes2 `0x1d3c14/0x17aae8`，HUD/米数/分类器/组表为 `0x17abdc/0x17a338/0x1ba904/0x1bae4c`。新版的 9 个方法与 18 个模板已经原字节核对；基础转向、正数机动距离和结束可以交给现有会话 relay 与 GalaxyPlay 数值发布链。旧版继续使用 H01，新增版本使用 H02，未知版本仍拒绝。

来源诊断增加 `reason=unsupported-version` 和 `reason=invalid-action-or-type`，使下次版本升级或错误类型能直接定位。道路角色、路线剩余距离/时间与车道继续缺独立来源/合同，不能把提示缓存作为全程里程，也不能估算剩余分钟。

新增回归覆盖新版开始、右转 128→127 的距离变化、2700 的斜右提示、两个结束通知、H02 证据、错误类型、非法距离和未审版本拒绝。已有旧版测试仍保留。

验证命令：

```powershell
.\gradlew.bat :host-carlife-mixing:testDebugUnitTest :bridge:testDebugUnitTest :protocol-carplay:testDebugUnitTest :app:compileXiaomiDebugKotlin --offline --console=plain
```

结果为 BUILD SUCCESSFUL，1 分 17 秒。宿主 25 项、bridge 60 项、协议 1,143 项 debug 测试 XML 均无失败、错误或跳过，合计 1,228 项。宿主/协议测试实际执行，bridge 使用有效 up-to-date 结果；小米 Kotlin 编译实际执行。沙箱无法创建 C:/.gradle 锁文件后，经批准使用本机缓存完成离线验证。[完整验证记录](../../../research/connection/evidence/carwith-navigation-upgrade-validation-20261112.json)。

本次未构建或安装 APK。用户复测时先确认 source 为 `4.0.23-20261016`、decoded 为 STARTED/UPDATED，再检查 normalized 和 `5202/5201` 发送；仪表箭头、距离递减、结束与重新开始分项记录。完整道路/车道/路线概览未完成，不能据这次版本修复标为全部通过。
