/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13e3e0
 * original code SHA256: f8dc70e7a5e17a696ade1ab9b13e10b453c14e9d1ee46113f57a89dad9ca718e
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 ipod_BT_spp_data_pro(int param_1,int param_2,char *param_3)

{
  undefined8 uVar1;
  
  if (DAT_00171468 != (CIpodLib *)0x0) {
    uVar1 = CIpodLib::ipod_BT_spp_data_pro(DAT_00171468,param_1,param_2,param_3);
    return uVar1;
  }
  return 0xffffffff;
}

