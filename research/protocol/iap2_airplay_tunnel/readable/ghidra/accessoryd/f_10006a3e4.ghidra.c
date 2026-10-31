/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10006a3e4
 * original code SHA256: f59443759e4dfebad8f79b4d8d98c73a6a3c071aa12b9bb5913c32367edda627
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_features_registerIdentificationParamHandlers(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  long lVar4;
  undefined *puVar5;
  ulong uVar6;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined2 local_70 [8];
  
  if ((_iap2_features_registerIdentificationParamHandlers_handlersRegistered & 1) == 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
      puVar3 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iap2_features_registerMessageHandlers_cold_6();
        puVar3 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar3 = *(undefined **)(_gLogObjects + 0xa8);
    }
    iVar2 = _os_log_type_enabled(puVar3,1);
    if (iVar2 != 0) {
      local_70[0] = 0;
      __os_log_impl(0x100000000,puVar3,1,"Registering identification param handlers...",local_70,2);
    }
    puVar3 = PTR___os_log_default_10022bbb0;
    lVar4 = 0;
    do {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
        puVar5 = puVar3;
        if (_logObjectForModule_onceToken != -1) {
          _iap2_features_registerIdentificationParamHandlers_cold_2();
        }
      }
      else {
        puVar5 = *(undefined **)(_gLogObjects + 0xa8);
      }
      iVar2 = _os_log_type_enabled(puVar5,2);
      if (iVar2 != 0) {
        _iap2_features_registerIdentificationParamHandlers_cold_3
                  (local_70,lVar4,(ulong)local_70 | 4,puVar5);
      }
      puVar5 = (&PTR__kiAP2FeatureInfo_AccAuthentication_10021b558)[lVar4 * 2];
      if (puVar5 == (undefined *)0x0) {
        _iap2_features_registerIdentificationParamHandlers_cold_5
                  (auStack_80,&__kiAP2FeatureInfoEntries + lVar4 * 4,(ulong)auStack_80 | 4);
      }
      else if (*(long *)(puVar5 + 0x18) == 0) {
        _iap2_features_registerIdentificationParamHandlers_cold_4
                  (auStack_90,&__kiAP2FeatureInfoEntries + lVar4 * 4,(ulong)auStack_90 | 4);
      }
      else if (*(short *)(puVar5 + 0x20) != 0) {
        uVar6 = 0;
        do {
          puVar1 = (undefined4 *)(*(long *)(puVar5 + 0x18) + uVar6 * 0x18);
          _iap2_identification_setParamHandler(*puVar1,*(undefined8 *)(puVar1 + 2));
          if (*(char *)(puVar1 + 4) == '\x01') {
            _iap2_identification_setRequiredIdentificationParam(*puVar1);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(ushort *)(puVar5 + 0x20));
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 != 0x1d);
    _iap2_features_registerIdentificationParamHandlers_handlersRegistered = 1;
  }
  else {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
      puVar3 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iap2_features_registerMessageHandlers_cold_6();
        puVar3 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar3 = *(undefined **)(_gLogObjects + 0xa8);
    }
    iVar2 = _os_log_type_enabled(puVar3,2);
    if (iVar2 != 0) {
      _iap2_features_registerIdentificationParamHandlers_cold_7(puVar3);
    }
  }
  return 1;
}

