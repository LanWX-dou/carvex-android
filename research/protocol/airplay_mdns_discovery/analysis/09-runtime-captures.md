# 09 — 运行期抓包现状（本阶段最大缺口）

> 任务书完成判据第 2 条要求“至少一份真实车机的 Wi-Fi mDNS 抓包，能回放出完整服务图”。
> **本阶段没有这份抓包。** 本章记录：查了什么、为什么没有、怎么补、补不到时哪些结论必须保持 `OPEN`。

## 9.1 已经查过的位置

| 位置 | 结果 | 检查方式 |
|---|---|---|
| 整个工作区 `.pcap/.pcapng/.cap` | **0 个文件** | `Get-ChildItem -Recurse -Include *.pcap,*.pcapng,*.cap` |
| `sysdiagnose/…21G93/` 全部目录 | 无 `mdns`/`dns`/`bonjour`/`discover` 命名的文件 | 按文件名过滤 |
| `sysdiagnose/…/summaries/*.log`（139 个） | `airplay` **0 命中** | `findstr /s /i airplay` |
| `sysdiagnose/…/logs/Networking/` | 只有 `NetworkInterfaces.plist`、`networkextension*.plist`，无 mDNS 缓存 | 列目录 |
| `sysdiagnose/…/logs/parsecd/` | 只有 `config.plist`、`skapp_data`（5,754 B） | 列目录 |
| `sysdiagnose/…/WiFi/` | 有 `awdl_status.txt`、`wifi_status.txt`，**未发现 AirPlay 服务图** | 见 9.2 |
| `firmware/extracted/24A446/` | 是二进制提取，不是抓包 | — |

现有唯一的运行期材料是 **蓝牙经典** 的 23G90 记录（`research/protocol/iap2_control_session/runtime/23G90-bt-classic-2026-10-16.md`），它证明“车机与 iPhone 在同一场次完成 iAP2 识别/认证/CarPlay 启动”，**但不含任何 Wi-Fi 帧**，因此不能替代 mDNS 抓包。

## 9.2 为什么 sysdiagnose 不够

- `system_logs.logarchive` 是 tracev3 压缩容器，需要 `lzfse` + 专用解析；本机没有 `lzfse` 模块（`ModuleNotFoundError`），且日志里是否记了 TXT 原文本身不可知。
- `WiFi/awdl_status.txt` 只列 AWDL 对端，不含 DNS-SD 服务实例；CarPlay 无线走基础设施 Wi-Fi 时甚至不会出现在 AWDL 列表里。
- 结论：**sysdiagnose 不是抓包的替代品**，最多作为“当时连过哪台车”的旁证。

## 9.3 抓包 SOP（给能复现的人）

目标：拿到 **PTR → SRV → TXT → A/AAAA** 全链，最好含 Probe/Announce 与 Goodbye。

### 方案 A：笔记本镜像（推荐）

1. 让笔记本连到**车机自己开的 Wi-Fi**（不是手机热点），与车机同一网段。
2. 关闭“随机 MAC/私有 Wi-Fi 地址”之外的干扰不重要，关键是**允许组播**：
   - Windows：`dumpcap -i <接口> -f "udp port 5353" -w mdns.pcap`（Wireshark 自带 dumpcap；Windows 防火墙不影响收包，但 Wi-Fi 驱动可能过滤组播，见下）。
   - Linux：`sudo tcpdump -i wlan0 -s 0 -w mdns.pcap 'udp port 5353'`。
3. 触发顺序（每步间隔 5–10 s，便于在 pcap 里切段）：
   1. 车机冷启动/退出休眠；
   2. 手机加入车机 Wi-Fi；
   3. 发起无线 CarPlay 连接（或让车机进入可发现状态）；
   4. 等待 60 s（覆盖 TTL 刷新）；
   5. 断开连接/关闭车机，捕捉 Goodbye（TTL=0）。
4. 停止抓包，立刻记录：接口名、信道、时间（含时区）、车机型号/固件、手机型号/iOS 版本、是否同时连着蓝牙。
5. 计算哈希并归档：

```powershell
Get-FileHash .\mdns.pcap -Algorithm SHA256
```

### 方案 B：AP 侧镜像

在 OpenWrt/可镜像的路由器上：`tcpdump -i br-lan -s 0 -w /tmp/mdns.pcap 'udp port 5353'`，其余同上。
优点：不受终端 Wi-Fi 驱动组播过滤影响；缺点：如果车机与手机直连（SoftAP 模式），AP 侧看不到。

### 方案 C：车机自身抓包

若车机可开 adb/shell：`tcpdump -i any -s 0 -w /data/local/tmp/mdns.pcap 'udp port 5353'`。最接近“车机视角”，但很多车机不给权限。

### 验收前必须补齐的字段

抓包归入 `runtime/captures/`，同时写一个同名 `.json`：

```json
{
  "file": "mdns-2026-xx-xx.pcap",
  "sha256": "…",
  "interface": "wlan0 / br-lan / any",
  "channel": "6",
  "captured_at": "2026-xx-xxTxx:xx:xx+08:00",
  "capture_point": "笔记本 / AP / 车机",
  "head_unit": "型号 + 固件版本",
  "phone": "iPhone18,1 / iOS 27.0.1 (24A446)",
  "scenarios": ["cold-boot", "join", "browse", "goodbye"],
  "notes": "是否同时连蓝牙、是否开着 CarPlay"
}
```

`verify.py` 会校验：清单里的每个 pcap 存在、SHA256 一致、`.json` 字段齐全；**没有 pcap 时这一项记为 `OPEN-MDNS-7`，不算通过**。

## 9.4 抓包缺失时，哪些结论必须保持 OPEN

| 结论 | 缺抓包时 |
|---|---|
| 车机宣告哪些服务类型（是否只有 `_airplay._tcp`，有没有 `_raop._tcp`） | `OPEN-MDNS-8` |
| 实例名格式（是否含车机名/随机后缀） | `OPEN-MDNS-8` |
| SRV 端口是否固定 7000、target 是否 `.local` | `OPEN-MDNS-9` |
| TXT 键集合与取值（`features` 的实际十六进制、`pk`/`gid` 是否存在） | `OPEN-MDNS-10` |
| `features` 的位语义（只能证明客户端测了 bit55/bit56，不能证明全表） | `OPEN-MDNS-11` |
| TTL 实际取值、是否发 Goodbye | `OPEN-MDNS-5` |
| IPv6 是否可用、link-local scope 怎么给 | `OPEN-MDNS-12` |

这些不是“待办清单”，是**当前文档的诚实边界**：拿到 pcap 后按 `runtime/replay/` 的脚本跑一遍，逐条把 `OPEN` 改成结论，才算补完。

## 9.5 回放脚本怎么用（现在就能跑）

`reference-impl/mdns_discovery.py` 不依赖抓包库。拿到 pcap 后，用任意工具导出成 JSON（每个包一个 hex 串）：

```bash
tshark -r mdns.pcap -Y "udp.port==5353" -T fields -e frame.number -e data.data
```

把 `data.data` 去空格拼成 hex，按 `test_vectors.json` 的 `packets` 形状喂给解析器：

```bash
python3 reference-impl/mdns_discovery.py --hex "0000840000000001..."
```

`runtime/replay/replay.py` 就是这条链路的成品：`--from-tsv` 把 tshark 的 `frame/data.data` 两列转成 `packets.json`，`--packets` 回放并打印候选表；`--self-test` 用 10 条合成向量验证自己没坏（`verify.py` C9 会跑）。拿到 pcap 前它只能跑合成数据，回放结果的 `note` 字段会写明来源，**不会被当成真实车机观察**。
