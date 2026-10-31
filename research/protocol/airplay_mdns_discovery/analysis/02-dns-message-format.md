# 02 — DNS 报文格式（mDNS 传输的载荷）

> 本章回答覆盖项 2：**header / question / RR 如何布局、名称压缩怎么处理、TXT 怎么编码**。
> 每条规则都对应 `reference-impl/mdns_discovery.py` 里的一个函数，并由 `test_vectors.json` 的向量覆盖——所以这一章是**可执行**的。

## 2.1 头部（12 字节，网络序）

| 偏移 | 字段 | 长度 | mDNS 取值 | 参考实现 |
|---|---|---|---|---|
| 0 | ID | 2 | 恒 `0x0000`（mDNS 不用事务 ID） | `parse_message` 保留原值，不校验 |
| 2 | FLAGS | 2 | 见 §2.2 | `parse_message` 拆成 qr/opcode/aa/tc/rd/ra/z/rcode |
| 4 | QDCOUNT | 2 | 问题数 | 循环解析 |
| 6 | ANCOUNT | 2 | answer 数 | 循环解析 |
| 8 | NSCOUNT | 2 | authority 数 | 循环解析 |
| 10 | ARCOUNT | 2 | additional 数 | 循环解析 |

## 2.2 FLAGS 位

| 位 | 名称 | mDNS 用法 |
|---|---|---|
| 15 | QR | 0=查询，1=响应 |
| 14–11 | OPCODE | `0`（标准查询） |
| 10 | AA | 响应里通常为 1（权威） |
| 9 | TC | 截断标志；出现时接收方应等待更多数据（`OPEN-MDNS-3`） |
| 8 | RD | 0（mDNS 不做递归） |
| 7 | RA | 0 |
| 6–4 | Z | 0 |
| 3–0 | RCODE | 0 |

参考实现把 OPCODE≠0 的响应当作错误（`DnsError`），因为 mDNS 不允许其他 opcode。

## 2.3 名称与压缩

- 名称是标签序列：每字节长度（≤63）+ 标签字节，以 `0x00` 结尾。
- 压缩指针：两字节，高两位 `11`，低 14 位是**从报文起始**算的偏移；只能指向**前文**（RFC 1035 §4.1.4 “prior occurrence”）。
- 参考实现 `decode_name`：
  - 指针必须 `ptr < 当前读取位置`，否则报 `压缩指针必须指向前文`——这比“宽容解析”更严，目的是把畸形报文变成可诊断错误，而不是静默接受；
  - 递归深度上限 16，防指针环；
  - 保留原始标签字节，用 `surrogateescape` 解 UTF-8，避免非 UTF-8 名字直接崩。
- 两个向量覆盖错误路径：`bad-pointer`（指针指自身）、`truncated-question`（header 声称有问题但无字节）。

## 2.4 资源记录（RR）

```text
NAME     (压缩名称)
TYPE     2 字节
CLASS    2 字节，最高位 = cache-flush（mDNS）
TTL      4 字节（秒）
RDLENGTH 2 字节
RDATA    RDLENGTH 字节
```

本阶段涉及的 TYPE：

| TYPE | 值 | RDATA | 参考实现字段 |
|---|---|---|---|
| A | 1 | 4 字节 IPv4 | `address` |
| PTR | 12 | 一个名称 | `target` |
| TXT | 16 | 长度前缀串序列 | `txt` / `txt_dict` |
| AAAA | 28 | 16 字节 IPv6 | `address`、`link_local` |
| SRV | 33 | priority(2) weight(2) port(2) target(名称) | `priority`/`weight`/`port`/`target` |
| NSEC | 47 | 名称 + 位图 | `nsec_raw`（只保留原始字节） |
| OPT | 41 | EDNS0 | `opt_raw_len`（只记长度） |

未知 TYPE 一律保留 `rdata_hex`，不丢、不猜（对应任务书“未知键保留原始字节”的要求）。

## 2.5 TXT 记录

`[RFC 6763 §6]`：

- RDATA 是一个或多个“长度前缀字符串”：`len(1) + bytes(len)`，**没有 NUL 结尾**；
- 每个字符串通常是 `key=value`；没有 `=` 的整串是“只有键、无值”的属性（boolean）；
- 键是非空可打印 ASCII（不含 `=`），比较不区分 ASCII 大小写；不应发送重复键，接收业务解释取首次出现，诊断层可保留全部原始项；
- 字符串最大 255 字节；整个 TXT 记录建议 ≤ 1300 字节以免分片。

参考实现 `decode_txt` 的行为：

| 情况 | 行为 | 向量 |
|---|---|---|
| `k=v` | 拆成键值 | `full-chain` |
| 无 `=` / 有 `=` 但为空 | 分别为 `None` / `b''`；不能混同 | C10 独立字节反例 |
| 重复键 | `txt_to_dict` 诊断保留列表，`effective_txt` 不区分大小写 first-wins | `duplicate-key` + C10 |
| 非 UTF-8 值 | 转成 `0x` + 十六进制，不丢弃 | `unknown-key-binary` |
| 未知名 | 原样保留 | `unknown-key-binary` |
| 字符串越界 | `DnsError` | — |

## 2.6 参考实现的解析结果形状

```json
{
  "id": 0, "flags": 33792, "qr": true, "aa": true, "tc": false,
  "questions": [{"name": "_airplay._tcp.local.", "type": 12, "unicast_response": false}],
  "answer": [{"name": "_airplay._tcp.local.", "type": 12, "ttl": 4500, "target": "Living Room._airplay._tcp.local."}],
  "additional": [{"name": "Living Room._airplay._tcp.local.", "type": 33, "port": 7000, "target": "Demo-Receiver.local."}]
}
```

字段名是**本参考实现自己的**，不是 Apple 的 API 名；写客户端时按这个形状建模即可，不要去找同名符号。

## 2.7 本章未解决

| 编号 | 问题 |
|---|---|
| `OPEN-MDNS-3` | 截断（TC）与分片、EDNS0 优化、NSEC 的实际用法 |
| `OPEN-MDNS-6` | 车机报文里是否出现未知 TYPE/RR，以及它们是否影响解析 |
