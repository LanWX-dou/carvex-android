/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003ce304
 * original code SHA256: 6c40020dbe3650711ad9c01523353ff159f63350e94088f620487016ff2f9da5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003ce304(undefined8 param_1,long *param_2,long *param_3,int param_4,undefined8 param_5)

{
  uint uVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  long *plVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  char *pcVar9;
  undefined1 uVar10;
  ushort uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  undefined8 uStack_80;
  ushort uStack_78;
  ushort uStack_76;
  undefined4 uStack_74;
  undefined8 uStack_70;
  long *plStack_68;
  
  uStack_70 = 0;
  plStack_68 = (long *)0x0;
  uStack_74 = 0;
  uStack_76 = 0;
  uStack_80 = 0;
  FUN_1001b74c4(param_5,&uStack_80);
  plVar6 = param_2;
  FUN_1003cf074(param_2,&uStack_70);
  if ((int)plVar6 != 0) {
    iVar5 = 2;
    FUN_10000d938(2,0x35);
    param_2 = plVar6;
    if (iVar5 != 0) {
      FUN_10000d120("SDPServer: ServiceSearchRequest bad UUID list");
      uVar7 = 0x35;
      FUN_10000e9d4();
      uVar8 = uVar7;
      _os_log_type_enabled();
      if ((int)uVar8 != 0) {
        FUN_10018f150(uVar7);
      }
    }
    goto LAB_1003ce45c;
  }
  if (*(char *)((long)param_2 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
    FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                  ,0x327,"(*requestBS).__RWFlag == BYTESTREAM_READ");
  }
  if (*(char *)((long)param_2 + 0xf) == '\0') {
    uVar3 = *(ushort *)((long)param_2 + 0xc);
    if ((int)((uint)*(ushort *)((long)param_2 + 10) - (uint)uVar3) < 2) goto LAB_1003ce450;
    bVar2 = ((undefined1 *)(*param_2 + (ulong)uVar3))[1];
    uVar13 = (uint)bVar2;
    uVar4 = (uint)CONCAT11(*(undefined1 *)(*param_2 + (ulong)uVar3),bVar2);
    *(ushort *)((long)param_2 + 0xc) = uVar3 + 2;
    if (uVar4 != 0) {
      FUN_1003cf0f0(param_2,&uStack_78);
      if ((int)param_2 != 0) goto LAB_1003ce45c;
      uVar12 = param_4 + 0x3fff4U >> 2;
      uVar1 = uVar4;
      if ((uVar12 & 0xffff) <= uVar4) {
        uVar1 = uVar12;
      }
      param_2 = param_3;
      FUN_1003cf1e8(param_3,uVar1 * 4 + 4 & 0xfffc);
      if ((int)param_2 != 0) goto LAB_1003ce45c;
      if (*(char *)((long)param_3 + 0xf) != '\0') {
        FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x34a,
                      "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                     );
LAB_1003ce828:
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x34a,"ByteStream_NumReadBytesAvail(*responseBS) >= (2 * sizeof(uint16_t))");
      }
      uVar3 = *(ushort *)((long)param_3 + 0xc);
      if ((ulong)*(ushort *)((long)param_3 + 10) - (ulong)uVar3 < 4) goto LAB_1003ce828;
      uVar15 = 0;
      uVar12 = 0;
      uVar14 = 0;
      *(ushort *)((long)param_3 + 0xc) = uVar3 + 4;
      do {
        param_2 = plStack_68;
        FUN_1003cb688(plStack_68,uStack_70._2_2_,&uStack_76,&uStack_74,uStack_80);
        uVar10 = (undefined1)(uVar12 >> 8);
        if ((int)param_2 != 0) {
          uVar13 = uVar14;
          if ((int)param_2 != 0x337) goto LAB_1003ce45c;
          break;
        }
        if ((uStack_78 < uStack_76) && ((uVar12 & 0xffff) < (uVar1 & 0xffff))) {
          if (*(char *)((long)param_3 + 0xf) == '\0') {
            if (3 < (int)((uint)*(ushort *)((long)param_3 + 10) -
                         (uint)*(ushort *)((long)param_3 + 0xc))) {
              if (*(char *)((long)param_3 + 0xe) != '\x02') {
                pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
                goto LAB_1003ce808;
              }
              *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc) + 3) = (char)uStack_74;
              *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc) + 2) =
                   (char)((uint)uStack_74 >> 8);
              *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc) + 1) =
                   (char)((uint)uStack_74 >> 0x10);
              *(undefined1 *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc)) = uStack_74._3_1_;
              *(short *)((long)param_3 + 0xc) = *(short *)((long)param_3 + 0xc) + 4;
              uVar12 = uVar12 + 1;
              uVar15 = (uint)uStack_76;
              uVar10 = (undefined1)(uVar12 >> 8);
              goto LAB_1003ce5e4;
            }
          }
          else {
            FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                          ,0x35e,
                          "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                         );
          }
          pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 4";
LAB_1003ce808:
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                        ,0x35e,pcVar9);
        }
LAB_1003ce5e4:
        uVar14 = uVar14 + 1;
      } while ((uVar14 & 0xffff) < uVar4);
      if (uVar15 < uStack_76) {
        if (*(char *)((long)param_3 + 0xf) == '\0') {
          uVar11 = *(ushort *)((long)param_3 + 0xc);
          if (uVar11 < *(ushort *)((long)param_3 + 10)) {
            if (*(char *)((long)param_3 + 0xe) != '\x02') {
              pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
              goto LAB_1003ce960;
            }
            *(ushort *)((long)param_3 + 0xc) = uVar11 + 1;
            *(undefined1 *)(*param_3 + (ulong)uVar11) = 2;
            if (*(char *)((long)param_3 + 0xf) == '\0') {
              if (1 < (int)((uint)*(ushort *)((long)param_3 + 10) -
                           (uint)*(ushort *)((long)param_3 + 0xc))) {
                if (*(char *)((long)param_3 + 0xe) != '\x02') {
                  pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
                  goto LAB_1003ce9bc;
                }
                *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc) + 1) = (char)uVar15;
                *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc)) = (char)(uVar15 >> 8);
                uVar11 = *(short *)((long)param_3 + 0xc) + 2;
                *(ushort *)((long)param_3 + 0xc) = uVar11;
                goto LAB_1003ce6dc;
              }
            }
            else {
              FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                            ,0x36d,
                            "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                           );
            }
            pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 2";
LAB_1003ce9bc:
                    /* WARNING: Subroutine does not return */
            FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                          ,0x36d,pcVar9);
          }
        }
        else {
          FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                        ,0x36c,
                        "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                       );
        }
        pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 1";
LAB_1003ce960:
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x36c,pcVar9);
      }
      if (*(char *)((long)param_3 + 0xf) == '\0') {
        uVar11 = *(ushort *)((long)param_3 + 0xc);
        if (uVar11 < *(ushort *)((long)param_3 + 10)) {
          if (*(char *)((long)param_3 + 0xe) != '\x02') {
            pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
            goto LAB_1003ce978;
          }
          *(ushort *)((long)param_3 + 0xc) = uVar11 + 1;
          *(undefined1 *)(*param_3 + (ulong)uVar11) = 0;
          uVar11 = *(ushort *)((long)param_3 + 0xc);
LAB_1003ce6dc:
          if ((uint)*(ushort *)((long)param_3 + 10) < (uint)uVar3) {
                    /* WARNING: Subroutine does not return */
            FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                          ,0x375,"(size_t)(paramPos) <= (size_t)((*responseBS).__size)");
          }
          *(ushort *)((long)param_3 + 0xc) = uVar3;
          if (*(char *)((long)param_3 + 0xf) == '\0') {
            if (1 < (int)((uint)*(ushort *)((long)param_3 + 10) - (uint)uVar3)) {
              if (*(char *)((long)param_3 + 0xe) == '\x02') {
                *(char *)(*param_3 + (ulong)uVar3 + 1) = (char)uVar13;
                *(char *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc)) = (char)(uVar14 >> 8);
                uVar3 = *(short *)((long)param_3 + 0xc) + 2;
                *(ushort *)((long)param_3 + 0xc) = uVar3;
                if (*(char *)((long)param_3 + 0xf) == '\0') {
                  if (1 < (int)((uint)*(ushort *)((long)param_3 + 10) - (uint)uVar3)) {
                    if (*(char *)((long)param_3 + 0xe) == '\x02') {
                      *(char *)(*param_3 + (ulong)uVar3 + 1) = (char)uVar12;
                      *(undefined1 *)(*param_3 + (ulong)*(ushort *)((long)param_3 + 0xc)) = uVar10;
                      *(short *)((long)param_3 + 0xc) = *(short *)((long)param_3 + 0xc) + 2;
                      if (uVar11 <= *(ushort *)((long)param_3 + 10)) {
                        *(ushort *)((long)param_3 + 0xc) = uVar11;
                        FUN_1003cf2dc(param_3,3,param_1);
                        FUN_1003160d4(&uStack_70);
                        return;
                      }
                    /* WARNING: Subroutine does not return */
                      FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                                    ,0x378,"(size_t)(contPos) <= (size_t)((*responseBS).__size)");
                    }
                    pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
                    goto LAB_1003ce8d8;
                  }
                }
                else {
                  FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                                ,0x377,
                                "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                               );
                }
                pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 2";
LAB_1003ce8d8:
                    /* WARNING: Subroutine does not return */
                FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                              ,0x377,pcVar9);
              }
              pcVar9 = "(*responseBS).__RWFlag == BYTESTREAM_WRITE";
              goto LAB_1003ce894;
            }
          }
          else {
            FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                          ,0x376,
                          "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                         );
          }
          pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 2";
LAB_1003ce894:
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                        ,0x376,pcVar9);
        }
      }
      else {
        FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                      ,0x36f,
                      "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                     );
      }
      pcVar9 = "ByteStream_NumReadBytesAvail(*responseBS) >= 1";
LAB_1003ce978:
                    /* WARNING: Subroutine does not return */
      FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                    ,0x36f,pcVar9);
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/sdp/sdpserver.c"
                  ,0x327,
                  "OI_STATUS ServiceSearchRequest(uint16_t, OI_BYTE_STREAM *, OI_BYTE_STREAM *, uint16_t, OI_L2CAP_CID)"
                 );
LAB_1003ce450:
    *(undefined1 *)((long)param_2 + 0xf) = 1;
  }
  param_2 = (long *)0x323;
LAB_1003ce45c:
  iVar5 = 2;
  FUN_10000d938(2,0x35);
  if (iVar5 != 0) {
    FUN_10000d120("Error response to service search request: %!");
    uVar7 = 0x35;
    FUN_10000e9d4();
    uVar8 = uVar7;
    _os_log_type_enabled();
    if ((int)uVar8 != 0) {
      FUN_10018f150(uVar7);
    }
  }
  if (*param_3 != 0) {
    FUN_1000110b8();
  }
  FUN_1003160d4(&uStack_70);
  FUN_1003ce064(param_2,param_1,param_3);
  return;
}

