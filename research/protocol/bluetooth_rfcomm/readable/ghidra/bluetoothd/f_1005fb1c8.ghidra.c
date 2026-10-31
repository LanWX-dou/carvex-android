/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fb1c8
 * original code SHA256: ab0e90473e22593d888b78677fa633183f114e53088461bd1b7b34055cdc5a63
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_retain_x27 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x27 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_1005fb1c8(long param_1,long *param_2,uint param_3)

{
  undefined8 ***pppuVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ID IVar6;
  ID self;
  undefined *puVar7;
  ID IVar8;
  ulong uVar9;
  undefined8 *puVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  uint uVar13;
  undefined2 uVar14;
  undefined2 uVar15;
  uint uVar16;
  undefined8 auStack_100 [2];
  char cStack_e9;
  undefined8 **appuStack_e8 [2];
  char cStack_d1;
  undefined4 uStack_d0;
  uint uStack_cc;
  undefined2 uStack_c8;
  undefined2 uStack_c6;
  undefined2 uStack_c4;
  undefined2 uStack_c2;
  ushort uStack_c0;
  undefined2 uStack_be;
  undefined2 uStack_bc;
  ushort uStack_ba;
  undefined2 uStack_b8;
  undefined4 uStack_b6;
  undefined2 uStack_b2;
  undefined4 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  byte bStack_91;
  undefined2 *puStack_90;
  byte bStack_81;
  long *plStack_80;
  byte bStack_71;
  undefined8 uStack_70;
  
  uStack_70 = 0;
  bStack_71 = 0;
  plStack_80 = (long *)0x0;
  bStack_81 = 0;
  puStack_90 = (undefined2 *)0x0;
  bStack_91 = 0;
  uStack_a8 = 0;
  uStack_a0 = 0;
  FUN_100006ef8(&uStack_a8,param_1 + 0x228);
  plVar3 = (long *)(param_1 + 0x268);
  FUN_100006f84();
  plVar5 = plVar3;
  if (plVar3 == (long *)(ulong)param_3) {
    lVar4 = param_1 + 0x268;
    FUN_1000110dc(lVar4);
    plVar5 = param_2;
    _memcmp(param_2,lVar4,plVar3);
    if ((int)plVar5 == 0) {
      uVar13 = 0;
      goto LAB_1005fb700;
    }
  }
  if ((param_3 == 0) ||
     (plVar5 = param_2, FUN_10032541c(param_2,0xff,&bStack_81,&plStack_80), (int)plVar5 != 0)) {
LAB_1005fb26c:
    uVar16 = 0;
LAB_1005fb270:
    uVar13 = 1;
  }
  else {
    lVar4 = param_1 + 0x268;
    FUN_100006f84();
    plVar5 = (long *)0x0;
    if (lVar4 != 0) {
      plVar5 = (long *)(param_1 + 0x268);
      FUN_1000110dc();
      FUN_10032541c();
      if ((int)plVar5 != 0) goto LAB_1005fb26c;
    }
    if (bStack_81 != bStack_71) {
      uVar16 = 1;
      goto LAB_1005fb270;
    }
    plVar5 = plStack_80;
    _memcmp(plStack_80,uStack_70);
    uVar13 = (uint)((int)plVar5 != 0);
    uVar16 = 1;
  }
  FUN_1000071b8();
  (**(code **)(*plVar5 + 0x1b0))();
  if ((uVar16 & (uint)plVar5 & uVar13) == 1) {
    plVar3 = plStack_80;
    FUN_1005faeec(plStack_80,bStack_81);
    _NSLog(&cf_ReceivedEIRdict___);
    if (plVar3 != (long *)0x0) {
      IVar6 = objc_stub::FUN_100925de0((ID)plVar3,&cf_kCBMsgArgVID);
      self = objc_stub::FUN_100925de0((ID)plVar3,&cf_kCBMsgArgVIDSource);
      puVar7 = PTR__OBJC_CLASS___NSNumber_100bfc888;
      _objc_opt_class(PTR__OBJC_CLASS___NSNumber_100bfc888);
      IVar8 = IVar6;
      _objc_opt_isKindOfClass(IVar6,puVar7);
      if (((uint)IVar8 & (uint)(self != 0)) == 1) {
        puVar7 = PTR__OBJC_CLASS___NSNumber_100bfc888;
        _objc_opt_class(PTR__OBJC_CLASS___NSNumber_100bfc888);
        IVar8 = self;
        _objc_opt_isKindOfClass(self,puVar7);
        if ((IVar8 & 1) != 0) {
          IVar8 = objc_stub::FUN_1009256c0(IVar6);
          IVar6 = objc_stub::FUN_100925620(self);
          uVar2 = uRam0000000100cae440;
          uVar9 = uRam0000000100cae440;
          _os_log_type_enabled(uRam0000000100cae440,0);
          if ((uVar9 & 1) != 0) {
            FUN_10010aa84(appuStack_e8,param_1);
            pppuVar1 = (undefined8 ***)appuStack_e8[0];
            if (-1 < cStack_d1) {
              pppuVar1 = appuStack_e8;
            }
            uStack_d0 = (undefined4)_UNK_1009357b8;
            uStack_cc = (uint)pppuVar1;
            uStack_c8 = (undefined2)((ulong)pppuVar1 >> 0x20);
            uStack_c6 = (undefined2)((ulong)pppuVar1 >> 0x30);
            uStack_c4 = 0x400;
            uStack_c2 = (undefined2)IVar6;
            uStack_c0 = (ushort)(IVar6 >> 0x10);
            uStack_be = 0x400;
            uStack_bc = (undefined2)IVar8;
            uStack_ba = (ushort)(IVar8 >> 0x10);
            uStack_b8 = 0x400;
            uStack_b6 = 0;
            uStack_b2 = 0x400;
            uStack_b0 = 0;
            __os_log_impl(0x100000000,uVar2,0,
                          "setEIRData %{public}s deviceId information: vidSrc 0x%x vid 0x%x pid 0x%x version 0x%x"
                          ,&uStack_d0,0x24);
            if (cStack_d1 < '\0') {
              __ZdlPv(appuStack_e8[0]);
            }
          }
          FUN_1005ed7d0(param_1,IVar6,IVar8,0,0);
        }
      }
      IVar8 = objc_stub::FUN_100925de0((ID)plVar3,&cf_kCBMsgArgColorID);
      if (IVar8 != 0) {
        puVar7 = PTR__OBJC_CLASS___NSNumber_100bfc888;
        _objc_opt_class(PTR__OBJC_CLASS___NSNumber_100bfc888);
        IVar6 = IVar8;
        _objc_opt_isKindOfClass(IVar8,puVar7);
        if ((IVar6 & 1) != 0) {
          IVar8 = objc_stub::FUN_100925620(IVar8);
          FUN_1005fa8c8(param_1,IVar8);
        }
      }
      IVar8 = objc_stub::FUN_100925de0((ID)plVar3,&cf_kCBMsgArgModelIdentifier);
      if (IVar8 != 0) {
        puVar7 = PTR__OBJC_CLASS___NSString_100bfc8c8;
        _objc_opt_class(PTR__OBJC_CLASS___NSString_100bfc8c8);
        _objc_opt_isKindOfClass(IVar8,puVar7);
        if ((IVar8 & 1) != 0) {
          _objc_retainAutorelease();
          IVar8 = objc_stub::FUN_10090cba0(IVar8);
          _strlen();
          puVar10 = auStack_100;
          FUN_1001ec44c(puVar10,IVar8);
          _memmove();
          *(undefined1 *)((long)puVar10 + IVar8) = 0;
          __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_
                    (param_1 + 0x200,auStack_100);
          if (cStack_e9 < '\0') {
            __ZdlPv(auStack_100[0]);
          }
        }
      }
    }
  }
  FUN_1000072d0(&uStack_d0,param_2,param_3);
  FUN_100010b6c(param_1 + 0x268,&uStack_d0);
  uStack_d0 = 0xb9d988;
  uStack_cc = 1;
  if (CONCAT26(uStack_c2,CONCAT24(uStack_c4,CONCAT22(uStack_c6,uStack_c8))) != 0) {
    FUN_100007228();
  }
  if (param_3 == 0) goto LAB_1005fb700;
  FUN_10032541c(param_2,0x10,&bStack_91,&puStack_90);
  uVar2 = uRam0000000100cae440;
  uVar16 = (uint)bStack_91;
  if (((int)param_2 != 0) || (bStack_91 == 0)) {
    uVar9 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,0x10);
    if ((int)uVar9 != 0) {
      uStack_d0 = 0x4000400;
      uStack_c8 = 0x400;
      uStack_c6 = (undefined2)param_3;
      uStack_c4 = (undefined2)(param_3 >> 0x10);
      uStack_c2 = 0x400;
      uStack_c0 = (ushort)bStack_71;
      uStack_be = 0;
      uStack_bc = 0x400;
      uStack_ba = (ushort)bStack_81;
      uStack_b8 = 0;
      uStack_cc = uVar16;
      __os_log_error_impl(0x100000000,uVar2,0x10,
                          "Invalid newDeviceIdDataLength:%d, dataLength:%d, oldManufacturerDataLength:%d, newManufacturerDataLength:%d skipping setDeviceId"
                          ,&uStack_d0,0x1a);
    }
    goto LAB_1005fb700;
  }
  if (puStack_90 == (undefined2 *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Server/core/Device.mm"
                  ,0x1af6,"(uint8_t *)newDeviceIdData");
  }
  if (bStack_91 < 2) {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Server/core/Device.mm"
                  ,0x1af9,"bool BT::Device::setEIRData(uint8_t *, uint8_t)");
    uVar14 = 0;
LAB_1005fb6b4:
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Server/core/Device.mm"
                  ,0x1afa,"bool BT::Device::setEIRData(uint8_t *, uint8_t)");
    uVar15 = 0;
LAB_1005fb6d0:
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Server/core/Device.mm"
                  ,0x1afb,"bool BT::Device::setEIRData(uint8_t *, uint8_t)");
    uVar11 = 0;
LAB_1005fb6ec:
    uVar12 = 0;
  }
  else {
    uVar14 = *puStack_90;
    if (bStack_91 < 4) goto LAB_1005fb6b4;
    uVar15 = puStack_90[1];
    if (bStack_91 < 6) goto LAB_1005fb6d0;
    uVar11 = puStack_90[2];
    if (uVar16 < 8) goto LAB_1005fb6ec;
    uVar12 = puStack_90[3];
  }
  FUN_1005ed7d0(param_1,uVar14,uVar15,uVar11,uVar12);
LAB_1005fb700:
  FUN_100006ec0(&uStack_a8);
  return uVar13;
}

