/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100031c7c
 * original code SHA256: fc7619ee04e8ee2e166deb5e33d78fb025b5e340f700a69d4ea2bd9cb606c623
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000100031e08) */

void _iAP2LinkActionDetach(long param_1,undefined1 *param_2)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  code *pcVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  byte bVar11;
  undefined1 *puVar12;
  ulong unaff_x30;
  undefined1 auVar13 [16];
  undefined1 uStack_52;
  undefined1 uStack_51;
  
  if (param_1 == 0) {
    _iAP2LinkActionDetach_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
      _iAP2LinkConnectedCB(*(undefined8 *)(param_1 + 0x10),0);
      return;
    }
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(0xc471,0x100031cb4);
    (*pcVar4)();
  }
  auVar13 = _iAP2LinkActionDetach_cold_1();
  if (auVar13._0_8_ == 0) {
    _iAP2LinkActionSendACK_cold_5();
LAB_100031ee0:
    _iAP2LinkActionSendACK_cold_4();
LAB_100031ee4:
    _iAP2LinkActionSendACK_cold_3();
  }
  else {
    if (auVar13._8_8_ == (undefined1 *)0x0) goto LAB_100031ee0;
    *auVar13._8_8_ = 0x1d;
    lVar10 = *(long *)(auVar13._0_8_ + 0x10);
    _iAP2TimeCancelTimer(*(undefined8 *)(lVar10 + 200),*(undefined1 *)(lVar10 + 0xc2));
    *(undefined1 *)(lVar10 + 0xc2) = 0xff;
    if ((*(long *)(lVar10 + 0x120) == 0) || (iVar6 = _iAP2ListArrayGetCount(), iVar6 == 0)) {
LAB_100031d9c:
      lVar8 = _iAP2PacketCreateACKPacket
                        (lVar10,*(undefined1 *)(lVar10 + 0xbe),*(undefined1 *)(lVar10 + 0xbc),0,0,0)
      ;
      if (lVar8 != 0) {
        lVar9 = 0x24c;
LAB_100031dc4:
        *(int *)(lVar10 + lVar9) = *(int *)(lVar10 + lVar9) + 1;
        __iAP2LinkSendPacketCommon(lVar10,lVar8,0,0);
        _iAP2PacketRelease(lVar8);
        return;
      }
      goto LAB_100031ee4;
    }
    lVar8 = __GetRecvPckFirstItem(lVar10,&uStack_52);
    bVar11 = 0xff;
    if (lVar8 != 0) {
      do {
        if ((*(byte *)(lVar10 + 0xd4) & 1) == 0) {
          if ((bVar11 & 0x80) != 0) {
            bVar11 = 0x80;
          }
        }
        else {
          bVar5 = _iAP2PacketCalcSeqGap
                            (*(undefined1 *)(lVar10 + 0xbc),
                             *(undefined1 *)(*(long *)(lVar8 + 0x40) + 5));
          bVar2 = bVar5;
          if (bVar11 <= bVar5) {
            bVar2 = bVar11;
          }
          if (bVar5 != 0) {
            bVar11 = bVar2;
          }
        }
        lVar8 = __GetRecvPckNextItem(lVar10,uStack_52,&uStack_52);
      } while (lVar8 != 0);
      if (bVar11 < 2) goto LAB_100031d9c;
    }
    if (*(byte *)(lVar10 + 0x19b) < bVar11) goto LAB_100031d9c;
    iVar6 = _iAP2ListArrayGetCount(*(undefined8 *)(lVar10 + 0x120));
    if (iVar6 != 0) {
      uVar7 = _iAP2ListArrayGetCount(*(undefined8 *)(lVar10 + 0x120));
      uVar1 = (uint)*(ushort *)(lVar10 + 0x1a6);
      if ((uint)*(ushort *)(lVar10 + 0xc0) <= (uint)*(ushort *)(lVar10 + 0x1a6)) {
        uVar1 = (uint)*(ushort *)(lVar10 + 0xc0);
      }
      iVar6 = -0xc;
      if (*(char *)(lVar10 + 0xd5) != '\x02') {
        iVar6 = -10;
      }
      uVar1 = iVar6 + uVar1;
      uVar3 = uVar1 & 0xff;
      if (uVar7 <= uVar1) {
        uVar1 = uVar7;
        uVar3 = uVar7;
      }
      lVar8 = _iAP2PacketCreateEAKPacket
                        (lVar10,*(undefined1 *)(lVar10 + 0xbe),*(undefined1 *)(lVar10 + 0xbc),0,
                         uVar3);
      if (lVar8 != 0) {
        puVar12 = *(undefined1 **)(lVar8 + 0x48);
        lVar9 = __GetRecvPckFirstItem(lVar10,&uStack_51);
        if (((uVar1 & 0xff) != 0) && (lVar9 != 0)) {
          uVar7 = 0;
          do {
            *puVar12 = *(undefined1 *)(*(long *)(lVar9 + 0x40) + 5);
            uVar7 = uVar7 + 1;
            lVar9 = __GetRecvPckNextItem(lVar10,uStack_51,&uStack_51);
            puVar12 = puVar12 + 1;
          } while ((uVar7 & 0xff) < (uVar1 & 0xff) && lVar9 != 0);
        }
        *(int *)(lVar10 + 0x230) = *(int *)(lVar10 + 0x230) + 1;
        lVar9 = 0x244;
        goto LAB_100031dc4;
      }
      goto LAB_100031eec;
    }
  }
  _iAP2LinkActionSendACK_cold_2();
LAB_100031eec:
                    /* WARNING: Subroutine does not return */
  _iAP2LinkActionSendACK_cold_1();
}

