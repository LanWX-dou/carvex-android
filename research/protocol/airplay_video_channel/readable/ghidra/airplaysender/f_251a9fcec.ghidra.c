/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a9fcec
 * original code SHA256: 8b98c9da4b8a5797dd26c02b2323dbb2cabce3d8f3ac98804e73ab141363e175
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000251a9fd58) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _sdpsession_copyCryptor(undefined8 param_1,long *param_2)

{
  int iVar1;
  long lVar2;
  code *pcVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long local_38;
  long local_30;
  long local_28;
  
  lVar2 = func_0x00025810ac50();
  local_30 = 0;
  local_28 = 0;
  local_38 = 0;
  uVar5 = *(undefined8 *)(lVar2 + 0x38);
  lVar2 = func_0x000258109150(uVar5);
  puVar4 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 0x10);
  pcVar3 = (code *)*puVar4;
  if ((pcVar3 == (code *)0x0) || (pcVar3 == (code *)0x0)) {
    uVar5 = 0xffffce12;
  }
  else {
    uVar5 = (*pcVar3)((ulong)puVar4 & 0xffffffffffff | 0x7362000000000000,uVar5,&local_28,&local_30)
    ;
    if ((int)uVar5 == 0) {
      uVar5 = func_0x000258109680(*_DAT_2680d3150,local_28,local_30,&local_38);
      if ((int)uVar5 == 0) {
        if ((_gLogCategory_APSenderSessionSDP < 0x29) &&
           ((_gLogCategory_APSenderSessionSDP != -1 ||
            (iVar1 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x2000028), iVar1 != 0)))
           ) {
          _sdpsession_copyCryptor_cold_2();
        }
        uVar5 = 0;
        if (param_2 != (long *)0x0) {
          *param_2 = local_38;
          local_38 = 0;
        }
      }
      else {
        _sdpsession_copyCryptor_cold_1();
      }
      goto LAB_251a9fdf8;
    }
  }
  func_0x000258109a30(uVar5,"sdpsession_copyCryptor",0x65f,0);
LAB_251a9fdf8:
  if (local_28 != 0) {
    func_0x0002580f5830();
  }
  if (local_30 != 0) {
    func_0x0002580f5830();
  }
  if (local_38 != 0) {
    func_0x0002580f5830();
  }
  return uVar5;
}

