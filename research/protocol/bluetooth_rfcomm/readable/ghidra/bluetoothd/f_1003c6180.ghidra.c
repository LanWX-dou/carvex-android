/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6180
 * original code SHA256: bf7b9c47e6e0d212da8f49f51cc058e2d7fd4205ea8f96b64a5b5ed7dbdb643f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003c6180(char *param_1,byte *param_2)

{
  short sVar1;
  byte bVar2;
  undefined2 uVar3;
  byte bVar4;
  code *pcVar5;
  int iVar6;
  undefined8 uVar7;
  long lVar8;
  char *pcVar9;
  undefined8 uVar10;
  ulong unaff_x30;
  long lStack_28;
  
  bVar2 = *param_2;
  if (((bVar2 & 1) != 0) && ((param_2[1] >> 4 & 1) != 0)) {
    lStack_28 = 0;
    if (((bVar2 & 2) == 0) == (bool)param_1[0xc]) {
      bVar4 = bVar2 >> 2;
      if (bVar2 < 0xf8 && bVar4 != 1) {
        if (*param_1 == '\a') {
          if (3 < bVar2) {
            pcVar9 = param_1;
            FUN_1003c136c(param_1,bVar4,&lStack_28);
            if ((int)pcVar9 != 0) {
              iVar6 = 2;
              FUN_10000d938(2,0x32);
              if (iVar6 == 0) {
                return;
              }
              FUN_10000d120("DLCI %d not found");
              uVar7 = 0x32;
              FUN_10000e9d4();
              uVar10 = uVar7;
              _os_log_type_enabled();
              if ((int)uVar10 == 0) {
                return;
              }
              FUN_100105b50(uVar7);
              return;
            }
            iVar6 = 99;
            FUN_1003c5334(99,param_1,bVar4);
            if (*(char *)(lStack_28 + 0xd) == '\x06') {
              return;
            }
            if (*(char *)(lStack_28 + 0xd) == '\x05') {
              *(undefined1 *)(lStack_28 + 0xd) = 7;
              if (iVar6 == 0) {
                return;
              }
              iVar6 = 2;
              FUN_10000d938(2,0x32);
              if (iVar6 != 0) {
                FUN_10000d120("RFCOMM send command failed with result : %!");
                uVar7 = 0x32;
                FUN_10000e9d4();
                uVar10 = uVar7;
                _os_log_type_enabled();
                if ((int)uVar10 != 0) {
                  FUN_100105b50(uVar7);
                }
              }
              *(undefined4 *)(lStack_28 + 0xa4) = 0x3a5;
              FUN_1003c52cc(lStack_28,0);
              return;
            }
            pcVar5 = *(code **)(lStack_28 + 0x48);
            if (pcVar5 == (code *)0x0) {
              return;
            }
            *(undefined1 *)(lStack_28 + 0xd) = 8;
            if (iVar6 == 0) {
              return;
            }
            uVar3 = *(undefined2 *)(lStack_28 + 8);
            FUN_1003c16dc(lStack_28,0);
            (*pcVar5)(uVar3,0,0x39f);
            return;
          }
          lVar8 = 0x32;
          FUN_1003d7a1c();
          sVar1 = 0x1e;
          if (*(short *)(lVar8 + 10) != 0) {
            sVar1 = *(short *)(lVar8 + 10);
          }
          *param_1 = '\b';
          FUN_1003c518c(param_1,sVar1);
        }
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          FUN_1003c5334(99,param_1,bVar4);
          return;
        }
                    /* WARNING: Does not return */
        pcVar5 = (code *)SoftwareBreakpoint(0xc471,0x1003c62d4);
        (*pcVar5)();
      }
      iVar6 = 2;
      FUN_10000d938(2,0x32);
      if (iVar6 != 0) {
        FUN_10000d120("%! (%d)");
        uVar7 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar7;
        _os_log_type_enabled();
        if ((int)uVar10 != 0) {
          FUN_100105b50(uVar7);
        }
      }
    }
    else {
      iVar6 = 2;
      FUN_10000d938(2,0x32);
      if (iVar6 != 0) {
        FUN_10000d120("%! (%d)");
        uVar7 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar7;
        _os_log_type_enabled();
        if ((int)uVar10 != 0) {
          FUN_100105b50(uVar7);
        }
      }
    }
  }
  return;
}

