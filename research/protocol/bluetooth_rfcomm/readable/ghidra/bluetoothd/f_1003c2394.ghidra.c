/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2394
 * original code SHA256: 50d7725247246ccd3e2b7aa9d005673cedb7b71a100ce29f9bec1edd0305cae9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


char * FUN_1003c2394(undefined8 param_1,long *param_2)

{
  char *pcVar1;
  uint uVar2;
  
  if (iRam0000000100cade68 != 0) {
    uVar2 = (uint)((ulong)param_1 >> 8) & 0xffffff;
    if ((uVar2 < *pbRam0000000100cadd68) &&
       (pcVar1 = (char *)(lRam0000000100c38308 + (ulong)uVar2 * 0x58), *pcVar1 != '\0')) {
      FUN_1003c136c(pcVar1,(uint)param_1 & 0xff,param_2);
      if ((int)pcVar1 == 0) {
        uVar2 = 0x39f;
        if (*(char *)(*param_2 + 0xd) != '\t') {
          uVar2 = 0;
        }
        pcVar1 = (char *)(ulong)uVar2;
      }
    }
    else {
      pcVar1 = (char *)0x394;
    }
    return pcVar1;
  }
  return (char *)0x198;
}

