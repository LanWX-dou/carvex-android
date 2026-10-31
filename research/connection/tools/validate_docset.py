"""Read-only integrity checks for this documentation directory.

This validates file/JSON/link integrity only. It does not validate protocol
claims, firmware semantics, cryptography, interoperability, or video display.
It never rewrites files.
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    errors: list[str] = []
    json_count = 0
    markdown_count = 0
    for path in sorted(ROOT.rglob("*")):
        if not path.is_file():
            continue
        if path.suffix.lower() == ".json":
            json_count += 1
            try:
                json.loads(path.read_text(encoding="utf-8"))
            except Exception as exc:  # pragma: no cover - diagnostics path
                errors.append(f"invalid JSON: {path}: {exc}")
        elif path.suffix.lower() == ".md":
            markdown_count += 1
            text = path.read_text(encoding="utf-8")
            for match in re.finditer(r"\[[^\]]+\]\(([^)]+)\)", text):
                target = match.group(1).split("#", 1)[0]
                if not target or target.startswith(("http://", "https://", "mailto:")):
                    continue
                # Absolute external/local evidence paths are intentionally not
                # required to exist on another machine; relative doc links are.
                if ":" in target[:3] or target.startswith("/"):
                    continue
                if not (path.parent / target).exists():
                    errors.append(f"broken relative link: {path}: {target}")
    required = [
        ROOT / "README.md",
        ROOT / "00-baseline.md",
        ROOT / "01-connection-map.md",
        ROOT / "05-existing-runtime-observations.md",
        ROOT / "10-bluetooth-iap2-network.md",
        ROOT / "11-iap2-state-machine.md",
        ROOT / "12-identification-contract.md",
        ROOT / "15-identification-power-transport-branches.md",
        ROOT / "16-identification-lifecycle-branches.md",
        ROOT / "17-identification-feature-message-branches.md",
        ROOT / "18-identification-core-field-branches.md",
        ROOT / "14-iap2-version-capability-audit.md",
        ROOT / "20-airplay-session.md",
        ROOT / "21-endpoint-fusion.md",
        ROOT / "22-control-wire-contract.md",
        ROOT / "23-airplay-version-capability-audit.md",
        ROOT / "24-disconnect-reconnect.md",
        ROOT / "30-video-first-frame.md",
        ROOT / "31-video-codec-contract.md",
        ROOT / "40-failure-localization.md",
        ROOT / "50-test-matrix.md",
        ROOT / "60-implementation-differences.md",
        ROOT / "62-version-capability-audit.md",
        ROOT / "63-alignment-batch1.md",
        ROOT / "64-identification-deep-review.md",
        ROOT / "65-identification-lifecycle-batch2.md",
        ROOT / "66-identification-core-batch3.md",
        ROOT / "19-identification-power-provider-context.md",
        ROOT / "70-message-index.md",
        ROOT / "90-open-items.md",
        ROOT / "evidence" / "README.md",
        ROOT / "evidence" / "baseline.json",
        ROOT / "evidence" / "capture-observations.json",
        ROOT / "evidence" / "runtime-log-observations.json",
        ROOT / "evidence" / "bootstrap-evidence.json",
        ROOT / "evidence" / "iap2-state-evidence.json",
        ROOT / "evidence" / "identification-contract-evidence.json",
        ROOT / "evidence" / "identification-power-transport-evidence.json",
        ROOT / "evidence" / "identification-core-branches.json",
        ROOT / "evidence" / "identification-lifecycle-batch2.json",
        ROOT / "evidence" / "identification-core-batch3.json",
        ROOT / "evidence" / "identification-power-provider-context.json",
        ROOT / "evidence" / "identification-lifecycle-branches.json",
        ROOT / "evidence" / "identification-feature-message-evidence.json",
        ROOT / "evidence" / "airplay-evidence.json",
        ROOT / "evidence" / "endpoint-fusion-evidence.json",
        ROOT / "evidence" / "video-evidence.json",
        ROOT / "evidence" / "control-response-keys.json",
        ROOT / "evidence" / "control-wire-evidence.json",
        ROOT / "evidence" / "disconnect-evidence.json",
        ROOT / "evidence" / "video-codec-evidence.json",
        ROOT / "evidence" / "version-header-evidence.json",
        ROOT / "evidence" / "iap2-version-capability-evidence.json",
        ROOT / "evidence" / "airplay-version-capability-evidence.json",
        ROOT / "evidence" / "build-profile-audit.json",
    ]
    errors.extend(f"missing required document/evidence: {path}" for path in required if not path.exists())
    if errors:
        for error in errors:
            print(f"ERROR {error}")
        return 1
    print(f"OK markdown={markdown_count} json={json_count} root={ROOT}")
    print("LIMIT: integrity only; no protocol or real-headunit validation")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
