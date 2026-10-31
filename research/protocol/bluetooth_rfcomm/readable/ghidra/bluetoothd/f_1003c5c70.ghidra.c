/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c5c70
 * original code SHA256: 33d872df966ea57bc18b314900808444f592696196fc0f1f320fead0f476847b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003c5c70(char *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long lStack_38;
  
  bVar1 = *param_2;
  if ((bVar1 & 1) == 0) {
    return;
  }
  if ((param_2[1] >> 4 & 1) == 0) {
    return;
  }
  if ((((bVar1 & 2) == 0 ^ param_1[0xc]) & 1U) != 0) {
    return;
  }
  lStack_38 = 0;
  bVar2 = bVar1 >> 2;
  if (*param_1 == '\a') {
    if ((bVar1 < 0xf8) && (bVar2 != 1)) {
      pcVar4 = param_1;
      FUN_1003c136c(param_1,bVar2,&lStack_38);
      if ((int)pcVar4 == 0) {
        if (*(char *)(lStack_38 + 0xd) == '\x06') goto LAB_1003c5e50;
      }
      else {
        pcVar4 = param_1;
        FUN_1003c1404(param_1,bVar2,&lStack_38);
        if ((int)pcVar4 != 0) {
          iVar3 = 2;
          FUN_10000d938(2,0x32);
          if (iVar3 != 0) {
            FUN_10000d120("%! (%d)");
            uVar5 = 0x32;
            FUN_10000e9d4();
            uVar6 = uVar5;
            _os_log_type_enabled();
            if ((int)uVar6 != 0) {
              FUN_100105b50(uVar5);
            }
          }
          goto LAB_1003c5e50;
        }
        if (lStack_38 == 0) {
          FUN_1000f9438();
        }
      }
      *(undefined1 *)(lStack_38 + 0xd) = 3;
      *(byte *)(lStack_38 + 10) = bVar2;
      pcVar4 = param_1 + 6;
      FUN_1003c2314(pcVar4,bVar1 >> 3,*(undefined2 *)(lStack_38 + 0x10),
                    *(undefined2 *)(lStack_38 + 8));
      if ((int)pcVar4 == 0) {
        return;
      }
      iVar3 = 2;
      FUN_10000d938(2,0x32);
      if (iVar3 != 0) {
        FUN_10000d120("No registered server on DLCI %d, rejecting incoming link");
        uVar5 = 0x32;
        FUN_10000e9d4();
        uVar6 = uVar5;
        _os_log_type_enabled();
        if ((int)uVar6 != 0) {
          FUN_1008b4ec0(uVar5);
        }
      }
      *(undefined4 *)(lStack_38 + 0xa4) = 0x399;
      FUN_1003c16dc(lStack_38,0);
    }
    else {
      iVar3 = 2;
      FUN_10000d938(2,0x32);
      if (iVar3 != 0) {
        FUN_10000d120("%! (%d)");
        uVar5 = 0x32;
        FUN_10000e9d4();
        uVar6 = uVar5;
        _os_log_type_enabled();
        if ((int)uVar6 != 0) {
          FUN_100105b50(uVar5);
        }
      }
    }
  }
  else if ((*param_1 == '\x04') && (bVar1 < 4)) {
    iVar3 = 99;
    FUN_1003c5334(99,param_1,bVar2);
    if (iVar3 != 0) {
      return;
    }
    *param_1 = '\a';
    return;
  }
LAB_1003c5e50:
  FUN_1003c5334(0xf,param_1,bVar2);
  return;
}

