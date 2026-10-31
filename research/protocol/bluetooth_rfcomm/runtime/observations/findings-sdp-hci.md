# 运行时观测（首轮）：HCI 抓包中的 SDP 交互

采集对象：`D:\carvex-research\sysdiagnose` 下三个构建的 `logs/Bluetooth/*.pklg`（HCI 抓包）。

> **构建一致性声明**：本目录三份素材的构建是 `22H374`(iOS 18)、`23G90`(iOS 26)、`21G93`(iOS 17)，**都不是**本套文档的固件构建 `24A446`(iOS 27.0.1)。因此本文件的一切内容都是**跨构建佐证**，不得用于确认数值常量，也不改变任何 `CONFIRMED` 条款的证据等级。

## 1. 提取方法（可复现）

| 步骤 | 说明 | 工具 |
|---|---|---|
| 1 | pklg 记录解析：`[len:4be][ts_sec:4be][ts_usec:4be][type:1][payload]`；实测 `type=1` 为 HCI Event、`type=3` 为 ACL 数据 | `firmware/tools/pklg-rfcomm.py` |
| 2 | ACL 重组：按 `handle` 分桶，`PB=0b01` 为续片，其余为首片；再按 L2CAP `[len:2][cid:2][payload]` 切帧 | 同上 |
| 3 | 从 L2CAP 信令（CID `0x0001`）的 Connection Request 找 PSM=3(RFCOMM) 与 PSM=1(SDP) 的通道 | 同上 |
| 4 | 在 L2CAP 载荷里按 UUID 的两种字节序匹配，命中后按 SDP 数据元素 `[type:5][size:3]` 解码 | `firmware/tools/dump-sdp-records.py` |
| 5 | tracev3 日志按关键字扫描（未压缩段 + lzfse 分块解压） | `firmware/tools/scan-tracev3-keys.py` |

原始解码输出（未编辑）：

- `2026-10-14-22H374-sdp-raw.txt`
- `2026-10-16-23G90-sdp-raw.txt`
- `2026-10-16-21G93-sdp-raw.txt`

## 2. 结论 A（**已作废，见修正**）：曾判定 RFCOMM 帧为 0

> **本节的表格与结论已被推翻。** 当时的解析器只收 ACL 类型 3，且把 TX/RX 分片按同一 handle 混合重组，
> 导致所有 RFCOMM 帧被静默丢弃。修正后同一批文件的 RFCOMM 帧数为
> **126 / 44 / 173 / 194**，命令层可见 PN、MSC 与 iAP2 载荷。
> 正确的结论与逐帧数据见 `runtime/captures/2026-10-rfcomm-pklg-reanalysis.md`。
> 保留本节是为了记录这条错误结论的成因，避免再次把"工具缺陷"当成"事实为零"。

原始错误结论（留作对照）：曾判定三个窗口内 RFCOMM 通道"只建立了 L2CAP 请求、没有后续帧"，
并据此认为 `spec/07` 的帧测试向量无法获得线上佐证。

## 3. 结论 B：SDP 真实交互形态（可直接对照实现）

### B-1 iPhone 作为 SDP 客户端发出的请求

`ServiceSearchAttributeRequest`（PDU `0x06`）实测形态：

```
PDU=6  tid=0x0024  paramlen=30
  ServiceSearchPattern : SEQ[ UUID128 00000000-deca-fade-deca-deafdecacafe ]
  MaximumAttributeByteCount : 672 (0x02A0)
  AttributeIDList      : SEQ[ UINT16 0x0001, UINT16 0x0009 ]
  ContinuationState    : 长度 0
```

变体（同一构建内出现）：

```
ServiceSearchPattern : SEQ[ UUID128 <WiAP UUID>, UUID16 0x0100, UUID16 0x0003 ]
MaximumAttributeByteCount : 100 (0x0064)
AttributeIDList      : SEQ[ UINT16 0x0004, UINT16 0x0009 ]
```

`ServiceSearchRequest`（PDU `0x02`，23G90 捕获）：

```
ServiceSearchPattern : SEQ[ UUID128 00000000-deca-fade-deca-deafdecacafe ]
MaximumServiceRecordCount : 64 (0x0040)
ContinuationState    : 长度 0
```

要点：**只查 `0x0001`+`0x0009`，或 `0x0004`+`0x0009`**；把 `0x0100`/`0x0003` 放进**搜索模式**（而不是属性列表）用来筛选"含 L2CAP+RFCOMM 描述符"的记录。这与 `spec/03` 的两阶段查询一致，并给出了真实取值。

### B-2 一条不带 ServiceName 的记录（22H374）

> 方向说明：本批 pklg 未记录每条 ACL 的方向标志，因此**无法**仅凭抓包断定该记录由设备自身发布。判据是"属性集恰为 `{0x0000,0x0001,0x0002,0x0004}`、无 `0x0100` 名称"，与设备自身记录的特征一致，故标为**推断**。

`ServiceAttributeResponse`（PDU `0x05`）实测：

```
AttributeList = SEQ[
  UINT16 0x0000, UINT32 65550,                 # ServiceRecordHandle
  UINT16 0x0001, SEQ[ UUID128 00000000-deca-fade-deca-deafdecacaff ],   # ServiceClassIDList = WiapSink
  UINT16 0x0002, UINT32 329452940,             # ServiceRecordState
  UINT16 0x0004, SEQ[ SEQ[UUID16 0x0100], SEQ[UUID16 0x0003, UINT8 4] ] # L2CAP -> RFCOMM ch=4
]
ContinuationState = 0
```

**这条记录没有 `0x0100`（ServiceName），RFCOMM 通道号为 4。**

### B-3 三个构建里出现的对端记录

| 构建 | 服务类 | 通道号 | `0x0100` 名称 | 其他属性 |
|---|---|---|---|---|
| 22H374 | WiapSink | **4** | 无 | `0x0002` |
| 23G90 | WiapSink | **1** | `RFCOMM-SPP` | 无 `0x0005` |
| 21G93 | WiapSink | **5** | `iAP2` | `0x0005` = [0x1002] |
| 21G93 | Carplay（逆序字节） | 4 | `iAP2` | `0x0005` = [0x1002] |

推论（标为运行时候选，未升级为 `CONFIRMED`）：

- iPhone 自身记录用 `{0x0000, 0x0001, 0x0002, 0x0004}`，**不发布 ServiceName**；
- 对端（车机/配件）可能发布 `0x0005` BrowseGroupList、`0x0100` ServiceName，名称常见 `iAP2` / `RFCOMM-SPP`；
- **通道号不是固定值**：观测到 1、4、5 三种，实现方必须从 SDP 读取，不能写死（对应 `spec/03` R-3.16）。

## 4. 结论 C：SDP 线上的字节序——CarPlay 族是**逆序**（重要）

| UUID 族 | 固件内存（`__const` 实测） | EIR 上线（代码逆序复制） | SDP 线上（本批抓包） |
|---|---|---|---|
| WiAP `…deca-fade-deca-deafdecacafe/ff` | 文本序 | 逆序 | **文本序** |
| CarPlay `ec884348-cd41-40a2-9727-575d50bf1fd3` | 文本序 | 逆序 | **逆序** = `d31fbf50-5d57-2797-a240-41cd484388ec` |
| CarPlayGateway `2d8d2466-e14d-451c-88bc-7301abea291a` | 文本序 | 逆序 | **逆序** = `1a29eaab-0173-bc88-1c45-4de166248d2d` |

证据：

- 22H374 中 4 条独立 SSAR 的搜索模式都是 `1a29eaab-…`（CarPlayGateway 的逆序）；
- 21G93 中一条属性响应的 `0x0001` 值为 `d31fbf50-…`（Carplay 的逆序），且该记录同时带 `0x0100 = "iAP2"`，可判定为 CarPlay/iAP2 用途；
- 三个构建、多条独立报文一致，不是偶发。

**对实现的影响**：在 SDP 里按 `ec 88 43 48 …`（文本序）去匹配 CarPlay 服务**一定匹配不到**；必须用 `d3 1f bf 50 5d 57 27 97 a2 40 41 cd 48 43 88 ec`。

静态分析侧的事实（已复核，未受影响）：`0x1003d56fc` 的名称比较用**文本序**立即数（如 `0x1003d58b8` 构造 `0xa24041cd484388ec`），而 EIR 复制循环是**逆序**读取。因此"同一 UUID 在不同 API 路径上字节序不同"是本实现的既有事实；为何 CarPlay 族在 SDP 上也走逆序，标 `OPEN-RUN-1`。

## 5. 结论 D：tracev3 日志侧暂不可用（方法限制）

对 197 个 `*.tracev3` 按关键字扫描（`RFCOMM Channel connected`、`Initiating outgoing Wireless IAP`、`No registered server on DLCI`、`ServiceDataBaseState`、`frameSize` 等）**全部 0 命中**，而 `ComPortHandler` 有 5–7 次命中。原因是 os_log 归档的消息串与参数并非明文存储（字符串表为编码形式，数值参数压缩），本方法无法还原。

因此：**"0 命中"不能解释为"这些代码路径没有执行"**，只能说明"本方法在该素材上无效"。日志侧佐证需要完整的 tracev3 解析器（catalog + cimes + 类型化参数解码），记为 `OPEN-RUN-2`。

## 6. 本轮对文档的影响

| 影响 | 处理 |
|---|---|
| SDP 交互形态得到实测佐证 | 在 `spec/03` 增补观察到的请求形态（标注"观测值，非强制"） |
| 记录属性集得到实测佐证 | 在 `spec/02` 属性表补 `0x0002 ServiceRecordState`，并注明 iPhone 自身记录不含 `0x0100` |
| **CarPlay 族 SDP 字节序为逆序** | 在 `spec/01` 增补 §1.3.3 与强制警告；`analysis/01` 记录为运行时候选 |
| 通道号非固定（1/4/5） | 强化 `spec/03` R-3.16 的"必须从 SDP 读取" |
| RFCOMM 帧级未获佐证 | 在 `STATUS.md` 明确保留，`spec/07` 测试向量仍以固件为准 |
| 新增 OPEN | `OPEN-RUN-1`（CarPlay 族 SDP 逆序的原因）、`OPEN-RUN-2`（tracev3 解析能力） |
