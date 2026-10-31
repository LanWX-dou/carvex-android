/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518892fc
 * original code SHA256: 05bb68e7cf9343b5c68c710345df6e7403e06e0e2b6d4d9e56352795e9fad6f6
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251889384) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __FPSetup2ResponseCompletionHandler(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  code *pcVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  ulong uVar11;
  long local_78 [7];
  
  lVar6 = *(long *)(param_1 + 0x25c8);
  lVar10 = *(long *)(lVar6 + 0x28);
  lVar7 = *(long *)(param_1 + 0x25d0);
  uVar11 = *(ulong *)(param_1 + 0x25d8);
  local_78[5] = 0;
  local_78[2] = 0;
  local_78[1] = 0;
  local_78[4] = 0;
  local_78[3] = 0;
  local_78[0] = 0;
  uVar8 = *(undefined8 *)(param_1 + 0x25e0);
  uVar9 = *(undefined8 *)(lVar10 + 0xa0);
  lVar2 = func_0x000258109150(uVar9);
  puVar5 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 0x20);
  pcVar4 = (code *)*puVar5;
  if ((pcVar4 == (code *)0x0) || (pcVar4 == (code *)0x0)) {
    uVar8 = 0xffffce12;
LAB_2518894a4:
    uVar9 = 0x165d;
LAB_2518894b0:
    func_0x000258109a30(uVar8,"_FPSetup2ResponseCompletionHandler",uVar9,0);
LAB_2518894b8:
    if (lVar7 == 0) goto LAB_2518894c4;
  }
  else {
    uVar8 = (*pcVar4)((ulong)puVar5 & 0xffffffffffff | 0x9879000000000000,uVar9,uVar8,local_78);
    if ((int)uVar8 != 0) goto LAB_2518894a4;
    if (local_78[0] == 0) {
      uVar8 = 0x165e;
LAB_251889538:
      func_0x000258109a30(0,"_FPSetup2ResponseCompletionHandler",uVar8,0);
LAB_251889560:
      if ((_gLogCategory_AirPlayReceiverServer < 0x3d) &&
         ((_gLogCategory_AirPlayReceiverServer != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverServer,0x200003c), iVar1 != 0))
         )) {
        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverServer,
                            "void _FPSetup2ResponseCompletionHandler(HTTPMessageRef)",0x200003c,
                            "### FP-Setup2 Failed: %d, %#m\n");
      }
      goto LAB_2518894b8;
    }
    if ((uVar11 & 0xffffffc0) == 0) {
      uVar8 = 0x165f;
      goto LAB_251889538;
    }
    if (lVar7 == 0) {
LAB_251889500:
      uVar8 = 0;
      uVar9 = 0x1661;
      goto LAB_2518894b0;
    }
    lVar2 = func_0x0002580f6a50(lVar7);
    lVar3 = func_0x0002581064c0();
    if (lVar2 != lVar3) goto LAB_251889500;
    lVar2 = func_0x0002580f6a30(lVar7);
    uVar8 = func_0x00025810b980(local_78 + 1,0,lVar2,lVar2 + 0x10,lVar2 + 0x20,lVar2 + 0x30);
    if ((int)uVar8 != 0) {
      func_0x000258109a30(uVar8,"_FPSetup2ResponseCompletionHandler",0x1667,0);
      goto LAB_251889560;
    }
    func_0x00025810b6a0(lVar6,local_78 + 1);
    uVar8 = *_DAT_2680d3198;
    func_0x00025810a940(local_78[0],_APReceiverRequestProcessorSetProperty_2679,
                        &cfstringStruct_276112190,uVar8);
    func_0x00025810a940(local_78[0],_APReceiverRequestProcessorSetProperty_2679,
                        &cfstringStruct_2761121b0,uVar8);
    if (*(long *)(lVar10 + 0x50) != 0) {
      _IPaI1oem5iL();
      *(undefined8 *)(lVar10 + 0x50) = 0;
    }
    if ((_gLogCategory_AirPlayReceiverServer < 0x33) &&
       ((_gLogCategory_AirPlayReceiverServer != -1 ||
        (iVar1 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverServer,0x2000032), iVar1 != 0))))
    {
      func_0x000258101eb0(&_gLogCategory_AirPlayReceiverServer,
                          "void _FPSetup2ResponseCompletionHandler(HTTPMessageRef)",0x2000032,
                          "FP-Setup2 Complete\n");
    }
  }
  func_0x0002580f5830(lVar7);
LAB_2518894c4:
  func_0x0002580f5830(lVar6);
  return;
}

