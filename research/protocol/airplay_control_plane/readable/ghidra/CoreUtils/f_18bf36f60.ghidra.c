/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf36f60
 * original code SHA256: b5a1316def5c780964f15921ac0622bfa88121a42621ed8c8c21cbd6d90f9a7e
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _SRPClientVerify_libsrp(long *param_1,undefined8 param_2,ulong param_3)

{
  int iVar1;
  undefined8 uVar2;
  
  if (*param_1 == 0) {
    uVar2 = 0xffffe5a7;
  }
  else {
    if (param_3 >> 0x1f == 0) {
      iVar1 = (**(code **)(*(long *)(*param_1 + 0x60) + 0x40))();
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 0xffffe59e;
      }
      if (*param_1 == 0) {
        return uVar2;
      }
    }
    else {
      uVar2 = 0xffffe5a9;
    }
    _SRP_free();
    *param_1 = 0;
  }
  return uVar2;
}

