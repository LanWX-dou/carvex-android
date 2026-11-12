# 日志 7：CarWith 升级后导航输入被拒绝

日期：2026-11-12。目标为 CarWith → CarVeX → GalaxyPlay。用户确认下一次转向、距路口距离与道路、车道、全程剩余公里和分钟均未显示。原日志仅留在用户本机；入库为[脱敏观测](../evidence/navigation-source-log7-20261112.json)。

## 首个断点

`device-log (7).txt` 为 Release 20033，2,665,988 bytes / 19,936 行，SHA256 `da960902e8b6353d37a768c0eeaba2a9342179b38a135911351951ce84270259`。它保留多次旧会话，不能把早期已发送的 245 米机动作为后续会话已经恢复的证据。

| 会话 | 当前 Link 接受订阅 | 宿主来源事件 | 规范化事件 | 导航出站消息 |
|---|---|---|---|---|
| `8392ec2a` | 第 6,927 行，组件 42 / options 3 | 111 条，全部 rejected | 0 | 0 |
| `d76de65f` | 第 17,494 行，组件 42 / options 3 | 21 条，全部 rejected | 0 | 0 |

132 条来源记录均为 `version=4.0.23-20261016 decoded=rejected`；其中 6 条开始/结束通知、126 条 HUD 通知。原解析器在 `source.version != "4.0.14-20260801"` 时立即返回 null，所以没有进入 relay，也没有构建 `5201/5202`。这是本次发送链路的直接断点，不能解释为车机没有订阅或当前没有宿主输入。

例如第 11,302 行有严格 Boolean true 的开始通知；第 11,386 / 11,461 行有 `navi_turn=3`、128 / 127 的原距离整数；第 18,479 / 18,577 行有 `navi_turn=2`、2700 / 2600 的原距离整数。这些数值在新版原 APK 审计完成前仅是来源观测，不用于猜测 Apple 枚举。

相关来源日志发生于 2026-11-11 UTC，最新 2026-11-12 启动记录不包含新的导航试验。早期 `549f0b99` 有 5 次规范化与 10 条导航出站记录，属于日志保留历史。

## 新版原 APK 审计

用户随后提供 `CarWith_4.0.23-20261016.apk`，56,209,661 bytes，SHA256 `c897a45d92c84f06e670fc4edd323824093a093f67d8e7d7b058fee2a737d06c`。aapt 原 manifest 读取为 `com.miui.carlink` / `104000023` / `4.0.23-20261016`。以下为 classes2.dex 的 code_item 地址；[证据 JSON](../evidence/carwith-navigation-upgrade-20261112.json)记录方法归属、完整签名、原指令哈希与资源哈希。

| 合同 | 新版方法 / 原位置 | 与已审 4.0.14 的核对 |
|---|---|---|
| 开始 | `map.wms.j$b0.g`，`0x1d3c14` | 布尔开始分支写 `mix_notify_start_navi` / `isNavi=true`，随后交宿主控制入口 |
| 结束 | `LauncherDataBusClient.D`，`0x17aae8` | `isNavi=false` 与 HUD 整数 action=3；不区分取消/抵达 |
| HUD | `LauncherDataBusClient.F`，`0x17abdc` | classifier 输出 navi_turn；原六字段、action=1/2 和提示参考缓存路径相同 |
| 距离 | `LauncherDataBusClient.x`，`0x17a338` | 米与公里转换一致；“现在”、未知单位、异常可能为零，不能据零推定抵达 |
| 图标分类 | `map.l.d`，`0x1ba904` | 同一地图模板选择、0.8 置信门和原组码消费 |
| 模板组表 | `map.l.<clinit>`，`0x1bae4c` | 构造指令的资源后缀/组码和表写入一致 |
| 组码读写 | `map.l$a.<init>/a/b`，`0x1ba61c/0x1ba5ec/0x1ba604` | 第二构造参数写组码，b 返回组码，a 返回后缀 |

从原 DEX 反汇编核对以上 9 个方法：对应指令数量、寄存器、分支和业务常量一致；差异为方法/类的重命名及表索引重排，已逐项阅读，未用重命名后的字节哈希直接宣称完整 APK 等价。aapt2 重新确认 18 个已审模板的资源路径，其 PNG 原字节全部与 4.0.14 审计相同。因此仅将已审基础方向和正数机动距离合同扩展到这个明确版本。

```powershell
python -X utf8 -B research/connection/tools/inspect_carwith_navigation_upgrade.py D:/home/CarWith_4.0.23-20261016.apk
```

复核器 PASS 验证 APK 身份、9 个方法归属/签名/原指令哈希和 18 个未变化模板，不执行厂商代码，也不验证仪表显示。

## 实施范围与尚缺字段

`CarWithNavigation` 为两个已审版本选择独立 H01/H02 来源证据，保留未知版本拒绝和严格类型。日志新增 `unsupported-version` / `invalid-action-or-type` 原因。原 4.0.14 的行为、H01 地址和未知字段策略保持一致。新版输入恢复到当前 relay / GalaxyPlay 数值发布链；Apple 编码及接收兼容证据沿用[数值核心](navigation-numeric-core-20261111.md)。

| 用户希望显示的内容 | 本次处理结果 / 后续条件 |
|---|---|
| 下一次转向箭头 | 接通新版已审基础组码 2/3/4/5/7/8；其他组仍 unknown |
| 距下一机动多少米/公里 | 接通严格 Int 正数提示距离到现有机动发布；显示单位交接收端 |
| 进入哪条道路 | 当前 road_name 仍保留观测；道路角色、完整文本能力/编码合同待闭合 |
| 路口车道箭头 | 当前六字段 HUD 未提供结构化车道；本次 GalaxyPlay Identification 未声明 `5204`，不伪造车道 |
| 全程剩余公里 | total_distance 在新版仍为提示缓存，不能填全程值；继续需要独立路线距离来源 |
| 全程剩余分钟 | 当前 HUD 未提供剩余时间；需要实际来源与单位，不用距离估算 |

测试及修改文件见 [Android 实施记录](../../../android/docs/fixes/2026-11-12-carwith-navigation-version.md)。本轮修复版本适配，不声明完整导航功能完成。未构建或安装 APK，修复后实车显示仍 OPEN。
