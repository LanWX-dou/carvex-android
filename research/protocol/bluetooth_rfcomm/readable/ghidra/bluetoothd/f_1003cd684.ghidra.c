/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003cd684
 * original code SHA256: e0901aca9b159cb142f14d750ef6ae462e7c8eb6b50ffbc24180a7427f0c09de
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1003cd684(undefined8 param_1,undefined8 param_2)

{
  ushort *puVar1;
  ushort uVar2;
  byte *pbVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined2 uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined4 uStack_70;
  undefined8 uStack_6c;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  uStack_58 = 0;
  uStack_60 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  iVar4 = 0;
  FUN_10000d938(0,0x35);
  if (iVar4 != 0) {
    FUN_10000d120(
                 "SDPSERVER OI_SDPSRV_RespondToStalledIncomingRequest: stalled cid is %u, accept: %d"
                 );
    uVar5 = 0x35;
    FUN_10000e9d4();
    uVar6 = uVar5;
    _os_log_type_enabled();
    if ((int)uVar6 != 0) {
      FUN_10000ea80();
      uStack_70 = (undefined4)_UNK_100930b20;
      uStack_6c = uVar6;
      __os_log_impl(0x100000000,uVar5,0," %{public}s",&uStack_70,0xc);
    }
  }
  pbVar3 = pbRam0000000100c38438;
  uVar8 = (ulong)*pbRam0000000100c38438;
  if (uVar8 != 0) {
    lVar9 = 0;
    lVar10 = lRam0000000100c38440 + 2;
    do {
      puVar1 = (ushort *)(lRam0000000100c38440 + lVar9 * 0x20);
      if (((char)puVar1[1] != '\0') && ((uint)*puVar1 == (uint)param_2)) {
        if ((int)param_1 == 0) goto LAB_1003cd818;
        *(undefined1 *)(puVar1 + 1) = 1;
        uVar2 = *(ushort *)(pbVar3 + 4);
        *(ushort *)(lVar10 + 2) = uVar2;
        if (uVar2 < 0x81) {
          uVar7 = 0x80;
LAB_1003cd7ec:
          *(undefined2 *)(lVar10 + 2) = uVar7;
        }
        else {
          lVar9 = 0x28;
          FUN_1003d7a1c();
          if (*(ushort *)(lVar9 + 8) < uVar2) {
            lVar9 = 0x28;
            FUN_1003d7a1c();
            uVar7 = *(undefined2 *)(lVar9 + 8);
            goto LAB_1003cd7ec;
          }
          uVar7 = *(undefined2 *)(lVar10 + 2);
        }
        uStack_50 = 0;
        uStack_48 = 0;
        uStack_60 = CONCAT26(0x304,CONCAT42(0x1388ffff,uVar7));
        uStack_58 = 0;
LAB_1003cd818:
        iVar4 = 0x3cd8c8;
        FUN_10036a6d4(&LAB_1003cd8c8,&LAB_1003cd988,&LAB_1003cda70,param_2,&uStack_60,param_1,
                      &UNK_100934bd0);
        if (iVar4 == 0) {
          return;
        }
        iVar4 = 2;
        FUN_10000d938(2,0x35);
        if (iVar4 != 0) {
          FUN_10000d120("SDPServer: L2CAP failed to complete the connection %!");
          uVar5 = 0x35;
          FUN_10000e9d4();
          uVar6 = uVar5;
          _os_log_type_enabled();
          if ((int)uVar6 != 0) {
            FUN_10018f150(uVar5);
          }
        }
        *(undefined1 *)(puVar1 + 1) = 0;
        return;
      }
      lVar9 = lVar9 + 1;
      lVar10 = lVar10 + 0x20;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  iVar4 = 2;
  FUN_10000d938(2,0x35);
  if (iVar4 != 0) {
    FUN_10000d120("stalled sdpclient is NULL");
    uVar5 = 0x35;
    FUN_10000e9d4();
    uVar6 = uVar5;
    _os_log_type_enabled();
    if ((int)uVar6 != 0) {
      FUN_10018f150(uVar5);
    }
  }
  return;
}

