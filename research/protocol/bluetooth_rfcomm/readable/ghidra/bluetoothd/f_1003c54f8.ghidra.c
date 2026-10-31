/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c54f8
 * original code SHA256: 150ee03470f4e3632c0d871a2da1881e231af01de1038a7b43d71675bad8daf0
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long FUN_1003c54f8(long param_1,undefined1 param_2,undefined8 param_3,undefined1 param_4)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  iVar1 = 0x3c3c20;
  FUN_1000c00c4(phone_fn_1003c3c20,*(undefined2 *)(param_1 + 2),0,param_3,0);
  if (iVar1 == 0) {
    lVar5 = 0;
    *(undefined1 *)(param_1 + 0x50) = param_4;
    *(undefined1 *)(param_1 + 0x51) = param_2;
    *(undefined8 *)(param_1 + 0x48) = param_3;
  }
  else {
    if (iVar1 == 0x19a) {
      puVar2 = (undefined8 *)0x20;
      FUN_10000d0cc(0x20,0x10200408eab821d);
      if (puVar2 != (undefined8 *)0x0) {
        *puVar2 = param_3;
        *(undefined1 *)(puVar2 + 1) = param_4;
        *(undefined1 *)((long)puVar2 + 9) = param_2;
        FUN_1003d84a8(puVar2 + 2,param_1 + 0x38);
        return 0;
      }
    }
    else {
      iVar1 = 2;
      FUN_10000d938(2,0x32);
      if (iVar1 != 0) {
        FUN_10000d120("Error sending data to L2CAP, beginning session shutdown to %:");
        uVar3 = 0x32;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_1008b4ec0(uVar3);
        }
      }
      puVar2 = (undefined8 *)0x20;
      FUN_10000d0cc(0x20,0x10200408eab821d);
      if (puVar2 != (undefined8 *)0x0) {
        *puVar2 = param_3;
        *(undefined1 *)(puVar2 + 1) = param_4;
        *(undefined1 *)((long)puVar2 + 9) = param_2;
        FUN_1003d84a8(puVar2 + 2,param_1 + 0x38);
        FUN_1003c518c(param_1,0);
        if ((int)param_1 == 0) {
          return param_1;
        }
        FUN_1003d84bc(puVar2 + 2);
        FUN_1000110b8(puVar2);
        return param_1;
      }
    }
    lVar5 = 0x6a;
  }
  return lVar5;
}

