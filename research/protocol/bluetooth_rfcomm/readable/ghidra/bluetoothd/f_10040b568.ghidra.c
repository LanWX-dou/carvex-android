/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10040b568
 * original code SHA256: 5098af9801fb3dad37003e308f8dcaee077b77e12ddd768cd9c2a38f84962a3b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_retain_x1 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x26 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_10040b568(ID param_1)

{
  ushort *puVar1;
  short *psVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  ushort uVar6;
  undefined *self;
  char cVar7;
  ID IVar8;
  ulong uVar9;
  ushort **ppuVar10;
  ID IVar11;
  ID IVar12;
  uint *puVar13;
  ulong uVar14;
  undefined1 *self_00;
  undefined4 *puVar15;
  undefined8 uVar16;
  char *pcVar17;
  int iVar18;
  ulong uVar19;
  long lVar20;
  long lVar21;
  undefined8 uVar22;
  ulong uVar23;
  ID self_01;
  ID IVar24;
  undefined8 uVar25;
  undefined1 auStack_1d0 [16];
  uint uStack_1c0;
  int iStack_1bc;
  undefined1 auStack_1b0 [16];
  undefined8 uStack_1a0;
  long lStack_198;
  long *plStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined4 uStack_160;
  uint uStack_15c;
  undefined2 uStack_158;
  ushort uStack_156;
  undefined2 uStack_154;
  undefined2 uStack_152;
  undefined8 uStack_150;
  undefined1 uStack_145;
  uint uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined2 uStack_138;
  undefined2 uStack_136;
  undefined4 uStack_134;
  undefined8 uStack_130;
  ulong uStack_128;
  ushort *puStack_118;
  undefined8 uStack_110;
  undefined1 auStack_108 [128];
  long lStack_88;
  
  uVar16 = uRam0000000100cae4b8;
  lStack_88 = *(long *)PTR____stack_chk_guard_100bfc980;
  uVar25 = uRam0000000100cae4b8;
  _os_log_type_enabled(uRam0000000100cae4b8,0);
  if ((int)uVar25 != 0) {
    uStack_140 = (undefined4)_UNK_1009304d0;
    uStack_13c = (undefined4)param_1;
    uStack_138 = (undefined2)(param_1 >> 0x20);
    uStack_136 = (undefined2)(param_1 >> 0x30);
    __os_log_impl(0x100000000,uVar16,0,"addServiceDataToLocalSDP: %@",&uStack_140,0xc);
  }
  uVar16 = uRam0000000100cae4b8;
  if (param_1 == 0) {
    uVar25 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0x10);
    if ((int)uVar25 != 0) {
      FUN_1008bce00(uVar16);
    }
  }
  else {
    IVar8 = objc_stub::FUN_100919c80(param_1);
    uVar16 = uRam0000000100cae4b8;
    if (IVar8 != 0) {
      puStack_118 = (ushort *)0x0;
      uStack_110 = 0;
      uStack_138 = 0;
      uStack_136 = 0;
      uStack_134 = 0;
      uStack_140 = 0;
      uStack_13c = 0;
      uStack_128 = 0;
      uStack_130 = 0;
      uStack_144 = 0;
      _objc_retainAutorelease(param_1);
      IVar8 = objc_stub::FUN_100913420(param_1);
      if (IVar8 == 0) {
        pcVar17 = "(uint8_t*)serviceRecordData.bytes";
      }
      else {
        IVar8 = objc_stub::FUN_100919c80(param_1);
        if (IVar8 != 0) {
          uStack_110 = uStack_110 & 0xffffffffffffff;
          _objc_retainAutorelease(param_1);
          puStack_118 = (ushort *)objc_stub::FUN_100913420(param_1);
          IVar8 = objc_stub::FUN_100919c80(param_1);
          uStack_110 = CONCAT62(uStack_110._2_6_,(short)IVar8);
          IVar8 = objc_stub::FUN_100919c80(param_1);
          uVar25 = uStack_110;
          uVar16 = uRam0000000100cae4b8;
          uVar3 = (ushort)uStack_110;
          uStack_110._0_4_ = CONCAT22((short)IVar8,(ushort)uStack_110);
          pcVar17 = "((byteStreamData).__data != NULL) && ((byteStreamData).__trueSize > 0)";
          uVar22 = 0x629;
          if ((puStack_118 == (ushort *)0x0) || ((ushort)uStack_110 == 0)) goto LAB_10040bec0;
          uStack_110._7_1_ = SUB81(uVar25,7);
          cVar7 = uStack_110._7_1_;
          uStack_110 = CONCAT17(uStack_110._7_1_,0x1000000000000);
          uStack_110._0_4_ = CONCAT22(uVar3,uVar3);
          if (cVar7 != '\0') {
            uVar22 = 0x62a;
            FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Daemon/Server/XpcClassicConnection.mm"
                          ,0x62a,
                          "uint32_t XpcClassicConnection::addServiceDataToLocalSDP(NSData *__strong)"
                         );
            pcVar17 = "ByteStream_NumReadBytesAvail(byteStreamData) >= 2";
            goto LAB_10040bec0;
          }
          if (uVar3 < 2) {
            pcVar17 = "ByteStream_NumReadBytesAvail(byteStreamData) >= 2";
            uVar22 = 0x62a;
            goto LAB_10040bec0;
          }
          uVar3 = *puStack_118;
          uVar23 = (ulong)uVar3;
          uStack_110._0_6_ = CONCAT24(2,(undefined4)uStack_110);
          uStack_110 = CONCAT26(1,(undefined6)uStack_110);
          uVar25 = uRam0000000100cae4b8;
          _os_log_type_enabled(uRam0000000100cae4b8,0);
          if ((int)uVar25 != 0) {
            uStack_160 = (undefined4)_UNK_1009304c8;
            uStack_15c = (uint)uVar3;
            uStack_158 = 0x400;
            uStack_154 = 0;
            uStack_156 = uVar3;
            __os_log_impl(0x100000000,uVar16,0,
                          "addServiceDataToLocalSDP: Number of attributes: %d, 0x%x",&uStack_160,0xe
                         );
          }
          uVar9 = uVar23;
          _malloc_type_calloc(uVar23,0x18,0x10f20406c095635);
          uVar16 = uRam0000000100cae4b8;
          if (uVar9 != 0) {
            if (uVar3 != 0) {
              uVar19 = 0;
LAB_10040b760:
              iVar18 = (int)uVar19;
              if (uStack_110._7_1_ != '\0') {
                FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Daemon/Server/XpcClassicConnection.mm"
                              ,0x638,
                              "uint32_t XpcClassicConnection::addServiceDataToLocalSDP(NSData *__strong)"
                             );
                pcVar17 = "ByteStream_NumReadBytesAvail(byteStreamData) >= 2";
LAB_10040be54:
                    /* WARNING: Subroutine does not return */
                FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Daemon/Server/XpcClassicConnection.mm"
                              ,0x638,pcVar17);
              }
              pcVar17 = "ByteStream_NumReadBytesAvail(byteStreamData) >= 2";
              if (((int)((uint)uStack_110._2_2_ - (uint)uStack_110._4_2_) < 2) ||
                 (pcVar17 = "(byteStreamData).__RWFlag == BYTESTREAM_READ",
                 uStack_110._6_1_ != '\x01')) goto LAB_10040be54;
              uVar6 = *(ushort *)((long)puStack_118 + (ulong)uStack_110._4_2_);
              uVar3 = *(ushort *)((long)puStack_118 + (ulong)uStack_110._4_2_);
              uVar5 = (uint)uVar3;
              uStack_110._0_6_ = CONCAT24(uStack_110._4_2_ + 2,(undefined4)uStack_110);
              puVar1 = (ushort *)(uVar9 + ((uVar19 & 0xffff) * 2 + (uVar19 & 0xffff)) * 8);
              *puVar1 = uVar3;
              ppuVar10 = &puStack_118;
              FUN_100457334(ppuVar10,puVar1 + 4);
              uVar16 = uRam0000000100cae4b8;
              if (((ulong)ppuVar10 & 1) != 0) goto code_r0x00010040b7c4;
              uVar25 = uRam0000000100cae4b8;
              _os_log_type_enabled(uRam0000000100cae4b8,0x10);
              if ((int)uVar25 != 0) {
                FUN_1008bcc20(uVar5,uVar16);
              }
              if ((uVar19 & 0xffff) != 0) {
                lVar20 = 0;
                uVar19 = uVar19 & 0xffff;
                do {
                  FUN_100457214(uVar9 + lVar20 * 0x18 + 8);
                  lVar20 = lVar20 + 1;
                  uVar19 = uVar19 - 1;
                } while (uVar19 != 0);
              }
              _free(uVar9);
              goto LAB_10040bab4;
            }
LAB_10040b7fc:
            uStack_140 = (undefined4)uVar9;
            uStack_13c = (undefined4)(uVar9 >> 0x20);
            uStack_138 = (undefined2)uVar23;
            uStack_130 = 0;
            uStack_128 = uStack_128 & 0xffffffffffff0000;
            uStack_145 = 0;
            self_00 = &uStack_145;
            FUN_100061a60();
            uVar16 = _UNK_1009304d0;
            if ((uVar23 & 0xffff) == 0) {
              IVar8 = 0;
            }
            else {
              uVar19 = 0;
              IVar8 = 0;
              do {
                psVar2 = (short *)(uVar9 + uVar19 * 0x18);
                if (*psVar2 == 1) {
                  uVar25 = *(undefined8 *)(psVar2 + 4);
                  uStack_158 = (undefined2)uVar25;
                  uStack_156 = (ushort)((ulong)uVar25 >> 0x10);
                  uStack_154 = (undefined2)((ulong)uVar25 >> 0x20);
                  uStack_152 = (undefined2)((ulong)uVar25 >> 0x30);
                  uStack_160 = (undefined4)*(undefined8 *)psVar2;
                  uStack_15c = (uint)((ulong)*(undefined8 *)psVar2 >> 0x20);
                  uStack_150 = *(undefined8 *)(psVar2 + 8);
                  FUN_10040bfa0();
                  IVar8 = objc_stub::FUN_100914640((ID)self_00);
                  uVar25 = uRam0000000100cae4b8;
                  if (IVar8 == 0) {
                    uVar16 = uRam0000000100cae4b8;
                    _os_log_type_enabled(uRam0000000100cae4b8,0x10);
                    if ((int)uVar16 != 0) {
                      FUN_1008bccf0(uVar25);
                    }
                    uVar14 = 0;
                    goto LAB_10040bdec;
                  }
                  uStack_178 = 0;
                  uStack_180 = 0;
                  uStack_168 = 0;
                  uStack_170 = 0;
                  lStack_198 = 0;
                  uStack_1a0 = 0;
                  uStack_188 = 0;
                  plStack_190 = (long *)0x0;
                  IVar11 = objc_stub::FUN_100914660(IVar8,&uStack_1a0,auStack_108,0x10);
                  if (IVar11 != 0) {
                    lVar20 = *plStack_190;
                    do {
                      lVar21 = 0;
                      do {
                        if (*plStack_190 != lVar20) {
                          _objc_enumerationMutation(IVar8);
                        }
                        IVar24 = *(ID *)(lStack_198 + lVar21 * 8);
                        IVar12 = objc_stub::FUN_100919c80(IVar24);
                        uVar25 = uRam0000000100cae4b8;
                        if (IVar12 < 5) {
                          uStack_1c0 = uStack_1c0 & 0xffff0000;
                          _objc_retainAutorelease(IVar24);
                          puVar13 = (uint *)objc_stub::FUN_100913420(IVar24);
                          uVar14 = (ulong)*puVar13;
                          FUN_1003c8e9c(uVar14,&uStack_1c0);
                          uVar25 = uRam0000000100cae4b8;
                          uVar22 = uRam0000000100cae4b8;
                          _os_log_type_enabled(uRam0000000100cae4b8,0x10);
                          if ((int)uVar14 != 0) {
                            if ((int)uVar22 != 0) {
                              FUN_1008bcca0(IVar24,uVar14,uVar25);
                            }
                            goto LAB_10040bdec;
                          }
                          if ((int)uVar22 != 0) {
                            uStack_160 = (undefined4)uVar16;
                            uStack_15c = (uint)IVar24;
                            uStack_158 = (undefined2)(IVar24 >> 0x20);
                            uStack_156 = (ushort)(IVar24 >> 0x30);
                            __os_log_error_impl(0x100000000,uVar25,0x10,
                                                "New service being added for %@",&uStack_160,0xc);
                          }
                        }
                        else {
                          uVar22 = uRam0000000100cae4b8;
                          _os_log_type_enabled(uRam0000000100cae4b8,0x10);
                          if ((int)uVar22 != 0) {
                            FUN_1008bcc68(auStack_1b0,(ulong)auStack_1b0 | 1,uVar25);
                          }
                        }
                        lVar21 = lVar21 + 1;
                        IVar11 = IVar11 - 1;
                      } while (IVar11 != 0);
                      IVar11 = objc_stub::FUN_100914660(IVar8,&uStack_1a0,auStack_108,0x10);
                    } while (IVar11 != 0);
                  }
                  self_00 = (undefined1 *)0x0;
                }
                uVar19 = uVar19 + 1;
              } while (uVar19 != (uVar23 & 0xffff));
            }
            puVar15 = &uStack_140;
            FUN_1003cb22c(puVar15,&uStack_144);
            FUN_10006433c(&uStack_145);
            uVar16 = uRam0000000100cae4b8;
            if ((int)puVar15 == 0) {
              uVar25 = uRam0000000100cae4b8;
              _os_log_type_enabled(uRam0000000100cae4b8,0);
              if ((int)uVar25 != 0) {
                uStack_160 = (undefined4)_UNK_100930510;
                uStack_15c = uStack_144;
                __os_log_impl(0x100000000,uVar16,0,"addServiceDataToLocalSDP: SRH 0x%X",&uStack_160,
                              8);
              }
              uStack_160 = 0;
              uStack_15c = 0;
              uStack_158 = 0;
              uStack_156 = 0;
              uStack_154 = 0;
              uStack_152 = 0;
              FUN_100006ef8(&uStack_160,param_1 + 0xe0);
              IVar11 = objc_stub::FUN_1009124c0((ID)PTR__OBJC_CLASS___NSMutableArray_100bfcb08);
              uVar16 = _UNK_100930510;
              if ((uVar23 & 0xffff) != 0) {
                lVar20 = 0;
                uVar23 = uVar23 & 0xffff;
                do {
                  psVar2 = (short *)(uVar9 + lVar20 * 0x18);
                  sVar4 = *psVar2;
                  if (sVar4 == 0xd || sVar4 == 4) {
                    IVar12 = param_1;
                    FUN_10040c11c(param_1,psVar2 + 4);
                    if ((int)IVar12 != 0) {
                      IVar24 = objc_stub::FUN_10091b300
                                         ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,IVar12);
                      IVar24 = objc_stub::FUN_100914380(IVar11,IVar24);
                      uVar25 = uRam0000000100cae4b8;
                      if ((IVar24 & 1) == 0) {
                        uVar22 = uRam0000000100cae4b8;
                        _os_log_type_enabled(uRam0000000100cae4b8,0);
                        if ((int)uVar22 != 0) {
                          uStack_1c0 = (uint)uVar16;
                          iStack_1bc = (int)IVar12;
                          __os_log_impl(0x100000000,uVar25,0,
                                        "addServiceDataToLocalSDP: publishing PSM %d",&uStack_1c0,8)
                          ;
                        }
                        IVar24 = objc_stub::FUN_10091b300
                                           ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,IVar12);
                        objc_stub::FUN_1009117c0(IVar11,IVar24);
                        uVar25 = uRam0000000100cae4b8;
                        self = PTR__OBJC_CLASS___NSMutableDictionary_100bfcb18;
                        if (IVar8 == 0) {
                          uVar22 = uRam0000000100cae4b8;
                          _os_log_type_enabled(uRam0000000100cae4b8,0x10);
                          if ((int)uVar22 != 0) {
                            FUN_1008bcd60(auStack_1d0,(ulong)auStack_1d0 | 1,uVar25);
                          }
                        }
                        else {
                          IVar24 = objc_stub::FUN_100916d00(IVar8);
                          IVar12 = objc_stub::FUN_10091b300
                                             ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,IVar12);
                          IVar12 = objc_stub::FUN_100915960((ID)self,IVar24,IVar12);
                          self_01 = *(ID *)(param_1 + 0x120);
                          IVar24 = objc_stub::FUN_10091b280
                                             ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,
                                              (ulong)uStack_144);
                          objc_stub::FUN_100921880(self_01,IVar12,IVar24);
                        }
                        FUN_1000070cc();
                        FUN_10002f5ac();
                      }
                    }
                  }
                  lVar20 = lVar20 + 1;
                  uVar23 = uVar23 - 1;
                } while (uVar23 != 0);
              }
              FUN_100006ec0(IVar11,&uStack_160);
            }
            else {
              uVar25 = uRam0000000100cae4b8;
              _os_log_type_enabled(uRam0000000100cae4b8,0x10);
              if ((int)uVar25 != 0) {
                FUN_1008bcd24(puVar15,uVar16);
              }
            }
            uVar14 = (ulong)uStack_144;
LAB_10040bdec:
            FUN_10006b538(&uStack_145);
            goto LAB_10040bab8;
          }
          uVar25 = uRam0000000100cae4b8;
          _os_log_type_enabled(uRam0000000100cae4b8,0x10);
          if ((int)uVar25 != 0) {
            FUN_1008bcd98(uVar16);
          }
          goto LAB_10040bab4;
        }
        pcVar17 = "(serviceRecordData.length) > 0";
      }
      uVar22 = 0x628;
LAB_10040bec0:
                    /* WARNING: Subroutine does not return */
      FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Daemon/Server/XpcClassicConnection.mm"
                    ,uVar22,pcVar17);
    }
    uVar25 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0x10);
    if ((int)uVar25 != 0) {
      FUN_1008bcdcc(uVar16);
    }
  }
LAB_10040bab4:
  uVar14 = 0;
LAB_10040bab8:
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_88) {
    return uVar14;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
code_r0x00010040b7c4:
  if ((((byte)uVar6 & 2) == uVar5) || (uVar5 < 9 && (1 << (ulong)(uVar5 & 0x1f) & 0x160U) != 0)) {
    uVar23 = (ulong)((int)uVar23 - 1);
    iVar18 = iVar18 + -1;
  }
  uVar19 = (ulong)(iVar18 + 1U);
  if (((uint)uVar23 & 0xffff) <= (iVar18 + 1U & 0xffff)) goto LAB_10040b7fc;
  goto LAB_10040b760;
}

