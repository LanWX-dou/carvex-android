/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf36d10
 * original code SHA256: 118d811cdf5dfeb64bb84bf5218d413d70859562b5065e8dec292172c5b7f287
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_SRPClientStart_libsrp
          (long *param_1,undefined *param_2,undefined8 param_3,ulong param_4,undefined8 param_5,
          ulong param_6,undefined8 param_7,ulong param_8,undefined8 param_9,ulong param_10,
          undefined8 *param_11,long *param_12,undefined8 *param_13,long *param_14,
          undefined8 *param_15,long *param_16)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *local_68;
  undefined8 *local_60;
  undefined8 *local_58;
  
  local_60 = (undefined8 *)0x0;
  local_58 = (undefined8 *)0x0;
  local_68 = (undefined8 *)0x0;
  if (param_2 != &__kSRPParameters_3072_SHA512) {
    uVar3 = 0xffffe5b1;
    goto LAB_18bf36e98;
  }
  if (*param_1 != 0) {
    _SRP_free();
    *param_1 = 0;
  }
  lVar2 = _SRP_new(&_srp6a_client_meth);
  *param_1 = lVar2;
  if (lVar2 == 0) {
    uVar3 = 0xffffe5b8;
    goto LAB_18bf36e98;
  }
  if (param_4 == 0xffffffffffffffff) {
    param_4 = func_0x0001900d0320(param_3);
  }
  if (param_4 >> 0x1f == 0) {
    iVar1 = _SRP_set_user_raw(lVar2,param_3,param_4);
    if (iVar1 == 0) {
      if (param_8 >> 0x1f != 0) goto LAB_18bf36f50;
      iVar1 = _SRP_set_params(*param_1,param_7,param_8);
      if (iVar1 == 0) {
        if (param_6 == 0xffffffffffffffff) {
          param_6 = func_0x0001900d0320(param_5);
        }
        if (param_6 >> 0x1f != 0) goto LAB_18bf36f50;
        iVar1 = (**(code **)(*(long *)(*param_1 + 0x60) + 0x28))(*param_1,param_5,param_6);
        if ((iVar1 == 0) &&
           (iVar1 = (**(code **)(*(long *)(*param_1 + 0x60) + 0x30))(*param_1,&local_58), iVar1 == 0
           )) {
          uVar3 = 0xffffe5a9;
          if ((param_10 >> 0x1f != 0) || (*(int *)(local_58 + 1) < 1)) goto LAB_18bf36e98;
          iVar1 = (**(code **)(*(long *)(*param_1 + 0x60) + 0x38))(*param_1,&local_60,param_9);
          if (iVar1 == 0) {
            if (*(int *)(local_60 + 1) < 1) goto LAB_18bf36e98;
            iVar1 = (**(code **)(*(long *)(*param_1 + 0x60) + 0x48))(*param_1,&local_68);
            if (iVar1 == 0) {
              if (0 < *(int *)(local_68 + 1)) {
                uVar3 = 0;
                *param_11 = *local_58;
                *param_12 = (long)*(int *)(local_58 + 1);
                local_58[1] = 0;
                *param_13 = *local_60;
                *param_14 = (long)*(int *)(local_60 + 1);
                local_60[1] = 0;
                *param_15 = *local_68;
                *param_16 = (long)*(int *)(local_68 + 1);
                local_68[1] = 0;
              }
              goto LAB_18bf36e98;
            }
          }
        }
      }
    }
    uVar3 = 0xffffe5d4;
  }
  else {
LAB_18bf36f50:
    uVar3 = 0xffffe5a9;
  }
LAB_18bf36e98:
  if (local_58 != (undefined8 *)0x0) {
    _cstr_free();
    local_58 = (undefined8 *)0x0;
  }
  if (local_60 != (undefined8 *)0x0) {
    _cstr_clear_free();
    local_60 = (undefined8 *)0x0;
  }
  if (local_68 != (undefined8 *)0x0) {
    _cstr_free();
  }
  return uVar3;
}

