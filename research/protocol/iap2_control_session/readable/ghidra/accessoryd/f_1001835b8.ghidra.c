/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001835b8
 * original code SHA256: 36c4c90ea158777ae855815fde17d8ec863fde0a6debbae0990e2c3409927ebe
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_sessionFileTransfer_init(long param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  
  bVar1 = false;
  if (param_1 != 0) {
    uVar2 = _iAP2ListArrayGetBuffSize(0x80,0x18);
    puVar6 = (undefined8 *)_malloc_type_malloc(0x18,0x80040d6874129);
    *(undefined8 **)(param_1 + 0x1b8) = puVar6;
    uVar7 = _malloc_type_malloc(uVar2,0xc772888d);
    *puVar6 = uVar7;
    iVar3 = _iAP2ListArrayInit(uVar7,0x80,0x18);
    uVar7 = _malloc_type_malloc(uVar2,0xd6562240);
    puVar6[1] = uVar7;
    iVar4 = _iAP2ListArrayInit(uVar7,0x80,0x18);
    uVar7 = _malloc_type_malloc(uVar2,0xb7de34d2);
    puVar6[2] = uVar7;
    iVar5 = _iAP2ListArrayInit(uVar7,0x80,0x18);
    bVar1 = (iVar5 == 0 && iVar4 == 0) && iVar3 == 0;
  }
  return bVar1;
}

