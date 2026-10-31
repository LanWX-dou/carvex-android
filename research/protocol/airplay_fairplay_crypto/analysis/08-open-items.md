# 08 OPEN 台账（未证明项）

规则：OPEN必须在本文件登记；未证部分不得给确定值，部分闭合需分清边界。历史编号关闭后保留并标CLOSED。
当前11项未决、4项历史关闭（OPEN-7/9/11/13）；与12项覆盖分类计数是不同维度。
`verify.py` C4 会检查「spec 里引用的 OPEN 编号都在此表」。

---

## A-27 台账

| id | 未证明的问题 | 影响面 | 现有证据 | 需要什么才能关掉 |
|---|---|---|---|---|
| `OPEN-1` | FairPlay SAP消息语义与密钥封装算法 | 本项目未实现L1，不能仅凭外围完成握手 | analysis/02编排；无字面量不能证明算法不可能分析 | 适用的合法实现/授权接口，或进一步核心证据与受控输入输出 |
| `OPEN-2` | `_zxcm2Qme0x`（`0x2519f2904`，7,264 B）的用途 | 可能有未发现的 FP 分支 | 无直接调用者 | 反汇编通读 + 与 `Mib5yocT` 的常量比较 |
| `OPEN-3` | 目标CarPlay profile实际ET选择、发送责任与fallback适用性 | 决定FP type及兼容性 | 接收请求的X-Apple-ET与CSeq分支已核（A-38），不证明车机下发ET | 真实双向请求/响应或目标profile证据 |
| `OPEN-4` | `UpdateMasterAESKeyAfterSharing` 的调用时机 | 密钥刷新节奏 | 函数体完整，但无调用者 | 抓包观察换 key 前后帧；或读上层会话状态机 |
| `OPEN-5` | 旧 key 失效窗口与重传策略 | 丢包/重连行为 | 只知道「就地替换」 | 抓包 + 车机日志 |
| `OPEN-6` | 屏幕路径 16 字节密钥材料（会话 `+0x160`）的写入点 | 客户端如何得到同一材料 | 调用点确定，写入点未定位 | 对 `AirPlayReceiverSessionSetup` 全函数通读 |
| `OPEN-7` | CLOSED：门控属性的确切拼写 | 属性来源/profile仍影响互通 | A-43：原镜像符号、dyld v5原始指针与CFString字节均指向 `SupportsCoreUtilsPairingAndEncryption` | 目标profile如何映射到该内部能力、以及抓包对照（不再是拼写问题） |
| `OPEN-8` | 流类型码（0x60/0x64/0x65/0x66/0x67/0x6a/0x6b/0x6e/0x6f/0x78/0x82）的语义名字 | 文档可读性；选码 | 只有「码→行为」表（A-19） | 抓包看车机对哪种媒体建哪种会话 |
| `OPEN-9` | CLOSED：已核CTR/CBCFrame包装器固定AES128 key16B/IV16B | 不推广其他API/版本 | A-42：两Init固定CCCryptorCreate keyLength16、IV读取16B | C13原切片/锚点；短缓冲安全与完整profile另行处理 |
| `OPEN-10` | 屏幕128B头的发送构造/完整字段、其他回调路径及目标profile跨段互通 | **ChaCha 路线的正确性** | A-34已证头读入storage并作AAD；A-35已证可选双段，不再是空/零AAD二选一 | 补发送头构造证据；用合法密钥/nonce及完整原始头、已知明文对照，跨记录/双段校验目标库与profile |
| `OPEN-11` | CLOSED：CBCFrame逐Update重置初始IV，整块无填充CBC、余尾直通 | 关闭库级语义，不关闭媒体边界/实际互通 | A-40：Reset及尾拷贝原指令、CC公开契约 | C13进位/尾拷贝解释与NIST已知答案；网络调用者边界仍须核实 |
| `OPEN-12` | FP 消息内部是否有 magic/版本字段 | 消息可否自描述 | `FPLY` 字面量在三个镜像中不存在（A-28） | 抓包看 FP 载荷头 32 字节 |
| `OPEN-13` | CLOSED：本次涉及的六个CFString确切拼写 | 关闭静态键名问题，不关闭完整schema/互通 | A-37：原cache v5元数据、固定SHA镜像、六个对象/字符串、getter调用 | C12复算；目标profile与setup层级仍另需核实 |
| `OPEN-14` | 跨 iOS 版本的差异 | 版本兼容 | 仅 24A446 单一 build | 第二份固件做差分 |
| `OPEN-15` | KDF整数 `i` 的完整来源/传递及目标provider绑定 | 派生材料必须与对端一致 | A-17/A-46：Legacy直接格式化入参；Receiver从字典取非零整数再传给ForScreen，不支持“首流基址0/1”的假设 | 解析字段并追发送/接收链，核对目标会话provider和实际协商值；已知明文仅作交叉验证 |

## A-27 续一：历史OPEN-13已关闭

原稿把data链式指针直接当地址，误将工具解析失败当作键名不可得。
A-37用原始dyld v5 slide的value_add解析后，键名为请求头`X-Apple-ET`/`CSeq`、
安全信息字典`et`/`ekey`/`eiv`及内部属性`IsPINRequiredForPairing`。
16B是解封后key/IV数据约束，不是键名长度，ekey密文不保证16B。
完整setup schema层级/必填条件及目标profile仍未闭合，不能把关闭键名问题等同真实互通。

## A-27 续二：已确认项的边界声明

以下结论虽然确定，但只对**本 build（24A446）**成立：

- 流类型码表（A-19）。
- 错误码数值（A-25）。
- 名字前缀 `AirPlayStreamKey` / `AirPlayStreamIV`（A-17，字符串常量就在镜像里）。

跨版本是否一致 → `OPEN-14`。
