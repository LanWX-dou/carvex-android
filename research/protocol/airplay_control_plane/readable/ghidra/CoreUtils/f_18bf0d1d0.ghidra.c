/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf0d1d0
 * original code SHA256: 7a1d1e2a33d04e1f0c677ecea89f94818dc322a7a0b235fbaa0f9908716b5056
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _HTTPMessageGetOrCopyFormVariable
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  code *pcVar1;
  int iVar2;
  ulong unaff_x30;
  
  iVar2 = _URLGetOrCopyVariable
                    (*(long *)(param_1 + 0x20a8),
                     *(long *)(param_1 + 0x20a8) + *(long *)(param_1 + 0x20b0),param_2,param_3,
                     param_4,param_5,0);
  if (iVar2 == 0) {
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x18bf0d264);
    (*pcVar1)();
  }
  _URLGetOrCopyVariable
            (*(long *)(param_1 + 0x2148),*(long *)(param_1 + 0x2148) + *(long *)(param_1 + 0x2150),
             param_2,param_3,param_4,param_5,0);
  return;
}

