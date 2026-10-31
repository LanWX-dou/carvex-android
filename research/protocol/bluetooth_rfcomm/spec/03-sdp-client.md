# 03 SDP 客户端与通道号获取

## 3.1 客户端状态机

设备作为客户端时**必须**实现下列状态（状态名仅作标识，实现可另命名，但语义必须一一对应）：

| 状态 | 语义 | 允许的下一状态 |
|---|---|---|
| `IDLE` | 无查询 | `CONNECT` |
| `CONNECT` | 正在建立 SDP 的 L2CAP 通道 | `SEARCH`、`DISCONNECT` |
| `SEARCH` | 正在做服务搜索 | `DATABASE_QUERY`、`DID`、`DISCONNECT` |
| `SEARCH_D2D` | 设备到设备搜索（如需要） | `SEARCH`、`DISCONNECT` |
| `DID` | 查询 Device ID 记录（如需要） | `DISCONNECT` |
| `DATABASE_QUERY` | 协商数据库状态 | `DATABASE_CACHE_UPDATE_REQUIRED`、`DATABASE_VERIFY_COMPLETE`、`DATABASE_REMOTE_STATE_NOT_FOUND` |
| `DATABASE_REMOTE_STATE_NOT_FOUND` | 对端不支持数据库状态属性 | `DATABASE_RFCOMM_UPDATE`、`DISCONNECT` |
| `DATABASE_CACHE_UPDATE_REQUIRED` | 缓存失效，需全量查询 | `DATABASE_VERIFY_COMPLETE`、`DATABASE_RFCOMM_UPDATE` |
| `DATABASE_VERIFY_COMPLETE` | 缓存有效，可跳过全量 | `DATABASE_RFCOMM_UPDATE` |
| `DATABASE_RFCOMM_UPDATE` | 统计含 RFCOMM 的服务并逐条查属性 | `DISCONNECT` |
| `DISCONNECT` | 释放 SDP 通道 | `IDLE` |

**R-3.1** 状态机**必须**是单向推进的：除重连外不得回退到更早状态。

**R-3.2** 任一状态发生错误时，**必须**进入 `DISCONNECT` 并在释放资源后回到 `IDLE`，不得停留在中间态。

## 3.2 数据库状态协商（缓存优化）

**R-3.3** 客户端**必须**在 `DATABASE_QUERY` 状态读取对端记录的属性 `0x0200`（ServiceDatabaseState）。

**R-3.4** 状态比较规则：

| 本地缓存 | 对端状态 | 动作 |
|---|---|---|
| 已知 | 与本地相同 | 缓存有效 → `DATABASE_VERIFY_COMPLETE`，跳过全量查询 |
| 已知 | 与本地不同 | → `DATABASE_CACHE_UPDATE_REQUIRED`，执行全量查询 |
| 未知 | 对端也无该属性 | → `DATABASE_RFCOMM_UPDATE`（直接进入通道查询） |
| 未知 | 对端有该属性 | → `DATABASE_CACHE_UPDATE_REQUIRED`（全量查询）；完成后可写回本地缓存 |
| 任意 | 对端返回"属性不支持"错误 | → `DATABASE_CACHE_UPDATE_REQUIRED`，按全量处理 |

**R-3.5** 对端不支持 `0x0200` **不得**视为失败：**必须**降级为全量查询并继续。

**R-3.6** 缓存状态**必须**与对端设备标识绑定（例如按设备地址 + 服务记录集合指纹存储），不得全局共用一个值。

## 3.3 两阶段查询

**R-3.7** 客户端**必须**采用两阶段查询，不得假设一次 SearchAttribute 能取回全部记录：

| 阶段 | 请求 | 结果 |
|---|---|---|
| 1 | ServiceSearchRequest（按服务类 UUID） | 匹配记录的句柄列表（可能需续读） |
| 2 | ServiceAttributeRequest / ServiceSearchAttributeRequest（按句柄 + 属性 ID 列表） | 属性值（可能需续读） |

**R-3.8** `DATABASE_RFCOMM_UPDATE` 状态**必须**先筛出"协议描述符中含 RFCOMM"的记录，再对每条记录单独查属性；无任何 RFCOMM 记录时应正常结束（不报错）。

**R-3.9** 续读**必须**携带服务端返回的 continuation 信息；客户端**不得**自行拼接或猜测偏移。

**R-3.10** 客户端**必须**处理"续读返回的数据与首次不一致"的情形（服务端数据库在查询期间变更）：应当以最后一次完整结果为准，或整体重查。

## 3.4 通道号提取

**R-3.11** RFCOMM 通道号**必须**从属性 `0x0004`（ProtocolDescriptorList）中提取：

```
ProtocolDescriptorList
  └─ 元素 1: [L2CAP 协议 UUID][L2CAP 参数: PSM]      ← 实测可能只有 UUID，无 PSM 参数
  └─ 元素 2: [RFCOMM 协议 UUID][RFCOMM 参数: 通道号 1 字节]
```

**R-3.11a** 解析器**必须**容忍 L2CAP 元素**缺少 PSM 参数**的情形（实测记录为 `SEQ[SEQ[UUID16 0x0100], SEQ[UUID16 0x0003, UINT8 通道号]]`），不得因此把记录判为无效。

**R-3.11b** 解析器**不得**假设协议描述符中只有两个元素，也不得假设元素顺序（尽管实测为 L2CAP 在前、RFCOMM 在后）。

**R-3.12** 通道号取值**必须**校验在 0–30 范围内；越界视为无效记录。

**R-3.13** 若记录含 L2CAP 元素但无 RFCOMM 元素（如仅支持 L2CAP 的服务），客户端**必须**把它记为"L2CAP 服务（PSM）"，不得误判为 RFCOMM 通道。

**R-3.14** 客户端**必须**把 `{服务 UUID, 通道号}` 作为一对返回给上层；同一设备可有多个 `{UUID, 通道}`。

**R-3.15** 客户端**应当**同时保留记录句柄，供后续属性查询使用。

## 3.5 发起连接时的取值

**R-3.16** 发起 RFCOMM 连接时，目标通道号**必须**来自 3.4 的结果，**不得**写死为 1 或从本地配置猜测。

> 实测通道号在三个不同环境下分别为 **4、1、5**，确认"通道号非固定值"；写死任何常数都会在部分设备上失败。

## 3.7 实测请求形态（参考，非强制）

以下是抓包中观察到的真实请求形态，可作为互操作对照，**不构成强制要求**：

```text
# 类型 A：只查服务类与 profile
PDU=0x06 (ServiceSearchAttributeRequest)
  ServiceSearchPattern       : SEQ[ UUID128 <WiAP 或 CarPlay UUID> ]
  MaximumAttributeByteCount  : 672 (0x02A0)
  AttributeIDList            : SEQ[ UINT16 0x0001, UINT16 0x0009 ]
  ContinuationState          : 空（长度 0）

# 类型 B：用协议描述符筛选后再取通道
PDU=0x06
  ServiceSearchPattern       : SEQ[ UUID128 <WiAP UUID>, UUID16 0x0100, UUID16 0x0003 ]
  MaximumAttributeByteCount  : 100 (0x0064)
  AttributeIDList            : SEQ[ UINT16 0x0004, UINT16 0x0009 ]
  ContinuationState          : 空

# 类型 C：先列记录句柄
PDU=0x02 (ServiceSearchRequest)
  ServiceSearchPattern       : SEQ[ UUID128 <WiAP UUID> ]
  MaximumServiceRecordCount  : 64 (0x0040)
  ContinuationState          : 空
```

要点：

1. 搜索模式里出现 `0x0100`(L2CAP) 与 `0x0003`(RFCOMM) 两个 **16-bit UUID**，用于筛选"带 L2CAP+RFCOMM 描述符"的记录；
2. 属性列表只取 `0x0001`+`0x0009`（类型 A）或 `0x0004`+`0x0009`（类型 B）；
3. 所有观测到的请求 `ContinuationState` 均为空——**这不代表**可以不实现续读（长记录仍会出现，见 `02` R-2.11）。

> 依据：`runtime/observations/findings-sdp-hci.md` §3。

**R-3.17** 若同一设备同时广播新旧两套无线 iAP UUID，客户端**应当**按 UUID 版本分别记录，并在日志/上报中区分（如"新 UUID"/"旧 UUID"）。

**R-3.18** 连接参数（N1、信用窗口）**必须**由调用方显式给出，且满足 `N1 ≤ 信用窗口字节数`（见 04.2）。

## 3.6 一致性判据

1. 对端不支持 `0x0200` 时仍能完成通道号获取。
2. 缓存命中时**不**发起全量 ServiceSearchAttribute（可用报文计数验证）。
3. 长记录（> MTU）能通过 continuation 完整取回。
4. 无 RFCOMM 服务时正常结束，不产生错误上报。
5. 同一设备多记录时能返回多组 `{UUID, 通道号}`。
6. 连接使用的通道号与 SDP 结果一致。

## 附录 A：本章依据

| 编号 | 结论 | 固件证据 |
|---|---|---|
| C-01 | 11 个状态名 | 状态名表 `0x100bbde30`（11 指针，逐个字符串已读取） |
| C-02 | 状态 5/7/8/9 的语义与日志 | `0x100632af4` C 行 73–373 |
| C-03 | `0x322` = 属性不支持 | `0x100632af4` C 行 73；日志 `Remote device does not support ServiceDataBaseState restarting full SDP` |
| C-04 | 先筛 RFCOMM 再逐条查 | `0x100632af4` C 行 349–373；日志 `Found %lu services supported RFCOMM, starting channel query` |
| C-05 | 通道号取自解析结果 `+0x18` | `0x1007a3ba4` C 行 76–79、123–125 |
| C-06 | 客户端三 API 原型 | 断言字符串（`0x1003c9720`/`0x1003c9ab8`/`0x1003c9dd8`） |
| C-07 | PDU ID `0x02` | `0x1003c9720` C 行 67 |
| C-08 | 续读实现 | `0x1003ca1d8` C 行 42–79 |
