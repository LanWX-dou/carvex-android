/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005faeec
 * original code SHA256: e92123fb56a18b99af0dc2b02d9d5779ae2ea3ea4af8b761d14dd500f89f0eb1
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined * FUN_1005faeec(short *param_1,uint param_2)

{
  byte bVar1;
  undefined8 uVar2;
  code *pcVar3;
  ID IVar4;
  undefined8 uVar5;
  undefined *self;
  char *pcVar6;
  undefined2 *puVar7;
  undefined *self_00;
  uint uVar8;
  long lVar9;
  ulong unaff_x30;
  undefined2 auStack_70 [8];
  undefined2 auStack_60 [8];
  
  puVar7 = auStack_70;
  if (*param_1 == 0x4c || *param_1 == 0x4c00) {
    uVar8 = 3;
    lVar9 = 2;
  }
  else {
    if ((char)*param_1 != 'L') {
      self_00 = (undefined *)0x0;
      goto LAB_1005fb108;
    }
    uVar8 = 2;
    lVar9 = 1;
  }
  self_00 = PTR__OBJC_CLASS___NSMutableDictionary_100bfcb18;
  _objc_alloc_init();
  IVar4 = objc_stub::FUN_10091b300((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,0x4c);
  objc_stub::FUN_100921860((ID)self_00,IVar4,&cf_kCBMsgArgVID);
  objc_stub::FUN_100921860
            ((ID)self_00,&PTR__OBJC_CLASS___NSConstantIntegerNumber_100bf8710,&cf_kCBMsgArgVIDSource
            );
  bVar1 = *(byte *)((long)param_1 + lVar9);
  IVar4 = objc_stub::FUN_10091b260((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,(ulong)bVar1);
  objc_stub::FUN_100921860((ID)self_00,IVar4,&cf_CBCentralManagerScanOptionMatchingRuleTypeKey);
  uVar2 = uRam0000000100cae440;
  lVar9 = lVar9 + 1;
  if (bVar1 < 3) {
    if (bVar1 == 1) {
      if (uVar8 < param_2) {
        if (param_2 == 0x14) {
          IVar4 = objc_stub::FUN_100914bc0
                            ((ID)PTR__OBJC_CLASS___NSData_100bfcae0,(char *)((long)param_1 + lVar9),
                             0x10);
          objc_stub::FUN_100921860((ID)self_00,IVar4,&cf_ServiceUUIDHash);
        }
        else {
          self = PTR__OBJC_CLASS___NSString_100bfc8c8;
          _objc_alloc();
          IVar4 = objc_stub::FUN_1009185a0
                            ((ID)self,(char *)((long)param_1 + lVar9),(ulong)(param_2 - uVar8),4);
          if (IVar4 != 0) {
            objc_stub::FUN_100921860((ID)self_00,IVar4,&cf_kCBMsgArgModelIdentifier);
          }
        }
      }
      goto LAB_1005fb108;
    }
    if ((bVar1 != 2) ||
       (uVar5 = uRam0000000100cae440, _os_log_type_enabled(uRam0000000100cae440,0), (int)uVar5 == 0)
       ) goto LAB_1005fb108;
    auStack_60[0] = 0;
    pcVar6 = "Warning: Received Apple EIR 3rd party advertising data - not processed";
    puVar7 = auStack_60;
  }
  else {
    if (bVar1 == 3) {
      IVar4 = objc_stub::FUN_10091b260
                        ((ID)PTR__OBJC_CLASS___NSNumber_100bfc888,
                         (ulong)*(byte *)((long)param_1 + lVar9));
      objc_stub::FUN_100921860((ID)self_00,IVar4,&cf_kCBMsgArgColorID);
      goto LAB_1005fb108;
    }
    if ((bVar1 != 7) ||
       (uVar5 = uRam0000000100cae440, _os_log_type_enabled(uRam0000000100cae440,0), (int)uVar5 == 0)
       ) goto LAB_1005fb108;
    auStack_70[0] = 0;
    pcVar6 = "Warning: Received Apple EIR ProxPairing data - not processed";
  }
  __os_log_impl(0x100000000,uVar2,0,pcVar6,puVar7,2);
LAB_1005fb108:
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(0xc471,0x1005fb134);
    (*pcVar3)();
  }
  return self_00;
}

