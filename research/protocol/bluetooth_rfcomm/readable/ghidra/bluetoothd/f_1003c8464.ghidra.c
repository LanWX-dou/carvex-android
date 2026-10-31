/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c8464
 * original code SHA256: 61bdc0c4a1fd4bf24f0c1d8c2dbff2ebd721e1737631d4d0cc9acff19224faaa
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 phone_fn_1003c8464(long param_1,uint param_2,uint param_3,undefined2 param_4,int param_5)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  long lVar4;
  
  FUN_1003c18a4();
  if (param_1 == 0) {
    iVar1 = 2;
    FUN_10000d938(2,0x32);
    if (iVar1 != 0) {
      FUN_10000d120("No session found with CID %d");
      uVar2 = 0x32;
      FUN_10000e9d4();
      uVar3 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar3 != 0) {
        FUN_10018f150(uVar2);
      }
    }
  }
  else if ((param_2 & 0x7f) << 1 < 0x3e) {
    lVar4 = param_1;
    FUN_1003c136c();
    if ((int)lVar4 == 0) {
      iVar1 = 0;
      if (cRam000000000000000d == '\0') {
        if (param_3 <= uRam0000000000000010) {
          uRam0000000000000010 = (ushort)param_3;
        }
        if (param_5 == 0) {
          param_4 = 0;
          *(undefined1 *)(param_1 + 0x2c) = 0;
        }
        else {
          *(undefined1 *)(param_1 + 0x2c) = 1;
          uRam0000000000000012 = param_4;
          FUN_1003c4c88();
          if (iVar1 != 0) {
            iVar1 = 2;
            FUN_10000d938(2,0x32);
            if (iVar1 == 0) {
              return 0x72;
            }
            FUN_10000d120("%! (%d)");
            uVar2 = 0x32;
            FUN_10000e9d4();
            uVar3 = uVar2;
            _os_log_type_enabled();
            if ((int)uVar3 == 0) {
              return 0x72;
            }
            FUN_10018f150(uVar2);
            return 0x72;
          }
        }
        cRam000000000000000d = 5;
        uRam000000000000000e = (char)param_4;
        return 0;
      }
    }
    else {
      iVar1 = 2;
      FUN_10000d938(2,0x32);
      if (iVar1 != 0) {
        FUN_10000d120("Could not find link for DLCI (%d)");
        uVar2 = 0x32;
        FUN_10000e9d4();
        uVar3 = uVar2;
        _os_log_type_enabled();
        if ((int)uVar3 != 0) {
          FUN_10018f150(uVar2);
        }
      }
    }
  }
  else {
    iVar1 = 2;
    FUN_10000d938(2,0x32);
    if (iVar1 != 0) {
      FUN_10000d120("%! (%d)");
      uVar2 = 0x32;
      FUN_10000e9d4();
      uVar3 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar3 != 0) {
        FUN_10018f150(uVar2);
      }
    }
  }
  return 0x72;
}

