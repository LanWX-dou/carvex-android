/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100136828
 * original code SHA256: 70199066575553e322932d440af7c4a640d1bf80b81e6fd75e041c8a46eee330
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionLog_parseIncomingMessage(long param_1,long param_2,undefined8 param_3)

{
  code *pcVar1;
  undefined8 uVar2;
  long lVar3;
  ulong unaff_x30;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x1c8);
  if (*(long *)(lVar3 + 0x10) == 0) {
    uVar2 = _malloc_type_malloc(0xffff,0xd38c428a);
    *(undefined8 *)(lVar3 + 0x10) = uVar2;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100136894);
    (*pcVar1)();
  }
  uVar2 = _loggingProtocol_parseIncomingByteStream(param_2,param_3,lVar3);
  return uVar2;
}

