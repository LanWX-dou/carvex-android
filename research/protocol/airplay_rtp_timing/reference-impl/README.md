# reference-impl —— 参考解析/打包实现

> 作用：把 `spec/01` 的字节级规定落成可执行代码，供 `verify.py` 重算与第三方对照。
> 边界：**只实现有证据的字段**；第0字节/SSRC等在测试夹具中有占位值，不能当成已证协议要求；外层发送映射未实现，不是可直接连接车机的组包器。

## 文件

| 文件 | 内容 |
|---|---|
| `rtp_parser.py` | 固定头解析、元素区两态解析/打包、PT 规则、内部长度出参公式、子包时间戳重建；含 `self_test()` |
| `test_vectors.json` | 机器可读向量：元素打包 5 组、PT 改写 6 组、内部长度出参4组、元素区门 6 组 |
| `verify_compose_layout.py` | 原镜像/切片/.s一致性、双游标有限解释与L10截断反例；不执行外部API |
| `verify_audio_message.py` | 消息API/发送调用链/计数的原字节锚点与有限解释；依赖相邻FairPlay的AirPlaySupport镜像/元数据和仓库dsc-stubs.txt |

`build_packet`仅构造合成12B头坐标测试夹具；4B元素列表后自动补当前PT的1B终止元素。`PhonyPacket`遇缺终止元素、截断或扫描上限时拒绝；`element_count`若给出为含终止元素的上限，不是载荷起点。PT=0x60必须显式传入适用的`merged`模式。1481仍只是夹具的保守长度策略，不是已证线上MTU。夹具的严格检查不代表原固件已有同等检查。

## 用法

```bash
cd research/protocol/airplay_rtp_timing/reference-impl
python3 rtp_parser.py          # 自检，输出 "rtp_parser self_test: ok"
```

```python
from rtp_parser import PhonyPacket, build_packet
pkt = build_packet(0x64, sequence=0x1234, timestamp=0x1000,
                   elements=[(0x05, 0x2ABC, 0x155)], payload=b"...")
p = PhonyPacket(pkt)  # 自动扫描1B终止元素，不靠外部count定位载荷
print(hex(p.payload_type), p.sequence, hex(p.timestamp), p.sub_packet_timestamps())
```

## 与 `spec/01` 的对应

| 代码 | 条款 |
|---|---|
| `PhonyPacket.__post_init__` 的头 12 字节解析 | `R-1.1`–`R-1.4` |
| `MAX_PACKET` 长度检查 | `R-1.5` |
| `has_extended_header` | `R-1.9` |
| `pack_element` / `unpack_element` | `R-1.6`、`R-1.7`、`R-1.12` |
| `unpack_element_internal` | `R-1.11` |
| 元素扫描的终止（bit7=0） | `R-1.16` |
| `sub_packet_timestamps` | `R-1.8` |
| `header_length` | `R-1.10` |
| `remap_pt_for_merged` | `R-7.2` |

## 明确未实现

1. `pkt+0` 的版本/填充/扩展/CSRC 位：按 `spec/01 R-1.13` 属未定义，`build_packet` 只写`0x80`作为合成测试占位值，不宣称车机接受；
2. SSRC（`pkt+8..11`）：未定义，`build_packet` 留 0；
3. marker 位：未定义，`build_packet` 恒写 0；
4. 外层音频数据到网络包的映射（`spec/01 R-1.14`）；交错布局说法已撤回；
5. `B7`/`L10`的跨profile消费语义（`spec/01 R-1.15`）：这里只透传字段，不验证载荷切分。
