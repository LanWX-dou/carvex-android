# OPSX 2.2 — 换曲显式清除旧媒体文本

依据：24A446 5001两个encoder与独立初始默认更新；R-2.8/2.10、已核UTF-8+NUL字段。
DiPlay实际CarPlayPlaybackStatus对缺失字段保留、空C字符串清除，属于接收合同，不据此推断全部Apple行为。
原publisher在replaceMedia时重置本地缓存但仅发送delta；新曲省略artist/album会让接收端保留旧曲文本。

此次只将替换时原本已知但新曲缺失的媒体文本(title/artist/album/genre/composer)补为显式空字符串，
先更新本地快照再按实际订阅发送。普通delta继续保留，explicit empty继续可清。
数字/布尔值/封面ID没有通用清除证据，不补零或伪造ID；当前接收的旧duration可能保留，需后续真实provider/清除合同。
应用/播放字段不由媒体文本清除规则制造值；独立START默认消息仍先于缓存真值，不改为一次实况初始化。

新增实际DiPlay源码联测从旧歌含歌手/专辑→新歌省略→歌手增量→零进度，检查空C字符串、接收清除、
省略未知数字及增量保留。原初始顺序/重订阅/Unicode测试继续回归。命令与结果见OPSX记录。
没有修改DiPlay生产代码、打包/安装或实车验证；数值失效与完整封面生命周期仍明确待证。
