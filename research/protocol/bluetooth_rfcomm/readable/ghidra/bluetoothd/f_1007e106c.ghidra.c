/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1007e106c
 * original code SHA256: ed29cb2eaa2474708528a1aab25ad563df5f0d77a2f266572a0f0340baa686cd
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001007e3de0) */
/* WARNING: Removing unreachable block (ram,0x0001007e3d3c) */
/* WARNING: Removing unreachable block (ram,0x0001007e3c00) */
/* WARNING: Removing unreachable block (ram,0x0001007e3afc) */
/* WARNING: Removing unreachable block (ram,0x0001007e39f8) */
/* WARNING: Removing unreachable block (ram,0x0001007e38dc) */
/* WARNING: Removing unreachable block (ram,0x0001007e37d8) */
/* WARNING: Removing unreachable block (ram,0x0001007e36d8) */
/* WARNING: Removing unreachable block (ram,0x0001007e35e0) */
/* WARNING: Removing unreachable block (ram,0x0001007e34e8) */
/* WARNING: Removing unreachable block (ram,0x0001007e33e8) */
/* WARNING: Removing unreachable block (ram,0x0001007e32e8) */
/* WARNING: Removing unreachable block (ram,0x0001007e31e8) */
/* WARNING: Removing unreachable block (ram,0x0001007e30e8) */
/* WARNING: Removing unreachable block (ram,0x0001007e2fe4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2ee8) */
/* WARNING: Removing unreachable block (ram,0x0001007e2de4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2ce4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2bf4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2bd4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2ad0) */
/* WARNING: Removing unreachable block (ram,0x0001007e29cc) */
/* WARNING: Removing unreachable block (ram,0x0001007e26c4) */
/* WARNING: Removing unreachable block (ram,0x0001007e28b0) */
/* WARNING: Removing unreachable block (ram,0x0001007e27b8) */
/* WARNING: Removing unreachable block (ram,0x0001007e26a4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2148) */
/* WARNING: Removing unreachable block (ram,0x0001007e2254) */
/* WARNING: Removing unreachable block (ram,0x0001007e2540) */
/* WARNING: Removing unreachable block (ram,0x0001007e2424) */
/* WARNING: Removing unreachable block (ram,0x0001007e233c) */
/* WARNING: Removing unreachable block (ram,0x0001007e2270) */
/* WARNING: Removing unreachable block (ram,0x0001007e2128) */
/* WARNING: Removing unreachable block (ram,0x0001007e1e8c) */
/* WARNING: Removing unreachable block (ram,0x0001007e1d64) */
/* WARNING: Removing unreachable block (ram,0x0001007e1c40) */
/* WARNING: Removing unreachable block (ram,0x0001007e1ad4) */
/* WARNING: Removing unreachable block (ram,0x0001007e19ac) */
/* WARNING: Removing unreachable block (ram,0x0001007e1898) */
/* WARNING: Removing unreachable block (ram,0x0001007e177c) */
/* WARNING: Removing unreachable block (ram,0x0001007e1664) */
/* WARNING: Removing unreachable block (ram,0x0001007e116c) */
/* WARNING: Removing unreachable block (ram,0x0001007e167c) */
/* WARNING: Removing unreachable block (ram,0x0001007e1794) */
/* WARNING: Removing unreachable block (ram,0x0001007e18b0) */
/* WARNING: Removing unreachable block (ram,0x0001007e19c4) */
/* WARNING: Removing unreachable block (ram,0x0001007e1aec) */
/* WARNING: Removing unreachable block (ram,0x0001007e1c58) */
/* WARNING: Removing unreachable block (ram,0x0001007e1d7c) */
/* WARNING: Removing unreachable block (ram,0x0001007e1ea4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2164) */
/* WARNING: Removing unreachable block (ram,0x0001007e2234) */
/* WARNING: Removing unreachable block (ram,0x0001007e234c) */
/* WARNING: Removing unreachable block (ram,0x0001007e2434) */
/* WARNING: Removing unreachable block (ram,0x0001007e2554) */
/* WARNING: Removing unreachable block (ram,0x0001007e2264) */
/* WARNING: Removing unreachable block (ram,0x0001007e2158) */
/* WARNING: Removing unreachable block (ram,0x0001007e26e0) */
/* WARNING: Removing unreachable block (ram,0x0001007e27c8) */
/* WARNING: Removing unreachable block (ram,0x0001007e28c0) */
/* WARNING: Removing unreachable block (ram,0x0001007e26d4) */
/* WARNING: Removing unreachable block (ram,0x0001007e29e4) */
/* WARNING: Removing unreachable block (ram,0x0001007e2ae8) */
/* WARNING: Removing unreachable block (ram,0x0001007e2c10) */
/* WARNING: Removing unreachable block (ram,0x0001007e2c04) */
/* WARNING: Removing unreachable block (ram,0x0001007e2cfc) */
/* WARNING: Removing unreachable block (ram,0x0001007e2dfc) */
/* WARNING: Removing unreachable block (ram,0x0001007e2f00) */
/* WARNING: Removing unreachable block (ram,0x0001007e2ffc) */
/* WARNING: Removing unreachable block (ram,0x0001007e3100) */
/* WARNING: Removing unreachable block (ram,0x0001007e3200) */
/* WARNING: Removing unreachable block (ram,0x0001007e3300) */
/* WARNING: Removing unreachable block (ram,0x0001007e3400) */
/* WARNING: Removing unreachable block (ram,0x0001007e3500) */
/* WARNING: Removing unreachable block (ram,0x0001007e35f8) */
/* WARNING: Removing unreachable block (ram,0x0001007e36f0) */
/* WARNING: Removing unreachable block (ram,0x0001007e37f0) */
/* WARNING: Removing unreachable block (ram,0x0001007e38f4) */
/* WARNING: Removing unreachable block (ram,0x0001007e3a08) */
/* WARNING: Removing unreachable block (ram,0x0001007e3b0c) */
/* WARNING: Removing unreachable block (ram,0x0001007e3c10) */
/* WARNING: Removing unreachable block (ram,0x0001007e3d4c) */
/* WARNING: Removing unreachable block (ram,0x0001007e3df8) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_1007e106c(undefined8 *param_1)

{
  ID *pIVar1;
  ushort *puVar2;
  char cVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int iVar10;
  byte bVar11;
  int iVar12;
  char *pcVar13;
  mach_header *pmVar14;
  undefined2 *puVar15;
  ID IVar16;
  long *plVar17;
  undefined8 *puVar18;
  undefined *puVar19;
  ID IVar20;
  undefined8 uVar21;
  mach_header *pmVar22;
  mach_header *pmVar23;
  ushort uVar24;
  uint uVar25;
  float fVar26;
  float afStack_ec [3];
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  int iStack_d4;
  byte bStack_cd;
  uint uStack_cc;
  undefined1 auStack_c8 [52];
  uint uStack_94;
  char acStack_90 [32];
  
  *param_1 = &PTR_DAT_100bcc648;
  param_1[1] = &PTR____cxa_pure_virtual_100bcc690;
  param_1[2] = &PTR____cxa_pure_virtual_100bcc6a8;
  param_1[3] = &PTR_DAT_100bcc6d8;
  pcVar13 = acStack_90;
  FUN_1001ec44c(pcVar13,0x13);
  pcVar13[0xf] = 'a';
  uVar21 = s_LeConnectionManager_100a83faf._0_8_;
  pcVar13[0x10] = 'g';
  pcVar13[0x11] = 'e';
  pcVar13[0x12] = 'r';
  *(undefined8 *)(pcVar13 + 8) = s_LeConnectionManager_100a83faf._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x13] = '\0';
  FUN_1006608a0(param_1 + 4,acStack_90);
  *param_1 = &PTR_LAB_100bcbb68;
  param_1[1] = &PTR_DAT_100bcbc00;
  param_1[2] = &PTR_DAT_100bcbc18;
  param_1[3] = &PTR_DAT_100bcbc48;
  param_1[4] = &PTR_DAT_100bcbcc8;
  param_1[0xb] = &PTR_DAT_100bcbce0;
  param_1[0xc] = &PTR_DAT_100bcbd00;
  param_1[0xd] = &PTR_DAT_100bcbd18;
  thunk_FUN_100038f7c(param_1 + 0x10);
  param_1[0x1a] = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x19) = 0;
  param_1[0x1e] = 0;
  param_1[0x20] = 0;
  param_1[0x1f] = 0;
  param_1[0x25] = 0;
  param_1[0x2d] = 0;
  param_1[0x2c] = 0;
  param_1[0x1c] = 0;
  param_1[0x1b] = 0;
  *(undefined4 *)(param_1 + 0x1d) = 0;
  param_1[0x2a] = 0;
  param_1[0x2b] = param_1 + 0x2c;
  param_1[0x30] = 0;
  param_1[0x2f] = 0;
  param_1[0x2e] = param_1 + 0x2f;
  param_1[0x33] = 0;
  param_1[0x32] = 0;
  param_1[0x31] = param_1 + 0x32;
  param_1[0x36] = 0;
  param_1[0x35] = 0;
  param_1[0x34] = param_1 + 0x35;
  param_1[0x39] = 0;
  param_1[0x38] = 0;
  param_1[0x37] = param_1 + 0x38;
  param_1[0x3c] = 0;
  param_1[0x3b] = 0;
  param_1[0x3a] = param_1 + 0x3b;
  param_1[0x3f] = 0;
  param_1[0x3e] = 0;
  param_1[0x3d] = param_1 + 0x3e;
  param_1[0x42] = 0;
  param_1[0x41] = 0;
  param_1[0x40] = param_1 + 0x41;
  param_1[0x45] = 0;
  param_1[0x44] = 0;
  param_1[0x43] = param_1 + 0x44;
  param_1[0x46] = 0;
  param_1[0x4f] = 0;
  param_1[0x4e] = 0;
  param_1[0x4d] = param_1 + 0x4e;
  *(undefined1 *)(param_1 + 0x50) = 0;
  param_1[0x53] = 0;
  param_1[0x52] = 0;
  param_1[0x51] = param_1 + 0x52;
  param_1[0x56] = 0;
  param_1[0x55] = 0;
  param_1[0x54] = param_1 + 0x55;
  param_1[0x59] = 0;
  param_1[0x58] = 0;
  param_1[0x57] = param_1 + 0x58;
  param_1[0x5c] = 0;
  param_1[0x5b] = 0;
  param_1[0x5a] = param_1 + 0x5b;
  param_1[0x5f] = 0;
  param_1[0x5e] = 0;
  param_1[0x5d] = param_1 + 0x5e;
  *(undefined1 *)(param_1 + 0x60) = 0x81;
  pIVar1 = param_1 + 0x61;
  param_1[0x6a] = 0;
  param_1[0x69] = 0;
  param_1[0x62] = 0;
  *pIVar1 = 0;
  param_1[100] = 0;
  param_1[99] = 0;
  param_1[0x66] = 0;
  param_1[0x65] = 0;
  param_1[0x67] = 0;
  param_1[0x68] = param_1 + 0x69;
  param_1[0x6b] = 0;
  *(undefined1 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)((long)param_1 + 0x362) = 0x1e;
  param_1[0x6f] = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = param_1 + 0x6e;
  *(undefined4 *)(param_1 + 0x70) = 0;
  param_1[0x72] = 0;
  param_1[0x71] = 0;
  param_1[0x7b] = 0;
  param_1[0x7a] = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  param_1[0x75] = 0;
  param_1[0x74] = 0;
  param_1[0x77] = 0;
  param_1[0x76] = 0;
  param_1[0x79] = param_1 + 0x7a;
  thunk_FUN_10043e6dc(param_1 + 0x7c,1);
  *(undefined1 *)(param_1 + 0x82) = 1;
  thunk_FUN_10043e6dc(param_1 + 0x83,1);
  *(undefined1 *)(param_1 + 0x89) = 1;
  *(undefined1 *)((long)param_1 + 1099) = 0;
  uVar21 = _UNK_100955830;
  *(undefined8 *)((long)param_1 + 0x462) = _UNK_100955838;
  *(undefined8 *)((long)param_1 + 0x45a) = uVar21;
  *(undefined8 *)((long)param_1 + 0x46a) = _UNK_1009558a0;
  *(undefined4 *)((long)param_1 + 0x472) = 0xc000c;
  *(undefined2 *)((long)param_1 + 0x476) = 0xc02;
  *(undefined1 *)(param_1 + 0x8f) = 0;
  *(undefined8 *)((long)param_1 + 0x47a) = _UNK_1009558a8;
  *(undefined4 *)((long)param_1 + 0x482) = 0x60303;
  *(undefined2 *)((long)param_1 + 0x486) = 6;
  *(int *)(param_1 + 0x91) = (int)_UNK_1009357f8;
  *(undefined2 *)((long)param_1 + 0x48c) = 1;
  *(undefined1 *)((long)param_1 + 0x48e) = 0;
  param_1[0x94] = 0;
  param_1[0x93] = 0;
  param_1[0x92] = param_1 + 0x93;
  param_1[0x97] = 0;
  param_1[0x96] = 0;
  param_1[0x95] = param_1 + 0x96;
  param_1[0x98] = 0;
  param_1[0x9b] = 0;
  param_1[0x9a] = 0;
  param_1[0x99] = param_1 + 0x9a;
  *(undefined2 *)(param_1 + 0x9c) = 10;
  *(undefined4 *)((long)param_1 + 0x4e4) = 0xe10;
  *(undefined2 *)(param_1 + 0x9d) = 2;
  *(undefined4 *)((long)param_1 + 0x4ec) = 0xe10;
  param_1[0xa0] = 0;
  param_1[0x9f] = 0;
  param_1[0x9e] = param_1 + 0x9f;
  param_1[0xa3] = 0;
  param_1[0xa2] = 0;
  param_1[0xa1] = param_1 + 0xa2;
  param_1[0xa6] = 0;
  param_1[0xa5] = 0;
  param_1[0xa4] = param_1 + 0xa5;
  param_1[0xa9] = 0;
  param_1[0xa8] = 0;
  param_1[0xa7] = param_1 + 0xa8;
  param_1[0xac] = 0;
  param_1[0xab] = 0;
  param_1[0xaa] = param_1 + 0xab;
  *(int *)(param_1 + 0xad) = (int)_UNK_1009558b0;
  *(undefined2 *)((long)param_1 + 0x56c) = 0xa1ab;
  *(undefined1 *)((long)param_1 + 0x56e) = 0xa6;
  param_1[0xb0] = 0;
  param_1[0xaf] = 0;
  param_1[0xae] = param_1 + 0xaf;
  param_1[0xb1] = 0;
  *(undefined2 *)(param_1 + 0xb2) = 2;
  param_1[0xb5] = 0;
  param_1[0xb4] = 0;
  param_1[0xb3] = param_1 + 0xb4;
  param_1[0xb8] = 0;
  param_1[0xb7] = 0;
  param_1[0xb6] = param_1 + 0xb7;
  *(undefined4 *)(param_1 + 0xb9) = 0;
  param_1[0xbc] = 0;
  param_1[0xbb] = 0;
  param_1[0xba] = 0;
  pmVar14 = (mach_header *)(param_1 + 0xbd);
  thunk_FUN_100763fe8();
  param_1[0xc3] = 0;
  param_1[0xc2] = 0;
  param_1[0xc1] = param_1 + 0xc2;
  param_1[0xc6] = 0;
  param_1[0xc5] = 0;
  param_1[0xc4] = param_1 + 0xc5;
  param_1[199] = _UNK_1009558b8;
  *(undefined4 *)(param_1 + 200) = 10;
  param_1[0xc9] = 0;
  *(undefined1 *)(param_1 + 0xca) = 0;
  *(undefined4 *)((long)param_1 + 0x66c) = 0;
  *(undefined8 *)((long)param_1 + 0x654) = 0;
  *(undefined8 *)((long)param_1 + 0x664) = 0;
  *(undefined8 *)((long)param_1 + 0x65c) = 0;
  *(undefined1 *)(param_1 + 0xce) = 1;
  param_1[0xd1] = 0;
  param_1[0xd0] = 0;
  param_1[0xcf] = param_1 + 0xd0;
  param_1[0xd2] = 0;
  *(undefined1 *)(param_1 + 0xd3) = 0;
  *(undefined2 *)((long)param_1 + 0x6a1) = 0;
  uStack_94 = 0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x17);
  *(ulong *)(pcVar13 + 0xf) =
       CONCAT71(s_MaxFilterAcceptListSize_100a83fc3._16_7_,s_MaxFilterAcceptListSize_100a83fc3[0xf])
  ;
  uVar21 = s_MaxFilterAcceptListSize_100a83fc3._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT17(s_MaxFilterAcceptListSize_100a83fc3[0xf],s_MaxFilterAcceptListSize_100a83fc3._8_7_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x17] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar22 = (mach_header *)(ulong)uStack_94;
    pmVar14 = pmRam0000000100cae4e8;
    if ((int)uStack_94 < 2) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fbf80(pmVar22,pmVar23);
        pmVar14 = pmVar22;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = uVar25;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Using override value (%d) for max number of devices in connection Filter Accept List"
                      ,auStack_c8 + 0x18,8);
        uVar25 = uStack_94;
      }
      *(char *)(param_1 + 0x6c) = (char)uVar25;
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x19);
  uVar21 = CONCAT17(s_DefaultConnectionInterval_100a83fdb[0x10],
                    s_DefaultConnectionInterval_100a83fdb._9_7_);
  *(undefined8 *)(pcVar13 + 0x11) = s_DefaultConnectionInterval_100a83fdb._17_8_;
  *(undefined8 *)(pcVar13 + 9) = uVar21;
  uVar21 = s_DefaultConnectionInterval_100a83fdb._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT71(s_DefaultConnectionInterval_100a83fdb._9_7_,s_DefaultConnectionInterval_100a83fdb[8]
               );
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x19] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar22 = (mach_header *)(ulong)uStack_94;
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 - 8 < 0x3e1) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = uVar25;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Using override value %d ms for default LE connection interval",
                      auStack_c8 + 0x18,8);
        uVar25 = uStack_94;
      }
      *(short *)((long)param_1 + 0x362) = (short)uVar25;
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fbfbc(pmVar22,pmVar23);
        pmVar14 = pmVar22;
      }
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,10);
  pcVar13[8] = 't';
  pcVar13[9] = 'h';
  *(undefined8 *)pcVar13 = s_DataLength_100a83ff5._0_8_;
  pcVar13[10] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 == 0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fbff8();
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = uVar25;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Warning: Using override value %d ms for LE data length"
                      ,auStack_c8 + 0x18,8);
        uVar25 = uStack_94;
      }
      *(short *)((long)param_1 + 0x364) = (short)uVar25;
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x22);
  pcVar13[0x20] = 'e';
  uVar5 = s_AllowAllConnectionParameterUpdat_100a84000._24_8_;
  uVar4 = s_AllowAllConnectionParameterUpdat_100a84000._16_8_;
  uVar21 = s_AllowAllConnectionParameterUpdat_100a84000._0_8_;
  pcVar13[0x21] = 's';
  *(undefined8 *)(pcVar13 + 8) = s_AllowAllConnectionParameterUpdat_100a84000._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x22] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 == 0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc038();
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 == 0) {
        uRam0000000100c96aa0 = 1;
      }
      else {
        auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Allow all connection parameters from remote request",
                      auStack_c8 + 0x18,2);
        uRam0000000100c96aa0 = uStack_94 != 0;
      }
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x14);
  pcVar13[0x10] = 'n';
  uVar21 = s_EnablePhyStatsFindMy_100a84023._0_8_;
  pcVar13[0x11] = 'd';
  pcVar13[0x12] = 'M';
  pcVar13[0x13] = 'y';
  *(undefined8 *)(pcVar13 + 8) = s_EnablePhyStatsFindMy_100a84023._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x14] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 == 0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc078();
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 == 0) {
        uRam0000000100c96aa1 = 1;
      }
      else {
        auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Warning: Enabling PHY Stats for findMy connections",
                      auStack_c8 + 0x18,2);
        uRam0000000100c96aa1 = uStack_94 != 0;
      }
    }
  }
  uVar5 = _UNK_100955858;
  uVar4 = _UNK_100955850;
  uVar21 = _UNK_100955840;
  param_1[0x49] = _UNK_100955848;
  param_1[0x48] = uVar21;
  param_1[0x4b] = uVar5;
  param_1[0x4a] = uVar4;
  *(undefined4 *)(param_1 + 0x4c) = 9000;
  uVar5 = _UNK_100955878;
  uVar4 = _UNK_100955870;
  uVar21 = _UNK_100955860;
  param_1[0x22] = _UNK_100955868;
  param_1[0x21] = uVar21;
  param_1[0x24] = uVar5;
  param_1[0x23] = uVar4;
  FUN_1000110f0();
  pcVar13 = auStack_c8 + 0x18;
  FUN_1001ec44c(pcVar13,0x1c);
  uVar6 = s_CoexConnectionScanParameters_100a84038._0_8_;
  uVar21 = CONCAT44(s_CoexConnectionScanParameters_100a84038._12_4_,
                    s_CoexConnectionScanParameters_100a84038._8_4_);
  *(undefined8 *)(pcVar13 + 8) = uVar21;
  *(undefined8 *)pcVar13 = uVar6;
  uVar7 = s_CoexConnectionScanParameters_100a84038._20_8_;
  uVar4 = CONCAT44(s_CoexConnectionScanParameters_100a84038._16_4_,
                   s_CoexConnectionScanParameters_100a84038._12_4_);
  *(undefined8 *)(pcVar13 + 0x14) = s_CoexConnectionScanParameters_100a84038._20_8_;
  *(undefined8 *)(pcVar13 + 0xc) = uVar4;
  pcVar13[0x1c] = '\0';
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x19);
  uVar5 = CONCAT17(s_CoexConnectionScanTimeout_100a84055[0x10],
                   s_CoexConnectionScanTimeout_100a84055._9_7_);
  *(undefined8 *)(pcVar13 + 0x11) = s_CoexConnectionScanTimeout_100a84055._17_8_;
  *(undefined8 *)(pcVar13 + 9) = uVar5;
  uVar5 = s_CoexConnectionScanTimeout_100a84055._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT71(s_CoexConnectionScanTimeout_100a84055._9_7_,s_CoexConnectionScanTimeout_100a84055[8]
               );
  *(undefined8 *)pcVar13 = uVar5;
  pcVar13[0x19] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 == 0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc038();
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = uVar25;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Override fFastConnectionScanDurationMsCoexCarPlay=%dms",
                      auStack_c8 + 0x18,8);
        uVar25 = uStack_94;
      }
      *(uint *)((long)param_1 + 0x25c) = uVar25;
      *(uint *)(param_1 + 0x4c) = uVar25;
    }
  }
  FUN_1000110f0();
  pcVar13 = auStack_c8 + 0x18;
  FUN_1001ec44c(pcVar13,0x1c);
  *(undefined8 *)(pcVar13 + 8) = uVar21;
  *(undefined8 *)pcVar13 = uVar6;
  *(undefined8 *)(pcVar13 + 0x14) = uVar7;
  *(undefined8 *)(pcVar13 + 0xc) = uVar4;
  pcVar13[0x1c] = '\0';
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x23);
  pcVar13[0x1f] = 'u';
  uVar9 = s_CoexConnectionScanIntervalWithAu_100a8406f._24_8_;
  uVar8 = s_CoexConnectionScanIntervalWithAu_100a8406f._16_8_;
  uVar5 = s_CoexConnectionScanIntervalWithAu_100a8406f._0_8_;
  pcVar13[0x20] = 'd';
  pcVar13[0x21] = 'i';
  pcVar13[0x22] = 'o';
  *(undefined8 *)(pcVar13 + 8) = s_CoexConnectionScanIntervalWithAu_100a8406f._8_8_;
  *(undefined8 *)pcVar13 = uVar5;
  *(undefined8 *)(pcVar13 + 0x18) = uVar9;
  *(undefined8 *)(pcVar13 + 0x10) = uVar8;
  pcVar13[0x23] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (uStack_94 == 0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc0b8();
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._28_8_ = (double)(int)uVar25 * 0.625;
        auStack_c8._24_4_ = (undefined4)_UNK_100930ae8;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Override fFastConnectionScanIntervalMsCoexCarPlayWithAudio=%fms",
                      auStack_c8 + 0x18,0xc);
        uVar25 = uStack_94;
      }
      *(short *)(param_1 + 0x23) = (short)uVar25;
    }
  }
  FUN_1000110f0();
  pcVar13 = auStack_c8 + 0x18;
  FUN_1001ec44c(pcVar13,0x1c);
  *(undefined8 *)(pcVar13 + 8) = uVar21;
  *(undefined8 *)pcVar13 = uVar6;
  *(undefined8 *)(pcVar13 + 0x14) = uVar7;
  *(undefined8 *)(pcVar13 + 0xc) = uVar4;
  pcVar13[0x1c] = '\0';
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x26);
  *(ulong *)(pcVar13 + 0x1e) =
       CONCAT62(s_CoexConnectionScanIntervalWithou_100a84093._32_6_,
                s_CoexConnectionScanIntervalWithou_100a84093._30_2_);
  uVar5 = s_CoexConnectionScanIntervalWithou_100a84093._16_8_;
  uVar4 = s_CoexConnectionScanIntervalWithou_100a84093._0_8_;
  uVar21 = CONCAT26(s_CoexConnectionScanIntervalWithou_100a84093._30_2_,
                    s_CoexConnectionScanIntervalWithou_100a84093._24_6_);
  *(undefined8 *)(pcVar13 + 8) = s_CoexConnectionScanIntervalWithou_100a84093._8_8_;
  *(undefined8 *)pcVar13 = uVar4;
  *(undefined8 *)(pcVar13 + 0x18) = uVar21;
  *(undefined8 *)(pcVar13 + 0x10) = uVar5;
  pcVar13[0x26] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    if (uStack_94 == 0) {
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc0f8(pmVar23);
      }
    }
    else {
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._28_8_ = (double)(int)uVar25 * 0.625;
        auStack_c8._24_4_ = (undefined4)_UNK_100930ae8;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Override fFastConnectionScanIntervalMsCoexCarPlayNoAudio=%fms",
                      auStack_c8 + 0x18,0xc);
        uVar25 = uStack_94;
      }
      *(short *)((long)param_1 + 0x116) = (short)uVar25;
    }
  }
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28);
  IVar20 = *pIVar1;
  *pIVar1 = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,IVar20);
  uVar21 = param_1[0x62];
  param_1[0x62] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  uVar21 = param_1[99];
  param_1[99] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  uVar21 = param_1[100];
  param_1[100] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  uVar21 = param_1[0x65];
  param_1[0x65] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  uVar21 = param_1[0x66];
  param_1[0x66] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  uVar21 = param_1[0x67];
  param_1[0x67] = IVar16;
  IVar16 = objc_stub::FUN_10091e560((ID)PTR__OBJC_CLASS___NSMutableSet_100bfcb28,uVar21);
  param_1[0x6b] = IVar16;
  plVar17 = (long *)0x0;
  *(undefined1 *)((long)param_1 + 0x477) = 0x18;
  FUN_1000071f0();
  (**(code **)(*plVar17 + 0x11e8))();
  *(char *)((long)param_1 + 0x476) = (char)plVar17;
  FUN_1000110f0();
  (**(code **)(*plVar17 + 8))();
  if ((int)plVar17 != 0) {
    FUN_1007e4524(param_1);
  }
  uVar21 = param_1[0x46];
  param_1[0x46] = 0;
  auStack_c8._0_4_ = 0;
  auStack_c8._4_4_ = 0;
  pmVar14 = (mach_header *)auStack_c8;
  FUN_100035440(uVar21);
  param_1[0x71] = (long)(int)auStack_c8._0_4_;
  param_1[0x72] = (long)(short)auStack_c8._4_2_;
  *(undefined1 *)(param_1 + 0x73) = 0;
  uStack_cc = 0;
  bStack_cd = 0;
  *(undefined1 *)((long)param_1 + 0x44c) = 0;
  puVar2 = (ushort *)((long)param_1 + 0x44e);
  puVar2[0] = 0;
  puVar2[1] = 0;
  *(undefined2 *)((long)param_1 + 0x452) = 0;
  FUN_1000110f0();
  puVar18 = (undefined8 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar18,8);
  *puVar18 = 0x65726f436e616353;
  *(undefined1 *)(puVar18 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1d);
  uVar21 = CONCAT53(s_IsScanCoreConnectionOverriden_100a840ba._16_5_,
                    s_IsScanCoreConnectionOverriden_100a840ba._13_3_);
  *(undefined8 *)(pcVar13 + 0x15) = s_IsScanCoreConnectionOverriden_100a840ba._21_8_;
  *(undefined8 *)(pcVar13 + 0xd) = uVar21;
  uVar21 = s_IsScanCoreConnectionOverriden_100a840ba._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT35(s_IsScanCoreConnectionOverriden_100a840ba._13_3_,
                s_IsScanCoreConnectionOverriden_100a840ba._8_5_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1d] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x48))(pmVar14,auStack_c8 + 0x18,auStack_c8,(long)param_1 + 0x44c)
  ;
  pmVar23 = pmRam0000000100cae4e8;
  if (((int)pmVar14 != 0) && (*(char *)((long)param_1 + 0x44c) != '\0')) {
    pmVar22 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar22 != 0) {
      auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
      pmVar22 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"Overriding Connection Scan Parameters on ScanCore.",
                    auStack_c8 + 0x18,2);
    }
    FUN_1000110f0();
    puVar18 = (undefined8 *)(auStack_c8 + 0x18);
    FUN_1001ec44c(puVar18,8);
    *puVar18 = 0x65726f436e616353;
    *(undefined1 *)(puVar18 + 1) = 0;
    pcVar13 = auStack_c8;
    FUN_1001ec44c(pcVar13,0x1f);
    uVar21 = CONCAT71(s_IsScanCoreEnabledConnectionScan_100a840d8._16_7_,
                      s_IsScanCoreEnabledConnectionScan_100a840d8[0xf]);
    *(undefined8 *)(pcVar13 + 0x17) = s_IsScanCoreEnabledConnectionScan_100a840d8._23_8_;
    *(undefined8 *)(pcVar13 + 0xf) = uVar21;
    uVar21 = s_IsScanCoreEnabledConnectionScan_100a840d8._0_8_;
    *(ulong *)(pcVar13 + 8) =
         CONCAT17(s_IsScanCoreEnabledConnectionScan_100a840d8[0xf],
                  s_IsScanCoreEnabledConnectionScan_100a840d8._8_7_);
    *(undefined8 *)pcVar13 = uVar21;
    pcVar13[0x1f] = '\0';
    (**(code **)(*(long *)pmVar22 + 0x48))
              (pmVar22,auStack_c8 + 0x18,auStack_c8,(long)param_1 + 0x453);
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    if (((int)pmVar22 == 0) || (*(char *)((long)param_1 + 0x453) == '\0')) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Overriding ScanCore Disabled for Connection Scan.",
                      auStack_c8 + 0x18,2);
      }
      *(undefined4 *)((long)param_1 + 0x44e) = 0;
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Overriding ScanCore Enabled for Connection Scan.",
                      auStack_c8 + 0x18,2);
      }
      FUN_1000110f0();
      puVar18 = (undefined8 *)(auStack_c8 + 0x18);
      FUN_1001ec44c(puVar18,8);
      *puVar18 = 0x65726f436e616353;
      *(undefined1 *)(puVar18 + 1) = 0;
      pcVar13 = auStack_c8;
      FUN_1001ec44c(pcVar13,0x12);
      pcVar13[0x10] = 'o';
      uVar21 = s_IntervalConnection_100a840f8._0_8_;
      pcVar13[0x11] = 'n';
      *(undefined8 *)(pcVar13 + 8) = s_IntervalConnection_100a840f8._8_8_;
      *(undefined8 *)pcVar13 = uVar21;
      pcVar13[0x12] = '\0';
      (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_cc);
      uVar25 = uStack_cc;
      iVar12 = 0;
      if (uStack_cc != 0) {
        iVar12 = (int)pmVar14;
      }
      if (iVar12 != 0) {
        *(short *)(param_1 + 0x8a) = (short)uStack_cc;
        pmVar23 = pmRam0000000100cae4e8;
        pmVar14 = pmRam0000000100cae4e8;
        _os_log_type_enabled(pmRam0000000100cae4e8,0);
        if ((int)pmVar14 != 0) {
          auStack_c8._24_4_ = (undefined4)_UNK_100930510;
          auStack_c8._28_4_ = uVar25;
          pmVar14 = &__mh_execute_header;
          __os_log_impl(0x100000000,pmVar23,0,"Overriding ScanCore Connection Scan Interval %d.",
                        auStack_c8 + 0x18,8);
        }
      }
      FUN_1000110f0();
      puVar18 = (undefined8 *)(auStack_c8 + 0x18);
      FUN_1001ec44c(puVar18,8);
      *puVar18 = 0x65726f436e616353;
      *(undefined1 *)(puVar18 + 1) = 0;
      pcVar13 = auStack_c8;
      FUN_1001ec44c(pcVar13,0x10);
      uVar21 = s_WindowConnection_100a8410b._0_8_;
      *(undefined8 *)(pcVar13 + 8) = s_WindowConnection_100a8410b._8_8_;
      *(undefined8 *)pcVar13 = uVar21;
      pcVar13[0x10] = '\0';
      (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_cc);
      uVar25 = uStack_cc;
      iVar12 = 0;
      if (uStack_cc != 0) {
        iVar12 = (int)pmVar14;
      }
      if (iVar12 != 0) {
        pmVar22 = (mach_header *)(ulong)uStack_cc;
        *puVar2 = (ushort)uStack_cc;
        pmVar23 = pmRam0000000100cae4e8;
        pmVar14 = pmRam0000000100cae4e8;
        _os_log_type_enabled(pmRam0000000100cae4e8,0);
        if ((int)pmVar14 != 0) {
          auStack_c8._24_4_ = (undefined4)_UNK_100930510;
          auStack_c8._28_4_ = uVar25;
          pmVar14 = &__mh_execute_header;
          __os_log_impl(0x100000000,pmVar23,0,"Overriding ScanCore Connection Scan Window %d.",
                        auStack_c8 + 0x18,8);
          pmVar22 = (mach_header *)(ulong)*puVar2;
        }
        uVar24 = *(ushort *)(param_1 + 0x8a);
        if ((uint)uVar24 < ((uint)pmVar22 & 0xffff)) {
          *(undefined1 *)((long)param_1 + 0x44c) = 0;
          pmVar23 = pmRam0000000100cae4e8;
          pmVar14 = pmRam0000000100cae4e8;
          _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
          if ((int)pmVar14 != 0) {
            FUN_1008fc138(pmVar22,uVar24,pmVar23);
            pmVar14 = pmVar22;
          }
          *(undefined4 *)((long)param_1 + 0x44e) = 0;
        }
      }
      FUN_1000110f0();
      puVar18 = (undefined8 *)(auStack_c8 + 0x18);
      FUN_1001ec44c(puVar18,8);
      *puVar18 = 0x65726f436e616353;
      *(undefined1 *)(puVar18 + 1) = 0;
      puVar18 = (undefined8 *)auStack_c8;
      FUN_1001ec44c(puVar18,0xe);
      *(ulong *)((long)puVar18 + 6) =
           CONCAT62(s_eLNAConnection_100a8411c._8_6_,s_eLNAConnection_100a8411c._6_2_);
      *puVar18 = CONCAT26(s_eLNAConnection_100a8411c._6_2_,s_eLNAConnection_100a8411c._0_6_);
      *(undefined1 *)((long)puVar18 + 0xe) = 0;
      (**(code **)(*(long *)pmVar14 + 0x48))(pmVar14,auStack_c8 + 0x18,auStack_c8,&bStack_cd);
      bVar11 = bStack_cd;
      if (((uint)pmVar14 & (uint)bStack_cd) != 0) {
        *(byte *)((long)param_1 + 0x452) = bStack_cd;
        pmVar23 = pmRam0000000100cae4e8;
        pmVar14 = pmRam0000000100cae4e8;
        _os_log_type_enabled(pmRam0000000100cae4e8,0);
        if ((int)pmVar14 != 0) {
          auStack_c8._28_8_ = "enabled";
          if (bVar11 == 0) {
            auStack_c8._28_8_ = "disabled";
          }
          auStack_c8._24_4_ = (undefined4)_UNK_100930b00;
          pmVar14 = &__mh_execute_header;
          __os_log_impl(0x100000000,pmVar23,0,"Overriding ScanCore Connection Scan eLNA %s.",
                        auStack_c8 + 0x18,0xc);
        }
      }
    }
  }
  iStack_d4 = 0;
  *(undefined1 *)((long)param_1 + 0x454) = 0;
  *(undefined4 *)((long)param_1 + 0x456) = 0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x19);
  uVar21 = CONCAT17(s_IsConnectionScanOverriden_100a8412b[0x10],
                    s_IsConnectionScanOverriden_100a8412b._9_7_);
  *(undefined8 *)(pcVar13 + 0x11) = s_IsConnectionScanOverriden_100a8412b._17_8_;
  *(undefined8 *)(pcVar13 + 9) = uVar21;
  uVar21 = s_IsConnectionScanOverriden_100a8412b._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT71(s_IsConnectionScanOverriden_100a8412b._9_7_,s_IsConnectionScanOverriden_100a8412b[8]
               );
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x19] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x48))(pmVar14,auStack_c8 + 0x18,auStack_c8,(long)param_1 + 0x454)
  ;
  pmVar23 = pmRam0000000100cae4e8;
  if (((int)pmVar14 != 0) && (*(char *)((long)param_1 + 0x454) != '\0')) {
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"Overriding Connection Scan Parameters on MainCore.",
                    auStack_c8 + 0x18,2);
    }
    FUN_1000110f0();
    puVar15 = (undefined2 *)(auStack_c8 + 0x18);
    FUN_1001ec44c(puVar15,2);
    *puVar15 = 0x454c;
    *(undefined1 *)(puVar15 + 1) = 0;
    pcVar13 = auStack_c8;
    FUN_1001ec44c(pcVar13,0x16);
    *(ulong *)(pcVar13 + 0xe) =
         CONCAT62(s_ConnectionScanInterval_100a84145._16_6_,
                  s_ConnectionScanInterval_100a84145._14_2_);
    uVar21 = s_ConnectionScanInterval_100a84145._0_8_;
    *(ulong *)(pcVar13 + 8) =
         CONCAT26(s_ConnectionScanInterval_100a84145._14_2_,s_ConnectionScanInterval_100a84145._8_6_
                 );
    *(undefined8 *)pcVar13 = uVar21;
    pcVar13[0x16] = '\0';
    (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&iStack_d4);
    iVar10 = iStack_d4;
    iVar12 = 0;
    if (iStack_d4 != 0) {
      iVar12 = (int)pmVar14;
    }
    if (iVar12 != 0) {
      *(short *)(param_1 + 0x8b) = (short)iStack_d4;
      pmVar23 = pmRam0000000100cae4e8;
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = iVar10;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Overriding MainCore Connection Scan Interval %d.",
                      auStack_c8 + 0x18,8);
      }
    }
    FUN_1000110f0();
    puVar15 = (undefined2 *)(auStack_c8 + 0x18);
    FUN_1001ec44c(puVar15,2);
    *puVar15 = 0x454c;
    *(undefined1 *)(puVar15 + 1) = 0;
    pcVar13 = auStack_c8;
    FUN_1001ec44c(pcVar13,0x14);
    pcVar13[0x10] = 'n';
    uVar21 = s_ConnectionScanWindow_100a8415c._0_8_;
    pcVar13[0x11] = 'd';
    pcVar13[0x12] = 'o';
    pcVar13[0x13] = 'w';
    *(undefined8 *)(pcVar13 + 8) = s_ConnectionScanWindow_100a8415c._8_8_;
    *(undefined8 *)pcVar13 = uVar21;
    pcVar13[0x14] = '\0';
    (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&iStack_d4);
    iVar10 = iStack_d4;
    iVar12 = 0;
    if (iStack_d4 != 0) {
      iVar12 = (int)pmVar14;
    }
    if (iVar12 != 0) {
      *(short *)((long)param_1 + 0x456) = (short)iStack_d4;
      pmVar23 = pmRam0000000100cae4e8;
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = iVar10;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Overriding MainCore Connection Scan Window %d.",
                      auStack_c8 + 0x18,8);
      }
    }
    pmVar23 = (mach_header *)(ulong)*(ushort *)((long)param_1 + 0x456);
    uVar24 = *(ushort *)(param_1 + 0x8b);
    if (uVar24 < *(ushort *)((long)param_1 + 0x456)) {
      *(undefined1 *)((long)param_1 + 0x454) = 0;
      pmVar22 = pmRam0000000100cae4e8;
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc174(pmVar23,uVar24,pmVar22);
        pmVar14 = pmVar23;
      }
      *(undefined4 *)((long)param_1 + 0x456) = 0;
    }
  }
  uStack_d8 = 0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x11);
  pcVar13[0x10] = 'n';
  uVar21 = s_MinRSSIConnection_100a84171._0_8_;
  pcVar13[0x11] = '\0';
  *(undefined8 *)(pcVar13 + 8) = s_MinRSSIConnection_100a84171._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_d8);
  if ((int)pmVar14 != 0) {
    cVar3 = (char)uStack_d8;
    *(char *)((long)param_1 + 0x48b) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"MinRSSIConnection %d overridden",auStack_c8 + 0x18,8);
    }
  }
  uStack_dc = 0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x17);
  *(ulong *)(pcVar13 + 0xf) =
       CONCAT71(s_GlobalMinRSSIConnection_100a84183._16_7_,s_GlobalMinRSSIConnection_100a84183[0xf])
  ;
  uVar21 = s_GlobalMinRSSIConnection_100a84183._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT17(s_GlobalMinRSSIConnection_100a84183[0xf],s_GlobalMinRSSIConnection_100a84183._8_7_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x17] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_dc);
  if ((int)pmVar14 != 0) {
    cVar3 = (char)uStack_dc;
    *(char *)((long)param_1 + 0x48e) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"GlobalMinRSSIConnection %d overridden",auStack_c8 + 0x18,
                    8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x18);
  *(undefined8 *)(pcVar13 + 0x10) = s_MinRSSIConnectionEnabled_100a8419b._16_8_;
  uVar21 = s_MinRSSIConnectionEnabled_100a8419b._0_8_;
  *(undefined8 *)(pcVar13 + 8) = s_MinRSSIConnectionEnabled_100a8419b._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x18] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x48))(pmVar14,auStack_c8 + 0x18,auStack_c8,(long)param_1 + 0x48c)
  ;
  pmVar23 = pmRam0000000100cae4e8;
  if ((((int)pmVar14 != 0) && (*(char *)((long)param_1 + 0x48c) != '\0')) &&
     (pmVar14 = pmRam0000000100cae4e8, _os_log_type_enabled(pmRam0000000100cae4e8,0),
     (int)pmVar14 != 0)) {
    auStack_c8._24_4_ = auStack_c8._24_4_ & 0xffff0000;
    pmVar14 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar23,0,"MinRSSIConnectionEnabled is enabled (overridden)",
                  auStack_c8 + 0x18,2);
  }
  uStack_e0 = 0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x27);
  *(ulong *)(pcVar13 + 0x1f) =
       CONCAT71(s_NumDisconnectionsFromDisabledToS_100a841b4._32_7_,
                s_NumDisconnectionsFromDisabledToS_100a841b4[0x1f]);
  uVar5 = s_NumDisconnectionsFromDisabledToS_100a841b4._16_8_;
  uVar4 = s_NumDisconnectionsFromDisabledToS_100a841b4._0_8_;
  uVar21 = CONCAT17(s_NumDisconnectionsFromDisabledToS_100a841b4[0x1f],
                    s_NumDisconnectionsFromDisabledToS_100a841b4._24_7_);
  *(undefined8 *)(pcVar13 + 8) = s_NumDisconnectionsFromDisabledToS_100a841b4._8_8_;
  *(undefined8 *)pcVar13 = uVar4;
  *(undefined8 *)(pcVar13 + 0x18) = uVar21;
  *(undefined8 *)(pcVar13 + 0x10) = uVar5;
  pcVar13[0x27] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_e0);
  if ((int)pmVar14 != 0) {
    uVar24 = CONCAT11(0,(byte)uStack_e0);
    *(ushort *)(param_1 + 0x9c) = uVar24;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    uVar21 = auStack_c8._28_8_;
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._30_2_ = 0;
      auStack_c8._28_2_ = uVar24;
      auStack_c8._32_4_ = SUB84(uVar21,4);
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"NumDisconnectionsFromDisabledToStageOne %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x27);
  *(ulong *)(pcVar13 + 0x1f) =
       CONCAT71(s_NumDisconnectionsFromStageOneToD_100a841dc._32_7_,
                s_NumDisconnectionsFromStageOneToD_100a841dc[0x1f]);
  uVar5 = s_NumDisconnectionsFromStageOneToD_100a841dc._16_8_;
  uVar4 = s_NumDisconnectionsFromStageOneToD_100a841dc._0_8_;
  uVar21 = CONCAT17(s_NumDisconnectionsFromStageOneToD_100a841dc[0x1f],
                    s_NumDisconnectionsFromStageOneToD_100a841dc._24_7_);
  *(undefined8 *)(pcVar13 + 8) = s_NumDisconnectionsFromStageOneToD_100a841dc._8_8_;
  *(undefined8 *)pcVar13 = uVar4;
  *(undefined8 *)(pcVar13 + 0x18) = uVar21;
  *(undefined8 *)(pcVar13 + 0x10) = uVar5;
  pcVar13[0x27] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_e0);
  if ((int)pmVar14 != 0) {
    uVar24 = CONCAT11(0,(byte)uStack_e0);
    *(ushort *)(param_1 + 0x9d) = uVar24;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    uVar21 = auStack_c8._28_8_;
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._30_2_ = 0;
      auStack_c8._28_2_ = uVar24;
      auStack_c8._32_4_ = SUB84(uVar21,4);
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"NumDisconnectionsFromStageOneToDisabled %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  afStack_ec[2] = 0.0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x22);
  pcVar13[0x20] = 'n';
  uVar5 = s_TimeDurationFromDisabledToStageO_100a84204._24_8_;
  uVar4 = s_TimeDurationFromDisabledToStageO_100a84204._16_8_;
  uVar21 = s_TimeDurationFromDisabledToStageO_100a84204._0_8_;
  pcVar13[0x21] = 'e';
  *(undefined8 *)(pcVar13 + 8) = s_TimeDurationFromDisabledToStageO_100a84204._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x22] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 2);
  fVar26 = afStack_ec[2];
  if ((int)pmVar14 != 0) {
    *(float *)((long)param_1 + 0x4e4) = afStack_ec[2];
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = fVar26;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"TimeDurationFromDisabledToStageOne %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x22);
  pcVar13[0x20] = 'e';
  uVar5 = s_TimeDurationFromStageOneToDisabl_100a84227._24_8_;
  uVar4 = s_TimeDurationFromStageOneToDisabl_100a84227._16_8_;
  uVar21 = s_TimeDurationFromStageOneToDisabl_100a84227._0_8_;
  pcVar13[0x21] = 'd';
  *(undefined8 *)(pcVar13 + 8) = s_TimeDurationFromStageOneToDisabl_100a84227._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x22] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 2);
  fVar26 = afStack_ec[2];
  if ((int)pmVar14 != 0) {
    *(float *)((long)param_1 + 0x4ec) = afStack_ec[2];
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = fVar26;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"TimeDurationFromStageOneToDisabled %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  afStack_ec[1] = -NAN;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x16);
  *(ulong *)(pcVar13 + 0xe) =
       CONCAT62(s_ConnRSSIStageOneFindMy_100a8424a._16_6_,s_ConnRSSIStageOneFindMy_100a8424a._14_2_)
  ;
  uVar21 = s_ConnRSSIStageOneFindMy_100a8424a._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT26(s_ConnRSSIStageOneFindMy_100a8424a._14_2_,s_ConnRSSIStageOneFindMy_100a8424a._8_6_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x16] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)(param_1 + 0xad) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"ConnRSSIStageOneFindMy %d overridden",auStack_c8 + 0x18,8
                   );
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x16);
  *(ulong *)(pcVar13 + 0xe) =
       CONCAT62(s_ConnRSSIStageOneMagnet_100a84261._16_6_,s_ConnRSSIStageOneMagnet_100a84261._14_2_)
  ;
  uVar21 = s_ConnRSSIStageOneMagnet_100a84261._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT26(s_ConnRSSIStageOneMagnet_100a84261._14_2_,s_ConnRSSIStageOneMagnet_100a84261._8_6_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x16] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x569) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"ConnRSSIStageOneMagnet %d overridden",auStack_c8 + 0x18,8
                   );
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1d);
  uVar21 = CONCAT53(s_ConnRSSIStageOneExternal_Lock_100a84278._16_5_,
                    s_ConnRSSIStageOneExternal_Lock_100a84278._13_3_);
  *(undefined8 *)(pcVar13 + 0x15) = s_ConnRSSIStageOneExternal_Lock_100a84278._21_8_;
  *(undefined8 *)(pcVar13 + 0xd) = uVar21;
  uVar21 = s_ConnRSSIStageOneExternal_Lock_100a84278._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT35(s_ConnRSSIStageOneExternal_Lock_100a84278._13_3_,
                s_ConnRSSIStageOneExternal_Lock_100a84278._8_5_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1d] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x56a) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"ConnRSSIStageOneExternal_Lock %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1d);
  uVar21 = CONCAT53(s_ConnRSSIStageOneDigitalCarKey_100a84296._16_5_,
                    s_ConnRSSIStageOneDigitalCarKey_100a84296._13_3_);
  *(undefined8 *)(pcVar13 + 0x15) = s_ConnRSSIStageOneDigitalCarKey_100a84296._21_8_;
  *(undefined8 *)(pcVar13 + 0xd) = uVar21;
  uVar21 = s_ConnRSSIStageOneDigitalCarKey_100a84296._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT35(s_ConnRSSIStageOneDigitalCarKey_100a84296._13_3_,
                s_ConnRSSIStageOneDigitalCarKey_100a84296._8_5_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1d] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x56b) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"ConnRSSIStageOneDigitalCarKey %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1e);
  uVar21 = CONCAT62(s_ConnRSSIStageOneDigitalHomeKey_100a842b4._16_6_,
                    s_ConnRSSIStageOneDigitalHomeKey_100a842b4._14_2_);
  *(undefined8 *)(pcVar13 + 0x16) = s_ConnRSSIStageOneDigitalHomeKey_100a842b4._22_8_;
  *(undefined8 *)(pcVar13 + 0xe) = uVar21;
  uVar21 = s_ConnRSSIStageOneDigitalHomeKey_100a842b4._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT26(s_ConnRSSIStageOneDigitalHomeKey_100a842b4._14_2_,
                s_ConnRSSIStageOneDigitalHomeKey_100a842b4._8_6_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1e] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x56c) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"ConnRSSIStageOneDigitalHomeKey %d overridden",
                    auStack_c8 + 0x18,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x20);
  uVar5 = s_ConfigureCreateConnectionEnabled_100a842d3._24_8_;
  uVar4 = s_ConfigureCreateConnectionEnabled_100a842d3._16_8_;
  uVar21 = s_ConfigureCreateConnectionEnabled_100a842d3._0_8_;
  *(undefined8 *)(pcVar13 + 8) = s_ConfigureCreateConnectionEnabled_100a842d3._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x20] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x48))(pmVar14,auStack_c8 + 0x18,auStack_c8,(long)param_1 + 0x48d)
  ;
  pmVar23 = pmRam0000000100cae4e8;
  if (((int)pmVar14 != 0) &&
     (pmVar14 = pmRam0000000100cae4e8, _os_log_type_enabled(pmRam0000000100cae4e8,0),
     uVar21 = auStack_c8._28_8_, (int)pmVar14 != 0)) {
    auStack_c8._24_4_ = (undefined4)_UNK_100930510;
    auStack_c8._29_3_ = 0;
    auStack_c8[0x1c] = *(byte *)((long)param_1 + 0x48d);
    auStack_c8._32_4_ = SUB84(uVar21,4);
    pmVar14 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar23,0,"ConfigureCreateConnectionEnabled is set to %d (overridden)"
                  ,auStack_c8 + 0x18,8);
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1d);
  uVar21 = CONCAT53(s_ConnRSSIStageOneThirdPartyApp_100a842f4._16_5_,
                    s_ConnRSSIStageOneThirdPartyApp_100a842f4._13_3_);
  *(undefined8 *)(pcVar13 + 0x15) = s_ConnRSSIStageOneThirdPartyApp_100a842f4._21_8_;
  *(undefined8 *)(pcVar13 + 0xd) = uVar21;
  uVar21 = s_ConnRSSIStageOneThirdPartyApp_100a842f4._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT35(s_ConnRSSIStageOneThirdPartyApp_100a842f4._13_3_,
                s_ConnRSSIStageOneThirdPartyApp_100a842f4._8_5_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1d] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x56d) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,
                    "LEConnectionThirdPartyAppStageOneThresholdRssi %d overridden",auStack_c8 + 0x18
                    ,8);
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x19);
  uVar21 = CONCAT17(s_ConnRSSIStageOneLECarPlay_100a84312[0x10],
                    s_ConnRSSIStageOneLECarPlay_100a84312._9_7_);
  *(undefined8 *)(pcVar13 + 0x11) = s_ConnRSSIStageOneLECarPlay_100a84312._17_8_;
  *(undefined8 *)(pcVar13 + 9) = uVar21;
  uVar21 = s_ConnRSSIStageOneLECarPlay_100a84312._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT71(s_ConnRSSIStageOneLECarPlay_100a84312._9_7_,s_ConnRSSIStageOneLECarPlay_100a84312[8]
               );
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x19] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec + 1);
  if ((int)pmVar14 != 0) {
    cVar3 = SUB41(afStack_ec[1],0);
    *(char *)((long)param_1 + 0x56e) = cVar3;
    pmVar23 = pmRam0000000100cae4e8;
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = (int)cVar3;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,"LEConnectionLECarPlayStageOneThresholdRssi %d overridden"
                    ,auStack_c8 + 0x18,8);
    }
  }
  afStack_ec[0] = 0.0;
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x1c);
  uVar21 = CONCAT44(s_ConnScanTimeoutExtendPercent_100a8432c._16_4_,
                    s_ConnScanTimeoutExtendPercent_100a8432c._12_4_);
  *(undefined8 *)(pcVar13 + 0x14) = s_ConnScanTimeoutExtendPercent_100a8432c._20_8_;
  *(undefined8 *)(pcVar13 + 0xc) = uVar21;
  uVar21 = s_ConnScanTimeoutExtendPercent_100a8432c._0_8_;
  *(ulong *)(pcVar13 + 8) =
       CONCAT44(s_ConnScanTimeoutExtendPercent_100a8432c._12_4_,
                s_ConnScanTimeoutExtendPercent_100a8432c._8_4_);
  *(undefined8 *)pcVar13 = uVar21;
  pcVar13[0x1c] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x68))(pmVar14,auStack_c8 + 0x18,auStack_c8,afStack_ec);
  fVar26 = afStack_ec[0];
  pmVar23 = pmRam0000000100cae4e8;
  if ((int)pmVar14 != 0) {
    pmVar14 = pmRam0000000100cae4e8;
    if (afStack_ec[0] <= 0.0) {
      _os_log_type_enabled(pmRam0000000100cae4e8,0x10);
      if ((int)pmVar14 != 0) {
        FUN_1008fc1b0(fVar26);
        pmVar14 = pmVar23;
      }
    }
    else {
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._28_8_ = (undefined8)fVar26;
        auStack_c8._24_4_ = (undefined4)_UNK_100930ae8;
        pmVar14 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar23,0,"Set ConnScanTimeoutExtendPercent %f percent",
                      auStack_c8 + 0x18,0xc);
        fVar26 = afStack_ec[0];
      }
      *(float *)((long)param_1 + 0x58c) = fVar26;
    }
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x28);
  *(undefined8 *)(pcVar13 + 0x20) = s_ConnectionDenyListTimeoutSeconds_100a84349._32_8_;
  uVar5 = s_ConnectionDenyListTimeoutSeconds_100a84349._24_8_;
  uVar4 = s_ConnectionDenyListTimeoutSeconds_100a84349._16_8_;
  uVar21 = s_ConnectionDenyListTimeoutSeconds_100a84349._0_8_;
  *(undefined8 *)(pcVar13 + 8) = s_ConnectionDenyListTimeoutSeconds_100a84349._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x28] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  iVar12 = 0;
  if (0 < (int)uStack_94) {
    iVar12 = (int)pmVar14;
  }
  if (iVar12 == 1) {
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = uVar25;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,
                    "Warning: LeConnectionDenyList: Using override value (%d) for fLeConnectionDenyListTimeoutSec"
                    ,auStack_c8 + 0x18,8);
      uVar25 = uStack_94;
    }
    *(uint *)((long)param_1 + 0x63c) = uVar25;
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x29);
  uVar21 = CONCAT17(s_ConnectionDenyListIntervalSecond_100a84372[0x20],
                    s_ConnectionDenyListIntervalSecond_100a84372._25_7_);
  *(undefined8 *)(pcVar13 + 0x21) = s_ConnectionDenyListIntervalSecond_100a84372._33_8_;
  *(undefined8 *)(pcVar13 + 0x19) = uVar21;
  uVar5 = s_ConnectionDenyListIntervalSecond_100a84372._16_8_;
  uVar4 = s_ConnectionDenyListIntervalSecond_100a84372._0_8_;
  uVar21 = CONCAT71(s_ConnectionDenyListIntervalSecond_100a84372._25_7_,
                    s_ConnectionDenyListIntervalSecond_100a84372[0x18]);
  *(undefined8 *)(pcVar13 + 8) = s_ConnectionDenyListIntervalSecond_100a84372._8_8_;
  *(undefined8 *)pcVar13 = uVar4;
  *(undefined8 *)(pcVar13 + 0x18) = uVar21;
  *(undefined8 *)(pcVar13 + 0x10) = uVar5;
  pcVar13[0x29] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  iVar12 = 0;
  if (0 < (int)uStack_94) {
    iVar12 = (int)pmVar14;
  }
  if (iVar12 == 1) {
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = uVar25;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,
                    "Warning: LeConnectionDenyList: Using override value (%d) for fLeConnectionDenyListIntervalSec"
                    ,auStack_c8 + 0x18,8);
      uVar25 = uStack_94;
    }
    *(uint *)(param_1 + 199) = uVar25;
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x28);
  *(undefined8 *)(pcVar13 + 0x20) = s_ConnectionDenyListCountThreshold_100a8439c._32_8_;
  uVar5 = s_ConnectionDenyListCountThreshold_100a8439c._24_8_;
  uVar4 = s_ConnectionDenyListCountThreshold_100a8439c._16_8_;
  uVar21 = s_ConnectionDenyListCountThreshold_100a8439c._0_8_;
  *(undefined8 *)(pcVar13 + 8) = s_ConnectionDenyListCountThreshold_100a8439c._8_8_;
  *(undefined8 *)pcVar13 = uVar21;
  *(undefined8 *)(pcVar13 + 0x18) = uVar5;
  *(undefined8 *)(pcVar13 + 0x10) = uVar4;
  pcVar13[0x28] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  uVar25 = uStack_94;
  pmVar23 = pmRam0000000100cae4e8;
  iVar12 = 0;
  if (0 < (int)uStack_94) {
    iVar12 = (int)pmVar14;
  }
  if (iVar12 == 1) {
    pmVar14 = pmRam0000000100cae4e8;
    _os_log_type_enabled(pmRam0000000100cae4e8,0);
    if ((int)pmVar14 != 0) {
      auStack_c8._24_4_ = (undefined4)_UNK_100930510;
      auStack_c8._28_4_ = uVar25;
      pmVar14 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar23,0,
                    "Warning: LeConnectionDenyList: Using override value (%d) for fLeConnectionDenyListCountThreshold"
                    ,auStack_c8 + 0x18,8);
      uVar25 = uStack_94;
    }
    *(uint *)(param_1 + 200) = uVar25;
  }
  *(undefined1 *)((long)param_1 + 0x6a1) = 1;
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar14 + 0x198))();
  if ((int)pmVar14 != 0) {
    *(undefined1 *)((long)param_1 + 0x6a1) = 0;
  }
  FUN_1000110f0();
  puVar15 = (undefined2 *)(auStack_c8 + 0x18);
  FUN_1001ec44c(puVar15,2);
  *puVar15 = 0x454c;
  *(undefined1 *)(puVar15 + 1) = 0;
  pcVar13 = auStack_c8;
  FUN_1001ec44c(pcVar13,0x2e);
  uVar21 = CONCAT62(s_MRCConfigForExtendedRangeUseCase_100a843c5._32_6_,
                    s_MRCConfigForExtendedRangeUseCase_100a843c5._30_2_);
  *(undefined8 *)(pcVar13 + 0x26) = s_MRCConfigForExtendedRangeUseCase_100a843c5._38_8_;
  *(undefined8 *)(pcVar13 + 0x1e) = uVar21;
  uVar5 = s_MRCConfigForExtendedRangeUseCase_100a843c5._16_8_;
  uVar4 = s_MRCConfigForExtendedRangeUseCase_100a843c5._0_8_;
  uVar21 = CONCAT26(s_MRCConfigForExtendedRangeUseCase_100a843c5._30_2_,
                    s_MRCConfigForExtendedRangeUseCase_100a843c5._24_6_);
  *(undefined8 *)(pcVar13 + 8) = s_MRCConfigForExtendedRangeUseCase_100a843c5._8_8_;
  *(undefined8 *)pcVar13 = uVar4;
  *(undefined8 *)(pcVar13 + 0x18) = uVar21;
  *(undefined8 *)(pcVar13 + 0x10) = uVar5;
  pcVar13[0x2e] = '\0';
  (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
  iVar12 = 0;
  if (0 < (int)uStack_94) {
    iVar12 = (int)pmVar14;
  }
  if (iVar12 == 1) {
    FUN_1000110f0();
    puVar15 = (undefined2 *)(auStack_c8 + 0x18);
    FUN_1001ec44c(puVar15,2);
    *puVar15 = 0x454c;
    *(undefined1 *)(puVar15 + 1) = 0;
    pcVar13 = auStack_c8;
    FUN_1001ec44c(pcVar13,0x20);
    uVar5 = s_MRCConfigForExtendedRangeUseCase_100a843f4._24_8_;
    uVar4 = s_MRCConfigForExtendedRangeUseCase_100a843f4._16_8_;
    uVar21 = s_MRCConfigForExtendedRangeUseCase_100a843f4._0_8_;
    *(undefined8 *)(pcVar13 + 8) = s_MRCConfigForExtendedRangeUseCase_100a843f4._8_8_;
    *(undefined8 *)pcVar13 = uVar21;
    *(undefined8 *)(pcVar13 + 0x18) = uVar5;
    *(undefined8 *)(pcVar13 + 0x10) = uVar4;
    pcVar13[0x20] = '\0';
    (**(code **)(*(long *)pmVar14 + 0x58))(pmVar14,auStack_c8 + 0x18,auStack_c8,&uStack_94);
    pmVar23 = pmRam0000000100cae4e8;
    if ((int)pmVar14 != 0) {
      pmVar14 = pmRam0000000100cae4e8;
      _os_log_type_enabled(pmRam0000000100cae4e8,0);
      if ((int)pmVar14 != 0) {
        auStack_c8._24_4_ = (undefined4)_UNK_100930510;
        auStack_c8._28_4_ = uStack_94;
        __os_log_impl(0x100000000,pmVar23,0,
                      "Warning: Using override value (%d) for MRCConfigForExtendedRangeUseCase",
                      auStack_c8 + 0x18,8);
      }
      *(char *)((long)param_1 + 0x6a1) = (char)uStack_94;
    }
  }
  puVar19 = PTR__OBJC_CLASS___CMMotionActivityManager_100bfc430;
  _objc_opt_new();
  param_1[0xcc] = puVar19;
  puVar19 = PTR__OBJC_CLASS___NSOperationQueue_100bfc898;
  _objc_opt_new();
  uVar21 = param_1[0xcd];
  param_1[0xcd] = puVar19;
  objc_stub::FUN_100921420(param_1[0xcd],uVar21,1);
  uVar21 = 0;
  _dispatch_queue_attr_make_with_autorelease_frequency(0,1);
  pcVar13 = "com.apple.bluetooth.motionActivity";
  _dispatch_queue_create("com.apple.bluetooth.motionActivity",uVar21);
  objc_stub::FUN_100923500(param_1[0xcd],pcVar13);
  param_1[0xe] = 0;
  *(undefined2 *)(param_1 + 0xf) = 0;
  return param_1;
}

