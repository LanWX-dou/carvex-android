/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1006347c0
 * original code SHA256: 5c09eccbae67bd09114431e118d4fae237e88e91a9ea6ee83e4a64d17cb050f5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1006347c0(byte *param_1)

{
  uint uVar1;
  byte bVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_50;
  char *pcStack_4c;
  undefined2 uStack_44;
  char *pcStack_42;
  
  uVar3 = uRam0000000100cae4a0;
  lVar6 = lRam0000000100cae158;
  bVar2 = *param_1;
  if (bVar2 - 1 < 2) {
    if (*(int *)(lRam0000000100cae158 + 0x88) == 2) {
      *(undefined4 *)(lRam0000000100cae158 + 0x8c) = *(undefined4 *)(param_1 + 8);
      uVar3 = uRam0000000100cae4a0;
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar4 != 0) {
        uStack_50 = (undefined4)_UNK_100930b18;
        pcStack_4c = "SDP_PARSER_FOUND_ATTRIBUTE_ID_STATE";
        uStack_44 = 0x820;
        pcStack_42 = "SDP_PARSER_IDLE_STATE";
        __os_log_impl(0x100000000,uVar3,0,"SDP Client Parser State Change: %s -> %s\n",&uStack_50,
                      0x16);
        lVar6 = lRam0000000100cae158;
      }
      *(undefined4 *)(lVar6 + 0x88) = 0;
    }
    else if ((*(int *)(lRam0000000100cae158 + 0x88) == 1) && (*(int *)(param_1 + 8) == 0x201)) {
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar4 != 0) {
        uStack_50 = (undefined4)_UNK_100930b18;
        pcStack_4c = "SDP_PARSER_FOUND_SERVICE_CLASS_STATE";
        uStack_44 = 0x820;
        pcStack_42 = "SDP_PARSER_FOUND_ATTRIBUTE_ID_STATE";
        __os_log_impl(0x100000000,uVar3,0,"SDP Client Parser State Change: %s -> %s\n",&uStack_50,
                      0x16);
        lVar6 = lRam0000000100cae158;
      }
      *(undefined4 *)(lVar6 + 0x88) = 2;
    }
  }
  else if (bVar2 - 6 < 2) {
    if (*(short *)(param_1 + 2) != 0) {
      uVar5 = 0;
      do {
        FUN_1006347c0(*(long *)(param_1 + 8) + (uVar5 & 0xff) * 0x10);
        uVar1 = (int)uVar5 + 1;
        uVar5 = (ulong)uVar1;
      } while ((uVar1 & 0xff) < (uint)*(ushort *)(param_1 + 2));
    }
  }
  else if (bVar2 == 3) {
    uStack_58 = _UNK_10093a1e8;
    uStack_60 = _UNK_10093a1e0;
    FUN_10019da5c(param_1,&uStack_60);
    uVar3 = uRam0000000100cae4a0;
    if ((int)param_1 != 0) {
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar4 != 0) {
        if (*(uint *)(lRam0000000100cae158 + 0x88) < 4) {
          pcStack_4c = (&PTR_s_SDP_PARSER_IDLE_STATE_100bbddb8)
                       [*(uint *)(lRam0000000100cae158 + 0x88)];
        }
        else {
          pcStack_4c = "unknown sdp parser state";
        }
        uStack_50 = (undefined4)_UNK_100930b18;
        uStack_44 = 0x820;
        pcStack_42 = "SDP_PARSER_FOUND_SERVICE_CLASS_STATE";
        __os_log_impl(0x100000000,uVar3,0,"SDP Client Parser State Change: %s -> %s\n",&uStack_50,
                      0x16);
      }
      *(undefined4 *)(lRam0000000100cae158 + 0x88) = 1;
    }
  }
  return;
}

