# 06 包装器ABI与记录字段专项复核

证据固定于24A446 AirPlaySender，SHA256
`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`。
复用现有 `.s/.bin/.ghidra.c`，不修改原证据。Ghidra对PAC虚调用的伪签名不是ABI依据。

## 06.1 原地载荷与独立附加输出（A06.1）

`f_2519b508c` 的两次GetDataPointer：头的lengthAtOffset/dataPtr在sp+30/sp+38；
载荷的totalLength/lengthAtOffset/dataPtr在sp+18/sp+20/sp+28。
`5104..10c` 要求载荷连续覆盖总长；否则到52c4返回 `-0x4178`。

`5144`取headerLen到x26、headerPtr到x25，`5148`取payloadPtr到x23；
`519c..51bc` 将extraLen放栈，依次设置x0..x7为：
cryptor、headerPtr、headerLen、payloadPtr、payloadLen、同一payloadPtr、同一payloadLen、extraPtr。
`51c0`调用class+10；成功且extraPtr非NULL才在51fc创建extraBB，5214追加到payloadBB。
失败后不能假定明文和密码状态完整回滚。

导入核验来自 `firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt`：

| stub | 导入 |
|---|---|
| `0x25810eae0` | CMBlockBufferGetDataPointer |
| `0x25810ac90` | CMBlockBufferCreateWithMemoryBlock |
| `0x25810eab0` | CMBlockBufferAppendBufferReference |

## 06.2 派生参数与字符串原字节（A06.2）

`f_2519bfecc` 在bfee8..ef4保存x5/x4/x3/x2；bff34设w4=31，bff38/3c传原inputLength/inputOut；
bff5c设w4=32，bff60/64传原outputLength/outputOut。31/32是info长度，与输出长度分开。
原镜像映射采用segments.json：

| VA | 内容 | 长度（不含NUL） |
|---|---|---|
| `0x251bdf641` | `%s%llu` | 6 |
| `0x251bdf648` | `DataStream-Salt` | 15 |
| `0x251bdf658` | `DataStream-Input-Encryption-Key` | 31 |
| `0x251bdf6a9` | `DataStream-Output-Encryption-Key` | 32 |

ASPrintF（stub `0x25810a1a0`）产生C缓冲，返回长度存x19；盐长度不含末尾NUL。
`f_2519bffc8` 的c001c/c002c/c0038分别是CFDataCreateMutable、CFDataSetLength、
CFDataGetMutableBytePtr（stubs `0x25810e760/790/780`），不是字符串转换。
c0090..ac直接转发salt、saltLen、info、infoLen、outputLen、outputBytes。
本层不证明整数ID如何选，也不定义Input/Output相对于车机的业务方向。

## 06.3 构造计数与可选第二段（A06.3）

`f_2519b0014`：1160先处理主载荷；1164是outlined调用，1168是错误条件跳转。
sp+88非NULL时跳到12e8，12f0以同一headerBB和该尾段BB再调包装器，1308将其追加到主载荷。
随后1190/11bc完成配置/头/载荷组装；11c4错误分支通过后才在11c8..1d0令+470计数加1。
同函数0844显式清零该字段。因此它不是跨连接永久单调的密码nonce。

## 06.4 长度与帧间隔（A06.4）

旧稿仅看0e88的写入时机，就将w23命名“明文长度”，证据不足：

- 00b4..b8将storage+3a8保存到sp+38；0424将x21长度保存到sp+40。
- 0cc0..c4将这两个值相加到x23。
- 如存在sp+88尾段：0e40取得其CMBlockBufferGetDataLength，0e44..4c再加storage+3a8与尾段长到x23，
  这次额外的和同时存x27；0f9c将w27写入头+1c。
- 0e88写w23到头+0；无尾段时0e58置w27=0。

因此不能忽略额外长度或只填写编码帧明文大小。storage+3a8的赋值来源与具体cryptor绑定仍待闭合；
当前不把它直接命名“固定16B tag”。接收侧已核N/E的网络读入/分段语义，见FairPlay analysis11。

间隔循环在10ac作ticks差后，**10b0调用UpTicksToMilliseconds**（stub `0x25810bd90`），
10b8比较 `#0x10, lsl #12`，即 **0x10000=65536**，不是0x1000。
转换结果小于65536时存低16位，否则写0xffff；循环i从1到16且要求i<count。
未填区来自calloc为0。16是头内间隔槽数量，不能推出一批最多16个视频访问单元。

## 06.5 几何字段不是连续float[10]（A06.5）

`f_251b43fcc` 的4417c..1f0以FCVT将10个double转为float，写到下列偏移：

| storage源double偏移 | header目标float偏移 |
|---|---|
| 10、18 | 10、14 |
| 20、28、30、38 | 20、24、28、2c |
| 40、48、50、58 | 30、34、38、3c |

偏移均为十六进制；头+18..1f留空，不能把10个float连续打包到+10..37。
FCVT是浮点格式转换，不是把double原始字节截取前4B。

## 回归边界

`tools/verify-wrapper.py` 检查固定镜像SHA、五份完整原切片与重反汇编一致、ABI与字段指令锚点、
字符串原字节及导入符号；合成边界样例只验证文档算法，不执行密码原语或完整固件。
这些检查不能证明真实profile、网络发送成功、车机解码或握手互通。
