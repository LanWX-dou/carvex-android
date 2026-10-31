# 06 — 每个 OPEN 项能不能只靠固件解决

本文件回答一个问题：**不抓包，只挖 24A446，哪些缺口能补、哪些补不了。**
判断依据是“该信息是否存在于 iPhone 侧二进制里”，不是“我们有没有努力找”。

## 6.1 结论总表

| OPEN | 固件能否回答 | 本轮结果 | 依据 / 还缺什么 |
|---|---|---|---|
| `OPEN-MDNS-1` 顺序（0x4301 vs mDNS） | 部分 | 收窄：普通浏览与 assisted 浏览是两条入口（`A01.9`），先后仍不可见 | 顺序在运行期，需抓包/日志 |
| `OPEN-MDNS-2` AWDL/NAN/QU | 部分 | `awdl0`/`nan0` 绑定与 assisted 的 `awdl0` 已证（`A01.9`、`A04.2`）；QU 在 mDNSResponder 里，镜像无 | QU 需抓包 |
| `OPEN-MDNS-3` TTL/重传/EDNS0 | 否 | 这些由 mDNSResponder 决定，提取集里没有该守护进程 | 抓包 |
| `OPEN-MDNS-4` 服务类型默认值 | 是（已关闭） | `csel` 两分支给出 `_airplay._tcp.`/`_sideplay._tcp.` | `A01.5` |
| `OPEN-MDNS-5` Probe/Announce/Goodbye | 否 | 同上，mDNSResponder 缺失 | 抓包 |
| `OPEN-MDNS-6` 未知 TYPE/RR | 否 | 三个二进制里没有 `NSEC`/`HINFO` 字符串 | 抓包 |
| `OPEN-MDNS-7` 缺抓包 | 否 | 固件里不会有车机的宣告 | 抓包 |
| `OPEN-MDNS-8` 车机服务类型/实例名 | 否 | 车机侧代码不在 iPhone 固件里 | 车机固件或抓包 |
| `OPEN-MDNS-9` SRV 端口 | 否 | 端口来自 SRV 记录，固件里没有“默认 7000”的证据 | 抓包 |
| `OPEN-MDNS-10` 车机 TXT 取值 | 否 | 只有键名与读者，没有车机的值 | 抓包 |
| `OPEN-MDNS-11` 位语义 | 部分 | 位的位置已定（55/56 在 extended 半，`A02.7`），含义没有读者证据 | Apple 文档或行为验证 |
| `OPEN-MDNS-12` IPv6/scope | 部分 | link-local 转换路径存在（`A04.7`）、IPv4/IPv6 分别监听（`A04.8`） | 车机是否发 IPv6：抓包 |
| `OPEN-MDNS-13` `pk`/`pi`/`gid` 信任 | 部分 | 只见构造 TXT 的写入，发现路径无校验（`A02.3`） | 配对阶段 |
| `OPEN-MDNS-14` features 文本语法 | 是（已关闭） | 格式串 `0x%X` / `0x%X,0x%X`（低,高） | `A02.6` |
| `OPEN-MDNS-15` `fex` 结构 | 部分 | 已证是独立字符串键（`A02.8`），内部结构无 | 抓包 + 更多反汇编 |
| `OPEN-MDNS-16` 多地址选择 | 部分 | 有 IPv4/IPv6 监听与 `enableForceIPv4Addressing` 偏好键（`A04.8`），选择逻辑不可见 | 行为验证 |
| `OPEN-MDNS-17` 实例名形态 | 部分 | 名字直接取自 info 属性、无固定后缀（`APAdvertiserInfoCreateAirPlayServiceName`） | 车机取值：抓包 |
| `OPEN-MDNS-18` 版本差异 | 否 | 只有 24A446 一个构建 | 第二构建/车机 |
| `OPEN-MDNS-19` 切网/代理 | 否 | 运行期行为 | 抓包（切网场景） |
| `OPEN-MDNS-20` 冒充/冲突 | 否 | 需要对抗实验 | 实验 + 抓包 |
| `OPEN-MDNS-21` 休眠/唤醒 | 否 | 运行期行为 | 抓包（休眠场景） |

统计：**固件可判并已关闭 2 条**（4、14）；**部分可判、已收窄 8 条**（1、2、11、12、13、15、16、17）；**不可判 11 条**（3、5、6、7、8、9、10、18、19、20、21）。

## 6.2 为什么 mDNSResponder 不在

- `firmware/extracted/24A446/binaries/` 只有 51 个二进制，全部是 App/框架（AirPlay、CarPlay、Accessory、WiFi 相关）；
- `/usr/sbin/mDNSResponder`、`networkd` 属 rootfs，未在提取集内；`glob mDNSResponder*` 为 0 命中；
- 因此 TTL、Probe/Announce 间隔、QU、缓存刷新这些**守护进程内部常量**在固件里查不到，只能靠抓包或 Apple 开源代码（本阶段无网络，未核对）。

## 6.3 固件还能继续挖的方向（按性价比）

1. **`APTransport` 的 TXT 构造器全表**：`__APAdvertiserInfoAddStringToTXTRecord` 的 52 个调用点里还有 `raop`/`et`/`ft`/`sf`/`md`/`am`/`tp`/`vs`/`ov` 等键的取值来源，可补 `analysis/03` 的写方列。
2. **`APAssistedModeBrowser` 的 `assistedInfo` 键**：`getExpectedBonjourService` 的格式串（`0x275fa7900`）解码后可确认“服务名+协议”的拼接形态。
3. **`enableForceIPv4Addressing` 的读者**：找到读取该偏好的函数即可把 `OPEN-MDNS-16` 再收窄一档。
4. **`AirPlayReceiver` 的宣告端**：它是“手机作为接收方”的路径，可对照出 TXT 键的完整集合与默认值，但**不能**代表车机。

这些都需要 Ghidra 项目（本轮的 `/tmp/ghidra-apt` 已被清理），重跑 `analyzeHeadless` 约 5 分钟；指令级证据已写入 `analysis/01`/`03`/`04`，可复核。
