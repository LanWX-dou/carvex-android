/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000a5d0
 * original code SHA256: 73fc3b511b987db270bef9651316f1b0d769eea61008058b0b18c61baa84581b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


ulong _iAP2PacketParseBuffer
                (byte *param_1,uint param_2,undefined8 *param_3,uint param_4,undefined1 *param_5,
                int *param_6,int *param_7,int param_8)

{
  uint uVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  undefined8 uVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  ulong uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined1 uVar16;
  byte bVar17;
  ushort uVar18;
  undefined1 *puVar19;
  byte *pbVar20;
  byte *pbVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 extraout_d0;
  int iVar24;
  ulong local_80;
  
  uVar23 = *param_3;
  uVar7 = _iAP2LinkCurPckHdrSize(uVar23);
  uVar23 = _iAP2LinkGetChecksumType(uVar23);
  if (param_5 != (undefined1 *)0x0) {
    *param_5 = 0;
  }
  uVar5 = DAT_1001b4608;
  if ((param_1 == (byte *)0x0) || (param_2 == 0)) {
    uVar13 = 0;
  }
  else {
    uVar13 = 0;
    puVar19 = (undefined1 *)param_3[8];
    local_80 = (ulong)param_2 << 0x20;
    pbVar20 = param_1;
    do {
      uVar3 = *(ushort *)((long)param_3 + 0x3d);
      if (0x11 < (uVar3 & 0xff)) {
        return uVar13;
      }
      iVar10 = (int)uVar5;
      iVar24 = (int)((ulong)uVar5 >> 0x20);
      iVar9 = (int)local_80;
      uVar12 = (uint)(local_80 >> 0x20);
      pbVar21 = pbVar20;
      switch(uVar3 & 0xff) {
      default:
        *(undefined4 *)((long)param_3 + 0x34) = 0;
        *(undefined2 *)(param_3 + 7) = 0;
        *(undefined4 *)((long)param_3 + 0x2c) = 0;
        if (*pbVar20 != 0x55) {
          if (*pbVar20 != 0xff) goto LAB_10000acac;
          *puVar19 = 0xff;
          iVar11 = 1;
          *(undefined1 *)((long)param_3 + 0x3d) = 1;
          goto LAB_10000aca4;
        }
        if (param_7 == (int *)0x0) {
          iVar11 = 2;
        }
        else {
          *param_7 = *param_7 + 1;
          iVar11 = *(int *)((long)param_3 + 0x2c) + 2;
        }
        *puVar19 = 0;
        puVar19[1] = *pbVar20;
        *(int *)((long)param_3 + 0x2c) = iVar11;
        *(undefined1 *)((long)param_3 + 0x3d) = 0xd;
        goto LAB_10000acac;
      case 1:
        bVar17 = *pbVar20;
        if ((param_8 != 1) && (bVar17 == 0x5a)) {
          if (param_7 == (int *)0x0) {
            bVar17 = 0x5a;
          }
          else {
            *param_7 = *param_7 + 1;
            bVar17 = *pbVar20;
          }
          puVar19[1] = bVar17;
          uVar16 = 2;
LAB_10000ac98:
          *(undefined1 *)((long)param_3 + 0x3d) = uVar16;
          goto LAB_10000ac9c;
        }
        if (bVar17 != 0xff) {
          if (bVar17 == 0x55) {
            if (param_7 == (int *)0x0) {
              bVar17 = 0x55;
            }
            else {
              *param_7 = *param_7 + 1;
              bVar17 = *pbVar20;
            }
            puVar19[1] = bVar17;
            uVar16 = 0xd;
            goto LAB_10000ac98;
          }
          *(ushort *)((long)param_3 + 0x3d) = uVar3 & 0xff00;
        }
        goto LAB_10000acac;
      case 2:
        bVar17 = *pbVar20;
        puVar19[2] = bVar17;
        *(ushort *)((long)param_3 + 0x36) = (ushort)bVar17 << 8;
        uVar16 = 3;
        goto LAB_10000aa20;
      case 3:
        uVar3 = *(short *)((long)param_3 + 0x36) + (ushort)*pbVar20;
        puVar19[3] = *pbVar20;
        *(ushort *)((long)param_3 + 0x36) = uVar3;
        if ((uVar3 <= param_4 || param_4 == 0) && (uVar7 <= uVar3)) {
          uVar16 = 4;
          goto LAB_10000ac98;
        }
        ___iAP2PacketResetPacket(param_3);
        goto LAB_10000acac;
      case 4:
        puVar19[4] = *pbVar20;
        uVar16 = 5;
        goto LAB_10000aa20;
      case 5:
        puVar19[5] = *pbVar20;
        uVar16 = 6;
        goto LAB_10000aa20;
      case 6:
        puVar19[6] = *pbVar20;
        uVar16 = 7;
        goto LAB_10000aa20;
      case 7:
        puVar19[7] = *pbVar20;
        uVar16 = 8;
        goto LAB_10000aa20;
      case 8:
        pbVar21 = pbVar20 + 1;
        bVar17 = *pbVar20;
        _iAP2PacketSetHdrChecksum(param_3,uVar23,bVar17);
        *(undefined1 *)((long)param_3 + 0x3d) = 9;
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        if ((int)uVar23 == 0) {
          *(ushort *)((long)param_3 + 0x3d) = (ushort)*(byte *)((long)param_3 + 0x3e) << 8 | 10;
          uVar12 = _iAP2PacketCalcChecksum(param_3[8],8,0);
          if (uVar12 == bVar17) goto LAB_10000a894;
LAB_10000aabc:
          pbVar21 = pbVar20 + 1;
          _iAP2PacketGetChecksum(param_3[8] + 8,*(ushort *)((long)param_3 + 0x3d) >> 0xc & 3);
          if (param_6 != (int *)0x0) {
            *param_6 = *param_6 + 1;
          }
LAB_10000aae4:
          ___iAP2PacketResetPacket(param_3);
        }
        break;
      case 9:
        uVar8 = _iAP2PacketGetChecksum(param_3[8] + 8,uVar3 >> 0xc & 3);
        _iAP2PacketSetHdrChecksum(param_3,uVar23,(uint)*pbVar20 | (uVar8 & 0xff) << 8);
        *(undefined1 *)((long)param_3 + 0x3d) = 10;
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        iVar9 = _iAP2PacketCalcChecksum(param_3[8],8,uVar23);
        iVar10 = _iAP2PacketGetChecksum(param_3[8] + 8,*(ushort *)((long)param_3 + 0x3d) >> 0xc & 3)
        ;
        if (iVar9 != iVar10) goto LAB_10000aabc;
LAB_10000a894:
        pbVar21 = pbVar20 + 1;
        *(undefined2 *)((long)param_3 + 0x34) = 0;
        if (*(ushort *)((long)param_3 + 0x36) == uVar7) {
          uVar16 = 0x12;
          goto LAB_10000abd8;
        }
        break;
      case 10:
        uVar8 = _iAP2PacketGetPayloadLen(param_3);
        uVar4 = uVar8 - *(ushort *)((long)param_3 + 0x34);
        uVar15 = extraout_d0;
        if (uVar4 != 0) {
          uVar1 = uVar12;
          if (uVar4 <= uVar12) {
            uVar1 = uVar4;
          }
          _memcpy((void *)(param_3[9] + (ulong)(uint)*(ushort *)((long)param_3 + 0x34)),pbVar20,
                  (ulong)uVar1);
          uVar8 = *(ushort *)((long)param_3 + 0x34) + uVar1;
          *(short *)((long)param_3 + 0x34) = (short)uVar8;
          *(uint *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + uVar1;
          uVar15 = CONCAT44(uVar12 - uVar1,iVar9 - uVar1);
          local_80 = CONCAT44(uVar12 - uVar1,iVar9 + uVar1);
          pbVar21 = pbVar20 + uVar1;
        }
        uVar12 = _iAP2PacketGetPayloadLen(uVar15,param_3);
        if (uVar12 == (uVar8 & 0xffff)) {
          uVar16 = 0xb;
LAB_10000abd8:
          *(undefined1 *)((long)param_3 + 0x3d) = uVar16;
        }
        break;
      case 0xb:
        pbVar21 = pbVar20 + 1;
        _iAP2PacketSetPayloadChecksum(param_3,*pbVar20);
        *(undefined1 *)((long)param_3 + 0x3d) = 0xc;
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        if ((int)uVar23 == 0) {
          uVar22 = param_3[9];
          uVar14 = _iAP2PacketGetPayloadLen(param_3);
          uVar15 = 0;
          goto LAB_10000a7e4;
        }
        break;
      case 0xc:
        uVar8 = _iAP2PacketGetChecksum
                          (param_3[9] + (ulong)*(ushort *)((long)param_3 + 0x34),uVar3 >> 0xc & 3);
        _iAP2PacketSetPayloadChecksum(param_3,(uint)*pbVar20 | (uVar8 & 0xff) << 8);
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        uVar22 = param_3[9];
        uVar14 = _iAP2PacketGetPayloadLen(param_3);
        uVar15 = uVar23;
LAB_10000a7e4:
        pbVar21 = pbVar20 + 1;
        iVar9 = _iAP2PacketCalcChecksum(uVar22,uVar14,uVar15);
        iVar10 = _iAP2PacketGetChecksum
                           (param_3[9] + (ulong)*(ushort *)((long)param_3 + 0x34),
                            *(ushort *)((long)param_3 + 0x3d) >> 0xc & 3);
        if (iVar9 == iVar10) {
          *(undefined1 *)((long)param_3 + 0x3d) = 0x12;
        }
        else {
          if (param_6 != (int *)0x0) {
            *param_6 = *param_6 + 1;
          }
          ___iAP2PacketResetPacket(param_3);
        }
        break;
      case 0xd:
        bVar17 = *pbVar20;
        *(byte *)(param_3[8] + (ulong)*(uint *)((long)param_3 + 0x2c)) = bVar17;
        if (param_8 == 2) {
          if (bVar17 != 2 && bVar17 != 4) goto LAB_10000aae4;
        }
        else if (bVar17 == 0) {
          uVar16 = 0xe;
          goto LAB_10000ac98;
        }
        *(undefined1 *)((long)param_3 + 0x3d) = 0x10;
        *(ushort *)((long)param_3 + 0x36) = *pbVar20 + 4;
LAB_10000ac9c:
        iVar11 = *(int *)((long)param_3 + 0x2c) + 1;
LAB_10000aca4:
        *(int *)((long)param_3 + 0x2c) = iVar11;
        goto LAB_10000acac;
      case 0xe:
        bVar17 = *pbVar20;
        *(byte *)(param_3[8] + (ulong)*(uint *)((long)param_3 + 0x2c)) = bVar17;
        *(ushort *)((long)param_3 + 0x36) = (ushort)bVar17;
        uVar16 = 0xf;
        goto LAB_10000aa20;
      case 0xf:
        *(byte *)(param_3[8] + (ulong)*(uint *)((long)param_3 + 0x2c)) = *pbVar20;
        sVar2 = *(short *)((long)param_3 + 0x36);
        *(short *)((long)param_3 + 0x36) = sVar2 << 8;
        *(short *)((long)param_3 + 0x36) = (short)CONCAT21(sVar2,*pbVar20) + 6;
        uVar16 = 0x10;
LAB_10000aa20:
        *(undefined1 *)((long)param_3 + 0x3d) = uVar16;
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
LAB_10000acac:
        pbVar21 = pbVar20 + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        break;
      case 0x10:
        pbVar21 = pbVar20 + 1;
        *(byte *)(param_3[8] + (ulong)*(uint *)((long)param_3 + 0x2c)) = *pbVar20;
        iVar11 = *(int *)((long)param_3 + 0x2c);
        *(int *)((long)param_3 + 0x2c) = iVar11 + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
        if (iVar11 == *(ushort *)((long)param_3 + 0x36) - 2) {
          *(undefined1 *)((long)param_3 + 0x3d) = 0x11;
        }
        break;
      case 0x11:
        *(byte *)(param_3[8] + (ulong)*(uint *)((long)param_3 + 0x2c)) = *pbVar20;
        cVar6 = _iAP2PacketCalcChecksum(param_3[8] + 2,*(ushort *)((long)param_3 + 0x36) - 2,0);
        if (cVar6 != '\0') goto LAB_10000aae4;
        uVar3 = *(ushort *)((long)param_3 + 0x3d);
        *(ushort *)((long)param_3 + 0x3d) = uVar3 | 0x400;
        iVar11 = _iAP2PacketCheckDetect(param_3);
        if (iVar11 == 0) {
          iVar11 = _iAP2PacketCheckDetectNACK(param_3);
          if (iVar11 != 0) {
            uVar18 = 0x14;
            goto LAB_10000ac24;
          }
          iVar11 = _iAP2PacketCheckRequestIdentify(param_3);
          if (iVar11 == 0) {
            if (param_8 != 2) {
              uVar18 = 0x16;
              goto LAB_10000ace0;
            }
            ___iAP2PacketResetPacket(param_3);
          }
          else {
            uVar18 = 0x15;
LAB_10000ace0:
            *(ushort *)((long)param_3 + 0x3d) = uVar3 & 0xff00 | 0x400 | uVar18;
          }
        }
        else {
          uVar18 = 0x13;
LAB_10000ac24:
          *(ushort *)((long)param_3 + 0x3d) = uVar3 & 0xff00 | 0x400 | uVar18;
          if (param_5 != (undefined1 *)0x0) {
            *param_5 = 1;
          }
        }
        *(int *)((long)param_3 + 0x2c) = *(int *)((long)param_3 + 0x2c) + 1;
        pbVar21 = pbVar20 + 1;
        local_80 = CONCAT44(uVar12 + iVar24,iVar9 + iVar10);
      }
      uVar13 = local_80 & 0xffffffff;
      pbVar20 = pbVar21;
    } while (pbVar21 < param_1 + param_2);
  }
  return uVar13;
}

