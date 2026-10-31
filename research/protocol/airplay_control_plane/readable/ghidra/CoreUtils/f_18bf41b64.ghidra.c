/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf41b64
 * original code SHA256: 31f4b29d29f881161d5aa21378140b63049c3895462191c0c136b2046fba9998
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _TLV8BufferAppend(long *param_1,undefined1 param_2,long param_3,ulong param_4)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  undefined1 *puVar4;
  
  if (param_4 == 0xffffffffffffffff) {
    param_4 = func_0x0001900d0320(param_3);
  }
  if (param_4 < 0x7ffffffffffffffe) {
    uVar3 = param_4 / 0xff;
    if (param_4 % 0xff != 0) {
      uVar3 = uVar3 + 1;
    }
    lVar2 = param_4 + uVar3 * 2;
    if (param_4 < 0x100) {
      lVar2 = param_4 + 2;
    }
    uVar1 = param_1[1];
    uVar3 = uVar1 + lVar2;
    if (uVar3 <= (ulong)param_1[2]) {
      if (uVar3 < uVar1) {
        return 0xffffe5a1;
      }
      if (uVar3 < 0x12d) {
        puVar4 = (undefined1 *)((long)param_1 + uVar1 + 0x20);
      }
      else {
        lVar2 = func_0x0001900cfd70(uVar3,0x100004077774924);
        if (lVar2 == 0) {
          return 0xffffe5b8;
        }
        if (param_1[3] == 0) {
          if (param_1[1] != 0) {
            func_0x0001900cc480(lVar2,param_1 + 4);
          }
        }
        else {
          func_0x0001900cc480(lVar2);
          func_0x0001900cc3a0(param_1[3]);
        }
        *param_1 = lVar2;
        param_1[3] = lVar2;
        puVar4 = (undefined1 *)(lVar2 + param_1[1]);
      }
      lVar2 = param_3 + param_4;
      do {
        uVar3 = lVar2 - param_3;
        if (0xfe < uVar3) {
          uVar3 = 0xff;
        }
        *puVar4 = param_2;
        puVar4[1] = (char)uVar3;
        if (lVar2 != param_3) {
          func_0x0001900cc480(puVar4 + 2,param_3,uVar3);
        }
        param_3 = param_3 + uVar3;
        puVar4 = puVar4 + uVar3 + 2;
      } while (param_3 != lVar2);
      param_1[1] = (long)puVar4 - *param_1;
      return 0;
    }
  }
  return 0xffffe5a9;
}

