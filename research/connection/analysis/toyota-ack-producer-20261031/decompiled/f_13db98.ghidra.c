/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13db98
 * original code SHA256: d58938fd0c2385e0610f1f83527940f3c6dfec086c7e70cec6b00f0b0eb8a546
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 iap2Disconnect(int *param_1)

{
  if ((-1 < *param_1) && (DAT_00171468 != (CIpodLib *)0x0)) {
    CIpodLib::disconnect(DAT_00171468,param_1);
    return 0;
  }
  return 0;
}

