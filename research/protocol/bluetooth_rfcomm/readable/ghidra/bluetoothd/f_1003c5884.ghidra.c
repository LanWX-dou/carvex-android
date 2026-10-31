/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c5884
 * original code SHA256: 32565e93114728416cff1659f44630d733f6f89143980ea8ccc32fe2cb9c6fff
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long FUN_1003c5884(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5)

{
  long lVar1;
  long lVar2;
  undefined1 *puVar3;
  long lVar4;
  undefined1 auStack_46 [2];
  undefined2 uStack_44;
  undefined1 uStack_42;
  undefined1 uStack_41;
  
  if (((int)param_2 != 0) && ((int)param_4 != 0)) {
    FUN_1000f9438();
  }
  lVar1 = 3;
  FUN_1000c1394();
  if (lVar1 == 0) {
    lVar4 = 0x6a;
  }
  else {
    uStack_41 = 0;
    uStack_44 = 0;
    uStack_42 = 0;
    lVar2 = param_1;
    FUN_1003c57f8(param_1,param_2,param_4,param_5,auStack_46);
    lVar4 = lVar1;
    FUN_10006b424(lVar1,auStack_46,lVar2,0);
    if (((int)lVar4 == 0) &&
       (lVar4 = lVar1, FUN_10006b424(lVar1,param_3,param_4,0), (int)lVar4 == 0)) {
      puVar3 = auStack_46;
      FUN_1003c6b60(puVar3,2);
      uStack_41 = SUB81(puVar3,0);
      lVar4 = lVar1;
      FUN_10006b424(lVar1,&uStack_41,1,0);
      if (((int)lVar4 == 0) &&
         (FUN_1003c54f8(param_1,param_2,lVar1,0), lVar4 = param_1, (int)param_1 == 0)) {
        return param_1;
      }
    }
    FUN_1000c3bf8(lVar1);
  }
  return lVar4;
}

