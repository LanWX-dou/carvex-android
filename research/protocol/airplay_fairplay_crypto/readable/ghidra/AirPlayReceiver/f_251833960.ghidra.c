/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251833960
 * original code SHA256: be33fc1ecaac4876c85f15625b83d78a7c39f3838b1344779eb75102e1af654e
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _APReceiverFairPlayHelperRemoveAllFPSessions(long param_1)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    lVar2 = func_0x0002581017d0();
    if (0 < lVar2) {
      lVar5 = 0;
      do {
        uVar3 = func_0x0002581017e0(*(undefined8 *)(param_1 + 0x10),lVar5);
        lVar4 = func_0x00025810a6f0(uVar3,&cfstringStruct_27610f030,0);
        if ((_gLogCategory_APReceiverFairPlayHelper < 0x1f) &&
           ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
            (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e),
            iVar1 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                              "void APReceiverFairPlayHelperRemoveAllFPSessions(APReceiverFairPlayHelperRef)"
                              ,0x200001e,"Deleting FP session ID %llu on connection close\n");
        }
        if (lVar4 != 0) {
          _h5eRUOOOhxuaBmELCqQZZEcx(lVar4);
        }
        lVar5 = lVar5 + 1;
      } while (lVar2 != lVar5);
    }
    if (*(long *)(param_1 + 0x10) != 0) {
      func_0x0002580f5830();
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
  }
  return;
}

