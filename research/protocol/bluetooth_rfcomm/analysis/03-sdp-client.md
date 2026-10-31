# 03 SDP 客户端：查询流程与通道号获取

覆盖需求项：**（3）SDP 记录 / 属性 / RFCOMM 通道**中"客户端如何查到通道号"部分。

## 1. 目标

1. SDP 客户端的状态机有哪些状态（固件枚举值）。
2. 查询是如何被"数据库状态协商"优化的。
3. 从"服务记录"到"RFCOMM 通道号"的解析路径。
4. 发起 RFCOMM 连接前，通道号从哪个字段取出。

## 2. 结论

### C1 SDP 客户端状态枚举（固件字符串表）`CONFIRMED`

状态名表位于 `0x100bbde30`，11 项，被日志 `SDP Client State Change: %s -> %s` 与 `Service database state response with state %s` 使用。直接读取指针数组得到：

| 值 | 名称 |
|---|---|
| 0 | `SDP_IDLE_STATE` |
| 1 | `SDP_CONNECT_STATE` |
| 2 | `SDP_SEARCH_STATE` |
| 3 | `SDP_SEARCH_D2D_STATE` |
| 4 | `SDP_DID_STATE` |
| 5 | `SDP_DATABASE_QUERY_STATE` |
| 6 | `SDP_DATABASE_REMOTE_STATE_NOT_FOUND` |
| 7 | `SDP_DATABASE_CACHE_UPDATE_REQUIRED` |
| 8 | `SDP_DATABASE_VERIFY_COMPLETE_STATE` |
| 9 | `SDP_DATABASE_RFCOMM_UPDATE_STATE` |
| 10 | `SDP_DISCONNECT_STATE` |

依据：`f_100632af4` C 行 50–52 用 `(&PTR_s_SDP_IDLE_STATE_100bbde30)[state]` 取名字，且 `state < 0xb` 边界检查；表中 11 个指针均指向上述字符串。

另有解析器侧状态（`SDP_PARSER_*`）与服务器侧状态（`SDP_DATABASE_*` 子状态）作为独立字符串存在，说明客户端把"查询"和"解析"分成两层。

### C2 数据库状态协商：先比对，再决定全量查询 `CONFIRMED`

`0x100632af4` 是数据库状态响应回调（日志 `Service database state response with state %s, more %d, status %u`）。

| 依据 | 内容 |
|---|---|
| C 行 73 | `(int)param_3 == 0x322 && state == 5` → 远端**不支持** `ServiceDatabaseState` 属性 |
| C 行 79 | 日志 `Remote device does not support ServiceDataBaseState restarting full SDP` |
| C 行 105 | 置状态 7（`SDP_DATABASE_CACHE_UPDATE_REQUIRED`）→ 走全量 SDP |
| C 行 194 | `FUN_1005ebdf0(pcVar, &elem, 0x201, &out)` 解析响应数据元素（模板长度 `0x201`） |
| C 行 197–198 | 取 `*(int*)(elem+8)` 作为**远端数据库状态值** |
| C 行 215 | `if (remote == local)` → 置状态 8（`SDP_DATABASE_VERIFY_COMPLETE_STATE`，缓存有效，跳过全量） |
| C 行 245 | 否则置状态 7（缓存失效，需更新） |
| C 行 280–288 | 本地状态未知（`local == -1`）且远端也无状态 → 日志 `Local database state not found and remote state does not exist, move onto RFCOMM` → 置状态 9 |
| C 行 302–309 | 本地未知但远端有 → 日志 `Local database state not found, but remote state exists, full SDP` → 状态 7 |
| C 行 327/328 | 状态 7 后 `FUN_100017938()` / `FUN_100007104()` 触发全量查询 |

`0x322` = 802，作为"属性不支持"的错误码；`param_3 == 0` 表示成功。

### C3 状态 9：统计 RFCOMM 服务并逐个查通道 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| C 行 349 | `if (state == 9)` |
| C 行 350–351 | `iVar3 = FUN_1005fc024(session+0x70)` → 返回支持 RFCOMM 的服务条数 |
| C 行 358 | `iVar3 == 0` → 日志 `No RFCOMM services, we're done`，清零 `+0x80` 并结束 |
| C 行 369–370 | 否则日志 `Found %lu services supported RFCOMM, starting channel query` |
| C 行 372–373 | `uRam...100c1f619 = 0`（遍历游标清零）；`FUN_100634b7c()` 发起逐条属性查询 |

即：客户端**先筛出"协议描述符里含 RFCOMM"的记录**，再对每条记录单独查属性（典型是查 `0x0004` ProtocolDescriptorList），而不是一次性拉全部属性。这与 SDP 规范推荐的"两阶段查询"一致。

### C4 服务记录 → `{服务 UUID, RFCOMM 通道号}` 的解析 `CONFIRMED`

函数 `0x1005e6ce0`（C 行 10 起，555 行），日志 `Services dictionary: %@`。

| 依据 | 内容 |
|---|---|
| C 行 107–110 | 取/建 `NSMutableArray`（`param_1 + 0x5e0`）作为结果容器 |
| C 行 119–126 | 遍历会话内已解析的属性链表（`param_1 + 0x2c8`，`+0x2d0` 为哨兵） |
| C 行 194 | `FUN_1005ebdf0(attr, &elem, 0x201, &out)` 解析数据元素 |
| C 行 197 | 判定元素头字节：`*p == 1` 表示"属性 ID 列表"型元素 |
| C 行 288 | 短 UUID 路径：`length < 5` 时取 `*puVar13` 作为 UUID 值并 `FUN_1003c8e9c(uuid, &out)` 规范化 |
| 字面量 | `RFCOMM ServiceClass: `、`service short UUID: (0x%x)`、`service long UUID: %@`、`L2CAP PSM: 0x%x` |
| C 行 546 | 结束时日志 `Services dictionary: %@` |

产出字典的键是 `kCBMsgArgServiceUUID` + `kCBMsgArgRFCOMMChannelID`（或 L2CAP 的 `kCBMsgArgPSM`），证据来自同族函数 `0x10040c934` 的键集合（见 `05` 的 C6）：

```
kCBMsgArgDeviceUUID / kCBMsgArgResult / kCBMsgArgRFCOMMChannelID /
kCBMsgArgMTU / kCBMsgArgIsIncoming / kCBMsgArgSocket / kCBMsgArgServiceUUID
```

### C5 发起 RFCOMM 连接时通道号来自 SDP 解析结果 `CONFIRMED`

`0x1007a3ba4`（无线 iAP 出向连接）：

| 依据 | 内容 |
|---|---|
| C 行 61–64 | `FUN_1005ebdf0(param_2, &tmpl, 4, &out)`，其中 `tmpl` 来自 `PTR_DAT_100bca680`（元素类型模板） |
| C 行 76–79 | 命中条件：`p[0]==0x06 && *(short*)(p+2)==2 && *(char*)(*(char**)(p+8))==0x03 && *(int*)(rec+8)==3 && rec[0x10]==1` |
| C 行 79 | `uVar8 = *(uint *)(pcVar6 + 0x18)` ← **通道号取自解析结果 `+0x18`** |
| C 行 113–115 | 日志区分 `New WiAP UUID` / `Old WiAP UUID`（由 `param_2` 的最低位决定） |
| C 行 123–125 | 日志 `Initiating outgoing Wireless IAP connection request to device %{public}s on rfcomm channel %d, %{public}s` |
| C 行 134–135 | `FUN_1003c2b00(cb, &link_cfg, device+0x80, channel, 0x3ef, 0x3b01, &out, &ctx)` |
| C 行 147 | 失败返回 `0x131` |

解析结构中 `+0x08 == 3 && +0x10 == 1` 是"协议描述符里 RFCOMM 协议 + 通道号参数"的判定；`+0x18` 是通道号。`PARTIAL`：这几个偏移是解析器内部结构，未与 SDP 线上的 `0x0004` 属性字节做逐字节映射，见 `OPEN-SDPC-3`。

### C6 客户端三个 API 及其 PDU 构造 `PARTIAL`

断言字符串给出的原型：

| 地址 | 原型 |
|---|---|
| `0x1003c9720` | `OI_STATUS OI_SDP_SearchReq(OI_SDP_SEARCH_RSP_CB, uint16_t, const OI_DATAELEM *)` |
| `0x1003c9ab8` | `OI_STATUS OI_SDP_AttributeReq(OI_SDP_ATTRIBUTE_RSP_CB, OI_SDP_SERVICE_RECORD_HANDLE, const OI_DATAELEM *)` |
| `0x1003c9dd8` | `OI_STATUS OI_SDP_SearchAttributeReq(OI_SDP_SEARCH_ATTRIBUTE_RSP_CB, const OI_DATAELEM *, const OI_DATAELEM *)` |

`OI_SDP_SearchReq`（`0x1003c9720`）的组包过程：

| 依据 | 内容 |
|---|---|
| C 行 31–33 | 前置条件：`状态非 0/2/3`、`param_2 != 0`，否则静默返回 |
| C 行 35–36 | `*(short*)(state+0xc) = param_2`（最大记录数），`*(ushort*)(state+0x32) = 0`（结果计数清零） |
| C 行 38 | `FUN_100314a48()` 计算 UUID 列表元素长度，返回 `0xfffe` 则中止 |
| C 行 42–45 | 总长 = 元素长度 + `0x18`；若超过缓冲上限则中止 |
| C 行 47 | `FUN_10000d0cc(len, 0x100004052888210)` 分配请求缓冲 |
| C 行 67 | `*puStack_50 = 2` ← **PDU ID = 0x02（ServiceSearchRequest）** |
| C 行 74 | `uStack_44 = 5` 写入位置 = 5（PDU 头 1 + 2 + 2 之后） |
| C 行 75 | `FUN_100314cc4(&bs, param_3)` 写入 UUID 列表数据元素 |
| C 行 79–80 | 写 2 字节最大记录数（高字节在前） |
| C 行 85 | 写 1 字节 continuation state 长度 = 0 |
| C 行 88 | 记录总长到 `state+0x12` |
| C 行 89 | 保存回调 `state+0x14 = param_1` |
| C 行 90 | 内部字节位置 `state+8 = 3` |
| C 行 92 | `FUN_1003c9a00()` 发送 |

PDU ID `0x02` 与 SDP 规范的 ServiceSearchRequest 一致，可确认该函数对应"服务搜索"。

## 2.7 运行时佐证：真实的客户端请求形态（跨构建）

抓包（`runtime/observations/findings-sdp-hci.md` §3）解出三类真实请求，逐一对应上文结论：

| 观测 | 与静态结论的关系 |
|---|---|
| `PDU=0x06`，`SearchPattern = SEQ[UUID128 <WiAP>]`，`MaxAttrByteCount = 0x02A0`，`AttributeIDList = SEQ[0x0001, 0x0009]`，continuation 空 | 佐证 C6 的"PDU 0x06 + 属性 ID 列表"形态，并给出真实取值 |
| `PDU=0x06`，`SearchPattern = SEQ[UUID128 <WiAP>, UUID16 0x0100, UUID16 0x0003]`，`MaxAttrByteCount = 0x0064`，`AttributeIDList = SEQ[0x0004, 0x0009]` | **新事实**：搜索模式里可混入 16-bit UUID 作为协议描述符筛选条件；对应 `03` C4 的"先筛 RFCOMM 记录"策略 |
| `PDU=0x02`，`MaxServiceRecordCount = 0x0040` | 佐证服务搜索阶段存在（对应状态 2/3） |

**对 `03` C4 的补强**：C4 说的是"先筛出含 RFCOMM 的记录再逐条查属性"；抓包显示筛选是通过**搜索模式里附加 `0x0100`+`0x0003`** 完成的，而不是本地过滤句柄——这为 `spec/03` R-3.7/R-3.8 提供了实现路径的实证。

## 3. 对实现的约束（进入 spec）

1. 客户端必须实现"先查 `ServiceDatabaseState`（属性 `0x0200`），相同则跳过全量"的优化；远端不支持该属性时应回退全量。
2. 两阶段查询：先按服务类 UUID 找记录句柄，再按句柄查属性；不要假设一次 SearchAttribute 能拉全。
3. continuation state 必须处理（见 `02` C5）。
4. RFCOMM 通道号来自 `0x0004` ProtocolDescriptorList 中 RFCOMM 协议元素之后的 1 字节参数，取值 0–30 有效。
5. 失败/超时必须能回到 IDLE 并允许重试；状态机共 11 态。

## 4. 未决

| 编号 | 内容 | 原因 |
|---|---|---|
| `OPEN-SDPC-1` | 状态 1（CONNECT）、2（SEARCH）、4（DID）的具体转移条件 | 只确认 5/7/8/9 的转移，其余状态在未抽样函数中 |
| `OPEN-SDPC-2` | `0x1003c9720` 中 `state+8 = 3` 的字段语义 | 与状态枚举同值但字段偏移不同（枚举在 `+0x84`），判定为不同字段 |
| `OPEN-SDPC-3` | 解析结果 `+0x18` 与 SDP 线上 `0x0004` 属性的逐字节映射 | 解析器结构未与线上字节对照 |
| `OPEN-SDPC-4` | 客户端查询超时值与重试次数 | 未在抽样函数中定位到常量化超时 |
