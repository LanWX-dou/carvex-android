/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100005f38
 * original code SHA256: faf5f3e11f6cd836318747c7be008dc29f85c2da2c959a2ea89dfe3692b0d434
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 _iAP2LinkCurPckChksumSize(long param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (*(char *)(param_1 + 0xd5) == '\x02') {
    uVar1 = 2;
  }
  return uVar1;
}

