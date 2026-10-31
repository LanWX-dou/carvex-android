/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4dc0c
 * original code SHA256: 7104b148aeabbbfa91bd26edaf623183a0386a364b6c1451a15aebde0cf3da90
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _HTTPHeader_InitRequestV(long param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = _SNPrintF(param_1,0x2000,"%s%n %n%V%n %s\r\n");
  if (uVar1 - 0x2000 < 0xffffe001) {
    uVar2 = 0xffffe5a1;
  }
  else {
    uVar2 = 0;
    *(long *)(param_1 + 0x2018) = param_1;
    *(undefined8 *)(param_1 + 0x2020) = 0;
    *(long *)(param_1 + 0x2030) = param_1;
    *(undefined8 *)(param_1 + 0x2038) = 0;
    *(ulong *)(param_1 + 0x2000) = (ulong)uVar1;
  }
  *(undefined4 *)(param_1 + 0x211c) = uVar2;
  return;
}

