# 11 · 函数清单与覆盖

> 采样说明见 `00-method-and-environment.md`。`反编译` 列：`✓` 有 Ghidra 输出（未复核），`—` 仅汇编。

| 镜像 | 函数 | 地址 | 大小 (B) | 分组 | 反编译 |
|---|---|---|---|---|---|
| `AirPlaySender` | `coreUtilsPairing_PerformSetup` | `0x251aaf744` | 496 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_performSetupInternal` | `0x251b88c94` | 1444 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_sendPairingRequest` | `0x251b885ec` | 1704 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_PerformVerification` | `0x251b87acc` | 2848 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_DeriveKey` | `0x2519bd76c` | 148 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_createAirPlayPairingSession` | `0x251aaf934` | 636 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_validateMFiCertificate` | `0x251aafbb0` | 400 |  | ✓ |
| `AirPlaySender` | `coreUtilsPairing_IsPeerKnown` | `0x251b879e0` | 236 |  | ✓ |
| `AirPlaySender` | `coreUtilsKeyHolder_CreateEncryptionKeysForContext` | `0x251a358e4` | 764 |  | ✓ |
| `AirPlaySender` | `coreUtilsKeyHolder_CreateEncryptionKeysForStream` | `0x2519bfecc` | 252 |  | ✓ |
| `AirPlaySender` | `apsession_EnsureStarted` | `0x251a57ffc` | 80 |  | ✓ |
| `AirPlaySender` | `apsession_PerformStage1StartTransaction` | `0x251a587a0` | 188 |  | ✓ |
| `AirPlaySender` | `apsession_PerformStage2StartTransaction` | `0x251a5885c` | 100 |  | ✓ |
| `AirPlaySender` | `apsession_CreateTransportStreamWithID` | `0x2519c8f04` | 276 |  | ✓ |
| `AirPlaySender` | `APSenderSessionCreateStreamDescriptor` | `0x251ab1780` | 176 |  | ✓ |
| `AirPlaySender` | `apsession_setupStreamCreatingResponseInternal` | `0x2519bbf24` | 5764 |  | ✓ |
| `AirPlaySender` | `endpoint_setupStreams` | `0x251b371ac` | 3144 |  | ✓ |
| `AirPlaySender` | `APSenderSessionCreateTransportStreamWithID` | `0x251a52a68` | 180 |  | ✓ |
| `AirPlaySender` | `apsession_CreateTransportStream` | `0x251a58098` | 268 |  | ✓ |
| `AirPlaySender` | `sdpsession_setupStreamCreatingResponseInternal` | `0x251a9e5d0` | 1724 |  | ✓ |
| `APTransport` | `APTransportConnectionHTTPCreate` | `0x24fdc7034` | 1652 |  | ✓ |
| `APTransport` | `httpconnection_connect` | `0x24fe16938` | 956 |  | ✓ |
| `APTransport` | `httpconnection_handleConnectionEstablished` | `0x24fdc8e50` | 1392 |  | ✓ |
| `APTransport` | `httpconnection_sendPackageInternal` | `0x24fda5468` | 1156 |  | ✓ |
| `APTransport` | `httppackage_createWithHTTPMessage` | `0x24fda1e78` | 828 |  | ✓ |
| `APTransport` | `APTransportPackageHTTPGetHTTPMessage` | `0x24fda58ec` | 4000 |  | ✓ |
| `APTransport` | `APTransportPackageHTTPSetURL` | `0x24fda6c70` | 108 |  | ✓ |
| `APTransport` | `httppackage_matchIncomingMessageMethodAndURL` | `0x24fda25cc` | 188 |  | ✓ |
| `APTransport` | `httpconnection_httpResponseReceived` | `0x24fda4b28` | 1228 |  | ✓ |
| `APTransport` | `httpconnection_ConfigureEncryption` | `0x24fdc8688` | 176 |  | ✓ |
| `APTransport` | `httpconnection_configureEncryptionInternal` | `0x24fdc97e8` | 748 |  | ✓ |
| `APTransport` | `session_CreateStreamWithID` | `0x24fda858c` | 176 |  | ✓ |
| `APTransport` | `APTransportStreamIDMake` | `0x24fdfad5c` | 20 |  | ✓ |
| `APTransport` | `APTransportStreamIDMakeWithPort` | `0x24fdfad94` | 12 |  | ✓ |
| `APTransport` | `APTransportStreamIDGetStreamCategory` | `0x24fda863c` | 8 |  | ✓ |
| `APTransport` | `httpconnection_SendPackage` | `0x24fda2380` | 492 |  | ✓ |
| `CoreUtils` | `HTTPMessageCreate` | `0x18be4be58` | 176 |  | ✓ |
| `CoreUtils` | `HTTPMessageInitRequest` | `0x18bf0cc5c` | 48 |  | ✓ |
| `CoreUtils` | `HTTPHeader_InitRequestF` | `0x18be4dccc` | 44 |  | ✓ |
| `CoreUtils` | `HTTPHeader_InitRequestV` | `0x18be4dc0c` | 192 |  | ✓ |
| `CoreUtils` | `HTTPHeader_InitRequest` | `0x18be4dcf8` | 60 |  | ✓ |
| `CoreUtils` | `HTTPHeader_SetField` | `0x18be4d44c` | 44 |  | ✓ |
| `CoreUtils` | `HTTPHeader_Parse` | `0x18be4c4c8` | 1080 |  | ✓ |
| `CoreUtils` | `HTTPMessageReadMessageEx` | `0x18be49060` | 2312 |  | ✓ |
| `CoreUtils` | `HTTPMessageSetBody` | `0x18be4da90` | 196 |  | ✓ |
| `CoreUtils` | `HTTPMessageGetHeaderField` | `0x18be4c03c` | 36 |  | ✓ |
| `CoreUtils` | `HTTPMessageGetOrCopyFormVariable` | `0x18bf0d1d0` | 172 |  | ✓ |
| `CoreUtils` | `PairingSessionCreate` | `0x18bf220cc` | 408 |  | ✓ |
| `CoreUtils` | `PairingSessionExchange` | `0x18bf23048` | 7504 |  | ✓ |
| `CoreUtils` | `PairingSessionDeriveKey` | `0x18be5021c` | 272 |  | ✓ |
| `CoreUtils` | `SetupClientExchange` | `0x18bf24d98` | 8548 |  | ✓ |
| `CoreUtils` | `VerifyClientExchange` | `0x18bf29408` | 4280 |  | ✓ |
| `CoreUtils` | `SRPClientStart_libsrp` | `0x18bf36d10` | 592 |  | ✓ |
| `CoreUtils` | `SRPClientVerify_libsrp` | `0x18bf36f60` | 112 |  | ✓ |
| `CoreUtils` | `TLV8GetNext` | `0x18bf41440` | 100 |  | ✓ |
| `CoreUtils` | `TLV8Get` | `0x18bf413cc` | 116 |  | ✓ |
| `CoreUtils` | `TLV8GetBytes` | `0x18bf414a4` | 332 |  | ✓ |
| `CoreUtils` | `TLV8BufferAppend` | `0x18bf41b64` | 404 |  | ✓ |
| `CoreUtils` | `ChaCha20Poly1305EncryptMessage` | `0x18be560fc` | 84 |  | ✓ |
| `CoreUtils` | `ChaCha20Poly1305DecryptMessage` | `0x18be5a694` | 52 |  | ✓ |
| `CoreUtils` | `CryptoAEADCreate` | `0x18be7bb64` | 296 |  | ✓ |
| `CoreUtils` | `NetTransportChaCha20Poly1305Configure` | `0x18bf1adbc` | 272 |  | ✓ |
| `CoreUtils` | `CryptoAEADEncryptMessage` | `0x18be7bc8c` | 12 |  | ✓ |
| `CoreUtils` | `ChaCha20Poly1305Initialize` | `0x18be7c3f8` | 40 |  | ✓ |
| `CoreUtils` | `NetTransportWriteV` | `0x18be4d5fc` | 692 |  | ✓ |
| `CoreUtils` | `NetTransportRead` | `0x18be49968` | 848 |  | ✓ |

合计 66 个函数（AirPlaySender 20 / APTransport 16 / CoreUtils 30）。
