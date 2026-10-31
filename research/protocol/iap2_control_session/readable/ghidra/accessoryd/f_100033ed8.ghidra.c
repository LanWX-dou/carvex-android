/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100033ed8
 * original code SHA256: 0c6fea9d4958cb0a92934289129b57674f60c55d8eaf925119bfe8701777de6f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


int _iAP2LinkGetBuffSize(undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  uVar1 = (uint)param_1;
  iVar2 = _iAP2FSMGetBuffSize();
  iVar3 = _iAP2TimeGetBuffSize(uVar1 + 2 & 0xff);
  iVar4 = _iAP2TimeSyncGetBuffSize();
  iVar5 = _iAP2BuffPoolGetBuffSize(0,0,0);
  if (uVar1 < 0x81) {
    iVar6 = _iAP2BuffPoolGetBuffSize(1,param_2,0x80);
    if (uVar1 < 0x80) {
      uVar1 = 0x7f;
    }
    iVar7 = _iAP2BuffPoolGetBuffSize(2,0xffff,uVar1 + 1);
    iVar8 = _iAP2ListArrayGetBuffSize(param_1,8);
    iVar9 = _iAP2ListArrayGetBuffSize(param_1,8);
    iVar2 = iVar2 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8 + iVar9 + 0x268;
    iVar3 = 5;
    do {
      iVar4 = _iAP2ListArrayGetBuffSize(0xff,8);
      iVar2 = iVar4 + iVar2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    return iVar2;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkGetBuffSize_cold_1();
}

