/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002e730
 * original code SHA256: fcd19f803b749d86808e00ec8d1884e09a37411b7ba9048d96ce7d971a6e32f3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ___iap2_deviceAuthentication_RequestDeviceChallengeResponse_block_invoke(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  long lVar6;
  undefined4 local_60;
  uint local_5c;
  undefined2 local_58;
  uint local_56;
  undefined2 local_52;
  long local_50;
  
  lVar6 = *(long *)(param_1 + 0x30);
  if (*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) == 0) {
    lVar3 = 0;
    lVar2 = 0;
    lVar4 = lVar6;
  }
  else {
    lVar2 = _CFDataGetBytePtr();
    lVar3 = _CFDataGetLength(*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18));
    lVar4 = *(long *)(param_1 + 0x30);
  }
  _iAP2MsgInit(lVar6 + 0x80,0xaa13,*(undefined8 *)(lVar4 + 200),0xffff,0,0);
  if ((lVar2 == 0) || (lVar3 == 0)) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x34)) {
      puVar5 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        ___iap2_deviceAuthentication_RequestDeviceCertificate_block_invoke_cold_1();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0x198);
    }
    iVar1 = _os_log_type_enabled(puVar5,0x10);
    if (iVar1 != 0) {
      local_56 = (uint)lVar2 & 0xffff;
      local_60 = (undefined4)DAT_1001b3100;
      local_5c = (uint)*(ushort *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18);
      local_58 = 0x400;
      local_52 = 0x800;
      local_50 = lVar3;
      __os_log_error_impl(0x100000000,puVar5,0x10,
                          "No device signature parameter due to pCFDataChallenge:%04X, pSignatureBytes:%04X, signatureLength:%02lX"
                          ,&local_60,0x18);
    }
  }
  else {
    _iAP2MsgAddDataParam(lVar6 + 0x80,0,0,lVar2,(uint)lVar3 & 0xffff);
  }
  _iap2_sessionControl_sendOutgoingMessage(*(undefined8 *)(param_1 + 0x30),lVar6 + 0x80);
  if (*(long *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18) != 0) {
    _CFRelease();
    *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18) = 0;
  }
  if (*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) != 0) {
    _CFRelease();
    *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) = 0;
  }
  return;
}

