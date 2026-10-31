# -*- coding: utf-8 -*-
"""Generate selection.json for the three AirPlay images (curated list)."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1] / "source/metadata"

SEL = {
    "CoreUtils": [
        ("HTTPMessageCreate", "HTTP", "HTTP message object creation"),
        ("HTTPMessageInitRequest", "HTTP", "request-line initialization (plain)"),
        ("HTTPHeader_InitRequestF", "HTTP", "request-line initialization with format"),
        ("HTTPHeader_InitRequest", "HTTP", "request-line initialization wrapper"),
        ("HTTPHeader_InitRequestV", "HTTP", "request-line formatting core"),
        ("HTTPHeader_SetField", "HTTP", "header field write"),
        ("HTTPHeader_Parse", "HTTP", "header field parse"),
        ("HTTPMessageReadMessageEx", "HTTP", "incremental RTSP/HTTP message reader"),
        ("HTTPMessageSetBody", "HTTP", "body attach; Content-Length source"),
        ("HTTPMessageGetHeaderField", "HTTP", "header lookup semantics"),
        ("HTTPMessageGetOrCopyFormVariable", "HTTP", "form/param variable extraction"),
        ("PairingSessionCreate", "PAIR", "pairing session factory (client/server, type)"),
        ("PairingSessionExchange", "PAIR", "TLV exchange -> HTTP request"),
        ("PairingSessionDeriveKey", "PAIR", "HKDF-based key derivation"),
        ("SetupClientExchange", "PAIR", "pair-setup client M1..M6"),
        ("VerifyClientExchange", "PAIR", "pair-verify client M1..M4"),
        ("SRPClientStart_libsrp", "PAIR", "SRP-6a client start"),
        ("SRPClientVerify_libsrp", "PAIR", "SRP-6a client proof check"),
        ("TLV8GetNext", "PAIR", "TLV8 iteration"),
        ("TLV8Get", "PAIR", "TLV8 single value"),
        ("TLV8GetBytes", "PAIR", "TLV8 value bytes"),
        ("TLV8BufferAppend", "PAIR", "TLV8 encode"),
        ("ChaCha20Poly1305EncryptMessage", "CRYPTO", "AEAD record encryption"),
        ("ChaCha20Poly1305DecryptMessage", "CRYPTO", "AEAD record decryption"),
        ("CryptoAEADCreate", "CRYPTO", "AEAD context"),
    ],
    "APTransport": [
        ("APTransportConnectionHTTPCreate", "TRANSPORT", "control channel connection factory"),
        ("httpconnection_connect", "TRANSPORT", "TCP connect path"),
        ("httpconnection_handleConnectionEstablished", "TRANSPORT", "post-connect state"),
        ("httpconnection_sendPackageInternal", "TRANSPORT", "request framing; CSeq"),
        ("httppackage_createWithHTTPMessage", "TRANSPORT", "HTTPMessage -> package"),
        ("APTransportPackageHTTPGetHTTPMessage", "TRANSPORT", "package -> HTTPMessage; type->method/URL"),
        ("APTransportPackageHTTPSetURL", "TRANSPORT", "URL/method set"),
        ("httppackage_matchIncomingMessageMethodAndURL", "TRANSPORT", "response correlation"),
        ("httpconnection_httpResponseReceived", "TRANSPORT", "response dispatch"),
        ("httpconnection_ConfigureEncryption", "TRANSPORT", "control channel encryption"),
        ("httpconnection_configureEncryptionInternal", "TRANSPORT", "encryption setup internals"),
        ("session_CreateStreamWithID", "TRANSPORT", "stream creation by ID"),
        ("APTransportStreamIDMake", "TRANSPORT", "stream ID construction"),
        ("APTransportStreamIDMakeWithPort", "TRANSPORT", "stream ID with port"),
        ("APTransportStreamIDGetStreamCategory", "TRANSPORT", "stream category accessor"),
    ],
    "AirPlaySender": [
        ("coreUtilsPairing_PerformSetup", "PAIR", "client pair-setup entry"),
        ("coreUtilsPairing_performSetupInternal", "PAIR", "pair-setup state machine"),
        ("coreUtilsPairing_sendPairingRequest", "PAIR", "pairing request transport"),
        ("coreUtilsPairing_PerformVerification", "PAIR", "client pair-verify entry"),
        ("coreUtilsPairing_DeriveKey", "PAIR", "session key derivation"),
        ("coreUtilsPairing_createAirPlayPairingSession", "PAIR", "session type/flags"),
        ("coreUtilsPairing_validateMFiCertificate", "PAIR", "certificate validation"),
        ("coreUtilsPairing_IsPeerKnown", "PAIR", "known-peer gate"),
        ("coreUtilsKeyHolder_CreateEncryptionKeysForContext", "CRYPTO", "control/event key contexts"),
        ("coreUtilsKeyHolder_CreateEncryptionKeysForStream", "CRYPTO", "per-stream keys"),
        ("apsession_EnsureStarted", "SESSION", "session start"),
        ("apsession_PerformStage1StartTransaction", "SESSION", "stage 1 (info/pairing)"),
        ("apsession_PerformStage2StartTransaction", "SESSION", "stage 2 (setup)"),
        ("apsession_CreateTransportStreamWithID", "SESSION", "stream creation by ID"),
        ("APSenderSessionCreateStreamDescriptor", "SESSION", "stream descriptor / type"),
    ],
}

for img, items in SEL.items():
    d = ROOT / img
    funcs = [{"symbol": s, "group": g, "note": n} for s, g, n in items]
    out = {"image": img, "functions": funcs}
    p = d / "selection.json"
    with p.open("w", encoding="utf-8") as handle:
        json.dump(out, handle, indent=1, ensure_ascii=False)
    print("wrote", p, len(funcs))
