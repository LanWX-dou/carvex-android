# 02 服务注册与 SDP 服务端

## 2.1 注册模型

**R-2.1** 设备**必须**以"属性列表"为单位注册服务记录，不得依赖隐式模板。属性列表的传输格式为：

```
+----------------+     +----------------+-------------------+
| 属性个数 N (2) |  →  | 属性 ID (2)    | 数据元素 (变长)   |  × N
+----------------+     +----------------+-------------------+
```

- 属性个数：2 字节**大端**。
- 属性 ID：2 字节**大端**，取值见 2.2。
- 数据元素：按 SDP 数据元素编码（类型 + 长度 + 值）。

**R-2.2** 设备**必须**支持以下属性 ID，且含义与 SDP 规范一致：

| 属性 ID | 名称 | 要求 |
|---|---|---|
| `0x0000` | ServiceRecordHandle | 由协议栈分配，注册输入中**不得**给出 |
| `0x0001` | ServiceClassIDList | **必须**包含；UUID 列表，**大端** |
| `0x0002` | ServiceRecordState | **应当**包含；32 位记录状态值，记录变更时更新 |
| `0x0004` | ProtocolDescriptorList | **必须**包含；其中 RFCOMM 协议元素后跟 1 字节通道号 |
| `0x0005` | BrowseGroupList | 应当包含 |
| `0x0009` | BluetoothProfileDescriptorList | 用于声明 profile 版本 |
| `0x0100` | ServiceName | **可以**包含；实测设备自身的 WiAP 记录**不含**该属性 |
| `0x0200` | ServiceDatabaseState | **可以**包含；用于 03 章的缓存优化 |

**R-2.2a** 抓包实测到的最小属性集为 `{0x0000, 0x0001, 0x0002, 0x0004}`（该记录不带 `0x0100` 名称，推断为设备自身记录；抓包无方向标志，不能据此断定方向）。对端设备实测额外包含 `0x0005`（值 `0x1002` PublicBrowseRoot）与 `0x0100`（名称如 `iAP2`、`RFCOMM-SPP`）。


**R-2.3** 属性 `0x0001` 的处理**必须**支持"一条记录多个服务类 UUID"：值是 UUID 列表，长度 2 或 4 视为短 UUID（16/32 位），长度 16 视为 128-bit UUID。

**R-2.4** 注册**必须**是幂等的：同一服务重复注册**必须**返回明确的"已存在"错误，而不是产生重复记录。

**R-2.5** 注册时**必须**为每条记录分配唯一的 32 位记录句柄，且句柄在会话生命周期内不变。

**R-2.6** RFCOMM 通道号**必须**由设备在注册时确定，并写入 `0x0004`；通道号与 DLCI 的关系固定为：

```
通道号 = DLCI >> 1
DLCI   = (会话方向位 | (通道号 << 1)) ^ 1
```

**R-2.7** 设备**必须**至少能同时持有多条服务记录的独立通道号；通道号取值 0–30 有效，同一会话内不得重复。

## 2.2 SDP 服务端请求处理

设备作为服务端**必须**实现三个请求：

| PDU | 名称 | 请求内容 | 响应内容 |
|---|---|---|---|
| `0x02` | ServiceSearchRequest | 服务搜索模式（UUID 列表）+ MaximumServiceRecordCount + continuation | TotalServiceRecordCount、CurrentServiceRecordCount、句柄列表、continuation |
| `0x04` | ServiceAttributeRequest | 记录句柄 + MaximumAttributeByteCount + 属性 ID 列表 + continuation | AttributeListByteCount、属性列表、continuation |
| `0x06` | ServiceSearchAttributeRequest | 服务搜索模式 + MaximumAttributeByteCount + 属性 ID 列表 + continuation | AttributeListsByteCount、属性列表、continuation |

**R-2.8** 服务端**必须**对 `MaximumServiceRecordCount` 与响应容量取**双约束**：

```
实际返回条数 = min( 请求的记录数, (MTU - 12) / 4 )
```

**R-2.9** 服务端**必须**在响应头固定占用 12 字节（PDU 头 + 字节计数 + 记录数 + continuation 长度 + 余量），每条记录句柄占 4 字节。容量不足时**必须**截断记录条数并置 continuation 非空，**不得**截断单条记录句柄。

**R-2.10** 服务端**必须**把所有整数与属性值中的整数字段按**大端**写入；128-bit UUID 按**大端**写入（与 EIR 相反）。

**R-2.11** 服务端**必须**实现 continuation state：

- 单次响应放不下时，返回已写部分 + 非空的 continuation 信息。
- 对端携带 continuation 再次请求时，**必须**从上次中断处继续，**不得**重启遍历。
- continuation 长度上限由对端 MTU 决定；无更多数据时 continuation 长度**必须**为 0。

**R-2.12** 服务端**必须**在收到非法 UUID 列表时报错并返回错误 PDU（`0x01` ErrorResponse），不得静默返回空列表。

**R-2.13** 服务端**应当**对"服务搜索模式无匹配"返回 `TotalServiceRecordCount = 0` 且 continuation 为空，而不是错误。

## 2.3 记录匹配语义

**R-2.14** ServiceSearchRequest 的匹配**必须**按"服务类 UUID 列表的交集非空"判定：请求的搜索模式中任一 UUID 出现在记录的 `0x0001` 中即为匹配。

**R-2.15** 一个 UUID 在搜索模式中出现多次时，**不得**产生重复匹配。

**R-2.16** 匹配结果的顺序**不**做规定（实现可任意），但同一请求的多次续读**必须**保持稳定顺序，否则 continuation 会重复/遗漏记录。

## 2.4 属性请求语义

**R-2.17** 属性 ID 列表**必须**支持两类写法：

- 具体 ID（2 字节或 4 字节范围形式）。
- 范围（起始 ID + 结束 ID），**必须**返回范围内所有存在的属性。

**R-2.18** 请求的属性不存在时**必须**跳过，不得插入空元素。

**R-2.19** `0x0000`（记录句柄）**应当**允许被读取，返回注册时分配的句柄。

**R-2.20** 服务端**必须**按 MaximumAttributeByteCount 限制返回值，并在截断时置 continuation；单条属性值**不得**被截断（要么整条返回，要么放到下一段）。

## 2.5 一致性判据

1. 注册一条含 2 个 128-bit UUID、1 个 RFCOMM 通道号、1 个名称的服务后，ServiceSearchRequest 能命中，且属性请求能取回全部 4 个属性。
2. 记录数超过 `(MTU-12)/4` 时返回条数被正确截断且 continuation 非空；续读能取回剩余记录且不重复。
3. 属性列表超长时按属性整条切分，不出现半个属性。
4. 所有整数为大端；128-bit UUID 与 EIR 中的字节序列互为逆序。
5. 非法 UUID 列表返回错误 PDU。

## 附录 A：本章依据

| 编号 | 结论 | 固件证据 |
|---|---|---|
| S-01 | 注册输入为"计数 + (属性ID, 元素)" | `0x10040b568` C 行 158–205；原型 `uint32_t XpcClassicConnection::addServiceDataToLocalSDP(NSData*)` |
| S-02 | 属性 `0x0001` 单独处理、UUID 长度分档 | `0x10040b568` C 行 242、271–288 |
| S-03 | 三个请求的原型 | 断言字符串：`ServiceSearchRequest(uint16_t, OI_BYTE_STREAM*, OI_BYTE_STREAM*, uint16_t, OI_L2CAP_CID)` 等（`0x1003ce304`/`0x1003ce9c4`/`0x1003cec64`） |
| S-04 | 记录数双约束与 12 字节开销 | `0x1003ce304` C 行 74–80、115–120（`(param_4 + 0x3fff4) >> 2`） |
| S-05 | 大端与 continuation | `0x1003ca1d8` C 行 42–79 |
| S-06 | RFCOMM 注册占 8 个通道槽 | `0x1002f1300` C 行 67–71、日志 `RFCOMM registration failed!` |
| S-07 | 通道号 = DLCI>>1 | `0x1003c1404` C 行 29；`0x1003c2314` C 行 25 |
