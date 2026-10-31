/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c9dd8
 * original code SHA256: 6f0f94432f9d3923685cd6867edd0cf52e18eb73dfb42f88da14f1d3a5aff1ff
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001003c9fb4) */

void FUN_1003c9dd8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  char *pcVar6;
  undefined1 *puStack_50;
  ushort uStack_48;
  ushort uStack_46;
  ushort uStack_44;
  undefined2 uStack_42;
  
  if (((iRam0000000100cade70 == 0) || (iVar2 = *piRam0000000100c383a0, iVar2 == 0 || iVar2 == 3)) ||
     (iVar2 == 2)) {
    return;
  }
  uVar4 = param_2;
  FUN_100314a48();
  if ((int)uVar4 == 0) {
    return;
  }
  uVar5 = param_3;
  FUN_1003c9d1c();
  if ((int)uVar5 != 0) {
    return;
  }
  uVar5 = param_3;
  FUN_100314a48();
  if ((int)uVar5 == 0) {
    return;
  }
  uVar1 = (int)uVar4 + 0x18 + (int)uVar5;
  if ((uint)*(ushort *)(piRam0000000100c383a0 + 3) < (uVar1 & 0xffff)) {
    return;
  }
  puStack_50 = *(undefined1 **)(piRam0000000100c383a0 + 6);
  if (puStack_50 == (undefined1 *)0x0) {
    pcVar6 = "SDP_State->ReqBuffer";
LAB_1003ca000:
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x622,pcVar6);
  }
  if ((uVar1 & 0xffff) == 0) {
    pcVar6 = "(bufLen) > 0";
    goto LAB_1003ca000;
  }
  uStack_48 = (ushort)uVar1;
  uStack_42 = 2;
  *puStack_50 = 6;
  uStack_46 = uStack_48;
  if (0xfffffffffffffffb < ((ulong)uVar1 & 0xffff) - 5) {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x62b,"ByteStream_NumReadBytesAvail(request) >= (2 * sizeof(uint16_t))");
  }
  uStack_44 = 5;
  FUN_100314cc4(&puStack_50,param_2);
  if (uStack_42._1_1_ == '\0') {
    if (1 < (int)((uint)uStack_46 - (uint)uStack_44)) {
      if ((char)uStack_42 == '\x02') {
        puStack_50[(ulong)uStack_44 + 1] = *(undefined1 *)((long)piRam0000000100c383a0 + 0xe);
        puStack_50[uStack_44] = *(undefined1 *)((long)piRam0000000100c383a0 + 0xf);
        uStack_44 = uStack_44 + 2;
        FUN_100314cc4(&puStack_50,param_3);
        *(ushort *)(piRam0000000100c383a0 + 4) = uStack_44;
        if (uStack_42._1_1_ == '\0') {
          if ((uint)uStack_44 <= (uint)uStack_46 && (uint)uStack_46 != (uint)uStack_44) {
            if ((char)uStack_42 == '\x02') {
              uStack_46 = uStack_44 + 1;
              puStack_50[(uint)uStack_44] = 0;
              piVar3 = piRam0000000100c383a0;
              uStack_42 = 0xf;
              *(ushort *)((long)piRam0000000100c383a0 + 0x12) = uStack_46;
              *(undefined8 *)(piVar3 + 0x14) = param_1;
              *(undefined1 *)(piVar3 + 8) = 7;
              uStack_44 = uStack_46;
              FUN_1003c9a00();
              return;
            }
            pcVar6 = "(request).__RWFlag == BYTESTREAM_WRITE";
            goto LAB_1003ca0a0;
          }
        }
        else {
          FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                        ,0x63a,
                        "OI_STATUS OI_SDP_SearchAttributeReq(OI_SDP_SEARCH_ATTRIBUTE_RSP_CB, const OI_DATAELEM *, const OI_DATAELEM *)"
                       );
        }
        pcVar6 = "ByteStream_NumReadBytesAvail(request) >= 1";
LAB_1003ca0a0:
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                      ,0x63a,pcVar6);
      }
      pcVar6 = "(request).__RWFlag == BYTESTREAM_WRITE";
      goto LAB_1003ca05c;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x630,
                  "OI_STATUS OI_SDP_SearchAttributeReq(OI_SDP_SEARCH_ATTRIBUTE_RSP_CB, const OI_DATAELEM *, const OI_DATAELEM *)"
                 );
  }
  pcVar6 = "ByteStream_NumReadBytesAvail(request) >= 2";
LAB_1003ca05c:
                    /* WARNING: Subroutine does not return */
  FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                ,0x630,pcVar6);
}

