/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cb0b8
 * original code SHA256: cd10b271d98ca7bbec441e91cd937e593d9424ce83f906d60200b6cf19af109e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkRunLoopTimeout(long param_1,undefined8 param_2,int param_3)

{
  code *pcVar1;
  undefined8 uVar2;
  ulong unaff_x30;
  
  if ((param_1 == 0) || ((*(byte *)(param_1 + 0x2c) & 1) != 0)) {
    return;
  }
  if (param_3 < 0xd) {
    if (param_3 == 0xb) {
      uVar2 = 0x80;
    }
    else {
      if (param_3 != 0xc) {
        return;
      }
      uVar2 = 0x10;
    }
  }
  else if (param_3 == 0xd) {
    uVar2 = 0x20;
  }
  else {
    if (param_3 != 0x1a) {
      return;
    }
    uVar2 = 0x40;
  }
  _iAP2LinkRunLoopSetEventMaskBit(param_1,uVar2);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
    _iAP2LinkRunLoopSignal(param_1,0,0);
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000cb154);
  (*pcVar1)();
}

