/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003ce9c4
 * original code SHA256: 856ffb6d0fc08ead7dafa88bbda9d68f3c9522ce8d9fc7349ae2f948c09c53f9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003ce9c4(undefined8 param_1,long *param_2,long *param_3,undefined8 param_4,
                  undefined8 param_5)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long *plVar10;
  long *plVar11;
  undefined2 uStack_68;
  undefined2 uStack_66;
  short sStack_64;
  short sStack_62;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  uStack_60 = 0;
  uStack_58 = 0;
  sStack_64 = 0;
  if (*(char *)((long)param_2 + 0xf) == '\0') {
    uVar3 = *(ushort *)((long)param_2 + 10);
    uVar4 = *(ushort *)((long)param_2 + 0xc);
    if (5 < (ulong)uVar3 - (ulong)uVar4) {
      if (*(char *)((long)param_2 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x4cc,"(*requestBS).__RWFlag == BYTESTREAM_READ");
      }
      if ((int)((uint)uVar3 - (uint)uVar4) < 4) {
        *(undefined1 *)((long)param_2 + 0xf) = 1;
        FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x4cd,
                      "OI_STATUS ServiceAttributeRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                     );
LAB_1003ceb74:
        *(undefined1 *)((long)param_2 + 0xf) = 1;
      }
      else {
        uVar2 = *(uint *)(*param_2 + (ulong)uVar4);
        uVar1 = uVar4 + 4;
        uVar6 = (ushort)uVar1;
        *(ushort *)((long)param_2 + 0xc) = uVar6;
        if ((int)((uint)uVar3 - (uVar1 & 0xffff)) < 2) goto LAB_1003ceb74;
        uVar3 = *(ushort *)(*param_2 + (ulong)uVar6);
        *(ushort *)((long)param_2 + 0xc) = uVar4 + 6;
        if (6 < ((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8)) {
          plVar10 = param_2;
          FUN_1003cf4d8(param_2,&uStack_60);
          if (((int)plVar10 != 0) ||
             (FUN_1003cf0f0(param_2,&sStack_62), plVar10 = param_2, (int)param_2 != 0))
          goto LAB_1003cea34;
          uStack_66 = 0;
          plVar10 = param_3;
          FUN_1003cf55c(param_3,(uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8,param_4,&uStack_66);
          if ((int)plVar10 != 0) goto LAB_1003cea34;
          uVar1 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
          plVar11 = (long *)(ulong)(uVar1 >> 0x10 | uVar1 << 0x10);
          if (sStack_62 == 0) {
            plVar10 = plVar11;
            FUN_1003cf640(plVar11,&uStack_60,&uStack_68,param_5);
            if ((int)plVar10 != 0) goto LAB_1003cea34;
            FUN_1003cf738(param_3,uStack_68,&sStack_62);
          }
          sVar5 = *(short *)((long)param_3 + 0xc);
          sStack_64 = sStack_62;
          FUN_1003cf99c(plVar11,&uStack_60,&sStack_64,param_3,param_5);
          if (((ulong)plVar11 & 1) == 0) {
            sStack_62 = (*(short *)((long)param_3 + 0xc) - sVar5) + sStack_62;
            if (sStack_62 == 0) {
              FUN_1000f9438();
              goto LAB_1003cebd8;
            }
          }
          else {
LAB_1003cebd8:
            sStack_62 = 0;
          }
          if (sStack_64 == 0) {
            FUN_1003cfac0(param_3,uStack_66,sStack_62);
            FUN_1003cf2dc(param_3,5,param_1);
            FUN_1003160d4(&uStack_60);
            return;
          }
          plVar10 = (long *)0x325;
          goto LAB_1003cea34;
        }
      }
      plVar10 = (long *)0x323;
      goto LAB_1003cea34;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                  ,0x4c8,
                  "OI_STATUS ServiceAttributeRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                 );
  }
  plVar10 = (long *)0x324;
LAB_1003cea34:
  iVar7 = 2;
  FUN_10000d938(2,0x35);
  if (iVar7 != 0) {
    FUN_10000d120("Error response to service attribute request: %!");
    uVar8 = 0x35;
    FUN_10000e9d4();
    uVar9 = uVar8;
    _os_log_type_enabled();
    if ((int)uVar9 != 0) {
      FUN_10018f150(uVar8);
    }
  }
  if (*param_3 != 0) {
    FUN_1000110b8();
  }
  FUN_1003160d4(&uStack_60);
  FUN_1003ce064(plVar10,param_1,param_3);
  return;
}

