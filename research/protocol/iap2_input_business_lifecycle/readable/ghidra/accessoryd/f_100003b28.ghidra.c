/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100003b28
 * original code SHA256: 62e660e3b33078677e756ef201631dacb87327b9060b54c797af3a6c6c65ef0a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x14 bytes */

ID ACCNavigationRouteGuidanceUpdateInfo::keyForType_(ID param_1,SEL param_2,unsigned_short param_3)

{
  code *pcVar1;
  int iVar2;
  undefined *puVar3;
  ulong unaff_x30;
  undefined4 local_30;
  uint local_2c;
  
  if (param_3 - 1 < 0x1a) {
    switch((uint)param_3) {
    default:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 0xb:
      break;
    case 0xc:
      break;
    case 0xd:
      break;
    case 0xe:
      break;
    case 0xf:
      break;
    case 0x10:
      break;
    case 0x11:
      break;
    case 0x12:
      break;
    case 0x13:
      break;
    case 0x14:
      break;
    case 0x15:
      break;
    case 0x16:
      break;
    case 0x17:
      break;
    case 0x18:
      break;
    case 0x19:
      break;
    case 0x1a:
    }
  }
  else {
    if (_gLogObjects == (undefined8 *)0x0 || _gNumLogObjects < 1) {
      puVar3 = PTR___os_log_default_10022bbb0;
      if (::_logObjectForModule_onceToken != -1) {
        param_1 = __ACCNavigationRouteGuidanceUpdateInfo_keyForType___cold_1();
        puVar3 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar3 = (undefined *)*_gLogObjects;
    }
    iVar2 = _os_log_type_enabled(puVar3,param_1,0);
    if (iVar2 != 0) {
      local_30 = (undefined4)DAT_1001b30b0;
      local_2c = (uint)param_3;
      __os_log_impl(0x100000000,param_1,0,
                    "[#Navigation] ERROR: Unknown RouteGuidnaceUpdate InfoType %d",&local_30,8);
    }
    param_1 = 0;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100003cc0);
    (*pcVar1)();
  }
  return param_1;
}

