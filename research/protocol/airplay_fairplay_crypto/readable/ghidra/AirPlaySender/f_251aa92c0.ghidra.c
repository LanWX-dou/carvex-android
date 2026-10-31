/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa92c0
 * original code SHA256: ec824aad1e5f64d6b6d1db6e3e61a8f72ba2b73d948d137726fdbfe4d04a9da3
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_legacyKeyHolder_CopyProperty
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  int iVar2;
  long *plVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  plVar3 = (long *)func_0x00025810ac50();
  if ((_gLogCategory_APKeyHolderLegacy < 0xb) &&
     ((_gLogCategory_APKeyHolderLegacy != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APKeyHolderLegacy,0x200000a), iVar2 != 0)))) {
    func_0x000258101eb0(&_gLogCategory_APKeyHolderLegacy,
                        "OSStatus legacyKeyHolder_CopyProperty(CMBaseObjectRef, CFStringRef, CFAllocatorRef, void *)"
                        ,0x200000a,"[%p] %###s propertyKey: \'%@\'\n");
  }
  iVar2 = func_0x000258101830(param_2,&cfstringStruct_27612c2d0);
  if (iVar2 == 0) {
    if ((_gLogCategory_APKeyHolderLegacy < 0x5b) &&
       ((_gLogCategory_APKeyHolderLegacy != -1 ||
        (iVar2 = func_0x000258101e40(&_gLogCategory_APKeyHolderLegacy,0x200005a), iVar2 != 0)))) {
      _legacyKeyHolder_CopyProperty_cold_1(param_2);
    }
    uVar5 = 0xffffce10;
  }
  else {
    puVar1 = _DAT_2680d3188;
    if (*plVar3 != 0) {
      puVar1 = _DAT_2680d3198;
    }
    uVar4 = func_0x0002580f6a60(*puVar1);
    uVar5 = 0;
    *param_4 = uVar4;
  }
  return uVar5;
}

