# spec 05 流建立：类型码 → 加密器

## R-5.1 分派表（24A446 目标构建的行为表，不是跨版本选码规范）

G定义见R-5.7；表格仅适用于keyholder已存在、方法和构造器成功的分派路径。
A/B是两个对象出参槽，未列出的槽为NULL，不代表主备或自动确定线上方向。

| 类型码 | G=0 | G≠0 |
|---|---|---|
| 0x60/0x66/0x67（96/102/103） | A=CBC | A=ChaCha(flag=1) |
| 0x64（100） | A/B=NULL | A/B各一个ChaCha，flag均1 |
| 0x65/0x6a（101/106） | A/B=NULL | A=ChaCha(flag=1) |
| 0x6b（107） | A/B=NULL | B=ChaCha(flag=1) |
| 0x6e/0x6f（110/111） | A=CTR | A=ChaCha(flag=0) |
| 0x78/0x82（120/130） | A/B=NULL | A/B=NULL |
| 其他 | Bad type | Bad type |

flag为构造器字节参数，不能未经使用者核验命名为方向或认证开关。provider参数及槽对应见A-45。
依据：A-19、A-43–A-45。级别：A（限定分派），不是目标车机能力表。

## R-5.2 ChaCha 的 key 必须 ≥ 32 字节

`APSCryptorChaCha20Poly1305Create` 校验 `CFDataGetLength(key) > 0x1f`，不满足即 `0xfffee7e1`。
实现侧应固定 32 字节，不要传 16 字节或 64 字节后截断。
依据：A-20（`0x226f2f54c`，比较常量 `0x1f`，错误子码 `0x98`）。级别：A。

## R-5.3 Apple CBC加密器建立两个方向的上下文

```
enc = AES_CBCFrame_Init(key, iv, dir=1)
dec = AES_CBCFrame_Init(key, iv, dir=0)
```

这是Apple对象实现：两个方向各自维护上下文。独立客户端按实际收发需求实现；只发送的调用者不必额外建立不用的解密对象。
依据：A-20、A-40/A-42。级别：A（Apple内部行为），不是强制内部架构要求。

## R-5.4 AES-CTR 的 key 与 iv 都不能为空

```
AES_CTR_Init(ctx, keyPtr, ivPtr)     // 任一为 NULL → 0xfffee7e1
```

CoreUtils Init已证固定AES key16B/IV16B；构造器本身未检查CFData长度，独立实现应严格检查。
依据：A-20、A-42。级别：A；历史OPEN-9关闭。

## R-5.5 明文流

到达分派时，120/130直接交出NULL对象；G=0时100/101/106/107也如此。
本函数不在这些分支调用APSCryptorGetNull。NULL只说明本处未创建加密对象，
不能保证目标profile接受、外层未加密或之后不会拒绝。
依据：A-44/A-45。级别：A（本地行为）。

## R-5.6 未知类型必须拒绝，不得猜

到达类型分派的未知值返回0xfffee76f。独立客户端应拒绝未支持类型，不默认当视频/无加密。
但原函数上游另有早退：G=0、storage+0x40非零且keyholder=NULL时可不检查type就成功，
只清A输出（若存在），B输出未写；这不是目标profile合法性的证明，不作为客户端绕过条件。
依据：A-44/A-45。级别：A（原分支）；独立拒绝未支持类型为本地策略。

## R-5.7 端点属性与对象存在性必须共同核对

G是内部端点描述的`SupportsCoreUtilsPairingAndEncryption`属性getter返回值，
0/非0按R-5.1分派；历史OPEN-7的属性名已闭合。非0并不使120/130创建ChaCha。
G≠0且keyholder为空先返回0xfffee773，包括120/130；G=0也有A-45所述对象门。
此属性从网络能力到内部描述的来源、目标profile及实际provider选择未闭合，不能自行切换，
不能把同名内部属性直接发到网络，不能把密码失败后切换G当降级。
依据：A-43–A-45。级别：A（属性/门控），目标profile适用性仍待证。

## R-5.8 类型码的语义名不是证据

本规范**不**写「0x6e 是视频」「0x60 是音频」这类断言。已知的只是 R-5.1 的行为表。
语义名 → `OPEN-8`，需实测：用某码建流，看车机建了什么会话 / 解出什么。
依据：A-19、`OPEN-8`。级别：A（禁止断言）。
