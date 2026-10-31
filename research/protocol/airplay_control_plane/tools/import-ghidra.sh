#!/bin/bash
# Import the three AirPlay images into one Ghidra project, then stop.
# Run inside WSL as root (same ownership model as the iap2-link project).
set -u
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../../.." && pwd)"
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
export PATH="$JAVA_HOME/bin:$PATH"
HEADLESS="$ROOT/firmware/tools/ghidra/support/analyzeHeadless"
PROJ="$ROOT/firmware/analysis/24A446/airplay-control/project"
SRC="$ROOT/research/protocol/airplay_control_plane/source/firmware"
LOG="$ROOT/firmware/analysis/24A446/airplay-control"
mkdir -p "$LOG" "$PROJ"
for img in CoreUtils APTransport AirPlaySender; do
  echo "=== import $img $(date -Is)"
  "$HEADLESS" "$PROJ" airplay -import "$SRC/$img" \
      -max-cpu 4 -analysisTimeoutPerFile 5400 \
      >> "$LOG/ghidra-import-$img.log" 2>&1
  echo "=== done $img rc=$? $(date -Is)"
done
