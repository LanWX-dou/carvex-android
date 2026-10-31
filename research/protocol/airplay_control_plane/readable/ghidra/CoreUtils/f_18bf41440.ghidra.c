/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf41440
 * original code SHA256: bbd26b75167b4843c30347912e21aef79ea89dd6065f7db37f8da61af93d06af
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_TLV8GetNext(undefined1 *param_1,undefined1 *param_2,undefined1 *param_3,long *param_4,
            ulong *param_5,ulong *param_6)

{
  undefined1 *puVar1;
  byte bVar2;
  
  if (param_1 != param_2) {
    if (param_2 <= param_1) {
      return 0xffffe5cf;
    }
    if (1 < (ulong)((long)param_2 - (long)param_1)) {
      puVar1 = param_1 + 2;
      bVar2 = param_1[1];
      if (puVar1 + bVar2 <= param_2) {
        *param_3 = *param_1;
        *param_4 = (long)puVar1;
        *param_5 = (ulong)bVar2;
        if (param_6 != (ulong *)0x0) {
          *param_6 = (ulong)(puVar1 + bVar2);
        }
        return 0;
      }
      return 0xffffe5a2;
    }
  }
  return 0xffffe5b9;
}

