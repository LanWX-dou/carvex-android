# 02 服务注册、SDP 本地数据库与 SDP 服务端

覆盖需求项：**（2）CarPlay 服务注册与 UUID**、**（3）SDP 记录 / 属性 / RFCOMM 通道号**。

## 1. 目标

1. iPhone 侧"注册一个经典蓝牙服务"到底做了什么。
2. 本地 SDP 数据库的入口格式、属性 ID 处理、记录句柄分配。
3. SDP 服务端三个请求的处理边界（记录数上限、响应字节预算、continuation state）。
4. RFCOMM 通道号在 SDP 中的位置，以及它由谁决定。

## 2. 结论

### C1 本地服务注册的输入是"属性列表字节块"，不是结构体 `CONFIRMED`

入口：`uint32_t XpcClassicConnection::addServiceDataToLocalSDP(NSData *__strong)`，地址 `0x10040b568`。函数名与原型来自断言字符串（C 行 146–150）：

```
"/Sources/MobileBluetooth_base/Daemon/Server/XpcClassicConnection.mm", 0x62a,
"uint32_t XpcClassicConnection::addServiceDataToLocalSDP(NSData *__strong)"
```

输入块格式（由 C 行 158–205 的读取顺序确认）：

```
偏移 0..1   : uint16 属性个数 N          （C 行 158: uVar3 = *puStack_118）
随后 N 次   : uint16 属性 ID             （C 行 197–202: uVar3 = *(ushort*)(base + off)）
              DE 数据元素（由 FUN_100457334 解析）
```

每条属性被复制进一个 `N * 0x18` 的临时数组，元素布局为：

```
+0x00  uint16  属性 ID
+0x08  ...     数据元素值（16 字节，含类型与长度）
```

内存分配用 `_malloc_type_calloc(N, 0x18, …)`（C 行 175），失败即返回。

`CONFIRMED` 依据：属性计数、属性 ID 读取、`0x18` 步长、`calloc` 参数在汇编中均为立即数可见；断言字符串给出函数原型。

### C2 属性 `0x0001`（ServiceClassIDList）被单独处理 `CONFIRMED`

C 行 242：`if (*psVar2 == 1)` → 只对该属性 ID 取 `+0x08` 的值，转成集合后逐个元素：

| 依据 | 内容 |
|---|---|
| C 行 271–288 | 遍历属性值里的 UUID 集合，取每个元素字节与长度（`IVar12 = length; if (IVar12 < 5)` → 短 UUID 路径，否则长 UUID 路径） |
| C 行 288 | `FUN_1003c8e9c(uuid)` → `0x1003c8e9c` 把 UUID 加入本地 SDP 的"服务类"索引 |
| 日志 `0x10040b...` | `New service being added for %@` |

`IVar12 < 5` 的阈值说明：长度 2 或 4 字节按短 UUID（16/32 位）处理，长度 16 按 128 位处理——与 SDP 数据元素规定一致。

**关键含义：CarPlay 的 ServiceClassIDList 内容不在 bluetoothd 里，是上层以字节块形式送进来的。** 因此本套文档不声称掌握"CarPlay 服务记录的全部属性取值"，见 `OPEN-SDP-1`。

### C3 SDP 服务端三个请求处理函数的原型（来自断言字符串）`CONFIRMED`

| 地址 | 原型（固件字符串原文） |
|---|---|
| `0x1003ce304` | `OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)` |
| `0x1003ce9c4` | `OI_STATUS ServiceAttributeRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)` |
| `0x1003cec64` | `OI_STATUS ServiceSearchAttributeRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)` |
| `0x1003ca1d8` | `OI_STATUS ServiceRecordResponse(OI_BYTE_STREAM *)` |

参数语义（按 `0x1003ce304` 内部用法反推，`PARTIAL`）：

```
arg1 = uint16  请求方期望的最大记录数（MaximumServiceRecordCount）
arg2 = 请求字节流（读）
arg3 = 响应字节流（写）
arg4 = uint16  响应可用字节预算（MTU 相关）
arg5 = OI_L2CAP_CID  回发用的 L2CAP 通道
```

### C4 ServiceSearchRequest 的记录数与响应预算计算 `CONFIRMED`

| 依据 | 内容 |
|---|---|
| C 行 42 | `FUN_1003cf074(param_2, &plStack_68)` 解析 UUID 列表；失败 → 日志 `SDPServer: ServiceSearchRequest bad UUID list` 并返回错误 |
| C 行 67–70 | 读 2 字节大端：`uVar4 = CONCAT11(b0, b1)` = MaximumServiceRecordCount |
| C 行 74 | `uVar12 = (param_4 + 0x3fff4) >> 2` → **响应预算换算成记录数**：`(可用字节 - 12) / 4` |
| C 行 76 | `if (uVar12 <= uVar4) uVar1 = uVar12;` → 实际返回条数 = `min(请求数, 预算条数)` |
| C 行 80 | `FUN_1003cf1e8(param_3, uVar1*4 + 4 & 0xfffc)` 预留 `4 + 4*N` 字节 |
| C 行 98–106 | 循环 `FUN_1003cb688(...)` 逐个匹配记录；`0x337` 视为"没有更多"而非错误 |
| C 行 115–120 | 句柄按**大端 4 字节**写入响应：先写最高字节，再 `>>16`、`>>8`、最低字节 |

`(param_4 + 0x3fff4) >> 2` 中的 `0x3fff4` 是 `0x40000 - 0xC` 的补码形式，等价于 `(param_4 - 12) / 4`。即：**响应头固定占用 12 字节**（PDU 头 5 + 字节计数 2 + 记录数 2 + 继续状态 1 + 余量），每条记录句柄 4 字节。

### C5 SDP 全部 16-bit 字段为大端，并实现 continuation state `CONFIRMED`

`ServiceRecordResponse`（`0x1003ca1d8`）的解析逻辑：

| 依据 | 内容 |
|---|---|
| C 行 42 | `uVar2 = (uVar13 >> 8) | (uVar13 & 0xff00ff) << 8` → 16 位字节序翻转（大端→本机） |
| C 行 44–45 | 再读一个 16 位置换后的字段（continuation state 长度 `uVar6`） |
| C 行 52–55 | `uVar6 == 0` → 没有更多数据，直接完成 |
| C 行 60–75 | 否则逐 4 字节读属性字节计数项，翻转后存入 `piVar8+10` 指向的数组，计数存 `+0x32` |
| C 行 67/69/72 | 三次字节序翻转（32 位与 16 位混合重排），确认全部网络序 |
| C 行 77–79 | 若读到的记录数等于已知总数，或继续状态回退到起点 → 状态置 1（完成） |

含义：iPhone 的 SDP 客户端**实现了完整的 continuation state 分段续读**，不是"一次读完"。平台实现若忽略 continuation state，会在长记录（CarPlay 记录通常较长）上截断。

### C6 RFCOMM 的注册动作 `PARTIAL`

函数 `0x1002f1300`，字面量 `RFCOMM registration failed!`（引用点 `0x1002f1440` 附近）。

| 依据 | 内容 |
|---|---|
| C 行 43–45 | 已有全局标志 `iRam...100cadde0 != 0` → 返回 `0x8c`（重复注册） |
| C 行 46–47 | `FUN_1001aad2c(0x198, …)` 分配 0x198 字节注册块，失败返回 `0x6a` |
| C 行 67–71 | 8 次循环把 `+0x00` 起、步长 `0x30` 的 8 个槽写成 `0xffff`（8 个"服务通道号"槽位，初始无效） |
| C 行 76–77 | `param_5`/`param_6` 存到 `+0x192`/`+0x194`（两个 uint16 外部参数） |
| C 行 79 | `FUN_1003c2434(&LAB_1002f15e0, &PTR_LAB_100ba52a8, param_5, param_6, +400, &UNK_100ba52e8)` → 向 L2CAP 注册回调 |
| C 行 86–88 | 由 `sRam...100c1cc48` 取值分支：`0x106` / `0x107` / 其他，三套不同的 SDP 注册路径 |
| C 行 104/110/119 | 各分支调用 `FUN_1003cb22c(&elem, +0x184)` 插入 SDP 记录，返回记录句柄到 `+0x184` |
| C 行 126 | `param_4`（外部指针）存到 `+0x188` |
| C 行 130 | `FUN_10031ed88(0x600000)` |
| C 行 139 | 失败日志 `RFCOMM registration failed!` |

`PARTIAL` 原因：`param_3` 的位语义只解出两处（`param_3 >> 5 & 1`、`param_3 & 0x1f | (param_3 >> 9 & 1) << 5`），`0x106/0x107` 这两个魔数的含义（profile 版本？设备类别？）无证据；`FUN_1003c2434` 的 L2CAP 注册参数结构未展开。

已可确定的部分：**RFCOMM 注册会一次性占掉 8 个服务通道槽位，其中一个槽位号被写进 SDP 记录的 RFCOMM 协议描述符**（见 C7）。

### C7 RFCOMM 通道号在协议栈内的位置 `CONFIRMED`

服务端按"通道号"索引注册表：

| 依据 | 内容 |
|---|---|
| `0x1003c2314` C 行 23–26 | `lVar3 = 0x100c38318 + 0x1a`；比较 `*(byte*)(base + i*0x38 + 0x1a) == channel` |
| `0x1003c2314` C 行 26 | 命中后 `(**(code**)(lVar3 - 0x12))()` → 调用该注册项 `+0x08` 的回调 |
| `0x1003c2314` C 行 18/34 | 未命中返回 `0x79`（121） |
| `0x1003c1404` C 行 29 | 入向连接时用 `*(byte*)(base + i*0x38 + 0x1a) == dlci >> 1` 匹配 → **DLCI 与通道号的关系是 `通道号 = DLCI >> 1`** |
| `0x1003c1404` C 行 36–46 | 命中后把注册项的字段复制到新建 DLCI：`+0x14 = 1`（incoming 标志）、`+0xa0 = 注册项+0x08 的 uint16`、`+0x10 = min(session+4, 注册项+0x10)`、`+0x28`/`+0x30` = 注册项的两个回调指针 |

因此"服务通道号"（SDP 里出现的 RFCOMM channel number）在协议栈内部就是注册表索引，与 DLCI 满足 `DLCI = 2*n + {0|1}`（n 为通道号），具体取 0 还是 1 取决于会话角色，见 `04` 的 C3。

## 2.6 运行时佐证：真实 SDP 记录（跨构建）

抓包（`runtime/observations/findings-sdp-hci.md` §3）解出一条 WiAP Sink 记录（**推断**为设备自身发布：属性集不含 `0x0100`；抓包无方向标志，无法据此断定）：

```
AttributeList = SEQ[
  UINT16 0x0000, UINT32 65550,
  UINT16 0x0001, SEQ[ UUID128 00000000-deca-fade-deca-deafdecacaff ],
  UINT16 0x0002, UINT32 329452940,
  UINT16 0x0004, SEQ[ SEQ[UUID16 0x0100], SEQ[UUID16 0x0003, UINT8 4] ]
]
ContinuationState = 0
```

由此得到三条实测事实（标为运行时候选）：

1. 记录属性集为 `{0x0000, 0x0001, 0x0002, 0x0004}`，**不含** `0x0100`（ServiceName）——补上了 C2 未覆盖的 `0x0002`；
2. `0x0004` 的 L2CAP 元素**只有 UUID 0x0100、没有 PSM 参数**；
3. 该构建下 RFCOMM 通道号为 **4**；另有构建/对端观测到 1 与 5 → 通道号非固定。

对端记录的形态：`0x0005` = [0x1002]、`0x0100` = `iAP2` / `RFCOMM-SPP`。

## 3. 对实现的约束（进入 spec）

1. 经典 SDP 数据库的写入必须以"属性列表"为单位，且必须至少包含 `0x0000`（ServiceRecordHandle，由栈分配）、`0x0001`（ServiceClassIDList）、`0x0004`（ProtocolDescriptorList，含 RFCOMM 通道号）。
2. 属性 ID 与 UUID 在 SDP 记录中是**大端**。
3. 服务端必须在 12 字节开销之外按 `4 字节/句柄` 计算容量，并支持最多 `min(请求, 容量)` 条。
4. continuation state 必须实现双向（服务端生成、客户端续读）。
5. 一个服务可注册多个 128-bit 服务类 UUID（`0x0001` 是列表），CarPlay 与 WiAP 可同时出现在一条记录里。

## 4. 未决

| 编号 | 内容 | 原因 |
|---|---|---|
| `OPEN-SDP-1` | CarPlay / WiAP 服务记录的**完整属性取值**（`0x0004` 中的 RFCOMM 通道号、`0x0009` profile 版本、`0x0100` 名称等） | **部分收窄**：抓包已给出 WiAP Sink 记录的属性集与通道号（见 2.6），以及一个对端 CarPlay/iAP2 记录；但 `0x0009` 的 profile 版本、以及"由谁传入该字节块"仍未取证 |
| `OPEN-SDP-2` | `0x106` / `0x107` 两个分支的确切含义 | 无字符串或常量证据 |
| `OPEN-SDP-3` | `arg4`（响应字节预算）的调用方取值与 SDP MTU 的关系 | 未追到调用点 |
| `OPEN-SDP-4` | 本地数据库的物理布局（记录句柄分配策略） | 只确认句柄为 32 位大端、`0x1003cb22c` 负责插入，未展开分配器 |
