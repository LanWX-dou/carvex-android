/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c9720
 * original code SHA256: 07e7b5a5e2da67a0fafa81621a5410d8cd88e08ed0b1ecd6846bca8ae6ec4d8b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001003c990c) */
/* WARNING: Removing unreachable block (ram,0x0001003c99bc) */
/* WARNING: Removing unreachable block (ram,0x0001003c99e8) */

void FUN_1003c9720(undefined8 param_1,uint param_2,undefined8 param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined8 uVar5;
  long lVar6;
  char *pcVar7;
  undefined1 *puStack_50;
  ushort uStack_48;
  ushort uStack_46;
  ushort uStack_44;
  undefined2 uStack_42;
  
  piVar4 = piRam0000000100c383a0;
  if ((((iRam0000000100cade70 == 0) || (iVar3 = *piRam0000000100c383a0, iVar3 == 0 || iVar3 == 3))
      || (iVar3 == 2)) || (param_2 == 0)) {
    return;
  }
  *(short *)(piRam0000000100c383a0 + 0xc) = (short)param_2;
  *(undefined2 *)((long)piVar4 + 0x32) = 0;
  uVar5 = param_3;
  FUN_100314a48();
  if ((int)uVar5 == 0xfffe) {
    return;
  }
  uVar2 = (int)uVar5 + 0x18;
  if ((uint)*(ushort *)(piRam0000000100c383a0 + 3) < (uVar2 & 0xffff)) {
    return;
  }
  lVar6 = (ulong)param_2 << 2;
  FUN_10000d0cc(lVar6,0x100004052888210);
  piVar4 = piRam0000000100c383a0;
  *(long *)(piRam0000000100c383a0 + 10) = lVar6;
  if (lVar6 == 0) {
    return;
  }
  puStack_50 = *(undefined1 **)(piVar4 + 6);
  if (puStack_50 == (undefined1 *)0x0) {
    pcVar7 = "SDP_State->ReqBuffer";
LAB_1003c9958:
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x523,pcVar7);
  }
  if ((uVar2 & 0xffff) == 0) {
    pcVar7 = "(bufLen) > 0";
    goto LAB_1003c9958;
  }
  uStack_48 = (ushort)uVar2;
  uStack_42 = 2;
  *puStack_50 = 2;
  uStack_46 = uStack_48;
  if (0xfffffffffffffffb < ((ulong)uVar2 & 0xffff) - 5) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x52c,"ByteStream_NumReadBytesAvail(request) >= (2 * sizeof(uint16_t))");
  }
  uStack_44 = 5;
  FUN_100314cc4(&puStack_50,param_3);
  if (uStack_42._1_1_ == '\0') {
    if (1 < (int)((uint)uStack_46 - (uint)uStack_44)) {
      if ((char)uStack_42 == '\x02') {
        puStack_50[(ulong)uStack_44 + 1] = (char)piRam0000000100c383a0[0xc];
        puStack_50[uStack_44] = *(undefined1 *)((long)piRam0000000100c383a0 + 0x31);
        uVar1 = uStack_44 + 2;
        *(ushort *)(piRam0000000100c383a0 + 4) = uVar1;
        if ((ushort)(uStack_44 + 2) < uStack_46) {
          uStack_46 = uStack_44 + 3;
          puStack_50[uVar1] = 0;
          piVar4 = piRam0000000100c383a0;
          uStack_42 = 0xf;
          *(ushort *)((long)piRam0000000100c383a0 + 0x12) = uStack_46;
          *(undefined8 *)(piVar4 + 0x14) = param_1;
          *(undefined1 *)(piVar4 + 8) = 3;
          uStack_44 = uStack_46;
          FUN_1003c9a00();
          return;
        }
        uStack_44 = uVar1;
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                      ,0x53d,"ByteStream_NumReadBytesAvail(request) >= 1");
      }
      pcVar7 = "(request).__RWFlag == BYTESTREAM_WRITE";
      goto LAB_1003c99b4;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x534,
                  "OI_STATUS OI_SDP_SearchReq(OI_SDP_SEARCH_RSP_CB, uint16_t, const OI_DATAELEM *)")
    ;
  }
  pcVar7 = "ByteStream_NumReadBytesAvail(request) >= 2";
LAB_1003c99b4:
                    /* WARNING: Subroutine does not return */
  FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                ,0x534,pcVar7);
}

