#!/bin/bash
# Decompile the selected functions of the three AirPlay images (Ghidra headless).
set -u
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../../.." && pwd)"
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
export PATH="$JAVA_HOME/bin:$PATH"
HEADLESS="$ROOT/firmware/tools/ghidra/support/analyzeHeadless"
PROJ="$ROOT/firmware/analysis/24A446/airplay-control/project"
DOC="$ROOT/research/protocol/airplay_control_plane"
for img in CoreUtils APTransport AirPlaySender; do
  echo "=== decompile $img $(date -Is)"
  "$HEADLESS" "$PROJ" airplay -process "$img" -noanalysis \
      -scriptPath "$ROOT/firmware/tools/ghidra-scripts" \
      -postScript ExportDecomp.java \
      "$DOC/source/metadata/$img/ghidra-request.json" \
      "$DOC/readable/ghidra/$img" 2>&1 | tail -40
done
