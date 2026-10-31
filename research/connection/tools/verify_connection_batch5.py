"""Read-only phone/test snapshot verification; not a firmware or vehicle test."""
import hashlib
import json
from pathlib import Path
import xml.etree.ElementTree as ET

DOC = Path(__file__).resolve().parents[1]


def main():
    data = json.loads((DOC / "evidence/connection-mainline-batch5.json").read_text(encoding="utf-8"))
    totals = {}
    for item in data["source_snapshots"] + data["test_reports"]:
        raw = Path(item["path"]).read_bytes()
        if hashlib.sha256(raw).hexdigest() != item["sha256"]:
            raise SystemExit("FAIL: snapshot changed " + item["path"])
        if "suite" not in item:
            continue
        root = ET.fromstring(raw)
        for key in ("tests", "failures", "errors", "skipped"):
            if int(root.attrib[key]) != item[key]:
                raise SystemExit("FAIL: test count " + item["path"])
        if any(item[key] for key in ("failures", "errors", "skipped")):
            raise SystemExit("FAIL: non-passing suite " + item["suite"])
        totals[item["module"]] = totals.get(item["module"], 0) + item["tests"]
    if totals != {"protocol-carplay": 838, "core": 79}:
        raise SystemExit("FAIL: unexpected test totals " + repr(totals))
    print("PASS: 12 phone source snapshots, 126 JUnit reports; 917 tests, zero failures/errors/skips")
    print("LIMIT: source/report integrity only; no build execution or hardware acceptance")


if __name__ == "__main__":
    main()
