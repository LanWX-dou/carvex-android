/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067c6c
 * original code SHA256: 52ada067b598fca56ffd2ce84aa4e82ffbcaa9e4994cdf22f595bba963d76e08
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _iAP2MsgAddDataParam
               (long param_1,undefined8 param_2,undefined8 param_3,void *param_4,uint param_5)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x20);
  lVar1 = 0;
  if ((long)((lVar2 + (ulong)(param_5 + 4)) - *(long *)(param_1 + 0x18)) <=
      (long)(ulong)*(uint *)(param_1 + 0x10)) {
    lVar1 = lVar2;
  }
  if (lVar1 != 0) {
    _iAP2MsgInitParam(param_1,lVar2,param_3,9,param_5 + 4 & 0xffff,param_2);
    _memcpy((void *)(lVar2 + 4),param_4,(ulong)param_5);
  }
  return lVar1;
}

