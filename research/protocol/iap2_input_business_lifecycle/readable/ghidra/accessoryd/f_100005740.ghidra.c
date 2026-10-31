/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100005740
 * original code SHA256: cef6e7262d518f292d54fd64cd417296d47f201958493609171460c8a90f3f01
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iAP2LinkGetSessionForService(long param_1,uint param_2)

{
  undefined1 *puVar1;
  ulong uVar2;
  undefined1 uVar3;
  long lVar4;
  
  if ((param_1 == 0) || (uVar2 = (ulong)*(byte *)(param_1 + 0x1a4), uVar2 == 0)) {
    uVar3 = 0;
  }
  else {
    lVar4 = 0;
    uVar3 = 0;
    do {
      puVar1 = (undefined1 *)(param_1 + 0x1b8 + lVar4 * 4);
      if (param_2 == (byte)puVar1[1]) {
        uVar3 = *puVar1;
      }
      lVar4 = lVar4 + 1;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return uVar3;
}

