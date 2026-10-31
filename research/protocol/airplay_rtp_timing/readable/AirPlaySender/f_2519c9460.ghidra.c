/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c9460
 * original code SHA256: b2ea0e85f0e863a9d0c1e6a4e107e8413b993717b31f1234eda3772fb9084931
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_APSRTPPacketHandlerCreate
          (undefined8 param_1,uint param_2,uint param_3,undefined8 *param_4,long *param_5)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined8 uVar5;
  long extraout_x8;
  long lVar6;
  long extraout_x9;
  ulong uVar7;
  long lVar8;
  undefined8 uVar9;
  undefined1 auVar10 [16];
  
  if (__MergedGlobals != -1) {
    func_0x0002580f48c0(&__MergedGlobals,&___block_literal_global);
  }
  lVar2 = func_0x000258106640(param_1,DAT_27097bd40,0x6a8,0);
  if (lVar2 == 0) {
    auVar10 = _OUTLINED_FUNCTION_2();
    func_0x000258109a30(auVar10._0_8_,auVar10._8_8_,0x196,0);
    if ((param_4 != (undefined8 *)0x0) && ((code *)param_4[1] != (code *)0x0)) {
      (*(code *)param_4[1])(*param_4);
    }
    lVar2 = 0;
    uVar3 = 0xffffe5b8;
    goto LAB_2519c96c8;
  }
  func_0x0002580f43c0(lVar2 + 0x10,0x6a8);
  *(uint *)(lVar2 + 0x18) = param_2;
  *(uint *)(lVar2 + 0x1c) = param_3;
  if (param_4 == (undefined8 *)0x0) {
    if ((param_2 & 1) == 0) goto LAB_2519c968c;
LAB_2519c9530:
    _OUTLINED_FUNCTION_2();
    func_0x000258109a30(0,extraout_x1,0x1a2,0);
    uVar3 = 0xffffe5cf;
  }
  else {
    uVar3 = *param_4;
    uVar9 = param_4[3];
    uVar5 = param_4[2];
    *(undefined8 *)(lVar2 + 0x28) = param_4[1];
    *(undefined8 *)(lVar2 + 0x20) = uVar3;
    *(undefined8 *)(lVar2 + 0x38) = uVar9;
    *(undefined8 *)(lVar2 + 0x30) = uVar5;
    if ((param_2 & 1) == 0) {
LAB_2519c968c:
      if ((param_2 >> 1 & 1) != 0) {
        _QueueInit(param_1,lVar2 + 0x680,*(int *)(lVar2 + 0x1c) + -1,"SeqQ");
        uVar3 = 0;
        *(undefined8 *)(lVar2 + 0x678) = 0;
        *(undefined8 *)(lVar2 + 0xa0) = 0;
        *(long *)(lVar2 + 0xa8) = lVar2 + 0xb0;
        goto LAB_2519c96c8;
      }
LAB_2519c9690:
      uVar3 = 0;
      goto LAB_2519c96c8;
    }
    if (param_4[2] == 0) goto LAB_2519c9530;
    if (param_3 < 2) {
      *(undefined8 *)(lVar2 + 0x60) = 0;
LAB_2519c955c:
      uVar7 = (ulong)(param_3 + 0x14);
      lVar4 = func_0x000258106450(param_1,uVar7 * 0x18,0x1020040f89cb87b,0);
      *(long *)(lVar2 + 0x40) = lVar4;
      if (lVar4 == 0) goto LAB_2519c9690;
      *(ulong *)(lVar2 + 0x48) = uVar7;
      func_0x0002580f43c0(lVar4,uVar7 * 0x18);
      uVar3 = func_0x00025810eca0(param_1,uVar7,lVar2 + 0x50);
      if ((int)uVar3 == 0) {
        if (param_3 + 0x14 != 0) {
          lVar8 = 0;
          lVar4 = 0;
          do {
            uVar3 = (**(code **)(lVar2 + 0x30))
                              (*(undefined8 *)(lVar2 + 0x20),
                               *(long *)(lVar2 + 0x40) + lVar4 * 0x18 + 8);
            if (((int)uVar3 != 0) ||
               (_OUTLINED_FUNCTION_1(), lVar6 = extraout_x8, *(long *)(extraout_x9 + 8) == 0)) {
              if ((_gLogCategory_APSRTPPacketHandler < 0x5b) &&
                 ((_gLogCategory_APSRTPPacketHandler != -1 ||
                  (iVar1 = func_0x000258101e40(&_gLogCategory_APSRTPPacketHandler,0x5a), iVar1 != 0)
                  ))) {
                _OUTLINED_FUNCTION_1();
                func_0x000258101eb0(&_gLogCategory_APSRTPPacketHandler,
                                    "OSStatus APSRTPPacketHandlerCreate(CFAllocatorRef, APSRTPPacketHandlerMode, uint32_t, const APSRTPPacketHandlerDelegate *, CFTypeRef *)"
                                    ,0x5a,
                                    "Unable to acquire transport buffer; err = %d, buf ptr %{ptr}\n"
                                   );
              }
              if ((int)uVar3 != 0) {
                _OUTLINED_FUNCTION_2();
                func_0x000258109a30(uVar3,extraout_x1_00,0x1c7,0);
                goto LAB_2519c9548;
              }
              lVar6 = *(long *)(lVar2 + 0x40);
            }
            func_0x00025810ecc0(*(undefined8 *)(lVar2 + 0x50),lVar6 + lVar4 * 0x18);
            lVar4 = lVar4 + 1;
            lVar8 = lVar8 + 0x18;
          } while (uVar7 * 0x18 - lVar8 != 0);
        }
        uVar3 = func_0x00025810eca0(param_1,uVar7,lVar2 + 0x58);
        if ((int)uVar3 == 0) goto LAB_2519c968c;
        auVar10 = _OUTLINED_FUNCTION_2();
        uVar5 = 0x1cf;
      }
      else {
        auVar10 = _OUTLINED_FUNCTION_2();
        uVar5 = 0x1be;
      }
    }
    else {
      uVar3 = func_0x00025810eca0(param_1,param_3 - 1,lVar2 + 0x60);
      if ((int)uVar3 == 0) {
        _QueueInit(param_1,lVar2 + 0x68,*(int *)(lVar2 + 0x1c) + -1,"LenQ");
        goto LAB_2519c955c;
      }
      auVar10 = _OUTLINED_FUNCTION_2();
      uVar5 = 0x1a8;
    }
    func_0x000258109a30(auVar10._0_8_,auVar10._8_8_,uVar5,0);
  }
LAB_2519c9548:
  func_0x0002580f5830(lVar2);
  lVar2 = 0;
LAB_2519c96c8:
  *param_5 = lVar2;
  return uVar3;
}

