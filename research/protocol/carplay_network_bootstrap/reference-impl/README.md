# reference-impl — bootstrap_fsm

这是 `carplay_network_bootstrap` 的纯规划模型，不执行真实网络操作。

它把 `spec/01`–`spec/03` 中可编码的部分固定下来：

- `0x4301` 子集校验：SSID、securityType、channel、passphrase；
- 凭据记录：`CredentialRecord`（不伪造 `CarPlayUUID`）；
- BSSID → IPv6 link-local（EUI-64，样本规则，不宣称为通用）；
- 端点候选与显式策略（`4301-first` / `link-local-first` / `mdns-first`）；来源权威仍是 `OPEN-NB-4`；
- 输出 `BootstrapPlan`，附带 `OPEN-NB-*` 列表和 warning。

它**不**做关联、DHCP、mDNS 查询、TCP 连接；这些由平台适配层执行并记录 wire log。

## 用法

```bash
python3 -B test_bootstrap.py
```

## 示例

```python
from bootstrap_fsm import StartParams, plan_bootstrap

plan = plan_bootstrap(
    StartParams(
        ssid="CFMOTO4801",
        password="<redacted>",
        security_type=2,
        channel=157,
        wifi_ips=("192.168.43.1",),
        port=7000,
    ),
    carplay_uuid="80A46250-7FB2-4A9F-ACF1-8F551F286B88",
    bssid="6c:df:4a:14:6e:ea",
)
print(plan.endpoint.dial_string())  # 192.168.43.1:7000
print(plan.open_items)
```

测试全部为合成输入；通过测试不代表真实车机接受这些参数。
