/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c1964
 * original code SHA256: 0c1bb76aaac5341ff68284928e58abf1a83c789c17982e18258418e983a7c6bc
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


char * FUN_1003c1964(int *param_1)

{
  char *pcVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  
  if (iRam0000000100cade68 == 0) {
    iVar2 = 2;
    FUN_10000d938(2,0x32);
    if (iVar2 != 0) {
      FUN_10000d120("OI_Rfcomm_GetSessionByAddr");
      uVar3 = 0x32;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_1008b924c(uVar3);
      }
    }
  }
  else {
    uVar5 = (ulong)*pbRam0000000100cadd68;
    if (uVar5 != 0) {
      lVar6 = 0;
      do {
        pcVar1 = (char *)(lRam0000000100c38308 + lVar6 * 0x58);
        if ((*pcVar1 != '\0') &&
           (*param_1 == *(int *)(pcVar1 + 6) && (short)param_1[1] == *(short *)(pcVar1 + 10))) {
          return pcVar1;
        }
        lVar6 = lVar6 + 1;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
  return (char *)0x0;
}

