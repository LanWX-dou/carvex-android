/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10006b878
 * original code SHA256: 567a323f0753af98181c92a6f7bc0a17d269b6a526a46c26a9a8be56320a463f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iap2_sessionRouter_processSessionData
          (undefined8 param_1,long param_2,ushort *param_3,ulong param_4)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined2 local_60 [8];
  
  if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
    puVar5 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _iap2_sessionRouter_processSessionData_cold_1();
      puVar5 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar5 = *(undefined **)(_gLogObjects + 0xa8);
  }
  iVar3 = _os_log_type_enabled(puVar5,2);
  if (iVar3 != 0) {
    _iap2_sessionRouter_processSessionData_cold_2(param_2,puVar5);
  }
  uVar6 = 0;
  bVar1 = *(byte *)(param_2 + 1);
  if (bVar1 < 2) {
    if (bVar1 == 0) {
      uVar6 = _iap2_sessionControl_parseIncomingMessage(param_1,param_3,param_4);
    }
    else if (bVar1 == 1) {
      uVar6 = _iap2_sessionFileTransfer_handleDatagram(param_1,param_3,param_4);
    }
  }
  else if (bVar1 == 2) {
    if ((uint)param_4 < 3) {
      if ((uint)param_4 == 2) {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x16)) {
          puVar5 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _iap2_sessionRouter_processSessionData_cold_3();
            puVar5 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar5 = *(undefined **)(_gLogObjects + 0xa8);
        }
        iVar3 = _os_log_type_enabled(puVar5,0);
        if (iVar3 != 0) {
          local_60[0] = 0;
          __os_log_impl(0x100000000,puVar5,0,"Received EA packet of 0 bytes, no data to process!",
                        local_60,2);
        }
        uVar6 = 1;
      }
      else {
        uVar6 = 0;
      }
    }
    else {
      uVar2 = *param_3;
      lVar4 = _CFDataCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,param_3 + 1,
                            (param_4 & 0xffffffff) - 2);
      uVar6 = _platform_externalAccessory_handleIncomingEADataFromAccessoryForSessionID
                        (uVar2 >> 8 | uVar2 << 8,lVar4);
      if (lVar4 != 0) {
        _CFRelease(lVar4);
      }
    }
  }
  else if (bVar1 == 4) {
    uVar6 = _iap2_sessionLog_parseIncomingMessage(param_1,param_3,param_4);
  }
  return uVar6;
}

