/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251acea60
 * original code SHA256: 4eb6337a41569a3720404fee23caeb380c55f4d2b51ac9419b0f8725bb5bed49
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_fpAuthentication_CreateEncryptedKey
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  bool bVar1;
  long *plVar2;
  undefined8 uVar3;
  long lVar4;
  undefined1 *puVar5;
  undefined4 local_54;
  undefined8 local_50;
  undefined1 auStack_48 [16];
  long local_38;
  
  local_38 = *_DAT_2681b4ee0;
  local_50 = 0;
  local_54 = 0;
  plVar2 = (long *)func_0x00025810ac50();
  if (*plVar2 == 0) {
    uVar3 = 0xfffee785;
    _fpAuthentication_CreateEncryptedKey_cold_3();
  }
  else {
    func_0x000258101800(param_2,0,0x10,auStack_48);
    uVar3 = _U4HBs(*plVar2,auStack_48,0x10,&local_50,&local_54);
    if ((int)uVar3 == 0) {
      lVar4 = func_0x0002580f6ff0(param_3,local_50,local_54);
      if (lVar4 == 0) {
        _fpAuthentication_CreateEncryptedKey_cold_2();
        uVar3 = 0xfffee788;
      }
      else {
        uVar3 = 0;
        *param_4 = lVar4;
      }
    }
    else {
      _fpAuthentication_CreateEncryptedKey_cold_1();
    }
  }
  _jEHf8Xzsv8K(local_50);
  lVar4 = -0x10;
  puVar5 = auStack_48;
  do {
    *puVar5 = 0;
    bVar1 = lVar4 != -1;
    lVar4 = lVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (bVar1);
  if (*_DAT_2681b4ee0 == local_38) {
    return uVar3;
  }
  uVar3 = func_0x0002580f4380();
  return uVar3;
}

