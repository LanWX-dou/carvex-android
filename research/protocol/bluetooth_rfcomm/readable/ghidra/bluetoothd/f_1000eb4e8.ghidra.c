/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000eb4e8
 * original code SHA256: 0457a4ec3119498d8c7200ec6df68cfbeb1be41b16346073645ffd8c2c2cc623
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_1000eb4e8(long param_1,ulong param_2,long param_3)

{
  uint uVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  ulong uVar5;
  undefined8 uVar6;
  ulong uVar7;
  ulong uVar8;
  undefined *puVar9;
  undefined8 uVar10;
  int *piVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  char *pcVar14;
  uint uVar15;
  long lVar16;
  ulong uVar17;
  ulong uVar18;
  int iVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uStack_b80;
  ulong uStack_b70;
  undefined8 uStack_b50;
  undefined2 uStack_b48;
  int iStack_b46;
  undefined2 uStack_b42;
  uint uStack_b40;
  undefined2 uStack_b3c;
  uint uStack_b3a;
  undefined2 uStack_b36;
  uint uStack_b34;
  undefined2 uStack_b30;
  uint uStack_b2e;
  undefined2 uStack_b2a;
  uint uStack_b28;
  undefined2 uStack_b24;
  uint uStack_b22;
  undefined1 uStack_b11;
  undefined1 auStack_b10 [16];
  undefined1 auStack_b00 [16];
  undefined1 auStack_af0 [16];
  undefined8 uStack_ae0;
  undefined8 uStack_ad8;
  undefined8 uStack_ad0;
  undefined8 uStack_ac8;
  undefined8 uStack_ac0;
  undefined8 uStack_ab8;
  undefined8 uStack_ab0;
  undefined8 uStack_aa8;
  uint uStack_a94;
  ulong uStack_a90;
  undefined8 uStack_a88;
  undefined1 auStack_a7a [2570];
  long lStack_70;
  
  lStack_70 = *(long *)PTR____stack_chk_guard_100bfc980;
  _bzero(auStack_a7a,0xa0a);
  uVar6 = uRam0000000100cae4c0;
  uVar13 = _UNK_100930b08;
  uVar12 = _UNK_1009304c8;
  lVar16 = *(long *)(param_3 + 0xd0);
  uStack_a94 = 0;
  uVar18 = param_2;
  if (lVar16 == 0) {
    do {
      uVar6 = uRam0000000100cae4c0;
      uStack_a90 = CONCAT44(uStack_a90._4_4_,0xa0a);
      iVar19 = *(int *)(param_3 + 0x164);
      uStack_b50 = auStack_a7a;
      if (iVar19 == 2) {
        uVar15 = (uint)*(ushort *)(param_3 + 0x168);
        if (0xa09 < uVar15) {
          uVar15 = 0xa0a;
        }
        uStack_a90 = CONCAT44(uStack_a90._4_4_,uVar15);
        uVar10 = uRam0000000100cae4c0;
        _os_log_type_enabled(uRam0000000100cae4c0,0);
        if ((int)uVar10 != 0) {
          uStack_ad8._0_6_ = CONCAT42(*(undefined4 *)(param_3 + 0x15c),0x400);
          pcVar14 = "MAX buffer size for the RFCOMM Channel is %d getWriteBufferUsed=%d";
LAB_1000ebb18:
          uStack_ae0 = CONCAT44(uVar15,(int)uVar12);
          __os_log_impl(0x100000000,uVar6,0,pcVar14,&uStack_ae0,0xe);
        }
LAB_1000ebb20:
        puVar9 = (undefined *)0x0;
        bVar4 = false;
        uVar18 = param_2 & 0xffffffff;
      }
      else {
        if (iVar19 == 1) {
          uVar15 = (uint)*(ushort *)(param_3 + 0x168);
          if (0xa09 < uVar15) {
            uVar15 = 0xa0a;
          }
          uStack_a90 = CONCAT44(uStack_a90._4_4_,uVar15);
          uVar10 = uRam0000000100cae4c0;
          _os_log_type_enabled(uRam0000000100cae4c0,0);
          if ((int)uVar10 != 0) {
            uStack_ad8._0_6_ = CONCAT42(*(undefined4 *)(param_3 + 0x15c),0x400);
            pcVar14 = "MAX buffer size for the L2CAP Channel is %d getWriteBufferUsed=%d";
            goto LAB_1000ebb18;
          }
          goto LAB_1000ebb20;
        }
        if (iVar19 == 0) {
          auStack_af0[0] = 0;
          FUN_100061a60(auStack_af0);
          puVar9 = *(undefined **)(param_3 + 0x60);
          FUN_10030d088(puVar9,&uStack_b50,&uStack_a90);
          FUN_10006433c(auStack_af0);
          uVar6 = uRam0000000100cae4c0;
          iVar19 = (int)puVar9;
          bVar4 = iVar19 == 0;
          if ((iVar19 != 0) &&
             (uVar10 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x10),
             (int)uVar10 != 0)) {
            uStack_ae0 = CONCAT44((int)uVar18,(int)uVar13);
            uStack_ad8._0_6_ = CONCAT42(iVar19,0x400);
            uStack_ad8 = CONCAT26(0x400,(undefined6)uStack_ad8);
            uStack_ad0 = CONCAT44(uStack_ad0._4_4_,(undefined4)uStack_a90);
            __os_log_error_impl(0x100000000,uVar6,0x10,
                                "Failed to get a buffer from the stack for pipe 0x%04x with result %{bluetooth:OI_STATUS}u, default size %d"
                                ,&uStack_ae0,0x14);
          }
          FUN_10006b538(auStack_af0);
        }
        else {
          puVar9 = (undefined *)0x0;
          bVar4 = false;
        }
      }
      piVar11 = (int *)(ulong)*(uint *)(param_3 + 0xb8);
      _read(piVar11,uStack_b50,uStack_a90 & 0xffffffff);
      uVar6 = uRam0000000100cae4c0;
      if ((long)piVar11 < 1) {
        if (piVar11 == (int *)0x0) {
          uVar12 = uRam0000000100cae4c0;
          _os_log_type_enabled(uRam0000000100cae4c0,0x10);
          if ((int)uVar12 != 0) {
            FUN_1008c1750(uVar18,uVar6);
          }
        }
        else {
          ___error();
          uVar12 = uRam0000000100cae4c0;
          if (*piVar11 == 0x23) {
            if (bVar4 != false) {
              uStack_ae0 = uStack_ae0 & 0xffffffffffffff00;
              FUN_100061a60(&uStack_ae0);
              thunk_FUN_1000110b8(uStack_b50);
              FUN_10006433c(&uStack_ae0);
              FUN_10006b538(&uStack_ae0);
            }
            bVar3 = true;
            goto LAB_1000ebde8;
          }
          uVar13 = uRam0000000100cae4c0;
          _os_log_type_enabled(uRam0000000100cae4c0,0x10);
          if ((int)uVar13 != 0) {
            FUN_1008c16ec(uVar18,uVar12);
          }
        }
        bVar3 = false;
        if (bVar4 == false) goto LAB_1000ebde8;
        uStack_ae0 = uStack_ae0 & 0xffffffffffffff00;
        FUN_100061a60(&uStack_ae0);
        thunk_FUN_1000110b8(uStack_b50);
        FUN_10006433c(&uStack_ae0);
        goto LAB_1000ebddc;
      }
      if (*(char *)(param_1 + 0x8b) == '\x01') {
        FUN_1000ec0a4(uVar18);
        FUN_10044e35c();
      }
      uStack_ae0 = uStack_ae0 & 0xffffffffffffff00;
      FUN_100061a60(&uStack_ae0);
      iVar19 = *(int *)(param_3 + 0x164);
      uVar15 = (uint)piVar11;
      if (iVar19 == 2) {
        puVar9 = &DAT_10044e6a4;
        FUN_1003c2ae8(&DAT_10044e6a4,uVar18,uStack_b50,uVar15 & 0xffff);
      }
      else if (iVar19 == 1) {
        puVar9 = &DAT_10044e6a4;
        FUN_100368a64(&DAT_10044e6a4,uVar18,0,uStack_b50,uVar15 & 0xffff);
      }
      else if (iVar19 == 0) {
        puVar9 = &DAT_10044e6a4;
        FUN_1000bfe14(&DAT_10044e6a4,*(undefined8 *)(param_3 + 0x60),uVar18,uStack_b50,
                      uVar15 & 0xffff,bVar4);
      }
      FUN_10006433c(&uStack_ae0);
      uVar6 = uRam0000000100cae4c0;
      if ((int)puVar9 != 0x19c) goto LAB_1000ebc94;
      FUN_10006b538(&uStack_ae0);
    } while( true );
  }
  uVar18 = *(ulong *)(param_3 + 0xe0);
  if ((uVar18 == 0) &&
     (uVar12 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x11),
     (int)uVar12 != 0)) {
    FUN_1008c1628(uVar6);
  }
  uStack_ab8 = 0;
  uStack_ac0 = 0;
  uStack_aa8 = 0;
  uStack_ab0 = 0;
  uStack_ad8 = 0;
  uStack_ae0 = 0;
  uStack_ac8 = 0;
  uStack_ad0 = 0;
  uVar5 = uVar18;
  _os_channel_get_next_slot(uVar18,0,&uStack_ae0);
  uVar13 = _UNK_100935838;
  uVar12 = _UNK_100930510;
  uStack_b70 = 0;
  uStack_b80 = 0;
  uVar21 = 0;
  uStack_a90 = 0;
  uStack_a88 = 0;
  uVar17 = param_2;
  do {
    uVar6 = uRam0000000100cae4c0;
    if ((*(int *)(param_3 + 0x164) != 0) &&
       (uVar10 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x11),
       (int)uVar10 != 0)) {
      FUN_1008c1674(auStack_af0,(ulong)auStack_af0 | 1,uVar6);
    }
    if (uVar5 == 0) {
LAB_1000eb618:
      uVar15 = 0;
    }
    else {
      iVar19 = *(int *)(param_3 + 0x15c);
      if ((uint)(*(int *)(param_3 + 0x158) - iVar19) < (uint)uStack_ae0._2_2_) goto LAB_1000eb618;
      uVar15 = 0;
      do {
        uVar20 = uVar5;
        if ((iVar19 != 0) && (uVar5 = uVar20, *(int *)(param_3 + 0x160) == 3)) break;
        uVar5 = uVar18;
        _os_channel_slot_get_packet(uVar18,uVar20);
        uVar21 = uVar5;
        _os_packet_get_next_buflet();
        uVar6 = uRam0000000100cae4c0;
        if ((uVar21 == 0) &&
           (uVar10 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x11),
           (int)uVar10 != 0)) {
          FUN_1008c1698(auStack_b00,(ulong)auStack_b00 | 1,uVar6);
        }
        uVar7 = uVar21;
        _os_buflet_get_data_offset(uVar21);
        uVar8 = uVar21;
        _os_buflet_get_object_address(uVar21);
        _os_buflet_get_data_length();
        _os_packet_get_flow_uuid(uVar5,&uStack_a90);
        uVar6 = uRam0000000100cae4c0;
        uVar2 = uStack_ae0._2_2_;
        iVar19 = (int)uVar21;
        if (((*(int *)(param_3 + 0x160) == 3) && (0x2a3 < uStack_ae0._2_2_)) &&
           (uVar10 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x11),
           (int)uVar10 != 0)) {
          uStack_b50 = (undefined1 *)(ulong)CONCAT24(uVar2,(int)uVar12);
          __os_log_fault_impl(0x100000000,uVar6,0x11,
                              "Payload length %d exceeds supported MTU for isoch channel",
                              &uStack_b50,8);
          uVar2 = uStack_ae0._2_2_;
          if (iVar19 != 0) goto LAB_1000eb918;
LAB_1000eb8c8:
          if (uVar2 == 0) goto LAB_1000eb918;
          FUN_1000ebf48(param_3,uStack_ad0,uVar2);
        }
        else {
          if (iVar19 == 0) goto LAB_1000eb8c8;
LAB_1000eb918:
          uVar6 = uRam0000000100cae4c0;
          if (iVar19 == 0) {
            uVar10 = uRam0000000100cae4c0;
            _os_log_type_enabled(uRam0000000100cae4c0,0x10);
            if ((int)uVar10 != 0) {
              FUN_1008c16bc(auStack_b10,(ulong)auStack_b10 | 1,uVar6);
            }
          }
          else {
            FUN_1000ebf48(param_3,uVar8 + (uVar7 & 0xffffffff),uVar21 & 0xffffffff);
          }
        }
        uVar1 = (uint)(ushort)uStack_a88;
        if (uVar15 != 0) {
          uVar1 = uVar15;
        }
        uVar5 = uVar18;
        _os_channel_get_next_slot(uVar18,uVar20,&uStack_ae0);
        uVar21 = uVar20;
        uVar15 = uVar1;
        if (uVar5 == 0) break;
        iVar19 = *(int *)(param_3 + 0x15c);
      } while ((uint)uStack_ae0._2_2_ <= (uint)(*(int *)(param_3 + 0x158) - iVar19));
    }
    bVar3 = *(int *)(param_3 + 0x15c) == 0;
    if (*(int *)(param_3 + 0x15c) == 0) goto LAB_1000ebce4;
    uStack_b11 = 0;
    FUN_100061a60(&uStack_b11);
    uVar6 = *(undefined8 *)(param_3 + 0x60);
    FUN_1000bf9ec(uVar6,&uStack_a94);
    if (((int)uVar6 != 0) && ((int)uVar6 != 0x138f)) {
      uStack_a94 = 0x3f7;
    }
    uVar1 = uStack_a94;
    if (*(uint *)(param_3 + 0x15c) <= uStack_a94) {
      uVar1 = *(uint *)(param_3 + 0x15c);
    }
    if ((*(byte *)(param_3 + 0x16a) & 1) == 0) {
      uStack_b70 = uVar17;
      FUN_1000ec0a4();
      uStack_b70 = uStack_b70 & 0xffffffff;
    }
    if (*(char *)(param_1 + 0x8b) == '\x01') {
      FUN_10044e35c();
    }
    iVar19 = 0x44e6a4;
    FUN_1000bfe14(&DAT_10044e6a4,*(undefined8 *)(param_3 + 0x60),uVar17,
                  *(undefined8 *)(param_3 + 0x150),uVar1 & 0xffff,0);
    if ((*(byte *)(param_3 + 0x16a) & 1) == 0) {
      FUN_1000ec0a4();
      uStack_b80 = uVar17 & 0xffffffff;
    }
    FUN_10006433c(&uStack_b11);
    uVar6 = uRam0000000100cae4f8;
    if (*(char *)(param_1 + 0x8a) == '\x01') {
      uVar2 = (ushort)uStack_a88;
      uVar10 = uRam0000000100cae4f8;
      _os_log_type_enabled(uRam0000000100cae4f8,0);
      if ((int)uVar10 != 0) {
        uStack_b34 = uVar1 & 0xffff;
        uStack_b2e = (uint)uStack_b70 & 0xffff;
        uStack_b22 = (uint)bRam0000000100cae500;
        bRam0000000100cae500 = bRam0000000100cae500 + 1;
        uStack_b28 = (int)uStack_b80 - 1U & 0xffff;
        uStack_b50 = (undefined1 *)CONCAT44(0x14,(int)uVar13);
        uStack_b48 = 0x400;
        iStack_b46 = 0x3c;
        uStack_b42 = 0x400;
        uStack_b3c = 0x400;
        uStack_b3a = (uint)uVar2;
        uStack_b36 = 0x400;
        uStack_b30 = 0x400;
        uStack_b2a = 0x400;
        uStack_b24 = 0x400;
        uStack_b40 = uVar15;
        __os_log_impl(0x100000000,uVar6,0,
                      "28 {curProtocol: %hhu, prevProtocol: %hhu, prevSeqnStart: %hu, prevSeqnEnd: %hu, prevLen: %hu, curSeqNStart: %hu, curSeqnEnd:%hu, logSeqn: %hhu}"
                      ,&uStack_b50,0x32);
      }
    }
    *(int *)(param_3 + 0xfc) = *(int *)(param_3 + 0xfc) + 1;
    uVar6 = uRam0000000100cae4c0;
    if (iVar19 != 0x19c) goto LAB_1000eb9b4;
    FUN_1000eb2a4(param_3,uVar1);
    uVar17 = param_2 & 0xffffffff;
    FUN_10006b538(&uStack_b11);
  } while( true );
LAB_1000ebc94:
  if (((int)puVar9 != 0) &&
     (uVar12 = uRam0000000100cae4c0, _os_log_type_enabled(uRam0000000100cae4c0,0x10),
     (int)uVar12 != 0)) {
    FUN_1008c1790(uVar18,puVar9,uVar6);
  }
LAB_1000ebddc:
  FUN_10006b538(&uStack_ae0);
  bVar3 = false;
  goto LAB_1000ebde8;
LAB_1000eb9b4:
  if (iVar19 == 0) {
    FUN_1000eb2a4(param_3,uVar1);
  }
  else {
    uVar12 = uRam0000000100cae4c0;
    _os_log_type_enabled(uRam0000000100cae4c0,0x10);
    if ((int)uVar12 != 0) {
      uStack_b50 = (undefined1 *)CONCAT44((int)param_2,(int)_UNK_1009304c8);
      uStack_b48 = 0x400;
      iStack_b46 = iVar19;
      __os_log_error_impl(0x100000000,uVar6,0x10,
                          "Failed to transmit data from socket on pipe 0x%04x with result %{bluetooth:OI_STATUS}u"
                          ,&uStack_b50,0xe);
    }
  }
  FUN_10006b538(&uStack_b11);
LAB_1000ebce4:
  if (uVar21 != 0) {
    _os_channel_advance_slot(uVar18,uVar21);
  }
  if (((*(int *)(param_3 + 0x160) == 3) || (*(uint *)(param_3 + 0xf4) <= *(uint *)(param_3 + 0xfc)))
     || (_os_channel_available_slot_count(), (uint)uVar18 < 2)) {
    *(undefined4 *)(param_3 + 0xfc) = 0;
    _os_channel_sync(lVar16,1);
  }
LAB_1000ebde8:
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_70) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return bVar3;
}

