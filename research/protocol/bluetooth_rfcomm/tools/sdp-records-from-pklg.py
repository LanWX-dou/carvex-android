#!/usr/bin/env python3
"""从 pklg 抓包提取并解码 SDP 服务记录（双向）。

用途：为 `spec/09-client-open-rfcomm.md` 提供"车机/adapter 到底在 SDP 里暴露了什么"的运行时证据。

修正了首轮工具的三处缺陷（见 `runtime/captures/2026-10-rfcomm-pklg-reanalysis.md` §1）：
  1. ACL 记录同时接受 type=2（TX，host→controller）与 type=3（RX）；
  2. ACL 重组按 (handle, 方向) 分组，不再把双向交错拼进同一缓冲；
  3. 不依赖 PSM=3 判断 RFCOMM，SDP 直接按 L2CAP CID=1 取。

记录布局：[len:4 BE][ts:4][usec:4][type:1][payload]；总长 = 4 + len。

用法：python3 tools/sdp-records-from-pklg.py <pklg 文件> [...]
"""
import collections
import struct
import sys

SDP = 0x0001
ATTR = {0x0000: "ServiceRecordHandle", 0x0001: "ServiceClassIDList", 0x0002: "ServiceRecordState",
        0x0004: "ProtocolDescriptorList", 0x0005: "BrowseGroupList",
        0x0006: "LanguageBaseAttributeIDList", 0x0008: "ServiceAvailability",
        0x0009: "BluetoothProfileDescriptorList", 0x0100: "ServiceName",
        0x0101: "ServiceDescription", 0x0301: "SupportedFeatures"}


def records(path):
    data = open(path, "rb").read()
    off, n = 0, len(data)
    while off + 4 <= n:
        rl = struct.unpack_from(">I", data, off)[0]
        if rl < 9 or off + 4 + rl > n:
            break
        yield data[off + 12], data[off + 13:off + 4 + rl]
        off += 4 + rl


def acl_l2cap(path):
    """产出 (方向, handle, cid, body)。方向来自记录 type：2=TX，3=RX。"""
    dirs = {2: "TX", 3: "RX"}
    bufs = collections.defaultdict(bytearray)
    for typ, p in records(path):
        if typ not in dirs or len(p) < 4:
            continue
        hf, dlen = struct.unpack_from("<HH", p, 0)
        acl = p[4:4 + dlen]
        if len(acl) < dlen:
            continue
        key = (hf & 0x0FFF, dirs[typ])
        pb = (hf >> 12) & 0x3
        if pb == 0b01:
            bufs[key] += acl
        else:
            bufs[key] = bytearray(acl)
        buf = bufs[key]
        while len(buf) >= 4:
            l2len, cid = struct.unpack_from("<HH", buf, 0)
            if len(buf) < 4 + l2len:
                break
            body = bytes(buf[4:4 + l2len])
            del buf[:4 + l2len]
            yield key[1], key[0], cid, body


# 抓包里观察到的长度描述子：0x35 后跟 1 字节长度、0x36 后跟 2 字节长度
# （与教科书表格 5=2 字节、6=4 字节不同，故此处按实测取值，并对另一端做回退尝试）。
_LEN_BYTES = {4: 1, 5: 1, 6: 2, 7: 4}
_LEN_BYTES_ALT = {4: 1, 5: 2, 6: 4, 7: 8}


def de(b, i=0, table=None):
    """解码一个 SDP 数据元素 -> (值, 下一偏移)。"""
    table = table or _LEN_BYTES
    h = b[i]
    t, s = (h >> 3) & 0x1F, h & 7
    i += 1
    ln = {0: 1, 1: 2, 2: 4, 3: 8}.get(s)
    if ln is None:
        nb = table[s]
        ln = int.from_bytes(b[i:i + nb], "big")
        i += nb
    raw = b[i:i + ln]
    if len(raw) < ln:
        raise ValueError("truncated element")
    if t in (6, 7):
        out, j = [], 0
        while j < len(raw):
            v, j = de(raw, j, table)
            out.append(v)
        return out, i + ln
    if t == 3:
        if ln == 2:
            return ("uuid16", "%04x" % struct.unpack(">H", raw)[0]), i + ln
        if ln == 4:
            return ("uuid32", "%08x" % struct.unpack(">I", raw)[0]), i + ln
        if ln == 16:
            hx = raw.hex()
            return ("uuid128", "%s-%s-%s-%s-%s" % (hx[:8], hx[8:12], hx[12:16], hx[16:20], hx[20:])), i + ln
        return ("uuid?", raw.hex()), i + ln
    if t == 1:
        return ("uint", int.from_bytes(raw, "big")), i + ln
    if t == 4:
        return ("text", raw.decode("utf-8", "replace")), i + ln
    if t == 5:
        return ("bool", int.from_bytes(raw, "big")), i + ln
    return ("raw%d" % t, raw.hex()), i + ln


def rfcomm_channel(pdl):
    """从 ProtocolDescriptorList 取 RFCOMM 通道号；返回 (channel, proto_uuid)。"""
    for proto in pdl or []:
        if not isinstance(proto, list) or not proto:
            continue
        head = proto[0]
        if isinstance(head, tuple) and head[0] in ("uuid16", "uuid32") and head[1].endswith(("0001", "0003")):
            for p in proto[1:]:
                if p[0] == "uint":
                    return p[1], head[1]
    return None, None


def attr_pairs(lst):
    attrs, i = {}, 0
    while i + 1 < len(lst):
        aid, val = lst[i], lst[i + 1]
        if not isinstance(aid, tuple) or aid[0] != "uint":
            break
        attrs[int(aid[1])] = val
        i += 2
    return attrs


def main(paths):
    for path in paths:
        print("### pklg: %s" % path.split("/")[-1])
        stats = collections.Counter()
        seen = set()
        for direction, handle, cid, body in acl_l2cap(path):
            if cid == SDP or len(body) < 5:      # CID 1 是 L2CAP 信令，不是 SDP
                continue
            pid, tid = body[0], struct.unpack_from(">H", body, 1)[0]
            plen = struct.unpack_from(">H", body, 3)[0]
            if pid not in (0x02, 0x03, 0x04, 0x05, 0x06, 0x07) or plen != len(body) - 5:
                continue
            param = body[5:5 + plen]
            stats[(direction, pid)] += 1
            if pid == 0x07:                     # ServiceSearchAttributeResponse
                off = 2
            elif pid == 0x05:                   # ServiceAttributeResponse
                off = 0
            else:
                continue
            alen = struct.unpack_from(">H", param, off)[0]
            blob = param[off + 2:off + 2 + alen]
            lst = None
            for table in (_LEN_BYTES, _LEN_BYTES_ALT):
                try:
                    v, used = de(blob, 0, table)
                    if used == len(blob):
                        lst = v
                        break
                except Exception:
                    pass
            if lst is None:
                print("  ! 解码失败 tid=0x%04x（已试两种长度表）" % tid)
                continue
            attrs = attr_pairs(lst)
            cls = [v[1] for v in attrs.get(0x0001, []) if isinstance(v, tuple) and v[0].startswith("uuid")]
            ch, proto = rfcomm_channel(attrs.get(0x0004))
            base = 0
            for v in attrs.get(0x0006, []):
                if isinstance(v, list) and v and isinstance(v[0], tuple) and v[0][0] == "uint":
                    base = v[0][1]
            n = attrs.get(base + 0x0100) or attrs.get(0x0100)
            name = n[1] if isinstance(n, tuple) else None
            extra = {ATTR.get(k, "0x%04x" % k): v for k, v in attrs.items()
                     if k not in (0x0000, 0x0001, 0x0002, 0x0004, 0x0006, 0x0100)}
            key = (direction, handle, tid)
            if key in seen:
                continue
            seen.add(key)
            print("  [%s] handle=0x%x tid=0x%04x uuid=%s rfcomm_ch=%s proto=%s name=%r"
                  % (direction, handle, tid, ",".join(cls) or "-", ch, proto, name))
            if extra:
                print("       附加属性: %s" % extra)
        print("  PDU 统计（方向, PDU id）: %s" % dict(sorted(stats.items())))
        print()


if __name__ == "__main__":
    main(sys.argv[1:])
