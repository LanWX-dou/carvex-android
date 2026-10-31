/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1004f20fc
 * original code SHA256: 7df98ee7f27b0fa608b8b50e63f63d632cbbfbbf00a2ecc4cfe5f4dd794425e9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool phone_fn_1004f20fc(undefined8 param_1,undefined8 param_2,int *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  int iVar16;
  undefined8 uVar17;
  int *piVar18;
  undefined4 uStack_5c;
  int *piStack_58;
  undefined8 uStack_50;
  long lStack_48;
  
  piVar18 = param_3 + 2;
  piStack_58 = piVar18;
  FUN_10020eda4(&piStack_58,*(undefined8 *)piVar18);
  *(int **)param_3 = piVar18;
  param_3[4] = 0;
  param_3[5] = 0;
  piVar18[0] = 0;
  piVar18[1] = 0;
  piStack_58 = (int *)0x0;
  uStack_50 = 0;
  lStack_48 = 0;
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceHandsfree",&piStack_58);
  iVar16 = (int)uVar17;
  bVar1 = iVar16 != 0;
  if (!bVar1) {
    FUN_1004f25cc();
    uStack_5c = 1;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServicePhoneBook",&piStack_58);
  iVar16 = (int)uVar17;
  bVar2 = iVar16 == 0;
  if (bVar2) {
    FUN_1004f25cc();
    uStack_5c = 2;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceRemote",&piStack_58);
  iVar16 = (int)uVar17;
  bVar3 = iVar16 == 0;
  if (bVar3) {
    FUN_1004f25cc();
    uStack_5c = 8;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceA2DP",&piStack_58);
  iVar16 = (int)uVar17;
  bVar4 = iVar16 == 0;
  if (bVar4) {
    FUN_1004f25cc();
    uStack_5c = 0x10;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceHID",&piStack_58);
  iVar16 = (int)uVar17;
  bVar5 = iVar16 == 0;
  if (bVar5) {
    FUN_1004f25cc();
    uStack_5c = 0x20;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceWiAP",&piStack_58);
  iVar16 = (int)uVar17;
  bVar6 = iVar16 == 0;
  if (bVar6) {
    FUN_1004f25cc();
    uStack_5c = 0x80;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceNetSharing",&piStack_58);
  iVar16 = (int)uVar17;
  bVar7 = iVar16 == 0;
  if (bVar7) {
    FUN_1004f25cc();
    uStack_5c = 0x100;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceNetSharingUser",&piStack_58);
  iVar16 = (int)uVar17;
  bVar8 = iVar16 == 0;
  if (bVar8) {
    FUN_1004f25cc();
    uStack_5c = 0x1000;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceGaming",&piStack_58);
  iVar16 = (int)uVar17;
  bVar9 = iVar16 == 0;
  if (bVar9) {
    FUN_1004f25cc();
    uStack_5c = 0x800;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceBraille",&piStack_58);
  iVar16 = (int)uVar17;
  bVar10 = iVar16 == 0;
  if (bVar10) {
    FUN_1004f25cc();
    uStack_5c = 0x2000;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceMAP",&piStack_58);
  iVar16 = (int)uVar17;
  bVar11 = iVar16 == 0;
  if (bVar11) {
    FUN_1004f25cc();
    uStack_5c = 0x200;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceWiAPSink",&piStack_58);
  iVar16 = (int)uVar17;
  bVar12 = iVar16 == 0;
  if (bVar12) {
    FUN_1004f25cc();
    uStack_5c = 0x20000;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceWirelessCarPlay",&piStack_58);
  iVar16 = (int)uVar17;
  bVar13 = iVar16 == 0;
  if (bVar13) {
    FUN_1004f25cc();
    uStack_5c = 0x40000;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  uVar17 = param_1;
  FUN_1004f1b08(param_1,param_2,"ServiceAACP",&piStack_58);
  iVar16 = (int)uVar17;
  bVar14 = iVar16 == 0;
  if (bVar14) {
    FUN_1004f25cc();
    uStack_5c = 0x80000;
    piVar18 = param_3;
    FUN_1004f2670(param_3,&uStack_5c);
    *piVar18 = iVar16;
  }
  FUN_1004f1b08(param_1,param_2,"ServiceGATT",&piStack_58);
  iVar16 = (int)param_1;
  bVar15 = iVar16 == 0;
  if (bVar15) {
    FUN_1004f25cc();
    uStack_5c = 0x100000;
    FUN_1004f2670(param_3,&uStack_5c);
    *param_3 = iVar16;
  }
  if (lStack_48 < 0) {
    __ZdlPv(piStack_58);
  }
  return !bVar15 &&
         (!bVar14 &&
         (!bVar13 &&
         (!bVar12 &&
         (!bVar11 &&
         (!bVar10 &&
         (!bVar9 &&
         (!bVar8 && (!bVar7 && (!bVar6 && (!bVar5 && (!bVar4 && (!bVar3 && (!bVar2 && bVar1)))))))))
         ))));
}

