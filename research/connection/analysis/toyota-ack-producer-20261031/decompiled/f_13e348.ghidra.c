/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13e348
 * original code SHA256: 96b4982a09e52653ce9a5ca3321447bc642563c21fc5ab92bb7ede0d11b80c0c
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ipod_bt_spp_state_change(undefined4 param_1)

{
  if (DAT_00171468 != (CIpodLib *)0x0) {
    CIpodLib::ipod_bt_spp_state_change(DAT_00171468,param_1);
    return;
  }
  return;
}

