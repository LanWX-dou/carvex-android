# analysis/07 — 识别门控（消息准入）

每条入站消息和每条出站消息都要过一道"识别门控"。这是会话层唯一的**强制安全边界**：链路通了、会话有了、处理器找到了，消息仍然可能被丢弃。

## 7.1 入站门控

`_iap2_identification_isIdentifiedForIncomingMessageID(component, msgID)`（`0x100051054`）：

```
0x100051054   if (component == 0) return false
0x100051058   w = msgID
              if (msgID < 0x1d01) goto 白名单判断
              if (msgID < 0xaa01) { w = msgID - 0x1d01; goto 白名单判断 }
              if (msgID == 0xaa01) return true
              if (msgID == 0xaa03) return true
              if (msgID == 0xaa06) goto 0x1000510c4（只查识别）
              goto 通用判定
白名单判断:
0x1000510b0   if (w < 6 && ((1 << w) & 0x31) != 0) return true
```

| 消息 ID | 判定 | 依据 |
|---|---|---|
| `0x0000`、`0x0004`、`0x0005` | **无条件放行** | `0x1000510b0`，掩码 `0x31` = bit0/4/5 |
| `0x1d01`、`0x1d05`、`0x1d06` | **无条件放行** | `0x1000510b0`，`w = msgID-0x1d01`，掩码 `0x31` |
| `0xaa01`、`0xaa03` | **无条件放行** | `0x100051090`、`0x100051098` |
| `0xaa06` | 需识别完成（见下） | `0x1000510a0` 分支 |
| 其他 | 需认证完成 + 识别完成 + 消息 ID 在集合里 | `0x1000510c4` 之后 |

两条特例分支的具体条件：

```
0xaa06:  info = iap2_identification_getIdentificationInfo(component)
         if (info == 0 || [info+0x60] == 0) return false
         if (iap2_identification_getState(component) != 6) return false
         set = [info+0x60]  → CFSetContainsValue(set, 0xaa06)

其他:   info = iap2_identification_getIdentificationInfo(component)
         if (info == 0) return false
         if (iap2_accAuthentication_getState(component) != 2) return false
         if (iap2_identification_getState(component) != 6) return false
         if ([info+0x60] == 0) return false
         CFSetContainsValue([info+0x60], msgID)
```

**关键不对称**：`0xaa06`（识别消息）**不要求认证完成**；其他消息必须先认证（状态 2）再识别（状态 6）。这与 `analysis/05` 的"版本 2 → 识别优先 / 否则认证优先"是同一套逻辑的两面。

状态值 `2`（认证完成）与 `6`（识别完成）都是枚举常量，其数字含义来自 `iap2_accAuthentication_getState` / `iap2_identification_getState` 的返回值域，本阶段只采信"`0xaa06` 只要 6、其余要 2 且 6"这一比较关系，不解释状态机语义（属上一/下一阶段范围）。

## 7.2 出站门控

`_iap2_identification_isIdentifiedForOutgoingMessageID(component, msgID)`（`0x100005138`）：

```
w0 = 1                                     ; 默认放行
if (msgID - 0xaa00 <= 5)                   ; 0xaa00..0xaa05
    if ((1 << (msgID-0xaa00)) & 0x35) return 1     ; 0xaa00,0xaa02,0xaa04,0xaa05
if (msgID <= 5)
    if ((1 << msgID) & 0x31) return 1              ; 0x00,0x04,0x05
if (msgID - 0x1d00 <= 3)
    if (msgID-0x1d00 != 1) return 1                ; 0x1d00,0x1d02,0x1d03
通用判定:
    info = getIdentificationInfo(component) ; 0 → 0
    accAuthentication_getState(component) != 2 → 0
    identification_getState(component)    != 6 → 0
    [info+0x68] == 0 → 0
    CFSetContainsValue([info+0x68], msgID) → 1/0
    成功时打 os_signpost（id 0x2b94115c）
```

出站白名单与入站**不同**：

| 集合 | 入站放行 | 出站放行 |
|---|---|---|
| `0x00/0x04/0x05` | 是 | 是 |
| `0x1d01/0x1d05/0x1d06` | 是 | **否**（出站是 `0x1d00/0x1d02/0x1d03`） |
| `0xaa01/0xaa03` | 是 | **否** |
| `0xaa00/0xaa02/0xaa04/0xaa05` | 否（走通用判定） | 是 |
| `0xaa06` | 仅需识别 | 走通用判定（需认证+识别） |

两个"识别集合"是**不同的 CFSet**：入站用 `[info+0x60]`，出站用 `[info+0x68]`。所以"我能收的"和"我能发的"是两份名单，不是一份。

`0x1d01` 在出站侧**刻意不白名单**（`cmp w8,#1; b.ne` 跳过的正是 1），必须等认证+识别都完成才能发。

## 7.3 门控在两条路径上的位置

| 路径 | 调用点 | 失败行为 |
|---|---|---|
| 入站 | `0x10011d518` 内，取到 msgID 之后、查处理器之前 | 记 `"Not identified for incoming message ID: 0x%04X! (endpoint %@)"`，返回 0，消息丢弃 |
| 出站 | `0x100004f14` 内，取到 msgID 之后、真正发之前 | 记 `"Failed to send, Outgoing Message ID: 0x%04X (%d bytes) for endpoint %@"`，返回 0 |

**顺序很重要**：入站是"先门控、后查处理器"。所以一条未获准的消息不会因为"碰巧有处理器"而被执行，也不会因为"没有处理器"而绕过门控。

## 7.4 未决

- **`OPEN-SES-14`**：三个取值函数未逐指令核对。其中 `iap2_accAuthentication_getState`（`0x1000052e0`）与 `iap2_identification_getState`（`0x1000052a4`）有符号名；"取识别信息"的函数在**符号表里没有名字**（地址 `0x100051238`，紧接 `__startFeatureFromDevice` 之后），Ghidra 只是按签名把它标成 `iap2_identification_getIdentificationInfo` —— **这个名字不是证据**。本文件只用它们的**比较关系**（`!= 2`、`!= 6`）与返回指针的 `+0x60`/`+0x68` 两个集合偏移，不用其内部结构。
- **`OPEN-SES-15`**：`[info+0x60]` 与 `[info+0x68]` 两个集合的**填充时机**未取证（谁往里加消息 ID）。因此"某条消息在什么时刻恰好变得可收/可发"无法给出时间线。
