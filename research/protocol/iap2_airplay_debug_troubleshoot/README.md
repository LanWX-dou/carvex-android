# 仿 iPhone 客户端排障手册

目标：定位客户端连接 CarPlay 车机时的**第一个可证失败边界**，不是根据一个错误码猜根因。
设备=客户端/iPhone端，配件=车机。停车台架、自己的设备及获授权测试环境内使用。

先读 [30分钟定位流程](spec/01-diagnostic-model.md)，再按现象转入
[错误域表](spec/02-error-codes.md)、[抓包](spec/03-capture-filters.md)、
[日志](spec/04-logging.md)、[案例](spec/05-casebook.md)和[超时](spec/08-timeouts-recovery.md)。
采集前核对[检查清单](spec/06-checklist.md)。

状态：[STATUS](STATUS.md)。本版首次落实12项内容，但**尚无各层真实失败样本**，
不宣称30分钟效率已实测或真车互通。案例分为已执行的本地合成注入与仍待台架验证的方案。
参考代码不发送网络流量、不持有真实凭证、不实现客户端。

```powershell
python -B research/protocol/iap2_airplay_debug_troubleshoot/verify.py
python -B research/protocol/iap2_airplay_debug_troubleshoot/reference-impl/reproduce.py --case ALL
```

来源与可信边界见 [证据索引](analysis/00-evidence-index.md)，未决见 [OPEN](spec/07-open-items.md)。
测试成功不能升级任何现场根因结论；未知类型、端口或认证profile不能通过试错降级来“修好”。
