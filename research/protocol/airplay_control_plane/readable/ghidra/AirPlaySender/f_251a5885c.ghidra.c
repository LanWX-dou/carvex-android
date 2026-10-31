/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a5885c
 * original code SHA256: 6bf53a913044028027050eec6bc9b79d046e8a3207380b52117b4aafb843ca11
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _apsession_PerformStage2StartTransaction(undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 local_30;
  undefined8 uStack_28;
  
  lVar1 = func_0x00025810ac50();
  if (*(int *)(lVar1 + 0xe0) == 5) {
    local_30 = param_1;
    uStack_28 = param_2;
    uVar2 = func_0x00025810d260(*(undefined8 *)(lVar1 + 0x78),
                                _apsession_ensureStartedInternalStage2StartTransaction,&local_30);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

