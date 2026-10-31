# 15 · CoreUtils key holder 的角色、标签与派生输入

范围：24A446 的 APTransport + **CoreUtils key holder / CoreUtils pairing provider**。
另有 Legacy/SharedKey provider，不能将本章条件性结论外推到它们或所有 CarPlay profile。
原始镜像、符号、汇编和反编译 C 交叉核对；没有车机抓包或实际握手。

## 15.1 `+0x100` 是 IsServer，不是 IsListener（A15.1）

`APTransportConnectionHTTPCreate`（`0x24fdc7034`）在 `0x24fdc7164..180` 从第五入参选项字典取
CFString `0x275fa45e0` 对应的整数/布尔值，`cmp #0; cset ne` 后存入 `obj+0x100`；
getter出错则在 `0x24fdc718c` 清零。该 CFString 解码为 **`IsServer`**。
`IsListener` 是另一键，写入的是 `obj+0xe0`（`0x24fdc70bc..0dc`）。

因此不能因程序监听socket或设备叫“手机/车机”便替代此角色选项。
本端主动请求控制会话时的非服务器配置，和被动事件/其它服务通道必须分别判断。
本章未追全所有构造调用者如何设置该选项。

## 15.2 两个输出的标签绑定（A15.2）

`_coreUtilsKeyHolder_CreateEncryptionKeysForContext`（`0x251a358e4`）：

- context与 CFString `0x27612c250` 比较为零时，选 **`Ctrl`** 标签组；与 `0x27612c270` 相等时选 **`Events`** 标签组。
  它们是内部上下文名字，不是必须在线上新增的字段。
- `0x251a35908..2c` 保存输出参数：x3→x20、x5→x19；长度x2/x4为0时各默认32。
- 控制分支 `0x251a359c8..9ec`：首次派生用 `Control-Read-Encryption-Key`，第二次用 `Control-Write-Encryption-Key`，共同salt=`Control-Salt`。
- `0x251a35a6c..a88` 首次派生输出到sp+18，`0x251a35b08..b0c` 写入第4参数；
  `0x251a35ae0..afc` 第二次输出到sp+10，`0x251a35b1c..b20` 写入第6参数。
- APTransport `0x24fdc98a4..bc` 将这两个输出接到 `K_A=[fp-28]`、`K_B=[fp-30]`，
  再按 `A13.3` 的角色分支传给 Configure。

| CoreUtils provider 的 Ctrl 上下文 | 本地 Read（解密收到的记录） | 本地 Write（加密发出的记录） |
|---|---|---|
| IsServer = 0 | Control-Read-Encryption-Key | Control-Write-Encryption-Key |
| IsServer ≠ 0 | Control-Write-Encryption-Key | Control-Read-Encryption-Key |

Events上下文相同输出顺序，使用Events标签组；不要把Ctrl密钥直接拿去Events。
非服务器控制客户端在**满足本provider与上下文前提时**即可使用表中第一行，不再笼统称方向完全未知。

虚调用绑定不能只靠函数名猜：`APKeyHolderCoreUtilsCreate` 在 `0x251a35600..610` 传入
`_kAPSKeyHolderCoreUtilsVTable=0x276124ae0`；其+10槽指向class=`0x276124b58`，
class+40槽解码为 `0x251a358e4`（与APTransport虚调用槽+40一致），class+30为 `0x2519bffc8`。
解码使用本构建经验规则，核对唯一映射与符号；不是对任意PAC指针的通用承诺。

## 15.3 派生输入不是 Pair-Verify TLV 加密密钥（A15.3）

`_coreUtilsKeyHolder_CreateDerivedKey`（`0x2519bffc8`）分配要求长度的输出数据，
转发 salt/saltLen/info/infoLen/outputLen/outputBuffer 给保存的pairing provider虚表+8。
采用CoreUtils pairing provider时，该槽由
`_kAPPairingClientCoreUtilsVTable+0x10 → 0x276126d88`、class+8 → `0x2519bd76c` 确认。
`_coreUtilsPairing_DeriveKey` 在 `0x2519bd7a0..7c0` 取其PairingSession并原样转发参数到
stub `0x25810ba10 = _PairingSessionDeriveKey`（CoreUtils `0x18be5021c`）。

该函数读取session内部type=`+0x60`与state=`+0x80`，派生门如下（数值是内部枚举，不是线上TLV类型）：

| 内部type | 必需state | HKDF输入 |
|---|---|---|
| 1、2 | 7，且指针/长度均非零 | `*(sess+0x300)`，长度 `*(sess+0x308)` |
| 3、4 | 5 | `sess+0x28e`，32B |
| 5、6 | 3 | `sess+0x28e`，32B |
| 0或>6 | 拒绝 | 返回 `-0x1a4f` |

状态不符或1/2的指针/长度为空返回 `-0x1a35`。
证据：`0x18be50240..2ec`，先检查type≤6，再按 `(1<<type)` 的6/18/60掩码分组。
两组最终都调用 `ccsha512_di` / `cchkdf`，参数为外部传入的salt/info和输出长度。

对于已核完整Verify产生 `sess+0x28e` 的共享秘密路径（`A14.1`），且此派生门通过时：

```text
K_A = HKDF-SHA512(shared_secret[32], salt="Control-Salt",
                  info="Control-Read-Encryption-Key", length=32)
K_B = HKDF-SHA512(shared_secret[32], salt="Control-Salt",
                  info="Control-Write-Encryption-Key", length=32)
```

不能把 `sess+0x1ae` 的 Pair-Verify TLV 加密密钥再当作这里的输入；标签不包含末尾NUL。
该公式仅覆盖上述provider/输入分支；Setup来源的可变长材料、恢复和其它provider要分别核对。

## 15.4 剩余缺口与回归

`OPEN-AP-22`/`40` 的本provider静态链已从“方向/输入未知”缩小到调用者选择问题：
目标CarPlay连接具体用哪个provider、内部type如何设定、角色选项与切换时刻仍需调用者/运行证据。
不能因公式闭合就宣布控制加密的启用时刻或全部车机兼容性闭合。

`tools/verify-keyholder.py` 核对六份已有及两份新增函数切片、角色CFString/虚表槽位/标签常量，
并有限解释派生门的状态与缺失输入分支。它不执行HKDF或网络握手。
