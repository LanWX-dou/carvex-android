/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003010ac
 * original code SHA256: e6d03c1e3b6ba9f00db8e0c3e6de366593e7cc240b97ef567f280f63d99fb9d1
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003010ac(long param_1,undefined2 param_2,int param_3)

{
  long lVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  int *piVar6;
  undefined8 uStack_48;
  undefined2 *puStack_40;
  undefined2 uStack_32;
  
  uStack_32 = (undefined2)param_1;
  FUN_10029ead0();
  uStack_48 = 0;
  if (param_1 == 0) {
    iVar2 = 2;
    FUN_10000d938(2,0x18);
    if (iVar2 != 0) {
      FUN_10000d120("RFCOMM connect confirm called for bogus link handle %x");
      uVar3 = 0x18;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_10018f150(uVar3);
      }
    }
  }
  else if (param_3 == 0) {
    piVar6 = (int *)(param_1 + 0xb0);
    *(undefined2 *)(param_1 + 0x48) = param_2;
    *(undefined4 *)(param_1 + 0xcc) = 2;
    if (*piVar6 != 0) {
      FUN_1000609fc();
      *piVar6 = 0;
    }
    iVar2 = *(int *)(param_1 + 0x98);
    lVar5 = 0x18;
    FUN_1003d7a1c();
    lVar1 = 0;
    if (iVar2 != 0) {
      lVar1 = 2;
    }
    puStack_40 = &uStack_32;
    uStack_48 = CONCAT62(uStack_48._2_6_,2);
    iVar2 = 0x301248;
    FUN_10006135c(&LAB_100301248,&uStack_48,*(undefined2 *)(lVar5 + lVar1),piVar6);
    if (iVar2 != 0) {
      iVar2 = 2;
      FUN_10000d938(2,0x18);
      if (iVar2 != 0) {
        FUN_10000d120("Register connect timeout handler failed %!\n");
        uVar3 = 0x18;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_10018f150(uVar3);
        }
      }
    }
  }
  else {
    iVar2 = 2;
    FUN_10000d938(2,0x18);
    if (iVar2 != 0) {
      FUN_10000d120("OBEX server RFCOMM connection failed: %!");
      uVar3 = 0x18;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_10018f150(uVar3);
      }
    }
    *(undefined4 *)(param_1 + 0xcc) = 0;
    if (*(long *)(param_1 + 8) != 0) {
      FUN_1000110b8();
      *(undefined8 *)(param_1 + 8) = 0;
    }
  }
  return;
}

