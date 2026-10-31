# 07 — 装配路径：对象、双游标与长度出参

> 以 `source/asm/AirPlaySender/f_2519c348c.s` 原切片为准。旧版把相邻执行的元素写入与 memcpy 当作同一游标，进而推导“交错布局/末尾 RTP 头”，该推导已撤回。

## 7.1 结论摘要

| 编号 | 结论 | 强度 |
|---|---|---|
| `A07.1` | 当前镜像扫描发现两个直接 BL 调用点：`0x2519c2c4c`、`0x251b818f0`；不包括间接调用 | `CONFIRMED` |
| `A07.2` | 参数为 `(handler, inputWrapper, extraLength, outputWrapper, lengthOut, optionalCountOut)`；x3是包装对象，不是裸数据指针；返回OSStatus | `CONFIRMED（数据流）` |
| `A07.3` | 合并正常路径使用独立元素游标E和数据游标P，布局为连续元素、1B终止元素、所选旧载荷、当前载荷 | `CONFIRMED（内部数据区）` |
| `A07.4` | 最后复制的是GetAudioDataPointer返回的当前音频数据；Create长度实参包括当前数据、第三参数和合并数据 | `CONFIRMED` |
| `A07.5` | `lengthOut=4n+11`（单包10）与数据总长是不同量；主调用者用它推进后处理指针 | `CONFIRMED` |
| `A07.6` | analysis/11已核B=M+10、h为附加输出预留；网络映射与provider语义仍缺 | `OPEN-RTP-10` |
| `A07.7` | analysis/11已核第二调用者参数/后处理；实际选择及网络交付终点仍缺 | `OPEN-RTP-11` |

## 7.2 API与对象边界

`firmware/analysis/24A446/airplay-fairplay/dsc-stubs.txt` 的导入符号为：

| stub | 符号 |
|---|---|
| `0x25810dfc0` | `_APSTransportMessageGetAudioDataHeader` |
| `0x25810e050` | `_APSTransportMessageSetAudioDataHeader` |
| `0x25810dff0` | `_APSTransportMessageGetAudioDataTimestamp` |
| `0x25810dfd0` | `_APSTransportMessageGetAudioDataPointer` |
| `0x25810dfa0` | `_APSTransportMessageCreateReferencingBBufWithAudioDataLength` |

名字辅助识别边界，不替代API实现取证。Compose在`0x2519c3504`从`inputWrapper+0x10`取音频头，`0x2519c3514`把它设到`outputWrapper+8`；`0x2519c3520`复制包装对象首个32位字段，合并时`0x2519c35b4`改写该字段。它们不是对线上`pkt+1`的直接写入。

`0x2519c3540`从`outputWrapper+8`取数据地址B到`[sp+0x58]`，随后`0x2519c3558`才把B放入x28。不能把入口x28（对象）与此后的x28（数据游标）混为一谈。

## 7.3 两条独立游标

令n为成功路径所选旧载荷数量（w22），当前数据另计一份。容量/环队列选择位于`0x2519c35b8`–`0x2519c36b4`，这里不假定任意n都能入选。

```asm
0x2519c3558: ldr x28, [sp, #0x58]       ; E=B
...
0x2519c36c0: mov w9, #1
0x2519c36c4: bfi w9, w22, #2, #0x1e    ; w9=(4*n+1) mod 2^32
0x2519c36c8: add x24, x24, x9           ; 累计长度，初值为参数x2
0x2519c36cc: add x8, x8, x9
0x2519c36d0: str x8, [sp, #0x58]       ; P=B+4*n+1
...
0x2519c374c: str w8, [x28], #4         ; 写元素，只有E前移4
0x2519c3750: ldp x0, x1, [sp, #0x58]   ; x0=P，x1=旧载荷地址
0x2519c3754: bl #0x2580f43e0           ; 拷贝长度x2
0x2519c3758: ldur x8, [x29, #-0x58]    ; 旧载荷长度
0x2519c375c: ldr x9, [sp, #0x58]
0x2519c3760: add x10, x9, x8
0x2519c3764: str x10, [sp, #0x58]      ; 只有P前移载荷长度
```

正常完成所选n项后：

```text
B → [E0 4B] … [E(n-1) 4B] [当前PT & 0x7f 1B] [旧数据0] … [旧数据n-1] [当前数据]
     元素连续区             终止元素           音频数据连续区
```

`0x2519c37ec`在E写终止元素；`0x2519c3808`重新取得当前输入的音频数据，`0x2519c3824`复制到P。n=0的合并模式仍写1B终止元素；单包模式跳过元素区，仅在B复制当前数据。

这证明B起的内部音频数据区，与接收侧连续元素扫描没有“交错/连续冲突”。analysis/11已核B=M+10、M复制到I+2，B对应I+12；实际网络包映射仍缺。

`0x2519c3738`/`0x2519c3740`把这次复制的数据长度低10位写入L10，不含4B元素自身；B7来自所选输入包装对象首字段低7位；D14来自当前时间戳减旧时间戳的低14位。尚未证明所有profile同义，也没有证明上游永远保证长度≤1023。

## 7.4 两种长度与主调用者

正常、不溢出的输入域，设第三参数为h，旧数据长度为s_i，当前数据长度为s：

| 模式 | Create的x2实参（`0x2519c383c`） | `*lengthOut`（`0x2519c3854`） |
|---|---|---|
| 合并 | `h+4n+1+sum(s_i)+s` | `4n+11` |
| 单包 | `h+s` | `10` |

后者不是整包长度，不能据11分解出线上PT/seq/ts/SSRC。相对单包10增加的量正是元素区`4n+1`。

主调用者`f_2519c2770.s`：

- `0x2519c2a54`调用后处理对象虚方法取长度，经`0x2519c2a6c`存栈；无对象路径`0x2519c2a78`存0；`0x2519c2b64`恢复为x25，`0x2519c2c40`作为第三参数。h是数值开销，不是指针，算法语义待核。
- 编码读取结果长度在`0x2519c2b58`传给Create，生成`inputWrapper+0x10`；末尾音频数据并非“12字节头”。
- `0x2519c2b80`–`0x2519c2b8c`更新序号，`0x2519c2c20`填时间戳，`0x2519c2c2c`调用SetAudioDataHeader；不直接推出外层网络字节序。
- Compose成功后，`0x2519c2c98`读lengthOut，`0x2519c2ca0`用它推进后处理指针，`0x2519c2d48`从总量减去相关区间；不是把它作为socket整包发送长度。

## 7.5 实现与验证边界

可采用已证的元素编码和局部布局模型，但不能把包装对象偏移作为线上坐标。`reference-impl/verify_compose_layout.py`核对原切片和双游标算术，覆盖合并n=0/1/2、不等长载荷、单包及长度截断反例；不执行整个队列、外部API、密码库或网络发送。

| 未决 | 剩余关闭条件 |
|---|---|
| `OPEN-RTP-10` / `OPEN-RTP-1` | 音频消息API已由analysis/11补证；继续核provider算法、网络适配与实际发送范围 |
| `OPEN-RTP-11` | 第二调用者输入/后处理已核；继续核实际选择与下游网络交付 |
| `OPEN-RTP-4` | 核第二套PT掩码的各分支语义，不能因两套掩码就臆测交错布局 |
