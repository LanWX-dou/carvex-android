/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003ca1d8
 * original code SHA256: ab5a503d7d5d7629bd833f5dc9f0f1ed714c08c2c11490716ddc67305e1891de
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003ca1d8(long *param_1)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  code *pcVar7;
  int *piVar8;
  long lVar9;
  ushort uVar10;
  uint uVar11;
  ushort uVar12;
  ushort uVar13;
  ulong unaff_x30;
  
  if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x3ff,"(*Response).__RWFlag == BYTESTREAM_READ");
  }
  if (*(char *)((long)param_1 + 0xf) == '\0') {
    uVar10 = *(ushort *)((long)param_1 + 0xc);
    if (1 < (int)((uint)*(ushort *)((long)param_1 + 10) - (uint)uVar10)) {
      uVar13 = *(ushort *)(*param_1 + (ulong)uVar10);
      uVar2 = uVar10 + 2;
      uVar5 = (ushort)uVar2;
      *(ushort *)((long)param_1 + 0xc) = uVar5;
      uVar4 = *(ushort *)((long)param_1 + 10);
      if (1 < (int)((uint)uVar4 - (uVar2 & 0xffff))) {
        uVar2 = (uint)(uVar13 >> 8) | (uVar13 & 0xff00ff) << 8;
        lVar9 = *param_1;
        uVar13 = *(ushort *)(lVar9 + (ulong)uVar5);
        uVar6 = (uint)(uVar13 >> 8) | (uVar13 & 0xff00ff) << 8;
        uVar10 = uVar10 + 4;
        *(ushort *)((long)param_1 + 0xc) = uVar10;
        piVar8 = piRam0000000100c383a0;
        if (uVar2 < uVar6) {
          return;
        }
        if (uVar6 == 0) {
          uVar13 = *(ushort *)((long)piRam0000000100c383a0 + 0x32);
          uVar5 = *(ushort *)(piRam0000000100c383a0 + 0xc);
        }
        else {
          uVar11 = 0;
          uVar5 = *(ushort *)(piRam0000000100c383a0 + 0xc);
          uVar12 = *(ushort *)((long)piRam0000000100c383a0 + 0x32);
          do {
            if (uVar5 == uVar12) {
              return;
            }
            if ((int)(uVar4 - 3) <= (int)(uint)uVar10) goto LAB_1003ca2c4;
            uVar1 = (ulong)uVar10;
            uVar10 = uVar10 + 4;
            uVar3 = *(uint *)(lVar9 + uVar1);
            *(ushort *)((long)param_1 + 0xc) = uVar10;
            uVar3 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
            uVar13 = uVar12 + 1;
            *(ushort *)((long)piVar8 + 0x32) = uVar13;
            *(uint *)(*(long *)(piVar8 + 10) + (ulong)uVar12 * 4) = uVar3 >> 0x10 | uVar3 << 0x10;
            uVar11 = uVar11 + 1;
            uVar12 = uVar13;
          } while (uVar11 < uVar6);
        }
        if (((uint)uVar13 == (uint)uVar5) || (uVar2 == uVar13)) {
          *piVar8 = 1;
        }
        else {
          FUN_1003cac40();
          if ((int)param_1 != 0) {
            return;
          }
          piVar8 = piRam0000000100c383a0;
          if (*piRam0000000100c383a0 == 2) {
            if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
              pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003ca394);
              (*pcVar7)();
            }
            FUN_1003c9a00();
            return;
          }
        }
        (**(code **)(piVar8 + 0x14))
                  (*(undefined8 *)(piVar8 + 10),*(undefined2 *)((long)piVar8 + 0x32),0);
        FUN_1000110b8(*(undefined8 *)(piRam0000000100c383a0 + 10));
        piVar8 = piRam0000000100c383a0;
        piVar8[10] = 0;
        piVar8[0xb] = 0;
        return;
      }
      goto LAB_1003ca2c4;
    }
    *(undefined1 *)((long)param_1 + 0xf) = 1;
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                  ,0x3ff,"OI_STATUS ServiceRecordResponse(OI_BYTE_STREAM *)");
    *(undefined1 *)((long)param_1 + 0xf) = 1;
    if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
      FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                    ,0x400,"(*Response).__RWFlag == BYTESTREAM_READ");
    }
  }
  FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdp.c"
                ,0x400,"OI_STATUS ServiceRecordResponse(OI_BYTE_STREAM *)");
LAB_1003ca2c4:
  *(undefined1 *)((long)param_1 + 0xf) = 1;
  return;
}

