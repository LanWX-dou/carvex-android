/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003cbd74
 * original code SHA256: 39631b0a90b17b15a9fa192d4f2314010fed4b66300a5309aa8f6af2a8cd9d28
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_1003cbd74(long param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined8 param_5,
             undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 *puVar1;
  ushort uVar2;
  int iVar3;
  undefined8 uVar4;
  byte *pbVar5;
  undefined8 uVar6;
  ulong uVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  undefined4 uStack_50;
  undefined8 uStack_4c;
  
  uVar7 = (ulong)uRam0000000100c383c8;
  if (uVar7 != 0) {
    lVar9 = 0;
    lVar10 = lRam0000000100c383d0;
    do {
      if (*(long *)(lRam0000000100c383d0 + lVar9 * 0x20) == param_1) {
        puVar1 = (undefined8 *)(lRam0000000100c383d0 + lVar9 * 0x20);
        iVar3 = 0;
        FUN_10000d938(0,0x36);
        if (iVar3 != 0) {
          uVar8 = *puVar1;
          FUN_10000d120(
                       "SDP record for remote device with hci handle: %p already exists, let\'s update the record"
                       );
          uVar4 = 0x36;
          FUN_10000e9d4();
          uVar6 = uVar4;
          _os_log_type_enabled();
          if ((int)uVar6 != 0) {
            FUN_10000ea80();
            uStack_50 = (undefined4)_UNK_100930b20;
            uStack_4c = uVar6;
            __os_log_impl(0x100000000,uVar4,0," %{public}s",&uStack_50,0xc,param_7,param_8,uVar8);
          }
        }
        if (0x111d < param_2) {
          if (param_2 == 0x111e) {
            *(undefined2 *)(lVar10 + 0x14) = param_3;
            *(undefined2 *)(lVar10 + 0x16) = param_4;
            return 0;
          }
          if (param_2 != 0x112e) {
            if (param_2 != 0x1134) {
              return 0;
            }
            *(undefined2 *)(lVar10 + 0x1a) = param_3;
            return 0;
          }
          *(undefined2 *)(lVar10 + 0x10) = param_3;
          *(undefined2 *)(lVar10 + 0x12) = param_4;
          return 0;
        }
        if (param_2 - 0x110eU < 2) {
          *(undefined2 *)(lVar10 + 0xc) = param_3;
          *(undefined2 *)(lVar10 + 0xe) = param_4;
          return 0;
        }
        if (param_2 != 0x110c) {
          return 0;
        }
        *(undefined2 *)(lVar10 + 8) = param_3;
        *(undefined2 *)(lVar10 + 10) = param_4;
        return 0;
      }
      lVar9 = lVar9 + 1;
      lVar10 = lVar10 + 0x20;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  iVar3 = 0;
  FUN_10000d938(0,0x36);
  if (iVar3 != 0) {
    lVar9 = param_1;
    FUN_10000d120("SDP record for remote device with hci handle: %p does not exist, creating one");
    uVar4 = 0x36;
    FUN_10000e9d4();
    uVar6 = uVar4;
    _os_log_type_enabled();
    if ((int)uVar6 != 0) {
      FUN_10000ea80();
      uStack_50 = (undefined4)_UNK_100930b20;
      uStack_4c = uVar6;
      __os_log_impl(0x100000000,uVar4,0," %{public}s",&uStack_50,0xc,param_7,param_8,lVar9);
    }
  }
  uVar2 = uRam0000000100c383c8;
  pbVar5 = (byte *)0x28;
  FUN_1003d7a1c();
  if (*pbVar5 <= uVar2) {
    FUN_1000f9438();
  }
  uVar2 = uRam0000000100c383c8;
  pbVar5 = (byte *)0x28;
  FUN_1003d7a1c();
  lVar9 = lRam0000000100c383d0;
  if (uVar2 == *pbVar5) {
    iVar3 = 2;
    FUN_10000d938(2,0x36);
    if (iVar3 != 0) {
      FUN_10000d120(
                   "No room to add another SDP remote record for connection %p. Total number of SDP remote records : %d"
                   );
      uVar4 = 0x36;
      FUN_10000e9d4();
      uVar6 = uVar4;
      _os_log_type_enabled();
      if ((int)uVar6 != 0) {
        FUN_1008b4ec0(uVar4);
      }
    }
    uVar6 = 0x68;
  }
  else {
    uVar7 = (ulong)uRam0000000100c383c8;
    *(long *)(lRam0000000100c383d0 + uVar7 * 0x20) = param_1;
    if (param_2 < 0x111e) {
      if (param_2 - 0x110eU < 2) {
        lVar9 = lVar9 + uVar7 * 0x20;
        *(undefined2 *)(lVar9 + 0xc) = param_3;
        *(undefined2 *)(lVar9 + 0xe) = param_4;
      }
      else if (param_2 == 0x110c) {
        lVar9 = lVar9 + uVar7 * 0x20;
        *(undefined2 *)(lVar9 + 8) = param_3;
        *(undefined2 *)(lVar9 + 10) = param_4;
      }
    }
    else if (param_2 == 0x111e) {
      lVar9 = lVar9 + uVar7 * 0x20;
      *(undefined2 *)(lVar9 + 0x14) = param_3;
      *(undefined2 *)(lVar9 + 0x16) = param_4;
    }
    else if (param_2 == 0x112e) {
      lVar9 = lVar9 + uVar7 * 0x20;
      *(undefined2 *)(lVar9 + 0x10) = param_3;
      *(undefined2 *)(lVar9 + 0x12) = param_4;
    }
    else if (param_2 == 0x1134) {
      *(undefined2 *)(lVar9 + uVar7 * 0x20 + 0x1a) = param_3;
    }
    uVar6 = 0;
    uRam0000000100c383c8 = uRam0000000100c383c8 + 1;
  }
  return uVar6;
}

