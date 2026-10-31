/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000353f8
 * original code SHA256: 54165a65b7b331990752a0d8630963d41f27a340a16187a75ef2be1f5d0e4972
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


ulong __iAP2LinkComparePacketSeq(undefined8 *param_1,undefined8 *param_2)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  
  plVar4 = (long *)*param_1;
  plVar5 = (long *)*param_2;
  uVar1 = _iAP2PacketCalcSeqGap(*(undefined1 *)(plVar4[8] + 5),*(undefined1 *)(plVar5[8] + 5));
  lVar3 = *plVar4;
  if (lVar3 != *plVar5) {
    __iAP2LinkComparePacketSeq_cold_1();
    uVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)uVar2 != 0) {
      uVar2 = ___logObjectForModule_block_invoke_cold_1();
    }
    return uVar2;
  }
  if (uVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (ulong)uVar1 | 0xffffffffffffff00;
    if (uVar1 <= *(byte *)(lVar3 + 0x1a5)) {
      uVar2 = (ulong)uVar1;
    }
  }
  return uVar2;
}

