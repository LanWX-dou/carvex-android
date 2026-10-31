# analysis/06 — 特性注册表与消息处理器

控制会话"认识"哪些消息，取决于一张 29 项的**特性信息表**和一张由它灌出来的**全局消息处理器字典**。两者关系是：特性表是编译期常量，字典是运行期产物。

## 6.1 特性信息表

符号 `__kiAP2FeatureInfoEntries`，地址 `0x10021b550`，实测 29 项、每项 16 字节：

| 偏移 | 宽度 | 内容 |
|---|---|---|
| `+0x00` | 4 | 特性号（0–28） |
| `+0x08` | 8 | 指向特性信息结构 |

特性信息结构：

| 偏移 | 宽度 | 内容 | 证据 |
|---|---|---|---|
| `+0x00` | 8 | 创建函数 | `0x10013e49c`：`(**(code **)*plVar13)(param_1)` |
| `+0x08` | 8 | 处理器表指针 | `0x10006a1d0`：`*(long *)(puVar5 + 8)` |
| `+0x10` | 2 | 处理器个数 | `0x10006a1d0`：`*(short *)(puVar5 + 0x10)` |
| `+0x22` | 1 | 特性号（重复，用于匹配） | `0x10013e49c`：`*(byte *)((long)plVar13 + 0x22)` |

实测分布（`source/metadata/tables.json`，由 `extract-feature-table.py` 抽取）：

| 特性号 | 处理器数 | 特性号 | 处理器数 |
|---|---|---|---|
| 0 | 3 | 15 | 2 |
| 1 | 3 | 16 | 5 |
| 2 | 1 | 17 | 3 |
| 3 | 4 | 18 | 4 |
| 4 | 3 | 19 | 2 |
| 5 | 3 | 20 | 1 |
| 6 | **14** | 21 | **13** |
| 7 | 4 | 22 | 2 |
| 8 | 0（无表） | 23 | 3 |
| 9 | 2 | 24 | 3 |
| 10 | 1 | 25 | 2 |
| 11 | 4 | 26 | **1**（`0x4301`） |
| 12 | 1 | 27 | 0（无表） |
| 13 | 8 | 28 | 1 |
| 14 | 3 | | |

合计 **27 张表 / 96 个处理器**。特性 8 与 27 没有处理器表，说明"有特性但不收消息"是合法配置。

## 6.2 注册：一次性灌入全局字典

`_iap2_features_registerMessageHandlers`（`0x10006a1d0`）：

```
0x10006a1d0  if (handlersRegistered & 1) { log 已注册; return 1; }     ; 幂等
              log "Registering message handlers..."
              for (lVar4 = 0; lVar4 != 0x1d; lVar4++)                  ; ★ 29 次
                  info = (&PTR__kiAP2FeatureInfo_AccAuthentication)[lVar4*2]
                  if (info == 0 || info->handlers == 0) → 走 cold 报错
                  if (info->count != 0)
                      for (k = 0; k < info->count; k++)
                          setHandler(entry[k].msgID, entry[k].fn)
              handlersRegistered = 1;
```

处理器表每项 16 字节（`uVar6 * 0x10`），`*(undefined2*)puVar1` 是消息 ID，`*(undefined8*)(puVar1+4)` 是函数指针。

注册动作落到 `_iap2_messageHandlers_setHandler`（`0x10012e4c4`），后者就是一个 `CFDictionarySetValue`；查找侧 `_iap2_messageHandlers_getHandler`（`0x10012e644`）是 `CFDictionaryGetValue`。

**三个后果**：

1. **注册是全局的、进程级的、只做一次**（`handlersRegistered` 标志）。断连不会撤销处理器（`analysis/12` 的 `cleanup` 不碰这张字典）。
2. **注册发生在 `sessionControl_init` 里**，也就是链路第一次连上时才发生。若某条消息在链路连上之前到达，处理器字典还是空的——但由于表也是空的，消息根本到不了分发层（`analysis/02`），两层保护一致。
3. **消息 ID 是 16 位**,一个消息 ID 只能有一个处理器（字典覆盖语义）。若两个特性注册同一个 ID，后者覆盖前者，镜像里没有检查。

## 6.3 建特性：奇偶门控

`_iap2_features_createFeatures(component, 特性号)`（`0x10013e49c`）只创建**指定**的那一个特性：

```
for (i = 0; i != 0x1d; i++)                       ; 29 项
    id   = kiAP2FeatureInfoEntries[i]             ; 表里的特性号
    info = kiAP2FeatureInfo[i]
    if (info == 0 || info->create == 0) continue
    if (byte[info+0x22] != 特性号) continue        ; 只处理匹配项
    if (component == 0 || component[0xd0 + id*8] == 0) {   ; 槽空
        if ((特性号 & 1) != 0 || iap2_identification_isIdentifiedForFeature(component, id)) {
            槽 = info->create(component)
            if (槽 == 0) log "Error creating feature: %d!"
        }
    } else {
        log "Feature already created: %d!"
    }
```

两条硬规则：

- **奇数特性号跳过识别门控**，偶数特性号必须先 `iap2_identification_isIdentifiedForFeature(component, id)` 为真。
- 槽位按"表里的特性号"索引（`0xd0 + id*8`），不是按循环下标。29 个槽恰好占满 `0xd0`–`0x1b7`。

> **`OPEN-SES-13`**：`createFeatures` 的调用点（`0x10011d1a4`）前面紧挨着一个 outlined 片段（`0x10000946c`），因此**传入的特性号是不是常量**无法确认。`sessionControl_init` 看起来只创建一次特性，但若第二个参数来自寄存器残留，行为就依赖调用序。

## 6.4 对"控制会话"的意义

- 控制会话**自己没有处理器表**；它通过 `parseIncomingMessage` → `getHandler(msgID)` 走全局字典（`analysis/08`）。
- 因此"控制会话能处理哪些消息"= 96 条全局映射中的一部分，且**与当前连接无关**。
- `0x4301` 属于特性 26（CarPlay），不属于控制会话私有表。控制会话只是"消息到达的通道"，不是"消息的所有者"。
