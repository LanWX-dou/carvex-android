# runtime：向量、抓包与复现

## 1. 目录

```
runtime/
  README.md            本文件
  vectors/             合成测试向量（由同一候选实现生成，不是独立互通证据）
    kdf.json           3 组：SHA-512 KDF（spec/04）
    chacha.json        6 组：含多段nonce、非零128B头双段记录与空明文
    ctr.json           2 组：AES-128-CTR（spec/06）
    cbc.json           6个调用输入：CBCFrame逐调用初始IV重置、余尾直通（spec/06）
    negative.json      4 组：错 key / 错 nonce / 改 tag / 短帧
  captures/            真实抓包目录：**当前为空**，原因见 §4
```

## 2. 向量怎么用

```bash
# 全部自检（含向量重算比对）
python3 research/protocol/airplay_fairplay_crypto/verify.py

# 只重新生成向量（会覆盖 runtime/vectors/*.json）
python3 research/protocol/airplay_fairplay_crypto/reference-impl/gen_vectors.py
```

`verify.py --write` 会重写 `manifest.json` 与 `function-index.json`（改过任何文件之后要跑一次，
否则 C9 会报「内容变了」）。

## 3. 向量字段含义

| 字段 | 含义 |
|---|---|
| `key_hex` | 32 字节（ChaCha）或 16 字节（AES/CTR）密钥 |
| `nonce_hex` | **8 字节**小端计数器（不是 12 字节 IETF nonce） |
| `aad_hex` | 附加认证数据；旧空/零AAD仅为算法自检，已核屏幕路径为原始128B头 |
| `plaintext_hex` / `frame_hex` | 明文 与 `密文‖tag16` |
| `payload_len` | 密文长度 = `len(frame) - 16` |

`chacha-3`保留历史空AAD候选算法自检，不再作为OPEN-10的二选一判据。
`chacha-5`验证空明文+16B tag，`chacha-6`验证同一非零128B头下两个段分别使用nonce0/1。
夹具的未定义头字段没有profile合法性保证，不可直接拿来连车机。
`verify_screen_aad.py`复核原切片和局部分段指令；合成往返不能证明目标库MAC编排相同。
`verify_aes_state.py`另核CoreUtils原字节与状态循环，并用NIST SP800-38A F.2.1/F.5.1的
独立CBC/CTR已知答案验证参考AES；这不等于已执行Apple库或已连接车机。
CTR多次调用需保留AES128CTR对象；一次性aes128_ctr_crypt每次重建状态，不可逐帧重复用初始IV。
CBCFrame恰好相反，每次Update重置初始IV；不能按任意TCP分片决定调用边界。

C14核对分派的G/keyholder/type门和provider参数，不执行provider。
C15核对Sender Legacy已有同一SHA-512 KDF公式及Receiver的整数传值，C6负责向量；
两者均不能证明目标CarPlay会话一定选择Legacy，不能将派生整数任意设为首流0/1。

## 4. 为什么 `captures/` 是空的（诚实声明）

`TASK.md` §6 A2 要求「真实抓包闭合密钥交换 + 加密帧 + 解密」。**本阶段没有满足**：

- 工作区唯一的时间序列数据是 23G90 的 BT-classic iAP2 抓包；
- 它包含 AirPlay 数据面的连接建立，但**不含** `/fp-setup`、`/setup` 的 RTSP 明文，
  也**不含**帧级密文/明文对（无法做已知明文攻击或 tag 校验）；
- 因此本 docset 全部「线上行为」结论都来自固件，不来自抓包。

`verify.py` 的 C10 在无抓包时**显式 SKIP**（打印原因），不会静默通过。

## 5. 补抓步骤（取得合适证据后逐项评估OPEN）

1. 让设备与车机进入同一无线链路，抓包点放在**能同时看到 RTSP 与数据面**的位置
   （推荐车机侧镜像口或 AP 侧，避免丢包导致的假阴性）。
2. 过滤：
   `tcp port 7000 or tcp port 7001 or udp portrange 6000-7000`
   （AirPlay 的 RTSP 与媒体端口；具体端口以实际协商为准，`/setup` 响应里能看到）。
3. 必须完整保存**握手 → `/setup` → 首帧**这一段，缺一段就无法对齐密钥与帧。
4. 归档到 `runtime/captures/`，命名 `YYYYMMDD-<车机型号>-<阶段>.pcapng`，并附一份
   `notes.md` 写明：`/fp-setup` 的 ET 值、`/setup` 的字段名原文（脱敏后的键名即可）、
   屏幕记录的完整原始128B头与全部body，并受控提供合法密钥/nonce、已知明文对照；
   密钥不要提交公开仓库。只有前64字节不够验证AAD/tag。

OPEN-7的属性拼写和OPEN-13的键名已静态闭合，但能力来源、setup层级/profile仍未闭合。可优先核对OPEN-3的ET、
OPEN-15整数来源/传递及OPEN-10头构造/跨段互通；不要把ET值直接当作分派属性G。
一次样本不自动关闭这些项目。历史OPEN-9/11的AES库规则已静态闭合，实际媒体调用边界和互通仍需运行对照。

## 6. 与 spec 的对应

| 向量文件 | 对应规则 |
|---|---|
| `kdf.json` | spec/04 R-4.1、R-4.2、R-4.3 |
| `chacha.json` | spec/07 R-7.1、R-7.3、R-7.4 |
| `ctr.json` | spec/06 R-6.1、R-6.2 |
| `cbc.json` | spec/06 R-6.3 |
| `negative.json` | spec/07 R-7.5、spec/08 R-8.2 |
