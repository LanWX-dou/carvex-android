/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a587a0
 * original code SHA256: 400afcb299ac4cc3ac9a2bc497c9d22fccef823bdbede7654f8d8d3883a744cc
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_apsession_PerformStage1StartTransaction
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  long *local_40;
  long local_38;
  
  lVar1 = func_0x00025810ac50();
  local_40 = &local_38;
  local_38 = 0;
  if (*(int *)(lVar1 + 0xe0) == 5) {
    local_58 = param_1;
    uStack_50 = param_2;
    local_48 = param_3;
    uVar2 = func_0x00025810d260(*(undefined8 *)(lVar1 + 0x78),
                                _apsession_ensureStartedInternalStage1StartTransaction,&local_58);
    if ((int)uVar2 == 0) {
      *param_4 = local_38;
    }
    else {
      func_0x000258109a30(uVar2,"apsession_PerformStage1StartTransaction",0x1027,0);
      if (local_38 != 0) {
        func_0x0002580f5830();
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

