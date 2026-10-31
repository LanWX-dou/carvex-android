/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519bbf24
 * original code SHA256: 2474956bad6630ee63b02d72eb56748aa49531735f5e4f3772422c313bb6655c
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0002519bd0dc) */
/* WARNING: Removing unreachable block (ram,0x0002519bcd28) */
/* WARNING: Removing unreachable block (ram,0x0002519bcc48) */
/* WARNING: Removing unreachable block (ram,0x0002519bcb88) */
/* WARNING: Removing unreachable block (ram,0x0002519bcf40) */
/* WARNING: Removing unreachable block (ram,0x0002519bce74) */
/* WARNING: Removing unreachable block (ram,0x0002519bcffc) */
/* WARNING: Removing unreachable block (ram,0x0002519bcda8) */
/* WARNING: Removing unreachable block (ram,0x0002519bcddc) */
/* WARNING: Removing unreachable block (ram,0x0002519bcc14) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _apsession_setupStreamCreatingResponseInternal(ulong *param_1)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  undefined8 *puVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined8 uVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  char *pcVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 *puVar23;
  code *pcVar24;
  undefined8 uVar25;
  ulong uVar26;
  long local_100;
  ulong local_f0;
  uint local_e4;
  long local_e0;
  long local_d8;
  ulong local_d0;
  undefined8 local_c8;
  code *local_c0;
  undefined *puStack_b8;
  long *local_b0;
  int local_a8;
  long local_a0;
  long *local_98;
  undefined8 local_90;
  undefined8 local_88;
  ulong local_80 [4];
  
  local_80[2] = *_DAT_2681b4ee0;
  pcVar9 = (char *)func_0x00025810ac50(*param_1);
  if ((_gLogCategory_APSenderSessionAirPlay < 0x29) &&
     ((_gLogCategory_APSenderSessionAirPlay != -1 ||
      (iVar7 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x2000028), iVar7 != 0))))
  {
    _apsession_setupStreamCreatingResponseInternal_cold_1(param_1,pcVar9);
  }
  if (*pcVar9 != '\0') goto LAB_2519bd2bc;
  iVar7 = (int)param_1[1];
  uVar4 = iVar7 - 0x6f;
  if ((0x13 < uVar4 || (1 << (ulong)(uVar4 & 0x1f) & 0x80201U) == 0) &&
     (iVar7 = _apsession_registryContainsStream(*param_1,iVar7,0), iVar7 != 0)) goto LAB_2519bd2bc;
  local_d0 = *param_1;
  local_c8 = 0;
  uVar10 = _apsession_ensureStartedInternal(&local_d0);
  if ((int)uVar10 != 0) {
    func_0x000258109a30(uVar10,"apsession_setupStreamCreatingResponseInternal",0x1353,0);
    goto LAB_2519bd470;
  }
  uVar26 = *param_1;
  iVar7 = (int)param_1[1];
  uVar10 = param_1[2];
  puVar23 = (undefined8 *)param_1[3];
  local_e4 = 0;
  lVar11 = func_0x00025810ac50(uVar26);
  uVar21 = _kAPEndpointDescriptionProperty_SupportsCoreUtilsPairingAndEncryption;
  local_d8 = 0;
  local_80[0] = 0;
  local_80[1] = 0;
  lVar12 = func_0x000258109860(*(undefined8 *)(lVar11 + 0x30),
                               _kAPEndpointDescriptionProperty_SupportsCoreUtilsPairingAndEncryption
                               ,0);
  if ((_gLogCategory_APSenderSessionAirPlay < 0x1f) &&
     ((_gLogCategory_APSenderSessionAirPlay != -1 ||
      (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200001e), iVar8 != 0))))
  {
    _apsession_setupStreamCreatingResponseInternal_cold_2(uVar26);
  }
  iVar8 = _apsession_isCancelled(uVar26);
  if (iVar8 != 0) {
    _apsession_setupStreamCreatingResponseInternal_cold_3(&local_e4);
LAB_2519bd460:
    local_f0 = 0;
    goto LAB_2519bca50;
  }
  _apsession_copyTransportControlStream(uVar26,&local_e0);
  lVar19 = local_e0;
  local_e4 = 0;
  if (local_e0 == 0) {
    _apsession_setupStreamCreatingResponseInternal_cold_20(&local_e4);
    goto LAB_2519bd460;
  }
  uVar25 = *_DAT_2680d3150;
  lVar13 = func_0x000258101820(uVar25,0,_DAT_2680d3340,_DAT_2680d3358);
  if (lVar13 == 0) {
    _apsession_setupStreamCreatingResponseInternal_cold_19(&local_e4,lVar19);
    goto LAB_2519bd460;
  }
  if ((*(char *)(lVar11 + 0x81) == '\0') &&
     (local_e4 = _apsession_appendControlSetupRequest(uVar26,lVar13,0), local_e4 != 0)) {
    _apsession_setupStreamCreatingResponseInternal_cold_4();
LAB_2519bd524:
    local_f0 = 0;
    local_100 = lVar19;
    goto LAB_2519bca40;
  }
  local_100 = func_0x0002581017c0(uVar25,0,_DAT_2680d3338);
  if (local_100 == 0) {
    _apsession_setupStreamCreatingResponseInternal_cold_18(&local_e4);
    goto LAB_2519bd524;
  }
  if (uVar10 == 0) {
    lVar14 = func_0x000258101820(uVar25,0,_DAT_2680d3340,_DAT_2680d3358);
  }
  else {
    lVar14 = func_0x000258102650(uVar25,0,uVar10);
  }
  uVar25 = _kAPSenderSessionStreamKey_Type;
  if (lVar14 == 0) {
    _apsession_setupStreamCreatingResponseInternal_cold_17(&local_e4);
    local_f0 = 0;
    goto LAB_2519bca34;
  }
  func_0x00025810a790(lVar14,_kAPSenderSessionStreamKey_Type,iVar7);
  bVar5 = false;
  local_f0 = 0;
  uVar4 = iVar7 - 0x60;
  if (uVar4 < 0x10) {
    uVar3 = 1 << (ulong)(uVar4 & 0x1f);
    if ((uVar3 & 0xcf1) == 0) {
      if ((uVar3 & 0xc000) != 0) {
        func_0x00025810bd60(local_80);
        uVar10 = (local_80[0] & 0xff00ff00ff00ff00) >> 8 | (local_80[0] & 0xff00ff00ff00ff) << 8;
        uVar10 = (uVar10 & 0xffff0000ffff0000) >> 0x10 | (uVar10 & 0xffff0000ffff) << 0x10;
        local_f0 = uVar10 >> 0x20 | uVar10 << 0x20;
        func_0x00025810a790(lVar14,_kAPSenderSessionStreamKey_ConnectionID);
        if (*(int *)(lVar11 + 0xe0) == 5) {
          bVar5 = true;
        }
        else {
          lVar12 = func_0x00025810f7c0();
          bVar5 = false;
          if (lVar12 != 0) {
            func_0x0002580f7000(lVar14,&cfstringStruct_27612ff30,lVar12);
            func_0x0002580f5830(lVar12);
            bVar5 = false;
          }
        }
        if (((iVar7 == 0x6e) && (_gLogCategory_APSenderSessionAirPlay < 0x1f)) &&
           ((_gLogCategory_APSenderSessionAirPlay != -1 ||
            (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200001e),
            iVar8 != 0)))) {
          _apsession_setupStreamCreatingResponseInternal_cold_5(uVar26);
        }
      }
    }
    else {
      if (lVar12 == 0) {
        local_f0 = 0;
      }
      else {
        func_0x00025810bd60(local_80);
        uVar10 = (local_80[0] & 0xff00ff00ff00ff00) >> 8 | (local_80[0] & 0xff00ff00ff00ff) << 8;
        uVar10 = (uVar10 & 0xffff0000ffff0000) >> 0x10 | (uVar10 & 0xffff0000ffff) << 0x10;
        local_f0 = uVar10 >> 0x20 | uVar10 << 0x20;
        func_0x00025810a790(lVar14,_kAPSenderSessionStreamKey_ConnectionID);
      }
      bVar5 = false;
    }
  }
  func_0x0002581017b0(local_100,lVar14);
  func_0x0002580f7000(lVar13,&cfstringStruct_27612ff50,local_100);
  if ((_gLogCategory_APSenderSessionAirPlay < 0xb) &&
     ((_gLogCategory_APSenderSessionAirPlay != -1 ||
      (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200000a), iVar8 != 0))))
  {
    func_0x000258101eb0(&_gLogCategory_APSenderSessionAirPlay,
                        "OSStatus apsession_setupStreamsCreatingResponse(APSenderSessionRef, APStreamType, CFDictionaryRef, uint64_t *, int *, CFDictionaryRef *)"
                        ,0x200000a,"[%{ptr}] Setup request to %\'\'@: %@\n");
  }
  uVar22 = 0;
  uVar15 = *(undefined8 *)(lVar11 + 0x60);
  if (0x22 < uVar4) goto switchD_2519bc2a8_caseD_2;
  switch(uVar4) {
  default:
    uVar22 = 0xf000003;
    func_0x00025810d3e0(uVar15,0xf000002);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    break;
  case 1:
    func_0x00025810d3e0(uVar15,0xf000004);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000005;
    break;
  case 4:
    func_0x00025810d3e0(uVar15,0xf000006);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000007;
    break;
  case 5:
    func_0x00025810d3e0(uVar15,0xf00000c);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf00000d;
    break;
  case 6:
    func_0x00025810d3e0(uVar15,0xf00000a);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf00000b;
    break;
  case 7:
    func_0x00025810d3e0(uVar15,0xf000010);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000011;
    break;
  case 8:
    func_0x00025810d3e0(uVar15,0xf000008);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000009;
    break;
  case 9:
    func_0x00025810d3e0(uVar15,0xf00000e);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf00000f;
    break;
  case 10:
    func_0x00025810d3e0(uVar15,0xf000012);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000013;
    break;
  case 0xb:
    func_0x00025810d3e0(uVar15,0xf000016);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000017;
    break;
  case 0xc:
    func_0x00025810d3e0(uVar15,0xf000014);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000015;
    break;
  case 0xd:
    func_0x00025810d3e0(uVar15,0xf000018);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf000019;
    break;
  case 0xe:
  case 0xf:
    uVar22 = 0xf000000;
  case 2:
  case 3:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
switchD_2519bc2a8_caseD_2:
    func_0x00025810d3e0(uVar15,uVar22);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar22 = 0;
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    if (uVar4 < 0x23) {
      switch(uVar4) {
      default:
        uVar22 = 0xf000003;
        break;
      case 1:
        uVar22 = 0xf000005;
        break;
      case 2:
      case 3:
      case 0xd:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x20:
      case 0x21:
        break;
      case 4:
        uVar22 = 0xf000007;
        break;
      case 5:
        uVar22 = 0xf00000d;
        break;
      case 6:
        uVar22 = 0xf00000b;
        break;
      case 7:
        uVar22 = 0xf000011;
        break;
      case 8:
        uVar22 = 0xf000009;
        break;
      case 9:
        uVar22 = 0xf00000f;
        break;
      case 10:
        uVar22 = 0xf000013;
        break;
      case 0xb:
        uVar22 = 0xf000017;
        break;
      case 0xc:
        uVar22 = 0xf000015;
        break;
      case 0xe:
      case 0xf:
        uVar22 = 0xf000001;
        break;
      case 0x18:
        uVar22 = 0xf00001b;
        break;
      case 0x22:
        uVar22 = 0xf00001d;
      }
    }
    break;
  case 0x18:
    func_0x00025810d3e0(uVar15,0xf00001a);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf00001b;
    break;
  case 0x22:
    func_0x00025810d3e0(uVar15,0xf00001c);
    local_e4 = func_0x00025810e4e0(lVar19,0x73747570,lVar13,&local_d8);
    uVar15 = *(undefined8 *)(lVar11 + 0x60);
    uVar22 = 0xf00001d;
  }
  func_0x00025810d3e0(uVar15,uVar22);
  if (local_e4 == 0) {
    if ((_gLogCategory_APSenderSessionAirPlay < 0xb) &&
       ((_gLogCategory_APSenderSessionAirPlay != -1 ||
        (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200000a), iVar8 != 0)))
       ) {
      func_0x000258101eb0(&_gLogCategory_APSenderSessionAirPlay,
                          "OSStatus apsession_setupStreamsCreatingResponse(APSenderSessionRef, APStreamType, CFDictionaryRef, uint64_t *, int *, CFDictionaryRef *)"
                          ,0x200000a,"[%{ptr}] Setup response from %\'\'@: %@\n");
    }
    iVar8 = _apsession_isCancelled(uVar26);
    if (iVar8 != 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_7(&local_e4);
      goto LAB_2519bd4ec;
    }
    func_0x00025810a6f0(local_d8,&cfstringStruct_27612fa70,&local_e4);
    lVar12 = local_d8;
    local_e4 = 0;
    uVar15 = func_0x000258106470();
    uVar15 = func_0x00025810a710(lVar12,&cfstringStruct_27612ff50,uVar15,&local_e4);
    if (local_e4 != 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_8();
      goto LAB_2519bd4ec;
    }
    lVar12 = func_0x0002581017d0(uVar15);
    if (lVar12 != 1) {
      _apsession_setupStreamCreatingResponseInternal_cold_9();
      goto LAB_2519bd4ec;
    }
    uVar22 = func_0x000258102670();
    lVar12 = func_0x00025810a5c0(uVar15,0,uVar22,&local_e4);
    if (local_e4 != 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_10();
      goto LAB_2519bd4ec;
    }
    iVar8 = func_0x00025810a6f0(lVar12,uVar25,&local_e4);
    uVar15 = _kAPSenderSessionStreamKey_StreamID;
    if (local_e4 != 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_11(local_e4);
      goto LAB_2519bd4ec;
    }
    if (iVar7 != iVar8) {
      _apsession_setupStreamCreatingResponseInternal_cold_12();
      goto LAB_2519bd4ec;
    }
    lVar16 = func_0x00025810a6f0(lVar12,_kAPSenderSessionStreamKey_StreamID,&local_e4);
    if ((bVar5) && (local_e4 != 0)) {
      lVar16 = func_0x00025810ac50(uVar26);
      local_a0 = 0;
      local_90 = DAT_251c6aff0;
      local_88 = 0;
      local_98 = &local_a0;
      func_0x00025810b430(*(undefined8 *)(lVar16 + 200));
      local_d0 = _DAT_2681b4ed0;
      local_c8 = DAT_251c6aff8;
      local_c0 = ___apsession_generateUniqueStreamIDFromRegistry_block_invoke;
      puStack_b8 = &DAT_2693e5c30;
      local_b0 = &local_a0;
      local_a8 = iVar7;
      func_0x00025810b000(&local_c0,*(undefined8 *)(lVar16 + 0x278),&local_d0);
      func_0x00025810b440(*(undefined8 *)(lVar16 + 200));
      lVar16 = local_98[3];
      func_0x0002580f4ba0(&local_a0,8);
      if ((_gLogCategory_APSenderSessionAirPlay < 0x3d) &&
         ((_gLogCategory_APSenderSessionAirPlay != -1 ||
          (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200003c), iVar8 != 0)
          ))) {
        _apsession_setupStreamCreatingResponseInternal_cold_13(iVar7,uVar26,lVar16);
      }
    }
    local_e4 = 0;
    local_d0 = local_d0 & 0xffffffff00000000;
    lVar17 = func_0x00025810ac50(uVar26);
    if ((_gLogCategory_APSenderSessionAirPlay < 0x33) &&
       ((_gLogCategory_APSenderSessionAirPlay != -1 ||
        (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x2000032), iVar8 != 0)))
       ) {
      _apsession_setupStreamCreatingResponseInternal_cold_14(iVar7,uVar26,lVar16,local_f0);
    }
    lVar18 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
    if (lVar18 == 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_16();
    }
    else {
      func_0x00025810a790(lVar18,uVar25,iVar7);
      func_0x00025810a790(lVar18,uVar15,lVar16);
      func_0x00025810a790(lVar18,_kAPSenderSessionStreamKey_ConnectionID,local_f0);
      lVar16 = func_0x00025810aa80(&local_d0,"%lu-%llu");
      if ((int)local_d0 == 0) {
        func_0x00025810b430(*(undefined8 *)(lVar17 + 200));
        func_0x000258101810(*(undefined8 *)(lVar17 + 0x278),lVar16,lVar18);
        func_0x00025810b440(*(undefined8 *)(lVar17 + 200));
      }
      else {
        _apsession_setupStreamCreatingResponseInternal_cold_15();
      }
      func_0x0002580f5830(lVar18);
      if (lVar16 != 0) {
        func_0x0002580f5830(lVar16);
      }
    }
    if (iVar7 == 0x67) {
      func_0x00025810b430(*(undefined8 *)(lVar11 + 200));
      puVar6 = _DAT_2680fc070;
      if (*(long *)(lVar11 + 0xf8) != 0) {
        func_0x000258109dc0(*(long *)(lVar11 + 0xf8),*_DAT_2680fc070,0x78);
      }
      if (*(long *)(lVar11 + 0x100) != 0) {
        func_0x000258109dc0(*(long *)(lVar11 + 0x100),*puVar6,0x78);
      }
      func_0x00025810b440(*(undefined8 *)(lVar11 + 200));
    }
    *(undefined1 *)(lVar11 + 0x81) = 1;
    if (puVar23 != (undefined8 *)0x0) {
      if (lVar12 == 0) {
        uVar25 = 0;
      }
      else {
        uVar25 = func_0x0002580f6a60(lVar12);
      }
      *puVar23 = uVar25;
    }
  }
  else {
    _apsession_setupStreamCreatingResponseInternal_cold_6();
LAB_2519bd4ec:
    local_f0 = 0;
  }
  func_0x0002580f5830(lVar19);
  lVar19 = lVar14;
LAB_2519bca34:
  func_0x0002580f5830(lVar19);
LAB_2519bca40:
  func_0x0002580f5830(local_100);
  func_0x0002580f5830(lVar13);
LAB_2519bca50:
  if (local_d8 != 0) {
    func_0x0002580f5830();
  }
  uVar10 = (ulong)local_e4;
  if (local_e4 == 0) {
    uVar26 = *param_1;
    iVar7 = (int)param_1[1];
    plVar1 = (long *)param_1[4];
    plVar2 = (long *)param_1[5];
    lVar11 = func_0x00025810ac50(uVar26);
    local_d8 = 0;
    local_d0 = 0;
    local_a0 = 0;
    local_80[0] = 0;
    local_e0 = 0;
    lVar12 = func_0x000258109860(*(undefined8 *)(lVar11 + 0x30),uVar21,0);
    func_0x00025810b430(*(undefined8 *)(lVar11 + 200));
    if (*(long *)(lVar11 + 0x150) == 0) {
      lVar19 = 0;
    }
    else {
      lVar19 = func_0x0002580f6a60();
    }
    func_0x00025810b440(*(undefined8 *)(lVar11 + 200));
    if (((lVar12 == 0) && (*(char *)(lVar11 + 0x40) != '\0')) && (lVar19 == 0)) {
      if (plVar1 == (long *)0x0) {
LAB_2519bd148:
        uVar10 = 0;
      }
      else {
        uVar10 = 0;
        *plVar1 = 0;
      }
    }
    else if (lVar19 == 0) {
      _apsession_setupStreamCreatingResponseInternal_cold_33();
      uVar10 = 0xfffee773;
    }
    else {
      if (iVar7 < 0x6a) {
        if (iVar7 < 0x66) {
          if (iVar7 != 0x60) {
            if (iVar7 == 100) {
              if (lVar12 != 0) {
                lVar11 = func_0x000258109150(lVar19);
                puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
                pcVar24 = (code *)*puVar23;
                if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
                  uVar10 = 0xffffce12;
                }
                else {
                  uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,
                                      local_f0,0x20,&local_d0,0x20,&local_a0);
                  if ((int)uVar10 == 0) {
                    uVar21 = *_DAT_2680d3150;
                    uVar10 = func_0x000258109690(uVar21,local_a0,1,&local_d8);
                    if ((int)uVar10 == 0) {
                      uVar10 = func_0x000258109690(uVar21,local_d0,1,&local_e0);
                      if ((int)uVar10 == 0) goto LAB_2519bd120;
                      _apsession_setupStreamCreatingResponseInternal_cold_28();
                    }
                    else {
                      _apsession_setupStreamCreatingResponseInternal_cold_27();
                    }
                    goto LAB_2519bd208;
                  }
                }
                uVar21 = 0x1d85;
                goto LAB_2519bd200;
              }
            }
            else {
              if (iVar7 != 0x65) goto LAB_2519bd054;
              if (lVar12 != 0) {
                lVar11 = func_0x000258109150(lVar19);
                puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
                pcVar24 = (code *)*puVar23;
                if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
                  uVar10 = 0xffffce12;
                }
                else {
                  uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,
                                      local_f0,0x20,0,0x20,&local_a0);
                  if ((int)uVar10 == 0) {
                    uVar10 = func_0x000258109690(*_DAT_2680d3150,local_a0,1,&local_d8);
                    if ((int)uVar10 != 0) {
                      _apsession_setupStreamCreatingResponseInternal_cold_26();
                      goto LAB_2519bd208;
                    }
                    goto LAB_2519bd120;
                  }
                }
                uVar21 = 0x1d93;
                goto LAB_2519bd200;
              }
            }
            goto LAB_2519bd120;
          }
        }
        else if (1 < iVar7 - 0x66U) goto LAB_2519bd054;
        lVar11 = func_0x000258109150(lVar19);
        if (lVar12 == 0) {
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x10);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0x7362000000000000,lVar19,
                                &local_a0,local_80);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x000258109680(*_DAT_2680d3150,local_a0,local_80[0],&local_d8);
              if ((int)uVar10 == 0) {
                if ((_gLogCategory_APSenderSessionAirPlay < 0x29) &&
                   ((_gLogCategory_APSenderSessionAirPlay != -1 ||
                    (iVar7 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x2000028),
                    iVar7 != 0)))) {
                  pcVar20 = "[%{ptr}] CBC Cryptor created\n";
                  goto LAB_2519bceec;
                }
                goto LAB_2519bd120;
              }
              _apsession_setupStreamCreatingResponseInternal_cold_30();
              goto LAB_2519bd208;
            }
          }
          uVar21 = 0x1d79;
        }
        else {
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,local_f0
                                ,0x20,0,0x20,&local_a0);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x000258109690(*_DAT_2680d3150,local_a0,1,&local_d8);
              if ((int)uVar10 == 0) {
                if ((_gLogCategory_APSenderSessionAirPlay < 0x29) &&
                   ((_gLogCategory_APSenderSessionAirPlay != -1 ||
                    (iVar7 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x2000028),
                    iVar7 != 0)))) {
                  pcVar20 = "[%{ptr}] ChaCha Cryptor created\n";
LAB_2519bceec:
                  _apsession_setupStreamCreatingResponseInternal_cold_31(pcVar20,uVar26);
                }
                goto LAB_2519bd120;
              }
              _apsession_setupStreamCreatingResponseInternal_cold_29();
              goto LAB_2519bd208;
            }
          }
          uVar21 = 0x1d71;
        }
      }
      else if (iVar7 < 0x6e) {
        if (iVar7 == 0x6a) {
          if (lVar12 == 0) {
LAB_2519bd120:
            if (plVar1 != (long *)0x0) {
              *plVar1 = local_d8;
              local_d8 = 0;
            }
            if (plVar2 == (long *)0x0) goto LAB_2519bd148;
            uVar10 = 0;
            *plVar2 = local_e0;
            local_e0 = 0;
            goto LAB_2519bd208;
          }
          lVar11 = func_0x000258109150(lVar19);
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,local_f0
                                ,0x20,0,0x20,&local_a0);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x000258109690(*_DAT_2680d3150,local_a0,1,&local_d8);
              if ((int)uVar10 != 0) {
                _apsession_setupStreamCreatingResponseInternal_cold_25();
                goto LAB_2519bd208;
              }
              goto LAB_2519bd120;
            }
          }
          uVar21 = 0x1d9e;
        }
        else {
          if (iVar7 != 0x6b) goto LAB_2519bd054;
          if (lVar12 == 0) goto LAB_2519bd120;
          lVar11 = func_0x000258109150(lVar19);
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,local_f0
                                ,0x20,&local_d0,0x20,0);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x000258109690(*_DAT_2680d3150,local_d0,1,&local_e0);
              if ((int)uVar10 != 0) {
                _apsession_setupStreamCreatingResponseInternal_cold_24();
                goto LAB_2519bd208;
              }
              goto LAB_2519bd120;
            }
          }
          uVar21 = 0x1da9;
        }
      }
      else {
        if (1 < iVar7 - 0x6eU) {
          if ((iVar7 == 0x78) || (iVar7 == 0x82)) goto LAB_2519bd120;
LAB_2519bd054:
          uVar10 = 0xfffee76f;
          if ((_gLogCategory_APSenderSessionAirPlay < 0x5b) &&
             ((_gLogCategory_APSenderSessionAirPlay != -1 ||
              (iVar8 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x200005a),
              iVar8 != 0)))) {
            _apsession_setupStreamCreatingResponseInternal_cold_32(iVar7,uVar26);
          }
          goto LAB_2519bd208;
        }
        lVar11 = func_0x000258109150(lVar19);
        if (lVar12 == 0) {
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x28);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xa730000000000000,lVar19,local_f0
                                ,&local_a0,local_80);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x00025810d160(*_DAT_2680d3150,local_a0,local_80[0],&local_d8);
              if ((int)uVar10 != 0) {
                _apsession_setupStreamCreatingResponseInternal_cold_23();
                goto LAB_2519bd208;
              }
              goto LAB_2519bd120;
            }
          }
          uVar21 = 0x1dbc;
        }
        else {
          puVar23 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x38);
          pcVar24 = (code *)*puVar23;
          if ((pcVar24 == (code *)0x0) || (pcVar24 == (code *)0x0)) {
            uVar10 = 0xffffce12;
          }
          else {
            uVar10 = (*pcVar24)((ulong)puVar23 & 0xffffffffffff | 0xe8aa000000000000,lVar19,local_f0
                                ,0x20,0,0x20,&local_a0);
            if ((int)uVar10 == 0) {
              uVar10 = func_0x000258109690(*_DAT_2680d3150,local_a0,0,&local_d8);
              if ((int)uVar10 != 0) {
                _apsession_setupStreamCreatingResponseInternal_cold_22();
                goto LAB_2519bd208;
              }
              goto LAB_2519bd120;
            }
          }
          uVar21 = 0x1db5;
        }
      }
LAB_2519bd200:
      func_0x000258109a30(uVar10,"apsession_createCryptors",uVar21,0);
    }
LAB_2519bd208:
    if (local_d0 != 0) {
      func_0x0002580f5830();
    }
    if (local_a0 != 0) {
      func_0x0002580f5830();
    }
    if (local_80[0] != 0) {
      func_0x0002580f5830();
    }
    if (local_d8 != 0) {
      func_0x0002580f5830();
    }
    if (local_e0 != 0) {
      func_0x0002580f5830();
    }
    if (lVar19 != 0) {
      func_0x0002580f5830(lVar19);
    }
    if ((int)uVar10 == 0) {
      uVar10 = _apsession_restartKeepAliveInDifferentModeIfNeeded(*param_1);
      if ((int)uVar10 == 0) {
        if ((_gLogCategory_APSenderSessionAirPlay < 0x29) &&
           ((_gLogCategory_APSenderSessionAirPlay != -1 ||
            (iVar7 = func_0x000258101e40(&_gLogCategory_APSenderSessionAirPlay,0x2000028),
            iVar7 != 0)))) {
          _apsession_setupStreamCreatingResponseInternal_cold_36(param_1,pcVar9,param_1 + 1);
        }
        uVar25 = *(undefined8 *)(pcVar9 + 0x20);
        uVar21 = func_0x00025810ad10();
        func_0x00025810f2d0(uVar25,uVar21,_kAPSenderSessionNotification_Started,*param_1,0,0);
LAB_2519bd2bc:
        uVar10 = 0;
        goto LAB_2519bd2c0;
      }
      _apsession_setupStreamCreatingResponseInternal_cold_35();
    }
    else {
      _apsession_setupStreamCreatingResponseInternal_cold_34(uVar10);
    }
  }
  else {
    _apsession_setupStreamCreatingResponseInternal_cold_21(uVar10);
  }
LAB_2519bd470:
  _apsession_dispatchPostFailedNotification
            (*param_1,uVar10,_kAPSenderSessionState_Starting,param_1[6]);
LAB_2519bd2c0:
  if (*_DAT_2681b4ee0 != local_80[2]) {
    uVar10 = func_0x0002580f4380();
    return uVar10;
  }
  return uVar10;
}

