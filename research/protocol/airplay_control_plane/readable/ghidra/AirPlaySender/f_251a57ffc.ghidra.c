/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a57ffc
 * original code SHA256: 3eb8c10150e916621e36532d96fdce2e9a2b6e2cd8e4a1966c8ea4d29fd15a95
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _apsession_EnsureStarted(undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  undefined8 local_30;
  undefined8 uStack_28;
  
  lVar1 = func_0x00025810ac50();
  local_30 = param_1;
  uStack_28 = param_2;
  func_0x00025810d260(*(undefined8 *)(lVar1 + 0x78),_apsession_ensureStartedInternal,&local_30);
  return;
}

