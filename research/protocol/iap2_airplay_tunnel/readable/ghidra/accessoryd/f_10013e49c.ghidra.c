/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013e49c
 * original code SHA256: 0e48ff8a185e019490bd90f7fed483d9029d96ed34c448a0d1b41d182d6511d8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iap2_features_createFeatures
          (long param_1,uint param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  bool bVar4;
  undefined1 uVar5;
  int iVar6;
  long lVar7;
  undefined8 uVar8;
  char *pcVar9;
  uint uVar10;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long lVar11;
  long lVar12;
  undefined8 unaff_x24;
  long *plVar13;
  ulong uVar14;
  undefined1 auVar15 [16];
  
  bVar4 = _gLogObjects == 0;
  bVar1 = bVar4 || _gNumLogObjects == 0x15;
  if (param_2 == 0) {
    if (bVar4 || _gNumLogObjects < 0x16) {
      _OUTLINED_FUNCTION_1();
      if (!bVar1) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 == 0) goto LAB_10013e550;
    _OUTLINED_FUNCTION_6();
  }
  else {
    if (bVar4 || _gNumLogObjects < 0x16) {
      _OUTLINED_FUNCTION_1();
      if (!bVar1) {
        _OUTLINED_FUNCTION_2();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 == 0) goto LAB_10013e550;
    _OUTLINED_FUNCTION_6();
  }
  _OUTLINED_FUNCTION_14();
LAB_10013e550:
  lVar11 = 0;
  lVar12 = 0x1d;
  do {
    uVar14 = (ulong)(uint)(&__kiAP2FeatureInfoEntries)[lVar11 * 4];
    plVar13 = (long *)(&PTR__kiAP2FeatureInfo_AccAuthentication_10021b558)[lVar11 * 2];
    if ((plVar13 != (long *)0x0) && (*plVar13 != 0)) {
      uVar10 = (uint)*(byte *)((long)plVar13 + 0x22);
      cVar2 = SBORROW4(uVar10,param_2);
      cVar3 = (int)(uVar10 - param_2) < 0;
      uVar5 = uVar10 == param_2;
      if ((bool)uVar5) {
        if ((param_1 == 0) || (*(long *)(param_1 + 0xd0 + uVar14 * 8) == 0)) {
          if (((param_2 & 1) != 0) ||
             (iVar6 = _iap2_identification_isIdentifiedForFeature(param_1,uVar14), iVar6 != 0)) {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar3 != cVar2)) {
              _OUTLINED_FUNCTION_1();
              if (!(bool)uVar5) {
                _OUTLINED_FUNCTION_2();
                _dispatch_once();
              }
              _OUTLINED_FUNCTION_11();
            }
            else {
              unaff_x24 = *(undefined8 *)(extraout_x8_00 + 0xa8);
            }
            iVar6 = _os_log_type_enabled(unaff_x24,1);
            if (iVar6 != 0) {
              auVar15 = _OUTLINED_FUNCTION_3();
              __os_log_impl(auVar15._0_8_,auVar15._8_8_,1,
                            "Creating feature: %{coreacc:iAP2Feature_t}d...",param_5,8);
            }
            if (*(code **)*plVar13 == (code *)0x0) {
              if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar3 != cVar2)) {
                _OUTLINED_FUNCTION_1();
                if (!(bool)uVar5) {
                  _OUTLINED_FUNCTION_2();
                  _dispatch_once();
                }
                _OUTLINED_FUNCTION_11();
              }
              else {
                unaff_x24 = *(undefined8 *)(extraout_x8_01 + 0xa8);
              }
              iVar6 = _os_log_type_enabled(unaff_x24,0);
              if (iVar6 != 0) {
                auVar15 = _OUTLINED_FUNCTION_3();
                uVar8 = 0;
                pcVar9 = "No create function for feature: %{coreacc:iAP2Feature_t}d!";
                goto LAB_10013e610;
              }
            }
            else {
              lVar7 = (**(code **)*plVar13)(param_1);
              if (lVar7 == 0) {
                if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar3 != cVar2)) {
                  _OUTLINED_FUNCTION_1();
                  if (!(bool)uVar5) {
                    _OUTLINED_FUNCTION_2();
                    _dispatch_once();
                  }
                  _OUTLINED_FUNCTION_11();
                }
                else {
                  unaff_x24 = *(undefined8 *)(extraout_x8_02 + 0xa8);
                }
                iVar6 = _os_log_type_enabled(unaff_x24,0x10);
                if (iVar6 != 0) {
                  auVar15 = _OUTLINED_FUNCTION_3();
                  __os_log_error_impl(auVar15._0_8_,auVar15._8_8_,0x10,
                                      "Error creating feature: %{coreacc:iAP2Feature_t}d!",param_5,8
                                     );
                }
              }
              else if (param_1 != 0) {
                *(long *)(param_1 + 0xd0 + uVar14 * 8) = lVar7;
              }
            }
          }
        }
        else {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar3 != cVar2)) {
            _OUTLINED_FUNCTION_1();
            if (!(bool)uVar5) {
              _OUTLINED_FUNCTION_2();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_11();
          }
          else {
            unaff_x24 = *(undefined8 *)(extraout_x8 + 0xa8);
          }
          iVar6 = _os_log_type_enabled(unaff_x24,1);
          if (iVar6 != 0) {
            auVar15 = _OUTLINED_FUNCTION_3();
            uVar8 = 1;
            pcVar9 = "Feature already created: %{coreacc:iAP2Feature_t}d!";
LAB_10013e610:
            __os_log_impl(auVar15._0_8_,auVar15._8_8_,uVar8,pcVar9,param_5,8);
          }
        }
      }
    }
    lVar11 = lVar11 + 1;
    lVar12 = lVar12 + -1;
    if (lVar12 == 0) {
      return 0;
    }
  } while( true );
}

