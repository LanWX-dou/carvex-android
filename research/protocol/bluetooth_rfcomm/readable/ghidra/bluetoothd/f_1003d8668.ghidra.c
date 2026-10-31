/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003d8668
 * original code SHA256: af02597f09985ba968a52340c559a1cdb26e8f6dce5dd9ad52af23ab9836d07f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined2 * FUN_1003d8668(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  if ((param_1 == 0) || ((int)param_2 == 0)) {
    puVar2 = (undefined2 *)0x10;
    FUN_10000d0cc(0x10,0x11ad2b49);
    if (puVar2 != (undefined2 *)0x0) {
      *puVar2 = 0;
      *(undefined1 *)(puVar2 + 1) = 0;
      *(undefined4 *)(puVar2 + 2) = 0;
    }
  }
  else {
    puVar2 = (undefined2 *)0x28;
    FUN_10000d0cc(0x28,0x11ad2b49);
    if (puVar2 != (undefined2 *)0x0) {
      *puVar2 = 1;
      puVar2[3] = 0;
      *(undefined1 *)(puVar2 + 1) = 1;
      puVar2[2] = (short)param_2;
      puVar3 = puVar2 + 8;
      FUN_10006b6c0(puVar3,param_1,param_2,param_3);
      if ((int)puVar3 != 0) {
        iVar1 = 2;
        FUN_10000d938(2,0x30);
        if (iVar1 != 0) {
          FUN_10000d120("OI_MBUF_Wrap - InitCell failed %!");
          uVar4 = 0x30;
          FUN_10000e9d4();
          uVar5 = uVar4;
          _os_log_type_enabled();
          if ((int)uVar5 != 0) {
            FUN_10018f150(uVar4);
          }
        }
        FUN_1000bfd54(puVar2);
        FUN_1000110b8(puVar2);
        puVar2 = (undefined2 *)0x0;
      }
    }
  }
  return puVar2;
}

