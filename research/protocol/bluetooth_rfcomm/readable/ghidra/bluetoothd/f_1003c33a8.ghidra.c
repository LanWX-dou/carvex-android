/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c33a8
 * original code SHA256: 5050227e84019dcb001a8b100bb4cc2e835318ba388d9efa7a8bfe4c2c7cebcf
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined4 *
FUN_1003c33a8(undefined4 *param_1,undefined8 param_2,undefined4 *param_3,uint param_4,uint param_5,
             uint param_6,undefined2 *param_7,undefined2 *param_8,undefined8 param_9,int param_10)

{
  uint uVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  long lVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined2 uStack_90;
  undefined4 uStack_8e;
  undefined2 uStack_8a;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined4 *puStack_70;
  undefined4 *puStack_68;
  
  puStack_70 = (undefined4 *)0x0;
  puStack_68 = (undefined4 *)0x0;
  if ((iRam0000000100cade68 != 0) || (puVar6 = param_1, FUN_1003c2624(), (int)puVar6 == 0)) {
    puVar6 = param_3;
    FUN_1003c1f78(param_3,&puStack_68);
    puVar3 = puStack_68;
    if ((int)puVar6 == 0) {
      uVar2 = *(undefined2 *)(param_3 + 1);
      puVar9 = (undefined4 *)((long)puStack_68 + 6);
      *puVar9 = *param_3;
      *(undefined2 *)((long)puStack_68 + 10) = uVar2;
      *(undefined8 *)(puStack_68 + 8) = 0;
      FUN_1003d7a1c(0x28);
      iVar8 = 5;
      if (0x7f < param_5) {
        iVar8 = 6;
      }
      uVar1 = iVar8 + param_5;
      if ((uVar1 & 0xffff) < 0x81) {
        uStack_90 = 0x80;
      }
      else {
        lVar5 = 0x28;
        FUN_1003d7a1c();
        uStack_90 = (short)uVar1;
        if ((uint)*(ushort *)(lVar5 + 8) < (uVar1 & 0xffff)) {
          lVar5 = 0x28;
          FUN_1003d7a1c();
          uStack_90 = *(undefined2 *)(lVar5 + 8);
        }
      }
      uStack_8e = 0x1388ffff;
      uStack_8a = 0x308;
      uStack_80 = 0;
      uStack_78 = 0;
      uStack_88 = 0;
      puVar6 = (undefined4 *)0x3;
      FUN_100369364(3,&uStack_90,puVar9,&LAB_1003c3a94,&LAB_1003c4180,&DAT_1003c3a08,
                    (undefined1 *)((long)puVar3 + 2),&UNK_100934970);
      if ((int)puVar6 == 0) {
        *param_8 = *(undefined2 *)((long)puVar3 + 2);
        *(bool *)(puVar3 + 3) = param_10 != 0;
        puVar6 = puVar3;
        if (param_10 == 0) {
          FUN_1003c1404(puVar3,(param_4 & 0x7f) << 1,&puStack_70);
        }
        else {
          FUN_1003c14dc();
        }
        *(bool *)(puVar3 + 3) = param_10 != 0;
        if ((int)puVar6 == 0) {
          *(undefined4 **)(puStack_70 + 0x12) = param_1;
          *(undefined8 *)(puStack_70 + 10) = param_2;
          *(short *)(puStack_70 + 4) = (short)param_5;
          if (param_7 != (undefined2 *)0x0) {
            *param_7 = *(undefined2 *)(puStack_70 + 2);
          }
          uVar2 = 0;
          if (param_5 != 0) {
            uVar2 = (undefined2)(param_6 / param_5);
          }
          *(undefined2 *)(puStack_70 + 0x28) = uVar2;
          *(undefined8 *)(puStack_70 + 0xc) = param_9;
          FUN_1003c4c88();
          *(undefined1 *)puVar3 = 7;
          puVar6 = puStack_70;
        }
        else {
          *(undefined1 *)puVar3 = 0;
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 != 0) {
            FUN_10000d120("OI_RFCOMM_createChannelForFastConnect allocate link failed");
            uVar4 = 0x32;
            FUN_10000e9d4();
            uVar7 = uVar4;
            _os_log_type_enabled();
            if ((int)uVar7 != 0) {
              FUN_1008b8180(puVar6,uVar4);
            }
          }
        }
      }
      else {
        *(undefined1 *)puVar3 = 0;
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 != 0) {
          FUN_10000d120("OI_RFCOMM_createChannelForFastConnect create L2CAP channel failed");
          uVar4 = 0x32;
          FUN_10000e9d4();
          uVar7 = uVar4;
          _os_log_type_enabled();
          if ((int)uVar7 != 0) {
            FUN_1008b8180(puVar6,uVar4);
          }
        }
      }
    }
    else {
      iVar8 = 2;
      FUN_10000d938(2,0x32);
      if (iVar8 != 0) {
        FUN_10000d120("OI_RFCOMM_createChannelForFastConnect Allocate Session failed");
        uVar4 = 0x32;
        FUN_10000e9d4();
        uVar7 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar7 != 0) {
          FUN_1008b8180(puVar6,uVar4);
        }
      }
    }
  }
  return puVar6;
}

