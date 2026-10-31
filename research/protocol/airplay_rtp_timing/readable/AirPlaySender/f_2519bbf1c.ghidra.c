/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519bbf1c
 * original code SHA256: 746df51fc535a22786339edc5eca06ad9f3415878d9b4bd2727a1eb89186a6f9
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1  [16] _APAudioZeroTimeStampProviderGetUpdateInterval(long param_1)

{
  undefined1 auVar1 [16];
  
  auVar1._0_8_ = *(ulong *)(param_1 + 0x10);
  auVar1._8_8_ = 0;
  return auVar1;
}

