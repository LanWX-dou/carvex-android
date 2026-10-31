# reference-impl — 自测用参考实现

这里的东西**不是**产品代码，只用于两件事：

1. 把"消息头/参数头/长度校验"写成可执行代码，让 `verify.py` 能算出与规范一致的字节；
2. 把生命周期状态机写成可执行代码，让 `verify.py` 能逐行比对 `spec/06` 的迁移表。

## 文件

| 文件 | 内容 | 对应规范 |
|---|---|---|
| `input_codec.py` | 6 字节消息头（`40 40 | 总长 BE | 消息 ID BE`）、参数头（`总长 BE | 参数 ID BE`）、U8/U16/数据长度校验 | `sess/R-3.x`、`R-1.2`、`R-1.10`、`R-2.3` |
| `test_vectors.json` | 7 组编码向量 + 4 个长度负例 | 同上 |
| `lifecycle_fsm.py` | `ACTIVE / SUSPENDED / RESUMED / DISCONNECTED / RECONNECTING` 与 11 条迁移 | `spec/06` 6.6 节 |

## 注意

- `test_vectors.json` 是**构造的**自测向量，不是抓包；它只保证"编码器与规范一致"，
  不能证明线上字节正确（见 `analysis/09`）；
- `input_codec.py` 只按长度推断类型，**不做**字段语义解释；
- `lifecycle_fsm.py` 里的"暂停定时器 / 保留或丢弃队列"是本文给出的实现约束，
  固件侧只证到"挂起/恢复走状态机、断开逐域回调"。

## 跑一遍

```bash
python3 input_codec.py     # 打印一条 0x6800 的编码与解码
python3 lifecycle_fsm.py   # 跑一遍迁移自测
cd .. && python3 verify.py # C13 / C14 校验
```
