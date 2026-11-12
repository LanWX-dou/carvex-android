# 导航原始输入完整日志

日期：2026-11-12。用户确认右转规划正确，要求打印所有导航信息，实车测试后再判断车道与全程距离/时间。此次只增加输入诊断和提取工具；现有导航解析、快照、规划与 wire 发布合同沿用已有实现。

此前 `CarWithNavigation.diagnostic` 只打印预选字段及文字/图标哈希，无法检查未打印的 extras。本次在宿主回调入口记录全部实际键和值，包括未知字段、错误类型和 null；嵌套 Bundle、Map、集合、SparseArray 与原始/对象数组逐层展开。开始/结束通知及 HUD 回调均记录，未通过版本或类型解码的输入也记录。其他 action 名含 navi/hud/lane/route/map 的回调作为候选同样记录，不因此修改其原处理分支。

日志包含 `navigation event=raw-begin/raw-field/raw-end`，按日志会话、source、binding 和 capture 编号关联。field 的 JSON payload 保存路径、原 Java 类型、编码与分段编号。数值保持原类型/值，不推断单位；文本的完整 UTF-16 code units 和所有 byte[] 以 Base64 分段保存，每段最多 2048 个编码字符，包含字节数和 SHA256。文本预览最多 512 个字符，完整值从 Base64 还原，没有截断原数据。JSON 转义避免换行拆记录及原日志脱敏器修改实际载荷。

Bitmap 转为 PNG；其他 Parcelable 和 Serializable 保存其完整编码字节，无法序列化时记录错误类型；其他不支持的对象明确以 toString 记录。循环/重复容器记录原路径引用，避免无限展开。单个字段或日志 sink 出错不拒绝有效 HUD。新增捕获不将图片或原始数组留在导航快照中。

这轮按用户明确要求记录原始道路文字、未知字段及图片内容，是针对本次实车调查的完整输入日志；旧摘要仍保持脱敏。导出的设备日志和还原数据只保留本地，不加入仓库。

## 实车测试后读取

用户自行构建并安装新代码。测试前清除旧日志，保留从连接到导航结束的完整日志；在车道提示出现和全程距离/时间变化时记下界面数值及时间，然后导出日志。旧日志 8 没有新增原始记录，无法用本工具补出当时未记录的图像或字段。

```powershell
python -X utf8 -B research/connection/tools/extract_navigation_raw.py 'D:/home/device-log (9).txt' --output local-backups/navigation-field-test
```

输出 `navigation-raw.json`，每个字段包含原路径、类型和完整文本/数值；图像/二进制另存 `.png/.jpg/.bin/.parcel/.ser`，文件名由编号生成。工具核对全部分段、字节数、哈希和回调开始/结束计数，缺段或字段读取失败会标记 incomplete 并返回非零，不猜测缺失内容；不会执行或反序列化第三方对象。

## 验证

新增五项宿主回归，覆盖未知/嵌套车道候选与原类型、13,301 字节图标完整还原、长中文/换行/引号/代理字符还原、循环及字段/日志失败，以及回调编号/其他导航 action。宿主 30 项全部通过；协议 1,146 项有效 up-to-date，小米 Kotlin 编译通过，最终 Gradle BUILD SUCCESSFUL。全部 Gradle 命令显式使用 `--gradle-user-home D:\Java\gradle`，不更改全局环境。

使用实际编译的 formatter 生成两段合成回调，再交给 Python 提取器：长文本、13,301 字节数组、PNG、嵌套车道和原数值均完整还原；缺段、冲突哈希检查及原日志脱敏兼容通过。118 个本地文档链接和空白检查通过，OpenSpec 严格校验通过。合成载荷和还原产物仅保存在忽略的 local-backups 目录；源码哈希与结果见[验证记录](../../../research/connection/evidence/navigation-full-input-validation-20261112.json)。

Android Bitmap/Parcel 的实际设备编码及新日志实车导出仍待用户测试。这些诊断不表示车道或全程字段来源合同已完成，OpenSpec 保持原未完成项。
