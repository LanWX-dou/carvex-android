/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002e5b4
 * original code SHA256: 8d08b9e05e6d7b74173edcd3054fb31850cf9e192f5dd3a09083f7cb800d4920
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ___iap2_deviceAuthentication_RequestDeviceCertificate_block_invoke(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined *puVar6;
  long lVar7;
  undefined4 local_60;
  uint local_5c;
  undefined2 local_58;
  uint local_56;
  undefined2 local_52;
  long local_50;
  
  lVar2 = _platform_auth_createDeviceDataCertificate(2);
  lVar7 = *(long *)(param_1 + 0x20);
  if (lVar2 == 0) {
    lVar4 = 0;
    lVar3 = 0;
    lVar5 = lVar7;
  }
  else {
    lVar3 = _CFDataGetBytePtr(lVar2);
    lVar4 = _CFDataGetLength(lVar2);
    lVar5 = *(long *)(param_1 + 0x20);
  }
  _iAP2MsgInit(lVar7 + 0x80,0xaa11,*(undefined8 *)(lVar5 + 200),0xffff,0,0);
  if ((lVar3 == 0) || (lVar4 == 0)) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x34)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        ___iap2_deviceAuthentication_RequestDeviceCertificate_block_invoke_cold_1();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x198);
    }
    iVar1 = _os_log_type_enabled(puVar6,0x10);
    if (iVar1 != 0) {
      local_5c = (uint)lVar2 & 0xffff;
      local_56 = (uint)lVar3 & 0xffff;
      local_60 = (undefined4)DAT_1001b3100;
      local_58 = 0x400;
      local_52 = 0x800;
      local_50 = lVar4;
      __os_log_error_impl(0x100000000,puVar6,0x10,
                          "No device cert data parameter due to pCFDevCertData:%04X, pDevCertBytes:%04X, devCertLength:%02lX"
                          ,&local_60,0x18);
    }
  }
  else {
    _iAP2MsgAddDataParam(lVar7 + 0x80,0,0,lVar3,(uint)lVar4 & 0xffff);
  }
  _iap2_sessionControl_sendOutgoingMessage(*(undefined8 *)(param_1 + 0x20),lVar7 + 0x80);
  if (lVar2 != 0) {
    _CFRelease(lVar2);
  }
  return;
}

