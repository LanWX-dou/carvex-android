/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6f94
 * original code SHA256: a62cb98b6ee9ec08681a1ea6ae6d275e531c5b71e2ca07bbc72ef0ad034e7946
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003c6f94(long param_1,int param_2,undefined8 param_3,uint param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 uStack_148;
  byte bStack_147;
  undefined8 uStack_146;
  undefined8 uStack_13e;
  undefined8 uStack_136;
  undefined8 uStack_12e;
  undefined8 uStack_126;
  undefined8 uStack_11e;
  undefined8 uStack_116;
  undefined8 uStack_10e;
  undefined8 uStack_106;
  undefined8 uStack_fe;
  undefined8 uStack_f6;
  undefined8 uStack_ee;
  undefined8 uStack_e6;
  undefined8 uStack_de;
  undefined8 uStack_d6;
  undefined8 uStack_ce;
  undefined8 uStack_c6;
  undefined8 uStack_be;
  undefined8 uStack_b6;
  undefined8 uStack_ae;
  undefined8 uStack_a6;
  undefined8 uStack_9e;
  undefined8 uStack_96;
  undefined8 uStack_8e;
  undefined8 uStack_86;
  undefined8 uStack_7e;
  undefined8 uStack_76;
  undefined8 uStack_6e;
  undefined8 uStack_66;
  undefined6 uStack_5e;
  undefined2 uStack_58;
  undefined6 uStack_56;
  undefined8 uStack_50;
  long lStack_48;
  
  lStack_48 = *(long *)PTR____stack_chk_guard_100bfc980;
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  uStack_50 = 0;
  uStack_56 = 0;
  uStack_5e = 0;
  uStack_58 = 0;
  uStack_66 = 0;
  uStack_6e = 0;
  uStack_76 = 0;
  uStack_7e = 0;
  uStack_86 = 0;
  uStack_8e = 0;
  uStack_96 = 0;
  uStack_9e = 0;
  uStack_a6 = 0;
  uStack_ae = 0;
  uStack_b6 = 0;
  uStack_be = 0;
  uStack_c6 = 0;
  uStack_ce = 0;
  uStack_d6 = 0;
  uStack_de = 0;
  uStack_e6 = 0;
  uStack_ee = 0;
  uStack_f6 = 0;
  uStack_fe = 0;
  uStack_106 = 0;
  uStack_10e = 0;
  uStack_116 = 0;
  uStack_11e = 0;
  uStack_126 = 0;
  uStack_12e = 0;
  uStack_136 = 0;
  uStack_13e = 0;
  uStack_146 = 0;
  if ((param_4 >> 7 & 1) == 0) {
    uStack_148 = 0x23;
    if (param_2 == 0) {
      uStack_148 = 0x21;
    }
    bStack_147 = (byte)(param_4 << 1) | 1;
    ___memmove_chk(&uStack_146,param_3,param_4,0xfe);
    if (param_2 != 0) {
      FUN_1003c6d00(param_1);
    }
    FUN_1003c5884(param_1,0,&uStack_148,param_4 + 2 & 0xff,0);
  }
  else {
    iVar1 = 2;
    FUN_10000d938(2,0x32);
    if (iVar1 != 0) {
      FUN_10000d120("OI_RfcommMux_TEST invalid size=%d");
      uVar2 = 0x32;
      FUN_10000e9d4();
      uVar3 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar3 != 0) {
        FUN_10018f150(uVar2);
      }
    }
  }
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_48) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

