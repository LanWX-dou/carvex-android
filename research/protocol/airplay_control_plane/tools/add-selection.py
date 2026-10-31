# -*- coding: utf-8 -*-
"""Idempotently add batch-2 functions to source/metadata/<img>/selection.json.

Run after tools/make-selection.py (which resets the base list):
    python3 tools/make-selection.py && python3 tools/add-selection.py
"""
import json, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

EXTRA = {
    "AirPlaySender": [
        ("_apsession_setupStreamCreatingResponseInternal", "SETUP", "SETUP response / streams[].type"),
        ("_endpoint_setupStreams", "SETUP", "endpoint-side stream setup"),
        ("_APSenderSessionCreateTransportStreamWithID", "SETUP", "stream creation (sender side)"),
        ("_apsession_CreateTransportStream", "SETUP", "stream creation (session side)"),
        ("_sdpsession_setupStreamCreatingResponseInternal", "SETUP", "SDP variant of SETUP response"),
    ],
    "CoreUtils": [
        ("_NetTransportChaCha20Poly1305Configure", "CRYPTO", "AEAD framing configuration"),
        ("_CryptoAEADEncryptMessage", "CRYPTO", "AEAD encrypt entry"),
        ("_ChaCha20Poly1305Initialize", "CRYPTO", "AEAD init"),
        ("_NetTransportWriteV", "CRYPTO", "transport write path"),
        ("_NetTransportRead", "CRYPTO", "transport read path (record framing)"),
    ],
    "APTransport": [
        ("_httpconnection_handleConnectionEstablished", "TRANSPORT", "post-connect state"),
        ("_httpconnection_SendPackage", "TRANSPORT", "public send entry"),
    ],
}

for img, items in EXTRA.items():
    p = os.path.join(ROOT, "source", "metadata", img, "selection.json")
    d = json.load(open(p, encoding="utf-8"))
    have = {f["symbol"] for f in d["functions"]}
    for sym, group, note in items:
        if sym not in have:
            d["functions"].append({"symbol": sym, "group": group, "note": note})
    json.dump(d, open(p, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
    print(img, len(d["functions"]))
