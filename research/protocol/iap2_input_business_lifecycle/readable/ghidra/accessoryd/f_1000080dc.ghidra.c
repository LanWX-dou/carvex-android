/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000080dc
 * original code SHA256: d7029b8810d04c3ad32234487d5e34f58b1e55906dcea29f2da23741b998445b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkProcessOutQueue(long param_1)

{
  long lVar1;
  char *pcVar2;
  bool bVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  long *plVar8;
  int iVar9;
  long lVar10;
  char cVar11;
  ulong uVar12;
  char *pcVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  ulong unaff_x30;
  
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    _iAP2LinkProcessOutQueue_cold_1();
  }
  lVar1 = param_1 + 0x130;
  iVar9 = 4;
  do {
    iVar5 = _iAP2LinkSendWindowAvailable(param_1);
    if (iVar5 == 0) break;
    iVar5 = 0;
    bVar3 = false;
    do {
      iVar6 = _iAP2LinkSendWindowAvailable(param_1);
      if ((iVar6 == 0) ||
         (iVar6 = _iAP2ListArrayGetAvailSpace(*(undefined8 *)(param_1 + 0x128)), iVar6 == 0)) break;
      uVar16 = (ulong)*(byte *)(param_1 + 0x158);
      iVar6 = _iAP2ListArrayGetCount(*(undefined8 *)(lVar1 + uVar16 * 8));
      if (iVar6 != 0) {
        uVar7 = _iAP2ListArrayGetFirstItemIndex(*(undefined8 *)(lVar1 + uVar16 * 8));
        plVar8 = (long *)_iAP2ListArrayItemForIndex(*(undefined8 *)(lVar1 + uVar16 * 8),uVar7);
        if ((plVar8 != (long *)0x0) && (lVar15 = *plVar8, lVar15 != 0)) {
          _iAP2PacketRetain(lVar15);
          lVar10 = *(long *)(lVar15 + 0x40);
          uVar12 = (ulong)*(byte *)(param_1 + 0x1a4);
          if (uVar12 == 0) {
LAB_1000081c8:
            cVar11 = '\x01';
          }
          else {
            lVar14 = 0;
            pcVar13 = (char *)0x0;
            do {
              pcVar2 = (char *)(param_1 + 0x1b8 + lVar14 * 4);
              if (*pcVar2 != *(char *)(lVar10 + 7)) {
                pcVar2 = pcVar13;
              }
              lVar14 = lVar14 + 1;
              uVar12 = uVar12 - 1;
              pcVar13 = pcVar2;
            } while (uVar12 != 0);
            if ((pcVar2 == (char *)0x0) || ((pcVar2[3] & 1U) == 0)) goto LAB_1000081c8;
            cVar11 = '\0';
          }
          *(char *)(lVar10 + 5) = *(char *)(param_1 + 0xbe) + cVar11;
          *(undefined1 *)(lVar10 + 6) = *(undefined1 *)(param_1 + 0xbc);
          iVar6 = __iAP2LinkSendPacketCommon(param_1,lVar15,0,0);
          if (iVar6 == 0) break;
          iVar6 = _iAP2PacketGetPayloadLen(lVar15);
          *(int *)(param_1 + 0x214) = *(int *)(param_1 + 0x214) + iVar6;
          *(int *)(param_1 + 0x21c) = *(int *)(param_1 + 0x21c) + 1;
          _iAP2ListArrayDeleteItem(*(undefined8 *)(lVar1 + uVar16 * 8),uVar7,__DeletePckCB);
          if (*(code **)(lVar15 + 0x18) != (code *)0x0) {
            (**(code **)(lVar15 + 0x18))(param_1,*(undefined8 *)(lVar15 + 8));
          }
          if ((*(code **)(lVar15 + 0x10) != (code *)0x0) &&
             ((*(ushort *)(lVar15 + 0x3d) >> 0xb & 1) == 0)) {
            (**(code **)(lVar15 + 0x10))(param_1,*(undefined8 *)(lVar15 + 8));
          }
          _iAP2PacketRelease(lVar15);
        }
        iVar6 = _iAP2ListArrayGetCount(*(undefined8 *)(lVar1 + uVar16 * 8));
        bVar3 = (bool)(iVar6 != 0 | bVar3);
      }
      cVar11 = '\0';
      if (*(byte *)(param_1 + 0x158) < 4) {
        cVar11 = *(byte *)(param_1 + 0x158) + 1;
      }
      *(char *)(param_1 + 0x158) = cVar11;
      iVar5 = iVar5 + 1;
    } while (iVar5 != 5);
    if (!bVar3) {
      bVar3 = false;
      goto LAB_1000082b0;
    }
    bVar3 = iVar9 != 0;
    iVar9 = iVar9 + -1;
  } while (bVar3);
  bVar3 = true;
LAB_1000082b0:
  uVar16 = _iAP2LinkSendWindowAvailable(param_1);
  if ((uVar16 & 1) == 0) {
    _iAP2LinkEventNotify(param_1,4,0);
  }
  if (bVar3) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(0xc471,0x1000082fc);
      (*pcVar4)();
    }
    _iAP2LinkSignalSendBuffCB(param_1);
    return;
  }
  return;
}

