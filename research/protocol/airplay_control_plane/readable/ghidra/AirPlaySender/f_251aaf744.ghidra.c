/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aaf744
 * original code SHA256: ac9faa9cec2cffe382ff78fe90fd7ae357f058677663eab1b685c52d510b5d26
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _coreUtilsPairing_PerformSetup
              (undefined8 param_1,long param_2,int param_3,int param_4,undefined8 param_5,
              undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9,
              undefined8 param_10,undefined8 param_11,undefined8 param_12)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  
  lVar4 = func_0x00025810ac50();
  *(undefined1 *)(lVar4 + 0x3a) = 0;
  if (param_4 == 0) {
    if (*(char *)(lVar4 + 0x39) == '\0') {
      uVar6 = 0;
      if (param_3 != 0) {
        uVar6 = 2;
      }
    }
    else {
      uVar6 = 3;
      if (*(char *)(lVar4 + 0x3b) != '\0') {
        uVar6 = 5;
      }
    }
  }
  else {
    uVar6 = 4;
  }
  if (param_3 == 0) {
    iVar2 = _coreUtilsPairing_performSetupInternal
                      (param_1,&cfstringStruct_276136450,uVar6,*(undefined1 *)(lVar4 + 0x40),0,0,
                       param_7,param_8,param_9,param_10,param_12);
    iVar3 = 0x30ed3;
    if (iVar2 != 0x30ed1) {
      iVar3 = iVar2;
    }
    iVar2 = 0;
    if (iVar3 != 0) {
      _coreUtilsPairing_PerformSetup_cold_1(iVar3);
      iVar2 = iVar3;
    }
  }
  else if (param_2 == 0) {
    uVar5 = func_0x00025810d530();
    iVar3 = _coreUtilsPairing_sendPairingRequest
                      (param_1,uVar6,0x70707374,0,0,0,0,0,uVar5,param_11,0,param_12);
    iVar2 = 0x30ed1;
    if (iVar3 != 0) {
      iVar2 = iVar3;
    }
  }
  else {
    iVar3 = _coreUtilsPairing_performSetupInternal
                      (param_1,param_2,uVar6,*(undefined1 *)(lVar4 + 0x40),param_5,param_6,param_7,
                       param_8,param_9,param_10,param_12);
    if ((iVar3 == 0x30ed1) && (*(char *)(lVar4 + 0x38) == '\0')) {
      uVar5 = func_0x00025810d530();
      iVar3 = _coreUtilsPairing_sendPairingRequest
                        (param_1,uVar6,0x70707374,0,0,0,0,0,uVar5,param_11,0,0);
      bVar1 = iVar3 == 0;
    }
    else {
      bVar1 = iVar3 == 0x30f16;
    }
    iVar2 = 0x30ed1;
    if (!bVar1) {
      iVar2 = iVar3;
    }
  }
  return iVar2;
}

