/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100085034
 * original code SHA256: 54ad8930aaf0075cac02ee2c0e71eaff02efbcbf19727c32b6cad7716b3b1e33
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

int __mfi4Auth_relay_handle_AccessoryInformationUpdate(undefined8 *param_1,long param_2)

{
  char *pcVar1;
  int iVar2;
  ID self;
  ID IVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  char *pcVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined *puVar10;
  uint uVar11;
  char *pcVar12;
  char *pcVar13;
  char *pcVar14;
  char *pcVar15;
  char *pcVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;
  char *local_88;
  uint local_80;
  char *local_7c;
  undefined2 local_74;
  uint local_72;
  byte local_65;
  int local_64;
  
  local_64 = 1;
  local_65 = 0;
  self = _objc_alloc_init(PTR__OBJC_CLASS___NSMutableDictionary_10022bc70);
  if (param_1 == (undefined8 *)0x0) {
    IVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)IVar3 != 0) {
      IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_11();
    }
  }
  else if (*(char *)((long)param_1 + 0x1e) == '\x01') {
    IVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)IVar3 != 0) {
      IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_10();
    }
  }
  else if (param_2 == 0) {
    IVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)IVar3 != 0) {
      IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_9();
    }
  }
  else {
    iVar2 = _iAP2MsgGetMsgID(param_2);
    if (iVar2 == 0x5503) {
      local_64 = 0x5e;
      IVar3 = _iAP2MsgGetFirstParam(param_2,0);
      uVar9 = DAT_1001b3098;
      local_88 = (char *)0x0;
      pcVar12 = (char *)0x0;
      pcVar17 = (char *)0x0;
      pcVar13 = (char *)0x0;
      pcVar15 = (char *)0x0;
      pcVar18 = (char *)0x0;
      do {
        if (IVar3 == 0) {
          IVar3 = 0;
          if (pcVar18 != (char *)0x0) {
            uVar9 = 0;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar9 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,uVar9,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = pcVar18;
              __os_log_impl(0x100000000,uVar9,0,"vendor nameString %@",&local_80,0xc);
            }
            IVar3 = NSMutableDictionary::setObject_forKey_
                              (self,pcVar18,*(undefined8 *)PTR__kACCInfo_Name_10022b5b8);
          }
          if (pcVar17 != (char *)0x0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = pcVar17;
              __os_log_impl(0x100000000,IVar3,0,"modelIdentifierString %@",&local_80,0xc);
            }
            IVar3 = NSMutableDictionary::setObject_forKey_
                              (self,pcVar17,*(undefined8 *)PTR__kACCInfo_Model_10022b5b0);
          }
          if (pcVar15 != (char *)0x0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = pcVar15;
              __os_log_impl(0x100000000,IVar3,0,"manufacturerString %@",&local_80,0xc);
            }
            IVar3 = NSMutableDictionary::setObject_forKey_
                              (self,pcVar15,*(undefined8 *)PTR__kACCInfo_Manufacturer_10022b5a8);
          }
          if (pcVar13 != (char *)0x0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = pcVar13;
              __os_log_impl(0x100000000,IVar3,0,"serialNumberString %@",&local_80,0xc);
            }
            IVar3 = NSMutableDictionary::setObject_forKey_
                              (self,pcVar13,*(undefined8 *)PTR__kACCInfo_SerialNumber_10022b5c8);
          }
          if (pcVar12 != (char *)0x0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = pcVar12;
              __os_log_impl(0x100000000,IVar3,0,"firmwareVersionString %@",&local_80,0xc);
            }
            IVar3 = NSMutableDictionary::setObject_forKey_
                              (self,pcVar12,
                               *(undefined8 *)PTR__kACCInfo_FirmwareVersionActive_10022b590);
          }
          if (local_88 == (char *)0x0) {
            if ((((pcVar12 != (char *)0x0) || (pcVar13 != (char *)0x0)) || (pcVar15 != (char *)0x0))
               || ((pcVar17 != (char *)0x0 || (pcVar18 != (char *)0x0)))) goto LAB_100085838;
          }
          else {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar10 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
                puVar10 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
            if (iVar2 != 0) {
              local_80 = (uint)DAT_1001b3088;
              local_7c = local_88;
              __os_log_impl(0x100000000,IVar3,0,"hardwareVersionString %@",&local_80,0xc);
            }
            NSMutableDictionary::setObject_forKey_
                      (self,local_88,*(undefined8 *)PTR__kACCInfo_HardwareVersion_10022b5a0);
LAB_100085838:
            lVar6 = param_1[0x29];
            IVar3 = 0;
            if (lVar6 != 0) {
              IVar3 = (**(code **)(lVar6 + 0x10))(lVar6,*param_1,self);
            }
          }
          local_64 = 0;
          break;
        }
        uVar4 = _iAP2MsgGetParamID(IVar3);
        uVar8 = uVar4;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar10 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar8 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
            puVar10 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        uVar5 = _os_log_type_enabled(puVar10,uVar8,0);
        uVar11 = (uint)uVar4;
        if ((uVar5 & 1) != 0) {
          local_7c = "_mfi4Auth_relay_handle_AccessoryInformationUpdate";
          local_74 = 0x400;
          local_80 = (uint)uVar9;
          local_72 = uVar11;
          __os_log_impl(0x100000000,uVar8,0,"%s: paramID: %d",&local_80,0x12);
        }
        pcVar14 = pcVar13;
        pcVar16 = pcVar15;
        pcVar19 = pcVar18;
        pcVar1 = local_88;
        if (uVar11 < 6) {
          uVar5 = _iAP2MsgGetParamValueLen(IVar3);
          lVar6 = _iAP2MsgGetDataAsString(IVar3,&local_64);
          if (local_64 == 0) {
            if (*(char *)(lVar6 + ((uVar5 & 0xffffffff) - 1)) == '\0') {
              pcVar7 = (char *)NSString::stringWithUTF8String_
                                         ((ID)PTR__OBJC_CLASS___NSString_10022bb48,lVar6);
              if ((int)uVar11 < 3) {
                pcVar19 = pcVar7;
                if ((uVar11 != 0) && (pcVar16 = pcVar7, pcVar19 = pcVar18, uVar11 == 1)) {
                  pcVar16 = pcVar15;
                  pcVar17 = pcVar7;
                }
              }
              else {
                pcVar14 = pcVar7;
                if ((uVar11 != 3) && (pcVar14 = pcVar13, pcVar1 = pcVar7, uVar11 == 4)) {
                  pcVar12 = pcVar7;
                  pcVar1 = local_88;
                }
              }
            }
            else {
              iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
              if (iVar2 != 0) {
                local_7c = "_mfi4Auth_relay_handle_AccessoryInformationUpdate";
                local_74 = 0x400;
                local_80 = (uint)uVar9;
                local_72 = uVar11;
                __os_log_error_impl(0x100000000,PTR___os_log_default_10022bbb0,0x10,
                                    "%s: string parameter not NUL terminated! (paramID %d)",
                                    &local_80,0x12);
              }
            }
          }
        }
        else if (uVar11 == 0xf2) {
          _iAP2MsgGetDataAsU64(IVar3,&local_64);
        }
        local_88 = pcVar1;
        IVar3 = _iAP2MsgGetNextParamWithError(param_2,0,IVar3,&local_65);
        pcVar13 = pcVar14;
        pcVar15 = pcVar16;
        pcVar18 = pcVar19;
      } while ((local_65 & 1) == 0);
    }
    else {
      IVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if ((int)IVar3 != 0) {
        IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_1();
      }
    }
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar10 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      IVar3 = __mfi4Auth_relay_handle_AccessoryInformationUpdate_cold_3();
      puVar10 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar10 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar2 = _os_log_type_enabled(puVar10,IVar3,0);
  if (iVar2 != 0) {
    local_80 = local_80 & 0xffff0000;
    __os_log_impl(0x100000000,IVar3,0,"_mfi4Auth_relay_handle_AccessoryInformationUpdate: finish",
                  &local_80,2);
  }
  return local_64;
}

