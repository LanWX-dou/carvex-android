/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013ea10
 * original code SHA256: 0341417ad4b2e92c866a931667119128c57622169aa83d29b3f2cad9f2d7f8e7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_features_startFeaturesFromDevice(undefined8 param_1,uint param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  long *plVar6;
  code *pcVar7;
  long lVar8;
  long lVar9;
  undefined *puVar10;
  
  bVar2 = _gLogObjects == 0;
  bVar1 = bVar2 || _gNumLogObjects == 0x15;
  if (param_2 == 0) {
    if (bVar2 || _gNumLogObjects < 0x16) {
      _OUTLINED_FUNCTION_1();
      if (!bVar1) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar3 = _OUTLINED_FUNCTION_15();
    if (iVar3 == 0) goto LAB_10013eac4;
    _OUTLINED_FUNCTION_6();
  }
  else {
    if (bVar2 || _gNumLogObjects < 0x16) {
      _OUTLINED_FUNCTION_1();
      if (!bVar1) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar3 = _OUTLINED_FUNCTION_15();
    if (iVar3 == 0) goto LAB_10013eac4;
    _OUTLINED_FUNCTION_6();
  }
  _OUTLINED_FUNCTION_14();
LAB_10013eac4:
  lVar8 = 0;
  lVar9 = 0x1d;
  do {
    plVar6 = (long *)(&PTR__kiAP2FeatureInfo_AccAuthentication_10021b558)[lVar8 * 2];
    if (((plVar6 != (long *)0x0) && (lVar5 = *plVar6, lVar5 != 0)) &&
       (*(byte *)((long)plVar6 + 0x22) == param_2)) {
      if ((param_2 & 1) == 0) {
        iVar3 = _iap2_identification_isIdentifiedForFeature
                          (param_1,(&__kiAP2FeatureInfoEntries)[lVar8 * 4]);
        if (iVar3 == 0) goto LAB_10013ebf4;
        lVar5 = *plVar6;
      }
      pcVar7 = *(code **)(lVar5 + 0x10);
      bVar2 = _gLogObjects == 0;
      bVar1 = bVar2 || _gNumLogObjects == 0x15;
      if (pcVar7 == (code *)0x0) {
        if (bVar2 || _gNumLogObjects < 0x16) {
          _OUTLINED_FUNCTION_1();
          puVar10 = PTR___os_log_default_10022bbb0;
          if (!bVar1) {
            _OUTLINED_FUNCTION_2();
            _dispatch_once();
            puVar10 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar10 = *(undefined **)(_gLogObjects + 0xa8);
        }
        iVar3 = _os_log_type_enabled(puVar10,0);
        if (iVar3 != 0) {
          uVar4 = _OUTLINED_FUNCTION_6();
          __os_log_impl(uVar4,puVar10,0,
                        "No auto-start function for feature: %{coreacc:iAP2Feature_t}d!");
        }
      }
      else {
        if (bVar2 || _gNumLogObjects < 0x16) {
          _OUTLINED_FUNCTION_1();
          puVar10 = PTR___os_log_default_10022bbb0;
          if (!bVar1) {
            _OUTLINED_FUNCTION_2();
            _dispatch_once();
            puVar10 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar10 = *(undefined **)(_gLogObjects + 0xa8);
        }
        iVar3 = _os_log_type_enabled(puVar10,1);
        if (iVar3 != 0) {
          uVar4 = _OUTLINED_FUNCTION_6();
          __os_log_impl(uVar4,puVar10,1,"Auto-starting feature: %{coreacc:iAP2Feature_t}d...");
        }
        (*pcVar7)(param_1);
      }
    }
LAB_10013ebf4:
    lVar8 = lVar8 + 1;
    lVar9 = lVar9 + -1;
    if (lVar9 == 0) {
      return 0;
    }
  } while( true );
}

