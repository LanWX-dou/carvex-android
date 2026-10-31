/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005e6ce0
 * original code SHA256: b1fa782c518573d30a2f2690b6c7b1ef8d203d24ee12bf24b89ffb725646efcc
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1005e6ce0(long param_1)

{
  undefined8 ****ppppuVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  bool bVar10;
  ID IVar11;
  long lVar12;
  undefined8 uVar13;
  ulong *puVar14;
  ulong uVar15;
  undefined4 *puVar16;
  long *plVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  long *plVar20;
  long *plVar21;
  ulong uVar22;
  ID IVar23;
  ulong uVar24;
  int iVar25;
  ulong *puVar26;
  undefined4 uVar27;
  undefined8 uStack_200;
  undefined4 uStack_1f8;
  char cStack_1e9;
  undefined8 ***pppuStack_1e0;
  long lStack_1d8;
  long lStack_1d0;
  undefined4 uStack_1c0;
  undefined4 uStack_1bc;
  undefined2 uStack_1b8;
  undefined2 uStack_1b6;
  undefined4 uStack_1b4;
  undefined2 uStack_1b0;
  undefined5 uStack_1ae;
  byte bStack_1a9;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  long lStack_198;
  ulong uStack_190;
  ulong uStack_188;
  long lStack_180;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined8 uStack_160;
  undefined8 uStack_150;
  ulong uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  cfstringStruct *pcStack_130;
  cfstringStruct *pcStack_128;
  ID IStack_120;
  ID IStack_118;
  cfstringStruct *pcStack_110;
  cfstringStruct *pcStack_108;
  ID IStack_100;
  ID IStack_f8;
  cfstringStruct *pcStack_f0;
  cfstringStruct *pcStack_e8;
  ID IStack_e0;
  ID IStack_d8;
  cfstringStruct *pcStack_d0;
  cfstringStruct *pcStack_c8;
  ID IStack_c0;
  ID IStack_b8;
  cfstringStruct *pcStack_b0;
  cfstringStruct *pcStack_a8;
  ID IStack_a0;
  ID IStack_98;
  cfstringStruct *pcStack_90;
  cfstringStruct *pcStack_88;
  ID IStack_80;
  ID IStack_78;
  long lStack_70;
  
  lStack_70 = *(long *)PTR____stack_chk_guard_100bfc980;
  uStack_140 = 0;
  uStack_138 = 0;
  FUN_100006ef8(&uStack_140);
  IVar11 = objc_stub::FUN_100914640(*(ID *)(param_1 + 0x5e0));
  if (IVar11 == 0) {
    IVar11 = objc_stub::FUN_1009124c0((ID)PTR__OBJC_CLASS___NSMutableArray_100bfcb08);
    *(ID *)(param_1 + 0x5e0) = IVar11;
  }
  else {
    objc_stub::FUN_10091cc20(*(ID *)(param_1 + 0x5e0));
  }
  uVar9 = _UNK_100930b00;
  uVar8 = _UNK_100930510;
  uVar18 = _UNK_1009304f0;
  uVar7 = _UNK_1009304d0;
  plVar20 = *(long **)(param_1 + 0x2c8);
  if (plVar20 == (long *)(param_1 + 0x2d0)) {
    iVar25 = 0;
  }
  else {
    iVar25 = 0;
    do {
      uStack_148 = ((undefined8 *)plVar20[4])[1];
      uStack_150 = *(undefined8 *)plVar20[4];
      uStack_170 = 0;
      uStack_16c = 0;
      uStack_168 = 0;
      uStack_164 = 0;
      uStack_160 = 0;
      lVar12 = param_1;
      FUN_1005ebdf0(param_1,&uStack_150,4,&uStack_170);
      puVar26 = (ulong *)CONCAT44(uStack_16c,uStack_170);
      if ((int)lVar12 != 0) {
        puVar14 = (ulong *)CONCAT44(uStack_164,uStack_168);
        if (puVar26 != puVar14) {
          do {
            uVar5 = *(ushort *)((long)puVar26 + 2);
            if (((uVar5 & 1) == 0) && (uVar5 != 0)) {
              uVar22 = 0;
              uVar24 = puVar26[1];
              do {
                uVar19 = uRam0000000100cae440;
                lVar12 = uVar24 + (uVar22 << 4 | 0x10);
                iVar2 = *(int *)(uVar24 + uVar22 * 0x10 + 8);
                uVar27 = (undefined4)uVar18;
                if (iVar2 == 3) {
                  bVar4 = *(byte *)(lVar12 + 8);
                  uVar15 = (ulong)bVar4;
                  uVar13 = uRam0000000100cae440;
                  _os_log_type_enabled(uRam0000000100cae440,0);
                  if ((int)uVar13 != 0) {
                    uStack_190 = (ulong)CONCAT14(bVar4,(int)uVar8);
                    __os_log_impl(0x100000000,uVar19,0,"RFCOMM CID: %d",&uStack_190,8);
                  }
                  uStack_190 = 0;
                  uStack_188 = 0;
                  lStack_180 = 0;
                  puVar14 = &uStack_190;
                  FUN_1001ec44c(puVar14,0x15);
                  uVar19 = s_RFCOMM_ServiceClass__100a68c0a._0_8_;
                  puVar14[1] = CONCAT35(s_RFCOMM_ServiceClass__100a68c0a._13_3_,
                                        s_RFCOMM_ServiceClass__100a68c0a._8_5_);
                  *puVar14 = uVar19;
                  *(ulong *)((long)puVar14 + 0xd) =
                       CONCAT53(s_RFCOMM_ServiceClass__100a68c0a._16_5_,
                                s_RFCOMM_ServiceClass__100a68c0a._13_3_);
                  *(char *)((long)puVar14 + 0x15) = '\0';
                  uStack_1a8 = 0;
                  uStack_1a0 = 0;
                  lStack_198 = 0;
                  if ((char)uStack_150 == '\x03') {
                    if (uStack_150._2_2_ < 5) {
                      if (uStack_150._2_2_ == 2) {
                        pppuStack_1e0 =
                             (undefined8 ***)
                             CONCAT62(pppuStack_1e0._2_6_,
                                      (ushort)uStack_148 >> 8 | (ushort)uStack_148 << 8);
                        IVar11 = objc_stub::FUN_100914bc0
                                           ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,&pppuStack_1e0,2)
                        ;
                        uVar19 = uRam0000000100cae440;
                        uVar13 = uRam0000000100cae440;
                        _os_log_type_enabled(uRam0000000100cae440,0);
                        if ((int)uVar13 != 0) {
                          uStack_1bc = (uint)uStack_148;
                          uStack_1b8 = 0x840;
                          uStack_1b6 = (undefined2)IVar11;
                          uStack_1b4 = (undefined4)(IVar11 >> 0x10);
                          uStack_1b0 = (undefined2)(IVar11 >> 0x30);
                          uStack_1c0 = uVar27;
                          __os_log_impl(0x100000000,uVar19,0,"service short UUID: (0x%x) %@",
                                        &uStack_1c0,0x12);
                        }
                        IVar23 = *(ID *)(param_1 + 0x5e0);
                        pcStack_f0 = &cf_kCBMsgArgServiceUUID;
                        pcStack_e8 = &cf_kCBMsgArgRFCOMMChannelID;
                        IStack_e0 = IVar11;
                        IStack_d8 = objc_stub::FUN_10091b260
                                              ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,uVar15);
                        IVar11 = objc_stub::FUN_100915980
                                           ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_e0,
                                            &pcStack_f0,2);
                        objc_stub::FUN_1009117c0(IVar23,IVar11);
                      }
                      else {
                        uVar3 = ((uint)uStack_148 & 0xff00ff00) >> 8 |
                                ((uint)uStack_148 & 0xff00ff) << 8;
                        pppuStack_1e0 =
                             (undefined8 ***)
                             CONCAT44(pppuStack_1e0._4_4_,uVar3 >> 0x10 | uVar3 << 0x10);
                        IVar11 = objc_stub::FUN_100914bc0
                                           ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,&pppuStack_1e0);
                        uVar19 = uRam0000000100cae440;
                        uVar13 = uRam0000000100cae440;
                        _os_log_type_enabled(uRam0000000100cae440,0);
                        if ((int)uVar13 != 0) {
                          uStack_1bc = (uint)uStack_148;
                          uStack_1b8 = 0x840;
                          uStack_1b6 = (undefined2)IVar11;
                          uStack_1b4 = (undefined4)(IVar11 >> 0x10);
                          uStack_1b0 = (undefined2)(IVar11 >> 0x30);
                          uStack_1c0 = uVar27;
                          __os_log_impl(0x100000000,uVar19,0,"service short UUID: (0x%x) %@",
                                        &uStack_1c0,0x12);
                        }
                        IVar23 = *(ID *)(param_1 + 0x5e0);
                        pcStack_110 = &cf_kCBMsgArgServiceUUID;
                        pcStack_108 = &cf_kCBMsgArgRFCOMMChannelID;
                        IStack_100 = IVar11;
                        IStack_f8 = objc_stub::FUN_10091b260
                                              ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,uVar15);
                        IVar11 = objc_stub::FUN_100915980
                                           ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_100
                                            ,&pcStack_110,2);
                        objc_stub::FUN_1009117c0(IVar23,IVar11);
                      }
                      uVar15 = uStack_148 & 0xffffffff;
                      FUN_1003d59f8(uVar15);
                      FUN_1003e9cbc(&uStack_1a8,uVar15);
                    }
                    else {
                      IVar11 = objc_stub::FUN_100914bc0
                                         ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,uStack_148);
                      uVar19 = uRam0000000100cae440;
                      uVar13 = uRam0000000100cae440;
                      _os_log_type_enabled(uRam0000000100cae440,0);
                      if ((int)uVar13 != 0) {
                        uStack_1bc = (undefined4)IVar11;
                        uStack_1b8 = (undefined2)(IVar11 >> 0x20);
                        uStack_1b6 = (undefined2)(IVar11 >> 0x30);
                        uStack_1c0 = (int)uVar7;
                        __os_log_impl(0x100000000,uVar19,0,"service long UUID: %@",&uStack_1c0,0xc);
                      }
                      IVar23 = *(ID *)(param_1 + 0x5e0);
                      pcStack_130 = &cf_kCBMsgArgServiceUUID;
                      pcStack_128 = &cf_kCBMsgArgRFCOMMChannelID;
                      IStack_120 = IVar11;
                      IStack_118 = objc_stub::FUN_10091b260
                                             ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,uVar15);
                      IVar11 = objc_stub::FUN_100915980
                                         ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_120,
                                          &pcStack_130,2);
                      objc_stub::FUN_1009117c0(IVar23,IVar11);
                      uVar15 = uStack_148;
                      FUN_1003d56fc(uStack_148);
                      FUN_1003e9cbc(&uStack_1a8,uVar15);
                    }
                    iVar25 = iVar25 + 1;
                  }
                  uStack_1c0 = 0;
                  uStack_1bc = 0;
                  uStack_1b8 = 0;
                  uStack_1b6 = 0;
                  uStack_1b4 = 0;
                  uStack_1b0 = 0;
                  uStack_1ae = 0;
                  bStack_1a9 = 0;
                  puVar16 = &uStack_1c0;
                  FUN_1001ec44c(puVar16,1);
                  *(undefined2 *)puVar16 = 10;
                  pppuStack_1e0 = (undefined8 ***)0x0;
                  lStack_1d8 = 0;
                  lStack_1d0 = 0;
                  FUN_1005eb214(&uStack_200,&uStack_190,&uStack_1a8);
                  uVar15 = CONCAT44(uStack_1b4,CONCAT22(uStack_1b6,uStack_1b8));
                  puVar16 = (undefined4 *)CONCAT44(uStack_1bc,uStack_1c0);
                  if (-1 < (char)bStack_1a9) {
                    uVar15 = (ulong)bStack_1a9;
                    puVar16 = &uStack_1c0;
                  }
                  plVar17 = &uStack_200;
                  __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendEPKcm
                            (plVar17,puVar16,uVar15);
                  lStack_1d8 = plVar17[1];
                  pppuStack_1e0 = (undefined8 ***)*plVar17;
                  lStack_1d0 = plVar17[2];
                  plVar17[1] = 0;
                  plVar17[2] = 0;
                  *plVar17 = 0;
                  if (cStack_1e9 < '\0') {
                    __ZdlPv(CONCAT44(uStack_200._4_4_,(undefined4)uStack_200));
                  }
                  uVar19 = uRam0000000100cae440;
                  uVar13 = uRam0000000100cae440;
                  _os_log_type_enabled(uRam0000000100cae440,0);
                  if ((int)uVar13 != 0) {
                    ppppuVar1 = (undefined8 ****)pppuStack_1e0;
                    if (-1 < lStack_1d0) {
                      ppppuVar1 = &pppuStack_1e0;
                    }
                    uStack_200._4_4_ = SUB84(ppppuVar1,0);
                    uStack_1f8 = (undefined4)((ulong)ppppuVar1 >> 0x20);
LAB_1005e76e4:
                    uStack_200._0_4_ = (int)uVar9;
                    __os_log_impl(0x100000000,uVar19,0,"%s",&uStack_200,0xc);
                  }
LAB_1005e76ec:
                  if (lStack_1d0 < 0) {
                    __ZdlPv(pppuStack_1e0);
                  }
                  if ((char)bStack_1a9 < '\0') {
                    __ZdlPv(CONCAT44(uStack_1bc,uStack_1c0));
                  }
                  if (lStack_198 < 0) {
                    __ZdlPv(uStack_1a8);
                  }
                  if (lStack_180 < 0) {
                    __ZdlPv(uStack_190);
                  }
                }
                else if (iVar2 == 0x100) {
                  uVar3 = *(uint *)(lVar12 + 8);
                  uStack_190 = 0;
                  uStack_188 = 0;
                  lStack_180 = 0;
                  puVar14 = &uStack_190;
                  FUN_1001ec44c(puVar14,0x14);
                  *(undefined4 *)(puVar14 + 2) = 0x203a7373;
                  uVar19 = s_L2CAP_ServiceClass__100a68c20._0_8_;
                  puVar14[1] = s_L2CAP_ServiceClass__100a68c20._8_8_;
                  *puVar14 = uVar19;
                  *(char *)((long)puVar14 + 0x14) = '\0';
                  uStack_1a8 = 0;
                  uStack_1a0 = 0;
                  lStack_198 = 0;
                  if ((char)uStack_150 == '\x03') {
                    if (uStack_150._2_2_ < 5) {
                      if (uStack_150._2_2_ == 2) {
                        pppuStack_1e0 =
                             (undefined8 ***)
                             CONCAT62(pppuStack_1e0._2_6_,
                                      (ushort)uStack_148 >> 8 | (ushort)uStack_148 << 8);
                        IVar11 = objc_stub::FUN_100914bc0
                                           ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,&pppuStack_1e0,2)
                        ;
                        uVar19 = uRam0000000100cae440;
                        uVar13 = uRam0000000100cae440;
                        _os_log_type_enabled(uRam0000000100cae440,0);
                        if ((int)uVar13 != 0) {
                          uStack_1bc = (uint)uStack_148;
                          uStack_1b8 = 0x840;
                          uStack_1b6 = (undefined2)IVar11;
                          uStack_1b4 = (undefined4)(IVar11 >> 0x10);
                          uStack_1b0 = (undefined2)(IVar11 >> 0x30);
                          uStack_1c0 = uVar27;
                          __os_log_impl(0x100000000,uVar19,0,"service short UUID: (0x%x) %@",
                                        &uStack_1c0,0x12);
                        }
                        IVar23 = *(ID *)(param_1 + 0x5e0);
                        pcStack_90 = &cf_kCBMsgArgServiceUUID;
                        pcStack_88 = &cf_kCBMsgArgPSM;
                        IStack_80 = IVar11;
                        IStack_78 = objc_stub::FUN_10091b300
                                              ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,
                                               (ulong)(uVar3 & 0xffff));
                        IVar11 = objc_stub::FUN_100915980
                                           ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_80,
                                            &pcStack_90,2);
                        objc_stub::FUN_1009117c0(IVar23,IVar11);
                      }
                      else {
                        uVar6 = ((uint)uStack_148 & 0xff00ff00) >> 8 |
                                ((uint)uStack_148 & 0xff00ff) << 8;
                        pppuStack_1e0 =
                             (undefined8 ***)
                             CONCAT44(pppuStack_1e0._4_4_,uVar6 >> 0x10 | uVar6 << 0x10);
                        IVar11 = objc_stub::FUN_100914bc0
                                           ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,&pppuStack_1e0);
                        uVar19 = uRam0000000100cae440;
                        uVar13 = uRam0000000100cae440;
                        _os_log_type_enabled(uRam0000000100cae440,0);
                        if ((int)uVar13 != 0) {
                          uStack_1bc = (uint)uStack_148;
                          uStack_1b8 = 0x840;
                          uStack_1b6 = (undefined2)IVar11;
                          uStack_1b4 = (undefined4)(IVar11 >> 0x10);
                          uStack_1b0 = (undefined2)(IVar11 >> 0x30);
                          uStack_1c0 = uVar27;
                          __os_log_impl(0x100000000,uVar19,0,"service short UUID: (0x%x) %@",
                                        &uStack_1c0,0x12);
                        }
                        IVar23 = *(ID *)(param_1 + 0x5e0);
                        pcStack_b0 = &cf_kCBMsgArgServiceUUID;
                        pcStack_a8 = &cf_kCBMsgArgPSM;
                        IStack_a0 = IVar11;
                        IStack_98 = objc_stub::FUN_10091b300
                                              ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,
                                               (ulong)(uVar3 & 0xffff));
                        IVar11 = objc_stub::FUN_100915980
                                           ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_a0,
                                            &pcStack_b0,2);
                        objc_stub::FUN_1009117c0(IVar23,IVar11);
                      }
                      uVar15 = uStack_148 & 0xffffffff;
                      FUN_1003d59f8(uVar15);
                      FUN_1003e9cbc(&uStack_1a8,uVar15);
                    }
                    else {
                      IVar11 = objc_stub::FUN_100914bc0
                                         ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,uStack_148);
                      uVar19 = uRam0000000100cae440;
                      uVar13 = uRam0000000100cae440;
                      _os_log_type_enabled(uRam0000000100cae440,0);
                      if ((int)uVar13 != 0) {
                        uStack_1bc = (undefined4)IVar11;
                        uStack_1b8 = (undefined2)(IVar11 >> 0x20);
                        uStack_1b6 = (undefined2)(IVar11 >> 0x30);
                        uStack_1c0 = (int)uVar7;
                        __os_log_impl(0x100000000,uVar19,0,"service long UUID: %@",&uStack_1c0,0xc);
                      }
                      IVar23 = *(ID *)(param_1 + 0x5e0);
                      pcStack_d0 = &cf_kCBMsgArgServiceUUID;
                      pcStack_c8 = &cf_kCBMsgArgPSM;
                      IStack_c0 = IVar11;
                      IStack_b8 = objc_stub::FUN_10091b300
                                            ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,
                                             (ulong)(uVar3 & 0xffff));
                      IVar11 = objc_stub::FUN_100915980
                                         ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_c0,
                                          &pcStack_d0,2);
                      objc_stub::FUN_1009117c0(IVar23,IVar11);
                      uVar15 = uStack_148;
                      FUN_1003d56fc(uStack_148);
                      FUN_1003e9cbc(&uStack_1a8,uVar15);
                    }
                    iVar25 = iVar25 + 1;
                  }
                  uStack_1c0 = 0;
                  uStack_1bc = 0;
                  uStack_1b8 = 0;
                  uStack_1b6 = 0;
                  uStack_1b4 = 0;
                  uStack_1b0 = 0;
                  uStack_1ae = 0;
                  bStack_1a9 = 0;
                  puVar16 = &uStack_1c0;
                  FUN_1001ec44c(puVar16,1);
                  *(undefined2 *)puVar16 = 10;
                  pppuStack_1e0 = (undefined8 ***)0x0;
                  lStack_1d8 = 0;
                  lStack_1d0 = 0;
                  FUN_1005eb214(&uStack_200,&uStack_190,&uStack_1a8);
                  uVar15 = CONCAT44(uStack_1b4,CONCAT22(uStack_1b6,uStack_1b8));
                  puVar16 = (undefined4 *)CONCAT44(uStack_1bc,uStack_1c0);
                  if (-1 < (char)bStack_1a9) {
                    uVar15 = (ulong)bStack_1a9;
                    puVar16 = &uStack_1c0;
                  }
                  plVar17 = &uStack_200;
                  __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendEPKcm
                            (plVar17,puVar16,uVar15);
                  lStack_1d8 = plVar17[1];
                  pppuStack_1e0 = (undefined8 ***)*plVar17;
                  lStack_1d0 = plVar17[2];
                  plVar17[1] = 0;
                  plVar17[2] = 0;
                  *plVar17 = 0;
                  if (cStack_1e9 < '\0') {
                    __ZdlPv(CONCAT44(uStack_200._4_4_,(undefined4)uStack_200));
                  }
                  uVar19 = uRam0000000100cae440;
                  uVar13 = uRam0000000100cae440;
                  _os_log_type_enabled(uRam0000000100cae440,0);
                  if ((int)uVar13 != 0) {
                    ppppuVar1 = (undefined8 ****)pppuStack_1e0;
                    if (-1 < lStack_1d0) {
                      ppppuVar1 = &pppuStack_1e0;
                    }
                    uStack_200._4_4_ = SUB84(ppppuVar1,0);
                    uStack_1f8 = (undefined4)((ulong)ppppuVar1 >> 0x20);
                    goto LAB_1005e76e4;
                  }
                  goto LAB_1005e76ec;
                }
                uVar22 = uVar22 + 2;
              } while (uVar22 < uVar5);
              puVar14 = (ulong *)CONCAT44(uStack_164,uStack_168);
            }
            puVar26 = puVar26 + 2;
          } while (puVar26 != puVar14);
          puVar26 = (ulong *)CONCAT44(uStack_16c,uStack_170);
        }
        if (puVar26 != puVar14) {
          do {
            puVar14 = puVar26 + 2;
            uStack_188 = puVar26[1];
            uStack_190 = *puVar26;
            FUN_100457214(&uStack_190);
            puVar26 = puVar14;
          } while (puVar14 != (ulong *)CONCAT44(uStack_164,uStack_168));
          puVar26 = (ulong *)CONCAT44(uStack_16c,uStack_170);
        }
      }
      if (puVar26 != (ulong *)0x0) {
        uStack_168 = SUB84(puVar26,0);
        uStack_164 = (undefined4)((ulong)puVar26 >> 0x20);
        __ZdlPv(puVar26);
      }
      plVar17 = (long *)plVar20[1];
      plVar21 = plVar20;
      if ((long *)plVar20[1] == (long *)0x0) {
        do {
          plVar20 = (long *)plVar21[2];
          bVar10 = plVar21 != (long *)*plVar20;
          plVar21 = plVar20;
        } while (bVar10);
      }
      else {
        do {
          plVar20 = plVar17;
          plVar17 = (long *)*plVar20;
        } while ((long *)*plVar20 != (long *)0x0);
      }
    } while (plVar20 != (long *)(param_1 + 0x2d0));
  }
  uVar7 = uRam0000000100cae440;
  uVar18 = uRam0000000100cae440;
  _os_log_type_enabled(uRam0000000100cae440,0);
  if ((int)uVar18 != 0) {
    uStack_170 = (undefined4)_UNK_1009304d0;
    uStack_16c = (undefined4)*(undefined8 *)(param_1 + 0x5e0);
    uStack_168 = (undefined4)((ulong)*(undefined8 *)(param_1 + 0x5e0) >> 0x20);
    __os_log_impl(0x100000000,uVar7,0,"Services dictionary: %@",&uStack_170,0xc);
  }
  FUN_100006ec0(&uStack_140);
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_70) {
    return iVar25;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

