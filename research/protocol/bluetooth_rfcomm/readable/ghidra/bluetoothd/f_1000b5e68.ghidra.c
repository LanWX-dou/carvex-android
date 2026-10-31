/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b5e68
 * original code SHA256: 185f76f22ba7d063e1b82b165f553d3fb6071444b5cc2fd8366da6814d452db8
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_1000b5e68(long *param_1,byte param_2)

{
  ushort uVar1;
  undefined1 *puVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  short sVar8;
  uint uVar9;
  undefined3 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined1 *puVar13;
  undefined8 uVar14;
  char cVar15;
  ulong uVar16;
  undefined1 *puVar17;
  int iVar18;
  long lVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  undefined1 *puVar23;
  undefined4 uVar24;
  undefined4 uStack_c0;
  undefined8 uStack_bc;
  undefined8 uStack_b0;
  ulong uStack_a8;
  undefined1 *puStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  ulong uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  if (*(char *)((long)param_1 + 0xf) == '\0') {
    uVar5 = *(ushort *)((long)param_1 + 10);
    uVar6 = *(ushort *)((long)param_1 + 0xc);
    uStack_78 = 0;
    uStack_80 = 0;
    uStack_68 = 0;
    uStack_70 = 0;
    uStack_98 = 0;
    puStack_a0 = (undefined1 *)0x0;
    uStack_88 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    uStack_b0 = 0;
    if (9 < (uint)uVar5 - (uint)uVar6) {
      if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                      ,0x1b8,"(*pBs).__RWFlag == BYTESTREAM_READ");
      }
      if ((uint)uVar5 < (uint)uVar6 || (uint)uVar5 == (uint)uVar6) {
        *(undefined1 *)((long)param_1 + 0xf) = 1;
        iVar18 = 2;
        FUN_10000d938(2,0x42);
        if (iVar18 == 0) {
          return;
        }
        FUN_10000d120(
                     "Could not get the number of reports of the LE extended advertising report event"
                     );
        uVar11 = 0x42;
        FUN_10000e9d4();
        uVar14 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar14 == 0) {
          return;
        }
        FUN_100105b50(uVar11);
        return;
      }
      *(ushort *)((long)param_1 + 0xc) = uVar6 + 1;
      uVar14 = _UNK_100930b20;
      uStack_98 = (ulong)param_2 << 8;
      uStack_68 = 0x7f7f7f;
      uVar22 = (uint)*(byte *)(*param_1 + (ulong)(uint)uVar6);
      if (uVar22 == 0) {
        return;
      }
      uVar21 = 0;
      while( true ) {
        lVar19 = uStack_98;
        if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x1c4,"(*pBs).__RWFlag == BYTESTREAM_READ");
        }
        if (*(char *)((long)param_1 + 0xf) != '\0') break;
        uVar5 = *(ushort *)((long)param_1 + 0xc);
        if ((int)((uint)*(ushort *)((long)param_1 + 10) - (uint)uVar5) < 2) goto LAB_1000b64f0;
        bVar3 = *(byte *)(*param_1 + (ulong)uVar5);
        bVar4 = ((byte *)(*param_1 + (ulong)uVar5))[1];
        *(ushort *)((long)param_1 + 0xc) = uVar5 + 2;
        uVar20 = bVar3 & 0x1f;
        uStack_98._0_4_ = CONCAT22((short)uVar20,(undefined2)uStack_98);
        uStack_98._5_3_ = SUB83(lVar19,5);
        uStack_98 = CONCAT35(uStack_98._5_3_,CONCAT14(bVar3 >> 5,(undefined4)uStack_98)) &
                    0xffffff03ffffffff;
        uStack_88 = (ulong)CONCAT16(bVar3 >> 7,CONCAT15(bVar4,(undefined5)uStack_88)) &
                    0xffff3fffffffffff;
        uVar10 = (undefined3)uStack_88;
        uStack_88 = CONCAT17(bVar4 >> 7,
                             (int7)CONCAT35(uStack_88._5_3_,
                                            CONCAT14(bVar4 >> 6,(undefined4)uStack_88))) &
                    0xffffff01ffffffff;
        uVar9 = uVar20 - 0x10;
        if ((uVar9 < 0xe) && ((0x2c2dU >> (ulong)(uVar9 & 0x1f) & 1) != 0)) {
          cVar15 = (&UNK_1009342bd)[(int)uVar9];
        }
        else {
          uStack_88._0_4_ = CONCAT13(1,uVar10);
          iVar18 = 0;
          FUN_10000d938(0,0x42);
          uVar24 = (undefined4)uVar14;
          if ((bVar3 & 1) == 0) {
            if ((uVar20 >> 3 & 1) == 0) {
              if (iVar18 != 0) {
                FUN_10000d120("legacy=false LE_ADVERTISING_TYPE_NON_CONNECTABLE_UNDIRECTED");
                uVar12 = 0x42;
                FUN_10000e9d4();
                uVar11 = uVar12;
                _os_log_type_enabled();
                if ((int)uVar11 != 0) {
                  FUN_10000ea80();
                  uStack_c0 = uVar24;
                  uStack_bc = uVar11;
                  __os_log_impl(0x100000000,uVar12,0," %{public}s",&uStack_c0,0xc);
                }
              }
              cVar15 = '\x03';
            }
            else {
              if (iVar18 != 0) {
                FUN_10000d120("legacy=false EXTENDED_ADVERTISING_EVENT_TYPE_SCAN_RSP");
                uVar12 = 0x42;
                FUN_10000e9d4();
                uVar11 = uVar12;
                _os_log_type_enabled();
                if ((int)uVar11 != 0) {
                  FUN_10000ea80();
                  uStack_c0 = uVar24;
                  uStack_bc = uVar11;
                  __os_log_impl(0x100000000,uVar12,0," %{public}s",&uStack_c0,0xc);
                }
              }
              cVar15 = '\x04';
            }
          }
          else if ((uVar20 >> 2 & 1) == 0) {
            if (iVar18 != 0) {
              FUN_10000d120("legacy=false EXTENDED_ADVERTISING_EVENT_TYPE_CONNECTABLE");
              uVar12 = 0x42;
              FUN_10000e9d4();
              uVar11 = uVar12;
              _os_log_type_enabled();
              if ((int)uVar11 != 0) {
                FUN_10000ea80();
                uStack_c0 = uVar24;
                uStack_bc = uVar11;
                __os_log_impl(0x100000000,uVar12,0," %{public}s",&uStack_c0,0xc);
              }
            }
            cVar15 = '\0';
          }
          else {
            if (iVar18 != 0) {
              FUN_10000d120(
                           "legacy=false EXTENDED_ADVERTISING_EVENT_TYPE_CONNECTABLE & EXTENDED_ADVERTISING_EVENT_TYPE_DIRECTED_ADV"
                           );
              uVar12 = 0x42;
              FUN_10000e9d4();
              uVar11 = uVar12;
              _os_log_type_enabled();
              if ((int)uVar11 != 0) {
                FUN_10000ea80();
                uStack_c0 = uVar24;
                uStack_bc = uVar11;
                __os_log_impl(0x100000000,uVar12,0," %{public}s",&uStack_c0,0xc);
              }
            }
            cVar15 = '\x01';
          }
        }
        uVar11 = uStack_b0;
        cVar15 = cVar15 + uStack_88._5_1_ * '\x10' + -0x50;
        uStack_b0 = CONCAT71(uStack_b0._1_7_,cVar15);
        if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x1f6,"(*pBs).__RWFlag == BYTESTREAM_READ");
        }
        if (*(char *)((long)param_1 + 0xf) != '\0') {
          FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x1f6,
                        "void _HCIEventHandler_ExtendedAdvertisingReport(OI_BYTE_STREAM *, const HCI_EVENT_DESCRIPTOR *, uint8_t, bool)"
                       );
LAB_1000b6550:
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120("Could not get the address type of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar5 = *(ushort *)((long)param_1 + 0xc);
        if (*(ushort *)((long)param_1 + 10) <= uVar5) goto LAB_1000b6550;
        lVar19 = (ulong)uVar5 + 1;
        *(short *)((long)param_1 + 0xc) = (short)lVar19;
        uStack_b0._2_6_ = SUB86(uVar11,2);
        uStack_b0._0_2_ = CONCAT11(*(undefined1 *)(*param_1 + (ulong)uVar5),cVar15);
        if ((int)((uint)*(ushort *)((long)param_1 + 10) - (int)lVar19) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x1f9,"ByteStream_NumReadBytesAvail(*pBs) >= OI_BD_ADDR_BYTE_SIZE");
        }
        FUN_10000d09c((ulong)&uStack_b0 | 2,*param_1 + lVar19,6);
        uVar11 = uStack_90;
        uVar16 = uStack_98;
        uVar6 = *(ushort *)((long)param_1 + 0xc);
        uVar5 = uVar6 + 6;
        *(ushort *)((long)param_1 + 0xc) = uVar5;
        if (*(char *)((long)param_1 + 0xf) != '\0') {
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120("Could not get the address of the LE advertising report event");
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x1fc,"(*pBs).__RWFlag == BYTESTREAM_READ");
        }
        uVar7 = *(ushort *)((long)param_1 + 10);
        if (uVar7 <= uVar5) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120("Could not get the primary PHY  of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        lVar19 = *param_1;
        uVar1 = uVar6 + 7;
        *(ushort *)((long)param_1 + 0xc) = uVar1;
        bVar3 = *(byte *)(lVar19 + (ulong)uVar5);
        uStack_98._0_6_ = CONCAT15(bVar3,(undefined5)uStack_98);
        uStack_80 = CONCAT62(uStack_80._2_6_,CONCAT11(bVar3 >> 6,bVar3 >> 7)) & 0xffffffffffff01ff;
        uStack_80 = CONCAT53(uStack_80._3_5_,CONCAT12(bVar3 >> 5,(undefined2)uStack_80)) &
                    0xffffffffff01ffff;
        if (uVar7 <= uVar1) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the secondary PHY of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar5 = uVar6 + 8;
        *(ushort *)((long)param_1 + 0xc) = uVar5;
        uStack_98._7_1_ = SUB81(uVar16,7);
        uStack_98._0_7_ = CONCAT16(*(undefined1 *)(lVar19 + (ulong)uVar1),(undefined6)uStack_98);
        if (uVar7 <= uVar5) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the advertising SID of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar1 = uVar6 + 9;
        *(ushort *)((long)param_1 + 0xc) = uVar1;
        uStack_98 = CONCAT17(*(undefined1 *)(lVar19 + (ulong)uVar5),(undefined7)uStack_98);
        uVar20 = (uint)uVar7;
        if (uVar20 <= uVar1) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the advertising txPower of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar5 = uVar6 + 10;
        *(ushort *)((long)param_1 + 0xc) = uVar5;
        uStack_90 = CONCAT71(uStack_90._1_7_,*(undefined1 *)(lVar19 + (ulong)uVar1));
        uVar12 = uStack_90;
        if (uVar20 <= uVar5) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the advertising RSSI of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar7 = uVar6 + 0xb;
        *(ushort *)((long)param_1 + 0xc) = uVar7;
        uStack_98 = CONCAT71(uStack_98._1_7_,*(undefined1 *)(lVar19 + (ulong)uVar5));
        if ((int)(uVar20 - uVar7) < 2) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the periodic advertising interval of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uStack_90._4_4_ = SUB84(uVar11,4);
        uStack_90._0_4_ = CONCAT22(*(undefined2 *)(lVar19 + (ulong)uVar7),(short)uVar12);
        uVar9 = uVar6 + 0xd;
        uVar5 = (ushort)uVar9;
        *(ushort *)((long)param_1 + 0xc) = uVar5;
        if (uVar20 <= (uVar9 & 0xffff)) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the direct address type of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        uVar9 = uVar6 + 0xe;
        uVar6 = (ushort)uVar9;
        *(ushort *)((long)param_1 + 0xc) = uVar6;
        uStack_90._5_3_ = SUB83(uVar11,5);
        uStack_90._0_5_ = CONCAT14(*(undefined1 *)(lVar19 + (ulong)uVar5),(undefined4)uStack_90);
        if ((int)(uVar20 - (uVar9 & 0xffff)) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x217,"ByteStream_NumReadBytesAvail(*pBs) >= OI_BD_ADDR_BYTE_SIZE");
        }
        FUN_10000d09c((long)&uStack_90 + 5,lVar19 + (ulong)uVar6,6);
        sVar8 = *(short *)((long)param_1 + 0xc);
        *(ushort *)((long)param_1 + 0xc) = sVar8 + 6U;
        if (*(char *)((long)param_1 + 0xf) != '\0') {
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120(
                       "Could not get the direct address of the LE extended advertising report event"
                       );
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                        ,0x21a,"(*pBs).__RWFlag == BYTESTREAM_READ");
        }
        if (*(ushort *)((long)param_1 + 10) <= (ushort)(sVar8 + 6U)) {
          *(undefined1 *)((long)param_1 + 0xf) = 1;
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120("Could not get the dataLength of the LE extended advertising report event");
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        *(short *)((long)param_1 + 0xc) = sVar8 + 7;
        bVar3 = *(byte *)(*param_1 + (ulong)(ushort)(sVar8 + 6U));
        puVar13 = (undefined1 *)(ulong)bVar3;
        uStack_a8 = CONCAT62(uStack_a8._2_6_,(ushort)bVar3);
        if (0xe5 < bVar3) {
          iVar18 = 2;
          FUN_10000d938(2,0x42);
          if (iVar18 == 0) {
            return;
          }
          FUN_10000d120("Too many data bytes in the LE extended advertising report event.");
          uVar11 = 0x42;
          FUN_10000e9d4();
          uVar14 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar14 == 0) {
            return;
          }
          FUN_100105b50(uVar11);
          return;
        }
        FUN_10000d0cc(puVar13,0xd390669f);
        puStack_a0 = puVar13;
        if (puVar13 != (undefined1 *)0x0) {
          uVar16 = uStack_a8 & 0xffff;
          if ((short)uStack_a8 != 0) {
            puVar2 = puVar13 + uVar16;
            if (*(char *)((long)param_1 + 0xe) != '\x01') {
                    /* WARNING: Subroutine does not return */
              FUN_10010e274("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                            ,0x226,"(*pBs).__RWFlag == BYTESTREAM_READ");
            }
            lVar19 = *param_1;
            uVar5 = *(ushort *)((long)param_1 + 0xc);
            if (*(char *)((long)param_1 + 0xf) == '\0') {
              iVar18 = (uint)*(ushort *)((long)param_1 + 10) - (uint)uVar5;
            }
            else {
              FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                            ,0x226,
                            "void _HCIEventHandler_ExtendedAdvertisingReport(OI_BYTE_STREAM *, const HCI_EVENT_DESCRIPTOR *, uint8_t, bool)"
                           );
              iVar18 = 0;
              uVar16 = uStack_a8 & 0xffff;
            }
            if (iVar18 < (int)uVar16) {
              *(undefined1 *)((long)param_1 + 0xf) = 1;
LAB_1000b68a0:
              iVar18 = 2;
              FUN_10000d938(2,0x42);
              if (iVar18 == 0) {
                return;
              }
              FUN_10000d120(
                           "Could not get the dataLength of the LE extended advertising report event"
                           );
              uVar11 = 0x42;
              FUN_10000e9d4();
              uVar14 = uVar11;
              _os_log_type_enabled();
              if ((int)uVar14 == 0) {
                return;
              }
              FUN_100105b50(uVar11);
              return;
            }
            puVar17 = (undefined1 *)(lVar19 + (ulong)uVar5);
            do {
              puVar23 = puVar13 + 1;
              *puVar13 = *puVar17;
              puVar17 = puVar17 + 1;
              puVar13 = puVar23;
            } while (puVar23 < puVar2);
            *(short *)((long)param_1 + 0xc) = *(short *)((long)param_1 + 0xc) + (short)uStack_a8;
            if (*(char *)((long)param_1 + 0xf) != '\0') goto LAB_1000b68a0;
          }
        }
        if (1 < uStack_b0._1_1_) {
          uStack_b0._0_2_ = CONCAT11(uStack_b0._1_1_ - 2,(undefined1)uStack_b0);
        }
        FUN_10000d394(&uStack_b0);
        FUN_1000110b8(puStack_a0);
        uVar21 = uVar21 + 1;
        if (uVar21 == uVar22) {
          return;
        }
      }
      FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                    ,0x1c4,
                    "void _HCIEventHandler_ExtendedAdvertisingReport(OI_BYTE_STREAM *, const HCI_EVENT_DESCRIPTOR *, uint8_t, bool)"
                   );
LAB_1000b64f0:
      *(undefined1 *)((long)param_1 + 0xf) = 1;
      iVar18 = 2;
      FUN_10000d938(2,0x42);
      if (iVar18 == 0) {
        return;
      }
      FUN_10000d120("Could not get the event type of the LE extended advertising report event");
      uVar11 = 0x42;
      FUN_10000e9d4();
      uVar14 = uVar11;
      _os_log_type_enabled();
      if ((int)uVar14 == 0) {
        return;
      }
      FUN_100105b50(uVar11);
      return;
    }
  }
  else {
    FUN_10018e16c("/Library/Caches/com.apple.xbs/952C007F-8C9D-4363-A920-E59123B6E337/TemporaryDirectory.r6Sgt3/Sources/MobileBluetooth_base/Stack/corestack/le/LE_Events.c"
                  ,0x1ae,
                  "void _HCIEventHandler_ExtendedAdvertisingReport(OI_BYTE_STREAM *, const HCI_EVENT_DESCRIPTOR *, uint8_t, bool)"
                 );
  }
  uStack_68 = 0;
  uStack_70 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_88 = 0;
  uStack_90 = 0;
  uStack_98 = 0;
  puStack_a0 = (undefined1 *)0x0;
  uStack_a8 = 0;
  uStack_b0 = 0;
  iVar18 = 2;
  FUN_10000d938(2,0x42);
  if (iVar18 != 0) {
    FUN_10000d120("Not enough data in the packet : %d, expecting at least %d");
    uVar11 = 0x42;
    FUN_10000e9d4();
    uVar14 = uVar11;
    _os_log_type_enabled();
    if ((int)uVar14 != 0) {
      FUN_100105b50(uVar11);
    }
  }
  return;
}

