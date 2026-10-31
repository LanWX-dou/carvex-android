#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""runtime/replay/replay.py — 把 mDNS 报文回放成服务图与候选表。

三种用法：

    # 1) 自测：用合成向量验证回放链路
    python3 runtime/replay/replay.py --self-test

    # 2) 回放一份 packets.json（抓包导出或手写）
    python3 runtime/replay/replay.py --packets captures/xxx.packets.json

    # 3) 把 tshark 导出的 TSV 转成 packets.json
    tshark -r x.pcap -Y "udp.port==5353" -T fields -e frame.number -e data.data > raw.tsv
    python3 runtime/replay/replay.py --from-tsv raw.tsv --out captures/x.packets.json

packets.json 形状：

    {"note": "真实抓包 / 合成", "ipv4_subnet": "192.168.1.0/24",
     "packets": [{"hex": "0000...", "src": "192.168.1.2:5353"}],
     "expect":  {"instances": [...], "ports": [...]}}     # 可选

本工具只解析字节、不做连接；输出是“解析器在这些字节上看到了什么”。
"""
import argparse
import json
import pathlib
import re
import sys

HERE = pathlib.Path(__file__).resolve().parent
DOCSET = HERE.parent.parent
sys.path.insert(0, str(DOCSET / "reference-impl"))

import mdns_discovery as md  # noqa: E402

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
sys.stderr.reconfigure(encoding="utf-8", errors="replace")


def hexify(s: str) -> str:
    """去掉冒号/空格，只留十六进制字符。"""
    return re.sub(r"[^0-9a-fA-F]", "", s)


def load_packets(path: pathlib.Path) -> dict:
    doc = json.loads(path.read_text(encoding="utf-8"))
    if "packets" not in doc:
        raise SystemExit(f"{path}: 缺少 packets 字段")
    return doc


def replay(doc: dict) -> dict:
    doc = dict(doc)
    doc["packets"] = [{"hex": hexify(p["hex"]), **{k: v for k, v in p.items() if k != "hex"}}
                      for p in doc["packets"]]
    return md.run_vector(doc)


def candidate_rows(actual: dict) -> list[dict]:
    rows = []
    for r in actual.get("ranked", []):
        addrs = []
        for a in r.get("addresses", []):
            addrs.append(a.get("address") if isinstance(a, dict) else a)
        rows.append({
            "instance": r.get("instance"),
            "host": r.get("host") or (r.get("srv") or {}).get("target"),
            "port": (r.get("srv") or {}).get("port"),
            "addresses": addrs,
            "txt_keys": sorted((r.get("txt") or {}).keys()),
            "usable": r.get("usable"),
            "score": r.get("score"),
            "reasons": r.get("reasons", []),
        })
    return rows


def print_table(rows: list[dict], out=sys.stdout) -> None:
    print("| 实例 | 主机 | 端口 | 地址 | TXT 键 | 可用 | 分 | 理由 |", file=out)
    print("|---|---|---|---|---|---|---|---|", file=out)
    for r in rows:
        print("| {instance} | {host} | {port} | {addresses} | {txt_keys} | {usable} | {score} | {reasons} |".format(
            instance=r["instance"] or "—",
            host=r["host"] or "—",
            port=r["port"] if r["port"] is not None else "—",
            addresses=", ".join(r["addresses"]) or "—",
            txt_keys=", ".join(r["txt_keys"]) or "—",
            usable="✅" if r["usable"] else "❌",
            score=r["score"] if r["score"] is not None else "—",
            reasons="; ".join(r["reasons"]) or "—",
        ), file=out)


def self_test() -> int:
    vec = DOCSET / "reference-impl" / "test_vectors.json"
    doc = json.loads(vec.read_text(encoding="utf-8"))
    total = failed = 0
    for v in doc["vectors"]:
        total += 1
        expect = v.get("expect", {})
        want_error = bool(expect.get("error"))
        try:
            actual = replay(v)
        except Exception as exc:  # noqa: BLE001
            if want_error:
                print(f"[ ok ] {v['name']}: 按预期报错（{type(exc).__name__}: {exc}）")
            else:
                failed += 1
                print(f"[FAIL] {v['name']}: 回放异常 {exc}")
            continue
        if want_error:
            failed += 1
            print(f"[FAIL] {v['name']}: 期望报错但解析成功")
            continue
        errs = md.check_expect(actual, expect)
        if errs:
            failed += 1
            print(f"[FAIL] {v['name']}: " + "; ".join(errs))
        else:
            print(f"[ ok ] {v['name']}: {len(actual['flat'])} 个实例, "
                  f"{len(actual.get('ranked', []))} 条候选")
    print(f"\n{total} vectors, {failed} failures")
    return 1 if failed else 0


def from_tsv(path: pathlib.Path, out: pathlib.Path) -> int:
    packets = []
    bad = 0
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if not line.strip():
            continue
        parts = line.split("\t")
        hx = hexify(parts[-1])
        if len(hx) < 24 or len(hx) % 2:
            bad += 1
            continue
        packets.append({"hex": hx, "frame": parts[0] if len(parts) > 1 else None})
    doc = {"note": f"从 {path.name} 导出；未人工核对", "packets": packets}
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(doc, ensure_ascii=False, indent=1), encoding="utf-8")
    print(f"wrote {out} packets={len(packets)} skipped={bad}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description="mDNS 回放：packets → 服务图 → 候选表")
    ap.add_argument("--self-test", action="store_true", help="用合成向量自测")
    ap.add_argument("--packets", type=pathlib.Path, help="packets.json")
    ap.add_argument("--from-tsv", type=pathlib.Path, help="tshark -T fields 导出的 TSV")
    ap.add_argument("--out", type=pathlib.Path, help="--from-tsv 的输出")
    ap.add_argument("--json", action="store_true", help="输出机器可读 JSON")
    args = ap.parse_args()

    if args.self_test:
        return self_test()
    if args.from_tsv:
        if not args.out:
            raise SystemExit("--from-tsv 需要 --out")
        return from_tsv(args.from_tsv, args.out)
    if not args.packets:
        ap.print_help()
        return 2

    doc = load_packets(args.packets)
    want_error = bool((doc.get("expect") or {}).get("error"))
    try:
        actual = replay(doc)
    except Exception as exc:  # noqa: BLE001
        if want_error:
            print(f"[expect 通过] 按预期报错：{type(exc).__name__}: {exc}")
            return 0
        print(f"[解析失败] {type(exc).__name__}: {exc}")
        return 1
    if want_error:
        print("[expect 失败] 期望报错但解析成功")
        return 1
    rows = candidate_rows(actual)
    if args.json:
        print(json.dumps({"candidates": rows, "log": actual.get("log", []),
                          "packets": len(doc["packets"])},
                         ensure_ascii=False, indent=1, default=str))
    else:
        note = doc.get("note", "")
        print(f"# 回放 {args.packets.name}：{len(doc['packets'])} 个报文"
              + (f"（{note}）" if note else ""))
        print()
        print_table(rows)
        if actual.get("log"):
            print("\n解析日志：")
            for line in actual["log"]:
                print(f"- {line}")
    if "expect" in doc:
        errs = md.check_expect(actual, doc["expect"])
        if errs:
            print("\n[expect 失败] " + "; ".join(errs))
            return 1
        print("\n[expect 通过]")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
