# 04 音频密码处理：消息坐标、条件与状态

> 本专题服务设备侧客户端：媒体音向车机发送，车机麦克风向本设备接收。不能从接收helper反推所有媒体发送profile。原指令补证见 [09](09-message-coordinate-audit.md)。

## 4.1 消息不等于网络包

设M为音频CMBlockBuffer消息，T为消息总长，I为ReadNewMessage内部缓冲：
M复制到I+2，内部结束坐标L=T+2。M的头长10B，数据起点M+10对应I+12。
I+1由额外PT参数写入，I+0未由该拷贝设置。这不证明网络包就是这两字节加M。

g为元素区长度：没有元素时g=0；正常终止的RED描述符有C个块时g=4C-3。
因此解密输入范围在完整连续消息下为M[10+g:T]，等价I[12+g:L]。
无RED时即使内部C=1，也不能套公式得到g=1。

## 4.2 尾部开销不是“音频恒24”

CR-01提供某ChaCha叶子mode分支的16/24B开销线索。Sender raw100的G≠0路径创建两个flag=1对象，
不代表所有音频都经过此分支。[FairPlay分派](../../airplay_fairplay_crypto/analysis/14-cryptor-gates-and-output-slots.md)
已核type/G/keyholder联合门：例如96/102/103在G=0时为CBC，G≠0时为ChaCha；
100等在不同门下也可能无本层对象，不能据此批准线上明文。

只有实际provider已确认采用tag16+nonce8布局时，才能将对应密码输入的最后24B分为tag和nonce。
不能把相同规则套到所有流、所有外层包或所有RED块，也不能按认证失败自动试另一布局。

## 4.3 AAD入口（已重核）

AirPlaySupport的GetAudioAADPointer（0x226e68af0）在0x226e68b08将offset设2，
b14调用CMBlockBufferGetDataPointer，b20/b24把长度输出写为8。它操作的是M：

```text
AAD input = M[2:10]
          = I[4:12]       # 仅在已核M -> I复制路径成立
```

这是时间戳BE32和第二个BE32字段，不含M的序号。不能直接命名为“任意网络packet[4:12]”。
该helper本身不验证总长≥10；独立实现应先检查头完整，这是本地安全增强。
它提供AAD入口参数，但不证明所有cryptor都使用AEAD。

## 4.4 派生与方向

CoreUtils媒体KeyHolder以DataStream-Salt加传入整数的十进制表示作为salt，
info分别为DataStream-Input-Encryption-Key（31B）和DataStream-Output-Encryption-Key（32B），
两者均不含NUL；输出长度另外传入，raw100所述调用为32B。
视频analysis06已核ABI，控制面analysis15已核CoreUtils pairing provider的HKDF-SHA512输入门，
不能继续笼统称“算法未知”；目标会话选择该provider和整数ID来源仍需核验。

raw100的两输出槽与设备发送/麦克风接收的最终绑定，应以完整调用者链为依据；
旧+180/+1d0槽及Input/Output方向来自历史transaction线索，未将其推广为所有profile。
Legacy/CBC与其它provider不能套用CoreUtils标签。内部NULL不是明文协商。

## 4.5 失败、计数与发布

认证失败不向解码器或业务发布明文是独立实现的安全要求。
CR-04关于局部不提交长度/不递增计数的证据不能推出整个流水线、前面已成功的段或队列都已回滚。
必须分别记录本次处理的输入范围、已提交输出、密码状态及传输状态；不要盲重试原地buffer。
16B布局下的nonce来源和推进、24B布局尾nonce与内部状态关系均需绑定具体provider。

## 4.6 未闭合

- `OPEN-CRYPT-1`：外层网络映射、目标provider/profile、nonce/尾部及RED密码边界；
  不再把M+2/8B入口或正常C=n+1算术当全未知。
- `OPEN-CRYPT-2`：会话绑定的重放/去重策略，不能只凭未认证的seq声称防重放。
- `OPEN-CRYPT-3`：连续认证失败的恢复动作；既未证明必断线，也未证明应默认一直保持旧会话。
