/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c9ab8
 * original code SHA256: 64e7c427c2178a94d2c69ca9c2125b9c69ad64525a92ddbfa1014382b31cf8c6
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001003c9c3c) */

void FUN_1003c9ab8(undefined8 param_1,uint param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  short sVar5;
  int *piVar6;
  undefined8 uVar7;
  char *pcVar8;
  undefined1 *puStack_40;
  undefined8 uStack_38;
  
  if (iRam0000000100cade70 == 0) {
    return;
  }
  uStack_38 = 0;
  iVar2 = *piRam0000000100c383a0;
  if (iVar2 == 0 || iVar2 == 3) {
    return;
  }
  if (iVar2 == 2) {
    return;
  }
  uVar7 = param_3;
  FUN_1003c9d1c();
  if ((int)uVar7 != 0) {
    return;
  }
  uVar7 = param_3;
  FUN_100314a48();
  piVar6 = piRam0000000100c383a0;
  if ((int)uVar7 == 0) {
    return;
  }
  uVar1 = (int)uVar7 + 0x1c;
  if ((uint)*(ushort *)(piRam0000000100c383a0 + 3) < (uVar1 & 0xffff)) {
    return;
  }
  puStack_40 = *(undefined1 **)(piRam0000000100c383a0 + 6);
  if (puStack_40 == (undefined1 *)0x0) {
    pcVar8 = "SDP_State->ReqBuffer";
LAB_1003c9c88:
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x5b5,pcVar8);
  }
  if ((uVar1 & 0xffff) == 0) {
    pcVar8 = "(bufLen) > 0";
    goto LAB_1003c9c88;
  }
  uVar4 = (undefined2)uVar1;
  uStack_38 = CONCAT62(uStack_38._2_6_,uVar4);
  uStack_38 = CONCAT26(2,(undefined6)uStack_38);
  uStack_38._0_4_ = CONCAT22(uVar4,uVar4);
  *puStack_40 = 4;
  if (0xfffffffffffffffb < ((ulong)uVar1 & 0xffff) - 5) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x5be,"ByteStream_NumReadBytesAvail(request) >= (2 * sizeof(uint16_t))");
  }
  if ((uVar1 & 0xffff) < 9) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x5c2,"ByteStream_NumReadBytesAvail(request) >= 4");
  }
  uVar3 = (param_2 & 0xff00ff00) >> 8 | (param_2 & 0xff00ff) << 8;
  *(uint *)(puStack_40 + 5) = uVar3 >> 0x10 | uVar3 << 0x10;
  if ((uVar1 & 0xffff) < 0xb) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x5c3,"ByteStream_NumReadBytesAvail(request) >= 2");
  }
  puStack_40[10] = *(undefined1 *)((long)piVar6 + 0xe);
  puStack_40[9] = *(undefined1 *)((long)piVar6 + 0xf);
  uStack_38._0_6_ = CONCAT24(0xb,(undefined4)uStack_38);
  uStack_38 = CONCAT26(2,(undefined6)uStack_38);
  FUN_100314cc4(&puStack_40,param_3);
  *(ushort *)(piRam0000000100c383a0 + 4) = uStack_38._4_2_;
  if (uStack_38._7_1_ == '\0') {
    if ((uint)uStack_38._4_2_ <= (uint)uStack_38._2_2_ &&
        (uint)uStack_38._2_2_ != (uint)uStack_38._4_2_) {
      if (uStack_38._6_1_ == '\x02') {
        sVar5 = uStack_38._4_2_ + 1;
        puStack_40[(uint)uStack_38._4_2_] = 0;
        piVar6 = piRam0000000100c383a0;
        uStack_38._0_4_ = CONCAT22(sVar5,(undefined2)uStack_38);
        uStack_38 = (ulong)CONCAT16(0xf,CONCAT24(sVar5,(undefined4)uStack_38));
        *(short *)((long)piRam0000000100c383a0 + 0x12) = sVar5;
        *(undefined8 *)(piVar6 + 0x14) = param_1;
        *(undefined1 *)(piVar6 + 8) = 5;
        FUN_1003c9a00();
        return;
      }
      pcVar8 = "(request).__RWFlag == BYTESTREAM_WRITE";
      goto LAB_1003c9d14;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x5cd,
                  "OI_STATUS OI_SDP_AttributeReq(OI_SDP_ATTRIBUTE_RSP_CB, OI_SDP_SERVICE_RECORD_HANDLE, const OI_DATAELEM *)"
                 );
  }
  pcVar8 = "ByteStream_NumReadBytesAvail(request) >= 1";
LAB_1003c9d14:
                    /* WARNING: Subroutine does not return */
  FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                ,0x5cd,pcVar8);
}

