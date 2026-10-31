/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000468dc
 * original code SHA256: b968de982afd6ab95add487792c8d9441cde0ef8c466e4ac8f4956fdf1537c09
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */

void _mfi4Auth_protocol_handle_RequestAuthCert(long param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined *puVar8;
  byte bVar9;
  undefined8 uVar10;
  int iVar11;
  long lVar12;
  char local_95;
  int local_94;
  undefined1 *local_90;
  undefined8 uStack_88;
  undefined1 *local_80;
  undefined1 *puStack_78;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_10022bb80;
  local_94 = 1;
  local_95 = '\0';
  if (param_1 == 0) {
    _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_4();
LAB_100046c54:
    lVar12 = 0;
joined_r0x000100046c2c:
    if (local_94 == 0) goto LAB_100046bc4;
  }
  else {
    if (*(char *)(param_1 + 0x1e) == '\x01') {
      _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_3();
      goto LAB_100046c54;
    }
    if (param_2 == 0) {
      _mfi4Auth_protocol_handle_RequestAuthCert_cold_5();
      goto LAB_100046c54;
    }
    lVar2 = _iAP2MsgGetFirstParam(param_2,0);
    uVar7 = DAT_1001b3108;
    if (lVar2 == 0) {
      bVar9 = 0;
      lVar5 = 0;
    }
    else {
      bVar9 = 0;
      uVar10 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
      do {
        uVar3 = _iAP2MsgGetParamID(lVar2);
        uVar6 = uVar3;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar8 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar6 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
            puVar8 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar8 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar1 = _os_log_type_enabled(puVar8,uVar6,2);
        iVar11 = (int)uVar3;
        if (iVar1 != 0) {
          local_90 = (undefined1 *)CONCAT44(iVar11,(int)uVar7);
          uStack_88._0_6_ = CONCAT42(iVar11,0x400);
          __os_log_debug_impl(0x100000000,uVar6,2,"RequestAuthCert: paramId %d (0x%x)",&local_90,0xe
                             );
        }
        if (iVar11 == 1) {
          local_90 = (undefined1 *)0x0;
          uStack_88 = (undefined1 *)0x0;
          local_80 = (undefined1 *)((ulong)local_80 & 0xffffffff00000000);
          iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_94,&local_90,0x14);
          if (iVar1 == 0x14) {
            lVar12 = _SecCertificateCreateWithBytes
                               (uVar10,*(undefined8 *)(param_1 + 0x1f0),
                                *(undefined8 *)(param_1 + 0x1f8));
            if ((lVar12 != 0) && (lVar5 = _SecCertificateGetSubjectKeyID(lVar12), lVar5 != 0)) {
              puVar4 = (undefined8 *)_CFDataGetBytePtr();
              if ((local_90 == (undefined1 *)*puVar4 && uStack_88 == (undefined1 *)puVar4[1]) &&
                  ((ulong)local_80 & 0xffffffff) == (ulong)*(uint *)(puVar4 + 2)) {
                bVar9 = bVar9 | 2;
                goto LAB_100046aa4;
              }
              _mfi4Auth_protocol_handle_RequestAuthCert_cold_2(&local_94);
              goto joined_r0x000100046c2c;
            }
          }
          else {
LAB_100046c1c:
            lVar12 = 0;
          }
LAB_100046c20:
          local_94 = -1;
          goto joined_r0x000100046c2c;
        }
        if (iVar11 == 0) {
          uStack_88 = &DAT_aaaaaaaaaaaaaaaa;
          local_90 = &DAT_aaaaaaaaaaaaaaaa;
          puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
          local_80 = &DAT_aaaaaaaaaaaaaaaa;
          iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_94,&local_90,0x20);
          if ((iVar1 != 0x20) ||
             (((*(undefined1 **)(param_1 + 0x1bc) != local_90 ||
               *(undefined1 **)(param_1 + 0x1c4) != uStack_88) ||
              *(undefined1 **)(param_1 + 0x1cc) != local_80) ||
              *(undefined1 **)(param_1 + 0x1d4) != puStack_78)) goto LAB_100046c1c;
          lVar12 = 0;
          bVar9 = bVar9 | 1;
        }
        else {
          lVar12 = 0;
        }
LAB_100046aa4:
        lVar2 = _iAP2MsgGetNextParamWithError(param_2,0,lVar2,&local_95);
        if (local_95 == '\x01') goto LAB_100046c20;
        lVar5 = lVar2;
        if (lVar12 != 0) {
          lVar5 = _CFRelease(lVar12);
        }
      } while (lVar2 != 0);
    }
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
      puVar8 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        lVar5 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(_gLogObjects + 0x1d0);
    }
    iVar1 = _os_log_type_enabled(puVar8,lVar5,2);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_RequestAuthCert_cold_4(bVar9,lVar5);
    }
    if (0xfd < (byte)(bVar9 - 3)) {
      if (bVar9 == 1) {
        uVar7 = 6;
      }
      else {
        uVar7 = 4;
      }
      local_94 = _mfi4Auth_protocol_initMessage_AuthCert(param_1,param_3,uVar7);
      lVar12 = 0;
      goto joined_r0x000100046c2c;
    }
    lVar12 = 0;
    local_94 = -1;
  }
  _mfi4Auth_protocol_handle_AuthState(param_1,1);
LAB_100046bc4:
  if (lVar12 != 0) {
    _CFRelease(lVar12);
  }
  if (*(long *)PTR____stack_chk_guard_10022bb80 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(local_94);
  }
  return;
}

