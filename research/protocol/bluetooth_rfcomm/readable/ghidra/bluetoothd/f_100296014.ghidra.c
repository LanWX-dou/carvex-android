/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100296014
 * original code SHA256: e7531ab07d5dc010d135c1740fccf30a068964bfe3b3dae45c2ab23964c8c939
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_100296014(undefined2 *param_1,undefined8 param_2,undefined **param_3)

{
  int iVar1;
  undefined2 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 uVar5;
  
  puVar2 = param_1;
  FUN_100295f6c();
  if (puVar2 == (undefined2 *)0x0) {
    FUN_1000f9438();
    if ((int)param_3 == 0) goto LAB_1002960a8;
LAB_10029604c:
    iVar1 = 2;
    FUN_10000d938(2,0xf);
    if (iVar1 != 0) {
      FUN_10000d120("RFCOMM connection failed %!\n");
      uVar3 = 0xf;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_10018f150(uVar3);
      }
    }
    *puVar2 = 0;
    FUN_100295f6c();
    if (param_1 == (undefined2 *)0x0) goto LAB_10029610c;
    uVar5 = 0;
  }
  else {
    if ((int)param_3 != 0) goto LAB_10029604c;
LAB_1002960a8:
    param_3 = &PTR_LAB_100ba3230;
    FUN_1003228d8(&PTR_LAB_100ba3230,puVar2 + 0xe);
    if ((int)param_3 != 0) {
      iVar1 = 2;
      FUN_10000d938(2,0xf);
      if (iVar1 != 0) {
        FUN_10000d120("OI_DEVMGR_RegisterScoApplication failed %!\n");
        uVar3 = 0xf;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_10018f150(uVar3);
        }
      }
    }
    FUN_100295f6c();
    if (param_1 == (undefined2 *)0x0) goto LAB_10029610c;
    uVar5 = 3;
  }
  *(undefined1 *)(param_1 + 0x11) = uVar5;
LAB_10029610c:
  FUN_100296340(*puVar2,param_3,param_2);
  return;
}

