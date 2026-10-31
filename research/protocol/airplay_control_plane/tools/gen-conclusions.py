# -*- coding: utf-8 -*-
"""Collect A-conclusion ids from analysis/*.md into analysis/A-conclusions.md (registry)."""
import glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pat = re.compile(r"`?(A\d\d\.\d+)`?")
items = {}
order = []
for path in sorted(glob.glob(os.path.join(ROOT, "analysis", "[0-9]*.md"))):
    name = os.path.basename(path)
    for line in open(path, encoding="utf-8"):
        for m in pat.finditer(line):
            aid = m.group(1)
            if aid not in items:
                text = re.sub(r"[`*]", "", line).strip()
                text = text.replace("|", "/")[:150]
                items[aid] = (name, text)
                order.append(aid)

lines = ["# A · 结论登记", "",
         "> 本表由 `tools/gen-conclusions.py` 从 `analysis/*.md` 汇总；每条结论的完整推理在其来源章节。",
         "> 级别：`A` = 有指令/字节证据；推断在正文里标 `INFERRED`；未闭合进 `08-open-items.md`。",
         "", "| id | 结论（摘要） | 来源 |", "|---|---|---|"]
for aid in order:
    src, text = items[aid]
    lines.append("| `%s` | %s | `%s` |" % (aid, text, src))
lines += ["", "合计 %d 条。" % len(order), ""]
open(os.path.join(ROOT, "analysis/A-conclusions.md"), "w", encoding="utf-8").write("\n".join(lines))
print("conclusions:", len(order))
