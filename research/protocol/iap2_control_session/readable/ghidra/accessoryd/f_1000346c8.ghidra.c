/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000346c8
 * original code SHA256: bcd355c846e466c7ca8163474ee190f8f7831dc356fb446d64f34466d486a834
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkResetSeqAck(long param_1,ulong param_2,int param_3)

{
  undefined8 uVar1;
  
  __CleanupSendPckList();
  *(undefined2 *)(param_1 + 0xbe) = 0;
  *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) & 0xf3;
  _iAP2TimeSyncCleanup(*(undefined8 *)(param_1 + 0x108));
  uVar1 = _iAP2TimeSyncInit(*(undefined8 *)(param_1 + 0x108));
  *(undefined8 *)(param_1 + 0x108) = uVar1;
  if (param_3 != 0) {
    *(undefined8 *)(param_1 + 0x1d0) = 0;
    *(undefined4 *)(param_1 + 0x1d8) = 0;
    *(undefined2 *)(param_1 + 0xd5) = 1;
    *(undefined8 *)(param_1 + 0x1ec) = 0;
  }
  if ((param_2 & 1) == 0) {
    _iAP2ListArrayCleanup(*(undefined8 *)(param_1 + 0x120),__DeletePckCB);
    *(undefined2 *)(param_1 + 0xbc) = 0;
    *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) & 0xfc;
    if (param_3 != 0) {
      *(undefined4 *)(param_1 + 0x1cc) = 0;
      *(undefined8 *)(param_1 + 0x1dc) = 0;
    }
  }
  return;
}

