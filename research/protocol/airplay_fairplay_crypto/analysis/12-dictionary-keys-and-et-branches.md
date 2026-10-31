# 12 CFString键名与ET分支复核

## A-37 六个CFString可以解析，关闭历史OPEN-13的键名问题

此前把链式指针当绝对地址并拼错地址（`0x2591935b2b`），不能据此认定键名不可得。
原dyld缓存`.54.dylddata`中对象所在mapping为`0x271bf4000..0x2776e8000`，
其slide info version=5、value_add=`0x180000000`。这不是Mach-O自带fixups信息。
对这里的未认证指针：target=`value_add+(raw & ((1<<34)-1))`，再恢复high8；本表high8均0。
CFString对象的+16为data指针，+24为长度，flags=0x7c8；不能用flags低位当字符串长度。

| CFString地址 | 原始data指针 | 解码data地址 | 长度 | 拼写/角色 |
|---|---|---|---|---|
| 0x276118010 | 0x00200000d1935b2b | 0x251935b2b | 10 | `X-Apple-ET`，请求头取整型 |
| 0x276118030 | 0x00200000d1935b36 | 0x251935b36 | 4 | `CSeq`，请求头取字符串 |
| 0x276118e70 | 0x00200000d1938051 | 0x251938051 | 2 | `et`，安全信息字典整数键 |
| 0x2761199f0 | 0x00200000d1940452 | 0x251940452 | 4 | `ekey`，封装密钥数据 |
| 0x276119a10 | 0x00200000d1940457 | 0x251940457 | 3 | `eiv`，IV数据 |
| 0x276114350 | 0x00200000d192642b | 0x25192642b | 23 | `IsPINRequiredForPairing`，内部属性，不是新增线上键 |

六个对象与所有字符串均落在固定SHA的Receiver镜像内；对象原字节还与原cache交叉比对。
ADRP/ADD与getter桩复核见`verify_dictionary_keys.py`（C12），不是只读Ghidra占位名猜字符串。
**16B约束是解封后的key或IV数据长度，不是键名长度；ekey密文长度由FP核心给出。**
这关闭上述键名的静态未知项，不关闭整个/setup schema、目标车机profile或真实互通。

## A-38 `/fp-setup`类型选择不只“ET必须8或32”

`0x2518a53cc..5438`：`CFDictionaryGetInt64Ranged(request,"X-Apple-ET",0,0xffffffff,&err)`。

| getter结果 | 后续条件 | 本地FP type |
|---|---|---|
| err=0 | ET低32位=8 | 2 |
| err=0 | ET低32位=32 | 3 |
| err=0 | 其他值 | Bad ET错误路径 |
| err!=0 | `CFDictionaryCopyCString(request,"CSeq",NULL)`返回非NULL | 2，并保留该字符串 |
| err!=0 | 上述返回NULL | 3 |

仅有缺键时会这样处理的表述也太窄：判断的是getter错误码；这里只证明控制流，
不宣称所有错误原因等价，也不把CSeq的值解释为ET数值。独立客户端不应靠故意缺ET触发降级。
该getter读取入站请求；不能从这里推出ET一定由车机下发，发送端选择仍依赖目标profile。

## A-39 `/setup`安全信息的早退不等于完成安装密钥

`0x2518d3810..3834`读取小写`et`。getter失败或值=1跳到`0x2518d3ab0`，
将返回槽置0并进入ekey/eiv删除流程，不调用本分支的FP解封与AES设置。
只有进入后续封装密钥路径时，才在`386c..3878`要求et=32或8；其余进入Bad ET。
因此“缺ET必报Bad ET”“所有setup都必须含这三个字段”不成立。
这不证明et=1是可用明文协商、清掉旧密钥或绕过会话其他校验；客户端不能把本函数返回0当作新密钥已安装。

本轮未重新定义完整setup层级或所有调用者。`et`/`ekey`/`eiv`属于传入的安全信息字典，
何种profile在顶层/流条目使用以及必填条件需沿各调用者继续验证，不再无条件写“每流必填”。
