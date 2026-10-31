/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100005f4c
 * original code SHA256: a2fc5e0f6c1b80f4c3be57e4541f7edc279ab70c2b2e4cd9df85aaa1353aa3d9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 _iAP2LinkCurPckHdrSize(long param_1)

{
  undefined4 uVar1;
  
  uVar1 = 9;
  if (*(char *)(param_1 + 0xd5) == '\x02') {
    uVar1 = 10;
  }
  return uVar1;
}

