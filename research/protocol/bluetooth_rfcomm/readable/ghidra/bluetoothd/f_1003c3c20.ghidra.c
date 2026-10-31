/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c3c20
 * original code SHA256: 5c468306359a0a7b3c6c5cc3a905721d20cd7f694fb779c281b880f72c86e4b6
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003c3c20(long param_1,long param_2,undefined8 param_3,long param_4)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  char cVar8;
  undefined8 uVar9;
  code *pcVar10;
  long *plVar11;
  ulong uStack_48;
  
  uStack_48 = 0;
  if ((int)param_4 != 0) {
    iVar3 = 2;
    FUN_10000d938(2,0x32);
    if (iVar3 != 0) {
      FUN_10000d120("RFCOMM Write failed %!");
      uVar4 = 0x32;
      FUN_10000e9d4();
      uVar9 = uVar4;
      _os_log_type_enabled();
      if ((int)uVar9 != 0) {
        FUN_10018f150(uVar4);
      }
    }
  }
  if (param_2 == 0) {
    FUN_1000f9438();
  }
  FUN_1003c18a4();
  if (param_1 == 0) {
    iVar3 = 2;
    FUN_10000d938(2,0x32);
    if (iVar3 != 0) {
      FUN_10000d120("RFCOMM session has gone away - freeing orphaned MBUF %lx");
      uVar4 = 0x32;
      FUN_10000e9d4();
      uVar9 = uVar4;
      _os_log_type_enabled();
      if ((int)uVar9 != 0) {
        FUN_10018f150(uVar4);
      }
    }
    FUN_1000c3bf8(param_2);
    return;
  }
  if (*(long *)(param_1 + 0x48) != param_2) {
    FUN_1000f9438();
  }
  *(undefined8 *)(param_1 + 0x48) = 0;
  FUN_1000c3bf8(param_2);
  cVar8 = *(char *)(param_1 + 0x50);
  cVar1 = *(char *)(param_1 + 0x51);
  if (cVar8 == '\x01') {
    lVar5 = param_1;
    FUN_1003c136c(param_1,cVar1,&uStack_48);
    if ((int)lVar5 != 0) {
      iVar3 = 2;
      FUN_10000d938(2,0x32);
      if (iVar3 == 0) {
        return;
      }
      FUN_10000d120("%! (%d)");
      uVar4 = 0x32;
      FUN_10000e9d4();
      uVar9 = uVar4;
      _os_log_type_enabled();
      if ((int)uVar9 == 0) {
        return;
      }
      FUN_10018f150(uVar4);
      return;
    }
    if ((int)param_4 == 0) {
      uVar9 = *(undefined8 *)(uStack_48 + 0x58);
      FUN_1003d891c(uVar9,*(undefined2 *)(uStack_48 + 0x10));
      if ((int)uVar9 == 0) {
        param_4 = 0;
      }
      else {
        uVar7 = uStack_48;
        FUN_1003c4c24();
        if ((uVar7 & 1) == 0) {
          *(undefined1 *)(uStack_48 + 0x60) = 1;
          return;
        }
        param_4 = param_1;
        FUN_1003c5674(param_1,cVar1,*(undefined8 *)(uStack_48 + 0x58),0,1);
        if ((int)param_4 == 0) {
          return;
        }
        if ((int)param_4 == 0x19a) {
          FUN_1000f9438();
          param_4 = 0x19a;
        }
      }
    }
  }
  plVar6 = (long *)(param_1 + 0x38);
  if ((long *)*plVar6 != plVar6) {
    FUN_1003d8540();
    plVar11 = plVar6 + -2;
    iVar3 = 0x3c3c20;
    FUN_1000c00c4(phone_fn_1003c3c20,*(undefined2 *)(param_1 + 2),0,*plVar11,0);
    if (iVar3 == 0) {
      *(short *)(param_1 + 0x50) = (short)plVar6[-1];
      *(long *)(param_1 + 0x48) = plVar6[-2];
    }
    else {
      FUN_1000c3bf8(*plVar11);
      iVar3 = 2;
      FUN_10000d938(2,0x32);
      if (iVar3 != 0) {
        FUN_10000d120("Write failed");
        uVar4 = 0x32;
        FUN_10000e9d4();
        uVar9 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar9 != 0) {
          FUN_10018f150(uVar4);
        }
      }
    }
    FUN_1000110b8(plVar11);
  }
  if (cVar8 == '\0') {
    if ((cVar1 != '\0') &&
       (FUN_1003c136c(param_1,cVar1,&uStack_48), uVar7 = uStack_48, (int)param_1 == 0)) {
      cVar8 = *(char *)(uStack_48 + 0xb);
      *(undefined1 *)(uStack_48 + 0xb) = 0;
      if (cVar8 == '\x0f') {
        cVar8 = *(char *)(uStack_48 + 0xd);
        if ((cVar8 != '\x06') && (cVar8 != '\t')) {
          FUN_1000f9438();
          cVar8 = *(char *)(uVar7 + 0xd);
        }
        if (cVar8 == '\t') {
          FUN_1003c16dc(uVar7,1);
        }
      }
      else if (cVar8 == 'c') {
        if (*(char *)(uStack_48 + 0xd) == '\b') {
          pcVar10 = *(code **)(uStack_48 + 0x48);
          uVar2 = *(undefined2 *)(uStack_48 + 8);
          FUN_1003c16dc(uStack_48,0);
          (*pcVar10)(uVar2,0,0x39f);
        }
        else if (*(char *)(uStack_48 + 0xd) == '\a') {
          *(undefined4 *)(uStack_48 + 0xa4) = 0x39f;
          FUN_1003c52cc(uStack_48,0);
        }
      }
    }
  }
  else {
    if (uStack_48 == 0) {
      FUN_1000f9438();
    }
    uVar7 = uStack_48;
    uVar9 = *(undefined8 *)(uStack_48 + 0x58);
    *(undefined8 *)(uStack_48 + 0x58) = 0;
    FUN_1000c42ec(uVar9);
    (**(code **)(uVar7 + 0x50))(*(undefined2 *)(uVar7 + 8),uVar9,param_4);
  }
  return;
}

