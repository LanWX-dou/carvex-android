# 10 方法与局限（自证清单）

本文件是给复审者看的：**我做了什么、没做什么、哪些结论的强度只到这里。**

---

## A-32 实际逐条阅读的范围

| 镜像 | 导出函数数 | 说明 |
|---|---|---|
| `AirPlaySender` | 36 | 覆盖 FairPlay 客户端类全部方法、keyholder 家族、流响应构造（`apsession_createCryptors`）、音频加密键生成 |
| `AirPlayReceiver` | 15 | 覆盖 `/fp-setup`、`/setup` 取键、会话建立、屏幕三件套（CBC/CTR/ChaCha + 解密） |
| `AirPlaySupport` | 6 | 覆盖 SHA-512 KDF 两版、三个加密器构造、`APSCryptorGetNull` |

专项补充：`source/asm-audit/`有Receiver 2份及CoreUtils 3份原切片（A-34–A-36）；
`source/asm-aes-audit/`另有CoreUtils 6份（A-40–A-42）。不计入上表57个基础导出或新增Ghidra数。
C14复用已有Sender/Support切片核对属性/对象门；C15复用两份Sender和一份Receiver切片核对Legacy KDF正面证据及整数传值。
两项均不增加切片/Ghidra计数，也不执行完整固件或网络握手。

**没有**逐条阅读的部分（这些只用于交叉引用）：

- `AirPlaySender` 里 2,375,824 字节的其余函数（约 99%）。
- keyholder 的 `Finalize`、`CopyProperty`、`Shared`/`CoreUtils` 两个家族的多数方法（只读了 Legacy）。
- 接收侧 `_airplayReqProcessor_requestProcessSetupPlist`（`0x2518a2c18`）只做了调用点定位，未通读。

结论强度据此分三级（`spec/` 每条规则都标注了级别）：

- **A 级（可写死）**：有函数体 + 汇编 + 字节三重印证。例：KDF 拼接顺序、ChaCha 帧布局、ET→类型映射。
- **B 级（可写但有边界）**：函数体清楚但相关外部语义未核；已补证的CBCFrame库规则不再列为全未知。
- **C 级（只能写方向）**：只有调用点或只有符号，例：`UpdateMasterAESKeyAfterSharing` 的时机。

## A-33 已知局限（逐条，避免过度解读）

1. **调用图不含虚调用**。`xref-scan.py` 只识别 `bl`/`b`。`blraa`（PAC 签名的间接调用）与 `blr`
   不计入，因此「没有调用者」不能推出「未使用」。旧稿关于decryptBuffer没有直接调用者的说法错误：
   `0x25185ab80`和`0x25185abcc`两处直接BL已定位（A-35）。setter调用者仍需另行追踪。
2. **函数大小是上界**。「到下一个 `function_starts`」的距离包含对齐填充与相邻的内联块。
   用大小做「函数有多复杂」的判断会略高估。
3. **Ghidra 产物未复核**。所有 `.ghidra.c` 都带 `DECOMPILED_UNREVIEWED` 头；本 docset 的结论
   **不**建立在其类型/签名上，只建立在汇编与字节上。反编译里出现的 `param_4` 之类是推测。
4. **单版本**。全部结论限 24A446。跨版本差异未做 → `OPEN-14`。
5. **无抓包**。A2 验收项未达成（A-30）。任何需要「线上字节」的结论都只能是间接推断。
6. **历史链式指针误读已纠正**。A-37利用原cache v5 slide解析六个CFString，关闭OPEN-13；完整schema仍未闭合。
7. **反编译的寄存器—参数映射不可信**。例如取键路径（`_GetDecryptKey`，内联后仅存日志串）里 Ghidra 把「存在性判定」和
   「取值判定」混成 `local_54 == 0`；本 docset 以 `0x2518a5414`/`0x2518a541c` 的条件分支为准。

## 复现命令（可直接粘贴）

```powershell
# 1) 重新解析镜像元数据（若 metadata 缺失）
python3 firmware/tools/macho-meta.py research/protocol/airplay_fairplay_crypto/source/firmware/AirPlaySender `
        research/protocol/airplay_fairplay_crypto/source/metadata/sender

# 2) 重新反汇编某个函数（任意地址窗口）
python3 firmware/tools/slice.py research/protocol/airplay_fairplay_crypto/source/firmware/AirPlayReceiver `
        research/protocol/airplay_fairplay_crypto/source/metadata/receiver 0x2518a5410 0x30

# 3) 查谁调用了某个函数
python3 firmware/tools/xref-query.py firmware/analysis/24A446/airplay-fairplay/xrefs-sender.json `
        research/protocol/airplay_fairplay_crypto/source/metadata/sender `
        firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt callers _Mib5yocT

# 4) 读常量字符串
python3 firmware/tools/read-cstr.py research/protocol/airplay_fairplay_crypto/source/firmware/AirPlaySupport `
        research/protocol/airplay_fairplay_crypto/source/metadata/support 0x226f51f63

# 5) 全量自检
python3 research/protocol/airplay_fairplay_crypto/verify.py
```

## 关于「这份文档能不能指导实现」

见 `A-conclusions.md` 末尾的判决表；简版：

- **能**：消息编排、密钥材料语义、KDF、流类型分派、ChaCha/CTR 帧格式、错误码定位。
- **本项目未交付**：FairPlay SAP算法与适用接口；需核实合法实现/授权条件，不以未交付推导实现不可能。
- **尚未闭合**：`/setup`完整schema/profile、屏幕完整头构造及真实密码互通（`OPEN-10`）；键名问题已关闭。
  AAD来源已能静态追到128B网络头，不应继续描述为不可移植内部结构。
