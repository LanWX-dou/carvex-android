/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226ee961c
 * original code SHA256: ab6beb42f76502b1f3afe6d16210dc2de872760d180a4d8c0b94bcc771447e2a
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _APSEncryptionUtilsDeriveAESKeySHA512
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 *param_7,undefined8 *param_8)

{
  bool bVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 local_180;
  undefined8 uStack_178;
  undefined8 local_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_a8;
  undefined8 uStack_a0;
  long local_68;
  
  local_68 = *_DAT_2681b4ee0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_148 = 0;
  local_150 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_168 = 0;
  local_170 = 0;
  uStack_158 = 0;
  uStack_160 = 0;
  uStack_178 = 0;
  local_180 = 0;
  if (param_7 != (undefined8 *)0x0) {
    func_0x00022818b840(&local_180);
    func_0x00022818b850(&local_180,param_3,param_4);
    func_0x00022818b850(&local_180,param_1,param_2);
    func_0x00022818b830(&local_a8,&local_180);
    param_7[1] = uStack_a0;
    *param_7 = local_a8;
  }
  if (param_8 != (undefined8 *)0x0) {
    func_0x00022818b840(&local_180);
    func_0x00022818b850(&local_180,param_5,param_6);
    func_0x00022818b850(&local_180,param_1,param_2);
    func_0x00022818b830(&local_a8,&local_180);
    param_8[1] = uStack_a0;
    *param_8 = local_a8;
  }
  lVar3 = -0x40;
  puVar2 = &local_a8;
  do {
    *(undefined1 *)puVar2 = 0;
    bVar1 = lVar3 != -1;
    lVar3 = lVar3 + 1;
    puVar2 = (undefined8 *)((long)puVar2 + 1);
  } while (bVar1);
  if (*_DAT_2681b4ee0 == local_68) {
    return;
  }
  func_0x00022813e7e0();
  return;
}

