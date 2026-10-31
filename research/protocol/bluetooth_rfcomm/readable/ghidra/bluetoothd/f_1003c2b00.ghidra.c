/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2b00
 * original code SHA256: b0792e1c66fb6050501b6f10ac5bdde67a389ec8a9259f4ca428bb797ddca1d9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


char * FUN_1003c2b00(char *param_1,long *param_2,char *param_3,char param_4,undefined8 param_5,
                    uint param_6,undefined2 *param_7,undefined8 param_8)

{
  uint uVar1;
  undefined2 uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  char *pcVar8;
  char *pcVar9;
  uint uVar10;
  char *pcStack_70;
  char *pcStack_68;
  
  pcStack_70 = (char *)0x0;
  if ((iRam0000000100cade68 == 0) && (pcVar9 = param_1, FUN_1003c2624(), (int)pcVar9 != 0)) {
    return pcVar9;
  }
  if (param_2 != (long *)0x0) {
    if ((param_2[1] == 0) && (FUN_1000f9438(), param_2[1] == 0)) {
      return (char *)0x65;
    }
    if ((*param_2 == 0) && (FUN_1000f9438(), *param_2 == 0)) {
      return (char *)0x65;
    }
    if ((param_1 != (char *)0x0) && (param_3 != (char *)0x0)) {
      uVar1 = *puRam0000000100c38320;
      uVar10 = (uint)param_5;
      pcVar9 = (char *)0x65;
      if ((uVar10 != 0) && (uVar10 <= param_6 || param_6 == 0)) {
        if ((byte)(param_4 - 0x1fU) < 0xe2) {
          pcVar9 = (char *)0x38e;
        }
        else {
          pcVar5 = param_3;
          FUN_1003c1964();
          pcVar8 = pcVar5;
          pcStack_68 = pcVar5;
          if (pcVar5 == (char *)0x0) {
            pcVar9 = param_3;
            FUN_1003c1f78(param_3,&pcStack_68);
            pcVar8 = pcStack_68;
            if ((int)pcVar9 != 0) goto LAB_1003c2ce4;
            uVar2 = *(undefined2 *)(param_3 + 4);
            *(undefined4 *)(pcStack_68 + 6) = *(undefined4 *)param_3;
            *(undefined2 *)(pcStack_68 + 10) = uVar2;
            pcVar9 = pcStack_68;
            FUN_1003c1d40(pcStack_68,param_5);
            if ((int)pcVar9 != 0) goto LAB_1003c2ce4;
          }
          pcVar9 = pcVar8;
          FUN_1003c14dc(pcVar8,(pcVar8[0xc] | param_4 << 1) ^ 1,&pcStack_70);
          pcVar3 = pcStack_70;
          if ((int)pcVar9 == 0) {
            *(char **)(pcStack_70 + 0x48) = param_1;
            *(long **)(pcStack_70 + 0x28) = param_2;
            *(short *)(pcStack_70 + 0x10) = (short)param_5;
            if (param_7 != (undefined2 *)0x0) {
              *param_7 = *(undefined2 *)(pcStack_70 + 8);
            }
            uVar2 = 0;
            if (uVar10 != 0) {
              uVar2 = (undefined2)(param_6 / uVar10);
            }
            *(undefined2 *)(pcStack_70 + 0xa0) = uVar2;
            *(undefined8 *)(pcStack_70 + 0x30) = param_8;
            if ((pcVar5 != (char *)0x0) && (*pcVar8 == '\a')) {
              pcVar9 = pcStack_70;
              FUN_1003c20b8();
              if ((int)pcVar9 != 0) {
                *(int *)(pcVar3 + 0xa4) = (int)pcVar9;
                FUN_1003c16dc(pcVar3,1);
                return pcVar9;
              }
              return pcVar9;
            }
            return (char *)0x0;
          }
        }
      }
LAB_1003c2ce4:
      iVar4 = 2;
      FUN_10000d938(2,0x32);
      if (iVar4 != 0) {
        FUN_10000d120("OI_RFCOMM_Connect failed");
        uVar6 = 0x32;
        FUN_10000e9d4();
        uVar7 = uVar6;
        _os_log_type_enabled();
        if ((int)uVar7 != 0) {
          FUN_1008b8180(pcVar9,uVar6);
        }
      }
      if (iRam0000000100cade68 == 0) {
        return pcVar9;
      }
      if (uVar1 < *puRam0000000100c38320) {
        FUN_1003c1eac();
        return pcVar9;
      }
      if (*puRam0000000100c38320 == 0) {
        FUN_1003c2d6c();
        return pcVar9;
      }
      return pcVar9;
    }
  }
  FUN_1000f9438();
  return (char *)0x65;
}

