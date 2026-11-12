# OPSX 2.3 — 5003请求与实况分离

原24A446 `0x10014aa20`及A14.3/C18：三个U32在解析结束后分别交平台elapsed、queue index、
queue window；仅p2=ffffffff为auto，p2即时请求依赖START子项11，p0/p1没有START active门。
原实现把请求值直接写入snapshot再发5001，混淆请求与播放器实况，且把p2高位U32当signed Int。

此次新增原始U32请求模型和原子解析，未知项忽略、非法已知长度不发起任何请求。
publisher将可执行请求交给显式provider接口，独立记录parsed/platformRequestQueued/observedExecution。
没有provider明确拒绝，不修改观察快照、不发5001；生产AirSession目前不注入provider。
p0/p1不依赖START；p2即时请求单独门控。provider接受仍不代表播放完成，实况只能由真实update进入。
没有根据未证时间单位新增seekTo/队列执行，真实provider、单位、归一化与失败反馈继续OPEN。

新增测试覆盖U32高位/auto、原子失败、无provider无快照改写、实际hook接收而不回写、
独立window门与provider拒绝。协议单测和小米编译在OPSX记录；没有打包/安装/实车验证。
本项修正了伪执行；完整真实播放器请求验收仍未满足。
