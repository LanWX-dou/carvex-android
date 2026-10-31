# runtime/ 使用规则

本目录存放**运行期**素材。当前为空：本阶段没有任何 AirPlay 音频抓包（见
`analysis/08-runtime-captures.md`）。

## captures/

放原始抓包与元数据，命名 `YYYYMMDD-<车型或固件>-<场景>.pcap`，同名 `.md` 记录：

- 抓取时间、抓点（AP 网桥 / 车机侧 / 接收端替身）；
- 车机型号与固件、设备型号与 iOS 版本；
- 触发的用户动作（播放哪段音频、是否说话、是否人为丢包）；
- 五元组、`SETUP` 请求/回复全文；
- pcap 的 `sha256` 与字节数。

## replay/

放**从抓包派生**的可回放产物：`stream-<n>.jsonl`（每行一个包的
`ts/len/pt/seq/ssrc/tail24_hex`）、`summary.json`（包数、PT 直方图、seq 空洞）。
派生脚本与参数一并放这里，保证可重放。

## 禁止

- 不要把合成数据放进 `captures/`；
- 不要在没有 pcap 的情况下把 `replay/` 的内容写成「实测」；
- 不要提交含密钥、证书、设备序列号的明文素材（脱敏后单独放）。
