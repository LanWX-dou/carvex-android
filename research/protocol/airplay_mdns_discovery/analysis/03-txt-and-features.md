# 03 — TXT 键与 `features` 位

> 本章回答覆盖项 5–7：TXT 里有哪些键、客户端读哪些、`features` 怎么用。
> 关键区分：**“iOS 会写出这个键”**（构造 TXT 的代码）≠ **“iOS 会读这个键”**（解析设备 TXT 的代码）。两者在本章分表列出。

## 3.1 键字符串与地址（APTransport）

| 键 | 字符串地址 | 读方（发现路径） | 写方（构造 TXT） |
|---|---|---|---|
| `features` | `0x24fe4f2f0` | `_deviceFound` `0x24fd99778` | `CopyAirPlayData*` `0x24fd9354c` |
| `fex` | `0x24fe4f7fa` | `_deviceFound` `0x24fd99748` | `CopyAirPlayData*` `0x24fd93510` |
| `flags` | `0x24fe4f80a` | `_deviceFound` `0x24fd99a00` | `CopyAirPlayData*` `0x24fd93628` |
| `psi` | `0x24fe4b4bc` | `_deviceFound` `0x24fd997d4` | — |
| `serialNumber` | `0x24fe4f340` | `_deviceFound` `0x24fd99834`、NAN 事件处理器 `0x24fe1cc54` | `CopyAirPlayData*` `0x24fd93b24` |
| `manufacturer` | `0x24fe4f32b` | `_deviceFound` `0x24fd9984c` | — |
| `deviceid` | `0x24fe4f734` | NAN 事件处理器 `0x24fe1cb94` | `CopyAirPlayData*` `0x24fd9347c` |
| `model` | `0x24fe4b473` | NAN 事件处理器 `0x24fe1cc30` | `CopyAirPlayData*` `0x24fd93aac` |
| `protovers` | `0x24fe4f860` | — | `CopyAirPlayData*` `0x24fd93c00` |
| `srcvers` | `0x24fe4f870` | — | `CopyAirPlayData*` `0x24fd93cf0`、`_APCarPlayControlServerCreate` `0x24fe01c5c` |
| `pk` | `0x24fe4f86d` | — | `CopyAirPlayData*` `0x24fd93cb4` |
| `pi` | `0x24fe4f86a` | — | `CopyAirPlayData*` `0x24fd93c3c` |
| `gid` | `0x24fe4f810` | — | `CopyAirPlayData*` `0x24fd9366c` |
| `vv` | `0x24fe4f87f` | — | `CopyAirPlayData*` `0x24fd93d80` |
| `btaddr` | `0x24fe4f72d` | — | `CopyAirPlayData*` `0x24fd93450` |

RAOP 侧（`_APAdvertiserInfoCopyRAOPData`）：`am`、`et`、`ft`、`md`、`ov`、`sf`、`tp`、`vs`、`vv`、`pk`。

**读方有三处**：`-[APBonjourCacheManager _deviceFound:altPairedInfo:recheck:event:]`（普通发现路径）、`__APBonjourBrowserHandleDeviceEventForAirPlayNANService`（NAN 路径）、`+[APBonjourCacheHomeKit isDeviceCacheable:]`（读 `model`，`0x24fdae57c`）。这三个函数是本阶段能确认的“客户端 TXT 消费点”。

**不能下的结论**：`pk`/`pi`/`gid` 虽然出现在构造侧，但**没有证据**表明发现路径会校验它们；因此 `pk` 不能当“已认证身份”（`OPEN-MDNS-13`）。

## 3.2 `features` 的编码（写方与读方都找到了）

### 3.2.1 写方：文本格式（CONFIRMED）

`__APAdvertiserInfoGetTXTRecordNumberCString`（`0x24fd940a0`–`0x24fd940ec`，76 B，19 条指令）：

```asm
0x24fd940b0  lsr  x8, x0, #0x20          ; 取高 32 位
0x24fd940b4  cbnz x8, 0x24fd940c8        ; 高 32 位非 0 → 两段
0x24fd940bc  adrp x2, "0x%X"      @0x24fe4fc8c
0x24fd940cc  adrp x2, "0x%X,0x%X" @0x24fe4fc82
0x24fd940c8  stp  x0, x8, [sp]           ; 参数：x0 = 低 32 位，x8 = 高 32 位
0x24fd940d8  mov  w1, #0x100             ; 输出缓冲 256 B
```

- 高 32 位为 0 → 只输出 `0x%X`（一个 32 位值）；
- 否则输出 `0x%X,0x%X`，**第一个是低 32 位，第二个是高 32 位**；
- 大写十六进制、带 `0x` 前缀、逗号分隔、无空格。

调用点在 TXT 构造器里：`0x24fd93544` 调用该函数，`0x24fd9354c` 以 `features`（`0x24fe4f2f0`）为键把它加入 TXT（`__APAdvertiserInfoAddStringToTXTRecord`，`0x24fd93fbc`）。

→ **`OPEN-MDNS-14` 关闭**：不是“任意十六进制串”，而是上述两种固定形态。

### 3.2.2 读方：字符串 → 64 位整数

`_APAdvertiserInfoCreateAPSFeaturesFromTXTRecordEx`（`0x24fd9ac78`–`0x24fd9ad68`，240 B）：

```text
v = TXT[key] 或 备用 TXT[key]              # 0x2500ee670 / 0x2500ee690
if v != nil: n = <0x2500edff0>(v)         # 字符串 → uint64（导入桩，名字被剥离）
*out = n
```

调用点 `0x24fdcd244` 成功后再调用 `__APAdvertiserInfoSetFeaturesEx`（`0x24fd99f1c`）把值写进 info 的 `FeaturesEx` 属性。

`_deviceFound` 里的消费路径（`0x24fd99748`–`0x24fd997c4`）仍是：优先 `fex`，否则 `features`；然后 `0x2500ee040(v, 0x37)`、`0x2500ee040(v, 0x38)` 两次位查询。

### 3.2.3 legacy / extended 两半

| 符号 | 地址 | 含义 |
|---|---|---|
| `kAPAdvertiserInfoProperty_FeaturesLegacy` | `0x269375540` | 低 32 位（legacy）属性 |
| `kAPAdvertiserInfoProperty_FeaturesEx` | `0x269375548` | 高 32 位（extended）属性 |
| `kAPAdvertiserInfoProperty_RequiredSenderFeatures` | `0x269375550` | 发送方要求的能力属性 |
| `__APAdvertiserInfoSetLegacyFeatures` | `0x24fd9a6e4` | 写 legacy 属性 |
| `__APAdvertiserInfoSetFeaturesEx` | `0x24fd99f1c` | 写 Ex 属性（先做 CFNumber 类型检查） |

对应字符串：`features` `0x24fe4f2f0`、`featuresEx` `0x24fe4f2f9`、`requiredSenderFeatures` `0x24fe4f304`。

因此 64 位值是 **legacy（低 32）`|` extended（高 32）`<< 32`**；索引 55/56 落在 extended 半的第 23/24 位（`55-32`、`56-32`），这是基于参数顺序的推断（`A02.7`，`INFERRED`）。

### 3.2.4 `fex`

同一个构造器在 `0x24fd93510` 以 `fex`（`0x24fe4f7fa`）为键加入一个**字符串**值（`0x24fd9351c` 调 `__APAdvertiserInfoAddStringToTXTRecord`），值来自 info 的 Ex/`requiredSenderFeatures` 属性。所以 `fex` 与 `features` 是**两个独立的 TXT 键**，`fex` 的值是字符串；其内部结构仍未取证（`OPEN-MDNS-15`）。

## 3.3 `features` 逐位表（只列有证据的位）

| 位 | 用途 | 证据 | 状态 |
|---|---|---|---|
| 55 | 查询索引 `0x37`；按 low/high 拆分属 extended 半第 23 位 | `0x24fd997a8` | 读到了；语义 `OPEN-MDNS-11`；位位置见 `A02.7`（INFERRED） |
| 56 | 查询索引 `0x38`；与 `psi`、`recheck` 联合判断（`0x24fd997f4`–`0x24fd99800`） | `0x24fd997b8`、`0x24fd997c4` | 读到了；语义 `OPEN-MDNS-11`；extended 半第 24 位（INFERRED） |
| 其他 0–63 | 本阶段未找到逐位判断 | — | `OPEN-MDNS-11` |

**这张表故意是空的**：AirPlay 的 `features` 位表在网上有各种版本，但本阶段没有一份能把“位 X = 能力 Y”钉到 24A446 的指令或车机行为上。按任务书要求，未验证的位不得按常见位表硬套。

## 3.4 `flags` 与 `features` 不是一个东西

- `flags` 是独立键（`0x24fe4f80a`），读点在 `0x24fd99a00`，与 `features` 的读点相隔约 0x290 字节；
- 构造侧 `flags` 与 `features` 分别写入（`0x24fd93628` / `0x24fd9354c`）；
- 因此**不得**把 `flags`、`sf`、`ft` 混进 `features` 位图（任务书 §5.1C 的明确要求）。

## 3.5 值编码

| 键 | 观察到的编码 | 证据 |
|---|---|---|
| `features` | 文本（按 `0x10` 缓冲解析） | `0x24fd99778` 的参数 |
| `flags` | 文本/整数 | 读点后用通用取值桩；未细究 |
| `pk` | base64（AirPlay 公钥惯例） | **未取证**，`OPEN-MDNS-13` |
| `deviceid` | 形如 MAC 的字符串 | NAN 处理器读取后按字符串处理；格式 `OPEN-MDNS-10` |

## 3.6 未知键与坏值

参考实现（`A02.2`）将诊断与业务视图分开：原始项/重复/二进制字节保留；业务查询使用合法 ASCII 键、不区分大小写、首次生效，无值与空值分别表示。hex 仅供显示，不能作为线上属性值重新编码；认识键名也不代表已认证。

## 3.7 本章未解决

| 编号 | 问题 |
|---|---|
| `OPEN-MDNS-10` | 车机实际出现的键集合与取值（无抓包） |
| `OPEN-MDNS-11` | `features` 全位表语义 |
| `OPEN-MDNS-13` | `pk`/`pi`/`gid` 能否作为身份/配对依据 |
| `OPEN-MDNS-14` | `features` 文本语法（是否 `0x…,0x…` 双段）、大小写、前导零 |
| `OPEN-MDNS-15` | `fex` 的结构与优先级（存在时完全替代 `features`？） |
