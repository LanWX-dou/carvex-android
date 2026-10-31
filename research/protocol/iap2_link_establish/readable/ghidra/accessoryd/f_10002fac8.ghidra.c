/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002fac8
 * original code SHA256: 86c0ee14fee66262143ba8409e2e167857dfaf9c6d0df4cc41c5a21655e0eac7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkDeviceActionSendDetect(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong unaff_x30;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendDetect_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    lVar3 = *(long *)(param_1 + 0x10);
    _iAP2LinkResetSeqAck(lVar3,0,1);
    puVar2 = *(undefined8 **)(lVar3 + 0x160);
    uVar7 = puVar2[3];
    uVar6 = puVar2[2];
    uVar5 = puVar2[5];
    uVar4 = puVar2[4];
    uVar9 = puVar2[1];
    uVar8 = *puVar2;
    *(undefined2 *)(lVar3 + 0x198) = *(undefined2 *)(puVar2 + 6);
    *(undefined8 *)(lVar3 + 0x180) = uVar7;
    *(undefined8 *)(lVar3 + 0x178) = uVar6;
    *(undefined8 *)(lVar3 + 400) = uVar5;
    *(undefined8 *)(lVar3 + 0x188) = uVar4;
    *(undefined8 *)(lVar3 + 0x170) = uVar9;
    *(undefined8 *)(lVar3 + 0x168) = uVar8;
    _iAP2LinkConnectedCB(lVar3,0);
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10002fb48);
      (*pcVar1)();
    }
    _iAP2LinkSendDetectCB(lVar3,0);
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkDeviceActionSendDetect_cold_1();
}

