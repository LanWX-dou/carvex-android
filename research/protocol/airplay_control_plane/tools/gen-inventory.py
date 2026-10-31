# -*- coding: utf-8 -*-
"""Generate analysis/11-function-inventory.md from asm/readable artifacts.

Rows come from source/asm/<img>/index.json (what was actually exported); the
selection list is only used to report functions that were requested but not
exported, so the table can never claim a function we do not have bytes for.
"""
import json, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
rows = []
missing = []
for img in ("AirPlaySender", "APTransport", "CoreUtils"):
    sel = json.load(open(os.path.join(ROOT, "source/metadata", img, "selection.json"), encoding="utf-8"))
    idx = json.load(open(os.path.join(ROOT, "source/asm", img, "index.json"), encoding="utf-8"))
    by = {}
    for e in idx["functions"]:
        by[e["symbol"]] = e
        by[e["symbol"].lstrip("_")] = e
    for e in idx["functions"]:
        dec = os.path.join(ROOT, "readable/ghidra", img, "f_%s.ghidra.c" % e["address"].replace("0x", ""))
        rows.append((img, e["symbol"], e["address"], e["size"], "", os.path.exists(dec)))
    for f in sel["functions"]:
        if f["symbol"] not in by and "_" + f["symbol"] not in by:
            missing.append("%s" % f["symbol"].lstrip("_"))

lines = ["# 11 · 函数清单与覆盖", "",
         "> 采样说明见 `00-method-and-environment.md`。`反编译` 列：`✓` 有 Ghidra 输出（未复核），`—` 仅汇编。",
         "", "| 镜像 | 函数 | 地址 | 大小 (B) | 分组 | 反编译 |", "|---|---|---|---|---|---|"]
for img, sym, addr, size, group, dec in rows:
    lines.append("| `%s` | `%s` | `0x%s` | %d | %s | %s |" %
                 (img, sym.lstrip("_"), str(addr).replace("0x", ""), size, group, "✓" if dec else "—"))
lines += ["", "合计 %d 个函数（AirPlaySender %d / APTransport %d / CoreUtils %d）。" % (
    len(rows),
    sum(1 for r in rows if r[0] == "AirPlaySender"),
    sum(1 for r in rows if r[0] == "APTransport"),
    sum(1 for r in rows if r[0] == "CoreUtils")), ""]
if missing:
    lines += ["选中但未导出（结论中一律标 `OPEN`，不以函数名代替证据）：" +
              "、".join("`%s`" % m for m in sorted(set(missing))) + "。", ""]
open(os.path.join(ROOT, "analysis/11-function-inventory.md"), "w", encoding="utf-8").write("\n".join(lines))
print("wrote analysis/11-function-inventory.md rows=%d missing=%d" % (len(rows), len(set(missing))))
