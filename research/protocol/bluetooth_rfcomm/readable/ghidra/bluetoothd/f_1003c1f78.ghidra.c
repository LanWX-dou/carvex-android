/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c1f78
 * original code SHA256: 4815bd64a7d76b102a91267de4123cd30efb617dc0d9bff9903b8debb6c08c97
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c1f78(int *param_1,long *param_2)

{
  char *pcVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  lVar2 = lRam0000000100c38308;
  if (iRam0000000100cade68 == 0) {
    return 0x198;
  }
  if (*pbRam0000000100cadd68 != 0) {
    uVar4 = 0;
    do {
      pcVar1 = (char *)(lVar2 + uVar4 * 0x58);
      *param_2 = (long)pcVar1;
      if ((*pcVar1 != '\0') &&
         (*param_1 == *(int *)(pcVar1 + 6) && (short)param_1[1] == *(short *)(pcVar1 + 10))) {
        return 0x38d;
      }
      uVar4 = uVar4 + 1;
      uVar3 = (ulong)*pbRam0000000100cadd68;
    } while (uVar4 < uVar3);
    if (*pbRam0000000100cadd68 != 0) {
      lVar2 = 0;
      lVar5 = lRam0000000100c38308;
      do {
        pcVar1 = (char *)(lRam0000000100c38308 + lVar2 * 0x58);
        if (*pcVar1 == '\0') {
          pcVar1[0x50] = '\0';
          pcVar1[0x51] = '\0';
          pcVar1[0x52] = '\0';
          pcVar1[0x53] = '\0';
          pcVar1[0x54] = '\0';
          pcVar1[0x55] = '\0';
          pcVar1[0x56] = '\0';
          pcVar1[0x57] = '\0';
          pcVar1[0x38] = '\0';
          pcVar1[0x39] = '\0';
          pcVar1[0x3a] = '\0';
          pcVar1[0x3b] = '\0';
          pcVar1[0x3c] = '\0';
          pcVar1[0x3d] = '\0';
          pcVar1[0x3e] = '\0';
          pcVar1[0x3f] = '\0';
          pcVar1[0x30] = '\0';
          pcVar1[0x31] = '\0';
          pcVar1[0x32] = '\0';
          pcVar1[0x33] = '\0';
          pcVar1[0x34] = '\0';
          pcVar1[0x35] = '\0';
          pcVar1[0x36] = '\0';
          pcVar1[0x37] = '\0';
          pcVar1[0x48] = '\0';
          pcVar1[0x49] = '\0';
          pcVar1[0x4a] = '\0';
          pcVar1[0x4b] = '\0';
          pcVar1[0x4c] = '\0';
          pcVar1[0x4d] = '\0';
          pcVar1[0x4e] = '\0';
          pcVar1[0x4f] = '\0';
          pcVar1[0x40] = '\0';
          pcVar1[0x41] = '\0';
          pcVar1[0x42] = '\0';
          pcVar1[0x43] = '\0';
          pcVar1[0x44] = '\0';
          pcVar1[0x45] = '\0';
          pcVar1[0x46] = '\0';
          pcVar1[0x47] = '\0';
          pcVar1[0x18] = '\0';
          pcVar1[0x19] = '\0';
          pcVar1[0x1a] = '\0';
          pcVar1[0x1b] = '\0';
          pcVar1[0x1c] = '\0';
          pcVar1[0x1d] = '\0';
          pcVar1[0x1e] = '\0';
          pcVar1[0x1f] = '\0';
          pcVar1[0x10] = '\0';
          pcVar1[0x11] = '\0';
          pcVar1[0x12] = '\0';
          pcVar1[0x13] = '\0';
          pcVar1[0x14] = '\0';
          pcVar1[0x15] = '\0';
          pcVar1[0x16] = '\0';
          pcVar1[0x17] = '\0';
          pcVar1[0x28] = '\0';
          pcVar1[0x29] = '\0';
          pcVar1[0x2a] = '\0';
          pcVar1[0x2b] = '\0';
          pcVar1[0x2c] = '\0';
          pcVar1[0x2d] = '\0';
          pcVar1[0x2e] = '\0';
          pcVar1[0x2f] = '\0';
          pcVar1[0x20] = '\0';
          pcVar1[0x21] = '\0';
          pcVar1[0x22] = '\0';
          pcVar1[0x23] = '\0';
          pcVar1[0x24] = '\0';
          pcVar1[0x25] = '\0';
          pcVar1[0x26] = '\0';
          pcVar1[0x27] = '\0';
          pcVar1[8] = '\0';
          pcVar1[9] = '\0';
          pcVar1[10] = '\0';
          pcVar1[0xb] = '\0';
          pcVar1[0xc] = '\0';
          pcVar1[0xd] = '\0';
          pcVar1[0xe] = '\0';
          pcVar1[0xf] = '\0';
          pcVar1[0] = '\0';
          pcVar1[1] = '\0';
          pcVar1[2] = '\0';
          pcVar1[3] = '\0';
          pcVar1[4] = '\0';
          pcVar1[5] = '\0';
          pcVar1[6] = '\0';
          pcVar1[7] = '\0';
          *pcVar1 = '\x01';
          *(undefined2 *)(lVar5 + 0x2c) = 0x101;
          FUN_1003d848c(lVar5 + 0x38);
          FUN_1003d848c(lVar5 + 0x10);
          *(undefined1 *)(lVar5 + 0x52) = 0;
          *param_2 = (long)pcVar1;
          *piRam0000000100c38320 = *piRam0000000100c38320 + 1;
          return 0;
        }
        lVar2 = lVar2 + 1;
        lVar5 = lVar5 + 0x58;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  return 0x68;
}

