/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013e788
 * original code SHA256: c8b5db11aed052287434f32bd7abac90b9385bb81059f8b72a745d26e3f2a613
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_features_createFeature(long param_1,uint param_2)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  undefined1 uVar4;
  int iVar5;
  undefined8 uVar6;
  long lVar7;
  undefined *puVar8;
  undefined8 uVar9;
  char *pcVar10;
  long extraout_x8;
  long extraout_x9;
  long extraout_x11;
  uint extraout_w12;
  undefined8 unaff_x21;
  long *plVar11;
  undefined4 local_50;
  uint local_4c;
  
  _OUTLINED_FUNCTION_13();
  while( true ) {
    _OUTLINED_FUNCTION_6();
    plVar11 = *(long **)(extraout_x11 + 8);
    bVar3 = extraout_w12 != param_2;
    cVar2 = '\0';
    uVar4 = bVar3 || plVar11 == (long *)0x0;
    cVar1 = !bVar3 && (long)plVar11 < 0;
    if ((!bVar3 && plVar11 != (long *)0x0) && (*plVar11 != 0)) break;
    if (extraout_x9 == 1) {
      return 0;
    }
  }
  if ((param_1 == 0) || (*(long *)(param_1 + 0xd0 + (ulong)param_2 * 8) == 0)) {
    uVar4 = _gLogObjects != 0 && _gNumLogObjects == 0x16;
    if (_gLogObjects != 0 && 0x15 < _gNumLogObjects) {
      unaff_x21 = *(undefined8 *)(_gLogObjects + 0xa8);
    }
    else {
      _OUTLINED_FUNCTION_1();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar5 = _os_log_type_enabled(unaff_x21,1);
    if (iVar5 != 0) {
      local_50 = (undefined4)DAT_1001b30b0;
      local_4c = param_2;
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_10();
      __os_log_impl();
    }
    if (*(code **)*plVar11 != (code *)0x0) {
      lVar7 = (**(code **)*plVar11)(param_1);
      if (lVar7 != 0) {
        if (param_1 == 0) {
          return 0;
        }
        *(long *)(param_1 + 0xd0 + (ulong)param_2 * 8) = lVar7;
        return 0;
      }
      if ((_gLogObjects == 0) || (uVar4 = _gNumLogObjects == 0x16, _gNumLogObjects < 0x16)) {
        _OUTLINED_FUNCTION_1();
        puVar8 = PTR___os_log_default_10022bbb0;
        if (!(bool)uVar4) {
          _OUTLINED_FUNCTION_2();
          _dispatch_once();
          puVar8 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar8 = *(undefined **)(_gLogObjects + 0xa8);
      }
      iVar5 = _os_log_type_enabled(puVar8,0x10);
      if (iVar5 == 0) {
        return 0;
      }
      local_50 = (undefined4)DAT_1001b30b0;
      local_4c = param_2;
      uVar6 = _OUTLINED_FUNCTION_6();
      __os_log_error_impl(uVar6,puVar8,0x10,"Error creating feature: %{coreacc:iAP2Feature_t}d!",
                          &local_50,8);
      return 0;
    }
    if ((_gLogObjects == 0) || (uVar4 = _gNumLogObjects == 0x16, _gNumLogObjects < 0x16)) {
      _OUTLINED_FUNCTION_1();
      puVar8 = PTR___os_log_default_10022bbb0;
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(_gLogObjects + 0xa8);
    }
    iVar5 = _os_log_type_enabled(puVar8,0);
    if (iVar5 == 0) {
      return 0;
    }
    local_50 = (undefined4)DAT_1001b30b0;
    local_4c = param_2;
    uVar6 = _OUTLINED_FUNCTION_6();
    pcVar10 = "No create function for feature: %{coreacc:iAP2Feature_t}d!";
    uVar9 = 0;
  }
  else {
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar1 != cVar2)) {
      _OUTLINED_FUNCTION_1();
      puVar8 = PTR___os_log_default_10022bbb0;
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(extraout_x8 + 0xa8);
    }
    iVar5 = _os_log_type_enabled(puVar8,1);
    if (iVar5 == 0) {
      return 0;
    }
    local_50 = (undefined4)DAT_1001b30b0;
    local_4c = param_2;
    uVar6 = _OUTLINED_FUNCTION_6();
    pcVar10 = "Feature already created: %{coreacc:iAP2Feature_t}d!";
    uVar9 = 1;
  }
  __os_log_impl(uVar6,puVar8,uVar9,pcVar10,&local_50,8);
  return 0;
}

