/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c20b8
 * original code SHA256: 76346c66966ef09af6166edecedcf3ab27f013eb281350fe36b8d5922f23e14a
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * FUN_1003c20b8(undefined1 *param_1)

{
  ushort uVar1;
  ushort uVar2;
  code *pcVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulong unaff_x30;
  
  if (param_1 == (undefined1 *)0x0) {
    FUN_1000f9438();
  }
  if (param_1[0xd] != '\0') {
    FUN_1000f9438();
  }
  puVar5 = param_1;
  FUN_1003c4c88();
  if ((int)puVar5 != 0) {
    iVar4 = 2;
    FUN_10000d938(2,0x32);
    if (iVar4 != 0) {
      FUN_10000d120("DLCI: %d");
      uVar6 = 0x32;
      FUN_10000e9d4();
      uVar7 = uVar6;
      _os_log_type_enabled();
      if ((int)uVar7 != 0) {
        FUN_1008b8180(puVar5,uVar6);
      }
    }
    return puVar5;
  }
  uVar2 = *(ushort *)(*(long *)(param_1 + 0x80) + 4);
  uVar1 = *(ushort *)(param_1 + 0x10);
  if (uVar2 <= *(ushort *)(param_1 + 0x10)) {
    uVar1 = uVar2;
  }
  *(ushort *)(param_1 + 0x10) = uVar1;
  puVar5 = &LAB_1003c21ac;
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(0xc471,0x1003c2198);
    (*pcVar3)();
  }
  FUN_1003d8e5c(&LAB_1003c21ac,*(long *)(param_1 + 0x80) + 6,*(undefined8 *)(param_1 + 0x30),
                param_1 + 0x38,0);
  return puVar5;
}

