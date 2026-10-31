/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13db70
 * original code SHA256: 620c8dc735aeaa863f2ae255e9d4c885146f7204091b2d27fb33eaf9e3cd2eb8
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 iap2Connect(int *param_1,char *param_2)

{
  undefined8 uVar1;
  
  if (DAT_00171468 != (CIpodLib *)0x0) {
    uVar1 = CIpodLib::connect(DAT_00171468,param_1,param_2);
    return uVar1;
  }
  return 0xffffffff;
}

