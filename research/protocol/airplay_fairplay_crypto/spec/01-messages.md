# spec 01 消息与承载

## R-1.1 FairPlay 交换走「流消息」通道，操作码固定为 `fp25`

承载方式：把 FP 载荷包成 `CMBlockBuffer`，用流对象的 vtable 方法（`[+0x10]+0x38`）发出，
第一个参数是 32 位操作码 **`0x66703235`**（ASCII `"fp25"`）。
接收侧对应的响应也是二进制块，不是文本。
在控制面，该 `fp25` 操作码对应 RTSP **`POST /fp-setup`**、`Content-Type: application/octet-stream`
（control `analysis/05-rtsp-methods.md:53`）；vtable 与 HTTP 是同一载荷的两层描述，不是两条不同通道。
依据：A-08（`0x251ace8d0`/`0x251ace8d4`）、A-10（`application/octet-stream`）、control `analysis/05`。级别：A。

## R-1.2 FP 载荷对上层不透明，长度不固定

- 发送侧：载荷长度由 FairPlay 核心的输出长度决定（`outLen`），包成 `CMBlockBuffer` 后原样发出。
- 接收侧：响应长度同样由核心给出。
- 实现**不得**假设固定长度，也不得假设载荷内部有可解析的自描述头。
依据：A-08（`0x251ace858`、`0x251ace8f8`）、A-28（无 `FPLY` 字面量）、`OPEN-12`。级别：A。

## R-1.3 握手是「状态字节驱动的循环」，不写死轮数

```
state = ?
while (true) {
    发 request(载荷 = 上一步输出或首个空载荷)
    收 response → (ptr, len)
    core(type=3, hwInfo, ctx, ptr, len, &out, &outLen, &state)
    if (state == 0) break;        // 完成
    if (state == 1) continue;     // 继续
    error(0xfffee786);            // 其它值
}
```

**不要**在文档或代码里写「恰好 N 轮」；轮数由 `state` 决定，属于运行时行为。
依据：A-08（`0x251ace818`、`0x251ace820`、`0x251ace918`）。级别：A（循环结构）/ C（实际轮数）。

## R-1.4 安全信息在 `/setup` 路径处理

- `/fp-setup` 只负责把 FairPlay 上下文建立起来。
- `/setup`（binary plist；control `R-5.1`）的调用者进入安全信息处理，字典键为`et`/`ekey`/`eiv`。
- 仅这些调用点不证明所有流都必须逐流包含三键；完整schema层级/profile仍需核实。
依据：A-24、A-26、A-37/A-39。级别：A（调用点与键名）；完整schema未闭合。

## R-1.5 已核字段拼写与所在接口

| 字段 | 形态 | 取值约束 | 证据 |
|---|---|---|---|
| `X-Apple-ET` | 请求头；范围整数getter，键长10 | getter成功时8→type2、32→type3，其他错误 | A-37/A-38 |
| `CSeq` | 请求头；字符串getter，键长4 | ET getter失败后按返回指针是否非NULL选type2/3 | A-38 |
| `et` | 安全信息字典整数，键长2 | FP解封分支接受8/32；getter错误或1另有早退 | A-39 |
| `ekey` | 安全信息字典数据，键长4 | 密文长度不固定；FP解出后必须16B | A-24/A-37 |
| `eiv` | 安全信息字典数据，键长3 | IV16B，不经FP包裹；传输层可另加密 | A-12/A-24/A-37 |

上述键名已由原镜像、dyld v5指针和getter调用闭合（历史OPEN-13已关闭）。
`IsPINRequiredForPairing`是内部属性，不要据此向线上添加同名字段。
`et`/`ekey`/`eiv`的schema位置与必填条件不能仅靠这些函数泛化。
依据：A-37–A-39。级别：A（本build键名与本地分支）。

## R-1.6 本地字典清理不等于线上一次性

所分析的 Receiver 正常收尾路径删除本地字典中的 `ekey`/`eiv`。这不证明所有车机都会如此处理，更不证明重连必须重做完整 FairPlay、或对端会拒绝重复字段；重连/密钥生命周期仍须额外证据。独立客户端应避免不受控的密钥/nonce 复用，这是安全策略而非由删除操作推出的线上规则。
依据：A-24 末段（`CFDictionaryRemoveValue`）。级别：A（本地清理）/ OPEN（线上生命周期）。
