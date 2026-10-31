#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""AirPlay mDNS / DNS-SD 发现参考实现（只做解析与选择，不做配对/媒体）。

范围：
  * 解析 mDNS 报文（DNS 头、question、answer/authority/additional）；
  * 解码名称压缩、TXT 长度前缀串、SRV/A/AAAA/PTR；
  * 由多条报文重建服务图（PTR → SRV → TXT → A/AAAA）；
  * 处理 TTL=0（goodbye）并保留 cache-flush 标志；完整 RRset flush 仍由平台 DNS-SD 缓存层负责；
  * 给出可解释的候选排序（不自动连第一个）。

不做：
  * 不实现 AirPlay 配对、加密、RTSP、媒体；
  * 不打开套接字、不依赖第三方库；纯标准库，可离线跑测试向量。

用法：
  python3 mdns_discovery.py --vectors test_vectors.json
  python3 mdns_discovery.py --hex "40400006..."     # 解码单条报文并打印 JSON
"""
from __future__ import annotations

import argparse
import ipaddress
import json
import socket
import struct
import sys
import time

# ---------------------------------------------------------------- DNS 常量

TYPE_A = 1
TYPE_PTR = 12
TYPE_TXT = 16
TYPE_AAAA = 28
TYPE_SRV = 33
TYPE_NSEC = 47
TYPE_OPT = 41

CLASS_IN = 1
CLASS_MASK = 0x7FFF
CACHE_FLUSH = 0x8000

RCODE_NAMES = {0: "NOERROR", 1: "FORMERR", 2: "SERVFAIL", 3: "NXDOMAIN", 4: "NOTIMP", 5: "REFUSED"}


class DnsError(ValueError):
    """报文层错误：截断、指针环、非法长度。"""


# ---------------------------------------------------------------- 名称解码


def decode_name(buf: bytes, off: int, depth: int = 0, end: int | None = None) -> tuple[str, int]:
    """解码 DNS 名称，返回 (带结尾点的名字, 指向压缩指针之后的新偏移)。

    压缩指针只允许指向前文（ptr < 当前消息已读位置）；限制跳转次数防环。
    """
    if depth > 16:
        raise DnsError("名称压缩指针层级过深（疑似环）")
    end = len(buf) if end is None else min(end, len(buf))
    if off < 0:
        raise DnsError("名称偏移为负")
    labels: list[bytes] = []
    def display(parts):
        return ".".join(p.decode("utf-8", "surrogateescape").replace("\\", "\\\\").replace(".", "\\.") for p in parts)
    while True:
        if off >= end:
            raise DnsError("名称越界")
        ln = buf[off]
        if ln == 0:
            off += 1
            break
        if ln & 0xC0 == 0xC0:
            if off + 1 >= end:
                raise DnsError("压缩指针截断")
            ptr = ((ln & 0x3F) << 8) | buf[off + 1]
            if ptr >= off:
                raise DnsError("压缩指针必须指向前文")
            tail, _ = decode_name(buf, ptr, depth + 1)
            name = display(labels)
            result = (name + ("." if tail == "." else "." + tail)) if labels else tail
            if sum(len(s.encode("utf-8", "surrogateescape")) + 1 for s in split_labels(result)) + 1 > 255:
                raise DnsError("展开名称超过 255 字节")
            return result, off + 2
        if ln & 0xC0:
            raise DnsError(f"不支持的标签类型 0x{ln:02x}")
        off += 1
        if off + ln > end:
            raise DnsError("标签越界")
        labels.append(buf[off:off + ln])
        off += ln
    if sum(len(p) + 1 for p in labels) + 1 > 255:
        raise DnsError("展开名称超过 255 字节")
    name = display(labels)
    return (name + "." if name else "."), off


def split_labels(name: str) -> list[str]:
    """拆展示/配置字符串；线上编码仍由 encode_name 按 wire label 完成。"""
    if name in (".", ""):
        return []
    body = name[:-1] if name.endswith(".") else name
    out, cur, esc = [], [], False
    for ch in body:
        if esc:
            cur.append(ch)
            esc = False
        elif ch == "\\":
            esc = True
        elif ch == ".":
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    out.append("".join(cur))
    if esc or any(not label for label in out):
        raise DnsError("非法展示名称：空标签或悬空转义")
    return out


# ---------------------------------------------------------------- TXT 解码


def decode_txt(rdata: bytes) -> list[tuple[str, bytes | None]]:
    """把 TXT rdata 解成长度前缀串列表，再拆 key=value。

    无 '=' 的值为 None；有 '=' 但为空为 b''（RFC 6763 §6.4/6.5）。
    原始重复/非法键保留供诊断；业务查找用 effective_txt。
    """
    out: list[tuple[str, bytes | None]] = []
    off = 0
    while off < len(rdata):
        ln = rdata[off]
        off += 1
        if off + ln > len(rdata):
            raise DnsError("TXT 字符串长度越界")
        chunk = rdata[off:off + ln]
        off += ln
        if not chunk:  # 空字符串是空 TXT 表示，不是空名属性。
            continue
        if b"=" in chunk:
            k, v = chunk.split(b"=", 1)
        else:
            k, v = chunk, None
        out.append((k.decode("utf-8", "surrogateescape"), v))
    return out


def txt_to_dict(pairs: list[tuple[str, bytes | None]]) -> dict[str, list[str | None]]:
    """诊断视图，非业务字典：保留重复/大小写，无值为 None，二进制显示 hex。"""
    d: dict[str, list[str | None]] = {}
    for k, v in pairs:
        if v is None:
            d.setdefault(k, []).append(None)
            continue
        try:
            val = v.decode("utf-8")
        except UnicodeDecodeError:
            val = "0x" + v.hex()
        d.setdefault(k, []).append(val)
    return d


def effective_txt(pairs: list[tuple[str, bytes | None]]) -> dict[str, bytes | None]:
    """RFC 6763 §6.4：合法 ASCII 键不分大小写，首次出现生效；值仍是原字节。"""
    out = {}
    for k, v in pairs:
        if not k or any(ord(c) < 0x20 or ord(c) > 0x7e or c == "=" for c in k):
            continue
        out.setdefault(k.lower(), v)
    return out


# ---------------------------------------------------------------- 报文解析


def _read_rr(buf: bytes, off: int) -> tuple[dict, int]:
    name, off = decode_name(buf, off)
    if off + 10 > len(buf):
        raise DnsError("资源记录头截断")
    rtype, rclass, ttl, rdlen = struct.unpack_from("!HHIH", buf, off)
    off += 10
    if off + rdlen > len(buf):
        raise DnsError("资源记录 rdata 截断")
    rdata = buf[off:off + rdlen]
    rr: dict = {
        "name": name,
        "type": rtype,
        "class": rclass & CLASS_MASK,
        "cache_flush": bool(rclass & CACHE_FLUSH),
        "ttl": ttl,
        "rdata_len": rdlen,
    }
    if rtype == TYPE_A:
        if rdlen != 4:
            raise DnsError("A 记录必须为 4 字节")
        rr["address"] = str(ipaddress.IPv4Address(rdata))
    elif rtype == TYPE_AAAA:
        if rdlen != 16:
            raise DnsError("AAAA 记录必须为 16 字节")
        addr = ipaddress.IPv6Address(rdata)
        rr["address"] = str(addr)
        rr["link_local"] = addr.is_link_local
    elif rtype == TYPE_PTR:
        rr["target"], consumed = decode_name(buf, off, end=off + rdlen)
        if consumed != off + rdlen:
            raise DnsError("PTR RDATA 有多余字节")
    elif rtype == TYPE_SRV:
        if rdlen < 7:
            raise DnsError("SRV RDATA 不足 7 字节")
        prio, weight, port = struct.unpack_from("!HHH", rdata, 0)
        target, consumed = decode_name(buf, off + 6, end=off + rdlen)
        if consumed != off + rdlen:
            raise DnsError("SRV RDATA 有多余字节")
        rr.update({"priority": prio, "weight": weight, "port": port, "target": target})
    elif rtype == TYPE_TXT:
        pairs = decode_txt(rdata)
        rr["rdata_hex"] = rdata.hex()
        rr["txt"] = [{"key": k, "value_hex": None if v is None else v.hex(),
                      "has_value": v is not None, "value": txt_to_dict([(k, v)])[k][0]} for k, v in pairs]
        rr["txt_dict"] = txt_to_dict(pairs)
        rr["txt_effective"] = {k: values[0] for k, values in txt_to_dict(list(effective_txt(pairs).items())).items()}
    elif rtype == TYPE_NSEC:
        rr["nsec_raw"] = rdata.hex()
    elif rtype == TYPE_OPT:
        rr["opt_raw_len"] = rdlen
    else:
        rr["rdata_hex"] = rdata.hex()
    return rr, off + rdlen


def parse_datagram(buf: bytes, *, source_port: int) -> dict | None:
    """UDP 接收入口的源端口门；非 5353 的响应静默忽略（RFC 6762 §6）。

    parse_message 只解码字节，不掌握传输元数据。真实 I/O 还须保留接口、
    目标地址、legacy 查询关联等上下文；本函数不是完整 mDNS 栈。
    """
    if len(buf) < 12:
        raise DnsError("DNS 头不足 12 字节")
    if (buf[2] & 0x80) and source_port != 5353:
        return None
    return parse_message(buf)


def parse_message(buf: bytes) -> dict:
    if len(buf) < 12:
        raise DnsError("DNS 头不足 12 字节")
    (mid, flags, qd, an, ns, ar) = struct.unpack_from("!HHHHHH", buf, 0)
    # RFC 6762 §18.1: multicast response ID MUST be ignored on reception.
    # Legacy unicast also legitimately echoes a nonzero query ID.
    if (flags >> 11) & 0xF not in (0,):
        raise DnsError("mDNS OPCODE 不为 0")
    msg: dict = {
        "id": mid,
        "flags": flags,
        "qr": bool(flags & 0x8000),
        "opcode": (flags >> 11) & 0xF,
        "aa": bool(flags & 0x0400),
        "tc": bool(flags & 0x0200),
        "rd": bool(flags & 0x0100),
        "ra": bool(flags & 0x0080),
        "z": (flags >> 4) & 0x7,
        "rcode": flags & 0xF,
        "rcode_name": RCODE_NAMES.get(flags & 0xF, "?"),
        "questions": [],
        "answer": [],
        "authority": [],
        "additional": [],
    }
    off = 12
    for _ in range(qd):
        qname, off = decode_name(buf, off)
        if off + 4 > len(buf):
            raise DnsError("question 截断")
        qtype, qclass = struct.unpack_from("!HH", buf, off)
        off += 4
        msg["questions"].append(
            {
                "name": qname,
                "type": qtype,
                "class": qclass & CLASS_MASK,
                "unicast_response": bool(qclass & CACHE_FLUSH),
            }
        )
    for section, count in (("answer", an), ("authority", ns), ("additional", ar)):
        for _ in range(count):
            rr, off = _read_rr(buf, off)
            msg[section].append(rr)
    msg["consumed"] = off
    msg["trailing_bytes"] = len(buf) - off
    return msg


# ---------------------------------------------------------------- 服务图


class ServiceGraph:
    """单接口解析/聚合演示，并非完整 mDNS 缓存。

    TTL 正常过期和 goodbye 的一秒宽限已实现；完整 RRset cache-flush、
    多接口隔离、名称规范化和冲突消解仍需平台 DNS-SD 栈提供。
    """

    def __init__(self, clock=time.monotonic) -> None:
        self.clock = clock
        self.ptr: dict[tuple[str, str], dict] = {}
        self.srv: dict[tuple[str, str], dict] = {}
        self.txt: dict[tuple[str, str], dict] = {}
        self.addr: dict[str, dict[str, dict]] = {}
        self.log: list[str] = []

    def expire(self, now: float | None = None) -> None:
        """按收到时记录的实际 TTL 淘汰缓存。

        向量运行不会自动推进时钟；接入真实 socket 时由调用方周期性调用。
        """
        now = self.clock() if now is None else now
        for table_name in ("ptr", "srv", "txt"):
            table = getattr(self, table_name)
            for key, value in list(table.items()):
                if value.get("expires_at", float("inf")) <= now:
                    table.pop(key, None)
                    self.log.append(f"expire {table_name} {key}")
        for host, values in list(self.addr.items()):
            for addr, value in list(values.items()):
                if value.get("expires_at", float("inf")) <= now:
                    values.pop(addr, None)
                    self.log.append(f"expire addr {host} {addr}")
            if not values:
                self.addr.pop(host, None)

    def add_message(self, msg: dict, src: str | None = None) -> None:
        if not msg["qr"]:
            return  # query 中的 known-answer / probe 不是宣告
        for section in ("answer", "additional"):
            for rr in msg[section]:
                self._add_rr(rr, section, src)

    def _add_rr(self, rr: dict, section: str, src: str | None) -> None:
        received_at = self.clock()
        if rr["class"] != CLASS_IN:
            return
        # TTL=0 只影响完全相同的 RR，且给 cooperating responder 一秒救援。
        identity = {k: v for k, v in rr.items() if k not in ("ttl", "cache_flush")}
        def goodbye(table, key):
            old = table.get(key)
            if old and old.get("identity") == identity:
                old["expires_at"] = received_at + 1
        rtype = rr["type"]
        name = rr["name"]
        if rtype == TYPE_PTR:
            target = rr["target"]
            key = (name, target)
            if rr["ttl"] == 0:
                goodbye(self.ptr, key)
                self.log.append(f"goodbye PTR {name} -> {target}")
            else:
                old = self.ptr.get(key)
                if old and old.get("identity") != identity:
                    self.log.append(f"conflict PTR {name} -> {target}")
                self.ptr[key] = {"service": name, "instance": target, "ttl": rr["ttl"], "src": src, "expires_at": received_at + rr["ttl"], "identity": identity}
        elif rtype == TYPE_SRV:
            key = (name, "")
            if rr["ttl"] == 0:
                goodbye(self.srv, key)
                self.log.append(f"goodbye SRV {name}")
            else:
                old = self.srv.get(key)
                if old and old.get("identity") != identity:
                    self.log.append(f"conflict SRV {name}")
                self.srv[key] = {
                    "instance": name,
                    "target": rr["target"],
                    "port": rr["port"],
                    "priority": rr["priority"],
                    "weight": rr["weight"],
                    "ttl": rr["ttl"],
                    "src": src,
                    "expires_at": received_at + rr["ttl"],
                    "identity": identity,
                }
        elif rtype == TYPE_TXT:
            key = (name, "")
            if rr["ttl"] == 0:
                goodbye(self.txt, key)
                self.log.append(f"goodbye TXT {name}")
            else:
                old = self.txt.get(key)
                if old and old.get("identity") != identity:
                    self.log.append(f"conflict TXT {name}")
                self.txt[key] = {"instance": name, "pairs": rr["txt"], "dict": rr["txt_dict"], "effective": rr["txt_effective"], "rdata_hex": rr["rdata_hex"], "ttl": rr["ttl"], "src": src, "expires_at": received_at + rr["ttl"], "identity": identity}
        elif rtype in (TYPE_A, TYPE_AAAA):
            host = name
            addr = rr["address"]
            if rr["ttl"] == 0:
                goodbye(self.addr.get(host, {}), addr)
                self.log.append(f"goodbye {host} {addr}")
            else:
                old = self.addr.get(host, {}).get(addr)
                if old and old.get("identity") != identity:
                    self.log.append(f"conflict address {host} {addr}")
                self.addr.setdefault(host, {})[addr] = {
                    "address": addr,
                    "family": 4 if rtype == TYPE_A else 6,
                    "link_local": rr.get("link_local", False),
                    "ttl": rr["ttl"],
                    "expires_at": received_at + rr["ttl"],
                    "identity": identity,
                }
        # 其他类型（NSEC/OPT/未知）只记日志，不参与服务图
        else:
            self.log.append(f"ignore type {rtype} {name}")

    def services(self) -> dict[str, dict]:
        """返回 {service_type: {instance: {...}}} 形式的服务图。"""
        self.expire()
        out: dict[str, dict] = {}
        for (service, instance), meta in sorted(self.ptr.items()):
            entry = out.setdefault(service, {}).setdefault(
                instance,
                {"instance": instance, "service": service, "ptr_ttl": meta["ttl"], "srv": None, "txt": None, "addresses": []},
            )
            srv = self.srv.get((instance, ""))
            if srv:
                entry["srv"] = {k: srv[k] for k in ("target", "port", "priority", "weight", "ttl")}
                host = srv["target"]
                entry["addresses"] = [dict({k: v[k] for k in ("address", "family", "link_local", "ttl")}, host=host) for v in sorted(self.addr.get(host, {}).values(), key=lambda x: x["address"])]
            txt = self.txt.get((instance, ""))
            if txt:
                entry["txt"] = {"pairs": txt["pairs"], "dict": txt["dict"], "ttl": txt["ttl"]}
        return out

    def flat(self) -> list[dict]:
        out = []
        for service, instances in self.services().items():
            for instance, entry in instances.items():
                out.append(dict(entry, service=service, instance=instance))
        return out


# ---------------------------------------------------------------- 候选排序


def _ipv4_in_subnet(addr: str, net: str | None) -> bool:
    if not net:
        return False
    try:
        return ipaddress.IPv4Address(addr) in ipaddress.IPv4Network(net, strict=False)
    except ValueError:
        return False


def rank_candidates(entries: list[dict], ipv4_subnet: str | None = None,
                    interface: str | None = None) -> list[dict]:
    """给候选打分并附上理由。

    评分只表达「更容易连通的顺序」，不是「可信」；排序结果必须由调用方
    按策略使用，参考实现不自动连接任何一个。interface 必须由调用方从
    实际接收接口提供（单接口图），不是由 TXT/报文声明推断。
    """
    ranked = []
    for e in entries:
        reasons: list[str] = []
        score = 0
        srv = e.get("srv")
        if not srv:
            reasons.append("缺 SRV，不能得到端口")
            e = dict(e, score=-1, reasons=reasons, usable=False)
            ranked.append(e)
            continue
        if not isinstance(srv.get("port"), int) or not 0 < srv["port"] <= 65535:
            ranked.append(dict(e, score=-1, reasons=["SRV 端口不可用"], usable=False))
            continue
        addrs = e.get("addresses") or []
        if not addrs:
            reasons.append("缺 A/AAAA，不能得到可连地址")
            e = dict(e, score=-1, reasons=reasons, usable=False)
            ranked.append(e)
            continue
        best = None
        for a in addrs:
            s = 0
            r: list[str] = []
            if a["family"] == 4:
                s += 3
                r.append("IPv4")
                if _ipv4_in_subnet(a["address"], ipv4_subnet):
                    s += 2
                    r.append("与本地同网段")
            else:
                if a.get("link_local"):
                    if not interface:
                        reasons.append("IPv6 link-local 缺接收接口/scope，不可用")
                        continue
                    s += 1
                    r.append("IPv6 link-local（需要 scope/interface）")
                else:
                    s += 2
                    r.append("IPv6 全局")
            if best is None or s > best[0]:
                best = (s, a, r)
        if best is None:
            ranked.append(dict(e, score=-1, reasons=reasons, usable=False))
            continue
        score += best[0]
        reasons.extend(best[2])
        txt = e.get("txt") or {}
        d = txt.get("effective") or {}
        if "features" in d:
            reasons.append("TXT 提供 features")
        if "pk" in d:
            reasons.append("TXT 提供 pk（未认证，不能当身份）")
        e = dict(e, score=score, reasons=reasons, usable=True, preferred_address=best[1]["address"])
        if best[1].get("link_local"):
            e["preferred_scope"] = interface
        ranked.append(e)
    ranked.sort(key=lambda x: (-x["score"], x["instance"]))
    return ranked


# ---------------------------------------------------------------- 编码（测试用）


def encode_name(name: str) -> bytes:
    out = bytearray()
    for label in split_labels(name):
        raw = label.encode("utf-8", "surrogateescape")
        if len(raw) > 63:
            raise ValueError("标签超过 63 字节")
        out.append(len(raw))
        out += raw
    out.append(0)
    if len(out) > 255:
        raise ValueError("名称超过 255 字节")
    return bytes(out)


def encode_txt(pairs: list[tuple[str, str | bytes | None]]) -> bytes:
    """None 编码 key-only；空字符串/bytes 编码 key=；空属性集编码单个零字节。"""
    out = bytearray()
    for k, v in pairs:
        if not k or any(ord(c) < 0x20 or ord(c) > 0x7e or c == "=" for c in k):
            raise ValueError("TXT 键必须为非空 printable ASCII，且不含 =")
        chunk = k.encode("ascii")
        if v is not None:
            chunk += b"=" + (v.encode("utf-8") if isinstance(v, str) else v)
        if len(chunk) > 255:
            raise ValueError("TXT 字符串超过 255 字节")
        out.append(len(chunk))
        out += chunk
    return bytes(out) if out else b"\x00"


def build_message(
    answers: list[dict],
    questions: list[dict] | None = None,
    msg_id: int = 0,
    flags: int = 0x8400,
    additional: list[dict] | None = None,
) -> bytes:
    """构造 mDNS 报文（仅测试向量用）。

    rr 形如 {"name","type","ttl","rdata"}，rdata 已是字节。
    """
    questions = questions or []
    additional = additional or []
    out = bytearray(struct.pack("!HHHHHH", msg_id, flags, len(questions), len(answers), 0, len(additional)))
    for q in questions:
        out += encode_name(q["name"])
        out += struct.pack("!HH", q["type"], q.get("class", CLASS_IN) | (CACHE_FLUSH if q.get("qu") else 0))
    for rr in answers + additional:
        out += encode_name(rr["name"])
        out += struct.pack("!HHIH", rr["type"], CLASS_IN | (CACHE_FLUSH if rr.get("cache_flush") else 0), rr["ttl"], len(rr["rdata"]))
        out += rr["rdata"]
    return bytes(out)


def rr_ptr(name: str, target: str, ttl: int = 4500, cache_flush: bool = False) -> dict:
    return {"name": name, "type": TYPE_PTR, "ttl": ttl, "rdata": encode_name(target), "cache_flush": cache_flush}


def rr_srv(name: str, target: str, port: int, priority: int = 0, weight: int = 0, ttl: int = 120) -> dict:
    return {
        "name": name,
        "type": TYPE_SRV,
        "ttl": ttl,
        "cache_flush": True,
        "rdata": struct.pack("!HHH", priority, weight, port) + encode_name(target),
    }


def rr_txt(name: str, pairs: list[tuple[str, str | bytes | None]], ttl: int = 4500) -> dict:
    return {"name": name, "type": TYPE_TXT, "ttl": ttl, "cache_flush": True, "rdata": encode_txt(pairs)}


def rr_a(name: str, addr: str, ttl: int = 120) -> dict:
    return {"name": name, "type": TYPE_A, "ttl": ttl, "cache_flush": True, "rdata": socket.inet_aton(addr)}


def rr_aaaa(name: str, addr: str, ttl: int = 120) -> dict:
    return {"name": name, "type": TYPE_AAAA, "ttl": ttl, "cache_flush": True, "rdata": ipaddress.IPv6Address(addr).packed}


# ---------------------------------------------------------------- 向量执行


def run_vector(vec: dict) -> dict:
    """执行一条测试向量：喂入报文，产出服务图 + 排序。"""
    now = [0.0]
    graph = ServiceGraph(clock=lambda: now[0])
    msgs = []
    for pkt in vec["packets"]:
        now[0] = pkt.get("at", now[0])
        raw = bytes.fromhex(pkt["hex"])
        msg = parse_message(raw)
        msgs.append(msg)
        graph.add_message(msg, pkt.get("src"))
    now[0] = vec.get("snapshot_at", now[0])
    entries = graph.flat()
    ranked = rank_candidates(entries, vec.get("ipv4_subnet"))
    return {
        "messages": msgs,
        "graph": graph.services(),
        "flat": entries,
        "ranked": ranked,
        "log": graph.log,
    }


def check_expect(actual: dict, expect: dict) -> list[str]:
    """按向量里的 expect 字段做子集断言，返回失败描述列表。"""
    errs: list[str] = []
    flat = actual["flat"]
    if "instances" in expect:
        names = sorted(e["instance"] for e in flat)
        if names != sorted(expect["instances"]):
            errs.append(f"instances {names} != {expect['instances']}")
    if "ports" in expect:
        ports = sorted(e["srv"]["port"] for e in flat if e.get("srv"))
        if ports != sorted(expect["ports"]):
            errs.append(f"ports {ports} != {expect['ports']}")
    if "addresses" in expect:
        addrs = sorted(a["address"] for e in flat for a in e.get("addresses") or [])
        if addrs != sorted(expect["addresses"]):
            errs.append(f"addresses {addrs} != {expect['addresses']}")
    if "txt" in expect:
        for e in flat:
            got = (e.get("txt") or {}).get("dict") or {}
            for k, v in expect["txt"].items():
                if got.get(k) != v:
                    errs.append(f"txt[{k}] {got.get(k)} != {v}")
    if "txt_lists" in expect:
        for e in flat:
            got = (e.get("txt") or {}).get("dict") or {}
            for k, v in expect["txt_lists"].items():
                if got.get(k) != v:
                    errs.append(f"txt_lists[{k}] {got.get(k)} != {v}")
    if "ranked" in expect:
        got = [e["instance"] for e in actual["ranked"]]
        if got != expect["ranked"]:
            errs.append(f"ranked {got} != {expect['ranked']}")
    if "usable" in expect:
        got = [bool(e.get("usable")) for e in actual["ranked"]]
        if got != expect["usable"]:
            errs.append(f"usable {got} != {expect['usable']}")
    if "log_contains" in expect:
        for frag in expect["log_contains"]:
            if not any(frag in line for line in actual["log"]):
                errs.append(f"log missing {frag!r}")
    if "questions" in expect:
        got = [[q["name"], q["unicast_response"]] for m in actual["messages"] for q in m["questions"]]
        if got != [list(x) for x in expect["questions"]]:
            errs.append(f"questions {got} != {expect['questions']}")
    if "error" in expect:
        want = expect["error"]
        got = actual.get("error")
        if want is True and not got:
            errs.append("expected an error, got none")
        elif isinstance(want, str) and got != want:
            errs.append(f"error {got!r} != {want!r}")
    return errs


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--vectors", help="测试向量 JSON")
    ap.add_argument("--hex", help="单条报文十六进制")
    ap.add_argument("--json", action="store_true", help="输出机器可读结果")
    args = ap.parse_args()

    if args.hex:
        msg = parse_message(bytes.fromhex(args.hex))
        print(json.dumps(msg, ensure_ascii=False, indent=2))
        return 0

    if not args.vectors:
        ap.print_help()
        return 2

    doc = json.load(open(args.vectors, encoding="utf-8"))
    fails = 0
    for vec in doc["vectors"]:
        try:
            actual = run_vector(vec)
        except DnsError as exc:
            actual = {"error": str(exc), "flat": [], "ranked": [], "log": [], "graph": {}, "messages": []}
        errs = check_expect(actual, vec.get("expect", {}))
        status = "ok" if not errs else "FAIL"
        print(f"[{status}] {vec['name']}")
        for e in errs:
            print(f"    - {e}")
            fails += 1
    print(f"\n{len(doc['vectors'])} vectors, {fails} failures")
    return 0 if fails == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
