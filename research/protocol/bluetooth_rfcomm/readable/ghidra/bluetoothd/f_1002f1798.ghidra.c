/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1002f1798
 * original code SHA256: 3bb8e309238004c89e450bfab5e621f141acdfc09a168d5852ef25d1d9732a3e
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * phone_fn_1002f1798(ulong param_1,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined1 *puVar7;
  
  if (iRam0000000100cadde0 == 0) {
LAB_1002f18e4:
    puVar7 = (undefined1 *)0x198;
  }
  else {
    lVar5 = 0;
    lVar6 = 8;
    do {
      if ((uint)*(ushort *)(lRam0000000100c29f50 + lVar5 * 0x30) == (uint)param_1) {
        uVar3 = param_1;
        FUN_1002f1948();
        if ((int)uVar3 == 8) goto LAB_1002f184c;
        if (*(char *)(lRam0000000100c29f50 + (uVar3 & 0xffffffff) * 0x30 + 0x1c) == '\x02') {
          if (param_2 == 0) {
            puVar7 = &LAB_1002f19e8;
            FUN_1003c2df0(&LAB_1002f19e8,param_1,0);
            FUN_1002f1bf8(uVar3);
            return puVar7;
          }
          puVar7 = &LAB_1002f19e8;
          FUN_1003c2df0(&LAB_1002f19e8,param_1,1);
          if ((int)puVar7 == 0) {
            return puVar7;
          }
          iVar1 = 2;
          FUN_10000d938(2,0x10);
          if (iVar1 != 0) {
            FUN_10000d120("OI_RFCOMM_Accept failed: %! %d\n");
            uVar2 = 0x10;
            FUN_10000e9d4();
            uVar4 = uVar2;
            _os_log_type_enabled();
            if ((int)uVar4 != 0) {
              FUN_1008b4ec0(uVar2);
            }
          }
          FUN_1002f1bf8(uVar3);
          return puVar7;
        }
        goto LAB_1002f18e4;
      }
      lVar5 = lVar5 + 1;
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
    iVar1 = 2;
    FUN_10000d938(2,0x10);
    if (iVar1 != 0) {
      FUN_10000d120("Could not find addr for device %d");
      uVar2 = 0x10;
      FUN_10000e9d4();
      uVar4 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_1008b4ec0(uVar2);
      }
    }
    FUN_1002f1948(param_1);
LAB_1002f184c:
    puVar7 = (undefined1 *)0x70a;
  }
  return puVar7;
}

