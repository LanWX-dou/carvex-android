# 09 搜索未命中与历史解析失败的边界

“查不到”只能限定在所检查字节/方法内，不能直接证明线上协议不存在某字段或算法。

---

## A-28 `FPLY` 字面量在三个镜像中都不存在

做法：对三份镜像的**全部字节**做模式扫描（大小写与字节序各一次）：

```
FPLY / FPLY 小写 / 'F','P','L','Y' 任意大小写 / 4 字节倒序 'YLPF'
```

结果：`AirPlaySender`、`AirPlayReceiver`、`AirPlaySupport` **命中数均为 0**。

推论（谨慎表述）：

- 只能说明扫描未找到连续字面量；分段写入、算术构造、运行输入或外部库都可能产生它。
- 不足以证明线上没有FPLY头，也不证明通过进一步反编译无法得到其字段依据。
- 结合 A-10（接收侧把 FP 响应当 `application/octet-stream`）与 A-08（发送侧把 FP 输出当
  `CMBlockBuffer`），可确定为：**载荷对上层完全不透明**，长度由核心给出。

`OPEN-12`保留：需实际载荷或进一步核心实现证据，不能从未命中推导否定结论。

## A-29 三类解析失败，必须记录（否则会被当成「没有」）

### (1) 没有 bind 信息

三份镜像都不含 `LC_DYLD_CHAINED_FIXUPS`，也不含 `LC_DYLD_INFO`/`LC_DYLD_INFO_ONLY`。
后果：`firmware/tools/import-resolve.py` 直接不可用；外部调用只能靠 `__TEXT_STUBS` + 桩表（A-03）。

### (2) 历史CFString解析失败，已由A-37修正

接收侧读键用的常量（`0x276118010`、`0x276118030`、`0x276118e70`、`0x2761199f0`、`0x276119a10`、
`0x276114350`）位于 `__AUTH_CONST.__cfstring`，结构里的 data 指针形如 `0x00200000d1935b2b`
（高位带 0x0020，低位不像任何镜像内地址）。已尝试且**全部失败**：

| 手段 | 结果 |
|---|---|
| Ghidra 反编译 | 只给 `cfstringStruct_276118010` 占位名 |
| `ipsw dyld dump` 同地址 | 得到的就是原始 qword，不解释 |
| `ipsw dyld extract` | 不解引用 |
| `ipsw dyld a2s 0x2591935b2b` | `address not within any mapping's address range` |
| `ipsw dyld str` | 需已知地址，鸡生蛋 |

以上只是旧方法失败记录，原稿“键名不可得”结论撤回。正确使用cache v5 slide信息后，
示例解析为`0x251935b2b`，不是表中误拼的`0x2591935b2b`。六个键名与调用点已在A-37–A-39闭合，历史OPEN-13关闭。

### (3) `ipsw dyld a2s` 会给出**错误但像真的**答案

对 `__TEXT_STUBS` 里的桩地址调用 `a2s`，它会把地址归到某个无关镜像的最近符号
（实测得到过 `HDCloudSyncCoordinator` 之类）。这是**假阳性**，比没有答案更危险。

纪律：导入符号只认两种来源——(a) 桩表命中；(b) 镜像自身的符号表。
两者都没有的地址，写「未解析」，不写猜测名。

## A-30 本阶段没有抓包可用（验收项 A2 未达成的直接原因）

工作区里唯一的时间序列数据是 23G90 的 **BT-classic iAP2** 抓包。它的第二条连接是 AirPlay
数据面，但**没有** `/fp-setup`、`/setup` 的 RTSP 明文，也没有媒体帧级的密文/明文对照。

因此：

- 「密钥交换 + 加密帧 + 解密」的**真实闭环无法闭合**。
- 本 docset 用「独立测试向量 + 参考实现」替代，但这**不能**替代抓包（`TASK.md` §6 A2 明确不许）。
- `STATUS.md` 必须写「未达成」，`runtime/README.md` 给出补抓的具体步骤。

## A-31 发送侧未发现直接调用屏幕 KDF（不能推出永远不用）

在线性直接调用扫描中，`APSEncryptionUtilsDeriveAESKeySHA512ForScreen` 的调用者只有一处：
`AirPlayReceiver` 的 `_AirPlayReceiverSessionSetup`（`0x2518d5c30`）。
本次抽样的 `AirPlaySender` 侧没有直接调用点（含通用版）。但扫描不含 `blraa`/`blr`、
虚表实现和外部上层模块，故这只是“未发现直接调用”的证据，不是全局否定。

所以：

- 更直接的反证是Sender的Legacy provider已有同一KDF实现（A-17/A-46）：
  `0x251aa9824/983c`两次直接调用`0x251aa9a60`，该函数直接调用CC_SHA512而非Support包装器。
  因此不是“发送侧可能复用”，而是“Sender内已存在同公式实现”；目标会话是否选中它仍需provider绑定。

结论写法：**Sender Legacy与Receiver均有该公式的正面证据；目标profile选择仍需核验，缺少对某一包装器的调用不能否定同算法。**
