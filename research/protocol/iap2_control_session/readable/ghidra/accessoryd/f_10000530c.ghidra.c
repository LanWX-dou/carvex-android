/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000530c
 * original code SHA256: ef649a15dcb10dd0de493ce4a2d8753f302f1c0acc8cb231bd3a82a5820dbc1d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2MsgSendControl(long param_1,undefined8 *param_2)

{
  code *pcVar1;
  uint uVar2;
  ulong unaff_x30;
  
  uVar2 = _iAP2MsgCalcMessageLen(param_2);
  _iAP2MsgPreSendCtlProcess(*(undefined8 *)(param_1 + 0x10),param_2);
  *(char *)(param_2[3] + 2) = (char)(uVar2 >> 8);
  *(char *)(param_2[3] + 3) = (char)uVar2;
  if ((uVar2 & 0xffff) == 0) {
    return;
  }
  *param_2 = param_2[3];
  *(uint *)(param_2 + 1) = uVar2 & 0xffff;
  *(undefined4 *)((long)param_2 + 0xc) = 0;
  *(undefined1 *)(param_2 + 7) = 0;
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100005390);
    (*pcVar1)();
  }
  ___iAP2LinkDataSentCB(*(undefined8 *)(param_1 + 0x18),param_2);
  return;
}

