# runtime/ — 运行期样本

| 文件 | 说明 |
|---|---|
| `accessoryd-packets-2026-10-16-221117.log.ips` | 23G90 的 accessoryd 包日志，与控制会话阶段逐字节相同 |
| `parse-capture.py` | 解析脚本：默认只打印 `transport=AirPlay` 的连接；`--all` 打印全部 |

## 身份

| 项 | 值 |
|---|---|
| 大小 | 25,059 B |
| SHA256 | `7283f8a1d50c6c920198587f816c86aec996b7d749e84be7db771f5a7595dadd` |
| 构建 | 23G90（**不是** 24A446）|
| 行数 | 79 |

## 用法

```bash
cd research/protocol/iap2_airplay_tunnel
python3 runtime/parse-capture.py          # 只看 AirPlay 连接（40 帧）
python3 runtime/parse-capture.py --all    # 两条连接（74 帧）
```

脚本会校验每条 iAP2 消息的 `len` 字段与链路载荷长度一致，输出 `ok` 或 `LEN-MISMATCH`。当前样本全部为 `ok`。

## 为什么构建不同

抓包来自 23G90 设备（iOS 26.x 期），目标二进制是 24A446（iOS 27.0.1）。两者在这条链路上的**帧结构**一致，但**不能**据此断言 24A446 行为完全相同：

- 帧格式：由控制会话阶段在 24A446 上指令级确认（`control/R-3.1`），抓包只作旁证；
- 具体消息集合（本例 Location）：只证明 23G90 会这么做；
- 因此本目录的样本一律标 `23G90`，`A05.*` 的等级写作"运行期（23G90）"。
