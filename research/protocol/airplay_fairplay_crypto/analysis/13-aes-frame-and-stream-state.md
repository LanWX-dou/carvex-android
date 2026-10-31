# 13 CoreUtils AES：CBC逐调用重置与CTR连续状态

范围：24A446、固定SHA的CoreUtils（复用control docset）；新增6份原切片于
`source/asm-aes-audit/CoreUtils/`。这是库行为，不自动决定CarPlay媒体的网络记录边界。

## A-40 CBCFrame不是链接上一帧，也不是PKCS#7

`_AES_CBCFrame_Init 0x18be62b48` 调用CCCryptorCreate：
operation=(dir==0 ? 1 : 0)、algorithm=0、options=0、keyLength=16、iv=NULL，输出句柄存ctx+0。
成功后复制传入16B IV至ctx+8。CommonCrypto的0/1分别为加密/解密，options0为CBC且不填充。
因此本包装器dir=0解密、非零加密（调用者通常传1），不是由构造顺序猜方向。

`_AES_CBCFrame_Update 0x18be62ba4`：

1. `62bcc` 计算full=len & ~15；full=0时直接进入字节拷贝，没有Reset/Update调用。
2. full>0时`62bdc..be4`把ctx+8交给CCCryptorReset，**每次重置保存的初始IV**。
3. `62bf0..c04`只给CCCryptorUpdate整块前缀full，输出容量也是full，无Final或填充。
4. `62c0c..c30`按库返回的moved推进src/dst，然后将余下输入字节原样复制。
   在正常无填充AES-CBC下moved=full，所以尾部len%16字节不加密；长度<16整段直通。
5. Reset或Update报错则立即返回，不做尾拷贝。此包装器没有独立检查moved==full，
   不把异常库输出也称为保证；也不假定错误时输出缓冲未被改变。

ctx+8的初始IV在Update内不被写回，不链接上一调用的末密文块。同一key/IV下相同调用输入得到相同输出。
**“一次Update”不能无证等同任意TCP分片或编码帧**：需核具体调用者选取的媒体边界。
历史OPEN-11所问的库级IV/尾块语义已关闭；网络profile与真实多记录互通仍未验证。

## A-41 CTR为AES-ECB生成密钥流，保留跨调用余量

`_AES_CTR_Init 0x18be628bc`以operation0、algorithm0、options2（ECB）、keyLength16建立句柄。
成功后把IV16B存ctx+8，ctx+0x28清0。ctx+0x18是16B密钥流缓存，+0x28是消费偏移。

`_AES_CTR_Update 0x18be62914`：

- 先消费上一调用剩余的缓存字节；偏移按 `(offset+1)&15` 回到0。
- 对新块把ctx+8的16B计数器交给CCCryptorUpdate，要求产出恰好16B；非16返回`-0x1a57`。
- 两处增量循环`629cc..9f4`、`62a70..a98`均从计数器byte15往byte0进位，**128位大端+1**。
  溢出后原函数回绕，不是只增低64位。
- 对输入逐字节XOR；不足16B也生成一个完整密钥流块并立即推进计数器，
  未消费字节留下供下一次Update。仅保存“下一计数器”而丢掉缓存会使分段处理失步。
- 空输入成功且不消费密钥流。原地src==dst可用；任意重叠缓冲不由此保证。
- 外部Update失败/产出长度异常不保证整次调用状态原子回滚；本轮不定义错误后重试协议。

独立实现应保留同一个CTR上下文跨调用；`aes128_ctr_crypt`是新建上下文的一次性便捷函数，
多段/多帧应使用`AES128CTR.update`。参考实现拒绝计数器耗尽后生成新块，是本地安全策略，非固件检查。

## A-42 固定128位key、收尾与实现结构边界

两个Init都固定传keyLength=16并复制IV16B。它们没有key长度参数，不提供AES192/256选择；
底层CommonCrypto支持那些长度不代表本包装器支持。调用者必须提供至少16B可读材料，
独立API应要求精确16B，不模拟固件对短缓冲的越界风险或把超长静默当AES256。
历史OPEN-9就本包装器已关闭，不推广到其他API/版本。

`CTR_Final 0x18be62afc`、`CBCFrame_Final 0x18be62c50`释放非NULL句柄后，分别用memset_s清48/24B。
这里的Final是资源清理，**不是CCCryptorFinal，不添加/输出PKCS#7块**。
这些是Apple内部上下文大小；独立客户端不必照抄内存布局，也不必在只发送的用途建立额外解密上下文。

## 证据、复算与边界

- 原始切片、导入桩：C13 `reference-impl/verify_aes_state.py`固定镜像SHA、逐字节比对和重反汇编；
  47个锚点、5个导入符号；有限解释两处进位循环和尾拷贝，不模拟外部CommonCrypto。
- API常量/契约：Apple公开CommonCrypto的[CommonCryptor.h](https://github.com/apple-oss-distributions/CommonCrypto/blob/a0ac082c490b65585ade764511acfdbf1d97bc5e/include/CommonCryptor.h)
  （2026-10-26读取）。algorithm=0是AES，不要仅从旧枚举名AES128推导key大小；这里由keyLength16证明。
- 独立已知答案：[NIST SP800-38A](https://doi.org/10.6028/NIST.SP.800-38A) F.2.1/F.5.1；
  两组64B答案、CTR 65种切分、81种CBC尾长、34种原指令进位与耗尽负例。
- 没有目标车机抓包、没有执行CommonCrypto二进制、没有新Ghidra输出。测试通过不升级为端到端互通。
