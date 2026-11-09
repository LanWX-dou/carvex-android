# 仪表音乐与导航推送核查（2026-11-09）

状态：已修复可确定的软件缺口，仪表显示仍为 OPEN；没有实车验收，未打包。

## 日志事实

输入为用户提供的 `D:\home\device-log.txt`，SHA256
`ccc437989185ad4f065dba559432478e40060677c3ffccf69a6694530d16f705`。
以下统计只取会话 `851b4936`，不复制歌曲、道路等用户内容。

| 事件 | 数量 / 位置 |
|---|---|
| RX `5000` / RX `5200` | 各 2 次，分别在蓝牙 bootstrap 与 runtime Link |
| TX `5001` | 34 次，包含初始化首报和后续音乐更新 |
| TX `5201` | 12 次 |
| TX `5202` | 0 次 |
| `Host action carlife_vehicle_music_info` | 33 次 |
| `Host action carlife_vehicle_music_progress` | 181 次，extras 为 `curTime,duration` |
| `Host action carlife_show_hud_info` | 12 次 |
| `Host action mix_notify_start_navi` | 6 次，extras 为 `isNavi` |

`Host action` 与 `host host-action:` 是同一回调的两条日志，计数不可混用。
bootstrap 在 1979 行接受组件 42 / mask 3；runtime 在 2210 行进入 CONTROL_READY，
2214 行后收到音乐订阅，2220 行后收到导航订阅。车机具备消息方向声明并且发起订阅，
所以“车机完全没有订阅/手机完全没有发送”不符合日志。TX / 队列接收也不等于仪表已显示。

## 已确认缺口与修改

1. 音乐 optionalAction 只处理 `carlife_vehicle_music_info`，遗漏独立进度广播。
   现在识别 progress action 的 `curTime,duration`，以增量更新发送，保留 0 进度并拒绝 u32 越界。
   单位沿用已有宿主适配器的毫秒约定；旧日志没有数值，不能据字段名宣称该宿主单位已实证。
2. 回调先替换 `latestMusic`，再启动协程读取共享最新值，导致消息间的字段和顺序不稳定。
   新增会话级 HostMusicRelay：锁内合并、直接提交不可变增量；runtime.send 只排队，不等待 ACK。
   AirSession 建立前的部分更新也会合并；音乐进度不会再当成整首歌曲替换快照。
3. runtime 回调未分派 `5200/5203`，发送却依赖 bootstrap 的全局 NavigationGuidance 状态。
   新增会话级 NavigationPublisher，按当前认证 Link 的能力、订阅组件和 options 发送；
   接受 STOP 后禁止三类导航更新，链路失效清订阅，重连必须重新 START。
   解析复用纯函数，bootstrap 全局状态不再授权 runtime 发送。订阅前的最新本地道路样本可缓存，
   START 时按新组件和 options 编码。这是本地数据缓存策略，不是声称固件存在相同缓存。
4. 视频 SETUP 后直接 `linkReady(true)` 并回放全局蓝牙音乐订阅，可能重置运行期订阅。
   移除这个路径，音乐发布器只由实际 RuntimeIap 状态和当前 Link 的 START 驱动。
   保留已有“初始化默认首报→真实快照”的顺序，不删除 default 初始化。
5. 增加出站字段 ID、queued 结果、HUD action/turn/distance、isNavi 值与类型、音乐时间数值诊断。
   不新增歌曲/道路正文日志；queued 仅表示本地发送队列接受，不表示仪表接受。

## 固件依据与边界

基线 accessoryd SHA256：
`2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`。

- `0x10017527c`：START；`0x1001753c0..0x100175404` 收集 U16 组件，
  `0x100175408..0x100175478` 校验 options，`0x100175590..0x1001755c0` 检查特性及消息集合。
- `0x10017593c`：STOP；`0x100175a44..0x100175a88` 检查组件参数，坏长度进入失败路径。
- 音乐编码器 `0x1001465c4` 与媒体项编码器 `0x10014569c`；本次不改字段 ID、类型、订阅顺序。
- 默认首报 `0x10008f588 / 0x10008f978` 保持不变。
- [导航 spec](../../protocol/iap2_input_business_lifecycle/spec/03-navigation-hud.md)：
  R-3.1、R-3.3～R-3.6 的声明、解析和停止要求。
- [先前 Now Playing 审计](nowplaying-pre-road-test-audit-20261031.md)：已记录视频 readiness
  与 bootstrap 全局订阅的隔离缺口。不能把跨 Link 迁移订阅当成固件行为。

## 尚未闭合，不能宣称仪表功能修复完成

- 初始化首报 status 为 STOPPED，但当前宿主没有已确认的真实播放器状态输入；后续音乐更新
  没有 status。仪表可能因此保持停止态，这是候选原因，尚无接收端证据。
  音频 lane 开关、按键发送成功、收到曲名都不等价于播放器实际 PLAYING/PAUSED，未做强制映射。
- 导航只发送已有的道路/距离字段；没有接入 route state、maneuver list 或 `5202` 转向。
  旧日志只记 HUD keys，不含 action/navi_turn/isNavi 数值；本地未找到对应宿主 APK。
  不能将宿主 turn 整数直接当 iAP maneuver type，也不能凭 action 名字猜开始/到达/结束。
- `remain_distance` 是到下一转向还是到终点，`road_name` 是当前路还是转向后道路，仍需宿主源代码
  或与操作对应的运行证据。本次保留原有映射，不将其升级为 CONFIRMED。
- 封面文件传输仍未实现；没有证据表明它是本次曲名无法显示的根因。
- 修改后的运行期需接收新的 START；仅在旧蓝牙链路订阅、不在 runtime 订阅的设备路径未验证。

下一步：核对当前手机版本的 CarWith APK 中生命周期与枚举定义，并与新的完整日志对照；
分别记录音乐播放/暂停/切歌，以及导航开始/转向/取消。确认宿主状态后再补相应 wire 字段，
最后检查车机接收与仪表显示。没有这部分证据不能通过硬编码状态来关闭问题。

## 验证

2026-11-09 最终代码运行：

```powershell
.\gradlew.bat :core:testDebugUnitTest :protocol-carplay:testDebugUnitTest :bridge:testDebugUnitTest :app:compileXiaomiDebugKotlin --console=plain
```

BUILD SUCCESSFUL；core 83、protocol-carplay 1061、bridge 19，共 1163 项，失败/错误/跳过均 0。
新增 11 项覆盖独立进度广播、连接前缓存、增量顺序、订阅前数据、runtime 组件隔离、坏 START/STOP、
停止与重连、能力闸门、options 重编码和跨会话隔离。`git diff --check` 通过。
本地单测不能证明车机已显示音乐或导航。没有构建 APK、安装或实车结果。
