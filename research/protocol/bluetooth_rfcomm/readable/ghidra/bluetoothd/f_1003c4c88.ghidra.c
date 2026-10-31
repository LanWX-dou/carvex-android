/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c4c88
 * original code SHA256: 4c91605d8cf0fcb0e43917364b8c5af9f6c740eb2e568758096e75a45868f86b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c4c88(long param_1)

{
  ulong *puVar1;
  ushort uVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  uVar2 = *(ushort *)(param_1 + 0xa0);
  if (uVar2 == 0) {
    *(undefined1 *)(param_1 + 0xa2) = 0;
  }
  else {
    uVar6 = (uint)uVar2;
    if (0xfe < uVar2) {
      uVar6 = 0xff;
    }
    *(char *)(param_1 + 0xa2) = (char)uVar6;
    *(undefined1 *)(param_1 + 0xa3) = 0;
    uVar3 = (ulong)(uVar6 * 0x18);
    FUN_10000d0cc(uVar3,0x10300407b68707e);
    *(ulong *)(param_1 + 0x68) = uVar3;
    if (uVar3 == 0) {
      return 0x6a;
    }
    if (*(char *)(param_1 + 0xa2) != '\0') {
      uVar3 = 0;
      do {
        uVar4 = (ulong)*(ushort *)(param_1 + 0x10);
        FUN_10000d0cc(uVar4,0x9a058afc);
        lVar5 = *(long *)(param_1 + 0x68);
        puVar1 = (ulong *)(lVar5 + uVar3 * 0x18);
        *puVar1 = uVar4;
        *(undefined2 *)(puVar1 + 1) = 0;
        if (uVar4 == 0) {
          if (uVar3 != 0) {
            lVar5 = 0;
            do {
              FUN_1000110b8(*(undefined8 *)(*(long *)(param_1 + 0x68) + lVar5 * 0x18));
              lVar5 = lVar5 + 1;
              uVar3 = uVar3 - 1;
            } while (uVar3 != 0);
            lVar5 = *(long *)(param_1 + 0x68);
          }
          FUN_1000110b8(lVar5);
          *(undefined1 *)(param_1 + 0xa2) = 0;
          return 0x6a;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(byte *)(param_1 + 0xa2));
    }
  }
  *(undefined1 *)(param_1 + 0xe) = 0;
  return 0;
}

