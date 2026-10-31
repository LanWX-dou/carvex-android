/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003cec64
 * original code SHA256: 9d183be0e7b01ea09188628654b26c4a3040353bfaf46362dc1d8bf33b1049b3
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003cec64(undefined8 param_1,long *param_2,long *param_3,undefined8 param_4,
                  undefined8 param_5)

{
  ushort uVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ushort uVar7;
  short sVar8;
  short sVar9;
  ushort uStack_86;
  uint uStack_84;
  undefined8 uStack_80;
  undefined2 uStack_78;
  ushort uStack_76;
  undefined4 uStack_74;
  undefined8 uStack_70;
  long *plStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_70 = 0;
  plStack_68 = (long *)0x0;
  uStack_74 = 0;
  uStack_80 = 0;
  FUN_1001b74c4(param_5,&uStack_80);
  plVar3 = param_2;
  FUN_1003cf074(param_2,&uStack_70);
  if ((int)plVar3 != 0) goto LAB_1003cee18;
  if (*(char *)((long)param_2 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                  ,0x55b,"(*requestBS).__RWFlag == BYTESTREAM_READ");
  }
  if (*(char *)((long)param_2 + 0xf) == '\0') {
    uVar7 = *(ushort *)((long)param_2 + 0xc);
    if ((int)((uint)*(ushort *)((long)param_2 + 10) - (uint)uVar7) < 2) goto LAB_1003cee0c;
    uVar1 = *(ushort *)(*param_2 + (ulong)uVar7);
    *(ushort *)((long)param_2 + 0xc) = uVar7 + 2;
    if (6 < ((uint)(uVar1 >> 8) | (uVar1 & 0xff00ff) << 8)) {
      plVar3 = param_2;
      FUN_1003cf4d8(param_2,&uStack_60);
      if (((int)plVar3 == 0) &&
         (FUN_1003cf0f0(param_2,&uStack_76), plVar3 = param_2, (int)param_2 == 0)) {
        uStack_78 = 0;
        plVar3 = param_3;
        FUN_1003cf55c(param_3,(uint)(uVar1 >> 8) | (uVar1 & 0xff00ff) << 8,param_4,&uStack_78);
        if ((int)plVar3 == 0) {
          uVar7 = uStack_76;
          if (uStack_76 == 0) {
            uStack_84 = 0;
            uStack_74 = uStack_74 & 0xffff;
            sVar8 = 0;
            while( true ) {
              plVar3 = plStack_68;
              FUN_1003cb688(plStack_68,uStack_70._2_2_,(long)&uStack_74 + 2,&uStack_84,uStack_80);
              if ((int)plVar3 != 0) break;
              plVar3 = (long *)(ulong)uStack_84;
              FUN_1003cf640(plVar3,&uStack_60,&uStack_86,param_5);
              if ((int)plVar3 != 0) goto LAB_1003cee18;
              sVar9 = 2;
              if (0xff < uStack_86) {
                sVar9 = 3;
              }
              if (uStack_86 != 0) {
                sVar8 = uStack_86 + sVar8 + sVar9;
              }
            }
            if ((int)plVar3 != 0x337) goto LAB_1003cee18;
            FUN_1003cf738(param_3,sVar8,&uStack_76);
            uVar7 = uStack_76;
          }
          sVar8 = *(short *)((long)param_3 + 0xc);
          uStack_74 = (uint)uVar7;
          do {
            do {
              uStack_84 = 0;
              plVar3 = plStack_68;
              FUN_1003cb688(plStack_68,uStack_70._2_2_,(long)&uStack_74 + 2,&uStack_84,uStack_80);
              if ((int)plVar3 != 0) {
                if ((int)plVar3 == 0x337) goto LAB_1003cef10;
                goto LAB_1003cee18;
              }
              plVar3 = (long *)(ulong)uStack_84;
              FUN_1003cf640(plVar3,&uStack_60,&uStack_86,param_5);
              if ((int)plVar3 != 0) goto LAB_1003cee18;
            } while (uStack_86 == 0);
            plVar3 = param_3;
            FUN_1003cf738(param_3,uStack_86,&uStack_74);
            if ((int)plVar3 == 0) break;
            uVar4 = (ulong)uStack_84;
            FUN_1003cf99c(uVar4,&uStack_60,&uStack_74,param_3,param_5);
          } while ((uVar4 & 1) != 0);
          sVar8 = (*(short *)((long)param_3 + 0xc) - sVar8) + uVar7;
          if (sVar8 == 0) {
            FUN_1000f9438();
LAB_1003cef10:
            sVar8 = 0;
          }
          if ((short)uStack_74 == 0) {
            FUN_1003cfac0(param_3,uStack_78,sVar8);
            FUN_1003cf2dc(param_3,7,param_1);
            FUN_1003160d4(&uStack_70);
            FUN_1003160d4(&uStack_60);
            return;
          }
          plVar3 = (long *)0x325;
        }
      }
      goto LAB_1003cee18;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                  ,0x55b,
                  "OI_STATUS ServiceSearchAttributeRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                 );
LAB_1003cee0c:
    *(undefined1 *)((long)param_2 + 0xf) = 1;
  }
  plVar3 = (long *)0x323;
LAB_1003cee18:
  iVar2 = 2;
  FUN_10000d938(2,0x35);
  if (iVar2 != 0) {
    FUN_10000d120("Error response to service search request: %!");
    uVar5 = 0x35;
    FUN_10000e9d4();
    uVar6 = uVar5;
    _os_log_type_enabled();
    if ((int)uVar6 != 0) {
      FUN_10018f150(uVar5);
    }
  }
  if (*param_3 != 0) {
    FUN_1000110b8();
  }
  FUN_1003160d4(&uStack_70);
  FUN_1003160d4(&uStack_60);
  FUN_1003ce064(plVar3,param_1,param_3);
  return;
}

